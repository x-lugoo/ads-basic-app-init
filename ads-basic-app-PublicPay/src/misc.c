/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.
                
                       http://www.nexgo.cn/en/

 ******************************************************************************
  File Name     :  misc.c
  Version       :  
  Author        :  wenmin
  Date          :  2016-10-19
  Description   :  This file includes other general functions.


  
******************************************************************************/
#include "global.h"

/*----------------------------------------------------------------------------*/
// name of transaction
static const ST_TRADENAME TabTransName[] =
{
    {TRANSID_SALE,          {STR_TRANS_SALE}},
    {TRANSID_VOID,          {STR_TRANS_VOID}},
    {TRANSID_REFUND,        {STR_TRANS_REFUND}},
    {TRANSID_ADJUST,        {STR_TRANS_ADJUST}},
    {TRANSID_OFFSALE,       {STR_TRANS_SALE}},
    {TRANSID_TIP,           {STR_TRANS_TIP}}
};

/*****************************************************************************
** Description :  Get Transcation Name
** Parameters  :  input:
                  (1)E_TRANS_ID eTransID : Transaction ID
                  output:
                  (1)u8 *pasName : Transaction name
                            
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnGetName(u8 *pasName, E_TRANS_ID eTransID)
{
    u8 i;
    u16 k;

    k = sizeof(TabTransName) / sizeof(ST_TRADENAME);

    for (i = 0; i < k; i++)
    {
        if (TabTransName[i].eTransID == eTransID)
        {
            strcpy(pasName, TabTransName[i].asName);
            break;
        }
    }
}

/*****************************************************************************
** Descriptions:  Display LEDs for indicating the status during the contactless payment.
** Parameters  :  input: 
                  (1)u8 ucLedStatus: lower four bits indicate the status(on/off) of each LED.
                  e.g. 0x0F = 0000 1111, all LEDs are on
                  0x0c = 0000 1010, only 1st and 3rd LEDs are on
                  
** Return      :  None
** Author      :  guozexian 20161020
** Remarks     :
*****************************************************************************/
void TrnDispLed(u8 ucLedStatus)
{
    u8 model[64] = {0};

    sdkSysGetMachineModel(model);

    SDK_DISP_SRECT st_led_g3[4] =
    {
        {LED_TOP_LEFT_X(LED_G3, 0), LED_TOP_LEFT_Y(LED_G3), LED_BOTTOM_RIGHT_X(LED_G3, 0), LED_BOTTOM_RIGHT_Y(LED_G3)},
        {LED_TOP_LEFT_X(LED_G3, 1), LED_TOP_LEFT_Y(LED_G3), LED_BOTTOM_RIGHT_X(LED_G3, 1), LED_BOTTOM_RIGHT_Y(LED_G3)},
        {LED_TOP_LEFT_X(LED_G3, 2), LED_TOP_LEFT_Y(LED_G3), LED_BOTTOM_RIGHT_X(LED_G3, 2), LED_BOTTOM_RIGHT_Y(LED_G3)},
        {LED_TOP_LEFT_X(LED_G3, 3), LED_TOP_LEFT_Y(LED_G3), LED_BOTTOM_RIGHT_X(LED_G3, 3), LED_BOTTOM_RIGHT_Y(LED_G3)},
    };

    SDK_DISP_SRECT st_led_g870[4] =
    {
        {LED_TOP_LEFT_X(LED_G870, 0), LED_TOP_LEFT_Y(LED_G870), LED_BOTTOM_RIGHT_X(LED_G870, 0), LED_BOTTOM_RIGHT_Y(LED_G870)},
        {LED_TOP_LEFT_X(LED_G870, 1), LED_TOP_LEFT_Y(LED_G870), LED_BOTTOM_RIGHT_X(LED_G870, 1), LED_BOTTOM_RIGHT_Y(LED_G870)},
        {LED_TOP_LEFT_X(LED_G870, 2), LED_TOP_LEFT_Y(LED_G870), LED_BOTTOM_RIGHT_X(LED_G870, 2), LED_BOTTOM_RIGHT_Y(LED_G870)},
        {LED_TOP_LEFT_X(LED_G870, 3), LED_TOP_LEFT_Y(LED_G870), LED_BOTTOM_RIGHT_X(LED_G870, 3), LED_BOTTOM_RIGHT_Y(LED_G870)},
    };

    if (!strcmp(model, "G3"))
    {
        sdkDispSetRectColor(&st_led_g3[0], (ucLedStatus & LED_1) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
        sdkDispSetRectColor(&st_led_g3[1], (ucLedStatus & LED_2) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
        sdkDispSetRectColor(&st_led_g3[2], (ucLedStatus & LED_3) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
        sdkDispSetRectColor(&st_led_g3[3], (ucLedStatus & LED_4) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
    }
    else if (!strcmp(model, "G870"))
    {
        sdkDispSetRectColor(&st_led_g870[0], (ucLedStatus & LED_1) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
        sdkDispSetRectColor(&st_led_g870[1], (ucLedStatus & LED_2) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
        sdkDispSetRectColor(&st_led_g870[2], (ucLedStatus & LED_3) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
        sdkDispSetRectColor(&st_led_g870[3], (ucLedStatus & LED_4) ? SDK_DISP_GREEN_COLOR : COLOR_GREP);
    }
    else        //monochrome screen
    {

    }
    sdkDispBrushScreen();
}


/*****************************************************************************
** Description :  Control back light
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnLightCtrl(void)
{
    if (gstAppSysCfg.stSysParam.bIsBacklight)
    {
        sdkSysBlackLightOn();
        sdkSysBlackLightCtro(FALSE); 
    }
}

/*****************************************************************************
** Description :  Light up the screen
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnLightRelease(void)
{
    sdkSysBlackLightCtro(TRUE); 
}

/*****************************************************************************
** Description :  Check the condition of transcation
** Parameters  :  input:
                  (1)bool bIsSaveRecord : Whether to save record
                  (2)bool bIsSupport :Whether it is supported it
                            
** Return      :  (1)TRUE: OK
                  (2)FALSE: Check failed
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckCondition(bool bIsSaveRecord, bool bIsSupport)
{
    bool print = TRUE;
    s32 avail, used, used_rate;
    ST_TRANSLOG st_translog;
    s32 ret;
    ST_BATCHUP_INFO st_batch;
    ST_SETTLE st_settle;
    
    if(!gstLoginInfo.bIsPosLogon)
    {
        if(gstAppSysCfg.stTransParam.bIsAutoLogon)
        {
            memcpy(&st_translog, &gstTransData.stTransLog, sizeof(ST_TRANSLOG));
            gstLoginInfo.ucUserNO = 1;
            ret = LogonSendMsg();
            memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
            if(SDK_OK != ret)
            {
                TrnSetStatus(ERR_LOGON_FAIL);
                return FALSE;
            }
            gstTransData.stTransLog.stMsgInfo.ucCashierNO = 1;
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LOGON_SUCCESS, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ENTER, TMR_PROMPT);
        }
        else
        {
            TrnSetStatus(ERR_NO_LOGON);
            return FALSE;
        }
    }
    else if((ADMINNO == gstLoginInfo.ucUserNO) || (SYSADMINNO == gstLoginInfo.ucUserNO))
    {
        TrnSetStatus(ERR_NO_CASHIER);
        return FALSE;
    }
    
    memcpy(&st_translog, &gstTransData.stTransLog, sizeof(ST_TRANSLOG));
    ret = RecordSearch(LOG_STAT_NEEDREPRINT, (void *)&print, &gstTransData.stTransLog);
    if(SDK_OK == ret)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_LAST_PRINT_FAILED, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REPRINT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
        {
            ret = PrintRecipt(TRUE);
            if(SDK_OK != ret)
            {
                memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
                TrnSetStatus(ERR_REPRINT);
                return FALSE;
            }
        }
        else
        {
            memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
            TrnSetStatus(ERR_REPRINT);
            return FALSE;
        }
    }
    
    memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));
    
    if (TRANSID_SETTLE != gstTransData.stTransLog.eTransID)
    {
        if (SDK_OK == BatchUpReadInfo(&st_batch))
        {
            TrnSetStatus(ERR_SETTLE_STARTED);
            return FALSE;
        }
    }

    if((TRANSID_SETTLE == gstTransData.stTransLog.eTransID && SDK_OK != BatchUpReadInfo(&st_batch))
        || TRANSID_SETTLE != gstTransData.stTransLog.eTransID)
    {
        if(SDK_OK == SettleReadInfo(&st_settle))
        {
            if(SETTLE_SEND == st_settle.ucPrintState)
            {
                SettleDeleteInfo();
            }
            else if(SETTLE_CLEARED != st_settle.ucPrintState)
            {
                TrnSetStatus(ERR_SETTLE_PRINT);
                return FALSE;
            }
        }
    }
    
    if (bIsSaveRecord)      //need save record
    {
        if (!sdkDf("/mtd0", &avail, &used, &used_rate))
        {
            TrnSetStatus(ERR_FILE_SYSTEM);
            return FALSE;
        }

        if (avail < 200)   //flash less than 200K
        {
            TrnSetStatus(ERR_MEMORY_FULL);
            return FALSE;
        }
        else
        {
            if (RecordGetNum() >= gstAppSysCfg.stTransParam.uiMaxTransNum)  //Transaction records number is reach the limit
            {
                TrnSetStatus(ERR_TRANSNUM_LIMIT);
                return FALSE;
            }
        }
    }
    
    if(!bIsSupport)
    {
        TrnSetStatus(ERR_TRANS_NOSUPPORT);
        return FALSE;
    }

    memcpy(&gstTransData.stTransLog, &st_translog, sizeof(ST_TRANSLOG));

    return TRUE;
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
s32 TrnCheckTotalAmount(E_TRANS_ID eTransID, u8 *asAmount)
{
    u8 tmp[16+1] = {0};
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2, value3;
    bool value4;
    long long amt_cur, amt_total;
    long long amt_tmp;

    if(NULL == asAmount)
    {
        return SDK_PARA_ERR;
    }

    memset(st_filter, 0, sizeof(st_filter));
    amt_cur = atoll(asAmount);
    amt_tmp = atoll("999999999999");

    switch(eTransID)
    {
        case TRANSID_SALE:
        case TRANSID_ADJUST:
        case TRANSID_TIP:
            value1 = TRANSID_SALE;
            value2 = TRANSID_TIP;
            value3 = TRANSID_ADJUST;
            value4 = FALSE;

            st_filter[0].iId = LOG_TRANSID;
            st_filter[0].eMode = FILTER_MULTI;
            st_filter[0].pasValue[0] = &value1;
            st_filter[0].pasValue[1] = &value2;
            st_filter[0].pasValue[2] = &value3;
            st_filter[0].iNum = 3;
            
            st_filter[1].iId = LOG_STAT_ADJUSTED;
            st_filter[1].eMode = FILTER_SIGNEL;
            st_filter[1].pasValue[0] = &value4;
            
            st_filter[2].iId = LOG_STAT_ICCFAILTRANS;
            st_filter[2].eMode = FILTER_SIGNEL;
            st_filter[2].pasValue[0] = &value4;
            
            st_filter[3].iId = LOG_STAT_NEEDREVERSAL;
            st_filter[3].eMode = FILTER_SIGNEL;
            st_filter[3].pasValue[0] = &value4;
            
            st_filter[4].iId = -1;

            RecordGetSum(LOG_MSG_AMOUNT, st_filter, tmp);
            Trace("misc", "TrnCheckTotalAmount = %s\r\n", tmp);
            amt_total = atoll(tmp);
            if((amt_total + amt_cur) > amt_tmp)
            {
                return SDK_ERR;
            }
            break;

        case TRANSID_VOID:
        case TRANSID_REFUND:
            value1 = TRANSID_VOID;
            value2 = TRANSID_REFUND;
            value4 = FALSE;

            st_filter[0].iId = LOG_TRANSID;
            st_filter[0].eMode = FILTER_MULTI;
            st_filter[0].pasValue[0] = &value1;
            st_filter[0].pasValue[1] = &value2;
            st_filter[0].iNum = 2;
            
            st_filter[1].iId = LOG_STAT_NEEDREVERSAL;
            st_filter[1].eMode = FILTER_SIGNEL;
            st_filter[1].pasValue[0] = &value4;
                
            st_filter[2].iId = -1;

            RecordGetSum(LOG_MSG_AMOUNT, st_filter, tmp);
            amt_total = atoll(tmp);
            if((amt_total + amt_cur) > amt_tmp)
            {
                return SDK_ERR;
            }
            break;

        default:
            return SDK_OK;
    }
   
    return SDK_OK;
}

s32 TrnCheckCashBackAmount(u8 *asAmount, u8 *asCashBack)
{
    long long amt, amt_cash;
    long long amt_tmp;

    if(NULL == asAmount || NULL == asCashBack)
    {
        return SDK_PARA_ERR;
    }

    amt = atoll(asAmount);
    amt_cash = atoll(asCashBack);
    amt_tmp = atoll("999999999999");

    if((amt + amt_cash) > amt_tmp)
    {
        return SDK_ERR;
    }
   
    return SDK_OK;
}

/*****************************************************************************
** Description :  Check if the transaction need to print detail
** Parameters  :  input:
                  (1)ST_TRANSLOG *pstTransLog :Transaction log
                            
** Return      :  (1)TRUE: need to print detail
                  (2)FALSE: do not need to print detail
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckPrintDetail(ST_TRANSLOG *pstTransLog)
{
    if(pstTransLog->stTransStatus.bIsVoided 
       || pstTransLog->stTransStatus.bIsAdjusted
       || pstTransLog->stTransStatus.bIsIccFailTrans
       || pstTransLog->stTransStatus.bIsNeedReversal)
    {
        return FALSE;
    }
    
    if (TRANSID_SALE == pstTransLog->eTransID 
        || TRANSID_OFFSALE == pstTransLog->eTransID
        || TRANSID_TIP == pstTransLog->eTransID
        || TRANSID_REFUND == pstTransLog->eTransID)
    {
        return TRUE;
    }

    return FALSE;
}

/*****************************************************************************
** Description :  Increase trace number
** Parameters  :  input:
                  (1)s32 iNum : increased  number
                            
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnIncTraceNo(s32 iNum)
{
    s32 i = 0;

    i = atoi(gstAppSysCfg.stTransParam.asTraceNO);

    i += iNum;

    if ((i < 1) || (i > 999999))
    {
        i = 1;
    }
    sprintf(gstAppSysCfg.stTransParam.asTraceNO, "%06d", i);
    SetupSaveSetting();
}

/*****************************************************************************
** Description :  Increase the batch number
** Parameters  :  input:
                  (1)s32 iNum : increased number
                           
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnIncBatchNo(s32 iNum)
{
    s32 i = 0;

    i = atoi(gstAppSysCfg.stTransParam.asBatchNO);

    i += iNum;

    if ((i < 1) || (i > 999999))
    {
        i = 1;
    }
    sprintf(gstAppSysCfg.stTransParam.asBatchNO, "%06d", i);
    SetupSaveSetting();
}

/*****************************************************************************
** Description :  Get the input number string
** Parameters  :  input:
                  (1)s32 iTimeOut : timeout(ms)
                  (2)s32 iMinLen : min len
                  (3)s32 iMaxLen : max len
                  (4)s32 iLine : display row
                  output:
                  (1)u8 *pasNumber : number string
                            
** Return      :  (1)The key value of number

** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnGetNumber(s32 iTimeOut, u8 *pasNumber, s32 iMin, s32 iMax, s32 iLine)
{
    s32 key;
    u8 tmp[64];
    s32 min_len, max_len;
    s32 value;

    sprintf(tmp, "%d", iMax);
    max_len = strlen(tmp);
    sprintf(tmp, "%d", iMin);
    min_len = strlen(tmp);

    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, pasNumber, pasNumber[0] + 1);

    while(1)
    {
        key = sdkKbGetScanf(iTimeOut, tmp, min_len, max_len, SDK_MMI_NUMBER, iLine);
        if(SDK_KEY_ENTER == key)
        {
            value = atoi(&tmp[1]);
            if(value < iMin || value > iMax)
            {
                sdkSysBeep(SDK_SYS_BEEP_ERR);
                continue;
            }
            memcpy(pasNumber, tmp, tmp[0] + 1);
        }
        break;
    }

    return key;
}

/*****************************************************************************
** Description :  Callback function for TransGatAmount to disp formated amount
** Parameters  :  input:
                  (1)const u32 uiMode: Display mode
                  (2)const s32 siDispRow: Display row
                  (3)void *pVar: reserved
                  output:                
                  (1)u8 *pStrDisp: Displayed string
                        
** Return      :  (1)SDK_OK: succeeded
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 CbTrnDispAmount(u8 *pStrDisp, const u32 uiMode, const s32 siDispRow, void *pVar)
{
    u8 tmp[32], amt[32];

    sdkDispClearRowRam(siDispRow);
    TrnPadding(tmp, pStrDisp, '0', 12, RIGHT_ALIGN);   // Pad leading '0's to amount string
    TrnFormatAmount(amt, tmp, TRUE);
    sdkDispFillRowRam(siDispRow, 0, amt, SDK_DISP_RIGHT_DEFAULT);
    sdkDispBrushScreen();

    return SDK_OK;
}

/*****************************************************************************
** Description :  Get amount from the keypad
** Parameters  :  input:
                  (1)s32 iTimeOut : Timeout(ms)
                  (2)s32 iLine : Display row
                  (3)bool bIsAllowZero: Whether to support amount "0"

                  output: 
                  (1)u8 *pasAmount : Amount string
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)Key Value
                  (3)SDK_TIME_OUT: time out
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnGetAmount(s32 iTimeOut, u8 *pasAmount, s32 iLine, bool bIsAllowZero)
{
    s32 key;
    s32 timid;
    bool nomorekey = 0;
    u8 amtbuf[16] = {0}, strbuf[32] = {0};
    u8 amt[12 + 1];

    sdkDispClearRowRam(iLine);
    memset(amt, 0, sizeof(amt));
    TrnPadding(amt, pasAmount, '0', 12, RIGHT_ALIGN);   // Pad leading '0's to amount string
    memset(strbuf, 0, sizeof(strbuf));
    TrnFormatAmount(strbuf, amt, TRUE);
    sdkDispFillRowRam(iLine, 0, strbuf, SDK_DISP_RIGHT_DEFAULT);
    sdkDispBrushScreen();

    strcpy(&amtbuf[1], pasAmount);
    amtbuf[0] = strlen(pasAmount);

    // Start timer for input timeout
    timid = sdkTimerGetId();

    // If timeout, quit the loop
    while (!sdkTimerIsEnd(timid, iTimeOut))
    {
        // Check for valid key
        if ((key = sdkKbGetKey()) > 0)
        {
            // Restart timer
            timid = sdkTimerGetId();

            // Non-numeric key was pressed
            if (key < SDK_KEY_0 || key > SDK_KEY_9)
            {
                switch (key)
                {
                     // Finish inputting
                     case SDK_KEY_ENTER:
                        {
                            // Continue inputting if string length is less than minimum length
                            if (amtbuf[0] < 1)
                            {
                                if(bIsAllowZero)
                                {
                                    return SDK_OK;
                                }
                                else
                                {
                                    sdkSysBeep(SDK_SYS_BEEP_ERR);
                                    continue;
                                }
                            }
                            memcpy(pasAmount, &amtbuf[1], amtbuf[0]);
                        }

                     case SDK_KEY_ESC:
                        {
                            sdkSysBeep(SDK_SYS_BEEP_OK);
                            return key;

                            // Delete the last character inputted if available
                        }

                     case SDK_KEY_BACKSPACE:
                     case SDK_KEY_CLEAR:
                        {
                            if (amtbuf[0] > 0)
                            {
                                sdkSysBeep(SDK_SYS_BEEP_OK);
                                amtbuf[amtbuf[0]] = '\0';
                                amtbuf[0]--;
                                nomorekey = 0;
                            }
                            else
                            {
                                sdkSysBeep(SDK_SYS_BEEP_ERR);
                                continue;
                            }
                        }
                        break;

                     default:
                       sdkSysBeep(SDK_SYS_BEEP_ERR);
                       continue;
                }
            }
            else   // Numeric key was pressed
            {
                // No more input is allowed
                if (nomorekey)
                {
                    sdkSysBeep(SDK_SYS_BEEP_ERR);
                    continue;
                }

                // The first digit couldn't be '0'
                if (0 == amtbuf[0] && '0' == key)
                {
                    sdkSysBeep(SDK_SYS_BEEP_ERR);
                    continue;
                }
                sdkSysBeep(SDK_SYS_BEEP_OK);

                if (++amtbuf[0] >= 9)
                //if (++amtbuf[0] >= 12)
                {
                    nomorekey = 1;
                }
                amtbuf[amtbuf[0]] = key;
            }
                        
            // Display characters inputted
            sdkDispClearRowRam(iLine);

            TrnPadding(amt, &amtbuf[1], '0', 12, RIGHT_ALIGN);   // Pad leading '0's to amount string
            TrnFormatAmount(strbuf, amt, TRUE);
            sdkDispFillRowRam(iLine, 0, strbuf, SDK_DISP_RIGHT_DEFAULT);

            sdkDispBrushScreen();
        }
    }

    return SDK_TIME_OUT;

    //return sdkKbGetScanfEx(iTimeOut, pasAmount, 1, 12, SDK_MMI_NUMBER, iLine, TransDispAmountCb, NULL, SDK_MMI_NUMBER);
}

/*****************************************************************************
** Description :  Change or update a password
** Parameters  :  input:
                  (1)u8 *pasTitle : Displayed title
                  (2) u32 uiLen : Password length
                            
                  output:
                  (1)u8 *pasPassword : New password
                            
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnPasswordUpdate(u8 *pasTitle, u8 *pasPassword, u32 uiLen)
{
    u8 tmp[32];
    u8 temp_again[32];

    // Display title
    DispTitle(pasTitle);
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_ORIG_PWD, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, uiLen, uiLen, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE3))
    {
        return FALSE;
    }
    if(0 != memcmp(pasPassword, &tmp[1], tmp[0]))
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_ORIG_PWD_INCORRECT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT);
        return FALSE;
    }

    while(1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_NEW_PWD, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(tmp, 0, sizeof(tmp));
        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, uiLen, uiLen, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE3))
        {
            return FALSE;
        }
        
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_PWD_AGAIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(temp_again, 0, sizeof(temp_again));
        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, temp_again, uiLen, uiLen, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE3))
        {
            return FALSE;
        }

        if(0 != memcmp(&tmp[1], &temp_again[1], temp_again[0]))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PWD_NOT_MATCH, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                continue;
            }
            return FALSE;
        }
        else
        {
            break;
        }
    }
    
    memcpy(pasPassword, &tmp[1], tmp[0]);
    
    return TRUE;
}

/*****************************************************************************
** Description :  Set a password
** Parameters  :  input:
                  (1)u8 *pasTitle : Displayed title
                  (2)u32 uiLen : Password length
                            
                  output:
                  (1)u8 *pasPassword : Password
                            
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE: Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnPasswordSet(u8 *pasTitle, u8 *pasPassword, u32 uiLen)
{
    u8 tmp[32];
    u8 temp_again[32];

    // Display title
    DispTitle(pasTitle);
    
    while(1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_PLS_INPUT_PWD, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(tmp, 0, sizeof(tmp));
        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, tmp, uiLen, uiLen, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE3))
        {
            return FALSE;
        }
        
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_SETUP_PLS_INPUT_PWD_AGAIN, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(temp_again, 0, sizeof(temp_again));
        if (SDK_KEY_ENTER != TrnInputLine(TMR_OPERATE, temp_again, uiLen, uiLen, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE3))
        {
            return FALSE;
        }

        if(0 != memcmp(&tmp[1], &temp_again[1], temp_again[0]))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PWD_NOT_MATCH, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                continue;
            }
            return FALSE;
        }
        else
        {
            break;
        }
    }
    
    memcpy(pasPassword, &tmp[1], tmp[0]);

    return TRUE;
}
/*****************************************************************************
** Description :  Convert BCD-coded amount into the displayed string
** Parameters  :  input:
                  (1)u8 const *pasAmount : Amount
                  (2)bool bIsCurrency: Whether it is a currency.

                  output:
                  (1)u8 *pasStr : Displayed amount
                            
** Return      :  void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnFormatAmount(u8 *pasStr, u8 const *pasAmount, bool bIsCurrency)
{
    s32 amt;
    u8 point = gstAppSysCfg.stTermInfo.uiAmountDecimalLen;
    u8 len = 0;
    u8 tmp[32];

    len = 12 - strspn(pasAmount, "0");

    memset(tmp, 0, sizeof(tmp));

    if(bIsCurrency)
    {
        sprintf(tmp, "%s ", gstAppSysCfg.stTermInfo.asCurrencyName);
    }
    
    if(0 == point)
    {
        if(len > 0)
        {
            sprintf(&tmp[strlen(tmp)], "%s", &pasAmount[12 - len]);
        }
        else
        {
            strcpy(&tmp[strlen(tmp)], "0");
        }
    }
    else if(len <= point)
    {
        amt = atoi(pasAmount);
        sprintf(&tmp[strlen(tmp)], "0.%0*d", point, amt);
    }
    else
    {
        sprintf(&tmp[strlen(tmp)], "%.*s.%.*s", (len - point), &pasAmount[12 - len], point, &pasAmount[12 - point]);
    }

    strcpy(pasStr, tmp);
}

/*****************************************************************************
** Description :  Input card PIN
** Parameters  :  input:
                  (1)bool bIsWithPan : Whether it is with PAN.
                  (2)SDK_ICC_CARDDATA const *pstCardData : Card data structure
                  (3)s32 iDispLine : Display row
                            
                  output:
                  (1)u8 *phePwd : Password ciphertext
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)SDK_ESC: User cancelled
                  (3)SDK_TIME_OUT: Time out
                  (4)SDK_PED_NOPIN: No pin input
                        
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnInputPin(bool bIsWithPan, const u8 *pasTransAmount, SDK_ICC_CARDDATA const *pstCardData, u8 *phePwd, s32 iDispLine)
{
    SDK_PED_PIN_CFG st_pincfg;
    s32 len;
    s32 ret;
    u8 ksn_len;
    u8 amt[6] = {0};
    u8 *p_amt = NULL;

    if(NULL != pasTransAmount)
    {
        sdkAscToBcdR(amt, pasTransAmount, 6);
        p_amt = amt;
    }

    memset(&st_pincfg, 0, sizeof(st_pincfg));
    st_pincfg.ePinMode = SDK_PED_IC_ONLINE_PIN;
    st_pincfg.ucRow = iDispLine;
    st_pincfg.iTimeOut = TMR_OPERATE;
    if(gstAppSysCfg.stSecureKey.bIsUseDUKPT)
    {
        st_pincfg.eKeyType = SDK_PED_DES_DUKPT;
        st_pincfg.ucTpkIndex = 0;
    }
    else
    {
        st_pincfg.eKeyType = gstAppSysCfg.stSecureKey.bIsTripleDES ? SDK_PED_DES_TRIPLE : SDK_PED_DES_SINGLE;
        st_pincfg.ucTpkIndex = gstAppSysCfg.stSecureKey.uiTpkIndex;
    }

    // Whether card number should be involved in PIN encryption
    if (bIsWithPan)
    {
        len = strlen(pstCardData->asCardNO);

        if (len >= 13)
        {
            sdkAscToBcd(st_pincfg.hePan + 2, pstCardData->asCardNO + len - 13, 12);
        }
    }
    // Input PIN from pin pad
    while(1)
    {
        if(gstAppSysCfg.stSecureKey.bIsUseDUKPT)
        {
            ret = sdkPEDDukptGetPin(SDK_PED_DUKPT_GET_PIN_RELEASE, 0, &st_pincfg, 4, 12, phePwd, gstTransData.heKSN, &ksn_len, TMR_OPERATE);
        }
        else
        {
            ret = sdkPEDInputPIN(&st_pincfg, p_amt, phePwd);
        }

        if (SDK_OK != ret && SDK_PED_NOPIN != ret)
        {
            if(SDK_PED_PIN_FORMAT_ERR == ret)
            {
                continue;
            }
            if(SDK_ESC == ret || SDK_TIME_OUT == ret)
            {
                TrnSetStatus(ret);
            }
            else
            {
                TrnSetStatus(ERR_ENCRYPT);
            }
            sdkPEDCancel();
        }
        break;
    }

    if(SDK_OK == ret && gstAppSysCfg.stSecureKey.bIsUseDUKPT)
    {
        memmove(&phePwd[1], phePwd, 8);
        phePwd[0] = 8;
    }
    
    return ret;
}

/*****************************************************************************
** Description :  Function of swiping card
** Parameters  :  input:
                  (1)s32 iCardMode : Card type(ICC/RF/MAG)
                  (2)SDK_ICC_TRADE_PARAM *pstIccTradeParam :Related EMV data parameter

                  output:
                  (1)ST_CARDINFO *pstCardInfo : Card info
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)SDK_EQU: Wait for swiping again
                  (3)SDK_ERR: Failed
                  (4)ERR_CHIPMAGCARD: It is a ICC. Do not allow swiping
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnProcSwipe(s32 iCardMode, SDK_ICC_TRADE_PARAM *pstIccTradeParam, ST_CARDINFO *pstCardInfo)
{
    s32 ret = SDK_ESC;
    
    // Read magnetic stripe card
    ret = sdkIccGetMagData(&pstCardInfo->stCardParam, &pstCardInfo->stCardData);

    switch (ret)
    {
        // Get track data successfully
        case SDK_OK:
            if(pstCardInfo->stCardData.bIsIccMagCard && CTLSFLOW_FALLBACK != pstCardInfo->stCardParam.ucCLType)
            {
                DispClearContent();
                if((iCardMode & SDK_ICC_ICC) || (iCardMode & SDK_ICC_RF))
                {
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CHIP_CARD_PLS_INSERT, SDK_DISP_DEFAULT);
                }
                else
                {
                    return SDK_OK;
                }
                sdkDispBrushScreen();
                if(SDK_KEY_ESC == sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT))
                {
                    return SDK_ERR;
                }
                return ERR_CHIPMAGCARD;
            }
            sdkIccCloseMag();
            if (iCardMode & SDK_ICC_RF)
            {
                sdkIccPowerDown(); //Power OFF Contactless IC Card Reader
            }
            return SDK_OK;
            // Error occurred while swiping card
            
        case SDK_ICC_BRUSH_ERR:
            sdkSysBeep(SDK_SYS_BEEP_ERR);
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_READ_CARD_ERROR, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_PLEASE_TRY_AGAIN, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();

            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
            break;

        // No card detected
        case SDK_ICC_NOCARD:
            break;

        // Quit reading card on other errors
        default:
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_READ_CARD_ERROR, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();

            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
            sdkIccCloseMag();
            if (iCardMode & SDK_ICC_RF)
            {
               sdkIccPowerDown(); //Power OFF Contactless IC Card Reader
            }
            return SDK_ERR;
    }

    return SDK_EQU;
}

/*****************************************************************************
** Description :  Manual input card number
** Parameters  :  input:
                  (1)s32 iCardMode : Card type(ICC/RF/MAG)
                  (2)s32 iKey : Key
                  (3)SDK_ICC_TRADE_PARAM *pstIccTradeParam : Related EMV data parameter

                  output:
                  (1)ST_CARDINFO *pstCardInfo :Card info
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)SDK_ERR:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnProcManual(s32 iCardMode, s32 iKey, SDK_ICC_TRADE_PARAM *pstIccTradeParam, ST_CARDINFO *pstCardInfo)
{
    u8 tmp[32];
    s32 ret;

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_CARDNO, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    tmp[0] = 1;
    tmp[1] = iKey;
    ret = sdkKbGetScanf(TMR_OPERATE, tmp, 13, 19, SDK_MMI_NUMBER, SDK_DISP_LINE3);
    if (SDK_KEY_ENTER != ret)
    {
        return SDK_ERR;
    }

    pstCardInfo->stCardData.ucCardLen = tmp[0];
    memcpy(pstCardInfo->stCardData.asCardNO, &tmp[1], tmp[0]);
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Function of inserting card
** Parameters  :  input:
                  (1)s32 iCardMode  : Card type(ICC/RF/MAG)
                  (2)SDK_ICC_TRADE_PARAM *pstIccTradeParam  : Related EMV data parameter

                  output:
                  (1)ST_CARDINFO *pstCardInfo  :Card info
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)SDK_EQU: Waiting for card
                  (3)SDK_ESC: No card detected, quit.

** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnProcInsert(s32 iCardMode, SDK_ICC_TRADE_PARAM *pstIccTradeParam, ST_CARDINFO *pstCardInfo)
{
    s32 ret = SDK_ESC;
    
    // Check if IC is inserted
    ret = sdkIccGetCardStatus(&pstCardInfo->stCardParam, 50);

    if (SDK_OK == ret)
    {
        sdkSysBeep(SDK_SYS_BEEP_OK);
        if (iCardMode & SDK_ICC_RF)
        {
            sdkIccPowerDown(); //Power OFF Contactless IC Card Reader
        }        
        return SDK_OK;
    }
    else if (SDK_ICC_NOCARD != ret)
    {
        DispEmvReadCardReturn(ret);
        if (iCardMode & SDK_ICC_RF)
        {
            sdkIccPowerDown(); //Power OFF Contactless IC Card Reader
        }
        return SDK_ESC;
    }
    
    return SDK_EQU;
}

/*****************************************************************************
** Description :  Function for reading CTLS card
** Parameters  :  input:
                  (1)s32 iCardMode  : Card type(ICC/RF/MAG)
                  (2)SDK_ICC_TRADE_PARAM *pstIccTradeParam  : Related EMV data parameter
                  (3)u32 uiTimer : Timeout(ms)

                  output:
                  (1)ST_CARDINFO *pstCardInfo  :Card info
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)SDK_EQU: Waiting for card
                  (3)SDK_ESC: No card detected, quit.
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnProcTap(s32 iCardMode, SDK_ICC_TRADE_PARAM *pstIccTradeParam, ST_CARDINFO *pstCardInfo, u32 uiTimer)
{
    u8 uid[64] = {0}; //uid[0]:Length of UID£»heUID[1~x]:body data of UID
    s32 ret = SDK_ESC;
    //bool is_msd = FALSE;
    
    //Power on and detecting the card
    ret = sdkIccPowerOnAndSeek(pstIccTradeParam, &pstCardInfo->stCardParam, uid);
    if (SDK_OK == ret)
    {
        Trace("misc", "ucCLType=%02d    RFcard ok!+++++\r\n", pstCardInfo->stCardParam.ucCLType);
        //return Qflow ,make sure the external Contactless PINPAD
        if (CTLSFLOW_QUICK == pstCardInfo->stCardParam.ucCLType)
        {
            //gstTransInfo.bis02Protocol = TRUE;
        }
        return SDK_OK;
    }
    else if(SDK_ICC_PLS_INSERT_CARD == ret)//inset card  //contact interface
    {
        memset(pstCardInfo, 0, sizeof(ST_CARDINFO));

        if (iCardMode & SDK_ICC_RF)
        {
            sdkIccPowerDown();
            iCardMode &= ~SDK_ICC_RF;
        }
        DispReadCardErr(1);
        sdkSysBeep(SDK_SYS_BEEP_ERR);

        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_WAITKEY);

        if( gstAppSysCfg.stSysParam.bIsExtPED )
        {
            sdkPEDCancel();
        }
        return SDK_ESC;
    }
    else if (SDK_ICC_NOCARD != ret && SDK_ICC_MORECARD != ret) //No Card or More than one card
    {
        sdkIccPowerDown();    //Power off
        DispEmvReadCardReturn(ret);
        return SDK_ESC;
    }

    return SDK_EQU;
}

/*****************************************************************************
** Description :   Process reading card
** Parameters  :  input:
                  (1)s32 iCardMode  : Card type(ICC/RF/MAG)
                  (2)SDK_ICC_TRADE_PARAM *pstIccTradeParam  : Related EMV data parameter

                  output:
                  (1)ST_CARDINFO *pstCardInfo  :Card info

** Return      :  (1)SDK_OK:  Succeeded
                  (2)SDK_ESC: No card detected, quit.
                  (3)SDK_EQU: For online wait, fallback or simplied flow
                  (4)CARDPROC_OFFLINE_SUCC: Offline aproved
                  (5)CARDPROC_OFFLINE_FAIL: Offline declined
                  (6)CARDPROC_CTLS_SWITCH: For CTLS it switches to swiping
                        
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnReadCard(s32 iCardMode, SDK_ICC_TRADE_PARAM *pstIccTradeParam, ST_CARDINFO *pstCardInfo)
{
    bool bflag = 1;
    u32 timer = sdkTimerGetId();
    u32 rf_timer; 
    s32 ret = SDK_ESC;
    s32 key;
    u8 buf[64];
    E_ICCRET e_iccret;
    u8 tmp[128];

    if (iCardMode & SDK_ICC_RF)
    {
        EmvInitPayPassWave(pstIccTradeParam);
    }

    if (iCardMode & SDK_ICC_ICC || iCardMode & SDK_ICC_RF)
    {
        EmvConfigTransParam(&gstTransData, pstIccTradeParam);
    }

    if ((NULL == pstIccTradeParam || SDK_OK != sdkIccTransInit(pstIccTradeParam))
        && (iCardMode & SDK_ICC_RF || iCardMode & SDK_ICC_ICC))
    {
        if (iCardMode & SDK_ICC_RF)
        {
            sdkIccPowerDown();            //Power off Contactless Card Reader
        }
        DispEmvReadCardReturn(SDK_PARA_ERR);       //Display message and exit
        return SDK_ESC;
    }
    
    if (iCardMode & SDK_ICC_MAG)
    {
        // Open magnetic stripe card reader
       sdkIccOpenMag();
    }
    if (iCardMode & SDK_ICC_ICC)
    {
        sdkIccOpenIcDev(); //For Contact IC Card
    }

    if (iCardMode & SDK_ICC_RF)
    {
        sdkIccOpenRfDev(); //For Contactless IC Card
    }
    sdkKbKeyFlush();        // Flush key buffer

    rf_timer = sdkTimerGetId();

    while (1)
    {
        key = sdkKbGetKey();
        
        if (SDK_KEY_ESC == key)
        {
            pstCardInfo->stCardParam.ucCardMode = 0;

            if (iCardMode & SDK_ICC_RF)
            {
                sdkIccPowerDown(); 
            }
            TrnSetStatus(SDK_ESC);
            return SDK_ESC;
        }
        
        if (bflag)
        {
            DispReadCard(iCardMode);
            bflag = 0;
            // Get timer id
            timer = sdkTimerGetId();
        }

        // If timeout, return to previous menu
        if (sdkTimerIsEnd(timer, TMR_OPERATE))
        {
            if (iCardMode & SDK_ICC_RF)
            {
                sdkIccPowerDown(); 
            }
            TrnSetStatus(SDK_TIME_OUT);
            return SDK_TIME_OUT;
        }

        // Read magnetic card
        if (iCardMode & SDK_ICC_MAG)
        {
            ret = TrnProcSwipe(iCardMode, pstIccTradeParam, pstCardInfo);
            if(SDK_ERR == ret)
            {
                return SDK_ESC;
            }
            else if(SDK_OK == ret)
            {
                memset(buf, 0, sizeof(buf));
                ret = TrnGetMagCardNo(&pstCardInfo->stCardData, buf);
                if(SDK_OK != ret || (pstCardInfo->stCardData.ucCardLen > 0 && !DispCardNo(buf)))
                {
                    return SDK_ESC;
                }
                return SDK_OK;
            }
            else if(ERR_CHIPMAGCARD == ret)
            {
                iCardMode &= (~SDK_ICC_MAG);
                bflag = 1;
            }
        }

        // Read IC card
        if (iCardMode & SDK_ICC_ICC)
        {
            ret = TrnProcInsert(iCardMode, pstIccTradeParam, pstCardInfo);
            if(SDK_ESC == ret)
            {
                return SDK_ESC;
            }
            else if(SDK_OK == ret)
            {
                // EMV mandatory flow
                e_iccret = EmvMandatoryTransFlowStart(pstIccTradeParam, pstCardInfo);

                if (ICCRET_OFFLINE_APPROVE == e_iccret || ICCRET_OFFLINE_DECLINE == e_iccret)
                {
                    if(ICCRET_OFFLINE_APPROVE == e_iccret)  //offline approved
                    {
                        return CARDPROC_OFFLINE_SUCC;
                    }
                    else                                    //offline declined
                    {
                        return CARDPROC_OFFLINE_FAIL;
                    }
                }
                else if(ICCRET_FALLBACK == e_iccret)
                {
                    return SDK_OK;
                }
                else if(ICCRET_ONLINE_WAIT == e_iccret || ICCRET_FALLBACK == e_iccret || ICCRET_EASYFLOW == e_iccret)
                {
                    return SDK_EQU;
                }
                else if (ICCRET_EASYFLOW != e_iccret)
                {
                    return SDK_ESC;
                }
            }
        }

        //Read Contactless Card
        if (iCardMode & SDK_ICC_RF)
        {
            ret = TrnProcTap(iCardMode, pstIccTradeParam, pstCardInfo, timer);

            if(SDK_ESC == ret)
            {
                return SDK_ESC;
            }
            else if(SDK_OK == ret)
            {
                // EMV mandatory flow
                e_iccret = EmvMandatoryTransFlowStart(pstIccTradeParam, pstCardInfo);

                if (ICCRET_OFFLINE_APPROVE == e_iccret || ICCRET_OFFLINE_DECLINE == e_iccret || ICCRET_CTLS_SWITCH == e_iccret
                    || ICCRET_CTLS_FALLBACK == e_iccret || ICCRET_DISCOVERY == e_iccret)
                {
                    switch(e_iccret)
                    {
                         case ICCRET_OFFLINE_APPROVE:
							e_iccret = CARDPROC_OFFLINE_SUCC;
                            break;

                         case ICCRET_OFFLINE_DECLINE:
                            e_iccret = CARDPROC_OFFLINE_FAIL;
                            break;

                         case ICCRET_CTLS_SWITCH:
                            e_iccret = CARDPROC_CTLS_SWITCH;
                            break;

                         case ICCRET_CTLS_FALLBACK:
                            e_iccret = CARDPROC_CTLS_FALLBACK;
                            break;

                         case ICCRET_DISCOVERY:
                            e_iccret = CARDPROC_DISCOVERY;
                            break;

                         default:
                            e_iccret = CARDPROC_OFFLINE_FAIL;
                            break;
                    }
                    return e_iccret;
                }
                else if (ICCRET_ONLINE_WAIT == e_iccret || ICCRET_FALLBACK == e_iccret || ICCRET_EASYFLOW == e_iccret)
                {
					if (CTLSTYPE_MSD == gstTransData.eCtlsType) 	//paypass MSD check whether need online PIN 
					{
						memset(tmp, 0, sizeof(tmp));
					
						if (gstAppSysCfg.stSysParam.bIsIntRf)
						{
							if( sdkIccReadTLV("\xDF\x81\x1E", tmp, &ret) > 0)
							{
								TraceHex("misc", "MSD: mag stripe CVM", tmp, ret);
					
								if (0x20 == (tmp[0] & 0x20))	 //online PIN
								{
									return SDK_OK;
								}
							}
						}
						else			//G101 won't returen DF811E
						{
							if (0x20 == (gucMsdCVM & 0x20)) 		//online PIN
							{
								return SDK_OK;
							}
						}
					}		 
                    return SDK_EQU;
                }
                else if (ICCRET_EASYFLOW != e_iccret)
                {
                    return SDK_ESC;
                }
			}
        }

        if (iCardMode & SDK_ICC_MANUAL)
        {
            if(key >= SDK_KEY_0 && key <= SDK_KEY_9)
            {
                sdkSysBeep(SDK_SYS_BEEP_OK);
                ret = TrnProcManual(iCardMode, key, pstIccTradeParam, pstCardInfo);
                if(SDK_ESC == ret)
                {
                    return SDK_ESC;
                }
                else if(SDK_OK == ret)
                {
                    if(!DispCardNo(pstCardInfo->stCardData.asCardNO))
                    {
                        return SDK_ESC;
                    }
                    if(!TrnInputExpiredDate(pstCardInfo->stCardData.asExpiredDate))
                    {
                        return SDK_ESC;
                    }
                    pstCardInfo->stCardParam.ucCardMode = SDK_ICC_MANUAL;
                    return SDK_OK;
                }
            }
        }

    }
    Trace("misc", "TrnReadCard->cardmode = %d\r\n", pstCardInfo->stCardParam.ucCardMode);

    if (iCardMode & SDK_ICC_RF)
    {
        sdkIccPowerDown(); //Power OFF Contactless IC Card Reader
    }
    sdkSysBeep(SDK_SYS_BEEP_ERR);
    return SDK_ESC;
}

/*****************************************************************************
** Description :  Get a string
** Parameters  :  input:
                  (1)s32 iTimeOut : timeout(ms)
                  (2)s32 iMinLen : String min length
                  (3)s32 iMaxLen :String max length
                  (4)s32 iMode : Input mode
                  (5)s32 iLine : Display row

                  output:
                  (1)u8 *pasStr : Output string

** Return      :  (1)Key value
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnInputLine(s32 iTimeOut, u8 *pasStr, s32 iMinLen, s32 iMaxLen, s32 iMode, s32 iLine)
{
    return sdkKbGetScanf(iTimeOut, pasStr, iMinLen, iMaxLen, iMode, iLine);
}

/*****************************************************************************
** Description :  Get an IP address
** Parameters  :  input:
                  (1)s32 iTimeOut  : Timeout(ms)
                  (2)s32 iLine : Display row

                  output:                            
                  (1)u8 *pasIpAddr : Input IP address
                            
** Return      :  (1)Key Value
                  (2)SDK_TIME_OUT: time out
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnInputIpAddr(s32 iTimeOut, u8 *pasIpAddr, s32 iLine)
{
    s32 key, timid;
    s32 digitno = 0, dotno = 0;
    s32 i;


    sdkDispClearRowRam(iLine);

    if (!pasIpAddr[0])
    {
        sdkDispFillRowRam(iLine, 0, "_", SDK_DISP_RIGHT_DEFAULT);
    }
    else
    {
        sdkDispFillRowRam(iLine, 0, &pasIpAddr[1], SDK_DISP_RIGHT_DEFAULT);
    }
    sdkDispBrushScreen();

    // Intialize the number of digits following the last dot and the number of dots
    for (i = pasIpAddr[0]; i >= 1; i--)
    {
        if (0 == dotno && '.' != pasIpAddr[i])
        {
            digitno++;
        }

        if ('.' == pasIpAddr[i])
        {
            dotno++;
        }
    }

    // Start timer for input timeout
    timid = sdkTimerGetId();

    // If timeout, quit the loop
    while (!sdkTimerIsEnd(timid, iTimeOut))
    {
        // Check for valid key
        if ((key = sdkKbGetKey()) > 0)
        {
            // Restart timer
            timid = sdkTimerGetId();

            // Non-numeric key was pressed
            if (key < SDK_KEY_0 || key > SDK_KEY_9)
            {
                switch (key)
                {
                     // Finish inputting
                     case SDK_KEY_ENTER:
                        {
                            // Continue inputting if string length is less than minimum length
                            if (!sdkCommIsRightIP(&pasIpAddr[1]))
                            {
                                sdkSysBeep(SDK_SYS_BEEP_ERR);
                                continue;
                            }
                        }

                     case SDK_KEY_ESC:
                        {
                            sdkSysBeep(SDK_SYS_BEEP_OK);
                            return key;

                            // Delete the last character inputted if available
                        }

                     case SDK_KEY_BACKSPACE:
                     case SDK_KEY_CLEAR:
                        {
                            if (pasIpAddr[0] > 0)
                            {
                                // Decrement the count of dots if the character to be deleted is a dot
                                if ('.' == pasIpAddr[pasIpAddr[0]] && dotno > 0)
                                {
                                    dotno--;

                                    // Count the number of digits following the last dot again
                                    for (i = pasIpAddr[0] - 1; i >= 1 && '.' != pasIpAddr[i]; i--)
                                    {
                                        digitno++;
                                    }
                                }
                                else
                                {
                                    digitno--;
                                }
                                pasIpAddr[pasIpAddr[0]] = '\0';
                                pasIpAddr[0]--;
                            }
                            else
                            {
                                sdkSysBeep(SDK_SYS_BEEP_ERR);
                                continue;
                            }
                        }
                        break;

                     // A dot is inputted if FUNCTION key is pressed
                     case SDK_KEY_FUNCTION:
                        {
                            if (dotno >= 3 || 0 == digitno)
                            {
                                sdkSysBeep(SDK_SYS_BEEP_ERR);
                                continue;
                            }
                            pasIpAddr[0]++;
                            pasIpAddr[pasIpAddr[0]] = '.';
                            dotno++;
                            digitno = 0;
                        }
                        break;

                     default:
                       sdkSysBeep(SDK_SYS_BEEP_ERR);
                       continue;
                }
            }
            else   // Numeric key was pressed
            {
                // No more input is allowed
                if (digitno >= 3)
                {
                    sdkSysBeep(SDK_SYS_BEEP_ERR);
                    continue;
                }
                sdkSysBeep(SDK_SYS_BEEP_OK);

                // Add a key to buffer
                pasIpAddr[0]++;
                pasIpAddr[pasIpAddr[0]] = key;
                digitno++;
            }
            // Display characters inputted
            sdkDispClearRowRam(iLine);

            if (!pasIpAddr[0])
            {
                sdkDispFillRowRam(iLine, 0, "_", SDK_DISP_RIGHT_DEFAULT);
            }
            else
            {
                sdkDispFillRowRam(iLine, 0, &pasIpAddr[1], SDK_DISP_RIGHT_DEFAULT);
            }
            sdkDispBrushScreen();
        }
    }

    return SDK_TIME_OUT;
}
/*****************************************************************************
** Description :  Get magnetic track data from EMV tag
** Parameters  :  output:
                  (1)SDK_ICC_CARDDATA *pstCardData : Card data structure
                            
** Return      :  (1)SDK_OK: Succeeded

** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnGetIccMagData(SDK_ICC_CARDDATA *pstCardData)
{
    u16 i = 0, j = 0;
    u32 len = 0;
    u8 tmp[256] = {0};


//    Trace("offline", "-----1TrnGetIccMagData[%s]\r\n", pstCardData->asCardNO);
//    Trace("offline", "-----1TrnGetIccMagData[%s]\r\n", pstCardData->asTrack2Data);
//    Trace("offline", "-----1TrnGetIccMagData[%s]\r\n", pstCardData->asTrack3Data);
    sdkIccGetCardData(pstCardData);

    memset(pstCardData->asTrack3Data, 0, sizeof(pstCardData->asTrack3Data));
    pstCardData->ucTrack3Len = 0;
//    Trace("offline", "-----2TrnGetIccMagData[%s]\r\n", pstCardData->asCardNO);
//    Trace("offline", "-----2TrnGetIccMagData[%s]\r\n", pstCardData->asTrack2Data);
//    Trace("offline", "-----2TrnGetIccMagData[%s]\r\n", pstCardData->asTrack3Data);
    
    len = 256;
    memset(tmp,0,sizeof(tmp));
    if (sdkIccReadTLV("\x95", tmp, &len) > 0) 
    {
        TraceHex("misc", "tag 95 ", tmp, len);
    }

    if (sdkIccReadTLV("\x5F\x24", tmp, &len) > 0)     // Read expiration date: YYMMDD
    {
        TraceHex("misc", "tag 5f24 ", tmp, len);

        if (len > 0)
        {
            sdkBcdToAsc(pstCardData->asExpiredDate, &tmp[0], 2);
        }
    }
    memset(tmp, 0, sizeof(tmp));
    len = 256;

    if (sdkIccReadTLV("\x5A", tmp, &len) > 0)         //  Read PAN
    {
        TraceHex("misc", "tag 5A ", tmp, len);

        if (len)
        {
            pstCardData->ucCardLen = len * 2;
            sdkBcdToAsc(pstCardData->asCardNO, tmp, len);


            if (0x0f == (tmp[len - 1] & 0x0f))
            {
                pstCardData->ucCardLen--;
                pstCardData->asCardNO[pstCardData->ucCardLen] = '\0';
            }
            Trace("misc", "pstCardData->asCardNO = %s\r\n", pstCardData->asCardNO);
        }
        else
        {
            Trace("misc", "tag 5A error!\r\n");
            Assert(0);
        }
    }
    else
    {
        Trace("misc", "get tag 5A error\r\n");
    }
    memset(tmp, 0, sizeof(tmp));
    len = 256;

    if (sdkIccReadTLV("\x57", tmp, &len) > 0)    // Read IC2 info
    {
        TraceHex("misc", "tag 57 ", tmp, len);

        if (len > 0)
        {
            for (i = len - 1; i > 1; i--)
            {
                if (0xff != tmp[i])
                {
                    break;
                }
            }

            j = i + 1;

            if (0x0f == (tmp[j - 1] & 0x0f))
            {
                i = (j * 2 - 1);
            }
            else
            {
                i = (j * 2);
            }

            if (i > 37)
            {
                i = 37;
            }
            pstCardData->ucTrack2Len = i;
            sdkBcdToAsc(pstCardData->asTrack2Data, tmp, len);
            pstCardData->bIsIccMagCard  = TRUE;
            Trace("misc", "tag 57  len = [%d]  data = [%s]\r\n", pstCardData->ucTrack2Len, pstCardData->asTrack2Data);
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Extract account number from track data
** Parameters  :  input:
                  (1)SDK_ICC_CARDDATA const *pstCardData : Card data structure

                  output:
                  (1)u8 *pasCardNo : Account number
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)SDK_PARA_ERR: Parameters error
                  (3)SDK_ERR: Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnGetMagCardNo(SDK_ICC_CARDDATA const *pstCardData, u8 *pasCardNo)
{
    u8 tmp[256] = {0};
    s32 ret = SDK_OK;
    u16 i = 0;
    u8 len = 0;
    u8 track2len = 0;
    u8 track3len = 0;
    bool track2flag = FALSE;

    if(NULL == pstCardData && NULL == pasCardNo)
    {
        return SDK_PARA_ERR;
    }

    memset(tmp, 0, sizeof(tmp));
    track2len = pstCardData->ucTrack2Len;

    if (track2len)
    {
        if (track2len > 37)
        {
            track2len = 37;
        }
        memcpy(tmp, pstCardData->asTrack2Data, track2len);
        track2flag = TRUE;
    }
    else
    {
        track3len = pstCardData->ucTrack3Len;

        if (track3len)
        {
            if (track3len > 104)
            {
                track3len = 104;
            }
            memcpy(tmp, pstCardData->asTrack3Data, track3len);
        }
    }

    if (track2len || track3len)
    {
        len = strlen(tmp);

        for (i = 0; i < len; i++)
        {
            if ('D' == tmp[i])
            {
                if ('2' == tmp[i + 5] || '6' == tmp[i + 5])
                {
                    ret = SDK_OK;
                }
                break;
            }
        }

        len = i;

        if (len > 19)
        {
            len = 19;
        }
        tmp[len++] = 0;
    }
    else
    {
        memset(tmp, 0, sizeof(tmp));
        len = pstCardData->ucCardLen;

        if (len > 19)
        {
            len = 19;
        }

        if (len < 13)
        {
            ret = SDK_ERR;
        }
        memcpy(tmp, pstCardData->asCardNO, len);
        tmp[len++] = 0;
        track2flag = TRUE;
    }

    if (0 == strlen(tmp))
    {
        return SDK_ERR;
    }
    memcpy(pasCardNo, tmp, len);

    if (track2flag && strlen(tmp) >= 13)
    {
        return ret;
    }
    else
    {
        return SDK_ERR;
    }
}

/*****************************************************************************
** Description :  Padding characters in a fixed length string.
** Parameters  :  input:
                  (1)u8 *pasSrc : Original string
                  (2)u8 ucChar : filler character
                  (3)s32 iLen : Destination string length
                  (4)enum ALIGN_MODE eAlign : Align mode

                  output:
                  (1)u8 *pasDest : Destination string
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnPadding(u8 *pasDest, u8 *pasSrc, u8 ucChar, s32 iLen, E_ALIGN_MODE eAlign)
{
    memset(pasDest, ucChar, iLen);

    if (RIGHT_ALIGN == eAlign)
    {
        memcpy(&pasDest[iLen - strlen(pasSrc)], pasSrc, strlen(pasSrc));
    }
    else
    {
        memcpy(pasDest, pasSrc, strlen(pasSrc));
    }
    pasDest[iLen] = '\0';
}

/*****************************************************************************
** Description :  Combine two strings together, pading with the blank spaces
** Parameters  :  input:
                  (1)enum ALIGN_MODE eAlign  : Align mode
                  (2)const u8 *pasSrc  : The source string
                  (3)u32 uiMaxLen : Max len of destination string

                  output:
                  (1)u8 *pasDest : Destination string
                            
** Return      :  (1)SDK_PARA_ERR: Parameters error
                  (2)SDK_OK: Succeeded
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnFormBlankAlignChar(E_ALIGN_MODE eAlign, u8 *pasDest, const u8 *pasSrc, u32 uiMaxLen)
{
    s32 len, cplen, off;

    if (NULL == pasDest || NULL == pasSrc || uiMaxLen <= strlen(pasDest))
    {
        return SDK_PARA_ERR;
    }

    len = uiMaxLen - strlen(pasDest);
    off = strlen(pasDest);

    memset(&pasDest[off], ' ', len);
    cplen = len > strlen(pasSrc) ? strlen(pasSrc) : len;

    if (RIGHT_ALIGN == eAlign)
    {
        off += len - cplen;
    }

    memcpy(&pasDest[off], pasSrc, cplen);

    return SDK_OK;
}

/*****************************************************************************
** Description :  Input and Check the admin password
** Parameters  :  None 
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckAdminPwd(void)
{
    u8 pwd[64];
    s32 ret;

    if(gstAppSysCfg.stTransParam.bIsCheckAdminPwd)
    {
        while(1)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_ADMIN_PWD, SDK_DISP_LEFT_DEFAULT);
            sdkDispBrushScreen();
        
            memset(pwd, 0, sizeof(pwd));
            ret = TrnInputLine(TMR_OPERATE, pwd, 6, 6, SDK_MMI_NUMBER | SDK_MMI_PWD, SDK_DISP_LINE3);
            if (SDK_KEY_ENTER != ret)
            {
                TrnSetStatus(ret);
                return FALSE;
            }
            if(0 == memcmp(&pwd[1], gstAppSysCfg.stUserPwd.asAdminPwd, ADMIN_PWDLEN))
            {
                break;
            }
            else
            {
                DispClearContent();
                sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PWD_ERROR, SDK_DISP_DEFAULT);
                sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
                sdkDispBrushScreen();
                ret = sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_OPERATE);
                if(SDK_KEY_ENTER != ret)
                {
                    TrnSetStatus(ret);
                    return FALSE;
                }
                continue;
            }
        }
    }

    return TRUE;
}

/*****************************************************************************
** Description :  Input and get trace number
** Parameters  :  output:
                  (1)u8 *pasTracerNo : Output string

** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnInputTraceNo(u8 *pasTracerNo)
{
    u8 tmp[7+1];
    s32 ret;

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_ORIG_TRACENO, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    memset(tmp, 0, sizeof(tmp));
    ret = TrnInputLine(TMR_OPERATE, tmp, 1, 6, SDK_MMI_NUMBER, SDK_DISP_LINE3);
    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return FALSE;
    }

    if(tmp[0] < 6)
    {
        TrnPadding(pasTracerNo, &tmp[1], '0', 6, RIGHT_ALIGN);
    }
    else
    {
        strncpy(pasTracerNo, &tmp[1], 6);
    }

    return TRUE;
}

/*****************************************************************************
** Description :  Input and get reference number
** Parameters  :  ouput:
                  (1)u8 *pasRefNo : Output string

** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnInputReferenceNo(u8 *pasRefNo)
{
    u8 tmp[13+1] = {0};
    s32 ret;
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_ORIG_REFNO, SDK_DISP_LEFT_DEFAULT);
    sdkDispBrushScreen();

    ret = TrnInputLine(TMR_OPERATE, tmp, 12, 12, SDK_MMI_NUMBER | SDK_MMI_LETTER, SDK_DISP_LINE3);
    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return FALSE;
    }
    
    strncpy(pasRefNo, &tmp[1], 12);
    
    return TRUE;
}





bool TrnInputVoiceCommonNo(u8 *pasInputdNo,E_VOICE_INPUT_TYPE eInputType)
{
   	u8 tmp[21+1];
    s32 ret;

    DispClearContent();
	if(VOICE_INPUT_INVOICE_NO == eInputType)
	{
		 sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_INVOICE__NO, SDK_DISP_LEFT_DEFAULT);
	}
    else
    {
		sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_PAYMEN_METHOD_NO, SDK_DISP_LEFT_DEFAULT);
    }
	
    sdkDispBrushScreen();
    memset(tmp, 0, sizeof(tmp));
    ret = TrnInputLine(TMR_OPERATE, tmp, 5, 20, SDK_MMI_NUMBER, SDK_DISP_LINE3);
    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return FALSE;
    }

    if(tmp[0] < 20)
    {
        TrnPadding(pasInputdNo, &tmp[1], ' ', 20, LEFT_ALIGN);
    }
    else
    {
        strncpy(pasInputdNo, &tmp[1], 20);
    }
    TraceHex("xgd","paymethodNo,var tmp=",tmp,21);
	TraceHex("xgd","paymethodNo,=",pasInputdNo,20);
	
    return TRUE;
}


/*****************************************************************************
** Description :  Check date format (MMDD)
** Parameters  :  output
                  (1)u8 *pasDate : Date(MMDD)

** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckDate(u8 *pasDate)
{
    u8 day_buf[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    u8 month = 0, day = 0;
    u8 tmp[3] = {0};

    strncpy(tmp, pasDate, 2);
    month = atoi(tmp);
    strncpy(tmp, &pasDate[2], 2);
    day = atoi(tmp);

    if(month <= 0 || month > 12 || day <= 0 || day > day_buf[month - 1])
    {
        return FALSE;
    }

    return TRUE;
}

/*****************************************************************************
** Description :  check year and month format (YYMM)
** Parameters  :  output:
                  (1)u8 *pasYearMonth : YYMM
                            
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckYearMonth(u8 *pasYearMonth)
{
    u8 month = 0;
    u8 tmp[3] = {0};

    strncpy(tmp, &pasYearMonth[2], 2);
    month = atoi(tmp);

    if(month <= 0 || month > 12)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_FORMAT_ERR, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_DIGITAL | SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
        return FALSE;
    }

    return TRUE;
}

/*****************************************************************************
** Description :  check time format(yymmddhhmmss)
** Parameters  :  output:
                  (1)u8 *pbcTime : time buffer(BCD code)
                  (2)u8 ucLen : time buffer length
                            
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckTime(u8 *pbcTime, u8 ucLen)
{
    u8 days;
    u16 i;
    bool leepyear;

    sdkBcdToU16(&i, pbcTime, 1);                                 

    if(i < 50)
    {
        i += 2000;
    }
    else
    {
        i += 1900;
    }

    if(((0 == i % 4) && (0 != i % 100)) || (0 == i % 400))
    {
        leepyear = TRUE;
    }
    else
    {
        leepyear = FALSE;
    }

    if(ucLen <= 1)
    {
        return TRUE;
    }
    sdkBcdToU16(&i, pbcTime + 1, 1);

    if(i > 12 || 0 == i)
    {
        return FALSE;
    }

    if(ucLen <= 2)
    {
        return TRUE;
    }

    if((1 == i) || (3 == i) || (5 == i) || (7 == i) || (8 == i) || (10 == i) || (12 == i))
    {
        days = 31;
    }
    else if(2 != i)
    {
        days = 30;
    }
    else if(leepyear)
    {
        days = 29;
    }
    else
    {
        days = 28;
    }
    sdkBcdToU16(&i, pbcTime + 2, 1);

    if(i > days || 0 == i)
    {
        return FALSE;
    }

    if(ucLen <= 3)
    {
        return TRUE;
    }
    sdkBcdToU16(&i, pbcTime + 3, 1);

    if(i > 23)
    {
        return FALSE;
    }

    if(ucLen <= 4)
    {
        return TRUE;
    }
    sdkBcdToU16(&i, pbcTime + 4, 1);

    if(i > 59)
    {
        return FALSE;
    }

    if(ucLen <= 5)
    {
        return TRUE;
    }
    sdkBcdToU16(&i, pbcTime + 5, 1);

    if(i > 59)
    {
        return FALSE;
    }
    return TRUE;
}

/*****************************************************************************
** Description :  Input and get an amount
** Parameters  :  input:
                  (1)E_AMOUNT_MODE eAmountMode : amount mode
                  output:
                  (1) u8 *pasAmount : amount
                            
** Return      :  (1)SDK_OK:Succeeded
                  (2)SDK_PARA_ERR: Parameters error
                  (3)SDK_ERR: Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnInputAmount(E_AMOUNT_MODE eAmountMode, u8 *pasAmount)
{
    s32 ret;
    u8 buf[16];

    if (NULL == pasAmount || (SALE_AMOUNT > eAmountMode || CASHBACK_AMOUNT < eAmountMode))
    {
        Assert(0);
        return SDK_PARA_ERR;
    }
    DispClearContent();

    if (CASHBACK_AMOUNT == eAmountMode)
    {
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_CASHBACK, SDK_DISP_LEFT_DEFAULT);
    }
    else
    {
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_AMOUNT, SDK_DISP_LEFT_DEFAULT);
    }
    sdkDispBrushScreen();
    
    memset(buf, 0, sizeof(buf));
    if(strlen(pasAmount))
    {
        strcpy(buf, pasAmount);
        //buf[0] = strlen(pasAmount);
    }

    if (CASHBACK_AMOUNT == eAmountMode)
    {
        ret = TrnGetAmount(TMR_OPERATE, buf, SDK_DISP_LINE4, TRUE);
    }
    else
    {
        ret = TrnGetAmount(TMR_OPERATE, buf, SDK_DISP_LINE3, FALSE);
    }

    if (SDK_KEY_ENTER != ret)
    {
        TrnSetStatus(ret);
        return SDK_ERR;
    }
    TrnPadding(pasAmount, buf, '0', 12, RIGHT_ALIGN);   // Pad leading '0's to amount string
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Input and get date (MMDD)
** Parameters  :  output:
                  (1)u8 *pasDate : date

** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnInputDate(u8 *pasDate)
{
    u8 tmp[5+1] = {0};
    s32 ret;

    while(1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_ORIG_DATE, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_MMDD, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(tmp, 0, sizeof(tmp));
        ret = TrnInputLine(TMR_OPERATE, tmp, 4, 4, SDK_MMI_NUMBER, SDK_DISP_LINE4);
        if (SDK_KEY_ENTER != ret)
        {
            TrnSetStatus(ret);
            return FALSE;
        }

        if(!TrnCheckDate(&tmp[1]))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_FORMAT_ERR, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            ret = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
            if(SDK_KEY_ENTER != ret)
            {
                TrnSetStatus(ret);
                return FALSE;
            }
        }
        else
        {
            break;
        }
    }
    
    strncpy(pasDate, &tmp[1], 4);
    
    return TRUE;
}

/*****************************************************************************
** Description :  Input and get a card expire date
** Parameters  :  output:
                  (1)u8 *pasDate  :  card expire date
                            
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnInputExpiredDate(u8 *pasDate)
{
    u8 tmp[5+1] = {0};
    s32 ret;

    while(1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_EXPIRYDATE, SDK_DISP_LEFT_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_YYMM, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        memset(tmp, 0, sizeof(tmp));
        ret = TrnInputLine(TMR_OPERATE, tmp, 4, 4, SDK_MMI_NUMBER, SDK_DISP_LINE4);
        if (SDK_KEY_ENTER != ret)
        {
            TrnSetStatus(ret);
            return FALSE;
        }
        
        if(!TrnCheckYearMonth(&tmp[1]))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_FORMAT_ERR, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ESC == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT))
            {
                TrnSetStatus(SDK_KEY_ESC);
                return FALSE;
            }
        }
        else
        {
            break;
        }
    }
    strncpy(pasDate, &tmp[1], 4);
    
    return TRUE;
}

/*****************************************************************************
** Description : Add a cashier
** Parameters  :  output:
                  (1)u32 *puiOperator: Cashier ID
                            
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnInputAddCashier(u32 *puiOperator)
{
    s32 ret;
    u8 buf[64] = {0};
    u32 cashier;

    while (1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_CASHIER_NO, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        // Input operator number
        memset(buf, 0, sizeof(buf));
        ret = sdkKbGetScanf(TMR_OPERATE, buf, 1, 2, SDK_MMI_NUMBER, SDK_DISP_LINE3);
        if (SDK_KEY_ENTER != ret)
        {
            return FALSE;
        }

        cashier = atoi(&buf[1]);

        if((cashier > (CASHIER_NUM - 1)) || cashier < 1)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INVALID_CASHIER_NO, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                continue;
            }
            else
            {
                return FALSE;
            }
        }
        else if(gstAppSysCfg.stUserPwd.stCashier[cashier].bIsExist)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_CASHIER_EXISTED, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                continue;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            break;
        }
    }

    *puiOperator = cashier;
    return TRUE;
}

/*****************************************************************************
** Description :  Delete a cashier
** Parameters  :  output:
                  (1)u32 *puiOperator: the deleted cashier ID

** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnInputDeleteCashier(u32 *puiOperator)
{
    s32 ret;
    u8 buf[64] = {0};
    u32 cashier;

    while (1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INPUT_CASHIER_NO, SDK_DISP_LEFT_DEFAULT);
        sdkDispBrushScreen();

        // Input operator number
        memset(buf, 0, sizeof(buf));
        ret = sdkKbGetScanf(TMR_OPERATE, buf, 1, 2, SDK_MMI_NUMBER, SDK_DISP_LINE3);
        if (SDK_KEY_ENTER != ret)
        {
            return FALSE;
        }

        cashier = atoi(&buf[1]);

        if((cashier > (CASHIER_NUM - 1)) || cashier < 1)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_INVALID_CASHIER_NO, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                continue;
            }
            else
            {
                return FALSE;
            }
        }
        else if(!gstAppSysCfg.stUserPwd.stCashier[cashier].bIsExist)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_CASHIER_NOT_EXISTED, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                continue;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            break;
        }
    }

    *puiOperator = cashier;
    return TRUE;
}
/*****************************************************************************
** Description :  mask partial card number
** Parameters  :  input:
                  (1)E_TRANS_ID eTransID : Transacrion ID

                  output:
                  (1)u8 *pasCardNo : Masked card number string
                  
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnMaskCardNo(E_TRANS_ID eTransID, u8 *pasCardNo)
{
    u8 len;

    if (gstAppSysCfg.stTransParam.bIsMaskPAN)
    {
        len = strlen(pasCardNo);

        if (len > 10 && len < 20)
        {
            memset(&pasCardNo[6], '*', len - 10);
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*****************************************************************************
** Description :  Check the refund maximum amount
** Parameters  :  input:
                  (1)u8 *pasAmount: Amount

** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckRefundAmount(u8 *pasAmount)
{
    u32 amount;
    u32 max_amount;

    amount = atoi(pasAmount);
    max_amount = atoi(gstAppSysCfg.stTransParam.asRefundMaxAmount);
    if(0 == gstAppSysCfg.stTermInfo.uiAmountDecimalLen)
    {
        max_amount /= 100;
    }
    else if(1 == gstAppSysCfg.stTermInfo.uiAmountDecimalLen)
    {
        max_amount /= 10;
    }
    else if(3 == gstAppSysCfg.stTermInfo.uiAmountDecimalLen)
    {
        max_amount *= 10;
    }

    if(amount > max_amount)
    {
        return FALSE;
    }
    return TRUE;
}

/*****************************************************************************
** Description :  Confirm the refund amount
** Parameters  :  input:
                  (1)u8 *pasAmount: Amount
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)SDK_ESC: Failed
                  (3)SDK_EQU: Need re-input
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnConfirmRefundAmount(u8 *pasAmount)
{
    u8 tmp[32] = {0};
    s32 key;
    s32 ret = SDK_ESC;

    if (NULL == pasAmount)
    {
        return SDK_ESC;
    }
    
    TrnFormatAmount(tmp, pasAmount, TRUE);

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PLS_CONFIRM, SDK_DISP_LEFT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, tmp, SDK_DISP_RIGHT_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE5, 0, STR_PRESS_CANCEL_REINPUT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    key = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);
    if (SDK_KEY_ENTER == key)
    {
        ret = SDK_OK;
    }
    else if (SDK_KEY_ESC == key)
    {
        ret = SDK_EQU;
    }
    else
    {
        ret = key;
    }
    
    return ret;
}

/*****************************************************************************
** Description :  Judge if it is a credit transaction
** Parameters  :  input:
                  (1)E_TRANS_ID eTransID: Transaction ID
                            
** Return      :  (1)TRUE: Succeeded
                  (2)FALSE:Failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnJudgeCreditTrans(E_TRANS_ID eTransID)
{
    if (TRANSID_VOID == eTransID || TRANSID_REFUND == eTransID)
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
** Description :  Synchronize date and time from the successful transaction
** Parameters  :  input:
                  (1)ST_TRANSDATA *pstTransData: Transaction data
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnSyncDateTime(ST_TRANSDATA *pstTransData)
{
    u8 buf[64] = {0};
    
    if(SDK_OK == sdkGetRtc(buf))
    {
        sdkAscToBcd(&buf[1], pstTransData->stTransLog.stMsgInfo.asTransDate, 4);
        sdkAscToBcd(&buf[3], pstTransData->stTransLog.stMsgInfo.asTransTime, 6);
        sdkSetRtc(buf);
    }
}

/*****************************************************************************
** Description :  Switch application
** Parameters  :  None 
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnSwitchApp(void)
{
    u8 tmp[256] = {0};
    
    sdkSysSwitchApp(NULL, "", 0, tmp);
}

/*****************************************************************************
** Description :  Turn off the pinpad voice
** Parameters  :  None 
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnPedCloseVoice(void)
{

    u8 card_type = SDK_ICC_RFCARD_A;
    u8 tmp[256] = {0};
    SDK_ICC_SYS_CODE st_syscode;

    if(gstAppSysCfg.stSysParam.bIsExtPED)
    {
        st_syscode.uiLen = 1;
        st_syscode.ucSysCode[0] |= 0x01;     //bit0£º0-backlight off 1-backlight on

        st_syscode.ucSysCode[0] &= (~(0x01 << 4));     //bit4£º0- do not play prompt tone 1-play prompt tone
        sdkIccRFQueryEx(card_type, tmp, 50, &st_syscode);

        sdkIccCloseRfDev ();

        sdkmSleep(3000);
    }
}

/*****************************************************************************
** Description :  set global error code
** Parameters  :  input:
                  (1)s32 iErrCode: Error code
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnSetStatus(s32 iStatus)
{
    gstTransData.iStatus = iStatus;
}

/*****************************************************************************
** Description :  get global error code
** Parameters  :  None
** Return      :  (1)The error code
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnGetStatus(void)
{
    return gstTransData.iStatus;
}

/*****************************************************************************
** Description :  Initialize the transaction global value
** Parameters  :  None 
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnInitGlobal(void)
{
    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    memset(&gstSendPacket, 0, sizeof(SDK_8583_ST8583));
    memset(&gstRecvPacket, 0, sizeof(SDK_8583_ST8583));
    gstTransData.stTransLog.eTransID = TRANSID_MAINMENU;
}

/*****************************************************************************
** Description :  General process when finishing a transaction
** Parameters  :  None 
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnEndProcess(void)
{
    ST_CARDINFO *pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    u32 tmr;

    if(TRANSID_MAINMENU != gstTransData.stTransLog.eTransID 
        && TRANSID_UNKNOWN != gstTransData.stTransLog.eTransID
        && TRANSID_WELCOME != gstTransData.stTransLog.eTransID)
    {
        if(0 == TrnGetStatus())
        {
            sdkSysBeep(SDK_SYS_BEEP_OK);
            
            if(TRANSID_BALANCE != gstTransData.stTransLog.eTransID)
            {
                DispSuccResponse();
            }
        }
        else
        {
            sdkSysBeep(SDK_SYS_BEEP_ERR);
            DispTransStatus();
        }
    }

    if (SDK_ICC_ICC == pst_cardinfo->stCardParam.ucCardMode)
    {
        tmr = sdkTimerGetId();
        while(SDK_OK == sdkIccGetCardStatus(&pst_cardinfo->stCardParam, 500))
        {
            if(sdkTimerIsEnd(tmr, 2 * 1000))
            {
                tmr = sdkTimerGetId();
                sdkSysBeep(SDK_SYS_BEEP_ERR);
            }
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_TAKE_CARD, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
        }
    }
    else if(SDK_ICC_RF == pst_cardinfo->stCardParam.ucCardMode)
    {
        sdkIccPowerDown();
    }

    sdkPEDCancel();
    TrnInitGlobal();

    sdkCommDestoryLink();
}

/*****************************************************************************
** Description :  Check whether the response code is success
** Parameters  :  input:
                  (1)const u8 *asResp : response code
                            
** Return      :  (1)TRUE : transaction success
                  (2)FALSE : transaction fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool TrnCheckResponseCode(const u8 *asResp)
{
    if (memcmp(asResp, "00", 2) == 0
        || memcmp(asResp, "11", 2) == 0
        || memcmp(asResp, "A2", 2) == 0
        || memcmp(asResp, "A4", 2) == 0
        || memcmp(asResp, "A5", 2) == 0
        || memcmp(asResp, "A6", 2) == 0
        )
    {
        return true;
    }
    return false;
}

/*****************************************************************************
** Description :  Get icc data from ISO8583 message (field 55)
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstPacket8583 : 8583 data
                            
** Return      :  Void
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void TrnGetIccDataFromMsg(SDK_8583_ST8583 *pstPacket8583)
{
    int i;
    u32 len = 0;
    s32 ret;
    u8 buf[255];
    u8 data[512];           // #55 receive icc data
    s32 data_len;           // receive icc data length
    ST_EMVINFO *pst_emvinfo = &gstTransData.stTransLog.stEmvInfo;
    ST_TRANSLOG_TLV tab_tlv[] = 
    {
        {"\x9F\x26", sizeof(pst_emvinfo->heAC),            pst_emvinfo->heAC,            NULL},
        {"\x9F\x27", sizeof(pst_emvinfo->ucCID),           &pst_emvinfo->ucCID,          NULL},
        {"\x9F\x10", sizeof(pst_emvinfo->heIAD),           pst_emvinfo->heIAD,           &pst_emvinfo->ucIADLen},
        {"\x9F\x37", sizeof(pst_emvinfo->heUN),            pst_emvinfo->heUN,            NULL},
        {"\x9F\x36", sizeof(pst_emvinfo->heATC),           pst_emvinfo->heATC,           NULL},
        {"\x95",     sizeof(pst_emvinfo->heTVR),           pst_emvinfo->heTVR,           NULL},
        {"\x9A",     sizeof(pst_emvinfo->heTransDate),     pst_emvinfo->heTransDate,     NULL},
        {"\x9C",     sizeof(pst_emvinfo->ucTransType),     &pst_emvinfo->ucTransType,    NULL},
        {"\x9F\x02", sizeof(pst_emvinfo->bcTransAmount),   pst_emvinfo->bcTransAmount,   NULL},
        {"\x5F\x2A", sizeof(pst_emvinfo->bcCurrencyCode),  pst_emvinfo->bcCurrencyCode,  NULL},
        {"\x9F\x1A", sizeof(pst_emvinfo->bcCountryCode),   pst_emvinfo->bcCountryCode,   NULL},
        {"\x82",     sizeof(pst_emvinfo->heAIP),           pst_emvinfo->heAIP,           NULL},
        {"\x9F\x33", sizeof(pst_emvinfo->heTermCap),       pst_emvinfo->heTermCap,       NULL},
        {"\x9F\x34", sizeof(pst_emvinfo->heCVMR),          pst_emvinfo->heCVMR,          NULL},
        {"\x9F\x03", sizeof(pst_emvinfo->bcAmountOther),   pst_emvinfo->bcAmountOther,   NULL},
        {"\x84",     sizeof(pst_emvinfo->heAID),           pst_emvinfo->heAID,           &pst_emvinfo->ucAIDLen},
        {"\x9F\x08", sizeof(pst_emvinfo->heAppVerNum),     pst_emvinfo->heAppVerNum,     NULL},
        {"\x9F\x09", sizeof(pst_emvinfo->heTermAppVerNum), pst_emvinfo->heTermAppVerNum, NULL},
        {"\x9F\x35", sizeof(pst_emvinfo->ucTermType),      &pst_emvinfo->ucTermType,     NULL},
        {"\x9F\x1E", sizeof(pst_emvinfo->asIFDSN),         pst_emvinfo->asIFDSN,         NULL},
        {"\x9F\x53", sizeof(pst_emvinfo->ucCategoryCode),  &pst_emvinfo->ucCategoryCode, NULL},
        {"\x9F\x41", sizeof(pst_emvinfo->heTransSeqCnt),   pst_emvinfo->heTransSeqCnt,   NULL},
        {"\x9F\x6E", sizeof(pst_emvinfo->heFFI),           pst_emvinfo->heFFI,           &pst_emvinfo->ucFFILen},
        {"\x9F\x4C", sizeof(pst_emvinfo->heIDN),           pst_emvinfo->heIDN,           NULL},
        {"\x9F\x5D", sizeof(pst_emvinfo->bcAOSA),          pst_emvinfo->bcAOSA,          NULL},
        {"\x9B",     sizeof(pst_emvinfo->heTSI),           pst_emvinfo->heTSI,           NULL},
        {"\x5F\x34", sizeof(pst_emvinfo->ucPANSN),         &pst_emvinfo->ucPANSN,        NULL},
        {"\x50",     sizeof(pst_emvinfo->asAppLabel),      pst_emvinfo->asAppLabel,      NULL},
        {"\x9F\x12", sizeof(pst_emvinfo->asAppPreferName), pst_emvinfo->asAppPreferName, NULL},
        {"\x91",     sizeof(pst_emvinfo->heIssAuthData),   pst_emvinfo->heIssAuthData,   &pst_emvinfo->ucIssAuthDataLen},
        {"\xDF\x31", sizeof(pst_emvinfo->heScriptResult),  pst_emvinfo->heScriptResult,  &pst_emvinfo->ucScriptResultLen}, 
    };

    if(NULL == pstPacket8583)
    {
        return;
    }
    
    data_len = IsoGetField(pstPacket8583, 55, data, sizeof(data));
    if(data_len <= 0)
    {
        return;
    }

    for(i = 0; i < sizeof(tab_tlv) / sizeof(ST_TRANSLOG_TLV); i++)
    {
        memset(buf, 0, sizeof(buf));
        ret = EmvParseIccTlv(data, data_len, tab_tlv[i].heTag, buf, &len);
        if (SDK_OK == ret && len > 0 && len <= tab_tlv[i].ucDatalen)
        {
            memcpy(tab_tlv[i].pAddress, buf, len);
            if(tab_tlv[i].pLength)
            {
                *tab_tlv[i].pLength = (u8)len;
            }
            continue;
        }
        
        memset(buf, 0, sizeof(buf));
        ret = sdkIccReadTLV(tab_tlv[i].heTag, buf, &len);
        if (SDK_OK == ret && len > 0 && len <= tab_tlv[i].ucDatalen)
        {
            memcpy(tab_tlv[i].pAddress, buf, len);
            if(tab_tlv[i].pLength)
            {
                *tab_tlv[i].pLength = (u8)len;
            }
        }
    }
}

/*****************************************************************************
** Description : Get data of transaction from received ISO8583 message,
                  and save it to structure "gstTransData"
                  
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstRecvPacket : 8583 received message
                            
** Return      :  (1)SDK_OK: Succeeded
                  (2)ERR_CALCMAC: Calculating MAC failed
                  (3)ERR_UNPACK_MSG: Unpacking failed
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnUpdateTransDataRecv(SDK_8583_ST8583 *pstRecvPacket)
{
    s32 len = 0;
    u8 buf[1024] = {0};
    u8 mac[8] = {0};
    s32 ret = 0;
    u32 amount = 0, tip_amount=0, amt=0, recamt=0;
    ST_TRANSLOG *pst_translog = NULL;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_CARDINFO *pst_cardinfo = NULL;

    pst_translog = &gstTransData.stTransLog;
    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    
    if(8 == IsoGetField(pstRecvPacket, 64, buf, sizeof(buf)))
    {
        IsoGetMsgMac(pstRecvPacket, mac);
        if(0 != memcmp(buf, mac, 8))
        {
            TrnSetStatus(ERR_CALCMAC);
            return ERR_CALCMAC;
        }
    }
    
    if(IsoGetField(pstRecvPacket, 0, buf, sizeof(buf)) <= 0)
    {
        TrnSetStatus(ERR_UNPACK_MSG);
        return ERR_UNPACK_MSG;
    }

    gstTransData.asMTI[2] += 1;
    if(0 != memcmp(buf, gstTransData.asMTI, 4))
    {
        TrnSetStatus(ERR_MSGTYPE);
        return ERR_UNPACK_MSG;
    }
    
    // #39
    if(IsoGetField(pstRecvPacket, 39, pst_msginfo->asRespCode, sizeof(pst_msginfo->asRespCode)) <= 0 
        && TRANSID_SETTLE != pst_translog->eTransID)
    {
        TrnSetStatus(ERR_UNPACK_MSG);
        return ERR_UNPACK_MSG;
    }
    
    // #2
    memset(buf, 0, sizeof(buf));
    if(IsoGetField(pstRecvPacket, 2, buf, sizeof(buf)) > 0)
    {
        memset(pst_translog->stCardInfo.stCardData.asCardNO, 0, sizeof(pst_translog->stCardInfo.stCardData.asCardNO));
        strcpy(pst_translog->stCardInfo.stCardData.asCardNO, buf);
        pst_translog->stCardInfo.stCardData.ucCardLen = strlen(buf);
    }
    
    // #3
    memset(buf, 0, sizeof(buf));
    if(IsoGetField(pstRecvPacket, 3, buf, sizeof(buf)))
    {
        if(strcmp(buf, pst_msginfo->asProcCode))
        {
            TrnSetStatus(ERR_PROCESSCODE);
            return ERR_UNPACK_MSG;
        }
    }
        
    // #4
    memset(buf, 0, sizeof(buf));
    if(IsoGetField(pstRecvPacket, 4, buf, sizeof(buf)) > 0)
    {
        amount = atoi(pst_msginfo->asAmount);
        tip_amount = atoi(pst_msginfo->asTipAmount);
        recamt = atoi(buf);
         
        if(TRANSID_ADJUST == pst_translog->eTransID || TRANSID_BATCHUP_TIP == pst_translog->eTransID)
        {
            amt = amount + tip_amount;
        }
        else
        {
            amt = amount;
        }
        
        if(recamt != amt)
        {
            TrnSetStatus(ERR_TRANSAMOUNT);
            return ERR_UNPACK_MSG;
        }
        
        if(TRANSID_ADJUST == pst_translog->eTransID)
        {
            if(atoi(buf) > 0)
            {
                memcpy(pst_msginfo->asAmount, buf, 12);
            }

        }
    }

    // #11
    memset(buf, 0, sizeof(buf));
    IsoGetField(pstRecvPacket, 11, buf, sizeof(buf));
    if(0 != memcmp(buf, pst_msginfo->asTraceNO, 6))
    {
        TrnSetStatus(ERR_TRACENO);
        return ERR_UNPACK_MSG;
    }
    
    // #12
    IsoGetField(pstRecvPacket, 12, pst_msginfo->asTransTime, sizeof(pst_msginfo->asTransTime));

    // #13
    IsoGetField(pstRecvPacket, 13, pst_msginfo->asTransDate, sizeof(pst_msginfo->asTransDate));
    
    // #14
    IsoGetField(pstRecvPacket, 14, pst_cardinfo->stCardData.asExpiredDate, sizeof(pst_cardinfo->stCardData.asExpiredDate));
        
    // #15
    IsoGetField(pstRecvPacket, 15, pst_msginfo->asSettlementDate, sizeof(pst_msginfo->asSettlementDate));    
   
    // #32
    if(8 != IsoGetField(pstRecvPacket, 32, pst_msginfo->asAIID, sizeof(pst_msginfo->asAIID)))
    {
        TrnSetStatus(ERR_UNPACK_MSG);
        return ERR_UNPACK_MSG;
    }
    
    // #37
    IsoGetField(pstRecvPacket, 37, pst_msginfo->asRefNO, sizeof(pst_msginfo->asRefNO));        
    
    // #38
    IsoGetField(pstRecvPacket, 38, pst_msginfo->asAuthCode, sizeof(pst_msginfo->asAuthCode));        
        
    // #41
    memset(buf, 0, sizeof(buf));
    IsoGetField(pstRecvPacket, 41, buf, sizeof(buf));        
    if(0 != memcmp(buf, gstAppSysCfg.stTermInfo.asTermID, 8))
    {
        TrnSetStatus(ERR_TERMINALNO);
        return ERR_UNPACK_MSG;
    }
    
    // #42
    memset(buf, 0, sizeof(buf));
    IsoGetField(pstRecvPacket, 42, buf, sizeof(buf));        
    if(0 != memcmp(buf, gstAppSysCfg.stTermInfo.asMerchID, 15))
    {
        TrnSetStatus(ERR_MERCHANTNO);
        return ERR_UNPACK_MSG;
    }
    
    // #44
    memset(buf, 0, sizeof(buf));
    ret = IsoGetField(pstRecvPacket, 44, buf, sizeof(buf));        
    if(ret > 0)
    {
        memcpy(pst_msginfo->asIssuerCode, buf, 11);
        if(ret > 11)
        {
            memcpy(pst_msginfo->asAcquirerCode, &buf[11], 11);
        }
    }
    
    // #48
    IsoGetField(pstRecvPacket, 48, gstTransData.asAdditionInfo, sizeof(gstTransData.asAdditionInfo));        
    
    // #52
    IsoGetField(pstRecvPacket, 52, gstTransData.hePIN, sizeof(gstTransData.hePIN));        

    // #53
    //IsoGetField(pstRecvPacket, 53, gstTransInfo.szSRCInfo, sizeof(gstTransInfo.szSRCInfo));        
    
    // #54
    memset(buf, 0, sizeof(buf));
    ret = IsoGetField(pstRecvPacket, 54, buf, sizeof(buf));        
    if(ret > 0)
    {
        memcpy(pst_msginfo->asBalance, &buf[7], 13);
    }
    
    // #55
    gstTransData.iRecvIccDataLen = IsoGetField(pstRecvPacket, 55, gstTransData.bcRecvIccData, sizeof(gstTransData.bcRecvIccData));
    TrnGetIccDataFromMsg(pstRecvPacket);

    // #60
    memset(buf, 0, sizeof(buf));
    len = 0;
    ret = IsoGetField(pstRecvPacket, 60, buf, sizeof(buf));        
    if(ret > 0)
    {
        len += 2;
        memcpy(pst_msginfo->asBatchNO, buf + len, 6);
    }
    
    // #62
    gstTransData.iPrivateDataLen = IsoGetField(pstRecvPacket, 62, gstTransData.bcPrivateData, sizeof(gstTransData.bcPrivateData));        

    // #63
    memset(buf, 0, sizeof(buf));
    memset(pst_msginfo->asInterOrgCode, 0, sizeof(pst_msginfo->asInterOrgCode));
    memset(pst_msginfo->asIssuerInfo, 0, sizeof(pst_msginfo->asIssuerInfo));
    memset(pst_msginfo->asCUPInfo, 0, sizeof(pst_msginfo->asCUPInfo));
    memset(pst_msginfo->asAcqInfo, 0, sizeof(pst_msginfo->asAcqInfo));
    memset(pst_msginfo->asTermReserved, 0, sizeof(pst_msginfo->asTermReserved));
    len = 0;
    ret = IsoGetField(pstRecvPacket, 63, buf, sizeof(buf));
    if(ret > 0)
    {
        len = 0;
        memcpy(pst_msginfo->asInterOrgCode, buf + len, 3);
        len += 3;
        if(len < strlen(buf))
        {
            memcpy(pst_msginfo->asIssuerInfo, buf + len, 20);
            len += 20;                
        }
        if(len < strlen(buf))
        {
            memcpy(pst_msginfo->asCUPInfo, buf + len, 20);
            len += 20;                
        }
        if(len < strlen(buf))
        {
            memcpy(pst_msginfo->asAcqInfo, buf + len, 20);
            len += 20;                
        }
        if(len < strlen(buf))
        {
            memcpy(pst_msginfo->asTermReserved, buf + len, 60);
        }
    }    
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Get data of transaction from sent ISO8583 message,
                  and save it to structure "gstTransData"
 
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstSendPacket : 8583 sent message
                            
** Return      :  (1)SDK_OK: Succeeded
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 TrnUpdateTransDataSend(SDK_8583_ST8583 *pstSendPacket)
{
    s32 len = 0;
    u8 buf[128] = {0};
    s32 ret = 0;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_CARDINFO *pst_cardinfo = NULL;

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    
    //[0]message type
    IsoGetField(pstSendPacket, 0, gstTransData.asMTI, sizeof(gstTransData.asMTI));
    
    //[2]card number data
    IsoGetField(pstSendPacket, 2, pst_cardinfo->stCardData.asCardNO, sizeof(pst_cardinfo->stCardData.asCardNO));
    
    //[3]Processing Code
    IsoGetField(pstSendPacket, 3, pst_msginfo->asProcCode, sizeof(pst_msginfo->asProcCode));
        
    //[4]Amount
    IsoGetField(pstSendPacket, 4, pst_msginfo->asAmount, sizeof(pst_msginfo->asAmount));

    //[11]System Trace Audit Number
    IsoGetField(pstSendPacket, 11, pst_msginfo->asTraceNO, sizeof(pst_msginfo->asTraceNO));
    
    //[12]Local Transaction Time
    IsoGetField(pstSendPacket, 12, pst_msginfo->asTransTime, sizeof(pst_msginfo->asTransTime));

    //[13]Local Transaction Date
    IsoGetField(pstSendPacket, 13, pst_msginfo->asTransDate, sizeof(pst_msginfo->asTransDate));
        
    //[22]Point of Service Entry Mode
    IsoGetField(pstSendPacket, 22, pst_msginfo->asEntryMode, sizeof(pst_msginfo->asEntryMode));
    
    //[25]Point of Service Condition Code
    IsoGetField(pstSendPacket, 25, pst_msginfo->asConditionCode, sizeof(pst_msginfo->asConditionCode));
    
    //[26]PIN Capture Code
    IsoGetField(pstSendPacket, 26, pst_msginfo->asPinCapCode, sizeof(pst_msginfo->asPinCapCode));
           
    //[41]Card Acceptor Terminal ID(TID)
    IsoGetField(pstSendPacket, 41, pst_msginfo->asTermID, sizeof(pst_msginfo->asTermID));        
    
    //[42]Card Acceptor Identification Code(MID)
    IsoGetField(pstSendPacket, 42, pst_msginfo->asMerchID, sizeof(pst_msginfo->asMerchID));        
            
    //[49]Transaction Currency Code
    IsoGetField(pstSendPacket, 49, pst_msginfo->asCurrencyCode, sizeof(pst_msginfo->asCurrencyCode));        
    
    //[60]field 60
    memset(buf, 0, sizeof(buf));
    len = 0;
    ret = IsoGetField(pstSendPacket, 60, buf, sizeof(buf));        
    if(ret > 0)
    {
        memcpy(pst_msginfo->asFuncCode, buf, 2);
        len += 2;
        memcpy(pst_msginfo->asBatchNO, buf + len, 6);
    }

    TrnGetIccDataFromMsg(pstSendPacket);
    
    return SDK_OK;
}

