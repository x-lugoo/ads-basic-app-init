/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.
                
                       http://www.nexgo.cn/en/

 ******************************************************************************
  File Name     :   
  Version       :  
  Author        :  wenmin
  Date          :  2016-10-19
  Description   : 


  
******************************************************************************/
#include "global.h"

/*----------------------------------------------------------------------------*/
/*****************************************************************************
** Description :  Pack the ISO8583 message of sale transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SalePackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 buf[128] = {0};
    s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "702406C030C09A11");

    if (ret <= 0)
    {
        return 0;
    }
    
    // #0  Message Type Identifier (MTI)
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0200", 4);
    if (ret <= 0)
    {
        return 0;
    }
    
    // #60.1  transaction type code
    memset(buf, 0, sizeof(buf));
    strcat(buf, "22");
    // #60.2  batch number
    strcat(buf, gstAppSysCfg.stTransParam.asBatchNO);
    // #60.3  network management information code
    strcat(buf, "000");
    // #60.4  Reading capability at the terminal
    if ((0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_QCTLS, 2)) || 
        (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_MSD, 2)) || 
        (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_CTLS, 2)))                 
    {
        strcat(buf, "6");
    }
    else if ((0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_MANUAL, 2)) ||
             (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_SWIPE, 2)) ||
             (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_INSERT, 2)))
    {
        strcat(buf, "5");
    }
    else 
    {
        strcat(buf, "0");
    }
    // #60.5  IC card condition code based on CUPIC debit / credit standard
    if (CTLSFLOW_FALLBACK == gstTransData.stTransLog.stCardInfo.stCardParam.ucCLType && 
        gstTransData.stTransLog.stCardInfo.stCardData.bIsIccMagCard)       //fallbcak
    {
        strcat(buf, "2");
    }
    else
    {
        strcat(buf, "0");
    }
    // #60.6  Symbol of supporting partial deduction and return balance
    strcat(buf, "0");
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  ICC offline Sale transaction process 
** Parameters  :  input
                  (1)s32 iIccRet: return value from EMV kernel
                  
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SaleOfflineProc(s32 iIccRet)
{
    s32 ret = SDK_ERR;
    u8 buf[64];

    SalePackMsg(&gstSendPacket);
    TrnUpdateTransDataSend(&gstSendPacket);

    gstTransData.stTransLog.stTransStatus.bIsOffline = TRUE;
    if(SDK_OK == sdkGetRtc(buf))
    {
        sdkBcdToAsc(gstTransData.stTransLog.stMsgInfo.asTransDate, &buf[1], 2);
        sdkBcdToAsc(gstTransData.stTransLog.stMsgInfo.asTransTime, &buf[3], 3);
    }
    
    if (CARDPROC_OFFLINE_SUCC == iIccRet) 
    {
        gstTransData.stTransLog.stTransStatus.bIsNeedRePrint = TRUE;
        ret = RecordAppend(&gstTransData.stTransLog);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_FILE_SYSTEM);
            ret = SDK_ERR;
        }
        TrnIncTraceNo(1);
        PrintRecipt(FALSE);
        ret = SDK_OK;
    }
    else
    {
        gstTransData.stTransLog.stTransStatus.bIsIccFailTrans = TRUE;
        DispAOSA();
        ret = RecordAppend(&gstTransData.stTransLog);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_FILE_SYSTEM);
            ret = SDK_ERR;
        }
        else
        {
            TrnIncTraceNo(1);
            TrnSetStatus(SDK_ERR);
            ret = SDK_ERR;
        }
    }
    
    return ret;
}

/*****************************************************************************
** Description :  Sale transaction process
** Parameters  :  input
                  (1)u16 usCardType: all support card type in this transaction
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void SaleTrans(u16 usCardType)
{
    SDK_ICC_TRADE_PARAM st_tradeparam;
    ST_CARDINFO *pst_cardinfo = NULL;
    ST_MSGINFO *pst_msginfo = NULL;
	ST_SENT_POLICY_DATA_FIELD *stPolicyDataField = NULL;
    s32 ret;
    u8 buf[16], sale_amt[6], cashback_amt[6];
 
    memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_msginfo->ucCashierNO = gstLoginInfo.ucUserNO;
	stPolicyDataField  = &gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField;
    gstTransData.stTransLog.eTransID = TRANSID_SALE;

    DispTitle(STR_TRANS_SALE);
    if(!TrnCheckCondition(TRUE, gstAppSysCfg.stTransParam.bIsSupportSale))
    {
        return;
    }
	memcpy(pst_msginfo->asAmount, stPolicyDataField->asAmount, 12);
    while(1)
    {
        ret = TrnReadCard(usCardType, &st_tradeparam, pst_cardinfo);
        Trace("sale", "TrnReadCard=[%d]\r\n", ret);

        if (ret < 0)
        {
            if(0 == TrnGetStatus())
            {
                TrnSetStatus(ERR_READ_CARD);
            }
            return;
        }

        if ((SDK_ICC_RF == pst_cardinfo->stCardParam.ucCardMode)
            && ((CARDPROC_CTLS_SWITCH == ret)
                || (CARDPROC_CTLS_FALLBACK == ret)
                || (CARDPROC_DISCOVERY == ret)))
        {
            if (CARDPROC_CTLS_SWITCH == ret)
            {
                usCardType &= ~SDK_ICC_RF;
            }
           
            gstTransData.stTransLog.eTransID = TRANSID_SALE;
            sdkBcdToAsc(pst_msginfo->asAmount, sale_amt, 6);
            sdkBcdToAsc(pst_msginfo->asCashbackAmount, cashback_amt, 6);
            continue;
        }
        else
        {
            break;
        }
    }

    if(CARDPROC_OFFLINE_FAIL == ret || CARDPROC_OFFLINE_SUCC == ret)
    {
        SaleOfflineProc(ret);
        return;
    }
    /* step8 : pre-dial if necessary */
    CommuPreLink();

    /* step9 : Input PIN */
    if (SDK_OK == ret)
    {
        memset(buf, 0, sizeof(buf));
        TrnFormatAmount(buf, pst_msginfo->asAmount, TRUE);     //Convert BCD-coded amount to display string
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_AMOUNT, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, buf, SDK_DISP_RIGHT_DEFAULT);          //Display amount and prompt for password
        sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_INPUT_PIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();
        ret = TrnInputPin(TRUE, pst_msginfo->asAmount, &pst_cardinfo->stCardData, gstTransData.hePIN, SDK_DISP_LINE5);  // Input password

        if (SDK_OK != ret && SDK_PED_NOPIN != ret)
        {
            return;
        }
    }
    /* step10 : Exchange transaction ISO8538 messages */
    ret = CommuExchangeIsoMsg(&st_tradeparam, SalePackMsg, TRUE, TRUE, TRUE);
    if (ret <= 0)
    {
        return;
    }

    DispTransSucc();
    
    /* step11 : print receipt */
    PrintRecipt(FALSE);

    TrnSetStatus(TRANS_STATUS_FINISH);
    
    return;
}

/*****************************************************************************
** Description :  Sale transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void OnSale(void)
{
    SaleTrans(ICCRF|MAGONLY);
    sdkPEDCancel();
    EmvLedClose();
}

