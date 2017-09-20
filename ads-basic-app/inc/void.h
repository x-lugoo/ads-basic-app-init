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
#ifndef _VOID_H_
#define _VOID_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern u16 VoidCheckBrushOrPwd(ST_TRANSLOG *stTransLog, bool *bIsNeedCard, bool *pbIsNeedPwd);
extern s32 VoidCheckOriginalTrans(ST_TRANSLOG *pstTransLog);
extern s32 VoidPackMsg(SDK_8583_ST8583 *pstIsoMsg);
extern void VoidTrans(u16 usCardType);
extern void OnVoid(void);
extern s32 EchoVoidPackMsg(SDK_8583_ST8583 *pstIsoMsgSend, SDK_8583_ST8583 *pstIsoMsgRecv);
/*-----------------------------------------------------------------------------*/
#endif



