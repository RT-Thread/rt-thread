/***************************************************************************//**
* \file cy_crypto_core_hmac_v2.h
* \version 2.70
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


#if !defined (CY_CRYPTO_CORE_HMAC_V2_H)
#define CY_CRYPTO_CORE_HMAC_V2_H

#include "cy_crypto_common.h"

#if defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C)

#include "cy_crypto_core_sha_v2.h"

#define CY_CRYPTO_HMAC_IPAD               (0x36u)
#define CY_CRYPTO_HMAC_0PAD               (0x5Cu)
#define CY_CRYPTO_HMAC_MAX_PAD_SIZE       (128u)
#define CY_CRYPTO_HMAC_MAX_M0_KEY_SIZE    (128u)

/** \cond INTERNAL */

typedef struct
{
    /* Allocates CY_CRYPTO_HMAC_MAX_PAD_SIZE Bytes for the inner padding. */
    uint8_t ipad[CY_CRYPTO_HMAC_MAX_PAD_SIZE];

    /* Allocates CY_CRYPTO_HMAC_MAX_PAD_SIZE Bytes for the outer padding. */
    uint8_t opad[CY_CRYPTO_HMAC_MAX_PAD_SIZE];

    /* Allocates CY_CRYPTO_SHA_MAX_BLOCK_SIZE Bytes for the HMAC keys. */
    uint8_t m0Key[CY_CRYPTO_SHA_MAX_BLOCK_SIZE];

    /* SHA buffers for storing and processing the data */
    cy_stc_crypto_v2_sha512_buffers_t shaBuffers;
} cy_stc_crypto_v2_hmac_buffers_t;

/** \endcond */

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Init(CRYPTO_Type *base,
                                                cy_stc_crypto_hmac_state_t *hmacState,
                                                cy_en_crypto_sha_mode_t mode, cy_stc_crypto_v2_hmac_buffers_t *hmacBuffer);

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Start(CRYPTO_Type *base,
                                                cy_stc_crypto_hmac_state_t *hmacState,
                                                uint8_t const *key,
                                                uint32_t keyLength);

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Update(CRYPTO_Type *base,
                                                cy_stc_crypto_hmac_state_t  *hmacState,
                                                uint8_t   const *message,
                                                uint32_t  messageSize);

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Finish(CRYPTO_Type *base,
                                                cy_stc_crypto_hmac_state_t *hmacState,
                                                uint8_t *hmac);

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac_Free(CRYPTO_Type *base,
                                                cy_stc_crypto_hmac_state_t *hmacState);

cy_en_crypto_status_t Cy_Crypto_Core_V2_Hmac(CRYPTO_Type *base,
                                          uint8_t *hmac,
                                          uint8_t  const *message,
                                          uint32_t messageSize,
                                          uint8_t  const *key,
                                          uint32_t keyLength,
                                          cy_en_crypto_sha_mode_t mode);


#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* #if !defined (CY_CRYPTO_CORE_HMAC_V2_H) */


/* [] END OF FILE */
