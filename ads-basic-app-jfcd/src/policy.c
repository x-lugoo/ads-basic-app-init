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
#include <sys/types.h>
#include <sys/fcntl.h>

/*----------------------------------------------------------------------------*/

#define FILENAME_POLICY_LOG "/mtd0/res/policy.log"

s32 OutputPolicyDebugMsg(void)
{
	s32 iFd;

	iFd = open(FILENAME_POLICY_LOG,O_RDWR | O_CREAT,0644);
	if(iFd < 0)
	{
		printf("open file %s error\n",FILENAME_POLICY_LOG);
		return SDK_ERR;
	}
	dup2(iFd,1);//redirect iFd file describe symble  to stdout
	close(iFd);
	printf("start to collect debug log\n");
	return SDK_OK;
}

s32 OpenPolicyComm(void)
{
	SDK_COMM_STUARTPARAM uartCfg;
	s32 iRet;

	memset(&uartCfg,0,sizeof(SDK_COMM_STUARTPARAM));
	uartCfg.ucCom = SDK_COMM_UART_PINPAD;
	uartCfg.uiBaudrate = 115200;
	uartCfg.ucByteLen =  '8';
	uartCfg.ucCheckBit = 'n';
	uartCfg.ucStopBitLen = '1';
	uartCfg.ucFlowControl = '0';
	iRet = ClosePolicyComm();
	printf("close commm iRet =%d, struction size =%d\n",iRet,sizeof(SDK_COMM_STUARTPARAM));

    iRet = sdkCommOpenUart(&uartCfg);
	printf("open commm iRet =%d\n",iRet);
	return iRet;
	
}

s32 HandlePolicyMsg(void)
{
	u8 ucRecvBuf[512];
	s32 iLen;
	s32 iRet;
	int i = 0;
	u8  ucDebugBuf[2048];
	
	iRet = RecvPolicyMsg(ucRecvBuf,&iLen);
	if(iRet != SDK_OK)
	{
		return iRet;
	}
	if(!VarifyPolicyMsg(ucRecvBuf,iLen))
	{
		return SDK_ERR;
	}
	if(0 == memcmp(&ucRecvBuf[1],"01",2))
	{
		SavePolicyMsg(ucRecvBuf,iLen);

		PackPolicyMsg(ucRecvBuf,&iLen,POLICY_FIRST_REQUEST);
		for(;i < iLen;i++)
		{
			snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
		}
			printf("%s(%d)\n iLen=%d,SendBuf=%s\n",__FUNCTION__,__LINE__,iLen,ucDebugBuf);	
			iRet = SendPolicyMsg(ucRecvBuf, iLen);
			printf("send iRet = %d %s(%d)\n",iRet,__FUNCTION__,__LINE__);
		}
	else if(0 == memcmp(&ucRecvBuf[1],"02",2))
	{
		//return SDK_ERR;//tmp operate
		SavePolicyMsg(ucRecvBuf,iLen);

		PackPolicyMsg(ucRecvBuf,&iLen,POLICY_CONFIRM_REQUEST);
		for(;i < iLen;i++)
		{
			snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
		}
			printf("%s(%d)\n iLen=%d,SendBuf=%s\n",__FUNCTION__,__LINE__,iLen,ucDebugBuf);	
			iRet = SendPolicyMsg(ucRecvBuf, iLen);
			printf("send iRet = %d %s(%d)\n",iRet,__FUNCTION__,__LINE__);


		
	}
	else
	{
		return SDK_ERR;
	}
	
	return SDK_OK;
}

s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyRequest)
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

	 memcpy(stPolicyDataField->asRetCode,"00",POLICY_RETURN_CODE_LEN);//for test
	 
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asRetCode,POLICY_RETURN_CODE_LEN);
		 iSendLen += POLICY_RETURN_CODE_LEN;

	 memcpy(stPolicyDataField->asCardNo,"5555555577777777   ",POLICY_CARD_NO_LEN);//for test
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asCardNo,POLICY_CARD_NO_LEN);
		 iSendLen += POLICY_CARD_NO_LEN;

  	 memcpy(stPolicyDataField->asTransDate,"20171012",POLICY_TRANS_DATE_LEN);//for test
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asTransDate,POLICY_TRANS_DATE_LEN);
		 iSendLen += POLICY_TRANS_DATE_LEN;

	 memcpy(stPolicyDataField->asTransTime,"163212",POLICY_TRANS_TIME_LEN);//for test
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asTransTime,POLICY_TRANS_TIME_LEN);
		 iSendLen += POLICY_TRANS_TIME_LEN;

	 memcpy(stPolicyDataField->asTransNo,"000012",POLICY_TRANS_NO_LEN);//for test
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asTransNo,POLICY_TRANS_NO_LEN);
		 iSendLen += POLICY_TRANS_NO_LEN;

	 memcpy(stPolicyDataField->asRefNo,"000045888898",POLICY_REFERENCE_NO_LEN);//for test
	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asRefNo,POLICY_REFERENCE_NO_LEN);
		 iSendLen += POLICY_REFERENCE_NO_LEN;

	 
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
	
	return (sdkCommUartSendData(SDK_COMM_UART_PINPAD,pheInputBuf,iLen));
}

s32 SavePolicyMsg(u8 *pheInputBuf,s32 iLen)
{
	ST_SENT_POLICY_DATA_FIELD *stPolicyDataField = NULL;
	s32 iDataFieldOffsetLen = 0;
	u8 ucRecvBuf[512] = {0};
	
	memcpy(ucRecvBuf,pheInputBuf,iLen);
	stPolicyDataField  = &gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField;
	iDataFieldOffsetLen = 7;
	memcpy(stPolicyDataField->asCompanyCode,ucRecvBuf + iDataFieldOffsetLen,POLICY_COMPANY_CODE_LEN);
	printf("company code=%s\n",stPolicyDataField->asCompanyCode);
	
	iDataFieldOffsetLen += POLICY_COMPANY_CODE_LEN;
	memcpy(stPolicyDataField->asMID,ucRecvBuf + iDataFieldOffsetLen,POLICY_MID_LEN);
	printf("Mid=%s\n",stPolicyDataField->asMID);
	
	iDataFieldOffsetLen += POLICY_MID_LEN;
	memcpy(stPolicyDataField->asTID,ucRecvBuf + iDataFieldOffsetLen,POLICY_TID_LEN);
	printf("TID=%s\n",stPolicyDataField->asTID);
	
	iDataFieldOffsetLen += POLICY_TID_LEN;
	memcpy(stPolicyDataField->asPolicyNum,ucRecvBuf + iDataFieldOffsetLen,POLICY_NUMBER_LEN);
	printf("Policy number=%s\n",stPolicyDataField->asPolicyNum);

	
	iDataFieldOffsetLen += POLICY_NUMBER_LEN;
	memcpy(stPolicyDataField->asAmount,ucRecvBuf + iDataFieldOffsetLen,POLICY_AMOUNT_LEN);
	printf("Amount=%s\n",stPolicyDataField->asAmount);

	
	iDataFieldOffsetLen += POLICY_AMOUNT_LEN;
	memcpy(stPolicyDataField->asOrigDataField,ucRecvBuf + iDataFieldOffsetLen,POLICY_ORIGINAL_DATA_FIELD_LEN);
	printf("OrigDataField=%s\n",stPolicyDataField->asOrigDataField);

	
	iDataFieldOffsetLen += POLICY_ORIGINAL_DATA_FIELD_LEN;
	memcpy(stPolicyDataField->asAddMsg,ucRecvBuf + iDataFieldOffsetLen,POCLICY_ADDITIONAL_LEN);
	printf("AddMsg=%s\n",stPolicyDataField->asAddMsg);

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

s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen)
{
	u8 ucRecvBuf[512] = {0};
	u8  ucDebugBuf[2048];
	s32 iRet;
	s32 iLen = 0;
	s32 iTrueLen = 0;
	s32 i = 0;
	s32 iFirstPos = 0;
	s32 iSecondPos = 0;
	u32 uiRecvTimer = sdkTimerGetId();
	SDK_QUEUE_HAND pHead = NULL;


	iRet = sdkCommUartRecvData(SDK_COMM_UART_PINPAD,ucRecvBuf,300,200);
	if(iRet < 0) 
	{
		return iRet;
	}
	if(0x02 != ucRecvBuf[0])
	{
		return SDK_ERR;
	}
	pHead = sdkQueueCreate(512);
	sdkQueueInsertData(pHead,ucRecvBuf, iRet);
	printf("RecvLen=%d,queueLen=%d,%s(%d)\n",iRet,sdkQueueGetDataLen(pHead),__FUNCTION__,__LINE__);
	while(1)
	{
		iRet = sdkCommUartRecvData(SDK_COMM_UART_PINPAD,ucRecvBuf,300,1000 *120);
		if(iRet < 0) 
		{
			sdkQueueRelease(pHead);
			return iRet;
		}
		iLen = iRet;
		sdkQueueInsertData(pHead,ucRecvBuf, iLen);
		iFirstPos = sdkQueueGetPosValue(pHead, 0);
		iSecondPos = sdkQueueGetPosValue(pHead, 1);
		//printf("pos0:0X%02X,pos1:0X%02X %s(%d)\n",iFirstPos,iSecondPos,__FUNCTION__,__LINE__);
		
		//printf("RecvLen=%d,queueLen=%d,%s(%d)\n",iLen,sdkQueueGetDataLen(pHead),__FUNCTION__,__LINE__);
		
		if(sdkQueueGetDataLen(pHead) < 7)
		{
			continue;
		}
		//printf("pos3=%02X,pos4=%02X,pos5=%02X,pos6=%02X %s(%d)\n",
		//	sdkQueueGetPosValue(pHead, 3),sdkQueueGetPosValue(pHead, 4),sdkQueueGetPosValue(pHead, 5),
		//	sdkQueueGetPosValue(pHead, 6),__FUNCTION__,__LINE__);

		iTrueLen = (sdkQueueGetPosValue(pHead, 3)- '0') * 1000 + (sdkQueueGetPosValue(pHead, 4) - '0') * 100
					+ (sdkQueueGetPosValue(pHead, 5)- '0') * 10 + (sdkQueueGetPosValue(pHead, 6) - '0') + 9;
		//printf("TrueLen=%d,%s(%d)\n",iTrueLen,__FUNCTION__,__LINE__);
		if(sdkQueueGetDataLen(pHead) < iTrueLen)
		{
			continue;
		}
		else if(sdkQueueGetDataLen(pHead) == iTrueLen)
		{
			break;
		}
		else
		{
			sdkQueueRelease(pHead);
			return SDK_ERR;
		}
		if(sdkTimerIsEnd(uiRecvTimer, 120 * 1000))
        {
			sdkQueueRelease(pHead);
            return SDK_ERR;
        }
	}//while(1)
	sdkQueueGetData(pHead,ucRecvBuf, iTrueLen);
	sdkQueueRelease(pHead);
	*iOutputLen = iTrueLen;
	memcpy(pheOutputBuf,ucRecvBuf,iTrueLen);
	//for(;i < iTrueLen;i++)
	//{
	//	snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
	//}
	//printf("%s(%d)\n iLen=%d,RecvBuf=%s\n",__FUNCTION__,__LINE__,iTrueLen,ucDebugBuf);
	
	return SDK_OK;
}



s32 ClosePolicyComm(void)
{
	return (sdkCommCloseUart(SDK_COMM_UART_PINPAD));
}
	








