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

/*----------------------------------------------------------------------------*/

/*****************************************************************************
** Description :  Automatic upload offline trans process
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void OfflineAutoUpload(void)
{
    s32 cnt = 0;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2, value3, value4;
    bool value5;
    
    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_ADJUST;
    value2 = TRANSID_TIP;
    value3 = UPLOAD_OFFLINE_SUCCESS;
    value4 = UPLOAD_OFFLINE_DECLINE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_MULTI;
    st_filter[0].pasValue[0] = &value1;
    st_filter[0].pasValue[1] = &value2;
    st_filter[0].iNum = 2;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_SIGNEL_BESIDE;
    st_filter[1].pasValue[0] = &value3;
    
    st_filter[2].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[2].eMode = FILTER_SIGNEL_BESIDE;
    st_filter[2].pasValue[0] = &value4;

    st_filter[3].iId = -1;

    cnt = RecordGetNumEx(st_filter);
    
    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_SALE;
    value2 = UPLOAD_OFFLINE_SUCCESS;
    value3 = UPLOAD_OFFLINE_DECLINE;
    value5 = TRUE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_SIGNEL_BESIDE;
    st_filter[1].pasValue[0] = &value2;
    
    st_filter[2].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[2].eMode = FILTER_SIGNEL_BESIDE;
    st_filter[2].pasValue[0] = &value3;
    
    st_filter[3].iId = LOG_STAT_OFFLINE;
    st_filter[3].eMode = FILTER_SIGNEL;
    st_filter[3].pasValue[0] = &value5;

    st_filter[4].iId = -1;
    
    cnt += RecordGetNumEx(st_filter);

    if(cnt >= gstAppSysCfg.stTransParam.uiOffSaleAutoUpNum)
    {
        DispSaveScreen();
        DispTitle(STR_TRANS_OFFLINE_UPLOAD);
        OfflineSendMsg();
        DispRestoreScreen();
    }
}

/*****************************************************************************
** Description :  Pack the ISO8583 message of offline transaction upload
                  (magnetic stripe offline transaction)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 OfflinePackMagTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack the ISO8583 message of offline transaction upload
                  (ICC offline transaction)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 OfflinePackIccTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 cardno[20] = {0};
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);

    // #2, must upload the account of card for all ICC-offline transactions
    if (SDK_OK == TrnGetMagCardNo(&gstTransData.stTransLog.stCardInfo.stCardData, cardno))
    {
        IsoSetField(pstIsoMsg, 2, cardno, strlen(cardno));
    }
    
    // #11
    IsoSetField(pstIsoMsg, 11, gstTransData.stTransLog.stMsgInfo.asTraceNO, 6);

    // #35
    sdk8583ClrField(pstIsoMsg, 35);

    // #36
    sdk8583ClrField(pstIsoMsg, 36);

    if (!sdk8583IsDomainExist(pstIsoMsg, 35)
        && !sdk8583IsDomainExist(pstIsoMsg, 36)
        && !sdk8583IsDomainExist(pstIsoMsg, 52))
    {
        sdk8583ClrField(pstIsoMsg, 53);
    }
    
    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Offline transaction upload process (magnetic stripe offline transaction)
** Parameters  :  input
                  (1)u32 uiUpNum : already upload times
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 OfflineSendMsgMag(u32 uiUpNum)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i;
    s32 offset = 0;
    u8 tmp[64];
    ST_TRANSLOG *pst_translog = &gstTransData.stTransLog;
    ST_TRANSLOG st_translog;
    SDK_8583_ST8583 st_sendpacket;
    SDK_8583_ST8583 st_recvpacket;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2, value3;

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PROCESSING, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    
    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_ADJUST;
    value2 = TRANSID_TIP;
    value3 = UPLOAD_OFFLINE_NONE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_MULTI;
    st_filter[0].pasValue[0] = &value1;
    st_filter[0].pasValue[1] = &value2;
    st_filter[0].iNum = 2;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_SIGNEL;
    st_filter[1].pasValue[0] = &value3;
    
    st_filter[2].iId = -1;

    cnt = RecordGetNumEx(st_filter);
    for(i = 0; i < cnt; i++)
    {
        //search the transaction
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }

        memcpy(pst_translog, &st_translog, sizeof(ST_TRANSLOG));
        
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%s[%d/%d]", STR_INFO_UPLOADING, i + 1, cnt);
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, tmp, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        
        // Exchange transaction ISO8538 messages
        memset(&st_sendpacket, 0, sizeof(SDK_8583_ST8583));
        memset(&st_recvpacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ESC;
        }
        
        ret = OfflinePackMagTransMsg(&st_sendpacket);
        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ESC;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&st_sendpacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ESC;
        }
        
        TrnUpdateTransDataSend(&st_sendpacket);
    
        memset(&st_recvpacket, 0, sizeof(SDK_8583_ST8583));   
        
        ret = CommuExchangeIsoPacket(&st_sendpacket, &st_recvpacket);
        Trace("offline", "CommuExchangeIsoPacket = %d\r\n", ret);
        if(SDK_OK != ret || (0 == memcmp(pst_translog->stMsgInfo.asRespCode, "A0", 2)))
        {
            if (uiUpNum >= (gstAppSysCfg.stTransParam.uiOffTransUpTimes - 1))
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_OFFLINE_FAIL;
                RecordUpdate(&st_translog);
                offset++;
            }
        }
        else
        {
            if((0 == memcmp(pst_translog->stMsgInfo.asRespCode, "00", 2))
            || (0 == memcmp(pst_translog->stMsgInfo.asRespCode, "94", 2)))
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_OFFLINE_SUCCESS;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_OFFLINE_DECLINE;
            }
            RecordUpdate(&st_translog);
            offset++;
        }
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Offline transaction upload process (ICC offline transaction)
** Parameters  :  input
                  (1)u32 uiUpNum : already upload times
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 OfflineSendMsgIcc(u32 uiUpNum)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i = 0;
    s32 offset = 0;
    u8 tmp[64];
    ST_TRANSLOG *pst_translog = &gstTransData.stTransLog;
    ST_TRANSLOG st_translog;
    SDK_8583_ST8583 st_sendpacket;
    SDK_8583_ST8583 st_recvpacket;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2;
    bool value3;

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PROCESSING, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    
    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_SALE;
    value2 = UPLOAD_OFFLINE_NONE;
    value3 = TRUE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_SIGNEL;
    st_filter[1].pasValue[0] = &value2;
        
    st_filter[2].iId = LOG_STAT_OFFLINE;
    st_filter[2].eMode = FILTER_SIGNEL;
    st_filter[2].pasValue[0] = &value3;
    
    st_filter[3].iId = LOG_STAT_ICCFAILTRANS;
    st_filter[3].eMode = FILTER_SIGNEL_BESIDE;
    st_filter[3].pasValue[0] = &value3;

    st_filter[4].iId = -1;
    
    cnt = RecordGetNumEx(st_filter);
    for(i = 0; i < cnt; i++)
    {
        //search the transaction
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }
        
        if(!(st_translog.stEmvInfo.ucCID & 0x40))
        {
            continue;
        }
        
        memcpy(pst_translog, &st_translog, sizeof(ST_TRANSLOG));

        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%s[%d/%d]", STR_INFO_UPLOADING, i + 1, cnt);
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, tmp, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        
        // Exchange transaction ISO8538 messages
        memset(&st_sendpacket, 0, sizeof(SDK_8583_ST8583));
        memset(&st_recvpacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ESC;
        }
        
        ret = OfflinePackIccTransMsg(&st_sendpacket);
        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ESC;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&st_sendpacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ESC;
        }
        
        TrnUpdateTransDataSend(&st_sendpacket);
    
        memset(&st_recvpacket, 0, sizeof(SDK_8583_ST8583));   
        
        ret = CommuExchangeIsoPacket(&st_sendpacket, &st_recvpacket);
        if(SDK_OK != ret || (0 == memcmp(pst_translog->stMsgInfo.asRespCode, "A0", 2)))
        {
            if (uiUpNum >= (gstAppSysCfg.stTransParam.uiOffTransUpTimes - 1))
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_OFFLINE_FAIL;
                RecordUpdate(&st_translog);
                offset++;
            }
        }
        else
        {
            if((0 == memcmp(pst_translog->stMsgInfo.asRespCode, "00", 2))
            || (0 == memcmp(pst_translog->stMsgInfo.asRespCode, "94", 2)))
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_OFFLINE_SUCCESS;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_OFFLINE_DECLINE;
            }
            RecordUpdate(&st_translog);
            offset++;
        }
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Offline transaction upload process
** Parameters  :  None 
** Return      :  (1)FALSE : fail 
                  (2)TRUE : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool OfflineSendMsg(void)
{
    u8 i = 0;
    s32 ret = 0;
    ST_TRANSLOG st_translog;
    
    memcpy(&st_translog, &gstTransData.stTransLog, sizeof(ST_TRANSLOG));

    for (i = 0; i < gstAppSysCfg.stTransParam.uiOffTransUpTimes; i++)
    {
        ret = OfflineSendMsgMag(i);
        if (SDK_OK != ret)
        {
            return FALSE;
        }
        
        ret = OfflineSendMsgIcc(i);
        if (SDK_OK != ret)
        {
            return FALSE;
        }
    }
    
    memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));

    return TRUE;
}

