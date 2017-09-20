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
#ifndef __APPDBG_H__
#define __APPDBG_H__

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/

typedef struct
{
	s32 sTranNo;
	SDK_8583_ST8583 stSendBag8583;
	SDK_8583_ST8583 stRecvBag8583;
}ST_SAVED_DEBUG8583;

typedef struct 
{
	u8 heEchoTmk[8+1];
	u8 heEchoTpk[8+1];
	u8 heEchoTak[8+1];
	u8 asAccount[19+1];
	u8 ucCardNoLen;
	u8 asPin[12+1];
	u8 ucPinLen;
	u8 asAmount[12+1];
}ST_SAVE_ECHO_MSG;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern void DbgTraceAsc(const u8 *pheData, u32 uiDataLen);
extern void DbgTraceIso8583(u8 *pasTitle, SDK_8583_ST8583 *pstBag8583);
extern void *DbgPrintIso8583(u8 *pasTitle,void *arg);
extern bool DbgPrintHex8583(u8 *pasTitle,const u8 *pheData, s32 uiDataLen);
extern s32 DbgReadDbgTranTotalNum(s32 *siSavedDebugNum);
extern s32 DbgSaveDbgTranTotalNum(s32 siSaveDebugNum);
extern s32 DbgReadTran8583(ST_SAVED_DEBUG8583 *pstSavedDebug8583,s32 siOffset);
extern s32 DbgSaveTran8583(s32 siTranNO,SDK_8583_ST8583 *pstSentBag8583,SDK_8583_ST8583 *pstRecv8583,s32 siOffset);
extern s32 DbgEchoModeExchangeIsoPacket(SDK_8583_ST8583 *pstIsoMsgSend, SDK_8583_ST8583 *pstIsoMsgRecv);
extern s32 DbgEchoInitMsg(ST_SAVE_ECHO_MSG *pstEchoMsg);
extern s32 DbgSaveEchoMsg(ST_SAVE_ECHO_MSG *pstEchoMsg);
extern s32 DbgReadEchoMsg(ST_SAVE_ECHO_MSG *pstEchoMsg);
extern s32 DbgEchoHandleField39AndField54(E_TRANS_ID eTranId, SDK_8583_ST8583 *pstIsoMsgSend,u8 *pucFiled39,u8 *pszField54);
extern bool DbgEchoIsRightPin(SDK_8583_ST8583 *pstIsoMsgSend,ST_SAVE_ECHO_MSG *pstEchoMsg);
/*-----------------------------------------------------------------------------*/
#endif



