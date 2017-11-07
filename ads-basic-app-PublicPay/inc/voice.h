/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.
                
                       http://www.xinguodu.com/en/

 ******************************************************************************
  File Name      :   
  Version         :  
  Author          :  Jeff
  Date            :  2017-10-31
  Description   : 


  
******************************************************************************/
#ifndef __VOICE_H__
#define __VOICE_H__

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#include "global.h"

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-------------------------------- ---------------------------------------------*/

typedef struct 
{
	u8 asPayMethodNum[20 + 1];
	u8 asInvoiceNum[20 + 1];
	
}ST_VOICE_MSG;

typedef struct 
{
	u8 heVoiceTMK[24+1];
	u8 ucTmkLen;
	u8 heVoiceTPK[24+1];
	u8 ucTpkLen;
	u8 heVoiceTAK[24+1];
	u8 ucTakLen;
	u8 ucIsTriDes;

}ST_SAVED_VOICE_SECURE_MSG;

typedef enum 
{
	VOICE_INPUT_INVOICE_NO,
	VOICE_INPUT_PAYMENT_NO,
	
}E_VOICE_INPUT_TYPE;

extern s32 VoiceReAddFuncPackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 VoiceAddFuncPackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 VoiceCancelOneFuncPackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 VoiceCancelAllFuncPackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern void VoiceReAddTrans(u16 usCardType);
extern void VoiceReAddFunc(void);
extern void VoiceAddFunc(void);
extern void VoiceCancelAllFunc(void);
extern void VoiceCancelOneFunc(void);
extern s32 ReadVoiceSecureMsg(ST_SAVED_VOICE_SECURE_MSG *pstVoiceSecureMsg);
extern s32 SaveVoiceSecureMsg(ST_SAVED_VOICE_SECURE_MSG *pstVoiceSecureMsg);


#endif













