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
#ifndef _STR_H_
#define _STR_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONSTANTS
-----------------------------------------------------------------------------*/

#define STR_TRANS_LOGON                "LOGON"
#define STR_TRANS_LOGOUT               "LOGOUT"
#define STR_TRANS_SALE                 "SALE"
#define STR_TRANS_VOID                 "VOID"
#define STR_TRANS_REFUND               "REFUND"
#define STR_TRANS_TIP                  "TIP"
#define STR_TRANS_ADJUST               "ADJUST"
#define STR_TRANS_BALANCE              "BALANCE"
#define STR_TRANS_SETTLEMENT           "SETTLEMENT"
#define STR_TRANS_BATCH_UP             "BATCH UP"
#define STR_TRANS_OFFLINE_UPLOAD       "OFFLINE UPLOAD"
#define STR_TRANS_SCRIPT_UPLOAD        "SCRIPT UPLOAD"
#define STR_TRANS_REVERSAL             "REVERSAL"

#define STR_FUNC_REPRINT               "REPRINT"
#define STR_FUNC_TRANS_QUERY           "TRANS QUERY"
#define STR_FUNC_SETUP                 "SETUP"
#define STR_FUNC_SWITCH_APP            "SWITCH APP"
#define STR_FUNC_QUERY_ANY             "QUERY ANY"
#define STR_FUNC_QUERY_DETAILS         "QUERY DETAILS"
#define STR_FUNC_QUERY_SUMMARY         "QUERY SUMMARY"
#define STR_FUNC_REPRINT_LAST          "REPRINT LAST"
#define STR_FUNC_REPRINT_ANY           "REPRINT ANY"
#define STR_FUNC_DETAILS_REPORT        "DETAILS REPORT"
#define STR_FUNC_SUMMARY_REPORT        "SUMMARY REPORT"
#define STR_FUNC_REPRINT_SETTLE        "REPRINT SETTLEMENT"

#define STR_CARD_VISA                  "VISA"
#define STR_CARD_MC                    "MC"
#define STR_CARD_JCB                   "JCB"
#define STR_CARD_AMEX                  "AMEX"
#define STR_CARD_CUP                   "CUP"

#define STR_CARD_MANUAL                "MANUAL"
#define STR_CARD_SWIPE                 "SWIPE"
#define STR_CARD_INSERT                "INSERT"
#define STR_CARD_TAP                   "TAP"

#define STR_DETAIL_IC                  "[IC]"
#define STR_DETAIL_RF                  "[RF]"
#define STR_DETAIL_SWIPE               "[SWIPE]"
#define STR_DETAIL_MANUAL              "[MANUAL]"

#define STR_STATUS_ALREADY_VOIDED      "(ALREADY VOIDED)"
#define STR_STATUS_ALREADY_ADJUSTED    "(ALREADY ADJUSTED)"
#define STR_STATUS_ALREADY_UPLOADED    "(ALREADY UPLOADED)"
#define STR_STATUS_NOT_UPLOADED        "(NOT UPLOADED)"
#define STR_STATUS_UPLOAD_FAIL         "(UPLOAD FAIL)"
#define STR_STATUS_UPLOAD_REJECTED     "(UPLOAD REJECTED)"

#define STR_PRESS_ENTER_REINPUT        "<ENTER> - REINPUT"
#define STR_PRESS_ENTER_RETRY          "<ENTER> - RETRY"
#define STR_PRESS_ENTER_CONFIRM        "<ENTER> - CONFIRM" 
#define STR_PRESS_ENTER_REPRINT        "<ENTER> - REPRINT"
#define STR_PRESS_ENTER_EXIT           "<ENTER> - EXIT"
#define STR_PRESS_ENTER_YES            "<ENTER> - YES"
#define STR_PRESS_ENTER_CONTINUE       "<ENTER> - CONTINUE"
#define STR_PRESS_ENTER_START          "<ENTER> - START"
#define STR_PRESS_CANCEL_EXIT          "<CANCEL> - EXIT"
#define STR_PRESS_CANCEL_REINPUT       "<CANCEL> - REINPUT"
#define STR_PRESS_CANCEL_STOP          "<CANCEL> - STOP"
#define STR_PRESS_CANCEL_NO            "<CANCEL> - NO"
#define STR_PRESS_CANCEL_SKIP          "<CANCEL> - SKIP"

#define STR_INFO_TRANS_NOT_FOUND       "TRANS NOT FOUND"
#define STR_INFO_TIP_EXCEED            "TIP EXCEED"
#define STR_INFO_AMT_EXCEED            "AMOUNT EXCEED"
#define STR_INFO_ADD_AID_FAIL          "ADD AID FAIL!"
#define STR_INFO_ADD_CAPK_FAIL         "ADD CAPK FAIL!"
#define STR_INFO_CONFIGURATION_ERROR   "CONFIGURATION ERROR!"
#define STR_INFO_CONNECT_WIFI_FAILED   "CONNECT WIFI FAILED"
#define STR_INFO_OPEN_ETH0_FAILED      "OPEN ETH0 FAILED!"
#define STR_INFO_CREATE_PPP_FAILED     "CREATE PPP FAILED!"
#define STR_INFO_TRANS_FINISH          "TRANS FINISH"
#define STR_INFO_TRANS_FAILED          "TRANS FAILED"
#define STR_INFO_PIN_ERR               "PIN ERROR"
#define STR_INFO_CONTACT_ISSUER        "PLS CONTACT ISSUER"
#define STR_INFO_INVALID_MERCHANT      "INVALID MERCHANT"
#define STR_INFO_CARD_PICKED_UP        "CARD PICKED UP"
#define STR_INFO_CONTACT_ACQUIRER      "PLS CONTACT ACQUIRER"
#define STR_INFO_PLS_RETRY             "PLS RETRY"
#define STR_INFO_AMOUNT_EXCEED         "AMOUNT EXCEED"
#define STR_INFO_INVALID_CARDNO        "INVALID CARD NO."
#define STR_INFO_CARD_NOT_ACCEPTED     "CARD NOT ACCEPTED"
#define STR_INFO_OPERATION             "OPERATION ERR"
#define STR_INFO_CARD_EXPIRED          "CARD EXPIRED"
#define STR_INFO_WRONG_CARD            "WRONG CARD"
#define STR_INFO_TRY_ANOTHER_CARD      "PLS TRY ANOTHER CARD"
#define STR_INFO_PIN_TRY_LIMIT         "PIN TRY LIMIT"
#define STR_INFO_TRANS_NOT_SUPPORTED   "TRANS NOT SUPPORTED"
#define STR_INFO_USE_CHIPCARD          "PLS USE CHIP CARD"
#define STR_INFO_NOT_SUFFICIENT_FUNDS  "NOT SUFFICIENT FUNDS"
#define STR_INFO_PLS_CHECK             "PLS CHECK" 
#define STR_INFO_INVALID_TERM          "INVALID TERM"
#define STR_INFO_SALE_TIMES_LIMIT      "SALE TIMES LIMIT"
#define STR_INFO_TRANS_TIMEOUT         "TRANS TIMEOUT"
#define STR_INFO_POS_LOGON_FIRST       "POS LOGON FIRST"
#define STR_INFO_RESEND_OFFLINE_DATA   "RESEND OFFLINE DATA"
#define STR_INFO_PLS_RETRY_LATER       "PLS RETRY LATER"
#define STR_INFO_POS_NOT_REGISTERED    "POS NOT REGISTERED"
#define STR_INFO_MAC_ERR               "MAC ERROR"
#define STR_INFO_PLS_LOGON_AGAIN       "PLS LOGON AGAIN"
#define STR_INFO_INQUIRE_SUCC          "INQUIRE SUCCESS"
#define STR_INFO_CHECK_PINPAD          "CHECK PINPAD"
#define STR_INFO_BALANCE               "BALANCE:"
#define STR_INFO_INPUT_PIN             "INPUT PIN:"
#define STR_INFO_INPUT_ONLINE_PIN      "INPUT ONLINE PIN:"
#define STR_INFO_INPUT_OFFLINE_PIN     "INPUT OFFLINE PIN:"
#define STR_INFO_CAPKI                 "CAPKI"  
#define STR_INFO_LINKING               "LINKING..."
#define STR_INFO_AMOUNT                "AMOUNT:"
#define STR_INFO_SENDING               "SENDING..."
#define STR_INFO_RECEIVING             "RECEIVING..."
#define STR_INFO_TRANS_SUCCESS         "TRANS SUCCESS"
#define STR_INFO_VIP_CLIENT            "VIP CLIENT"
#define STR_INFO_CONFIRM_WITH_ISS      "PLS CONFIRM WITH ISS"
#define STR_INFO_SWIPE_ERROR           "SWIPE ERROR"
#define STR_INFO_TRANS_CANCEL          "TRANS CANCEL"
#define STR_INFO_PLS_SWIPE_INSERT      "PLS SWIPE/INSERT-->"
#define STR_INFO_PLS_SWIPE_AGAIN       "PLS SWIPE AGAIN-->"
#define STR_INFO_RESPONSE_CODE         "RESPONSE CODE:"
#define STR_INFO_CASHIER_LOGON_FIRST   "CASHIER LOGON FIRST"
#define STR_INFO_REPRINT_FAILED        "REPRINT FAILED"
#define STR_INFO_SETTLE_PRINT_FAILED   "SETTLE PRINT FAILED"
#define STR_INFO_PLS_REPRINT           "PLS REPRINT"
#define STR_INFO_SETTLING              "SETTLING..."
#define STR_INFO_DO_SETTLEMENT_FIRST   "DO SETTLEMENT FIRST"
#define STR_INFO_FILE_SYSTEM_ERROR     "FILE SYSTEM ERROR"
#define STR_INFO_MEMORY_INSUFFICIENT   "MEMORY INSUFFICIENT"
#define STR_INFO_TRANS_NUM_EXCEEDED    "TRANS NUM EXCEEDED"
#define STR_INFO_NOT_SUPPORTED         "NOT SUPPORTED"
#define STR_INFO_READ_CARD_FAILED      "READ CARD FAILED"
#define STR_INFO_RECEIVE_DATA          "RECEIVE DATA"
#define STR_INFO_DISCONNECTED          "DISCONNECTED"
#define STR_INFO_BUFFER_ERROR          "BUFFER ERROR"
#define STR_INFO_CREATE_LINK           "CREATE LINK" 
#define STR_INFO_UNKOWN_ERROR          "UNKOWN ERROR!"
#define STR_INFO_TIMEOUT               "TIMEOUT"
#define STR_INFO_NO_LINE_DETECTED      "NO LINE DETECTED"
#define STR_INFO_PUT_HANDLE_BACK       "PUT HANDLE BACK"
#define STR_INFO_LINE_BUSY             "LINE BUSY"
#define STR_INFO_NO_SIM_DETECTED       "NO SIM DETECTED"
#define STR_INFO_LINK_FAILURE          "LINK FAILURE"
#define STR_INFO_PACK_MSG_FAILED       "PACK MSG FAILED"
#define STR_INFO_SEND_DATA_FAILED      "SEND DATA FAILED"
#define STR_INFO_RECEIVE_DATA_FAILED   "RECEIVE DATA FAILED"
#define STR_INFO_UNPACK_MSG_FAILED     "UNPACK MSG FAILED"
#define STR_INFO_PLS_CALL_BANK         "PLS CALL BANK"
#define STR_INFO_PRINT_ERROR           "PRINT ERROR"
#define STR_INFO_CHECK_MSG_FAILED      "CHECK MSG FAILED"
#define STR_INFO_MTI_NOT_MATCH         "MTI NOT MATCH"
#define STR_INFO_PROCCODE_NOT_MATCH    "PROCCODE NOT MATCH"
#define STR_INFO_TRACENO_NOT_MATCH     "TRACENO NOT MATCH"
#define STR_INFO_AMOUNT_NOT_MATCH      "AMOUNT NOT MATCH"
#define STR_INFO_BATCHNO_NOT_MATCH     "BATCHNO NOT MATCH"
#define STR_INFO_TID_NOT_MATCH         "TID NOT MATCH"
#define STR_INFO_MID_NOT_MATCH         "MID NOT MATCH"
#define STR_INFO_PLS_LOGON_FIRST       "PLS LOGON FIRST"
#define STR_INFO_VOID_NOT_ALLOWED      "VOID NOT ALLOWED"
#define STR_INFO_ALREADY_VOIDED        "ALREADY VOIDED"
#define STR_INFO_CARDNO_NOT_MATCH      "CARDNO NOT MATCH"
#define STR_INFO_ADJUST_NOT_ALLOWED    "ADJUST NOT ALLOWED"
#define STR_INFO_ADJUST_TIMES_LIMIT    "ADJUST TIMES LIMIT"
#define STR_INFO_BATCHUP_FAILED        "BATCHUP FAILED"
#define STR_INFO_USER_NOT_EXIST        "USER NOT EXIST"
#define STR_INFO_PASSWORD_ERR          "PASSWORD ERR"
#define STR_INFO_UPDATE_KEY_FAILED     "UPDATE KEY FAILED!"
#define STR_INFO_NO_TRANS              "NO TRANS"
#define STR_INFO_ALREADY_ADJUSTED      "ALREADY ADJUSTED"
#define STR_INFO_AUTO_LOGON_FAIL       "AUTO LOGON FAIL"
#define STR_INFO_RESET_FAILURE         "RESET FAILURE"
#define STR_INFO_DDA_FAILED            "DDA FAILED"
#define STR_INFO_NO_CARD_PRESENT       "NO CARD PRESENT"
#define STR_INFO_MULTI_CARDS           "MULTI CARDS"
#define STR_INFO_NEED_MUTUAL_AUTH      "NEED MUTUAL AUTH"
#define STR_INFO_READ_CHIP_FAIL        "READ CHIP FAIL"
#define STR_INFO_PLS_SWIPE_CARD        "PLS SWIPE CARD"
#define STR_INFO_PURE_EC_NOT_SUPPORT   "PURE EC NOT SUPPORT"
#define STR_INFO_PURE_EC_CARD          "PURE EC CARD"
#define STR_INFO_PROCESS_WITH_PBOC     "PROCESS WITH PBOC"
#define STR_INFO_CARD_IS_BLOCKED       "CARD IS BLOCKED"
#define STR_INFO_NO_APP_SELECTED       "NO APP SELECTED"
#define STR_INFO_DATA_FORMAT_ERR       "DATA FORMAT ERR"
#define STR_INFO_APP_IS_BLOCKED        "APP IS BLOCKED"
#define STR_INFO_BATERR_OR_LOWPOWER    "BAT ERR OR LOW POWER"
#define STR_INFO_SHUTTING_DOWN         "SHUTTING DOWN.."
#define STR_INFO_LOW_POWER             "LOW POWER"
#define STR_INFO_PLS_CHARGE            "PLS CHARGE"
#define STR_INFO_ENCRYPTION_ERROR      "ENCRYPTION ERROR!"
#define STR_INFO_OPERATE_FAILED        "OPERATE FAILED"
#define STR_INFO_CARD_NO               "CARD NO.:"
#define STR_INFO_SALE                  "SALE:"
#define STR_INFO_REFUND                "REFUND:"
#define STR_INFO_TRACE_NO              "TRACE NO.:"
#define STR_INFO_AUTH_NO               "AUTH NO.:"
#define STR_INFO_REF_NO                "REF NO.:"
#define STR_INFO_ARROW_UP              "��"
#define STR_INFO_ARROW_DOWN            "��"
#define STR_INFO_SAVING_PARAM          "SAVING PARAM"
#define STR_INFO_PLEASE_WAIT           "PLEASE WAIT..."
#define STR_INFO_TRANS_FAIL            "TRANS FAIL!"
#define STR_INFO_AVAILABLE_AMT         "AVAILABLE AMT:"
#define STR_INFO_NEXGO                 "NEXGO"
#define STR_INFO_ORIG_AMOUNT           "ORIG AMOUNT:"
#define STR_INFO_LAST_CHANCE           "LAST CHANCE!"
#define STR_INFO_WELCOME               "~WELCOME~"
#define STR_INFO_PIN_CORRECT           "PIN CORRECT"
#define STR_INFO_SELECT_APP            "SELECT APP"
#define STR_INFO_SEE_PHONE             "PLS SEE PHONE"
#define STR_INFO_REOVME_CARD           "PLS REOVME CARD"
#define STR_INFO_USER_NO               "USER NO.:"
#define STR_INFO_PASSWORD              "PASSWORD:"
#define STR_INFO_SYSTEM_INIT           "SYSTEM INIT"
#define STR_INFO_LOGON_SUCCESS         "LOGON SUCCESS"
#define STR_INFO_LAST_PRINT_FAILED     "LAST PRINT FAILED"
#define STR_INFO_INPUT_ORIG_PWD        "INPUT ORIG PWD"
#define STR_INFO_ORIG_PWD_INCORRECT    "ORIG PWD INCORRECT"    
#define STR_INFO_INPUT_NEW_PWD         "INPUT NEW PWD"
#define STR_INFO_INPUT_PWD_AGAIN       "INPUT PWD AGAIN"
#define STR_INFO_PWD_NOT_MATCH         "PWD NOT MATCH"
#define STR_INFO_INPUT_PWD             "INPUT PWD"
#define STR_INFO_CHIP_CARD_PLS_INSERT  "CHIP CARD,PLS INSERT"
#define STR_INFO_READ_CARD_ERROR       "READ CARD ERROR"
#define STR_INFO_PLEASE_TRY_AGAIN      "PLEASE TRY AGAIN"
#define STR_INFO_INPUT_CARDNO          "INPUT CARDNO."
#define STR_INFO_INPUT_ADMIN_PWD       "INPUT ADMIN PWD:"
#define STR_INFO_PWD_ERROR             "PWD ERROR"
#define STR_INFO_INPUT_ORIG_TRACENO    "INPUT ORIG TRACENO."
#define STR_INFO_INPUT_ORIG_REFNO      "INPUT ORIG REFNO."
#define STR_INFO_FORMAT_ERR            "FORMAT ERR"
#define STR_INFO_INPUT_CASHBACK        "INPUT CASHBACK"
#define STR_INFO_INPUT_AMOUNT          "INPUT AMOUNT"
#define STR_INFO_INPUT_ORIG_DATE       "INPUT ORIG DATE"
#define STR_INFO_MMDD                  "(MMDD)"
#define STR_INFO_INPUT_EXPIRYDATE      "INPUT EXPIRY DATE"
#define STR_INFO_YYMM                  "(YYMM)"
#define STR_INFO_INPUT_CASHIER_NO      "INPUT CASHIER NO."
#define STR_INFO_INVALID_CASHIER_NO    "INVALID CASHIER NO."
#define STR_INFO_CASHIER_EXISTED       "CASHIER EXISTED"
#define STR_INFO_CASHIER_NOT_EXISTED   "CASHIER NOT EXISTED"
#define STR_INFO_PLS_CONFIRM           "PLS CONFIRM:"
#define STR_INFO_PLS_TAKE_CARD         "PLS TAKE CARD"
#define STR_INFO_PROCESSING            "PROCESSING..."
#define STR_INFO_UPLOADING             "UPLOADING..."
#define STR_INFO_LACK_OF_PAPER         "LACK OF PAPER"
#define STR_INFO_PRINT_FAILED          "PRINT FAILED"
#define STR_INFO_PRINT_TIMEOUT         "PRINT TIMEOUT"
#define STR_INFO_PRINTING              "PRINTING..."
#define STR_INFO_PRINTING_SETTLE       "PRINTING SETTLE..."
#define STR_INFO_PRINT_FORMAT_ERR      "PRINT FORMAT ERR"
#define STR_INFO_PRINT_OVER            "PRINT OVER"
#define STR_INFO_REFUND_AMT_EXCEED     "REFUND AMT EXCEED"
#define STR_INFO_QUERY_OVER            "QUERY OVER"
#define STR_INFO_PRINT_DETAIL          "PRINT DETAIL..."
#define STR_INFO_STOP_PRINT            "STOP PRINT?"
#define STR_INFO_NO_SETTLE_INFO        "NO SETTLE INFO"
#define STR_INFO_BALANCED_BATCHUP      "BALANCED, BATCH UP"
#define STR_INFO_UNBALANCED_BATCH_UP   "UNBALANCED, BATCH UP"
#define STR_INFO_BATCH_UP_FAILED       "BATCH UP FAILED"
#define STR_INFO_CONTINUE_BATCH_UP     "CONTINUE BATCH UP?"
#define STR_INFO_PRINT_TRXN_DETAIL     "PRINT TRANS DETAIL?"
#define STR_INFO_NO_OR_YES             "0.NO  1.YES"
#define STR_INFO_PRINT_FAILED_DETAIL   "PRINT FAILED DETAIL?"
#define STR_INFO_SET_FAILED            "SET FAILED"
#define STR_INFO_PLS_SETTLE_FIRST      "PLS SETTLE FIRST"
#define STR_INFO_LEN_ERR               "LEN ERR"
#define STR_INFO_CARD_READ_OK          "CARD READ OK"

#define STR_SETUP_COMMU_MODE           "SELECT COMMU MODE"
#define STR_SETUP_MODEM                "MODEM"
#define STR_SETUP_GPRS                 "GPRS"
#define STR_SETUP_CDMA                 "CDMA"
#define STR_SETUP_ETHERNET             "ETHERNET"
#define STR_SETUP_WIFI                 "WIFI"
#define STR_SETUP_OTHER                "OTHER"
#define STR_SETUP_WIFI_HOTSPOTS        "HOTSPOTS"
#define STR_SETUP_WIFI_PARAMETER       "PARAMETER"
#define STR_SETUP_SHIELD               "TRANS SHIELD"
#define STR_SETUP_PIN                  "TRANS PIN"
#define STR_SETUP_SWIPE                "TRANS SWIPE"
#define STR_SETUP_OFFLINE              "OFFLINE"
#define STR_SETUP_MANUAL_INPUT_KEY     "MANUAL INPUT KEY"
#define STR_SETUP_KEY_INDEX            "KEY INDEX"
#define STR_SETUP_DES_TYPE             "DES TYPE"
#define STR_SETUP_DUPKT                "DUPKT"
#define STR_SETUP_CHANGE_SYSTEM_PWD    "CHANGE SYSTEM PWD"
#define STR_SETUP_CHANGE_ADMIN_PWD     "CHANGE ADMIN PWD"
#define STR_SETUP_CLEAR_REVERSAL       "CLEAR REVERSAL"
#define STR_SETUP_CLEAR_TRANS          "CLEAR TRANS"
#define STR_SETUP_AUTO_TRANS           "AUTO TRANS"
#define STR_SETUP_VERSION              "VERSION"
#define STR_SETUP_TERMINAL             "TERMINAL"
#define STR_SETUP_COMMUNICATION        "COMMUNICATION"
#define STR_SETUP_TRANSACTION          "TRANSACTION"
#define STR_SETUP_SYSTEM               "SYSTEM"
#define STR_SETUP_KEY_MANAGEMENT       "KEY MANAGEMENT"
#define STR_SETUP_CHANGE_PASSWORD      "CHANGE PASSWORD"
#define STR_SETUP_ADD_CASHIER          "ADD CASHIER"
#define STR_SETUP_INQUIRE_CASHIER      "INQUIRE CASHIER"
#define STR_SETUP_DELETE_CASHIER       "DELETE CASHIER"
#define STR_SETUP_CHANGE_CASHIER_PWD   "CHANGE CASHIER PWD"
#define STR_SETUP_SYSTEM_MANAGEMENT    "SYSTEM MANAGEMENT"    
#define STR_SETUP_ADMIN_MANAGE         "ADMIN MANAGE"
#define STR_SETUP_MID                  "MID(15):"
#define STR_SETUP_TID                  "TID(8):"
#define STR_SETUP_MERCHANT_NAME        "MERCHANT NAME:"
#define STR_SETUP_COUNTRY_CODE         "COUNTRY CODE:"
#define STR_SETUP_CURRENCY_CODE        "CURRENCY CODE:"
#define STR_SETUP_CURRENCY_NAME        "CURRENCY NAME:"
#define STR_SETUP_AMOUNT_CENT_LENGTH   "AMOUNT CENT LENGTH:"
#define STR_SETUP_1_MODEM_2_GPRS       "1.MODEM   2.GPRS"
#define STR_SETUP_3_CDMA_4_ETHERNET    "3.CDMA    4.ETHERNET"
#define STR_SETUP_5_WIFI               "5.WIFI"
#define STR_SETUP_5_WIFI_6_ECHO        "5.WIFI    6.ECHO"
#define STR_SETUP_TEL_NUMBER1          "TEL NUMBER1:"
#define STR_SETUP_TEL_NUMBER2          "TEL NUMBER2:"
#define STR_SETUP_TEL_NUMBER3          "TEL NUMBER3:"
#define STR_SETUP_PABX_NO              "PABX NO.:"
#define STR_SETUP_APN                  "APN:"
#define STR_SETUP_HOST_IP              "HOST IP:"
#define STR_SETUP_PORT                 "PORT:"
#define STR_SETUP_ENABLE_USER          "ENABLE USER?"
#define STR_SETUP_USER                 "USER:"
#define STR_SETUP_USER_PASSWORD        "USER PASSWORD:"
#define STR_SETUP_USER_NAME            "USER NAME:"
#define STR_SETUP_DHCP                 "ENABLE DHCP?"
#define STR_SETUP_LOCAL_IP             "LOCAL IP:"
#define STR_SETUP_SUBNET_MASK          "SUBNET MASK:"
#define STR_SETUP_GATEWAY              "GATEWAY:"
#define STR_SETUP_OPEN_WIFI_DEVICE     "OPEN WIFI DEVICE..."
#define STR_SETUP_OPEN_FAILED          "OPEN FAILED"
#define STR_SETUP_NEED_SCAN_HOTSPOTS   "NEED SCAN HOTSPOTS?"
#define STR_SETUP_SCAN_HOTSPOTS        "SCAN HOTSPOTS..."
#define STR_SETUP_SCAN_HOTSPOTS_FAIL   "SCAN FAIL"
#define STR_SETUP_SELECT_SSID          "SELECT A SSID"
#define STR_SETUP_WIFI_CONNECTING      "WIFI CONNECTING..."
#define STR_SETUP_CONNECT_WIFI_SUCC    "CONNECT WIFI SUCC"
#define STR_SETUP_TPDU                 "TPDU:"
#define STR_SETUP_ENABLE_SSL           "ENABLE SSL:"
#define STR_SETUP_1_ENABLE             "1-ENABLE"
#define STR_SETUP_0_DISABLE            "0-DISABLE"
#define STR_SETUP_MSG_LEN_FORMAT       "MSG LEN FORMAT:"
#define STR_SETUP_0_BCD                "0-BCD"
#define STR_SETUP_1_HEX                "1-HEX"
#define STR_SETUP_DAIL_TIME            "DAIL TIME:"
#define STR_SETUP_REDAIL_TIMES         "REDAIL TIMES:"
#define STR_SETUP_RECV_TIME            "RECV TIME:"
#define STR_SETUP_1_SUPPORT            "1-SUPPORT"
#define STR_SETUP_0_NOT_SUPPORT        "0-NOT SUPPORT"
#define STR_SETUP_VOID_INPUT_PIN       "VOID INPUT PIN?"
#define STR_SETUP_YES_OR_NO            "1-YES  0-NO"
#define STR_SETUP_VOID_SWIPE_CARD      "VOID SWIPE CARD?"
#define STR_SETUP_AUTO_LOGOUT          "AUTO LOGOUT?"
#define STR_SETUP_OFFLINE_UPLOAD_TIMES "OFFLINE UPLOAD TIMES"
#define STR_SETUP_1_9                  "(1-9):"
#define STR_SETUP_AUTO_UPLOAD_NUM      "AUTO UPLOAD NUM:"
#define STR_SETUP_INPUT_ADMIN_PWD      "INPUT ADMIN PWD?"
#define STR_SETUP_MAX_REFUND_AMT       "MAX REFUND AMT:"
#define STR_SETUP_TIP_RATE             "TIP RATE(%):"
#define STR_SETUP_PAYPASS_PAYWAVE      "PAYPASS/PAYWAVE:"
#define STR_SETUP_FALLBACK             "FALLBACK:"
#define STR_SETUP_REFUND_MODE          "REFUND MODE:"
#define STR_SETUP_0_GENERAL            "0-GENERAL"
#define STR_SETUP_1_CHINA_UNION_PAY    "1-CHINA UNION PAY"
#define STR_SETUP_AUTO_LOGON           "AUTO LOGON:"
#define STR_SETUP_VIRTUAL_RF_LED       "VIRTUAL RF LED:"
#define STR_SETUP_MASK_CARD_NO         "MASK CARD NO.?"
#define STR_SETUP_VOID_AMT_PRINT       "VOID AMT PRINT '-'?"
#define STR_SETUP_CURRENT_TRACE_NO     "CURRENT TRACE NO.:"
#define STR_SETUP_CURRENT_BATCH_NO     "CURRENT BATCH NO.:"
#define STR_SETUP_PRINT_TIMES          "PRINT TIMES:"
#define STR_SETUP_PRINT_SIZE           "PRINT SIZE:"
#define STR_SETUP_1_BIG_2_MEDIUM       "1-BIG 2-MEDIUM:"
#define STR_SETUP_3_SMALL              "3-SMALL:"
#define STR_SETUP_REVERSAL_TIMES       "REVERSAL TIMES(1-3):"
#define STR_SETUP_MAX_TRANS_NUM        "MAX TRANS NUM:"
#define STR_SETUP_1_500                "(1-500)"
#define STR_SETUP_PINPAD_MODE          "PINPAD MODE:"
#define STR_SETUP_0_INTERNAL           "0-INTERNAL"
#define STR_SETUP_1_EXTERNAL           "1-EXTERNAL"
#define STR_SETUP_RF_READER_MODE       "RF READER MODE:"
#define STR_SETUP_0_EXTERNAL           "0-EXTERNAL"
#define STR_SETUP_1_INTERNAL           "1-INTERNAL"
#define STR_SETUP_IDLE_TIME            "IDLE TIME:"
#define STR_SETUP_KEY_INDEX_0_9        "KEY INDEX(0-9):"
#define STR_SETUP_PLS_INPUT_TMK_16     "PLS INPUT TMK(16):"
#define STR_SETUP_PLS_INPUT_TMK_32     "PLS INPUT TMK(32):"
#define STR_SETUP_INJECT_TMK_SUCCESS   "INJECT TMK SUCCESS"    
#define STR_SETUP_INJECT_TMK_FAILED    "INJECT TMK FAILED"
#define STR_SETUP_KEY_ALGORITHM        "KEY ALGORITHM:"
#define STR_SETUP_0_DES_1_3DES         "0-DES  1-3DES"
#define STR_SETUP_DUKPT                "DUKPT:"
#define STR_SETUP_KSN                  "KSN(20):"
#define STR_SETUP_CHANGE_PWD_SUCCESS   "CHANGE PWD SUCCESS"
#define STR_SETUP_ClEAR_REV_SUCC       "CLEAR REV SUCC"
#define STR_SETUP_ClEAR_TRANS_SUCC     "CLEAR TRANS SUCC"
#define STR_SETUP_INPUT_TRANS_NUM      "INPUT TRANS NUM:"
#define STR_SETUP_VER                  "VER:"
#define STR_SETUP_DATE                 "DATE:"
#define STR_SETUP_TIME                 "TIME:"
#define STR_SETUP_MANAGE               "MANAGE:"
#define STR_SETUP_LIBXGDEMV            "LIBXGDEMV:"
#define STR_SETUP_DAEMON               "DAEMON:"
#define STR_SETUP_PANEL                "PANEL:"
#define STR_SETUP_LIBDEV               "LIBDEV:"
#define STR_SETUP_CASHIER_NO           "CASHIER NO.:"
#define STR_SETUP_PLS_INPUT_PWD        "INPUT PWD:"
#define STR_SETUP_PLS_INPUT_PWD_AGAIN  "INPUT PWD AGAIN:"
#define STR_SETUP_ADD_SUCCESS          "ADD SUCCESS"
#define STR_SETUP_DETELE_SUCCESS       "DETELE SUCCESS"
#define STR_SETUP_SET_TIME             "SET TIME"
#define STR_SETUP_SYSTEM_TIME          "SYSTEM TIME"
#define STR_SETUP_NEW_TIME             "NEW TIME"
#define STR_DEBUG_8583				   "PRINT 8583"
#define STR_SETUP_INPUT_STN			   "INPUT STN"
/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
#endif

