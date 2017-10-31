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


static SDK_SSL_HANDLE _pgSSL;
/*----------------------------------------------------------------------------*/
/*****************************************************************************
** Description :  Configure communication parameters to SDK
** Parameters  :  input:
                  (1)bool bIsUseBackup: whether use the backup parameters
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  Set the communication parameters to SDK, Usually call before 
                  create link
*****************************************************************************/
void CommuConfigParam(bool bIsUseBackup)
{
    SDK_COMM_STCOMMPARAM st_commparam;
    ST_COMMU_PARAM *pst_commuparam = NULL;

    memset(&st_commparam, 0, sizeof(st_commparam));
    st_commparam.ucDialTime = gstAppSysCfg.stCommuParam.ucDialTime * 1000;   // Maximum period of time for dialing before timeout
    st_commparam.ucReDialTimes = gstAppSysCfg.stCommuParam.ucReDialTimes;    // Times to try for redial

    pst_commuparam = &gstAppSysCfg.stCommuParam;

    st_commparam.eMode = pst_commuparam->uiCommuMode;
    switch (st_commparam.eMode)
    {
         // Setup Modem
         case SDK_COMM_MODEM:
            st_commparam.stCommInfo.stModemInfo.eLinkMode = SDK_COMM_LINK_MODE_SYN;             // Synchronization link mode
            st_commparam.stCommInfo.stPppWireLessInfo.bIsNeedExParam = 0;                       // Extended parameters are not needed
            strcpy(st_commparam.stCommInfo.stModemInfo.asOutLineNo, pst_commuparam->asPabxNO);  // PABX number
            strcpy(st_commparam.stCommInfo.stModemInfo.asPhone[0], pst_commuparam->asPhone1);   // Telephone Number 1
            strcpy(st_commparam.stCommInfo.stModemInfo.asPhone[1], pst_commuparam->asPhone2);   // Telephone Number 2
            strcpy(st_commparam.stCommInfo.stModemInfo.asPhone[2], pst_commuparam->asPhone3);   // Telephone Number 3
            break;

         // Setup GPRS
         case SDK_COMM_GPRS:
            st_commparam.bSocketConnectMode = 0;                                                     // Socket connection mode: 0->short, 1->long
            st_commparam.stCommInfo.stPppWireLessInfo.bIsNeedExParam = 0;                            // Extended parameters are not needed
            st_commparam.stCommInfo.stPppWireLessInfo.bIsNeedUser = pst_commuparam->bIsGprsNeedUser; // User and password are not needed
            strcpy(st_commparam.stCommInfo.stPppWireLessInfo.asGprsApn, pst_commuparam->asGprsAPN);  // APN
            if(pst_commuparam->bIsGprsNeedUser)
            {
                strcpy(st_commparam.stCommInfo.stPppWireLessInfo.asUsername, pst_commuparam->asGprsUser);    // User name
                strcpy(st_commparam.stCommInfo.stPppWireLessInfo.asPassword, pst_commuparam->asGprsUserPwd); // Password
            }
            if(!bIsUseBackup)
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asGprsHostIP1);   // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asGprsHostPort1);     // Server port
            }
            else
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asGprsHostIP2);   // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asGprsHostPort2);     // Server port
            }
            break;

         // Setup CDMA
         case SDK_COMM_CDMA:
            st_commparam.bSocketConnectMode = 0;                               // Socket connection mode: 0->short, 1->long
            st_commparam.stCommInfo.stPppWireLessInfo.bIsNeedExParam = 0;      // Extended parameters are not needed
            st_commparam.stCommInfo.stPppWireLessInfo.bIsNeedUser = 1;         // User and password are not needed
            if(pst_commuparam->bIsGprsNeedUser)
            {
                strcpy(st_commparam.stCommInfo.stPppWireLessInfo.asUsername, pst_commuparam->asCdmaUser);    // User name
                strcpy(st_commparam.stCommInfo.stPppWireLessInfo.asPassword, pst_commuparam->asCdmaUserPwd); // Password
            }
            if(!bIsUseBackup)
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asCdmaHostIP1);   // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asCdmaHostPort1);     // Server port
            }
            else
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asCdmaHostIP2);   // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asCdmaHostPort2);     // Server port
            }
            break;

         // Setup ETHERNET
         case SDK_COMM_ETHERNET:
            st_commparam.stCommInfo.stLanInfo.bIsDhcp = pst_commuparam->bIsNetDHCP;     // Disable DHCP
            st_commparam.stCommInfo.stLanInfo.bIsPPPoe = 0;                             // Not PPPoe
            if(0 == pst_commuparam->bIsNetDHCP)
            {
                strcpy(st_commparam.stCommInfo.stLanInfo.asNetClientIP, pst_commuparam->asNetLocalIP); // Local IP
                strcpy(st_commparam.stCommInfo.stLanInfo.asNetGate, pst_commuparam->asNetGateway);     // Local gateway
                strcpy(st_commparam.stCommInfo.stLanInfo.asNetMask, pst_commuparam->asNetMask);        // Local Subnet mask
            }
            
            if(!bIsUseBackup)
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asNetHostIP1);  // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asNetHostPort1);    // Server Port
            }
            else
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asNetHostIP2);  // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asNetHostPort2);    // Server Port
            }
            break;

         case SDK_COMM_WIFI:
            st_commparam.stCommInfo.stLanInfo.bIsDhcp = (bool)pst_commuparam->stWifiInfo.iDhcp;    // Disable DHCP
            st_commparam.stCommInfo.stLanInfo.bIsPPPoe = 0;                                        // Not PPPoe
            if(0 == pst_commuparam->stWifiInfo.iDhcp)
            {
                strcpy(st_commparam.stCommInfo.stLanInfo.asNetClientIP, pst_commuparam->stWifiInfo.cLocalIp); // Local IP
                strcpy(st_commparam.stCommInfo.stLanInfo.asNetGate, pst_commuparam->stWifiInfo.cGateWay);     // Local gateway
                strcpy(st_commparam.stCommInfo.stLanInfo.asNetMask, pst_commuparam->stWifiInfo.cMask);        // Local Subnet mask
            }
            if(!bIsUseBackup)
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asWifiHostIP1);   // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asWifiHostPort1);     // Server Port
            }
            else
            {
                strcpy(st_commparam.stServerInfo.asServerIP, pst_commuparam->asWifiHostIP2);   // Server IP
                strcpy(st_commparam.stServerInfo.asPort, pst_commuparam->asWifiHostPort2);     // Server Port
            }
            break;

         default:
           return;
    }

    // Configure communication device
    if (SDK_OK != sdkCommConfig(&st_commparam))
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CONFIGURATION_ERROR, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_WAITKEY);
        return;
    }
}

/*****************************************************************************
** Description :  Create link in non-blocking mode in advance
** Parameters  :  None 
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  if communication mode is:
                  GPRS or CDMA: only execute PPP logon
                  MODEM: execute dailing
                  othe mode: do nothing
*****************************************************************************/
void CommuPreLink(void)
{
    if (SDK_COMM_MODEM == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        sdkCommPre();
    }
    else if (SDK_COMM_GPRS == gstAppSysCfg.stCommuParam.uiCommuMode ||
             SDK_COMM_CDMA == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        sdkCommCreatePPP(0);
    }
}

/*****************************************************************************
** Description :  Open ethernet device and set local parameters 
** Parameters  :  None 
** Return      :  (1)TRUE: success 
                  (2)FALSE: fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool CommuOpenEthernet(void)
{
    SDK_COMM_STLANPARAM st_lanparam;

    memset(&st_lanparam, 0, sizeof(st_lanparam));
    st_lanparam.bIsDhcp = gstAppSysCfg.stCommuParam.bIsNetDHCP;

    if (!st_lanparam.bIsDhcp)
    {
        strcpy(st_lanparam.asNetClientIP, gstAppSysCfg.stCommuParam.asNetLocalIP);
        strcpy(st_lanparam.asNetMask, gstAppSysCfg.stCommuParam.asNetMask);
        strcpy(st_lanparam.asNetGate, gstAppSysCfg.stCommuParam.asNetGateway);
        strcpy(st_lanparam.asDnsIP, gstAppSysCfg.stCommuParam.asNetDNS1);
    }
    return (SDK_OK == sdkExtOpenEthernet(&st_lanparam)) ? TRUE : FALSE;
}

/*****************************************************************************
** Description :  Open wifi device and connect to the hotspot
** Parameters  :  None 
** Return      :  (1)TRUE: success 
                  (2)FALSE: fail
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool CommuOpenWiFi(void)
{
    s32 ret;

    ret = sdkWIFICheck();
    if (SDK_WIFI_LOGOFF == ret || SDK_WIFI_FAIL == ret)
    {    
        sdkWIFIDisConnect();
        if (SDK_WIFI_SUCCESS != sdkWIFIConnect(&gstAppSysCfg.stCommuParam.stWifiInfo))
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CONNECT_WIFI_FAILED, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_WAITKEY);
            return FALSE;
        }
    }
    return TRUE;
}

/*****************************************************************************
** Description :  Connect to the host with SSL protocol
** Parameters  :  input:
                  (1)s32 iTimeOut: connect timeout(unit: second) 

** Return      :  (1)SDK_ERR: connect fail
                  (2)SDK_OK: connect success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  1.Create a SSL connection need 3 files:
                    (1)root certificate: necessary
                    (2)client certificate: no necessary(following the host)
                    (3)private key: no necessary(following the host)
                  put these files to the application private directory(path is 
                  "/mtd0/xxxxxd" "xxxxx" is your appid)
                  The certificate format is PEM default, change the 5th parameter
                  of "sdkSslLoadCACertKey" to change the format.
                  
                  2.The SSL protocol is SSLv3.0 default, change the 2th parameter
                  of "sdkSslSetOption" to change the protocol
*****************************************************************************/
s32 CommuSslConnect(s32 iTimeOut)
{
    s32 ret = 0;
    s32 cipher = -1;
    u8   ip[16]; 
    u32  port = 0; 
    u8 ca_path[128], clientca_path[128], clientkey_path[128];
    
    memset(ca_path, 0, sizeof(ca_path));
    memset(clientca_path, 0, sizeof(clientca_path));
    memset(clientkey_path, 0, sizeof(clientkey_path));
    sdkSysGetCurAppDir(ca_path);
    sdkSysGetCurAppDir(clientca_path);
    sdkSysGetCurAppDir(clientkey_path);
    strcat(ca_path, "ca.cert");
    strcat(clientca_path, "client.cert");
    strcat(clientkey_path, "key.cert");

    CommuConfigParam(FALSE);
    
    if(SDK_COMM_ETHERNET == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        memcpy(ip, gstAppSysCfg.stCommuParam.asNetHostIP1, sizeof(ip));
        port = atoi(gstAppSysCfg.stCommuParam.asNetHostPort1);
        if (!CommuOpenEthernet())
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_OPEN_ETH0_FAILED, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_WAITKEY);
            return SDK_ERR;
        }
    }
    else if(SDK_COMM_GPRS == gstAppSysCfg.stCommuParam.uiCommuMode)
    {                
        memcpy(ip, gstAppSysCfg.stCommuParam.asGprsHostIP1, sizeof(ip));
        port = atoi(gstAppSysCfg.stCommuParam.asGprsHostPort1);
        ret = sdkCommCreatePPP(20 * 1000);
        Trace("commu", "sdkCommCreatePPP() = %d\r\n", ret);
        if (SDK_OK != ret)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CREATE_PPP_FAILED, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_WAITKEY);
            return SDK_ERR;
        }
    }
    else if(SDK_COMM_WIFI == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        memcpy(ip, gstAppSysCfg.stCommuParam.asWifiHostIP1, sizeof(ip));
        port = atoi(gstAppSysCfg.stCommuParam.asWifiHostPort1);
        if (!CommuOpenWiFi())
        {
            return SDK_ERR;
        }
    }
    else if(SDK_COMM_CDMA == gstAppSysCfg.stCommuParam.uiCommuMode)
    {
        memcpy(ip, gstAppSysCfg.stCommuParam.asCdmaHostIP1, sizeof(ip));
        port = atoi(gstAppSysCfg.stCommuParam.asCdmaHostPort1);
        ret = sdkCommCreatePPP(20 * 1000);
        Trace("commu", "sdkCommCreatePPP() = %d\r\n", ret);
        if (SDK_OK != ret)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_CREATE_PPP_FAILED, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();
            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_WAITKEY);
            return SDK_ERR;
        }
    }
    else
    {
        return SDK_ERR;
    }
      
    // CA file location
    if (!sdkAccessFile(ca_path) || !sdkAccessFile(clientca_path) || !sdkAccessFile(clientkey_path))
    {
        Trace("commu", "CA file check fail\r\n");
        return SDK_ERR;
    }
    
    // Create an SSL handle
    if(NULL == _pgSSL)
    {
        ret = sdkSslNew(&_pgSSL);
        if (SDK_SSL_OK != ret)
        {
            Trace("commu", "Create an SSL handle fail[%d]\r\n", ret);
            return SDK_ERR;
        }
    }
    
    // Set SSL options
    ret = sdkSslSetOption(_pgSSL, SDK_PROTOCOL_SSLv3, cipher);
    if (SDK_SSL_OK == ret)
    {
        // Load CA file
        ret = sdkSslLoadCACertKey(_pgSSL, ca_path, clientca_path, clientkey_path, SDK_SSL_FILE_PEM);
        if (SDK_SSL_OK == ret)
        {
            // Connect server
            ret = sdkSslConnect(_pgSSL, ip, port, iTimeOut);
            if (SDK_SSL_OK == ret)
            {
                return SDK_OK;
            }
        }
    }
    Trace("commu", "SSL connect fail[%d]\r\n", ret);
    
    sdkSslDisconnect(_pgSSL);
    sdkSslFree(_pgSSL);
    _pgSSL = NULL;
    return SDK_ERR;
}

/*****************************************************************************
** Description :  Connect to the host
** Parameters  :  None 
** Return      :  (1)SDK_ERR: connect fail
                  (2)SDK_OK: connect success
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 CommuCreateLink(void)
{
    s32 ret;
    
    CommuConfigParam(FALSE);

    // Create a link
    if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
    {
        if(SDK_COMM_MODEM == gstAppSysCfg.stCommuParam.uiCommuMode &&
            SDK_COMM_LINK_DIAL_START == sdkCommCheckCommState(0))
        {
            ret = SDK_OK;
        }
        else
        {
            ret = sdkCommCreateLink();
        }
    }
    else
    {
        ret = CommuSslConnect(gstAppSysCfg.stCommuParam.ucDialTime * 1000);
    }

    if (SDK_OK != ret)
    {
        // Destroy link on error
        if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
        {
            sdkCommDestoryLink();
        }
        else
        {
            sdkSslDisconnect(_pgSSL);
            sdkSslFree(_pgSSL);
            _pgSSL = NULL;
        }
        
        switch (ret)
        {
             // Time out
             case SDK_TIME_OUT:
                TrnSetStatus(ERR_LINK_TIMEOUT);
                break;

             case SDK_COMM_NOLINE: // No telephone line detected
             case SDK_COMM_NOSTAKE:// Handle is lifted off
             case SDK_COMM_ENGAGED:// Line busy
             case SDK_COMM_NO_SIM:// No SIM card delected for wireless communication
             case SDK_COMM_LINKFAIL:// Link failure
                TrnSetStatus(ret);
                break;

             // Unkown error
             default:
                TrnSetStatus(ERR_LINK);
                break;
        }

        sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_WAITKEY);
        return SDK_ERR;
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Exchange ISO8583 messages for transactions
** Parameters  :  input:
                  (1)SDK_ICC_TRADE_PARAM *pstIccTradeParam : IC card transaction parameter
                  (2)s32 (*pPackFun)(SDK_8583_ST8583 *) : Packet message callback function
                  (3)BOOL bIsReversal : Is this transaction need reversal
                  (4)BOOL bIsPreposition : Is this transaction need deal preposition transaction
                  (5)BOOL bIsSaveRecord  : Is this transaction need save record
                  
** Return      :  (1)SDK_PARA_ERR: input parameter error
                  (2)SDK_ERR: process fail
                  (3)SDK_ESC: user cancel
                  (4)ERR_RESP_CODE : wrong response code
                  (5)SDK_OK: set CAPKs success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  This function process the preposition transaction, reversal, 
                  packet message, communication with host, IC card transaction flow,
                  and save transaction record
*****************************************************************************/
s32 CommuExchangeIsoMsg(SDK_ICC_TRADE_PARAM *pstIccTradeParam, 
                        s32 (*pPackFun)(SDK_8583_ST8583 *), 
                        BOOL bIsReversal,  
                        BOOL bIsPreposition,
                        BOOL bIsSaveRecord)
{
    s32 ret;
    u8 i;
    ST_MSGINFO *pst_msginfo = NULL;
    E_ICCRET e_iccret;
    u8 buf[64];
    ST_CARDINFO *pst_cardinfo = NULL;

    if(NULL == pPackFun)
    {
        return SDK_PARA_ERR;
    }

    pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;

    // process preposition transation
    if(bIsPreposition)
    {
        DispSaveScreen();
        DispTitle(STR_TRANS_OFFLINE_UPLOAD);
        if(SDK_OK != OfflineSendMsg())
        {
            return SDK_ERR;
        }
        DispTitle(STR_TRANS_SCRIPT_UPLOAD);
        if(SDK_OK != ScriptSendMsg())
        {
            return SDK_ERR;
        }
        DispTitle(STR_TRANS_REVERSAL);
        if(SDK_OK != ReversalSendMsg())
        {
            return SDK_ERR;
        }
        DispRestoreScreen();
    }

    for(i = 0; i < 3; i++)
    {
        DispClearContent();
        sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_LINKING, SDK_DISP_DEFAULT);
        sdkDispBrushScreen();
        
        // Create a communication link
        ret = CommuCreateLink();
        if (SDK_OK != ret)
        {
            return SDK_ERR;
        }
        
        // Pack login 8583 message
        ret = pPackFun(&gstSendPacket);

        if (0 == ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
            
        // Encrypt sending packet
        ret = IsoPackMsgMac(&gstSendPacket);
        if (SDK_OK != ret)
        {
            TrnSetStatus(ERR_PACK_MSG);
            return SDK_ERR;
        }
        
        TrnUpdateTransDataSend(&gstSendPacket);
        
        // save reversal
        if(bIsReversal)
        {
            gstTransData.stTransLog.stTransStatus.bIsNeedReversal = TRUE;
            gstTransData.stTransLog.stTransStatus.ucReversalReason = 0x06;     //other reason
            if(SDK_OK != RecordAppend(&gstTransData.stTransLog))
            {
                TrnSetStatus(ERR_FILE_SYSTEM);
                return SDK_ERR;
            }
        }
        
        memset(&gstRecvPacket, 0, sizeof(gstRecvPacket));

        // Exchange ISO8583 messages
        ret = CommuExchangeIsoPacket(&gstSendPacket, &gstRecvPacket);
        if(SDK_OK == ret)    //host approves with "00" in field39 but chip card rejects the transaction
        {            
            TrnGetIccDataFromMsg(&gstRecvPacket);
            
            //issuer-to-card data processing, script processing, 2nd Generate Application Cryptogram
            if ((NULL != pstIccTradeParam)
                && (SDK_ICC_ICC == pst_cardinfo->stCardParam.ucCardMode 
                || SDK_ICC_RF == pst_cardinfo->stCardParam.ucCardMode)
                && (SDK_ICC_ALL_FLOW == pstIccTradeParam->eFlowMode))
            {
                EmvOptImportRespData(&gstRecvPacket);
                e_iccret = EmvOptTransFlowOnlineProcess(pstIccTradeParam, &pst_cardinfo->stCardParam);
                if (ICCRET_ONLINE_APPROVE != e_iccret)
                {
                    if(!TrnCheckResponseCode(pst_msginfo->asRespCode))
                    {
                        if(bIsReversal)
                        {
                            if(SDK_OK != RecordDeleteLast())
                            {
                                TrnSetStatus(ERR_FILE_SYSTEM);
                                return SDK_ERR;
                            }
                        }
                        TrnSetStatus(ERR_RESP_CODE);
                    }
                    else
                    {
                        TrnSetStatus(ERR_ICC_AUTHFAIL);
                    }
                    return SDK_ERR;
                }

                ScriptGetResult();
            }

            if(bIsReversal)
            {
                gstTransData.stTransLog.stTransStatus.bIsNeedReversal = FALSE;
                if(SDK_OK != RecordUpdate(&gstTransData.stTransLog))
                {
                    TrnSetStatus(ERR_FILE_SYSTEM);
                    return SDK_ERR;
                }
            }
            
            // Process wrong pin
            if(0 == memcmp(pst_msginfo->asRespCode, "55", 2) && TRANSID_SALE == gstTransData.stTransLog.eTransID)
            {
                if (2 == i)
                {
                    if(bIsReversal)
                    {
                        if(SDK_OK != RecordDeleteLast())
                        {
                            TrnSetStatus(ERR_FILE_SYSTEM);
                            return SDK_ERR;
                        }
                    }
                    TrnSetStatus(ERR_RESP_CODE);
                    return SDK_ERR;
                }
                else
                {
                    sdkSysBeep(SDK_SYS_BEEP_ERR);
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_TRANS_FAILED, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_PIN_ERR,      SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_PRESS_ENTER_RETRY, SDK_DISP_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE5, 0, STR_PRESS_CANCEL_EXIT, SDK_DISP_DEFAULT);
                    sdkDispBrushScreen();
                    ret = sdkKbWaitKey(SDK_KEY_MASK_ALL, TMR_OPERATE);
                }

                if (SDK_KEY_ENTER == ret)
                {
                    memset(buf, 0, sizeof(buf));
                    memset(gstTransData.hePIN, 0, sizeof(gstTransData.hePIN));
                    TrnFormatAmount(buf, gstTransData.stTransLog.stMsgInfo.asAmount, TRUE);
                    // Display amount and prompt for password
                    DispClearContent();
                    sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_AMOUNT, SDK_DISP_LEFT_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE3, 0, buf, SDK_DISP_RIGHT_DEFAULT);
                    sdkDispFillRowRam(SDK_DISP_LINE4, 0, STR_INFO_INPUT_PIN, SDK_DISP_LEFT_DEFAULT);
                    sdkDispBrushScreen();
                    // Input password
                    ret = TrnInputPin(TRUE, gstTransData.stTransLog.stMsgInfo.asAmount, 
                                      &pst_cardinfo->stCardData, gstTransData.hePIN, SDK_DISP_LINE5);
                    if (SDK_OK != ret && SDK_PED_NOPIN != ret)
                    {
                        return SDK_ESC;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    TrnSetStatus(ret);
                    return SDK_ESC;
                }
            }
            else if(TrnCheckResponseCode(pst_msginfo->asRespCode))
            {
                if(bIsSaveRecord && bIsReversal)
                {
                    gstTransData.stTransLog.stTransStatus.bIsNeedRePrint = TRUE;
                    gstTransData.stTransLog.stTransStatus.bIsNeedReversal = FALSE;
                    gstTransData.stTransLog.stTransStatus.ucReversalReason = 0;
                    if(SDK_OK != RecordUpdate(&gstTransData.stTransLog))
                    {
                        TrnSetStatus(ERR_FILE_SYSTEM);
                        return SDK_ERR;
                    }
                }
                else if(bIsSaveRecord)
                {
                    gstTransData.stTransLog.stTransStatus.bIsNeedRePrint = TRUE;
                    if(SDK_OK != RecordAppend(&gstTransData.stTransLog))
                    {
                        TrnSetStatus(ERR_FILE_SYSTEM);
                        return SDK_ERR;
                    }
                }
                else if(FALSE == bIsSaveRecord && gstTransData.stTransLog.stTransStatus.bIsNeedScript)
                {
                    gstTransData.stTransLog.stTransStatus.bIsNeedRePrint = FALSE;
                    gstTransData.stTransLog.stTransStatus.bIsNeedReversal = FALSE;
                    gstTransData.stTransLog.stTransStatus.bIsIccFailTrans = TRUE;
                    if(SDK_OK != RecordAppend(&gstTransData.stTransLog))
                    {
                        TrnSetStatus(ERR_FILE_SYSTEM);
                        return SDK_ERR;
                    }
                }
                TrnSyncDateTime(&gstTransData);
                return SDK_OK;
            }
            else if(TRANSID_SETTLE == gstTransData.stTransLog.eTransID)     //settle have no #39
            {
                return SDK_OK;
            }
            else
            {
                if(bIsReversal)
                {
                    if(SDK_OK != RecordDeleteLast())
                    {
                        TrnSetStatus(ERR_FILE_SYSTEM);
                        return SDK_ERR;
                    }
                }
                TrnSetStatus(ERR_RESP_CODE);
                return ERR_RESP_CODE;
            }
        }
        else if((ERR_RECV == ret || ERR_RECV_TIMEOUT == ret) && bIsReversal)
        {
            gstTransData.stTransLog.stTransStatus.ucReversalReason = 0x98;     //receive fail
            if(SDK_OK != RecordUpdate(&gstTransData.stTransLog))
            {
                TrnSetStatus(ERR_FILE_SYSTEM);
                return SDK_ERR;
            }
            break;
        }
        else if(ERR_CALCMAC == ret && bIsReversal)
        {
            gstTransData.stTransLog.stTransStatus.ucReversalReason = 0xA0;     //wrong mac
            if(SDK_OK != RecordUpdate(&gstTransData.stTransLog))
            {
                TrnSetStatus(ERR_FILE_SYSTEM);
                return SDK_ERR;
            }
            break;
        }
        else if(ERR_UNPACK_MSG == ret)
        {
            break;
        }
        else
        {
            if(bIsReversal)
            {
                if(SDK_OK != RecordDeleteLast())
                {
                    TrnSetStatus(ERR_FILE_SYSTEM);
                    return SDK_ERR;
                }
            }
            break;
        }
    }
    return SDK_ESC;
}

/*****************************************************************************
** Description :  Exchange ISO8583 packets between POS and HOST
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstIsoMsgSend : message buffer for send
                  output:
                  (1)SDK_8583_ST8583 *pstIsoMsgRecv : message buffer for reveive
                  
** Return      :  (1)SDK_ERR : send data fail
                  (2)ERR_RECV_TIMEOUT : receive data timeout
                  (3)ERR_RECV : receive data fail
                  (4)SDK_OK : succeeded
                  (5)ERR_CALCMAC : Calculating MAC failed
                  (6)ERR_UNPACK_MSG : Unpacking failed
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 CommuExchangeIsoPacket(SDK_8583_ST8583 *pstIsoMsgSend, SDK_8583_ST8583 *pstIsoMsgRecv)
{
    s32 ret;
    u8 bag_data[SDK_8583_BAGMAXLEN + 2];
    u32 len = SDK_8583_BAGMAXLEN;
    
    //DispClearContent();
    sdkDispClearRowRam(SDK_DISP_LINE3);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_SENDING, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();
    
    // Send transation data
    TraceHex("commu", "ISO8583 send", pstIsoMsgSend->ucBagData, pstIsoMsgSend->nBagLen);
    DbgTraceIso8583("commu", pstIsoMsgSend);

    if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
    {
        if(LENTYPE_BCD == gstAppSysCfg.stCommuParam.eMsgLenType)
        {
            sdkU16ToHex(bag_data, pstIsoMsgSend->nBagLen, 2);
            memcpy(&bag_data[2], pstIsoMsgSend->ucBagData, pstIsoMsgSend->nBagLen);
            ret = sdkCommSendData(bag_data, pstIsoMsgSend->nBagLen + 2, SDK_COMM_TRANSPARENT);
        }
        else
        {
            ret = sdkCommSendData(pstIsoMsgSend->ucBagData, pstIsoMsgSend->nBagLen, SDK_COMM_SEND8583);
        }
    }
    else
    {
        sdkU16ToHex(bag_data, pstIsoMsgSend->nBagLen, 2);
        memcpy(&bag_data[2], pstIsoMsgSend->ucBagData, pstIsoMsgSend->nBagLen);
        ret = sdkSslSend(_pgSSL, bag_data, pstIsoMsgSend->nBagLen + 2);
    }

    if (ret < SDK_OK)
    {
        Trace("commu", "sdkCommSendData: [%d]\n", ret);
        if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
        {
            sdkCommDestoryLink();
        }
        else
        {
            sdkSslDisconnect(_pgSSL);
            sdkSslFree(_pgSSL);
            _pgSSL = NULL;
        }
        TrnSetStatus(ERR_SEND);
        return SDK_ERR;
    }
    //DispClearContent();
    sdkDispClearRowRam(SDK_DISP_LINE3);
    sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_RECEIVING, SDK_DISP_DEFAULT);
    sdkDispBrushScreen();

    TrnIncTraceNo(1);

    // Receive response data
    if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
    {
        ret = sdkCommRecvData(pstIsoMsgRecv->ucBagData, len, gstAppSysCfg.stCommuParam.ucRecvTime * 1000, NULL);
    }
    else
    {
        ret = sdkSslReceive(_pgSSL, pstIsoMsgRecv->ucBagData, &len, gstAppSysCfg.stCommuParam.ucRecvTime * 1000);
    }

    if (ret < 0)
    {
        // Display error messages
        switch (ret)
        {
            case SDK_COMM_WAVELOST:
            case SDK_COMM_BUFFER_ERROR:
                TrnSetStatus(ret);
                break;

            case SDK_TIME_OUT:
                TrnSetStatus(ERR_RECV_TIMEOUT);
                break;

            default:
                TrnSetStatus(ERR_RECV);
                break;
        }

        // Destroy the link
        if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
        {
            sdkCommDestoryLink();
        }
        else
        {
            sdkSslDisconnect(_pgSSL);
            sdkSslFree(_pgSSL);
            _pgSSL = NULL;
        }

        if(SDK_TIME_OUT == ret)
        {
            return ERR_RECV_TIMEOUT;
        }
        return ERR_RECV;
    }
    
    if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
    {
        sdkCommDestoryLink();
    }
    else
    {
        sdkSslDisconnect(_pgSSL);
        sdkSslFree(_pgSSL);
        _pgSSL = NULL;
    }

    if(0 == gstAppSysCfg.stCommuParam.bIsWithSSL)
    {
        pstIsoMsgRecv->nBagLen = ret;
    }
    else
    {
        pstIsoMsgRecv->nBagLen = len - 2;
        memmove(pstIsoMsgRecv->ucBagData, &pstIsoMsgRecv->ucBagData[2], pstIsoMsgRecv->nBagLen);
    }

    // Parse the response message
    TraceHex("commu", "ISO8583 received", pstIsoMsgRecv->ucBagData, pstIsoMsgRecv->nBagLen);

    if (0 == IsoParse8583(pstIsoMsgRecv))
    {
        TrnSetStatus(ERR_UNPACK_MSG);
        return ERR_UNPACK_MSG;
    }
    DbgTraceIso8583("commu", pstIsoMsgRecv);

    return TrnUpdateTransDataRecv(pstIsoMsgRecv);
}

