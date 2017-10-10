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
	
#ifdef JEFF_ECHO
	Trace("xgd","pstIsoMsg->nBagLen=%d  %s(%d)\r\n",pstIsoMsg->nBagLen,__FUNCTION__,__LINE__);
#endif   

    // #0  Message Type Identifier (MTI)
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0200", 4);

#ifdef JEFF_ECHO
	Trace("xgd","pstIsoMsg->nBagLen=%d Ret=%d %s(%d)\r\n",pstIsoMsg->nBagLen,ret,__FUNCTION__,__LINE__);
#endif	
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


s32 EchoSalePackMsg(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 	mac[16] = {0};
	u8 field39[2+1] = {0};
	u8 *pSendEchoMsg;
	s32 iRet;
	
	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"\x02\x10",2);//set msg code
	pstIsoMsgRecv->nBagLen += 2;
	pSendEchoMsg += 2;
	memcpy(pSendEchoMsg,"\x20\x38\x00\x81\x0E\xD0\x80\x13",8);//set bitmap
	pstIsoMsgRecv->nBagLen += 8;
	iRet = EchoIsoPackPublicMsg(TRANSID_SALE,pstIsoMsgRecv);//field 11,12,13
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField25(pstIsoMsgRecv); //Field 25,condition code
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField32(pstIsoMsgRecv);//field 32 acquirer  identification instruction
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField37(pstIsoMsgRecv); //Field 37,reference num
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField38(pstIsoMsgRecv); // Field 38,auth code
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField39(TRANSID_SALE,pstIsoMsgRecv,field39);  //Field 39,response code
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleTIDMID(pstIsoMsgRecv);//set field 41,42
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField44(pstIsoMsgRecv); //Field 44
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField49(pstIsoMsgRecv); //Field 49
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField60(TRANSID_SALE,pstIsoMsgRecv); //Field 60
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField63(pstIsoMsgRecv); //Field 63
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoGetMsgMac(pstIsoMsgRecv->ucBagData,pstIsoMsgRecv->nBagLen,mac,11);//Taking mannual method to calc mac
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,mac,8);
	pstIsoMsgRecv->nBagLen += 8;
	return SDK_OK;
#endif
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
    s32 ret;
    u8 buf[16], sale_amt[6], cashback_amt[6];

    /* step1 : initializes the transaction data */
    if(0 == strlen(gstTransData.stTransLog.stMsgInfo.asAmount))
    {
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    }
    memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_msginfo->ucCashierNO = gstLoginInfo.ucUserNO;
    gstTransData.stTransLog.eTransID = TRANSID_SALE;

    /* step2 : Display title */
    DispTitle(STR_TRANS_SALE);

    /* step3 : check transaction conditions */
    if(!TrnCheckCondition(TRUE, gstAppSysCfg.stTransParam.bIsSupportSale))
    {
        return;
    }

    /* step4 : input transaction amount */
    ret = TrnInputAmount(SALE_AMOUNT, pst_msginfo->asAmount);
    if(SDK_OK != ret)
    {
        return;
    }

    /* step5 : input cashback amount(optional) */
    ret = TrnInputAmount(CASHBACK_AMOUNT, pst_msginfo->asCashbackAmount);
    if(SDK_OK != ret)
    {
        return;
    }

//    if(SDK_OK != TrnCheckCashBackAmount(pst_msginfo->asAmount, pst_msginfo->asCashbackAmount))
//    {
//        TrnSetStatus(ERR_CASHBACK_LIMIT);
//        return;
//    }

    /* step6 : calculate total amount (total amount = sale amount + cashback amount) */
    memset(sale_amt, 0, sizeof(sale_amt));
    sdkAscToBcd(sale_amt, pst_msginfo->asAmount, 12);

    memset(cashback_amt, 0, sizeof(cashback_amt));
    sdkAscToBcd(cashback_amt, pst_msginfo->asCashbackAmount, 12);
    
    sdkBcdAdd(sale_amt, sale_amt, 6, cashback_amt, 6);
    memset(pst_msginfo->asAmount, 0, sizeof(pst_msginfo->asAmount));
    sdkBcdToAsc(pst_msginfo->asAmount, sale_amt, 6);
    
//    if(SDK_OK != TrnCheckTotalAmount(gstTransData.stTransLog.eTransID, pst_msginfo->asAmount))
//    {
//        TrnSetStatus(ERR_AMT_LIMIT);
//        return;
//    }

    /* step7 : Process card */
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
            memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
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

