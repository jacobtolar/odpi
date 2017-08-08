//-----------------------------------------------------------------------------
// Copyright (c) 2016, 2017 Oracle and/or its affiliates.  All rights reserved.
// This program is free software: you can modify it and/or redistribute it
// under the terms of:
//
// (i)  the Universal Permissive License v 1.0 or at your option, any
//      later version (http://oss.oracle.com/licenses/upl); and/or
//
// (ii) the Apache License v 2.0. (http://www.apache.org/licenses/LICENSE-2.0)
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// dpi.h
//   Master include file for ODPI-C library.
//-----------------------------------------------------------------------------

#ifndef DPI_PUBLIC
#define DPI_PUBLIC

// define standard integer types for older versions of Microsoft Visual Studio
#ifdef _MSC_VER
#if _MSC_VER < 1600
#define int8_t              signed __int8
#define int16_t             signed __int16
#define int32_t             signed __int32
#define int64_t             signed __int64
#define uint8_t             unsigned __int8
#define uint16_t            unsigned __int16
#define uint32_t            unsigned __int32
#define uint64_t            unsigned __int64
#endif
#endif

#ifndef int8_t
#include <stdint.h>
#endif

// define __func__ for older versions of Microsoft Visual Studio
#ifdef _MSC_VER
#if _MSC_VER < 1900
#define __func__ __FUNCTION__
#endif
#endif

// define ODPI-C version information
#define DPI_MAJOR_VERSION   2
#define DPI_MINOR_VERSION   0
#define DPI_PATCH_LEVEL     0
#define DPI_VERSION_SUFFIX  "-rc.2"

#define DPI_STR_HELPER(x)       #x
#define DPI_STR(x)              DPI_STR_HELPER(x)
#define DPI_VERSION_STRING  \
        DPI_STR(DPI_MAJOR_VERSION) "." \
        DPI_STR(DPI_MINOR_VERSION) "." \
        DPI_STR(DPI_PATCH_LEVEL) \
        DPI_VERSION_SUFFIX
#define DPI_DEFAULT_DRIVER_NAME "ODPI-C : " DPI_VERSION_STRING

#define DPI_VERSION_TO_NUMBER(major, minor, patch) \
        ((major * 10000) + (minor * 100) + patch)
#define DPI_VERSION_NUMBER \
        DPI_VERSION_TO_NUMBER(DPI_MAJOR_VERSION, DPI_MINOR_VERSION, \
                DPI_PATCH_LEVEL)

#define DPI_ORACLE_VERSION_TO_NUMBER(versionNum, releaseNum, updateNum, \
                portReleaseNum, portUpdateNum) \
        ((versionNum * 100000000) + (releaseNum * 1000000) + \
                (updateNum * 10000) + (portReleaseNum * 100) + (portUpdateNum))

// define default array size to use
#define DPI_DEFAULT_FETCH_ARRAY_SIZE            100

// define ping interval (in seconds) used when getting connections
#define DPI_DEFAULT_PING_INTERVAL               60

// define ping timeout (in milliseconds) used when getting connections
#define DPI_DEFAULT_PING_TIMEOUT                5000

// define constants for dequeue wait (AQ)
#define DPI_DEQ_WAIT_NO_WAIT                    0
#define DPI_DEQ_WAIT_FOREVER                    ((uint32_t) -1)

// define maximum precision that can be supported by an int64_t value
#define DPI_MAX_INT64_PRECISION                 18

// define constants for success and failure of methods
#define DPI_SUCCESS                             0
#define DPI_FAILURE                             -1

// set debug level (DPI_DEBUG_LEVEL) as a bitmask of desired flags
// reporting is to stderr
// 0x0001: reports errors during free
// 0x0002: reports on reference count changes
// 0x0004: reports on public function calls
#define DPI_DEBUG_LEVEL_FREES                       0x0001
#define DPI_DEBUG_LEVEL_REFS                        0x0002
#define DPI_DEBUG_LEVEL_FNS                         0x0004


//-----------------------------------------------------------------------------
// Enumerations
//-----------------------------------------------------------------------------

// connection/pool authorization modes
typedef enum {
    DPI_MODE_AUTH_DEFAULT = 0x00000000,         // OCI_DEFAULT
    DPI_MODE_AUTH_SYSDBA = 0x00000002,          // OCI_SYSDBA
    DPI_MODE_AUTH_SYSOPER = 0x00000004,         // OCI_SYSOPER
    DPI_MODE_AUTH_PRELIM = 0x00000008,          // OCI_PRELIM_AUTH
    DPI_MODE_AUTH_SYSASM = 0x00008000           // OCI_SYSASM
} dpiAuthMode;

// connection close modes
typedef enum {
    DPI_MODE_CONN_CLOSE_DEFAULT = 0x0000,       // OCI_DEFAULT
    DPI_MODE_CONN_CLOSE_DROP = 0x0001,          // OCI_SESSRLS_DROPSESS
    DPI_MODE_CONN_CLOSE_RETAG = 0x0002          // OCI_SESSRLS_RETAG
} dpiConnCloseMode;

// connection/pool creation modes
typedef enum {
    DPI_MODE_CREATE_DEFAULT = 0x00000000,       // OCI_DEFAULT
    DPI_MODE_CREATE_THREADED = 0x00000001,      // OCI_THREADED
    DPI_MODE_CREATE_EVENTS = 0x00000004         // OCI_EVENTS
} dpiCreateMode;

// dequeue modes for advanced queuing
typedef enum {
    DPI_MODE_DEQ_BROWSE = 1,                    // OCI_DEQ_BROWSE
    DPI_MODE_DEQ_LOCKED = 2,                    // OCI_DEQ_LOCKED
    DPI_MODE_DEQ_REMOVE = 3,                    // OCI_DEQ_REMOVE
    DPI_MODE_DEQ_REMOVE_NO_DATA = 4             // OCI_DEQ_REMOVE_NODATA
} dpiDeqMode;

// dequeue navigation flags for advanced queuing
typedef enum {
    DPI_DEQ_NAV_FIRST_MSG = 1,                  // OCI_DEQ_FIRST_MSG
    DPI_DEQ_NAV_NEXT_TRANSACTION = 2,           // OCI_DEQ_NEXT_TRANSACTION
    DPI_DEQ_NAV_NEXT_MSG = 3                    // OCI_DEQ_NEXT_MSG
} dpiDeqNavigation;

// event types
typedef enum {
    DPI_EVENT_NONE = 0,                         // OCI_EVENT_NONE
    DPI_EVENT_STARTUP = 1,                      // OCI_EVENT_STARTUP
    DPI_EVENT_SHUTDOWN = 2,                     // OCI_EVENT_SHUTDOWN
    DPI_EVENT_SHUTDOWN_ANY = 3,                 // OCI_EVENT_SHUTDOWN_ANY
    DPI_EVENT_DROP_DB = 4,                      // OCI_EVENT_DROP_DB
    DPI_EVENT_DEREG = 5,                        // OCI_EVENT_DEREG
    DPI_EVENT_OBJCHANGE = 6,                    // OCI_EVENT_OBJCHANGE
    DPI_EVENT_QUERYCHANGE = 7                   // OCI_EVENT_QUERYCHANGE
} dpiEventType;

// statement execution modes
typedef enum {
    DPI_MODE_EXEC_DEFAULT = 0x00000000,             // OCI_DEFAULT
    DPI_MODE_EXEC_DESCRIBE_ONLY = 0x00000010,       // OCI_DESCRIBE_ONLY
    DPI_MODE_EXEC_COMMIT_ON_SUCCESS = 0x00000020,   // OCI_COMMIT_ON_SUCCESS
    DPI_MODE_EXEC_BATCH_ERRORS = 0x00000080,        // OCI_BATCH_ERRORS
    DPI_MODE_EXEC_PARSE_ONLY = 0x00000100,          // OCI_PARSE_ONLY
    DPI_MODE_EXEC_ARRAY_DML_ROWCOUNTS = 0x00100000  // OCI_RETURN_ROW_COUNT_ARRAY
} dpiExecMode;

// statement fetch modes
typedef enum {
    DPI_MODE_FETCH_NEXT = 0x00000002,           // OCI_FETCH_NEXT
    DPI_MODE_FETCH_FIRST = 0x00000004,          // OCI_FETCH_FIRST
    DPI_MODE_FETCH_LAST = 0x00000008,           // OCI_FETCH_LAST
    DPI_MODE_FETCH_PRIOR = 0x00000010,          // OCI_FETCH_PRIOR
    DPI_MODE_FETCH_ABSOLUTE = 0x00000020,       // OCI_FETCH_ABSOLUTE
    DPI_MODE_FETCH_RELATIVE = 0x00000040        // OCI_FETCH_RELATIVE
} dpiFetchMode;

// message delivery modes in advanced queuing
typedef enum {
    DPI_MODE_MSG_PERSISTENT = 1,                // OCI_MSG_PERSISTENT
    DPI_MODE_MSG_BUFFERED = 2,                  // OCI_MSG_BUFFERED
    DPI_MODE_MSG_PERSISTENT_OR_BUFFERED = 3     // OCI_MSG_PERSISTENT_OR_BUFFERED
} dpiMessageDeliveryMode;

// message states in advanced queuing
typedef enum {
    DPI_MSG_STATE_READY = 0,                    // OCI_MSG_READY
    DPI_MSG_STATE_WAITING = 1,                  // OCI_MSG_WAITING
    DPI_MSG_STATE_PROCESSED = 2,                // OCI_MSG_PROCESSED
    DPI_MSG_STATE_EXPIRED = 3                   // OCI_MSG_EXPIRED
} dpiMessageState;

// native C types
typedef enum {
    DPI_NATIVE_TYPE_INT64 = 3000,
    DPI_NATIVE_TYPE_UINT64,
    DPI_NATIVE_TYPE_FLOAT,
    DPI_NATIVE_TYPE_DOUBLE,
    DPI_NATIVE_TYPE_BYTES,
    DPI_NATIVE_TYPE_TIMESTAMP,
    DPI_NATIVE_TYPE_INTERVAL_DS,
    DPI_NATIVE_TYPE_INTERVAL_YM,
    DPI_NATIVE_TYPE_LOB,
    DPI_NATIVE_TYPE_OBJECT,
    DPI_NATIVE_TYPE_STMT,
    DPI_NATIVE_TYPE_BOOLEAN,
    DPI_NATIVE_TYPE_ROWID
} dpiNativeTypeNum;

// operation codes (database change and continuous query notification)
typedef enum {
    DPI_OPCODE_ALL_OPS = 0x0,                   // OCI_OPCODE_ALLOPS
    DPI_OPCODE_ALL_ROWS = 0x1,                  // OCI_OPCODE_ALLROWS
    DPI_OPCODE_INSERT = 0x2,                    // OCI_OPCODE_INSERT
    DPI_OPCODE_UPDATE = 0x4,                    // OCI_OPCODE_UPDATE
    DPI_OPCODE_DELETE = 0x8,                    // OCI_OPCODE_DELETE
    DPI_OPCODE_ALTER = 0x10,                    // OCI_OPCODE_ALTER
    DPI_OPCODE_DROP = 0x20,                     // OCI_OPCODE_DROP
    DPI_OPCODE_UNKNOWN = 0x40                   // OCI_OPCODE_UNKNOWN
} dpiOpCode;

// Oracle types
typedef enum {
    DPI_ORACLE_TYPE_NONE = 2000,
    DPI_ORACLE_TYPE_VARCHAR,
    DPI_ORACLE_TYPE_NVARCHAR,
    DPI_ORACLE_TYPE_CHAR,
    DPI_ORACLE_TYPE_NCHAR,
    DPI_ORACLE_TYPE_ROWID,
    DPI_ORACLE_TYPE_RAW,
    DPI_ORACLE_TYPE_NATIVE_FLOAT,
    DPI_ORACLE_TYPE_NATIVE_DOUBLE,
    DPI_ORACLE_TYPE_NATIVE_INT,
    DPI_ORACLE_TYPE_NUMBER,
    DPI_ORACLE_TYPE_DATE,
    DPI_ORACLE_TYPE_TIMESTAMP,
    DPI_ORACLE_TYPE_TIMESTAMP_TZ,
    DPI_ORACLE_TYPE_TIMESTAMP_LTZ,
    DPI_ORACLE_TYPE_INTERVAL_DS,
    DPI_ORACLE_TYPE_INTERVAL_YM,
    DPI_ORACLE_TYPE_CLOB,
    DPI_ORACLE_TYPE_NCLOB,
    DPI_ORACLE_TYPE_BLOB,
    DPI_ORACLE_TYPE_BFILE,
    DPI_ORACLE_TYPE_STMT,
    DPI_ORACLE_TYPE_BOOLEAN,
    DPI_ORACLE_TYPE_OBJECT,
    DPI_ORACLE_TYPE_LONG_VARCHAR,
    DPI_ORACLE_TYPE_LONG_RAW,
    DPI_ORACLE_TYPE_NATIVE_UINT,
    DPI_ORACLE_TYPE_MAX
} dpiOracleTypeNum;

// session pool close modes
typedef enum {
    DPI_MODE_POOL_CLOSE_DEFAULT = 0x0000,       // OCI_DEFAULT
    DPI_MODE_POOL_CLOSE_FORCE = 0x0001          // OCI_SPD_FORCE
} dpiPoolCloseMode;

// modes used when acquiring a connection from a session pool
typedef enum {
    DPI_MODE_POOL_GET_WAIT = 0,                 // OCI_SPOOL_ATTRVAL_WAIT
    DPI_MODE_POOL_GET_NOWAIT = 1,               // OCI_SPOOL_ATTRVAL_NOWAIT
    DPI_MODE_POOL_GET_FORCEGET = 2              // OCI_SPOOL_ATTRVAL_FORCEGET
} dpiPoolGetMode;

// purity values when acquiring a connection from a pool
typedef enum {
    DPI_PURITY_DEFAULT = 0,                     // OCI_ATTR_PURITY_DEFAULT
    DPI_PURITY_NEW = 1,                         // OCI_ATTR_PURITY_NEW
    DPI_PURITY_SELF = 2                         // OCI_ATTR_PURITY_SELF
} dpiPurity;

// database shutdown modes
typedef enum {
    DPI_MODE_SHUTDOWN_DEFAULT = 0,              // OCI_DEFAULT
    DPI_MODE_SHUTDOWN_TRANSACTIONAL = 1,        // OCI_DBSHUTDOWN_TRANSACTIONAL
    DPI_MODE_SHUTDOWN_TRANSACTIONAL_LOCAL = 2,  // OCI_DBSHUTDOWN_TRANSACTIONAL_LOCAL
    DPI_MODE_SHUTDOWN_IMMEDIATE = 3,            // OCI_DBSHUTDOWN_IMMEDIATE
    DPI_MODE_SHUTDOWN_ABORT = 4,                // OCI_DBSHUTDOWN_ABORT
    DPI_MODE_SHUTDOWN_FINAL = 5                 // OCI_DBSHUTDOWN_FINAL
} dpiShutdownMode;

// database startup modes
typedef enum {
    DPI_MODE_STARTUP_DEFAULT = 0,               // OCI_DEFAULT
    DPI_MODE_STARTUP_FORCE = 1,                 // OCI_DBSTARTUPFLAG_FORCE
    DPI_MODE_STARTUP_RESTRICT = 2               // OCI_DBSTARTUPFLAG_RESTRICT
} dpiStartupMode;

// statement types
typedef enum {
    DPI_STMT_TYPE_SELECT = 1,                   // OCI_STMT_SELECT
    DPI_STMT_TYPE_UPDATE = 2,                   // OCI_STMT_UPDATE
    DPI_STMT_TYPE_DELETE = 3,                   // OCI_STMT_DELETE
    DPI_STMT_TYPE_INSERT = 4,                   // OCI_STMT_INSERT
    DPI_STMT_TYPE_CREATE = 5,                   // OCI_STMT_CREATE
    DPI_STMT_TYPE_DROP = 6,                     // OCI_STMT_DROP
    DPI_STMT_TYPE_ALTER = 7,                    // OCI_STMT_ALTER
    DPI_STMT_TYPE_BEGIN = 8,                    // OCI_STMT_BEGIN
    DPI_STMT_TYPE_DECLARE = 9,                  // OCI_STMT_DECLARE
    DPI_STMT_TYPE_CALL = 10                     // OCI_STMT_CALL
} dpiStatementType;

// subscription namespaces
typedef enum {
    DPI_SUBSCR_NAMESPACE_DBCHANGE = 2           // OCI_SUBSCR_NAMESPACE_DBCHANGE
} dpiSubscrNamespace;

// subscription protocols
typedef enum {
    DPI_SUBSCR_PROTO_CALLBACK = 0,              // OCI_SUBSCR_PROTO_OCI
    DPI_SUBSCR_PROTO_MAIL = 1,                  // OCI_SUBSCR_PROTO_MAIL
    DPI_SUBSCR_PROTO_PLSQL = 2,                 // OCI_SUBSCR_PROTO_SERVER
    DPI_SUBSCR_PROTO_HTTP = 3                   // OCI_SUBSCR_PROTO_HTTP
} dpiSubscrProtocol;

// subscription quality of service
typedef enum {
    DPI_SUBSCR_QOS_RELIABLE = 0x01,
    DPI_SUBSCR_QOS_DEREG_NFY = 0x02,
    DPI_SUBSCR_QOS_ROWIDS = 0x04,
    DPI_SUBSCR_QOS_QUERY = 0x08,
    DPI_SUBSCR_QOS_BEST_EFFORT = 0x10
} dpiSubscrQOS;

// visibility of messages in advanced queuing
typedef enum {
    DPI_VISIBILITY_IMMEDIATE = 1,               // OCI_DEQ_IMMEDIATE
    DPI_VISIBILITY_ON_COMMIT = 2                // OCI_DEQ_ON_COMMIT
} dpiVisibility;


//-----------------------------------------------------------------------------
// Handle Types
//-----------------------------------------------------------------------------
typedef struct dpiConn dpiConn;
typedef struct dpiPool dpiPool;
typedef struct dpiStmt dpiStmt;
typedef struct dpiVar dpiVar;
typedef struct dpiLob dpiLob;
typedef struct dpiObject dpiObject;
typedef struct dpiObjectAttr dpiObjectAttr;
typedef struct dpiObjectType dpiObjectType;
typedef struct dpiRowid dpiRowid;
typedef struct dpiSubscr dpiSubscr;
typedef struct dpiDeqOptions dpiDeqOptions;
typedef struct dpiEnqOptions dpiEnqOptions;
typedef struct dpiMsgProps dpiMsgProps;


//-----------------------------------------------------------------------------
// Complex Native Data Types (used for transferring data to/from ODPI-C)
//-----------------------------------------------------------------------------

// structure used for transferring byte strings to/from ODPI-C
typedef struct {
    char *ptr;
    uint32_t length;
    const char *encoding;
} dpiBytes;

// structure used for transferring day/seconds intervals to/from ODPI-C
typedef struct {
    int32_t days;
    int32_t hours;
    int32_t minutes;
    int32_t seconds;
    int32_t fseconds;
} dpiIntervalDS;

// structure used for transferring years/months intervals to/from ODPI-C
typedef struct {
    int32_t years;
    int32_t months;
} dpiIntervalYM;

// structure used for transferring dates to/from ODPI-C
typedef struct {
    int16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint32_t fsecond;
    int8_t tzHourOffset;
    int8_t tzMinuteOffset;
} dpiTimestamp;


//-----------------------------------------------------------------------------
// Other Types
//-----------------------------------------------------------------------------

// forward declarations
typedef struct dpiAppContext dpiAppContext;
typedef struct dpiCommonCreateParams dpiCommonCreateParams;
typedef struct dpiConnCreateParams dpiConnCreateParams;
typedef struct dpiContext dpiContext;
typedef struct dpiData dpiData;
typedef struct dpiEncodingInfo dpiEncodingInfo;
typedef struct dpiErrorInfo dpiErrorInfo;
typedef struct dpiObjectAttrInfo dpiObjectAttrInfo;
typedef struct dpiObjectTypeInfo dpiObjectTypeInfo;
typedef struct dpiPoolCreateParams dpiPoolCreateParams;
typedef struct dpiQueryInfo dpiQueryInfo;
typedef struct dpiStmtInfo dpiStmtInfo;
typedef struct dpiSubscrCreateParams dpiSubscrCreateParams;
typedef struct dpiSubscrMessage dpiSubscrMessage;
typedef struct dpiSubscrMessageQuery dpiSubscrMessageQuery;
typedef struct dpiSubscrMessageRow dpiSubscrMessageRow;
typedef struct dpiSubscrMessageTable dpiSubscrMessageTable;
typedef struct dpiVersionInfo dpiVersionInfo;

// structure used for application context
struct dpiAppContext {
    const char *namespaceName;
    uint32_t namespaceNameLength;
    const char *name;
    uint32_t nameLength;
    const char *value;
    uint32_t valueLength;
};

// structure used for common parameters used for creating standalone
// connections and session pools
struct dpiCommonCreateParams {
    dpiCreateMode createMode;
    const char *encoding;
    const char *nencoding;
    const char *edition;
    uint32_t editionLength;
    const char *driverName;
    uint32_t driverNameLength;
};

// structure used for creating connections
struct dpiConnCreateParams {
    dpiAuthMode authMode;
    const char *connectionClass;
    uint32_t connectionClassLength;
    dpiPurity purity;
    const char *newPassword;
    uint32_t newPasswordLength;
    dpiAppContext *appContext;
    uint32_t numAppContext;
    int externalAuth;
    void *externalHandle;
    dpiPool *pool;
    const char *tag;
    uint32_t tagLength;
    int matchAnyTag;
    const char *outTag;
    uint32_t outTagLength;
    int outTagFound;
    uint32_t lobPrefetchSize;
};

// structure used for transferring data to/from ODPI-C
struct dpiData {
    int isNull;
    union {
        int asBoolean;
        int64_t asInt64;
        uint64_t asUint64;
        float asFloat;
        double asDouble;
        dpiBytes asBytes;
        dpiTimestamp asTimestamp;
        dpiIntervalDS asIntervalDS;
        dpiIntervalYM asIntervalYM;
        dpiLob *asLOB;
        dpiObject *asObject;
        dpiStmt *asStmt;
        dpiRowid *asRowid;
    } value;
};

// structure used for transferring encoding information from ODPI-C
struct dpiEncodingInfo {
    const char *encoding;
    int32_t maxBytesPerCharacter;
    const char *nencoding;
    int32_t nmaxBytesPerCharacter;
};

// structure used for transferring error information from ODPI-C
struct dpiErrorInfo {
    int32_t code;
    uint16_t offset;
    const char *message;
    uint32_t messageLength;
    const char *encoding;
    const char *fnName;
    const char *action;
    const char *sqlState;
    int isRecoverable;
};

// structure used for transferring object attribute information from ODPI-C
struct dpiObjectAttrInfo {
    const char *name;
    uint32_t nameLength;
    dpiOracleTypeNum oracleTypeNum;
    dpiNativeTypeNum defaultNativeTypeNum;
    dpiObjectType *objectType;
};

// structure used for transferring object type information from ODPI-C
struct dpiObjectTypeInfo {
    const char *schema;
    uint32_t schemaLength;
    const char *name;
    uint32_t nameLength;
    int isCollection;
    dpiOracleTypeNum elementOracleTypeNum;
    dpiNativeTypeNum elementDefaultNativeTypeNum;
    dpiObjectType *elementObjectType;
    uint16_t numAttributes;
};

// structure used for creating pools
struct dpiPoolCreateParams {
    uint32_t minSessions;
    uint32_t maxSessions;
    uint32_t sessionIncrement;
    int pingInterval;
    int pingTimeout;
    int homogeneous;
    int externalAuth;
    dpiPoolGetMode getMode;
    const char *outPoolName;
    uint32_t outPoolNameLength;
};

// structure used for transferring query metadata from ODPI-C
struct dpiQueryInfo {
    const char *name;
    uint32_t nameLength;
    dpiOracleTypeNum oracleTypeNum;
    dpiNativeTypeNum defaultNativeTypeNum;
    uint32_t dbSizeInBytes;
    uint32_t clientSizeInBytes;
    uint32_t sizeInChars;
    int16_t precision;
    int8_t scale;
    int nullOk;
    dpiObjectType *objectType;
};

// structure used for transferring statement information from ODPI-C
struct dpiStmtInfo {
    int isQuery;
    int isPLSQL;
    int isDDL;
    int isDML;
    dpiStatementType statementType;
    int isReturning;
};

// callback for subscriptions
typedef void (*dpiSubscrCallback)(void* context, dpiSubscrMessage *message);

// structure used for creating subscriptions
struct dpiSubscrCreateParams {
    dpiSubscrNamespace subscrNamespace;
    dpiSubscrProtocol protocol;
    dpiSubscrQOS qos;
    dpiOpCode operations;
    uint32_t portNumber;
    uint32_t timeout;
    const char *name;
    uint32_t nameLength;
    dpiSubscrCallback callback;
    void *callbackContext;
    const char *recipientName;
    uint32_t recipientNameLength;
};

// structure used for transferring messages in subscription callbacks
struct dpiSubscrMessage {
    dpiEventType eventType;
    const char *dbName;
    uint32_t dbNameLength;
    dpiSubscrMessageTable *tables;
    uint32_t numTables;
    dpiSubscrMessageQuery *queries;
    uint32_t numQueries;
    dpiErrorInfo *errorInfo;
};

// structure used for transferring query information in messages in
// subscription callbacks (continuous query notification)
struct dpiSubscrMessageQuery {
    uint64_t id;
    dpiOpCode operation;
    dpiSubscrMessageTable *tables;
    uint32_t numTables;
};

// structure used for transferring row information in messages in
// subscription callbacks
struct dpiSubscrMessageRow {
    dpiOpCode operation;
    const char *rowid;
    uint32_t rowidLength;
};

// structure used for transferring table information in messages in
// subscription callbacks
struct dpiSubscrMessageTable {
    dpiOpCode operation;
    const char *name;
    uint32_t nameLength;
    dpiSubscrMessageRow *rows;
    uint32_t numRows;
};

// structure used for transferring version information
struct dpiVersionInfo {
    int versionNum;
    int releaseNum;
    int updateNum;
    int portReleaseNum;
    int portUpdateNum;
    uint32_t fullVersionNum;
};


//-----------------------------------------------------------------------------
// Context Methods (dpiContext)
//-----------------------------------------------------------------------------

// create a context handle and validate the version information
int dpiContext_create(unsigned int majorVersion, unsigned int minorVersion,
        dpiContext **context, dpiErrorInfo *errorInfo);

// destroy context handle
int dpiContext_destroy(dpiContext *context);

// return the OCI client version in use
int dpiContext_getClientVersion(const dpiContext *context,
        dpiVersionInfo *versionInfo);

// get error information
void dpiContext_getError(const dpiContext *context, dpiErrorInfo *errorInfo);

// initialize context parameters to default values
int dpiContext_initCommonCreateParams(const dpiContext *context,
        dpiCommonCreateParams *params);

// initialize connection create parameters to default values
int dpiContext_initConnCreateParams(const dpiContext *context,
        dpiConnCreateParams *params);

// initialize pool create parameters to default values
int dpiContext_initPoolCreateParams(const dpiContext *context,
        dpiPoolCreateParams *params);

// initialize subscription create parameters to default values
int dpiContext_initSubscrCreateParams(const dpiContext *context,
        dpiSubscrCreateParams *params);


//-----------------------------------------------------------------------------
// Connection Methods (dpiConn)
//-----------------------------------------------------------------------------

// add a reference to a connection
int dpiConn_addRef(dpiConn *conn);

// begin a distributed transaction
int dpiConn_beginDistribTrans(dpiConn *conn, long formatId,
        const char *transactionId, uint32_t transactionIdLength,
        const char *branchId, uint32_t branchIdLength);

// break execution of the statement running on the connection
int dpiConn_breakExecution(dpiConn *conn);

// change the password for the specified user
int dpiConn_changePassword(dpiConn *conn, const char *userName,
        uint32_t userNameLength, const char *oldPassword,
        uint32_t oldPasswordLength, const char *newPassword,
        uint32_t newPasswordLength);

// close the connection now, not when the reference count reaches zero
int dpiConn_close(dpiConn *conn, dpiConnCloseMode mode, const char *tag,
        uint32_t tagLength);

// commits the current active transaction
int dpiConn_commit(dpiConn *conn);

// create a connection and return a reference to it
int dpiConn_create(const dpiContext *context, const char *userName,
        uint32_t userNameLength, const char *password, uint32_t passwordLength,
        const char *connectString, uint32_t connectStringLength,
        const dpiCommonCreateParams *commonParams,
        dpiConnCreateParams *createParams, dpiConn **conn);

// dequeue a message from a queue
int dpiConn_deqObject(dpiConn *conn, const char *queueName,
        uint32_t queueNameLength, dpiDeqOptions *options, dpiMsgProps *props,
        dpiObject *payload, const char **msgId, uint32_t *msgIdLength);

// enqueue a message to a queue
int dpiConn_enqObject(dpiConn *conn, const char *queueName,
        uint32_t queueNameLength, dpiEnqOptions *options, dpiMsgProps *props,
        dpiObject *payload, const char **msgId, uint32_t *msgIdLength);

// get current schema associated with the connection
int dpiConn_getCurrentSchema(dpiConn *conn, const char **value,
        uint32_t *valueLength);

// get edition associated with the connection
int dpiConn_getEdition(dpiConn *conn, const char **value,
        uint32_t *valueLength);

// return the encoding information used by the connection
int dpiConn_getEncodingInfo(dpiConn *conn, dpiEncodingInfo *info);

// get external name associated with the connection
int dpiConn_getExternalName(dpiConn *conn, const char **value,
        uint32_t *valueLength);

// get the OCI service context handle associated with the connection
int dpiConn_getHandle(dpiConn *conn, void **handle);

// get internal name associated with the connection
int dpiConn_getInternalName(dpiConn *conn, const char **value,
        uint32_t *valueLength);

// get logical transaction id associated with the connection
int dpiConn_getLTXID(dpiConn *conn, const char **value, uint32_t *valueLength);

// create a new object type and return it for subsequent object creation
int dpiConn_getObjectType(dpiConn *conn, const char *name, uint32_t nameLength,
        dpiObjectType **objType);

// return information about the server version in use
int dpiConn_getServerVersion(dpiConn *conn, const char **releaseString,
        uint32_t *releaseStringLength, dpiVersionInfo *versionInfo);

// return the statement cache size
int dpiConn_getStmtCacheSize(dpiConn *conn, uint32_t *cacheSize);

// create a new dequeue options object and return it
int dpiConn_newDeqOptions(dpiConn *conn, dpiDeqOptions **options);

// create a new enqueue options object and return it
int dpiConn_newEnqOptions(dpiConn *conn, dpiEnqOptions **options);

// create a new message properties object and return it
int dpiConn_newMsgProps(dpiConn *conn, dpiMsgProps **props);

// create a new subscription for events
int dpiConn_newSubscription(dpiConn *conn, dpiSubscrCreateParams *params,
        dpiSubscr **subscr, uint32_t *subscrId);

// create a new temporary LOB
int dpiConn_newTempLob(dpiConn *conn, dpiOracleTypeNum lobType, dpiLob **lob);

// create a new variable and return it for subsequent binding/defining
int dpiConn_newVar(dpiConn *conn, dpiOracleTypeNum oracleTypeNum,
        dpiNativeTypeNum nativeTypeNum, uint32_t maxArraySize, uint32_t size,
        int sizeIsBytes, int isArray, dpiObjectType *objType, dpiVar **var,
        dpiData **data);

// ping the connection to see if it is still alive
int dpiConn_ping(dpiConn *conn);

// prepare a distributed transaction for commit
int dpiConn_prepareDistribTrans(dpiConn *conn, int *commitNeeded);

// prepare a statement and return it for subsequent execution/fetching
int dpiConn_prepareStmt(dpiConn *conn, int scrollable, const char *sql,
        uint32_t sqlLength, const char *tag, uint32_t tagLength,
        dpiStmt **stmt);

// release a reference to the connection
int dpiConn_release(dpiConn *conn);

// rolls back the current active transaction
int dpiConn_rollback(dpiConn *conn);

// set action associated with the connection
int dpiConn_setAction(dpiConn *conn, const char *value, uint32_t valueLength);

// set client identifier associated with the connection
int dpiConn_setClientIdentifier(dpiConn *conn, const char *value,
        uint32_t valueLength);

// set client info associated with the connection
int dpiConn_setClientInfo(dpiConn *conn, const char *value,
        uint32_t valueLength);

// set current schema associated with the connection
int dpiConn_setCurrentSchema(dpiConn *conn, const char *value,
        uint32_t valueLength);

// set database operation associated with the connection
int dpiConn_setDbOp(dpiConn *conn, const char *value, uint32_t valueLength);

// set external name associated with the connection
int dpiConn_setExternalName(dpiConn *conn, const char *value,
        uint32_t valueLength);

// set internal name associated with the connection
int dpiConn_setInternalName(dpiConn *conn, const char *value,
        uint32_t valueLength);

// set module associated with the connection
int dpiConn_setModule(dpiConn *conn, const char *value, uint32_t valueLength);

// set the statement cache size
int dpiConn_setStmtCacheSize(dpiConn *conn, uint32_t cacheSize);

// shutdown the database
int dpiConn_shutdownDatabase(dpiConn *conn, dpiShutdownMode mode);

// startup the database
int dpiConn_startupDatabase(dpiConn *conn, dpiStartupMode mode);


//-----------------------------------------------------------------------------
// Data Methods (dpiData)
//-----------------------------------------------------------------------------

// return the boolean portion of the data
int dpiData_getBool(dpiData *data);

// return the bytes portion of the data
dpiBytes *dpiData_getBytes(dpiData *data);

// return the double portion of the data
double dpiData_getDouble(dpiData *data);

// return the float portion of the data
float dpiData_getFloat(dpiData *data);

// return the integer portion of the data
int64_t dpiData_getInt64(dpiData *data);

// return the interval (days/seconds) portion of the data
dpiIntervalDS *dpiData_getIntervalDS(dpiData *data);

// return the interval (years/months) portion of the data
dpiIntervalYM *dpiData_getIntervalYM(dpiData *data);

// return the LOB portion of the data
dpiLob *dpiData_getLOB(dpiData *data);

// return the object portion of the data
dpiObject *dpiData_getObject(dpiData *data);

// return the statement portion of the data
dpiStmt *dpiData_getStmt(dpiData *data);

// return the timestamp portion of the data
dpiTimestamp *dpiData_getTimestamp(dpiData *data);

// return the unsigned integer portion of the data
uint64_t dpiData_getUint64(dpiData *data);

// set the boolean portion of the data
void dpiData_setBool(dpiData *data, int value);

// set the bytes portion of the data
void dpiData_setBytes(dpiData *data, char *ptr, uint32_t length);

// set the double portion of the data
void dpiData_setDouble(dpiData *data, double value);

// set the float portion of the data
void dpiData_setFloat(dpiData *data, float value);

// set the integer portion of the data
void dpiData_setInt64(dpiData *data, int64_t value);

// set the interval (days/seconds) portion of the data
void dpiData_setIntervalDS(dpiData *data, int32_t days, int32_t hours,
        int32_t minutes, int32_t seconds, int32_t fsceconds);

// set the interval (years/months) portion of the data
void dpiData_setIntervalYM(dpiData *data, int32_t years, int32_t months);

// set the LOB portion of the data
void dpiData_setLOB(dpiData *data, dpiLob *lob);

// set the object portion of the data
void dpiData_setObject(dpiData *data, dpiObject *obj);

// set the statement portion of the data
void dpiData_setStmt(dpiData *data, dpiStmt *stmt);

// set the timestamp portion of the data
void dpiData_setTimestamp(dpiData *data, int16_t year, uint8_t month,
        uint8_t day, uint8_t hour, uint8_t minute, uint8_t second,
        uint32_t fsecond, int8_t tzHourOffset, int8_t tzMinuteOffset);

// set the unsigned integer portion of the data
void dpiData_setUint64(dpiData *data, uint64_t value);


//-----------------------------------------------------------------------------
// Dequeue Option Methods (dpiDeqOptions)
//-----------------------------------------------------------------------------

// add a reference to dequeue options
int dpiDeqOptions_addRef(dpiDeqOptions *options);

// return condition associated with dequeue options
int dpiDeqOptions_getCondition(dpiDeqOptions *options, const char **value,
        uint32_t *valueLength);

// return consumer name associated with dequeue options
int dpiDeqOptions_getConsumerName(dpiDeqOptions *options, const char **value,
        uint32_t *valueLength);

// return correlation associated with dequeue options
int dpiDeqOptions_getCorrelation(dpiDeqOptions *options, const char **value,
        uint32_t *valueLength);

// return mode associated with dequeue options
int dpiDeqOptions_getMode(dpiDeqOptions *options, dpiDeqMode *value);

// return message id associated with dequeue options
int dpiDeqOptions_getMsgId(dpiDeqOptions *options, const char **value,
        uint32_t *valueLength);

// return navigation associated with dequeue options
int dpiDeqOptions_getNavigation(dpiDeqOptions *options,
        dpiDeqNavigation *value);

// return transformation associated with dequeue options
int dpiDeqOptions_getTransformation(dpiDeqOptions *options, const char **value,
        uint32_t *valueLength);

// return visibility associated with dequeue options
int dpiDeqOptions_getVisibility(dpiDeqOptions *options, dpiVisibility *value);

// return wait time associated with dequeue options
int dpiDeqOptions_getWait(dpiDeqOptions *options, uint32_t *value);

// release a reference from dequeue options
int dpiDeqOptions_release(dpiDeqOptions *options);

// set condition associated with dequeue options
int dpiDeqOptions_setCondition(dpiDeqOptions *options, const char *value,
        uint32_t valueLength);

// set consumer name associated with dequeue options
int dpiDeqOptions_setConsumerName(dpiDeqOptions *options, const char *value,
        uint32_t valueLength);

// set correlation associated with dequeue options
int dpiDeqOptions_setCorrelation(dpiDeqOptions *options, const char *value,
        uint32_t valueLength);

// set delivery mode associated with dequeue options
int dpiDeqOptions_setDeliveryMode(dpiDeqOptions *options,
        dpiMessageDeliveryMode value);

// set mode associated with dequeue options
int dpiDeqOptions_setMode(dpiDeqOptions *options, dpiDeqMode value);

// set message id associated with dequeue options
int dpiDeqOptions_setMsgId(dpiDeqOptions *options, const char *value,
        uint32_t valueLength);

// set navigation associated with dequeue options
int dpiDeqOptions_setNavigation(dpiDeqOptions *options,
        dpiDeqNavigation value);

// set transformation associated with dequeue options
int dpiDeqOptions_setTransformation(dpiDeqOptions *options, const char *value,
        uint32_t valueLength);

// set visibility associated with dequeue options
int dpiDeqOptions_setVisibility(dpiDeqOptions *options, dpiVisibility value);

// set wait time associated with dequeue options
int dpiDeqOptions_setWait(dpiDeqOptions *options, uint32_t value);


//-----------------------------------------------------------------------------
// Enqueue Option Methods (dpiEnqOptions)
//-----------------------------------------------------------------------------

// add a reference to enqueue options
int dpiEnqOptions_addRef(dpiEnqOptions *options);

// return transformation associated with enqueue options
int dpiEnqOptions_getTransformation(dpiEnqOptions *options, const char **value,
        uint32_t *valueLength);

// return visibility associated with enqueue options
int dpiEnqOptions_getVisibility(dpiEnqOptions *options, dpiVisibility *value);

// release a reference from enqueue options
int dpiEnqOptions_release(dpiEnqOptions *options);

// set delivery mode associated with enqueue options
int dpiEnqOptions_setDeliveryMode(dpiEnqOptions *options,
        dpiMessageDeliveryMode value);

// set transformation associated with enqueue options
int dpiEnqOptions_setTransformation(dpiEnqOptions *options, const char *value,
        uint32_t valueLength);

// set visibility associated with enqueue options
int dpiEnqOptions_setVisibility(dpiEnqOptions *options, dpiVisibility value);


//-----------------------------------------------------------------------------
// LOB Methods (dpiLob)
//-----------------------------------------------------------------------------

// add a reference to the LOB
int dpiLob_addRef(dpiLob *lob);

// close the LOB
int dpiLob_close(dpiLob *lob);

// close the LOB's resources
int dpiLob_closeResource(dpiLob *lob);

// create a copy of the LOB
int dpiLob_copy(dpiLob *lob, dpiLob **copiedLob);

// flush buffers for the LOB
int dpiLob_flushBuffer(dpiLob *lob);

int dpiLob_getBufferSize(dpiLob *lob, uint64_t sizeInChars,
        uint64_t *sizeInBytes);

// return the chunk size for the LOB
int dpiLob_getChunkSize(dpiLob *lob, uint32_t *size);

// return the directory alias name and file name of a BFILE LOB
int dpiLob_getDirectoryAndFileName(dpiLob *lob, const char **directoryAlias,
        uint32_t *directoryAliasLength, const char **fileName,
        uint32_t *fileNameLength);

// return if the file associated with a BFILE LOB exists
int dpiLob_getFileExists(dpiLob *lob, int *exists);

// return if the LOB's resources are currently open
int dpiLob_getIsResourceOpen(dpiLob *lob, int *isOpen);

// return the current size of the LOB
int dpiLob_getSize(dpiLob *lob, uint64_t *size);

// open the LOB's resources (used to improve performance of multiple
// read/writes operations)
int dpiLob_openResource(dpiLob *lob);

// read bytes from the LOB at the specified offset
int dpiLob_readBytes(dpiLob *lob, uint64_t offset, uint64_t amount,
        char *value, uint64_t *valueLength);

// release a reference to the LOB
int dpiLob_release(dpiLob *lob);

// set the directory name and file name of the BFILE LOB
int dpiLob_setDirectoryAndFileName(dpiLob *lob, const char *directoryAlias,
        uint32_t directoryAliasLength, const char *fileName,
        uint32_t fileNameLength);

// sets the contents of a LOB from a byte string
int dpiLob_setFromBytes(dpiLob *lob, const char *value, uint64_t valueLength);

// trim the LOB to the specified size
int dpiLob_trim(dpiLob *lob, uint64_t newSize);

// write bytes to the LOB at the specified offset
int dpiLob_writeBytes(dpiLob *lob, uint64_t offset, const char *value,
        uint64_t valueLength);


//-----------------------------------------------------------------------------
// Message Properties Methods (dpiMsgProps)
//-----------------------------------------------------------------------------

// add a reference to message properties
int dpiMsgProps_addRef(dpiMsgProps *props);

// return the number of attempts made to deliver the message
int dpiMsgProps_getNumAttempts(dpiMsgProps *props, int32_t *value);

// return correlation associated with the message
int dpiMsgProps_getCorrelation(dpiMsgProps *props, const char **value,
        uint32_t *valueLength);

// return the number of seconds the message was delayed
int dpiMsgProps_getDelay(dpiMsgProps *props, int32_t *value);

// return the mode used for delivering the message
int dpiMsgProps_getDeliveryMode(dpiMsgProps *props,
        dpiMessageDeliveryMode *value);

// return the time the message was enqueued
int dpiMsgProps_getEnqTime(dpiMsgProps *props, dpiTimestamp *value);

// return the name of the exception queue associated with the message
int dpiMsgProps_getExceptionQ(dpiMsgProps *props, const char **value,
        uint32_t *valueLength);

// return the number of seconds until the message expires
int dpiMsgProps_getExpiration(dpiMsgProps *props, int32_t *value);

// return the original message id for the message
int dpiMsgProps_getOriginalMsgId(dpiMsgProps *props, const char **value,
        uint32_t *valueLength);

// return the priority of the message
int dpiMsgProps_getPriority(dpiMsgProps *props, int32_t *value);

// return the state of the message
int dpiMsgProps_getState(dpiMsgProps *props, dpiMessageState *value);

// release a reference from message properties
int dpiMsgProps_release(dpiMsgProps *props);

// set correlation associated with the message
int dpiMsgProps_setCorrelation(dpiMsgProps *props, const char *value,
        uint32_t valueLength);

// set the number of seconds to delay the message
int dpiMsgProps_setDelay(dpiMsgProps *props, int32_t value);

// set the name of the exception queue associated with the message
int dpiMsgProps_setExceptionQ(dpiMsgProps *props, const char *value,
        uint32_t valueLength);

// set the number of seconds until the message expires
int dpiMsgProps_setExpiration(dpiMsgProps *props, int32_t value);

// set the original message id for the message
int dpiMsgProps_setOriginalMsgId(dpiMsgProps *props, const char *value,
        uint32_t valueLength);

// set the priority of the message
int dpiMsgProps_setPriority(dpiMsgProps *props, int32_t value);


//-----------------------------------------------------------------------------
// Object Methods (dpiObject)
//-----------------------------------------------------------------------------

// add a reference to the object
int dpiObject_addRef(dpiObject *obj);

// append an element to the collection
int dpiObject_appendElement(dpiObject *obj, dpiNativeTypeNum nativeTypeNum,
        dpiData *value);

// copy the object and return the copied object
int dpiObject_copy(dpiObject *obj, dpiObject **copiedObj);

// delete an element from the collection
int dpiObject_deleteElementByIndex(dpiObject *obj, int32_t index);

// get the value of the specified attribute
int dpiObject_getAttributeValue(dpiObject *obj, dpiObjectAttr *attr,
        dpiNativeTypeNum nativeTypeNum, dpiData *value);

// return whether an element exists in a collection at the specified index
int dpiObject_getElementExistsByIndex(dpiObject *obj, int32_t index,
        int *exists);

// get the value of the element in a collection at the specified index
int dpiObject_getElementValueByIndex(dpiObject *obj, int32_t index,
        dpiNativeTypeNum nativeTypeNum, dpiData *value);

// return the first index used in a collection
int dpiObject_getFirstIndex(dpiObject *obj, int32_t *index, int *exists);

// return the last index used in a collection
int dpiObject_getLastIndex(dpiObject *obj, int32_t *index, int *exists);

// return the next index used in a collection given an index
int dpiObject_getNextIndex(dpiObject *obj, int32_t index, int32_t *nextIndex,
        int *exists);

// return the previous index used in a collection given an index
int dpiObject_getPrevIndex(dpiObject *obj, int32_t index, int32_t *prevIndex,
        int *exists);

// return the number of elements in a collection
int dpiObject_getSize(dpiObject *obj, int32_t *size);

// release a reference to the object
int dpiObject_release(dpiObject *obj);

// set the value of the specified attribute
int dpiObject_setAttributeValue(dpiObject *obj, dpiObjectAttr *attr,
        dpiNativeTypeNum nativeTypeNum, dpiData *value);

// set the value of the element in a collection at the specified index
int dpiObject_setElementValueByIndex(dpiObject *obj, int32_t index,
        dpiNativeTypeNum nativeTypeNum, dpiData *value);

// trim a number of elements from the end of a collection
int dpiObject_trim(dpiObject *obj, uint32_t numToTrim);


//-----------------------------------------------------------------------------
// Object Type Attribute Methods (dpiObjectAttr)
//-----------------------------------------------------------------------------

// add a reference to the attribute
int dpiObjectAttr_addRef(dpiObjectAttr *attr);

// return the name of the attribute
int dpiObjectAttr_getInfo(dpiObjectAttr *attr, dpiObjectAttrInfo *info);

// release a reference to the attribute
int dpiObjectAttr_release(dpiObjectAttr *attr);


//-----------------------------------------------------------------------------
// Object Type Methods (dpiObjectType)
//-----------------------------------------------------------------------------

// add a reference to the object type
int dpiObjectType_addRef(dpiObjectType *objType);

// create an object of the specified type and return it
int dpiObjectType_createObject(dpiObjectType *objType, dpiObject **obj);

// return the attributes available on the object type
int dpiObjectType_getAttributes(dpiObjectType *objType, uint16_t numAttributes,
        dpiObjectAttr **attributes);

// return information about the object type
int dpiObjectType_getInfo(dpiObjectType *objType, dpiObjectTypeInfo *info);

// release a reference to the object type
int dpiObjectType_release(dpiObjectType *objType);


//-----------------------------------------------------------------------------
// Session Pools Methods (dpiPool)
//-----------------------------------------------------------------------------

// acquire a connection from the pool and return it
int dpiPool_acquireConnection(dpiPool *pool, const char *userName,
        uint32_t userNameLength, const char *password, uint32_t passwordLength,
        dpiConnCreateParams *createParams, dpiConn **conn);

// add a reference to a pool
int dpiPool_addRef(dpiPool *pool);

// destroy the pool now, not when its reference count reaches zero
int dpiPool_close(dpiPool *pool, dpiPoolCloseMode closeMode);

// create a session pool and return it
int dpiPool_create(const dpiContext *context, const char *userName,
        uint32_t userNameLength, const char *password, uint32_t passwordLength,
        const char *connectString, uint32_t connectStringLength,
        const dpiCommonCreateParams *commonParams,
        dpiPoolCreateParams *createParams, dpiPool **pool);

// get the pool's busy count
int dpiPool_getBusyCount(dpiPool *pool, uint32_t *value);

// return the encoding information used by the session pool
int dpiPool_getEncodingInfo(dpiPool *pool, dpiEncodingInfo *info);

// get the pool's "get" mode
int dpiPool_getGetMode(dpiPool *pool, dpiPoolGetMode *value);

// get the pool's maximum lifetime session
int dpiPool_getMaxLifetimeSession(dpiPool *pool, uint32_t *value);

// get the pool's open count
int dpiPool_getOpenCount(dpiPool *pool, uint32_t *value);

// return the statement cache size
int dpiPool_getStmtCacheSize(dpiPool *pool, uint32_t *cacheSize);

// get the pool's timeout value
int dpiPool_getTimeout(dpiPool *pool, uint32_t *value);

// release a reference to the pool
int dpiPool_release(dpiPool *pool);

// set the pool's "get" mode
int dpiPool_setGetMode(dpiPool *pool, dpiPoolGetMode value);

// set the pool's maximum lifetime session
int dpiPool_setMaxLifetimeSession(dpiPool *pool, uint32_t value);

// set the statement cache size
int dpiPool_setStmtCacheSize(dpiPool *pool, uint32_t cacheSize);

// set the pool's timeout value
int dpiPool_setTimeout(dpiPool *pool, uint32_t value);


//-----------------------------------------------------------------------------
// Statement Methods (dpiStmt)
//-----------------------------------------------------------------------------

// add a reference to a statement
int dpiStmt_addRef(dpiStmt *stmt);

// bind a variable to the statement using the given name
int dpiStmt_bindByName(dpiStmt *stmt, const char *name, uint32_t nameLength,
        dpiVar *var);

// bind a variable to the statement at the given position
// positions are determined by the order in which names are introduced
int dpiStmt_bindByPos(dpiStmt *stmt, uint32_t pos, dpiVar *var);

// bind a value to the statement using the given name
// this creates the variable by looking at the type and then binds it
int dpiStmt_bindValueByName(dpiStmt *stmt, const char *name,
        uint32_t nameLength, dpiNativeTypeNum nativeTypeNum, dpiData *data);

// bind a value to the statement at the given position
// this creates the variable by looking at the type and then binds it
int dpiStmt_bindValueByPos(dpiStmt *stmt, uint32_t pos,
        dpiNativeTypeNum nativeTypeNum, dpiData *data);

// close the statement now, not when its reference count reaches zero
int dpiStmt_close(dpiStmt *stmt, const char *tag, uint32_t tagLength);

// define a variable to accept the data for the specified column (1 based)
int dpiStmt_define(dpiStmt *stmt, uint32_t pos, dpiVar *var);

// define type of data to use for the specified column (1 based)
int dpiStmt_defineValue(dpiStmt *stmt, uint32_t pos,
        dpiOracleTypeNum oracleTypeNum, dpiNativeTypeNum nativeTypeNum,
        uint32_t size, int sizeIsBytes, dpiObjectType *objType);

// execute the statement and return the number of query columns
// zero implies the statement is not a query
int dpiStmt_execute(dpiStmt *stmt, dpiExecMode mode,
        uint32_t *numQueryColumns);

// execute the statement multiple times (queries not supported)
int dpiStmt_executeMany(dpiStmt *stmt, dpiExecMode mode, uint32_t numIters);

// fetch a single row and return the index into the defined variables
// this will internally perform any execute and array fetch as needed
int dpiStmt_fetch(dpiStmt *stmt, int *found, uint32_t *bufferRowIndex);

// return the number of rows that are available in the defined variables
// up to the maximum specified; this will internally perform execute/array
// fetch only if no rows are available in the defined variables and there are
// more rows available to fetch
int dpiStmt_fetchRows(dpiStmt *stmt, uint32_t maxRows,
        uint32_t *bufferRowIndex, uint32_t *numRowsFetched, int *moreRows);

// get the number of batch errors that took place in the previous execution
int dpiStmt_getBatchErrorCount(dpiStmt *stmt, uint32_t *count);

// get the batch errors that took place in the previous execution
int dpiStmt_getBatchErrors(dpiStmt *stmt, uint32_t numErrors,
        dpiErrorInfo *errors);

// get the number of bind variables that are in the prepared statement
int dpiStmt_getBindCount(dpiStmt *stmt, uint32_t *count);

// get the names of the bind variables that are in the prepared statement
int dpiStmt_getBindNames(dpiStmt *stmt, uint32_t *numBindNames,
        const char **bindNames, uint32_t *bindNameLengths);

// get the number of rows to (internally) fetch at one time
int dpiStmt_getFetchArraySize(dpiStmt *stmt, uint32_t *arraySize);

// get next implicit result from previous execution; NULL if no more exist
int dpiStmt_getImplicitResult(dpiStmt *stmt, dpiStmt **implicitResult);

// return information about the statement
int dpiStmt_getInfo(dpiStmt *stmt, dpiStmtInfo *info);

// get the number of query columns (zero implies the statement is not a query)
int dpiStmt_getNumQueryColumns(dpiStmt *stmt, uint32_t *numQueryColumns);

// return metadata about the column at the specified position (1 based)
int dpiStmt_getQueryInfo(dpiStmt *stmt, uint32_t pos, dpiQueryInfo *info);

// get the value for the specified column of the current row fetched
int dpiStmt_getQueryValue(dpiStmt *stmt, uint32_t pos,
        dpiNativeTypeNum *nativeTypeNum, dpiData **data);

// get the row count for the statement
// for queries, this is the number of rows that have been fetched so far
// for non-queries, this is the number of rows affected by the last execution
int dpiStmt_getRowCount(dpiStmt *stmt, uint64_t *count);

// get the number of rows affected for each DML operation just executed
// using the mode DPI_MODE_EXEC_ARRAY_DML_ROWCOUNTS
int dpiStmt_getRowCounts(dpiStmt *stmt, uint32_t *numRowCounts,
        uint64_t **rowCounts);

// get subscription query id for continuous query notification
int dpiStmt_getSubscrQueryId(dpiStmt *stmt, uint64_t *queryId);

// release a reference to the statement
int dpiStmt_release(dpiStmt *stmt);

// scroll the statement to the desired row
// this is only valid for scrollable statements
int dpiStmt_scroll(dpiStmt *stmt, dpiFetchMode mode, int32_t offset,
        int32_t rowCountOffset);

// set the number of rows to (internally) fetch at one time
int dpiStmt_setFetchArraySize(dpiStmt *stmt, uint32_t arraySize);


//-----------------------------------------------------------------------------
// Rowid Methods (dpiRowid)
//-----------------------------------------------------------------------------

// add a reference to the rowid
int dpiRowid_addRef(dpiRowid *rowid);

// get string representation from rowid
int dpiRowid_getStringValue(dpiRowid *rowid, const char **value,
        uint32_t *valueLength);

// release a reference to the rowid
int dpiRowid_release(dpiRowid *subscr);


//-----------------------------------------------------------------------------
// Subscription Methods (dpiSubscr)
//-----------------------------------------------------------------------------

// add a reference to the subscription
int dpiSubscr_addRef(dpiSubscr *subscr);

// close the subscription
int dpiSubscr_close(dpiSubscr *subscr);

// prepare statement for registration with subscription
int dpiSubscr_prepareStmt(dpiSubscr *subscr, const char *sql,
        uint32_t sqlLength, dpiStmt **stmt);

// release a reference to the subscription
int dpiSubscr_release(dpiSubscr *subscr);


//-----------------------------------------------------------------------------
// Variable Methods (dpiVar)
//-----------------------------------------------------------------------------

// add a reference to the variable
int dpiVar_addRef(dpiVar *var);

// copy the data from one variable to another variable
int dpiVar_copyData(dpiVar *var, uint32_t pos, dpiVar *sourceVar,
        uint32_t sourcePos);

// return pointer to array of dpiData structures for transferring data
// this is needed for DML returning where the number of elements is modified
int dpiVar_getData(dpiVar *var, uint32_t *numElements, dpiData **data);

// return the number of elements in a PL/SQL index-by table
int dpiVar_getNumElementsInArray(dpiVar *var, uint32_t *numElements);

// return the size in bytes of the buffer used for fetching/binding
int dpiVar_getSizeInBytes(dpiVar *var, uint32_t *sizeInBytes);

// release a reference to the variable
int dpiVar_release(dpiVar *var);

// set the value of the variable from a byte string
int dpiVar_setFromBytes(dpiVar *var, uint32_t pos, const char *value,
        uint32_t valueLength);

// set the value of the variable from a LOB
int dpiVar_setFromLob(dpiVar *var, uint32_t pos, dpiLob *lob);

// set the value of the variable from an object
int dpiVar_setFromObject(dpiVar *var, uint32_t pos, dpiObject *obj);

// set the value of the variable from a rowid
int dpiVar_setFromRowid(dpiVar *var, uint32_t pos, dpiRowid *rowid);

// set the value of the variable from a statement
int dpiVar_setFromStmt(dpiVar *var, uint32_t pos, dpiStmt *stmt);

// set the number of elements in a PL/SQL index-by table
int dpiVar_setNumElementsInArray(dpiVar *var, uint32_t numElements);

#endif

