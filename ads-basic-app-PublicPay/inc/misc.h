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
#ifndef _MISC_H_
#define _MISC_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
typedef enum      
{
    LEFT_ALIGN,
    RIGHT_ALIGN,
}E_ALIGN_MODE;

typedef enum      
{
    SALE_AMOUNT = 0,
    CASHBACK_AMOUNT,
}E_AMOUNT_MODE;

#define COLOR_GREP  (((211<<9)&0xF800) | ((211<<4)&0x7E0) | ((211>>2)&0x1F))

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef struct        
{
    E_TRANS_ID eTransID;     
    u8 asName[32];    
}ST_TRADENAME;

typedef struct
{
    u8 heTag[3];
    u8 ucDatalen;
    u8 *pAddress;
    u8 *pLength;
}ST_TRANSLOG_TLV;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern s32 CbTrnDispAmount(u8 *pStrDisp, const u32 uiMode, const s32 siDispRow, void *pVar);
extern bool TrnCheckAdminPwd(void);
extern bool TrnCheckCondition(bool bIsSaveRecord, bool bIsSupport);
extern bool TrnCheckDate(u8 *pasDate);
extern bool TrnCheckPrintDetail(ST_TRANSLOG *pstTransLog);
extern bool TrnCheckYearMonth(u8 *pasYearMonth);
extern void TrnDispLed(u8 ucLedStatus);
extern void TrnInitGlobal(void);
extern void TrnEndProcess(void);
extern void TrnFormatAmount(u8 *pasStr, u8 const *pasAmount, bool bIsCurrency);
extern s32 TrnFormBlankAlignChar(E_ALIGN_MODE eAlign, u8 *pasDest, const u8 *pasSrc, u32 uiMaxLen);
extern bool TrnGetAlphanumeric(s32 iKeyVal, u8 *pucChar);
extern s32 TrnGetAmount(s32 iTimeOut, u8 *pasAmount, s32 iLine, bool bIsAllowZero);
extern s32 TrnGetStatus(void);
extern bool TrnCheckResponseCode(const u8 *asResp);
extern void TrnGetIccDataFromMsg(SDK_8583_ST8583 *pstPacket8583);
extern s32 TrnGetIccMagData(SDK_ICC_CARDDATA *pstCardData);
extern s32 TrnGetMagCardNo(SDK_ICC_CARDDATA const *pstCardData, u8 *pasCardNo);
extern void TrnGetName(u8 *pasName, E_TRANS_ID eTransID);
extern s32 TrnGetNumber(s32 iTimeOut, u8 *pasNumber, s32 iMin, s32 iMax, s32 iLine);
extern void TrnIncBatchNo(s32 iNum);
extern void TrnIncTraceNo(s32 iNum);
extern s32 TrnInputAmount(E_AMOUNT_MODE eAmountMode, u8 *pasAmount);
extern bool TrnInputDate(u8 *pasDate);
extern bool TrnInputExpiredDate(u8 *pasDate);
extern s32 TrnInputIpAddr(s32 iTimeOut, u8 *pasIpAddr, s32 iLine);
extern s32 TrnInputLine(s32 iTimeOut, u8 *pasStr, s32 iMinLen, s32 iMaxLen, s32 iMode, s32 iLine);
extern s32 TrnInputPin(bool bIsWithPan, const u8 *pasTransAmount, SDK_ICC_CARDDATA const *pstCardData, u8 *phePwd, s32 iDispLine);
extern bool TrnInputReferenceNo(u8 *pasRefNo);
extern bool TrnInputPaymentMethodNo(u8 *pasPayMethodNo);
extern bool TrnInputTraceNo(u8 *pasTracerNo);
extern bool TrnInputAddCashier(u32 *puiOperator);
extern bool TrnInputDeleteCashier(u32 *puiOperator);
extern bool TrnCheckRefundAmount(u8 *pasAmount);
extern s32 TrnConfirmRefundAmount(u8 *pasAmount);
extern bool TrnJudgeCreditTrans(E_TRANS_ID eTransID);
extern void TrnLightCtrl();
extern void TrnLightRelease();
extern bool TrnMaskCardNo(E_TRANS_ID eTransID, u8 *pasCardNo);
extern void TrnPadding(u8 *pasDest, u8 *pasSrc, u8 ucChar, s32 iLen, E_ALIGN_MODE eAlign);
extern bool TrnPasswordUpdate(u8 *pasTitle, u8 *pasPassword, u32 uiLen);
extern bool TrnPasswordSet(u8 *pasTitle, u8 *pasPassword, u32 uiLen);
extern void TrnPedCloseVoice(void);
extern s32 TrnProcInsert(s32 iCardMode, 
                            SDK_ICC_TRADE_PARAM *pstIccTradeParam, 
                            ST_CARDINFO *pstCardInfo);
extern s32 TrnProcManual(s32 iCardMode, 
                             s32 iKey,
                            SDK_ICC_TRADE_PARAM *pstIccTradeParam, 
                            ST_CARDINFO *pstCardInfo);
extern s32 TrnProcSwipe(s32 iCardMode, 
                            SDK_ICC_TRADE_PARAM *pstIccTradeParam, 
                            ST_CARDINFO *pstCardInfo);
extern s32 TrnProcTap(s32 iCardMode, 
                          SDK_ICC_TRADE_PARAM *pstIccTradeParam, 
                          ST_CARDINFO *pstCardInfo,
                          u32 uiTimer);
extern s32 TrnReadCard(s32 iCardMode, 
                           SDK_ICC_TRADE_PARAM *pstIccTradeParam, 
                           ST_CARDINFO *pstCardInfo);
extern void TrnSetStatus(s32 iStatus);
extern void TrnSwitchApp(void);
extern void TrnSyncDateTime(ST_TRANSDATA *pstTransData);
extern s32 TrnUpdateTransDataRecv(SDK_8583_ST8583 *pstRecvPacket);
extern s32 TrnUpdateTransDataSend(SDK_8583_ST8583 *pstSendPacket);
extern bool TrnCheckTime(u8 *pbcTime, u8 ucLen);
extern s32 TrnCheckTotalAmount(E_TRANS_ID eTransID, u8 *asAmount);
extern s32 TrnCheckCashBackAmount(u8 *asAmount, u8 *asCashBack);


/*-----------------------------------------------------------------------------*/
#endif

