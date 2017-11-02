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
#ifndef _EMV_H_
#define _EMV_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define FILE_EMV_BEEP_OK    "/mtd0/res/emvbeepok.wav"     //success tone  
#define FILE_EMV_BEEP_ERR   "/mtd0/res/emvbeeperr.wav"    //alert tone  
#define PAYPASSPAYWAVE_CFG_INI  "/mtd0/res/paypasspaywave.ini"

/* card type in current contactless transaction */
typedef enum
{
    CTLS_UNKNOWN = 0X00,        //unknown ctls card type
    CTLS_QPBOC   = 0x01,        //qPBOC
    CTLS_PAYWAVE = 0x02,        //paywave
    CTLS_PAYPASS = 0x04,        //paypass
}E_CTLS_CARD_TYPE;

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef struct
{
    u8 heTag[3];
    u8 ucDatalen;
    u8 heValue[256];
}ST_EMV_TLV;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
// callback functions
extern s32 CbEmvInputAmount(u8 *pasAmount);
extern s32 CbVoiceEmvInputAmount(u8 *pasAmount);
extern s32 CbEmvDispCardNo(u8 const *pasCardNo);
extern s32 CbEmvDispPrompts(SDK_ICC_PROMPT_TYPE ePromptType);
extern s32 CbEmvDispCandAppList(u8 ucAppNum, u8 **ppheAppList);
extern void CbEmvReinitParam(void);
extern s32 CbEmvInputPin(const u8 *pasAmount, u8 ucRemainPinTries, u8 ePinMode, u8 *phePin);
extern s32 CbEmvCltsRemoveCard(void); 

extern u8 DispInputPin(u8 *pucDispLine, E_PED_DISPAMOUNT eDispAmountMode, u8 const *pasAmount, SDK_PED_PIN_MODE ePinMode, u8 ucRemainPinTries);
extern s32 EmvInputPin(u8 *phePin, bool bIsWithPan, const u8 *pasAmount, SDK_PED_PIN_MODE ePinMode, u8 ucDispLine);
extern s32 EmvOptImportRespData(SDK_8583_ST8583 *pst8583Packet);
extern void EmvConfigTransParam(ST_TRANSDATA *pstTransData, SDK_ICC_TRADE_PARAM *pstIccTradeParam);
extern void EmvInitPayPassWave(SDK_ICC_TRADE_PARAM *pstTradeParam);
extern s32 EmvReadPaypassPaywaveCfgIni(void);
extern s32 EmvMandatoryTransFlowDetail(SDK_ICC_TRADE_PARAM * pstIccTradeParam, SDK_ICC_PARAM * pstIccParam);
extern E_ICCRET EmvMandatoryTransFlow(SDK_ICC_TRADE_PARAM *pstIccTradeParam, SDK_ICC_PARAM *pstIccParam);
extern E_ICCRET  EmvMandatoryTransFlowStart(SDK_ICC_TRADE_PARAM  *pstIccTradeParam, ST_CARDINFO *pstCardInfo);
extern E_ICCRET EmvOptTransFlowOnlineProcess(SDK_ICC_TRADE_PARAM *pstIccTradeParam, SDK_ICC_PARAM *pstIccParam);
extern s32 EmvParseIccTlv(const u8 *pData, s32 iDatalen, const u8 *pheTag, u8 *pheOutData, s32 *piOutLen);
extern E_ICCRET EmvGetReadCardResult(SDK_EMV_RLT eEmvRet);
extern void EmvInitCtlsParam(void);
extern s32 EmvReadCtlsParam(void);
extern void EmvLedIdle(void);      
extern void EmvLedReadCard(void);
extern void EmvLedReadCardOk(void);    
extern void EmvLedTransFail(void);
extern void EmvLedClose(void);

/*-----------------------------------------------------------------------------*/
#endif


