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
#ifndef _LOGON_H_
#define _LOGON_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define ADMINNO             0                                   //admin
#define SYSADMINNO          99                                  //sys admin


/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern s32 LogonPackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern s32 LogonSendMsg();
extern void LogonTrans(void);

/*-----------------------------------------------------------------------------*/
#endif

