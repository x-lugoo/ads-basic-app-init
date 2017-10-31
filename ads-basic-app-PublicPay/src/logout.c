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
#include "global.h"

/*----------------------------------------------------------------------------*/
/*****************************************************************************
** Description :  Logout transaction process
** Parameters  :  None
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void LogoutTrans(void)
{
    memset(&gstLoginInfo, 0, sizeof(ST_LOGIN_INFO));

    sdkSysBeep(SDK_SYS_BEEP_OK);
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_TRANS_SUCCESS, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
}

