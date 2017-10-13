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
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef AFX_APP_VARIABLES
#define EXTERN
#else
#define EXTERN extern
#endif

/*-----------------------------------------------------------------------------
*                           INCLUDES
-----------------------------------------------------------------------------*/

/*--------------------- system headers ---------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
#include <time.h>

/*---------------------- sdk headers ----------------------*/
#include "sdkGlobal.h"
#include "sdkexGlobal.h"
#include "sdkiso8583.h"


/*---------------------- app headers ----------------------*/
#include "policy.h"
/*-----------------------------------------------------------------------------
*                          GLOBAL MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define APPVERSION  "BASIC170505101"
#define SUBVERSION  "311003"

//#define T2_DEBUG

#ifdef T2_DEBUG
#define     SDK_ICC_PLS_INSERT_CARD   (SDK_SYS_RET_ERR_MAX + (-8))  // switch to another interface
#define     SDK_ICC_PLS_SEE_PHONE     (SDK_SYS_RET_ERR_MAX + (-9))  // see phone and perform CDCVM
#endif

#define PATH_MTD0_RES "/mtd0/res/"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define TMR_OPERATE  (30*1000)  // Timer for exiting to main menu automatically when no operation
#define TMR_WAITKEY  (5*1000)   // Timer for waiting key to confirm 
#define TMR_PROMPT   (3*1000)   // Timer for prompting
#define TMR_NONE     (0)        // no timeout

#define TMR_REFRESH_TIME     (900)        // welcome screen time refresh timer
#define TMR_CTLS_LED_IDLE    (5000)       // CTLS LED idle timer 

#define FILE_BACKGROUND_BMP  "/mtd0/res/background.bmp"    // background image
#define FILENAME_PRINT_BMP   "printlogo.bmp"               // print title image
#define FILENAME_WELCOME_BMP "welcome.bmp"                 // welcome display image

#define CARDPROC_NONEEDPIN       (100)
#define CARDPROC_OFFLINE_SUCC    (101)
#define CARDPROC_OFFLINE_FAIL    (102)
#define CARDPROC_CTLS_SWITCH     (103)
#define CARDPROC_CTLS_FALLBACK   (104)
#define CARDPROC_DISCOVERY       (105)

//contactless LED indicators
#define LED_G870        0
#define LED_G3          1

#define LED_LEFT_BEGIN_G3    60    //left offset of the first LED
#define LED_TOP_BEGIN_G3     20    //top offset of each LED
#define LED_LEFT_BEGIN_G870  20    //left offset of the first LED
#define LED_TOP_BEGIN_G870   20    //top offset of each LED
#define LED_LEFT_BEGIN_MONO  18    //left offset of the first LED
#define LED_TOP_BEGIN_MONO   0     //top offset of each LED

#define LED_COLOR_SIZE_W     35    //width of the simulated LED indicator displayed on the color screen
#define LED_COLOR_SIZE_H     35    //height of the simulated LED indicator displayed on the color screen
#define LED_COLOR_GAP        20    //gap between two simulated LED indicators

#define LED_MONO_SIZE_W      8     //width of the simulated LED indicator displayed on the monochrome screen
#define LED_MONO_SIZE_H      12    //height of the simulated LED indicator displayed on the monochrome screen
#define LED_MONO_GAP         20    //gap between two simulated LED indicators

#define LED_TOP_LEFT_X(model, led_num)              (((LED_G3 == model) ? LED_LEFT_BEGIN_G3 : LED_LEFT_BEGIN_G870) + led_num * (LED_COLOR_SIZE_W + LED_COLOR_GAP))  //top left X-Y coordinate of each simulated LED indicator
#define LED_TOP_LEFT_Y(model)                               ((LED_G3 == model) ? LED_TOP_BEGIN_G3 : LED_TOP_BEGIN_G870)
#define LED_BOTTOM_RIGHT_X(model, led_num)     (((LED_G3 == model) ? LED_LEFT_BEGIN_G3 : LED_LEFT_BEGIN_G870) + led_num * (LED_COLOR_SIZE_W + LED_COLOR_GAP) + LED_COLOR_SIZE_W)    //bottom right X-Y coordinate of each LED indicator
#define LED_BOTTOM_RIGHT_Y(model)                     (((LED_G3 == model) ? LED_TOP_BEGIN_G3 : LED_TOP_BEGIN_G870) + LED_COLOR_SIZE_H)

#define LED_1                   (0x1 << 3)
#define LED_2                   (0x1 << 2)
#define LED_3                   (0x1 << 1)
#define LED_4                   (0x1 << 0)

#define LED_1_ON                 0x08
#define LED_12_ON                0x0c
#define LED_123_ON               0x0e
#define LED_1234_ON              0x0f
#define LED_1234_OFF             0x00


// Key indices
#define KEYINDEX_TMK         0          // Terminal master key(TMK) index
#define KEYINDEX_TPK         1          // Terminal PIN key(TPK) index
#define KEYINDEX_TAK         2          // Terminal MAC key(TAK) index


#define HANDONLY        SDK_ICC_MANUAL                      //only manual enter card number
#define MAGONLY         SDK_ICC_MAG                         //only use mag card
#define ICCONLY         SDK_ICC_ICC                         //only insert ic card
#define MAGICC          (SDK_ICC_ICC|SDK_ICC_MAG)           //both swipe card and insert card
#define RFONLY          SDK_ICC_RF                          //only tap card
#define ICCRF           (SDK_ICC_ICC|SDK_ICC_RF)            //both tap card and insert card
#define MAGICCHAND      (SDK_ICC_ICC|SDK_ICC_MAG|SDK_ICC_MANUAL)    //both swipe card and insert card and manual enter card number

#define  CARDMODE_MANUAL    "01"    // manual enter card number
#define  CARDMODE_SWIPE     "02"    // swipe card
#define  CARDMODE_INSERT    "05"    // insert card
#define  CARDMODE_QCTLS     "07"    // tap card quick
#define  CARDMODE_MSD       "91"    // MSD
#define  CARDMODE_CTLS      "98"    // tap card

#define TRANS_STATUS_FINISH   1

/*-----------------------------------------------------------------------------
*                          GLOBAL DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef enum 
{
    ERR_NO_CASHIER      = (SDK_APP_RET_ERR_MAX + (-1)),   //is not cashier logon status
    ERR_NO_LOGON        = (SDK_APP_RET_ERR_MAX + (-2)),   //pos is not logon
    ERR_LOGON_FAIL      = (SDK_APP_RET_ERR_MAX + (-3)),   //pos logon fail
    ERR_REPRINT         = (SDK_APP_RET_ERR_MAX + (-4)),   //last print is error
    ERR_SETTLE_STARTED  = (SDK_APP_RET_ERR_MAX + (-5)),   //settlement is not finish
    ERR_FILE_SYSTEM     = (SDK_APP_RET_ERR_MAX + (-6)),   //file system error
    ERR_MEMORY_FULL     = (SDK_APP_RET_ERR_MAX + (-7)),   //flash memory is full
    ERR_TRANSNUM_LIMIT  = (SDK_APP_RET_ERR_MAX + (-8)),   //transaction number is limit
    ERR_TRANS_NOSUPPORT = (SDK_APP_RET_ERR_MAX + (-9)),   //transaction is not support
    ERR_READ_CARD       = (SDK_APP_RET_ERR_MAX + (-10)),  //read card fail
    ERR_ICC_AUTHFAIL    = (SDK_APP_RET_ERR_MAX + (-11)),  //ICC 2nd authorization fail
    ERR_CHIPMAGCARD     = (SDK_APP_RET_ERR_MAX + (-12)),  //swipe a mag card with chip
    ERR_ICC_RESET       = (SDK_APP_RET_ERR_MAX + (-13)),  //icc card reset fail
    ERR_LINK            = (SDK_APP_RET_ERR_MAX + (-14)),  //create link fail
    ERR_LINK_TIMEOUT    = (SDK_APP_RET_ERR_MAX + (-15)),  //create link timeout
    ERR_SEND            = (SDK_APP_RET_ERR_MAX + (-16)),  //send message fail
    ERR_RECV            = (SDK_APP_RET_ERR_MAX + (-17)),  //receive message fail
    ERR_RECV_TIMEOUT    = (SDK_APP_RET_ERR_MAX + (-18)),  //receive message timeout
    ERR_ENCRYPT         = (SDK_APP_RET_ERR_MAX + (-19)),  //encrypt data fail
    ERR_PACK_MSG        = (SDK_APP_RET_ERR_MAX + (-20)),  //pack message fail
    ERR_UNPACK_MSG      = (SDK_APP_RET_ERR_MAX + (-21)),  //unpack message fail
    ERR_RESP_CODE       = (SDK_APP_RET_ERR_MAX + (-22)),  //response code error
    ERR_MSGTYPE         = (SDK_APP_RET_ERR_MAX + (-23)),  //matching message type fail
    ERR_PROCESSCODE     = (SDK_APP_RET_ERR_MAX + (-24)),  //matching process code fail
    ERR_TRACENO         = (SDK_APP_RET_ERR_MAX + (-25)),  //matching trace number fail
    ERR_TRANSAMOUNT     = (SDK_APP_RET_ERR_MAX + (-26)),  //matching transation amount fail
    ERR_BATCHNO         = (SDK_APP_RET_ERR_MAX + (-27)),  //matching batch number fail
    ERR_TERMINALNO      = (SDK_APP_RET_ERR_MAX + (-28)),  //matching terminal ID fail
    ERR_MERCHANTNO      = (SDK_APP_RET_ERR_MAX + (-29)),  //matching merchant ID fail
    ERR_CALCMAC         = (SDK_APP_RET_ERR_MAX + (-30)),  //calc MAC fail
    ERR_PRINT           = (SDK_APP_RET_ERR_MAX + (-31)),  //print receipt fail
    ERR_SETTLE_PRINT    = (SDK_APP_RET_ERR_MAX + (-32)),  //print settlement fail	
    ERR_NOTALLOW_VOID   = (SDK_APP_RET_ERR_MAX + (-33)),  //void transaction is not allow
    ERR_NOTALLOW_ADJUST = (SDK_APP_RET_ERR_MAX + (-34)),  //adjust transaction is not allow
    ERR_ALREADY_VOID    = (SDK_APP_RET_ERR_MAX + (-35)),  //transaction is already voided
    ERR_ALREADY_ADJUSTED= (SDK_APP_RET_ERR_MAX + (-36)),  //transaction is already adjusted
    ERR_DIFF_CARD       = (SDK_APP_RET_ERR_MAX + (-37)),  //the card is different with original card
    ERR_ADJUST_LIMIT    = (SDK_APP_RET_ERR_MAX + (-38)),  //adjust times limit
    ERR_BATCHUP         = (SDK_APP_RET_ERR_MAX + (-39)),  //batch up fail
    ERR_SCRIPTFAIL      = (SDK_APP_RET_ERR_MAX + (-40)),  //execute ICC script fail
    ERR_USER_NOEXIST    = (SDK_APP_RET_ERR_MAX + (-41)),  //user is not exist
    ERR_PASSWORD        = (SDK_APP_RET_ERR_MAX + (-42)),  //password is wrong
    ERR_UPDATE_KEY      = (SDK_APP_RET_ERR_MAX + (-43)),  //update work key fail
    ERR_NO_TRANS        = (SDK_APP_RET_ERR_MAX + (-44)),  //not any transaction record in pos
    ERR_AMT_LIMIT       = (SDK_APP_RET_ERR_MAX + (-45)),  //not any transaction record in pos
    ERR_CASHBACK_LIMIT  = (SDK_APP_RET_ERR_MAX + (-46)),  //not any transaction record in pos
}E_APP_ERRNO;

//transaction IDs
typedef enum
{
    TRANSID_UNKNOWN = 0x00,
    TRANSID_WELCOME,                // welcome menu
    TRANSID_MAINMENU,               // main menu

    TRANSID_LOGON,                  // login transaction
    TRANSID_LOGOUT,                 // logout transaction
    TRANSID_BALANCE,                // balance inquire transaction
    
    TRANSID_SALE,                   // sale transaction
    TRANSID_VOID,                   // void transaction
    TRANSID_REFUND,                 // refund transaction
    TRANSID_ADJUST,                 // adjust transaction for offline settlement
    TRANSID_TIP,                    // tip transaction for sale
    TRANSID_OFFSALE,
    TRANSID_SETTLE,
    
    TRANSID_REVERSAL,
    TRANSID_SCRIPT,

    TRANSID_BATCHUP_TIP,            // batch upload tip
    TRANSID_BATCHUP_TRAILER,        // batch upload trailer 
    TRANSID_BATCHUP_END,            // batch upload end

    TRANSID_REPORT,
    //add new transaction IDs here ...
}E_TRANS_ID;

typedef enum                                                
{   
    //offline upload    
    UPLOAD_OFFLINE_NONE,            //not uploaded                                               
    UPLOAD_OFFLINE_SUCCESS,         //upload success                                           
    UPLOAD_OFFLINE_FAIL,            //fail to upload                                            
    UPLOAD_OFFLINE_DECLINE,         //uploaded but rejected                                                  
                                                                                        
    //batch upload                                           
    UPLOAD_BATCH_DONE,              //batch upload success                              
    UPLOAD_BATCHDONE_OFFFAIL,       //batch upload success but failed to upload this offline transaction before  
    UPLOAD_BATCHDONE_OFFDECLINE,    //batch upload success but host rejected when upload this offline transaction before 

}E_UPLOAD_STATUS;

typedef enum 
{
    TRANS_NORMAL,               // normal
    TRANS_VOIDED,               // already void
    TRANS_REFUNDED,             // already refund
    TRANS_ADJUSTED,             // already adjust
}E_TRANS_STATUS;

// pinpad display amount
typedef enum                                              
{                                                         
    DISPAMOUNT_NORNAL,          // Display amount        
    DISPAMOUNT_NONE,            // Don't display amount   
    DISPAMOUNT_ORGINAL,         // Display original amount
}E_PED_DISPAMOUNT;                                        

// ICC return value
typedef enum
{
    ICCRET_OK               =  0,       // Continue IC transaction
    ICCRET_ONLINE_WAIT      =  1,       // Go online
    ICCRET_OFFLINE_APPROVE  =  2,       // Offline approve
    ICCRET_OFFLINE_DECLINE  =  3,       // Offline decline, error packet needs to be saved
    ICCRET_ONLINE_APPROVE   =  4,       // Online approve
    ICCRET_ONLINE_DECLINE   =  5,       // Online decline
    ICCRET_TRANS_CANCEL     =  6,       // Transaction cancelled
    ICCRET_FALLBACK         =  7,       // Fallback
    ICCRET_ERR              =  8,       // Error
    ICCRET_REVERSAL         =  9,       // Reversal
    ICCRET_EASYFLOW         = 10,       // Simplified flow
    ICCRET_CTLS_FALLBACK    = 11,       // Swiping card repeated
    ICCRET_CTLS_SWITCH      = 12,       // CTLS interface switchs to contact interface
    ICCRET_DISCOVERY        = 13,       // Restart discovery processing
}E_ICCRET;

//Cardreader return contactless transaction type
//0x91-QPBOC, 0x17-paywave IC card, 0x02-paypass IC card, 0x22-paypass Magnetic Stripe card
typedef enum
{
    CTLSTYPE_QUICK   = 0x91,
    CTLSTYPE_PAYWAVE = 0x17,
    CTLSTYPE_PAYPASS = 0x02,
    CTLSTYPE_MSD     = 0x22,
}E_EMV_CTLS_TYPE;

// EMV contactless flow
typedef enum
{
    CTLSFLOW_NORMAL     = 0x00,         // Normal flow
    CTLSFLOW_FULLEMV    = 0x01,         // Contactless PBOC
    CTLSFLOW_QUICK      = 0x02,         // Contactless QPBOC
    CTLSFLOW_MSD        = 0x03,         // Contactless MSD
    CTLSFLOW_FALLBACK   = 0x04,         // Contact fallback
}E_EMV_CTLS_FLOW;

// DUKPT get PIN mode
typedef enum
{
    GETPIN_RELEASE  = 0,    
    GETPIN_DEBUG    = 1,      
    GETPIN_NOUPDATE = 3,  
}E_DUKPT_GETPIN;


// DUKPT get MAC mode
typedef enum
{
    GETMAC_NEWKEY = 1,          //use new key
    GETMAC_OLDKEY = 2,          //use old key
}E_DUKPT_GETMAC;


// card information
typedef struct
{
    SDK_ICC_PARAM stCardParam;
    SDK_ICC_CARDDATA stCardData;    // Must NOT store track1/2/3 data in DB!!!
    u8 asCardHolder[26+1];          // card holder name(MAG/5F20)
    u8 asCVV[4+1];                  // CVV(must be encrypted before being stored in DB!!!)
}ST_CARDINFO;

// ICC transaction data
typedef struct                                              
{ 
    /* request */                                                          
    u8 heAC[8];                     //Tag 9F26(M): Application Cryptogram
    u8 ucCID;                       //Tag 9F27(M): Cryptogram Info Data  
    u8 ucIADLen;                    //IAD length
    u8 heIAD[32];                   //Tag 9F10(M): Issuer Application Data  
    u8 heUN[4];                     //Tag 9F37(M): Unpredictable Number
    u8 heATC[2];                    //Tag 9F36(M): Application Transaction Counter  
    u8 heTVR[5];                    //Tag 95  (M): Terminal Verification Results              
    u8 heTransDate[3];              //Tag 9A  (M): Transaction Date 
    u8 ucTransType;                 //Tag 9C  (M): Transaction Type
    u8 bcTransAmount[6];            //Tag 9F02(M): Transaction Amount  
    u8 bcCurrencyCode[2];           //Tag 5F2A(M): Transaction Currency Code
    u8 bcCountryCode[2];            //Tag 9F1A(M): Terminal Country Code 
    u8 heAIP[2];                    //Tag 82  (M): Application Interchange Profile   
    u8 heTermCap[3];                //Tag 9F33(M): Terminal Capabilities  
    u8 heCVMR[3];                   //Tag 9F34(M): CVM Results
    u8 bcAmountOther[6];            //Tag 9F03(O): Amount Other  
    u8 ucAIDLen;                    //AID length
    u8 heAID[16];                   //Tag 84  (O): Dedicated File Name/Application ID  
    u8 heAppVerNum[2];              //Tag 9F08(O): Application Version Number
    u8 heTermAppVerNum[2];          //Tag 9F09(O): Terminal Application Version Number
    u8 ucTermType;                  //Tag 9F35(O): Terminal Type
    u8 asIFDSN[8];                  //Tag 9F1E(O): IFD Serial Number
    u8 ucCategoryCode;              //Tag 9F53(O): Transaction Category Code
    u8 heTransSeqCnt[4];            //Tag 9F41(O): Transaction Sequence Counter
    u8 ucFFILen;                    //FFI length                        
    u8 heFFI[32];                   //Tag 9F6E(O): Form Factor Indicator
    u8 heIDN[8];                    //Tag 9F4C(O): ICC Dynamic Number  
    u8 bcAOSA[6];                   //Tag 9F5D(O): Available Offline Spending Amount 
    u8 heTSI[2];                    //Tag 9B  (O): Transaction Status Information                                           
    u8 ucPANSN;                     //Tag 5F34(O): Application PAN Sequence Number
    u8 asAppLabel[16+1];            //Tag 50  (O): Application Label
    u8 asAppPreferName[16+1];       //Tag 9F12(O): Application Preferred Name

    /* response */
    u8 ucIssAuthDataLen;            //Issuer Authentication Data length
    u8 heIssAuthData[32];           //Tag 91    : Issuer Authentication Data                                            
    u8 ucScriptResultLen;           //issuer script result length
    u8 heScriptResult[21];          //Tag DF31  : issuer script 71/72 result                                            

    /* RFU */
    u8 ucRFULen;                    //RFU data length
    u8 heRFU[128];                  //RFU data
}ST_EMVINFO;


// transaction message info.
typedef struct
{
    u8 ucCashierNO;                 // Cashier NO.
    
    /* request message */
    u8 heBitmap[16];                // #xx bitmap, 8 or 16 bytes, up to 128 fields
                                    // #02 PAN: stCardInfo->stCardData.asCardNO 
    u8 asProcCode[6+1];             // #03 Processing Code  
    u8 asAmount[12+1];              // #04 Amount   
    u8 asDateTime[10+1];            // #07 Transmission Date & Time 
    u8 asTraceNO[6+1];              // #11 System Trace Audit Number    
                                    // #14 Expiration Date: stCardInfo->stIccData.asExpiredDate 
    u8 asEntryMode[3+1];            // #22 Point of Service Entry Mode  
                                    // #23 Card Sequence Number: stEmvInfo.ucPANSN  
    u8 asConditionCode[2+1];        // #25 Point of Service Condition Code  
    u8 asPinCapCode[2+1];           // #26 PIN Capture Code 
                                    // #35 Track-2 Data: stCardInfo->stIccData.asTrack2Data 
                                    // #36 Track-3 Data: stCardInfo->stIccData.asTrack3Data 
    u8 asTermID[8+1];               // #41 Card Acceptor Terminal ID(TID): stTermInfo.asTermID  
    u8 asMerchID[15+1];             // #42 Card Acceptor Identification Code(MID): stTermInfo.asMID 
                                    // #45 Track-1 Data:    stCardInfo->stIccData.asTrack1Data  
    u8 asTipAmount[12+1];           // #48/#54 Additional Data – Private: TIP Amount   
    u8 asCurrencyCode[3+1];         // #49 Transaction Currency Code    
                                    // #55 ICC-Related Data: get data from stEmvInfo    
    u8 asOrigBatchNO[6+1];          // #61.1 original System batch Number   
    u8 asOrigTraceNO[6+1];          // #61.2 original System Trace Audit Number 
    u8 asOrigDate[4+1];             // #61.3 original transaction date
    u8 asCashbackAmount[12+1];      // #xx: cashback amount 
                                                                
    /* response message */
    u8 asTransTime[6+1];            // #12 Local Transaction Time   
    u8 asTransDate[4+1];            // #13 Local Transaction Date   
    u8 asSettlementDate[4+1];       // #15 Date Of Settlement   
    u8 asAIID[11+1];                // #32 Acquiring Institution ID Code    
    u8 asRefNO[12+1];               // #37 Retrieval Ref. Number    
    u8 asAuthCode[6+1];             // #38 Authorisation Identification Res
    u8 asRespCode[2+1];             // #39 response code    
    u8 asIssuerCode[11+1];          // #44 Additional Response Data - Issuer code
    u8 asAcquirerCode[11+1];        // #44 Additional Response Data - Acquirer code
    u8 asBalance[13+1];             // #54 Additional Amounts   
    
    u8 asFuncCode[2+1];              // #60.2 System batch Number    
    u8 asBatchNO[6+1];              // #60.2 System batch Number    
    u8 asInterOrgCode[3+1];         // #63.1 International Organization code
    u8 asIssuerInfo[40+1];          // #63.2.1 Issuer info
    u8 asCUPInfo[40+1];             // #63.2.2 CUP info
    u8 asAcqInfo[40+1];             // #63.2.3 acquirer info
    u8 asTermReserved[60+1];        // #63.2.4 
}ST_MSGINFO;

// tranaction status
typedef struct
{   
    bool bIsIccTrans;                       // ICC transaction or not
    bool bIsIccFailTrans;                   // ICC transaction or not
    bool bIsOffline;                        // offline transaction or not
    bool bIsVoided;                         // have been voided or not
    bool bIsAdjusted;                       // have been adjusted or not
    bool bIsNeedRePrint;                    // had printed or not
    bool bIsNeedReversal;                   // need reversal or not 
    bool bIsNeedScript;                     // need send script resault or not  
    u8 ucReversalReason;                    // reversal reason 
    u8 ucAdjustedTimes;                     // how many times the transaction has been adjusted
    E_UPLOAD_STATUS eUploadStatus;          // transaction upload status
}ST_TRANS_STATUS;

typedef struct      //stored in DB                                                                                 
{             
    s32 iID;                                // transaction record ID
    s32 iOriginalID;                        // original transaction record ID   //只要保存这个ID，就可以根据该ID找到原交易所有信息
    E_TRANS_ID eTransID;                    // transaction ID
    ST_CARDINFO stCardInfo;                 // card info                                            
    ST_EMVINFO stEmvInfo;                   // EMV info
    ST_MSGINFO stMsgInfo;                   // MSG info
    ST_TRANS_STATUS stTransStatus;          // transaction status
    u8 heRFU[256];                          // RFU
    ST_SENT_POLICY_MSG stSentPolicyMsg;     //Policy Msg added by jeff 20171010
}ST_TRANSLOG;

typedef struct      //stored in DB                                                                                 
{             
    ST_TRANSLOG stTransLog;         // transaction status
    
    s32 iStatus;                   // global error code
    
    u8 asMTI[4+1];                  // #0 Message Type Identifier
    u8 hePIN[13];                   // #52 Personal Identification Number
    u8 heKSN[10];                   // DUKPT KSN        //wm20161008
    
    E_EMV_CTLS_TYPE eCtlsType;      // Cardreader return contactless transaction type
    bool bIsOnlineEC;               // Electronic cash to online process
        
    u8 asAdditionInfo[323+1];       // #48 Additional Data - Private
    u8 bcRecvIccData[255];          // #55 receive icc data
    s32  iRecvIccDataLen;           // receive icc data length
    u8 bcPrivateData[255];          // #62 Reserved private data
    s32  iPrivateDataLen;           // Reserved private data len
    bool bIsCtlsReadCardOk;         // whether read CTLS card ok     
    u8 ucCtlsCardType;              // CTLS card type
    
}ST_TRANSDATA; 

// Cashier info
typedef struct
 {                       
     u8 ucCashierNO;     
     u8 asCashierPwd[9]; 
 }ST_CASHIER;            

typedef struct
{
    u8 ucUserNO;              
    bool bIsPosLogon;             
    bool bIsCashierLogon;              
}ST_LOGIN_INFO;

// transaction name table
typedef struct
{
    E_TRANS_ID eTransID;       
    u8 asName[32];        
}ST_TRANS_NAME;

typedef s32 (*PACKET_FUN)(SDK_8583_ST8583 *pstIsoMsg);

typedef struct
{
    u32 eTransID;
    PACKET_FUN pFun;
}ST_PACKET_INFO;

/*---------------------- app headers ----------------------*/
//#include "const.h"
//#include "struct.h"
#include "str.h"
#include "misc.h"
#include "commu.h"
#include "aid.h"
#include "capk.h"
#include "emv.h"
#include "iso8583.h"
#include "database.h"
#include "record.h"
#include "setup.h"
#include "report.h"

#include "logon.h"
#include "logout.h"
#include "sale.h"
#include "void.h"
#include "refund.h"
#include "settle.h"
#include "adjust.h"
#include "balance.h"
#include "offline.h"
#include "reversal.h"
#include "script.h"
#include "print.h"
#include "display.h"

//#include "appdbg.h"

/*-----------------------------------------------------------------------------
*                           GLOBAL VARIABLES
-----------------------------------------------------------------------------*/

EXTERN ST_APP_SYSCFG gstAppSysCfg; 

EXTERN u16 *pgScrBuff;      //screen buffer
EXTERN u32 guiScrBuffSize;  //screen buffer size
EXTERN u8  gucCommPort;     //communication port with pc 

EXTERN ST_TRANSDATA gstTransData;       //transaction related information

EXTERN ST_LOGIN_INFO gstLoginInfo;      //login related information

EXTERN SDK_8583_ST8583 gstSendPacket;   // ISO8583 send packet struct
EXTERN SDK_8583_ST8583 gstRecvPacket;   // ISO8583 receive packet struct

EXTERN u8 gucMsdCVM;
EXTERN u8 gheTRMData[8];

/*-----------------------------------------------------------------------------*/
#endif

