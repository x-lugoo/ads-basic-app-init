/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.
                
                       http://www.xinguodu.com/en/

 ******************************************************************************
  File Name     :   
  Version       :  
  Author        :  Jeff
  Date          :  2017-10-10
  Description   : 


  
******************************************************************************/
#ifndef __POLICY_H__
#define __POLICY_H__

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/
#define POLICY_COMPANY_CODE_LEN			 6
#define POLICY_MID_LEN					15
#define POLICY_TID_LEN					8
#define POLICY_NUMBER_LEN				40
#define POLICY_AMOUNT_LEN				12
#define POLICY_RETURN_CODE_LEN			2
#define POLICY_CARD_NO_LEN				19
#define POLICY_TRANS_DATE_LEN			8
#define POLICY_TRANS_TIME_LEN			6
#define POLICY_TRANS_NO_LEN				6
#define POLICY_REFERENCE_NO_LEN 		12
#define POLICY_ORIGINAL_DATA_FIELD_LEN  40
#define POCLICY_ADDITIONAL_LEN			160

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-------------------------------- ---------------------------------------------*/
typedef struct
{
	u8 asCompanyCode[POLICY_COMPANY_CODE_LEN + 1];
	u8 asMID[POLICY_MID_LEN + 1];
	u8 asTID[POLICY_TID_LEN + 1];
	u8 asPolicyNum[POLICY_NUMBER_LEN + 1];
	u8 asAmount[POLICY_AMOUNT_LEN + 1];
	u8 asRetCode[POLICY_RETURN_CODE_LEN + 1];
	u8 asCardNo[POLICY_CARD_NO_LEN + 1];
	u8 asTransDate[POLICY_TRANS_DATE_LEN + 1];
	u8 asTransTime[POLICY_TRANS_TIME_LEN + 1];
	u8 asTransNo[POLICY_TRANS_NO_LEN + 1];
	u8 asRefNo[POLICY_REFERENCE_NO_LEN + 1];
	u8 asOrigDataField[POLICY_ORIGINAL_DATA_FIELD_LEN + 1];
	u8 asAddMsg[POCLICY_ADDITIONAL_LEN + 1];
}ST_SENT_POLICY_DATA_FIELD;

typedef struct 
{
	u8 ucSTX;
	u8 asCmd[2 + 1];
	u8 heDataLen[4];
	ST_SENT_POLICY_DATA_FIELD stPolicyDataField;
	u8 ucETX;
	u8 ucCRC;
}ST_SENT_POLICY_MSG;



#endif

