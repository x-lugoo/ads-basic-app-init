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



