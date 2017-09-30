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
const static SDK_ICC_EmvSysIni_STRUCT TabVisaLiveAIDs[] =
{
    {
        5,                                    //AidLen      
        "\xA0\x00\x00\x00\x03",               //AID      
        0,                                    //Asi      
        "\x00\x8c",                           //AppVerNum      
        {0xD8, 0x40, 0x00, 0xA8, 0x00},       //TAC-default      
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online      
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline      
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit      
        {0x00, 0x00, 0x00, 0x00},             //threshold      
        0,                                    //MaxTargetPercent      
        0,                                    //TargetPercent      
        3,                                    //TermDDOLlen      
        {0x9F, 0x37, 0x04},                   //TermDDOL      
        0,                                    //TermPinCap      
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit      
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit      
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt      
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt      
        0,                                    //bShowRandNum      
        0,                                    //bLocalName      
        0,                                    //AppLocalNameLen      
        {0},                                  //AppLocalName      
        0                                     //bForceOnline      
    },
};


const static SDK_ICC_EmvSysIni_STRUCT TabVisaTestAIDs[] =
{
//change VISA test AID FloorLimit {0} to {0x00,0x00,0x01,0x00}
//change VISA default and online TAC first byte 0xD8 to 0xDC    

    {
        7,          						  //AidLen
        "\xA0\x00\x00\x00\x03\x10\x10",       //AID  
        0,                                    //Asi
        "\x00\x8c",                           //AppVerNum
        {0xDC, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xDC, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        0,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        7,          					      //AidLen
        "\xA0\x00\x00\x00\x03\x20\x10",       //AID  
        0,                                    //Asi
        "\x00\x8c",                           //AppVerNum
        {0xDC, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xDC, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        0,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};

const static SDK_ICC_EmvSysIni_STRUCT TabMasterLiveAIDs[] =
{
    {
        7,                                    //AidLen
        "\xA0\x00\x00\x00\x04\x10\x10",       //AID(add for POSB card)  
        0,                                    //Asi
        "\x00\x02",                           //AppVerNum
        {0xFC, 0x50, 0xAC, 0xA0, 0x00},       //TAC-default  
        {0xF8, 0x50, 0xAC, 0xF8, 0x00},       //TAC-online  
        {0x04, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        0,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        6,                                    //AidLen
        "\xA0\x00\x00\x00\x04\x10",           //AID
        0,                                    //Asi
        "\x00\x02",                           //AppVerNum
        {0xFC, 0x50, 0xAC, 0xA0, 0x00},       //TAC-default  
        {0xF8, 0x50, 0xAC, 0xF8, 0x00},       //TAC-online  
        {0x04, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        0,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        6,                                    //AidLen
        "\xA0\x00\x00\x00\x04\x30",           //AID
        0,                                    //Asi
        "\x00\x02",                           //AppVerNum
        {0xFC, 0x50, 0xAC, 0xA0, 0x00},       //TAC-default  
        {0xF8, 0x50, 0xAC, 0xF8, 0x00},       //TAC-online  
        {0x04, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        0,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};

const static SDK_ICC_EmvSysIni_STRUCT TabMasterTestAIDs[] =
{
    {
        7,                                    //AidLen
        "\xA0\x00\x00\x00\x04\x10\x10",       //AID  
        0,                                    //Asi
        "\x00\x02",                           //AppVerNum
        {0xFC, 0x50, 0xB8, 0xA0, 0x00},       //TAC-default  
        {0xFC, 0x50, 0xB8, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        7,                                    //AidLen
        "\xA0\x00\x00\x00\x04\x30\x60",       //AID  
        0,                                    //Asi
        "\x00\x02",                           //AppVerNum
        {0xFC, 0x50, 0xB8, 0xA0, 0x00},       //TAC-default  
        {0xFC, 0x50, 0xB8, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        7,                                    //AidLen
        "\xA0\x00\x00\x00\x04\x60\x00",       //AID  
        0,                                    //Asi
        "\x00\x02",                           //AppVerNum
        {0xFC, 0x50, 0xB8, 0xA0, 0x00},       //TAC-default  
        {0xFC, 0x50, 0xB8, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        7,                                    //AidLen
        "\xA0\x00\x00\x00\x10\x10\x30",       //AID  
        0,                                    //Asi
        "\x00\x02",                           //AppVerNum
        {0xFC, 0x50, 0xB8, 0xA0, 0x00},       //TAC-default  
        {0xFC, 0x50, 0xB8, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};


const static SDK_ICC_EmvSysIni_STRUCT TabJcbLiveAIDs[] =
{
    {
        7,                                    //AidLen
        "\xA0\x00\x00\x00\x65\x10\x10",       //AID  
        0,                                    //Asi
        "\x00\x21",                           //AppVerNum
        {0xfc, 0x60, 0x24, 0x28, 0x00},       //TAC-default  
        {0xfc, 0x60, 0xac, 0xf8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};


const static SDK_ICC_EmvSysIni_STRUCT TabJcbTestAIDs[] =
{
    {
        7,                                    //AidLen
        "\xA0\x00\x00\x00\x65\x10\x10",       //AID  
        0,                                    //Asi
        "\x00\x21",                           //AppVerNum
        {0xfc, 0x60, 0x24, 0xa8, 0x00},       //TAC-default  
        {0xfc, 0x60, 0xac, 0xf8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};

const static SDK_ICC_EmvSysIni_STRUCT TabAmexLiveAIDs[] =
{
    {
        6,                                    //AidLen
        "\xA0\x00\x00\x00\x25\x01",           //AID
        0,                                    //Asi
        "\x00\x01",                           //AppVerNum
        {0xfc, 0x60, 0x24, 0x28, 0x00},       //TAC-default  
        {0xfc, 0x60, 0xac, 0xf8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};


const static SDK_ICC_EmvSysIni_STRUCT TabAmexTestAIDs[] =
{
    {
        6,                                    //AidLen
        "\xA0\x00\x00\x00\x25\x01",           //AID
        0,                                    //Asi
        "\x00\x01",                           //AppVerNum
        {0xFC, 0x50, 0xB8, 0xA0, 0x00},       //TAC-default  
        {0xFC, 0x50, 0xB8, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x00, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x00, 0x40, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x02, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};

const static SDK_ICC_EmvSysIni_STRUCT TabCupLiveAIDs[] =
{
    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x06",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x01",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x02",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x03",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x00, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};


const static SDK_ICC_EmvSysIni_STRUCT TabCupTestAIDs[] =
{
    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x01",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x02",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x03",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },

    {
        8,                                    //AidLen
        "\xA0\x00\x00\x03\x33\x01\x01\x06",   //AID      
        0,                                    //Asi
        "\x00\x20",                           //AppVerNum
        {0x08, 0x40, 0x00, 0xA8, 0x00},       //TAC-default  
        {0xD8, 0x40, 0x04, 0xF8, 0x00},       //TAC-online  
        {0x00, 0x10, 0x00, 0x00, 0x00},       //TAC-decline  
        {0x00, 0x00, 0x01, 0x00},             //FloorLimit
        {0x00, 0x00, 0x00, 0x00},             //threshold
        0,                                    //MaxTargetPercent
        0,                                    //TargetPercent
        3,                                    //TermDDOLlen
        {0x9F, 0x37, 0x04},                   //TermDDOL
        1,                                    //TermPinCap
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //vlptranslimit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //termcvm_limit          
        {0x00, 0x00, 0x00, 0x10, 0x00, 0x00}, //clessofflineamt          
        {0x00, 0x00, 0x00, 0x01, 0x00, 0x00}, //clessofflinelimitamt          
        0,                                    //bShowRandNum
        0,                                    //bLocalName
        0,                                    //AppLocalNameLen
        {0},                                  //AppLocalName
        0                                     //bForceOnline
    },
};

static SDK_ICC_EmvSysIni_STRUCT _gstAid;

// AIDs
static ST_DATABASE TabAid = 
{
    TABNAME_AID,
    FALSE,
    {
        {AID_ID, "ID",                DB_PRIMARY_KEY,  0, FALSE, NULL,                        0},
        {STR(AID_AIDLEN),             DB_DATATYPE_U8,  0, FALSE, &_gstAid.AidLen,              0},
        {STR(AID_AID),                DB_DATATYPE_BIN, 0, FALSE, _gstAid.Aid,                  sizeof(_gstAid.Aid)}, 
        {STR(AID_ASI),                DB_DATATYPE_U8,  0, FALSE, &_gstAid.Asi,                 0},     
        {STR(AID_APP_VERSION),        DB_DATATYPE_BIN, 0, FALSE, _gstAid.AppVerNum,            sizeof(_gstAid.AppVerNum)},
        {STR(AID_TAC_DEFAULT),        DB_DATATYPE_BIN, 0, FALSE, _gstAid.TacDefault,           sizeof(_gstAid.TacDefault)},
        {STR(AID_TAC_ONLINE),         DB_DATATYPE_BIN, 0, FALSE, _gstAid.TacOnline,            sizeof(_gstAid.TacOnline)},
        {STR(AID_TAC_DECLINE),        DB_DATATYPE_BIN, 0, FALSE, _gstAid.TacDecline,           sizeof(_gstAid.TacDecline)},
        {STR(AID_EMV_FLOOR_LIMIT),    DB_DATATYPE_BIN, 0, FALSE, _gstAid.FloorLimit,           sizeof(_gstAid.FloorLimit)},
        {STR(AID_THRESHOLD),          DB_DATATYPE_BIN, 0, FALSE, _gstAid.Threshold,            sizeof(_gstAid.Threshold)},
        {STR(AID_MAX_TARGET_PERCENT), DB_DATATYPE_U8,  0, FALSE, &_gstAid.MaxTargetPercent,    0},
        {STR(AID_TARGET_PERCENT),     DB_DATATYPE_U8,  0, FALSE, &_gstAid.TargetPercent,       0},
        {STR(AID_TERM_DDOL_LEN),      DB_DATATYPE_U8,  0, FALSE, &_gstAid.TermDDOLLen,         0},
        {STR(AID_TERM_DDOL),          DB_DATATYPE_BIN, 0, FALSE, _gstAid.TermDDOL,             sizeof(_gstAid.TermDDOL)},
        {STR(AID_TERM_PIN_CAP),       DB_DATATYPE_U8,  0, FALSE, &_gstAid.TermPinCap,          0},
        {STR(AID_VLP_TRANS_LIMIT),    DB_DATATYPE_BIN, 0, FALSE, _gstAid.vlptranslimit,        sizeof(_gstAid.vlptranslimit)},     
        {STR(AID_CTLS_CVM_LIMIT),     DB_DATATYPE_BIN, 0, FALSE, _gstAid.termcvm_limit,        sizeof(_gstAid.termcvm_limit)},    
        {STR(AID_CTLS_TRANS_LIMIT),   DB_DATATYPE_BIN, 0, FALSE, _gstAid.clessofflineamt,      sizeof(_gstAid.clessofflineamt)},    
        {STR(AID_CTLS_FLOOR_LIMIT),   DB_DATATYPE_BIN, 0, FALSE, _gstAid.clessofflinelimitamt, sizeof(_gstAid.clessofflinelimitamt)}, 
        {STR(AID_IS_SHOW_RAND_NUM),   DB_DATATYPE_U8,  0, FALSE, &_gstAid.bShowRandNum,        0},
        {STR(AID_IS_LOCAL_NAME),      DB_DATATYPE_U8,  0, FALSE, &_gstAid.bLocalName,          0},    
        {STR(AID_IS_FORCE_ONLINE),    DB_DATATYPE_U8,  0, FALSE, &_gstAid.bForceOnline,        0},
    }
};

/*****************************************************************************
** Description :  set specify default AIDs to EMV-kernel
** Parameters  :  input:
                  (1)E_CARD_TYPE eCardType: which card type AID you need to set
                  (2)bool bIsLiveAid: whether it is live AID
                  
** Return      :  (1)SDK_PARA_ERR: input parameter error
                  (2)SDK_ERR: set AIDs fail
                  (3)SDK_OK: set AIDs success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
s32 EmvSetAid(E_CARD_TYPE eCardType, bool bIsLiveAid)
{
    s32 i = 0, num = 0;
    s32 ret = SDK_OK;
    const SDK_ICC_EmvSysIni_STRUCT *pst_aid =  NULL;
    u8 card_type[64] = {0};
    u8 tmp[128] = {0};

    if (eCardType < VISA || eCardType > CUP)
    {
        Assert(0);
        return SDK_PARA_ERR;
    }

    switch (eCardType)
    {
         case VISA:
            strcpy(card_type, STR_CARD_VISA);
            num = (bIsLiveAid) ? (sizeof(TabVisaLiveAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT))
                               : (sizeof(TabVisaTestAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT));
            pst_aid = (bIsLiveAid) ? TabVisaLiveAIDs : TabVisaTestAIDs;
            break;

         case MASTER:
            strcpy(card_type, STR_CARD_MC);
            num = (bIsLiveAid) ? (sizeof(TabMasterLiveAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT))
                               : (sizeof(TabMasterTestAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT));
            pst_aid = (bIsLiveAid) ? TabMasterLiveAIDs : TabMasterTestAIDs;
            break;

         case JCB:
            strcpy(card_type, STR_CARD_JCB);
            num = (bIsLiveAid) ? (sizeof(TabJcbLiveAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT))
                               : (sizeof(TabJcbTestAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT));
            pst_aid = (bIsLiveAid) ? TabJcbLiveAIDs : TabJcbTestAIDs;
            break;

         case AMEX:
            strcpy(card_type, STR_CARD_AMEX);
            num = (bIsLiveAid) ? (sizeof(TabAmexLiveAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT))
                               : (sizeof(TabAmexTestAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT));
            pst_aid = (bIsLiveAid) ? TabAmexLiveAIDs : TabAmexTestAIDs;
            break;

         case CUP:
            strcpy(card_type, STR_CARD_CUP);
            num = (bIsLiveAid) ? (sizeof(TabCupLiveAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT))
                               : (sizeof(TabCupTestAIDs)/sizeof(SDK_ICC_EmvSysIni_STRUCT));
            pst_aid = (bIsLiveAid) ? TabCupLiveAIDs : TabCupTestAIDs;
            break;

         default:
             break;
    }

    if(SDK_OK != sdkIccAddAnyAIDList(pst_aid, num))
    {
        for (i = 0; i < num; i++)
        {
            ret = sdkIccAddAnyAIDList(&pst_aid[i], 1);
            Trace("emv", "sdkIccAddAnyAIDList: ret = %d\r\n", ret);

            if (SDK_OK != ret)
            {
                sprintf(tmp, "%s:", card_type);
                sdkBcdToAsc(&tmp[strlen(tmp)], pst_aid[i].Aid, pst_aid[i].AidLen);            
                sdkDispClearScreen();
                sdkDispFillRowRam(SDK_DISP_LINE2, 0, STR_INFO_ADD_AID_FAIL, SDK_DISP_DEFAULT);
                sdkDispFillRowRam(SDK_DISP_LINE3, 0, tmp, SDK_DISP_DEFAULT);
                sdkDispBrushScreen();
                sdkKbWaitKey(SDK_KEY_MASK_ENTER | SDK_KEY_MASK_ESC, 0);
                return SDK_ERR;
            }
        }
    }
    else
    {
        sdkDbCreateTable(&TabAid);
        for (i = 0; i < num; i++)
        {
            memcpy(&_gstAid, &pst_aid[i], sizeof(SDK_ICC_EmvSysIni_STRUCT));
            sdkDbInsertRecord(&TabAid);
        }
    }

    return SDK_OK;
}

/*****************************************************************************
** Description :  config all default AIDs to EMV-kernel
** Parameters  :  input
                  (1)bool bIsLiveAid: whether it is live AID
                  
** Return      :  None
** Author      :  wenmin   2016-10-18 
** Remarks     :  
*****************************************************************************/
void EmvSetAllDefaultAid(bool bIsLiveAid)
{
    sdkIccDelAllAIDLists();
    EmvSetAid(VISA, bIsLiveAid);
    EmvSetAid(MASTER, bIsLiveAid);
    EmvSetAid(JCB, bIsLiveAid);
    EmvSetAid(AMEX, bIsLiveAid);
    EmvSetAid(CUP, bIsLiveAid);
    sdkIccSaveAIDFile();
}

/*****************************************************************************
** Description :  config AIDs to EMV-kernel and database
** Parameters  :  input
                  (1)bool bIsLiveAid: whether it is live AID
                  
** Return      :  (1)SDK_ERR: set AIDs fail
                  (2)SDK_OK: set AIDs success
                  
** Author      :  wenmin   2016-10-18 
** Remarks     :  If there is not AIDs in the database, it will set default
                  AIDs to the EMV-kernel, and set default AIDs to the database.
                  If there have AIDs in the database, it will use the AIDs in
                  database to set to the EMV-kernel.
*****************************************************************************/
s32 EmvInitAid(bool bIsLiveAid)
{
    s32 num = 0;
    s32 i = 0;
    SDK_ICC_EmvSysIni_STRUCT *pst_aid =  NULL;
    
    if(DB_EXIT_SUCCESS != sdkDbOpen())
    {
        EmvSetAllDefaultAid(bIsLiveAid);
        return SDK_ERR;
    }

    num = sdkDbGetRecordTotalNum(TabAid.pasTabName, NULL, 0);
    if(num < 0)
    {
        EmvSetAllDefaultAid(bIsLiveAid);
        return SDK_OK;
    }

    pst_aid = (SDK_ICC_EmvSysIni_STRUCT *)sdkGetMem(sizeof(SDK_ICC_EmvSysIni_STRUCT) * num);
    if(NULL == pst_aid)
    {
        return SDK_ERR;
    }

    for(i = 0; i < num; i++)
    {
        memset(&_gstAid, 0, sizeof(SDK_ICC_EmvSysIni_STRUCT));
        if(DB_EXIT_SUCCESS != sdkDbGetRecordByIndex(TabAid.pasTabName, i, (void *)&TabAid))
        {
            sdkFreeMem(pst_aid);
            return SDK_ERR;
        }
        memcpy(&pst_aid[i], &_gstAid, sizeof(SDK_ICC_EmvSysIni_STRUCT));
    }
    sdkIccAddAnyAIDList(pst_aid, num);
    sdkIccSaveAIDFile();
    sdkFreeMem(pst_aid);
    
    return SDK_OK;
}

