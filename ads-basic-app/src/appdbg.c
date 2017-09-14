/******************************************************************************

            Copyright (C), Shenzhen Xinguodu Technology Co., LTD.

                       http://www.xinguodu.com/en/

******************************************************************************
   File Name     :
   Version       :
   Author        :  Steven
   Date          :  2016-11-09
   Description   :



******************************************************************************/
#include "global.h"
#include <sys/types.h>
#include <sys/fcntl.h>
/*----------------------------------------------------------------------------*/

/*****************************************************************************
** Descriptions:	Judge whether the data is an ASCII string
** Parameters:          const u8 *pData
                        u32 uiDataLen
** Returned value:
** Created By:		Steven 2016-11-09
** Remarks:
*****************************************************************************/
bool DbgIsAscStr(const u8 *pData, u32 uiDataLen)
{
    u32 i;

    for (i = 0; i < uiDataLen; i++)
    {
        if (pData[i] < 0x20 || pData[i] > 0x7F)
        {
            return false;
        }
    }

    return true;
}

/*****************************************************************************
** Descriptions:	Convert the hex data into ASCII format can print the converted string out.
** Parameters:          const u8 *pData
                        u32 uiDataLen
** Returned value:
** Created By:		Steven 2016-11-09
** Remarks:
*****************************************************************************/
void DbgTraceAsc(const u8 *pheData, u32 uiDataLen)
{
    s32 i;
    u8 temp[1024] = {0};

    memcpy(temp, pheData, uiDataLen);

    for (i = 0; i < uiDataLen; i++)
    {
        if (temp[i] < 0x20 || temp[i] > 0x7F)
        {
            temp[i] = '.';
        }
    }

    temp[i] = '\0';
}

/*****************************************************************************
** Descriptions:	Print the parsed ISO8583 fields as specified format.
** Parameters:      const u8 *pData
                    u32 uiDataLen
** Returned value:
** Created By:		Steven 2016-11-09
** Remarks:
*****************************************************************************/
void DbgTraceIso8583(u8 *pasTitle, SDK_8583_ST8583 *pstBag8583)
{
#ifndef XGD_SDK_DEBUG
    return;

#else
    u32 i;
    u8 buf[512];
    u8 buf1[1024];
    s32 siLen = 0;

    for (i = 0; i <= 64; i++)
    {
        if (sdk8583IsDomainExist(pstBag8583, i))
        {
            memset(buf, 0, sizeof(buf));
            siLen = 0;

            siLen = IsoGetField(pstBag8583, i, buf, sizeof(buf));

            if (siLen > 0)
            {
                if (DbgIsAscStr(buf, siLen))
                {
                    Trace(pasTitle, "[%03u][%03d][%s]\r\n", i, siLen, buf);
                }
                else
                {
                    memset(buf1, 0, sizeof(buf1));  //HEX will be marked with "*"
                    sdkBcdToAsc(buf1, buf, siLen);
                    Trace(pasTitle, "[%03u][%03d][%s]*\r\n", i, siLen, buf1);
                }
            }
        }
    }

#endif
}

void *DbgPrintIso8583(u8 *pasTitle,void *arg)
{
#ifndef JEFF_DEBUG
	return (void*)0;
#else
 	u32 i;
    u8 buf[512];
    u8 buf1[1024];
    s32 siLen = 0;
	SDK_8583_ST8583 *pstBag8583;
	SDK_PRINT_FONT st_font;

	pstBag8583 = arg;
	//init printer
	sdkPrintInit();
    PrintSetFont(&st_font, PRINT_FONT_HALF);
    sdkPrintStr(pasTitle, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
    for (i = 0; i <= 64; i++)
    {
        if (sdk8583IsDomainExist(pstBag8583, i))
        {
            memset(buf, 0, sizeof(buf));
            siLen = 0;

            siLen = IsoGetField(pstBag8583, i, buf, sizeof(buf));

            if (siLen > 0)
            {
                if (DbgIsAscStr(buf, siLen))
                {
                	snprintf(buf1,1024,"[%03u][%03d][%s]\r\n", i, siLen, buf);
					sdkPrintStr(buf1, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
                }
                else
                {
                    memset(buf1, 0, sizeof(buf1));  //HEX will be marked with "*"
                    sdkBcdToAsc(buf1, buf, siLen);
					sdkPrintStr(buf1, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
                }
            }
        }
    }
	sdkPrintStart();
	return (void*)0;
#endif	
}

bool DbgPrintHex8583(u8 *pasTitle,const u8 *pheData, s32 uiDataLen)
{
#ifndef JEFF_DEBUG
	return true;
#else
	u8 buf[2028+1];
	SDK_PRINT_FONT st_font;
	if(uiDataLen > 1024 || uiDataLen < 0){
		return false;
	}
	//init printer
	sdkPrintInit();
    PrintSetFont(&st_font, PRINT_FONT_HALF);
	sdkPrintStr(pasTitle, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
	memset(buf,0,sizeof(buf));
	sdkBcdToAsc(buf,pheData, uiDataLen);
	sdkPrintStr(buf, st_font, SDK_PRINT_LEFTALIGN, 0, 0);
	sdkPrintStart();
	return true;
#endif
}

s32 DbgSaveTran8583(s32 uiTranNO,SDK_8583_ST8583 *pstSentBag8583,SDK_8583_ST8583 *pstRecv8583,s32 uiOffset)
{
#ifndef JEFF_DEBUG
	return 0;
#else	
	s32 uiFd;
	ST_SAVED_DEBUG8583 stSavedDebug8583;
	

	uiFd = open(FILENAME_SAVED_8583_PKG,O_CREAT | O_RDWR,0644);
	if(uiFd < 0){
		return -1;
	}
	lseek(uiFd,sizeof(ST_SAVED_DEBUG8583) * uiOffset,SEEK_SET);
	stSavedDebug8583.sTranNo = uiTranNO;
	stSavedDebug8583.stSendBag8583 = *pstSentBag8583;
	stSavedDebug8583.stRecvBag8583 = *pstRecv8583;
	write(uiFd,&stSavedDebug8583,sizeof(stSavedDebug8583));
	close(uiFd);
	return 0;
#endif
}

s32 DbgReadTran8583(ST_SAVED_DEBUG8583 *pstSavedDebug8583,s32 uiOffset)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 uiFd;
	s32 uiRet;

	uiFd = open(FILENAME_SAVED_8583_PKG,O_RDONLY,0);
	if(uiFd < 0){
		return -1;
	}
	lseek(uiFd,sizeof(ST_SAVED_DEBUG8583) * uiOffset,SEEK_SET);
	uiRet = read(uiFd,pstSavedDebug8583,sizeof(ST_SAVED_DEBUG8583));
	close(uiFd);
	return uiRet;
#endif	
}

s32 DbgSaveDbgTranTotalNum(s32 uiSaveDebugNum)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 uiFd;

	uiFd = open(FILENAME_TATAL_SAVED_8383_NUM,O_CREAT | O_RDWR,0644);
	if(uiFd < 0){
		return -1;
	}
	write(uiFd,&uiSaveDebugNum,sizeof(s32));
	close(uiFd);
	return 0;
#endif	
}

s32 DbgReadDbgTranTotalNum(s32 *uiSavedDebugNum)
{
#ifndef JEFF_DEBUG
	return 0;
#else
	s32 uiFd;
	s32 uiRet;

	uiFd = open(FILENAME_TATAL_SAVED_8383_NUM,O_RDONLY,0);
	if(uiFd < 0){
		return -1;
	}
	uiRet = read(uiFd,uiSavedDebugNum,sizeof(s32));
	close(uiFd);
	return uiRet;
#endif
}

