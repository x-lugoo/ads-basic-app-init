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
** Description :  Justify the line on both sides.
** Parameters  :  input:
                  (1)const u8 *pasSrcLeft : left justifying string 
                  (2)const u8 *pasSrcRight : right justifying string 
                  (3)u8 ucRowCharNum : maximum char number a row
                  
                  output:
                  (1)u8 *pasDest : Justified string
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error
                  (2)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintJustifyLine(u8 *pasDest, const u8 *pasSrcLeft, const u8 *pasSrcRight, u8 ucRowCharNum)
{
    s32 len;

    if (NULL == pasDest || NULL == pasSrcLeft || NULL == pasSrcRight)
    {
        return SDK_PARA_ERR;

        Assert(0);
    }
    len = ucRowCharNum - strlen(pasSrcLeft) - strlen(pasSrcRight);             //length of the blank characters

    if (len < 0)
    {
        strncpy(pasDest, pasSrcLeft, ucRowCharNum);
    }
    else
    {
        strcpy(pasDest, pasSrcLeft);
        memset(&pasDest[strlen(pasDest)], ' ', len);
        strcpy(&pasDest[strlen(pasDest)], pasSrcRight);
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Set print font parameter
** Parameters  :  input:
                  (1)E_PRINT_FONT eFont : font type
                  output:
                  (1)SDK_PRINT_FONT *pstFont : SDK font type
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  just convert font type to SDK font structural
*****************************************************************************/
void PrintSetFont(SDK_PRINT_FONT *pstFont, E_PRINT_FONT eFont)
{
    memset(pstFont, 0, sizeof(SDK_PRINT_FONT));
    pstFont->uiLowUndef = 0;
    pstFont->uiHighUndef = 0;

    switch(eFont)
    {
        case PRINT_FONT_FULL:
            pstFont->uiAscFont = SDK_PRN_ASCII12X24;
            pstFont->uiAscZoom = SDK_PRN_ZOOM_A;
            pstFont->uiChFont = SDK_PRN_CH24X24;
            pstFont->uiChZoom = SDK_PRN_ZOOM_A;
            break;

        case PRINT_FONT_HALF:
            pstFont->uiAscFont = SDK_PRN_ASCII12X24;
            pstFont->uiAscZoom = SDK_PRN_ZOOM_N;
            pstFont->uiChFont = SDK_PRN_CH24X24;
            pstFont->uiChZoom = SDK_PRN_ZOOM_N;
            break;
            
        case PRINT_FONT_SMALL:
            pstFont->uiAscFont = SDK_PRN_ASCII8X16;
            pstFont->uiAscZoom = SDK_PRN_ZOOM_N;
            pstFont->uiChFont = SDK_PRN_CH20X20;
            pstFont->uiChZoom = SDK_PRN_ZOOM_N;
            break;
            
        case PRINT_FONT_BOLD:
            pstFont->uiAscFont = SDK_PRN_ASCII16X24B;
            pstFont->uiAscZoom = SDK_PRN_ZOOM_N;
            pstFont->uiChFont = SDK_PRN_CH24X24;
            pstFont->uiChZoom = SDK_PRN_ZOOM_N;
            break;
            
        case PRINT_FONT_HIGHBOLD:
            pstFont->uiAscFont = SDK_PRN_ASCII16X24B;
            pstFont->uiAscZoom = SDK_PRN_ZOOM_N;
            pstFont->uiChFont = SDK_PRN_CH24X24;
            pstFont->uiChZoom = SDK_PRN_ZOOM_N;
            break;
            
        default:
            pstFont->uiAscFont = SDK_PRN_ASCII12X24;
            pstFont->uiAscZoom = SDK_PRN_ZOOM_A;
            pstFont->uiChFont = SDK_PRN_CH24X24;
            pstFont->uiChZoom = SDK_PRN_ZOOM_A;
            break;
    }
}

/*****************************************************************************
** Description :  Start printer 
** Parameters  :  input:
                  (1)bool bIsRollPaper : whether need roll paper after print
                  
** Return      :  (1)SDK_EQU : print fail, need re-process
                  (2)SDK_ESC : print fail
                  (3)SDK_OK : success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  if return "SDK_EQU", must form print data again and start 
                  printer again.
*****************************************************************************/
s32 PrintStart(bool bIsRollPaper)
{
    s32 ret;
    s32 key;

    if(bIsRollPaper)
    {
        ret = sdkPrintStart();
    }
    else
    {
        ret = sdkPrintStartNoRollPaper();
    }

    if (SDK_OK == ret)
    {
        return SDK_OK;
    }
    else
    {
        DispSaveScreen();
        DispClearContent();
    }

    switch (ret)
    {
        case SDK_PRINT_OUTOF_PAPER:
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_LACK_OF_PAPER, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REPRINT, SDK_DISP_DEFAULT);
            break;

        case SDK_PRINT_LOSE_COMMAND:
        case SDK_PRINT_CACHE_ERR:
        case SDK_PRINT_DEV_FAIL:
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_FAILED, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REPRINT, SDK_DISP_DEFAULT);
            break;

        default:
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_TIMEOUT, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REPRINT, SDK_DISP_DEFAULT);
            break;
    }
    sdkDispBrushScreen();
    key = sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE);

    if (SDK_KEY_ENTER == key)
    {
        DispRestoreScreen();
        return SDK_EQU;
    }
    
    return SDK_ESC;
}

/*****************************************************************************
** Description :  Form recipt print data(reference data and ICC data)
** Parameters  :  input:
                  (1)bool bIsReprint : whether is re-print
                  (2)SDK_PRINT_FONT stFont : print font
                  (3)s32 iOffset : column offset
                  (4)s32 iRowGap : gap between two rows
                  (5)s32 iRowChar : maximum char number a row
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void PrintFormRefData(bool bIsReprint, SDK_PRINT_FONT stFont, s32 iOffset, s32 iRowGap, s32 iRowChar)
{
    u8 tmp[512], printbuf[1024];
    ST_MSGINFO *pst_msginfo = NULL;
    ST_CARDINFO *pst_cardinfo = NULL;
    ST_EMVINFO *pst_emvinfo = NULL;

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
    pst_emvinfo = &gstTransData.stTransLog.stEmvInfo;
    
    //-----reference
    memset(tmp, 0, sizeof(tmp));
    memset(tmp, '-', iRowChar);
    sdkPrintStr(tmp, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
    sdkPrintStr("REFERENCE:", stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);   
    
    //-----orig trace No.
    if (TRANSID_VOID == gstTransData.stTransLog.eTransID
        || TRANSID_TIP == gstTransData.stTransLog.eTransID)
    {
        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "ORIG TRACE NO.:");
        strcat(printbuf, pst_msginfo->asOrigTraceNO);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
        
        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "ORIG BATCH NO.:");
        strcat(printbuf, pst_msginfo->asOrigBatchNO);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
    }
    
    //-----orig ref no. & orig date
    if (TRANSID_REFUND == gstTransData.stTransLog.eTransID)
    {
        if(strlen(pst_msginfo->asRefNO))
        {
            memset(printbuf, 0, sizeof(printbuf));
            strcpy(printbuf, "ORIG REF. NO.:");
            strcat(printbuf, pst_msginfo->asRefNO);
            sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
        }

    }
    if (TRANSID_REFUND == gstTransData.stTransLog.eTransID
        || TRANSID_TIP == gstTransData.stTransLog.eTransID)
    {
        if(strlen(pst_msginfo->asOrigDate))
        {
            memset(printbuf, 0, sizeof(printbuf));
            strcpy(printbuf, "ORIG DATE:");
            strncat(printbuf, pst_msginfo->asOrigDate, 2);
            strcat(printbuf, "/");
            strncat(printbuf, pst_msginfo->asOrigDate + 2, 2);
            sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
        }
    }
    
    if(strlen(pst_msginfo->asIssuerInfo))
    {
        sdkPrintStr(pst_msginfo->asIssuerInfo, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
    }

    if(strlen(pst_msginfo->asCUPInfo))
    {
        sdkPrintStr(pst_msginfo->asCUPInfo, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
    }
    
    if(strlen(pst_msginfo->asAcqInfo))
    {
        sdkPrintStr(pst_msginfo->asAcqInfo, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
    }
    
    if(strlen(pst_msginfo->asTermReserved))
    {
        sdkPrintStr(pst_msginfo->asTermReserved, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
    }

    if((SDK_ICC_ICC == pst_cardinfo->stCardParam.ucCardMode || SDK_ICC_RF == pst_cardinfo->stCardParam.ucCardMode) 
        && TRANSID_SALE == gstTransData.stTransLog.eTransID)
    {
        memset(tmp, 0, sizeof(tmp));
        memset(printbuf, 0, sizeof(printbuf));
        if(0 != memcmp(pst_emvinfo->heAC, tmp, 8))
        {
            if(gstTransData.stTransLog.stTransStatus.bIsOffline)
            {
                strcpy(printbuf, "TC:");
                sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heAC, 8);
            }
            else
            {
                strcpy(printbuf, "ARQC:");
                sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heAC, 8);
            }
            sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
        }
        
        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "TVR:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heTVR, 5);
        strcat(printbuf, " CSN:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], &pst_emvinfo->ucPANSN, 1);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "AID:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heAID, pst_emvinfo->ucAIDLen);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "TSI:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heTSI, 2);
        strcat(printbuf, "  ATC:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heATC, 2);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "APP LABEL:");
        strcpy(&printbuf[strlen(printbuf)], pst_emvinfo->asAppLabel);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "APP NAME:");   
        strcpy(&printbuf[strlen(printbuf)], pst_emvinfo->asAppPreferName);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "UNPR_NUM:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heUN, 4);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "AIP:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heAIP, 2);

        if (CTLSFLOW_QUICK != pst_cardinfo->stCardParam.ucCLType)
        {
            strcat(printbuf, "  CVMR:");
            sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heCVMR, 3);
        }
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "IAD:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heIAD, pst_emvinfo->ucIADLen);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);

        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "TermCap:");
        sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heTermCap, 3);
        sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
    }
}

/*****************************************************************************
** Description :  Form recipt print data
** Parameters  :  input:
                  (1)bool bIsReprint : whether is re-print
                  (2)u32 uiPrintTimes : current print times
                  (3)u32 uiTotalTimes : total print times
                  
** Return      :  (1)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintFormReciptData(bool bIsReprint, u32 uiPrintTimes, u32 uiTotalTimes)
{
    u8 buf[512], tmp[512], printbuf[1024];
    u32 offset, rowspace;
    s32 rowchar = 32;
    SDK_PRINT_FONT st_font_title, st_font_keyword, st_font_label, st_font_transtype;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_CARDINFO *pst_cardinfo = NULL;

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;

    //-----init print
    sdkPrintInit();
    PrintSetFont(&st_font_title, PRINT_FONT_FULL);
    PrintSetFont(&st_font_keyword, PRINT_FONT_BOLD);
    PrintSetFont(&st_font_transtype, PRINT_FONT_FULL);
    if(PRINT_SIZE_BIG == gstAppSysCfg.stTransParam.uiPrintSize)
    {
        PrintSetFont(&st_font_label, PRINT_FONT_HALF);
        rowchar = 32;
        rowspace = 4;
    }
    else if(PRINT_SIZE_MEDIUM == gstAppSysCfg.stTransParam.uiPrintSize)
    {
        PrintSetFont(&st_font_label, PRINT_FONT_SMALL);
        rowchar = 48;
        rowspace = 4;
    }
    else
    {
        PrintSetFont(&st_font_label, PRINT_FONT_SMALL);
        rowchar = 48;
        rowspace = 0;
    }
    offset = 0;

    //-----print title
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, PATH_MTD0_RES);
    sdkSysGetCurAppId(buf);
    strncat(tmp, &buf[3], 5);
    strcat(tmp, FILENAME_PRINT_BMP);

    if (sdkAccessFile(tmp))
    {
        sdkPrintBitMap(tmp, SDK_PRINT_MIDDLEALIGN, rowspace);
    }
    
    sdkPrintStr("RECEIPT", st_font_title, SDK_PRINT_MIDDLEALIGN, offset, rowspace + 10);
    
    //-----merchant name
    sdkPrintStr("MERCHANT NAME:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    sdkPrintStr(gstAppSysCfg.stTermInfo.asMerchName, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----merchant id
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "MID:");
    strncpy(tmp, pst_msginfo->asMerchID, 15);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----terminal id
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "TID:");
    strncpy(tmp, pst_msginfo->asTermID, 8);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----cashier NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "CASHIER NO.:");
    sprintf(tmp, "%02d", pst_msginfo->ucCashierNO);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----issuing bank NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "ISS NO.:");
    strncpy(tmp, pst_msginfo->asIssuerCode, strcspn(pst_msginfo->asAcquirerCode, " "));
    //sdkTrim(tmp, SDK_RIGHT);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----acquirer bank NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "ACQ NO.:");
    strncpy(tmp, pst_msginfo->asAcquirerCode, strcspn(pst_msginfo->asAcquirerCode, " "));
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----card NO.
    sdkPrintStr("CARD NO.:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    memset(printbuf, 0, sizeof(printbuf));
    strcpy(tmp, pst_cardinfo->stCardData.asCardNO);
    TrnMaskCardNo(gstTransData.stTransLog.eTransID, tmp);
    strcpy(printbuf, tmp);

    if(0 == gstTransData.stTransLog.stCardInfo.stCardParam.ucCardMode)
    {
        strcat(printbuf, " N");
    }
    else if (0 == memcmp(pst_msginfo->asEntryMode, "01", 2))
    {
        strcat(printbuf, " M");
    }
    else if (0 == memcmp(pst_msginfo->asEntryMode, "02", 2))
    {
        strcat(printbuf, " S");
    }
    else if (0 == memcmp(pst_msginfo->asEntryMode, "05", 2))
    {
        strcat(printbuf, " I");
    }
    else if (0 == memcmp(pst_msginfo->asEntryMode, "07", 2) 
          || 0 == memcmp(pst_msginfo->asEntryMode, "96", 2) 
          || 0 == memcmp(pst_msginfo->asEntryMode, "98", 2))
    {
        strcat(printbuf, " C");
    }
    else if (0 == memcmp(pst_msginfo->asEntryMode, "92", 2))       //no card 
    {
        strcat(printbuf, " N");
    }
    sdkPrintStr(printbuf, st_font_keyword, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----expiry date
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "EXP DATE:");

    if (strlen(pst_cardinfo->stCardData.asExpiredDate))
    {
        strcat(tmp, "20");
        strncat(tmp, pst_cardinfo->stCardData.asExpiredDate, 2);
        strcat(tmp, "/");
        strncat(tmp, &pst_cardinfo->stCardData.asExpiredDate[2], 2);
    }
    else
    {
        strcpy(tmp, "  ");
    }
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----transaction type
    sdkPrintStr("TRANS TYPE:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    memset(tmp, 0, sizeof(tmp));
    TrnGetName(tmp, gstTransData.stTransLog.eTransID);
    sdkPrintStr(tmp, st_font_transtype, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----batch NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "BATCH NO.:");
    strncpy(tmp, pst_msginfo->asBatchNO, 6);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----trace NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "TRACE NO.:");
    strncpy(tmp, pst_msginfo->asTraceNO, 6);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----authorization NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "AUTH NO.:");
    strncpy(tmp, pst_msginfo->asAuthCode, 6);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----reference NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    strcpy(buf, "REF. NO.:");
    strncpy(tmp, pst_msginfo->asRefNO, 12);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----date & time
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    sdkGetRtc(buf);
    sprintf(tmp, "20%02X/%2.2s/%2.2s %2.2s:%2.2s:%2.2s",
            buf[0], pst_msginfo->asTransDate,
            &pst_msginfo->asTransDate[2],
            pst_msginfo->asTransTime,
            &pst_msginfo->asTransTime[2],
            &pst_msginfo->asTransTime[4]);

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "DATE/TIME:");
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----amount
    sdkPrintStr("AMOUNT:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    memset(printbuf, 0, sizeof(printbuf));
    strcpy(printbuf, gstAppSysCfg.stTermInfo.asCurrencyName);
    if (TRANSID_TIP == gstTransData.stTransLog.eTransID)
    {
        memset(buf, 0, sizeof(buf));
        memset(tmp, 0, sizeof(tmp));
        sdkAscToBcdR(buf, pst_msginfo->asAmount, 6);
        sdkAscToBcdR(tmp, pst_msginfo->asTipAmount, 6);
        sdkBcdSub(buf, buf, 6, tmp, 6);
        memset(tmp, 0, sizeof(tmp));
        sdkBcdToAsc(tmp, buf, 6);
        memset(buf, 0, sizeof(buf));
        TrnFormatAmount(buf, tmp, FALSE);
        strcat(printbuf, " ");    
        strcat(printbuf, buf);
    }
    else
    {
        memset(buf, 0, sizeof(buf));

        if ((gstAppSysCfg.stTransParam.bIsPrintMinusSign) 
         && (TrnJudgeCreditTrans(gstTransData.stTransLog.eTransID)))
        {
            memset(tmp, 0, sizeof(tmp));
            TrnFormatAmount(tmp, pst_msginfo->asAmount, FALSE);
            strcat(printbuf, " -");    
            strcat(printbuf, tmp);
        }
        else
        {
            memset(tmp, 0, sizeof(tmp));
            TrnFormatAmount(tmp, pst_msginfo->asAmount, FALSE);
            strcat(printbuf, " ");    
            strcat(printbuf, tmp);
        }
    }
    sdkPrintStr(printbuf, st_font_keyword, SDK_PRINT_RIGHTALIGN, offset, rowspace);

    //-----tip
    if (TRANSID_TIP == gstTransData.stTransLog.eTransID)
    {
        sdkPrintStr("TIP:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
        memset(tmp, 0, sizeof(tmp));
        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, gstAppSysCfg.stTermInfo.asCurrencyName);
        TrnFormatAmount(tmp, pst_msginfo->asTipAmount, FALSE);
        strcat(printbuf, " ");    
        strcat(printbuf, tmp);
        sdkPrintStr(printbuf, st_font_keyword, SDK_PRINT_RIGHTALIGN, offset, rowspace);

        //-----total amount
        sdkPrintStr("TOTAL:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
        memset(tmp, 0, sizeof(tmp));
        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, gstAppSysCfg.stTermInfo.asCurrencyName);
        TrnFormatAmount(tmp, pst_msginfo->asAmount, FALSE);
        strcat(printbuf, " ");    
        strcat(printbuf, tmp);
        sdkPrintStr(printbuf, st_font_keyword, SDK_PRINT_RIGHTALIGN, offset, rowspace);
    }

    //-----balance
    memset(tmp, 0, sizeof(tmp));

    if (strlen(pst_msginfo->asBalance))
    {
        memset(printbuf, 0, sizeof(printbuf));
        memset(buf, 0, sizeof(buf));
        memset(tmp, 0, sizeof(tmp));
        strcpy(buf, "BALANCE:");

        if ('D' == pst_msginfo->asBalance[0])
        {
            strcat(tmp, "-");
        }
        TrnFormatAmount(&tmp[strlen(tmp)], &pst_msginfo->asBalance[1], FALSE);
        PrintJustifyLine(printbuf, buf, tmp, rowchar);
        sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    }

    //-----International credit card organization
    if (strlen(pst_msginfo->asInterOrgCode))
    {
        memset(printbuf, 0, sizeof(printbuf));
        memset(buf, 0, sizeof(buf));
        memset(tmp, 0, sizeof(tmp));
        strcpy(buf, "CARD ORG:");
        strncpy(tmp, pst_msginfo->asInterOrgCode, 3);
        PrintJustifyLine(printbuf, buf, tmp, rowchar);
        sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    }

    PrintFormRefData(bIsReprint, st_font_label, offset, rowspace, rowchar);
    
    //-----reprint flag
    if (bIsReprint)
    {
        sdkPrintStr("DUPLICATED", st_font_keyword, SDK_PRINT_MIDDLEALIGN, offset, rowspace);
    }

    //-----cardholder name
    if (strlen(pst_cardinfo->asCardHolder))
    {
        memset(printbuf, 0, sizeof(printbuf));
        strcpy(printbuf, "CARDHOLDER:");
        strcat(printbuf, pst_cardinfo->asCardHolder);
        sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    }

    //-----signature
    if (0 == uiPrintTimes)
    {
        sdkPrintStr("CARDHOLDER SIGNATURE:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
        sdkPrintStr(" ", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
        sdkPrintStr(" ", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
        sdkPrintStr(" ", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

        sdkPrintStr("I ACKNOWLEDGE SATISFACTORY RECEIPT OF RELATIVE  GOODS/SERVICES", st_font_label, 
                    SDK_PRINT_LEFTALIGN, offset, rowspace);
    }

    //-----terminal info
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "NEXGO-");
    memset(tmp, 0, sizeof(tmp));
    sdkSysGetMachineModel(tmp);
    strcat(buf, tmp);
    strcat(buf, "-");
    strcat(buf, APPVERSION);
    sdkPrintStr(buf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----copy name
    memset(printbuf, 0, sizeof(printbuf));
    switch (uiPrintTimes)
    {
         case 0:
           strcpy(printbuf, "--MERCHANT COPY--");
           break;

         case 1:

           if (2 == uiTotalTimes)
           {
               strcpy(printbuf, "--CARDHOLDER COPY--");
           }
           else
           {
               strcpy(printbuf, "--BANK COPY--");
           }
           break;

         default:
           if (3 == uiTotalTimes)
           {
               strcpy(printbuf, "--CARDHOLDER COPY--");
           }
           else
           {
               strcpy(printbuf, "--BANK COPY--");
           }
           break;
    }
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_RIGHTALIGN, offset, rowspace);
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Form settle report print data
** Parameters  :  input:
                  (1)bool bIsReprint : whether is re-print
                  
** Return      :  (1)SDK_OK : success
                  (1)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintFormSettleData(bool bIsReprint)
{
    u8 buf[512], tmp[512], printbuf[1024];
    u8 amount[16];
    u32 offset, rowspace;
    s32 rowchar = 32;
    SDK_PRINT_FONT st_font_title, st_font_keyword, st_font_label;
    ST_SETTLE st_settle;

    if(SDK_OK != SettleReadInfo(&st_settle))
    {
        return SDK_ERR;
    }

    //-----init print
    sdkPrintInit();
    PrintSetFont(&st_font_title, PRINT_FONT_FULL);
    PrintSetFont(&st_font_keyword, PRINT_FONT_BOLD);
    PrintSetFont(&st_font_label, PRINT_FONT_HALF);
    rowchar = 32;
    rowspace = 4;
    offset = 0;

    //-----print title
    sdkPrintStr("SETTLEMENT", st_font_title, SDK_PRINT_MIDDLEALIGN, offset, rowspace);
    
    //-----merchant name
    sdkPrintStr("MERCHANT NAME:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    sdkPrintStr(gstAppSysCfg.stTermInfo.asMerchName, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----merchant id
    memset(printbuf, 0, sizeof(printbuf));
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "MID:");
    strncpy(tmp, st_settle.asMerchID, 15);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----terminal id
    memset(printbuf, 0, sizeof(printbuf));
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "TID:");
    strncpy(tmp, st_settle.asTermID, 8);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----cashier NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "CASHIER NO.:");
    sprintf(tmp, "%02d", st_settle.ucCashierNO);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----batch NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "BATCH NO.:");
    PrintJustifyLine(printbuf, buf, st_settle.asBatchNO, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----date & time
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    sdkGetRtc(buf);
    sprintf(tmp, "20%02X/%2.2s/%2.2s %2.2s:%2.2s:%2.2s",
            buf[0], st_settle.asDateTime,
            &st_settle.asDateTime[2],
            &st_settle.asDateTime[4],
            &st_settle.asDateTime[6],
            &st_settle.asDateTime[8]);
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "DATE/TIME:");
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----separator
    memset(buf, 0, sizeof(buf));
    memset(buf, '-', rowchar);
    sdkPrintStr(buf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----summary record title
    memset(printbuf, 0, sizeof(buf));
    strcpy(printbuf, "TYPE");
    PrintJustifyLine(printbuf, printbuf, "SUM", rowchar / 2);
    PrintJustifyLine(printbuf, printbuf, "AMOUNT", rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----settle result
    if ('1' == st_settle.stTotal.ucSettleCode && '1' == st_settle.stTotalRMB.ucSettleCode)
    {
        sdkPrintStr("RECONCILIATION BALANCED", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    }
    else if ('1' != st_settle.stTotal.ucSettleCode || '1' != st_settle.stTotalRMB.ucSettleCode)
    {
        sdkPrintStr("RECONCILIATION UNBALANCED", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    }
    else
    {
        sdkPrintStr("RECONCILIATION ERR", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    }

    //-----summary debit
    memset(printbuf, 0, sizeof(buf));
    strcpy(printbuf, "SALE");
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%3d", st_settle.stTotal.stTotalAll.uiTotalDebitNum);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar / 2);
    memset(tmp, 0, sizeof(tmp));
    memset(amount, 0, sizeof(amount));
    sdkBcdToAsc(amount, st_settle.stTotal.stTotalAll.bcTotalDebitAmount, 6);
    TrnFormatAmount(tmp, amount, FALSE);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----summary credit
    memset(printbuf, 0, sizeof(buf));
    strcpy(printbuf, "REFUND");
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%3d", st_settle.stTotal.stTotalAll.uiTotalCreditNum);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar / 2);
    memset(tmp, 0, sizeof(tmp));
    memset(amount, 0, sizeof(amount));
    sdkBcdToAsc(amount, st_settle.stTotal.stTotalAll.bcTotalCreditAmount, 6);
    TrnFormatAmount(tmp, amount, FALSE);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----reprint flag
    if (bIsReprint)
    {
        //-----separator
        memset(tmp, 0, sizeof(tmp));
        memset(tmp, '-', rowchar);
        sdkPrintStr(tmp, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
        sdkPrintStr("DUPLICATED", st_font_keyword, SDK_PRINT_MIDDLEALIGN, offset, rowspace);
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Form total report print data
** Parameters  :  input:
                  (1)ST_SETTLE *pstSettle : settle information
                  
** Return      :  (1)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintFormTotalData(ST_SETTLE *pstSettle)
{
    u8 buf[512], tmp[512], printbuf[1024];
    u8 amount[16];
    u32 offset, rowspace;
    s32 rowchar = 32;
    SDK_PRINT_FONT st_font_title, st_font_keyword, st_font_label;

    //-----init print
    sdkPrintInit();
    PrintSetFont(&st_font_title, PRINT_FONT_FULL);
    PrintSetFont(&st_font_keyword, PRINT_FONT_BOLD);
    PrintSetFont(&st_font_label, PRINT_FONT_HALF);
    rowchar = 32;
    rowspace = 4;
    offset = 0;

    //-----print title
    sdkPrintStr("SUMMARY REPORT", st_font_title, SDK_PRINT_MIDDLEALIGN, offset, rowspace);
    
    //-----merchant name
    sdkPrintStr("MERCHANT NAME:", st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    sdkPrintStr(gstAppSysCfg.stTermInfo.asMerchName, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----merchant id
    memset(printbuf, 0, sizeof(printbuf));
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "MID:");
    strncpy(tmp, gstAppSysCfg.stTermInfo.asMerchID, 15);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----terminal id
    memset(printbuf, 0, sizeof(printbuf));
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "TID:");
    strncpy(tmp, gstAppSysCfg.stTermInfo.asTermID, 8);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----cashier NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(tmp, 0, sizeof(tmp));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "CASHIER NO.:");
    sprintf(tmp, "%02d", gstLoginInfo.ucUserNO);
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----batch NO.
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "BATCH NO.:");
    PrintJustifyLine(printbuf, buf, gstAppSysCfg.stTransParam.asBatchNO, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----date & time
    memset(printbuf, 0, sizeof(printbuf));
    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    sdkGetRtc(buf);
    sprintf(tmp, "20%02X/%02X/%02X %02X:%02X:%02X",
            buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
    memset(buf, 0, sizeof(buf));
    strcpy(printbuf, "DATE/TIME:");
    PrintJustifyLine(printbuf, buf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----separator
    memset(buf, 0, sizeof(buf));
    memset(buf, '-', rowchar);
    sdkPrintStr(buf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----summary record title
    memset(printbuf, 0, sizeof(buf));
    strcpy(printbuf, "TYPE");
    PrintJustifyLine(printbuf, printbuf, "SUM", rowchar / 2);
    PrintJustifyLine(printbuf, printbuf, "AMOUNT", rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----summary debit
    memset(printbuf, 0, sizeof(buf));
    strcpy(printbuf, "SALE");
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%3d", pstSettle->stTotal.stTotalAll.uiTotalDebitNum);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar / 2);
    memset(tmp, 0, sizeof(tmp));
    memset(amount, 0, sizeof(amount));
    sdkBcdToAsc(amount, pstSettle->stTotal.stTotalAll.bcTotalDebitAmount, 6);
    TrnFormatAmount(tmp, amount, FALSE);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);

    //-----summary credit
    memset(printbuf, 0, sizeof(buf));
    strcpy(printbuf, "REFUND");
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%3d", pstSettle->stTotal.stTotalAll.uiTotalCreditNum);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar / 2);
    memset(tmp, 0, sizeof(tmp));
    memset(amount, 0, sizeof(amount));
    sdkBcdToAsc(amount, pstSettle->stTotal.stTotalAll.bcTotalCreditAmount, 6);
    TrnFormatAmount(tmp, amount, FALSE);
    PrintJustifyLine(printbuf, printbuf, tmp, rowchar);
    sdkPrintStr(printbuf, st_font_label, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Form transaction detail report header print data
** Parameters  :  input:
                  (1)const u8 *pasTitle : print title
                  
** Return      :  (1)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintFormDetailHeaderData(const u8 *pasTitle)
{
    u8 tmp[512], printbuf[1024];
    SDK_PRINT_FONT st_font, st_font_title;
    
    sdkPrintInit();
    PrintSetFont(&st_font, PRINT_FONT_HALF);
    PrintSetFont(&st_font_title, PRINT_FONT_FULL);

    if(pasTitle)
    {
        sdkPrintStr((u8 *)pasTitle, st_font_title, SDK_PRINT_MIDDLEALIGN, 0, 14);
    }

    memset(printbuf, 0, sizeof(printbuf));
    strcpy(printbuf, "CARD NO.");
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "TRANS TYPE");
    PrintJustifyLine(printbuf, printbuf, tmp, 22);
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "AUTH NO.");
    PrintJustifyLine(printbuf, printbuf, tmp, 32);
    sdkPrintStr(printbuf, st_font, SDK_PRINT_LEFTALIGN, 0, 8);

    memset(printbuf, 0, sizeof(printbuf));
    strcpy(printbuf, "TRACE NO.");
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "AMOUNT");
    PrintJustifyLine(printbuf, printbuf, tmp, 32);
    sdkPrintStr(printbuf, st_font, SDK_PRINT_LEFTALIGN, 0, 10);
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Form transaction detail report print data
** Parameters  :  input:
                  (1)ST_TRANSLOG *stTransLog : transaction data
                  
** Return      :  (1)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintFormDetailData(ST_TRANSLOG *stTransLog)
{
    u8 tmp[512], printbuf[1024];
    SDK_PRINT_FONT st_font;
    ST_MSGINFO *pst_msginfo = NULL;
    ST_CARDINFO *pst_cardinfo = NULL;
    u32 offset, rowspace, len;
    s32 rowchar = 32;

    pst_msginfo = &stTransLog->stMsgInfo;
    pst_cardinfo = &stTransLog->stCardInfo;

    //-----init print
    sdkPrintInit();
    PrintSetFont(&st_font, PRINT_FONT_HALF);
    rowchar = 32;
    rowspace = 4;
    offset = 0;
    
    //-----card NO.
    memset(printbuf, 0, sizeof(printbuf));
    memcpy(printbuf, pst_cardinfo->stCardData.asCardNO, pst_cardinfo->stCardData.ucCardLen);
    len = strlen(printbuf);
    if (len > 10 && len < 20)
    {
        memset(&printbuf[6], '*', len - 10);
    }
    
    memset(tmp, 0, sizeof(tmp));
    switch (stTransLog->eTransID)
    {
         case TRANSID_SALE:
         case TRANSID_TIP:
           strcpy(tmp, "S");
           break;

         case TRANSID_REFUND:
           strcpy(tmp, "R");
           break;

         default:
           break;
    }

    PrintJustifyLine(printbuf, printbuf, tmp, 22);
    
    //-----authorization NO.
    memset(tmp, 0, sizeof(tmp));

    if (strlen(pst_msginfo->asAuthCode) > 0
        && UPLOAD_OFFLINE_FAIL != stTransLog->stTransStatus.eUploadStatus
        && UPLOAD_BATCHDONE_OFFFAIL != stTransLog->stTransStatus.eUploadStatus
        && UPLOAD_OFFLINE_DECLINE != stTransLog->stTransStatus.eUploadStatus
        && UPLOAD_BATCHDONE_OFFDECLINE != stTransLog->stTransStatus.eUploadStatus)
    {
        PrintJustifyLine(printbuf, printbuf, pst_msginfo->asAuthCode, rowchar);
    }

    sdkPrintStr(printbuf, st_font, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    //-----trace NO.
    memset(printbuf, 0, sizeof(printbuf));
    strcpy(printbuf, pst_msginfo->asTraceNO);

    //--amount
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%s ", gstAppSysCfg.stTermInfo.asCurrencyName);
    TrnFormatAmount(&tmp[strlen(tmp)], pst_msginfo->asAmount, FALSE);
    PrintJustifyLine(printbuf, printbuf, tmp, 32);

    sdkPrintStr(printbuf, st_font, SDK_PRINT_LEFTALIGN, offset, rowspace);
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Form transaction detail report footer print data
** Parameters  :  None
** Return      :  (1)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintFormDetailEndData(void)
{
    SDK_PRINT_FONT st_font;

    //-----init print
    sdkPrintInit();
    PrintSetFont(&st_font, PRINT_FONT_HALF);
    
    sdkPrintStr("  ", st_font, SDK_PRINT_LEFTALIGN, 0, 0);
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Print recipt
** Parameters  :  input:
                  (1)bool bIsReprint : whether is re-print
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintRecipt(bool bIsReprint)
{
    s32 ret;
    u32 times, totaltimes;

    totaltimes = gstAppSysCfg.stTransParam.uiPrintTimes;

    for (times = 0; times < totaltimes; times++)
    {
        while (1)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINTING, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();

            ret = PrintFormReciptData(bIsReprint, times, totaltimes);
            if (SDK_OK != ret)
            {
                TrnSetStatus(ERR_PRINT);
                return SDK_ERR;
            }

            ret = PrintStart(TRUE);

            if (SDK_EQU == ret)
            {
                continue;
            }
            else if (SDK_OK == ret)
            {
                break;
            }
            else
            {
                TrnSetStatus(ERR_PRINT);
                return SDK_ERR;
            }
        }

        if ((times + 1) < totaltimes)
        {
            sdkmSleep(2000);
        }
    }
    
    gstTransData.stTransLog.stTransStatus.bIsNeedRePrint = FALSE;
    RecordUpdate(&gstTransData.stTransLog);

    return SDK_OK;
}

/*****************************************************************************
** Description :  Print settlement report
** Parameters  :  input:
                  (1)bool bIsReprint : whether is re-print
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintSettleReport(bool bIsReprint)
{
    s32 ret;

    while (1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINTING_SETTLE, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();

        ret = PrintFormSettleData(bIsReprint);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PRINT);
            return SDK_ERR;
        }

        ret = PrintStart(TRUE);

        if (SDK_EQU == ret)
        {
            continue;
        }
        else if (SDK_OK == ret)
        {
            break;
        }
        else
        {
            TrnSetStatus(ERR_PRINT);
            return SDK_ERR;
        }
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Print transaction total report
** Parameters  :  input:
                  (1)ST_SETTLE *pstSettle : settle information
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintTotalReport(ST_SETTLE *pstSettle)
{
    s32 ret;

    while (1)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINTING, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PLEASE_WAIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();

        ret = PrintFormTotalData(pstSettle);
        if (SDK_OK != ret)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PRINT_FORMAT_ERR, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
            return SDK_ERR;
        }
        ret = PrintStart(TRUE);

        if (SDK_EQU == ret)
        {
            continue;
        }
        else if (SDK_OK == ret)
        {
            break;
        }
        else
        {
            return SDK_ERR;
        }

        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_OVER, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  Print transaction detail report header
** Parameters  :  input:
                  (1)const u8 *pasTitle : print title
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintDetailReportHeader(const u8 *pasTitle)
{
    s32 ret;

    while (1)
    {
        ret = PrintFormDetailHeaderData(pasTitle);
        if (SDK_OK != ret)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PRINT_FORMAT_ERR, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
            return SDK_ERR;
        }
        
        ret = PrintStart(FALSE);

        if (SDK_EQU == ret)
        {
            continue;
        }
        else if (SDK_OK == ret)
        {
            break;
        }
        else
        {
            return SDK_ERR;
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Print transaction detail report
** Parameters  :  input:
                  (1)ST_TRANSLOG *stTransLog : transaction data
                  
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintDetailReport(ST_TRANSLOG *stTransLog)
{
    s32 ret;

    while (1)
    {
        ret = PrintFormDetailData(stTransLog);
        if (SDK_OK != ret)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PRINT_FORMAT_ERR, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
            return SDK_ERR;
        }
        
        ret = PrintStart(FALSE);

        if (SDK_EQU == ret)
        {
            continue;
        }
        else if (SDK_OK == ret)
        {
            break;
        }
        else
        {
            return SDK_ERR;
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Print transaction detail report footer
** Parameters  :  None
** Return      :  (1)SDK_ERR : fail
                  (2)SDK_OK : success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 PrintDetailReportFooter(void)
{
    s32 ret;

    while (1)
    {
        ret = PrintFormDetailEndData();
        if (SDK_OK != ret)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PRINT_FORMAT_ERR, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
            return SDK_ERR;
        }
        
        ret = PrintStart(TRUE);

        if (SDK_EQU == ret)
        {
            continue;
        }
        else if (SDK_OK == ret)
        {
            break;
        }
        else
        {
            return SDK_ERR;
        }
    }
    return SDK_OK;
}

