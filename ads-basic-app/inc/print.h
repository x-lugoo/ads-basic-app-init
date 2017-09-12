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
#ifndef _PRINT_H_
#define _PRINT_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
typedef enum
{
    PRINT_FONT_FULL,
    PRINT_FONT_HALF,
    PRINT_FONT_SMALL,
    PRINT_FONT_BOLD,
    PRINT_FONT_HIGHBOLD,
}E_PRINT_FONT;

typedef enum
{
    PRINT_SIZE_BIG = 1,
    PRINT_SIZE_MEDIUM,
    PRINT_SIZE_SMALL,
}E_PRINT_SIZE;

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/

extern s32 PrintDetailReportHeader(const u8 *pasTitle);
extern s32 PrintDetailReport(ST_TRANSLOG *stTransLog);
extern s32 PrintDetailReportFooter(void);
extern s32 PrintFormDetailData(ST_TRANSLOG *stTransLog);
extern s32 PrintFormDetailEndData();
extern s32 PrintFormDetailHeaderData(const u8 *pasTitle);
extern s32 PrintFormReciptData(bool bIsReprint, u32 uiPrintTimes, u32 uiTotalTimes);
extern s32 PrintFormSettleData(bool bIsReprint);
extern s32 PrintFormTotalData(ST_SETTLE *pstSettle);
extern s32 PrintRecipt(bool bIsReprint);
extern void PrintSetFont(SDK_PRINT_FONT *pstFont, E_PRINT_FONT eFont);
extern s32 PrintSettleReport(bool bIsReprint);
extern s32 PrintStart(bool bIsRollPaper);
extern s32 PrintTotalReport(ST_SETTLE *pstSettle);

/*-----------------------------------------------------------------------------*/
#endif


