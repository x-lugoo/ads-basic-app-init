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
#ifndef _SETUP_H_
#define _SETUP_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define TABNAME_APPSYSCFG     "AppSysCfg"

#define ERR_SETTING_BASE         (-1100)

#define ERR_SETTING_INTERNAL     (SDK_RECORD_ERR_BASE - 1)
#define ERR_SETTING_CREATE       (SDK_RECORD_ERR_BASE - 2)
#define ERR_SETTING_READ         (SDK_RECORD_ERR_BASE - 3)
#define ERR_SETTING_WRITE        (SDK_RECORD_ERR_BASE - 4)
#define ERR_SETTING_ID           (SDK_RECORD_ERR_BASE - 5)


#define CASHIER_NUM  10                //cashier total number
#define CASHIER_PWDLEN  4              //cashier password length
#define ADMIN_PWDLEN  6                //administrator password length
#define SYSTEM_PWDLEN  8               //system manager password length

#define SETUP_MAXITEM          32
#define SETUP_MAXPROMPT_LINE   5

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef enum                                           
{                                                    
    CFG_ID,                                       

    /* system */   
    CFG_SYS_BEEP,               // system beep : enable/disable
    CFG_EXTERNAL_PED,           // external pinpad(PED) : enable/disable
    CFG_RF_READER_MODE,         // RF reader mode: internal, external, auto
    CFG_BACKLIGHT,              // LCD backlight : enable/disable
    CFG_IDLE_TIMER,             // system idle countdown timer
    CFG_LANGUAGE,
    
    /* communication */
    CFG_MSG_TPDU,               // TPDU of message
    CFG_MSG_NII,                // #24 network international identifier (NII)
    CFG_MSGLEN_TYPE,            // type of message's length : bcd/hex/asc
    
    CFG_DAIL_TIME,
    CFG_REDAIL_TIMES,
    CFG_RECV_TIME,
    CFG_COMMU_MODE,             // communication mode : dial-up, GPRS, WCDMA, ETHERNET, WIFI
    CFG_WITH_SSL,               // communication with SSL : enable/disable

    CFG_DIALUP_PHONE1,           // dial-up phone
    CFG_DIALUP_PHONE2,           // dial-up phone
    CFG_DIALUP_PHONE3,           // dial-up phone
    CFG_DIALUP_PABXNO,          // PABX NO.(prefix no.)
    
    CFG_GPRS_NEEDUSER,          // GPRS need user name : enable/disable
    CFG_GPRS_APN,               // GPRS APN
    CFG_GPRS_USER,              // GPRS user name
    CFG_GPRS_USERPWD,           // GPRS user password
    CFG_GPRS_HOSTIP,            // GPRS host IP adrress
    CFG_GPRS_HOSTPORT,          // GPRS host port

    CFG_CDMA_USER,              // CDMA user name
    CFG_CDMA_USERPWD,           // CDMA user password
    CFG_CDMA_HOSTIP,            // CDMA host IP address
    CFG_CDMA_HOSTPORT,          // CDMA host port
    
    CFG_ETHERNET_DHCP,          // ethernet DHCP : enable/disable
    CFG_ETHERNET_LOCALIP,       // ethernet local IP address
    CFG_ETHERNET_GATEWAY,       // ethernet gateway
    CFG_ETHERNET_MASK,          // ethernet mask
    CFG_ETHERNET_HOSTIP,        // ethernet host IP address
    CFG_ETHERNET_HOSTPORT,      // ethernet host port
    CFG_ETHERNET_DNS1,          // ethernet DNS 1
    CFG_ETHERNET_DNS2,          // ethernet DNS 2
    
    CFG_WIFI_HOSTIP,        // ethernet host IP address
    CFG_WIFI_HOSTPORT,      // ethernet host port
    
    CFG_WIFI_SSID,              // WIFI Service Set Identifier (SSID)
    CFG_WIFI_PWD,               // WIFI password
    CFG_WIFI_AUTH,              // WIFI authorization
    CFG_WIFI_CIPHER,            // WIFI cipher
    CFG_WIFI_DHCP,              // WIFI DHCP : enable/disable
    CFG_WIFI_LOCALIP,           // WIFI local IP address
    CFG_WIFI_GATEWAY,           // WIFI gateway
    CFG_WIFI_MASK,              // WIFI mask
    CFG_WIFI_DNS1,              // WIFI DNS 1
    CFG_WIFI_DNS2,              // WIFI DNS 1

    // transaction
    CFG_SUPPORT_SALE,           // sale transaction : enable/disable
    CFG_SUPPORT_VOID,           // void transaction : enable/disable
    CFG_SUPPORT_REFUND,         // refund transaction : enable/disable
    CFG_SUPPORT_ADJUST,         // adjust/tip transaction : enable/disable

    CFG_VOID_READCARD,          // read card when doing transactions of void: enable/disable
    CFG_VOID_PIN,               // need PIN when doing transactions of void: enable/disable
    CFG_AUTO_LOGON,
    CFG_AUTO_LOGOUT,            // auto logout after settlement: enable/disable
    CFG_CHECK_ADMINPWD,         // check admin password when doing transactions of void: enable/disable
    CFG_MASK_PAN,               // mask PAN when doing transactions of sale: enable/disalbe.
    CFG_PRINT_MINUSSIGN,
    CFG_REFUND_MAX_AMOUNT,      // max-amount of refund transaction
    CFG_OFF_TRANS_UPTIMES,      // offline transaction upload times
    CFG_OFF_SALE_AUTOUPNUM,     // offline sale auto upload number
    CFG_REVERSAL_TIMES,         // reversal times
    CFG_MAX_TRANS_NUM,          // max. number of transactions
    CFG_PRINT_TIMES,            // print recipt times
    CFG_PRINT_SIZE,             // print recipt size
    CFG_TIP_RATE,               // adjust/tip rate
    CFG_TIP_TIMES,              // adjust/tip times
    CFG_REFUND_MODE,            // refund mode
    CFG_TRACE_NO,               // trace no.
    CFG_BATCH_NO,               // batch no.
    CFG_TRANS_CTLS,             // contactless transaction : enable/disable
    CFG_TRANS_FALLBACK,         // fallback transaction : enable/disable
    CFG_FORCE_ONLINE,           // force online : enable/disable
    CFG_PROMPT_ICC,             // prompt the card is ICC : enable/disable
    CFG_CARD_TRACK1,            // get track-1 data of card : enable/disable                 
    CFG_CTLS_LED,               // LEDs for contactless transaction : enable/disable
    CFG_VIRTUAL_LED,

    // secure key                           
    CFG_DES_TYPE,               // mode of DES encryption: 3des/des
    CFG_USE_DUKPT,              // use DUKPT to encrypt : enable/disable                         
    CFG_TMK_INDEX,              // index of terminal master key(TMK)
    CFG_TAK_INDEX,              // index of terminal MAC key(TAK)
    CFG_TPK_INDEX,              // index of terminal PIN key(TPK) 

    // password                         
    CFG_CASHIER_PWD,            // cashier password
    CFG_ADMIN_PWD,              // admin password
    CFG_SYSTEM_PWD,             // system password

    // terminal info 
    CFG_TERMINAL_ID,            // terminal ID
    CFG_MERCHANT_ID,            // merchant ID
    CFG_MERCHANT_NAME,          // merchant name
    CFG_MERCHANT_ADDR1,         // merchant address 1
    CFG_MERCHANT_ADDR2,         // merchant address 2
    CFG_MERCHANT_ADDR3,         // merchant address 3
    CFG_MERCHANT_TEL,           // merchant telephone no.

    // others
    CFG_CURRENCY_CODE,          // currency code
    CFG_COUNTRY_CODE,
    CFG_CURRENCY_NAME,          // currency name
    CFG_AMOUNT_DECIMALLEN,      // lenght of decimal for amount(x.xx, x.xxx, ...)  
}E_SYSCFG_TAB; 

typedef enum
{
    LENTYPE_BCD = 0,
    LENTYPE_HEX,
    LENTYPE_ASC,
}E_MSGLEN_TYPE;

typedef enum
{
    SETUP_ASC, 
    SETUP_CHAR, 
    SETUP_INT, 
    SETUP_IP,  
    SETUP_ASC_NOZERO,
}E_SETUP_TYPE;

typedef struct
{
    E_SETUP_TYPE eType;
    u32 uiMin;
    u32 uiMax;
    void *pAddress;
    u32 uiMmiMask;
    bool bIsNeedSettle;
    u8 *pasStr[SETUP_MAXPROMPT_LINE + 1];
}ST_SETUP_ITEM;

typedef struct
{
    u8 asTitle[64];
    ST_SETUP_ITEM stItem[SETUP_MAXITEM + 1];
}ST_SETUP_GROUP;

typedef struct         // Multiple application sharing setting 
{
    bool bIsBeep;               // buzzer beep: enable/disable
    bool bIsExtPED;             // external pinpad: enable/disable
    bool bIsIntRf;              // RF reader mode: 0 - auto; 1 - internal; 2 - external
    bool bIsBacklight;          // backlight: enable/disable
    u32  uiIdleTimer;           // countdown timer to let system enter idle mode(0: keep no idle, >= 5 unit:second)
    u8 asLanguage[32 + 1];      // Language
}ST_SYS_PARAM;

// Communication
typedef struct                                                                      
{                                                                                   
    // General
    u8 asTPDU[12];                  // TPDU
    u8 asNII[3+1];                  // #24 network international identifier (NII)
    u8 ucReDialTimes;
    u8 ucDialTime;
    u8 ucRecvTime;
    E_MSGLEN_TYPE eMsgLenType;      // type of message's length : bcd/hex/asc

    bool bIsUseBackupFirst;         // use backup parameter firstly
    u32 uiCommuMode;                // communication mode
    bool bIsWithSSL;                // communication wiht SSL
    
    // Modem (dial-up)
    u8 asPhone1[28];                // phone number1
    u8 asPhone2[28];                // phone number2
    u8 asPhone3[28];                // phone number3
    u8 asPabxNO[9];                 // PABX number
                                                                                    
    // GPRS                                                  
    bool bIsGprsNeedUser;           // GPRS whether user name and password are needed
    u8 asGprsAPN[52];               // GPRS APN
    u8 asGprsUser[52];              // GPRS user name
    u8 asGprsUserPwd[52];           // GPRS user password
    u8 asGprsHostIP1[17];           // GPRS host IP address
    u8 asGprsHostPort1[7];          // GPRS host port 
    u8 asGprsHostIP2[17];           // GPRS host IP address
    u8 asGprsHostPort2[7];          // GPRS host port 

    // CDMA
    u8 asCdmaUser[52];              // CDMA user name
    u8 asCdmaUserPwd[52];           // CDMA user password
    u8 asCdmaHostIP1[17];           // CDMA host IP address
    u8 asCdmaHostPort1[7];          // CDMA host port
    u8 asCdmaHostIP2[17];           // CDMA host IP address
    u8 asCdmaHostPort2[7];          // CDMA host port
                                                                                    
    // Ethernet parameters                                                         
    bool bIsNetDHCP;                // enable DHCP or not                   
    u8 asNetLocalIP[17];            // ethernet Local IP                                     
    u8 asNetGateway[17];            // ethernet Local gateway                                
    u8 asNetMask[17];               // ethernet Local subnet mask                            
    u8 asNetHostIP1[17];                // ethernet host IP address                            
    u8 asNetHostPort1[7];           // ethernet host port                            
    u8 asNetHostIP2[17];                // ethernet host IP address                            
    u8 asNetHostPort2[7];           // ethernet host port                            
    u8 asNetDNS1[17];               // ethernet DNS 1                                         
    u8 asNetDNS2[17];               // ethernet DNS 2          
    
    // WIFI parameters                                                         
    u8 asWifiHostIP1[17];                // ethernet host IP address                            
    u8 asWifiHostPort1[7];           // ethernet host port                            
    u8 asWifiHostIP2[17];                // ethernet host IP address                            
    u8 asWifiHostPort2[7];           // ethernet host port                            
                                                                                    
    SDK_EXT_WIFI_INFO stWifiInfo;   // WIFI communication parameters
    
}ST_COMMU_PARAM;     


typedef struct
{
    // transactions enable/disable
    bool bIsSupportSale;
    bool bIsSupportVoid;
    bool bIsSupportRefund;
    bool bIsSupportAdjust;

    bool bIsVoidNeedCard;           // read card when doing transactions of void
    bool bIsVoidNeedPIN;            // need PIN when doing transactions of void
    bool bIsAutoLogon;              // do logon transaction automatically before other transaction
    bool bIsAutoLogout;             // do logout transaction automatically after settlement
    bool bIsCheckAdminPwd;          // need chenk admin password when doing transactions of void
    bool bIsMaskPAN;                // mask the PAN when doing thransacions of sale
    bool bIsPrintMinusSign;         // is void transaction need print minus sign
    
    u8  asRefundMaxAmount[12 + 1];  // the max. amount when doing refund transaction
    u32 uiOffTransUpTimes;          // offline transaction upload times
    u32 uiOffSaleAutoUpNum;
    u32 uiReversalTimes;
    u32 uiMaxTransNum;
    u32 uiPrintTimes;
    u32 uiPrintSize;
    u32 uiTipRate;
    u32 uiTipTimes;
    u32 uiRefundMode;
    u8  asTraceNO[6 + 1];
    u8  asBatchNO[6 + 1];
    bool bIsCTLS;
    bool bIsFallback;

    bool bIsForceOnline;
    bool bIsPromptICC;
    bool bIsEnableTrack1;
    bool bIsLedOn;
    bool bIsVirtualLed;
}ST_TRANS_PARAM;

typedef struct
{
    bool bIsTripleDES;
    bool bIsUseDUKPT;
    u32 uiTmkIndex;
    u32 uiTakIndex;
    u32 uiTpkIndex;
}ST_SECURE_KEY;

typedef struct
{
    bool bIsExist;   
    u8 asPwd[CASHIER_PWDLEN + 1];      // cashier password: len - CASHIER_PWDLEN
}ST_CASHIER_PWD;

typedef struct
{
    ST_CASHIER_PWD stCashier[CASHIER_NUM];
    u8 asAdminPwd[ADMIN_PWDLEN + 1];                        // admin password: len - ADMIN_PWDLEN
    u8 asSysPwd[SYSTEM_PWDLEN + 1];                         // system password: len - SYSTEM_PWDLEN
}ST_USER_PWD;

typedef struct
{
    u8 asTermID[8 + 1];             // terminal ID
    u8 asMerchID[15 + 1];           // merchant ID
    u8 asMerchName[40 + 1];     // merchant name
    u8 asMerchAddr1[48 + 1];        // merchant address line 1
    u8 asMerchAddr2[48 + 1];        // merchant address line 2
    u8 asMerchAddr3[48 + 1];        // merchant address line 3
    u8 asMerchTel[20+1];            // merchant telephone
    u8 asCurrencyCode[3 + 1];       // currency code
    u8 asCountryCode[3 + 1];        // currency code
    u8 asCurrencyName[3+1];         // currency name
    u32 uiAmountDecimalLen;         // lenght of decimal for amount(x.xx, x.xxx, ...)  
}ST_TERMINAL_INFO;

typedef struct
{
    s32 iId;
    ST_SYS_PARAM stSysParam;            // system parameters
    ST_COMMU_PARAM stCommuParam;        // communication parameters
    ST_USER_PWD stUserPwd;              // user password
    ST_TRANS_PARAM stTransParam;        // transaction parameters
    ST_SECURE_KEY stSecureKey;          // secure key
    ST_TERMINAL_INFO stTermInfo;        // terminal information

    // others
    
}ST_APP_SYSCFG;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern void MenuSetup(void);
extern void MenuAdmin(void);
extern void MenuSetupOthers(void);

// setting file
extern s32 SetupInitSetting(void);
extern s32 SetupAppendSetting(void);
extern s32 SetupReadSetting(s32 iIndex);
extern s32 SetupSaveSetting(void);

// communication parameters
extern void SetupCommu(void);
extern void SetupCommuCdma(void);
extern void SetupCommuDial(void);
extern void SetupCommuEthernet(void);
extern void SetupCommuGprs(void);
extern void SetupCommuMode(void);
extern void SetupCommuOthers(void);
extern void SetupCommuWifi(void);

// others
extern void SetupOthersAutoTrans(void);
extern void SetupOthersClearBatch(void);
extern void SetupOthersClearReversal(void);

// password
extern void SetupPassword(void);
extern void SetupPasswordAdmin(void);
//extern void SetupPasswordSafety(void);
extern void SetupPasswordSystem(void);

// Secure key
extern void SetupSecure(void);
extern void SetupSecureDesType(void);
extern void SetupSecureDukpt(void);
extern void SetupSecureTmk(void);
extern void SetupSecureTmkIndex(void);

extern void SetupShowVersion(void);
extern void SetupSystemParam(void);
extern void SetupTerminalInfo(void);

// transaction pramaters
extern void SetupTransParam(void);
extern void SetupTransParamOffline(void);
extern void SetupTransParamOthers(void);
extern void SetupTransParamPassword(void);
extern void SetupTransParamReadCard(void);
extern void SetupTransParamSettle(void);
extern void SetupTransParamSupport(void);

//admin
extern void SetupPasswordAdmin(void);
extern void SetupAddCashier(void);
extern void SetupQueryCashier(void);
extern void SetupDeleteCashier(void);
extern void SetupChangeCashierPwd(void);


/*-----------------------------------------------------------------------------*/
#endif

