/**
****************************************************************************************
*
* @file smp_common.h
*
* @brief Header file - Security Manager Protocol Common Definitions and Functions.
*
* Copyright (C) RivieraWaves 2009-2016
*
*
****************************************************************************************
*/

/**
 ****************************************************************************************
 * @addtogroup SMP_COMMON
 * @ingroup SMP
 * @{
 ****************************************************************************************
 */

#ifndef SMP_COMMON_H_
#define SMP_COMMON_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#include <stdbool.h>       // Standard Boolean Definitions
#include <stdint.h>        // Standard Integer Definitions

#include "co_utils.h"
#include "co_bt.h"         // Common Bluetooth Definitions

/*
 * DEFINES
 ****************************************************************************************
 */

/// Mask applied to a Pairing Failed error triggered by us.
#define SMP_PAIR_FAIL_REASON_MASK           (0x60)
/// Mask applied to a Pairing Failed error triggered by the peer device.
#define SMP_PAIR_FAIL_REASON_REM_MASK       (0x70)

/*
 * MACROS
 ****************************************************************************************
 */

/// Mask a Pairing Failed reason value with the provided mask.
#define SMP_GEN_PAIR_FAIL_REASON(mask, reason)  (mask | reason)
/// Extract the mask from a masked Pairing Failed reason value.
#define SMP_GET_PAIR_FAIL_MASK(reason)          (0xF0 & reason)
/// Extract the Pairing Failed reason value from a masked Pairing Failed reason value.
#define SMP_GET_PAIR_FAIL_REASON(reason)        (0x0F & reason)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/**
 * SMP Pairing Failed Reasons
 */
enum smp_pair_fail_reason
{

    /**
     * Passkey Entry Failed (0x01)
     * The user input of passkey failed, for example, the user cancelled the operation.
     */
    SMP_ERROR_PASSKEY_ENTRY_FAILED      = 0x01,
    /**
     * OOB Not Available (0x02)
     * The OOB Data is not available.
     */
    SMP_ERROR_OOB_NOT_AVAILABLE,
    /**
     * Authentication Requirements (0x03)
     * The pairing procedure cannot be performed as authentication requirements cannot be
     * met due to IO capabilities of one or both devices.
     */
    SMP_ERROR_AUTH_REQ,
    /**
     * Confirm Value Failed (0x04)
     * The confirm value does not match the calculated confirm value.
     */
    SMP_ERROR_CONF_VAL_FAILED,
    /**
     * Pairing Not Supported (0x05)
     * Pairing is not supported by the device.
     */
    SMP_ERROR_PAIRING_NOT_SUPP,
    /**
     * Encryption Key Size (0x06)
     * The resultant encryption key size is insufficient for the security requirements of
     * this device.
     */
    SMP_ERROR_ENC_KEY_SIZE,
    /**
     * Command Not Supported (0x07)
     * The SMP command received is not supported on this device.
     */
    SMP_ERROR_CMD_NOT_SUPPORTED,
    /**
     * Unspecified Reason (0x08)
     * Pairing failed due to an unspecified reason.
     */
    SMP_ERROR_UNSPECIFIED_REASON,
    /**
     * Repeated Attempts (0x09)
     * Pairing or Authentication procedure is disallowed because too little time has elapsed
     * since last pairing request or security request.
     */
    SMP_ERROR_REPEATED_ATTEMPTS,
    /**
     * Invalid Parameters (0x0A)
     * The command length is invalid or a parameter is outside of the specified range.
     */
    SMP_ERROR_INVALID_PARAM,
    /**
     * DHKey Check Failed (0x0B)
     * Indicates to the remote device that the DHKey Check value received doesn't
     * match the one calculated by the local device.
     */
    SMP_ERROR_DHKEY_CHECK_FAILED,
    /**
     * Numeric Comparison Failed (0x0C)
     * Indicates that the confirm values in the numeric comparison protocol do not match.
     */
    SMP_ERROR_NUMERIC_COMPARISON_FAILED,
    /**
     * BR/EDR pairing in progress (0x0D)
     * Indicates that the pairing over the LE transport failed due to a Pairing Request sent
     * over the BR/EDR transport in process.
     */
    SMP_ERROR_BREDR_PAIRING_IN_PROGRESS,
    /**
     * Cross-transport Key Derivation/Generation not allowed (0x0E)
     *
     * Indicates that the BR/EDR Link Key generated on the BR/EDR transport cannot be
     * used to derive and distribute keys for the LE transport.
     */
    SMP_ERROR_CROSS_TRANSPORT_KEY_GENERATION_NOT_ALLOWED,
};


/*
 * STRUCTURES
 ****************************************************************************************
 */


#endif // (SMP_COMMON_H_)

/// @} SMP_COMMON
