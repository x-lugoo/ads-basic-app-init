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
#ifndef _BALANCE_H_
#define _BALANCE_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern void DispBalanceAmount(void);
extern s32 BalancePackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern void BalanceTrans(u16 usCardType);
extern void OnBalance(void);
extern s32 EchoBalancePackMsg(SDK_8583_ST8583 *pstIsoMsgRecv);


/*-----------------------------------------------------------------------------*/
#endif



