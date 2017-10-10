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
** Description :  Pack the ISO8583 message of script result upload transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 ScriptPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 buf[128] = {0};
    s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    
    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "702402C030C08211");

    if (ret <= 0)
    {
        return 0;
    }
    
    // Message ID
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0620", 4);
    if (ret <= 0)
    {
        return 0;
    }
    
    // #3 
    IsoSetField(pstIsoMsg, 3, pst_msginfo->asProcCode, strlen(pst_msginfo->asProcCode));
    
    // #22
    IsoSetField(pstIsoMsg, 22, pst_msginfo->asEntryMode, strlen(pst_msginfo->asEntryMode));
    
    // #23
    sprintf(buf, "%03d", gstTransData.stTransLog.stEmvInfo.ucPANSN);
    IsoSetField(pstIsoMsg, 23, buf, strlen(buf));
    
    // #32
    IsoSetField(pstIsoMsg, 32, pst_msginfo->asAIID, strlen( pst_msginfo->asAIID));
    
    // #37
    IsoSetField(pstIsoMsg, 37, pst_msginfo->asRefNO, strlen( pst_msginfo->asRefNO));
    
    // #38
    IsoSetField(pstIsoMsg, 38, pst_msginfo->asAuthCode, strlen( pst_msginfo->asAuthCode));

    // #49
    IsoSetField(pstIsoMsg, 49, pst_msginfo->asCurrencyCode, strlen(pst_msginfo->asCurrencyCode));
    
    // #60.1  transaction type code
    memset(buf, 0, sizeof(buf));
    strcat(buf, "00");
    // #60.2  batch number
    strcat(buf, gstAppSysCfg.stTransParam.asBatchNO);
    // #60.3  network management information code
    strcat(buf, "951");
    // #60.4  Reading capability at the terminal
    if ((0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_QCTLS, 2)) || 
        (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_MSD, 2)) || 
        (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_CTLS, 2)))                 
    {
        strcat(buf, "6");
    }
    else if ((0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_MANUAL, 2)) ||
             (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_SWIPE, 2)) ||
             (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_INSERT, 2)))
    {
        strcat(buf, "5");
    }
    else 
    {
        strcat(buf, "0");
    }
    // #60.5  IC card condition code based on CUPIC debit / credit standard
    if (CTLSFLOW_FALLBACK == gstTransData.stTransLog.stCardInfo.stCardParam.ucCLType && 
        gstTransData.stTransLog.stCardInfo.stCardData.bIsIccMagCard)       //fallbcak
    {
        strcat(buf, "2");
    }
    else
    {
        strcat(buf, "0");
    }
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));
    
    // #61
    memset(buf, 0, sizeof(buf));
   
    sprintf(buf, "%-6.6s%-6.6s", pst_msginfo->asOrigBatchNO, 
                                 pst_msginfo->asOrigTraceNO);
    if (strlen(pst_msginfo->asOrigDate) == 4)
    {
        strncat(buf, pst_msginfo->asOrigDate, 4);
    }
    else
    {
        strcat(buf, "0000");
    }
    IsoSetField(pstIsoMsg, 61, buf, strlen(buf));


    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Reversal transaction process
** Parameters  :  None
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 ScriptSendMsg(void)
{
    s32 ret = 0;
    s32 i = 0;
    ST_TRANSLOG *pst_translog = &gstTransData.stTransLog;
    ST_TRANSLOG st_translog;
    ST_TRANSLOG st_translog_bak;
    s32 script = TRUE;
    SDK_8583_ST8583 st_sendpacket;
    SDK_8583_ST8583 st_recvpacket;
    bool flag = FALSE;
    
    memcpy(&st_translog_bak, &gstTransData.stTransLog, sizeof(ST_TRANSLOG));
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PROCESSING, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    
    if(SDK_OK != RecordSearch(LOG_STAT_NEEDSCRIPT, (void *)&script, &st_translog))
    {
        return SDK_OK;
    }

    memcpy(pst_translog, &st_translog, sizeof(ST_TRANSLOG));
    memcpy(pst_translog->stMsgInfo.asOrigTraceNO, pst_translog->stMsgInfo.asTraceNO, sizeof(pst_translog->stMsgInfo.asOrigTraceNO));
    memcpy(pst_translog->stMsgInfo.asOrigBatchNO, pst_translog->stMsgInfo.asBatchNO, sizeof(pst_translog->stMsgInfo.asOrigBatchNO));
    memcpy(pst_translog->stMsgInfo.asOrigDate, pst_translog->stMsgInfo.asTransDate, 4);
        
    for(i = 0; i < gstAppSysCfg.stTransParam.uiReversalTimes; i++)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            ret = SDK_ERR;
            break;
        }
        
        ret = ScriptPackMsg(&st_sendpacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            ret = SDK_ERR;
            break;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&st_sendpacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            ret = SDK_ERR;
            break;
        }
        
        TrnUpdateTransDataSend(&st_sendpacket);

        memset(&st_recvpacket, 0, sizeof(st_recvpacket));   
        
        ret = CommuExchangeIsoPacket(&st_sendpacket, &st_recvpacket);
        if(SDK_OK == ret)
        {
            flag = TRUE;
            break;
        }
        else if(i == (gstAppSysCfg.stTransParam.uiReversalTimes - 1))
        {
            flag = TRUE;
        }
    }

    if(flag)
    {
        if(st_translog.stTransStatus.bIsIccFailTrans)
        {
            if(SDK_OK != RecordDeleteOne(&st_translog))
            {
                TrnSetStatus(ERR_FILE_SYSTEM);
                ret = SDK_ERR;
            }
            ret = SDK_OK;
        }
        else
        {
            st_translog.stTransStatus.bIsNeedScript = FALSE;
            if(SDK_OK != RecordUpdate(&st_translog))
            {
                TrnSetStatus(ERR_FILE_SYSTEM);
                ret = SDK_ERR;
            }
            ret = SDK_OK;
        }
    }
    
    memcpy(&gstTransData.stTransLog, &st_translog_bak, sizeof(ST_TRANSLOG));
    
    return ret;
}

/*****************************************************************************
** Description :  Get ICC script execute result
** Parameters  :  None
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 ScriptGetResult()
{
    u8 tmp[256];
    u8 buf[512];
    s32 len = 0;
    ST_EMVINFO *pst_emvinfo = &gstTransData.stTransLog.stEmvInfo;

    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    len = IsoGetField(&gstRecvPacket, 55, buf, sizeof(buf));
    if(SDK_OK != EmvParseIccTlv(buf, len, "\x71", tmp, &len) && 
       SDK_OK != EmvParseIccTlv(buf, len, "\x72", tmp, &len))
    {
        return SDK_OK;
    }
    
    memset(tmp, 0, sizeof(tmp));
    // verify ICC script already execute by TSI
    if (sdkIccReadTLV("\x9B", tmp, &len) > 0 && 0x04 == (tmp[0] & 0x04)) 
    {
        // verify ICC script execute success by TVR
        if (sdkIccReadTLV("\x95", tmp, &len) > 0 && 0x10 != (tmp[4] & 0x10)) 
        {
            gstTransData.stTransLog.stTransStatus.bIsNeedScript = TRUE;
            sdkIccGetScriptResult(&len, pst_emvinfo->heScriptResult);
            pst_emvinfo->ucScriptResultLen = (u8)len;
            return SDK_OK;
        }
        else
        {
            return SDK_ERR;
        }
    }
    else
    {
        return SDK_ERR;
    }
}

