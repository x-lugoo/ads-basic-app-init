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
// 
static ST_PACKET_INFO TabPacketInfo[] = 
{
    {TRANSID_SALE,       SalePackMsg},
    {TRANSID_VOID,       VoidPackMsg},
    {TRANSID_REFUND,     RefundPackMsg},
    {TRANSID_TIP,        AdjustPackMsg},
    {TRANSID_ADJUST,     AdjustPackMsg},
};

/*****************************************************************************
** Description :  Save settle record
** Parameters  :  input:
                  (1)ST_SETTLE *pstSettle : settle information
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void SettleSaveInfo(ST_SETTLE *pstSettle)
{
    u8  path[256];
    
    memset(path, 0, sizeof(path));
    sdkSysGetCurAppDir(path);
    strcat(path, FILENAME_SETTLE);

    sdkSaveOverlap(path, (u8 *)pstSettle, sizeof(ST_SETTLE));
}

/*****************************************************************************
** Description :  Read settle record
** Parameters  :  output:
                  (1)ST_SETTLE *pstSettle : settle information
                  
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettleReadInfo(ST_SETTLE *pstSettle)
{
    u8  path[256];
    s32 ret;
    
    memset(path, 0, sizeof(path));
    sdkSysGetCurAppDir(path);
    strcat(path, FILENAME_SETTLE);

    ret = sdkReadOverlap(path, (u8 *)pstSettle, sizeof(ST_SETTLE));
    Trace("settle", "SettleReadInfo = %d", ret);
    if (SDK_FILE_OK == ret)
    {
        return SDK_OK;
    }

    return SDK_ERR;
}

/*****************************************************************************
** Description :  Delete settle record
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void SettleDeleteInfo(void)
{
    u8  path[256];
    
    memset(path, 0, sizeof(path));
    sdkSysGetCurAppDir(path);
    strcat(path, FILENAME_SETTLE);

    sdkDelFile(path);
    strcat(path, ".bak");
    sdkDelFile(path);
}

/*****************************************************************************
** Description :  Save batch upload information
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void BatchUpSaveInfo(ST_BATCHUP_INFO *pstBatchInfo)
{
    u8  path[256];
    
    memset(path, 0, sizeof(path));
    sdkSysGetCurAppDir(path);
    strcat(path, FILENAME_BATCHUP);

    sdkSaveOverlap(path, (u8 *)pstBatchInfo, sizeof(ST_BATCHUP_INFO));
}

/*****************************************************************************
** Description :  Delete batch upload information
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void BatchUpDeleteInfo(void)
{
    u8  path[256];
    
    memset(path, 0, sizeof(path));
    sdkSysGetCurAppDir(path);
    strcat(path, FILENAME_BATCHUP);

    sdkDelFile(path);
    strcat(path, ".bak");
    sdkDelFile(path);
}

/*****************************************************************************
** Description :  Read batch upload information
** Parameters  :  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpReadInfo(ST_BATCHUP_INFO *pstBatchInfo)
{
    u8  path[256];
    s32 ret;
    
    memset(path, 0, sizeof(path));
    sdkSysGetCurAppDir(path);
    strcat(path, FILENAME_BATCHUP);

    ret = sdkReadOverlap(path, (u8 *)pstBatchInfo, sizeof(ST_BATCHUP_INFO));
    if (SDK_FILE_OK == ret)
    {
        return SDK_OK;
    }

    return SDK_ERR;
}

/*****************************************************************************
** Description :  Get original transaction packet information
** Parameters  :  input & output:
                  (1)ST_PACKET_INFO *pstPacketInfo : original transaction packet 
                                                     information
                  
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-19 
** Remarks     :  use "eTransID" to match the information, so member "eTransID"
                  value must be set first
*****************************************************************************/
s32 SettleGetTransMsg(ST_PACKET_INFO *pstPacketInfo)
{
    u32 i;

    for (i = 0; i < sizeof(TabPacketInfo) / sizeof(ST_PACKET_INFO); i++)
    {
        if (TabPacketInfo[i].eTransID == pstPacketInfo->eTransID)
        {
            memcpy(pstPacketInfo, &TabPacketInfo[i], sizeof(ST_PACKET_INFO));
            return SDK_OK;
        }
    }
    return SDK_ERR;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of batch upload transaction(offline)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackOfflineTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 tmp[64] = {0};
    ST_MSGINFO *pst_msginfo = NULL;
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    
    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #22
    memset(tmp, 0, sizeof(tmp));
    if (IsoGetField(pstIsoMsg, 22, tmp, sizeof(tmp)) > 0)
    {
        tmp[2] = '2';
        IsoSetField(pstIsoMsg, 22, tmp, strlen(tmp));
    }
    
    // #26
    sdk8583ClrField(pstIsoMsg, 26);

    // #52
    sdk8583ClrField(pstIsoMsg, 52);

    // #53
    memset(tmp, 0, sizeof(tmp));
    if (IsoGetField(pstIsoMsg, 53, tmp, sizeof(tmp)) > 0)
    {
        tmp[0] = '0';
        IsoSetField(pstIsoMsg, 53, tmp, strlen(tmp));
    }

    // #64
    sdk8583ClrField(pstIsoMsg, 64);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of batch upload transaction(ICC offline)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackIccOfflineTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 tmp[64] = {0};
    u8 cardno[20] = {0};
    ST_MSGINFO *pst_msginfo = NULL;
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
        
    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #2
    if (SDK_OK == TrnGetMagCardNo(&gstTransData.stTransLog.stCardInfo.stCardData, cardno))
    {
        IsoSetField(pstIsoMsg, 2, cardno, strlen(cardno));
    }
    
    // #22
    memset(tmp, 0, sizeof(tmp));
    if (strlen(pst_msginfo->asEntryMode) > 0)
    {
        pst_msginfo->asEntryMode[2] = '2';
        IsoSetField(pstIsoMsg, 22, pst_msginfo->asEntryMode, strlen(pst_msginfo->asEntryMode));
    }
    
    // #26
    sdk8583ClrField(pstIsoMsg, 26);

    // #35
    sdk8583ClrField(pstIsoMsg, 35);

    // #36
    sdk8583ClrField(pstIsoMsg, 36);

    // #52
    sdk8583ClrField(pstIsoMsg, 52);

    if (!sdk8583IsDomainExist(pstIsoMsg, 35)
        && !sdk8583IsDomainExist(pstIsoMsg, 36)
        && !sdk8583IsDomainExist(pstIsoMsg, 52))
    {
        sdk8583ClrField(pstIsoMsg, 53);
    }
    // #64
    sdk8583ClrField(pstIsoMsg, 64);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of batch upload transaction(All Mag)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackAllMagTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 tmp[512] = {0};
    s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;
    
    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "0020000000C10010");
    if (ret <= 0)
    {
        return 0;
    }
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #48
    IsoSetField(pstIsoMsg, 48, gstTransData.asAdditionInfo, strlen(gstTransData.asAdditionInfo));

    // #60
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "00");
    strcat(tmp, gstAppSysCfg.stTransParam.asBatchNO);
    strcat(tmp, "201");
    IsoSetField(pstIsoMsg, 60, tmp, strlen(tmp));

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of batch upload transaction(Advice)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackAdviceTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 tmp[64] = {0};
    ST_MSGINFO *pst_msginfo = NULL;    
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    
    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #22
    memset(tmp, 0, sizeof(tmp));
    if (strlen(pst_msginfo->asEntryMode) > 0)
    {
        pst_msginfo->asEntryMode[2] = '2';
        IsoSetField(pstIsoMsg, 22, pst_msginfo->asEntryMode, strlen(pst_msginfo->asEntryMode));
    }
    // #26
    sdk8583ClrField(pstIsoMsg, 26);

    // #52
    sdk8583ClrField(pstIsoMsg, 52);

    // #64
    sdk8583ClrField(pstIsoMsg, 64);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of batch upload transaction(All ICC)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackAllIccTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 cardno[20] = {0};
    u8 tmp[255];
    ST_SETTLE stSettle;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    
    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #2
    if (SDK_OK == TrnGetMagCardNo(&gstTransData.stTransLog.stCardInfo.stCardData, cardno))
    {
        IsoSetField(pstIsoMsg, 2, cardno, strlen(cardno));
    }
    // #3
    sdk8583ClrField(pstIsoMsg, 3);
    
    // #11
    IsoSetField(pstIsoMsg, 11, pst_msginfo->asTraceNO, 6);

    // #14
    sdk8583ClrField(pstIsoMsg, 14);

    // #25
    sdk8583ClrField(pstIsoMsg, 25);

    // #26
    sdk8583ClrField(pstIsoMsg, 26);

    // #35
    sdk8583ClrField(pstIsoMsg, 35);

    // #36
    sdk8583ClrField(pstIsoMsg, 36);

    // #49
    sdk8583ClrField(pstIsoMsg, 49);

    // #52
    sdk8583ClrField(pstIsoMsg, 52);

    // #53
    sdk8583ClrField(pstIsoMsg, 53);

    // #60
    SettleReadInfo(&stSettle);
    memset(tmp, 0, sizeof(tmp));
    strcat(tmp, "00");
    strncat(tmp, pst_msginfo->asBatchNO, 6);  
    if ('1' != stSettle.stTotalRMB.ucSettleCode   
        || '1' != stSettle.stTotal.ucSettleCode)  
    {
        strcat(tmp, "205");
    }
    else
    {
        strcat(tmp, "203");
    }
    if ((0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_QCTLS, 2)) || 
        (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_MSD, 2)) || 
        (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_CTLS, 2)))                 
    {
        strcat(tmp, "6");
    }
    else if ((0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_MANUAL, 2)) ||
             (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_SWIPE, 2)) ||
             (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_INSERT, 2)))
    {
        strcat(tmp, "5");
    }
    else 
    {
        strcat(tmp, "0");
    }
    // #60.5  IC card condition code based on CUPIC debit / credit standard
    if (CTLSFLOW_FALLBACK == gstTransData.stTransLog.stCardInfo.stCardParam.ucCLType && 
        gstTransData.stTransLog.stCardInfo.stCardData.bIsIccMagCard)       //fallbcak
    {
        strcat(tmp, "2");
    }
    else
    {
        strcat(tmp, "0");
    }
    IsoSetField(pstIsoMsg, 60, tmp, strlen(tmp));
    
    // #62
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "61");

    if (0 != memcmp(pst_msginfo->asInterOrgCode,"CUP",3))
    {
        strcat(tmp, "01");
    }
    else
    {
        strcat(tmp, "00");
    }
    strcat(tmp, "00");

    if (strlen(pst_msginfo->asAmount) > 0)
    {
        strncat(tmp, pst_msginfo->asAmount, 12);
    }
    else
    {
        strcat(tmp, "000000000000");
    }
    strcat(tmp, pst_msginfo->asCurrencyCode);
    IsoSetField(pstIsoMsg, 62, tmp, strlen(tmp));
    
    // #63
    sdk8583ClrField(pstIsoMsg, 63);
    
    // #64
    sdk8583ClrField(pstIsoMsg, 64);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of batch upload transaction(All ICC fail)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackAllFailIccTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 cardno[20] = {0};
    u8 tmp[255];
    ST_SETTLE stSettle;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    
    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #2
    if (SDK_OK == TrnGetMagCardNo(&gstTransData.stTransLog.stCardInfo.stCardData, cardno))
    {
        IsoSetField(pstIsoMsg, 2, cardno, strlen(cardno));
    }
    // #3
    sdk8583ClrField(pstIsoMsg, 3);
    
    // #11
    IsoSetField(pstIsoMsg, 11, pst_msginfo->asTraceNO, 6);

    // #14
    sdk8583ClrField(pstIsoMsg, 14);

    // #25
    sdk8583ClrField(pstIsoMsg, 25);

    // #26
    sdk8583ClrField(pstIsoMsg, 26);

    // #35
    sdk8583ClrField(pstIsoMsg, 35);

    // #36
    sdk8583ClrField(pstIsoMsg, 36);

    // #49
    sdk8583ClrField(pstIsoMsg, 49);

    // #52
    sdk8583ClrField(pstIsoMsg, 52);

    // #53
    sdk8583ClrField(pstIsoMsg, 53);

    // #60
    SettleReadInfo(&stSettle);
    memset(tmp, 0, sizeof(tmp));
    strcat(tmp, "00");
    strncat(tmp, pst_msginfo->asBatchNO, 6);  

    if ('1' != stSettle.stTotalRMB.ucSettleCode   
        || '1' != stSettle.stTotal.ucSettleCode)  
    {
        strcat(tmp, "206");
    }
    else
    {
        strcat(tmp, "204");
    }
    IsoSetField(pstIsoMsg, 60, tmp, strlen(tmp));

    // #62
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "71");

    if (0 != memcmp(pst_msginfo->asInterOrgCode,"CUP",3))
    {
        strcat(tmp, "01");
    }
    else
    {
        strcat(tmp, "00");
    }
    strcat(tmp, "11");

    if (strlen(pst_msginfo->asAmount) > 0)
    {
        strncat(tmp, pst_msginfo->asAmount, 12);
    }
    else
    {
        strcat(tmp, "000000000000");
    }
    strcat(tmp, pst_msginfo->asCurrencyCode);
    strcat(tmp, "10");
    IsoSetField(pstIsoMsg, 62, tmp, strlen(tmp));
    
    // #63
    sdk8583ClrField(pstIsoMsg, 63);
    
    // #64
    sdk8583ClrField(pstIsoMsg, 64);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of batch upload transaction(All ARPC ERR)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackAllArpcErrIccTransMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 cardno[20] = {0};
    u8 tmp[255];
    ST_SETTLE stSettle;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_PACKET_INFO st_packetinfo;

    memset(&st_packetinfo, 0, sizeof(ST_PACKET_INFO));
    st_packetinfo.eTransID = gstTransData.stTransLog.eTransID;
    if(SDK_OK != SettleGetTransMsg(&st_packetinfo))
    {
        return 0;
    }
    st_packetinfo.pFun(pstIsoMsg);
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    
    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #2
    if (SDK_OK == TrnGetMagCardNo(&gstTransData.stTransLog.stCardInfo.stCardData, cardno))
    {
        IsoSetField(pstIsoMsg, 2, cardno, strlen(cardno));
    }
    // #3
    sdk8583ClrField(pstIsoMsg, 3);
    
    // #11
    IsoSetField(pstIsoMsg, 11, pst_msginfo->asTraceNO, 6);

    // #14
    sdk8583ClrField(pstIsoMsg, 14);

    // #25
    sdk8583ClrField(pstIsoMsg, 25);

    // #26
    sdk8583ClrField(pstIsoMsg, 26);

    // #35
    sdk8583ClrField(pstIsoMsg, 35);

    // #36
    sdk8583ClrField(pstIsoMsg, 36);

    // #49
    sdk8583ClrField(pstIsoMsg, 49);

    // #52
    sdk8583ClrField(pstIsoMsg, 52);

    // #53
    sdk8583ClrField(pstIsoMsg, 53);

    // #60
    SettleReadInfo(&stSettle);
    memset(tmp, 0, sizeof(tmp));
    strcat(tmp, "00");
    strncat(tmp, pst_msginfo->asBatchNO, 6);  

    if ('1' != stSettle.stTotalRMB.ucSettleCode   
        || '1' != stSettle.stTotal.ucSettleCode)  
    {
        strcat(tmp, "206");
    }
    else
    {
        strcat(tmp, "204");
    }
    IsoSetField(pstIsoMsg, 60, tmp, strlen(tmp));

    // #62
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "71");

    if (0 != memcmp(pst_msginfo->asInterOrgCode,"CUP",3))
    {
        strcat(tmp, "01");
    }
    else
    {
        strcat(tmp, "00");
    }
    strcat(tmp, "05");

    if (strlen(pst_msginfo->asAmount) > 0)
    {
        strncat(tmp, pst_msginfo->asAmount, 12);
    }
    else
    {
        strcat(tmp, "000000000000");
    }
    strcat(tmp, pst_msginfo->asCurrencyCode);
    strcat(tmp, "22");
    IsoSetField(pstIsoMsg, 62, tmp, strlen(tmp));
    
    // #63
    sdk8583ClrField(pstIsoMsg, 63);
    
    // #64
    sdk8583ClrField(pstIsoMsg, 64);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack ISO8583 message of trailer transaction(settlement finish)
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackTrailerMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 tmp[255] = {0};
    s32 ret;
    ST_BATCHUP_INFO st_batchinfo;
    ST_SETTLE st_settle;
    ST_MSGINFO *pst_msginfo = NULL;
    
    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "0020000000C10010");
    if (ret <= 0)
    {
        return 0;
    }
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    // #0, MTI
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0320", 4);

    // #48
    BatchUpReadInfo(&st_batchinfo);
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%04d", st_batchinfo.uiBatchUpNum);
    IsoSetField(pstIsoMsg, 48, tmp, strlen(tmp));


    // #60
    SettleReadInfo(&st_settle);
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "00");
    strcat(tmp, gstAppSysCfg.stTransParam.asBatchNO);

    if ('1' != st_settle.stTotalRMB.ucSettleCode
        || '1' != st_settle.stTotal.ucSettleCode)
    {
        strcat(tmp, "202");
    }
    else
    {
        strcat(tmp, "207");
    }
    IsoSetField(pstIsoMsg, 60, tmp, strlen(tmp));

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack #48 data for settle transation
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void SettleSetField048(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 tmp[512] = {0};
    u32 offset = 0;
    ST_SETTLE st_settle;

    SettleReadInfo(&st_settle);

    offset = 0;
    memset(tmp, 0, sizeof(tmp));
    sdkBcdToAsc(&tmp[offset], st_settle.stTotalRMB.stTotalAll.bcTotalDebitAmount, 6);
    offset += 12;
    sprintf(&tmp[offset], "%03u", st_settle.stTotalRMB.stTotalAll.uiTotalDebitNum);
    offset += 3;
    sdkBcdToAsc(&tmp[offset], st_settle.stTotalRMB.stTotalAll.bcTotalCreditAmount, 6);
    offset += 12;
    sprintf(&tmp[offset], "%03u", st_settle.stTotalRMB.stTotalAll.uiTotalCreditNum);
    offset += 3;
    tmp[offset++] = '0';
    sdkBcdToAsc(&tmp[offset], st_settle.stTotal.stTotalAll.bcTotalDebitAmount, 6);
    offset += 12;
    sprintf(&tmp[offset], "%03u", st_settle.stTotal.stTotalAll.uiTotalDebitNum);
    offset += 3;
    sdkBcdToAsc(&tmp[offset], st_settle.stTotal.stTotalAll.bcTotalCreditAmount, 6);
    offset += 12;
    sprintf(&tmp[offset], "%03u", st_settle.stTotal.stTotalAll.uiTotalCreditNum);
    offset += 3;
    tmp[offset++] = '0';

    IsoSetField(pstIsoMsg, 48, tmp, offset);
}

/*****************************************************************************
** Description :  Pack ISO8583 message of settlement transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettlePackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    u8 tmp[255] = {0};
    s32 i;
    s32 ret;
    ST_MSGINFO *pst_msginfo = NULL;

    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "0020000000C18012");
    if (ret <= 0)
    {
        return 0;
    }
    
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;

    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0500", 4);
    
    // #48
    SettleSetField048(pstIsoMsg);

    // #60
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "00");
    strcat(tmp, gstAppSysCfg.stTransParam.asBatchNO);
    strcat(tmp, "201");
    IsoSetField(pstIsoMsg, 60, tmp, strlen(tmp));

    // #63
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%02d", gstLoginInfo.ucUserNO);
    i = strlen(tmp);
    if (i < 3)
    {
        tmp[2] = 0x20;
    }
    IsoSetField(pstIsoMsg, 63, tmp, 3);

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Get the transaction statistics
** Parameters  :  output:
                  (1)ST_SETTLE *pstSettle : settle information
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : fail
                  (3)SDK_OK : success
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
s32 SettleGetTotalAmount(ST_SETTLE *pstSettle)
{
    ST_TOTAL_ALL    *pst_totalall = &pstSettle->stTotal.stTotalAll;
    ST_TOTAL_TRADE  *pst_totaltrade = &pstSettle->stTotal.stTotalTrans;
    u8 amount[12+1] = {0};
    u8 tmp[16+1] = {0};
    u8 amt[16+1] = {0};
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value3;
    u8 value2;
    s32 count;

    if(NULL == pstSettle)
    {
        return SDK_PARA_ERR;
    }

    memset(pst_totalall, 0, sizeof(ST_TOTAL_INFO));
    memset(pst_totaltrade, 0, sizeof(ST_TOTAL_TRADE));

    //sale total
    memset(st_filter, 0, sizeof(st_filter));
    memset(amt, 0, sizeof(amt));
    count = 0;
    value1 = TRANSID_SALE;
    value2 = FALSE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_ADJUSTED;
    st_filter[1].eMode = FILTER_SIGNEL;
    st_filter[1].pasValue[0] = &value2;
    
    st_filter[2].iId = LOG_STAT_ICCFAILTRANS;
    st_filter[2].eMode = FILTER_SIGNEL;
    st_filter[2].pasValue[0] = &value2;
    
    st_filter[3].iId = LOG_STAT_NEEDREVERSAL;
    st_filter[3].eMode = FILTER_SIGNEL;
    st_filter[3].pasValue[0] = &value2;
    
    st_filter[4].iId = -1;

    RecordGetSum(LOG_MSG_AMOUNT, st_filter, tmp);
    count = RecordGetNumEx(st_filter);
    memset(amt, '0', 12);
    strcpy(&amt[12 - strlen(tmp)], tmp);
    sdkAscToBcd(amount, amt, 12);
    //sdkU32ToBcd(amount, amt, 6);
    pst_totaltrade->uiTotalSaleNum += count;
    pst_totalall->uiTotalDebitNum += count;
    sdkBcdAdd(pst_totaltrade->bcTotalSaleAmount, pst_totaltrade->bcTotalSaleAmount, 6, amount, 6);
    sdkBcdAdd(pst_totalall->bcTotalDebitAmount, pst_totalall->bcTotalDebitAmount, 6, amount, 6);
    
    //refund total
    memset(st_filter, 0, sizeof(st_filter));
    memset(amt, 0, sizeof(amt));
    count = 0;
    value1 = TRANSID_REFUND;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
        
    st_filter[1].iId = -1;

    RecordGetSum(LOG_MSG_AMOUNT, st_filter, tmp);
    count = RecordGetNumEx(st_filter);
    memset(amt, '0', 12);
    strcpy(&amt[12 - strlen(tmp)], tmp);
    sdkAscToBcd(amount, amt, 12);
    //sdkU32ToBcd(amount, amt, 6);
    pst_totaltrade->uiTotalRefundNum += count;
    pst_totalall->uiTotalCreditNum += count;
    sdkBcdAdd(pst_totaltrade->bcTotalRefundAmount, pst_totaltrade->bcTotalRefundAmount, 6, amount, 6);
    sdkBcdAdd(pst_totalall->bcTotalCreditAmount, pst_totalall->bcTotalCreditAmount, 6, amount, 6);
    
    //void total
    memset(st_filter, 0, sizeof(st_filter));
    memset(amt, 0, sizeof(amt));
    count = 0;
    value1 = TRANSID_VOID;
    value2 = FALSE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_NEEDREVERSAL;
    st_filter[1].eMode = FILTER_SIGNEL;
    st_filter[1].pasValue[0] = &value2;
        
    st_filter[2].iId = -1;

    RecordGetSum(LOG_MSG_AMOUNT, st_filter, tmp);
    count = RecordGetNumEx(st_filter);
    memset(amt, '0', 12);
    strcpy(&amt[12 - strlen(tmp)], tmp);
    sdkAscToBcd(amount, amt, 12);
    //sdkU32ToBcd(amount, amt, 6);
    pst_totaltrade->uiTotalVoidNum += count;
    pst_totalall->uiTotalCreditNum += count;
    sdkBcdAdd(pst_totaltrade->bcTotalVoidAmount, pst_totaltrade->bcTotalVoidAmount, 6, amount, 6);
    sdkBcdAdd(pst_totalall->bcTotalCreditAmount, pst_totalall->bcTotalCreditAmount, 6, amount, 6);
    
    //adjust total
    memset(st_filter, 0, sizeof(st_filter));
    memset(amt, 0, sizeof(amt));
    count = 0;
    value1 = TRANSID_TIP;
    value3 = TRANSID_ADJUST;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_MULTI;
    st_filter[0].pasValue[0] = &value1;
    st_filter[0].pasValue[1] = &value3;
    st_filter[0].iNum = 2;
        
    st_filter[1].iId = -1;

    RecordGetSum(LOG_MSG_AMOUNT, st_filter, tmp);
    count = RecordGetNumEx(st_filter);
    memset(amt, '0', 12);
    strcpy(&amt[12 - strlen(tmp)], tmp);
    sdkAscToBcd(amount, amt, 12);
    //sdkU32ToBcd(amount, amt, 6);
    pst_totaltrade->uiTotalSaleNum += count;
    pst_totalall->uiTotalDebitNum += count;
    sdkBcdAdd(pst_totaltrade->bcTotalSaleAmount, pst_totaltrade->bcTotalSaleAmount, 6, amount, 6);
    sdkBcdAdd(pst_totalall->bcTotalDebitAmount, pst_totalall->bcTotalDebitAmount, 6, amount, 6);
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload all offline transactions process
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  (2)bool *pbIsResend : whether have upload fail transactions
                  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTransOffline(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i;
    s32 offset = 0;
    ST_TRANSLOG st_translog;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2, value3;

    if (BATCHUP_ICLOG == pstBatchInfo->ucBatchUpType)
    {
        return SDK_OK;
    }

    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_ADJUST;
    value2 = TRANSID_TIP;
    value3 = UPLOAD_BATCH_DONE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_MULTI;
    st_filter[0].pasValue[0] = &value1;
    st_filter[0].pasValue[1] = &value2;
    st_filter[0].iNum = 2;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_LESS_THAN;
    st_filter[1].pasValue[0] = &value3;

    if(BATCHUP_RMB == pstBatchInfo->ucBatchUpType)
    {
        st_filter[2].iId = LOG_MSG_INTERORGCODE;
        st_filter[2].eMode = FILTER_SIGNEL;
        st_filter[2].pasValue[0] = "CUP";
    
        st_filter[3].iId = -1;
    }
    else
    {
        st_filter[2].iId = -1;
    }
    
    cnt = RecordGetNumEx(st_filter);
    Trace("settle", "MAG OFFLINE TRANS NUM = %d\r\n", cnt);
    for(i = 0; i < cnt; i++)
    {
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }
        
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        gstTransData.stTransLog.eTransID = st_translog.eTransID;

        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackOfflineTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            *pbIsResend = 1;
            continue;
        }
        else
        {
            if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
            }
            else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
            }
        }

        //update translog
        RecordUpdate(&st_translog);
        offset++;
        
        pstBatchInfo->uiBatchUpNum++;
        BatchUpSaveInfo(pstBatchInfo);
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload all ICC offline transactions process
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  (2)bool *pbIsResend : whether have upload fail transactions
                  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTransIccOffline(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i;
    s32 offset = 0;
    ST_TRANSLOG st_translog;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2;
    bool value3;

    if (BATCHUP_ICLOG == pstBatchInfo->ucBatchUpType)
    {
        return SDK_OK;
    }

    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_SALE;
    value2 = UPLOAD_BATCH_DONE;
    value3 = TRUE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_LESS_THAN;
    st_filter[1].pasValue[0] = &value2;
    
    st_filter[2].iId = LOG_STAT_OFFLINE;
    st_filter[2].eMode = FILTER_SIGNEL;
    st_filter[2].pasValue[0] = &value3;

    if(BATCHUP_RMB == pstBatchInfo->ucBatchUpType)
    {
        st_filter[3].iId = LOG_MSG_INTERORGCODE;
        st_filter[3].eMode = FILTER_SIGNEL;
        st_filter[3].pasValue[0] = "CUP";
    
        st_filter[4].iId = -1;
    }
    else
    {
        st_filter[3].iId = -1;
    }
    
    cnt = RecordGetNumEx(st_filter);
    Trace("settle", "ICC OFFLINE TRANS NUM = %d\r\n", cnt);
    for(i = 0; i < cnt; i++)
    {
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
        
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        gstTransData.stTransLog.eTransID = st_translog.eTransID;
        
        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackIccOfflineTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            *pbIsResend = 1;
            continue;
        }
        else
        {
            if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
            }
            else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
            }
        }

        //update translog
        RecordUpdate(&st_translog);
        offset++;
        
        pstBatchInfo->uiBatchUpNum++;
        BatchUpSaveInfo(pstBatchInfo);
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload all magnetic stripe transactions process
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  (2)bool *pbIsResend : whether have upload fail transactions
                  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTransAllMag(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend)
{    
    s32 ret = 0;
    s32 cnt = 0;
    s32 i, j;
    s32 len = 0;
    s32 offsend_cnt = 0;
    s32 offset = 0;
    s32 offset_send = 0;
    u8 buf[1024] = {0};
    u8 tmp[1024] = {0};
    ST_TRANSLOG st_translog;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2, value3;

    if (BATCHUP_ICLOG == pstBatchInfo->ucBatchUpType)
    {
        return SDK_OK;
    }

    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_SALE;
    value2 = TRANSID_VOID;
    value3 = UPLOAD_BATCH_DONE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_MULTI;
    st_filter[0].pasValue[0] = &value1;
    st_filter[0].pasValue[1] = &value2;
    st_filter[0].iNum = 2;
    
    st_filter[1].iId = LOG_MSG_ENTRYMODE;
    st_filter[1].eMode = FILTER_MULTI;
    st_filter[1].pasValue[0] = "021";
    st_filter[1].pasValue[1] = "022";
    st_filter[1].iNum = 2;
    
    st_filter[2].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[2].eMode = FILTER_LESS_THAN;
    st_filter[2].pasValue[0] = &value3;

    if(BATCHUP_RMB == pstBatchInfo->ucBatchUpType)
    {
        st_filter[3].iId = LOG_MSG_INTERORGCODE;
        st_filter[3].eMode = FILTER_SIGNEL;
        st_filter[3].pasValue[0] = "CUP";
    
        st_filter[4].iId = -1;
    }
    else
    {
        st_filter[3].iId = -1;
    }
        
    offsend_cnt = 0;
    cnt = RecordGetNumEx(st_filter);
    Trace("settle", "ALL MAG TRANS NUM = %d\r\n", cnt);
    memset(buf, 0, sizeof(buf));
    for(i = 0; i < cnt; i++)
    {
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset_send, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }
                
        if(0 != memcmp(st_translog.stMsgInfo.asInterOrgCode, "CUP", 3))
        {
            memcpy(&buf[offsend_cnt*40], "01", 2);
        }
        else
        {
            memcpy(&buf[offsend_cnt*40], "00", 2);
        }
        sprintf((u8 *)buf+offsend_cnt*40+2, "%s", st_translog.stMsgInfo.asTraceNO);
        memset(tmp, '0', 20);
        len = strlen(st_translog.stCardInfo.stCardData.asCardNO);
        memcpy(tmp + 20 - len, st_translog.stCardInfo.stCardData.asCardNO, len);
        memcpy(buf + offsend_cnt * 40 + 8, tmp, 20);
        memcpy(buf + offsend_cnt * 40 + 28, st_translog.stMsgInfo.asAmount, 12);
        offsend_cnt++;
        if(BATCHUP_ONCE_NUM != offsend_cnt)
        {
            continue;
        }

        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        sprintf(gstTransData.asAdditionInfo, "%02d", offsend_cnt);
        memcpy(gstTransData.asAdditionInfo + 2, buf, offsend_cnt*40);
        gstTransData.stTransLog.eTransID = st_translog.eTransID;

        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackAllMagTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            offsend_cnt = 0;
            memset(buf, 0, sizeof(buf));
            *pbIsResend = 1;
            offset += BATCHUP_ONCE_NUM;
            continue;
        }
        else
        {
            for(j = 0; j < offsend_cnt; j++)
            {
                memset(&st_translog, 0, sizeof(ST_TRANSLOG));
                ret = RecordSearchEx(st_filter, offset, &st_translog);
                if(SDK_OK != ret)
                {
                    return SDK_ERR;
                }

                if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
                {
                    st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
                }
                else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
                {
                    st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
                }
                else
                {
                    st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
                }
                //update translog
                RecordUpdate(&st_translog);
            }
        }
        
        pstBatchInfo->uiBatchUpNum += BATCHUP_ONCE_NUM;
        offset_send += BATCHUP_ONCE_NUM;
        BatchUpSaveInfo(pstBatchInfo);
        offsend_cnt = 0;
        memset(buf, 0, sizeof(buf));
    }

    if(0 != offsend_cnt)
    {
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        sprintf(gstTransData.asAdditionInfo, "%02d", offsend_cnt);
        memcpy(gstTransData.asAdditionInfo + 2, buf, offsend_cnt*40);
        gstTransData.stTransLog.eTransID = st_translog.eTransID;

        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackAllMagTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            offsend_cnt = 0;
            *pbIsResend = 1;
            return SDK_OK;
        }
        else
        {
            for(j = 0; j < offsend_cnt; j++)
            {
                ret = RecordSearchEx(st_filter, offset, &st_translog);
                if(SDK_OK != ret)
                {
                    return SDK_ERR;
                }

                if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
                {
                    st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
                }
                else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
                {
                    st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
                }
                else
                {
                    st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
                }
                //update translog
                RecordUpdate(&st_translog);
            }
        }
        
        pstBatchInfo->uiBatchUpNum += offsend_cnt;
        offset_send += offsend_cnt;
        BatchUpSaveInfo(pstBatchInfo);
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload all advice transactions process
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  (2)bool *pbIsResend : whether have upload fail transactions
                  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTransAdvice(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i;
    s32 offset = 0;
    ST_TRANSLOG st_translog;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2;

    if (BATCHUP_ICLOG == pstBatchInfo->ucBatchUpType)
    {
        return SDK_OK;
    }

    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_REFUND;
    value2 = UPLOAD_BATCH_DONE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
        
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_LESS_THAN;
    st_filter[1].pasValue[0] = &value2;

    if(BATCHUP_RMB == pstBatchInfo->ucBatchUpType)
    {
        st_filter[2].iId = LOG_MSG_INTERORGCODE;
        st_filter[2].eMode = FILTER_SIGNEL;
        st_filter[2].pasValue[0] = "CUP";
    
        st_filter[3].iId = -1;
    }
    else
    {
        st_filter[2].iId = -1;
    }
    
    cnt = RecordGetNumEx(st_filter);
    Trace("settle", "ADVICE TRANS NUM = %d\r\n", cnt);
    for(i = 0; i < cnt; i++)
    {
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }        
        
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        gstTransData.stTransLog.eTransID = st_translog.eTransID;

        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackAdviceTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            *pbIsResend = 1;
            continue;
        }
        else
        {
            if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
            }
            else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
            }
        }

        //update translog
        RecordUpdate(&st_translog);
        offset++;
        
        pstBatchInfo->uiBatchUpNum++;
        BatchUpSaveInfo(pstBatchInfo);
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload all ICC success transactions process
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  (2)bool *pbIsResend : whether have upload fail transactions
                  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTransAllIcc(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i;
    s32 offset = 0;
    ST_TRANSLOG st_translog;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2;
    bool value3;

    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_SALE;
    value2 = UPLOAD_BATCH_DONE;
    value3 = FALSE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_LESS_THAN;
    st_filter[1].pasValue[0] = &value2;
    
    st_filter[2].iId = LOG_STAT_OFFLINE;
    st_filter[2].eMode = FILTER_SIGNEL;
    st_filter[2].pasValue[0] = &value3;
    
    st_filter[3].iId = LOG_MSG_ENTRYMODE;
    st_filter[3].eMode = FILTER_MULTI;
    st_filter[3].pasValue[0] = "051";
    st_filter[3].pasValue[1] = "052";
    st_filter[3].pasValue[2] = "071";
    st_filter[3].pasValue[3] = "072";
    st_filter[3].pasValue[4] = "981";
    st_filter[3].pasValue[5] = "982";
    st_filter[3].iNum = 6;

    st_filter[4].iId = -1;

    cnt = RecordGetNumEx(st_filter);
    Trace("settle", "ALL ICC TRANS NUM = %d\r\n", cnt);
    for(i = 0; i < cnt; i++)
    {
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }

        if(st_translog.stEmvInfo.heTVR[4] & 0x40)
        {
            continue; //ARPC wrong
        }
                
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        gstTransData.stTransLog.eTransID = st_translog.eTransID;

        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackAllIccTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            *pbIsResend = 1;
            continue;
        }
        else
        {
            if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
            }
            else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
            }
        }

        //update translog
        RecordUpdate(&st_translog);
        offset++;
        
        pstBatchInfo->uiBatchUpNum++;
        BatchUpSaveInfo(pstBatchInfo);
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload all ICC failed transactions process
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  (2)bool *pbIsResend : whether have upload fail transactions
                  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTransAllIccFail(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i;
    s32 offset = 0;
    ST_TRANSLOG st_translog;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2;
    bool value3;

    if (BATCHUP_ICLOG == pstBatchInfo->ucBatchUpType)
    {
        return SDK_OK;
    }

    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_SALE;
    value2 = UPLOAD_BATCH_DONE;
    value3 = TRUE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_LESS_THAN;
    st_filter[1].pasValue[0] = &value2;
    
    st_filter[2].iId = LOG_STAT_ICCFAILTRANS;
    st_filter[2].eMode = FILTER_SIGNEL;
    st_filter[2].pasValue[0] = &value3;

    st_filter[3].iId = -1;
    
    cnt = RecordGetNumEx(st_filter);
    Trace("settle", "ALL ICC FAIL TRANS NUM = %d\r\n", cnt);
    for(i = 0; i < cnt; i++)
    {
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }

        if(0 != st_translog.stEmvInfo.ucCID)
        {
            continue;
        }
            
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        gstTransData.stTransLog.eTransID = st_translog.eTransID;

        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackAllFailIccTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            *pbIsResend = 1;
            continue;
        }
        else
        {
            if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
            }
            else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
            }
        }
        
        //update translog
        RecordUpdate(&st_translog);
        offset++;
        
        pstBatchInfo->uiBatchUpNum++;
        BatchUpSaveInfo(pstBatchInfo);
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload all ICC success but ARPC wrong transactions process
** Parameters  :  input:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  (2)bool *pbIsResend : whether have upload fail transactions
                  output:
                  (1)ST_BATCHUP_INFO *pstBatchInfo : batch upload information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTransAllIccArpcErr(ST_BATCHUP_INFO *pstBatchInfo, bool *pbIsResend)
{
    s32 ret = 0;
    s32 cnt = 0;
    s32 i;
    s32 offset = 0;
    ST_TRANSLOG st_translog;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2;
    bool value3;

    memset(st_filter, 0, sizeof(st_filter));
    value1 = TRANSID_SALE;
    value2 = UPLOAD_BATCH_DONE;
    value3 = FALSE;

    st_filter[0].iId = LOG_TRANSID;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value1;
    
    st_filter[1].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[1].eMode = FILTER_LESS_THAN;
    st_filter[1].pasValue[0] = &value2;
    
    st_filter[2].iId = LOG_STAT_OFFLINE;
    st_filter[2].eMode = FILTER_SIGNEL;
    st_filter[2].pasValue[0] = &value3;
    
    st_filter[3].iId = LOG_MSG_ENTRYMODE;
    st_filter[3].eMode = FILTER_MULTI;
    st_filter[3].pasValue[0] = "051";
    st_filter[3].pasValue[1] = "052";
    st_filter[3].pasValue[2] = "071";
    st_filter[3].pasValue[3] = "072";
    st_filter[3].pasValue[4] = "981";
    st_filter[3].pasValue[5] = "982";
    st_filter[3].iNum = 6;

    st_filter[4].iId = -1;

    cnt = RecordGetNumEx(st_filter);
    Trace("settle", "ICC ARPC ERR TRANS NUM = %d\r\n", cnt);
    for(i = 0; i < cnt; i++)
    {
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        ret = RecordSearchEx(st_filter, i - offset, &st_translog);
        if(SDK_OK != ret)
        {
            break;  //no offline transaction need to upload
        }

        if(!(st_translog.stEmvInfo.heTVR[4] & 0x40))
        {
            continue;
        }
        
        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
        memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
        gstTransData.stTransLog.eTransID = st_translog.eTransID;

        memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
        memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
        sdkDispClearRowRam(SDK_DISP_LINE3);
        sdkDispClearRowRam(DispGetMaxLine() - 1);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        ret = SettlePackAllArpcErrIccTransMsg(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }

        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_ERR == ret || ERR_RECV == ret)
        {
            return SDK_ERR;
        }
        else if(ERR_RECV_TIMEOUT == ret)
        {
            *pbIsResend = 1;
            continue;
        }
        else
        {
            if (UPLOAD_OFFLINE_FAIL == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFFAIL;
            }
            else if (UPLOAD_OFFLINE_DECLINE == st_translog.stTransStatus.eUploadStatus)
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCHDONE_OFFDECLINE;
            }
            else
            {
                st_translog.stTransStatus.eUploadStatus = UPLOAD_BATCH_DONE;
            }
        }
        
        //update translog
        RecordUpdate(&st_translog);
        offset++;
        
        pstBatchInfo->uiBatchUpNum++;
        BatchUpSaveInfo(pstBatchInfo);
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload  transactions process
** Parameters  :  None
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpTrans(void)
{
    s32 ret = 0;
    s32 i = 0;
    ST_SETTLE st_settle;
    ST_BATCHUP_INFO st_batchinfo;
    u8 no_allsucc;

    DispTitle(STR_TRANS_BATCH_UP);

    SettleReadInfo(&st_settle);
    BatchUpReadInfo(&st_batchinfo);

    if ('1' == st_settle.stTotal.ucSettleCode && '1' == st_settle.stTotalRMB.ucSettleCode)
    {
        sdkDispClearRowRam(SDK_DISP_LINE2);
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_BALANCED_BATCHUP, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
    }
    else if ('1' != st_settle.stTotal.ucSettleCode || '1' != st_settle.stTotalRMB.ucSettleCode)
    {
        sdkDispClearRowRam(SDK_DISP_LINE2);
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_UNBALANCED_BATCH_UP, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
    }

    while(i < 3)//st_batchinfo.ucReSendNum + 1)
    {
        /* 1)(when the account reconciliation does not match)
        all offline transaction of magnetic stripe card*/
        ret = BatchUpTransOffline(&st_batchinfo, &no_allsucc);
        if(SDK_OK != ret)
        {
            return ret;
        }
        /* 2)(when the account reconciliation does not match) 
        for successful offline purchase transaction (including the low-value 
        payment application) of debit/credit IC card based on CUPIC standards*/
        ret = BatchUpTransIccOffline(&st_batchinfo, &no_allsucc);
        if(SDK_OK != ret)
        {
            return ret;
        }

        /* 3)(when the account reconciliation does not match)
        for details of online request transaction of magnetic stripe card*/
        ret = BatchUpTransAllMag(&st_batchinfo, &no_allsucc);
        if(SDK_OK != ret)
        {
            return ret;
        }
        /* 4)(when the account reconciliation does notmatch)
        For details of advice transaction of magnetic stripe card and IC card 
        based on CUPIC debit/credit standards including refund and 
        pre-authorization completion (advice) transaction*/
        ret = BatchUpTransAdvice(&st_batchinfo, &no_allsucc);
        if(SDK_OK != ret)
        {
            return ret;
        }
        /* 5) (account reconciliation matches or account reconciliation no matches)
        Submit details of all successful online transactions again for 
        submission of TC value generated through successful transaction of 
        debit/credit IC card based on CUPIC standards*/
        ret = BatchUpTransAllIcc(&st_batchinfo, &no_allsucc);
        if(SDK_OK != ret)
        {
            return ret;
        }
        /* 6)(when account reconciliation matches or account reconciliation no matches)
        Submit details of all failed offline purchase transactions to let the Issuer
        understand all situations for offline purchase transaction of debit/credit IC 
        card based on CUPIC standards*/
        ret = BatchUpTransAllIccFail(&st_batchinfo, &no_allsucc);
        if(SDK_OK != ret)
        {
            return ret;
        }
        /* 7)(when account reconciliation matches or account reconciliation no matches)
        Submit details of all online transactions accepted with ARPC error for the
        Issuer¡®s prevention of debit/credit IC card risk transaction based on CUPIC
        standards*/
        ret = BatchUpTransAllIccArpcErr(&st_batchinfo, &no_allsucc);
        if(SDK_OK != ret)
        {
            return ret;
        }

        if(1 == no_allsucc)
        {
            no_allsucc = 0;
            i++;
            continue;
        }
        break;
    }
    
    /* 8)(when account reconciliation matches or account reconciliation no matches)
    Submit message for end of batch submission*/
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    gstTransData.stTransLog.eTransID = TRANSID_BATCHUP_END;

    ret = CommuExchangeIsoMsg(NULL, SettlePackTrailerMsg, FALSE, FALSE, FALSE);
    if (ret <= 0 && ERR_RESP_CODE != ret)
    {
        return SDK_ERR;
    }

    TrnSetStatus(0);
    BatchUpDeleteInfo();
    return SDK_OK;
}

/*****************************************************************************
** Description :  Batch upload transactions continue process
** Parameters  :  None
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 BatchUpContinue(void)
{
    s32 ret = 0 ;
    ST_SETTLE st_settle;

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CONTINUE_BATCH_UP, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    ret = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
    if(SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return SDK_ESC; 
    }
    
//    ret = BatchUpTrans();
//    if(SDK_OK != ret)
//    {
//        return ret;
//    }
    while(1)
    {
        ret = BatchUpTrans();
        if(SDK_OK == ret)
        {
            break;
        }
        else
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_BATCH_UP_FAILED, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CONTINUE_BATCH_UP, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            
            ret = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
            if(SDK_KEY_ENTER != ret)
            {
                TrnSetStatus(ret);
                return SDK_ERR; 
            }
            //TrnSetStatus(ERR_BATCHUP);
            //return SDK_ERR;
        }
    }

    memset(&st_settle, 0, sizeof(ST_SETTLE));
    
    ret = SettleReadInfo(&st_settle);
    if(SDK_OK != ret) 
    {
        return ret;
    }

    return SettleEndProcess(FALSE);
}

/*****************************************************************************
** Description :  Process after settle and batch up success
** Parameters  :  input:
                  (1)bool bRePrint : whether is reprint
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettleEndProcess(bool bRePrint)
{
    s32 key;
    ST_SETTLE st_settle;
    ST_BATCHUP_INFO st_batch;

    memset(&st_settle, 0, sizeof(ST_SETTLE));

    if(SDK_OK == SettleReadInfo(&st_settle))
    {
        if(SETTLE_SEND == st_settle.ucPrintState)
        {
            SettleDeleteInfo();
            return SDK_OK;
        }
        
        if (SDK_OK == BatchUpReadInfo(&st_batch))
        {
            return SDK_OK;
        }
        
        if (SETTLE_NONE == st_settle.ucPrintState)
        {
            if(SDK_OK != PrintSettleReport(bRePrint))
            {
                DispClearContent();
                sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED, SDK_DISP_DEFAULT);
                sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
                sdkDispBrushScreen();
                sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
                return SDK_ERR;
            }

            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_TRXN_DETAIL, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_NO_OR_YES, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            key = sdkKbWaitKey(SDK_KEY_MASK_0 | SDK_KEY_MASK_1 | SDK_KEY_MASK_ESC, TMR_OPERATE);
            if(SDK_KEY_1 == key)
            {
                if(SDK_OK != ReportPrintTransDetail())
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
                    return SDK_ERR;
                }
            }

            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED_DETAIL, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_NO_OR_YES, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            key = sdkKbWaitKey(SDK_KEY_MASK_0 | SDK_KEY_MASK_1 | SDK_KEY_MASK_ESC, TMR_OPERATE);
            if(SDK_KEY_1 == key)
            {
                if(SDK_OK != ReportPrintErrSendTransDetail())
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
                    return SDK_ERR;
                }
            }
            st_settle.ucPrintState = SETTLE_PRINTED;
            SettleSaveInfo(&st_settle);
        }

        if (SETTLE_PRINTED == st_settle.ucPrintState)
        {
            RecordDeleteAll();
            BatchUpDeleteInfo();
            TrnIncBatchNo(1);
            st_settle.ucPrintState = SETTLE_CLEARED;
            SettleSaveInfo(&st_settle);
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Reprint settle and detail report
** Parameters  :  None
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettleReprint(void)
{
    s32 key;
    ST_SETTLE st_settle;

    memset(&st_settle, 0, sizeof(ST_SETTLE));

    if(SDK_OK == SettleReadInfo(&st_settle))
    {
        if(SDK_OK != PrintSettleReport(TRUE))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
            return SDK_ERR;
        }

        if(SETTLE_NONE == st_settle.ucPrintState)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_TRXN_DETAIL, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_NO_OR_YES, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            key = sdkKbWaitKey(SDK_KEY_MASK_0 | SDK_KEY_MASK_1 | SDK_KEY_MASK_ESC, TMR_OPERATE);
            if(SDK_KEY_1 == key)
            {
                if(SDK_OK != ReportPrintTransDetail())
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
                    return SDK_ERR;
                }
            }

            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED_DETAIL, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_NO_OR_YES, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            key = sdkKbWaitKey(SDK_KEY_MASK_0 | SDK_KEY_MASK_1 | SDK_KEY_MASK_ESC, TMR_OPERATE);
            if(SDK_KEY_1 == key)
            {
                if(SDK_OK != ReportPrintErrSendTransDetail())
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
                    return SDK_ERR;
                }
            }
            st_settle.ucPrintState = SETTLE_PRINTED;
            SettleSaveInfo(&st_settle);
        }
        
        if (SETTLE_PRINTED == st_settle.ucPrintState)
        {
            RecordDeleteAll();
            BatchUpDeleteInfo();
            TrnIncBatchNo(1);
            st_settle.ucPrintState = SETTLE_CLEARED;
            SettleSaveInfo(&st_settle);
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Settlement transaction process
** Parameters  :  None
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 SettleTrans(void)
{
    s32 ret = 0;
    ST_SETTLE st_settle;
    ST_BATCHUP_INFO st_batchinfo;
    ST_MSGINFO *pst_msginfo = NULL;

    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    gstTransData.stTransLog.stMsgInfo.ucCashierNO = gstLoginInfo.ucUserNO;
    gstTransData.stTransLog.eTransID = TRANSID_SETTLE;

    memset(&st_batchinfo, 0, sizeof(ST_BATCHUP_INFO));
    memset(&st_settle, 0, sizeof(ST_SETTLE));

    DispTitle(STR_TRANS_SETTLEMENT);

    if(!TrnCheckCondition(FALSE, TRUE))
    {
        return SDK_ERR;
    }

    if (SDK_OK == BatchUpReadInfo(&st_batchinfo))
    {
        return BatchUpContinue();
    }

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PROCESSING, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    
    // Statistical total number of transactions
    ret = SettleGetTotalAmount(&st_settle);
    if(SDK_OK != ret)
    {
        return ret;
    }

    if(SDK_OK != DispTransTotal(&st_settle))
    {
        return SDK_ERR;
    }

    st_settle.ucPrintState = SETTLE_SEND;
    SettleSaveInfo(&st_settle);    
        
    ret = CommuExchangeIsoMsg(NULL, SettlePackMsg, FALSE, TRUE, FALSE);
    Trace("settle", "CommuExchangeIsoMsg ret = %d", ret);
    if (ret <= 0)
    {
        SettleDeleteInfo();
        return SDK_ERR;
    }

    // save settle response code 
    Trace("settle", "SettleTrans asAdditionInfo = %s", gstTransData.asAdditionInfo);
    st_settle.stTotalRMB.ucSettleCode = gstTransData.asAdditionInfo[30];
    st_settle.stTotal.ucSettleCode = gstTransData.asAdditionInfo[61];
   
    memcpy(st_settle.asMerchID, pst_msginfo->asMerchID, 15);
    memcpy(st_settle.asTermID, pst_msginfo->asTermID, 8);
    memcpy(st_settle.asBatchNO, pst_msginfo->asBatchNO, 6);
    st_settle.ucCashierNO = pst_msginfo->ucCashierNO;
    memcpy(st_settle.asDateTime, pst_msginfo->asTransDate, 4);
    memcpy(&st_settle.asDateTime[4], pst_msginfo->asTransTime, 6);

    st_settle.ucPrintState = SETTLE_NONE;
    
    //save settle info
    SettleSaveInfo(&st_settle);

    if('1' == st_settle.stTotalRMB.ucSettleCode && '1' == st_settle.stTotal.ucSettleCode)
    {
        st_batchinfo.ucBatchUpType = BATCHUP_ICLOG;
    }
    if('1' != st_settle.stTotalRMB.ucSettleCode && '1' == st_settle.stTotal.ucSettleCode)
    {
        st_batchinfo.ucBatchUpType = BATCHUP_RMB;
    }
    if('1' == st_settle.stTotalRMB.ucSettleCode && '1' != st_settle.stTotal.ucSettleCode)
    {
        st_batchinfo.ucBatchUpType = BATCHUP_FRN;
    }
    if('1' != st_settle.stTotalRMB.ucSettleCode && '1' != st_settle.stTotal.ucSettleCode)
    {
        st_batchinfo.ucBatchUpType = BATCHUP_ALL;
    }

    BatchUpSaveInfo(&st_batchinfo);
    
    // batch up
    while(1)
    {
        ret = BatchUpTrans();
        if(SDK_OK == ret)
        {
            break;
        }
        else
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_BATCH_UP_FAILED, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CONTINUE_BATCH_UP, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            
            ret = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
            if(SDK_KEY_ENTER != ret)
            {
                TrnSetStatus(ret);
                return SDK_ERR; 
            }
            //TrnSetStatus(ERR_BATCHUP);
            //return SDK_ERR;
        }
    }
    
    DispTitle(STR_TRANS_SETTLEMENT);
    
    return SettleEndProcess(FALSE);
}

/*****************************************************************************
** Description :  Settlement transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void OnSettle(void)
{
    SettleTrans();
    sdkPEDCancel();
    EmvLedClose();
}


