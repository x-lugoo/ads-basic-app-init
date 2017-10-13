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
static SDK_ICC_EXPARAM3 _gstSdkIccExparam3; //for contactless transaction

/*
   TTQ (9F66)
   Byte 1
   bit 8: 1 = MSD supported
   bit 7: RFU (O)
   bit 6: 1 = qVSDC supported
   bit 5: 1 = EMV contact chip supported
   bit 4: 1 = Offline-only reader
   bit 3: 1 = Online PIN supported
   bit 2: 1 = Signature supported
   bit 1: 1 = Offline Data Authentication (ODA) for Online Authorizations supported.
   Note: Readers compliant to this specification set TTQ byte 1 bit 1 to 0b.
   Byte 2
   bit 8: 1 = Online cryptogram required
   bit 7: 1 = CVM required
   bit 6: 1 = (Contact Chip) Offline PIN supported
   bits 5-1: RFU (00000)
   Byte 3
   bit 8: 1 = Issuer Update Processing supported
   bit 7: 1 = Mobile functionality supported (Consumer Device CVM)
   bits 6-1: RFU (000000)
   Byte 4
   RFU ('00')
*/

/*
   CTQ (9F6C)
   Byte 1
   bit 8: 1 = Online PIN Required
   bit 7: 1 = Signature Required
   bit 6: 1 = Go Online if Offline Data Authentication Fails and Reader is online capable.
   bit 5: 1 = Switch Interface if Offline Data Authentication fails and Reader supports VIS.
   bit 4: 1 = Go Online if Application Expired
   bit 3: 1 = Switch Interface for Cash Transactions
   bit 2: 1 = Switch Interface for Cashback Transactions
   bit 1: RFU (O)
   Byte 2
   bit 8: 1 = Consumer Device CV Update Processing at the POS
   bits 6-1: RFU (000000) M Performed
   Note: Bit 8 is not used by cards compliant to this specification, and is set to 0b.
   bit 7: 1 = Card supports Issuer

   TermTransPredicable("\x9F\x66"),TermCapab("9F33")TermAddCapab(9F40),
   Certification center public key check value(DF03),EC Reset Threshold(9F6D),
*/
 
/* Tag DF03
    byte1 bit8 :status check
    byte1 bit7: Amount, Authorized of Zero Check
    byte1 bit6: Reader Contactless Transaction Limit (RCTL) Check
    byte1 bit5: Reader Contactless Floor Limit Check
    byte1 bit4: Reader CVM Required Limit Check 
    byte1 bit3: CVN17 support
    byte1 bit2: DRL support
    byte1 bit1: Amount, Authorized of Zero Check option (0 - option1   1- option2)

    byte2 bit3: dual interface
    byte2 bit2: mag track2 upload
    byte2 bit1: mag track1 upload
*/

/* VISA payWave config parameters */
static ST_EMV_TLV TabPaywaveCfg[] =
{
    {"\x9F\x66", 0x04, "\x36\x00\xC0\x00"},      //Terminal Transaction Qualifiers(TTQ)
    {"\x9F\x33", 0x03, "\xE0\x60\xC8"},          //Terminal Capabilities     //online PIN & signature & SDA & DDA & CDA
    {"\x9F\x40", 0x05, "\x61\x00\xD0\xB0\x01"},  //Additional Terminal Capabilities    //CASH & CASHBACK-OFF, GOODS & SERVICES-ON
    {"\xDF\x03", 0x02, "\x0C\x03"},              //self-defined tag      
};

/* MasterCard PayPass config parameters */
static ST_EMV_TLV TabPaypassCfg[] =
{
    {"\x9F\x33",     0x03, "\xE0\x60\xC8"},             //Terminal Capabilities, online PIN & signature & SDA & DDA & CDA
    {"\x9F\x40",     0x05, "\x60\x00\xF0\xA0\x01"},     //Additional Terminal Capabilities, Goods & Services
    {"\x9f\x6d",     0x02, "\x00\x01"},                 //Mag-stripe Application Version Number
    {"\xdf\x81\x1b", 0x01, "\x60"},                     //Kernel Configuration, b8-only EMV mode, b7-only mag-stripe mode, b6-On device cardholder verification supported(for mobile)
    {"\xdf\x81\x25", 0x06, "\x00\x09\x99\x99\x99\x99"}, //Reader Contactless Transaction Limit (On-device CVM), for mobile only!!!
    {"\xdf\x81\x1e", 0x01, "\x30"},                     //(MSD mode)Mag-stripe CVM Capability -CVM Required,  0x20-online PIN, 0x10-signature
    {"\xdf\x81\x2c", 0x01, "\x10"},                     //(MSD mode)Mag-stripe CVM Capability -No CVM Required,  0x00-no CVM, 0x20-online PIN, 0x10-signature
    {"\xdf\x81\x1f", 0x01, "\x08"},                     //Security Capability, BIT8:SDA, BIT7:DDA, BIT4:CDA
    {"\xdf\x81\x17", 0x01, "\x00"},                     //Card Data Input Capability    //b8-Manual key entry, b7-Magnetic stripe, b6-IC with contacts,b5-1RFU
    {"\xdf\x81\x18", 0x01, "\x60"},                     //(EMV mode)CVM Capability -CVM Required,  0x60 - online PIN & signature  , 0x20-signature
    {"\xdf\x81\x19", 0x01, "\x20"},                     //(EMV mode)CVM Capability -No CVM Required, 0x20-signature
};

/*****************************************************************************
** Description :  EMV flow callback function - input amount
** Parameters  :  output:
				  (1)u8 *pasAmount: transaction amount
				  
** Return      :  (1)SDK_ERR: succeed to input amount
                  (2)SDK_OK : fail to input amount
                  
** Author      :  wenmin   2016-10-18
** Remarks     :  The sale amount must be inputed but cashback amount is optional,
                  user can just bypass cashback amount by pressing key "ENTER". 
*****************************************************************************/
s32 CbEmvInputAmount(u8 *pasAmount)
{
#if 0	
    u8 sale_amt[12 + 1] = {0}, cashback_amt[12 + 1] = {0};
    u8 amt1[6], amt2[6];

    if (SDK_OK != TrnInputAmount(SALE_AMOUNT, sale_amt))
    {
        return SDK_ERR;
    }

    if (SDK_OK != TrnInputAmount(CASHBACK_AMOUNT, cashback_amt))
    {
        return SDK_ERR;
    }
    memset(amt1, 0, sizeof(amt1));
    sdkAscToBcd(amt1, sale_amt, 12);
    TraceHex("sale", "sale amount", amt1, 6);
    memset(amt2, 0, sizeof(amt2));
    sdkAscToBcd(amt2, cashback_amt, 12);
    TraceHex("sale", "cashback amount", amt2, 6);
    memcpy(gstTransData.stTransLog.stMsgInfo.asCashbackAmount, cashback_amt, 13);
    sdkBcdAdd(amt1, amt1, 6, amt2, 6);
    sdkBcdToAsc(pasAmount, amt1, 6);
    Trace("sale", "total amount(sale + cashback) = %s\r\n", pasAmount);
#endif
	memcpy(pasAmount,gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField.asAmount, 12);
    return SDK_OK;
}

/*****************************************************************************
** Description :  EMV flow callback function - display card number
** Parameters  :  input:
				  (1)u8 const *pasCardNo: card number
				  
** Return      :  (1)SDK_ESC: Cancel transaction while asked to confirm the card
                              number.
                  (2)SDK_OK : Confirm card number and proceed the transaction.
                  
** Author      :  wenmin   2016-10-18
** Remarks     :
*****************************************************************************/
s32 CbEmvDispCardNo(u8 const *pasCardNo)
{
    if(!DispCardNo(pasCardNo))
    {
        return SDK_ESC;
    }

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    return SDK_OK;
}

/*****************************************************************************
** Description :  EMV flow callback function - display some prompt information
** Parameters  :  input: 
                  (1)SDK_ICC_PROMPT_TYPE ePromptType 
                  
** Return      :  (1)TRUE : confirm and proceed transaction
                  (2)FALSE: cancel transaction
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  Must pay attention to the prompt "LAST CHANCE" in order not  
                  to block the offline PIN due to PIN try limit exceeds.
*****************************************************************************/
s32 CbEmvDispPrompts(SDK_ICC_PROMPT_TYPE ePromptType)
{
    u8 tmp[128] = {0};
    s32 len = 0;

    Trace("emv", "-->CbEmvDispPrompts()");

    DispClearContent();

    switch (ePromptType)
    {
         case SDK_ICC_OFFLINE_PIN_ERR:
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PIN_ERR, SDK_DISP_DEFAULT);
            break;

         case SDK_ICC_OFFLINE_PIN_SUC:
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PIN_CORRECT, SDK_DISP_DEFAULT);
            break;

         case SDK_ICC_INPUT_PIN_AGAIN:
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PIN_ERR, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_RETRY, SDK_DISP_DEFAULT);

            if (sdkIccReadTLV("\x97\x17", tmp, &len) > 0)
            {
                if (1 == tmp[0])
                {
                    sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_LAST_CHANCE, SDK_DISP_DEFAULT);
                }
            }
            break;

         case SDK_ICC_WAIT:
         default:
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
            break;
    }

    sdkDispBrushScreen();

    if (SDK_KEY_ESC == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_WAITKEY))
    {
        return FALSE;
    }
    return TRUE;
}

/*****************************************************************************
** Description :  EMV flow callback function - display candicate list
** Parameters  :  input:
                  (1)u8 ucAppNum:application number in the candidate list   
                  (2)u8 **ppheAppList: candidate list
                  
** Return      :  (1)return index of the selected application
                  (2)SDK_ESC: user cancels application selection
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 CbEmvDispCandAppList(u8 ucAppNum, u8 **ppheAppList)
{
    SDK_ICC_AIDLIST *pst_aidlist = NULL;
    u8 allpage = 0;
    u8 currpage = 0;
    s32 key = 0;
    u8 dispbuf[256] = {0};
    u8 tmp[64] = {0};
    u8 len = 0;
    u8 i = 0, j = 0, selectindex = 0;

    Trace("emv", "-->CbEmvDispCandAppList()");

    allpage = (ucAppNum + 3) / 4;

    for (i = 0, j = 0; i < ucAppNum; i++)
    {
        pst_aidlist = (SDK_ICC_AIDLIST *)(*(ppheAppList + i));
        memset(tmp, 0, sizeof(tmp));

        if (0 != pst_aidlist->ucAidLen)
        {
            sdkAscToBcd(tmp, pst_aidlist->asAid, pst_aidlist->ucAidLen);

            if (0 == memcmp(tmp, "\xA0\x00\x00\x03\x33", 5))
            {
                j++;
                selectindex = i + 1;
            }
        }
    }

    if (1 == j)
    {
        return selectindex;
    }
    DispSaveScreen();
    sdkDispClearScreen();
    sdkDispFillRowRam(SDK_DISP_LINE1, 0, STR_INFO_SELECT_APP, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    while (1)
    {
        memset(dispbuf, 0, sizeof(dispbuf));
        memset(tmp, 0, sizeof(tmp));

        for (i = 0; i < 4; i++)
        {
            if (currpage * 4 + i + 1 > ucAppNum)
            {
                break;
            }
            tmp[0] = i + '1';
            tmp[1] = '.';

            strcat(dispbuf, tmp);
            pst_aidlist = (SDK_ICC_AIDLIST *)(*(ppheAppList + currpage * 4 + i));

            if (1 == pst_aidlist->ucLocalName)     // Merchant perferred name.
            {
                len = pst_aidlist->ucAppLocalNameLen;

                if (len > sizeof(pst_aidlist->asAppLocalName))
                {
                    len = sizeof(pst_aidlist->asAppLocalName);
                }
                strncat(dispbuf, pst_aidlist->asAppLocalName, len);
            }
            else if (0 != pst_aidlist->ucPreferNameLen && 0x01 == pst_aidlist->ucIcti)     //Preferred name in card
            {
                len = pst_aidlist->ucPreferNameLen;

                if (len > sizeof(pst_aidlist->asPreferName))
                {
                    len = sizeof(pst_aidlist->asPreferName);
                }
                strncat(dispbuf, pst_aidlist->asPreferName, len);
            }
            else if (0 != pst_aidlist->ucAppLabelLen)     //Label in card
            {
                len = pst_aidlist->ucAppLabelLen;

                if (len > sizeof(pst_aidlist->asAppLabel))
                {
                    len = sizeof(pst_aidlist->asAppLabel);
                }
                strncat(dispbuf, pst_aidlist->asAppLabel, len);
            }
            else        //others display AID
            {
                len = pst_aidlist->ucAidLen;
                strncat(dispbuf, pst_aidlist->asAid, len);
            }
            dispbuf[strlen(dispbuf)] = '\n';
        }

        sdkDispLabel(SDK_DISP_LINE2, dispbuf, SDK_DISP_LEFT_DEFAULT);
        key = sdkKbWaitKey(SDK_KEY_MASK_1 | SDK_KEY_MASK_2 | SDK_KEY_MASK_3 | SDK_KEY_MASK_4 |
                           SDK_KEY_MASK_UP | SDK_KEY_MASK_DOWN | SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);

        switch (key)
        {
             case SDK_KEY_ENTER:
             case SDK_KEY_DOWN:
                if (currpage + 1 < allpage)
                {
                    currpage++; 
                }
                break;

             case SDK_KEY_UP:
                if (currpage > 0)
                {
                    currpage--;
                }
                break;

             case SDK_KEY_1:
             case SDK_KEY_2:
             case SDK_KEY_3:
             case SDK_KEY_4:
                DispRestoreScreen();
                DispClearContent();
                sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
                sdkDispBrushScreen();
                return (key - '0') + currpage * 4;
                break;

             case SDK_KEY_ESC:
             default:
                return SDK_ESC;
                break;
        }
    }
}

/*****************************************************************************
** Description :  EMV flow callback function - re-init EMV parameters
** Parameters  :  None 
** Return      :  None 
** Author      :  wenmin   2016-10-18 
** Remarks     :  This callback function is provided to user to re-init the
                  EMV parameters which are initialized by the EMV kernel. e.g.
                  The terminal capabilities(9F33) initialized in the EMV kernel
                  is "E0B0C8". If it doesn't meet your requirement, you can reset
                  in this function.
*****************************************************************************/
void CbEmvReinitParam(void)
{
    u8 tmp[64];
    u8 cashback_amt[6];

    /* Terminal Capabilities */
    sdkIccConfigTLV("\x9F\x33", "\xE0\xB0\xC8", 3);

    /* country code */
    memset(tmp, 0, sizeof(tmp));
    sdkAscToBcdR(tmp, gstAppSysCfg.stTermInfo.asCountryCode, 2);
    sdkIccConfigTLV("\x9F\x1A", tmp, 2);

    /* currency code */
    memset(tmp, 0, sizeof(tmp));
    sdkAscToBcdR(tmp, gstAppSysCfg.stTermInfo.asCurrencyCode, 2);
    sdkIccConfigTLV("\x5F\x2A", tmp, 2);

    /* transaction type */
    if (TRANSID_BALANCE == gstTransData.stTransLog.eTransID)
    {
        sdkIccConfigTLV("\x9C", "\x31", 1);
    }
    else if (TRANSID_VOID == gstTransData.stTransLog.eTransID)
    {
        sdkIccConfigTLV("\x9C", "\x17", 1);
    }
    else
    {
        sdkIccConfigTLV("\x9C", "\x00", 1);
    }
    /* Transaction Sequence Counter */
    sdkAscToBcdR(tmp, gstAppSysCfg.stTransParam.asTraceNO, 4);
    sdkIccConfigTLV("\x9f\x41", tmp, 4);

    /* Terminal Application Version Number */
    sdkIccConfigTLV("\x9F\x09", "\x00\x30", 2);

    /* other amount(cashback amount) */
    memset(cashback_amt, 0, sizeof(cashback_amt));
    memset(tmp, 0, sizeof(tmp));
    sdkAscToBcd(cashback_amt, gstTransData.stTransLog.stMsgInfo.asCashbackAmount, 12);

    if (0 != memcmp(cashback_amt, tmp, 6))
    {
        sdkIccConfigTLV("\x9F\x03", cashback_amt, 6);
    }
}
/*****************************************************************************
** Description :  EMV flow callback function - re-init contactless parameters
** Parameters  :  None 
** Return      :  None 
** Author      :  Steven 2016-11-07 
** Remarks     :  This callback function is provided to user to re-init/configurate
                  some CTLS parameters which will be used during the CTLS transaction. 
                  e.g. The TRM(9F1D) may be used in a PayPass transaction. And 
                  the transaction type(9C) may be different according to different
                  transaction and card type(payWave or PayPass).
*****************************************************************************/
void CbEmvReinitCtlsParam(void)
{
    u8 tmp[64];
    u8 cashback_amt[6];
    s32 len = 0;

    /* Terminal Risk Management Data(for PayPass) */
    if (SDK_OK != sdkIccContactLessConfigTLV("\x9F\x1D", gheTRMData, 8))
    {
        Assert(0);
    }
    memset(tmp, 0, sizeof(tmp));
    sdkIccReadTLV("\x9F\x1D", tmp, &len);
    TraceHex("emv", "paypass 9F1D", tmp, len);

    /* reinit parameters according to different transactions */
    switch(gstTransData.stTransLog.eTransID)
    {
        case TRANSID_SALE:
            memset(tmp, 0, sizeof(tmp));
            memset(cashback_amt, 0, sizeof(cashback_amt));
            Trace("emv", "cashback amount = %s\r\n", gstTransData.stTransLog.stMsgInfo.asCashbackAmount);
            sdkAscToBcdR(cashback_amt, gstTransData.stTransLog.stMsgInfo.asCashbackAmount, 6);

            if (0 < memcmp(cashback_amt, tmp, 6)) //cashback amount > 0
            {
                sdkIccContactLessConfigTLV("\x9F\x03", cashback_amt, 6);    //other amount(cashback amount)
                sdkIccContactLessConfigTLV("\x9C", "\x09", 1);      //Transaction Type(cashback)
            }
            else
            {
                sdkIccContactLessConfigTLV("\x9C", "\x00", 1);
            }
            break;

        case TRANSID_VOID:
            sdkIccContactLessConfigTLV("\x9C", "\x17", 1);
            break;

        default:
            sdkIccContactLessConfigTLV("\x9C", "\x00", 1);
            break;
    }
}
/*****************************************************************************
** Description :  EMV flow callback function - remove card
** Parameters  :  None
** Return      :  (1)SDK_OK: exit normally

** Author      :  Steven 2016-10-20
** Remarks     :  The callback function is to prompt cardholder to take his/her
                  card away safely rather than holding the card in the RF field 
                  all the time.
*****************************************************************************/
s32 CbEmvCltsRemoveCard(void)
{
    EmvLedReadCardOk();     //read card complete
    return SDK_OK;
}

/*****************************************************************************
** Description :  EMV flow callback function - Input online/offline PIN
** Parameters  :  input:
                  (1)const u8 *pasTransAmount: transaction amount displayed on
                                            external PINPAD
                  (2)u8 ucRemainPinTries: remaining PIN tries for offline PIN
                  (3)SDK_PED_PIN_MODE ePinMode: PIN mode
                  (4)u8 ucDispLine: the line to display the masked PIN
                  
                  output:
                  (1)u8 *phePin: 8-byte PIN ciphertext for online PIN or 8-byte 
                  plaintext foroffline PIN
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error
                  (2)SDK_OK : input success
                  (3)SDK_ERR : input fail
                  
** Author      :  wenmin   2016-10-18
** Remarks     :
*****************************************************************************/
s32 CbEmvInputPin(const u8 *pasTransAmount, u8 ucRemainPinTries, u8 ePinMode, u8 *phePin)
{
    u8 pwd[13] = {0};
    u8 row;
    s32 ret;
    s32 pinlen = 0;

    Trace("emv", "-->CbEmvInputPin()");

    // Display input password
    ret = DispInputPin(&row, DISPAMOUNT_NORNAL, pasTransAmount, ePinMode, ucRemainPinTries);

    if (SDK_OK != ret)
    {
        return ret;
    }
    // Get password
    ret = EmvInputPin(pwd, TRUE, pasTransAmount, ePinMode, row);

    if (SDK_OK == ret)
    {
        pinlen = pwd[0];

        if (pinlen > 12)
        {
            pinlen = 12;
        }
        TraceHex("emv", "pwd", pwd, pinlen + 1);

        if (NULL != phePin)
        {
            memcpy(phePin, pwd, pinlen + 1);
            TraceHex("emv", "phePin", phePin, pinlen + 1);
        }

        if (SDK_PED_IC_OFFLINE_PIN != ePinMode)
        {
            memcpy(gstTransData.hePIN, pwd, pinlen + 1);
            TraceHex("emv", "gstTransData.hePIN", gstTransData.hePIN, pinlen + 1);
        }
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
    }
    return ret;
}

/*****************************************************************************
** Description :  Get result after performing the EMV mandatory flow. 
** Parameters  :  input:
                  (1)SDK_EMV_RLT eEmvRet: return code(normal/error) returned by 
                                          EMV kernel.
                                          
** Return      :  see also enum "E_ICCRET"
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
E_ICCRET EmvGetReadCardResult(SDK_EMV_RLT eEmvRet)
{
    E_ICCRET icc_ret = ICCRET_TRANS_CANCEL;

    switch (eEmvRet)
    {
         case SDK_OK:                    //transaction proceeds normally
            icc_ret = ICCRET_OK;
            break;

         case SDK_UsePbocErr:           //switch to contact interface
            icc_ret = ICCRET_CTLS_SWITCH;
            break;

         case SDK_AppTimeOutErr:        //time out of response of APDU, need to restart discovry processing
            icc_ret = ICCRET_DISCOVERY;
            break;

         case SDK_NoAppSelErr:
         case SDK_TransOfflineDeclineErr: //other errors that cause transaction aborts exceptionally
            icc_ret = ICCRET_CTLS_FALLBACK;
            break;

         case SDK_OfflineDecline:        //offline declined
         case SDK_QpbocDDAAuthFail:
         case SDK_QpbocReadLastLogErr:
            icc_ret = ICCRET_OFFLINE_DECLINE;
            break;

         case SDK_TransOnlineDeclineErr: //online declined
            icc_ret = ICCRET_ONLINE_DECLINE;
            break;

         case SDK_NeedMagCardErr:        //fallback
            icc_ret = ICCRET_FALLBACK;
            break;

         case SDK_CancelTransErr:        //transaction cancelled
            icc_ret = ICCRET_TRANS_CANCEL;
            break;

         case SDK_TransOnlineApprove:    // Online approved
         case SDK_TransOK_ARPCErr:       // APRC error but transaction is approved
            icc_ret = ICCRET_ONLINE_APPROVE;
            break;

         case SDK_OnlineWait:            //transactions needs to go online
            icc_ret = ICCRET_ONLINE_WAIT; 
            break;

         case SDK_NeedReversal:          //need reversal
            icc_ret = ICCRET_REVERSAL; 
            break;

         case SDK_DispLog:               //display log
         case SDK_ReadLogEnd:            //read to the end of the log
            icc_ret = ICCRET_OK;
            break;

         case SDK_TransOfflineApprove:   // offline approved
         case SDK_OfflineApprove:
            icc_ret = ICCRET_OFFLINE_APPROVE;
            break;

         case SDK_IccEasyFlow:           // simplified EMV flow
            icc_ret = ICCRET_EASYFLOW;
            break;

         default:
            icc_ret = ICCRET_ERR;
            break;
    }

    return icc_ret;
}

/*****************************************************************************
** Description :  Input cardholder PIN
** Parameters  :  input:
                  (1)bool bIsWithPan: whether use PAN for encryption 
                  (2)const u8 *pasTransAmount: transaction amount displayed on
                                               external PINPAD
                  (3)SDK_PED_PIN_MODE ePinMode: PIN mode
                  (4)u8 ucDispLine: the line to display the masked PIN
                  
                  output:
                  (1)u8 *phePin: 8-byte PIN ciphertext for online PIN or 8-byte 
                                 plaintext foroffline PIN
                                 
** Return      :  (1)SDK_OK : input success
                  (2)SDK_ERR : input fail

** Author      :  wenmin   2016-10-18 
** Remarks     :  If terminal should support online PIN, the parameter "TermPinCap"
                  in the related AID structure "SDK_ICC_EmvSysIni_STRUCT" be set as
                  "TRUE" or value "1".
*****************************************************************************/
s32 EmvInputPin(u8 *phePin, bool bIsWithPan, const u8 *pasTransAmount, SDK_PED_PIN_MODE ePinMode, u8 ucDispLine)
{
    SDK_PED_PIN_CFG st_pincfg;
    u8 tmp[32] = {0};
    s32 ret;
    u8 amt[6] = {0};
    ST_CARDINFO *pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    u8 ksn_len;
    
    sdkAscToBcdR(amt, pasTransAmount, 6);

    memset(&st_pincfg, 0, sizeof(SDK_PED_PIN_CFG));
    st_pincfg.ePinMode = ePinMode;
    st_pincfg.ucRow = ucDispLine;
    st_pincfg.iTimeOut = TMR_OPERATE;

    if(gstAppSysCfg.stSecureKey.bIsUseDUKPT)
    {
        st_pincfg.eKeyType = SDK_PED_DES_DUKPT;
        st_pincfg.ucTpkIndex = 0;
    }
    else
    {
        st_pincfg.eKeyType = gstAppSysCfg.stSecureKey.bIsTripleDES ? SDK_PED_DES_TRIPLE : SDK_PED_DES_SINGLE;
        st_pincfg.ucTpkIndex = gstAppSysCfg.stSecureKey.uiTpkIndex;
    }

    // Check if PAN is involved in PIN encryption
    if (bIsWithPan)
    {
        if (SDK_ICC_ICC == pst_cardinfo->stCardParam.ucCardMode
            || SDK_ICC_RF == pst_cardinfo->stCardParam.ucCardMode)
        {
            if (0 == pst_cardinfo->stCardData.ucCardLen
                && 0 == pst_cardinfo->stCardData.ucTrack2Len
                && 0 == pst_cardinfo->stCardData.ucTrack3Len)
            {
                TrnGetIccMagData(&pst_cardinfo->stCardData);
            }
        }
        memset(tmp, 0, sizeof(tmp));
        ret = TrnGetMagCardNo(&pst_cardinfo->stCardData, tmp);
        Trace("emv", "TrnGetMagCardNo=[%d]\r\n", ret);

        if (SDK_ERR == ret || SDK_PARA_ERR == ret)
        {
            sdkPEDCancel();

            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_ENCRYPTION_ERROR, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
            return SDK_ERR;
        }
        sdkAscToBcd(st_pincfg.hePan + 2, tmp + strlen(tmp) - 13, 12);
    }
    Trace("emv", "ePinMode=%02x,eKeyType=%02x,ucTpkIndex=%02x\r\n", st_pincfg.ePinMode, st_pincfg.eKeyType, st_pincfg.ucTpkIndex);
    TraceHex("emv", "hePan", st_pincfg.hePan, 8);

    while (1)
    {
        st_pincfg.iTimeOut = 30000;
        
        if(gstAppSysCfg.stSecureKey.bIsUseDUKPT)
        {
            ret = sdkPEDDukptGetPin(SDK_PED_DUKPT_GET_PIN_RELEASE, 0, &st_pincfg, 4, 12, phePin, gstTransData.heKSN, &ksn_len, TMR_OPERATE);
        }
        else
        {
            ret = sdkPEDInputPIN(&st_pincfg, amt, phePin);     // Input and encrypt PIN
        }
        TraceHex("emv", "phePin", phePin, 9);
        Trace("emv", "sdkPEDInputPIN=[%d]\r\n", ret);

        if (SDK_OK != ret)
        {
            if (SDK_PED_PIN_FORMAT_ERR == ret)
            {
                // Password format error
                continue;
            }
            sdkPEDCancel();

            if (SDK_PED_NOPIN == ret)
            {
                // No password
                break;
            }

            if (SDK_ESC != ret && SDK_TIME_OUT != ret)
            {
                DispClearContent();
                sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_ENCRYPTION_ERROR, SDK_DISP_DEFAULT);
                sdkDispBrushScreen();
                sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
            }
            else
            {
                TrnSetStatus(ret);
            }
            return SDK_ERR;
        }
        break;
    }

    if(SDK_OK == ret && gstAppSysCfg.stSecureKey.bIsUseDUKPT)
    {
        phePin[0] = 8;
    }

    return SDK_OK;
}
/*****************************************************************************
** Description :  check response code                  
** Parameters  :  input:
                  (1)const u8 *pasRespCode: response code returned by host
                  
** Return      :  (1)TRUE : transaction is authorized
                  (2)FALSE: transaction is declined
                  
** Author      :  Steven 2016-10-20 
** Remarks     :  Other response codes besides "00" may also means transaction
                  is successful.
*****************************************************************************/
bool EmvCheckRespCode(const u8 *pasRespCode)
{
    if (0 == memcmp(pasRespCode, "00", 2)
        || 0 == memcmp(pasRespCode, "11", 2)
        || 0 == memcmp(pasRespCode, "A2", 2)
        || 0 == memcmp(pasRespCode, "A4", 2)
        || 0 == memcmp(pasRespCode, "A5", 2)
        || 0 == memcmp(pasRespCode, "A6", 2)
        )
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
** Description :  Import response code, issuer authentication data,issuer-to-card
                  script to EMV library.                 
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pst8583Packet: ISO packet
                  
** Return      :  (1)SDK_PARA_ERR: parameter error
                  (2)SDK_OK: success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  This function must be called before performing subsequent transaction
                  EMV flow after going online, i.e. calling "EmvOptTransFlowOnlineProcess".
*****************************************************************************/
s32 EmvOptImportRespData(SDK_8583_ST8583 *pst8583Packet)
{
    u8 code[3], buf[256];
    u8 iss_data[16], script71[128], script72[128], script[300];
    s32 iss_data_len = 0, script71_len = 0, script72_len = 0, script_len = 0;
    s32 len = 0;

    if (NULL == pst8583Packet)
    {
        Assert(0);
        return SDK_PARA_ERR;
    }
    /* response code */
    memset(code, 0, sizeof(code));
    len = IsoGetField(pst8583Packet, 39, code, 3);

    if (len > 0)
    {
        if (EmvCheckRespCode(code))
        {
            memset(code, 0, sizeof(code));
            strcpy(code, "00");
        }
    }
    Trace("emv", "code=%s\r\n", code);

    /* Issuer Authentication Data */
    memset(buf, 0, sizeof(buf));
    len = IsoGetField(pst8583Packet, 55, buf, sizeof(buf));

    if (len > 0)
    {
        memset(iss_data, 0, sizeof(iss_data));

        if(SDK_OK == EmvParseIccTlv(buf, len, "\x91", iss_data, &iss_data_len))
        {
            if(iss_data_len > 16)
            {
                iss_data_len = 0;
                memset(iss_data, 0, sizeof(iss_data));
            }
            TraceHex("emv", "Iss Data", iss_data, iss_data_len);
            sdkIccConfigTLV("\x91", iss_data, iss_data_len);
        }
        /* Issuer Script 71 */
        memset(script71, 0, sizeof(script71));

        if(SDK_OK == EmvParseIccTlv(buf, len, "\x71", script71, &script71_len) && script71_len < 128)
        {
            sdkIccConfigTLV("\x71", script71, script71_len);
            script[script_len++] = 0x71;
            script[script_len++] = script71_len;
            memcpy(script + script_len, script71, script71_len);
            script_len += script71_len;
            TraceHex("emv", "scrpit 71", script71, script71_len);
        }
        /* Issuer Script 72 */
        memset(script72, 0, sizeof(script72));

        if(SDK_OK == EmvParseIccTlv(buf, len, "\x72", script72, &script72_len) && script72_len < 128)
        {
            sdkIccConfigTLV("\x72", script72, script72_len);
            script[script_len++] = 0x72;
            script[script_len++] = script72_len;
            memcpy(script + script_len, script72, script72_len);
            script_len += script72_len;
            TraceHex("emv", "script 72", script72, script72_len);
        }
    }
    /* import data */
    sdkIccGetOnlineData(TRUE, code, iss_data, iss_data_len, script, script_len);

    return SDK_OK;
}

/*****************************************************************************
** Description :  To configure the EMV transaction parameters.
** Parameters  :  input:
                  (1)ST_TRANSDATA *pstTransData: current transaction data

                  output:
                  (1)SDK_ICC_TRADE_PARAM *pstIccTradeParam: global configuration 
                     of current EMV transaction.
                     
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  To ensure that the EMV transaction is performed as expected,
                  please check carefully whether the configuration is correct,
                  especially for the private configuration of each kind of 
                  transaction.
*****************************************************************************/
void EmvConfigTransParam(ST_TRANSDATA *pstTransData, SDK_ICC_TRADE_PARAM *pstIccTradeParam)
{
    E_TRANS_ID trans_id;      //transaction ID

    if (NULL == pstIccTradeParam)
    {
        Assert(0);
        return;
    }

    /* public configuration for each kind of transaction */
    pstIccTradeParam->pasTradeAmount = pstTransData->stTransLog.stMsgInfo.asAmount;  //transaction amount(SALE amount only or SALE+CASHBACK amount)
    pstIccTradeParam->bIsForceOnline = FALSE;   //TRUE: go online every time, FALSE: may be offline or online
    pstIccTradeParam->bIsFallback = FALSE;      //TRUE: support fallback, FALSE: fallback not supported
    pstIccTradeParam->eFlowMode = SDK_ICC_EASY_FLOW; //ALL_FLOW: full EMV flow, EASY_FLOW: partial EMV flow which will return after PAN is read by READ RECORD cmd

    pstIccTradeParam->bIsSupportQPBOC = FALSE;
    pstIccTradeParam->bIsSupportCLPBOC = FALSE;     //ignore
    pstIccTradeParam->bIsSupportEc = FALSE;         //ignore
    pstIccTradeParam->bIsPromptChooseEc = FALSE;    //ignore
    pstIccTradeParam->bIsDefaultEc = FALSE;         //ignore
    memset(&pstIccTradeParam->stFixedAid, 0, sizeof(SDK_ICC_FIXED_AID)); // whether to select the fixed AID

    pstIccTradeParam->InputAmount = NULL;
    pstIccTradeParam->DispReselectApp = NULL;
    pstIccTradeParam->DispCardOut = NULL;
    pstIccTradeParam->VerifyCardNo = NULL;
    pstIccTradeParam->InputPWD = NULL;
    pstIccTradeParam->DispOnlineRandNum = NULL;     //ignore
    pstIccTradeParam->DispChooseEC = NULL;          //ignore
    pstIccTradeParam->DispPromptData = CbEmvDispPrompts;
    pstIccTradeParam->DispCandAppList = CbEmvDispCandAppList;
    pstIccTradeParam->UserIccTransInit = CbEmvReinitParam;

    trans_id = pstTransData->stTransLog.eTransID;   

    switch (trans_id)
    {
    	/* private configuration for SALE */
        case TRANSID_SALE: //sale
            pstIccTradeParam->bIsForceOnline = FALSE;
            pstIccTradeParam->bIsFallback = TRUE;
            pstIccTradeParam->bIsSupportQPBOC = TRUE;
            pstIccTradeParam->eFlowMode = SDK_ICC_ALL_FLOW;
            pstIccTradeParam->InputAmount = CbEmvInputAmount;
            pstIccTradeParam->VerifyCardNo = CbEmvDispCardNo;
            pstIccTradeParam->InputPWD = CbEmvInputPin;
            pstIccTradeParam->DispCardOut = CbEmvCltsRemoveCard;
            break;
            
    	/* private configuration for QUERY BALANCE */
        case TRANSID_BALANCE:
            pstIccTradeParam->bIsForceOnline = TRUE;
            pstIccTradeParam->bIsFallback = TRUE;
            pstIccTradeParam->eFlowMode = SDK_ICC_ALL_FLOW;
            pstIccTradeParam->VerifyCardNo = CbEmvDispCardNo;
            pstIccTradeParam->InputPWD = CbEmvInputPin;

    	/* private configuration for VOID & REFUND*/
        case TRANSID_VOID:
        case TRANSID_REFUND:
            pstIccTradeParam->bIsForceOnline = TRUE;
            pstIccTradeParam->bIsFallback = TRUE;
            pstIccTradeParam->bIsSupportQPBOC = TRUE;
            pstIccTradeParam->VerifyCardNo = CbEmvDispCardNo;
            break;

         default:
            break;
    }
}

/*****************************************************************************
** Description :  Initialize CTLS paypass/paywave parameters
** Parameters  :  input & output:
                  (1)SDK_ICC_TRADE_PARAM *pstTradeParam: global configuration of 
                     current EMV transaction.
                     
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  This function must be called before initiating a CTLS transaction.
*****************************************************************************/
void EmvInitPayPassWave(SDK_ICC_TRADE_PARAM *pstTradeParam)
{   
    if(gstAppSysCfg.stTransParam.bIsCTLS)
    {
        memset(&_gstSdkIccExparam3, 0, sizeof(SDK_ICC_EXPARAM3));
        _gstSdkIccExparam3.bIsPayPassWaveSupport = 1;
        _gstSdkIccExparam3.bIsPayPassWaveTradeOnlineOnlySet = 0;
        _gstSdkIccExparam3.bIsPayPassWaveTradeOutReaderIsBeepSet = 0;
        _gstSdkIccExparam3.CurTradeSupportCardTypeSet = 0x07;           //BIT3:paypass, BIT2:paywave, BIT1:qPBOC
        _gstSdkIccExparam3.CurTradeTypeSet = 0x00;
        pstTradeParam->pheReserved3 = &_gstSdkIccExparam3;
    }
}

/*****************************************************************************
** Descriptions:	Read the configuration of the contactless reader for paypass/paywave.
** Parameters:          void
** Returned value:
** Created By:		guozexian  20160103
** Remarks:
*****************************************************************************/
s32 EmvReadPaypassPaywaveCfgIni(void)
{
    SDK_INI_HAND pHand = NULL;
    s32 ret = SDK_OK;
    u8 temp[256] = {0};
    u8 section_name[64] = {0};
    u8 param[256];
    s32 param_len = 0, section_num = 0;
    u8 i = 0;
    SDK_ICC_PAYWAVE_DRL st_drl_param;

    if (false == sdkAccessFile(PAYPASSPAYWAVE_CFG_INI))
    {
        sdkDispPromptBox(false, 0, "paypasspaywave.ini HAVE NOT FUND");
        return SDK_ESC;
    }
    pHand = sdkIniLoad(PAYPASSPAYWAVE_CFG_INI);

    if (NULL == pHand)
    {
        Assert(0);
        return SDK_ERR;
    }
    section_num = sdkIniGetSectionNum(pHand);

    if (2 > section_num)
    {
        Trace("gzx", "section number err!\r\n");
        return SDK_ERR;
    }
    memset(section_name, 0, sizeof(section_name));
    sdkIniGetSectionName(pHand, 0, section_name);

    memset(param, 0, sizeof(param));
    param_len = 0;

    //9F66_TTQ
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "9F66_TTQ", temp);

    if (ret > 0)
    {
        if (ret != 8)
        {
            DispEMVErr(section_name, "9F66_TTQ");
            return SDK_ERR;
        }
        memcpy(param, "\x9F\x66", 2);
        param_len += 2;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //9F33_TERM_CAP
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "9F33_TERM_CAP", temp);

    if (ret > 0)
    {
        if (ret != 6)
        {
            DispEMVErr(section_name, "9F33_TERM_CAP");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\x9F\x33", 2);
        param_len += 2;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //9F40_ADD_TERM_CAP
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "9F40_ADD_TERM_CAP", temp);

    if (ret > 0)
    {
        if (ret != 10)
        {
            DispEMVErr(section_name, "9F40_ADD_TERM_CAP");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\x9F\x40", 2);
        param_len += 2;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF03
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF03", temp);

    if (ret > 0)
    {
        if (ret != 4)
        {
            DispEMVErr(section_name, "DF03");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x03", 2);
        param_len += 2;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    TraceHex("gzx", "PayWave config", param, param_len);
    ret = sdkIccInitPayWaveParam(param, param_len);
    Trace("gzx", "sdkIccInitPayWaveParam ret=%d \r\n", ret);

    if (ret != SDK_OK)
    {
        Assert(0);
        return ret;
    }
    memset(param, 0, sizeof(param));
    param_len = 0;
    memset(section_name, 0, sizeof(section_name));
    sdkIniGetSectionName(pHand, 1, section_name);

    //9F33_TERM_CAP
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "9F33_TERM_CAP", temp);

    if (ret > 0)
    {
        if (ret != 6)
        {
            DispEMVErr(section_name, "9F33_TERM_CAP");
            return SDK_ERR;
        }
        memcpy(param, "\x9F\x33", 2);
        param_len += 2;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //9F40_ADD_TERM_CAP
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "9F40_ADD_TERM_CAP", temp);

    if (ret > 0)
    {
        if (ret != 10)
        {
            DispEMVErr(section_name, "9F40_ADD_TERM_CAP");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\x9F\x40", 2);
        param_len += 2;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //9F6D_MAG_APP_VER
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "9F6D_MAG_APP_VER", temp);

    if (ret > 0)
    {
        if (ret != 4)
        {
            DispEMVErr(section_name, "9F6D_MAG_APP_VER");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\x9F\x6D", 2);
        param_len += 2;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF811B_KERNEL_CONFIG
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF811B_KERNEL_CONFIG", temp);
	TraceHex("emv","DF811B_KERNEL_CONFIG",temp, ret);

    if (ret > 0)
    {
        if (ret != 2)
        {
            DispEMVErr(section_name, "DF811B_KERNEL_CONFIG");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x1B", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF8125_RCTL
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF8125_RCTL", temp);

    if (ret > 0)
    {
        if (ret != 12)
        {
            DispEMVErr(section_name, "DF8125_RCTL");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x25", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF811E_MSD_CVM
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF811E_MSD_CVM", temp);

    if (ret > 0)
    {
        if (ret != 2)
        {
            DispEMVErr(section_name, "DF811E_MSD_CVM");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x1E", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        gucMsdCVM = param[param_len];       //guozexian 20160121
        Trace("gzx", "paypass MSD CVM(DF811E) = %02x\r\n", gucMsdCVM);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF812D_MSD_NO_CVM
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF812D_MSD_NO_CVM", temp);

    if (ret > 0)
    {
        if (ret != 2)
        {
            DispEMVErr(section_name, "DF812D_MSD_NO_CVM");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x2D", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF811F_SECURE_CAP
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF811F_SECURE_CAP", temp);

    if (ret > 0)
    {
        if (ret != 2)
        {
            DispEMVErr(section_name, "DF811F_SECURE_CAP");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x1F", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF8117_CARD_DATA_INPUT_CAP
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF8117_CARD_DATA_INPUT_CAP", temp);

    if (ret > 0)
    {
        if (ret != 2)
        {
            DispEMVErr(section_name, "DF8117_CARD_DATA_INPUT_CAP");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x17", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF8118_EMV_CVM
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF8118_EMV_CVM", temp);

    if (ret > 0)
    {
        if (ret != 2)
        {
            DispEMVErr(section_name, "DF8118_EMV_CVM");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x18", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        return SDK_PARA_ERR;
    }
    //DF8119_EMV_NO_CVM
    memset(temp, 0, sizeof(temp));
    ret = sdkIniGetKeyValue(pHand, section_name, "DF8119_EMV_NO_CVM", temp);

    if (ret > 0)
    {
        if (ret != 2)
        {
            DispEMVErr(section_name, "DF8119_EMV_NO_CVM");
            return SDK_ERR;
        }
        memcpy(&param[param_len], "\xDF\x81\x19", 3);
        param_len += 3;
        param[param_len++] = ret / 2;
        sdkAscToBcd(&param[param_len], temp, ret);
        param_len += (ret / 2);
    }
    else
    {
        //return SDK_PARA_ERR;
    }
    TraceHex("gzx", "PayPass config", param, param_len);
    ret = sdkIccInitPayPassParam(param, param_len);
    Trace("gzx", "sdkIccInitPayPassParam  ret=%d \r\n", ret);

    /*=======BEGIN: guozexian 20160614  17:31 modify===========*/
    if (ret == SDK_OK)
    {
        //9F1D_TRM_DATA(for paypass)
        memset(temp, 0, sizeof(temp));
        memset(gheTRMData, 0, sizeof(gheTRMData));
        ret = sdkIniGetKeyValue(pHand, section_name, "9F1D_TRM_DATA", temp);
		TraceHex("emv","9F1D_TRM_DATA",temp, ret);
        if (ret > 0)
        {
            if (ret != 16)
            {
                DispEMVErr(section_name, "9F1D_TRM_DATA");
                return SDK_ERR;
            }
            sdkAscToBcd(gheTRMData, temp, ret);
            TraceHex("gzx", "9F1D for paypass(HEX)", gheTRMData, ret / 2);
            ret = SDK_OK;
        }
        else
        {
            ret = SDK_PARA_ERR;
        }
    }
    /*====================== END======================== */


    /*==========BEGIN: guozexian 20161116 modify==============*/
    memset(&st_drl_param, 0, sizeof(st_drl_param));     //clear DRL

    if (12 < section_num)       // maximum 10 DRL sets
    {
        section_num = 12;
    }
    section_num -= 2;

    for (i = 0; i < section_num; i++)
    {
        memset(section_name, 0, sizeof(section_name));
        sdkIniGetSectionName(pHand, i + 2, section_name);

        //App Program ID
        memset(temp, 0, sizeof(temp));
        ret = sdkIniGetKeyValue(pHand, section_name, "APP_PROG_ID", temp);

        if (0 < ret)
        {
            if (0 != (ret % 2))
            {
                DispEMVErr(section_name, "READER_CHECK_PARAM");
                return SDK_ERR;
            }
            st_drl_param.paywaveparamsets[i].AppProgIDlen = ret / 2;
            sdkAscToBcd(st_drl_param.paywaveparamsets[i].AppProgID, temp, ret);
            Trace("gzx", "[%d] set DRL", i - 1);
            TraceHex("gzx", "AppProgID", st_drl_param.paywaveparamsets[i].AppProgID, st_drl_param.paywaveparamsets[i].AppProgIDlen);
        }
        else
        {
            return SDK_PARA_ERR;
        }
        //PaywaveRCP
        memset(temp, 0, sizeof(temp));
        ret = sdkIniGetKeyValue(pHand, section_name, "READER_CHECK_PARAM", temp);

        if (0 < ret)
        {
            if (4 != ret)
            {
                DispEMVErr(section_name, "READER_CHECK_PARAM");
                return SDK_ERR;
            }
            sdkAscToBcd(st_drl_param.paywaveparamsets[i].PaywaveRCP, temp, ret);
            TraceHex("gzx", "PaywaveRCP", st_drl_param.paywaveparamsets[i].PaywaveRCP, 2);
        }
        else
        {
            return SDK_PARA_ERR;
        }
        //CTLS CVM limit
        memset(temp, 0, sizeof(temp));
        ret = sdkIniGetKeyValue(pHand, section_name, "CL_CVM_LIMIT", temp);

        if (0 < ret)
        {
            if (12 != ret)
            {
                DispEMVErr(section_name, "CL_CVM_LIMIT");
                return SDK_ERR;
            }
            sdkAscToBcd(st_drl_param.paywaveparamsets[i].PaywaveCVMLimit, temp, ret);
            TraceHex("gzx", "Paywave CVM Limit", st_drl_param.paywaveparamsets[i].PaywaveCVMLimit, 6);
        }
        else
        {
            return SDK_PARA_ERR;
        }
        //CTLS Transaction limit
        memset(temp, 0, sizeof(temp));
        ret = sdkIniGetKeyValue(pHand, section_name, "CL_TRANS_LIMIT", temp);

        if (0 < ret)
        {
            if (12 != ret)
            {
                DispEMVErr(section_name, "CL_TRANS_LIMIT");
                return SDK_ERR;
            }
            sdkAscToBcd(st_drl_param.paywaveparamsets[i].PaywaveTransLimit, temp, ret);
            TraceHex("gzx", "Paywave Trans Limit", st_drl_param.paywaveparamsets[i].PaywaveTransLimit, 6);
        }
        else
        {
            return SDK_PARA_ERR;
        }
        //CTLS floor limit
        memset(temp, 0, sizeof(temp));
        ret = sdkIniGetKeyValue(pHand, section_name, "CL_FLOOR_LIMIT", temp);

        if (0 < ret)
        {
            if (12 != ret)
            {
                DispEMVErr(section_name, "CL_FLOOR_LIMIT");
                return SDK_ERR;
            }
            sdkAscToBcd(st_drl_param.paywaveparamsets[i].PaywaveFloorLimit, temp, ret);
            TraceHex("gzx", "Paywave Floor Limit", st_drl_param.paywaveparamsets[i].PaywaveFloorLimit, 6);
        }
        else
        {
            return SDK_PARA_ERR;
        }
    }

    /*====================== END======================== */
    ret = sdkIccSetPaywaveDRL(&st_drl_param);
    Trace("gzx", "sdkIccSetPaywaveDRL  ret=%d \r\n", ret);

    return ret;
}

/*****************************************************************************
** Description :  The mandatory EMV transaction flow details including 
                  contact & contactless chip card processing.
** Parameters  :  input:
                  (1)SDK_ICC_TRADE_PARAM * pstIccTradeParam: global configuration of 
                                                             current EMV transaction. 
                  (2)SDK_ICC_PARAM * pstIccParam: card configuration 
                  
** Return      :  (1)SDK_PARA_ERR: parameter error
                  (2)SDK_ERR: not contact or contactless transaction
                  (3)SDK_ICC_RESET_ERR: reset card failed
                  (4)for other return codes, see also enum "SDK_EMV_RLT"
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  In most of the cases, no need to modify the function at all, 
                  otherwise it may cause some unexpected errors. The only thing
                  user may need to change is about the callback function 
                  "CbEmvReinitCtlsParam", in which there are some different
                  processing of different contactless cards,i.e. paypass or paywave.
*****************************************************************************/
s32 EmvMandatoryTransFlowDetail(SDK_ICC_TRADE_PARAM * pstIccTradeParam, SDK_ICC_PARAM * pstIccParam)
{
    u8 buf[512] = {0};
    s32 len = 0, ret = 0;
    SDK_ICC_FIXED_AID st_fixed_aid;
    bool b_support_ctls = 0;
    u8 cur_support_cardtype = 0;
    u8 e_card_type = 0;

    if((NULL == pstIccTradeParam) || (NULL == pstIccParam))
    {
        return SDK_PARA_ERR;
    }

    if((SDK_ICC_RF != pstIccParam->ucCardMode) && (SDK_ICC_ICC != pstIccParam->ucCardMode)) 
    {
        return SDK_ERR;
    }

    /* payWave/PayPass/qPBOC transaction flow on external CTLS card reader(G101 PINPAD) */
    if(0x02 == pstIccParam->ucCLType)
    {
        return sdkIccDealQReaderTrade(pstIccTradeParam);
    }

    /* EMV/CTLS transaction initialization */
    if(SDK_OK != sdkIccTransInit(pstIccTradeParam))
    {
        Trace("emv", "sdkIccTransInit error!!!\r\n");
        return SDK_PARA_ERR;
    }

    /* check whether the CTLS lib exists and the CTLS parameters in "pstIccParam->pheReserved3" are configured correctly */
    if(SDK_ICC_RF == pstIccParam->ucCardMode)
    {
        if(NULL != pstIccTradeParam->pheReserved3)
        {
            sdkIccPayPassWaveCurTradeSupportCardTypeGet(&cur_support_cardtype);

            Trace("emv", "ctls lib exist = %d, pheReserved3->bIsPayPassWaveSupport = %d, pheReserved3->CurTradeSupportCardTypeSet = 0x%02X, support paypass/paywave = %d, cur_support_cardtype = 0x%02X\r\n",
                  sdkIccEmvContactLessLibIsExist(),
                  ((SDK_ICC_EXPARAM3*)(pstIccTradeParam->pheReserved3))->bIsPayPassWaveSupport,
                  ((SDK_ICC_EXPARAM3*)(pstIccTradeParam->pheReserved3))->CurTradeSupportCardTypeSet,
                  sdkIccIsSupportPayPassWave(),
                  cur_support_cardtype);
        }
        
        if(!sdkIccEmvContactLessLibIsExist())
        {
            b_support_ctls = 0;
            sdkIccPayPassWaveSupportSet(0x00);
            sdkIccPayPassWaveSupportCardTypeSet(0x80);
        }
        else if((sdkIccIsSupportPayPassWave()) && ((CTLS_PAYWAVE & cur_support_cardtype) || (CTLS_PAYPASS & cur_support_cardtype)))
        {
            ret = sdkIccEmvContactLessCfgt(pstIccTradeParam, pstIccParam);

            if( SDK_FUN_NULL == ret || FALSE == ret || 2 == ret )
            {
                Trace("emv", "app do not config contactless param!!! ret=%d\r\npstIccParam->pheReserved3 == NULL ?? \r\n", ret);
                b_support_ctls = 0;

                /* clear payWave/PayPass flags */
                sdkIccPayPassWaveSupportSet(0x00);
                sdkIccPayPassWaveSupportCardTypeSet(0x80);
            }
            else if(TRUE == ret)
            {
                b_support_ctls = 1;
            }
            else
            {
                return SDK_PARA_ERR;
            }
        }
    }
    /* reset ICC */
    ret = sdkIccResetIcc(pstIccParam, buf, &len);

    Trace("emv", "sdkIccResetIcc==%d\r\n", ret);

    if(SDK_OK != ret)
    {
        if(SDK_BrushOnDealingRF == ret)
        {
            Trace("emv", "swiping card during reading CTLS card!\r\n", ret);
            return ret;
        }

        if(pstIccTradeParam->bIsFallback && SDK_ICC_ICC == pstIccParam->ucCardMode)
        {
            Trace("emv", "ICC fallback!\r\n", ret);
            return SDK_NeedMagCardErr;
        }
        else
        {
            Trace("emv", "ICC reset failed!\r\n", ret);
            return SDK_ICC_RESET_ERR;
        }
    }
    /********** BEGIN: payWave/PayPass transaction flow on internal CTLS card reader **********/
    cur_support_cardtype = 0;
    sdkIccPayPassWaveCurTradeSupportCardTypeGet(&cur_support_cardtype);

    Trace("emv", "sdkIccIsSupportPayPassWave = %d\r\n", sdkIccIsSupportPayPassWave());
    Trace("emv", "cur_support_cardtype = %d\r\n", cur_support_cardtype);
    if((sdkIccIsSupportPayPassWave()) && ((CTLS_PAYWAVE & cur_support_cardtype) || (CTLS_PAYPASS & cur_support_cardtype)))
    {
        e_card_type = CTLS_UNKNOWN;
        sdkIccPayPassWaveSupportCardTypeSet(e_card_type);  //clear card type flag first

        if(SDK_ICC_RF == pstIccParam->ucCardMode && b_support_ctls)
        {
            ret = sdkIccContactlessEntryPoint(pstIccTradeParam, pstIccParam, &e_card_type);
            Trace("emv", "sdkIccContactlessEntryPoint = %d, card type = %d\r\n", ret, e_card_type);
            sdkIccPayPassWaveSupportCardTypeSet(e_card_type);

            if((SDK_OK == ret) && (CTLS_PAYWAVE == e_card_type || CTLS_PAYPASS == e_card_type)) //card type: 1-unionpay, 2-paywave ,4-paypass
            {
                /* reconfigurate some tags */
                gstTransData.ucCtlsCardType = e_card_type;
                pstIccTradeParam->UserIccTransInit = CbEmvReinitCtlsParam;

                sdkIccPayPassWaveSupportSet(0x01);
                ret = sdkIccContactlessTransFlow1(pstIccTradeParam, pstIccParam);
                Trace("emv", "sdkIccContactlessTransFlow1 = %d\r\n", ret);
                return ret;
            }
            else
            {
                if(SDK_OK != ret)
                {
                    sdkIccPayPassWaveSupportCardTypeSet(0x80);
                    Trace("emv", "sdkIccContactlessEntryPoint = %d\r\n", ret);
                    return ret; //quit the transaction flow
                }
                /*if comes here(ret == SDK_OK but card type is not 2 or 4), it will perform the below qPBOC transaction flow */
            }
        }
    }
    else
    {
        sdkIccPayPassWaveSupportCardTypeSet(0x80);
    }
    /********** END: payWave/PayPass transaction flow on internal CTLS card reader **********/



    /*********** BEGIN:  contact EMV transaction flow & CTLS qPBOC transaction flow ***********/
    ret = sdkIccGetAppCandidate(pstIccTradeParam, pstIccParam);     //get application candidate list
    Trace("emv", "GetAppCandidate = %d\r\n", ret);

    sdkIccPayPassWaveSupportCardTypeSet(0x80);      //not to influence the qPBOC transaction flow

    if(SDK_OK != ret)
    {
        return ret;
    }
    memcpy(&st_fixed_aid, &pstIccTradeParam->stFixedAid, sizeof(SDK_ICC_FIXED_AID));

    while(1)
    {
        /* application selection */
        ret = sdkIccGoToSelectApp(st_fixed_aid, pstIccTradeParam, pstIccParam);
        Trace("emv", "sdkIccGoToSelectApp =%d\r\n", ret);

        if(SDK_FixedAidAbsentErr == ret)       //if the app of fixed AID is not selected successfully, then rebuilt app candidate list for user to select
        {
            st_fixed_aid.bIsFixed = FALSE;
            continue;
        }
        else if(SDK_NoAppSelErr == ret)
        {
            if(pstIccTradeParam->bIsFallback)
            {
                return SDK_NeedMagCardErr;
            }
        }
        else if(SDK_OK == ret)      //select app successfully
        {
            Trace("emv", "pstIccTradeParam->eFlowMode = %d\r\n", pstIccTradeParam->eFlowMode);

            if(SDK_ICC_READLOG == pstIccTradeParam->eFlowMode)
            {
                return SDK_DispLog;
            }
            else if(SDK_ICC_EC_QUERY == pstIccTradeParam->eFlowMode)
            {
                ret = sdkIccReadECBalance(pstIccTradeParam, pstIccParam);
                Trace("emv", "sdkIccReadECBalance = %d\r\n", ret);
                return ret;
            }
            /* GPO */
            ret = sdkIccGoToInitialApp(pstIccTradeParam, pstIccParam);
            Trace("emv", "sdkIccGoToInitialApp = %d\r\n", ret);
        }

        if(SDK_AppSelectTryAgainErr == ret)
        {
            if(NULL != pstIccTradeParam->DispReselectApp)
            {
                /* callback function for prompting to reselect app  */
                ret = (*pstIccTradeParam->DispReselectApp)();
                Trace("emv", "DispReselectApp = %d\r\n", ret);

                if(SDK_OK != ret)
                {
                    return ret;
                }
            }
            /* application reselection */
            ret = sdkIccReSelectApp();
            Trace("emv", "sdkIccReSelectApp = %d\r\n", ret);

            if(SDK_NoAppSelErr == ret)     //if there is no candidate application to select, try fallback.
            {
                if(pstIccTradeParam->bIsFallback)
                {
                    Trace("emv", "no candidate app to select, try fallback.\r\n");
                    return SDK_NeedMagCardErr;
                }
            }

            if(SDK_OK != ret)
            {
                return ret;
            }
            continue;
        }

        /************* BEGIN: CUP qPBOC(NOT payWave/PayPass) on internal CTLS card reader *************/
        else if(SDK_OnlineWait == ret)         //online processing(non-pure EC account) for qPBOC
        {
            ret = sdkIccDealQpbocOnline(pstIccTradeParam, pstIccParam);
            Trace("emv", "sdkIccDealQpbocOnline = %d\r\n", ret);
            return ret;
        }
        else if(SDK_OfflineApprove == ret)        //offline approved for qPBOC
        {
            ret = sdkIccDealQpbocOffline(pstIccTradeParam, pstIccParam);
            Trace("emv", "sdkIccDealQpbocOffline = %d\r\n", ret);
            return ret;
        }
        else if(SDK_ICCQProveOffline == ret)    //recover torn transaction for qPBOC
        {
            sdkSysPlaySoundFile("emvbeepok.wav", 1);

            if(NULL != pstIccTradeParam->DispCardOut)
            {
                ret = (*pstIccTradeParam->DispCardOut)();
                Trace("emv", "DispCardOut = %d\r\n", ret);

                if(SDK_OK != ret)
                {
                    return ret;
                }
            }
            ret = sdkIccCardHolderVerf(pstIccTradeParam, pstIccParam);
            Trace("emv", "sdkIccCardHolderVerf = %d\r\n", ret);

            if(SDK_OfflineApprove != ret)
            {
                return ret;
            }
            ret = sdkIccProcessRestrict(pstIccTradeParam, pstIccParam);
            Trace("emv", "sdkIccProcessRestrict = %d\r\n", ret);

            if(SDK_AppEffectErr == ret || SDK_AppExpiredErr == ret )
            {
                return SDK_TransOfflineDeclineErr;
            }
            else if(SDK_OfflineApprove != ret)
            {
                return ret;
            }
            ret = sdkIccDataAuth(pstIccTradeParam, pstIccParam);
            Trace("emv", "sdkIccDataAuth = %d\r\n", ret);

            if(SDK_OfflineApprove == ret)
            {
                return SDK_TransOfflineApprove;
            }
            else if(SDK_OfflineDecline == ret)
            {
                return SDK_TransOfflineDeclineErr;
            }
            else
            {
                return ret;  //ODA failed, go online
            }
        }
        /************* END: CUP qPBOC(NOT payWave/PayPass) on internal CTLS card reader *************/
        else if(SDK_OK != ret)
        {
            return ret;
        }
        break;
    }

    /* the rest of contact EMV transaction flow */
    ret = sdkIccDealEmvFlow(pstIccTradeParam,  pstIccParam);
    Trace("emv", "sdkIccDealEmvFlow = %d\r\n", ret);

    return ret;
    /************END:  contact EMV transaction flow & CTLS qPBOC transaction flow ************/
}

/*****************************************************************************
** Description :  mandatory EMV transaction flow
** Parameters  :  input:
                  (1)SDK_ICC_TRADE_PARAM * pstIccTradeParam: global configuration of 
                     current EMV transaction. 
                  (2)SDK_ICC_PARAM * pstIccParam: card configuration  
                  
** Return      :  see also enum "E_ICCRET"
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
E_ICCRET EmvMandatoryTransFlow(SDK_ICC_TRADE_PARAM *pstIccTradeParam, SDK_ICC_PARAM *pstIccParam)
{
    s32 emv_ret = 0;
    E_ICCRET e_iccret = ICCRET_OK;
    //s32 key = 0;
    u32 tmr_id = 0;

    if (pstIccParam->ucCardMode & SDK_ICC_RF)
    {
        EmvLedReadCard();
    }
    
    emv_ret = EmvMandatoryTransFlowDetail(pstIccTradeParam, pstIccParam);

    /* CDCVM */
    if( SDK_ICC_PLS_SEE_PHONE == emv_ret )
    {
        sdkIccPowerDown();
        sdkSysBlackLightOn();
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_SEE_PHONE, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkmSleep(600);
        sdkSysPlaySoundFile(FILE_EMV_BEEP_ERR, 50);
        
        sdkKbWaitKey(SDK_KEY_MASK_ENTER, TMR_WAITKEY);
        DispReadCard(SDK_ICC_RF);
        
		tmr_id = sdkTimerGetId();
		while(1)
		{
			emv_ret = TrnProcTap(SDK_ICC_RF, pstIccTradeParam, &gstTransData.stTransLog.stCardInfo, 0);
	        Trace("emv", "TrnProcTap=%d\r\n", emv_ret);
			if(SDK_ESC == emv_ret)
			{
				return SDK_ESC;
			}
			if(SDK_OK == emv_ret)
			{	
				break;
			}
			if(sdkTimerIsEnd(tmr_id, TMR_OPERATE))
			{
				return SDK_ESC;
			}
		}
        pstIccParam->ucCLType = 0;
        emv_ret = EmvMandatoryTransFlowDetail(pstIccTradeParam, pstIccParam);
        Trace("emv", "EmvMandatoryTransFlowDetail=%d\r\n", emv_ret);
    }
    e_iccret = EmvGetReadCardResult(emv_ret);

    if (ICCRET_ERR == e_iccret)
    {
        EmvLedTransFail();

        if(-323 == emv_ret)     //for external contactless card reader(e.g. G101)
        {
            Trace("emv", "pstIccParam->ucCLType=%d gstTransInfo.ucTrxnId == TRANSID_SALE=%d\n",
                  pstIccParam->ucCLType, (gstTransData.stTransLog.eTransID == TRANSID_SALE));

            if(gstAppSysCfg.stSysParam.bIsExtPED && 0x00 == pstIccParam->ucCLType)
            {
                sdkPEDDisplayStr(STR_INFO_OPERATE_FAILED, 0, 0, 0x08);
                sdkPEDDisplayStr(STR_INFO_REOVME_CARD, 1, 0, 0x08);
            }
            TrnSetStatus(emv_ret);                 //save error code
        }
        else
        {
            DispEmvReadCardReturn(emv_ret);         //save error code
        }
    }

    if ((pstIccParam->ucCardMode & SDK_ICC_RF)
        && (ICCRET_ONLINE_WAIT == e_iccret
            || ICCRET_FALLBACK == e_iccret
            || ICCRET_ERR == e_iccret
            || ICCRET_OFFLINE_DECLINE == e_iccret
            || ICCRET_TRANS_CANCEL == e_iccret
            || ICCRET_OFFLINE_APPROVE == e_iccret))
    {
        if (ICCRET_OFFLINE_APPROVE == e_iccret)
        {
            if (!gstTransData.bIsCtlsReadCardOk)
            {
                EmvLedReadCardOk();
            }
        }
        else if(ICCRET_ONLINE_WAIT == e_iccret)
        {
            if (!gstTransData.bIsCtlsReadCardOk)
            {
                EmvLedReadCardOk();
            }
        }
        else
        {
            if (ICCRET_ERR != e_iccret)
            {
                EmvLedTransFail();
            }
        }
    }
    return e_iccret;
}

/*****************************************************************************
** Description :  Then entry of the mandatory EMV transaction flow.
** Parameters  :  input:
                  (1)SDK_ICC_TRADE_PARAM * pstIccTradeParam: global configuration of 
                     current EMV transaction. 
                  (2)ST_CARDINFO *pstCardInfo: card information
                  
** Return      :  see also enum "E_ICCRET"
** Author      :  wenmin   2016-10-18 
** Remarks     :  No matter contact or contactless transaction, must come into
                  this function to perform EMV flow.
*****************************************************************************/
E_ICCRET EmvMandatoryTransFlowStart(SDK_ICC_TRADE_PARAM  *pstIccTradeParam, ST_CARDINFO *pstCardInfo)
{
    E_ICCRET e_iccret = ICCRET_OK;
    s32 ret = SDK_OK;
    u8 tmp[8];
    u8 aid[16] = {0}, aid_len = 0;
    u8 amount[6] = {0};
    u8 floorlimit[6] = {0};
    SDK_ICC_EmvSysIni_STRUCT st_aid;

    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    e_iccret = EmvMandatoryTransFlow(pstIccTradeParam, &pstCardInfo->stCardParam);

    Trace("emv", "EmvMandatoryTransFlow = %d\r\n", e_iccret);

    if ((ICCRET_ONLINE_WAIT == e_iccret)                //request online
        || (ICCRET_OFFLINE_APPROVE == e_iccret)         //offline approved
        || (ICCRET_EASYFLOW == e_iccret)                //simplified EMV transaction flow
        || (ICCRET_OFFLINE_DECLINE == e_iccret))        //offline trade  failure
    {
        if (SDK_ICC_RF != pstCardInfo->stCardParam.ucCardMode)
        {
            pstCardInfo->stCardParam.ucCLType = CTLSFLOW_NORMAL;
        }
        memset(tmp, 0, sizeof(tmp));

        /* To get the CTLS transaction type from the self-defined tag 58 */
        if( sdkIccReadTLV("\x58", tmp, &ret) > 0)                       //transaction type(not standard EMV tag but self-defined tag)
        {
            gstTransData.eCtlsType = tmp[0];

            if( CTLSTYPE_MSD == gstTransData.eCtlsType )                //paypass MSD mode
            {
                pstCardInfo->stCardParam.ucCLType = CTLSFLOW_MSD;       //set CTLS transaction flow accrodingly
            }
            else if (CTLSTYPE_PAYWAVE == gstTransData.eCtlsType         //paywave
                     || CTLSTYPE_PAYPASS == gstTransData.eCtlsType)     //paypass EMV mode
            {
                pstCardInfo->stCardParam.ucCLType = CTLSFLOW_QUICK;     //set CTLS transaction flow accrodingly
            }
        }
        Trace("emv", "external CTLS reader return card type = 0x%02x\n", gstTransData.eCtlsType);

        /* check if paypass MSD transaction can be offline approved */
        memset(tmp, 0, sizeof(tmp));

        if (ICCRET_ONLINE_WAIT == e_iccret && CTLSFLOW_MSD == pstCardInfo->stCardParam.ucCLType)
        {
            memset(tmp, 0, sizeof(tmp));

            if( sdkIccReadTLV("\x84", tmp, &ret) > 0)                   //DFName
            {
                TraceHex("emv", "EmvMandatoryTransFlowStart: AID", tmp, ret);
                memcpy(aid, tmp, ret);
                aid_len = ret;
            }

            if (gstAppSysCfg.stSysParam.bIsIntRf)                       //internal CTLS card reader
            {
                if (0 == memcmp(aid, "\xA0\x00\x00\x00\x04", 5))        //MasterCard RID
                {
                    if( sdkIccReadTLV("\xDF\x81\x23", tmp, &ret) > 0)   //get paypass tag "DF8123"
                    {
                        TraceHex("emv", "EmvMandatoryTransFlowStart: DF8123", tmp, ret);
                        memcpy(floorlimit, tmp, ret);
                    }
                }
            }
            else     //external CTLS card reader, G101 won't return DF8123
            {
                memset(&st_aid, 0, sizeof(SDK_ICC_EmvSysIni_STRUCT));

                if (SDK_OK == sdkIccGetMatchAID(aid, aid_len, &st_aid))
                {
                    memcpy(floorlimit, st_aid.clessofflinelimitamt, 6);
                    TraceHex("emv", "EmvMandatoryTransFlowStart: offline limit amount", floorlimit, 6);
                }
            }
            sdkAscToBcd(amount, gstTransData.stTransLog.stMsgInfo.asAmount, 12);
            TraceHex("emv", "EmvMandatoryTransFlowStart: Trade amount", amount, 6);

            if (0 >= memcmp(amount, floorlimit, 6))  //less than or equal to CTLS floor limit
            {
                e_iccret = ICCRET_OFFLINE_APPROVE;
            }
        }

        if(SDK_ICC_RF == pstCardInfo->stCardParam.ucCardMode)
        {
            if ((ICCRET_ONLINE_WAIT != e_iccret) && !pstIccTradeParam->bIsSupportQPBOC)
            {
                sdkIccPowerDown();
            }

            if (ICCRET_ONLINE_WAIT == e_iccret)     //CTLS transaction goes online
            {
                gstTransData.bIsOnlineEC = TRUE;
            }
        }
        Trace("emv", "\r\nucCardMode=%d  ucCardLen= %d ucTrack2Len=%d  ucTrack3Len=%d\r\n", pstCardInfo->stCardParam.ucCardMode,
              pstCardInfo->stCardData.ucCardLen, pstCardInfo->stCardData.ucTrack2Len, pstCardInfo->stCardData.ucTrack3Len);

        if ((SDK_ICC_ICC == pstCardInfo->stCardParam.ucCardMode)
            || (SDK_ICC_RF == pstCardInfo->stCardParam.ucCardMode))
        {
            if (0 == pstCardInfo->stCardData.ucCardLen
                && 0 == pstCardInfo->stCardData.ucTrack2Len
                && 0 == pstCardInfo->stCardData.ucTrack3Len)
            {
                TrnGetIccMagData(&pstCardInfo->stCardData);
            }
        }
        Trace("emv", "ucCardMode=%d  ucCardLen= %d ucTrack2Len=%d  ucTrack3Len=%d\r\n", pstCardInfo->stCardParam.ucCardMode,
              pstCardInfo->stCardData.ucCardLen, pstCardInfo->stCardData.ucTrack2Len, pstCardInfo->stCardData.ucTrack3Len);
    }
    else if (ICCRET_FALLBACK == e_iccret)           //fallback
    {
        if(!gstAppSysCfg.stTransParam.bIsFallback)
        {
            return ICCRET_ERR;
        }

        if(SDK_ICC_RF == pstCardInfo->stCardParam.ucCardMode)
        {
            sdkIccPowerDown();
        }

        sdkSysBeep(SDK_SYS_BEEP_ERR);
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_READ_CHIP_FAIL, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLS_SWIPE_CARD, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ENTER, TMR_PROMPT);
        
        pstCardInfo->stCardParam.ucCardMode = 0;
        pstCardInfo->stCardParam.ucCLType = CTLSFLOW_FALLBACK;

        ret = TrnReadCard(MAGONLY, pstIccTradeParam, pstCardInfo);

        if (SDK_ESC == ret || SDK_TIME_OUT == ret)
        {
            e_iccret = ICCRET_TRANS_CANCEL;
        }
        else
        {
            e_iccret = ICCRET_FALLBACK;
        }
    }
    else if (ICCRET_CTLS_SWITCH == e_iccret || ICCRET_DISCOVERY == e_iccret)
    {
        if(SDK_ICC_RF == pstCardInfo->stCardParam.ucCardMode)
        {
            sdkIccPowerDown();
        }
    }
    Trace("emv", "EmvMandatoryTransFlowStart e_iccret = %d\r\n", e_iccret);
    return e_iccret;
}

/*****************************************************************************
** Description :  The optional EMV transaction flow after going online.
** Parameters  :  input:
                  (1)SDK_ICC_TRADE_PARAM * pstIccTradeParam: global configuration of 
                     current EMV transaction. 
                  (2)SDK_ICC_PARAM * pstIccParam: card configuration 
                  
** Return      :  (1)SDK_TransOnlineApprove: online approved
                  (2)ICCRET_REVERSAL: need reversal
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  If it needs reversal, must send auto-reversal right after the
                  transaction or before next online transaction.
*****************************************************************************/
E_ICCRET EmvOptTransFlowOnlineProcess(SDK_ICC_TRADE_PARAM *pstIccTradeParam, SDK_ICC_PARAM *pstIccParam)
{
    SDK_EMV_RLT e_emvret = 0;
    E_ICCRET e_iccret = 0;

    e_emvret = sdkIccTransFlow2(pstIccTradeParam, pstIccParam);
    Trace("emv", "e_emvret = %d\r\n", e_emvret);

    if (SDK_TransOnlineApprove == e_emvret
        || SDK_TransOK_ARPCErr == e_emvret)
    {
        e_iccret = ICCRET_ONLINE_APPROVE;        //online approve
    }
    else
    {
        e_iccret = ICCRET_REVERSAL;             //need reversal
    }
    return e_iccret;
}

/*****************************************************************************
** Description :  Get the value of a specified tag from the TLV encoded data.
** Parameters  :  input:
                  (1)const u8 *pData: The data from which the specified tag is parsed.
                  (2)s32 iDatalen: the data length.
                  (3)const u8 *pheTag:

                  output:
                  (1)u8 *pheOutData: the data obtained
                  (2)s32 *piOutLen: the data length
                  
** Return      :  (1)SDK_PARA_ERR: parameter error
                  (2)SDK_ERR: tag not found
                  (3)SDK_OK: get tag successfully
                  
** Author      :  wenmin   2016-10-18
** Remarks     :
*****************************************************************************/
s32 EmvParseIccTlv(const u8 *pData, s32 iDatalen, const u8 *pheTag, u8 *pheOutData, s32 *piOutLen)
{
    s32 index, taglen, len, tlvlen;

    if(NULL == pData || NULL == pheTag || NULL == pheOutData || NULL == piOutLen)
    {
        return SDK_PARA_ERR;
    }

    index = 0;

    if(0x1F == (pheTag[0] & 0x1F))
    {
        taglen = 2;
    }
    else
    {
        taglen = 1;
    }

    while(index < iDatalen)
    {
        tlvlen = 0;

        if(0x1F == (pData[index] & 0x1F))
        {
            tlvlen = 2;
        }
        else
        {
            tlvlen = 1;
        }

        if(pData[index + tlvlen] > 127)
        {
            tlvlen++;
        }
        len = pData[index + tlvlen];
        tlvlen++;
        tlvlen += len;

        if(memcmp(pheTag, pData + index, (u32)taglen))
        {
            index += tlvlen;
            continue;
        }
        else
        {
            memcpy(pheOutData, pData + index + tlvlen - len, len);
            *piOutLen = len;
            return SDK_OK;
        }
    }

    return SDK_ERR;
}

/*****************************************************************************
** Description :  Get length of the TLV encoded data.
** Parameters  :  input:
                  (1)const u8 *pTagData: TLV encoded data 
                  
** Return      :  data length
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 EmvGetTagLen(const u8 *pTagData)
{
    u8 taglen;

    if(0 == pTagData[0])
    {
        return 0;
    }

    if(0x1F == (pTagData[0] & 0x1F))
    {
        if(0x80 == (pTagData[1] & 0x80))
        {
            taglen = 3;
        }
        else
        {
            taglen = 2;
        }
    }
    else
    {
        taglen = 1;
    }
    return taglen;
}

/*****************************************************************************
** Description :  Initialize contactless parameters for paypass/paywave.
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  Make sure the parameters are set correctly because they will
                  influce the results of the paypass/paywave transaction directly. 
*****************************************************************************/
void EmvInitCtlsParam(void)
{
    s32 ret = SDK_ESC;
    u8 ghePaywaveCfg[128];
    u8 ghePaypassCfg[256];
    s32 i;
    s32 len, offset;

    offset = 0;

    for(i = 0; i < sizeof(TabPaypassCfg) / sizeof(ST_EMV_TLV); i++)
    {
        len = EmvGetTagLen(TabPaypassCfg[i].heTag);
        memcpy(&ghePaypassCfg[offset], TabPaypassCfg[i].heTag, len);
        offset += len;
        ghePaypassCfg[offset++] = TabPaypassCfg[i].ucDatalen;
        memcpy(&ghePaypassCfg[offset], TabPaypassCfg[i].heValue, TabPaypassCfg[i].ucDatalen);
        offset += TabPaypassCfg[i].ucDatalen;
    }

    offset = 0;

    for(i = 0; i < sizeof(TabPaywaveCfg) / sizeof(ST_EMV_TLV); i++)
    {
        len = EmvGetTagLen(TabPaywaveCfg[i].heTag);
        memcpy(&ghePaywaveCfg[offset], TabPaywaveCfg[i].heTag, len);
        offset += len;
        ghePaywaveCfg[offset++] = TabPaywaveCfg[i].ucDatalen;
        memcpy(&ghePaywaveCfg[offset], TabPaywaveCfg[i].heValue, TabPaywaveCfg[i].ucDatalen);
        offset += TabPaywaveCfg[i].ucDatalen;
    }

    ret = sdkIccInitPayWaveParam(ghePaywaveCfg, sizeof(ghePaywaveCfg));
    Trace("emv", "InitPayWaveParam = %d\r\n", ret);
    ret = sdkIccInitPayPassParam(ghePaypassCfg, sizeof(ghePaypassCfg));
    Trace("emv", "InitPayPassParam  = %d\r\n", ret);

    //When Terminal with Pinpad need enable this (st_initial.bIsHavePinPad = TRUE)
    if(gstAppSysCfg.stSysParam.bIsExtPED)
    {
        ret = sdkIccPayPassWaveTradeOnlineOnlySet(0x00);
        Trace("emv", "sdkIccPayPassWaveTradeOnlineOnlySet ret = %d\r\n", ret);
    }
    return;
}

/*****************************************************************************
** Description :  indicate reader in idle state
** Parameters  :  None 
** Return      :  None
** Author      :  Steven 2016-10-20 
** Remarks     :  The first status indicator shall flash at a rate of approximately
                  200ms on, five seconds off.
*****************************************************************************/
void EmvLedIdle(void)
{
    SDK_PED_LAMP_CTRL st_lampctrl;

    Trace("emv", "card mode = %d, RF mode = %d, bIsVirtualLed = %d\r\n",
          gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode, gstAppSysCfg.stSysParam.bIsIntRf, gstAppSysCfg.stTransParam.bIsVirtualLed);

    if (gstAppSysCfg.stSysParam.bIsIntRf) //internal CTLS card reader
    {
        if(gstAppSysCfg.stTransParam.bIsVirtualLed)
        {
            TrnDispLed(LED_1_ON);
            sdkmSleep(200);
            TrnDispLed(LED_1234_OFF);
        }
        else
        {
            memset(&st_lampctrl, 0, sizeof(SDK_PED_LAMP_CTRL));
            st_lampctrl.eLamp1 = SDK_LAMP_ON;        //Blue
            sdkPEDLampControl(&st_lampctrl);
            sdkmSleep(200);
            memset(&st_lampctrl, 0, sizeof(SDK_PED_LAMP_CTRL));
            sdkPEDLampControl(&st_lampctrl);
        }
    }
}

/*****************************************************************************
** Description :  indicate reading CTLS card 
** Parameters  :  None 
** Return      :  None
** Author      :  Steven 2016-10-20 
** Remarks     :  
*****************************************************************************/
void EmvLedReadCard(void)
{
    SDK_PED_LAMP_CTRL st_lampctrl;

    Trace("emv", "card mode = %d, RF mode = %d, bIsVirtualLed = %d\r\n",
          gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode, gstAppSysCfg.stSysParam.bIsIntRf, gstAppSysCfg.stTransParam.bIsVirtualLed);

    if ((SDK_ICC_RF == gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode) //CTLS transaction
        && (gstAppSysCfg.stSysParam.bIsIntRf)) //internal CTLS card reader
    {
        if(gstAppSysCfg.stTransParam.bIsVirtualLed)
        {
            sdkDispClearRowRam(SDK_DISP_LINE1);
            TrnDispLed(LED_1_ON);
            DispTitle(NULL);
        }
        else
        {
            memset(&st_lampctrl, 0, sizeof(SDK_PED_LAMP_CTRL));
            st_lampctrl.eLamp1 = SDK_LAMP_ON;        //Blue
            st_lampctrl.eLamp2 = SDK_LAMP_ON;        //Yellow
            sdkPEDLampControl(&st_lampctrl);
        }
    }
}

/*****************************************************************************
** Description :  indicate card CTLS read complete
** Parameters  :  None 
** Return      :  None
** Author      :  Steven 2016-10-20 
** Remarks     :  
*****************************************************************************/
void EmvLedReadCardOk(void)
{
    SDK_PED_LAMP_CTRL st_lampctrl;

    Trace("emv", "card mode = %d, RF mode = %d, bIsVirtualLed = %d\r\n",
          gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode, gstAppSysCfg.stSysParam.bIsIntRf, gstAppSysCfg.stTransParam.bIsVirtualLed);

    if ((SDK_ICC_RF == gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode) //CTLS transaction
        && (gstAppSysCfg.stSysParam.bIsIntRf)) //internal CTLS card reader
    {
        if(gstAppSysCfg.stTransParam.bIsVirtualLed)
        {
            DispTitle(NULL);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CARD_READ_OK, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_REOVME_CARD, SDK_DISP_DEFAULT);

            sdkSysSetVolume(SDK_SYS_TO_POS, 7); //max volume
            sdkSysPlaySoundFile(FILE_EMV_BEEP_OK, 1);
            sdkSysSetVolume(SDK_SYS_TO_POS, 4);
            gstTransData.bIsCtlsReadCardOk = TRUE;
            TrnDispLed(LED_12_ON);
            sdkmSleep(100);
            TrnDispLed(LED_123_ON);
            sdkmSleep(100);
            TrnDispLed(LED_1234_ON);
            sdkmSleep(750);
            TrnDispLed(LED_1234_OFF);
            DispTitle(NULL);
        }
        else
        {
            memset(&st_lampctrl, 0, sizeof(SDK_PED_LAMP_CTRL));
            st_lampctrl.eLamp1 = SDK_LAMP_ON;
            st_lampctrl.eLamp2 = SDK_LAMP_ON;
            sdkPEDLampControl(&st_lampctrl);
            sdkmSleep(100);
            st_lampctrl.eLamp3 = SDK_LAMP_ON;
            sdkPEDLampControl(&st_lampctrl);
            sdkmSleep(100);
            st_lampctrl.eLamp4 = SDK_LAMP_ON;
            sdkPEDLampControl(&st_lampctrl);
            sdkmSleep(750);
            memset(&st_lampctrl, 0, sizeof(SDK_PED_LAMP_CTRL));
            sdkPEDLampControl(&st_lampctrl);
        }
    }
}

/*****************************************************************************
** Description :  The CTLS transaction is declined.
** Parameters  :  None 
** Return      :  None
** Author      :  Steven 2016-10-20 
** Remarks     :  
*****************************************************************************/
void EmvLedTransFail(void)
{
    SDK_PED_LAMP_CTRL st_lampctrl;

    Trace("emv", "card mode = %d, RF mode = %d, bIsVirtualLed = %d\r\n",
          gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode, gstAppSysCfg.stSysParam.bIsIntRf, gstAppSysCfg.stTransParam.bIsVirtualLed);

    if ((SDK_ICC_RF == gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode) //CTLS transaction
        && (gstAppSysCfg.stSysParam.bIsIntRf)) //internal CTLS card reader
    {
        if(gstAppSysCfg.stTransParam.bIsVirtualLed)
        {
            TrnDispLed(LED_1234_OFF);
            sdkSysPlaySoundFile(FILE_EMV_BEEP_ERR, 50);
            DispTitle(NULL);
        }
        else
        {
            memset(&st_lampctrl, 0, sizeof(SDK_PED_LAMP_CTRL));
            sdkPEDLampControl(&st_lampctrl);
        }
    }
}

/*****************************************************************************
** Description :  Close all LED indicators.
** Parameters  :  None 
** Return      :  None
** Author      :  Steven 2016-10-20 
** Remarks     :  
*****************************************************************************/
void EmvLedClose(void)
{
    SDK_PED_LAMP_CTRL st_lampctrl;

    Trace("emv", "card mode = %d, RF mode = %d, bIsVirtualLed = %d\r\n",
          gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode, gstAppSysCfg.stSysParam.bIsIntRf, gstAppSysCfg.stTransParam.bIsVirtualLed);

    if ((SDK_ICC_RF == gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode) //CTLS transaction
        && (gstAppSysCfg.stSysParam.bIsIntRf)) //internal CTLS card reader

    {
        if(gstAppSysCfg.stTransParam.bIsVirtualLed)
        {
            TrnDispLed(LED_1234_OFF);
            DispTitle(NULL);
        }
        else
        {
            memset(&st_lampctrl, 0, sizeof(SDK_PED_LAMP_CTRL));
            sdkPEDLampControl(&st_lampctrl);
        }
    }
}

