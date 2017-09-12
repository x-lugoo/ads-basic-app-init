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
** Description :  Pack the ISO8583 message of refund transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RefundPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;
    u8 buf[128] = {0};

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
     
    if(REFUND_MODE_GENERAL != gstAppSysCfg.stTransParam.uiRefundMode)
    {
        ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "702406C03CC0981B");
    }
    else
    {
        ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "7024068030C08801");
    } 

    if (ret <= 0)
    {
        return 0;
    }
    // #0
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0220", 4);

    if (ret <= 0)
    {
        return 0;
    }
    
    // #3
    IsoSetField(pstIsoMsg, 3, "200000", 6);

    // #25
    IsoSetField(pstIsoMsg, 25, "00", 2);

    if(REFUND_MODE_GENERAL != gstAppSysCfg.stTransParam.uiRefundMode)
    {
        // #37
        IsoSetField(pstIsoMsg, 37, pst_msginfo->asRefNO, 12);
        
        // #61
        if (strlen(pst_msginfo->asOrigDate))
        {
            memset(buf, 0, sizeof(buf));
            memset(buf, '0', 12);

            if (4 == strlen(pst_msginfo->asOrigDate))
            {
                strncat(buf, pst_msginfo->asOrigDate, 4);
            }
            else
            {
                strcat(buf, "0000");
            }
            IsoSetField(pstIsoMsg, 61, buf, strlen(buf));
        }
    }
    
    // #60.1  transaction type code
    memset(buf, 0, sizeof(buf));
    strcat(buf, "25");
    // #60.2  batch number
    strcat(buf, gstAppSysCfg.stTransParam.asBatchNO);
    // #60.3  network management information code
    strcat(buf, "000");
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));
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
    
    // #63
    if(3 == strlen(pst_msginfo->asInterOrgCode))
    {
        IsoSetField(pstIsoMsg, 63, pst_msginfo->asInterOrgCode, strlen(pst_msginfo->asInterOrgCode));
    }
    else
    {
        IsoSetField(pstIsoMsg, 63, "000", 3);
    }
    
    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Refund transaction process
** Parameters  :  input
                  (1)u16 usCardType: all support card type in this transaction
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void RefundTrans(u16 usCardType)
{
    SDK_ICC_TRADE_PARAM st_tradeparam;
    ST_CARDINFO *pst_cardinfo = NULL;
    ST_MSGINFO *pst_msginfo = NULL;
    s32 ret;

    /* step1 : initializes the transaction data */
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    gstTransData.stTransLog.stMsgInfo.ucCashierNO = gstLoginInfo.ucUserNO;
    gstTransData.stTransLog.eTransID = TRANSID_REFUND;

    /* step2 : Display title */
    DispTitle(STR_TRANS_REFUND);
    
    /* step3 : check transaction conditions */
    if(!TrnCheckCondition(TRUE, gstAppSysCfg.stTransParam.bIsSupportRefund))
    {
        return;
    }

    /* step4 : verify admin password */
    if(!TrnCheckAdminPwd())
    {
        return;
    }

    /* step5 : Process card */
    ret = TrnReadCard(usCardType, &st_tradeparam, pst_cardinfo);
    if (ret < 0)
    {
        if(0 == TrnGetStatus())
        {
            TrnSetStatus(ERR_READ_CARD);
        }
        return;
    }
    
    /* step6 : Input original transaction info */
    if(REFUND_MODE_GENERAL != gstAppSysCfg.stTransParam.uiRefundMode)
    {
        if (!TrnInputReferenceNo(pst_msginfo->asRefNO))
        {
            return;
        }
        
        if (!TrnInputDate(pst_msginfo->asOrigDate))
        {
            return;
        }
    }    
    
    /* step7 : pre-dial if necessary */
    CommuPreLink();

    /* step8 : input transaction amount */
    while(1)
    {
        memset(pst_msginfo->asAmount, 0, sizeof(pst_msginfo->asAmount));
        ret = TrnInputAmount(SALE_AMOUNT, pst_msginfo->asAmount);
        if (SDK_OK != ret)
        {
            return;
        }
        
//        if(SDK_OK != TrnCheckTotalAmount(gstTransData.stTransLog.eTransID, pst_msginfo->asAmount))
//        {
//            TrnSetStatus(ERR_AMT_LIMIT);
//            return;
//        }

        if(!TrnCheckRefundAmount(pst_msginfo->asAmount))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_REFUND_AMT_EXCEED, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            ret = sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_OPERATE);
            if(SDK_KEY_ENTER == ret)
            {
                continue;
            }
            TrnSetStatus(ret);
            return;
        }

        ret = TrnConfirmRefundAmount(pst_msginfo->asAmount);
        if(SDK_OK == ret)
        {
            break;
        }
        else if(SDK_EQU != ret)
        {
            TrnSetStatus(ret);
            return;
        }
    }
    
    /* step9 : Exchange transaction ISO8538 messages */
    ret = CommuExchangeIsoMsg(&st_tradeparam, RefundPackMsg, FALSE, TRUE, TRUE);
    if (ret <= 0)
    {
        return;
    }

    DispTransSucc();
    
    /* step10 : print receipt */
    PrintRecipt(FALSE);
    
    TrnSetStatus(TRANS_STATUS_FINISH);
    
    return;    
}

/*****************************************************************************
** Description :  refund transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void OnRefund(void)
{
    RefundTrans(ICCRF|MAGONLY);
    sdkPEDCancel();
    EmvLedClose();
}

