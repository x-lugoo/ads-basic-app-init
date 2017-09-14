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

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern void DbgTraceAsc(const u8 *pheData, u32 uiDataLen);
extern void DbgTraceIso8583(u8 *pasTitle, SDK_8583_ST8583 *pstBag8583);
extern void *DbgPrintIso8583(u8 *pasTitle,void *arg);
extern bool DbgPrintHex8583(u8 *pasTitle,const u8 *pheData, s32 uiDataLen);
extern s32 DbgReadDbgTranTotalNum(s32 *uiSavedDebugNum);
extern s32 DbgSaveDbgTranTotalNum(s32 uiSaveDebugNum);
extern s32 DbgReadTran8583(ST_SAVED_DEBUG8583 *pstSavedDebug8583,s32 uiOffset);
extern s32 DbgSaveTran8583(s32 uiTranNO,SDK_8583_ST8583 *pstSentBag8583,SDK_8583_ST8583 *pstRecv8583,s32 uiOffset);
/*-----------------------------------------------------------------------------*/
#endif



