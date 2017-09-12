/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.
                
                       http://www.nexgo.cn/en/

 ******************************************************************************
  File Name     :  adjust.c
  Version       :  
  Author        :  wenmin
  Date          :  2016-10-19
  Description   : 


  
******************************************************************************/
#include "global.h"

/*----------------------------------------------------------------------------*/
/*****************************************************************************
** Description :  Pack the ISO8583 message of adjustment transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 AdjustPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 ret;
    u8 buf[128] = {0};
    ST_MSGINFO *pst_msginfo = NULL;
    u8 tmp[256];    

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    // public field
    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "702406C030C09A11");
    if (ret <= 0)
    {
        return 0;
    }

    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0220", 4);

    // #2
    memset(tmp, 0, sizeof(tmp));
    if(SDK_OK == TrnGetMagCardNo(&gstTransData.stTransLog.stCardInfo.stCardData, tmp))
    {
        IsoSetField(pstIsoMsg, 2, tmp, strlen(tmp));
    }
    
    // #11
    IsoSetField(pstIsoMsg, 11, pst_msginfo->asTraceNO, 6);
    
    // #22
    IsoSetField(pstIsoMsg, 22, "012", 3);
    
    // #37
    IsoSetField(pstIsoMsg, 37, pst_msginfo->asRefNO, 12);

    // #38
    IsoSetField(pstIsoMsg, 38, pst_msginfo->asAuthCode, 6);
    
    // #48
    IsoSetField(pstIsoMsg, 48, pst_msginfo->asTipAmount, 12);

    // #60.1
    memset(buf, 0, sizeof(buf));
    strcat(buf, "34");
    // #60.2  batch number
    strcat(buf, gstAppSysCfg.stTransParam.asBatchNO);
    // #60.3  network management information code
    strcat(buf, "000");
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));

    // #61
    memset(buf, 0, sizeof(buf)); 
    sprintf(buf, "%-6.6s%-6.6s%-4.4s00", pst_msginfo->asOrigBatchNO, 
                pst_msginfo->asOrigTraceNO, pst_msginfo->asOrigDate);
    IsoSetField(pstIsoMsg, 61, buf, strlen(buf));

    // #63
    IsoSetField(pstIsoMsg, 63, pst_msginfo->asInterOrgCode, sizeof(pst_msginfo->asInterOrgCode));

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Adjustment transaction process(add tip)
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void AdjustTrans(void)
{
    s32 ret;
    u32 tip, amount;
    u8 buf[64];
    ST_MSGINFO *pst_msginfo = NULL;
    ST_TRANSLOG st_translog;

    /* step1 : initializes the transaction data */
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    memset(&st_translog, 0, sizeof(ST_TRANSLOG));
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    gstTransData.stTransLog.stMsgInfo.ucCashierNO = gstLoginInfo.ucUserNO;
    gstTransData.stTransLog.eTransID = TRANSID_TIP;
    
    /* step2 : Display title */
    DispTitle(STR_TRANS_TIP);
    
    /* step3 : check transaction conditions */
    if(!TrnCheckCondition(TRUE, gstAppSysCfg.stTransParam.bIsSupportAdjust))
    {
        return;
    }
    
    /* step4 : get original transaction */
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        if (!TrnInputTraceNo(buf))
        {
            return;
        }

        ret = RecordSearch(LOG_MSG_TRACENO, buf, &st_translog); 
        if (SDK_OK == ret)
        {
            break;
        }
        else
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_TRANS_NOT_FOUND, SDK_DISP_DEFAULT);
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
    }

    /* step5 : check original transaction */
    if(st_translog.stTransStatus.bIsAdjusted)
    {
        TrnSetStatus(ERR_ALREADY_ADJUSTED);
        return;
    }

    if(st_translog.stTransStatus.bIsVoided)
    {
        TrnSetStatus(ERR_ALREADY_VOID);
        return;
    }

    if(TRANSID_SALE != st_translog.eTransID)
    {
        TrnSetStatus(ERR_NOTALLOW_ADJUST);
        return;
    }

    memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
    gstTransData.stTransLog.eTransID = TRANSID_TIP;
    strcpy(pst_msginfo->asOrigTraceNO, st_translog.stMsgInfo.asTraceNO);
    strcpy(pst_msginfo->asOrigBatchNO, st_translog.stMsgInfo.asBatchNO);
    memcpy(pst_msginfo->asOrigDate, st_translog.stMsgInfo.asTransDate, 4);

    /* step6 : disp transaction detail */
    if (SDK_OK != DispTransDetail(&st_translog))
    {
        return;
    }

    DispTitle(STR_TRANS_TIP);

    /* step7 : input transaction amount */
    while(1)
    {
        memset(pst_msginfo->asTipAmount, 0,sizeof(pst_msginfo->asTipAmount));
        ret = TrnInputAmount(SALE_AMOUNT, pst_msginfo->asTipAmount);
        if (SDK_OK != ret)
        {
            return;
        }
           
        tip = atoi(pst_msginfo->asTipAmount);
        amount = atoi(pst_msginfo->asAmount);
        if(tip > (amount * gstAppSysCfg.stTransParam.uiTipRate / 100))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_TIP_EXCEED, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            ret = sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_OPERATE);
            if(SDK_KEY_ENTER == ret)
            {
                continue;
            }
            TrnSetStatus(ret);
            return;
        }
        else
        {
            break;
        }
    }
    
//    if(SDK_OK != TrnCheckTotalAmount(gstTransData.stTransLog.eTransID, pst_msginfo->asAmount))
//    {
//        TrnSetStatus(ERR_AMT_LIMIT);
//        return;
//    }

    amount += tip;
    sprintf(pst_msginfo->asAmount, "%0*d", 12, amount);

    /* step8 : save transaction record */
    gstTransData.stTransLog.stTransStatus.bIsOffline = TRUE;
    gstTransData.stTransLog.stTransStatus.bIsNeedRePrint = TRUE;
    gstTransData.stTransLog.stMsgInfo.ucCashierNO = gstLoginInfo.ucUserNO;
    memcpy(pst_msginfo->asTraceNO, gstAppSysCfg.stTransParam.asTraceNO, 6);    
    gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode = 0;
    if(SDK_OK == sdkGetRtc(buf))
    {
        sdkBcdToAsc(pst_msginfo->asTransDate, &buf[1], 2);
        sdkBcdToAsc(pst_msginfo->asTransTime, &buf[3], 3);
    }
    
    if(SDK_OK != RecordAppend(&gstTransData.stTransLog))
    {
        TrnSetStatus(ERR_FILE_SYSTEM);
        return;
    }
    TrnIncTraceNo(1);
    
    /* step9 : update original transaction record */
    st_translog.stTransStatus.bIsAdjusted = TRUE;
    if(SDK_OK != RecordUpdate(&st_translog))
    {
        TrnSetStatus(ERR_FILE_SYSTEM);
        return;
    }
    
    /* step10 : print receipt */
    DispTransSucc();
    PrintRecipt(FALSE);
    TrnSetStatus(TRANS_STATUS_FINISH);
    
    return;     
}

/*****************************************************************************
** Description :  Adjustment transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void OnAdjust(void)
{
    AdjustTrans();
    sdkPEDCancel();
    EmvLedClose();
}


