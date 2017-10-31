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
** Description :  Update session key 
** Parameters  :  None 
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
                  (3)SDK_PARA_ERR : parameters error
                  (4)SDK_TIME_OUT : timeout

** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
static s32 PedUpdateSessionKey(void)
{
    s32 slt = 0;
    u8 revbuf[128] = {0};
    s32 len = 0;
    s32 num = 0;
    SDK_PED_WK_CFG st_wkcfg;
    SDK_PED_WK_CFG st_allwkcfg[3];

    memset(revbuf, 0, sizeof(revbuf));
    memcpy(revbuf, gstTransData.bcPrivateData, gstTransData.iPrivateDataLen);
    len = gstTransData.iPrivateDataLen;
    if (len < 0)
    {
        return SDK_ERR;
    }

    if (24 != len && 40 != len && 56 != len && 60 != len && 84 != len)
    {
        return SDK_ERR;
    }
    memset(&st_wkcfg, 0, sizeof(st_wkcfg));

    // Update TPK
    if (gstAppSysCfg.stSecureKey.bIsTripleDES)
    {
        st_wkcfg.eTmkType = SDK_PED_DES_TRIPLE;
        st_wkcfg.eWkType = SDK_PED_DES_TRIPLE;
        st_wkcfg.ucTmkIndex = gstAppSysCfg.stSecureKey.uiTmkIndex;
        st_wkcfg.ucEnWkLen = 16;
        memcpy(st_wkcfg.heEnWk, revbuf, 16);
        st_wkcfg.ucCheckDataLen = 16;
        memset(st_wkcfg.heCheckData, 0, 16);
        st_wkcfg.ucWkIndex = gstAppSysCfg.stSecureKey.uiTpkIndex;
        memcpy(st_wkcfg.heCheckValue, &revbuf[16], 4);
        st_wkcfg.ucCheckValueLen = 4;
        st_wkcfg.bOnlyCalcCheckValue = FALSE;
    }
    else
    {
        st_wkcfg.eTmkType = SDK_PED_DES_SINGLE;
        st_wkcfg.eWkType = SDK_PED_DES_SINGLE;
        st_wkcfg.ucTmkIndex = gstAppSysCfg.stSecureKey.uiTmkIndex;
        st_wkcfg.ucEnWkLen = 8;
        memcpy(st_wkcfg.heEnWk, revbuf, 8);
        st_wkcfg.ucCheckDataLen = 8;
        memset(st_wkcfg.heCheckData, 0, 8);
        st_wkcfg.ucWkIndex = gstAppSysCfg.stSecureKey.uiTpkIndex;
        memcpy(st_wkcfg.heCheckValue, &revbuf[8], 4);
        st_wkcfg.ucCheckValueLen = 4;
        st_wkcfg.bOnlyCalcCheckValue = FALSE;
    }
    TraceHex("logon", "heEnWk", st_wkcfg.heEnWk, st_wkcfg.ucEnWkLen);
    TraceHex("logon", "heCheckValue", st_wkcfg.heCheckValue, st_wkcfg.ucCheckValueLen);
    Trace("logon", "eTmkType=%02x,eWkType=%02x,ucTmkIndex=%d,ucWkIndex=%d \r\n", st_wkcfg.eTmkType, st_wkcfg.eWkType, 
        st_wkcfg.ucTmkIndex, st_wkcfg.ucWkIndex);

    st_allwkcfg[num] = st_wkcfg;
    num++;

    // Update TAK
    memset(&st_wkcfg, 0, sizeof(st_wkcfg));

    if (gstAppSysCfg.stSecureKey.bIsTripleDES)
    {
        st_wkcfg.eTmkType = SDK_PED_DES_TRIPLE;
        st_wkcfg.eWkType = SDK_PED_DES_SINGLE;
        st_wkcfg.ucTmkIndex = gstAppSysCfg.stSecureKey.uiTmkIndex;
        st_wkcfg.ucEnWkLen = 8;
        memcpy(st_wkcfg.heEnWk, &revbuf[20], 8);
        st_wkcfg.ucCheckDataLen = 8;
        memset(st_wkcfg.heCheckData, 0, 8);
        st_wkcfg.ucWkIndex = gstAppSysCfg.stSecureKey.uiTakIndex;
        memcpy(st_wkcfg.heCheckValue, &revbuf[36], 4);
        st_wkcfg.ucCheckValueLen = 4;
        st_wkcfg.bOnlyCalcCheckValue = FALSE;
    }
    else
    {
        st_wkcfg.eTmkType = SDK_PED_DES_SINGLE;
        st_wkcfg.eWkType = SDK_PED_DES_SINGLE;
        st_wkcfg.ucTmkIndex = gstAppSysCfg.stSecureKey.uiTmkIndex;
        st_wkcfg.ucEnWkLen = 8;
        memcpy(st_wkcfg.heEnWk, &revbuf[12], 8);
        st_wkcfg.ucCheckDataLen = 8;
        memset(st_wkcfg.heCheckData, 0, 8);
        st_wkcfg.ucWkIndex = gstAppSysCfg.stSecureKey.uiTakIndex;
        memcpy(st_wkcfg.heCheckValue, &revbuf[20], 4);
        st_wkcfg.ucCheckValueLen = 4;
        st_wkcfg.bOnlyCalcCheckValue = FALSE;
    }
    TraceHex("logon", "heEnWk", st_wkcfg.heEnWk, st_wkcfg.ucEnWkLen);
    TraceHex("logon", "heCheckValue", st_wkcfg.heCheckValue, st_wkcfg.ucCheckValueLen);
    Trace("logon", "eTmkType=%02x,eWkType=%02x,ucTmkIndex=%d,ucWkIndex=%d \r\n", st_wkcfg.eTmkType, st_wkcfg.eWkType, 
        st_wkcfg.ucTmkIndex, st_wkcfg.ucWkIndex);

    st_allwkcfg[num] = st_wkcfg;
    num++;
    
    slt = sdkPEDUpdateWk(st_allwkcfg, num, SDK_PED_TIMEOUT / 2);
    Trace("logon", "slt=[%d]\r\n", slt);

    return slt;
}

/*****************************************************************************
** Description :  Pack the ISO8583 message of logon transaction
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg: iso8583 packet
                  
** Return      :  (1)0: pack message fail
                  (2)length(non-zero): packet length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 LogonPackMsg(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 ret;
    u8 buf[64];

    ret = IsoPackPublicMsg(pstIsoMsg, &gstTransData, "0020000000C00012");

    if (ret <= 0)
    {
        return 0;
    }
    
    // Message ID
    IsoSetField(pstIsoMsg, SDK_8583_FIELD_MSG, "0800", 4);

    //60Óò
    memset(buf, 0, sizeof(buf));
    strcat(buf, "00");
    // #60.2  batch number
    strcat(buf, gstAppSysCfg.stTransParam.asBatchNO);
    // #60.3  network management information code
    if(gstAppSysCfg.stSecureKey.bIsTripleDES)
    {
        strcat(buf, "003");
    }
    else
    {
        strcat(buf, "001");
    }
    IsoSetField(pstIsoMsg, 60, buf, strlen(buf));

    //63Óò
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%02d ", gstLoginInfo.ucUserNO);
    IsoSetField(pstIsoMsg, 63, buf, strlen(buf));

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Send Logon transaction message
** Parameters  :  None 
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 LogonSendMsg(void)
{
    s32 ret;
    
    // Exchange transaction ISO8538 messages
    if (CommuExchangeIsoMsg(NULL, LogonPackMsg, FALSE, FALSE, FALSE) < 0)
    {
        return SDK_ERR;
    }

    memcpy(gstAppSysCfg.stTransParam.asBatchNO, gstTransData.stTransLog.stMsgInfo.asBatchNO, 6);
    SetupSaveSetting();
	TrnSyncDateTime(&gstTransData);
        
    // Update session keys
    ret = PedUpdateSessionKey();
    if (SDK_OK != ret)
    {
        TrnSetStatus(ERR_UPDATE_KEY);
        return SDK_ERR;
    }

    gstLoginInfo.bIsPosLogon = TRUE;
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Logon transaction process
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void LogonTrans(void)
{
    s32 ret;
    u8 buf[64] = {0};
    u32 cashier;
    ST_MSGINFO *pst_msginfo;

    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    gstTransData.stTransLog.eTransID = TRANSID_LOGON;
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    memcpy(gstTransData.asMTI, "0800", 4);
    memcpy(pst_msginfo->asTraceNO, gstAppSysCfg.stTransParam.asTraceNO, 6);
    
    // Display title
    DispTitle(STR_TRANS_LOGON);

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_USER_NO, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    // Input operator number
    memset(buf, 0, sizeof(buf));
    ret = sdkKbGetScanf(TMR_OPERATE, buf, 1, 2, SDK_MMI_NUMBER, SDK_DISP_LINE3);
    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return;
    }
    cashier = atoi(&buf[1]);
    
    if(SYSADMINNO != cashier && ADMINNO != cashier 
       && (((cashier > (CASHIER_NUM - 1)) || cashier < 1) || !gstAppSysCfg.stUserPwd.stCashier[cashier].bIsExist))
    {
        TrnSetStatus(ERR_USER_NOEXIST);
        return;
    }

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PASSWORD, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    // Input password
    memset(buf, 0, sizeof(buf));
    ret = sdkKbGetScanf(TMR_OPERATE, buf, 4, 8, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE3);
    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return;
    }
    
    if (SYSADMINNO == cashier && 0 == strcmp(&buf[1], gstAppSysCfg.stUserPwd.asSysPwd))
    {
        gstLoginInfo.ucUserNO = cashier;
        gstLoginInfo.bIsCashierLogon = FALSE;
        MenuSetup();
        return;
    }   
    else if (ADMINNO == cashier && 0 == strcmp(&buf[1], gstAppSysCfg.stUserPwd.asAdminPwd))
    {
        gstLoginInfo.ucUserNO = cashier;
        gstLoginInfo.bIsCashierLogon = FALSE;
        MenuAdmin();
        return;
    }
    else if (0 != strcmp(&buf[1], gstAppSysCfg.stUserPwd.stCashier[cashier].asPwd))
    {
        TrnSetStatus(ERR_PASSWORD);
        return;
    }

    // Dial in advance
    CommuPreLink();
    
    gstLoginInfo.ucUserNO = cashier;
    gstLoginInfo.bIsCashierLogon = TRUE;
    gstLoginInfo.bIsPosLogon = FALSE;
    
    LogonSendMsg();

    return;
}

