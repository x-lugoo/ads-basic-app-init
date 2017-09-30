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
** Description :  Query and display transaction detail(all transaction)
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportQueryTransDetail(void)
{
    s32 num;
    s32 i;
    ST_TRANSLOG st_translog;

    num = RecordGetNum();
    
    if (0 >= num)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }

    for(i = 0; i < num; i++)
    {
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        if(SDK_OK == RecordRead(i, &st_translog))
        {
            if(st_translog.stTransStatus.bIsIccFailTrans 
            || st_translog.stTransStatus.bIsNeedReversal)
            {
                continue;
            }
            if(SDK_OK != DispTransDetail(&st_translog))
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_QUERY_OVER, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_EXIT, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_PROMPT);
    
    return;
}

/*****************************************************************************
** Description :  Query and display transaction total
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportQueryTransTotal(void)
{
    ST_SETTLE st_settle;
    
    if (0 >= RecordGetNum())
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }

    if(SDK_OK != SettleGetTotalAmount(&st_settle))
    {
        return;
    }

    DispTransTotal(&st_settle);

    return;
}

/*****************************************************************************
** Description :  query and display specified transaction by trace no
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportQuerySpecifiedTrans(void)
{
    u8 buf[64];
	ST_TRANSLOG st_translog;
    

    if (0 >= RecordGetNum())
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }

    while (1)
    {
        //get original trace no
        memset(buf, 0, sizeof(buf));
        if (!TrnInputTraceNo(buf))
        {
            return;
        }

        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        if (SDK_OK == RecordSearch(LOG_MSG_TRACENO, buf, &st_translog) 
            && FALSE == st_translog.stTransStatus.bIsNeedReversal
            && FALSE == st_translog.stTransStatus.bIsIccFailTrans)
        {  
            DispTransDetail(&st_translog);
            return;
        }
        else
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_TRANS_NOT_FOUND, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_OPERATE))
            {
                continue;
            }
            return;
        }
    }
    return;
}

/*****************************************************************************
** Description :  Reprint the last successful transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportPrintLastTrans(void)
{
    ST_SETTLE st_settle;
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    bool value;

    if(SDK_OK == SettleReadInfo(&st_settle) && SETTLE_NONE == st_settle.ucPrintState)
    {
        PrintSettleReport(TRUE);
        return;
    }
        
    memset(st_filter, 0, sizeof(st_filter));
    value = FALSE;

    st_filter[0].bIsDesc = TRUE;
    st_filter[0].iId = LOG_STAT_NEEDREVERSAL;
    st_filter[0].eMode = FILTER_SIGNEL;
    st_filter[0].pasValue[0] = &value;
    
    st_filter[1].iId = LOG_STAT_ICCFAILTRANS;
    st_filter[1].eMode = FILTER_SIGNEL;
    st_filter[1].pasValue[0] = &value;

    st_filter[2].iId = -1;
    
    if (RecordGetNum() <= 0 || RecordGetNumEx(st_filter) <= 0)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }
    
    memset(&gstTransData.stTransLog, 0, sizeof(ST_TRANSLOG));
    if(SDK_OK == RecordSearchEx(st_filter, 0, &gstTransData.stTransLog))
    {
        PrintRecipt(TRUE);
    }
    
    return;
}

/*****************************************************************************
** Description :  Reprint specified transaction by trace no
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportPrintSpecifiedTrans(void)
{
    u8 buf[64];
	
	
    if (0 >= RecordGetNum())
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }

    while (1)
    {
        //get original trace no
        memset(buf, 0, sizeof(buf));
        if (!TrnInputTraceNo(buf))
        {
            return;
        }

        memset(&gstTransData.stTransLog, 0, sizeof(ST_TRANSLOG));
        if (SDK_OK == RecordSearch(LOG_MSG_TRACENO, buf, &gstTransData.stTransLog)
            && FALSE == gstTransData.stTransLog.stTransStatus.bIsNeedReversal
            && FALSE == gstTransData.stTransLog.stTransStatus.bIsIccFailTrans)
        {
			 //added by jeff 20170925 for printing iso8583
			Print8583Msg(gstTransData.stTransLog.stPrintIso8583.hePrintSendBuf,gstTransData.stTransLog.stPrintIso8583.iSendLen);
			Print8583Msg(gstTransData.stTransLog.stPrintIso8583.hePrintRecvBuf,gstTransData.stTransLog.stPrintIso8583.iRecvLen);
            PrintRecipt(TRUE);
            return;
        }
        else
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_TRANS_NOT_FOUND, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_REINPUT, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_OPERATE))
            {
                continue;
            }
            return;
        }
    }
    return;
}

/*****************************************************************************
** Description :  Print transaction detail(all transaction)
** Parameters  :  None 
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 ReportPrintTransDetail(void)
{
    s32 i, num;
    ST_TRANSLOG st_translog;
    bool flag = TRUE;
    s32 key;

    num = RecordGetNum();
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_DETAIL, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_STOP, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    for(i = 0; i < num; i++)
    {
        key = sdkKbGetKey();
        if (SDK_KEY_ESC == key)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_STOP_PRINT, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_YES, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_PRESS_CANCEL_NO, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                return SDK_ERR;
            }
            
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_DETAIL, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_STOP, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
        }
        
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        if(SDK_OK != RecordRead(i, &st_translog))
        {
            return SDK_ERR;
        }

        if(!TrnCheckPrintDetail(&st_translog))
        {
            continue;
        }

        if(flag)
        {
            if(SDK_OK != PrintDetailReportHeader("DETAIL REPORT"))
            {
                return SDK_ERR;
            }
            flag = FALSE;
        }

        if(SDK_OK != PrintDetailReport(&st_translog))
        {
            return SDK_ERR;
        }
    }

    if(!flag)
    {
        PrintDetailReportFooter();
    }

    DispTransSucc();
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Print transaction detail(offline transaction and upload fail)
** Parameters  :  None 
** Return      :  (1)SDK_OK : success
                  (2)SDK_ERR : fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 ReportPrintErrSendTransDetail(void)
{
    s32 i, num;
    ST_TRANSLOG st_translog;
    bool flag = TRUE;
    s32 key;
    
    ST_RECORD_FILTER st_filter[DB_MAXFILTER];
    s32 value1, value2, value3, value4;
    
    memset(st_filter, 0, sizeof(st_filter));
    value1 = UPLOAD_BATCHDONE_OFFFAIL;
    value2 = UPLOAD_BATCHDONE_OFFDECLINE;
    value3 = UPLOAD_OFFLINE_DECLINE;
    value4 = UPLOAD_OFFLINE_FAIL;
    
    st_filter[0].iId = LOG_STAT_UPLOADSTATUS;
    st_filter[0].eMode = FILTER_MULTI;
    st_filter[0].pasValue[0] = &value1;
    st_filter[0].pasValue[1] = &value2;
    st_filter[0].pasValue[2] = &value3;
    st_filter[0].pasValue[3] = &value4;
    st_filter[0].iNum = 4;
    
    st_filter[1].iId = -1;

    num = RecordGetNumEx(st_filter);
    
    DispClearContent();
    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_DETAIL, SDK_DISP_DEFAULT);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_STOP, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    for(i = 0; i < num; i++)
    {
        key = sdkKbGetKey();
        if (SDK_KEY_ESC == key)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_STOP_PRINT, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_ENTER_YES, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_PRESS_CANCEL_NO, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            if(SDK_KEY_ENTER == sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_OPERATE))
            {
                return SDK_ERR;
            }
            
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_PRINT_DETAIL, SDK_DISP_DEFAULT);
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_STOP, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
        }
        
        memset(&st_translog, 0, sizeof(ST_TRANSLOG));
        if(SDK_OK != RecordSearchEx(st_filter, i, &st_translog))
        {
            return SDK_ERR;
        }

        if(flag)
        {
            if(SDK_OK != PrintDetailReportHeader("FAILED OFFLINE TRXN DETAIL"))
            {
                return SDK_ERR;
            }
            flag = FALSE;
        }

        if(SDK_OK != PrintDetailReport(&st_translog))
        {
            return SDK_ERR;
        }
    }
    
    if(!flag)
    {
        PrintDetailReportFooter();
    }
    
    return SDK_OK;
}

/*****************************************************************************
** Description :  Reprint transaction detail(all transaction)
** Parameters  :  None 
** Return      :  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportRePrintTransDetail(void)
{
    if (0 >= RecordGetNum())
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return ;
    }
    
    ReportPrintTransDetail();
}

/*****************************************************************************
** Description :  Reprint transaction total
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportPrintTransTotal(void)
{
    ST_SETTLE st_settle;
    
    if (0 >= RecordGetNum())
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_TRANS, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }

    memset(&st_settle, 0, sizeof(ST_SETTLE));
    if(SDK_OK != SettleGetTotalAmount(&st_settle))
    {
        return;
    }
    
    PrintTotalReport(&st_settle);

    return;
}

/*****************************************************************************
** Description :  Rreprint the settlement transaction
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void ReportPrintSettle(void)
{
    ST_SETTLE st_settle;
    ST_BATCHUP_INFO st_batch;

    if(SDK_OK != SettleReadInfo(&st_settle) || SDK_OK == BatchUpReadInfo(&st_batch))
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_NO_SETTLE_INFO, SDK_DISP_DEFAULT);
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ESC | SDK_KEY_MASK_ENTER, TMR_PROMPT);
        return;
    }
    
    SettleReprint();

    return;
}

/*****************************************************************************
** Description :  Display and handles QueryTrans menu item.
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void MenuQueryTrans(void)
{
    ST_MENU st_menu = 
    {
        STR_FUNC_TRANS_QUERY,
        MENU_NUMBER,
        0,    
        {
            {STR_FUNC_QUERY_ANY,     SDK_DISP_LDISP, FALSE, 0, ReportQuerySpecifiedTrans},
            {STR_FUNC_QUERY_DETAILS, SDK_DISP_LDISP, FALSE, 0, ReportQueryTransDetail}, 
            {STR_FUNC_QUERY_SUMMARY, SDK_DISP_LDISP, FALSE, 0, ReportQueryTransTotal},
            {{0}},
        }
    };

    while(1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

/*****************************************************************************
** Description :  Display and handles PrintTrans menu item.
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void MenuPrintTrans(void)
{
    ST_MENU st_menu = 
    {
        STR_FUNC_REPRINT,
        MENU_NUMBER,
        0,    
        {
            {STR_FUNC_REPRINT_LAST,   SDK_DISP_LDISP, FALSE, 0, ReportPrintLastTrans}, 
            {STR_FUNC_REPRINT_ANY,    SDK_DISP_LDISP, FALSE, 0, ReportPrintSpecifiedTrans},
            {STR_FUNC_DETAILS_REPORT, SDK_DISP_LDISP, FALSE, 0, ReportRePrintTransDetail},
            {STR_FUNC_SUMMARY_REPORT, SDK_DISP_LDISP, FALSE, 0, ReportPrintTransTotal},
            {STR_FUNC_REPRINT_SETTLE, SDK_DISP_LDISP, FALSE, 0, ReportPrintSettle},
            {{0}},
        }
    };

    while(1)
    {
        if(SDK_OK != MenuProcess(&st_menu, TMR_OPERATE))
        {
            return;
        }
    }
}

