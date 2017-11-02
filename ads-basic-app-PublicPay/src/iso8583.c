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
// The property for each field
static SDK_8583_STFIELDDEF TabIsoFields[SDK_8583_FIELDMAX + 1] =
{
    /* FLD  00 */ {0, SDK_8583_LEN_BCD,  4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  01 */ {0, SDK_8583_LEN_BCD,  8, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0},
    /* FLD  02 */ {2, SDK_8583_LEN_BCD, 19, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD  03 */ {0, SDK_8583_LEN_BCD,  6, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  04 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  05 */ {0, SDK_8583_LEN_BCD, 20, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  06 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  07 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  08 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  09 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  10 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  11 */ {0, SDK_8583_LEN_BCD, 6, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  12 */ {0, SDK_8583_LEN_BCD, 6, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  13 */ {0, SDK_8583_LEN_BCD, 4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  14 */ {0, SDK_8583_LEN_BCD, 4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  15 */ {0, SDK_8583_LEN_BCD, 4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  16 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  17 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  18 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  19 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  20 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  21 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  22 */ {0, SDK_8583_LEN_BCD, 3, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  23 */ {0, SDK_8583_LEN_BCD, 3, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  24 */ {0, SDK_8583_LEN_BCD, 4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  25 */ {0, SDK_8583_LEN_BCD, 2, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  26 */ {0, SDK_8583_LEN_BCD, 2, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  27 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  28 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  29 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  30 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  31 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  32 */ {2, SDK_8583_LEN_BCD, 11, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  33 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  34 */ {0, SDK_8583_LEN_BCD, 40, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  35 */ {2, SDK_8583_LEN_BCD, 37, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD  36 */ {3, SDK_8583_LEN_BCD, 104, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD  37 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_ASC, SDK_8583_ALIGN_R, '0'},
    /* FLD  38 */ {0, SDK_8583_LEN_BCD, 6, SDK_8583_DATA_ASC, SDK_8583_ALIGN_R, '0'},
    /* FLD  39 */ {0, SDK_8583_LEN_BCD, 2, SDK_8583_DATA_ASC, SDK_8583_ALIGN_R, '0'},
    /* FLD  40 */ {0, SDK_8583_LEN_BCD, 40, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  41 */ {0, SDK_8583_LEN_BCD, 8, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  42 */ {0, SDK_8583_LEN_BCD, 15, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  43 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  44 */ {2, SDK_8583_LEN_BCD, 25, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  45 */ {2, SDK_8583_LEN_BCD, 76, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  46 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  47 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    			// {3, SDK_8583_LEN_BCD, 322, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},  //for cup                 
    /* FLD  48 */ {3, SDK_8583_LEN_BCD, 332, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0}, /*for voice sending*/
    /* FLD  49 */ {0, SDK_8583_LEN_BCD, 3, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  50 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  51 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  52 */ {0, SDK_8583_LEN_BCD, 8, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0},
    /* FLD  53 */ {0, SDK_8583_LEN_BCD, 16, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  54 */ {3, SDK_8583_LEN_BCD, 40, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  55 */ {3, SDK_8583_LEN_BCD, 255, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0},
    /* FLD  56 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  57 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  58 */ {3, SDK_8583_LEN_BCD, 100, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  59 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  60 */ {3, SDK_8583_LEN_BCD, 17, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  61 */ {3, SDK_8583_LEN_BCD, 29, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  62 */ {3, SDK_8583_LEN_BCD, 512, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  63 */ {3, SDK_8583_LEN_BCD, 163, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  64 */ {0, SDK_8583_LEN_BCD,  8, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0},
    /* FLD  65 */ {0, SDK_8583_LEN_BCD,  8, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0},
    /* FLD  66 */ {2, SDK_8583_LEN_BCD, 19, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD  67 */ {0, SDK_8583_LEN_BCD,  6, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  68 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  69 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  70 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  71 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  72 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  73 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  74 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  75 */ {0, SDK_8583_LEN_BCD, 6, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  76 */ {0, SDK_8583_LEN_BCD, 6, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  77 */ {0, SDK_8583_LEN_BCD, 4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  78 */ {0, SDK_8583_LEN_BCD, 4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  79 */ {0, SDK_8583_LEN_BCD, 4, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  80 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  81 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  82 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  83 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  84 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  85 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  86 */ {0, SDK_8583_LEN_BCD, 3, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  87 */ {0, SDK_8583_LEN_BCD, 3, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  88 */ {0, SDK_8583_LEN_BCD, 3, SDK_8583_DATA_ASC, SDK_8583_ALIGN_R, '0'},
    /* FLD  89 */ {0, SDK_8583_LEN_BCD, 2, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  90 */ {0, SDK_8583_LEN_BCD, 2, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  91 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  92 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  93 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  94 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  95 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  96 */ {2, SDK_8583_LEN_BCD, 11, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD  97 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD  98 */ {0, SDK_8583_LEN_BCD, 40, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD  99 */ {2, SDK_8583_LEN_BCD, 37, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD 100 */ {3, SDK_8583_LEN_BCD, 104, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD 101 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_ASC, SDK_8583_ALIGN_R, '0'},
    /* FLD 102 */ {0, SDK_8583_LEN_BCD, 6, SDK_8583_DATA_ASC, SDK_8583_ALIGN_R, '0'},
    /* FLD 103 */ {0, SDK_8583_LEN_BCD, 2, SDK_8583_DATA_ASC, SDK_8583_ALIGN_R, '0'},
    /* FLD 104 */ {0, SDK_8583_LEN_BCD, 40, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 105 */ {0, SDK_8583_LEN_BCD, 8, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 106 */ {0, SDK_8583_LEN_BCD, 15, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 107 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 108 */ {2, SDK_8583_LEN_BCD, 25, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 109 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 110 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 111 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 112 */ {3, SDK_8583_LEN_BCD, 322, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD 113 */ {0, SDK_8583_LEN_BCD, 3, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 114 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 115 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 116 */ {0, SDK_8583_LEN_BCD, 8, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0},
    /* FLD 117 */ {0, SDK_8583_LEN_BCD, 16, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, '0'},
    /* FLD 118 */ {3, SDK_8583_LEN_BCD, 40, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 119 */ {3, SDK_8583_LEN_BCD, 255, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0},
    /* FLD 120 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 121 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 122 */ {3, SDK_8583_LEN_BCD, 100, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 123 */ {0, SDK_8583_LEN_BCD, 12, SDK_8583_DATA_BCD, SDK_8583_ALIGN_R, '0'},
    /* FLD 124 */ {3, SDK_8583_LEN_BCD, 17, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD 125 */ {3, SDK_8583_LEN_BCD, 29, SDK_8583_DATA_BCD, SDK_8583_ALIGN_L, 'F'},
    /* FLD 126 */ {3, SDK_8583_LEN_BCD, 512, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 127 */ {3, SDK_8583_LEN_BCD, 163, SDK_8583_DATA_ASC, SDK_8583_ALIGN_L, ' '},
    /* FLD 128 */ {0, SDK_8583_LEN_BCD,  8, SDK_8583_DATA_BIT, SDK_8583_ALIGN_L, 0}
};

// DOL for EMV transaction
static const ST_ICCDATA_DOL TabEmvDOL[] =
{
    {"\x9f\x26", 0x08, 1, NULL},           // Application Cryptogram (M)
    {"\x9f\x27", 0x01, 1, NULL},           // Cryptogram Information Data (M)
    {"\x9f\x10", 0x20, 1, NULL},           // Issuer Application Data (M)
    {"\x9f\x37", 0x04, 1, NULL},           // Unpredicatable Number (M)
    {"\x9f\x36", 0x02, 1, NULL},           // Application Transaction Counter (M)
    {"\x95",     0x05, 1, NULL},               // Terminal Verification Results (M)
    {"\x9a",     0x03, 1, NULL},               // Transaction Date (M)
    {"\x9c",     0x01, 1, NULL},               // Transaction Type (M)
    {"\x9f\x02", 0x06, 1, NULL},           // Amount, Authorised (M)
    {"\x5f\x2a", 0x02, 1, NULL},           // Transaction Currency Code (M)
    {"\x82",     0x02, 1, NULL},               // Application Interchange Profile (M)
    {"\x9f\x1a", 0x02, 1, NULL},           // Terminal Country Code (M)
    {"\x9f\x03", 0x06, 1, NULL},           // Amount, Other (M)
    {"\x9f\x33", 0x03, 1, NULL},           // Terminal Capabilities (M)
    {"\x9f\x34", 0x03, 0, NULL},           // Cardholder Verification Method (O)
    {"\x9f\x35", 0x01, 0, NULL},           // Terminal Type (O)
    {"\x9f\x1e", 0x08, 0, NULL},           // Interface Device (IFD) Serial Number (C)
    {"\x84",     0x10, 0, NULL},               // Dedicated File (DF) Name (O)
    {"\x9f\x09", 0x02, 0, NULL},           // Application Version Number (O)
    {"\x9f\x41", 0x04, 0, NULL},           // Transaction Sequence Counter (O)
    {"\x9f\x63", 0x10, 0, NULL},           // Card Product Identification Information (0)
};

// DOL for EMV reversal transaction
static const ST_ICCDATA_DOL TabReversalEmvDOL[] =
{
    {"\x95",     0x05, 1, gstTransData.stTransLog.stEmvInfo.heTVR},              // Terminal Verification Results (M)
    {"\x9f\x1e", 0x08, 0, gstTransData.stTransLog.stEmvInfo.asIFDSN},            // Interface Device (IFD) Serial Number (C)
    {"\x9f\x10", 0x20, 1, gstTransData.stTransLog.stEmvInfo.heIAD},              // Issuer Application Data (M)
    {"\x9f\x36", 0x02, 1, gstTransData.stTransLog.stEmvInfo.heATC},              // Application Transaction Counter (M)
    {"\xdf\x31", 0x15, 0, gstTransData.stTransLog.stEmvInfo.heScriptResult},     // Issuer Script Result (C)
};

static const ST_ICCDATA_DOL TabScriptEmvDOL[] =
{
    {"\x9f\x33", 0x03, 1, gstTransData.stTransLog.stEmvInfo.heTermCap},         // Terminal Capabilities (M)
    {"\x95",     0x05, 1, gstTransData.stTransLog.stEmvInfo.heTVR},             // Terminal Verification Results (M)
    {"\x9f\x37", 0x04, 1, gstTransData.stTransLog.stEmvInfo.heUN},              // Unpredicatable Number (M)
    {"\x9f\x1e", 0x08, 0, gstTransData.stTransLog.stEmvInfo.asIFDSN},           // Interface Device (IFD) Serial Number (C)
    {"\x9f\x10", 0x20, 1, gstTransData.stTransLog.stEmvInfo.heIAD},             // Issuer Application Data (M)
    {"\x9f\x26", 0x08, 1, gstTransData.stTransLog.stEmvInfo.heAC},              // Application Cryptogram (M)
    {"\x9f\x36", 0x02, 1, gstTransData.stTransLog.stEmvInfo.heATC},             // Application Transaction Counter (M)
    {"\x82",     0x02, 1, gstTransData.stTransLog.stEmvInfo.heAIP},             // Application Interchange Profile (M)
    {"\xdf\x31", 0x15, 1, gstTransData.stTransLog.stEmvInfo.heScriptResult},    // Issuer Script Result (M)
    {"\x9f\x1a", 0x02, 1, gstTransData.stTransLog.stEmvInfo.bcCountryCode},     // Terminal Country Code (M)
    {"\x9a",     0x03, 1, gstTransData.stTransLog.stEmvInfo.heTransDate},       // Transaction Date (M)
};

//DOL for Visa PayWave
static const ST_ICCDATA_DOL TabPaywaveDOL[] =
{
    {"\x9f\x26", 0x08, 1, NULL},           // Application Cryptogram (M)
    {"\x9f\x27", 0x01, 1, NULL},           // Cryptogram Information Data (M)
    {"\x9f\x10", 0x20, 1, NULL},           // Issuer Application Data (M)
    {"\x9f\x37", 0x04, 1, NULL},           // Unpredicatable Number (M)
    {"\x9f\x36", 0x02, 1, NULL},           // Application Transaction Counter (M)
    {"\x95",     0x05, 1, NULL},               // Terminal Verification Results (M)
    {"\x9a",     0x03, 1, NULL},               // Transaction Date (M)
    {"\x9c",     0x01, 1, NULL},               // Transaction Type (M)
    {"\x9f\x02", 0x06, 1, NULL},           // Amount, Authorised (M)
    {"\x5f\x2a", 0x02, 1, NULL},           // Transaction Currency Code (M)
    {"\x82",     0x02, 1, NULL},               // Application Interchange Profile (M)
    {"\x9f\x1a", 0x02, 1, NULL},           // Terminal Country Code (M)
    {"\x9f\x03", 0x06, 1, NULL},           // Amount, Other (M)
    {"\x9f\x33", 0x03, 1, NULL},           // Terminal Capabilities (M)
    {"\x9f\x35", 0x01, 0, NULL},           //  Terminal Type (O)
    {"\x9f\x1e", 0x08, 0, NULL},           // Interface Device (IFD) Serial Number (C)
    {"\x84",     0x10, 0, NULL},               // Dedicated File (DF) Name (O)
    {"\x9f\x41", 0x04, 0, NULL},           // Transaction Sequence Counter (O)
};

//DOL for MasterCard PayPass
static const ST_ICCDATA_DOL TabPaypassDOL[] =
{
    {"\x5f\x2a", 0x02, 1, NULL},           // Transaction Currency Code (M)
    {"\x82",     0x02, 1, NULL},               // Application Interchange Profile (M)
    {"\x84",     0x10, 0, NULL},               // Dedicated File (DF) Name (O)
    {"\x95",     0x05, 1, NULL},               // Terminal Verification Results (M)
    {"\x9a",     0x03, 1, NULL},               // Transaction Date (M)
    {"\x9c",     0x01, 1, NULL},               // Transaction Type (M)
    {"\x9f\x02", 0x06, 1, NULL},           // Amount, Authorised (M)
    {"\x9f\x03", 0x06, 1, NULL},           // Amount, Other (M)
    {"\x9f\x09", 0x02, 0, NULL},           // Application Version Number O
    {"\x9f\x10", 0x20, 1, NULL},           // Issuer Application Data (M)
    {"\x9f\x1a", 0x02, 1, NULL},           // Terminal Country Code (M)
    {"\x9f\x1e", 0x08, 0, NULL},           // Interface Device (IFD) Serial Number (C)
    {"\x9f\x26", 0x08, 1, NULL},           // Application Cryptogram (M)
    {"\x9f\x27", 0x01, 1, NULL},           // Cryptogram Information Data (M)
    {"\x9f\x33", 0x03, 1, NULL},           // Terminal Capabilities (M)
    {"\x9f\x34", 0x03, 0, NULL},           // Cardholder Verification Method (O)
    {"\x9f\x35", 0x01, 0, NULL},           // Terminal Type (O)
    {"\x9f\x36", 0x02, 1, NULL},           // Application Transaction Counter (M)
    {"\x9f\x37", 0x04, 1, NULL},           // Unpredicatable Number (M)
    {"\x9f\x41", 0x04, 0, NULL},           // Transaction Sequence Counter (O)
};

/*****************************************************************************
** Description :  Set the content for a field
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstPacket8583 : 8583 message buffer
                  (2)u8 ucFieldNo : field number
                  (3)u8 *pheFieldData : field data
                  (4)u16 usDataLen : data length to set
                  
                  output:
                  (1)SDK_8583_ST8583 *pstPacket8583 : 8583 message buffer
                  
** Return      :  same as "sdk8583SetField"
** Author      :  wenmin   2016-10-18 
** Remarks     :  see the introductions of "sdk8583SetField" in SDK API
*****************************************************************************/
s32 IsoSetField(SDK_8583_ST8583 *pstPacket8583, u8 ucFieldNo, u8 *pheFieldData, u16 usDataLen)
{
    return sdk8583SetField(TabIsoFields[ucFieldNo], pstPacket8583, ucFieldNo, pheFieldData, usDataLen);
}

/*****************************************************************************
** Description :  Set the content for a field
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstPacket8583 : 8583 message buffer
                  (2)u8 ucFieldNo : field number
                  (3)u16 usMaxSize : data buffer maximum length
                  
                  output:
                  (1)u8 *pheFieldData : data buffer
** Return      :  
** Author      :  wenmin   2016-10-18 
** Remarks     :  see the introductions of "sdk8583SetField" in SDK API
*****************************************************************************/
s32 IsoGetField(SDK_8583_ST8583 *pstPacket8583, u8 ucFieldNo, u8 *pheFieldData, u16 usMaxSize)
{
    return sdk8583GetField(TabIsoFields[ucFieldNo], pstPacket8583, ucFieldNo, pheFieldData, usMaxSize);
}

/*****************************************************************************
** Description :  Pack public message fields
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstIsoMsg : 8583 message buffer
                  (2)ST_TRANSDATA *pstTransData : all transaction correlation data
                  (3)u8 *pasBitMap : bitmap to set public fields
                  
** Return      :  iso8583 bag length

** Author      :  wenmin   2016-10-18 
** Remarks     :  will set message head, and the field data. if some transaction have
                  different field data to set, must reset the different field after
                  call this funtion. The message will use the last set.
                  if message need to calc MAC, the "pasBitMap" field 64 must set
                  to '1'
*****************************************************************************/
s32 IsoPackPublicMsg(SDK_8583_ST8583 *pstIsoMsg, ST_TRANSDATA *pstTransData, u8 *pasBitMap)
{
    u8 pin_len;
    u8 bitmap[16], tmp[256], buf[256]; 
    u32 i, len, fieldno;
    ST_CARDINFO *pst_cardinfo = NULL;
    ST_MSGINFO *pst_msginfo = NULL;

    if ((NULL == pstIsoMsg) || (NULL == pstTransData) || (NULL == pasBitMap))
    {
        return 0;
    }
    
    //pst_cardinfo->stCardParam.ucCardMode = pstTransData->stTransLog.stCardInfo.stCardParam.ucCardMode;
    //pst_cardinfo->stCardParam.ucCLType = pstTransData->stTransLog.pst_cardinfo->stCardParam.ucCLType;
    pin_len = pstTransData->hePIN[0];
    pst_msginfo = &pstTransData->stTransLog.stMsgInfo;
    pst_cardinfo = &pstTransData->stTransLog.stCardInfo;

    // pack message header
    IsoPackMsgHeader(pstIsoMsg);

    // bitmap : ASC -> BCD
    len = strlen(pasBitMap);
    if (len > 32)
    {
        len = 32;
    }
    memset(bitmap,0,sizeof(bitmap));
    sdkAscToBcd(bitmap, pasBitMap, len);

    // get max. field no.
    fieldno = 64;
    if (IsoCheckBimap(bitmap, 1))
    {
        fieldno = 128;
    }

    for (i = 2; i <= fieldno; i++)
    {
        if (!IsoCheckBimap(bitmap, i))
        {
            continue;
        }

        switch (i)
        {
            case 2:
                if (SDK_ICC_MAG != pst_cardinfo->stCardParam.ucCardMode)
                {
                    memset(tmp, 0, sizeof(tmp));
                    if(SDK_ERR != TrnGetMagCardNo(&pst_cardinfo->stCardData, tmp))
                    {
                        IsoSetField(pstIsoMsg, 2, tmp, strlen(tmp));
                    }
                }
                break;

            case 3:
                IsoSetField(pstIsoMsg, 3, "000000", 6);
                break;

            case 4:
                if(strlen(pst_msginfo->asAmount))
                {
                    IsoSetField(pstIsoMsg, 4, pst_msginfo->asAmount, 12);
                }
                break;

            case 11:
                IsoSetField(pstIsoMsg, 11, gstAppSysCfg.stTransParam.asTraceNO, 6);
                break;

            case 14:
                if (strlen(pst_cardinfo->stCardData.asExpiredDate) >= 4 &&
                    (0 != memcmp(pst_cardinfo->stCardData.asExpiredDate, "0000", 4)))
                {
                    IsoSetField(pstIsoMsg, 14, pst_cardinfo->stCardData.asExpiredDate, 4);
                }
                break;

            case 22:
                if (SDK_ICC_MANUAL == pst_cardinfo->stCardParam.ucCardMode)
                {
                    strcpy(pst_msginfo->asEntryMode, "01");
                }
                else if (SDK_ICC_ICC == pst_cardinfo->stCardParam.ucCardMode 
                      || SDK_ICC_RF == pst_cardinfo->stCardParam.ucCardMode)
                {
                    if (CTLSFLOW_FULLEMV == pst_cardinfo->stCardParam.ucCLType)
                    {
                        strcpy(pst_msginfo->asEntryMode, "98");
                    }
                    else if (CTLSFLOW_QUICK == pst_cardinfo->stCardParam.ucCLType)
                    {
                        strcpy(pst_msginfo->asEntryMode, "07");
                    }
                    else if (CTLSFLOW_MSD == pst_cardinfo->stCardParam.ucCLType)
                    {
                        strcpy(pst_msginfo->asEntryMode, "91");
                    }
                    else
                    {
                        strcpy(pst_msginfo->asEntryMode, "05");
                    }
                }
                else if (SDK_ICC_MAG == pst_cardinfo->stCardParam.ucCardMode) 
                {
                    strcpy(pst_msginfo->asEntryMode, "02");
                }
                else
                {
                    strcpy(pst_msginfo->asEntryMode, "00");
                }    
                
                if (pin_len)   //PIN entered
                {
                    strcat(&pst_msginfo->asEntryMode[2], "1");
                }
                else    //PIN NOT entered
                {
                    strcat(&pst_msginfo->asEntryMode[2], "2");
                }
                IsoSetField(pstIsoMsg, 22, pst_msginfo->asEntryMode, strlen(pst_msginfo->asEntryMode));
                break;

            case 23:
                if (SDK_ICC_MANUAL != pst_cardinfo->stCardParam.ucCardMode 
                    && SDK_ICC_MAG != pst_cardinfo->stCardParam.ucCardMode 
                    && 0 != pst_cardinfo->stCardParam.ucCardMode)
                {
                    memset(tmp, 0, sizeof(tmp));
                    len = sizeof(tmp);

                    if (sdkIccReadTLV("\x5F\x34", tmp, &len) > 0)
                    {
                        if (len > 0)
                        {
                            sdkBcdToAsc(buf, tmp, len);
                            IsoSetField(pstIsoMsg, 23, buf, len * 2);
                        }
                    }
                    else
                    {
                        IsoSetField(pstIsoMsg, 23, "000", 3);
                        Trace("iso", "read tag 5f34 failed!\r\n");
                    }
                }
                break;

            case 25:
                IsoSetField(pstIsoMsg, 25, "00", 2);
                break;

            case 26:
                if (pin_len > 0)
                {
                    IsoSetField(pstIsoMsg, 26, "12", 2);
                }
                break;

            case 35:
                if (pst_cardinfo->stCardData.ucTrack2Len)
                {
                    IsoSetField(pstIsoMsg, 35, (u8 *)pst_cardinfo->stCardData.asTrack2Data, pst_cardinfo->stCardData.ucTrack2Len);
                }
                break;

            case 36:
                if (pst_cardinfo->stCardData.ucTrack3Len)
                {
                    IsoSetField(pstIsoMsg, 36, (u8 *)pst_cardinfo->stCardData.asTrack3Data, pst_cardinfo->stCardData.ucTrack3Len);
                }
                break;
                
            case 37:
                if (strlen(pst_msginfo->asRefNO))
                {
                    IsoSetField(pstIsoMsg, 37, (u8 *)pst_msginfo->asRefNO, 12);
                }
                break;
                
            case 38:
                if (strlen(pst_msginfo->asAuthCode))
                {
                    IsoSetField(pstIsoMsg, 38, (u8 *)pst_msginfo->asAuthCode, 6);
                }
                break;

            case 41:
                IsoSetField(pstIsoMsg, 41, gstAppSysCfg.stTermInfo.asTermID, 8);
                break;

            case 42:
                IsoSetField(pstIsoMsg, 42, gstAppSysCfg.stTermInfo.asMerchID, 15);
                break;
			case 48:
				break;
            case 49:
                IsoSetField(pstIsoMsg, 49, gstAppSysCfg.stTermInfo.asCurrencyCode, 3);
                break;

            case 52:
                if (pin_len > 0)
                {
                    IsoSetField(pstIsoMsg, 52, (u8 *)&pstTransData->hePIN[1], 8);
                }
                break;

            case 53:
                if (pin_len > 0 || pst_cardinfo->stCardData.ucTrack2Len > 0 
                    || pst_cardinfo->stCardData.ucTrack3Len > 0)
                {
                    memset(tmp, '0', 16);
                    if(pin_len > 0)
                    {
                        if(0 != pst_cardinfo->stCardParam.ucCardMode)
                        {
                            tmp[0] = '2';
                        }
                        else
                        {
                            tmp[0] = '1';
                        }
                    }
                    else
                    {
                        tmp[0] = '0';
                    }
                    if(gstAppSysCfg.stSecureKey.bIsTripleDES)
                    {
                        tmp[1] = '6';
                    }
                    IsoSetField(pstIsoMsg, 53, tmp, 16);
                }
                break;

            case 55:
                if (SDK_ICC_MANUAL != pst_cardinfo->stCardParam.ucCardMode 
                    && SDK_ICC_MAG != pst_cardinfo->stCardParam.ucCardMode 
                    && 0 != pst_cardinfo->stCardParam.ucCardMode)
                {
                    IsoFormIccDataField055(tmp, &len);        // Pack EMV data for field 55
                    IsoSetField(pstIsoMsg, 55, tmp, len);
                }
                break;

            case 64:
                IsoSetField(pstIsoMsg, 64, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
                break;

            default:
                IsoSetField(pstIsoMsg, i, tmp, 0);
                break;
        }
    }

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Pack the message header
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg : 8583 message buffer
                  
** Return      :  (1)SDK_PARA_ERR : input parameter error
                  (2)iso8583 bag length
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 IsoPackMsgHeader(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 len;
    u8 tmp[256] = {0};
    ST_CARDINFO *pst_cardinfo = NULL;

    if(NULL == pstIsoMsg)
    {
        return SDK_PARA_ERR;
    }

    pst_cardinfo = &gstTransData.stTransLog.stCardInfo;

    memset(pstIsoMsg, 0x00, sizeof(SDK_8583_ST8583));

    // TPDU
    sdkAscToBcd(pstIsoMsg->ucBagData, gstAppSysCfg.stCommuParam.asTPDU, 10);
    pstIsoMsg->nBagLen += 5;

    // App type
    pstIsoMsg->ucBagData[pstIsoMsg->nBagLen++] = 0x60;
    // update message head
    if (SDK_ICC_ICC == pst_cardinfo->stCardParam.ucCardMode || SDK_ICC_RF == pst_cardinfo->stCardParam.ucCardMode)
    {
        if(CTLSFLOW_QUICK == pst_cardinfo->stCardParam.ucCLType 
           || CTLSFLOW_NORMAL == pst_cardinfo->stCardParam.ucCLType
           || CTLSFLOW_FULLEMV == pst_cardinfo->stCardParam.ucCLType)
        {
            pstIsoMsg->ucBagData[5] = 0x61;
        }
    }    

    // Primary version
    pstIsoMsg->ucBagData[pstIsoMsg->nBagLen++] = 0x31;

    // Terminal status
    pstIsoMsg->ucBagData[pstIsoMsg->nBagLen++] = 0x00;

    // Sub-version
    sdkAscToBcd(&pstIsoMsg->ucBagData[pstIsoMsg->nBagLen], SUBVERSION, 6);
    pstIsoMsg->nBagLen += 3;

    pstIsoMsg->stFiled[SDK_8583_FIELD_MSG].nFieldHead = pstIsoMsg->nBagLen;


    // Bitmap
    len = IsoSetField(pstIsoMsg, SDK_8583_FIELD_MAP, tmp, 0);

    if (len < 0)
    {
        return len;
    }

    return pstIsoMsg->nBagLen;
}

/*****************************************************************************
** Description :  Check if certain field exists in bitmap
** Parameters  :  input:
                  (1)const u8 *pheBitmap : bitmap 
                  (2)u8 ucFieldNo : field number
                  
** Return      :  (1)TRUE : field exist
                  (2)FALSE : field not exist
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
bool IsoCheckBimap(const u8 *pheBitmap, u8 ucFieldNo)
{
    u8 tmp, i, j;

    if (ucFieldNo <= 0)
    {
        return FALSE;
    }
    
    i = (ucFieldNo - 1) / 8;            // i: byte[x]
    j = (ucFieldNo - 1) % 8;            // j: bit[x]

    tmp = 0x80;
    tmp = tmp >> j;

    tmp = tmp & pheBitmap[i];

    if (0 != tmp)
    {
        return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
** Description :  Encrypt sending packet with MAC
** Parameters  :  output:
                  (1)SDK_8583_ST8583 *pstIsoMsg : 8583 message buffer
                  
** Return      :  (1)SDK_ESC : encrypt error
                  (2)SDK_OK : encrypt success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 IsoPackMsgMac(SDK_8583_ST8583 *pstIsoMsg)
{
    s32 ret = SDK_OK;
    u8 mac[16];
	u8 testMacBuf[8 + 1];

	memset(testMacBuf,0,sizeof(testMacBuf));
    // Check if field 64 exists
    if (sdk8583IsDomainExist(pstIsoMsg, 64))
    {
        // Get MAC ,Using cup's method to  calculate mac 
        ret = IsoGetMsgMac(pstIsoMsg, mac);
		/*Take CBC mode to calculate MAC according manual method*/
        // ret = VoiceIsoGetMsgMac(pstIsoMsg, mac);
        if (SDK_OK != ret)
        {
            DispClearContent();
            sdkDispFillRowRam(SDK_DISP_LINE3, 0, STR_INFO_ENCRYPTION_ERROR, SDK_DISP_DEFAULT);
            sdkDispBrushScreen();

            sdkSysBeep(SDK_SYS_BEEP_ERR);
            sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, TMR_PROMPT);
            return SDK_ESC;
        }
        ret = IsoSetField(pstIsoMsg, 64, mac, 8);

        if (ret <= 0)
        {
            return SDK_ESC;
        }
    }
    return SDK_OK;
}

/*****************************************************************************
** Description :  Calculate MAC of ISO8583 message
** Parameters  :  input:
                  (1)SDK_8583_ST8583 *pstIsoMsg : 8583 message buffer
                  
                  output
                  (1)u8 *pucMac : the MAC result
                  
** Return      :  (1)SDK_ESC : encrypt error
                  (2)SDK_OK : encrypt success
** Return      :  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 IsoGetMsgMac(SDK_8583_ST8583 *pstIsoMsg, u8 *pucMac)
{
    s32 ret = SDK_OK;
    u8 *p_data = NULL;
    u16 len;
    u8 ksn_len;
	
    p_data = &(pstIsoMsg->ucBagData[pstIsoMsg->stFiled[SDK_8583_FIELD_MSG].nFieldHead]);
    len = pstIsoMsg->stFiled[64].nFieldHead - pstIsoMsg->stFiled[SDK_8583_FIELD_MSG].nFieldHead;

    if(gstAppSysCfg.stSecureKey.bIsUseDUKPT)
    {
        ret = sdkPEDDukptGetMac(GETMAC_OLDKEY, 0, p_data, len, pucMac, gstTransData.heKSN, &ksn_len, 60 * 1000);
    }
    else
    {
		/*for cup,Mac calculating takes ECB mode*/
        ret = sdkPEDCalcMac(gstAppSysCfg.stSecureKey.uiTakIndex, SDK_PED_ECB, SDK_PED_DES_SINGLE, p_data, len, pucMac);
        /*for voice sending ,Mac calculating takes CBC Mode*/
		//ret = sdkPEDCalcMac(gstAppSysCfg.stSecureKey.uiTakIndex, SDK_PED_CBC, SDK_PED_DES_SINGLE, p_data, len, pucMac);
    }
    if (SDK_OK != ret)
    {
        return SDK_ESC;
    }
    return SDK_OK;
}

s32 VoiceIsoGetMsgMac(SDK_8583_ST8583 *pstIsoMsg, u8 *pucMac)
{
    u8 *p_data = NULL;
    s32 iLen;
	s32 iLen2;
	s32 i;
	s32 j;
	s32 iRet;
	u8 ucMacResult[8+1];
	u8 ucIsoMsgBuf[2048+1];
	ST_SAVED_VOICE_SECURE_MSG stVoiceMsg;
	
    iRet = ReadVoiceSecureMsg(&stVoiceMsg);
	
	if(iRet < 0)
	{
		return iRet;
	}
    p_data = &(pstIsoMsg->ucBagData[pstIsoMsg->stFiled[SDK_8583_FIELD_MSG].nFieldHead]);
    iLen = pstIsoMsg->stFiled[64].nFieldHead - pstIsoMsg->stFiled[SDK_8583_FIELD_MSG].nFieldHead;
	iLen2 = iLen;
	memcpy(ucIsoMsgBuf,p_data,iLen);
	if(0 != (iLen % 8))
	{
		iLen = ((iLen / 8) + 1) * 8;
		memset(ucIsoMsgBuf + iLen2,0x00,iLen - iLen2);
	}
	memset(ucMacResult,0x00,sizeof(ucMacResult));
	for(j = 0;j < iLen / 8;j++)
	{
		for(i = 0;i < 8;i++)
		{
			ucMacResult[i] ^= ucIsoMsgBuf[j * 8 + i];
		}
		sdkDesS(1,ucMacResult,stVoiceMsg.heVoiceTAK);//Take CBC mode to encrypt MAC
	}
	memcpy(pucMac,ucMacResult,8);
    return SDK_OK;
}


/*****************************************************************************
** Description :  Parse ISO8583 message
** Parameters  :  input & output:
                  (1)SDK_8583_ST8583 *pstIsoMsg : 8583 message buffer
                  
** Return      :  same as "sdk8583Parse8583"
** Author      :  wenmin   2016-10-18 
** Remarks     :  see the introductions of "sdk8583Parse8583" in SDK API
*****************************************************************************/
s32 IsoParse8583(SDK_8583_ST8583 *pstIsoMsg)
{
    return sdk8583Parse8583(TabIsoFields, pstIsoMsg, 11);
}

/*****************************************************************************
** Description :  Pack the ICC data for field 55
** Parameters  :  output:
                  (1)u8 *pheDolData : field 55 data buffer
                  (2)s32 *piLen : field 55 length
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void IsoFormIccDataField055(u8 *pheDolData, s32 *piLen)
{
    u16 dollen = 0;
    u8 dol[256];
    u8 buf[256];
    u32 buflen = 0;
    u8 i = 0, num = 0;
    s32 ret;
    ST_ICCDATA_DOL st_doltag;

    // Number of tags to be read
    if( CTLSTYPE_PAYWAVE == gstTransData.eCtlsType)
    {
        num = sizeof(TabPaywaveDOL) / sizeof(ST_ICCDATA_DOL);
    }
    else if(CTLSTYPE_PAYPASS == gstTransData.eCtlsType)
    {
        num = sizeof(TabPaypassDOL) / sizeof(ST_ICCDATA_DOL);
    }
    else if(TRANSID_REVERSAL == gstTransData.stTransLog.eTransID)
    {
        num = sizeof(TabReversalEmvDOL) / sizeof(ST_ICCDATA_DOL);
    }
    else if(TRANSID_SCRIPT == gstTransData.stTransLog.eTransID)
    {
        num = sizeof(TabScriptEmvDOL) / sizeof(ST_ICCDATA_DOL);
    }
    else
    {
        num = sizeof(TabEmvDOL) / sizeof(ST_ICCDATA_DOL);
    }

    // Read tags one by one
    for (i = 0; i < num; i++)
    {
        if( CTLSTYPE_PAYWAVE == gstTransData.eCtlsType )
        {
            memcpy(&st_doltag, &TabPaywaveDOL[i], sizeof(ST_ICCDATA_DOL));
        }
        else if(CTLSTYPE_PAYPASS == gstTransData.eCtlsType)
        {
            memcpy(&st_doltag, &TabPaypassDOL[i], sizeof(ST_ICCDATA_DOL));
        }
        else if(TRANSID_REVERSAL == gstTransData.stTransLog.eTransID)
        {
            memcpy(&st_doltag, &TabReversalEmvDOL[i], sizeof(ST_ICCDATA_DOL));
        }
        else if(TRANSID_SCRIPT == gstTransData.stTransLog.eTransID)
        {
            memcpy(&st_doltag, &TabScriptEmvDOL[i], sizeof(ST_ICCDATA_DOL));
        }
        else
        {
            memcpy(&st_doltag, &TabEmvDOL[i], sizeof(ST_ICCDATA_DOL));
        }

        Trace("iso", "emv tag = [%02x%02x] len = [%d] ism = [%d] \r\n", st_doltag.heTag[0], st_doltag.heTag[1], st_doltag.ucDatalen, st_doltag.bIsMandatory);

        memset(buf, 0, sizeof(buf));
        buflen = sizeof(buf);
        
        if(st_doltag.pAddress)
        {
            ret = SDK_OK;
            buflen = st_doltag.ucDatalen;
            memcpy(buf, st_doltag.pAddress, buflen);
        }
        else
        {
            ret = sdkIccReadTLV(st_doltag.heTag, buf, &buflen);   // Read a specific tag
        }

        // Pack tag
        if (((SDK_OK == ret) && (buflen > 0)) || st_doltag.bIsMandatory)
        {
            if (0x1F == (st_doltag.heTag[0] & 0x1F))
            {
                memcpy(&dol[dollen], st_doltag.heTag, 2);
                dollen += 2;
            }
            else
            {
                dol[dollen++] = st_doltag.heTag[0];
            }
        }

        // Pack value
        if ((SDK_OK == ret) && (buflen > 0))
        {
            dol[dollen++] = buflen;
            memcpy(&dol[dollen], buf, buflen);
            dollen += buflen;
        }
        else
        {
            if (st_doltag.bIsMandatory)
            {
                dol[dollen++] = 0;
            }
        }
    }

    *piLen = dollen;
    memcpy(pheDolData, dol, dollen);
}

