/***************************************************************************//**
 * \file cyhal_crc_impl.h
*
* Description:
* Provides a high level interface for interacting with the Infineon CRC accelerator.
* This is a wrapper around the lower level PDL API.
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

#include "cyhal_crc.h"
#include "cyhal_hwmgr.h"
#include "cy_utils.h"

#if (CYHAL_DRIVER_AVAILABLE_CRC)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(CY_IP_MXCRYPTO)
#define _cyhal_crc_calcinit(base, width, polynomial, data_reverse, data_xor, rem_reverse, rem_xor, lfsr_init_state) \
            Cy_Crypto_Core_Crc_CalcInit((base), (width), (polynomial), (data_reverse) ? 1u : 0u, (data_xor), (rem_reverse) ? 1u : 0u, (rem_xor), (lfsr_init_state))

#define _cyhal_crc_calcpartial(base, data, length) \
            Cy_Crypto_Core_Crc_CalcPartial((base), (data), (length))

#define _cyhal_crc_calc_finish(base, crc) \
            Cy_Crypto_Core_Crc_CalcFinish((base), (obj->crc_width), (crc))

#define _cyhal_crc_calc_free(base)

#elif defined(CY_IP_M0S8CRYPTO)
extern cy_stc_crypto_crc_context_t _cyhal_crc_context[CY_IP_M0S8CRYPTO_INSTANCES];
#define _cyhal_crc_calcinit(base, width, polynomial, data_reverse, data_xor, rem_reverse, rem_xor, lfsr_init_state) \
            Cy_Crypto_Crc_CalcInit((base), (width), (polynomial), (data_reverse), (data_xor), (rem_reverse), (rem_xor), (lfsr_init_state), (&_cyhal_crc_context[obj->resource.block_num]))

#define _cyhal_crc_calcpartial(base, data, length) \
            Cy_Crypto_Crc_CalcPartial((base), (data), (length), (&_cyhal_crc_context[obj->resource.block_num]))

#define _cyhal_crc_calc_finish(base, crc) \
            Cy_Crypto_Crc_CalcFinish((base), (crc), (&_cyhal_crc_context[obj->resource.block_num]))

#define _cyhal_crc_calc_free(base) \
            Cy_Crypto_Crc_CalcFree((base), (&_cyhal_crc_context[obj->resource.block_num]))

#endif

// This helper function mirrors the definition of cyhal_crc_start
__STATIC_INLINE cy_rslt_t _cyhal_crc_start(cyhal_crc_t *obj, const crc_algorithm_t *algorithm)
{
    CY_ASSERT(NULL != obj);
    if(NULL == algorithm)
        return CYHAL_CRC_RSLT_ERR_BAD_ARGUMENT;

    obj->crc_width = algorithm->width;
    return _cyhal_crc_calcinit(obj->base,
                                algorithm->width,
                                algorithm->polynomial,
                                algorithm->dataReverse,
                                algorithm->dataXor,
                                algorithm->remReverse,
                                algorithm->remXor,
                                algorithm->lfsrInitState);
}

#define cyhal_crc_start(obj, algorithm) _cyhal_crc_start((obj), (algorithm))

// This helper function mirrors the definition of cyhal_crc_compute
__STATIC_INLINE cy_rslt_t _cyhal_crc_compute(const cyhal_crc_t *obj, const uint8_t *data, size_t length)
{
    CY_ASSERT(NULL != obj);
    if(NULL == data || 0 == length)
        return CYHAL_CRC_RSLT_ERR_BAD_ARGUMENT;

    return _cyhal_crc_calcpartial(obj->base, data, length);
}

#define cyhal_crc_compute(obj, data, length) _cyhal_crc_compute((obj), (data), (length))

// This helper function mirrors the definition of cyhal_crc_finish
__STATIC_INLINE cy_rslt_t _cyhal_crc_finish(const cyhal_crc_t *obj, uint32_t *crc)
{
    CY_ASSERT(NULL != obj);
    if(NULL == crc)
        return CYHAL_CRC_RSLT_ERR_BAD_ARGUMENT;
    return _cyhal_crc_calc_finish(obj->base, crc);
}

#define cyhal_crc_finish(obj, crc) _cyhal_crc_finish((obj), (crc))

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* CYHAL_DRIVER_AVAILABLE_CRC */
