/**
 ****************************************************************************************
 *
 * @file co_error.h
 *
 * @brief List of codes for error in RW Software.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef CO_ERROR_H_
#define CO_ERROR_H_

/**
 ****************************************************************************************
 * @addtogroup CO_ERROR Error Codes
 * @ingroup COMMON
 * @brief Defines error codes in messages.
 *
 * @{
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
enum co_error
{
/*****************************************************
 ***              ERROR CODES                      ***
 *****************************************************/

    CO_ERROR_NO_ERROR                        = 0x00,
    CO_ERROR_UNKNOWN_HCI_COMMAND             = 0x01,
    CO_ERROR_UNKNOWN_CONNECTION_ID           = 0x02,
    CO_ERROR_HARDWARE_FAILURE                = 0x03,
    CO_ERROR_PAGE_TIMEOUT                    = 0x04,
    CO_ERROR_AUTH_FAILURE                    = 0x05,
    CO_ERROR_PIN_MISSING                     = 0x06,
    CO_ERROR_MEMORY_CAPA_EXCEED              = 0x07,
    CO_ERROR_CON_TIMEOUT                     = 0x08,
    CO_ERROR_CON_LIMIT_EXCEED                = 0x09,
    CO_ERROR_SYNC_CON_LIMIT_DEV_EXCEED       = 0x0A,
    CO_ERROR_ACL_CON_EXISTS                  = 0x0B,
    CO_ERROR_COMMAND_DISALLOWED              = 0x0C,
    CO_ERROR_CONN_REJ_LIMITED_RESOURCES      = 0x0D,
    CO_ERROR_CONN_REJ_SECURITY_REASONS       = 0x0E,
    CO_ERROR_CONN_REJ_UNACCEPTABLE_BDADDR    = 0x0F,
    CO_ERROR_CONN_ACCEPT_TIMEOUT_EXCEED      = 0x10,
    CO_ERROR_UNSUPPORTED                     = 0x11,
    CO_ERROR_INVALID_HCI_PARAM               = 0x12,
    CO_ERROR_REMOTE_USER_TERM_CON            = 0x13,
    CO_ERROR_REMOTE_DEV_TERM_LOW_RESOURCES   = 0x14,
    CO_ERROR_REMOTE_DEV_POWER_OFF            = 0x15,
    CO_ERROR_CON_TERM_BY_LOCAL_HOST          = 0x16,
    CO_ERROR_REPEATED_ATTEMPTS               = 0x17,
    CO_ERROR_PAIRING_NOT_ALLOWED             = 0x18,
    CO_ERROR_UNKNOWN_LMP_PDU                 = 0x19,
    CO_ERROR_UNSUPPORTED_REMOTE_FEATURE      = 0x1A,
    CO_ERROR_SCO_OFFSET_REJECTED             = 0x1B,
    CO_ERROR_SCO_INTERVAL_REJECTED           = 0x1C,
    CO_ERROR_SCO_AIR_MODE_REJECTED           = 0x1D,
    CO_ERROR_INVALID_LMP_PARAM               = 0x1E,
    CO_ERROR_UNSPECIFIED_ERROR               = 0x1F,
    CO_ERROR_UNSUPPORTED_LMP_PARAM_VALUE     = 0x20,
    CO_ERROR_ROLE_CHANGE_NOT_ALLOWED         = 0x21,
    CO_ERROR_LMP_RSP_TIMEOUT                 = 0x22,
    CO_ERROR_LMP_COLLISION                   = 0x23,
    CO_ERROR_LMP_PDU_NOT_ALLOWED             = 0x24,
    CO_ERROR_ENC_MODE_NOT_ACCEPT             = 0x25,
    CO_ERROR_LINK_KEY_CANT_CHANGE            = 0x26,
    CO_ERROR_QOS_NOT_SUPPORTED               = 0x27,
    CO_ERROR_INSTANT_PASSED                  = 0x28,
    CO_ERROR_PAIRING_WITH_UNIT_KEY_NOT_SUP   = 0x29,
    CO_ERROR_DIFF_TRANSACTION_COLLISION      = 0x2A,
    CO_ERROR_QOS_UNACCEPTABLE_PARAM          = 0x2C,
    CO_ERROR_QOS_REJECTED                    = 0x2D,
    CO_ERROR_CHANNEL_CLASS_NOT_SUP           = 0x2E,
    CO_ERROR_INSUFFICIENT_SECURITY           = 0x2F,
    CO_ERROR_PARAM_OUT_OF_MAND_RANGE         = 0x30,
    CO_ERROR_ROLE_SWITCH_PEND                = 0x32, /* LM_ROLE_SWITCH_PENDING               */
    CO_ERROR_RESERVED_SLOT_VIOLATION         = 0x34, /* LM_RESERVED_SLOT_VIOLATION           */
    CO_ERROR_ROLE_SWITCH_FAIL                = 0x35, /* LM_ROLE_SWITCH_FAILED                */
    CO_ERROR_EIR_TOO_LARGE                   = 0x36, /* LM_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE */
    CO_ERROR_SP_NOT_SUPPORTED_HOST           = 0x37,
    CO_ERROR_HOST_BUSY_PAIRING               = 0x38,
    CO_ERROR_CONTROLLER_BUSY                 = 0x3A,
    CO_ERROR_UNACCEPTABLE_CONN_INT           = 0x3B,
    CO_ERROR_DIRECT_ADV_TO                   = 0x3C,
    CO_ERROR_TERMINATED_MIC_FAILURE          = 0x3D,
    CO_ERROR_CONN_FAILED_TO_BE_EST           = 0x3E,
    CO_ERROR_CCA_REJ_USE_CLOCK_DRAG          = 0x40,
    CO_ERROR_UNDEFINED                       = 0xFF,


/*****************************************************
 ***              HW ERROR CODES                   ***
 *****************************************************/

    CO_ERROR_HW_UART_OUT_OF_SYNC            = 0x00,
    CO_ERROR_HW_MEM_ALLOC_FAIL              = 0x01,
};

/// @} CO_ERROR

#endif // CO_ERROR_H_
