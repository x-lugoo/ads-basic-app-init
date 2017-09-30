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
static ST_DATABASE TabSysCfg = 
{
    TABNAME_APPSYSCFG,
    TRUE,
    {
        {CFG_ID, "ID",                  DB_PRIMARY_KEY,  0, FALSE, &gstAppSysCfg.iId,                               0},

        {STR(CFG_SYS_BEEP),             DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stSysParam.bIsBeep,                0},
        {STR(CFG_EXTERNAL_PED),         DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stSysParam.bIsExtPED,              0},
        {STR(CFG_RF_READER_MODE),       DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stSysParam.bIsIntRf,               0},
        {STR(CFG_BACKLIGHT),            DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stSysParam.bIsBacklight,           0},
        {STR(CFG_IDLE_TIMER),           DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stSysParam.uiIdleTimer,            0},
        {STR(CFG_LANGUAGE),             DB_DATATYPE_ASC, 0, FALSE, &gstAppSysCfg.stSysParam.asLanguage,             0},

        {STR(CFG_MSG_TPDU),             DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asTPDU,                0},
        {STR(CFG_MSG_NII),              DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNII,                 0},
        {STR(CFG_MSGLEN_TYPE),          DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stCommuParam.eMsgLenType,          0},

        {STR(CFG_DAIL_TIME),            DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stCommuParam.ucDialTime,           0},
        {STR(CFG_REDAIL_TIMES),         DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stCommuParam.ucReDialTimes,        0},
        {STR(CFG_RECV_TIME),            DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stCommuParam.ucRecvTime,           0},
        {STR(CFG_COMMU_MODE),           DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stCommuParam.uiCommuMode,          0},
        {STR(CFG_WITH_SSL),             DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stCommuParam.bIsWithSSL,           0},

        {STR(CFG_DIALUP_PHONE1),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asPhone1,              0},
        {STR(CFG_DIALUP_PHONE2),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asPhone2,              0},
        {STR(CFG_DIALUP_PHONE3),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asPhone3,              0},
        {STR(CFG_DIALUP_PABXNO),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asPabxNO,              0},

        {STR(CFG_GPRS_NEEDUSER),        DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stCommuParam.bIsGprsNeedUser,      0},
        {STR(CFG_GPRS_APN),             DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asGprsAPN,             0},
        {STR(CFG_GPRS_USER),            DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asGprsUser,            0},
        {STR(CFG_GPRS_USERPWD),         DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asGprsUserPwd,         0},
        {STR(CFG_GPRS_HOSTIP),          DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asGprsHostIP1,         0},
        {STR(CFG_GPRS_HOSTPORT),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asGprsHostPort1,       0},

        {STR(CFG_CDMA_USER),            DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asCdmaUser,            0},
        {STR(CFG_CDMA_USERPWD),         DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asCdmaUserPwd,         0},
        {STR(CFG_CDMA_HOSTIP),          DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asCdmaHostIP1,         0},
        {STR(CFG_CDMA_HOSTPORT),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asCdmaHostPort1,       0},

        {STR(CFG_ETHERNET_DHCP),        DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stCommuParam.bIsNetDHCP,           0},
        {STR(CFG_ETHERNET_LOCALIP),     DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNetLocalIP,          0},
        {STR(CFG_ETHERNET_GATEWAY),     DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNetGateway,          0},
        {STR(CFG_ETHERNET_MASK),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNetMask,             0},
        {STR(CFG_ETHERNET_HOSTIP),      DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNetHostIP1,          0},
        {STR(CFG_ETHERNET_HOSTPORT),    DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNetHostPort1,        0},
        {STR(CFG_ETHERNET_DNS1),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNetDNS1,             0},
        {STR(CFG_ETHERNET_DNS2),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asNetDNS2,             0},
            
        {STR(CFG_WIFI_HOSTIP),          DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asWifiHostIP1,          0},
        {STR(CFG_WIFI_HOSTPORT),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.asWifiHostPort1,        0},

        {STR(CFG_WIFI_SSID),            DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.stWifiInfo.ssid,       0},
        {STR(CFG_WIFI_PWD),             DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.stWifiInfo.pwd,        0},
        {STR(CFG_WIFI_AUTH),            DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stCommuParam.stWifiInfo.iAuth,     0},
        {STR(CFG_WIFI_CIPHER),          DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stCommuParam.stWifiInfo.iCipher,   0},
        {STR(CFG_WIFI_DHCP),            DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stCommuParam.stWifiInfo.iDhcp,     0},
        {STR(CFG_WIFI_LOCALIP),         DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.stWifiInfo.cLocalIp,   0},
        {STR(CFG_WIFI_GATEWAY),         DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.stWifiInfo.cGateWay,   0},
        {STR(CFG_WIFI_MASK),            DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.stWifiInfo.cMask,      0},
        {STR(CFG_WIFI_DNS1),            DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.stWifiInfo.cDns1,      0},
        {STR(CFG_WIFI_DNS2),            DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stCommuParam.stWifiInfo.cDns2,      0},

        {STR(CFG_SUPPORT_SALE),         DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsSupportSale,       0},
        {STR(CFG_SUPPORT_VOID),         DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsSupportVoid,       0},
        {STR(CFG_SUPPORT_REFUND),       DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsSupportRefund,     0}, 
        {STR(CFG_SUPPORT_ADJUST),       DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsSupportAdjust,     0}, 

        {STR(CFG_VOID_READCARD),        DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsVoidNeedCard,      0},   
        {STR(CFG_VOID_PIN),             DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsVoidNeedPIN,       0},   
        {STR(CFG_AUTO_LOGON),           DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsAutoLogon,         0},
        {STR(CFG_AUTO_LOGOUT),          DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsAutoLogout,        0},
        {STR(CFG_CHECK_ADMINPWD),       DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsCheckAdminPwd,     0},                
        {STR(CFG_MASK_PAN),             DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsMaskPAN,           0},                
        {STR(CFG_PRINT_MINUSSIGN),      DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsPrintMinusSign,    0},                
        {STR(CFG_REFUND_MAX_AMOUNT),    DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTransParam.asRefundMaxAmount,     0},          
        {STR(CFG_OFF_TRANS_UPTIMES),    DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiOffTransUpTimes,    0},                 
        {STR(CFG_OFF_SALE_AUTOUPNUM),   DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiOffSaleAutoUpNum,   0},                 
        {STR(CFG_REVERSAL_TIMES),       DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiReversalTimes,      0},                 
        {STR(CFG_MAX_TRANS_NUM),        DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiMaxTransNum,        0},                 
        {STR(CFG_PRINT_TIMES),          DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiPrintTimes,         0},                 
        {STR(CFG_PRINT_SIZE),           DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiPrintSize,          0},                 
        {STR(CFG_TIP_RATE),             DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiTipRate,           0},      
        //{STR(CFG_TIP_TIMES),            DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiTipTimes,          0},      
        {STR(CFG_REFUND_MODE),          DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTransParam.uiRefundMode,         0},
        {STR(CFG_TRACE_NO),             DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTransParam.asTraceNO,             0},
        {STR(CFG_BATCH_NO),             DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTransParam.asBatchNO,             0},
        {STR(CFG_TRANS_CTLS),           DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsCTLS,              0},     
        {STR(CFG_TRANS_FALLBACK),       DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsFallback,          0},     
        {STR(CFG_FORCE_ONLINE),         DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsForceOnline,       0},     
        {STR(CFG_PROMPT_ICC),           DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsPromptICC,         0},     
        {STR(CFG_CARD_TRACK1),          DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsEnableTrack1,      0},
        {STR(CFG_CTLS_LED),             DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsLedOn,             0},     
        {STR(CFG_VIRTUAL_LED),          DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stTransParam.bIsVirtualLed,        0},     

        {STR(CFG_DES_TYPE),             DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stSecureKey.bIsTripleDES,          0},     
        {STR(CFG_USE_DUKPT),            DB_DATATYPE_U8,  0, FALSE, &gstAppSysCfg.stSecureKey.bIsUseDUKPT,           0},     
        {STR(CFG_TMK_INDEX),            DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stSecureKey.uiTmkIndex,            0},      
        {STR(CFG_TAK_INDEX),            DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stSecureKey.uiTakIndex,            0},
        {STR(CFG_TPK_INDEX),            DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stSecureKey.uiTpkIndex,            0},

        {STR(CFG_CASHIER_PWD),          DB_DATATYPE_BIN, 0, FALSE, gstAppSysCfg.stUserPwd.stCashier,                sizeof(gstAppSysCfg.stUserPwd.stCashier)},
        {STR(CFG_ADMIN_PWD),            DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stUserPwd.asAdminPwd,               0}, 
        {STR(CFG_SYSTEM_PWD),           DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stUserPwd.asSysPwd,                 0},     

        {STR(CFG_TERMINAL_ID),          DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asTermID,                0},
        {STR(CFG_MERCHANT_ID),          DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asMerchID,               0},
        {STR(CFG_MERCHANT_NAME),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asMerchName,             0},
        {STR(CFG_MERCHANT_ADDR1),       DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asMerchAddr1,            0},
        {STR(CFG_MERCHANT_ADDR2),       DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asMerchAddr2,            0},
        {STR(CFG_MERCHANT_ADDR3),       DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asMerchAddr3,            0},
        {STR(CFG_MERCHANT_TEL),         DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asMerchTel,              0},
        {STR(CFG_CURRENCY_CODE),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asCurrencyCode,          0},
        {STR(CFG_COUNTRY_CODE),         DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asCountryCode,          0},
        {STR(CFG_CURRENCY_NAME),        DB_DATATYPE_ASC, 0, FALSE, gstAppSysCfg.stTermInfo.asCurrencyName,          0},
        {STR(CFG_AMOUNT_DECIMALLEN),    DB_DATATYPE_U32, 0, FALSE, &gstAppSysCfg.stTermInfo.uiAmountDecimalLen,     0},
        {-1, NULL},
    }
};

/*****************************************************************************
** Description :  Initial system configuration
** Parameters  :  None 
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
s32 SetupInitSetting(void)
{
    s32 num = 0;
    u8 i;
    SDK_SYS_INITIAL_INFO st_initial;
    
    if(DB_EXIT_SUCCESS != sdkDbCreateTable(&TabSysCfg))
    {
        Trace("setup", "sdkDbCreateTable fail\r\n");
        return SDK_ERR;         //return SDK_RECORD_CREATE_ERR;         //wsl20160927
    }

    num = sdkDbGetRecordTotalNum(TabSysCfg.pasTabName, NULL, 0);
    Trace("setup", "SetupInitSetting num = %d\r\n", num);
    if(0 == num)
    {
        Trace("setup", "Init All Param\r\n");

        memset(&gstAppSysCfg, 0, sizeof(ST_APP_SYSCFG));

        // system param
        gstAppSysCfg.stSysParam.bIsBeep = TRUE;       
        gstAppSysCfg.stSysParam.bIsExtPED = FALSE,   
        gstAppSysCfg.stSysParam.bIsIntRf = TRUE,  
        gstAppSysCfg.stSysParam.bIsBacklight = TRUE,       
        gstAppSysCfg.stSysParam.uiIdleTimer = 20,

        //commu param
        strcpy(gstAppSysCfg.stCommuParam.asTPDU, "6000000000");
        gstAppSysCfg.stCommuParam.ucReDialTimes = 3;
        gstAppSysCfg.stCommuParam.ucDialTime = 60;
        gstAppSysCfg.stCommuParam.ucRecvTime = 30;
        gstAppSysCfg.stCommuParam.eMsgLenType = LENTYPE_HEX;         

        gstAppSysCfg.stCommuParam.bIsUseBackupFirst = FALSE;
       // gstAppSysCfg.stCommuParam.uiCommuMode = SDK_COMM_GPRS;
		gstAppSysCfg.stCommuParam.uiCommuMode = SDK_COMM_ETHERNET;
        gstAppSysCfg.stCommuParam.bIsWithSSL = FALSE;

        strcpy(gstAppSysCfg.stCommuParam.asPhone1, "8073");
        strcpy(gstAppSysCfg.stCommuParam.asPhone2, "8073");
        strcpy(gstAppSysCfg.stCommuParam.asPhone3, "8073");
        strcpy(gstAppSysCfg.stCommuParam.asPabxNO, "");

        gstAppSysCfg.stCommuParam.bIsGprsNeedUser = FALSE;
        strcpy(gstAppSysCfg.stCommuParam.asGprsAPN, "cmnet");
        strcpy(gstAppSysCfg.stCommuParam.asGprsHostIP1, "219.133.170.86");
        strcpy(gstAppSysCfg.stCommuParam.asGprsHostPort1, "8209");
        strcpy(gstAppSysCfg.stCommuParam.asGprsHostIP2, "219.133.170.86");
        strcpy(gstAppSysCfg.stCommuParam.asGprsHostPort2, "8209");
        
        strcpy(gstAppSysCfg.stCommuParam.asCdmaUser, "card");
        strcpy(gstAppSysCfg.stCommuParam.asCdmaUserPwd, "card");
        strcpy(gstAppSysCfg.stCommuParam.asCdmaHostIP1, "219.133.170.86");
        strcpy(gstAppSysCfg.stCommuParam.asCdmaHostPort1, "8496");
        strcpy(gstAppSysCfg.stCommuParam.asCdmaHostIP2, "219.133.170.86");
        strcpy(gstAppSysCfg.stCommuParam.asCdmaHostPort2, "8496");

        gstAppSysCfg.stCommuParam.bIsNetDHCP = TRUE;
        strcpy(gstAppSysCfg.stCommuParam.asNetHostIP1, "172.23.1.84");
        strcpy(gstAppSysCfg.stCommuParam.asNetHostPort1, "8000");
        strcpy(gstAppSysCfg.stCommuParam.asNetHostIP2, "172.23.1.84");
        strcpy(gstAppSysCfg.stCommuParam.asNetHostPort2, "8000");
        
        strcpy(gstAppSysCfg.stCommuParam.asWifiHostIP1, "172.23.1.133");
        strcpy(gstAppSysCfg.stCommuParam.asWifiHostPort1, "8716");
        strcpy(gstAppSysCfg.stCommuParam.asWifiHostIP2, "172.23.1.133");
        strcpy(gstAppSysCfg.stCommuParam.asWifiHostPort2, "8716");
        
        //Trans param
        gstAppSysCfg.stTransParam.bIsSupportSale = TRUE;
        gstAppSysCfg.stTransParam.bIsSupportVoid = TRUE;
        gstAppSysCfg.stTransParam.bIsSupportRefund = TRUE;
        gstAppSysCfg.stTransParam.bIsSupportAdjust = TRUE;
        gstAppSysCfg.stTransParam.bIsVoidNeedCard = TRUE;
        gstAppSysCfg.stTransParam.bIsVoidNeedPIN = TRUE;
        gstAppSysCfg.stTransParam.bIsAutoLogon = TRUE;
        gstAppSysCfg.stTransParam.bIsAutoLogout = FALSE;
        gstAppSysCfg.stTransParam.bIsCheckAdminPwd = TRUE;
        gstAppSysCfg.stTransParam.bIsMaskPAN = TRUE;
        gstAppSysCfg.stTransParam.bIsPrintMinusSign = TRUE;

        strcpy(gstAppSysCfg.stTransParam.asRefundMaxAmount, "500000000");
        gstAppSysCfg.stTransParam.uiOffTransUpTimes = 3;
        gstAppSysCfg.stTransParam.uiOffSaleAutoUpNum = 10;
        gstAppSysCfg.stTransParam.uiReversalTimes = 3;
        gstAppSysCfg.stTransParam.uiMaxTransNum = 500;
        gstAppSysCfg.stTransParam.uiPrintTimes = 1;
        gstAppSysCfg.stTransParam.uiPrintSize = PRINT_SIZE_BIG;
        gstAppSysCfg.stTransParam.uiTipRate = 20;
        //gstAppSysCfg.stTransParam.uiTipTimes = 10;
        gstAppSysCfg.stTransParam.uiRefundMode = REFUND_MODE_GENERAL;   
        strcpy(gstAppSysCfg.stTransParam.asTraceNO, "000001");
        strcpy(gstAppSysCfg.stTransParam.asBatchNO, "000001");
        gstAppSysCfg.stTransParam.bIsCTLS = TRUE;
        gstAppSysCfg.stTransParam.bIsFallback = FALSE;
        gstAppSysCfg.stTransParam.bIsForceOnline = FALSE;
        gstAppSysCfg.stTransParam.bIsPromptICC = TRUE;
        gstAppSysCfg.stTransParam.bIsEnableTrack1 = FALSE;
        gstAppSysCfg.stTransParam.bIsLedOn = TRUE;
        gstAppSysCfg.stTransParam.bIsVirtualLed = FALSE;

        //Secure param
        gstAppSysCfg.stSecureKey.bIsTripleDES = FALSE;
        gstAppSysCfg.stSecureKey.bIsUseDUKPT = FALSE;
        gstAppSysCfg.stSecureKey.uiTmkIndex = 0;
        gstAppSysCfg.stSecureKey.uiTakIndex = 13;
        gstAppSysCfg.stSecureKey.uiTpkIndex = 14;
        
        //User param
        memset(gstAppSysCfg.stUserPwd.stCashier, 0, sizeof(gstAppSysCfg.stUserPwd.stCashier));
        for (i = 1; i < 6; i++)
        {
            strcpy(gstAppSysCfg.stUserPwd.stCashier[i].asPwd, "0000");
            gstAppSysCfg.stUserPwd.stCashier[i].bIsExist = TRUE;
        }
        strcpy(gstAppSysCfg.stUserPwd.asAdminPwd, "123456");
        strcpy(gstAppSysCfg.stUserPwd.asSysPwd, "88888888");
        
        //Term param
        strcpy(gstAppSysCfg.stTermInfo.asMerchID, "123456789012345");
        strcpy(gstAppSysCfg.stTermInfo.asTermID, "12345678");
        strcpy(gstAppSysCfg.stTermInfo.asMerchName, "NEXGO");
        strcpy(gstAppSysCfg.stTermInfo.asMerchAddr1, "NEXGO");
        strcpy(gstAppSysCfg.stTermInfo.asMerchAddr2, "NEXGO");
        strcpy(gstAppSysCfg.stTermInfo.asMerchAddr3, "NEXGO");
        strcpy(gstAppSysCfg.stTermInfo.asMerchTel, "86319929");
        strcpy(gstAppSysCfg.stTermInfo.asCurrencyCode, "156");
        strcpy(gstAppSysCfg.stTermInfo.asCountryCode, "457");
        strcpy(gstAppSysCfg.stTermInfo.asCurrencyName, "RMB");
        gstAppSysCfg.stTermInfo.uiAmountDecimalLen = 2; 

        st_initial.bIsHavePinPad = gstAppSysCfg.stSysParam.bIsExtPED;
        st_initial.bIsINRf = gstAppSysCfg.stSysParam.bIsIntRf;
        sdkSysReInitParam(&st_initial);

        SetupAppendSetting();
        Trace("setup", "setting db ID = %d\r\n", gstAppSysCfg.iId);
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Setup one item in a setting group
** Parameters  :  input:
                  (1)ST_SETUP_ITEM *pstItem : setup item description
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
s32 SetupItem(ST_SETUP_ITEM *pstItem)
{
    s32 line = SDK_DISP_LINE2;
    u32 i = 0;
    u8 tmp[256];
    u8 buf[256];
    
    DispClearContent();
    while(NULL != pstItem->pasStr[i])
    {
        sdkDispFillRowRam(line++, 0, pstItem->pasStr[i], SDK_DISP_LEFT_DEFAULT);
        i++;
    }
    sdkDispBrushScreen();

    switch(pstItem->eType)
    {
        case SETUP_ASC:
            memset(buf, 0, sizeof(buf));
            memset(tmp, 0, sizeof(tmp));
            strcpy(&tmp[1], pstItem->pAddress);
            tmp[0] = strlen(pstItem->pAddress);
            memcpy(buf, tmp, (tmp[0] + 1));
            Trace("setup", "SetupItem(SETUP_ASC) tmp = %s[%d]", &tmp[1], tmp[0]);
            if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, pstItem->uiMin, pstItem->uiMax, pstItem->uiMmiMask, line))
            {
                return SDK_ERR;
            }
            if(pstItem->bIsNeedSettle && RecordGetNum() > 0)
            {
                if(0 != memcmp(buf, tmp, tmp[0] + 1))
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_SET_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_SETTLE_FIRST, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
                    {
                        return SDK_OK;
                    }
                    else
                    {
                        return SDK_ERR;
                    }
                }
            }
            memset(pstItem->pAddress, 0, pstItem->uiMax);
            strncpy(pstItem->pAddress, &tmp[1], tmp[0]);
            break;

        case SETUP_CHAR:
            memset(tmp, 0, sizeof(tmp));
            sprintf(&tmp[1], "%d", *(u8 *)pstItem->pAddress);
            tmp[0] = strlen(&tmp[1]);
            memcpy(buf, tmp, (tmp[0] + 1));
            Trace("setup", "SetupItem(SETUP_CHAR) tmp = %s[%d]", &tmp[1], tmp[0]);
            if (SDK_KEY_ENTER != TrnGetNumber(TMR_OPERATE, tmp, pstItem->uiMin, pstItem->uiMax, line))
            {
                return SDK_ERR;
            }
            if(pstItem->bIsNeedSettle && RecordGetNum() > 0)
            {
                if(0 != memcmp(buf, tmp, tmp[0] + 1))
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_SET_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_SETTLE_FIRST, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
                    {
                        return SDK_OK;
                    }
                    else
                    {
                        return SDK_ERR;
                    }
                }
            }
            tmp[tmp[0] + 1] = 0;
            *(u8 *)pstItem->pAddress = atoi(&tmp[1]);
            break;
            
        case SETUP_INT:
            memset(tmp, 0, sizeof(tmp));
            sprintf(&tmp[1], "%d", *(u32 *)pstItem->pAddress);
            tmp[0] = strlen(&tmp[1]);
            memcpy(buf, tmp, (tmp[0] + 1));
            Trace("setup", "SetupItem(SETUP_INT) tmp = %s[%d]", &tmp[1], tmp[0]);
            if (SDK_KEY_ENTER != TrnGetNumber(TMR_OPERATE, tmp, pstItem->uiMin, pstItem->uiMax, line))
            {
                return SDK_ERR;
            }
            if(pstItem->bIsNeedSettle && RecordGetNum() > 0)
            {
                if(0 != memcmp(buf, tmp, tmp[0] + 1))
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_SET_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_SETTLE_FIRST, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
                    {
                        return SDK_OK;
                    }
                    else
                    {
                        return SDK_ERR;
                    }
                }
            }
            tmp[tmp[0] + 1] = 0;
            *(u32 *)pstItem->pAddress = atoi(&tmp[1]);
            break;

        case SETUP_IP:
            memset(tmp, 0, sizeof(tmp));
            strcpy(&tmp[1], pstItem->pAddress);
            tmp[0] = strlen(pstItem->pAddress);
            memcpy(buf, tmp, (tmp[0] + 1));
            if (SDK_KEY_ENTER != TrnInputIpAddr(TMR_OPERATE, tmp, line))
            {
                return SDK_ERR;
            }
            if(pstItem->bIsNeedSettle && RecordGetNum() > 0)
            {
                if(0 != memcmp(buf, tmp, tmp[0] + 1))
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_SET_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_SETTLE_FIRST, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
                    {
                        return SDK_OK;
                    }
                    else
                    {
                        return SDK_ERR;
                    }
                }
            }
            memset(pstItem->pAddress, 0, 16);
            strncpy(pstItem->pAddress, &tmp[1], tmp[0]);
            break;

        case SETUP_ASC_NOZERO:
            memset(buf, 0, sizeof(buf));
            memset(tmp, 0, sizeof(tmp));
            strcpy(&tmp[1], pstItem->pAddress);
            tmp[0] = strlen(pstItem->pAddress);
            memcpy(buf, tmp, (tmp[0] + 1));
            Trace("setup", "SetupItem(SETUP_ASC) tmp = %s[%d]", &tmp[1], tmp[0]);
            DispSaveScreen();
            while(1)
            {
                if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, pstItem->uiMin, pstItem->uiMax, pstItem->uiMmiMask, line))
                {
                    return SDK_ERR;
                }
                i = atoi(&tmp[1]);
                if(i == 0)
                {
                    sdkSysBeep(SDK_SYS_BEEP_ERR);
                    continue;
                }
                else
                {
                    break;
                }
            }
            if(pstItem->bIsNeedSettle && RecordGetNum() > 0)
            {
                if(0 != memcmp(buf, tmp, tmp[0] + 1))
                {
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_SET_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_SETTLE_FIRST, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
                    {
                        return SDK_OK;
                    }
                    else
                    {
                        return SDK_ERR;
                    }
                }
            }
            memset(pstItem->pAddress, 0, pstItem->uiMax);
            strncpy(pstItem->pAddress, &tmp[1], tmp[0]);
            break;

        default:
            break;
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Setup a setting group
** Parameters  :  input:
                  (1)ST_SETUP_GROUP *pstGroup : setup group description
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
s32 SetupGroup(ST_SETUP_GROUP *pstGroup)
{
    u32 i = 0;

    if(NULL != pstGroup->asTitle)
    {
        DispTitle(pstGroup->asTitle);
    }
    
    while(-1 != pstGroup->stItem[i].eType)
    {
        if(SDK_OK != SetupItem(&pstGroup->stItem[i]))
        {
            return SDK_ERR;
        }
        i++;
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Read system configuration
** Parameters  :  input:
                  (1)s32 iIndex : index in database
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
s32 SetupReadSetting(s32 iIndex)
{
    memset(&gstAppSysCfg, 0, sizeof(ST_APP_SYSCFG));
    if(DB_EXIT_SUCCESS != sdkDbGetRecordByIndex(TabSysCfg.pasTabName, iIndex, (void *)&TabSysCfg))
    {
        Trace("setup", "sdkDbGetRecordByIndex fail\r\n");
        return SDK_ERR;
    }
    
    return SDK_OK;
}


/*****************************************************************************
** Description :  Append a new system configuration
** Parameters  :  None 
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
s32 SetupAppendSetting(void)
{    
    if(DB_EXIT_SUCCESS != sdkDbInsertRecord(&TabSysCfg))
    {
        Trace("setup", "sdkDbInsertRecord fail\r\n");
        return SDK_ERR;
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Overwrite current system configuration
** Parameters  :  None 
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
s32 SetupSaveSetting(void)
{   
    if(DB_EXIT_SUCCESS != sdkDbUpdateRecord(&TabSysCfg))
    {
        Trace("setup", "sdkDbInsertRecord fail\r\n");
        return SDK_ERR;
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Setup terminal parameter
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTerminalInfo(void)
{    
    ST_TERMINAL_INFO *pst_terminalinfo = &gstAppSysCfg.stTermInfo;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_TERMINAL,
        {
            {SETUP_ASC, 15, 15, pst_terminalinfo->asMerchID, SDK_MMI_LETTER | SDK_MMI_NUMBER, TRUE, 
             {STR_SETUP_MID, NULL}},
            {SETUP_ASC,  8,  8, pst_terminalinfo->asTermID, SDK_MMI_LETTER | SDK_MMI_NUMBER, TRUE, 
             {STR_SETUP_TID, NULL}},
            {SETUP_ASC,  0, 40, pst_terminalinfo->asMerchName, SDK_MMI_LETTER | SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_MERCHANT_NAME, NULL}},
            {SETUP_ASC,  1,  3, pst_terminalinfo->asCountryCode, SDK_MMI_NUMBER, TRUE, 
             {STR_SETUP_COUNTRY_CODE, NULL}},
            {SETUP_ASC,  1,  3, pst_terminalinfo->asCurrencyCode, SDK_MMI_NUMBER, TRUE, 
             {STR_SETUP_CURRENCY_CODE, NULL}},
            {SETUP_ASC,  1,  3, pst_terminalinfo->asCurrencyName, SDK_MMI_LETTER | SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_CURRENCY_NAME, NULL}},
            {SETUP_INT,  0,  3, &pst_terminalinfo->uiAmountDecimalLen, SDK_MMI_NUMBER, TRUE, 
             {STR_SETUP_AMOUNT_CENT_LENGTH, NULL}},
            {-1},
        }
    };

    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup communication mode 
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuMode(void)
{
    s32 ret;
    u8 buf[16] = {0};
    ST_COMMU_PARAM *pst_commparam = &gstAppSysCfg.stCommuParam;
    
    // Display communication mode menu
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_1_MODEM_2_GPRS, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_3_CDMA_4_ETHERNET, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_SETUP_5_WIFI, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    // Choose communication mode
    memset(buf, 0, sizeof(buf));
    buf[0] = 1;

    switch (pst_commparam->uiCommuMode)
    {
         case SDK_COMM_MODEM:
            buf[1] = '1';
            break;

         case SDK_COMM_GPRS:
            buf[1] = '2';
            break;

         case SDK_COMM_CDMA:
            buf[1] = '3';
            break;

         case SDK_COMM_ETHERNET:
            buf[1] = '4';
            break;
            
         case SDK_COMM_WIFI:
            buf[1] = '5';
            break;

         default:
            break;
    }

    ret = TrnGetNumber(TMR_OPERATE, buf, 1, 5, SDK_DISP_LINE5);

    if (SDK_KEY_ENTER != ret)
    {
        return;
    }
    
    switch (buf[1])
    {
         // MODEM
         case SDK_KEY_1:
            pst_commparam->uiCommuMode = SDK_COMM_MODEM;
            break;

         // GPRS
         case SDK_KEY_2:
            pst_commparam->uiCommuMode = SDK_COMM_GPRS;
            break;

         // CDMA
         case SDK_KEY_3:
            pst_commparam->uiCommuMode = SDK_COMM_CDMA;
            break;

         // ETHERNET
         case SDK_KEY_4:
            pst_commparam->uiCommuMode = SDK_COMM_ETHERNET;
            break;
            
         case SDK_KEY_5:
            pst_commparam->uiCommuMode = SDK_COMM_WIFI;
            break;
         default:
           return;
    }
}

/*****************************************************************************
** Description :  Setup medem(dial-up) parameters of communication
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuDial(void)
{
    ST_COMMU_PARAM *pst_commparam = &gstAppSysCfg.stCommuParam;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_MODEM,
        {
            {SETUP_ASC, 1, 20, pst_commparam->asPhone1, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_TEL_NUMBER1, NULL}},
            {SETUP_ASC, 1, 20, pst_commparam->asPhone2, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_TEL_NUMBER2, NULL}},
            {SETUP_ASC, 1, 20, pst_commparam->asPhone3, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_TEL_NUMBER3, NULL}},
            {SETUP_ASC, 0, 7, pst_commparam->asPabxNO, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PABX_NO, NULL}},
            {-1},
        }
    };

    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup GPRS parameters of communication
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuGprs(void)
{
    ST_COMMU_PARAM *pst_commparam = &gstAppSysCfg.stCommuParam;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_GPRS,
        {
            {SETUP_ASC, 0, 20, pst_commparam->asGprsAPN, SDK_MMI_LETTER | SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_APN, NULL}},
            {SETUP_IP,  0, 15, pst_commparam->asGprsHostIP1, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_HOST_IP, NULL}},
            {SETUP_ASC, 1, 5, pst_commparam->asGprsHostPort1, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PORT, NULL}},
            {SETUP_CHAR, 0, 1, &pst_commparam->bIsGprsNeedUser, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_ENABLE_USER, STR_SETUP_YES_OR_NO, NULL}},
            {-1},
        }
    };    
    ST_SETUP_GROUP st_setup_user = 
    {
        STR_SETUP_GPRS,
        {
            {SETUP_ASC, 0, 20, pst_commparam->asGprsUser, SDK_MMI_LETTER | SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_USER, NULL}},
            {SETUP_ASC, 0, 20, pst_commparam->asGprsUserPwd, SDK_MMI_LETTER | SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_USER_PASSWORD, NULL}},
            {-1},
        }
    };
    
    if(SDK_OK == SetupGroup(&st_setup))
    {
        if(pst_commparam->bIsGprsNeedUser)
        {
            SetupGroup(&st_setup_user);
        }
    }
    
    return;
}

/*****************************************************************************
** Description :  Setup CDMA parameters of communication 
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuCdma(void)
{
    ST_COMMU_PARAM *pst_commparam = &gstAppSysCfg.stCommuParam;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_CDMA,
        {
            {SETUP_ASC, 0, 20, pst_commparam->asCdmaUser, SDK_MMI_LETTER | SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_USER_NAME, NULL}},
            {SETUP_ASC, 0, 20, pst_commparam->asCdmaUserPwd, SDK_MMI_LETTER | SDK_MMI_NUMBER, FALSE,
             {STR_INFO_PASSWORD, NULL}},
            {SETUP_IP,  0, 15, pst_commparam->asCdmaHostIP1, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_HOST_IP, NULL}},
            {SETUP_ASC, 1, 5, pst_commparam->asCdmaHostPort1, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PORT, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup ethernet parameters of communication 
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuEthernet(void)
{
    ST_COMMU_PARAM *pst_commparam = &gstAppSysCfg.stCommuParam;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_ETHERNET,
        {
            {SETUP_IP,  0, 15, pst_commparam->asNetHostIP1, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_HOST_IP, NULL}},
            {SETUP_ASC, 1, 5, pst_commparam->asNetHostPort1, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PORT, NULL}},
            {SETUP_CHAR, 0, 1, &pst_commparam->bIsNetDHCP, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_DHCP, STR_SETUP_YES_OR_NO, NULL}},
            {-1},
        }
    };    
    ST_SETUP_GROUP st_setup_local = 
    {
        STR_SETUP_ETHERNET,
        {
            {SETUP_IP,  0, 15, pst_commparam->asNetLocalIP, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_LOCAL_IP, NULL}},
            {SETUP_IP,  0, 15, pst_commparam->asNetMask, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_SUBNET_MASK, NULL}},
            {SETUP_IP,  0, 15, pst_commparam->asNetGateway, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_GATEWAY, NULL}},
            {-1},
        }
    };    
    
    if(SDK_OK == SetupGroup(&st_setup))
    {
        if(!pst_commparam->bIsNetDHCP)
        {
            SetupGroup(&st_setup_local);
        }
    }
    
    return;
}

/*****************************************************************************
** Description :  Setup WIFI parameters of communication 
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuWifiParam(void)
{
    SDK_EXT_WIFI_INFO *pst_wifiinfo = &gstAppSysCfg.stCommuParam.stWifiInfo;
    ST_COMMU_PARAM *pst_commparam = &gstAppSysCfg.stCommuParam;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_WIFI,
        {
            {SETUP_IP,  0, 15, pst_commparam->asWifiHostIP1, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_HOST_IP, NULL}},
            {SETUP_ASC, 1, 5, pst_commparam->asWifiHostPort1, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PORT, NULL}},
            {SETUP_INT, 0, 1, &pst_wifiinfo->iDhcp, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_DHCP, STR_SETUP_YES_OR_NO, NULL}},
            {-1},
        }
    };    
    ST_SETUP_GROUP st_setup_local = 
    {
        STR_SETUP_WIFI,
        {
            {SETUP_IP,  0, 15, pst_wifiinfo->cLocalIp, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_LOCAL_IP, NULL}},
            {SETUP_IP,  0, 15, pst_wifiinfo->cMask, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_SUBNET_MASK, NULL}},
            {SETUP_IP,  0, 15, pst_wifiinfo->cGateWay, SDK_MMI_LETTER, FALSE,
             {STR_SETUP_GATEWAY, NULL}},
            {-1},
        }
    };    
    
    if(SDK_OK == SetupGroup(&st_setup))
    {
        if(!pst_commparam->stWifiInfo.iDhcp)
        {
            SetupGroup(&st_setup_local);
        }
    }

    return;
}

/*****************************************************************************
** Description :  Setup WIFI Hotspots parameters of communication 
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuWifiHotspots(void)
{
    s32 ret  = 0;
    s32 i = 0; 
    s32 list_num = 0;
    s32 num = 20;
    SDKWIFIINFO st_wifilist[20];
    u8 buf[1024] = {0};
    u8 tmp[64] = {0};
    SDK_EXT_WIFI_INFO *pst_wifiinfo = &gstAppSysCfg.stCommuParam.stWifiInfo;
    
    DispTitle(STR_SETUP_WIFI);

    DispClearContent();  
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_OPEN_WIFI_DEVICE, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    
    // Open wifi device 
    ret = sdkWIFIOpen();
    if(SDK_WIFI_SUCCESS != ret)
    {
        DispClearContent();  
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_OPEN_FAILED, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
        return ;
    }

    if(0 < strlen(pst_wifiinfo->ssid))
    {
        DispClearContent();  
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_NEED_SCAN_HOTSPOTS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, "START - [ENTER]", SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE4, 0, "SKIP - [CANCEL]", SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        ret = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
    }

    if(SDK_KEY_ESC != ret)
    {
        memset(pst_wifiinfo->ssid, 0, sizeof(pst_wifiinfo->ssid));
        memset(pst_wifiinfo->pwd, 0, sizeof(pst_wifiinfo->pwd));
        pst_wifiinfo->iAuth = 0;
        pst_wifiinfo->iCipher = 0;
        DispClearContent();  
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_SCAN_HOTSPOTS, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();

        memset(st_wifilist, 0, sizeof(st_wifilist));
        memset(buf, 0, sizeof(buf));
        // It is slow when you search for the first time and it may return error
        // So you can search the second time after 5s.
        for(i = 0; i < 2; i++)
        {
            num = 20;
            // Get wifi SSID list
            ret = sdkWIFIGetSSIDList(st_wifilist, &num);
            if(SDK_WIFI_SUCCESS == ret && num > 0)
            {
                for(i = 0; i < num;i++)
                {
                    memset(tmp,0,sizeof(tmp));
                    if (st_wifilist[i].SecMode < SDK_WIFI_PSK_WEP)
                    {
                        sprintf(tmp, "%d. !%s\r", i + 1, st_wifilist[i].SSID);  // no encryption
                    }
                    else
                    {
                        sprintf(tmp, "%d. %s\r", i + 1, st_wifilist[i].SSID);   
                    }
                    strcat(buf, tmp);
                }
                break;
            }
            else
            {
                sdkmSleep(5000);
            }
        }
        
        if (SDK_WIFI_SUCCESS != ret)
        {
            Trace("setup", "sdkWIFIGetSSIDList ret = %d\r\n", ret);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_SCAN_HOTSPOTS_FAIL, SDK_DISP_DEFAULT);
            return ;
        }

        // Display SSID list
        list_num = sdkDispListBox(STR_SETUP_SELECT_SSID, buf, 0);
        if(list_num < 0 || ret > num)
        {
            Trace("setup", "sdkDispListBox list_num = %d\r\n", list_num);
            return ;
        }
        
        DispTitle(STR_SETUP_WIFI);
        
        if(st_wifilist[list_num].SecMode > SDK_WIFI_PSK_OPEN)
        {        
            memset(tmp, 0, sizeof(tmp));
            DispClearContent();  
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_PWD, SDK_DISP_LEFT_DEFAULT);
            sdkDispBrushScreen();
            
            if (SDK_KEY_ENTER != sdkKbGetScanf(30000, tmp, 0, 63, SDK_MMI_LETTER | SDK_MMI_NUMBER | SDK_MMI_SYMBOL, SDK_DISP_LINE3))
            {
                return;
            }
            if (0 != tmp[0])
            {
                memcpy(pst_wifiinfo->pwd, &tmp[1], tmp[0]);
            }
        }

        memcpy(pst_wifiinfo->ssid, st_wifilist[list_num].SSID, strlen(st_wifilist[list_num].SSID));
        pst_wifiinfo->iAuth = st_wifilist[list_num].SecMode;

        switch(pst_wifiinfo->iAuth)
        {
            case SDK_WIFI_PSK_OPEN:                /**no passwd */
                pst_wifiinfo->iCipher = 0;
                break;
                
            case SDK_WIFI_PSK_WEP:                 /**Open key  WEP*//**Share secret WEP*/         
                pst_wifiinfo->iCipher = SDK_WIFI_CIPHER_WEP|SDK_WIFI_CIPHER_WEP128;
                break;
                
            case SDK_WIFI_PSK_WPAPSK:              /**WPA-PSK*/
            case SDK_WIFI_PSK_WPA2PSK:             /**WPA2-PSK*/
                pst_wifiinfo->iCipher = SDK_WIFI_CIPHER_DEFAULT;
                break;
                
            case SDK_WIFI_PSK_WPACCKM:              /**WPA*/
                pst_wifiinfo->iCipher = SDK_WIFI_CIPHER_DEFAULT;
                break;
                
            default :
                break;
        }
    }
        
    sdkWIFIDisConnect();
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_WIFI_CONNECTING, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    // Making connection
    DispClearContent();
    if(SDK_WIFI_SUCCESS != sdkWIFIConnect(pst_wifiinfo))
    {
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CONNECT_WIFI_FAILED, SDK_DISP_DEFAULT);
    }
    else
    {
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_CONNECT_WIFI_SUCC, SDK_DISP_DEFAULT);
    }
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT); 
}

/*****************************************************************************
** Description :  Display and handles setup WIFI parameters menu item
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuWifi(void)
{     
    ST_MENU st_menu = 
    {
        STR_SETUP_WIFI,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_WIFI_PARAMETER,   SDK_DISP_LDISP, FALSE, 0, SetupCommuWifiParam}, 
            {STR_SETUP_WIFI_HOTSPOTS,    SDK_DISP_LDISP, FALSE, 0, SetupCommuWifiHotspots}, 
            {{0}},
        }
    };

    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Setup other parameters for communication 
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommuOthers(void)
{
    ST_COMMU_PARAM *pst_commparam = &gstAppSysCfg.stCommuParam;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_COMMUNICATION,
        {
            {SETUP_ASC,  10, 10, pst_commparam->asTPDU, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_TPDU, NULL}},
            {SETUP_CHAR, 0, 1, &pst_commparam->bIsWithSSL, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_ENABLE_SSL, STR_SETUP_1_ENABLE, STR_SETUP_0_DISABLE, NULL}},
            {SETUP_CHAR, 0, 1, &pst_commparam->eMsgLenType, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_MSG_LEN_FORMAT, STR_SETUP_0_BCD, STR_SETUP_1_HEX, NULL}},
            {SETUP_CHAR,  15, 60, &pst_commparam->ucDialTime, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_DAIL_TIME, NULL}},
            {SETUP_CHAR,  1, 3, &pst_commparam->ucReDialTimes, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_REDAIL_TIMES, NULL}},
            {SETUP_CHAR,  15, 60, &pst_commparam->ucRecvTime, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_RECV_TIME, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Display and handles setup communication parameters menu item
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupCommu(void)
{     
    ST_MENU st_menu = 
    {
        STR_SETUP_COMMUNICATION,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_COMMU_MODE,   SDK_DISP_LDISP, FALSE, 0, SetupCommuMode}, 
            {STR_SETUP_MODEM,        SDK_DISP_LDISP, FALSE, 0, SetupCommuDial}, 
            {STR_SETUP_GPRS,         SDK_DISP_LDISP, FALSE, 0, SetupCommuGprs},
            {STR_SETUP_CDMA,         SDK_DISP_LDISP, FALSE, 0, SetupCommuCdma},
            {STR_SETUP_ETHERNET,     SDK_DISP_LDISP, FALSE, 0, SetupCommuEthernet}, 
            {STR_SETUP_WIFI,         SDK_DISP_LDISP, FALSE, 0, SetupCommuWifi}, 
            {STR_SETUP_OTHER,        SDK_DISP_LDISP, FALSE, 0, SetupCommuOthers},
            {{0}},
        }
    };

    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Setup suppoort/unsupport the transactions
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTransParamSupport(void)
{
    ST_TRANS_PARAM *pst_trans = &gstAppSysCfg.stTransParam;
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_SHIELD,
        {
            {SETUP_CHAR, 0, 1, &pst_trans->bIsSupportSale, SDK_MMI_NUMBER, FALSE,
             {STR_TRANS_SALE, STR_SETUP_1_SUPPORT, STR_SETUP_0_NOT_SUPPORT, NULL}},
            {SETUP_CHAR, 0, 1, &pst_trans->bIsSupportVoid, SDK_MMI_NUMBER, FALSE,
             {STR_TRANS_VOID, STR_SETUP_1_SUPPORT, STR_SETUP_0_NOT_SUPPORT, NULL}},
            {SETUP_CHAR, 0, 1, &pst_trans->bIsSupportRefund, SDK_MMI_NUMBER, FALSE,
             {STR_TRANS_REFUND, STR_SETUP_1_SUPPORT, STR_SETUP_0_NOT_SUPPORT, NULL}},
            {SETUP_CHAR, 0, 1, &pst_trans->bIsSupportAdjust, SDK_MMI_NUMBER, FALSE,
             {STR_TRANS_TIP, STR_SETUP_1_SUPPORT, STR_SETUP_0_NOT_SUPPORT, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup need PIN or not when do void transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTransParamPassword(void)
{
    ST_TRANS_PARAM *pst_transparam = &gstAppSysCfg.stTransParam;   
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_PIN,
        {
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsVoidNeedPIN, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_VOID_INPUT_PIN, STR_SETUP_YES_OR_NO, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup need read card or not when do void transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTransParamReadCard(void)
{
    ST_TRANS_PARAM *pst_transparam = &gstAppSysCfg.stTransParam;   
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_SWIPE,
        {
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsVoidNeedCard, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_VOID_SWIPE_CARD, STR_SETUP_YES_OR_NO, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup the parameters of settlement transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTransParamSettle(void)
{
    ST_TRANS_PARAM *pst_transparam = &gstAppSysCfg.stTransParam;   
    ST_SETUP_GROUP st_setup = 
    {
        STR_TRANS_SETTLEMENT,
        {
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsAutoLogout, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_AUTO_LOGOUT, STR_SETUP_YES_OR_NO, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup the parameters of offline transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTransParamOffline(void)
{
    ST_TRANS_PARAM *pst_transparam = &gstAppSysCfg.stTransParam;   
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_OFFLINE,
        {
            {SETUP_INT,  1, 9, &pst_transparam->uiOffTransUpTimes, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_OFFLINE_UPLOAD_TIMES, STR_SETUP_1_9,NULL}},
            {SETUP_INT,  1, 10, &pst_transparam->uiOffSaleAutoUpNum, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_AUTO_UPLOAD_NUM, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Setup other parameters for transction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTransParamOthers(void)
{
    ST_TRANS_PARAM *pst_transparam = &gstAppSysCfg.stTransParam;   
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_OTHER,
        {
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsCheckAdminPwd, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_INPUT_ADMIN_PWD, STR_SETUP_YES_OR_NO, NULL}},
            {SETUP_ASC,  1, 9, pst_transparam->asRefundMaxAmount, SDK_MMI_POINT, FALSE,
             {STR_SETUP_MAX_REFUND_AMT, NULL}},
            {SETUP_INT,  1, 100, &pst_transparam->uiTipRate, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_TIP_RATE, NULL}},
            //{SETUP_INT,  1, 10, &pst_transparam->uiTipTimes, SDK_MMI_NUMBER, FALSE,
             //{"TIP TIMES:", NULL}},
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsCTLS, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PAYPASS_PAYWAVE, STR_SETUP_1_ENABLE, STR_SETUP_0_DISABLE, NULL}},
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsFallback, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_FALLBACK, STR_SETUP_1_ENABLE, STR_SETUP_0_DISABLE, NULL}},
            {SETUP_INT,  0, 1, &pst_transparam->uiRefundMode, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_REFUND_MODE, STR_SETUP_0_GENERAL, STR_SETUP_1_CHINA_UNION_PAY, NULL}},
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsAutoLogon, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_AUTO_LOGON, STR_SETUP_1_ENABLE, STR_SETUP_0_DISABLE, NULL}},
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsVirtualLed, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_VIRTUAL_RF_LED, STR_SETUP_1_ENABLE, STR_SETUP_0_DISABLE, NULL}},
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsMaskPAN, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_MASK_CARD_NO, STR_SETUP_YES_OR_NO, NULL}},
            {SETUP_CHAR, 0, 1, &pst_transparam->bIsPrintMinusSign, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_VOID_AMT_PRINT, STR_SETUP_YES_OR_NO, NULL}},
            {-1},
        }
    };    
    
    SetupGroup(&st_setup);
    
    return;
}

/*****************************************************************************
** Description :  Display and handles setup transaction parameters menu item
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupTransParam(void)
{
    ST_MENU st_menu = 
    {
        STR_SETUP_TRANSACTION,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_SHIELD,  SDK_DISP_LDISP, FALSE, 0, SetupTransParamSupport}, 
            {STR_SETUP_PIN,   SDK_DISP_LDISP, FALSE, 0, SetupTransParamPassword},
            {STR_SETUP_SWIPE,   SDK_DISP_LDISP, FALSE, 0, SetupTransParamReadCard},
            //{"SETTLEMENT", SDK_DISP_LDISP, FALSE, 0, SetupTransParamSettle},
            {STR_SETUP_OFFLINE,    SDK_DISP_LDISP, FALSE, 0, SetupTransParamOffline},
            {STR_SETUP_OTHER, SDK_DISP_LDISP, FALSE, 0, SetupTransParamOthers},
            {{0}},
        }
    };

    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Setup system parameters
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupSystemParam(void)
{    
    SDK_SYS_INITIAL_INFO st_initial;
    ST_TRANS_PARAM *pst_transparam = &gstAppSysCfg.stTransParam;   
    ST_SETUP_GROUP st_setup = 
    {
        STR_SETUP_SYSTEM,
        {
            {SETUP_ASC_NOZERO, 6, 6, pst_transparam->asTraceNO, SDK_MMI_HEX, FALSE,
             {STR_SETUP_CURRENT_TRACE_NO, NULL}},
            {SETUP_ASC_NOZERO, 6, 6, pst_transparam->asBatchNO, SDK_MMI_HEX, FALSE,
             {STR_SETUP_CURRENT_BATCH_NO, NULL}},
            {SETUP_INT, 1, 3, &pst_transparam->uiPrintTimes, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PRINT_TIMES, NULL}},
            {SETUP_INT, 1, 3, &pst_transparam->uiPrintSize, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PRINT_SIZE, STR_SETUP_1_BIG_2_MEDIUM, STR_SETUP_3_SMALL, NULL}},
            {SETUP_INT, 1, 3, &pst_transparam->uiReversalTimes, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_REVERSAL_TIMES, NULL}},
            {SETUP_INT, 1, 500, &pst_transparam->uiMaxTransNum, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_MAX_TRANS_NUM, STR_SETUP_1_500, NULL}},
            {SETUP_CHAR, 0, 1, &gstAppSysCfg.stSysParam.bIsExtPED, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_PINPAD_MODE, STR_SETUP_0_INTERNAL, STR_SETUP_1_EXTERNAL, NULL}},
            {SETUP_CHAR, 0, 1, &gstAppSysCfg.stSysParam.bIsIntRf, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_RF_READER_MODE, STR_SETUP_0_EXTERNAL, STR_SETUP_1_INTERNAL, NULL}},
            {SETUP_INT, 0, 60, &gstAppSysCfg.stSysParam.uiIdleTimer, SDK_MMI_NUMBER, FALSE,
             {STR_SETUP_IDLE_TIME, NULL}},
            {-1},
        }
    };
    
    SetupGroup(&st_setup);
    
    st_initial.bIsHavePinPad = gstAppSysCfg.stSysParam.bIsExtPED;
    st_initial.bIsINRf = gstAppSysCfg.stSysParam.bIsIntRf;
    sdkSysReInitParam(&st_initial);
    
    return;
}

/*****************************************************************************
** Description :  Inject the TMK
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupSecureTmk(void)
{
    s32 index;
    u8 tmp[33] = {0};
    u8 key[33] = {0};
     
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_KEY_INDEX_0_9, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    if (SDK_KEY_ENTER != TrnGetNumber(TMR_OPERATE, tmp, 0, 9, SDK_DISP_LINE3))
    {
        return;
    }
    index = tmp[1] - 0x30;

    memset(tmp, 0, sizeof(tmp));
    if(0 == gstAppSysCfg.stSecureKey.bIsTripleDES)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_PLS_INPUT_TMK_16, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, 16, 16, SDK_MMI_HEX, SDK_DISP_LINE3))
        {
            return;
        }
    }
    else
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_PLS_INPUT_TMK_32, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, 32, 32, SDK_MMI_HEX, SDK_DISP_LINE3))
        {
            return;
        }
    }
    sdkAscToBcd(key, &tmp[1], tmp[0]);
    DispClearContent();
    if(SDK_OK == sdkPEDUpdateTmk(index, gstAppSysCfg.stSecureKey.bIsTripleDES, key, 30000))
    {
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_INJECT_TMK_SUCCESS, SDK_DISP_LEFT_DEFAULT);
    }
    else
    {
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_INJECT_TMK_FAILED, SDK_DISP_LEFT_DEFAULT);
    }
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT);
}

/*****************************************************************************
** Description :  Setup the index for TMK
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupSecureTmkIndex(void)
{
    u8 tmp[33] = {0};
    ST_SECURE_KEY *pst_key = &gstAppSysCfg.stSecureKey;     
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_KEY_INDEX_0_9, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    if (SDK_KEY_ENTER != TrnGetNumber(TMR_OPERATE, tmp, 0, 9, SDK_DISP_LINE3))
    {
        return;
    }

    pst_key->uiTmkIndex = atoi(&tmp[1]);
}

/*****************************************************************************
** Description :  Setup DES type
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupSecureDesType(void)
{
    u8 tmp[33] = {0};
    ST_SECURE_KEY *pst_key = &gstAppSysCfg.stSecureKey;     
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_KEY_ALGORITHM, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_0_DES_1_3DES, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    sprintf(&tmp[1], "%d", pst_key->bIsTripleDES);
    tmp[0] = 1;
    if (SDK_KEY_ENTER != TrnGetNumber(TMR_OPERATE, tmp, 0, 1, SDK_DISP_LINE4))
    {
        return;
    }
    pst_key->bIsTripleDES = atoi(&tmp[1]);
}

/*****************************************************************************
** Description :  Setup use DUKPT or not and inject DUKPT key
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupSecureDukpt(void)
{
    s32 len;
    u8 tmp[33] = {0};
    u8 key[33] = {0};
    u8 ksn[33] = {0};    
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_DUKPT, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_1_SUPPORT, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_SETUP_0_NOT_SUPPORT, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    sprintf(&tmp[1], "%d", gstAppSysCfg.stSecureKey.bIsUseDUKPT);
    tmp[0] = 1;
    if (SDK_KEY_ENTER != TrnGetNumber(TMR_OPERATE, tmp, 0, 1, SDK_DISP_LINE5))
    {
        return;
    }
    gstAppSysCfg.stSecureKey.bIsUseDUKPT = tmp[1] - 0x30;

    if(gstAppSysCfg.stSecureKey.bIsUseDUKPT)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_KSN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(tmp, 0, sizeof(tmp));
        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, 20, 20, SDK_MMI_HEX, SDK_DISP_LINE3))
        {
            return;
        }

        sdkAscToBcd(ksn, &tmp[1], tmp[0]);

        memset(tmp, 0, sizeof(tmp));
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_PLS_INPUT_TMK_32, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, 32, 32, SDK_MMI_HEX, SDK_DISP_LINE3))
        {
            return;
        }
        len = 16;

        sdkAscToBcd(key, &tmp[1], tmp[0]);
        DispClearContent();
        if(SDK_OK == sdkPEDDukptLoadAndInit(SDK_PED_DUKPT_UPDATE_ALL, key, len, ksn, 10, 500))
        {
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_INJECT_TMK_SUCCESS, SDK_DISP_LEFT_DEFAULT);
        }
        else
        {
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_INJECT_TMK_FAILED, SDK_DISP_LEFT_DEFAULT);
        }
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT);
    }
}

/*****************************************************************************
** Description :  Display and handles setup secure parameters menu item
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupSecure(void)
{
    ST_MENU st_menu = 
    {
        STR_SETUP_KEY_MANAGEMENT,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_MANUAL_INPUT_KEY,  SDK_DISP_LDISP, FALSE, 0, SetupSecureTmk}, 
            {STR_SETUP_KEY_INDEX,   SDK_DISP_LDISP, FALSE, 0, SetupSecureTmkIndex},
            {STR_SETUP_DES_TYPE,   SDK_DISP_LDISP, FALSE, 0, SetupSecureDesType},
            {STR_SETUP_DUPKT, SDK_DISP_LDISP, FALSE, 0, SetupSecureDukpt},
            {{0}},
        }
    };

    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Setup the password for system administrator
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupPasswordSystem(void)
{
    ST_USER_PWD *pst_param = &gstAppSysCfg.stUserPwd;      
    
    if(TrnPasswordUpdate(STR_SETUP_CHANGE_SYSTEM_PWD, pst_param->asSysPwd, SYSTEM_PWDLEN))
    {
        SetupSaveSetting();

        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_CHANGE_PWD_SUCCESS, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
    }
}

/*****************************************************************************
** Description :  Setup the password for administrator
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupPasswordAdmin(void)
{
    ST_USER_PWD *pst_param = &gstAppSysCfg.stUserPwd;           

    if(TrnPasswordUpdate(STR_SETUP_CHANGE_ADMIN_PWD, pst_param->asAdminPwd, ADMIN_PWDLEN))
    {    
        SetupSaveSetting();

        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_CHANGE_PWD_SUCCESS, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
    }
}

/*****************************************************************************
** Description :  Setup the password of user
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupPassword(void)
{
    ST_MENU st_menu = 
    {
        STR_SETUP_CHANGE_PASSWORD,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_CHANGE_SYSTEM_PWD,  SDK_DISP_LDISP, FALSE, 0, SetupPasswordSystem}, 
            {STR_SETUP_CHANGE_ADMIN_PWD,   SDK_DISP_LDISP, FALSE, 0, SetupPasswordAdmin},
            {{0}},
        }
    };
    
    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Clean reversal related information
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupOthersClearReversal(void)
{
    ST_TRANSLOG *pst_translog = &gstTransData.stTransLog;
    s32 reversal = 1;
    s32 num;

    num = RecordGetNum();
    
    if (0 >= num)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }
   
    while(1)
    {
        if(SDK_OK != RecordSearch(LOG_STAT_NEEDREVERSAL, (void *)&reversal, pst_translog))
        {
            sdkDispClearScreen();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_ClEAR_REV_SUCC, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT);
            return;
        }

        RecordDeleteOne(pst_translog);
    }
}

/*****************************************************************************
** Description :  Clean all records(transaction log)
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupOthersClearBatch(void)
{
    s32 num;

    num = RecordGetNum();
    
    if (0 >= num)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }
    RecordDeleteAll();
    BatchUpDeleteInfo();
    sdkDispClearScreen();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_ClEAR_TRANS_SUCC, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT);
    return;
}

/*****************************************************************************
** Description :  Automatic do sale transaction(for test)
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupOthersAutoTrans(void)
{
    u32 num = 0;
    u8 tmp[16];
    SDK_ICC_TRADE_PARAM st_tradeparam;
    ST_CARDINFO *pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    s32 ret;
    u8 buf[16];
    s32 i;
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_INPUT_TRANS_NUM, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    if (SDK_KEY_ENTER != TrnGetNumber(TMR_OPERATE, tmp, 1, 5000, SDK_DISP_LINE3))
    {
        return;
    }
    num = atoi(&tmp[1]);


    //step1 : initializes the transaction data
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
    gstTransData.stTransLog.eTransID = TRANSID_SALE;

    //step2 : transaction conditions determine

    //step3 : Display title
    DispTitle("SALE");

    //step4 : input transaction amount
    if(SDK_OK != CbEmvInputAmount(gstTransData.stTransLog.stMsgInfo.asAmount))
    {
        return;
    }

    //step5 : Process card
    ret = TrnReadCard(MAGONLY, &st_tradeparam, pst_cardinfo);
    if (ret < 0)
    {
        return;
    }

    if (SDK_OK == ret)
    {
        //step6 : Input Pin
        // Convert BCD-coded amount to display string
        memset(buf, 0, sizeof(buf));
        TrnFormatAmount(buf, gstTransData.stTransLog.stMsgInfo.asAmount, TRUE);
        // Display amount and prompt for password
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_AMOUNT, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, buf, SDK_DISP_RIGHT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_INPUT_PIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();
        // Input password
        ret = TrnInputPin(TRUE, gstTransData.stTransLog.stMsgInfo.asAmount, 
                          &pst_cardinfo->stCardData, gstTransData.hePIN, SDK_DISP_LINE5);
        if (SDK_OK != ret && SDK_PED_NOPIN != ret)
        {
            return;
        }
    }
        
    for(i = 0; i < num; i++)
    {
        CommuExchangeIsoMsg(NULL, SalePackMsg, FALSE, FALSE, TRUE);
        
        gstTransData.stTransLog.stTransStatus.bIsNeedRePrint = FALSE;
        if(SDK_OK != RecordUpdate(&gstTransData.stTransLog))
        {
            TrnSetStatus(ERR_FILE_SYSTEM);
            return;
        }

        if(SDK_KEY_ESC == sdkKbGetKey())
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Show the application version
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupShowVersion(void)
{
    u8 tmp[128];
    ST_DISP_LIST st_list;
    u8 i;
    
    memset(&st_list, 0, sizeof(ST_DISP_LIST));
    
    DispTitle(STR_SETUP_VERSION);

    DispClearContent();
    sprintf(st_list.stItem[st_list.ucNum++].asStr, "%s%s", STR_SETUP_VER, APPVERSION);

    sprintf(st_list.stItem[st_list.ucNum++].asStr, "%s%s", STR_SETUP_DATE, __DATE__);
    sprintf(st_list.stItem[st_list.ucNum++].asStr, "%s%s", STR_SETUP_TIME, __TIME__);
    
    strcat(st_list.stItem[st_list.ucNum].asStr, STR_SETUP_MANAGE);
    memset(tmp, 0, sizeof(tmp));
    sdkSysGetManageVersion(tmp);
    strcat(st_list.stItem[st_list.ucNum++].asStr, tmp);
    
    strcat(st_list.stItem[st_list.ucNum].asStr, STR_SETUP_LIBXGDEMV);
    memset(tmp, 0, sizeof(tmp));
    sdkSysGetLibxgdemvVersion(tmp);
    strcat(st_list.stItem[st_list.ucNum++].asStr, tmp);

    strcat(st_list.stItem[st_list.ucNum].asStr, STR_SETUP_DAEMON);
    memset(tmp, 0, sizeof(tmp));
    sdkSysGetDaemonVersion(tmp);
    strcat(st_list.stItem[st_list.ucNum++].asStr, tmp);

    strcat(st_list.stItem[st_list.ucNum].asStr, STR_SETUP_PANEL);
    memset(tmp, 0, sizeof(tmp));
    sdkSysGetPanelVersion(tmp);
    strcat(st_list.stItem[st_list.ucNum++].asStr, tmp);
            
    strcat(st_list.stItem[st_list.ucNum].asStr, STR_SETUP_LIBDEV);
    memset(tmp, 0, sizeof(tmp));
    sdkSysGetLibdevVersion(tmp);
    strcat(st_list.stItem[st_list.ucNum++].asStr, tmp);

    for(i = 0; i < st_list.ucNum; i++)
    {
        st_list.stItem[i].ucDispAtr = SDK_DISP_LEFT_DEFAULT;
    }
    st_list.iStartLine = SDK_DISP_LINE2;
    st_list.iEndLine = DispGetMaxLine() - 1;
    
    DispListBox(TMR_OPERATE, &st_list);
}

/*****************************************************************************
** Description :  Setup system time
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupSystemTime(void)
{
    u8 tmp[64] = {0}, lcd_temp[64] = {0};
    s32 key = 0;
    u8 key_buf[64] = {0}, disp_buf[64] = {0}, time_format[64] = {0};
    u8 i, j;
    bool flag = TRUE;

    strcpy(time_format, "____-__-__ __:__:__");
    DispTitle(STR_SETUP_SET_TIME);
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_SYSTEM_TIME, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_SETUP_NEW_TIME, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE5, 0, time_format, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    while (1)
    {
        memset(tmp, 0, sizeof(tmp));
        sdkGetRtc(tmp);
        memset(lcd_temp, 0, sizeof(lcd_temp));

        if (tmp[0] < 0x50) //after 2000
        {
            sprintf(lcd_temp, "20%02x-%02x-%02x %02x:%02x:%02x", tmp[0],
                    tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
        }
        else //before 2000
        {
            sprintf(lcd_temp, "19%02x-%02x-%02x %02x:%02x:%02x", tmp[0],
                    tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
        }
        sdkDispRow(SDK_DISP_LINE3, 0, lcd_temp, SDK_DISP_DEFAULT);
        flag = FALSE;
        key = sdkKbGetKey();

        if (key == SDK_KEY_ENTER)
        {
            if(0 == strlen(key_buf))
            {
                sdkSysBeep(SDK_SYS_BEEP_OK);
                return;
            }
            
            if(14 == strlen(key_buf))
            {
                memset(tmp, 0, sizeof(tmp));
                memcpy(tmp, key_buf, 4);

                if (atoi(tmp) > 1950 && atoi(tmp) < 2049)
                {
                    memset(tmp, 0, sizeof(tmp));
                    sdkAscToBcd(tmp, &key_buf[2], 12);
                    if (TrnCheckTime(tmp, 6))
                    {
                        sdkSetRtc(tmp);
                        sdkSysBeep(SDK_SYS_BEEP_OK);
                        return;
                    }
                }
            }

            sdkSysBeep(SDK_SYS_BEEP_ERR);
        }
        else if (key == SDK_KEY_ESC)
        {
            sdkSysBeep(SDK_SYS_BEEP_OK);
            return;
        }
        else if (key == SDK_KEY_BACKSPACE)
        {
            flag = TRUE;
            if (strlen(key_buf) > 0)
            {
                sdkSysBeep(SDK_SYS_BEEP_OK);
                key_buf[strlen(key_buf) - 1] = '\0';
            }
            else
            {
                sdkSysBeep(SDK_SYS_BEEP_ERR);
            }
        }
        else if (key >= SDK_KEY_0 && key <= SDK_KEY_9)
        {
            flag = TRUE;
            if (strlen(key_buf) < 14)
            {
                sdkSysBeep(SDK_SYS_BEEP_OK);
                key_buf[strlen(key_buf)] = key;
            }
            else
            {
                sdkSysBeep(SDK_SYS_BEEP_ERR);
            }
        }
 
        if (flag)
        {
            strcpy(disp_buf, time_format);

            for (i = 0, j = 0; i < strlen(key_buf); i++, j++)
            {
                if (i == 4 || i == 6 || i == 8 || i == 10 || i == 12)
                {
                    j++;
                }
                disp_buf[j] = key_buf[i];
            }
            sdkDispRow(SDK_DISP_LINE5, 0, disp_buf, SDK_DISP_DEFAULT);
        }
    }
}

/*****************************************************************************
** Description :  other setting
** Parameters  :  None 
** Return      :  
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void MenuSetupOthers(void)
{
    ST_MENU st_menu = 
    {
        STR_SETUP_OTHER,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_CLEAR_REVERSAL,  SDK_DISP_LDISP, FALSE, 0, SetupOthersClearReversal}, 
            {STR_SETUP_CLEAR_TRANS,     SDK_DISP_LDISP, FALSE, 0, SetupOthersClearBatch},
            {STR_SETUP_AUTO_TRANS,      SDK_DISP_LDISP, FALSE, 0, SetupOthersAutoTrans},
            {STR_SETUP_VERSION,         SDK_DISP_LDISP, FALSE, 0, SetupShowVersion},
            {STR_SETUP_SET_TIME,        SDK_DISP_LDISP, FALSE, 0, SetupSystemTime},
            {{0}},
        }
    };

    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Main menu of system administrator setting
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void MenuSetup(void)
{
    ST_MENU st_menu = 
    {
        STR_SETUP_SYSTEM_MANAGEMENT,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_TERMINAL,        SDK_DISP_LDISP, FALSE, 0, SetupTerminalInfo}, 
            {STR_SETUP_COMMUNICATION,   SDK_DISP_LDISP, FALSE, 0, SetupCommu},
            {STR_SETUP_TRANSACTION,     SDK_DISP_LDISP, FALSE, 0, SetupTransParam},
            {STR_SETUP_SYSTEM,          SDK_DISP_LDISP, FALSE, 0, SetupSystemParam}, 
            {STR_SETUP_KEY_MANAGEMENT,  SDK_DISP_LDISP, FALSE, 0, SetupSecure},
            {STR_SETUP_CHANGE_PASSWORD, SDK_DISP_LDISP, FALSE, 0, SetupPassword},
            {STR_SETUP_OTHER,           SDK_DISP_LDISP, TRUE,  SDK_KEY_7, MenuSetupOthers},
            {{0}},
        }
    };

    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            DispSaveSetupParam();
            SetupSaveSetting();
            return;
        }
    }
}

/*****************************************************************************
** Description :  Add cashier
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupAddCashier(void)
{
    u32 cashier;
    u8 pwd[8];
    u8 pwd_again[8];
    u8 temp[8];

    DispTitle(STR_SETUP_ADD_CASHIER);

    //verify admin password
    if(!TrnCheckAdminPwd())
    {
        return;
    }
    
    if (!TrnInputAddCashier(&cashier))
    {
        return;
    }
    
    sprintf(temp, "%02d", cashier);
    
    while(1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_CASHIER_NO, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, temp, SDK_DISP_RIGHT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_PLS_INPUT_PWD, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(pwd, 0, sizeof(pwd));
        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, pwd, 4, 4, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE4))
        {
            return;
        }
        
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_CASHIER_NO, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, temp, SDK_DISP_RIGHT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_PLS_INPUT_PWD_AGAIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(pwd_again, 0, sizeof(pwd_again));
        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, pwd_again, 4, 4, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE4))
        {
            return;
        }

        if(0 != memcmp(&pwd[1], &pwd_again[1], pwd_again[0]))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PWD_NOT_MATCH, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                continue;
            }
            return;
        }
        else
        {
            break;
        }
    }

    memcpy(gstAppSysCfg.stUserPwd.stCashier[cashier].asPwd, &pwd[1], pwd[0]);
    gstAppSysCfg.stUserPwd.stCashier[cashier].bIsExist = TRUE;
    DispSaveSetupParam();
    SetupSaveSetting();
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_ADD_SUCCESS, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
    
    return;
}

/*****************************************************************************
** Description :  Query cashier
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupQueryCashier(void)
{
    ST_DISP_LIST st_list;
    u8 i = 0;
    u8 count = 0;
    u32 cashier = 1;
    u8 tmp[16];

    DispTitle(STR_SETUP_INQUIRE_CASHIER);
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_CASHIER_NO, SDK_DISP_LEFT_DEFAULT);

    memset(&st_list, 0, sizeof(ST_DISP_LIST));

    while(1)
    {
        if(gstAppSysCfg.stUserPwd.stCashier[cashier].bIsExist)
        {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%02d ", cashier);
            if(count >= 5)
            {
                count = 0;
                st_list.ucNum++;
            }
            strcat(st_list.stItem[st_list.ucNum].asStr, tmp);
            count++;
        }
        cashier++;
        if(cashier >= CASHIER_NUM)
        {
            break;
        }
    }
    
    for(i = 0; i <= st_list.ucNum; i++)
    {
        st_list.stItem[i].ucDispAtr = SDK_DISP_LEFT_DEFAULT;
    }
    st_list.iStartLine = SDK_DISP_LINE3;
    st_list.iEndLine = DispGetMaxLine() - 1;
    
    DispListBox(TMR_OPERATE, &st_list);
}

/*****************************************************************************
** Description :  Delete cashier
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupDeleteCashier(void)
{
    u32 cashier;

    DispTitle(STR_SETUP_DELETE_CASHIER);

    //verify admin password
    if(!TrnCheckAdminPwd())
    {
        return;
    }

    while(1)
    {
        if (!TrnInputDeleteCashier(&cashier))
        {
            return;
        }
        
        gstAppSysCfg.stUserPwd.stCashier[cashier].bIsExist = FALSE;
        DispSaveSetupParam();
        SetupSaveSetting();
        
        DispTitle(STR_SETUP_DELETE_CASHIER);
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_DETELE_SUCCESS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_CONTINUE, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
        {
            continue;
        }
        else
        {
            break;
        }
    }
    return;
}

/*****************************************************************************
** Description :  Change cashier password
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void SetupChangeCashierPwd(void)
{
    u32 cashier;

    DispTitle(STR_SETUP_CHANGE_CASHIER_PWD);

    if (!TrnInputDeleteCashier(&cashier))
    {
        return;
    }

    if(TrnPasswordUpdate(STR_SETUP_CHANGE_CASHIER_PWD, gstAppSysCfg.stUserPwd.stCashier[cashier].asPwd, CASHIER_PWDLEN))
    {    
        SetupSaveSetting();

        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_SETUP_CHANGE_PWD_SUCCESS, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
    }
}

/*****************************************************************************
** Description :  main menu of administrator setting
** Parameters  :  None 
** Return      :  
** Author      :  wenmin   2016-10-19 
** Remarks     :  
*****************************************************************************/
void MenuAdmin(void)
{
    ST_MENU st_menu = 
    {
        STR_SETUP_ADMIN_MANAGE,
        MENU_NUMBER,
        0,    
        {
            {STR_SETUP_CHANGE_ADMIN_PWD,   SDK_DISP_LDISP, FALSE, 0, SetupPasswordAdmin}, 
            {STR_SETUP_ADD_CASHIER,        SDK_DISP_LDISP, FALSE, 0, SetupAddCashier},
            {STR_SETUP_INQUIRE_CASHIER,    SDK_DISP_LDISP, FALSE, 0, SetupQueryCashier},
            {STR_SETUP_DELETE_CASHIER,     SDK_DISP_LDISP, FALSE, 0, SetupDeleteCashier}, 
            {STR_SETUP_CHANGE_CASHIER_PWD, SDK_DISP_LDISP, FALSE, 0, SetupChangeCashierPwd},
            {{0}},
        }
    };

    while (1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

