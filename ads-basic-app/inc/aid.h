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
#ifndef _AID_H_
#define _AID_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define TABNAME_AID      "Aid"


/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef enum
{
    VISA = 0,
    MASTER,
    JCB,
    AMEX,
    CUP
}E_CARD_TYPE;

typedef enum
{
    AID_ID,
    AID_AIDLEN,            
    AID_AID,               
    AID_ASI,               
    AID_APP_VERSION,         
    AID_TAC_DEFAULT,        
    AID_TAC_ONLINE,         
    AID_TAC_DECLINE,        
    AID_EMV_FLOOR_LIMIT,        
    AID_THRESHOLD,         
    AID_MAX_TARGET_PERCENT,  
    AID_TARGET_PERCENT,     
    AID_TERM_DDOL_LEN,       
    AID_TERM_DDOL,          
    AID_TERM_PIN_CAP,        
    AID_VLP_TRANS_LIMIT,     
    AID_CTLS_CVM_LIMIT,     
    AID_CTLS_TRANS_LIMIT,   
    AID_CTLS_FLOOR_LIMIT,
    AID_IS_SHOW_RAND_NUM,      
    AID_IS_LOCAL_NAME,    
    AID_LOCAL_NAME_LEN,             //add          
    AID_LOCAL_NAME,                 //add 
    AID_IS_FORCE_ONLINE,  
}E_AID_ITEM;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern s32 EmvInitAid(bool bIsLiveAid);
extern s32 EmvSetAid(E_CARD_TYPE eCardType, bool bIsLiveAid);
extern void EmvSetAllDefaultAid(bool bIsLiveAid);

/*-----------------------------------------------------------------------------*/
#endif

