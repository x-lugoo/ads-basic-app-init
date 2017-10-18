diff --git a/ads-basic-app-jfcd/inc/global.h b/ads-basic-app-jfcd/inc/global.h
index 628833a..4311ce6 100755
--- a/ads-basic-app-jfcd/inc/global.h
+++ b/ads-basic-app-jfcd/inc/global.h
@@ -532,7 +532,8 @@ typedef struct
 #include "script.h"
 #include "print.h"
 #include "display.h"
-#include "appdbg.h"
+
+//#include "appdbg.h"
 
 /*-----------------------------------------------------------------------------
 *                           GLOBAL VARIABLES
@@ -542,6 +543,7 @@ EXTERN ST_APP_SYSCFG gstAppSysCfg;
 
 EXTERN u16 *pgScrBuff;      //screen buffer
 EXTERN u32 guiScrBuffSize;  //screen buffer size
+EXTERN u8  gucCommPort;     //communication port with pc 
 
 EXTERN ST_TRANSDATA gstTransData;       //transaction related information
 
diff --git a/ads-basic-app-jfcd/inc/policy.h b/ads-basic-app-jfcd/inc/policy.h
index cba86d6..9ecc367 100755
--- a/ads-basic-app-jfcd/inc/policy.h
+++ b/ads-basic-app-jfcd/inc/policy.h
@@ -66,14 +66,13 @@ typedef struct
 
 typedef enum
 {
-	POLICY_FIRST_REQUEST,
+	POLICY_FIRST_REQUEST = 100,
 	POLICY_CONFIRM_REQUEST,
 	
 }E_POLICY_REQUEST;
 
 
 
-extern s32 OutputPolicyDebugMsg(void);
 extern s32 OpenPolicyComm(void);
 extern s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen);
 extern s32 ClosePolicyComm(void);
@@ -81,7 +80,7 @@ extern s32 HandlePolicyMsg(void);
 extern s32 SavePolicyMsg(u8 *pheInputBuf,s32 iLen);
 extern bool VarifyPolicyMsg(u8 *pheInputBuf,s32 iLen);
 extern s32 CalcPolicyCRCValue(u8 *pheInputBuf,s32 iLen);
-extern s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyRequest);
+extern s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyRequest,bool bIsSuccess);
 extern s32 SendPolicyMsg(u8 *pheInputBuf,s32 iLen);
 #endif
 
diff --git a/ads-basic-app-jfcd/src/emv.c b/ads-basic-app-jfcd/src/emv.c
index 9aaa56a..b628c9f 100755
--- a/ads-basic-app-jfcd/src/emv.c
+++ b/ads-basic-app-jfcd/src/emv.c
@@ -119,6 +119,7 @@ static ST_EMV_TLV TabPaypassCfg[] =
 *****************************************************************************/
 s32 CbEmvInputAmount(u8 *pasAmount)
 {
+#if 0	
     u8 sale_amt[12 + 1] = {0}, cashback_amt[12 + 1] = {0};
     u8 amt1[6], amt2[6];
 
@@ -141,6 +142,8 @@ s32 CbEmvInputAmount(u8 *pasAmount)
     sdkBcdAdd(amt1, amt1, 6, amt2, 6);
     sdkBcdToAsc(pasAmount, amt1, 6);
     Trace("sale", "total amount(sale + cashback) = %s\r\n", pasAmount);
+#endif
+	memcpy(pasAmount,gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField.asAmount, 12);
     return SDK_OK;
 }
 
diff --git a/ads-basic-app-jfcd/src/main.c b/ads-basic-app-jfcd/src/main.c
index f2d21d6..7a1e383 100755
--- a/ads-basic-app-jfcd/src/main.c
+++ b/ads-basic-app-jfcd/src/main.c
@@ -24,7 +24,7 @@ void MainMenu(void);
 void OnCircle();
 
 #define USE_SDK_DEBUG 
-#undef USE_SDK_DEBUG
+//#undef USE_SDK_DEBUG
 
 //-----------------------------------------------------------------------------
 #ifdef XGD_SDK_DEBUG
@@ -42,8 +42,8 @@ DBG_FILTER DbgFilter =
 {
     TRUE,                  // whether in testing state
     DBG_OUTPUT_ALL,        // only block the tags of black list
-    DBG_MODE_PINPAD,//DBG_MODE_PINPAD,        // mode for Trace(), TraceHex(), Assert(), Verify().
-    DBG_ENABLE_PINPAD,//DBG_ENABLE_PINPAD,        // enable all trace modes
+    DBG_MODE_RS232,//DBG_MODE_PINPAD,        // mode for Trace(), TraceHex(), Assert(), Verify().
+    DBG_ENABLE_ALL,//DBG_ENABLE_PINPAD,        // enable all trace modes
 };
 #endif
 
@@ -141,8 +141,8 @@ void AppInit(void)
 		EmvInitCtlsParam();
 	}
 
-    //initialize policy comm and debug msg
-	OutputPolicyDebugMsg();
+    //initialize communcation port and  open policy comm
+    gucCommPort = SDK_COMM_UART_PINPAD;
 	OpenPolicyComm();
 	
     if(gstAppSysCfg.stSysParam.bIsExtPED)
@@ -239,7 +239,6 @@ void OnCircle(void)
 	gstTransData.stTransLog.eTransID = TRANSID_WELCOME;
     while(1)
     {
-		//printf("eTransID=%d,%s(%d)\n",gstTransData.stTransLog.eTransID,__FUNCTION__,__LINE__);
         switch(gstTransData.stTransLog.eTransID)
         {
             // process disp welcome screen
@@ -274,7 +273,6 @@ void OnCircle(void)
                 continue;
 
             case TRANSID_SALE:
-                memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
                 gstTransData.stTransLog.stMsgInfo.asAmount[0] = (u8)key;
                 DispBackground(FILE_BACKGROUND_BMP);
                 sdkDispSetFontColor(color);
@@ -304,11 +302,6 @@ void OnCircle(void)
             gstTransData.stTransLog.eTransID = TRANSID_MAINMENU;
 			continue;
         }
-        else if(key > SDK_KEY_0 && key <= SDK_KEY_9)
-        {
-            sdkSysBeep(SDK_SYS_BEEP_OK);
-            gstTransData.stTransLog.eTransID = TRANSID_SALE;
-        }
         else if(SDK_KEY_FUNCTION == key)
         {
             TrnSwitchApp();
@@ -342,7 +335,7 @@ void OnCircle(void)
             refresh = TRUE;
         }
 		iRet = HandlePolicyMsg();
-		if(SDK_OK == iRet)
+		if(POLICY_FIRST_REQUEST == iRet)
 		{
 			sdkSysBeep(SDK_SYS_BEEP_OK);
             gstTransData.stTransLog.eTransID = TRANSID_SALE;
@@ -366,11 +359,11 @@ void MainMenu(void)
         0,    
         {
             {STR_TRANS_LOGON,      SDK_DISP_LDISP, FALSE, 0, LogonTrans}, 
-            {STR_TRANS_SALE,       SDK_DISP_LDISP, FALSE, 0, OnSale},
-            {STR_TRANS_VOID,       SDK_DISP_LDISP, FALSE, 0, OnVoid},
-            {STR_TRANS_REFUND,     SDK_DISP_LDISP, FALSE, 0, OnRefund},
-            {STR_TRANS_TIP,        SDK_DISP_LDISP, FALSE, 0, OnAdjust},
-            {STR_TRANS_BALANCE,    SDK_DISP_LDISP, FALSE, 0, OnBalance},
+            //{STR_TRANS_SALE,       SDK_DISP_LDISP, FALSE, 0, OnSale},
+           // {STR_TRANS_VOID,       SDK_DISP_LDISP, FALSE, 0, OnVoid},
+           // {STR_TRANS_REFUND,     SDK_DISP_LDISP, FALSE, 0, OnRefund},
+           // {STR_TRANS_TIP,        SDK_DISP_LDISP, FALSE, 0, OnAdjust},
+           // {STR_TRANS_BALANCE,    SDK_DISP_LDISP, FALSE, 0, OnBalance},
             {STR_TRANS_SETTLEMENT, SDK_DISP_LDISP, FALSE, 0, OnSettle},
             {STR_TRANS_LOGOUT,     SDK_DISP_LDISP, FALSE, 0, LogoutTrans}, 
             {STR_FUNC_REPRINT,     SDK_DISP_LDISP, FALSE, 0, MenuPrintTrans}, 
diff --git a/ads-basic-app-jfcd/src/misc.c b/ads-basic-app-jfcd/src/misc.c
index dc87173..eac1b3b 100755
--- a/ads-basic-app-jfcd/src/misc.c
+++ b/ads-basic-app-jfcd/src/misc.c
@@ -2861,7 +2861,13 @@ void TrnEndProcess(void)
 {
     ST_CARDINFO *pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
     u32 tmr;
+	u8  ucPackBuf[512];
+	u8  ucDebugBuf[2048];
+	s32 iLen;
+	s32 iRet;
+	s32 i = 0;
 
+	Trace("xgd","pass ENDPROCESS");
     if(TRANSID_MAINMENU != gstTransData.stTransLog.eTransID 
         && TRANSID_UNKNOWN != gstTransData.stTransLog.eTransID
         && TRANSID_WELCOME != gstTransData.stTransLog.eTransID)
@@ -2869,7 +2875,18 @@ void TrnEndProcess(void)
         if(0 == TrnGetStatus())
         {
             sdkSysBeep(SDK_SYS_BEEP_OK);
-            
+            if(TRANSID_SALE == gstTransData.stTransLog.eTransID)
+			{
+				
+				PackPolicyMsg(ucPackBuf,&iLen,POLICY_FIRST_REQUEST,true);
+				iRet = SendPolicyMsg(ucPackBuf,iLen);
+				Trace("xgd","send policy msg iRet=%d\r\n",iRet);	
+				for(i = 0;i < iLen;i++)
+				{
+					snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucPackBuf[i]);
+				}
+				Trace("xgd"," iLen=%d,SendBuf=%s\r\n",iLen,ucDebugBuf);	
+            }
             if(TRANSID_BALANCE != gstTransData.stTransLog.eTransID)
             {
                 DispSuccResponse();
@@ -2878,6 +2895,18 @@ void TrnEndProcess(void)
         else
         {
             sdkSysBeep(SDK_SYS_BEEP_ERR);
+			if(TRANSID_SALE == gstTransData.stTransLog.eTransID)
+			{
+				
+				PackPolicyMsg(ucPackBuf,&iLen,POLICY_FIRST_REQUEST,false);
+				iRet = SendPolicyMsg(ucPackBuf,iLen);
+				Trace("xgd","send policy msg iRet=%d\r\n",iRet);	
+				for(i = 0;i < iLen;i++)
+				{
+					snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucPackBuf[i]);
+				}
+				Trace("xgd"," iLen=%d,SendBuf=%s\r\n",iLen,ucDebugBuf);	
+			}
             DispTransStatus();
         }
     }
diff --git a/ads-basic-app-jfcd/src/policy.c b/ads-basic-app-jfcd/src/policy.c
index a1481c7..bfccdc1 100755
--- a/ads-basic-app-jfcd/src/policy.c
+++ b/ads-basic-app-jfcd/src/policy.c
@@ -20,52 +20,37 @@
 
 /*----------------------------------------------------------------------------*/
 
-#define FILENAME_POLICY_LOG "/mtd0/res/policy.log"
-
-s32 OutputPolicyDebugMsg(void)
-{
-	s32 iFd;
-
-	iFd = open(FILENAME_POLICY_LOG,O_RDWR | O_CREAT,0644);
-	if(iFd < 0)
-	{
-		printf("open file %s error\n",FILENAME_POLICY_LOG);
-		return SDK_ERR;
-	}
-	dup2(iFd,1);//redirect iFd file describe symble  to stdout
-	close(iFd);
-	printf("start to collect debug log\n");
-	return SDK_OK;
-}
 
 s32 OpenPolicyComm(void)
 {
 	SDK_COMM_STUARTPARAM uartCfg;
 	s32 iRet;
-
+	
 	memset(&uartCfg,0,sizeof(SDK_COMM_STUARTPARAM));
-	uartCfg.ucCom = SDK_COMM_UART_PINPAD;
+	uartCfg.ucCom = gucCommPort;
 	uartCfg.uiBaudrate = 115200;
 	uartCfg.ucByteLen =  '8';
 	uartCfg.ucCheckBit = 'n';
 	uartCfg.ucStopBitLen = '1';
 	uartCfg.ucFlowControl = '0';
 	iRet = ClosePolicyComm();
-	printf("close commm iRet =%d, struction size =%d\n",iRet,sizeof(SDK_COMM_STUARTPARAM));
+	Trace("xgd","close commm iRet =%d\r\n",iRet);
 
     iRet = sdkCommOpenUart(&uartCfg);
-	printf("open commm iRet =%d\n",iRet);
+	Trace("xgd","open commm iRet =%d\r\n",iRet);
+
 	return iRet;
 	
 }
 
 s32 HandlePolicyMsg(void)
-{
-	u8 ucRecvBuf[512];
+{ 
+	u8  ucRecvBuf[512] = {0};
+	u8  ucDebugBuf[2048];
 	s32 iLen;
 	s32 iRet;
-	int i = 0;
-	u8  ucDebugBuf[2048];
+	s32 i = 0;
+	s32 iExistRecodeFlag = 0;
 	
 	iRet = RecvPolicyMsg(ucRecvBuf,&iLen);
 	if(iRet != SDK_OK)
@@ -76,45 +61,58 @@ s32 HandlePolicyMsg(void)
 	{
 		return SDK_ERR;
 	}
+
+	iRet = SavePolicyMsg(ucRecvBuf,iLen); 
+	if(iRet != SDK_OK)
+	{
+		return iRet;
+	}
 	if(0 == memcmp(&ucRecvBuf[1],"01",2))
 	{
-		SavePolicyMsg(ucRecvBuf,iLen);
-
-		PackPolicyMsg(ucRecvBuf,&iLen,POLICY_FIRST_REQUEST);
-		for(;i < iLen;i++)
+		Trace("xgd","entry first policy request\r\n");
+		return POLICY_FIRST_REQUEST;
+	}
+	else if(0 == memcmp(&ucRecvBuf[1],"02",2))
+	{
+		Trace("xgd","entry confirm policy request,policy number =%s\r\n",gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField.asPolicyNum);
+		iRet = RecordSearch(LOG_POLICY_NUM,gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField.asPolicyNum,
+				&gstTransData.stTransLog); 
+		Trace("xgd","recordsearch policy msg returnValue=%d\r\n",iRet);
+        if(SDK_OK == iRet)
+        {
+			iExistRecodeFlag = 1;
+			PackPolicyMsg(ucRecvBuf,&iLen,POLICY_CONFIRM_REQUEST,true);
+        }
+		else
 		{
-			snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
+			PackPolicyMsg(ucRecvBuf,&iLen,POLICY_CONFIRM_REQUEST,false);
 		}
-			printf("%s(%d)\n iLen=%d,SendBuf=%s\n",__FUNCTION__,__LINE__,iLen,ucDebugBuf);	
-			iRet = SendPolicyMsg(ucRecvBuf, iLen);
-			printf("send iRet = %d %s(%d)\n",iRet,__FUNCTION__,__LINE__);
+		iRet = SendPolicyMsg(ucRecvBuf,iLen);
+		if(SDK_OK != iRet)
+		{
+			return iRet;
 		}
-	else if(0 == memcmp(&ucRecvBuf[1],"02",2))
-	{
-		//return SDK_ERR;//tmp operate
-		SavePolicyMsg(ucRecvBuf,iLen);
-
-		PackPolicyMsg(ucRecvBuf,&iLen,POLICY_CONFIRM_REQUEST);
-		for(;i < iLen;i++)
+		if(1 == iExistRecodeFlag)
+		{
+			PrintRecipt(FALSE);
+		}
+		Trace("xgd","send policy msg iRet=%d\r\n",iRet);	
+		for(i = 0;i < iLen;i++)
 		{
 			snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
 		}
-			printf("%s(%d)\n iLen=%d,SendBuf=%s\n",__FUNCTION__,__LINE__,iLen,ucDebugBuf);	
-			iRet = SendPolicyMsg(ucRecvBuf, iLen);
-			printf("send iRet = %d %s(%d)\n",iRet,__FUNCTION__,__LINE__);
-
-
-		
+		Trace("xgd"," iLen=%d,SendBuf=%s,confirm=%d\r\n",iLen,ucDebugBuf);
+		memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
+		return POLICY_CONFIRM_REQUEST;
 	}
 	else
 	{
 		return SDK_ERR;
 	}
-	
-	return SDK_OK;
+	return SDK_ERR;
 }
 
-s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyRequest)
+s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyRequest,bool bIsSuccess)
 {
 	u8  ucSendBuf[512] = {0};
 	s32 iSendLen = 0;
@@ -167,42 +165,60 @@ s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyReque
 	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asAmount,POLICY_AMOUNT_LEN);
 	 iSendLen += POLICY_AMOUNT_LEN;
 
-	 memcpy(stPolicyDataField->asRetCode,"00",POLICY_RETURN_CODE_LEN);//for test
-	 
-	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asRetCode,POLICY_RETURN_CODE_LEN);
-		 iSendLen += POLICY_RETURN_CODE_LEN;
 
-	 memcpy(stPolicyDataField->asCardNo,"5555555577777777   ",POLICY_CARD_NO_LEN);//for test
-	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asCardNo,POLICY_CARD_NO_LEN);
-		 iSendLen += POLICY_CARD_NO_LEN;
 
-  	 memcpy(stPolicyDataField->asTransDate,"20171012",POLICY_TRANS_DATE_LEN);//for test
-	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asTransDate,POLICY_TRANS_DATE_LEN);
+	if(true == bIsSuccess)
+	{
+		 memcpy(ucSendBuf + iSendLen,"00",POLICY_RETURN_CODE_LEN);
+	}
+	else
+	{
+		 if(POLICY_CONFIRM_REQUEST == ePolicyRequest)
+		 {
+		 	 memcpy(ucSendBuf + iSendLen,"ZW",POLICY_RETURN_CODE_LEN);
+		 }
+		 else if(POLICY_FIRST_REQUEST == ePolicyRequest)
+		 {
+		 	 memcpy(ucSendBuf + iSendLen,"01",POLICY_RETURN_CODE_LEN);
+		 }
+	}
+	iSendLen += POLICY_RETURN_CODE_LEN;
+	if(true == bIsSuccess)
+	{
+	  		
+		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stCardInfo.stCardData.asCardNO,POLICY_CARD_NO_LEN);
+		 iSendLen += POLICY_CARD_NO_LEN;
+	  
+		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asTransDate,POLICY_TRANS_DATE_LEN);
 		 iSendLen += POLICY_TRANS_DATE_LEN;
-
-	 memcpy(stPolicyDataField->asTransTime,"163212",POLICY_TRANS_TIME_LEN);//for test
-	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asTransTime,POLICY_TRANS_TIME_LEN);
+		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asTransTime,POLICY_TRANS_TIME_LEN);
 		 iSendLen += POLICY_TRANS_TIME_LEN;
 
-	 memcpy(stPolicyDataField->asTransNo,"000012",POLICY_TRANS_NO_LEN);//for test
-	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asTransNo,POLICY_TRANS_NO_LEN);
+		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asTraceNO,POLICY_TRANS_NO_LEN);
 		 iSendLen += POLICY_TRANS_NO_LEN;
-
-	 memcpy(stPolicyDataField->asRefNo,"000045888898",POLICY_REFERENCE_NO_LEN);//for test
-	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asRefNo,POLICY_REFERENCE_NO_LEN);
+		
+		 memcpy(ucSendBuf + iSendLen,gstTransData.stTransLog.stMsgInfo.asRefNO,POLICY_REFERENCE_NO_LEN);
 		 iSendLen += POLICY_REFERENCE_NO_LEN;
-
-	 
+	 }
+	 else
+	 {
+	  	 memset(ucSendBuf + iSendLen,' ',POLICY_CARD_NO_LEN);
+		 iSendLen += POLICY_CARD_NO_LEN;
+		 memset(ucSendBuf + iSendLen,' ',POLICY_TRANS_DATE_LEN);
+		 iSendLen += POLICY_TRANS_DATE_LEN;
+		 memset(ucSendBuf + iSendLen,' ',POLICY_TRANS_TIME_LEN);
+		 iSendLen += POLICY_TRANS_TIME_LEN;
+ 		 memset(ucSendBuf + iSendLen,' ',POLICY_TRANS_NO_LEN);
+		 iSendLen += POLICY_TRANS_NO_LEN;
+ 		 memset(ucSendBuf + iSendLen,' ',POLICY_REFERENCE_NO_LEN);
+		 iSendLen += POLICY_REFERENCE_NO_LEN;
+	 }
 	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asOrigDataField,POLICY_ORIGINAL_DATA_FIELD_LEN);
 	 iSendLen += POLICY_ORIGINAL_DATA_FIELD_LEN;
-	
 	 memcpy(ucSendBuf + iSendLen,stPolicyDataField->asAddMsg,POCLICY_ADDITIONAL_LEN);
 	 iSendLen += POCLICY_ADDITIONAL_LEN;
-
      memcpy(ucSendBuf + iSendLen,"\x03",1);
 	 iSendLen += 1;
-
-	 
 	 iVarifyCRC = CalcPolicyCRCValue(ucSendBuf,iSendLen);
 	 ucSendBuf[iSendLen] = iVarifyCRC;
 	 iSendLen += 1;
@@ -215,47 +231,48 @@ s32 PackPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen,E_POLICY_REQUEST ePolicyReque
 s32 SendPolicyMsg(u8 *pheInputBuf,s32 iLen)
 {
 	
-	return (sdkCommUartSendData(SDK_COMM_UART_PINPAD,pheInputBuf,iLen));
+	return (sdkCommUartSendData(gucCommPort,pheInputBuf,iLen));
 }
 
 s32 SavePolicyMsg(u8 *pheInputBuf,s32 iLen)
 {
 	ST_SENT_POLICY_DATA_FIELD *stPolicyDataField = NULL;
 	s32 iDataFieldOffsetLen = 0;
-	u8 ucRecvBuf[512] = {0};
+	u8 ucRecvBuf[512] = {0}; 
 	
+    memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
 	memcpy(ucRecvBuf,pheInputBuf,iLen);
 	stPolicyDataField  = &gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField;
 	iDataFieldOffsetLen = 7;
 	memcpy(stPolicyDataField->asCompanyCode,ucRecvBuf + iDataFieldOffsetLen,POLICY_COMPANY_CODE_LEN);
-	printf("company code=%s\n",stPolicyDataField->asCompanyCode);
+	Trace("xgd","company code=%s\r\n",stPolicyDataField->asCompanyCode);
 	
 	iDataFieldOffsetLen += POLICY_COMPANY_CODE_LEN;
 	memcpy(stPolicyDataField->asMID,ucRecvBuf + iDataFieldOffsetLen,POLICY_MID_LEN);
-	printf("Mid=%s\n",stPolicyDataField->asMID);
+	Trace("xgd","Mid=%s\r\n",stPolicyDataField->asMID);
 	
 	iDataFieldOffsetLen += POLICY_MID_LEN;
 	memcpy(stPolicyDataField->asTID,ucRecvBuf + iDataFieldOffsetLen,POLICY_TID_LEN);
-	printf("TID=%s\n",stPolicyDataField->asTID);
+	Trace("xgd","TID=%s\r\n",stPolicyDataField->asTID);
 	
 	iDataFieldOffsetLen += POLICY_TID_LEN;
 	memcpy(stPolicyDataField->asPolicyNum,ucRecvBuf + iDataFieldOffsetLen,POLICY_NUMBER_LEN);
-	printf("Policy number=%s\n",stPolicyDataField->asPolicyNum);
+	Trace("xgd","Policy number=%s\r\n",stPolicyDataField->asPolicyNum);
 
 	
 	iDataFieldOffsetLen += POLICY_NUMBER_LEN;
 	memcpy(stPolicyDataField->asAmount,ucRecvBuf + iDataFieldOffsetLen,POLICY_AMOUNT_LEN);
-	printf("Amount=%s\n",stPolicyDataField->asAmount);
+	Trace("xgd","Amount=%s\r\n",stPolicyDataField->asAmount);
 
 	
 	iDataFieldOffsetLen += POLICY_AMOUNT_LEN;
 	memcpy(stPolicyDataField->asOrigDataField,ucRecvBuf + iDataFieldOffsetLen,POLICY_ORIGINAL_DATA_FIELD_LEN);
-	printf("OrigDataField=%s\n",stPolicyDataField->asOrigDataField);
+	Trace("xgd","OrigDataField=%s\r\n",stPolicyDataField->asOrigDataField);
 
 	
 	iDataFieldOffsetLen += POLICY_ORIGINAL_DATA_FIELD_LEN;
 	memcpy(stPolicyDataField->asAddMsg,ucRecvBuf + iDataFieldOffsetLen,POCLICY_ADDITIONAL_LEN);
-	printf("AddMsg=%s\n",stPolicyDataField->asAddMsg);
+	Trace("xgd","AddMsg=%s\r\n",stPolicyDataField->asAddMsg);
 
 	strcpy(gstAppSysCfg.stTermInfo.asMerchID, stPolicyDataField->asMID);
     strcpy(gstAppSysCfg.stTermInfo.asTermID, stPolicyDataField->asTID);
@@ -296,27 +313,28 @@ s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen)
 	s32 i = 0;
 	s32 iFirstPos = 0;
 	s32 iSecondPos = 0;
-	u32 uiRecvTimer = sdkTimerGetId();
 	SDK_QUEUE_HAND pHead = NULL;
 
 
-	iRet = sdkCommUartRecvData(SDK_COMM_UART_PINPAD,ucRecvBuf,300,200);
+	iRet = sdkCommUartRecvData(gucCommPort,ucRecvBuf,300,300);
 	if(iRet < 0) 
 	{
 		return iRet;
 	}
 	if(0x02 != ucRecvBuf[0])
 	{
+		Trace("xgd","The first byte=%02X\r\n",ucRecvBuf[0]);
 		return SDK_ERR;
 	}
 	pHead = sdkQueueCreate(512);
 	sdkQueueInsertData(pHead,ucRecvBuf, iRet);
-	printf("RecvLen=%d,queueLen=%d,%s(%d)\n",iRet,sdkQueueGetDataLen(pHead),__FUNCTION__,__LINE__);
+	Trace("xgd","RecvLen=%d,queueLen=%d\r\n",iRet,sdkQueueGetDataLen(pHead));
 	while(1)
 	{
-		iRet = sdkCommUartRecvData(SDK_COMM_UART_PINPAD,ucRecvBuf,300,1000 *120);
+		iRet = sdkCommUartRecvData(gucCommPort,ucRecvBuf,300,300);  //Take non-blocked way to receive comm msgs
 		if(iRet < 0) 
 		{
+			Trace("xgd","Recv data fail.iRet = %d\r\n",iRet);
 			sdkQueueRelease(pHead);
 			return iRet;
 		}
@@ -324,9 +342,8 @@ s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen)
 		sdkQueueInsertData(pHead,ucRecvBuf, iLen);
 		iFirstPos = sdkQueueGetPosValue(pHead, 0);
 		iSecondPos = sdkQueueGetPosValue(pHead, 1);
-		//printf("pos0:0X%02X,pos1:0X%02X %s(%d)\n",iFirstPos,iSecondPos,__FUNCTION__,__LINE__);
-		
-		//printf("RecvLen=%d,queueLen=%d,%s(%d)\n",iLen,sdkQueueGetDataLen(pHead),__FUNCTION__,__LINE__);
+		Trace("xgd","pos0:0X%02X,pos1:0X%02X %s(%d)\r\n",iFirstPos,iSecondPos);
+		Trace("xgd","RecvLen=%d,queueLen=%d,%s(%d)\r\n",iLen,sdkQueueGetDataLen(pHead));
 		
 		if(sdkQueueGetDataLen(pHead) < 7)
 		{
@@ -338,7 +355,6 @@ s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen)
 
 		iTrueLen = (sdkQueueGetPosValue(pHead, 3)- '0') * 1000 + (sdkQueueGetPosValue(pHead, 4) - '0') * 100
 					+ (sdkQueueGetPosValue(pHead, 5)- '0') * 10 + (sdkQueueGetPosValue(pHead, 6) - '0') + 9;
-		//printf("TrueLen=%d,%s(%d)\n",iTrueLen,__FUNCTION__,__LINE__);
 		if(sdkQueueGetDataLen(pHead) < iTrueLen)
 		{
 			continue;
@@ -352,21 +368,16 @@ s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen)
 			sdkQueueRelease(pHead);
 			return SDK_ERR;
 		}
-		if(sdkTimerIsEnd(uiRecvTimer, 120 * 1000))
-        {
-			sdkQueueRelease(pHead);
-            return SDK_ERR;
-        }
 	}//while(1)
 	sdkQueueGetData(pHead,ucRecvBuf, iTrueLen);
 	sdkQueueRelease(pHead);
 	*iOutputLen = iTrueLen;
 	memcpy(pheOutputBuf,ucRecvBuf,iTrueLen);
-	//for(;i < iTrueLen;i++)
-	//{
-	//	snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
-	//}
-	//printf("%s(%d)\n iLen=%d,RecvBuf=%s\n",__FUNCTION__,__LINE__,iTrueLen,ucDebugBuf);
+	 for(i = 0;i < iTrueLen;i++)
+	 {
+	 	snprintf(ucDebugBuf + 3*i,2048,"%02X ",ucRecvBuf[i]);
+	 }
+	Trace("xgd","iLen=%d,RecvBuf=%s\r\n",iTrueLen,ucDebugBuf);
 	
 	return SDK_OK;
 }
@@ -375,7 +386,7 @@ s32 RecvPolicyMsg(u8 *pheOutputBuf,s32 *iOutputLen)
 
 s32 ClosePolicyComm(void)
 {
-	return (sdkCommCloseUart(SDK_COMM_UART_PINPAD));
+	return (sdkCommCloseUart(gucCommPort));
 }
 	
 
diff --git a/ads-basic-app-jfcd/src/print.c b/ads-basic-app-jfcd/src/print.c
index d90462f..607b5a7 100755
--- a/ads-basic-app-jfcd/src/print.c
+++ b/ads-basic-app-jfcd/src/print.c
@@ -354,6 +354,13 @@ void PrintFormRefData(bool bIsReprint, SDK_PRINT_FONT stFont, s32 iOffset, s32 i
         strcpy(printbuf, "TermCap:");
         sdkBcdToAsc(&printbuf[strlen(printbuf)], pst_emvinfo->heTermCap, 3);
         sdkPrintStr(printbuf, stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
+
+		memset(printbuf, 0, sizeof(printbuf));
+		strcpy(printbuf, "POLICY NUM:");
+		memcpy(printbuf + strlen(printbuf),
+			gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField.asPolicyNum,
+			POLICY_NUMBER_LEN);
+		sdkPrintStr(printbuf,stFont, SDK_PRINT_LEFTALIGN, iOffset, iRowGap);
     }
 }
 
diff --git a/ads-basic-app-jfcd/src/record.c b/ads-basic-app-jfcd/src/record.c
index ef2dbcb..dd6e855 100755
--- a/ads-basic-app-jfcd/src/record.c
+++ b/ads-basic-app-jfcd/src/record.c
@@ -124,23 +124,22 @@ static ST_DATABASE TabTransLog =
         {STR(LOG_STAT_UPLOADSTATUS),   DB_DATATYPE_U32, 0, FALSE, &_gstTransLog.stTransStatus.eUploadStatus,        0},
 	     //added by jeff 20171010 for handle policy tranx
 	    {STR(LOG_POLICY_STX),     	 	DB_DATATYPE_U8,   0, FALSE, &_gstTransLog.stSentPolicyMsg.ucSTX,     0}, 
-        {STR(LOG_POLICY_CMD), 	      	DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.asCmd,     0}, 
-		{STR(LOG_POLICY_DATALEN), 	 	DB_DATATYPE_BIN,  0, FALSE, &_gstTransLog.stSentPolicyMsg.heDataLen, sizeof(_gstTransLog.stSentPolicyMsg.heDataLen)},
+        {STR(LOG_POLICY_CMD), 	      	DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.asCmd,     0}, 
+		{STR(LOG_POLICY_DATALEN), 	 	DB_DATATYPE_BIN,  0, FALSE, _gstTransLog.stSentPolicyMsg.heDataLen, sizeof(_gstTransLog.stSentPolicyMsg.heDataLen)},
 	
-		{STR(LOG_POLICY_COMPANY_CODE), 	DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asCompanyCode,           0},
-		{STR(LOG_POLICY_MID), 	        DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asMID,     			     0}, 
-		{STR(LOG_POLICY_TID), 			DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asTID,     			     0},
-		{STR(LOG_POLICY_NUM), 			DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asPolicyNum,    	     0}, 	 
-		{STR(LOG_POLICY_AMOUNT), 		DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asAmount,     		     0}, 	 
-		{STR(LOG_POLICY_RET_CODE), 		DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asRetCode,    	 	     0}, 	 
-		{STR(LOG_POLICY_CARD_NO), 		DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asCardNo,     		     0}, 
-		{STR(LOG_POLICY_TRANS_DATE), 	DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asTransDate,             0}, 
-		{STR(LOG_POLICY_TRANS_TIME), 	DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asTransTime,             0}, 
-		{STR(LOG_POLICY_TRANS_NO), 		DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asTransNo,               0}, 
-		{STR(LOG_POLICY_REF_NO), 		DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asRefNo,             	  0}, 
-		{STR(LOG_POLICY_ORIG_DATA_FIELD), 	DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asOrigDataField,     0},
-		{STR(LOG_POLICY_ADD_MSG), 			DB_DATATYPE_ASC,  0, FALSE, &_gstTransLog.stSentPolicyMsg.stPolicyDataField.asAddMsg,            0}, 
-			
+		{STR(LOG_POLICY_COMPANY_CODE), 	DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asCompanyCode,           0},
+		{STR(LOG_POLICY_MID), 	        DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asMID,     			     0}, 
+		{STR(LOG_POLICY_TID), 			DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asTID,     			     0},
+		{STR(LOG_POLICY_NUM), 			DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asPolicyNum,    	     0}, 	 
+		{STR(LOG_POLICY_AMOUNT), 		DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asAmount,     		     0}, 	 
+		{STR(LOG_POLICY_RET_CODE), 		DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asRetCode,    	 	     0}, 	 
+		{STR(LOG_POLICY_CARD_NO), 		DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asCardNo,     		     0}, 
+		{STR(LOG_POLICY_TRANS_DATE), 	DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asTransDate,             0}, 
+		{STR(LOG_POLICY_TRANS_TIME), 	DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asTransTime,             0}, 
+		{STR(LOG_POLICY_TRANS_NO), 		DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asTransNo,               0}, 
+		{STR(LOG_POLICY_REF_NO), 		DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asRefNo,             	  0}, 
+		{STR(LOG_POLICY_ORIG_DATA_FIELD), 	DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asOrigDataField,     0},
+		{STR(LOG_POLICY_ADD_MSG), 			DB_DATATYPE_ASC,  0, FALSE, _gstTransLog.stSentPolicyMsg.stPolicyDataField.asAddMsg,            0}, 
 		{STR(LOG_POLICY_ETX),    			DB_DATATYPE_U8,   0, FALSE, &_gstTransLog.stSentPolicyMsg.ucETX,     							  0}, 
 		{STR(LOG_POLICY_CRC),    			DB_DATATYPE_U8,   0, FALSE, &_gstTransLog.stSentPolicyMsg.ucCRC,     							  0}, 						
         {-1, NULL},
@@ -258,6 +257,8 @@ s32 RecordGetNumEx(ST_RECORD_FILTER *pstFilter)
 *****************************************************************************/
 s32 RecordAppend(ST_TRANSLOG *pstTransLog)
 {
+	s32 iRet;
+	
     if(NULL == pstTransLog)
     {
         return SDK_PARA_ERR;
@@ -268,9 +269,9 @@ s32 RecordAppend(ST_TRANSLOG *pstTransLog)
         memcpy(&_gstTransLog, pstTransLog, sizeof(ST_TRANSLOG));
     }
     
-    if(DB_EXIT_SUCCESS != sdkDbInsertRecord(&TabTransLog))
+    if(DB_EXIT_SUCCESS != (iRet = sdkDbInsertRecord(&TabTransLog)))
     {
-        Trace("record", "sdkDbInsertRecord fail\r\n");
+        Trace("record", "sdkDbInsertRecord fail,iRet=%d\r\n",iRet);
         return SDK_ERR;
     }
     
diff --git a/ads-basic-app-jfcd/src/sale.c b/ads-basic-app-jfcd/src/sale.c
index c18b51a..6bc6ac4 100755
--- a/ads-basic-app-jfcd/src/sale.c
+++ b/ads-basic-app-jfcd/src/sale.c
@@ -169,67 +169,23 @@ void SaleTrans(u16 usCardType)
     SDK_ICC_TRADE_PARAM st_tradeparam;
     ST_CARDINFO *pst_cardinfo = NULL;
     ST_MSGINFO *pst_msginfo = NULL;
+	ST_SENT_POLICY_DATA_FIELD *stPolicyDataField = NULL;
     s32 ret;
     u8 buf[16], sale_amt[6], cashback_amt[6];
-
-    /* step1 : initializes the transaction data */
-    if(0 == strlen(gstTransData.stTransLog.stMsgInfo.asAmount))
-    {
-        memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
-    }
+ 
     memset(&st_tradeparam, 0, sizeof(SDK_ICC_TRADE_PARAM));
     pst_cardinfo = &gstTransData.stTransLog.stCardInfo;
     pst_msginfo = &gstTransData.stTransLog.stMsgInfo;
     pst_msginfo->ucCashierNO = gstLoginInfo.ucUserNO;
+	stPolicyDataField  = &gstTransData.stTransLog.stSentPolicyMsg.stPolicyDataField;
     gstTransData.stTransLog.eTransID = TRANSID_SALE;
 
-    /* step2 : Display title */
     DispTitle(STR_TRANS_SALE);
-
-    /* step3 : check transaction conditions */
     if(!TrnCheckCondition(TRUE, gstAppSysCfg.stTransParam.bIsSupportSale))
     {
         return;
     }
-
-    /* step4 : input transaction amount */
-    ret = TrnInputAmount(SALE_AMOUNT, pst_msginfo->asAmount);
-    if(SDK_OK != ret)
-    {
-        return;
-    }
-
-    /* step5 : input cashback amount(optional) */
-    ret = TrnInputAmount(CASHBACK_AMOUNT, pst_msginfo->asCashbackAmount);
-    if(SDK_OK != ret)
-    {
-        return;
-    }
-
-//    if(SDK_OK != TrnCheckCashBackAmount(pst_msginfo->asAmount, pst_msginfo->asCashbackAmount))
-//    {
-//        TrnSetStatus(ERR_CASHBACK_LIMIT);
-//        return;
-//    }
-
-    /* step6 : calculate total amount (total amount = sale amount + cashback amount) */
-    memset(sale_amt, 0, sizeof(sale_amt));
-    sdkAscToBcd(sale_amt, pst_msginfo->asAmount, 12);
-
-    memset(cashback_amt, 0, sizeof(cashback_amt));
-    sdkAscToBcd(cashback_amt, pst_msginfo->asCashbackAmount, 12);
-    
-    sdkBcdAdd(sale_amt, sale_amt, 6, cashback_amt, 6);
-    memset(pst_msginfo->asAmount, 0, sizeof(pst_msginfo->asAmount));
-    sdkBcdToAsc(pst_msginfo->asAmount, sale_amt, 6);
-    
-//    if(SDK_OK != TrnCheckTotalAmount(gstTransData.stTransLog.eTransID, pst_msginfo->asAmount))
-//    {
-//        TrnSetStatus(ERR_AMT_LIMIT);
-//        return;
-//    }
-
-    /* step7 : Process card */
+	memcpy(pst_msginfo->asAmount, stPolicyDataField->asAmount, 12);
     while(1)
     {
         ret = TrnReadCard(usCardType, &st_tradeparam, pst_cardinfo);
@@ -253,7 +209,7 @@ void SaleTrans(u16 usCardType)
             {
                 usCardType &= ~SDK_ICC_RF;
             }
-            memset(&gstTransData, 0, sizeof(ST_TRANSDATA));
+           
             gstTransData.stTransLog.eTransID = TRANSID_SALE;
             sdkBcdToAsc(pst_msginfo->asAmount, sale_amt, 6);
             sdkBcdToAsc(pst_msginfo->asCashbackAmount, cashback_amt, 6);
