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
#ifndef _COMMU_H_
#define _COMMU_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern void CommuConfigParam(bool bIsUseBackup);
extern void CommuPreLink();
extern bool CommuOpenEthernet(void);
extern bool CommuOpenWiFi(void);
extern s32 CommuSslConnect(s32 iTimeOut);
extern s32 CommuCreateLink(void);
extern s32 CommuExchangeIsoMsg(SDK_ICC_TRADE_PARAM *pstIccTradeParam, 
                                s32 (*pPackFun)(SDK_8583_ST8583 *), 
                                BOOL bIsReversal,  
                                BOOL bIsPreposition,
                                BOOL bIsSaveRecord);
extern s32 CommuExchangeIsoPacket(SDK_8583_ST8583 *pstIsoMsgSend, SDK_8583_ST8583 *pstIsoMsgRecv);


/*-----------------------------------------------------------------------------*/
#endif

