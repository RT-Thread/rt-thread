/***************************************************************************//**
* \file cyhal_crypto_common.h
*
* Description:
* This file provides common defines, addresses, and functions required by drivers
* using the Crypto block.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

#include "cy_device.h"
#include "cy_pdl.h"
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if (_CYHAL_DRIVER_AVAILABLE_CRYPTO)

#if defined(__cplusplus)
extern "C" {
#endif

/* Block count for CRYPTO blocks */
#if defined(CY_IP_MXCRYPTO)
#define CYHAL_CRYPTO_INST_COUNT      CY_IP_MXCRYPTO_INSTANCES
#elif defined(CY_IP_MXCRYPTOLITE)
#define CYHAL_CRYPTO_INST_COUNT      CY_IP_MXCRYPTOLITE_INSTANCES
#elif defined(CY_IP_M0S8CRYPTO)
#define CYHAL_CRYPTO_INST_COUNT      CY_IP_M0S8CRYPTO_INSTANCES
#elif defined(CY_IP_M0S8CRYPTOLITE)
#define CYHAL_CRYPTO_INST_COUNT      CY_IP_M0S8CRYPTOLITE_INSTANCES
#endif

typedef enum
{
    /* CRC hardware acceleration */
    CYHAL_CRYPTO_CRC,
    /* TRNG hardware acceleration */
    CYHAL_CRYPTO_TRNG,
    /* VU hardware acceleration */
    CYHAL_CRYPTO_VU,
    /* Common features of the Crypto block  */
    CYHAL_CRYPTO_COMMON,
} cyhal_crypto_feature_t;


/* Reserve the Crypto block and enable it.
 *
 * @param[out]  base Base address to the Crypto block.
 * @param[out]  resource Resource inst for the function (eg. CRC, TRNG) in the Crypto block.
 * @param[in]   feature feature to reserve on the Crypto block (eg. TRNG, CRC, etc.).
 * @return The status of the reserve request.
 */
cy_rslt_t cyhal_crypto_reserve(CRYPTO_Type** base, cyhal_resource_inst_t *resource, cyhal_crypto_feature_t feature);

/* Free the Crypto block and disable it.
 *
 * @param[in]  base Base address to the Crypto block.
 * @param[in]  resource Resource inst for the function in Crypto block.
 * @param[in]  feature Feature to free on the Crypto block (eg. TRNG, CRC, etc.).
 */
void cyhal_crypto_free(CRYPTO_Type* base, cyhal_resource_inst_t *resource, cyhal_crypto_feature_t feature);

#if defined(__cplusplus)
}
#endif

#endif /* _CYHAL_DRIVER_AVAILABLE_CRYPTO */
