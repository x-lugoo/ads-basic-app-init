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
#ifndef _CAPK_H_
#define _CAPK_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define TABNAME_CAPK     "Capk"


/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/
typedef enum
{
    CAPK_ID,
    CAPK_RID,        
    CAPK_CAPKI,      
    CAPK_HASH_INDEX,    
    CAPK_ARITH_INDEX,   
    CAPK_MODUL_LEN,   
    CAPK_MODUL,      
    CAPK_EXPONENT_LEN,
    CAPK_EXPONENT,   
    CAPK_CHECKSUM_LEN,
    CAPK_CHECKSUM,   
    CAPK_EXPIRE_DATE, 
}E_CAPK_ITEM;


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
extern s32 EmvInitCapk(bool bIsLiveCapk);
extern void EmvSetAllDefaultCapk(bool bIsLiveCapk);
extern s32 EmvSetCapk(E_CARD_TYPE eCardType, bool bIsLiveCapk);

/*-----------------------------------------------------------------------------*/
#endif

