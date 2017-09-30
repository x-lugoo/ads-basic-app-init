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
#include "global.h"

static ST_TRANSLOG _gstTransLog;

/*----------------------------------------------------------------------------*/
// transaction record(LOG)
static ST_DATABASE TabTransLog = 
{
    TABNAME_TRANSLOG,
    FALSE,
    {
        {LOG_ID, "ID",                 DB_PRIMARY_KEY,  0, FALSE, &_gstTransLog.iID,                                0},
        {STR(LOG_ORIGINALID),          DB_DATATYPE_U32, 0, FALSE, &_gstTransLog.iOriginalID,                        0},
        {STR(LOG_TRANSID),             DB_DATATYPE_U32, 0, FALSE, &_gstTransLog.eTransID,                           0},
        {STR(LOG_RFU),                 DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.heRFU,                               sizeof(_gstTransLog.heRFU)},
        //card data
        {STR(LOG_CARD_CARDMODE),       DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stCardInfo.stCardParam.ucCardMode,  0},     
        {STR(LOG_CARD_CLTYPE),         DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stCardInfo.stCardParam.ucCLType,    0},     
        {STR(LOG_CARD_ICCMAGCARD),     DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stCardInfo.stCardData.bIsIccMagCard,0},     
        {STR(LOG_CARD_UIDLEN),         DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stCardInfo.stCardData.ucUIDLen,     0},     
        {STR(LOG_CARD_UID),            DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stCardInfo.stCardData.ucUID,         0},     
        {STR(LOG_CARD_CARDLEN),        DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stCardInfo.stCardData.ucCardLen,    0},     
        {STR(LOG_CARD_CARDNO),         DB_DATATYPE_ASC, 0, TRUE, _gstTransLog.stCardInfo.stCardData.asCardNO,       0},
        {STR(LOG_CARD_CARDHOLDER),     DB_DATATYPE_ASC, 0, TRUE, _gstTransLog.stCardInfo.asCardHolder,              0},
        //icc data
        {STR(LOG_ICC_AC),              DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heAC,                      sizeof(_gstTransLog.stEmvInfo.heAC)},
        {STR(LOG_ICC_CID),             DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucCID,                    0}, 
        {STR(LOG_ICC_IADLEN),          DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucIADLen,                 0},
        {STR(LOG_ICC_IAD),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heIAD,                     sizeof(_gstTransLog.stEmvInfo.heIAD)},
        {STR(LOG_ICC_UN),              DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heUN,                      sizeof(_gstTransLog.stEmvInfo.heUN)},
        {STR(LOG_ICC_ATC),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heATC,                     sizeof(_gstTransLog.stEmvInfo.heATC)},
        {STR(LOG_ICC_TVR),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heTVR,                     sizeof(_gstTransLog.stEmvInfo.heTVR)},
        {STR(LOG_ICC_TRANSDATE),       DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heTransDate,               sizeof(_gstTransLog.stEmvInfo.heTransDate)},
        {STR(LOG_ICC_TRANSTYPE),       DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucTransType,              0}, 
        {STR(LOG_ICC_TRANSAMOUNT),     DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.bcTransAmount,             sizeof(_gstTransLog.stEmvInfo.bcTransAmount)},
        {STR(LOG_ICC_CURRENCYCODE),    DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.bcCurrencyCode,            sizeof(_gstTransLog.stEmvInfo.bcCurrencyCode)},
        {STR(LOG_ICC_COUNTRYCODE),     DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.bcCountryCode,             sizeof(_gstTransLog.stEmvInfo.bcCountryCode)},
        {STR(LOG_ICC_AIP),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heAIP,                     sizeof(_gstTransLog.stEmvInfo.heAIP)},
        {STR(LOG_ICC_TERMCAP),         DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heTermCap,                 sizeof(_gstTransLog.stEmvInfo.heTermCap)},
        {STR(LOG_ICC_CVMR),            DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heCVMR,                    sizeof(_gstTransLog.stEmvInfo.heCVMR)},
        {STR(LOG_ICC_AMOUNTOTHER),     DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.bcAmountOther,             sizeof(_gstTransLog.stEmvInfo.bcAmountOther)},
        {STR(LOG_ICC_AIDLEN),          DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucAIDLen,                 0},
        {STR(LOG_ICC_AID),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heAID,                     sizeof(_gstTransLog.stEmvInfo.heAID)},
        {STR(LOG_ICC_APPVERNUM),       DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heAppVerNum,               sizeof(_gstTransLog.stEmvInfo.heAppVerNum)},
        {STR(LOG_ICC_TERMAPPVERNUM),   DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heTermAppVerNum,           sizeof(_gstTransLog.stEmvInfo.heTermAppVerNum)},
        {STR(LOG_ICC_TERMTYPE),        DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucTermType,               0}, 
        {STR(LOG_ICC_IFDSN),           DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.asIFDSN,                  0}, 
        {STR(LOG_ICC_CATEGORYCODE),    DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucCategoryCode,           0}, 
        {STR(LOG_ICC_TRANSSEQCNT),     DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heTransSeqCnt,             sizeof(_gstTransLog.stEmvInfo.heTransSeqCnt)},
        {STR(LOG_ICC_FFILEN),          DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucFFILen,                 0},
        {STR(LOG_ICC_FFI),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heFFI,                     sizeof(_gstTransLog.stEmvInfo.heFFI)},
        {STR(LOG_ICC_IDN),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heIDN,                     sizeof(_gstTransLog.stEmvInfo.heIDN)},
        {STR(LOG_ICC_AOSA),            DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.bcAOSA,                    sizeof(_gstTransLog.stEmvInfo.bcAOSA)},
        {STR(LOG_ICC_TSI),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heTSI,                     sizeof(_gstTransLog.stEmvInfo.heTSI)},                          
        {STR(LOG_ICC_PANSN),           DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucPANSN,                  0}, 
        {STR(LOG_ICC_APPLABEL),        DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stEmvInfo.asAppLabel,                0},
        {STR(LOG_ICC_APPPREFERNAME),   DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stEmvInfo.asAppPreferName,           0},
        {STR(LOG_ICC_ISSAUTHDATALEN),  DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucIssAuthDataLen,         0},
        {STR(LOG_ICC_ISSAUTHDATA),     DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heIssAuthData,             sizeof(_gstTransLog.stEmvInfo.heIssAuthData)},                        
        {STR(LOG_ICC_SCRIPTRESULTLEN), DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucScriptResultLen,        0},
        {STR(LOG_ICC_SCRIPTRESULT),    DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heScriptResult,            sizeof(_gstTransLog.stEmvInfo.heScriptResult)},                            
        {STR(LOG_ICC_RFULEN),          DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stEmvInfo.ucRFULen,                 0},
        {STR(LOG_ICC_RFU),             DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stEmvInfo.heRFU,                     sizeof(_gstTransLog.stEmvInfo.heRFU)},
        //transation data 
        {STR(LOG_MSG_CASHIERNO),       DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stMsgInfo.ucCashierNO,              0}, 
        {STR(LOG_MSG_BITMAP),          DB_DATATYPE_BIN, 0, FALSE, _gstTransLog.stMsgInfo.heBitmap,                  sizeof(_gstTransLog.stMsgInfo.heBitmap)},
        {STR(LOG_MSG_PROCCODE),        DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asProcCode,                0},
        {STR(LOG_MSG_AMOUNT),          DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asAmount,                  0},
        {STR(LOG_MSG_DATETIME),        DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asDateTime,                0},
        {STR(LOG_MSG_TRACENO),         DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asTraceNO,                 0},
        {STR(LOG_MSG_ENTRYMODE),       DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asEntryMode,               0},
        {STR(LOG_MSG_CONDITIONCODE),   DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asConditionCode,           0}, 
        {STR(LOG_MSG_PINCAPCODE),      DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asPinCapCode,              0},
        {STR(LOG_MSG_TERMID),          DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asTermID,                  0},
        {STR(LOG_MSG_MERCHID),         DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asMerchID,                 0},
        {STR(LOG_MSG_TIPAMOUNT),       DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asTipAmount,               0},
        {STR(LOG_MSG_CURRENCYCODE),    DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asCurrencyCode,            0},
        {STR(LOG_MSG_ORIGBATCHNO),     DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asOrigBatchNO,             0},
        {STR(LOG_MSG_ORIGTRACENO),     DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asOrigTraceNO,             0},
        {STR(LOG_MSG_ORIGDATE),        DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asOrigDate,                0},
        {STR(LOG_MSG_TRANSTIME),       DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asTransTime,               0},
        {STR(LOG_MSG_TRANSDATE),       DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asTransDate,               0},
        {STR(LOG_MSG_SETTLEMENTDATE),  DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asSettlementDate,          0},
        {STR(LOG_MSG_AIID),            DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asAIID,                    0},
        {STR(LOG_MSG_REFNO),           DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asRefNO,                   0},
        {STR(LOG_MSG_AUTHCODE),        DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asAuthCode,                0},
        {STR(LOG_MSG_RESPCODE),        DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asRespCode,                0},
        {STR(LOG_MSG_ISSUERCODE),      DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asIssuerCode,              0},
        {STR(LOG_MSG_ACQUIRERCODE),    DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asAcquirerCode,            0},
        {STR(LOG_MSG_BALANCE),         DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asBalance,                 0},
        {STR(LOG_MSG_FUNCCODE),        DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asFuncCode,                0},
        {STR(LOG_MSG_BATCHNO),         DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asBatchNO,                 0},
        {STR(LOG_MSG_INTERORGCODE),    DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asInterOrgCode,            0},
        {STR(LOG_MSG_ISSUERINFO),      DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asIssuerInfo,              0},
        {STR(LOG_MSG_CUPINFO),         DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asCUPInfo,                 0},
        {STR(LOG_MSG_ACQINFO),         DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asAcqInfo,                 0},
        {STR(LOG_MSG_TERMRESERVED),    DB_DATATYPE_ASC, 0, FALSE, _gstTransLog.stMsgInfo.asTermReserved,            0},
        //transation status
        {STR(LOG_STAT_ICCTRANS),       DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsIccTrans,          0}, 
        {STR(LOG_STAT_ICCFAILTRANS),   DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsIccFailTrans,      0}, 
        {STR(LOG_STAT_OFFLINE),        DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsOffline,           0}, 
        {STR(LOG_STAT_VOIDED),         DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsVoided,            0},     
        {STR(LOG_STAT_ADJUSTED),       DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsAdjusted,          0}, 
        {STR(LOG_STAT_NEEDREPRINT),    DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsNeedRePrint,       0}, 
        {STR(LOG_STAT_NEEDREVERSAL),   DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsNeedReversal,      0}, 
        {STR(LOG_STAT_NEEDSCRIPT),     DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.bIsNeedScript,        0}, 
        {STR(LOG_STAT_REVERSALREASON), DB_DATATYPE_U8,  0, FALSE, &_gstTransLog.stTransStatus.ucReversalReason,     0}, 
        {STR(LOG_STAT_UPLOADSTATUS),   DB_DATATYPE_U32, 0, FALSE, &_gstTransLog.stTransStatus.eUploadStatus,        0},
        //iso8583 printing message ,added by jeff 20170925
        {STR(LOG_PRINT_SENDINFO),	   DB_DATATYPE_BIN,  0, FALSE, _gstTransLog.stPrintIso8583.hePrintSendBuf,      sizeof(_gstTransLog.stPrintIso8583.hePrintSendBuf)}, 
		{STR(LOG_PRINT_RECVINFO),	   DB_DATATYPE_BIN,  0, FALSE, _gstTransLog.stPrintIso8583.hePrintRecvBuf,      sizeof(_gstTransLog.stPrintIso8583.hePrintRecvBuf)},
		{STR(LOG_PRINT_SENDLEN),	   DB_DATATYPE_U32,  0, FALSE, &_gstTransLog.stPrintIso8583.iSendLen,            0},
		{STR(LOG_PRINT_RECVlEN),	   DB_DATATYPE_U32,  0, FALSE, &_gstTransLog.stPrintIso8583.iRecvLen,            0},	
        {-1, NULL},
    }
};

/*****************************************************************************
** Description :  Init transaction record(must be called once when power on)
** Parameters  :  None 
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordInit(void)
{
    if(DB_EXIT_SUCCESS != sdkDbOpen())
    {
        return SDK_ERR;
    }
    
    if(DB_EXIT_SUCCESS != sdkDbCreateTable(&TabTransLog))
    {
        Trace("record", "sdkDbCreateTable fail\r\n");
        sdkDbClose();
        return SDK_ERR;
    }
        
    return SDK_OK;
}

/*****************************************************************************
** Description :  Get transaction record total number
** Parameters  :  None 
** Return      :  (1)SDK_ERR : fail
                  (2)>= 0 : record total num
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordGetNum(void)
{
    s32 ret = 0;

    ret = sdkDbGetRecordTotalNum(TabTransLog.pasTabName, NULL, 0);
    if(ret < 0)
    {
        Trace("record", "sdkDbGetRecordTotal fail[%d]\r\n", ret);
        return SDK_ERR;
    }
    return ret;
}

/*****************************************************************************
** Description :  Get match condition record total number 
** Parameters  :  input:
                  (1)ST_RECORD_FILTER *pstFilter : record match conditions
                  
** Return      :  (1)SDK_ERR : fail
                  (2)>= 0 : record total num
** Author      :  wenmin   2016-10-18 
** Remarks     :  can create less than 5 filters, every filters can set 10 values
*****************************************************************************/
s32 RecordGetNumEx(ST_RECORD_FILTER *pstFilter)
{
    s32 ret = 0;
    ST_DB_FIELD st_field;
    ST_DB_FILTER st_filter[DB_MAXFILTER];
    s32 i, k;

    memset(&st_filter, 0, sizeof(st_filter));

    for(i = 0; i < DB_MAXFILTER; i++)
    {
        memset(&st_field, 0, sizeof(ST_DB_FIELD));
        if(-1 == pstFilter[i].iId)
        {
            break;
        }
        st_field.iId = pstFilter[i].iId;
        if(SDK_OK != RecordGetField(&st_field))
        {
            return SDK_ERR;
        }
        st_filter[i].pasName = st_field.pasFieldName;
        for(k = 0; k < DB_MAXFILTER_VALUE; k++)
        {
            st_filter[i].pasValue[k] = pstFilter[i].pasValue[k];
        }
        st_filter[i].eMode = pstFilter[i].eMode;
        st_filter[i].iNum = pstFilter[i].iNum;
        st_filter[i].iType = st_field.iType;
        st_filter[i].iLen = st_field.iLen;
    }
    
    ret = sdkDbGetRecordTotalNum(TabTransLog.pasTabName, st_filter, i);
    if(0 > ret)
    {
        Trace("record", "sdkDbGetRecordTotal fail\r\n");
        return SDK_ERR;
    }
    return ret;
}

/*****************************************************************************
** Description :  Append transaction record at the end of the database table
** Parameters  :  input:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data to save
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordAppend(ST_TRANSLOG *pstTransLog)
{
    if(NULL == pstTransLog)
    {
        return SDK_PARA_ERR;
    }

    if(&_gstTransLog != pstTransLog)
    {
        memcpy(&_gstTransLog, pstTransLog, sizeof(ST_TRANSLOG));
    }
    
    if(DB_EXIT_SUCCESS != sdkDbInsertRecord(&TabTransLog))
    {
        Trace("record", "sdkDbInsertRecord fail\r\n");
        return SDK_ERR;
    }
    
    if(SDK_OK == RecordReadLast(NULL))
    {
        if(&_gstTransLog != pstTransLog)
        {
            memcpy(pstTransLog, &_gstTransLog, sizeof(ST_TRANSLOG));
        }
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Update transaction record
** Parameters  :  input:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data to save
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  use "ID" field to match record.
*****************************************************************************/
s32 RecordUpdate(ST_TRANSLOG *pstTransLog)
{
    if(NULL == pstTransLog)
    {
        return SDK_PARA_ERR;
    }
    
    if(&_gstTransLog != pstTransLog)
    {
        memcpy(&_gstTransLog, pstTransLog, sizeof(ST_TRANSLOG));
    }

    if(DB_EXIT_SUCCESS != sdkDbUpdateRecord(&TabTransLog))
    {
        Trace("record", "sdkDbUpdateRecord fail\r\n");
        return SDK_ERR;
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Read transaction record by index
** Parameters  :  input:
                  (1)s32 iIndex : record index
                  output:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  use index to read record(not field "ID")
*****************************************************************************/
s32 RecordRead(s32 iIndex, ST_TRANSLOG *pstTransLog)
{
    if(NULL == pstTransLog)
    {
        return SDK_PARA_ERR;
    }
    
    memset(&_gstTransLog, 0, sizeof(ST_TRANSLOG));
    if(DB_EXIT_SUCCESS != sdkDbGetRecordByIndex(TabTransLog.pasTabName, iIndex, (void *)&TabTransLog))
    {
        Trace("record", "sdkDbGetRecordByIndex fail\r\n");
        return SDK_ERR;
    }

    if(pstTransLog)
    {
        memcpy(pstTransLog, &_gstTransLog, sizeof(ST_TRANSLOG));
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Read last transaction record 
** Parameters  :  output:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordReadLast(ST_TRANSLOG *pstTransLog)
{
    int num;
    
    num = RecordGetNum();
    Trace("record", "RecordGetNum num = %d\r\n", num);
    if(num > 0)
    {
        if(DB_EXIT_SUCCESS != sdkDbGetRecordByIndex(TabTransLog.pasTabName, (num - 1), (void *)&TabTransLog))
        {
            Trace("record", "sdkDbGetRecordByIndex fail\r\n");
            return SDK_ERR;
        }
    }

    Trace("record", "ID = %d\r\n", _gstTransLog.iID);
    if(pstTransLog && (&_gstTransLog != pstTransLog))
    {
        memcpy(pstTransLog, &_gstTransLog, sizeof(ST_TRANSLOG));
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Get record field attribute
** Parameters  :  input & output:
                  (1)ST_DB_FIELD *pstField : field attribute
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  must set "ST_DB_FIELD" member "iId" to get the attribute
*****************************************************************************/
s32 RecordGetField(ST_DB_FIELD *pstField)
{   
    s32 i = 0;
    
    if(NULL == pstField)
    {
        return SDK_PARA_ERR;
    }
    
    while(TabTransLog.stFields[i].iId >= 0)
    {
        if(pstField->iId == TabTransLog.stFields[i].iId)
        {
            memcpy(pstField, &TabTransLog.stFields[i], sizeof(ST_DB_FIELD));
            return SDK_OK;
        }
        i++;
    }
    return SDK_ERR;
}

/*****************************************************************************
** Description :  Search transaction record by one field
** Parameters  :  input:
                  (1)s32 iId : search field ID
                  (2)void *pasValue : search value
                  
                  output:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordSearch(s32 iId, void *pasValue, ST_TRANSLOG *pstTransLog)
{
    ST_DB_FIELD st_field;
    ST_DB_FILTER st_filter;
    
    if(NULL == pasValue || NULL == pstTransLog)
    {
        return SDK_PARA_ERR;
    }

    memset(&st_field, 0, sizeof(ST_DB_FIELD));
    memset(&st_filter, 0, sizeof(ST_DB_FILTER));
    
    st_field.iId = iId;
    if(SDK_OK != RecordGetField(&st_field))
    {
        return SDK_ERR;
    }
    st_filter.pasName = st_field.pasFieldName;
    st_filter.pasValue[0] = pasValue;
    st_filter.iType = st_field.iType;
    st_filter.iLen = st_field.iLen;
    
    memset(&_gstTransLog, 0, sizeof(ST_TRANSLOG));
	/*sdkDbSearchRecord hides some details ,I think that the function must have handled the global veriable _gstTransLog .
	 */
    if(DB_EXIT_SUCCESS != sdkDbSearchRecord(TabTransLog.pasTabName, &st_filter, &TabTransLog))
    {
        return SDK_ERR;
    }

    if(pstTransLog)
    {
        memcpy(pstTransLog, &_gstTransLog, sizeof(ST_TRANSLOG));
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Search transaction record by multiple condition
** Parameters  :  input:
                  (1)ST_RECORD_FILTER *pstFilter : record match conditions
                  (2)s32 iOffset : number of record that satisfies the condition
                  
                  output:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordSearchEx(ST_RECORD_FILTER *pstFilter, s32 iOffset, ST_TRANSLOG *pstTransLog)
{
    ST_DB_FIELD st_field;
    ST_DB_FILTER st_filter[DB_MAXFILTER];
    s32 i, k;

    if(NULL == pstFilter || NULL == pstTransLog)
    {
        return SDK_PARA_ERR;
    }

    memset(&st_filter, 0, sizeof(st_filter));

    for(i = 0; i < DB_MAXFILTER; i++)
    {
        memset(&st_field, 0, sizeof(ST_DB_FIELD));
        if(-1 == pstFilter[i].iId)
        {
            break;
        }
        st_field.iId = pstFilter[i].iId;
        if(SDK_OK != RecordGetField(&st_field))
        {
            return SDK_ERR;
        }
        st_filter[i].pasName = st_field.pasFieldName;
        for(k = 0; k < DB_MAXFILTER_VALUE; k++)
        {
            st_filter[i].pasValue[k] = pstFilter[i].pasValue[k];
        }
        st_filter[i].eMode = pstFilter[i].eMode;
        st_filter[i].iNum = pstFilter[i].iNum;
        st_filter[i].iType = st_field.iType;
        st_filter[i].iLen = st_field.iLen;
        if(pstFilter[i].bIsDesc)
        {
            st_filter[i].bIsDesc = TRUE;
        }
    }

    memset(&_gstTransLog, 0, sizeof(ST_TRANSLOG));
    if(DB_EXIT_SUCCESS != sdkDbMultiSearchRecord(TabTransLog.pasTabName, st_filter, i, iOffset, &TabTransLog))
    {
        return SDK_ERR;
    }

    if(pstTransLog)
    {
        memcpy(pstTransLog, &_gstTransLog, sizeof(ST_TRANSLOG));
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Get the sum of one field in the record that satisfies the condition
** Parameters  :  input:
                  (1)s32 iId : search field ID
                  (2)ST_RECORD_FILTER *pstFilter : record match conditions 
                  
                  output:
                  (1)s32 *piValue : the sum
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordGetSum(s32 iId, ST_RECORD_FILTER *pstFilter, u8 *pasValue)
{
    ST_DB_FIELD st_field;
    ST_DB_FILTER st_filter[DB_MAXFILTER];
    s32 i, k;

    if(NULL == pstFilter || NULL == pasValue)
    {
        return SDK_PARA_ERR;
    }

    memset(&st_filter, 0, sizeof(st_filter));

    for(i = 0; i < DB_MAXFILTER; i++)
    {
        memset(&st_field, 0, sizeof(ST_DB_FIELD));
        if(-1 == pstFilter[i].iId)
        {
            break;
        }
        st_field.iId = pstFilter[i].iId;
        if(SDK_OK != RecordGetField(&st_field))
        {
            return SDK_ERR;
        }
        st_filter[i].pasName = st_field.pasFieldName;
        for(k = 0; k < DB_MAXFILTER_VALUE; k++)
        {
            st_filter[i].pasValue[k] = pstFilter[i].pasValue[k];
        }
        st_filter[i].eMode = pstFilter[i].eMode;
        st_filter[i].iNum = pstFilter[i].iNum;
        st_filter[i].iType = st_field.iType;
        st_filter[i].iLen = st_field.iLen;
    }
    
    memset(&st_field, 0, sizeof(ST_DB_FIELD));
    st_field.iId = iId;
    if(SDK_OK != RecordGetField(&st_field))
    {
        return SDK_ERR;
    }
    
    if(DB_EXIT_SUCCESS != sdkDbGetSum(TabTransLog.pasTabName, st_field.pasFieldName, st_filter, i, pasValue))
    {
        return SDK_ERR;
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Delete one transaction record
** Parameters  :  input:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data to save
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  use "ID" field to match record.
*****************************************************************************/
s32 RecordDeleteOne(ST_TRANSLOG *pstTransLog)
{
    ST_DB_FIELD st_field;
    ST_DB_FILTER st_filter;
    
    if(NULL == pstTransLog)
    {
        return SDK_PARA_ERR;
    }

    if(&_gstTransLog != pstTransLog)
    {
        memcpy(&_gstTransLog, pstTransLog, sizeof(ST_TRANSLOG));
    }

    memset(&st_field, 0, sizeof(ST_DB_FIELD));
    memset(&st_filter, 0, sizeof(ST_DB_FILTER));
    
    st_field.iId = LOG_ID;
    if(SDK_OK != RecordGetField(&st_field))
    {
        return SDK_ERR;
    }
    
    st_filter.pasName = st_field.pasFieldName;
    st_filter.pasValue[0] = st_field.pAddress;
    st_filter.iType = st_field.iType;
    st_filter.iLen = st_field.iLen;
    
    if(DB_EXIT_SUCCESS != sdkDbDeleteOneRecord(TabTransLog.pasTabName, &st_filter))
    {
        Trace("record", "RecordInit fail\r\n");
        return SDK_ERR;
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Delete the last transaction record
** Parameters  :  None 
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 RecordDeleteLast(void)
{
    int num;

    num = RecordGetNum();
    if(num > 0)
    {
        if(DB_EXIT_SUCCESS != sdkDbGetRecordByIndex(TabTransLog.pasTabName, (num - 1), (void *)&TabTransLog))
        {
            Trace("record", "sdkDbGetRecordByIndex fail\r\n");
            return SDK_ERR;
        }
        if(SDK_OK != RecordDeleteOne(&_gstTransLog))
        {
            Trace("record", "RecordDeleteOne fail\r\n");
            return SDK_ERR;
        }
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Delete all transaction records
** Parameters  :  None 
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  just delete the data, database table will not be deleted
*****************************************************************************/
s32 RecordDeleteAll(void)
{
    if(DB_EXIT_SUCCESS != sdkDbDeleteAllRecords(TabTransLog.pasTabName))
    {
        Trace("record", "RecordInit fail\r\n");
        return SDK_ERR;
    }
    
    return SDK_OK;
}

