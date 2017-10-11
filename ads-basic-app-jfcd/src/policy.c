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

	memset(&uartCfg,0,sizeof(SDK_COMM_STUARTPARAM));
	uartCfg.ucCom = SDK_COMM_UART_PINPAD;
	uartCfg.uiBaudrate = 115200;
	uartCfg.ucByteLen =  8;
	uartCfg.ucCheckBit = 'n';
	uartCfg.ucStopBitLen = 1;
	uartCfg.ucFlowControl = 0;
	return (sdkCommOpenUart(&uartCfg));
}

s32 RecvPolicyMsg(void)
{
	u8 ucRecvBuf[512] = {0};
	s32 iOffset = 0;
	s32 iRet;
	s32 iDataFieldOffsetLen = 0;
	s32 iLen = 0;
	s32 iTotalLen = 0;
	s32 iTrueLen = 0;
	u8  ucDebugBuf[2048];
	s32 i = 0;
	ST_SENT_POLICY_DATA_FIELD *stPolicyDataField = NULL;
	u32 uiRecvTimer = sdkTimerGetId();
	
	while(1)
	{
		if(sdkTimerIsEnd(uiRecvTimer, 120 * 1000))
        {
            return SDK_ERR;
        }
		iRet = sdkCommUartRecvData(SDK_COMM_UART_PINPAD,ucRecvBuf + iOffset,512,120 * 1000);
		if(iRet < 0) 
		{
			printf("iRet=%d,%s(%d)\n",iRet,__FUNCTION__,__LINE__);
			return iRet;
		}
		iLen = iRet;
		if(0x02 != ucRecvBuf[0])
		{
			return SDK_ERR;
		}
		printf("RecvLen=%d,%s(%d)\n",iLen,__FUNCTION__,__LINE__);
		iOffset += iLen;
		iTotalLen += iLen;
		if(iTotalLen < 7)
		{
			continue;
		}
		iTrueLen = (ucRecvBuf[3]- '0') * 1000 + (ucRecvBuf[4] - '0') * 100 + (ucRecvBuf[5]- '0') * 10 + (ucRecvBuf[6] - '0') + 9;
		printf("TrueLen=%d,%s(%d)\n",iTrueLen,__FUNCTION__,__LINE__);
		if(iTotalLen < iTrueLen)
		{
			continue;
		}
		else if(iTotalLen == iTrueLen)
		{
			break;
		}
		else
		{
			return SDK_ERR;
		}
		
	}//while(1)
	for(;i < iTotalLen;i++)
	{
		snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
	}
	printf("%s(%d)\n iLen=%d,RecvBuf=%s\n",__FUNCTION__,__LINE__,iLen,ucDebugBuf);
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



s32 ClosePolicyComm(void)
{
	return (sdkCommCloseUart(SDK_COMM_UART_PINPAD));
}
	







