/***************************************************************************//**
* \file cyhal_trng_impl.h
*
* \brief
* Provides an implementation of the ModusToolboxâ„¢ TRNG HAL API.
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

#include "cyhal_trng.h"

#if (CYHAL_DRIVER_AVAILABLE_TRNG)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * \addtogroup group_hal_impl_trng TRNG (True Random Number Generator)
 * \ingroup group_hal_impl
 * \{
 * Initialization polynomial values for the True Random Number Generator.
 */

/** Galois ring oscillator value */
#define CYHAL_GARO31_INITSTATE          (0x04c11db7UL)
/** Fibonacci ring oscillator value */
#define CYHAL_FIRO31_INITSTATE          (0x04c11db7UL)

/** \} group_hal_impl_trng */

#define MAX_TRNG_BIT_SIZE               (32UL)

// This helper function mirrors the definition of cyhal_trng_generate
static inline uint32_t _cyhal_trng_generate_internal(const cyhal_trng_t *obj)
{
    CY_ASSERT(NULL != obj);
    uint32_t value;

#if defined(CY_IP_MXCRYPTO)
    cy_en_crypto_status_t status = Cy_Crypto_Core_Trng(
        obj->base, CYHAL_GARO31_INITSTATE, CYHAL_FIRO31_INITSTATE, MAX_TRNG_BIT_SIZE, &value);
#elif defined(CY_IP_M0S8CRYPTO) || defined(CY_IP_M0S8CRYPTOLITE)
    cy_en_crypto_status_t status = Cy_Crypto_Trng(
        obj->base, MAX_TRNG_BIT_SIZE, &value);
#endif

    (void)status;
    CY_ASSERT(CY_CRYPTO_SUCCESS == status);
    return value;
}

#define cyhal_trng_generate(obj) _cyhal_trng_generate_internal(obj)


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* CYHAL_DRIVER_AVAILABLE_TRNG */
