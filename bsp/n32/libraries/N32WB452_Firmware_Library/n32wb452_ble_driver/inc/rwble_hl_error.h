/**
 ****************************************************************************************
 *
 * @file rwble_hl_error.h
 *
 * @brief File that contains all error codes.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef RWBLE_HL_ERROR_H_
#define RWBLE_HL_ERROR_H_


/**
 ****************************************************************************************
 * @addtogroup ROOT
 * @brief High layer error codes
 *
 * This module contains the primitives that allow an application accessing and running the
 * BLE protocol stack
 *
 * @{
 ****************************************************************************************
 */



/// Error code from HCI TO HL Range - from 0x90 to 0xD0
#define RW_ERR_HCI_TO_HL(err)     (((err) != 0) ? ((err) + 0x90) : (0))


/// Error code from HL TO HCI Range - from 0x90 to 0xD0
#define RW_ERR_HL_TO_HCI(err)     (((err) > 0x90) ? ((err) - 0x90) : (0))

/**
 * List all HL error codes
 */
enum hl_err
{
    /// No error
    GAP_ERR_NO_ERROR                                                               = 0x00,

    // ----------------------------------------------------------------------------------
    // -------------------------  ATT Specific Error ------------------------------------
    // ----------------------------------------------------------------------------------
    /// No error
    ATT_ERR_NO_ERROR                                                               = 0x00,
    /// 0x01: Handle is invalid
    ATT_ERR_INVALID_HANDLE                                                         = 0x01,
    /// 0x02: Read permission disabled
    ATT_ERR_READ_NOT_PERMITTED                                                     = 0x02,
    /// 0x03: Write permission disabled
    ATT_ERR_WRITE_NOT_PERMITTED                                                    = 0x03,
    /// 0x04: Incorrect PDU
    ATT_ERR_INVALID_PDU                                                            = 0x04,
    /// 0x05: Authentication privilege not enough
    ATT_ERR_INSUFF_AUTHEN                                                          = 0x05,
    /// 0x06: Request not supported or not understood
    ATT_ERR_REQUEST_NOT_SUPPORTED                                                  = 0x06,
    /// 0x07: Incorrect offset value
    ATT_ERR_INVALID_OFFSET                                                         = 0x07,
    /// 0x08: Authorization privilege not enough
    ATT_ERR_INSUFF_AUTHOR                                                          = 0x08,
    /// 0x09: Capacity queue for reliable write reached
    ATT_ERR_PREPARE_QUEUE_FULL                                                     = 0x09,
    /// 0x0A: Attribute requested not existing
    ATT_ERR_ATTRIBUTE_NOT_FOUND                                                    = 0x0A,
    /// 0x0B: Attribute requested not long
    ATT_ERR_ATTRIBUTE_NOT_LONG                                                     = 0x0B,
    /// 0x0C: Encryption size not sufficient
    ATT_ERR_INSUFF_ENC_KEY_SIZE                                                    = 0x0C,
    /// 0x0D: Invalid length of the attribute value
    ATT_ERR_INVALID_ATTRIBUTE_VAL_LEN                                              = 0x0D,
    /// 0x0E: Operation not fit to condition
    ATT_ERR_UNLIKELY_ERR                                                           = 0x0E,
    /// 0x0F: Attribute requires encryption before operation
    ATT_ERR_INSUFF_ENC                                                             = 0x0F,
    /// 0x10: Attribute grouping not supported
    ATT_ERR_UNSUPP_GRP_TYPE                                                        = 0x10,
    /// 0x11: Resources not sufficient to complete the request
    ATT_ERR_INSUFF_RESOURCE                                                        = 0x11,
    /// 0x80: Application error (also used in PRF Errors)
    ATT_ERR_APP_ERROR                                                              = 0x80,

    // ----------------------------------------------------------------------------------
    // -------------------------- L2C Specific Error ------------------------------------
    // ----------------------------------------------------------------------------------
    /// Message cannot be sent because connection lost. (disconnected)
    L2C_ERR_CONNECTION_LOST                                                        = 0x30,
    /// Invalid PDU length exceed MTU
    L2C_ERR_INVALID_MTU_EXCEED                                                     = 0x31,
    /// Invalid PDU length exceed MPS
    L2C_ERR_INVALID_MPS_EXCEED                                                     = 0x32,
    /// Invalid Channel ID
    L2C_ERR_INVALID_CID                                                            = 0x33,
    /// Invalid PDU
    L2C_ERR_INVALID_PDU                                                            = 0x34,
    /// Connection refused - no resources available
    L2C_ERR_NO_RES_AVAIL                                                           = 0x35,
    /// Connection refused - insufficient authentication
    L2C_ERR_INSUFF_AUTHEN                                                          = 0x36,
    /// Connection refused - insufficient authorization
    L2C_ERR_INSUFF_AUTHOR                                                          = 0x37,
    /// Connection refused - insufficient encryption key size
    L2C_ERR_INSUFF_ENC_KEY_SIZE                                                    = 0x38,
    /// Connection Refused - insufficient encryption
    L2C_ERR_INSUFF_ENC                                                             = 0x39,
    /// Connection refused - LE_PSM not supported
    L2C_ERR_LEPSM_NOT_SUPP                                                         = 0x3A,
    /// No more credit
    L2C_ERR_INSUFF_CREDIT                                                          = 0x3B,
    /// Command not understood by peer device
    L2C_ERR_NOT_UNDERSTOOD                                                         = 0x3C,
    /// Credit error, invalid number of credit received
    L2C_ERR_CREDIT_ERROR                                                           = 0x3D,
    /// Channel identifier already allocated
    L2C_ERR_CID_ALREADY_ALLOC                                                      = 0x3E,


    // ----------------------------------------------------------------------------------
    // -------------------------- GAP Specific Error ------------------------------------
    // ----------------------------------------------------------------------------------
    /// Invalid parameters set
    GAP_ERR_INVALID_PARAM                                                          = 0x40,
    /// Problem with protocol exchange, get unexpected response
    GAP_ERR_PROTOCOL_PROBLEM                                                       = 0x41,
    /// Request not supported by software configuration
    GAP_ERR_NOT_SUPPORTED                                                          = 0x42,
    /// Request not allowed in current state.
    GAP_ERR_COMMAND_DISALLOWED                                                     = 0x43,
    /// Requested operation canceled.
    GAP_ERR_CANCELED                                                               = 0x44,
    /// Requested operation timeout.
    GAP_ERR_TIMEOUT                                                                = 0x45,
    /// Link connection lost during operation.
    GAP_ERR_DISCONNECTED                                                           = 0x46,
    /// Search algorithm finished, but no result found
    GAP_ERR_NOT_FOUND                                                              = 0x47,
    /// Request rejected by peer device
    GAP_ERR_REJECTED                                                               = 0x48,
    /// Problem with privacy configuration
    GAP_ERR_PRIVACY_CFG_PB                                                         = 0x49,
    /// Duplicate or invalid advertising data
    GAP_ERR_ADV_DATA_INVALID                                                       = 0x4A,
    /// Insufficient resources
    GAP_ERR_INSUFF_RESOURCES                                                       = 0x4B,
    /// Unexpected Error
    GAP_ERR_UNEXPECTED                                                             = 0x4C,
    /// Feature mismatch
    GAP_ERR_MISMATCH                                                               = 0x4D,


    // ----------------------------------------------------------------------------------
    // ------------------------- GATT Specific Error ------------------------------------
    // ----------------------------------------------------------------------------------
    /// Problem with ATTC protocol response
    GATT_ERR_INVALID_ATT_LEN                                                       = 0x50,
    /// Error in service search
    GATT_ERR_INVALID_TYPE_IN_SVC_SEARCH                                            = 0x51,
    /// Invalid write data
    GATT_ERR_WRITE                                                                 = 0x52,
    /// Signed write error
    GATT_ERR_SIGNED_WRITE                                                          = 0x53,
    /// No attribute client defined
    GATT_ERR_ATTRIBUTE_CLIENT_MISSING                                              = 0x54,
    /// No attribute server defined
    GATT_ERR_ATTRIBUTE_SERVER_MISSING                                              = 0x55,
    /// Permission set in service/attribute are invalid
    GATT_ERR_INVALID_PERM                                                          = 0x56,

    // ----------------------------------------------------------------------------------
    // ------------------------- SMP Specific Error -------------------------------------
    // ----------------------------------------------------------------------------------
    // SMP Protocol Errors detected on local device
    /// The user input of pass key failed, for example, the user canceled the operation.
    SMP_ERROR_LOC_PASSKEY_ENTRY_FAILED                                             = 0x61,
    /// The OOB Data is not available.
    SMP_ERROR_LOC_OOB_NOT_AVAILABLE                                                = 0x62,
    /// The pairing procedure cannot be performed as authentication requirements cannot be met
    /// due to IO capabilities of one or both devices.
    SMP_ERROR_LOC_AUTH_REQ                                                         = 0x63,
    /// The confirm value does not match the calculated confirm value.
    SMP_ERROR_LOC_CONF_VAL_FAILED                                                  = 0x64,
    /// Pairing is not supported by the device.
    SMP_ERROR_LOC_PAIRING_NOT_SUPP                                                 = 0x65,
    /// The resultant encryption key size is insufficient for the security requirements of
    /// this device.
    SMP_ERROR_LOC_ENC_KEY_SIZE                                                     = 0x66,
    /// The SMP command received is not supported on this device.
    SMP_ERROR_LOC_CMD_NOT_SUPPORTED                                                = 0x67,
    /// Pairing failed due to an unspecified reason.
    SMP_ERROR_LOC_UNSPECIFIED_REASON                                               = 0x68,
    /// Pairing or Authentication procedure is disallowed because too little time has elapsed
    /// since last pairing request or security request.
    SMP_ERROR_LOC_REPEATED_ATTEMPTS                                                = 0x69,
    /// The command length is invalid or a parameter is outside of the specified range.
    SMP_ERROR_LOC_INVALID_PARAM                                                    = 0x6A,
    /// Indicates to the remote device that the DHKey Check value received doesn't
    /// match the one calculated by the local device.
    SMP_ERROR_LOC_DHKEY_CHECK_FAILED                                               = 0x6B,
    /// Indicates that the confirm values in the numeric comparison protocol do not match.
    SMP_ERROR_LOC_NUMERIC_COMPARISON_FAILED                                        = 0x6C,
    /// Indicates that the pairing over the LE transport failed due to a Pairing Request sent
    /// over the BR/EDR transport in process.
    SMP_ERROR_LOC_BREDR_PAIRING_IN_PROGRESS                                        = 0x6D,
    /// Indicates that the BR/EDR Link Key generated on the BR/EDR transport cannot be
    /// used to derive and distribute keys for the LE transport.
    SMP_ERROR_LOC_CROSS_TRANSPORT_KEY_GENERATION_NOT_ALLOWED                       = 0x6E,
    // SMP Protocol Errors detected by remote device
    /// The user input of passkey failed, for example, the user canceled the operation.
    SMP_ERROR_REM_PASSKEY_ENTRY_FAILED                                             = 0x71,
    /// The OOB Data is not available.
    SMP_ERROR_REM_OOB_NOT_AVAILABLE                                                = 0x72,
    /// The pairing procedure cannot be performed as authentication requirements cannot be
    /// met due to IO capabilities of one or both devices.
    SMP_ERROR_REM_AUTH_REQ                                                         = 0x73,
    /// The confirm value does not match the calculated confirm value.
    SMP_ERROR_REM_CONF_VAL_FAILED                                                  = 0x74,
    /// Pairing is not supported by the device.
    SMP_ERROR_REM_PAIRING_NOT_SUPP                                                 = 0x75,
    /// The resultant encryption key size is insufficient for the security requirements of
    /// this device.
    SMP_ERROR_REM_ENC_KEY_SIZE                                                     = 0x76,
    /// The SMP command received is not supported on this device.
    SMP_ERROR_REM_CMD_NOT_SUPPORTED                                                = 0x77,
    /// Pairing failed due to an unspecified reason.
    SMP_ERROR_REM_UNSPECIFIED_REASON                                               = 0x78,
    /// Pairing or Authentication procedure is disallowed because too little time has elapsed
    /// since last pairing request or security request.
    SMP_ERROR_REM_REPEATED_ATTEMPTS                                                = 0x79,
    /// The command length is invalid or a parameter is outside of the specified range.
    SMP_ERROR_REM_INVALID_PARAM                                                    = 0x7A,
    /// Indicates to the remote device that the DHKey Check value received doesn't
    /// match the one calculated by the local device.
    SMP_ERROR_REM_DHKEY_CHECK_FAILED                                               = 0x7B,
    /// Indicates that the confirm values in the numeric comparison protocol do not match.
    SMP_ERROR_REM_NUMERIC_COMPARISON_FAILED                                        = 0x7C,
    /// Indicates that the pairing over the LE transport failed due to a Pairing Request sent
    /// over the BR/EDR transport in process.
    SMP_ERROR_REM_BREDR_PAIRING_IN_PROGRESS                                        = 0x7D,
    /// Indicates that the BR/EDR Link Key generated on the BR/EDR transport cannot be
    /// used to derive and distribute keys for the LE transport.
    SMP_ERROR_REM_CROSS_TRANSPORT_KEY_GENERATION_NOT_ALLOWED                       = 0x7E,
    // SMP Errors triggered by local device
    /// The provided resolvable address has not been resolved.
    SMP_ERROR_ADDR_RESOLV_FAIL                                                     = 0xD0,
    /// The Signature Verification Failed
    SMP_ERROR_SIGN_VERIF_FAIL                                                      = 0xD1,
    /// The encryption procedure failed because the slave device didn't find the LTK
    /// needed to start an encryption session.
    SMP_ERROR_ENC_KEY_MISSING                                                      = 0xD2,
    /// The encryption procedure failed because the slave device doesn't support the
    /// encryption feature.
    SMP_ERROR_ENC_NOT_SUPPORTED                                                    = 0xD3,
    /// A timeout has occurred during the start encryption session.
    SMP_ERROR_ENC_TIMEOUT                                                          = 0xD4,

    // ----------------------------------------------------------------------------------
    //------------------------ Profiles specific error codes ----------------------------
    // ----------------------------------------------------------------------------------
    /// Application Error
    PRF_APP_ERROR                                                                  = 0x80,
    /// Invalid parameter in request
    PRF_ERR_INVALID_PARAM                                                          = 0x81,
    /// Inexistent handle for sending a read/write characteristic request
    PRF_ERR_INEXISTENT_HDL                                                         = 0x82,
    /// Discovery stopped due to missing attribute according to specification
    PRF_ERR_STOP_DISC_CHAR_MISSING                                                 = 0x83,
    /// Too many SVC instances found -> protocol violation
    PRF_ERR_MULTIPLE_SVC                                                           = 0x84,
    /// Discovery stopped due to found attribute with incorrect properties
    PRF_ERR_STOP_DISC_WRONG_CHAR_PROP                                              = 0x85,
    /// Too many Char. instances found-> protocol violation
    PRF_ERR_MULTIPLE_CHAR                                                          = 0x86,
    /// Attribute write not allowed
    PRF_ERR_NOT_WRITABLE                                                           = 0x87,
    /// Attribute read not allowed
    PRF_ERR_NOT_READABLE                                                           = 0x88,
    /// Request not allowed
    PRF_ERR_REQ_DISALLOWED                                                         = 0x89,
    /// Notification Not Enabled
    PRF_ERR_NTF_DISABLED                                                           = 0x8A,
    /// Indication Not Enabled
    PRF_ERR_IND_DISABLED                                                           = 0x8B,
    /// Feature not supported by profile
    PRF_ERR_FEATURE_NOT_SUPPORTED                                                  = 0x8C,
    /// Read value has an unexpected length
    PRF_ERR_UNEXPECTED_LEN                                                         = 0x8D,
    /// Disconnection occurs
    PRF_ERR_DISCONNECTED                                                           = 0x8E,
    /// Procedure Timeout
    PRF_ERR_PROC_TIMEOUT                                                           = 0x8F,
    /// Client characteristic configuration improperly configured
    PRF_CCCD_IMPR_CONFIGURED                                                       = 0xFD,
    /// Procedure already in progress
    PRF_PROC_IN_PROGRESS                                                           = 0xFE,
    /// Out of Range
    PRF_OUT_OF_RANGE                                                               = 0xFF,

    // ----------------------------------------------------------------------------------
    //-------------------- LL Error codes conveyed to upper layer -----------------------
    // ----------------------------------------------------------------------------------
    /// Unknown HCI Command
    LL_ERR_UNKNOWN_HCI_COMMAND                                                     = 0x91,
    /// Unknown Connection Identifier
    LL_ERR_UNKNOWN_CONNECTION_ID                                                   = 0x92,
    /// Hardware Failure
    LL_ERR_HARDWARE_FAILURE                                                        = 0x93,
    /// BT Page Timeout
    LL_ERR_PAGE_TIMEOUT                                                            = 0x94,
    /// Authentication failure
    LL_ERR_AUTH_FAILURE                                                            = 0x95,
    /// Pin code missing
    LL_ERR_PIN_MISSING                                                             = 0x96,
    /// Memory capacity exceed
    LL_ERR_MEMORY_CAPA_EXCEED                                                      = 0x97,
    /// Connection Timeout
    LL_ERR_CON_TIMEOUT                                                             = 0x98,
    /// Connection limit Exceed
    LL_ERR_CON_LIMIT_EXCEED                                                        = 0x99,
    /// Synchronous Connection limit exceed
    LL_ERR_SYNC_CON_LIMIT_DEV_EXCEED                                               = 0x9A,
    /// ACL Connection exits
    LL_ERR_ACL_CON_EXISTS                                                          = 0x9B,
    /// Command Disallowed
    LL_ERR_COMMAND_DISALLOWED                                                      = 0x9C,
    /// Connection rejected due to limited resources
    LL_ERR_CONN_REJ_LIMITED_RESOURCES                                              = 0x9D,
    /// Connection rejected due to security reason
    LL_ERR_CONN_REJ_SECURITY_REASONS                                               = 0x9E,
    /// Connection rejected due to unacceptable BD Addr
    LL_ERR_CONN_REJ_UNACCEPTABLE_BDADDR                                            = 0x9F,
    /// Connection rejected due to Accept connection timeout
    LL_ERR_CONN_ACCEPT_TIMEOUT_EXCEED                                              = 0xA0,
    /// Not Supported
    LL_ERR_UNSUPPORTED                                                             = 0xA1,
    /// invalid parameters
    LL_ERR_INVALID_HCI_PARAM                                                       = 0xA2,
    /// Remote user terminate connection
    LL_ERR_REMOTE_USER_TERM_CON                                                    = 0xA3,
    /// Remote device terminate connection due to low resources
    LL_ERR_REMOTE_DEV_TERM_LOW_RESOURCES                                           = 0xA4,
    /// Remote device terminate connection due to power off
    LL_ERR_REMOTE_DEV_POWER_OFF                                                    = 0xA5,
    /// Connection terminated by local host
    LL_ERR_CON_TERM_BY_LOCAL_HOST                                                  = 0xA6,
    /// Repeated attempts
    LL_ERR_REPEATED_ATTEMPTS                                                       = 0xA7,
    /// Pairing not Allowed
    LL_ERR_PAIRING_NOT_ALLOWED                                                     = 0xA8,
    /// Unknown PDU Error
    LL_ERR_UNKNOWN_LMP_PDU                                                         = 0xA9,
    /// Unsupported remote feature
    LL_ERR_UNSUPPORTED_REMOTE_FEATURE                                              = 0xAA,
    /// Sco Offset rejected
    LL_ERR_SCO_OFFSET_REJECTED                                                     = 0xAB,
    /// SCO Interval Rejected
    LL_ERR_SCO_INTERVAL_REJECTED                                                   = 0xAC,
    /// SCO air mode Rejected
    LL_ERR_SCO_AIR_MODE_REJECTED                                                   = 0xAD,
    /// Invalid LMP parameters
    LL_ERR_INVALID_LMP_PARAM                                                       = 0xAE,
    /// Unspecified error
    LL_ERR_UNSPECIFIED_ERROR                                                       = 0xAF,
    /// Unsupported LMP Parameter value
    LL_ERR_UNSUPPORTED_LMP_PARAM_VALUE                                             = 0xB0,
    /// Role Change Not allowed
    LL_ERR_ROLE_CHANGE_NOT_ALLOWED                                                 = 0xB1,
    /// LMP Response timeout
    LL_ERR_LMP_RSP_TIMEOUT                                                         = 0xB2,
    /// LMP Collision
    LL_ERR_LMP_COLLISION                                                           = 0xB3,
    /// LMP Pdu not allowed
    LL_ERR_LMP_PDU_NOT_ALLOWED                                                     = 0xB4,
    /// Encryption mode not accepted
    LL_ERR_ENC_MODE_NOT_ACCEPT                                                     = 0xB5,
    /// Link Key Cannot be changed
    LL_ERR_LINK_KEY_CANT_CHANGE                                                    = 0xB6,
    /// Quality of Service not supported
    LL_ERR_QOS_NOT_SUPPORTED                                                       = 0xB7,
    /// Error, instant passed
    LL_ERR_INSTANT_PASSED                                                          = 0xB8,
    /// Pairing with unit key not supported
    LL_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUP                                           = 0xB9,
    /// Transaction collision
    LL_ERR_DIFF_TRANSACTION_COLLISION                                              = 0xBA,
    /// Unacceptable parameters
    LL_ERR_QOS_UNACCEPTABLE_PARAM                                                  = 0xBC,
    /// Quality of Service rejected
    LL_ERR_QOS_REJECTED                                                            = 0xBD,
    /// Channel class not supported
    LL_ERR_CHANNEL_CLASS_NOT_SUP                                                   = 0xBE,
    /// Insufficient security
    LL_ERR_INSUFFICIENT_SECURITY                                                   = 0xBF,
    /// Parameters out of mandatory range
    LL_ERR_PARAM_OUT_OF_MAND_RANGE                                                 = 0xC0,
    /// Role switch pending
    LL_ERR_ROLE_SWITCH_PEND                                                        = 0xC2,
    /// Reserved slot violation
    LL_ERR_RESERVED_SLOT_VIOLATION                                                 = 0xC4,
    /// Role Switch fail
    LL_ERR_ROLE_SWITCH_FAIL                                                        = 0xC5,
    /// Error, EIR too large
    LL_ERR_EIR_TOO_LARGE                                                           = 0xC6,
    /// Simple pairing not supported by host
    LL_ERR_SP_NOT_SUPPORTED_HOST                                                   = 0xC7,
    /// Host pairing is busy
    LL_ERR_HOST_BUSY_PAIRING                                                       = 0xC8,
    /// Controller is busy
    LL_ERR_CONTROLLER_BUSY                                                         = 0xCA,
    /// Unacceptable connection initialization
    LL_ERR_UNACCEPTABLE_CONN_INT                                                   = 0xCB,
    /// Direct Advertising Timeout
    LL_ERR_DIRECT_ADV_TO                                                           = 0xCC,
    /// Connection Terminated due to a MIC failure
    LL_ERR_TERMINATED_MIC_FAILURE                                                  = 0xCD,
    /// Connection failed to be established
    LL_ERR_CONN_FAILED_TO_BE_EST                                                   = 0xCE,
};

/// @} RWBLE_HL_ERROR_H

#endif // RWBLE_HL_ERROR_H_
