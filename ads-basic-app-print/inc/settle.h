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
#ifndef _SETTLE_H_
#define _SETTLE_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define  BATCHUP_RMB                1   
#define  BATCHUP_FRN                2
#define  BATCHUP_ALL                3
#define  BATCHUP_ICLOG              4


#define FILENAME_SETTLE     "SettleInfo"
#define FILENAME_BATCHUP    "BatchUpInfo"

#define BATCHUP_ONCE_NUM   8

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef struct
{
    u8 ucBatchUpType;                    //����������
    u32 uiBatchUpNum;                     //����������
    u8 ucBatchUpStep;                     //�����Ͳ���
    u8 ucReSendNum;
}ST_BATCHUP_INFO;

typedef struct
{
    u32 uiTotalSaleNum;                     //���ѽ����ܱ���(�������ѳ���)
    u8 bcTotalSaleAmount[6];                //���ѽ����ܽ��(�������ѳ���)

    u32 uiTotalVoidNum;                  //���ѳ��������ܱ���
    u8 bcTotalVoidAmount[6];               //���ѳ���

    u32 uiTotalRefundNum;                 //�˻������ܱ���
    u8 bcTotalRefundAmount[6];              //�˻������ܶ�
}ST_TOTAL_TRADE;

typedef struct 
{
    u32 uiTotalDebitNum;          //�ܵĽ�Ʊ���
    u8 bcTotalDebitAmount[6];       //�ܵĽ�ƽ��
    u32 uiTotalCreditNum;         //�ܵĴ��Ʊ���
    u8 bcTotalCreditAmount[6];      //�ܵĴ��ƽ��
}ST_TOTAL_ALL;


typedef struct
{
    u8 ucSettleCode;
    ST_TOTAL_ALL    stTotalAll;
    ST_TOTAL_TRADE  stTotalTrans;
}ST_TOTAL_INFO;

typedef struct
{
    u8 asMerchID[15 + 1];        
    u8 asTermID[8 + 1];          
    u8 asBatchNO[6 + 1];         
    u8 asDateTime[10 + 1];       
    u8 ucCashierNO;            
    ST_TOTAL_INFO stTotal;       
    ST_TOTAL_INFO stTotalRMB;   
    u8 ucPrintState;
}ST_SETTLE;

typedef enum
{
    SETTLE_SEND,
    SETTLE_NONE,
    SETTLE_PRINTED,
    SETTLE_CLEARED, 
}E_SETTLE_STATE;


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
/*-----------------------------------------------------------------------------*/

// batch upload
extern void BatchUpSaveInfo(ST_BATCHUP_INFO *pstBatchInfo);
extern void BatchUpDeleteInfo(void);
extern s32 BatchUpReadInfo(ST_BATCHUP_INFO *pstBatchInfo);
extern s32 BatchUpContinue(void);
extern s32 BatchUpTrans(void);
extern s32 BatchUpTransAdvice(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend);
extern s32 BatchUpTransAllIcc(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend);
extern s32 BatchUpTransAllIccArpcErr(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend);
extern s32 BatchUpTransAllIccFail(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend);
extern s32 BatchUpTransAllMag(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend);
extern s32 BatchUpTransIccOffline(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend);
extern s32 BatchUpTransOffline(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend);

// get total amount
extern s32 SettleGetTotalAmount(ST_SETTLE *pstSettle);
extern s32 SettleGetTotalAmountTrans(ST_TRANSLOG *pstTranslog, ST_TOTAL_INFO *pstTotalInfo);

// pack message of transactions
extern s32 SettleGetTransMsg(ST_PACKET_INFO *pstPacketInfo);
extern s32 SettlePackAdviceTransMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackAllArpcErrIccTransMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackAllFailIccTransMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackAllIccTransMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackAllMagTransMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackIccOfflineTransMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackOfflineTransMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettlePackTrailerMsg(SDK_8583_ST8583 *pstIsoMsg);

// settlement
extern s32 SettleReadInfo(ST_SETTLE *pstSettle);
extern void SettleSaveInfo(ST_SETTLE *pstSettle);
extern bool SettleCheckInfo(void);
extern void SettleDeleteInfo(void);
extern void SettleSetField048(SDK_8583_ST8583 *pstIsoMsg);
extern s32 SettleTrans(void);
extern void OnSettle(void);
extern s32 SettleEndProcess(bool bRePrint);
extern s32 SettleReprint(void);

/*-----------------------------------------------------------------------------*/
#endif

