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
#define AFX_APP_VARIABLES
#include "global.h"
#undef AFX_APP_VARIABLES

// functions
void AppMain(void);
void MainMenu(void);
void OnCircle();

#define USE_SDK_DEBUG 
#undef USE_SDK_DEBUG

//-----------------------------------------------------------------------------
#ifdef XGD_SDK_DEBUG

#ifdef USE_SDK_DEBUG 
static const SDK_DEBUG_FILTER DebugFilter =
{
    FALSE,                   //whether in testing state
    FALSE,                   //whether output function name
    SDK_DEBUG_TARGET_COM,    //debug massage output to serial port
    SDK_DEUBG_OUT_ALL,       //trace filtering mode
};
#else
DBG_FILTER DbgFilter =
{
    TRUE,                  // whether in testing state
    DBG_OUTPUT_ALL,        // only block the tags of black list
    DBG_MODE_PINPAD,        // mode for Trace(), TraceHex(), Assert(), Verify().
    DBG_ENABLE_PINPAD,        // enable all trace modes
};
#endif

// white list
char const *pWhiteList[] =
{
    "xgd",
    "emv",
};


// black list
char const *pBlackList[] =
{
    "dbg"
};

#endif

/*----------------------------------------------------------------------------*/
/*****************************************************************************
** Description :  Program entery point
** Parameters  :  input:
                  (1)s32 argc : input parameters number(no use now)
                  (2)char const *argv[] : input parameters(no use now)
                  
** Return      :  (1)0 : program quit
** Author      :  wenmin   2016-10-18 
** Remarks     :  

        [ PLEASE DO NOT MODIFY ANY OF CONTENTS IN THIS FUNCTION !!!]

*****************************************************************************/
s32 main(s32 argc, char const *argv[])
{
    sdkSysLoadDll(NULL, 0);                         // Load libraries
    sdkExtLoadDll(NULL, 0);                         //Load extended libraries
    sdkSysMain(argc, (const char **)argv);          // Initialize system
    
#ifdef XGD_SDK_DEBUG
#ifdef USE_SDK_DEBUG
        Verify(sdkDebugInitalList(pWhiteList, sizeof(pWhiteList) / sizeof(char *), pBlackList, sizeof(pBlackList) / sizeof(char *)) == SDK_OK);
        Verify(sdkDebugSetFilter(&DebugFilter) == SDK_OK);
#else /* if 0 */
        AppDbgInit(&DbgFilter,
            pWhiteList, sizeof(pWhiteList) / sizeof(char*),
            pBlackList, sizeof(pBlackList) / sizeof(char*));
#endif
#endif

    AppMain();                  // application main()

    sdkExtUnLoadDll();          //Unload extended libraries. it must be called before exiting main()
    sdkSysUnLoadDll();          // Unload libraries. it must be called before exiting main()
    sdkSysAppQuit();            // Do some clean-up before exiting main()

    return 0;
}

/*****************************************************************************
** Description :  initialize the application 
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void AppInit(void)
{
    SDK_SYS_INITIAL_INFO st_initial;
    bool print = TRUE;
    
    //display initial screen
    sdkDispClearScreen();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_SYSTEM_INIT, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    
    sdkIccPowerStartInit();                                                 // Must be called for EMV IC card reset
    
    //sdkDbTest();
    RecordInit();
    SetupInitSetting();
    SetupReadSetting(0);
    DispSetMaxLine();
    
    // Initialize system
    st_initial.bIsHavePinPad = gstAppSysCfg.stSysParam.bIsExtPED;   // PINPAD: TRUE->external, FALSE->internal
    st_initial.bIsINRf = gstAppSysCfg.stSysParam.bIsIntRf;          // RF-READER: TRUE->internal, FALSE->external
    sdkSysInitParam(&st_initial);
    
    //Initialize contactless parameter
	if (SDK_OK != EmvReadPaypassPaywaveCfgIni())
	{  	
		EmvInitCtlsParam();
	}

    if(gstAppSysCfg.stSysParam.bIsExtPED)
    {
        sdkPEDSetLanguage(SDK_PED_EN);
        TrnPedCloseVoice();
        PedShowWelcome();
    }

    // initialize AID & CAPK of EMV
    EmvInitAid(TRUE);
    EmvInitCapk(TRUE);

    // initialize display font color
    if(IsTermColorScreen())
    {
        sdkDispSetFontColor(SDK_DISP_WHITE_COLOR);
    }

    // check print error and reprint
    if(SDK_OK == RecordSearch(LOG_STAT_NEEDREPRINT, (void *)&print, &gstTransData.stTransLog))
    {
        PrintRecipt(TRUE);
    }
    SettleEndProcess(TRUE);
    
    // create PPP first if the communication mode is GPRS or CDMA
    if(SDK_COMM_GPRS == gstAppSysCfg.stCommuParam.uiCommuMode ||
       SDK_COMM_CDMA == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        //sdkCommCreatePPP(TMR_NONE);
    }

    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
    gstTransData.stTransLog.eTransID = TRANSID_MAINMENU;

}

/*****************************************************************************
** Description :  application start and go to main loop
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  the initialization of application should be configured here
*****************************************************************************/
void AppMain(void)
{
   // Get screen buffer for saving & restoring screen
    guiScrBuffSize = sdkDispGetScreenBufferSize();
    pgScrBuff = (u16 *)sdkGetMem(guiScrBuffSize * 2);

    AppInit();
    
    // main loop here!!!
    OnCircle();

    // Release screen buffer
    if(pgScrBuff)
    {
        sdkFreeMem(pgScrBuff);
        pgScrBuff = NULL;
    }
}

/*****************************************************************************
** Description :  process event on idle state(main loop)
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void OnCircle(void)
{
    s32 key;
    u32 tmr_disp;
    u32 tmr_idle;
    u32 tmr_led_idle;
    bool refresh = TRUE;
    bool refresh_time = TRUE;
    bool refresh_led = TRUE;
    u8 max_line;
    s32 color;

    tmr_disp = sdkTimerGetId();
    tmr_idle = sdkTimerGetId();
    tmr_led_idle = sdkTimerGetId();

    max_line = DispGetMaxLine() - 1;
    color = sdkDispGetFontColor();
    
    sdkKbKeyFlush();
    key = 0;
    while(1)
    {
        switch(gstTransData.stTransLog.eTransID)
        {
            // process disp welcome screen
            case TRANSID_WELCOME:
                if(refresh)
                {
                    DispWelcome();
                    refresh = FALSE;
                }
                if(refresh_time)
                {
                    DispIcon();
                    DispDateTime(max_line);
                    sdkDispBrushScreen();
                    refresh_time = FALSE;
                }

                if (refresh_led)
                {
                    EmvLedIdle();
                    refresh_led = FALSE;
                }
                break;

            case TRANSID_MAINMENU:
                DispBackground(FILE_BACKGROUND_BMP);
                sdkDispSetFontColor(color);
                MainMenu();
                gstTransData.stTransLog.eTransID = TRANSID_WELCOME;
                tmr_idle = sdkTimerGetId();
                refresh = TRUE;
                break;

            case TRANSID_SALE:
                memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
                gstTransData.stTransLog.stMsgInfo.asAmount[0] = (u8)key;
                DispBackground(FILE_BACKGROUND_BMP);
                sdkDispSetFontColor(color);
                OnSale();
                TrnEndProcess();
                gstTransData.stTransLog.eTransID = TRANSID_WELCOME;
                tmr_idle = sdkTimerGetId();
                refresh = TRUE;
                break;
                
            default:
                gstTransData.stTransLog.eTransID = TRANSID_WELCOME;
                refresh = TRUE;
                break;
        }       
   
        if(refresh)
        {
            OfflineAutoUpload();
        }
             
        // process key input
        key = sdkKbGetKey();
        if(SDK_KEY_ENTER == key)
        {
            sdkSysBeep(SDK_SYS_BEEP_OK);
            gstTransData.stTransLog.eTransID = TRANSID_MAINMENU;
        }
        else if(key > SDK_KEY_0 && key <= SDK_KEY_9)
        {
            sdkSysBeep(SDK_SYS_BEEP_OK);
            gstTransData.stTransLog.eTransID = TRANSID_SALE;
        }
        else if(SDK_KEY_FUNCTION == key)
        {
            TrnSwitchApp();
            refresh = TRUE;
        }
        else if(key > 0)
        {
            sdkSysBeep(SDK_SYS_BEEP_ERR);
        }

        // refresh disp timer
        if(sdkTimerIsEnd(tmr_disp, TMR_REFRESH_TIME))
        {
            tmr_disp = sdkTimerGetId();
            refresh_time = TRUE;
        }

        // CTLS LED idle state
        if(sdkTimerIsEnd(tmr_led_idle, TMR_CTLS_LED_IDLE))
        {
            tmr_led_idle = sdkTimerGetId();
            refresh_led = TRUE;
        }

        // process low power consumption
        if(!sdkSysIsExPower() && (0 != gstAppSysCfg.stSysParam.uiIdleTimer)
            && sdkTimerIsEnd(tmr_idle, gstAppSysCfg.stSysParam.uiIdleTimer * 1000))
        {
            sdkSysEnterIdle(1, 1);
            tmr_idle = sdkTimerGetId();
            refresh = TRUE;
        }
    }
}

/*****************************************************************************
** Description :  Display and handles main menu item.
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void MainMenu(void)
{
    ST_MENU st_menu = 
    {
        STR_INFO_NEXGO,
        MENU_HIGHLIGHT,
        0,    
        {
            {STR_TRANS_LOGON,      SDK_DISP_LDISP, FALSE, 0, LogonTrans}, 
            {STR_TRANS_SALE,       SDK_DISP_LDISP, FALSE, 0, OnSale},
            {STR_TRANS_VOID,       SDK_DISP_LDISP, FALSE, 0, OnVoid},
            {STR_TRANS_REFUND,     SDK_DISP_LDISP, FALSE, 0, OnRefund},
            {STR_TRANS_TIP,        SDK_DISP_LDISP, FALSE, 0, OnAdjust},
            {STR_TRANS_BALANCE,    SDK_DISP_LDISP, FALSE, 0, OnBalance},
            {STR_TRANS_SETTLEMENT, SDK_DISP_LDISP, FALSE, 0, OnSettle},
            {STR_TRANS_LOGOUT,     SDK_DISP_LDISP, FALSE, 0, LogoutTrans}, 
            {STR_FUNC_REPRINT,     SDK_DISP_LDISP, FALSE, 0, MenuPrintTrans}, 
            {STR_FUNC_TRANS_QUERY, SDK_DISP_LDISP, FALSE, 0, MenuQueryTrans}, 
            {STR_FUNC_SWITCH_APP,  SDK_DISP_LDISP, TRUE,  SDK_KEY_FUNCTION, TrnSwitchApp},
            {{0}},
        }
    };

    // Enable beep on key-pressing
    sdkSysEnableBeep(TRUE);
    sdkSysBeep(SDK_SYS_BEEP_OK);

    while(1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
        TrnEndProcess();
    }

    return;
}

