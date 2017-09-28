/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.

                       http://www.xinguodu.com/en/

******************************************************************************
   File Name     :
   Version       :
   Author        :  Jeff
   Date          :  2017-09-25
   Description   :



******************************************************************************/
#include "global.h"
#include <sys/types.h>
#include <sys/fcntl.h>
/*----------------------------------------------------------------------------*/


static ECHO_8583_STFIELDDEF EchoTabIsoFields[64 + 1] =
{
	 /*tpdu*/	 {0,10,  SDK_8583_DATA_BCD},
   	/*msg code*/ {0,4,   SDK_8583_DATA_BCD},
    /* FLD  02 */ {2,19,  SDK_8583_DATA_BCD},
    /* FLD  03 */ {0,6,   SDK_8583_DATA_BCD},
    /* FLD  04 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  05 */ {0,20,  SDK_8583_DATA_BCD},
    /* FLD  06 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  07 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  08 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  09 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  10 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  11 */ {0,6,   SDK_8583_DATA_BCD},
    /* FLD  12 */ {0,6,   SDK_8583_DATA_BCD},
    /* FLD  13 */ {0,4,   SDK_8583_DATA_BCD},
    /* FLD  14 */ {0,4,   SDK_8583_DATA_BCD},
    /* FLD  15 */ {0,4,   SDK_8583_DATA_BCD},
    /* FLD  16 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  17 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  18 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  19 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  20 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  21 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  22 */ {0,3,   SDK_8583_DATA_BCD},
    /* FLD  23 */ {0,3,   SDK_8583_DATA_BCD},
    /* FLD  24 */ {0,4,   SDK_8583_DATA_BCD},
    /* FLD  25 */ {0,2,   SDK_8583_DATA_BCD},
    /* FLD  26 */ {0,2,   SDK_8583_DATA_BCD},
    /* FLD  27 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  28 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  29 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  30 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  31 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  32 */ {2,11,  SDK_8583_DATA_BCD},
    /* FLD  33 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  34 */ {0,40,  SDK_8583_DATA_ASC},
    /* FLD  35 */ {2,37,  SDK_8583_DATA_BCD},
    /* FLD  36 */ {3,104, SDK_8583_DATA_BCD},
    /* FLD  37 */ {0,12,  SDK_8583_DATA_ASC},
    /* FLD  38 */ {0,6,   SDK_8583_DATA_ASC},
    /* FLD  39 */ {0,2,   SDK_8583_DATA_ASC},
    /* FLD  40 */ {0,40,  SDK_8583_DATA_ASC},
    /* FLD  41 */ {0,8,   SDK_8583_DATA_ASC},
    /* FLD  42 */ {0,15,  SDK_8583_DATA_ASC},
    /* FLD  43 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  44 */ {2,25,  SDK_8583_DATA_ASC},
    /* FLD  45 */ {2,76,  SDK_8583_DATA_BCD},
    /* FLD  46 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  47 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  48 */ {3,322, SDK_8583_DATA_BCD},
    /* FLD  49 */ {0,3,   SDK_8583_DATA_ASC},
    /* FLD  50 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  51 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  52 */ {0,8,   SDK_8583_DATA_BIT},
    /* FLD  53 */ {0,16,  SDK_8583_DATA_BCD},
    /* FLD  54 */ {3,40,  SDK_8583_DATA_ASC},
    /* FLD  55 */ {3,255, SDK_8583_DATA_BIT},
    /* FLD  56 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  57 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  58 */ {3,100, SDK_8583_DATA_ASC},
    /* FLD  59 */ {0,12,  SDK_8583_DATA_BCD},
    /* FLD  60 */ {3,17,  SDK_8583_DATA_BCD},
    /* FLD  61 */ {3,29,  SDK_8583_DATA_BCD},
    /* FLD  62 */ {3,512, SDK_8583_DATA_ASC},
    /* FLD  63 */ {3,163, SDK_8583_DATA_ASC},
    /* FLD  64 */ {0,8,   SDK_8583_DATA_BIT},
};





u8 *gpstEchoIso8583[66] =
{
	gstEchoIso8583.asTpdu,						/* tpdu*/                                                          
	gstEchoIso8583.asMsgCode,					/*Msg code*/  
	gstEchoIso8583.asPan,						/* FLD  02 */  
	gstEchoIso8583.asProcCode,					/* FLD  03 */  
	gstEchoIso8583.asTranAmt,					/* FLD  04 */  
	gstEchoIso8583.asField5,				 	/* FLD  05 */  
	gstEchoIso8583.asField6,					/* FLD  06 */  
	gstEchoIso8583.asField7,			 		/* FLD  07 */  
	gstEchoIso8583.asField8,					/* FLD  08 */  
	gstEchoIso8583.asField9,			 		/* FLD  09*/  
	gstEchoIso8583.asField10,					/* FLD  10 */  
	gstEchoIso8583.asSTAN,						/* FLD  11 */  
	gstEchoIso8583.asLocalTime,				    /* FLD  12 */  
	gstEchoIso8583.asLocalDate,				    /* FLD  13 */  
	gstEchoIso8583.asExpDate,					/* FLD  14 */ 
	gstEchoIso8583.asField15,					/* FLD  15 */
	gstEchoIso8583.asField16,					/* FLD  16 */
	gstEchoIso8583.asField17,					/* FLD  17 */
	gstEchoIso8583.asField18,					/* FLD  18 */
	gstEchoIso8583.asField19,					/* FLD  19 */
	gstEchoIso8583.asField20,					/* FLD  20 */
	gstEchoIso8583.asField21,					/* FLD  21 */
	gstEchoIso8583.asEntryMode,					/* FLD  22 */  
	gstEchoIso8583.asPanSeqNo,				    /* FLD  23 */  
	gstEchoIso8583.asNii,						/* FLD  24 */  
	gstEchoIso8583.asCondCode,					/* FLD  25*/ 
	gstEchoIso8583.asField26,					/* FLD  26*/ 
	gstEchoIso8583.asField27,					/* FLD  27*/ 
	gstEchoIso8583.asField28,					/* FLD  28*/ 
	gstEchoIso8583.asField29,					/* FLD  29*/ 
	gstEchoIso8583.asField30,					/* FLD  30*/ 
	gstEchoIso8583.asField31,					/* FLD  31*/ 
	gstEchoIso8583.asField32,					/* FLD  32*/ 
	gstEchoIso8583.asField33,					/* FLD  33*/ 
	gstEchoIso8583.asField34,					/* FLD  34*/ 	
	gstEchoIso8583.asTrack2,					/* FLD  35 */  
	gstEchoIso8583.asTrack3,					/* FLD  36 */  
	gstEchoIso8583.asRRN,						/* FLD  37 */  
	gstEchoIso8583.asAuthCode,				    /* FLD  38 */  
	gstEchoIso8583.asRspCode,					/* FLD  39 */ 
	gstEchoIso8583.asField40,					/* FLD  40 */ 
	gstEchoIso8583.asTermID,					/* FLD  41 */  
	gstEchoIso8583.asMerchantID,				/* FLD  42 */  
	gstEchoIso8583.asField43,					/* FLD  43 */  
	gstEchoIso8583.asAddlRsp,					/* FLD  44 */  
	gstEchoIso8583.asTrack1,					/* FLD  45 */  
	gstEchoIso8583.asField46,					/* FLD  46 */  
	gstEchoIso8583.asField47,					/* FLD  47 */  
	gstEchoIso8583.asField48,		    		/* FLD  48 */  
	gstEchoIso8583.asTranCurcyCode,		  		/* FLD  49 */  
	gstEchoIso8583.asHolderCurcyCode,			/* FLD  50 */  
	gstEchoIso8583.asField51,				 	/* FLD  51 */  
	gstEchoIso8583.hePINData,					/* FLD  52 */
	gstEchoIso8583.asField53,					/* FLD  53 */
	gstEchoIso8583.asExtAmount,					/* FLD  54 */  
	gstEchoIso8583.heICCData,		    		/* FLD  55 */  
	gstEchoIso8583.heICCData2,					/* FLD  56 */
	gstEchoIso8583.asField57, 					/* FLD  57 */
	gstEchoIso8583.asField58,					/* FLD  58 */
	gstEchoIso8583.asField59, 					/* FLD  59 */
	gstEchoIso8583.asField60, 					/* FLD  60 */                   
	gstEchoIso8583.asField61,					/* FLD  61 */  
	gstEchoIso8583.asField62,					/* FLD  62 */  
	gstEchoIso8583.asField63, 					/* FLD  63 */  
	gstEchoIso8583.asMac,						/* FLD  64 */  
	NULL,
};


void EchoSetFieldLen(s32 iFieldLen,s32 iFieldNo)
{
#ifndef JEFF_ECHO
	return;
#else
	gpstEchoIso8583[iFieldNo][0] = (iFieldLen >> 8) & 0xFF;
	gpstEchoIso8583[iFieldNo][1] =  iFieldLen & 0xFF;

#endif
}

s32 EchoGetFieldLen(s32 iFieldNo)
{
#ifndef JEFF_ECHO
	return 0;
#else
	s32 iLen;

	iLen = gpstEchoIso8583[iFieldNo][1] + (gpstEchoIso8583[iFieldNo][0] << 8);
	return iLen;
#endif
}

bool EchoFieldIsExist(s32 iFieldNo)
{
#ifndef JEFF_ECHO
	return false;
#else
	s32 iLen;

	iLen = EchoGetFieldLen(iFieldNo);
	return (iLen > 0 ? true:false);
#endif
}
void EchoSetField(ECHO_8583_STFIELDDEF *pstFieldDef,u8 *pheTrueFieldData,s32 iFieldLen,s32 iFieldNo)
{
#ifndef JEFF_ECHO
	return;
#else
	s32 iLen;
	u8  ucBuf[1024]={0};

	EchoSetFieldLen(iFieldLen,iFieldNo);
	if(pstFieldDef->ucFDataT == SDK_8583_DATA_BCD)
	{
		iLen = (iFieldLen % 2) ? (iFieldLen/2 + 1):(iFieldLen / 2);
		sdkBcdToAsc(ucBuf,pheTrueFieldData,iLen);
		memcpy(gpstEchoIso8583[iFieldNo] + ECHO_FIELD_LEN ,ucBuf,iFieldLen);
	}
	else
	{
		memcpy(gpstEchoIso8583[iFieldNo] + ECHO_FIELD_LEN ,pheTrueFieldData,iFieldLen);
	}
	
#endif
}

s32 EchoGetField(u8 *pheFieldData,s32 iFieldNo)
{
#ifndef JEFF_ECHO
	return 0;
#else
	s32 iFieldLen;

	iFieldLen = EchoGetFieldLen(iFieldNo);
	memcpy(pheFieldData,gpstEchoIso8583[iFieldNo] + ECHO_FIELD_LEN ,iFieldLen);
	return iFieldLen;
#endif
}


s32 SaveEchoMsg(ST_SAVED_ECHO_MSG *pstEchoMsg)
{
#ifndef JEFF_ECHO
	return 0;
#else
	s32 siFd;
	s32 iRet;
	
	siFd = open(FILENAME_SAVED_ECHO_MEG,O_CREAT | O_RDWR,0644);
	if(siFd < 0){
		return -1;
	}
	iRet = write(siFd,pstEchoMsg,sizeof(ST_SAVED_ECHO_MSG));
	if(iRet != sizeof(ST_SAVED_ECHO_MSG)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return iRet;
#endif
}



s32 ReadEchoMsg(ST_SAVED_ECHO_MSG *pstEchoMsg)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	s32 siFd;
	s32 iRet;
	
	siFd = open(FILENAME_SAVED_ECHO_MEG,O_RDONLY,0);
	if(siFd < 0){
		return -1;
	}
	iRet = read(siFd,pstEchoMsg,sizeof(ST_SAVED_ECHO_MSG));
	if(iRet != sizeof(ST_SAVED_ECHO_MSG)){
		close(siFd);
		return -2;
	}
	close(siFd);
	return SDK_OK;
#endif		
}

s32 EchoModeExchangeIsoPacket(const u8 *pheSrc,s32 iSrcLen, SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return 0;
#else
	s32 iRet;
	s32 iLen;
	u8  buf1[40]= {0};
	u8  buf2[40]= {0};

	memset(&gstEchoIso8583,0,sizeof(gstEchoIso8583));
	iRet = ReadEchoMsg(&gstSavedEchoMsg);
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
    iRet = EchoUnpackIso8583(pheSrc,iSrcLen);
	if(iRet < SDK_OK)
	{
		return SDK_ERR;
	}
	iRet = EchoIsoPackMsgHeader(pstIsoMsgRecv);
	if(iRet < 0)
	{
		return SDK_ERR;
	}
	iLen = EchoGetField(buf1, 1);//get Msg code
	if(iLen <= 0)
	{
		return SDK_ERR;
	}
	TraceHex("xgd","get sent Message code",buf1,iLen);
	iLen = EchoGetField(buf2, 3);//get process code
	if(0 != memcmp(buf1,"0800",4) && iLen <= 0)
	{
		return SDK_ERR;
	}
	if(0 == memcmp(buf1,"0800",4))//logon
	{
		memset(buf1,0,sizeof(buf1));
		iLen = EchoGetField(buf1,60);
		if(iLen <= 0)
		{	
			return SDK_ERR;
		}
		TraceHex("xgd","get Field60",buf1,iLen);
		
		if(0 == memcmp(buf1,"00",2) && (memcmp(buf1 + 8,"001",3)
			|| memcmp(buf1 + 8,"003",3) || memcmp(buf1 + 8,"004",3)))//compare 60.1<msg type code> and 60.3<network mangment code>
		{
			iRet = EchoLogonPackMsg(pstIsoMsgRecv);
		}
		
	}
	else if(0 == memcmp(buf1,"0200",4) && 0 == memcmp(buf2,"000000",6))//sale
	{
		iRet = EchoSalePackMsg(pstIsoMsgRecv);
		
	}
	
	else if(0 == memcmp(buf1,"0200",4) && 0 == memcmp(buf2,"200000",6))//void
	{
		iRet = EchoVoidPackMsg(pstIsoMsgRecv);
		
	}
	else if(0 == memcmp(buf1,"0200",4) && 0 == memcmp(buf2,"310000",6)) //balance
	{
		iRet = EchoBalancePackMsg(pstIsoMsgRecv);
	}	
	if(iRet < SDK_OK)
	{
		Trace("xgd","iRet=%d\r\n",iRet);
		return SDK_ERR;
	}

	//exit(0);//only for debug
	return SDK_OK;
#endif
}

s32 EchoInitMsg(ST_SAVED_ECHO_MSG *pstEchoMsg)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	memset(pstEchoMsg,0x00,sizeof(ST_SAVED_ECHO_MSG));
	memcpy(pstEchoMsg->heEchoTmk,"\x31\x31\x31\x31\x31\x31\x31\x31",8);
	memcpy(pstEchoMsg->heEchoTpk,"\x32\x32\x32\x32\x32\x32\x32\x32",8);
	memcpy(pstEchoMsg->heEchoTak,"\x33\x33\x33\x33\x33\x33\x33\x33",8);
	TraceHex("xgd","Init TPK",pstEchoMsg->heEchoTpk,8);
	TraceHex("xgd","Init TAK",pstEchoMsg->heEchoTak,8);
	strcpy(pstEchoMsg->asAccount,"6214836552574275");
	strcpy(pstEchoMsg->asAmount,"000000008000");
	strcpy(pstEchoMsg->asPin,"852369");
	strcpy(pstEchoMsg->ucTID,"12345678");
	pstEchoMsg->ucTIDLEN = 8;
	strcpy(pstEchoMsg->ucMID,"123456789012345");
	pstEchoMsg->ucMIDLen= 15;
	pstEchoMsg->ucPinLen = 6;
	pstEchoMsg->ucCardNoLen = 16;
	return SDK_OK;
#endif
}

s32 EchoHandleField25(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"\x00",1);//set Field37
	pstIsoMsgRecv->nBagLen += 1;
	return SDK_OK;
#endif
}




s32 EchoHandleField32(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"\x08",1);//Field 32 data
	pstIsoMsgRecv->nBagLen += 1;
	pSendEchoMsg += 1;
    memcpy(pSendEchoMsg,"\x00\x01\x00\x00",4);
	pstIsoMsgRecv->nBagLen += 4;
	return SDK_OK;
#endif
}

s32 EchoHandleField37(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"952795289529",12);//set Field37
	pstIsoMsgRecv->nBagLen += 12;
	return SDK_OK;
#endif
}

s32 EchoHandleField38(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"123456",6);//set Field37
	pstIsoMsgRecv->nBagLen += 6;
	return SDK_OK;	
#endif
}

s32 EchoHandleField39(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgRecv,u8 *pucFiled39)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	s32 iRet;
	s32 iLen;
	u8  ucBuf[64];
	u8  ucAmt[6];
	u8  ucAmt2[6];
	u8  ucAmt3[6];
	u8 *pSendEchoMsg;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	pstIsoMsgRecv->nBagLen += 2;
	strcpy(pucFiled39,"03");	
	if(TRANSID_LOGON != eTranId)
	{
		if(0 == EchoGetFieldLen(64) || ECHO_MAC_ERR == EchoGetFieldLen(64))
		{
			memcpy(pucFiled39,"A0",2); //
			memcpy(pSendEchoMsg,pucFiled39,2);
			return SDK_OK;
		}
	}
	iLen = EchoGetField(ucBuf,41); //check TID
	if(iLen != gstSavedEchoMsg.ucTIDLEN || (0 != memcmp(ucBuf,gstSavedEchoMsg.ucTID,gstSavedEchoMsg.ucTIDLEN)))
	{
		strcpy(pucFiled39,"03"); //invaild Meichant
		memcpy(pSendEchoMsg,pucFiled39,2);
		return SDK_OK;
	}
	iLen = EchoGetField(ucBuf,42);//check MID
	if(iLen != gstSavedEchoMsg.ucMIDLen || (0 != memcmp(ucBuf,gstSavedEchoMsg.ucMID,gstSavedEchoMsg.ucMIDLen)))
	{
		strcpy(pucFiled39,"03"); 
		memcpy(pSendEchoMsg,pucFiled39,2);
		return SDK_OK;
	}
	if(TRANSID_LOGON != eTranId && TRANSID_VOID != eTranId && EchoIsRightCardNo())
	{
		iRet = EchoIsRightPin();
		if(false == iRet)
		{
			strcpy(pucFiled39,"55"); 
			memcpy(pSendEchoMsg,pucFiled39,2);
			return SDK_OK;
		}
	}
  	if(true == EchoIsRightCardNo())
  	{
		EchoGetField(ucBuf, 4);
		switch(eTranId)
		{
			case TRANSID_SALE:
				if(memcmp(ucBuf,gstSavedEchoMsg.asAmount,12) > 0)
				{
					strcpy(pucFiled39,"51"); //No enough amount
				}
				else
				{
					sdkAscToBcd(ucAmt,gstSavedEchoMsg.asAmount,12);
					sdkAscToBcd(ucAmt2,ucBuf,12);
					sdkBcdSub(ucAmt3, ucAmt,6,ucAmt2, 6);
					sdkBcdToAsc(gstSavedEchoMsg.asAmount,ucAmt3,6);
				}
				break;
			case TRANSID_VOID:
					sdkAscToBcd(ucAmt,gstSavedEchoMsg.asAmount,12);
					sdkAscToBcd(ucAmt2,ucBuf,12);
					sdkBcdAdd(ucAmt3, ucAmt,6,ucAmt2, 6);
					sdkBcdToAsc(gstSavedEchoMsg.asAmount,ucAmt3,6);
				break;
			default:
				break;
		}
		iRet = SaveEchoMsg(&gstSavedEchoMsg);
		if(iRet < 0)
		{
			return SDK_ERR;
		}
	}
	memcpy(pucFiled39,"00",2); //
	memcpy(pSendEchoMsg,pucFiled39,2);
	return SDK_OK;
#endif
}

s32 EchoHandleTIDMID(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"12345678",8);  //Field 41
	pstIsoMsgRecv->nBagLen += 8;
	pSendEchoMsg += 8; 
	memcpy(pSendEchoMsg,"123456789012345",15);//field 42
	pstIsoMsgRecv->nBagLen += 15;
	return SDK_OK;
#endif
}

s32 EchoHandleField44(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;
   
	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"\x16",1);
	pSendEchoMsg += 1;
	pstIsoMsgRecv->nBagLen += 1;
	memcpy(pSendEchoMsg,"0102000001030000",16);//set Field44
	pstIsoMsgRecv->nBagLen += 16;
	return SDK_OK;
#endif
}


s32 EchoHandleField49(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;
   
	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"156",3);//set Field49
	pstIsoMsgRecv->nBagLen += 3;
	return SDK_OK;
#endif
}

s32 EchoHandleField54(SDK_8583_ST8583 *pstIsoMsgRecv,u8 *pucFiled39)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;
	s32 iLen;
   
	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"\x00\x20",2);
	pSendEchoMsg += 2;
	pstIsoMsgRecv->nBagLen += 2;
	
	iLen = strlen("0210156C");
	memcpy(pSendEchoMsg,"0210156C",iLen);
	pSendEchoMsg += iLen;
	pstIsoMsgRecv->nBagLen += iLen;
	if(EchoIsRightCardNo() && (0 == memcmp("00",pucFiled39,2)))
	{
		memcpy(pSendEchoMsg,gstSavedEchoMsg.asAmount,12);
	}
	else
	{
		memset(pSendEchoMsg ,'\0',12);
	}
	pSendEchoMsg += 12;
	pstIsoMsgRecv->nBagLen += 12;
	return SDK_OK;
#endif
}

s32 EchoCalcPinBlock(u8 *pucPinBlock)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	s32 i;
	s32 iLen;
	u8 buf[64] = {0};
	u8 bcCardNo[8+1];
	u8 hePin[8+1];
	u8 *pucPoint;

	pucPoint = gstSavedEchoMsg.asAccount + gstSavedEchoMsg.ucCardNoLen - 1 - 12;
	memcpy(buf,pucPoint,12);
	sdkAscToBcd(bcCardNo + 2, buf,12);
	memcpy(bcCardNo,"\x00\x00",2);
	
	hePin[0] = gstSavedEchoMsg.ucPinLen;
	sdkAscToBcd(hePin + 1, gstSavedEchoMsg.asPin,gstSavedEchoMsg.ucPinLen);
	iLen = gstSavedEchoMsg.ucPinLen % 2 ? (gstSavedEchoMsg.ucPinLen / 2 + 1):(gstSavedEchoMsg.ucPinLen / 2);
	memset(hePin + 1 + iLen,0xFF,8 - 1 - iLen);
	for(i = 0;i < 8;i++)
	{
		hePin[i] ^= bcCardNo[i];
	}
	if(gstSavedEchoMsg.ucIsTriDes)
	{
		sdkDes3S(true,hePin,gstSavedEchoMsg.heEchoTpk);
	}
	else
	{
		sdkDesS(true,hePin,gstSavedEchoMsg.heEchoTpk);
	}
	memcpy(pucPinBlock,hePin,8);
	TraceHex("xgd","pucPinBlock",pucPinBlock,8);
	return SDK_OK;
#endif

}
s32 EchoHandleField60(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;
	s32 iRet;
	u8 buf[64] = {0};
	u8 buf2[64] = {0};

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	switch(eTranId){
		case TRANSID_LOGON:
			memcpy(pSendEchoMsg,"\x00\x11",2);
			pSendEchoMsg += 2;
			pstIsoMsgRecv->nBagLen += 2;
			
			memcpy(pSendEchoMsg,"\x00\x00\x00\x01",4);
			pSendEchoMsg += 4;
			pstIsoMsgRecv->nBagLen += 4;
			
			iRet = EchoGetField(buf,60);
			if(iRet <= 0)
			{
				return SDK_ERR;
			}
			TraceHex("xgd","getField60",buf,iRet);
			sdkAscToBcd(buf2, buf + 8, 3);
			memcpy(pSendEchoMsg,buf2,2);
		    pSendEchoMsg += 2;
			pstIsoMsgRecv->nBagLen += 2;
			break;
		case TRANSID_SALE:
		case TRANSID_VOID:
		case TRANSID_BALANCE:
			memcpy(pSendEchoMsg,"\x00\x14",2);
			pSendEchoMsg += 2;
			pstIsoMsgRecv->nBagLen += 2;
			memcpy(pSendEchoMsg,"\x22\x00\x00\x01\x00\x06\x00",7);
			pSendEchoMsg += 7;
			pstIsoMsgRecv->nBagLen += 7;
			break;
		default:
			break;
	}
	return SDK_OK;
#endif
}

s32 EchoHandleField61(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 buf[64]={0};
	u8 *pSendEchoMsg;
	s32 iRet;
   
	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;

	memcpy(pSendEchoMsg,"\x00\x12",2);
  	pSendEchoMsg += 2;
	pstIsoMsgRecv->nBagLen += 2;
	
	iRet = EchoGetField(buf, 60);
	if(iRet <= 0)
	{
		return SDK_ERR;
	}
	sdkAscToBcd(pSendEchoMsg,buf + 2, 6);
	pSendEchoMsg += 3;
	pstIsoMsgRecv->nBagLen += 3;
    iRet = EchoGetField(buf,11);
	if(iRet <= 0)
	{
		return SDK_ERR;
	}
	sdkAscToBcd(pSendEchoMsg,buf,6);
	pSendEchoMsg += 3;
	pstIsoMsgRecv->nBagLen += 3;  
	
	return SDK_OK;
#endif
}

s32 EchoHandleField62(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgRecv,u8 *pucField39)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;
	s32 iRet;
	u8 buf[64] = {0};

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	switch(eTranId){
		case TRANSID_LOGON:
			if(0 != memcmp(pucField39,"00",2))
			{
				memcpy(pSendEchoMsg,"\x00\x24",2);
				pSendEchoMsg += 2;
				pstIsoMsgRecv->nBagLen += 2;
				memset(pSendEchoMsg,0x00,24);
				pSendEchoMsg += 24;
				pstIsoMsgRecv->nBagLen += 24;
				return SDK_OK;
			}
			iRet = sdkGetRandom(buf,32);
			if(iRet != SDK_OK)
			{
				return SDK_ERR;
			}

			if(0 == memcmp(pSendEchoMsg - 2,"\x00\x10",2)) //single des
			{
				memcpy(pSendEchoMsg,"\x00\x24",2);
				pSendEchoMsg += 2;
				pstIsoMsgRecv->nBagLen += 2;
				gstSavedEchoMsg.ucIsTriDes = false;
				memcpy(gstSavedEchoMsg.heEchoTpk,buf,8);
				memcpy(gstSavedEchoMsg.heEchoTak,buf + 8,8);
				sdkDesS(TRUE,buf,gstSavedEchoMsg.heEchoTmk);//usr Tmk to  encrypt tpk
				TraceHex("xgd","Encrypted TPK=",buf,8);
				 //calc tpk kcv 
				memset(buf + 8,0x00,8);                 
				sdkDesS(TRUE,buf + 8,gstSavedEchoMsg.heEchoTpk);
				TraceHex("xgd","TPK,KCV=",buf + 8,8);
				//usr TMK to  encrypt TAK
				memcpy(buf + 12,gstSavedEchoMsg.heEchoTak,8); 
				sdkDesS(TRUE,buf + 12,gstSavedEchoMsg.heEchoTmk);
				TraceHex("xgd","Encrypted TAK=",buf + 12,8);
				//calc TAK kcv 
				memset(buf + 20,0x00,8);       
				sdkDesS(TRUE,buf + 20,gstSavedEchoMsg.heEchoTak);
				memcpy(pSendEchoMsg,buf,24);
				TraceHex("xgd","TAK,KCV=",buf + 20,8);
				pSendEchoMsg += 24;
				pstIsoMsgRecv->nBagLen += 24;
			}
			else if(0 == memcmp(pSendEchoMsg - 2,"\x00\x30",0))  //tri des
			{
				memcpy(pSendEchoMsg,"\x00\x40",2);
				pSendEchoMsg += 2;
				pstIsoMsgRecv->nBagLen += 2;
				gstSavedEchoMsg.ucIsTriDes = true;
				memcpy(gstSavedEchoMsg.heEchoTpk,buf,16);
				memcpy(gstSavedEchoMsg.heEchoTak,buf + 16,16);
				sdkDes3S(TRUE,buf,gstSavedEchoMsg.heEchoTmk);//usr TMK to  encrypt tpk
				sdkDes3S(TRUE,buf + 8,gstSavedEchoMsg.heEchoTmk);//usr TMK to  encrypt tpk
				TraceHex("xgd","Encrypted TPK=",buf,16);
				 //calc tpk kcv 
				memset(buf + 16,0x00,8);                 
				sdkDes3S(TRUE,buf + 16,gstSavedEchoMsg.heEchoTpk);
				
				TraceHex("xgd","TPK,KCV=",buf + 16,8);
				//usr TMK to  encrypt TAK
				memcpy(buf + 20,gstSavedEchoMsg.heEchoTak,16);  
				sdkDes3S(TRUE,buf + 20,gstSavedEchoMsg.heEchoTmk);//usr TMK to  encrypt TAK
				sdkDes3S(TRUE,buf + 28,gstSavedEchoMsg.heEchoTmk);//usr TMK to  encrypt TAK
				TraceHex("xgd","Encrypted TAK=",buf + 20,16);
				//calc TAK kcv 
				memset(buf + 36,0x00,8);                           //TAK use single des to calc KCV
				sdkDesS(TRUE,buf + 36,gstSavedEchoMsg.heEchoTak);
				memcpy(pSendEchoMsg,buf,40);
				TraceHex("xgd","TAK,KCV=",buf + 36,8);
				pSendEchoMsg += 40;
				pstIsoMsgRecv->nBagLen += 40;
				
			}
			else if(0 == memcmp(pSendEchoMsg - 2,"\x00\x40",0))//tri des and include TDK
			{
				//to do ,right now teiminal does not support it.
			}
			else
			{
				return SDK_ERR;
			}
			iRet = EchoCalcPinBlock(gstSavedEchoMsg.ucPinBlock);
			if(iRet < SDK_OK)
			{
				return SDK_ERR;
			}
			TraceHex("xgd","jeff,generate pinPlock",gstSavedEchoMsg.ucPinBlock,8);
		    iRet = SaveEchoMsg(&gstSavedEchoMsg);
			if(iRet < 0)
			{
				return SDK_ERR;
			}
					break;
				default:
					break;
			}
		return SDK_OK;
#endif
}

s32 EchoHandleField63(SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 *pSendEchoMsg;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;
	memcpy(pSendEchoMsg,"\x00\x03",2);
	pSendEchoMsg += 2;
	pstIsoMsgRecv->nBagLen += 2;
	memcpy(pSendEchoMsg,"CUP",3);//set Field63
	pstIsoMsgRecv->nBagLen += 3;
	return SDK_OK;
#endif
}
bool EchoIsRightPin(void)
{
#ifndef JEFF_ECHO
	return false;
#else
	u8 asBuf[20];
	s32 iLen;

	iLen = EchoGetField(asBuf,52);
	if(0 == iLen)
	{
		if(gstSavedEchoMsg.ucIsSupportNoPin)
		{
			return true;
		}
	}
	else
	{
		if(0 == memcmp(gstSavedEchoMsg.ucPinBlock,asBuf,8))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
#endif
}

bool EchoIsRightCardNo(void)
{
#ifndef JEFF_ECHO
	return false;
	
#else
	s32 iLen;
	u8 buf[64];
	
	iLen = EchoGetField(buf,2);
	if(iLen <= 0)
	{
		iLen = EchoGetField(buf,35);
		if(iLen <= 0)
		{
			return false;
		}
	}
	if(0 != memcmp(gstSavedEchoMsg.asAccount,buf,gstSavedEchoMsg.ucCardNoLen) 
		|| (gstSavedEchoMsg.ucCardNoLen != iLen))
	{
		return false;
	}
	else
	{
		return true;
	}
		
	return false;
#endif	
}
void GetFieldLen(ECHO_8583_STFIELDDEF *pstFieldDef, s32 *iOutputFieldLen)
{
#ifndef JEFF_ECHO
	return;
#else
	if(pstFieldDef->ucFDataT == SDK_8583_DATA_BCD)
	{
		*iOutputFieldLen = (*iOutputFieldLen % 2) ? (*iOutputFieldLen/2 + 1):(*iOutputFieldLen / 2);
	}
	else if(pstFieldDef->ucFDataT == SDK_8583_DATA_ASC || pstFieldDef->ucFDataT == SDK_8583_DATA_BIT )
	{
		*iOutputFieldLen = *iOutputFieldLen;
	}
	return;
#endif	
}

s32 EchoIsoPackPublicMsg(E_TRANS_ID eTranId,SDK_8583_ST8583 *pstIsoMsgRecv)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	u8 buf[64];
	u8 buf2[64];
	u8 *pSendEchoMsg;
	s32 iLen;

	pSendEchoMsg = pstIsoMsgRecv->ucBagData + pstIsoMsgRecv->nBagLen;

	if(TRANSID_LOGON != eTranId)
	{
		iLen = EchoGetField(buf,3);
		if(iLen <= 0)
		{
			return SDK_ERR;
		}
		sdkAscToBcd(buf2,buf,iLen);
		iLen = iLen % 2? (iLen / 2) + 1:iLen / 2;
		memcpy(pSendEchoMsg,buf2,iLen);
		pSendEchoMsg += iLen;
		pstIsoMsgRecv->nBagLen += iLen;
	}
		
	iLen = EchoGetField(buf, 11); //Field 11
	if(iLen <= 0)
	{
		return SDK_ERR;
	}
	sdkAscToBcd(buf2,buf,iLen);
	iLen = iLen % 2? (iLen / 2) + 1:iLen / 2;
	memcpy(pSendEchoMsg,buf2,iLen);
	pSendEchoMsg += iLen;
	pstIsoMsgRecv->nBagLen += iLen;
	

	if(SDK_OK == sdkGetRtc(buf))
    {
    	//sdkBcdToAsc(buf2, &buf[3], 3);
		
		memcpy(pSendEchoMsg,&buf[3],3); //Field 12,time
		pSendEchoMsg += 3;
		pstIsoMsgRecv->nBagLen += 3;
		
		memcpy(pSendEchoMsg,&buf[1],2); //Field 13 data
		pSendEchoMsg += 2;
		pstIsoMsgRecv->nBagLen += 2;
    }	
	return SDK_OK;
#endif
	
}

s32 EchoUnpackIso8583(const u8 *pheSrc,s32 iSrcLen)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else	
	s32 i = 0;
	s32 iCount = 0;
	s32 iCurrentLen = 0;
	s32 iFieldLen = 0;
	s32 iBufLen = 0;
	u8  buf[9];
	u8  buf8583Pkg[2048];
	u8  bufTmp2[2048];
	ECHO_8583_STFIELDDEF *pstTabIsoFields = EchoTabIsoFields + 1;
	
	iCount = iSrcLen;
	memcpy(buf8583Pkg,pheSrc,iCount);
	/*TPDU*/
	EchoSetField(&EchoTabIsoFields[0],buf8583Pkg + iCurrentLen,10, 0);
	iCurrentLen += 5;//len of TPDU
	iCurrentLen += 6;//len of head
	 /*MSG CODE*/
	EchoSetField(&pstTabIsoFields[0],buf8583Pkg + iCurrentLen,4, 1);
	iCurrentLen += 2;
	/*Bit Map */
	memcpy(buf,buf8583Pkg + iCurrentLen,8);
	iCurrentLen += 8; //len of bitmap
	/*Field 2 -- Field 64*/
	for(i = 1;i < 64;i++)
	{
	   if(buf[i/8] & (0x80>>i%8))
	   {
	   	
		 if(pstTabIsoFields[i].ucFLenLen == 0)
		 {
		 	iFieldLen = pstTabIsoFields[i].sFDataLen;
			EchoSetField(&pstTabIsoFields[i],buf8583Pkg + iCurrentLen,iFieldLen,i+1);
			GetFieldLen(&pstTabIsoFields[i],&iFieldLen);
		 	iCurrentLen += iFieldLen;
		 }
		 else if(pstTabIsoFields[i].ucFLenLen == 2)
		 {
		 	iFieldLen = ((buf8583Pkg + iCurrentLen)[0] & 0x0F) 
							+ ((buf8583Pkg + iCurrentLen)[0] >> 4) * 10;
			if(iFieldLen > pstTabIsoFields[i].sFDataLen)
			{
				DispUnpack8583Err(i + 1); //display unpack error
				Trace("xgd","FieldNo%d,len=%d",i+1,iFieldLen);
				return SDK_ERR;
			}
			iCurrentLen += 1;
			EchoSetField(&pstTabIsoFields[i],buf8583Pkg + iCurrentLen,iFieldLen,i+1);
			GetFieldLen(&pstTabIsoFields[i],&iFieldLen);
			iCurrentLen += iFieldLen;
		 }
		else if(pstTabIsoFields[i].ucFLenLen == 3)
		 {
		 	iFieldLen =  ((buf8583Pkg + iCurrentLen)[0] >> 4) * 1000
						+ ((buf8583Pkg + iCurrentLen)[0] & 0x0F) * 100
						+ ((buf8583Pkg + iCurrentLen)[1] & 0x0F)
						+ ((buf8583Pkg + iCurrentLen)[1] >> 4) * 10;
			
			if(iFieldLen > pstTabIsoFields[i].sFDataLen)
			{
				DispUnpack8583Err(i + 1);//display unpack error
				Trace("xgd","FieldNo%d,len=%d",i+1,iFieldLen);
				return SDK_ERR;
			}
			iCurrentLen += 2;
			EchoSetField(&pstTabIsoFields[i],buf8583Pkg + iCurrentLen,iFieldLen,i+1);
			GetFieldLen(&pstTabIsoFields[i],&iFieldLen);
			iCurrentLen += iFieldLen;
		 }
		 
	   }
	}	
#if 0	
	for(i = 0; i <= 64;i++)
	{
		if((iFieldLen = EchoGetFieldLen(i)) > 0)
		{
			Trace("xgd","Exist FieldNo[%d],iField=%d\r\n",i,iFieldLen);
			iBufLen = EchoGetField(bufTmp2, i);
			TraceHex("xgd","FieldMsg=",bufTmp2,iBufLen);
		}
	}
#endif	
	EchoHandleResponseMac(pheSrc,iSrcLen);
	return SDK_OK;
#endif	
}

s32 EchoHandleResponseMac(const u8 *pheSrc,s32 iSrcLen)
{
#ifndef JEFF_ECHO
	return SDK_OK;
#else
	s32 iLen;
	s32 iRet;
	u8 buf[20];
	u8 mac[8+1];

	iLen = EchoGetField(buf, 64);
	if(0 == iLen)
	{
		return SDK_OK;
	}
	else
	{
		iRet = EchoGetMsgMac(pheSrc,iSrcLen - 8,mac,11);
		if(iRet < SDK_OK)
		{
			return SDK_ERR;
		}
		if(0 != memcmp(buf,mac,8))
		{
			EchoSetFieldLen(ECHO_MAC_ERR,64);
		}
	}
	return SDK_OK;
#endif
}

