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
#ifndef __ECHO_H__
#define __ECHO_H__

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-------------------------------- ---------------------------------------------*/
#define ECHO_FIELD_LEN   2
#define ECHO_MAC_ERR     1
typedef struct 
{
	u8 heEchoTmk[24+1];
	u8 ucTmkLen;
	u8 heEchoTpk[24+1];
	u8 ucTpkLen;
	u8 heEchoTak[24+1];
	u8 ucTakLen;
	u8 ucIsTriDes;
	u8 asAccount[19+1];
	u8 ucCardNoLen;
	u8 asPin[12+1];
	u8 ucPinLen;
	u8 ucPinBlock[8 + 1];
	u8 asAmount[12+1];
	u8 ucIsSupportNoPin;
	u8 ucTID[8 + 1];
	u8 ucTIDLEN;
	u8 ucMID[15 + 1];
	u8 ucMIDLen;
}ST_SAVED_ECHO_MSG;

/* attributes of a echo field in the 8583 message packet */
typedef struct
{
    u8 ucFLenLen;                                    // length of field length±
    u16 sFDataLen;                                  // maximum length of field data
    u8 ucFDataT;                                    // type of field datar               
} ECHO_8583_STFIELDDEF;


//the first two bytes save the length of data,and the last 2 bytes save '\0'
typedef struct
{
	u8  asTpdu[ECHO_FIELD_LEN+10+2];     				 /*tpdu*/
	u8	asMsgCode[ECHO_FIELD_LEN+4+2];					/*msg code*/   		                                                        			 
	u8	asPan[ECHO_FIELD_LEN+19+2];						/* FLD  02 */  
	u8	asProcCode[ECHO_FIELD_LEN+6+2];					/* FLD  03 */  
	u8	asTranAmt[ECHO_FIELD_LEN+12+2];					/* FLD  04 */  
	u8	asField5[ECHO_FIELD_LEN+20+2];				 	/* FLD  05 */  
	u8	asField6[ECHO_FIELD_LEN+12+2];					/* FLD  06 */  
	u8	asField7[ECHO_FIELD_LEN+12+2];			 		/* FLD  07 */  
	u8	asField8[ECHO_FIELD_LEN+12+2];					/* FLD  08 */  
	u8	asField9[ECHO_FIELD_LEN+12+2];				 	/* FLD  09*/  
	u8	asField10[ECHO_FIELD_LEN+12+2];					/* FLD  10 */  
	u8	asSTAN[ECHO_FIELD_LEN+6+2];						/* FLD  11 */  
	u8	asLocalTime[ECHO_FIELD_LEN+6+2];				/* FLD  12 */  
	u8	asLocalDate[ECHO_FIELD_LEN+4+2];				/* FLD  13 */  
	u8	asExpDate[ECHO_FIELD_LEN+4+2];					/* FLD  14 */ 
	u8	asField15[ECHO_FIELD_LEN+4+2];					/* FLD  15 */
	u8	asField16[ECHO_FIELD_LEN+12+2];					/* FLD  16 */
	u8	asField17[ECHO_FIELD_LEN+12+2];					/* FLD  17 */
	u8	asField18[ECHO_FIELD_LEN+12+2];					/* FLD  18 */
	u8	asField19[ECHO_FIELD_LEN+12+2];					/* FLD  19 */
	u8	asField20[ECHO_FIELD_LEN+12+2];					/* FLD  20 */
	u8	asField21[ECHO_FIELD_LEN+12+2];					/* FLD  21 */
	u8	asEntryMode[ECHO_FIELD_LEN+4+2];				/* FLD  22 */  
	u8	asPanSeqNo[ECHO_FIELD_LEN+4+2];				    /* FLD  23 */  
	u8	asNii[ECHO_FIELD_LEN+4+2];						/* FLD  24 */  
	u8	asCondCode[ECHO_FIELD_LEN+2+2];					/* FLD  25*/ 
	u8	asField26[ECHO_FIELD_LEN+2+2];					/* FLD  26*/ 
	u8	asField27[ECHO_FIELD_LEN+12+2];					/* FLD  27*/ 
	u8	asField28[ECHO_FIELD_LEN+12+2];					/* FLD  28*/ 
	u8	asField29[ECHO_FIELD_LEN+12+2];					/* FLD  29*/ 
	u8	asField30[ECHO_FIELD_LEN+12+2];					/* FLD  30*/ 
	u8	asField31[ECHO_FIELD_LEN+12+2];					/* FLD  31*/ 
	u8	asField32[ECHO_FIELD_LEN+12+2];					/* FLD  32*/ 
	u8	asField33[ECHO_FIELD_LEN+12+2];					/* FLD  33*/ 
	u8	asField34[ECHO_FIELD_LEN+40+2];					/* FLD  34*/ 	
	u8	asTrack2[ECHO_FIELD_LEN+37+2];					/* FLD  35 */  
	u8	asTrack3[ECHO_FIELD_LEN+104+2];					/* FLD  36 */  
	u8	asRRN[ECHO_FIELD_LEN+12+2];						/* FLD  37 */  
	u8	asAuthCode[ECHO_FIELD_LEN+6+2];				    /* FLD  38 */  
	u8	asRspCode[ECHO_FIELD_LEN+2+2];					/* FLD  39 */ 
	u8	asField40[ECHO_FIELD_LEN+40+2];					/* FLD  40 */ 
	u8	asTermID[ECHO_FIELD_LEN+8+2];					/* FLD  41 */  
	u8	asMerchantID[ECHO_FIELD_LEN+15+2];				/* FLD  42 */  
	u8	asField43[ECHO_FIELD_LEN+12+2];					/* FLD  43 */  
	u8	asAddlRsp[ECHO_FIELD_LEN+25+2];					/* FLD  44 */  
	u8	asTrack1[ECHO_FIELD_LEN+76+2];					/* FLD  45 */  
	u8	asField46[ECHO_FIELD_LEN+12+2];					/* FLD  46 */  
	u8	asField47[ECHO_FIELD_LEN+12+2];					/* FLD  47 */  
	u8	asField48[ECHO_FIELD_LEN+322+2];			    /* FLD  48 */  
	u8	asTranCurcyCode[ECHO_FIELD_LEN+4+2];		  	/* FLD  49 */  
	u8	asHolderCurcyCode[ECHO_FIELD_LEN+12+2];			/* FLD  50 */  
	u8	asField51[ECHO_FIELD_LEN+12+2];				 	/* FLD  51 */  
	u8	hePINData[ECHO_FIELD_LEN+8+2];					/* FLD  52 */
	u8  asField53[ECHO_FIELD_LEN+16 + 2];				/* FLD  53 */
	u8	asExtAmount[ECHO_FIELD_LEN+40+2];				/* FLD  54 */  
	u8	heICCData[ECHO_FIELD_LEN+255+2];			    /* FLD  55 */  
	u8	heICCData2[ECHO_FIELD_LEN+12+2];				/* FLD  56 */
	u8  asField57[ECHO_FIELD_LEN+12 + 2]; 				/* FLD  57 */
	u8  asField58[ECHO_FIELD_LEN+100 + 2];				/* FLD  58 */
	u8  asField59[ECHO_FIELD_LEN+12 + 2]; 				/* FLD  59 */
	u8	asField60[ECHO_FIELD_LEN+17+2]; 				/* FLD  60 */                   
	u8	asField61[ECHO_FIELD_LEN+29+2]; 				/* FLD  61 */  
	u8	asField62[ECHO_FIELD_LEN+512+2]; 				/* FLD  62 */  
	u8	asField63[ECHO_FIELD_LEN+163+2]; 				/* FLD  63 */  
	u8	asMac[ECHO_FIELD_LEN+8+2]; 						/* FLD  64 */  
	
}ST_ECHO_ISO8583;


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/


extern s32 EchoModeExchangeIsoPacket(const u8 *pheSrc,s32 iSrcLen, SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoInitMsg(ST_SAVED_ECHO_MSG *pstEchoMsg);
extern s32 SaveEchoMsg(ST_SAVED_ECHO_MSG *pstEchoMsg);
extern s32 ReadEchoMsg(ST_SAVED_ECHO_MSG *pstEchoMsg);
extern bool EchoIsRightPin(void);
extern s32 EchoUnpackIso8583(const u8 *pheSrc,s32 iSrcLen);
extern void EchoSetFieldLen(s32 iFieldLen,s32 iFieldNo);
extern s32 EchoGetFieldLen(s32 iFieldNo);
extern	bool EchoFieldIsExist(s32 iFieldNo);
extern	void EchoSetField(ECHO_8583_STFIELDDEF *pstFieldDef,u8 *pheTrueFieldData,s32 iFieldLen,s32 iFieldNo);
extern	s32 EchoGetField(u8 *pheFieldData,s32 iFieldNo);
extern s32 EchoIsoPackPublicMsg(E_TRANS_ID eTranId,SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField60(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField62(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgRecv,u8 *pucField39);
extern s32 EchoHandleTIDMID(SDK_8583_ST8583 *pstIsoMsgRecv);

extern s32 EchoHandleField25(SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField38(SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField44(SDK_8583_ST8583 *pstIsoMsgRecv);

extern s32 EchoHandleField32(SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField37(SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField39(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgRecv,u8 *pucFiled39);
extern s32 EchoHandleField49(SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField61(SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField63(SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 EchoHandleField54(SDK_8583_ST8583 *pstIsoMsgRecv,u8 *pucFiled39);
extern s32 EchoCalcPinBlock(u8 *pucPinBlock);
extern s32 EchoHandleResponseMac(const u8 *pheSrc,s32 iSrcLen);
extern bool EchoIsRightCardNo(void);
/*-----------------------------------------------------------------------------*/
#endif



