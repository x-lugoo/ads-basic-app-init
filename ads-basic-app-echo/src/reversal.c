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
** Description :  Pack the ISO8583 message of reversal transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 ReversalPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 buf[128] = {0};
    s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_CARDINFO *pst_cardinfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return 0;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;

    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "7024028006C08211");

    if (ret <= 0)
    {
        return 0;
    }
    
    // #0 MTI
    ret = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0400", 4);
    if (ret <= 0)
    {
        return 0;
    }

    // #3 
    IsoSetField(pstIsoMsg, 3, pst_msginfo->asProcCode, strlen(pst_msginfo->asProcCode));
    
    // #11
    IsoSetField(pstIsoMsg, 11, pst_msginfo->asTraceNO, strlen(pst_msginfo->asTraceNO));
    
    // #22
    IsoSetField(pstIsoMsg, 22, pst_msginfo->asEntryMode, strlen(pst_msginfo->asEntryMode));
    
    // #23
    if(0 != gstTransData.stTransLog.stEmvInfo.ucPANSN)
    {
        sprintf(buf, "%03d", gstTransData.stTransLog.stEmvInfo.ucPANSN);
        IsoSetField(pstIsoMsg, 23, buf, strlen(buf));
    }
    
    // #25
    IsoSetField(pstIsoMsg, 25, pst_msginfo->asConditionCode, strlen(pst_msginfo->asConditionCode));

    // #38
    if(strlen(pst_msginfo->asAuthCode))
    {
        IsoSetField(pstIsoMsg, 38, pst_msginfo->asAuthCode, strlen( pst_msginfo->asAuthCode));
    }

    // #39
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%02X", gstTransData.stTransLog.stTransStatus.ucReversalReason);
    IsoSetField(pstIsoMsg, 39, buf, strlen(buf));

    // #41
    IsoSetField(pstIsoMsg, 41, pst_msginfo->asTermID, strlen(pst_msginfo->asTermID));

    // #42
    IsoSetField(pstIsoMsg, 42, pst_msginfo->asMerchID, strlen(pst_msginfo->asMerchID));
    
    // #49
    IsoSetField(pstIsoMsg, 49, pst_msginfo->asCurrencyCode, strlen(pst_msginfo->asCurrencyCode));
    
    // #60
    memset(buf, 0, sizeof(buf));    
    strcat(buf, pst_msginfo->asFuncCode);
    strcat(buf, pst_msginfo->asBatchNO);
    strcat(buf, "000");
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
    // #60.6  Symbol of supporting partial deduction and return balance
    strcat(buf, "0");
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));
    
    // #61
    memset(buf, 0, sizeof(buf));
    if(strlen(pst_msginfo->asOrigBatchNO))
    {
        sprintf(buf, "%-6.6s%-6.6s", pst_msginfo->asOrigBatchNO, 
                                     pst_msginfo->asOrigTraceNO);
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
s32 ReversalSendMsg(void)
{
    s32 ret = 0;
    s32 i = 0;
    ST_TRANSLOG *pst_translog = &gstTransData.stTransLog;
    ST_TRANSLOG st_translog;
    s32 reversal = 1;
    SDK_8583_ST8583 st_sendpacket;
    SDK_8583_ST8583 st_recvpacket;

    memcpy(&st_translog, &gstTransData.stTransLog, sizeof(ST_TRANSLOG));

    while(1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PROCESSING, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        if(SDK_OK != RecordSearch(LOG_STAT_NEEDREVERSAL, (void *)&reversal, pst_translog))
        {
            Trace("reversal", "ReversalSendMsg no reversal\r\n");
            memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
            return SDK_OK;
        }

        pst_translog->eTransID = TRANSID_REVERSAL;
            
        //deal reversal
        for(i = 0; i < gstAppSysCfg.stTransParam.uiReversalTimes; i++)
        {
            memset(&st_sendpacket, 0, sizeof(SDK_8583_ST8583));
            memset(&st_recvpacket, 0, sizeof(SDK_8583_ST8583));
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            ret = CommuCreateLink();
            if (SDK_OK != ret)
            {
                memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
                return SDK_ERR;
            }
            
            ret = ReversalPackMsg(&st_sendpacket);

            if (0 == ret)
            {
                TrnSetStatus(ERR_PACK_MSG);
                memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
                return SDK_ERR;
            }

            // Encrypt sending packet
            ret = IsoPackMsgMac(&st_sendpacket);
            if (SDK_OK != ret)
            {
                TrnSetStatus(ERR_PACK_MSG);
                memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
                return SDK_ERR;
            }
            
            TrnUpdateTransDataSend(&st_sendpacket);
        
            memset(&st_recvpacket, 0, sizeof(st_recvpacket));   
            
            ret = CommuExchangeIsoPacket(&st_sendpacket, &st_recvpacket);
            if(SDK_OK == ret)
            {
                if((0 == memcmp(gstTransData.stTransLog.stMsgInfo.asRespCode, "00", 2)) ||
                   (0 == memcmp(gstTransData.stTransLog.stMsgInfo.asRespCode, "12", 2)) ||
                   (0 == memcmp(gstTransData.stTransLog.stMsgInfo.asRespCode, "25", 2)))
                {
                    RecordDeleteOne(pst_translog);
                    memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
                    return SDK_OK;
                }
            }
        }
        RecordDeleteOne(pst_translog);  //if reversal fail 3 times, delete reversal record.
    }
    
    memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
    
    return SDK_OK;
}

