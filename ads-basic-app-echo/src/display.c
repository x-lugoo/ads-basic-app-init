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
// prompt text for successful response code
static ST_RESP_TEXT TabRespSuccText[] = 
{
    //resp   line2                     line3                      
    {{"00"}, {""},                     {STR_INFO_TRANS_SUCCESS}   },
    {{"11"}, {STR_INFO_TRANS_SUCCESS}, {STR_INFO_VIP_CLIENT}      },
    {{"A2"}, {STR_INFO_TRANS_SUCCESS}, {STR_INFO_CONFIRM_WITH_ISS}},
    {{"A4"}, {STR_INFO_TRANS_SUCCESS}, {STR_INFO_CONFIRM_WITH_ISS}},
    {{"A5"}, {STR_INFO_TRANS_SUCCESS}, {STR_INFO_CONFIRM_WITH_ISS}},
    {{"A6"}, {STR_INFO_TRANS_SUCCESS}, {STR_INFO_CONFIRM_WITH_ISS}},
};

// prompt text for error response code
static ST_RESP_TEXT TabRespErrText[] = 
{
    //resp   line2                           line3                       
    {{"01"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"02"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"03"}, {""},                           {STR_INFO_INVALID_MERCHANT} },
    {{"04"}, {STR_INFO_CARD_PICKED_UP},      {STR_INFO_CONTACT_ACQUIRER} },
    {{"05"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"06"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"07"}, {STR_INFO_CARD_PICKED_UP},      {STR_INFO_CONTACT_ACQUIRER} },
    {{"09"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY}        },
    {{"12"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY}        },
    {{"13"}, {STR_INFO_AMOUNT_EXCEED},       {STR_INFO_PLS_RETRY}        },
    {{"14"}, {STR_INFO_INVALID_CARDNO},      {STR_INFO_CONTACT_ISSUER}   },
    {{"15"}, {""},                           {STR_INFO_CARD_NOT_ACCEPTED}},
    {{"19"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"20"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"21"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"22"}, {STR_INFO_OPERATION},           {STR_INFO_PLS_RETRY}        },
    {{"23"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"25"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"30"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY}        },
    {{"31"}, {""},                           {STR_INFO_CARD_NOT_ACCEPTED}},
    {{"33"}, {STR_INFO_CARD_EXPIRED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"34"}, {STR_INFO_CARD_PICKED_UP},      {STR_INFO_CONTACT_ACQUIRER} },
    {{"35"}, {STR_INFO_CARD_PICKED_UP},      {STR_INFO_CONTACT_ACQUIRER} },
    {{"36"}, {STR_INFO_WRONG_CARD},          {STR_INFO_TRY_ANOTHER_CARD} },
    {{"37"}, {STR_INFO_CARD_PICKED_UP},      {STR_INFO_CONTACT_ACQUIRER} },
    {{"38"}, {STR_INFO_PIN_TRY_LIMIT},       {""}                        },
    {{"39"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"40"}, {STR_INFO_TRANS_NOT_SUPPORTED}, {STR_INFO_CONTACT_ISSUER}   },
    {{"41"}, {STR_INFO_CARD_PICKED_UP},      {STR_INFO_CONTACT_ACQUIRER} },
    {{"42"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"43"}, {STR_INFO_CARD_PICKED_UP},      {STR_INFO_CONTACT_ACQUIRER} },
    {{"44"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"45"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_USE_CHIPCARD}     },
    {{"51"}, {STR_INFO_NOT_SUFFICIENT_FUNDS},{STR_INFO_PLS_CHECK}        },
    {{"52"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"53"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"54"}, {STR_INFO_CARD_EXPIRED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"55"}, {STR_INFO_PIN_ERR},             {STR_INFO_PLS_RETRY}        },
    {{"56"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"57"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"58"}, {STR_INFO_INVALID_TERM},        {STR_INFO_CONTACT_ACQUIRER} },
    {{"59"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"60"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"61"}, {""},                           {STR_INFO_AMOUNT_EXCEED}    },
    {{"62"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"63"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"64"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"65"}, {STR_INFO_SALE_TIMES_LIMIT},    {""}                        },
    {{"66"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ACQUIRER} },
    {{"67"}, {""},                           {STR_INFO_CARD_PICKED_UP}   },
    {{"68"}, {STR_INFO_TRANS_TIMEOUT},       {STR_INFO_PLS_RETRY}        },
    {{"75"}, {STR_INFO_PIN_TRY_LIMIT},       {""}                        },
    {{"77"}, {""},                           {STR_INFO_POS_LOGON_FIRST}  },
    {{"79"}, {STR_INFO_RESEND_OFFLINE_DATA}, {""}                        },
    {{"90"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY_LATER}  },
    {{"91"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY_LATER}  },
    {{"92"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY_LATER}  },
    {{"93"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
    {{"94"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY_LATER}  },
    {{"95"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY_LATER}  },
    {{"96"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_RETRY_LATER}  },
    {{"97"}, {STR_INFO_POS_NOT_REGISTERED},  {STR_INFO_CONTACT_ACQUIRER} },
    {{"98"}, {STR_INFO_TRANS_TIMEOUT},       {STR_INFO_PLS_RETRY}        },
    {{"99"}, {STR_INFO_PIN_ERR},             {STR_INFO_PLS_LOGON_AGAIN}  },
    {{"A0"}, {STR_INFO_MAC_ERR},             {STR_INFO_PLS_LOGON_AGAIN}  },
    {{"Z0"}, {STR_INFO_TRANS_FAILED},        {STR_INFO_CONTACT_ISSUER}   },
};

// prompt text for transaction status
static ST_TRANS_STATUS_TEXT TabTransStatusText[] =
{
    {SDK_ESC,                  {""},                           {STR_INFO_TRANS_CANCEL}       },
    {SDK_KEY_ESC,              {""},                           {STR_INFO_TRANS_CANCEL}       },
    {SDK_TIME_OUT,             {""},                           {STR_INFO_TRANS_TIMEOUT}      },
    {ERR_NO_CASHIER,           {""},                           {STR_INFO_CASHIER_LOGON_FIRST}},
    {ERR_REPRINT,              {""},                           {STR_INFO_REPRINT_FAILED}     },
    {ERR_SETTLE_STARTED,       {STR_INFO_SETTLING},            {STR_INFO_DO_SETTLEMENT_FIRST}},
    {ERR_SETTLE_PRINT,         {STR_INFO_SETTLE_PRINT_FAILED}, {STR_INFO_PLS_REPRINT}        },
    {ERR_FILE_SYSTEM,          {STR_INFO_FILE_SYSTEM_ERROR},   {STR_PRESS_CANCEL_EXIT}       },
    {ERR_MEMORY_FULL,          {STR_INFO_MEMORY_INSUFFICIENT}, {STR_INFO_DO_SETTLEMENT_FIRST}},
    {ERR_TRANSNUM_LIMIT,       {STR_INFO_TRANS_NUM_EXCEEDED},  {STR_INFO_DO_SETTLEMENT_FIRST}},
    {ERR_TRANS_NOSUPPORT,      {STR_INFO_NOT_SUPPORTED},       {STR_PRESS_CANCEL_EXIT}       },
    {ERR_READ_CARD,            {STR_INFO_READ_CARD_FAILED},    {STR_PRESS_CANCEL_EXIT}       },
    {SDK_COMM_WAVELOST,        {STR_INFO_RECEIVE_DATA},        {STR_INFO_DISCONNECTED}       },
    {ERR_RECV_TIMEOUT,         {STR_INFO_RECEIVE_DATA},        {STR_INFO_TIMEOUT}            },
    {SDK_COMM_BUFFER_ERROR,    {STR_INFO_RECEIVE_DATA},        {STR_INFO_BUFFER_ERROR}       },
    {ERR_LINK,                 {STR_INFO_CREATE_LINK},         {STR_INFO_UNKOWN_ERROR}       },
    {ERR_LINK_TIMEOUT,         {STR_INFO_CREATE_LINK},         {STR_INFO_TIMEOUT}            },
    {SDK_COMM_NOLINE,          {STR_INFO_CREATE_LINK},         {STR_INFO_NO_LINE_DETECTED}   },
    {SDK_COMM_NOSTAKE,         {STR_INFO_CREATE_LINK},         {STR_INFO_PUT_HANDLE_BACK}    },
    {SDK_COMM_ENGAGED,         {STR_INFO_CREATE_LINK},         {STR_INFO_LINE_BUSY}          },
    {SDK_COMM_NO_SIM,          {STR_INFO_CREATE_LINK},         {STR_INFO_NO_SIM_DETECTED}    },
    {SDK_COMM_LINKFAIL,        {STR_INFO_CREATE_LINK},         {STR_INFO_LINK_FAILURE}       },
    {ERR_PACK_MSG,             {""},                           {STR_INFO_PACK_MSG_FAILED}    },
    {ERR_ENCRYPT,              {""},                           {STR_INFO_ENCRYPTION_ERROR}   },
    {ERR_SEND,                 {""},                           {STR_INFO_SEND_DATA_FAILED}   },
    {ERR_RECV,                 {""},                           {STR_INFO_RECEIVE_DATA_FAILED}},
    {ERR_UNPACK_MSG,           {""},                           {STR_INFO_UNPACK_MSG_FAILED}  },
    {ERR_PRINT,                {""},                           {STR_INFO_PRINT_ERROR}        },
    {ERR_MSGTYPE,              {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_MTI_NOT_MATCH}      },
    {ERR_PROCESSCODE,          {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_PROCCODE_NOT_MATCH} },
    {ERR_TRACENO,              {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_TRACENO_NOT_MATCH}  },
    {ERR_TRANSAMOUNT,          {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_AMOUNT_NOT_MATCH}   },
    {ERR_BATCHNO,              {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_BATCHNO_NOT_MATCH}  },
    {ERR_TERMINALNO,           {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_TID_NOT_MATCH}      },
    {ERR_MERCHANTNO,           {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_MID_NOT_MATCH}      },
    {ERR_NO_LOGON,             {""},                           {STR_INFO_PLS_LOGON_FIRST}    },
    {ERR_CALCMAC,              {STR_INFO_CHECK_MSG_FAILED},    {STR_INFO_MAC_ERR}            },
    {ERR_NOTALLOW_VOID,        {""},                           {STR_INFO_VOID_NOT_ALLOWED}   },
    {ERR_ALREADY_VOID,         {""},                           {STR_INFO_ALREADY_VOIDED}     },
    {ERR_DIFF_CARD  ,          {STR_INFO_CARDNO_NOT_MATCH},    {STR_INFO_PLS_RETRY}          },
    {ERR_NOTALLOW_ADJUST,      {STR_INFO_ADJUST_NOT_ALLOWED},  {STR_PRESS_CANCEL_EXIT}       },
    {ERR_ADJUST_LIMIT,         {STR_INFO_ADJUST_TIMES_LIMIT},  {STR_PRESS_CANCEL_EXIT}       },
    {ERR_BATCHUP,              {""},                           {STR_INFO_BATCHUP_FAILED}     },
    {ERR_USER_NOEXIST,         {""},                           {STR_INFO_USER_NOT_EXIST}     },
    {ERR_PASSWORD,             {""},                           {STR_INFO_PASSWORD_ERR}       },
    {ERR_UPDATE_KEY,           {""},                           {STR_INFO_UPDATE_KEY_FAILED}  },
    {ERR_ICC_AUTHFAIL,         {STR_INFO_TRANS_FAILED},        {STR_INFO_PLS_CALL_BANK}      },
    {ERR_NO_TRANS,             {STR_INFO_NO_TRANS},            {STR_PRESS_CANCEL_EXIT}       },
    {ERR_ALREADY_ADJUSTED,     {""},                           {STR_INFO_ALREADY_ADJUSTED}   },
    {ERR_LOGON_FAIL,           {""},                           {STR_INFO_AUTO_LOGON_FAIL}    },
    {ERR_CASHBACK_LIMIT,       {""},                           {STR_INFO_AMT_EXCEED}         },
    {ERR_AMT_LIMIT,            {STR_INFO_AMT_EXCEED},          {STR_INFO_DO_SETTLEMENT_FIRST}},
    {ERR_ICC_RESET,            {STR_INFO_READ_CARD_FAILED},    {STR_INFO_RESET_FAILURE}      },
    {SDK_QpbocDDAAuthFail,     {STR_INFO_READ_CARD_FAILED},    {STR_INFO_DDA_FAILED}         },
    {SDK_QpbocNoCard,          {STR_INFO_READ_CARD_FAILED},    {STR_INFO_NO_CARD_PRESENT}    },
    {SDK_QpbocMoreCards,       {STR_INFO_READ_CARD_FAILED},    {STR_INFO_MULTI_CARDS}        },
    {SDK_QpbocAuthNoPerformed, {STR_INFO_READ_CARD_FAILED},    {STR_INFO_NEED_MUTUAL_AUTH}   },
    {SDK_ECNotSupportErr,      {STR_INFO_READ_CARD_FAILED},    {STR_INFO_PURE_EC_NOT_SUPPORT}},
    {SDK_EcLackBalanceErr,     {STR_INFO_READ_CARD_FAILED},    {STR_INFO_PURE_EC_CARD}       },
    {SDK_UsePbocErr,           {STR_INFO_READ_CARD_FAILED},    {STR_INFO_PROCESS_WITH_PBOC}  },
    {SDK_CardBlockErr,         {STR_INFO_READ_CARD_FAILED},    {STR_INFO_CARD_IS_BLOCKED}    },
    {SDK_NoAppSelErr,          {STR_INFO_READ_CARD_FAILED},    {STR_INFO_NO_APP_SELECTED}    },
    {SDK_IccDataFormatErr,     {STR_INFO_READ_CARD_FAILED},    {STR_INFO_DATA_FORMAT_ERR}    },
    {SDK_AppBlockErr,          {STR_INFO_READ_CARD_FAILED},    {STR_INFO_APP_IS_BLOCKED}     },
    {-323,                     {STR_INFO_READ_CARD_FAILED},    {STR_INFO_PLS_RETRY}          },
    {TRANS_STATUS_FINISH,      {""},                           {STR_INFO_TRANS_FINISH}       },
};

static u8 _gasTitle[64];
static u8 _gasTitleBak[64];

/*****************************************************************************
** Description :  Check whether the terminal has color screen
** Parameters  :  None 
** Return      :  (1)TRUE: is color screen 
                  (2)FALSE: is not color screen
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool IsTermColorScreen(void)
{
    u8 term_model[64] = {0};
    SDK_DISP_PIXEL st_pixel;

    sdkSysGetMachineModel(term_model);

    st_pixel = sdkDispGetScreenPixel();

    if(st_pixel.siX > 128 && st_pixel.siY > 64)
    {
        return TRUE;
    }

    if (0 == strcmp(term_model, "G3")
        || 0 == strcmp(term_model, "G3M")
        || 0 == strcmp(term_model, "G3N")
        || 0 == strcmp(term_model, "G870")
        || 0 == strcmp(term_model, "G2")
        || 0 == strcmp(term_model, "G810Q"))
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
** Description :  Set terminal maximum display line and display mode
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispSetMaxLine(void)
{
    SDK_SYS_LINE_INFOR st_lineinfo;
    u8 model[8] = {0};
    
    sdkSysGetMachineModel(model);
    if(!strcmp(model, "G870"))        // G870 resolution 240*320
    {
        st_lineinfo.eLine = SDK_SYS_LINE10;
        st_lineinfo.eLineMode = SDK_SYS_LINE1_LINE4;
        st_lineinfo.pVar = NULL;
    }
    else if(!strcmp(model, "G3"))     // G3 resolution 320*240
    {
        st_lineinfo.eLine = SDK_SYS_LINE7;
        st_lineinfo.eLineMode = SDK_SYS_LINE1_LINE4;
        st_lineinfo.pVar = NULL;
    }
    else if(IsTermColorScreen())
    {
        st_lineinfo.eLine = SDK_SYS_LINE7;
        st_lineinfo.eLineMode = SDK_SYS_LINE1_LINE4;
        st_lineinfo.pVar = NULL;
    }
    else                               // Other black and white screen resolution 128*64
    {
        st_lineinfo.eLine = SDK_SYS_LINE5;
        st_lineinfo.eLineMode = SDK_SYS_LINE1_LINE4;
        st_lineinfo.pVar = NULL;
    }
    sdkSysMultiSetLineMode(&st_lineinfo);
}

/*****************************************************************************
** Description :  Get terminal maximum display line
** Parameters  :  None 
** Return      :  terminal maximum display line(see enum "SDK_SYS_LINE_MODE")
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
u8 DispGetMaxLine(void)
{
    SDK_SYS_LINE_INFOR st_lineinfo;
    
    sdkSysMultiGetLineMode(&st_lineinfo);

    if(st_lineinfo.eLine <= 0)
    {
        st_lineinfo.eLine = SDK_SYS_LINE5;
    }

    return st_lineinfo.eLine;
}

/*****************************************************************************
** Description :  Save screen
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  Must malloc memory to initialize buffer "pgScrBuff", and use
                  "sdkDispGetScreenBufferSize" to initialize "guiScrBuffSize" 
                  before use.
*****************************************************************************/
void DispSaveScreen(void)
{
    memset(_gasTitleBak, 0, sizeof(_gasTitleBak));
    strcpy(_gasTitleBak, _gasTitle);
    sdkDispSaveScreen(pgScrBuff, guiScrBuffSize);
}

/*****************************************************************************
** Description :  Restore screen
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  Must malloc memory to initialize buffer "pgScrBuff", and use
                  "sdkDispGetScreenBufferSize" to initialize "guiScrBuffSize" 
                  before use.
*****************************************************************************/
void DispRestoreScreen(void)
{
    memset(_gasTitle, 0, sizeof(_gasTitle));
    strcpy(_gasTitle, _gasTitleBak);
    sdkDispClearScreen();
    sdkDispRestoreScreen(pgScrBuff, guiScrBuffSize);
}

/*****************************************************************************
** Description :  display background image
** Parameters  :  input:
                  (1)const u8 *pasBmpFileName : image file path
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  If it's not color screen, this API will do nothing.
*****************************************************************************/
void DispBackground(const u8 *pasBmpFileName)
{
    SDK_DISP_PIXEL pixel;

    if(IsTermColorScreen())
    {
        if(sdkAccessFile((u8 *)pasBmpFileName))
        {
            memset(&pixel, 0, sizeof(SDK_DISP_PIXEL));
            pixel = sdkDispGetScreenPixel();
            sdkDispSetBackground(0, 0, pixel.siX, pixel.siY, pasBmpFileName);
        }
    }
}

/*****************************************************************************
** Description :  Clear screen except the 1st line(title)
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispClearContent(void)
{
    u8 max_line = DispGetMaxLine();
    u8 i = 0; 
    SDK_DISP_PIXEL st_pixel;

    if(IsTermColorScreen())
    {
#ifdef T2_DEBUG
        for(i = 1; i < max_line; i++)
        {
            sdkDispClearRowRam(i);
        }
#else
        st_pixel = sdkDispGetScreenPixel();
        sdkDispClearAt(0, 24, st_pixel.siX, st_pixel.siY);
#endif
    }
    else
    {
        for(i = 1; i < max_line; i++)
        {
            sdkDispClearRowRam(i);
        }
    }
}

/*****************************************************************************
** Description :  Display read card error
** Parameters  :  input:
                  (1)u8 ucMode : 1:prompt swipe/insert card
                                 2:prompt swipe card
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispReadCardErr(u8 ucMode)
{ 
    u8 row = SDK_DISP_LINE3;

    if(1 == ucMode)
    { 
        DispClearContent();
        sdkDispFillRowRam(row++, 0, STR_INFO_TRANS_FAILED, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(row++, 0, STR_INFO_PLS_SWIPE_INSERT, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(row++, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();
    } 
    else 
    { 
        DispClearContent();
        sdkDispFillRowRam(row++, 0, STR_INFO_SWIPE_ERROR, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(row++, 0, STR_INFO_PLS_SWIPE_AGAIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(row++, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();
    } 
} 
    
/*****************************************************************************
** Description :  Display success response code
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispSuccResponse(void)
{
    u8 i;
    bool flag = FALSE;
    u8 buf[3] = {0};

    memcpy(buf, gstTransData.stTransLog.stMsgInfo.asRespCode, 2);

    for (i = 0; i < sizeof(TabRespSuccText) / sizeof(ST_RESP_TEXT); i++)
    {
        if (!memcmp(buf, TabRespSuccText[i].asRespCode, 2))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, TabRespSuccText[i].asTextLine2, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, TabRespSuccText[i].asTextLine3, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            flag = TRUE;
            break;
        }
    }

    if (!flag)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_TRANS_SUCCESS, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
    }
    
    sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
}

/*****************************************************************************
** Description :  Display error response code
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispErrResponse(void)
{
    u8 i;
    bool flag = FALSE;
    u8 tmp[64] = {0};
    u8 buf[3] = {0};

    memcpy(buf, gstTransData.stTransLog.stMsgInfo.asRespCode, 2);

    for (i = 0; i < sizeof(TabRespErrText) / sizeof(ST_RESP_TEXT); i++)
    {
        if (!memcmp(buf, TabRespErrText[i].asRespCode, 2))
        {
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, TabRespErrText[i].asTextLine2, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, TabRespErrText[i].asTextLine3, SDK_DISP_DEFAULT);
            sprintf(tmp, "%s%2.2s", STR_INFO_RESPONSE_CODE, buf);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, tmp, SDK_DISP_DEFAULT);
            flag = TRUE;
            break;
        }
    }

    if (!flag)
    {
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_TRANS_FAILED, SDK_DISP_DEFAULT);
        sprintf(tmp, "%s%2.2s", STR_INFO_RESPONSE_CODE, buf);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, tmp, SDK_DISP_DEFAULT);
    }
}


/*****************************************************************************
** Description :  Display the error reason of reading IC card.
** Parameters  :  input:
1                 (1)SDK_EMV_RLT eEmvRet : return value of EMV-kernel
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispEmvReadCardReturn(SDK_EMV_RLT eEmvRet)
{
    switch (eEmvRet)
    {
         case SDK_ICC_RESET_ERR:
            TrnSetStatus(ERR_ICC_RESET);
            break;

         case SDK_QpbocDDAAuthFail:
         case SDK_QpbocNoCard:
         case SDK_QpbocMoreCards:
         case SDK_QpbocAuthNoPerformed:
         case SDK_ECNotSupportErr:
         case SDK_EcLackBalanceErr:
         case SDK_UsePbocErr:
         case SDK_CardBlockErr:
         case SDK_NoAppSelErr:
         case SDK_IccDataFormatErr:
         case SDK_AppBlockErr:
            TrnSetStatus(eEmvRet);
            break;

         default:
            if(0 == TrnGetStatus())
            {
                TrnSetStatus(ERR_READ_CARD);
            }
            break;
    }
}

/*****************************************************************************
** Description :  Display transaction status
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispTransStatus(void)
{
    s32 code = 0;
    s32 timer = TMR_PROMPT;
    s32 i = 0;
    bool flag = FALSE;

    DispClearContent();
    
    code = TrnGetStatus();

    if(ERR_RESP_CODE == code)
    {
        DispErrResponse();
        timer = TMR_NONE;
    }
    else
    {
        for(i = 0; i < sizeof(TabTransStatusText) / sizeof(ST_TRANS_STATUS_TEXT); i++)
        {
            if(code == TabTransStatusText[i].iStatus)
            {
                flag = TRUE;
                sdkDispFillRowRam(SDK_DISP_LINE2, 0, TabTransStatusText[i].asTextLine2, SDK_DISP_DEFAULT);
                sdkDispFillRowRam(SDK_DISP_LINE3, 0, TabTransStatusText[i].asTextLine3, SDK_DISP_DEFAULT);
                break;
                
            }
        }
        if(!flag)
        {
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_TRANS_FAILED, SDK_DISP_DEFAULT);
        }
        timer = TMR_PROMPT;
    }
    
    sdkSysBeep(SDK_SYS_BEEP_ERR);
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, timer);
}

/*****************************************************************************
** Description :  Display card number and confirm
** Parameters  :  input:
                  (1)u8 *pasCardNo : card number string to display
                  
** Return      :  (1)TRUE: Already confirm
                  (2)FALSE: Not confirm
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool DispCardNo(const u8 *pasCardNo)
{
    s32 ret;
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_CARD_NO, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, pasCardNo, SDK_DISP_RIGHT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE5, 0, STR_PRESS_ENTER_CONFIRM, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    ret = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return FALSE;
    }

    return TRUE;
}

/*****************************************************************************
** Description :  Display read card prompt
** Parameters  :  input:
                  (1)s32 iCardMode : Read card mode
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispReadCard(s32 iCardMode)
{
    u8 buf[32];
    
    memset(buf, 0, sizeof(buf));

    if((iCardMode & SDK_ICC_MANUAL) && (iCardMode & SDK_ICC_ICC) &&
       (iCardMode & SDK_ICC_MAG) && (iCardMode & SDK_ICC_RF))
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_CARD_MANUAL"/"STR_CARD_SWIPE"/"STR_CARD_INSERT, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, "/"STR_CARD_TAP, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        return;
    }

    if (iCardMode & SDK_ICC_MANUAL)
    {
        strcpy(buf, STR_CARD_MANUAL);
    }
    if (iCardMode & SDK_ICC_MAG)
    {
        if (strlen(buf))
        {
            strcat(buf, "/");
        }
        strcpy(buf, STR_CARD_SWIPE);
    }

    if (iCardMode & SDK_ICC_ICC)
    {
        if (strlen(buf))
        {
            strcat(buf, "/");
        }
        strcat(buf, STR_CARD_INSERT);
    }

    if (iCardMode & SDK_ICC_RF) //Add for Contactless Card
    {
        if (strlen(buf))
        {
            strcat(buf, "/");
        }
        strcat(buf, STR_CARD_TAP);
    }

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, buf, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
}

/*****************************************************************************
** Description :  Display the title
** Parameters  :  input:
                  (1)const u8 *pasTitle : title string
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispTitle(const u8 *pasTitle)
{
    SDK_DISP_SRECT stRect = {0, 0, 320, 24};
    s32 color;
    SDK_DISP_PIXEL st_pixel;
    const u8 *p_title = pasTitle;

    if(NULL == p_title)
    {
        p_title = _gasTitle;
    }

    st_pixel = sdkDispGetScreenPixel();
    stRect.x1 = st_pixel.siX;
    
#ifdef T2_DEBUG
    sdkDispClearScreen();
    sdkDispFillRowRam(SDK_DISP_LINE1, 0, p_title, SDK_DISP_FDISP | SDK_DISP_CDISP);
    sdkDispBrushScreen();
#else
    color = sdkDispGetFontColor();

    sdkDispClearScreen();

    if(IsTermColorScreen())
    {
        sdkDispSetRectColor(&stRect, SDK_DISP_WHITE_COLOR);
        sdkDispSetFontColor(SDK_DISP_RED_COLOR);
        sdkDispFillRowRam(SDK_DISP_LINE1, 0, p_title, SDK_DISP_FDISP | SDK_DISP_CDISP | SDK_DISP_INCOL);
    }
    else
    {
        sdkDispFillRowRam(SDK_DISP_LINE1, 0, p_title, SDK_DISP_NOFDISPLINE | SDK_DISP_CDISP | SDK_DISP_INCOL);
    }
    sdkDispBrushScreen();

    if(NULL != pasTitle)
    {
        memset(_gasTitle, 0, sizeof(_gasTitle));
        strcpy(_gasTitle, pasTitle);
    }

    sdkDispSetFontColor(color);
#endif
}

/*****************************************************************************
** Description :  Display transaction success status
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispTransSucc(void)
{
    sdkSysBeep(SDK_SYS_BEEP_OK);
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_TRANS_SUCCESS, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
}

/*****************************************************************************
** Description :  Display the total of transation and wait confirm
** Parameters  :  input:
                  (1)ST_SETTLE *pstSettle : settle information
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : user cancel or confirm timeout
                  (3)SDK_OK : user confirmed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 DispTransTotal(ST_SETTLE *pstSettle)
{
    u8 tmp[256] = {0};
    u8 buf[256] = {0};
    s32 ret;

    if(NULL == pstSettle)
    {
        return SDK_PARA_ERR;
    }
    
    DispClearContent();
    sprintf(tmp, "%s %d", STR_INFO_SALE, pstSettle->stTotal.stTotalAll.uiTotalDebitNum);
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, tmp, SDK_DISP_LEFT_DEFAULT);

    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    sdkBcdToAsc(buf, pstSettle->stTotal.stTotalAll.bcTotalDebitAmount, 6);
    strcpy(tmp, STR_INFO_AMOUNT);
    TrnFormatAmount(&tmp[strlen(tmp)], buf, FALSE);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, tmp, SDK_DISP_LEFT_DEFAULT);
    
    sprintf(tmp, "%s %d", STR_INFO_REFUND, pstSettle->stTotal.stTotalAll.uiTotalCreditNum);
    sdkDispFillRowRam(SDK_DISP_LINE4, 0, tmp, SDK_DISP_LEFT_DEFAULT);
    
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    sdkBcdToAsc(buf, pstSettle->stTotal.stTotalAll.bcTotalCreditAmount, 6);
    strcpy(tmp, STR_INFO_AMOUNT);
    TrnFormatAmount(&tmp[strlen(tmp)], buf, FALSE);
    sdkDispFillRowRam(SDK_DISP_LINE5, 0, tmp, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();
    
    ret = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
    if(SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return SDK_ERR;
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Display the detail of transation
** Parameters  :  input:
                  (1)ST_TRANSLOG *pstTransLog : transaction record data 
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error 
                  (2)SDK_ERR : user cancel or confirm timeout
                  (3)SDK_OK : user confirmed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 DispTransDetail(ST_TRANSLOG *pstTransLog)
{
    u8 tmp[64];
    s32 ret = SDK_KEY_ESC;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_DISP_LIST st_list;
    u8 i;

    if(NULL == pstTransLog)
    {
        return SDK_PARA_ERR;
    }

    pst_msginfo = &pstTransLog->stMsgInfo;

    memset(&st_list, 0, sizeof(ST_DISP_LIST));

    DispClearContent();
    
    TrnGetName(tmp, pstTransLog->eTransID);
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, tmp, SDK_DISP_LEFT_DEFAULT);

    memset(tmp, 0, sizeof(tmp));
    if (pstTransLog->stTransStatus.bIsVoided)
    {
        strcpy(st_list.stItem[st_list.ucNum++].asStr, STR_STATUS_ALREADY_VOIDED);
    }

    if (pstTransLog->stTransStatus.bIsAdjusted)
    {
        strcpy(st_list.stItem[st_list.ucNum++].asStr, STR_STATUS_ALREADY_ADJUSTED);
    }
    
    if(pstTransLog->stTransStatus.bIsOffline)
    {
        if (UPLOAD_OFFLINE_SUCCESS == pstTransLog->stTransStatus.eUploadStatus)
        {
            strcat(st_list.stItem[st_list.ucNum++].asStr, STR_STATUS_ALREADY_UPLOADED);
        }
        else if (UPLOAD_OFFLINE_NONE == pstTransLog->stTransStatus.eUploadStatus)
        {
            strcat(st_list.stItem[st_list.ucNum++].asStr, STR_STATUS_NOT_UPLOADED);
        }
        else if (UPLOAD_OFFLINE_FAIL == pstTransLog->stTransStatus.eUploadStatus
                 || UPLOAD_BATCHDONE_OFFFAIL== pstTransLog->stTransStatus.eUploadStatus)
        {
            strcat(st_list.stItem[st_list.ucNum++].asStr, STR_STATUS_UPLOAD_FAIL);
        }
        else if (UPLOAD_OFFLINE_DECLINE == pstTransLog->stTransStatus.eUploadStatus
                 || UPLOAD_BATCHDONE_OFFDECLINE == pstTransLog->stTransStatus.eUploadStatus)
        {
            strcat(st_list.stItem[st_list.ucNum++].asStr, STR_STATUS_UPLOAD_REJECTED);
        }
    }

    if (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_INSERT, 2))
    {
        strcpy(st_list.stItem[st_list.ucNum++].asStr, STR_DETAIL_IC);
    }
    else if ((0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_QCTLS, 2)) || 
             (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_CTLS, 2)))
    {
        strcpy(st_list.stItem[st_list.ucNum++].asStr, STR_DETAIL_RF);
    }
    else if (0 == memcmp(pst_msginfo->asEntryMode, CARDMODE_SWIPE, 2))
    {
        strcpy(st_list.stItem[st_list.ucNum++].asStr, STR_DETAIL_SWIPE);
    }
    else
    {
        strcpy(st_list.stItem[st_list.ucNum++].asStr, STR_DETAIL_MANUAL);
    }

    //card NO.
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, pstTransLog->stCardInfo.stCardData.asCardNO);
    TrnMaskCardNo(pstTransLog->eTransID, tmp);
    strcpy(st_list.stItem[st_list.ucNum++].asStr, tmp);

    //trace NO.
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, STR_INFO_TRACE_NO);
    strcat(tmp, pst_msginfo->asTraceNO);
    strcpy(st_list.stItem[st_list.ucNum++].asStr, tmp);

    //authorization NO.
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, STR_INFO_AUTH_NO);
    strcat(tmp, pst_msginfo->asAuthCode);
    strcpy(st_list.stItem[st_list.ucNum++].asStr, tmp);

    //date & time
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%2.2s-%2.2s  %2.2s:%2.2s:%2.2s", pst_msginfo->asTransDate, &pst_msginfo->asTransDate[2],
                   pst_msginfo->asTransTime, &pst_msginfo->asTransTime[2], &pst_msginfo->asTransTime[4]);
    strcpy(st_list.stItem[st_list.ucNum++].asStr, tmp);
    
    //amount
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, STR_INFO_AMOUNT);
    TrnFormatAmount(&tmp[strlen(tmp)], pst_msginfo->asAmount, TRUE);
    strcpy(st_list.stItem[st_list.ucNum++].asStr, tmp);

    //reference NO.
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, STR_INFO_REF_NO);
    strcat(tmp, pst_msginfo->asRefNO);
    strcpy(st_list.stItem[st_list.ucNum++].asStr, tmp);

    for(i = 0; i < st_list.ucNum; i++)
    {
        st_list.stItem[i].ucDispAtr = SDK_DISP_LEFT_DEFAULT;
    }
    st_list.iStartLine = SDK_DISP_LINE3;
    st_list.iEndLine = DispGetMaxLine() - 1;
    
    ret = DispListBox(TMR_OPERATE, &st_list);

    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return SDK_ERR;
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Display list
** Parameters  :  input:
                  (1)s32 siOvertimer : display timeout
                  (2)ST_DISP_LIST *pstList : the list data to display
                  
** Return      :  (1)SDK_KEY_ENTER : user press "Enter" key
                  (2)SDK_KEY_ESC : user press "Cancel" key
                  (3)SDK_TIME_OUT : timeout
                  (4)SDK_ERR : display error
** Author      :  wenmin   2016-10-18 
** Remarks     :  if the list line is more than screen display line, will support
                  "pagedown" and "pageup" key to roll.
*****************************************************************************/
s32 DispListBox(s32 siOvertimer, ST_DISP_LIST *pstList)
{
    u8 start = 0;
    u8 end = pstList->iEndLine - pstList->iStartLine + 1;
    u8 i = 0;
    s32 line;
    s32 key;
    
    while(1)
    {
        line = pstList->iStartLine;
        end = start + pstList->iEndLine - pstList->iStartLine + 1;
        for(i = start; i < end; i++)
        {
            sdkDispClearRowRam(line);
            if(strlen(pstList->stItem[i].asStr))
            {
                sdkDispFillRowRam(line++, 0, pstList->stItem[i].asStr, pstList->stItem[i].ucDispAtr);
            }
        }
        if(pstList->ucNum > i && start != 0)
        {
            sdkDispFillRowRam(pstList->iStartLine, 0, STR_INFO_ARROW_UP, SDK_DISP_FDISP |SDK_DISP_RDISP| SDK_DISP_INCOL);
            sdkDispFillRowRam(pstList->iEndLine, 0, STR_INFO_ARROW_DOWN, SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
        }
        else if(pstList->ucNum > i)
        {
            sdkDispFillRowRam(pstList->iEndLine, 0, STR_INFO_ARROW_DOWN, SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
        }
        else if(start != 0)
        {
            sdkDispFillRowRam(pstList->iStartLine, 0, STR_INFO_ARROW_UP, SDK_DISP_FDISP |SDK_DISP_RDISP| SDK_DISP_INCOL);
        }
        sdkDispBrushScreen();

        key = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC | SDK_KEY_MASK_UP | SDK_KEY_MASK_DOWN, siOvertimer);
        if(SDK_KEY_ENTER == key || SDK_KEY_ESC == key || SDK_TIME_OUT == key)
        {
            return key;
        }
        else if(SDK_KEY_UP == key)
        {
            if(start != 0)
            {
                start--;
            }
            else
            {
                sdkSysBeep(SDK_SYS_BEEP_ERR);
            }
        }
        else if(SDK_KEY_DOWN == key)
        {
            if(pstList->ucNum > i)
            {
                start++;
            }
            else
            {
                sdkSysBeep(SDK_SYS_BEEP_ERR);
            }
        }
    }
    return SDK_ERR;
}

/*****************************************************************************
** Description :  Display battery state icon on screen top
** Parameters  :  input:
                  (1)s32 iPosition : the display position of horizontal axis
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  the position of vertical axis is default 0(at the screen top)
                  if battery is empty or battery status is abnormal, will shut
                  down.
*****************************************************************************/
void DispBatteryIcon(s32 iPosition)
{
    E_BATTERY_STATE e_battery = BATTERY_0;
    static E_BATTERY_STATE e_disp = BATTERY_0;
    static bool disp_warn = TRUE;     // is need disp low battery warning
    static bool is_full = FALSE;       // is battery full
    
    e_battery = sdkSysGetBatteryStateAndControl();
    
    if (sdkSysIsExPower())
    {
        disp_warn = TRUE;
        
        switch (e_battery)
        {
            case BATTERY_LOW:
            case BATTERY_0:
            case BATTERY_1:
            case BATTERY_2:
            case BATTERY_3:
                if(BATTERY_2 == e_battery)
                {
                   if(is_full)
                   {
                       is_full = FALSE;
                   }
                }

                if(!is_full)
                {
                   e_disp++;
                   if(e_disp > BATTERY_3)
                   {
                       e_disp = BATTERY_0;
                   }
                   sdkDispIcon(SDK_DISP_BATTERY, e_disp, iPosition, 0);
                }
                else
                {
                   sdkDispIcon(SDK_DISP_BATTERY, BATTERY_MAX, iPosition, 0);
                }
                break;

            case BATTERY_MAX:
                is_full = TRUE;
                sdkDispIcon(SDK_DISP_BATTERY, BATTERY_MAX, iPosition, 0);
                break;

            case BATTERY_ERR:
            default:
                e_disp = BATTERY_HIDE;
                sdkDispIcon(SDK_DISP_BATTERY, e_disp, iPosition, 0);
                break;
        }
    }
    else
    {
        is_full = FALSE;
        switch (e_battery)
        {
            case BATTERY_ERR:
            case BATTERY_LOW:
                sdkDispClearScreen();
                sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_BATERR_OR_LOWPOWER, SDK_DISP_DEFAULT);
                sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_SHUTTING_DOWN, SDK_DISP_DEFAULT);
                sdkDispBrushScreen();
                sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT);
                if (!sdkSysIsExPower())
                {
                    system("halt");
                }
                sdkDispClearRowRam(SDK_DISP_LINE2);
                sdkDispClearRowRam(SDK_DISP_LINE3);
                break;

            case BATTERY_0:
                if (disp_warn)
                {
                    sdkDispClearRowRam(SDK_DISP_LINE2);
                    sdkDispClearRowRam(SDK_DISP_LINE3);
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_LOW_POWER, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_CHARGE, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_OPERATE);
                    sdkDispClearRowRam(SDK_DISP_LINE2);
                    sdkDispClearRowRam(SDK_DISP_LINE3);
                    disp_warn = FALSE;
                }
                //no break;
                
            case BATTERY_1:
            case BATTERY_2:
            case BATTERY_3:
            case BATTERY_MAX:
            default:
                if (BATTERY_0 != e_battery)
                {
                   disp_warn = TRUE;
                }
                sdkDispIcon(SDK_DISP_BATTERY, e_battery, iPosition, 0);
                break;
        }
    }
}

/*****************************************************************************
** Description :  Display wireless mode icon on screen top
** Parameters  :  input:
                  (1)s32 iPosition : the display position of horizontal axis
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  the position of vertical axis is default 0(at the screen top)
                  only "GPRS" and "CDMA" mode will display the icon
*****************************************************************************/
void DispWirelessIcon(s32 iPosition)
{
    if (SDK_COMM_GPRS == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        Verify(SDK_OK == sdkDispIcon(SDK_DISP_GPRS, TRUE, iPosition, 0));
    }
    else if (SDK_COMM_CDMA == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        Verify(SDK_OK == sdkDispIcon(SDK_DISP_CDMA, TRUE, iPosition, 0));
    }
}

/*****************************************************************************
** Description :  Display wireless signal level icon on screen top
** Parameters  :  input:
                  (1)s32 iPosition : the display position of horizontal axis
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  the position of vertical axis is default 0(at the screen top)
                  only "GPRS" and "CDMA" mode will display the icon
*****************************************************************************/
void DispSignalIcon(s32 iPosition)
{
    u8 signal = 0;
    u8 flag;

    if (SDK_COMM_GPRS == gstAppSysCfg.stCommuParam.uiCommuMode 
     || SDK_COMM_CDMA == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        signal = sdkCommGetSignalLevel();

        if (signal >= 0x25)
        {
            flag = 5;
        }
        else if (signal >= 0x20)
        {
            flag = 4;
        }
        else if (signal >= 0x15)
        {
            flag = 3;
        }
        else if (signal >= 0x08)
        {
            flag = 2;
        }
        else if (0 == signal)
        {
            flag = 0;
        }
        else
        {
            flag = 1;
        }
        sdkDispIcon(SDK_DISP_SIGNAL, flag, iPosition, 0);
    }
}

/*****************************************************************************
** Description :  Show all icon on screen top
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  include battery, wireless mode, wireless signal icon
*****************************************************************************/
void DispIcon(void)
{
    u8 offset = 1;
    SDK_DISP_PIXEL st_pixel;

    st_pixel = sdkDispGetScreenPixel();
    offset = (IsTermColorScreen() ? 2 : 1);

    DispBatteryIcon(st_pixel.siX - (16 + 8 + 16) * offset);
    DispWirelessIcon(st_pixel.siX - (16 + 8) * offset);
    DispSignalIcon(st_pixel.siX - 16 * offset);
}

/*****************************************************************************
** Description :  Display current date and time 
** Parameters  :  input:
                  (1)u8 ucLine : display line number
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  different terminal model have different maximum line number,
                  display in the last line, use "DispGetMaxLine" to get line 
                  number
*****************************************************************************/
void DispDateTime(u8 ucLine)
{
    u8 tmp[64];
    u8 disp[128];

    memset(tmp, 0, sizeof(tmp));
    memset(disp, 0, sizeof(disp));

    if (SDK_OK == sdkGetRtc(tmp))
    {
        if (tmp[0] >= 0x50)
        {
            sprintf(disp, "19%02X-%02X-%02X %02X:%02X:%02X", 
                         // YY        MM        DD        HH        MM        SS
                          tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
        }
        else
        {
            sprintf(disp, "20%02X-%02X-%02X %02X:%02X:%02X", 
                         // YY        MM        DD        HH        MM        SS
                          tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
        }

        sdkDispClearRowRam(ucLine);
        sdkDispFillRowRam(ucLine, 0, disp, SDK_DISP_DEFAULT);
    }
}

/*****************************************************************************
** Description :  get BMP image width and height
** Parameters  :  input:
                  (1)const u8 *pasFileName : BMP file path
                  
                  output:
                  (1)u32 *puiHeight : image height
                  (2)u32 *puiWidth : image width
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  the file must be BMP format only
*****************************************************************************/
void DispGetBmpSize(const u8 *pasFileName, u32 *puiHeight, u32 *puiWidth)
{
    u8 tmp[8];
    s32 len = 8;
    
    sdkReadFile(pasFileName, tmp, 18, &len);
    memcpy(puiWidth, tmp, sizeof(u32));
    memcpy(puiHeight, &tmp[4], sizeof(u32));
}

/*****************************************************************************
** Description :  Display saving setup parameters status
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void DispSaveSetupParam(void)
{
    sdkDispClearScreen();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_SAVING_PARAM, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
}

/*****************************************************************************
** Description :  Display the AOSA on the declined screen and print it on a receipt
** Parameters  :  None
** Return      :  (1)TRUE : display success
                  (2)FALSE : display fail
** Author      :  guozexian  2016-11-09
** Remarks     :  
*****************************************************************************/
bool DispAOSA(void)
{
    u8 tmp[64];
    u8 amt[12 + 1];
    s32 len = 0;

    memset(tmp, 0, sizeof(tmp));

    if (0 < sdkIccReadTLV("\x9F\x5D", tmp, &len))
    {
        TraceHex("display", "AOSA", tmp, len);
        memset(amt, 0, sizeof(amt));
        sdkBcdToAsc(amt, tmp, len);
        memset(tmp, 0, sizeof(tmp));
        TrnFormatAmount(tmp, amt, FALSE);
        sdkDispClearScreen();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_TRANS_FAIL, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_AVAILABLE_AMT, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE4, 0, tmp, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkmSleep(1500);
        return TRUE;
    }
    return FALSE;
}

s32 DispEMVErr(const u8 *pasSection, const u8 *pasKey)
{
    u8 temp[128] = {0};

    if (NULL == pasSection || NULL == pasKey)
    {
        Assert(0);
        return SDK_PARA_ERR;
    }
    sprintf(temp, "[%s]\n'%s'\nLEN ERR", pasSection, pasKey);
    sdkDispPromptBox(false, 0, temp);
    return SDK_OK;
}

/*****************************************************************************
** Description :  Display idle screen(home page)
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  the home page background image must named "AID + welcome.bmp"
                  AID is the 5 byte application name in "multitask.ini". and 
                  put the image file to "/mtd0/res" directory
*****************************************************************************/
void DispWelcome(void)
{
    u8 buf[256], tmp[256];
    SDK_DISP_PIXEL st_pixel;
    u32 height, width;
    u8 max_line;
    
    st_pixel = sdkDispGetScreenPixel();
    max_line = DispGetMaxLine() - 1;

    
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, PATH_MTD0_RES);
    sdkSysGetCurAppId(buf);
    strncat(tmp, &buf[3], 5);
    strcat(tmp, FILENAME_WELCOME_BMP);
   
    sdkDispClearScreen();
        
    if (sdkAccessFile(tmp))
    {
        if(IsTermColorScreen())
        {
            // display background
            DispBackground(tmp);
            sdkDispSetFontColor(SDK_DISP_BLACK_COLOR);
        }
        else
        {
            DispGetBmpSize(tmp, &height, &width);
            sdkDispShowBmp(0, 0, width, height, tmp);
        }
    }
    else
    {
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_NEXGO, SDK_DISP_DEFAULT);
    }
    
    DispIcon();
    sdkDispFillRowRam(max_line - 1, 0, STR_INFO_INPUT_AMOUNT, SDK_DISP_DEFAULT);
    DispDateTime(max_line);
    sdkDispBrushScreen();
}

/*****************************************************************************
** Description :  Display input PIN prompt
** Parameters  :  input:
                  (1)E_PED_DISPAMOUNT eDispAmountMode : display amount mode
                  (2)u8 const *pasTransAmount : amount string to display 
                  (3)SDK_PED_PIN_MODE ePinMode : PIN mode 
                  (4)u8 ucRemainPinTries : offline PIN remain tries

                  output:
                  (1)u8 *pucDispLine : prompt display line number
                  
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error
                  (2)SDK_OK : display success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
u8 DispInputPin(u8 *pucDispLine, 
                E_PED_DISPAMOUNT eDispAmountMode, 
                u8 const *pasTransAmount, 
                SDK_PED_PIN_MODE ePinMode, 
                u8 ucRemainPinTries)
{
    u8 tmp[32] = {0};
    u8 tmp_amount[8] = {0};
    u8 amt[6] = {0};

    sdkAscToBcdR(amt, pasTransAmount, 6);
    memcpy(&tmp_amount[2], amt, 6);
    *pucDispLine = SDK_DISP_LINE2;

    DispClearContent();

    if (strlen(pasTransAmount) > 0 && (DISPAMOUNT_NORNAL == eDispAmountMode || DISPAMOUNT_ORGINAL == eDispAmountMode))
    {
        if (DISPAMOUNT_ORGINAL == eDispAmountMode)
        {
            sdkDispFillRowRam(*pucDispLine, 0, STR_INFO_ORIG_AMOUNT, SDK_DISP_LEFT_DEFAULT);
        }
        else
        {
            sdkDispFillRowRam(*pucDispLine, 0, STR_INFO_AMOUNT, SDK_DISP_LEFT_DEFAULT);
        }
        (*pucDispLine)++;

        TrnFormatAmount(tmp, pasTransAmount, TRUE);
        sdkDispFillRowRam(*pucDispLine, 0, tmp, SDK_DISP_RIGHT_DEFAULT);
        (*pucDispLine)++;
    }

    // Check if it's offline PIN
    if (SDK_PED_IC_OFFLINE_PIN == ePinMode)
    {
        Trace("emv", "ePinMode == SDK_PED_IC_OFFLINE_PIN");
        sdkDispFillRowRam(*pucDispLine, 0, STR_INFO_INPUT_OFFLINE_PIN, SDK_DISP_LEFT_DEFAULT);

        if (1 == ucRemainPinTries)
        {
            sdkDispFillRowRam((*pucDispLine) + 1, 0, STR_INFO_LAST_CHANCE, SDK_DISP_LEFT_DEFAULT);
        }
    }
    else
    {
        Trace("emv", "ePinMode != SDK_PED_IC_OFFLINE_PIN");
        sdkDispFillRowRam(*pucDispLine, 0, STR_INFO_INPUT_ONLINE_PIN, SDK_DISP_LEFT_DEFAULT);
    }
    (*pucDispLine)++;
    sdkDispBrushScreen();

    return SDK_OK;
}

/*****************************************************************************
** Description :  Show welcome on external PED screen
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void PedShowWelcome(void)
{
    SDK_PED_WELCOME_STR st_welcome =  {STR_INFO_NEXGO, STR_INFO_WELCOME};

    if(gstAppSysCfg.stSysParam.bIsExtPED)
    {
        sdkPEDDispWelcomStr(&st_welcome, TMR_PROMPT);
    }
    return;
}

/*****************************************************************************
** Description :  Pre-process the menu items
** Parameters  :  input:
                  (1)const ST_MENU *pstMenu : menu description

                  output:
                  (1)ST_MENU_ITEM *pstDispMenu : menu items description need display
                  (2)u32 *puiDispNum : menu items count need display
                  (3)ST_MENU_ITEM *pstHideMenu : menu items description need hide
                  (4)u32 *puiHideNum : menu items count need hide
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void MenuPreProcess(const ST_MENU *pstMenu, 
                    ST_MENU_ITEM *pstDispMenu, 
                    u32 *puiDispNum, 
                    ST_MENU_ITEM *pstHideMenu, 
                    u32 *puiHideNum)
{
    u32 i = 0, j = 0, k = 0;
    
    while(strlen(pstMenu->stItem[i].asText))
    {
        if(!pstMenu->stItem[i].bIsHide)
        {
            memcpy(&pstDispMenu[j++], &pstMenu->stItem[i], sizeof(ST_MENU_ITEM));
        }
        else if(0 != pstMenu->stItem[i].uiKeyValue)
        {
            memcpy(&pstHideMenu[k++], &pstMenu->stItem[i], sizeof(ST_MENU_ITEM));
        }
        i++;
    }
    *puiDispNum = j;
    *puiHideNum = k;
}

/*****************************************************************************
** Description :  Display menu and select by number key
** Parameters  :  input:
                  (1)const ST_MENU *pstMenu : menu description
                  (2)s32 iTimeOut : no operation timeout
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error
                  (2)SDK_ERR : user cancel or timeout
                  (3)SDK_OK : process callback funtion success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  use key "1"-"9" to select menu item, use key "pagedown" and 
                  "pageup" to roll page if one page can't display all item
*****************************************************************************/
s32 MenuSelectByKeyNum(const ST_MENU *pstMenu, s32 iTimeOut)
{
    u8 max_line = DispGetMaxLine() - 1;
    u8 cur_line = SDK_DISP_LINE1;
    u8 max_page = 0;
    u8 cur_page = 0;
    u8 num_purpage = max_line + 1;
    u8 i = 0, j = 0;
    s32 key = 0;
    u8 refresh = 1;
    u8 tmp[128] = {0};
    ST_MENU_ITEM pst_disp[MAX_MENU_ITEM];
    ST_MENU_ITEM pst_hide[MAX_MENU_ITEM];
    u32 disp_num;
    u32 hide_num;

    if(NULL == pstMenu)
    {
        return SDK_PARA_ERR;
    }
    
    memset(pst_disp, 0, sizeof(pst_disp));
    memset(pst_hide, 0, sizeof(pst_hide));

    MenuPreProcess(pstMenu, pst_disp, &disp_num, pst_hide, &hide_num);
    
    if(strlen(pstMenu->asTitle) > 0)
    {
        num_purpage -= 1;
        DispTitle(pstMenu->asTitle);
    }

    max_page = disp_num / num_purpage;
    if(0 == (disp_num % num_purpage))
    {
        max_page--;
    }    
    
    sdkKbKeyFlush();
    while(1)
    {
        if(refresh)
        {
            refresh = 0;

            if(strlen(pstMenu->asTitle) > 0)
            {
                //DispTitle(pstMenu->asTitle);
                DispClearContent();
                cur_line = SDK_DISP_LINE2;
            }
            else
            {
                sdkDispClearScreen();
                cur_line = SDK_DISP_LINE1;
            }
                        
            for(i = 0; i < num_purpage; i++)
            {
                if((cur_page * num_purpage + i) < disp_num)
                {
                    sprintf(tmp, "%d.%s", i + 1, pst_disp[cur_page * num_purpage + i].asText);
                    sdkDispFillRowRam(cur_line++, 0, tmp, 
                                      pst_disp[cur_page * num_purpage + i].uiAlign | SDK_DISP_FDISP | SDK_DISP_INCOL);
                }
                else
                {
                    break;
                }
            }
            if(cur_page > 0 && cur_page < max_page)
            {
                sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_ARROW_UP, SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
                sdkDispFillRowRam(max_line, 0, STR_INFO_ARROW_DOWN, SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
            }
            else if(cur_page > 0)
            {
                sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_ARROW_UP, SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
            }
            else if(0 == cur_page && cur_page < max_page)
            {
                sdkDispFillRowRam(max_line, 0, STR_INFO_ARROW_DOWN, SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
            }
            sdkDispBrushScreen();
        }
        
        key = sdkKbWaitKey(SDK_KEY_MASK_ALL, iTimeOut);
        if(key > SDK_KEY_0 && key <= (SDK_KEY_0 + i))
        {
            if(pst_disp[cur_page * num_purpage + (key - SDK_KEY_1)].pFun)
            {
                pst_disp[cur_page * num_purpage + (key - SDK_KEY_1)].pFun();
                return SDK_OK;
            }
        }
        else if(SDK_KEY_UP == key)
        {
            if(0 < cur_page)
            {
                cur_page--;
                refresh = 1;
            }
        }
        else if(SDK_KEY_DOWN == key)
        {
            if(cur_page < max_page)
            {
                cur_page++;
                refresh = 1;
            }
        }
        else if(SDK_KEY_ESC == key || SDK_TIME_OUT == key)
        {
            return SDK_ERR;
        }
        else
        {
            if(key < 0)
            {
                return SDK_ERR;
            }
            for(j = 0; j < hide_num; j++)
            {
                if(pst_hide[j].uiKeyValue == key && pst_hide[j].pFun)
                {
                    pst_hide[j].pFun();
                    return SDK_OK;
                }
            }
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Display menu and select by pagedown and pageup
** Parameters  :  input:
                  (1)const ST_MENU *pstMenu : menu description
                  (2)s32 iTimeOut : no operation timeout
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error
                  (2)SDK_ERR : user cancel or timeout
                  (3)SDK_OK : process callback funtion success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  use key "pagedown" and "pageup" to select item, the selected 
                  item will display in highlight mode, use key "enter" to confirm
                  the select.
*****************************************************************************/
s32 MenuSelectByKeyEnt(const ST_MENU *pstMenu, s32 iTimeOut)
{
    u8 max_line = DispGetMaxLine() - 1;
    u8 cur_line = SDK_DISP_LINE1;
    u8 num_purpage = max_line + 1;
    u8 start_item = 0;
    u8 end_item = 0;
    u8 cur_item = 0;
    u8 i = 0, j = 0;
    s32 key = 0;
    u8 refresh = 1;
    u8 tmp[128] = {0};
    ST_MENU_ITEM pst_disp[MAX_MENU_ITEM];
    ST_MENU_ITEM pst_hide[MAX_MENU_ITEM];
    u32 disp_num;
    u32 hide_num;

    if(NULL == pstMenu)
    {
        return SDK_PARA_ERR;
    }

    memset(pst_disp, 0, sizeof(pst_disp));
    memset(pst_hide, 0, sizeof(pst_hide));

    MenuPreProcess(pstMenu, pst_disp, &disp_num, pst_hide, &hide_num);
    if(strlen(pstMenu->asTitle) > 0)
    {
        num_purpage -= 1;
        DispTitle(pstMenu->asTitle);
    }

    sdkKbKeyFlush();
    
    while(1)
    {
        if(refresh)
        {
            refresh = 0;
            
            if(strlen(pstMenu->asTitle) > 0)
            {
                //DispTitle(pstMenu->asTitle);
                DispClearContent();
                cur_line = SDK_DISP_LINE2;
            }
            else
            {
                sdkDispClearScreen();
                cur_line = SDK_DISP_LINE1;
            }
            
            if(disp_num < num_purpage)
            {
                end_item = start_item + disp_num - 1;
            }
            else
            {
                end_item = start_item + num_purpage - 1;
            }
                        
            for(i = 0; i < num_purpage; i++)
            {
                if((start_item + i) < disp_num)
                {
                    if(MENU_HIGHLIGHT_NUMBER == pstMenu->eMode)
                    {
                        sprintf(tmp, "%d.%s", i + 1 + start_item, pst_disp[start_item + i].asText);
                    }
                    else
                    {
                        sprintf(tmp, "%s", pst_disp[start_item + i].asText);
                    }
                    
                    if(cur_item == start_item + i)
                    {
                        sdkDispFillRowRam(cur_line++, 0, tmp, 
                                          pst_disp[start_item + i].uiAlign | SDK_DISP_NOFDISPLINE | SDK_DISP_INCOL);
                    }
                    else
                    {
                        sdkDispFillRowRam(cur_line++, 0, tmp, 
                                          pst_disp[start_item + i].uiAlign | SDK_DISP_FDISP | SDK_DISP_INCOL);
                    }
                    
                    if(start_item > 0 && cur_item != start_item)
                    {
                        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_ARROW_UP, 
                                          SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
                    }
                    else if(start_item > 0 && cur_item == start_item)
                    {
                        if(IsTermColorScreen())
                        {
                            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_ARROW_UP, 
                                              SDK_DISP_FDISP |SDK_DISP_RDISP| SDK_DISP_INCOL);
                        }
                        else
                        {
                            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_ARROW_UP, 
                                              SDK_DISP_NOFDISP |SDK_DISP_RDISP| SDK_DISP_INCOL);
                        }
                    }
                    
                    if(end_item < (disp_num - 1) && cur_item != end_item)
                    {
                        sdkDispFillRowRam(max_line, 0, STR_INFO_ARROW_DOWN, 
                                          SDK_DISP_FDISP|SDK_DISP_RDISP| SDK_DISP_INCOL);
                    }
                    else if(end_item < (disp_num - 1) && cur_item == end_item)
                    {
                        if(IsTermColorScreen())
                        {
                            sdkDispFillRowRam(max_line, 0, STR_INFO_ARROW_DOWN, 
                                              SDK_DISP_FDISP |SDK_DISP_RDISP| SDK_DISP_INCOL);
                        }
                        else
                        {
                            sdkDispFillRowRam(max_line, 0, STR_INFO_ARROW_DOWN, 
                                              SDK_DISP_NOFDISP |SDK_DISP_RDISP| SDK_DISP_INCOL);
                        }
                    }
                }
            }
            sdkDispBrushScreen();
        }

        key = sdkKbWaitKey(SDK_KEY_MASK_ALL, iTimeOut);
        if(SDK_KEY_ENTER == key)
        {
            if(pst_disp[cur_item].pFun)
            {
                pst_disp[cur_item].pFun();
                return SDK_OK;
            }
        }
        else if(SDK_KEY_UP == key)
        {
            if(cur_item > start_item)
            {
                cur_item--;
                refresh = 1;
            }
            else if(cur_item > 0)
            {
                cur_item--;
                start_item--;
                refresh = 1;
            }
            else
            {
                sdkSysBeep(SDK_SYS_BEEP_ERR);
            }
        }
        else if(SDK_KEY_DOWN == key)
        {
            if(cur_item < end_item)
            {
                cur_item++;
                refresh = 1;
            }
            else if(cur_item < (disp_num - 1))
            {
                cur_item++;
                start_item++;
                refresh = 1;
            }
            else
            {
                sdkSysBeep(SDK_SYS_BEEP_ERR);
            }
        }
        else if(SDK_KEY_ESC == key || SDK_TIME_OUT == key)
        {
            return SDK_ERR;
        }
        else
        {
            if(key < 0)
            {
                return SDK_ERR;
            }
            for(j = 0; j < hide_num; j++)
            {
                if(pst_hide[j].uiKeyValue == key && pst_hide[j].pFun)
                {
                    pst_hide[j].pFun();
                    return SDK_OK;
                }
            }
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Menu process
** Parameters  :  input:
                  (1)const ST_MENU *pstMenu : menu description
                  (2)s32 iTimeOut : no operation timeout
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error
                  (2)SDK_ERR : user cancel or timeout
                  (3)SDK_OK : process callback funtion success

** Author      :  wenmin   2016-10-18 
** Remarks     :  will use "ST_MENU" member "eMode" to distinguish the menu mode
*****************************************************************************/
s32 MenuProcess(const ST_MENU *pstMenu, s32 iTimeOut)
{        
    gstTransData.stTransLog.eTransID = TRANSID_MAINMENU;
    
    if(pstMenu->eFontSize)
    {
        sdkDispSetFontSize(pstMenu->eFontSize);
    }

    if(MENU_NUMBER == pstMenu->eMode)
    {
        return MenuSelectByKeyNum(pstMenu, iTimeOut);
    }
    else
    {
        return MenuSelectByKeyEnt(pstMenu, iTimeOut);
    }
}


void DispUnpack8583Err(s32 iFieldNo)
{
	u8 buf[30];

	snprintf(buf,30,"unpack Field[%d] err",iFieldNo);
	DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, buf, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
}

