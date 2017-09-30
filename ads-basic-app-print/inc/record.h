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
#ifndef _RECORD_H_
#define _RECORD_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define TABNAME_TRANSLOG     "TransLog"

#define FILENAME_RECORDBACKUP   "recordbackup"

#define SDK_RECORD_ERR_BASE         (-1000)

#define SDK_RECORD_INTERNAL_ERR     (SDK_RECORD_ERR_BASE - 1)
#define SDK_RECORD_CREATE_ERR       (SDK_RECORD_ERR_BASE - 2)
#define SDK_RECORD_READ_ERR         (SDK_RECORD_ERR_BASE - 3)
#define SDK_RECORD_WRITE_ERR        (SDK_RECORD_ERR_BASE - 4)
#define SDK_RECORD_ID_ERR           (SDK_RECORD_ERR_BASE - 5)

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef enum
{
    LOG_ID,
    LOG_ORIGINALID,
    LOG_TRANSID,
    LOG_RFU,

    LOG_CARD_CARDMODE,
    LOG_CARD_CLTYPE,
    LOG_CARD_ICCMAGCARD,
    LOG_CARD_UIDLEN,
    LOG_CARD_UID,
    LOG_CARD_CARDLEN,
    LOG_CARD_CARDNO,
    LOG_CARD_CARDHOLDER,

    LOG_ICC_AC,
    LOG_ICC_CID,
    LOG_ICC_IADLEN,
    LOG_ICC_IAD,
    LOG_ICC_UN,
    LOG_ICC_ATC,
    LOG_ICC_TVR,
    LOG_ICC_TRANSDATE,
    LOG_ICC_TRANSTYPE,
    LOG_ICC_TRANSAMOUNT,
    LOG_ICC_CURRENCYCODE,
    LOG_ICC_COUNTRYCODE,
    LOG_ICC_AIP,
    LOG_ICC_TERMCAP,
    LOG_ICC_CVMR,
    LOG_ICC_AMOUNTOTHER,
    LOG_ICC_AIDLEN,
    LOG_ICC_AID,
    LOG_ICC_APPVERNUM,
    LOG_ICC_TERMAPPVERNUM,
    LOG_ICC_TERMTYPE,
    LOG_ICC_IFDSN,
    LOG_ICC_CATEGORYCODE,
    LOG_ICC_TRANSSEQCNT,
    LOG_ICC_FFILEN,
    LOG_ICC_FFI,
    LOG_ICC_IDN,
    LOG_ICC_AOSA,
    LOG_ICC_TSI,
    LOG_ICC_PANSN,
    LOG_ICC_APPLABEL,
    LOG_ICC_APPPREFERNAME,
    LOG_ICC_ISSAUTHDATALEN,
    LOG_ICC_ISSAUTHDATA,
    LOG_ICC_SCRIPTRESULTLEN,
    LOG_ICC_SCRIPTRESULT,
    LOG_ICC_RFULEN,
    LOG_ICC_RFU,

    LOG_MSG_CASHIERNO,
    LOG_MSG_BITMAP,
    LOG_MSG_PROCCODE,
    LOG_MSG_AMOUNT,
    LOG_MSG_DATETIME,
    LOG_MSG_TRACENO,
    LOG_MSG_ENTRYMODE,
    LOG_MSG_CONDITIONCODE,
    LOG_MSG_PINCAPCODE,
    LOG_MSG_TERMID,
    LOG_MSG_MERCHID,
    LOG_MSG_TIPAMOUNT,
    LOG_MSG_CURRENCYCODE,
    LOG_MSG_ORIGBATCHNO,
    LOG_MSG_ORIGTRACENO,
    LOG_MSG_ORIGDATE,
    LOG_MSG_TRANSTIME,
    LOG_MSG_TRANSDATE,
    LOG_MSG_SETTLEMENTDATE,
    LOG_MSG_AIID,
    LOG_MSG_REFNO,
    LOG_MSG_AUTHCODE,
    LOG_MSG_RESPCODE,
    LOG_MSG_ISSUERCODE,
    LOG_MSG_ACQUIRERCODE,
    LOG_MSG_BALANCE,
    LOG_MSG_FUNCCODE,
    LOG_MSG_BATCHNO,
    LOG_MSG_INTERORGCODE,
    LOG_MSG_ISSUERINFO,
    LOG_MSG_CUPINFO,
    LOG_MSG_ACQINFO,
    LOG_MSG_TERMRESERVED,

    LOG_STAT_ICCTRANS,
    LOG_STAT_ICCFAILTRANS,
    LOG_STAT_OFFLINE,
    LOG_STAT_VOIDED,
    LOG_STAT_ADJUSTED,
    LOG_STAT_REFUNDED,
    LOG_STAT_NEEDREPRINT,
    LOG_STAT_NEEDREVERSAL,
    LOG_STAT_NEEDSCRIPT,
    LOG_STAT_REVERSALREASON,
    LOG_STAT_UPLOADSTATUS,   

	LOG_PRINT_SENDINFO,  //added by jeff 20170925 for printing iso8583
	LOG_PRINT_RECVINFO,
	LOG_PRINT_SENDLEN,
	LOG_PRINT_RECVlEN,
	
}E_TRANSLOG_ID;

typedef struct
{
    s32 iId;
    E_FILTER_MODE eMode;
    void *pasValue[DB_MAXFILTER_VALUE];
    s32 iNum;
    bool bIsDesc;
}ST_RECORD_FILTER;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern s32 RecordAppend(ST_TRANSLOG *pstTransLog);
extern s32 RecordCheckBackup(void);
extern s32 RecordDeleteAll(void);
extern s32 RecordDeleteBackup(void);
extern s32 RecordDeleteLast();
extern s32 RecordDeleteOne(ST_TRANSLOG *pstTransLog);
extern s32 RecordGetField(ST_DB_FIELD *pstField);
extern s32 RecordGetNum(void);
extern s32 RecordGetNumEx(ST_RECORD_FILTER *pstFilter);
extern s32 RecordGetSum(s32 iId, ST_RECORD_FILTER *pstFilter, u8 *pasValue);
extern s32 RecordInit(void);
extern s32 RecordRead(s32 iIndex, ST_TRANSLOG *pstTransLog);
extern s32 RecordReadBackup(ST_TRANSLOG *gstTransLog);
extern s32 RecordReadLast(ST_TRANSLOG *pstTransLog);
extern s32 RecordSaveBackup(ST_TRANSLOG *gstTransLog);
extern s32 RecordSearch(s32 iId, void *pasValue, ST_TRANSLOG *pstTransLog);
extern s32 RecordSearchEx(ST_RECORD_FILTER *pstFilter, s32 iOffset, ST_TRANSLOG *pstTransLog);
extern s32 RecordUpdate(ST_TRANSLOG *pstTransLog);

/*-----------------------------------------------------------------------------*/
#endif


