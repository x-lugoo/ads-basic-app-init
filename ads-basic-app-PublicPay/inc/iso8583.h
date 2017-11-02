/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.
                
                       http://www.nexgo.cn/en/

 ******************************************************************************
  File Name     :   
  Version       :  
  Author        :  wenmin
  Date          :  2016-10-19
  Description   : 


  
******************************************************************************/
#ifndef _ISO8583_H_
#define _ISO8583_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/

// DOL structure for field 55
typedef struct 
{
    u8 heTag[3];
    u8 ucDatalen;
    bool bIsMandatory;
    u8 *pAddress;
}ST_ICCDATA_DOL;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern bool IsoCheckBimap(const u8 *pheBitmap, u8 ucFieldNo);
extern void IsoFormIccDataField055(u8 *pheDolData, s32 *piLen);
extern s32 IsoGetField(SDK_8583_ST8583 *pstPacket8583, u8 ucFieldNo, u8 *pheFieldData, u16 usMaxSize);
extern s32 IsoGetMsgMac(SDK_8583_ST8583 *pstIsoMsg, u8 *pucMac);
extern s32 IsoPackMsgHeader(SDK_8583_ST8583 *pstIsoMsg);
extern s32 IsoPackMsgMac(SDK_8583_ST8583 *pstIsoMsg);
extern s32 IsoPackPublicMsg(SDK_8583_ST8583 *pstIsoMsg, ST_TRANSDATA *pstTransData, u8 *pasBitMap);
extern s32 IsoParse8583(SDK_8583_ST8583 *pstIsoMsg);
extern s32 IsoSetField(SDK_8583_ST8583 *pstPacket8583, u8 ucFieldNo, u8 *pheFieldData, u16 usDataLen);
extern s32 VoiceIsoGetMsgMac(SDK_8583_ST8583 *pstIsoMsg, u8 *pucMac);

/*-----------------------------------------------------------------------------*/
#endif

