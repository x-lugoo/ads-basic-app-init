/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.
                
                       http://www.nexgo.cn/en/

 ******************************************************************************
  File Name     :   
  Version       :  
  Author        :  jeff
  Date          :  2017-10-31
  Description   : 


  
******************************************************************************/
#include "global.h"

/*----------------------------------------------------------------------------*/




s32 SaveVoiceSecureMsg(ST_SAVED_VOICE_SECURE_MSG *pstVoiceSecureMsg)
{
	s32 iRet;
	
	iRet = sdkWriteFile(FILENAME_SAVED_VOICE_SECURE_MEG,(u8 *)pstVoiceSecureMsg,sizeof(ST_SAVED_VOICE_SECURE_MSG));
	Trace("xgd","Write File,iRet=%d\r\n",iRet);
	return iRet;

}



s32 ReadVoiceSecureMsg(ST_SAVED_VOICE_SECURE_MSG *pstVoiceSecureMsg)
{
	s32 iRet;
	s32 iLen;

	iLen = sizeof(ST_SAVED_VOICE_SECURE_MSG);
	iRet = sdkReadFile(FILENAME_SAVED_VOICE_SECURE_MEG,(u8 *)pstVoiceSecureMsg, 0,&iLen);
	Trace("xgd","ReadFile,iRet=%d,iLen=%d\r\n",iRet,iLen);
	return iRet;
		
}


s32 VoiceHandleField48(SDK_8583_ST8583 *pstIsoMsg,E_TRANS_ID eTransId)
{
	u8 buf[100];
	u8 *pucBuf;
	s32 iLen = 0;
	ST_CARDINFO *pst_cardinfo = NULL;
	ST_VOICE_MSG *pst_voiceinfo = NULL;

	pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
	pst_voiceinfo = &gstTransData.stTransLog.stVoiceMsg;
	pucBuf = buf;
	switch(eTransId)
	{
		case TRANSID_VOICE_ADD_FUNC:
			/*Identification*/
			memcpy(pucBuf,"EC",2);
			pucBuf += 2;
			/*The type of the account*/
			memcpy(pucBuf,"01",2);
			pucBuf += 2;
			/*account number*/
			memcpy(pucBuf,pst_voiceinfo->asInvoiceNum,20);
			pucBuf += 20;
			/*The six numbers at the end of the bank card number*/
			memcpy(pucBuf,pst_cardinfo->stCardData.asCardNO + strlen(pst_cardinfo->stCardData.asCardNO) - 6,6);
			pucBuf += 6;
			/*payment method*/
			memcpy(pucBuf,"01",2);
			pucBuf += 2;
			/*the number of the payment */
			memcpy(pucBuf,pst_voiceinfo->asPayMethodNum,20);
			pucBuf += 20;
			/*password*/
			memcpy(pucBuf,"000000",6);
			pucBuf += 6;
			break;
		case TRANSID_VOICE_READD_ONE_FUNC:
			/*Identification*/
			memcpy(pucBuf,"EC",2);
			pucBuf += 2;
			/*The six numbers at the end of the bank card number*/
			memcpy(pucBuf,pst_cardinfo->stCardData.asCardNO + strlen(pst_cardinfo->stCardData.asCardNO) - 6,6);
			pucBuf += 6;
			/*PIN*/
			if(gstTransData.hePIN[0] > 0)
			{
				memcpy(pucBuf,&gstTransData.hePIN[1],8);
			}
			else
			{
				memset(pucBuf,0xFF,8);
			}
			TraceHex("xgd","the result PIN=",&gstTransData.hePIN[0],8);
			pucBuf += 8;
			/*payment method*/
			memcpy(pucBuf,"01",2);
			pucBuf += 2;
			/*the number of the payment */
			memcpy(pucBuf,pst_voiceinfo->asPayMethodNum,20);
			TraceHex("xgd","the result paymethodNo=",pucBuf,22);
			pucBuf += 20;
			break;
		case TRANSID_VOICE_CANCEL_ONE_FUNC:
			break;
		case TRANSID_VOICE_CANCEL_ALL_FUNC:
			break;
		default:
			break;
			
	}
	memcpy(pucBuf,"#",1);/*Ending Identification*/
	pucBuf += 1;
	iLen = pucBuf - buf;
	IsoSetField(pstIsoMsg,48,buf,iLen);
	return SDK_OK;
}

s32 VoiceReAddFuncPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    /*Field 3,11,25,41,42,48,64  */
    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "2020008000C10001");

    if (ret <= 0)
    {
        return 0;
    }
    
    /* Field 0  Message Type Identifier (MTI) */
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0100", 4);
    if (ret <= 0)
    {
        return 0;
    }
    /*Field 3 */
    IsoSetField(pstIsoMsg, 3, "930001", 6);

	/*Field 25*/
    IsoSetField(pstIsoMsg, 25, "87", 2); 

	/*Field 48*/
	VoiceHandleField48(pstIsoMsg,TRANSID_VOICE_READD_ONE_FUNC);
    return pstIsoMsg->nBagLen;
}

s32 VoiceAddFuncPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
	s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    /*Field 3,11,25,41,42,48,64  */
    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "2020008000C10001");

    if (ret <= 0)
    {
        return 0;
    }
    
    /* Field 0  Message Type Identifier (MTI) */
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0100", 4);
    if (ret <= 0)
    {
        return 0;
    }
    /*Field 3 */
    IsoSetField(pstIsoMsg, 3, "930002", 6);

	/*Field 25*/
    IsoSetField(pstIsoMsg, 25, "87", 2); 

	/*Field 48*/
	VoiceHandleField48(pstIsoMsg,TRANSID_VOICE_ADD_FUNC);
    return pstIsoMsg->nBagLen;
}


s32 VoiceCancelOneFuncPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    
    return pstIsoMsg->nBagLen;
}


void VoiceTrans(u16 usCardType,E_TRANS_ID eTranID)
{
    SDK_ICC_TRADE_PARAM st_tradeparam;
    ST_CARDINFO *pst_cardinfo = NULL;
    ST_MSGINFO *pst_msginfo = NULL;
	ST_VOICE_MSG *pst_voiceinfo = NULL;
    s32 ret;
    u8 buf[21];

    /* step1 : initializes the transaction data */
    if(0 == strlen(gstTransData.stTransLog.stMsgInfo.asAmount))
    {
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    }
    memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
	pst_voiceinfo = &gstTransData.stTransLog.stVoiceMsg;
    pst_msginfo->ucCashierNO = gstLoginInfo.ucUserNO;
    gstTransData.stTransLog.eTransID = eTranID;
	s32 (*pPackFun)(SDK_8583_ST8583 *) = NULL;

    /* step2 : Display title */
	switch(eTranID)
	{
		case TRANSID_VOICE_READD_ONE_FUNC:
			pPackFun = VoiceReAddFuncPackMsg;
			strcpy(buf,STR_TRANS_READD_FUNC);
			break;
		case TRANSID_VOICE_ADD_FUNC:
			pPackFun = VoiceAddFuncPackMsg;
			strcpy(buf,STR_TRANS_ADD_FUNC);
			break;
		case TRANSID_VOICE_CANCEL_ONE_FUNC:
			break;
		case TRANSID_VOICE_CANCEL_ALL_FUNC:
			break;
		default:
			break;
	}
    DispTitle(buf);
    /* step3 : input payment method number */
	switch(eTranID)
	{
		case TRANSID_VOICE_READD_ONE_FUNC:
		if(FALSE == TrnInputVoiceCommonNo(pst_voiceinfo->asPayMethodNum,VOICE_INPUT_PAYMENT_NO))
   		{
			return;
   		}
		break;
		case TRANSID_VOICE_ADD_FUNC:
		if(FALSE == TrnInputVoiceCommonNo(pst_voiceinfo->asInvoiceNum,VOICE_INPUT_PAYMENT_NO))
   		{
			return;
   		}
		if(FALSE == TrnInputVoiceCommonNo(pst_voiceinfo->asPayMethodNum,VOICE_INPUT_INVOICE_NO))
   		{
			return;
   		}
		break;
		case TRANSID_VOICE_CANCEL_ONE_FUNC:
			break;
		case TRANSID_VOICE_CANCEL_ALL_FUNC:
			break;
		default:
			break;
	}
    
	memset(buf,0,sizeof(buf));
    memcpy(buf,pst_voiceinfo->asPayMethodNum,20);
    /* step4 : Process card */
    while(1)
    {
        ret = TrnReadCard(usCardType, &st_tradeparam, pst_cardinfo);
        Trace("voice ReAdd func", "TrnReadCard=[%d]\r\n", ret);

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
            gstTransData.stTransLog.eTransID = eTranID;
			memcpy(pst_voiceinfo->asPayMethodNum,buf,20);
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
    /* step5 : pre-dial if necessary */
    CommuPreLink();

    /* step6: Input PIN */
    if (SDK_OK == ret)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PAYMENT_NO, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, buf, SDK_DISP_RIGHT_DEFAULT);          //Display paymentNo and prompt for password
        sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_INPUT_PIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();
        ret = TrnInputPin(false, pst_msginfo->asAmount, &pst_cardinfo->stCardData, gstTransData.hePIN, SDK_DISP_LINE5);  // Input password

        if (SDK_OK != ret && SDK_PED_NOPIN != ret)
        {
            return;
        }
    }
    /* step7 : Exchange transaction ISO8538 messages */
    ret = CommuExchangeIsoMsg(&st_tradeparam, pPackFun, TRUE, TRUE, TRUE);
    if (ret <= 0)
    {
        return;
    }

    DispTransSucc();
    
    /* step8 : print receipt */
    PrintRecipt(FALSE);

    TrnSetStatus(TRANS_STATUS_FINISH);
    
    return;
}


void VoiceReAddFunc(void)
{
    VoiceTrans(ICCRF|MAGONLY,TRANSID_VOICE_READD_ONE_FUNC);
    sdkPEDCancel();
    EmvLedClose();
}

void VoiceAddFunc(void)
{
    VoiceTrans(ICCRF|MAGONLY,TRANSID_VOICE_ADD_FUNC);
    sdkPEDCancel();
    EmvLedClose();
}

