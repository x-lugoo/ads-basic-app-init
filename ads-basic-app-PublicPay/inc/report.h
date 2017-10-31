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
#ifndef _REPORT_H_
#define _REPORT_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/

extern void MenuPrintTrans(void);
extern void MenuQueryTrans(void);
extern void ReportPrintLastTrans(void);
extern void ReportPrintSettle(void);
extern void ReportPrintSpecifiedTrans(void);
extern s32 ReportPrintTransDetail(void);
extern s32 ReportPrintErrSendTransDetail(void);
extern void ReportRePrintTransDetail(void);
extern void ReportPrintTransTotal(void);
extern void ReportQuerySpecifiedTrans(void);
extern void ReportQueryTransDetail(void);
extern void ReportQueryTransTotal(void);

/*-----------------------------------------------------------------------------*/
#endif


