/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.

                       http://www.xinguodu.com/en/

******************************************************************************
   File Name     :
   Version        :
   Author         :  Jeff
   Date            :  2017-10-10
   Description   :



******************************************************************************/
#include "global.h"
/*----------------------------------------------------------------------------*/


s32 OpenPolicyComm(void)
{
	SDK_COMM_STUARTPARAM uartCfg;
	s32 iRet;
	
	memset(&uartCfg,0,sizeof(SDK_COMM_STUARTPARAM));
	uartCfg.ucCom = gucCommPort;
	uartCfg.uiBaudrate = 115200;
	uartCfg.ucByteLen =  '8';
	uartCfg.ucCheckBit = 'n';
	uartCfg.ucStopBitLen = '1';
	uartCfg.ucFlowControl = '0';
	ClosePolicyComm();
    iRet = sdkCommOpenUart(&uartCfg);
	Trace("xgd","open commm iRet =%d\r\n",iRet);

	return iRet;
	
}

s32 HandlePolicyMsg(void)
{ 
	u8  ucRecvBuf[512] = {0};
	s32 iLen;
	s32 iRet;
	
	iRet = RecvPolicyMsg(ucRecvBuf,&iLen);
	if(iRet != SDK_OK)
	{
		return iRet;
	}
	if(!VarifyPolicyMsg(ucRecvBuf,iLen))
	{
		return SDK_ERR;
	}
	iRet = SavePolicyMsg(ucRecvBuf,iLen); 
	if(iRet != SDK_OK)
	{
		return iRet;
	}
	if(0 == memcmp(&ucRecvBuf[1],"01",2))
	{
		Trace("xgd","entry first policy request\r\n");
		return POLICY_FIRST_REQUEST;
	}
	else if(0 == memcmp(&ucRecvBuf[1],"02",2))
	{
		iRet = RecordSearch(LOG_POLICY_NUM,gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField.asPolicyNum,
				&gstTransData.stTransLog); 
        if(SDK_OK == iRet)
        {
			PackPolicyMsg(ucRecvBuf,&iLen,POLICY_CONFIRM_REQUEST,true);
        }
		else
		{
			PackPolicyMsg(ucRecvBuf,&iLen,POLICY_CONFIRM_REQUEST,false);
		}
		iRet = SendPolicyMsg(ucRecvBuf,iLen);
		if(SDK_OK != iRet)
		{
			return iRet;
		}
		memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
		return POLICY_CONFIRM_REQUEST;
	}
	else
	{
		return SDK_ERR;
	}
	return SDK_ERR;
}

s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyRequest,bool bIsSuccess)
{
	u8  ucSendBuf[512] = {0};
	s32 iSendLen = 0;
	s32 iSendDataFieldTotalLen = 0;
	s32 iSendDataTotalLen = 0;
	u8  ucDataLen[9] = {0};
	s32 iVarifyCRC = 0;
	ST_SENT_POLICY_DATA_FIELD *stPolicyDataField = NULL;
	
	iSendDataFieldTotalLen = POLICY_COMPANY_CODE_LEN + POLICY_MID_LEN + POLICY_TID_LEN 
		 					+ POLICY_NUMBER_LEN + POLICY_AMOUNT_LEN + POLICY_RETURN_CODE_LEN
		 					+ POLICY_CARD_NO_LEN + POLICY_TRANS_DATE_LEN + POLICY_TRANS_TIME_LEN
		 					+ POLICY_TRANS_NO_LEN + POLICY_REFERENCE_NO_LEN + POLICY_ORIGINAL_DATA_FIELD_LEN
		 					+ POCLICY_ADDITIONAL_LEN;
	iSendDataTotalLen = iSendDataFieldTotalLen + 9;
	sprintf(ucDataLen,"%04d",iSendDataFieldTotalLen);

	stPolicyDataField  = &gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField;
	ucSendBuf[iSendLen] = 0x02;
	iSendLen += 1;
	
	if(POLICY_FIRST_REQUEST == ePolicyRequest)
	{
		 memcpy(ucSendBuf + iSendLen,"01",2);
	}
	else if(POLICY_CONFIRM_REQUEST == ePolicyRequest)
	{
		 memcpy(ucSendBuf + iSendLen,"02",2);
	}
	else
	{
		return SDK_ERR;
	}	
	 iSendLen += 2;
	 memcpy(ucSendBuf + iSendLen,ucDataLen,4);
	 iSendLen += 4;

	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asCompanyCode,POLICY_COMPANY_CODE_LEN);
	 iSendLen += POLICY_COMPANY_CODE_LEN;

	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asMID,POLICY_MID_LEN);
	 iSendLen += POLICY_MID_LEN;
	
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asTID,POLICY_TID_LEN);
	 iSendLen += POLICY_TID_LEN;
	
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asPolicyNum,POLICY_NUMBER_LEN);
	 iSendLen += POLICY_NUMBER_LEN;
	
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asAmount,POLICY_AMOUNT_LEN);
	 iSendLen += POLICY_AMOUNT_LEN;



	if(true == bIsSuccess)
	{
		 memcpy(ucSendBuf + iSendLen,"00",POLICY_RETURN_CODE_LEN);
	}
	else
	{
		 if(POLICY_CONFIRM_REQUEST == ePolicyRequest)
		 {
		 	 memcpy(ucSendBuf + iSendLen,"ZW",POLICY_RETURN_CODE_LEN);
		 }
		 else if(POLICY_FIRST_REQUEST == ePolicyRequest)
		 {
		 	 memcpy(ucSendBuf + iSendLen,"01",POLICY_RETURN_CODE_LEN);
		 }
	}
	iSendLen += POLICY_RETURN_CODE_LEN;
	if(true == bIsSuccess)
	{
	  		
		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stCardInfo.stCardData.asCardNO,POLICY_CARD_NO_LEN);
		 iSendLen += POLICY_CARD_NO_LEN;
	  
		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asTransDate,POLICY_TRANS_DATE_LEN);
		 iSendLen += POLICY_TRANS_DATE_LEN;
		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asTransTime,POLICY_TRANS_TIME_LEN);
		 iSendLen += POLICY_TRANS_TIME_LEN;

		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asTraceNO,POLICY_TRANS_NO_LEN);
		 iSendLen += POLICY_TRANS_NO_LEN;
		
		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asRefNO,POLICY_REFERENCE_NO_LEN);
		 iSendLen += POLICY_REFERENCE_NO_LEN;
	 }
	 else
	 {
	  	 memset(ucSendBuf + iSendLen,' ',POLICY_CARD_NO_LEN);
		 iSendLen += POLICY_CARD_NO_LEN;
		 memset(ucSendBuf + iSendLen,' ',POLICY_TRANS_DATE_LEN);
		 iSendLen += POLICY_TRANS_DATE_LEN;
		 memset(ucSendBuf + iSendLen,' ',POLICY_TRANS_TIME_LEN);
		 iSendLen += POLICY_TRANS_TIME_LEN;
 		 memset(ucSendBuf + iSendLen,' ',POLICY_TRANS_NO_LEN);
		 iSendLen += POLICY_TRANS_NO_LEN;
 		 memset(ucSendBuf + iSendLen,' ',POLICY_REFERENCE_NO_LEN);
		 iSendLen += POLICY_REFERENCE_NO_LEN;
	 }
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asOrigDataField,POLICY_ORIGINAL_DATA_FIELD_LEN);
	 iSendLen += POLICY_ORIGINAL_DATA_FIELD_LEN;
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asAddMsg,POCLICY_ADDITIONAL_LEN);
	 iSendLen += POCLICY_ADDITIONAL_LEN;
     memcpy(ucSendBuf + iSendLen,"\x03",1);
	 iSendLen += 1;
	 iVarifyCRC = CalcPolicyCRCValue(ucSendBuf,iSendLen);
	 ucSendBuf[iSendLen] = iVarifyCRC;
	 iSendLen += 1;
	 *iOutputLen = iSendDataTotalLen ;
	 memcpy(pheOutputBuf,ucSendBuf,iSendDataTotalLen);
	 return SDK_OK;
	 
}

s32 SendPolicyMsg(u8 *pheInputBuf,s32 iLen)
{
	return (sdkCommUartSendData(gucCommPort,pheInputBuf,iLen));
}

s32 SavePolicyMsg(u8 *pheInputBuf,s32 iLen)
{
	ST_SENT_POLICY_DATA_FIELD *stPolicyDataField = NULL;
	s32 iDataFieldOffsetLen = 0;
	u8 ucRecvBuf[512] = {0}; 
	
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
	memcpy(ucRecvBuf,pheInputBuf,iLen);
	stPolicyDataField  = &gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField;
	iDataFieldOffsetLen = 7;
	memcpy(stPolicyDataField->asCompanyCode,ucRecvBuf + iDataFieldOffsetLen,POLICY_COMPANY_CODE_LEN);
	Trace("xgd","company code=%s\r\n",stPolicyDataField->asCompanyCode);
	
	iDataFieldOffsetLen += POLICY_COMPANY_CODE_LEN;
	memcpy(stPolicyDataField->asMID,ucRecvBuf + iDataFieldOffsetLen,POLICY_MID_LEN);
	Trace("xgd","Mid=%s\r\n",stPolicyDataField->asMID);
	
	iDataFieldOffsetLen += POLICY_MID_LEN;
	memcpy(stPolicyDataField->asTID,ucRecvBuf + iDataFieldOffsetLen,POLICY_TID_LEN);
	Trace("xgd","TID=%s\r\n",stPolicyDataField->asTID);
	
	iDataFieldOffsetLen += POLICY_TID_LEN;
	memcpy(stPolicyDataField->asPolicyNum,ucRecvBuf + iDataFieldOffsetLen,POLICY_NUMBER_LEN);
	Trace("xgd","Policy number=%s\r\n",stPolicyDataField->asPolicyNum);

	
	iDataFieldOffsetLen += POLICY_NUMBER_LEN;
	memcpy(stPolicyDataField->asAmount,ucRecvBuf + iDataFieldOffsetLen,POLICY_AMOUNT_LEN);
	Trace("xgd","Amount=%s\r\n",stPolicyDataField->asAmount);

	iDataFieldOffsetLen += POLICY_AMOUNT_LEN;
	memcpy(stPolicyDataField->asOrigDataField,ucRecvBuf + iDataFieldOffsetLen,POLICY_ORIGINAL_DATA_FIELD_LEN);
	Trace("xgd","OrigDataField=%s\r\n",stPolicyDataField->asOrigDataField);

	iDataFieldOffsetLen += POLICY_ORIGINAL_DATA_FIELD_LEN;
	memcpy(stPolicyDataField->asAddMsg,ucRecvBuf + iDataFieldOffsetLen,POCLICY_ADDITIONAL_LEN);
	Trace("xgd","AddMsg=%s\r\n",stPolicyDataField->asAddMsg);

	strcpy(gstAppSysCfg.stTermInfo.asMerchID, stPolicyDataField->asMID);
    strcpy(gstAppSysCfg.stTermInfo.asTermID, stPolicyDataField->asTID);
	SetupSaveSetting();
	return SDK_OK;
	
}

s32 CalcPolicyCRCValue(u8 *pheInputBuf,s32 iLen)
{
	s32 i;
	s32 iVerifyCRC = 0;
	
	for(i = 0;i < iLen;i++)
	{
		iVerifyCRC ^= pheInputBuf[i];
	}
	return iVerifyCRC;
}

bool VarifyPolicyMsg(u8 *pheInputBuf,s32 iLen)
{
	s32 iCRC;
	s32 iVerifyCRC = 0;
	
	iCRC = pheInputBuf[iLen -1];
	iVerifyCRC = CalcPolicyCRCValue(pheInputBuf,iLen - 1);
	return (iCRC  == iVerifyCRC);
}

static s32 CalcStartPointOffset(u8 *pheInputBuf,s32 iBufLen,s32 startChar)
{
	s32 i;

	for(i = 0;i < iBufLen;i++)
	{
		if(pheInputBuf[i] == startChar)
		{
			return i;
		}
	}
	return -1;
}

s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen)
{
	u8 ucRecvBuf[512] = {0};
	u8 *p;
	s32 iRet;
	s32 iLen = 0;
	s32 iTrueLen = 0;
	s32 iCurTotalLen = 0;
	s32 iOffsetLen = 0;
	static s32 flag = 0;
	static SDK_QUEUE_HAND pHead = NULL;


	p = ucRecvBuf;
	iRet = sdkCommUartRecvData(gucCommPort,ucRecvBuf,300,300);
	if(iRet < 0) 
	{
		return iRet;
	}
	if(0 == flag)
	{
		pHead = sdkQueueCreate(512);
		flag = 1;
	}
	iLen = iRet;
	sdkQueueInsertData(pHead,ucRecvBuf, iRet);
	iCurTotalLen = sdkQueueGetDataLen(pHead);
	sdkQueueGetData(pHead,ucRecvBuf, iCurTotalLen);
	TraceHex("xgd","RecvCommdata:",ucRecvBuf,iCurTotalLen);
	if(iCurTotalLen < 9)
	{
		return POLICY_CONT_TO_RECV;
	}
	
   do{
		iOffsetLen  = CalcStartPointOffset(ucRecvBuf,iCurTotalLen,0x02);
		if(-1 == iOffsetLen)
		{
			return POLICY_CONT_TO_RECV;
		}
		iTrueLen = (ucRecvBuf[iOffsetLen + 3] - '0') * 1000 + (ucRecvBuf[iOffsetLen + 4] - '0') * 100
				  +(ucRecvBuf[iOffsetLen + 5] - '0') * 10 +   (ucRecvBuf[iOffsetLen + 6] - '0') + 9;
		
		if(iCurTotalLen - iOffsetLen  < iTrueLen)
		{
			return POLICY_CONT_TO_RECV;
		}
	}while( (ucRecvBuf[iTrueLen-2] != 0x03) && (iCurTotalLen - iOffsetLen  >= iTrueLen));
	*iOutputLen = iTrueLen;
	memcpy(pheOutputBuf,p+iOffsetLen,iTrueLen);
	sdkQueueEmpty(pHead);
	return SDK_OK;
}


s32 ClosePolicyComm(void)
{
	return (sdkCommCloseUart(gucCommPort));
}
	








