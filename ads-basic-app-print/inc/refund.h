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
#ifndef _REFUND_H_
#define _REFUND_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define REFUND_MODE_GENERAL  0
#define REFUND_MODE_CUP      1

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern void RefundTrans(u16 usCardType);
extern s32 RefundPackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern void OnRefund(void);


/*-----------------------------------------------------------------------------*/
#endif

