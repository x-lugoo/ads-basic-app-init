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
** Description :  Check original transaction is support void
** Parameters  :  input:
                  (1)ST_TRANSLOG *pstTransLog : original transaction data
                  
** Return      :  (1)SDK_ERR: original transaction can't be void
                  (2)SDK_OK: original transaction can be void
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 VoidCheckOriginalTrans(ST_TRANSLOG *pstTransLog)
{
    ST_TRANS_STATUS *pst_status = NULL;

    pst_status = &gstTransData.stTransLog.stTransStatus;
    
    if (pst_status->bIsVoided)
    {
        TrnSetStatus(ERR_ALREADY_VOID);
        return SDK_ERR;
    }
    
    if (pst_status->bIsAdjusted)
    {
        TrnSetStatus(ERR_ALREADY_ADJUSTED);
        return SDK_ERR;
    }

    if (TRANSID_SALE != gstTransData.stTransLog.eTransID || TRUE == gstTransData.stTransLog.stTransStatus.bIsNeedReversal
        || TRUE == gstTransData.stTransLog.stTransStatus.bIsIccFailTrans)
    {
        TrnSetStatus(ERR_NOTALLOW_VOID);
        return SDK_ERR;
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Pack the ISO8583 message of void transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 VoidPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 ret;
    u8 buf[128] = {0};
    ST_MSGINFO *pst_msginfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "702406C030C09819");

    if (ret <= 0)
    {
        return 0;
    }
    // #0 MTI
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0200", 4);

    if (ret <= 0)
    {
        return 0;
    }
    
    // #3
    IsoSetField(pstIsoMsg, 3, "200000", 6);

    // #25
    IsoSetField(pstIsoMsg, 25, "00", 2); 
    
    // #37
    IsoSetField(pstIsoMsg, 37, pst_msginfo->asRefNO, 12);

    // #38
    IsoSetField(pstIsoMsg, 38, pst_msginfo->asAuthCode, 6);

    // #60
    memset(buf, 0, sizeof(buf));
    strcat(buf, "23");
    strcat(buf, gstAppSysCfg.stTransParam.asBatchNO);
    strcat(buf, "000");

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

    if (CTLSFLOW_FALLBACK == gstTransData.stTransLog.stCardInfo.stCardParam.ucCLType && 
        gstTransData.stTransLog.stCardInfo.stCardData.bIsIccMagCard)       //fallbcak
    {
        strcat(buf, "2");
    }
    else
    {
        strcat(buf, "0");
    }

    strcat(buf, "0");
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));

    // #61
    memset(buf, 0, sizeof(buf));
   
    sprintf(buf, "%-6.6s%-6.6s", pst_msginfo->asOrigBatchNO, 
                                 pst_msginfo->asOrigTraceNO);
    IsoSetField(pstIsoMsg, 61, buf, strlen(buf));
    
    return pstIsoMsg->nBagLen;
}

s32 EchoVoidPackMsg(SDK_8583_ST8583 *pstIsoMsgRecv)
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
	memcpy(pSendEchoMsg,"\x20\x38\x00\x81\x0E\xD0\x80\x1B",8);//set bitmap
	pstIsoMsgRecv->nBagLen += 8;
	iRet = EchoIsoPackPublicMsg(TRANSID_VOID,pstIsoMsgRecv);//field 11,12,13
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField25(pstIsoMsgRecv); //Field 25,condition code
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField32(pstIsoMsgRecv);//field 32
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
	iRet = EchoHandleField39(TRANSID_VOID,pstIsoMsgRecv,field39);  //Field 39,response code
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
	iRet = EchoHandleField60(TRANSID_VOID,pstIsoMsgRecv); //Field 60
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoHandleField61(pstIsoMsgRecv);
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
** Description :  Void transaction process
** Parameters  :  input
                  (1)u16 usCardType: all support card type in this transaction
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void VoidTrans(u16 usCardType)
{    
    SDK_ICC_TRADE_PARAM st_tradeparam;
    ST_CARDINFO *pst_cardinfo = NULL;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_CARDINFO st_cardinfo;
    ST_TRANSLOG st_translog;
    s32 ret;
    u8 buf[64];

    /* step1 : initializes the transaction data */
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    gstTransData.stTransLog.stMsgInfo.ucCashierNO = gstLoginInfo.ucUserNO;
    gstTransData.stTransLog.eTransID = TRANSID_VOID;

    /* step2 : Display title */
    DispTitle(STR_TRANS_VOID);
    
    /* step3 : check transaction conditions */
    if(!TrnCheckCondition(TRUE, gstAppSysCfg.stTransParam.bIsSupportVoid))
    {
        return;
    }

    /* step4 : verify admin password */
    if(!TrnCheckAdminPwd())
    {
        return;
    }

    /* step5 : get original transaction */
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        if (!TrnInputTraceNo(buf))
        {
            return;
        }

        ret = RecordSearch(LOG_MSG_TRACENO, buf, &gstTransData.stTransLog); 
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

    /* step6 : check original transaction */
    if(SDK_OK != VoidCheckOriginalTrans(&gstTransData.stTransLog))
    {
        return;
    }   
//    if(SDK_OK != TrnCheckTotalAmount(TRANSID_VOID, pst_msginfo->asAmount))
//    {
//        TrnSetStatus(ERR_AMT_LIMIT);
//        return;
//    }

    memcpy(&st_translog, &gstTransData.stTransLog, sizeof(ST_TRANSLOG));
    memcpy(pst_msginfo->asOrigBatchNO, pst_msginfo->asBatchNO, 6);
    memcpy(pst_msginfo->asOrigTraceNO, pst_msginfo->asTraceNO, 6);

    /* step7 : disp transaction detail */
    if (SDK_OK != DispTransDetail(&gstTransData.stTransLog))
    {
        return;
    }

    DispTitle(STR_TRANS_VOID);
    gstTransData.stTransLog.stMsgInfo.ucCashierNO = gstLoginInfo.ucUserNO;
    gstTransData.stTransLog.eTransID = TRANSID_VOID;

    /* step8 : Process card */
    if (gstAppSysCfg.stTransParam.bIsVoidNeedCard)
    {
        memcpy(&st_cardinfo, pst_cardinfo, sizeof(st_cardinfo));
        memset(pst_cardinfo, 0, sizeof(st_cardinfo));
        if (SDK_ICC_ICC == st_cardinfo.stCardParam.ucCardMode
            || SDK_ICC_RF == st_cardinfo.stCardParam.ucCardMode)
        {
            usCardType = ICCRF;
        }
        else
        {
            usCardType = MAGONLY;
        }
        
        ret = TrnReadCard(usCardType, &st_tradeparam, pst_cardinfo); 
        if (ret < 0)
        {
            if(0 == TrnGetStatus())
            {
                TrnSetStatus(ERR_READ_CARD);
            }
            return;
        }
        if(CARDPROC_OFFLINE_FAIL == ret || CARDPROC_OFFLINE_SUCC == ret)
        {
            //offline process
            return;
        }

        if(st_cardinfo.stCardData.ucCardLen != pst_cardinfo->stCardData.ucCardLen ||
           0 != memcmp(st_cardinfo.stCardData.asCardNO, pst_cardinfo->stCardData.asCardNO, st_cardinfo.stCardData.ucCardLen))
        {
            TrnSetStatus(ERR_DIFF_CARD);
            return;
        }
    }
    else
    {
        memcpy(&st_cardinfo, pst_cardinfo, sizeof(st_cardinfo));
        memset(pst_cardinfo, 0, sizeof(st_cardinfo));
        if(st_cardinfo.stCardData.ucCardLen > 0)
        {
            memcpy(pst_cardinfo->stCardData.asCardNO, st_cardinfo.stCardData.asCardNO, st_cardinfo.stCardData.ucCardLen);
            pst_cardinfo->stCardData.ucCardLen = st_cardinfo.stCardData.ucCardLen;
        }
        else
        {
            TrnGetMagCardNo(&st_cardinfo.stCardData, pst_cardinfo->stCardData.asCardNO);
            pst_cardinfo->stCardData.ucCardLen = strlen(pst_cardinfo->stCardData.asCardNO);
        }
        strcpy(pst_cardinfo->stCardData.asExpiredDate, st_cardinfo.stCardData.asExpiredDate);
        pst_cardinfo->stCardParam.ucCardMode = 0;
    }

    /* step9 : pre-dial if necessary */
    CommuPreLink();
    
    /* step10 : Input PIN */
    if (SDK_OK == ret)
    {
        if (gstAppSysCfg.stTransParam.bIsVoidNeedPIN)
        {
            memset(buf, 0, sizeof(buf));
            TrnFormatAmount(buf, pst_msginfo->asAmount, TRUE);     //Convert BCD-coded amount to display string
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_AMOUNT, SDK_DISP_LEFT_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, buf, SDK_DISP_RIGHT_DEFAULT);          //Display amount and prompt for password
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_INPUT_PIN, SDK_DISP_LEFT_DEFAULT);
            sdkDispBrushScreen();
            // Input password
            ret = TrnInputPin(TRUE, pst_msginfo->asAmount, &pst_cardinfo->stCardData, gstTransData.hePIN, SDK_DISP_LINE5);

            if (SDK_OK != ret && SDK_PED_NOPIN != ret)
            {
                return;
            }
        }
    }
                                
    /* step11 : Exchange transaction ISO8538 messages */
    ret = CommuExchangeIsoMsg(&st_tradeparam, VoidPackMsg, TRUE, TRUE, TRUE);
    if (ret <= 0)
    {
        return;
    }

    /* step12 : update original transaction record */
    st_translog.stTransStatus.bIsVoided = TRUE;
    if(SDK_OK != RecordUpdate(&st_translog))
    {
        TrnSetStatus(ERR_FILE_SYSTEM);
        return;
    }

    DispTransSucc();
    
    /* step13 : print receipt */
    PrintRecipt(FALSE);

    TrnSetStatus(TRANS_STATUS_FINISH);

    return;    
}

/*****************************************************************************
** Description :  Void transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void OnVoid(void)
{
    VoidTrans(ICCRF|MAGONLY);
    sdkPEDCancel();
    EmvLedClose();
}

