/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _FSL_IAP_SKBOOT_AUTHENTICATE_H_
#define _FSL_IAP_SKBOOT_AUTHENTICATE_H_

#include "fsl_common.h"

/*!
 * @addtogroup skboot_authenticate
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief SKBOOT return status*/
typedef enum _skboot_status
{
    kStatus_SKBOOT_Success               = 0x5ac3c35au, /*!< SKBOOT return success status.*/
    kStatus_SKBOOT_Fail                  = 0xc35ac35au, /*!< SKBOOT return fail status.*/
    kStatus_SKBOOT_InvalidArgument       = 0xc35a5ac3u, /*!< SKBOOT return invalid argument status.*/
    kStatus_SKBOOT_KeyStoreMarkerInvalid = 0xc3c35a5au, /*!< SKBOOT return Keystore invalid Marker status.*/
    kStatus_SKBOOT_HashcryptFinishedWithStatusSuccess =
        0xc15a5ac3, /*!< SKBOOT return Hashcrypt finished with the success status.*/
    kStatus_SKBOOT_HashcryptFinishedWithStatusFail =
        0xc15a5acb, /*!< SKBOOT return Hashcrypt finished with the fail status.*/
} skboot_status_t;

/*! @brief Secure bool flag*/
typedef enum _secure_bool
{
    kSECURE_TRUE                       = 0xc33cc33cU, /*!< Secure true flag.*/
    kSECURE_FALSE                      = 0x5aa55aa5U, /*!< Secure false flag.*/
    kSECURE_CALLPROTECT_SECURITY_FLAGS = 0xc33c5aa5U, /*!< Secure call protect the security flag.*/
    kSECURE_CALLPROTECT_IS_APP_READY   = 0x5aa5c33cU, /*!< Secure call protect the app is ready flag.*/
    kSECURE_TRACKER_VERIFIED           = 0x55aacc33U, /*!< Secure tracker verified flag.*/
} secure_bool_t;

/*******************************************************************************
 * Externs
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Authenticate entry function with ARENA allocator init
 *
 * This is called by ROM boot or by ROM API g_skbootAuthenticateInterface
 */
skboot_status_t skboot_authenticate(const uint8_t *imageStartAddr, secure_bool_t *isSignVerified);

/*!
 * @brief Interface for image authentication API
 */
void HASH_IRQHandler(void);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* _FSL_IAP_SKBOOT_AUTHENTICATE_H_ */
