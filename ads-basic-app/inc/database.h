#ifndef _DATABASE_H_
#define _DATABASE_H_

/*-----------------------------------------------------------------------------
*                           MACROS/CONST
-----------------------------------------------------------------------------*/
#define FILENAME_DATABASE       "DataBase.db"

#define DB_MAX_FIELDS 256

#define STR(a) a, #a

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define DB_MAXFILTER         10
#define DB_MAXFILTER_VALUE   10

/*-----------------------------------------------------------------------------
*                           DATA STRUCTURE
-----------------------------------------------------------------------------*/

/* Enumeration constant values to specify exit codes returned by this module */
typedef enum
{
    DB_EXIT_SUCCESS = 0,         /*!< Enum value Database operation is successful*/
    DB_EXIT_ERROR = -1,          /*!< Enum value SQL error or missing database */
    DB_EXIT_INTERNAL = -2,       /*!< Enum value An internal logic error */
    DB_EXIT_PERM = -3,           /*!< Enum value Access permission denied */
    DB_EXIT_ABORT = -4,          /*!< Enum value Callback routine requested an abort */
    DB_EXIT_BUSY = -5,           /*!< Enum value The database file is locked */
    DB_EXIT_LOCKED = -6,         /*!< Enum value A table in the database is locked */
    //DB_EXIT_MEMERROR = -7,     /*!< Enum value Memory error happened during allocation failed */
    DB_EXIT_READONLY = -8,       /*!< Enum value Attempt to write a readonly database */
    DB_EXIT_INTERRUPT = -9,      /*!< Enum value Operation terminated by interrupt function */
    DB_EXIT_IOERR = -10,         /*!< Enum value Some kind of disk I/O error occurred */
    DB_EXIT_CORRUPT = -11,       /*!< Enum value The database disk image is malformed */
    DB_EXIT_NOTFOUND = -12,      /*!< Enum value (Internal Only) Table or record not found */
    DB_EXIT_FULL = -13,          /*!< Enum value Insertion failed because database is full */
    DB_EXIT_CANTOPEN = -14,      /*!< Enum value Unable to open the database file */
    DB_EXIT_PROTOCOL = -15,      /*!< Enum value Database lock protocol error */
    DB_EXIT_EMPTY = -16,         /*!< Enum value (Internal Only) Database table is empty */
    DB_EXIT_SCHEMA = -17,        /*!< Enum value The database schema changed */
    DB_EXIT_TOOBIG = -18,        /*!< Enum value Too much data for one row of a table */
    DB_EXIT_CONSTRAINT = -19,    /*!< Enum value Abort due to contraint violation */
    DB_EXIT_MISMATCH = -20,      /*!< Enum value Data type mismatch */
    DB_EXIT_MISUSE = -21,        /*!< Enum value Library used incorrectly */
    DB_EXIT_NOLFS = -22,         /*!< Enum value Uses OS features not supported on host */
    DB_EXIT_AUTH = -23,          /*!< Enum value Authorization denied */
    DB_EXIT_ROW = -100,          /*!< Enum value Row is ready */
    DB_EXIT_DONE = -101,         /*!< Enum value All rows are executed */
    DB_EXIT_HANDLEERR = -1001,   /*!< Enum value DB or Query handle not found */
    DB_EXIT_MEMORYERR = -1002,   /*!< Enum value Dynamic memory allocation problem  */
    DB_EXIT_NORIGHT = -99,       /*!< Enum value User doesn't have right to perform the operation*/
    DB_EXIT_OTHER = -98,         /*!< Enum value any other reason to exit */
} E_DB_EXIT;

typedef enum
{
    DB_DATATYPE_ASC,
    DB_DATATYPE_U8,
    DB_DATATYPE_U16,
    DB_DATATYPE_U32,
    DB_DATATYPE_BIN,
    DB_PRIMARY_KEY,
}E_DB_DATATYPE;

/* Table field info */
typedef struct
{
    s32 iId;
    u8 *pasFieldName;            //Name of the field
    s32 iType;                   //Type of the field: TEXT, INT, VARCHAR(), etc
    s32 iSize;                   //Size of the field
    bool bIsEncrypt;
    void *pAddress;
    s32 iLen;
}ST_DB_FIELD;

typedef enum
{
    FILTER_SIGNEL,
    FILTER_SIGNEL_BESIDE,
    FILTER_MULTI,
    FILTER_BETWEEN,
    FILTER_LESS_THAN,
    FILTER_GREATER_THAN,
}E_FILTER_MODE;


/* database info */
typedef struct
{
    u8 *pasTabName;                            /*! Name of the table*/
    bool bIsBackup;
    ST_DB_FIELD  stFields[DB_MAX_FIELDS];      /*! List of table fields, last field should be {0, 0, 0}, which means the end of list*/
}ST_DATABASE;


typedef struct
{
    u8 *pasName;
    E_FILTER_MODE eMode;
    void *pasValue[DB_MAXFILTER_VALUE];
    s32 iNum;
    s32 iLen; 
    s32 iType;                                 //Type of the field: TEXT, INT, VARCHAR(), etc
    bool bIsDesc;
}ST_DB_FILTER;

/*-----------------------------------------------------------------------------
*                           FUNCTIONS
-----------------------------------------------------------------------------*/
/******************************* functions declaration *********************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** Description :  Open database file(file name is "database.so", file path is 
                  "/mtd0/xxxxxd" "xxxxx" is your appid.) 
                  If the file is exist, just open it. 
                  If the file is not exist, automatic create it, then open it.
                  This funtion must be called once at application start.
                  
** Parameter   :  ST_DATABASE *pstTable : struct "ST_DATABASE", defined in this head file.
                  Use this struct, you can define table name, and all column name,
                  data type, size and data address.
                  
** Return      :  DB_EXIT_ERROR : Open database fail
                  DB_EXIT_SUCCESS : Open database success
                  
** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbOpen(void);

/*******************************************************************************
** Description :  Close database file(file name is "database.so", file path is 
                  "/mtd0/xxxxxd" "xxxxx" is your appid.) 
                  Usually used on swich application
                  
** Parameter   :  void

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
void sdkDbClose(void);

/*******************************************************************************
** Description :  Create a table if the table is not exist
                  Table format is defined in struct "ST_DATABASE"
                  
** Parameter   :  ST_DATABASE *pstTable : struct "ST_DATABASE", defined in this head file.
                  Use this struct, you can define table name, and all column name,
                  data type, size and data address.
                  
** Return      :  DB_EXIT_ERROR : Open database fail
                  DB_EXIT_SUCCESS : Open database success
                  
** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbCreateTable(const ST_DATABASE *pstTable);

/*******************************************************************************
** Description :  Dump a table from database
                  
** Parameter   :  ST_DATABASE *pstTable : struct "ST_DATABASE", defined in this head file.
                  Use this struct, you can define table name, and all column name,
                  data type, size and data address.
                  
** Return      :  DB_EXIT_ERROR : Open database fail
                  DB_EXIT_SUCCESS : Open database success
                  
** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbDumpTable(const u8 *pasTable);

/*******************************************************************************
** Description :  Insert one record at the end of the table
                  
** Parameter   :  ST_DATABASE *pstTable : struct "ST_DATABASE", defined in this head file.
                  Use this struct, you can define table name, and all column name,
                  data type, size and data address.

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbInsertRecord(const ST_DATABASE *pstTable);

/*******************************************************************************
** Description :  Update one record if Id is same as parameter
                  
** Parameter   :  ST_DATABASE *pstTable : struct "ST_DATABASE", defined in this head file.
                  Use this struct, you can define table name, and all column name,
                  data type, size and data address.

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbUpdateRecord(const ST_DATABASE *pstTable);

/*******************************************************************************
** Description :  Search the first record meet the one condition
                  
** Parameter   :  const s8 *pasTable : table name
                  const s8 *pasName : column name
                  void *pasValue : search value
                  s32 iLen : value len
                  const s8 *pasType : value type
                  void *pDataOut : output buf, must be struct "ST_DATABASE" type

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbSearchRecord(const u8 *pasTable, ST_DB_FILTER *pstFilter, void *pDataOut);

/*******************************************************************************
** Description :  Search the first record meet the conditions
                  
** Parameter   :  const s8 *pasTable : table name
                  ST_DB_SEARCH *pstCondition : search conditions
                  s32 iNum : conditions count
                  void *pDataOut : output buf, must be struct "ST_DATABASE" type

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbMultiSearchRecord(const u8 *pasTable, ST_DB_FILTER *pstFilter, s32 iNum, s32 iOffset, void *pDataOut);

E_DB_EXIT sdkDbGetSum(const u8 *pasTable, u8 *pasName, ST_DB_FILTER *pstFilter, s32 iNum, u8 *pDataOut);

/*******************************************************************************
** Description :  Read the record by primary key "ID"
                  
** Parameter   :  const s8 *pasTable : table name
                  s32 iIndex : record id number
                  void *pDataOut : output buf, must be struct "ST_DATABASE" type

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbGetRecordByIndex(const u8 *pasTable, s32 iIndex, void *pDataOut);

/*******************************************************************************
** Description :  delete one record meet the conditions
                  
** Parameter   :  const s8 *pasTable : table name
                  const s8 *pasName : column name
                  void *pasValue : search value

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbDeleteOneRecord(const u8 *pasTable, ST_DB_FILTER *pstFilter);

/*******************************************************************************
** Description :  delete all record in table

** Parameter   :  const s8 *pasTable : table name

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
E_DB_EXIT sdkDbDeleteAllRecords(const u8 *pasTable);

/*******************************************************************************
** Description :  get record total number
                  
** Parameter   :  const s8 *pasTable : table name

** Return      :  void

** Author      :  wenmin 20160806

** Remark      :
*******************************************************************************/
s32 sdkDbGetRecordTotalNum(const u8 *pasTable, ST_DB_FILTER *pstFilter, s32 iNum);

#ifdef __cplusplus
}
#endif


#endif
