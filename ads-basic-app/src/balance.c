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
** Description :  Display balance amount after query transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispBalanceAmount(void)
{
    u8 disp[256] = {0};
    u8 amount[8] = {0};
    SDK_PED_SYMBOL e_symbol;
    ST_TRANSLOG *pst_translog = &gstTransData.stTransLog;
    
    Trace("balance", "DispBalanceAmount balance = %s \r\n", pst_translog->stMsgInfo.asBalance);
    if (strlen(pst_translog->stMsgInfo.asBalance) > 0)
    {
        if (gstAppSysCfg.stSysParam.bIsExtPED)
        {
            if ('C' == pst_translog->stMsgInfo.asBalance[0])
            {
                e_symbol = SDK_PED_POSITIVE;
            }
            else
            {
                e_symbol = SDK_PED_NEGATIVE;
            }
            sdkAscToBcdR(&amount[0], &pst_translog->stMsgInfo.asBalance[1], 6);
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INQUIRE_SUCC, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CHECK_PINPAD, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkPEDDispBalance(e_symbol, amount);
        }
        else
        {
            if ('C' != pst_translog->stMsgInfo.asBalance[0])
            {
                strcpy(disp, "-");
                TrnFormatAmount(&disp[1], &pst_translog->stMsgInfo.asBalance[1], FALSE);
            }
            else
            {
                TrnFormatAmount(disp, &pst_translog->stMsgInfo.asBalance[1], FALSE);
            }
            
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INQUIRE_SUCC, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_BALANCE, SDK_DISP_LEFT_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, disp, SDK_DISP_RIGHT_DEFAULT);
            sdkDispBrushScreen();
        }
        sdkSysBeep(SDK_SYS_BEEP_OK);
        sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
        sdkPEDCancel();
    }
}

/*****************************************************************************
** Description :  Pack the ISO8583 message of query balance transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BalancePackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 ret;
    u8 buf[128] = {0};
    ST_MSGINFO *pst_msginfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "602406C030C09A11");

    if (ret <= 0)
    {
        return 0;
    }
    
    // #0  Message Type Identifier (MTI)
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0200", 4);

    // #2
    IsoSetField(pstIsoMsg, 3, "310000", 6);

    // #25
    IsoSetField(pstIsoMsg, 25, "00", 2); 
    
    // #60.1  transaction type code
    memset(buf, 0, sizeof(buf));
    strcat(buf, "01");
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
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));
    
    return pstIsoMsg->nBagLen;
}


s32 EchoBalancePackMsg(SDK_8583_ST8583 *pstIsoMsgSend, SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 iRet;
	u8 	mac[16] = {0};
	u8  ucField39[2];
	u8  ucField54[30] = {0};
	
	IsoSetField(pstIsoMsgRecv,SDK_8583_FIELD_MSG,"0210",4);  //Field 0,message code
	EchoIsoPackPublicMsg(pstIsoMsgSend,pstIsoMsgRecv);

	IsoSetField(pstIsoMsgRecv,25,"00",2);  //Field 25,condition code
	IsoSetField(pstIsoMsgRecv,37,"123456789012",12);  //Field 37,reference num
	IsoSetField(pstIsoMsgRecv,38,"123456",6);  //Field 38,auth code
	
	iRet = DbgEchoHandleField39AndField54(TRANSID_BALANCE,pstIsoMsgSend,ucField39,ucField54);
	if(iRet < 0){
		return iRet;
	}
	IsoSetField(pstIsoMsgRecv,39,ucField39,2);  //Field 39,response code
	IsoSetField(pstIsoMsgRecv,44,"0102000001030000",strlen("0102000001030000"));  //Field 39,response code
	IsoSetField(pstIsoMsgRecv,49,"156",3);  //currency code
	IsoSetField(pstIsoMsgRecv,54,ucField54,strlen(ucField54));  //field54 balance
	
	TraceHex("xgd","balance field54",ucField54,strlen(ucField54));
	IsoSetField(pstIsoMsgRecv,60,"22000001000600",strlen("22000001000600"));  
	IsoSetField(pstIsoMsgRecv,63,"cup",3);
	IsoSetField(pstIsoMsgRecv,64,"\x00\x00\x00\x00\x00\x00\x00\x00", 8);//calc ,need to copy mac before calc truely mac
	memset(mac,0,sizeof(mac)); //get mac
	iRet = IsoGetMsgMac(pstIsoMsgRecv, mac);
	if (iRet <= 0)
    {
        return SDK_ESC;
    }
	TraceHex("xgd","generate Mac2",mac,8);
	iRet = IsoSetField(pstIsoMsgRecv, 64, mac, 8);
    if (iRet <= 0)
    {
        return SDK_ESC;
    }
	return 0;
#endif
}


/*****************************************************************************
** Description :  Query balance transaction process
** Parameters  :  input
                  (1)u16 usCardType: all support card type in this transaction
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void BalanceTrans(u16 usCardType)
{
    s32 ret;
    SDK_ICC_TRADE_PARAM st_tradeparam;
    ST_CARDINFO *pst_cardinfo = &gstTransData.stTransLog.stCardInfo;

    /* step1 : initializes the transaction data */
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    gstTransData.stTransLog.eTransID = TRANSID_BALANCE;
    
    /* step2 : Display title */
    DispTitle(STR_TRANS_BALANCE);
    
    /* step3 : check transaction conditions */
    if(!TrnCheckCondition(FALSE, TRUE))
    {
        return;
    }
    
    /* step4 : Process card */
    ret = TrnReadCard(usCardType, &st_tradeparam, pst_cardinfo);
    if (ret < 0)
    {
        if(0 == TrnGetStatus())
        {
            TrnSetStatus(ERR_READ_CARD);
        }
        return;
    }
    
    /* step5 : pre-dial if necessary */
    CommuPreLink();

    /* step6 : Input PIN */
    if(SDK_OK == ret)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_PIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();
        // Input password
        ret = TrnInputPin(TRUE, NULL, &pst_cardinfo->stCardData, gstTransData.hePIN, SDK_DISP_LINE5);

        if (SDK_OK != ret && SDK_PED_NOPIN != ret)
        {
            return;
        }
    }

    /* step7 : Exchange transaction ISO8538 messages */
    ret = CommuExchangeIsoMsg(&st_tradeparam, BalancePackMsg, FALSE, TRUE, FALSE);
    if (ret <= 0)
    {
        return;
    }
    
    DispTransSucc();

    /* step8 : display balance */
    DispBalanceAmount();
    
    TrnSetStatus(TRANS_STATUS_FINISH);
}

/*****************************************************************************
** Description :  Query balance transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void OnBalance(void)
{
    BalanceTrans(MAGICC);
}


