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
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define MAX_MENU_ITEM    64

#define DISP_LIST_MAX    20

typedef enum
{
    MENU_NUMBER,
    MENU_HIGHLIGHT,
    MENU_HIGHLIGHT_NUMBER,
}E_MENU_MODE;

typedef enum 
{
    BATTERY_ERR = -2,           // no battery
    BATTERY_LOW =  -1,          // battery low
    BATTERY_0 = 0,              // battery empty
    BATTERY_1 = 1,              // battery level 1
    BATTERY_2 = 2,              // battery level 2
    BATTERY_3 = 3,              // battery level 3
    BATTERY_HIDE = 98,          // hide battery icon
    BATTERY_MAX = 99,           // battery full
}E_BATTERY_STATE;

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef void (*MENUITEM_FUN)();

typedef struct
{
    u8 asText[64 + 1];
    u32 uiAlign;
    bool bIsHide;
    u32 uiKeyValue;
    MENUITEM_FUN pFun;
}ST_MENU_ITEM;

typedef struct
{
    u8 asTitle[64 + 1];
    E_MENU_MODE eMode;
    SDK_DISP_FONT eFontSize;
    ST_MENU_ITEM stItem[MAX_MENU_ITEM];
}ST_MENU;

typedef struct               
{
    s32 iStatus;          
    u8 asTextLine2[50+1];         
    u8 asTextLine3[50+1];         
}ST_TRANS_STATUS_TEXT;

typedef struct               
{
    u8 asRespCode[2+1];          
    u8 asTextLine2[50+1];         
    u8 asTextLine3[50+1];         
}ST_RESP_TEXT;

typedef struct
{
    u8 asStr[64];
    u8 ucDispAtr;
}ST_DISP_LIST_ITEM;

typedef struct
{
    s32 iStartLine;
    s32 iEndLine;
    u8 ucNum;
    ST_DISP_LIST_ITEM stItem[DISP_LIST_MAX];
}ST_DISP_LIST;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern bool IsTermColorScreen(void);
extern void DispSetMaxLine(void);
extern u8 DispGetMaxLine(void);
extern void DispSaveScreen(void);
extern void DispRestoreScreen(void);
extern void DispBackground(const u8 *pasBmpFileName);
extern void DispClearContent(void);
extern void DispReadCardErr(u8 ucMode);
extern void DispSuccResponse(void);
extern void DispErrResponse(void);
extern void DispEmvReadCardReturn(SDK_EMV_RLT eEmvRet);
extern void DispTransStatus(void);
extern s32 DispEmvErr(const u8 *pasSection, const u8 *pasKey);
extern bool DispCardNo(const u8 *pasCardNo);
extern void DispReadCard(s32 iCardMode);
extern void DispTitle(const u8 *pasTitle);
extern void DispTransSucc();
extern s32 DispTransTotal(ST_SETTLE *pstSettle);
extern s32 DispTransDetail(ST_TRANSLOG *pstTransLog);
extern s32 DispListBox(s32 siOvertimer, ST_DISP_LIST *pstList);
extern void DispBatteryIcon(s32 iPosition);
extern void DispWirelessIcon(s32 iPosition);
extern void DispSignalIcon(s32 iPosition);
extern void DispIcon(void);
extern void DispDateTime(u8 ucLine);
extern void DispGetBmpSize(const u8 *pasFileName, u32 *puiHeight, u32 *puiWidth);
extern void DispSaveSetupParam(void);
extern bool DispAOSA(void);
extern s32 DispEMVErr(const u8 *pasSection, const u8 *pasKey);
extern void DispWelcome();
extern void PedShowWelcome(void);
extern void MenuPreProcess(const ST_MENU *pstMenu, ST_MENU_ITEM *pstDispMenu, u32 *puiDispNum, ST_MENU_ITEM *pstHideMenu, u32 *puiHideNum);
extern s32 MenuSelectByKeyNum(const ST_MENU *pstMenu, s32 iTimeOut);
extern s32 MenuSelectByKeyEnt(const ST_MENU *pstMenu, s32 iTimeOut);
extern s32 MenuProcess(const ST_MENU *pstMenu, s32 iTimeOut);

/*-----------------------------------------------------------------------------*/
#endif


