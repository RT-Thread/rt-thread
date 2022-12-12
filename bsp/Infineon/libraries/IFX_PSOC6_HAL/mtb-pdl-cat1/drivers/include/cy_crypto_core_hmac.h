/***************************************************************************//**
* \file cy_crypto_core_hmac.h
* \version 2.50
*
* \brief
*  This file provides constants and function prototypes
*  for the API for the HMAC method in the Crypto block driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/


#if !defined (CY_CRYPTO_CORE_HMAC_H)
#define CY_CRYPTO_CORE_HMAC_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_SHA == 1)

#include "cy_crypto_core_hmac_v1.h"
#include "cy_crypto_core_hmac_v2.h"

typedef cy_en_crypto_status_t (*cy_crypto_hmac_func_t)(CRYPTO_Type *base,
                                          uint8_t *hmac,
                                          uint8_t  const *message,
                                          uint32_t messageSize,
                                          uint8_t  const *key,
                                          uint32_t keyLength,
                                          cy_en_crypto_sha_mode_t mode);

/**
* \addtogroup group_crypto_lld_mac_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Hmac
****************************************************************************//**
*
* Performs the HMAC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param hmac
* The pointer to the calculated HMAC. Must be 4-byte aligned.
*
* \param message
* The pointer to the message whose hash value is being computed.
*
* \param messageSize
* The size of the message.
*
* \param key
* The pointer to the key.
*
* \param keyLength
* The length of the key.
*
* \param mode
* \ref cy_en_crypto_sha_mode_t
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Hmac(CRYPTO_Type *base,
                                          uint8_t *hmac,
                                          uint8_t const *message,
                                          uint32_t messageSize,
                                          uint8_t const *key,
                                          uint32_t keyLength,
                                          cy_en_crypto_sha_mode_t mode)
{
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Hmac(base, hmac, message, messageSize, key, keyLength, mode);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Hmac(base, hmac, message, messageSize, key, keyLength, mode);
    }

    return tmpResult;
}

/** \} group_crypto_lld_mac_functions */

#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_HMAC_H) */


/* [] END OF FILE */
