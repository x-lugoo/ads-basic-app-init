/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.

                       http://www.xinguodu.com/en/

******************************************************************************
   File Name     :
   Version       :
   Author        :  Steven
   Date          :  2016-11-09
   Description   :



******************************************************************************/
#include "global.h"
#include <sys/types.h>
#include <sys/fcntl.h>
/*----------------------------------------------------------------------------*/

/*****************************************************************************
** Descriptions:	Judge whether the data is an ASCII string
** Parameters:          const u8 *pData
                        u32 uiDataLen
** Returned value:
** Created By:		Steven 2016-11-09
** Remarks:
*****************************************************************************/
bool DbgIsAscStr(const u8 *pData, u32 uiDataLen)
{
    u32 i;

    for (i = 0; i < uiDataLen; i++)
    {
        if (pData[i] < 0x20 || pData[i] > 0x7F)
        {
            return false;
        }
    }

    return true;
}

/*****************************************************************************
** Descriptions:	Convert the hex data into ASCII format can print the converted string out.
** Parameters:          const u8 *pData
                        u32 uiDataLen
** Returned value:
** Created By:		Steven 2016-11-09
** Remarks:
*****************************************************************************/
void DbgTraceAsc(const u8 *pheData, u32 uiDataLen)
{
    s32 i;
    u8 temp[1024] = {0};

    memcpy(temp, pheData, uiDataLen);

    for (i = 0; i < uiDataLen; i++)
    {
        if (temp[i] < 0x20 || temp[i] > 0x7F)
        {
            temp[i] = '.';
        }
    }

    temp[i] = '\0';
}

/*****************************************************************************
** Descriptions:	Print the parsed ISO8583 fields as specified format.
** Parameters:      const u8 *pData
                    u32 uiDataLen
** Returned value:
** Created By:		Steven 2016-11-09
** Remarks:
*****************************************************************************/
void DbgTraceIso8583(u8 *pasTitle, SDK_8583_ST8583 *pstBag8583)
{
#ifndef XGD_SDK_DEBUG
    return;

#else
    u32 i;
    u8 buf[512];
    u8 buf1[1024];
    s32 siLen = 0;

    for (i = 0; i <= 64; i++)
    {
        if (sdk8583IsDomainExist(pstBag8583, i))
        {
            memset(buf, 0, sizeof(buf));
            siLen = 0;

            siLen = IsoGetField(pstBag8583, i, buf, sizeof(buf));

            if (siLen > 0)
            {
                if (DbgIsAscStr(buf, siLen))
                {
                    Trace(pasTitle, "[%03u][%03d][%s]\r\n", i, siLen, buf);
                }
                else
                {
                    memset(buf1, 0, sizeof(buf1));  //HEX will be marked with "*"
                    sdkBcdToAsc(buf1, buf, siLen);
                    Trace(pasTitle, "[%03u][%03d][%s]*\r\n", i, siLen, buf1);
                }
            }
        }
    }

#endif
}

void *DbgPrintIso8583(u8 *pasTitle,void *arg)
{
#ifndef JEFF_DEBUG
	return (void*)0;
#else
 	u32 i;
    u8 buf[512];
    u8 buf1[1024];
    s32 siLen = 0;
	SDK_8583_ST8583 *pstBag8583;
	SDK_PRINT_FONT st_font;

	pstBag8583 = arg;
	//init printer
	sdkPrintInit();
    PrintSetFont(&st_font, PRINT_FONT_HALF);
    sdkPrintStr(pasTitle, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
    for (i = 0; i <= 64; i++)
    {
        if (sdk8583IsDomainExist(pstBag8583, i))
        {
            memset(buf, 0, sizeof(buf));
            siLen = 0;

            siLen = IsoGetField(pstBag8583, i, buf, sizeof(buf));

            if (siLen > 0)
            {
                if (DbgIsAscStr(buf, siLen))
                {
                	snprintf(buf1,1024,"[%03u][%03d][%s]\r\n", i, siLen, buf);
					sdkPrintStr(buf1, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
                }
                else
                {
                    memset(buf1, 0, sizeof(buf1));  //HEX will be marked with "*"
                    sdkBcdToAsc(buf1, buf, siLen);
					sdkPrintStr(buf1, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
                }
            }
        }
    }
	sdkPrintStart();
	return (void*)0;
#endif	
}

bool DbgPrintHex8583(u8 *pasTitle,const u8 *pheData, s32 uiDataLen)
{
#ifndef JEFF_DEBUG
	return true;
#else
	u8 buf[2028+1];
	SDK_PRINT_FONT st_font;
	if(uiDataLen > 1024 || uiDataLen < 0){
		return false;
	}
	//init printer
	sdkPrintInit();
    PrintSetFont(&st_font, PRINT_FONT_HALF);
	sdkPrintStr(pasTitle, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
	memset(buf,0,sizeof(buf));
	sdkBcdToAsc(buf,pheData, uiDataLen);
	sdkPrintStr(buf, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
	sdkPrintStart();
	return true;
#endif
}

s32 DbgSaveTran8583(s32 siTranNO,SDK_8583_ST8583 *pstSentBag8583,SDK_8583_ST8583 *pstRecv8583,s32 siOffset)
{
#ifndef JEFF_DEBUG
	return 0;
#else	
	s32 siFd;
	s32 siRet;
	ST_SAVED_DEBUG8583 stSavedDebug8583;
	

	siFd = open(FILENAME_SAVED_8583_PKG,O_CREAT | O_RDWR,0644);
	if(siFd < 0){
		return -1;
	}
	lseek(siFd,sizeof(ST_SAVED_DEBUG8583) * siOffset,SEEK_SET);
	stSavedDebug8583.sTranNo = siTranNO;
	stSavedDebug8583.stSendBag8583 = *pstSentBag8583;
	stSavedDebug8583.stRecvBag8583 = *pstRecv8583;
	siRet = write(siFd,&stSavedDebug8583,sizeof(stSavedDebug8583));
	if(siRet != sizeof(stSavedDebug8583)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return 0;
#endif
}

s32 DbgReadTran8583(ST_SAVED_DEBUG8583 *pstSavedDebug8583,s32 siOffset)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 siFd;
	s32 siRet;

	siFd = open(FILENAME_SAVED_8583_PKG,O_RDONLY,0);
	if(siFd < 0){
		return -1;
	}
	lseek(siFd,sizeof(ST_SAVED_DEBUG8583) * siOffset,SEEK_SET);
	siRet = read(siFd,pstSavedDebug8583,sizeof(ST_SAVED_DEBUG8583));
	if(siRet != sizeof(ST_SAVED_DEBUG8583)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return siRet;
#endif	
}

s32 DbgSaveDbgTranTotalNum(s32 siSaveDebugNum)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 siFd;
	s32 siRet;

	siFd = open(FILENAME_TATAL_SAVED_8383_NUM,O_CREAT | O_RDWR,0644);
	if(siFd < 0){
		return -1;
	}
	siRet = write(siFd,&siSaveDebugNum,sizeof(s32));
	if(siRet != sizeof(s32)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return 0;
#endif	
}

s32 DbgReadDbgTranTotalNum(s32 *siSavedDebugNum)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 siFd;
	s32 siRet;

	siFd = open(FILENAME_TATAL_SAVED_8383_NUM,O_RDONLY,0);
	if(siFd < 0){
		return -1;
	}
	siRet = read(siFd,siSavedDebugNum,sizeof(s32));
	if(siRet != sizeof(s32)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return siRet;
#endif
}

s32 DbgSaveEchoMsg(ST_SAVE_ECHO_MSG *pstEchoMsg)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 siFd;
	s32 siRet;
	
	siFd = open(FILENAME_SAVED_ECHO_MEG,O_CREAT | O_RDWR,0644);
	if(siFd < 0){
		return -1;
	}
	siRet = write(siFd,pstEchoMsg,sizeof(ST_SAVE_ECHO_MSG));
	if(siRet != sizeof(ST_SAVE_ECHO_MSG)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return siRet;
#endif
}



s32 DbgReadEchoMsg(ST_SAVE_ECHO_MSG *pstEchoMsg)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 siFd;
	s32 siRet;
	
	siFd = open(FILENAME_SAVED_ECHO_MEG,O_RDONLY,0);
	if(siFd < 0){
		return -1;
	}
	siRet = read(siFd,pstEchoMsg,sizeof(ST_SAVE_ECHO_MSG));
	if(siRet != sizeof(ST_SAVE_ECHO_MSG)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return siRet;
#endif		
}

s32 DbgEchoModeExchangeIsoPacket(SDK_8583_ST8583 *pstIsoMsgSend, SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 siRet;
	u8  buf1[20]= {0};
	u8  buf2[20]= {0};

	siRet = EchoIsoPackMsgHeader(pstIsoMsgRecv);
	if(siRet < 0){
		return siRet;
	}
	IsoGetField(pstIsoMsgSend,SDK_8583_FIELD_MSG,buf1,sizeof(buf1));//get message code
	TraceHex("xgd","get sent Message code",buf1,4);
	IsoGetField(pstIsoMsgSend,3,buf2,sizeof(buf2));//get process code
	TraceHex("xgd","get sent Message code",buf2,4);
	if(0 == memcmp(buf1,"0800",4)){
		siRet = EchoLogonPackMsg(pstIsoMsgSend,pstIsoMsgRecv);
	}else if(0 == memcmp(buf1,"0200",4) && 0 == memcmp(buf2,"000000",6)){
		siRet = EchoSalePackMsg(pstIsoMsgSend,pstIsoMsgRecv);
	}else if(0 == memcmp(buf1,"0200",4) && 0 == memcmp(buf2,"0200",4)){
	
	}
	if(siRet < 0){
		Trace("xgd","siRet=%d %s(%d)\r\n",siRet,__FUNCTION__,__LINE__);
		return siRet;
	}
	//exit(0);//only for debug
	return 0;
#endif
}

s32 DbgEchoInitMsg(ST_SAVE_ECHO_MSG *pstEchoMsg)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	u8 ucBuf[16];
	
	memset(pstEchoMsg,0x00,sizeof(ST_SAVE_ECHO_MSG));
	memcpy(pstEchoMsg->heEchoTmk,"\x31\x31\x31\x31\x31\x31\x31\x31",8);
#if 0	
	if(SDK_OK == sdkGetRandom(ucBuf,16)){
		memcpy(pstEchoMsg->heEchoTpk,ucBuf,8);
		memcpy(pstEchoMsg->heEchoTak,ucBuf + 8,8);
	}else{
		memcpy(pstEchoMsg->heEchoTpk,"\x32\x32\x32\x32\x32\x32\x32\x32",8);
		memcpy(pstEchoMsg->heEchoTak,"\x33\x33\x33\x33\x33\x33\x33\x33",8);
	}
#endif
#if 1
		memcpy(pstEchoMsg->heEchoTpk,"\x32\x32\x32\x32\x32\x32\x32\x32",8);
		memcpy(pstEchoMsg->heEchoTak,"\x33\x33\x33\x33\x33\x33\x33\x33",8);
#endif
	TraceHex("xgd","Init TPK",pstEchoMsg->heEchoTpk,8);
	TraceHex("xgd","Init TAK",pstEchoMsg->heEchoTak,8);
	strcpy(pstEchoMsg->asAccount,"6217921154022159");
	strcpy(pstEchoMsg->asAmount,"000000008000");
	strcpy(pstEchoMsg->asPin,"852369");
	return 0;
#endif
}

s32 DbgEchoHandleField39(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgSend,u8 *pucFile39)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	ST_SAVE_ECHO_MSG stEchoMsg;
	s32 iRet;
	u8  ucBuf[64];
	u8  ucBuf2[64];
	u8  ucAmt[6];
	u8  ucAmt2[6];
	u8  ucAmt3[6];

	iRet = DbgReadEchoMsg(&stEchoMsg);
	if(iRet < 0){
		return iRet;
	}
	strcpy(pucFile39,"00");
	switch(eTranId){
		case TRANSID_SALE:
			IsoGetField(pstIsoMsgSend,2,ucBuf,sizeof(ucBuf));
			if(sdk8583IsDomainExist(pstIsoMsgSend,4)){
		  		IsoGetField(pstIsoMsgSend,4,ucBuf2,sizeof(ucBuf2));
				if(memcmp(ucBuf,stEchoMsg.asAccount,16) == 0){
					TraceHex("xgd","sale amount",ucBuf2,12);
					TraceHex("xgd","Account amount",stEchoMsg.asAmount,12);
					if(memcmp(ucBuf2,stEchoMsg.asAmount,12) > 0){
						strcpy(pucFile39,"51");
					}else{
						sdkAscToBcd(ucAmt,stEchoMsg.asAmount,12);
						sdkAscToBcd(ucAmt2,ucBuf2,12);
						sdkBcdSub(ucAmt3, ucAmt,6,ucAmt2, 6);
						sdkBcdToAsc(stEchoMsg.asAmount,ucAmt3,6);
						TraceHex("xgd","remain amount",stEchoMsg.asAmount,12);
						iRet = DbgSaveEchoMsg(&stEchoMsg);
						if(iRet < 0){
							return iRet;
						}
					}
				}
			
		    }
			break;
		default:
			break;
	}

	return 0;
#endif
}
