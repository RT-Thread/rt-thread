/*******************************************************************************
* File Name: cyhal_crypto_common.c
*
* Description:
* Provides a high level interface for interacting with the Infineon Crypto Accelerator.
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

#include "cyhal_hwmgr.h"
#include "cyhal_crypto_common.h"

#if (_CYHAL_DRIVER_AVAILABLE_CRYPTO)

#if defined(__cplusplus)
extern "C"
{
#endif

static CRYPTO_Type* const _CYHAL_CRYPTO_BASE_ADDRESSES[CYHAL_CRYPTO_INST_COUNT] =
{
#if defined (CRYPTO)
    CRYPTO,
#endif
};

// Number of Crypto features
#define _CYHAL_CRYPTO_FEATURES_NUM         ((uint32_t)CYHAL_CRYPTO_COMMON + 1u)

// Defines for maximum available features in Crypto block
#define _CYHAL_CRYPTO_FEATURE_CRC_MAX_VAL         (1u)
#define _CYHAL_CRYPTO_FEATURE_TRNG_MAX_VAL        (1u)
#define _CYHAL_CRYPTO_FEATURE_VU_MAX_VAL          (256u)
#define _CYHAL_CRYPTO_FEATURE_COMMON_MAX_VAL      (256u)

static uint16_t _cyhal_crypto_features[CYHAL_CRYPTO_INST_COUNT][_CYHAL_CRYPTO_FEATURES_NUM] = {{0}};
static uint16_t _cyhal_crypto_features_max_val[_CYHAL_CRYPTO_FEATURES_NUM] = {_CYHAL_CRYPTO_FEATURE_CRC_MAX_VAL,
                                                                     _CYHAL_CRYPTO_FEATURE_TRNG_MAX_VAL,
                                                                     _CYHAL_CRYPTO_FEATURE_VU_MAX_VAL,
                                                                     _CYHAL_CRYPTO_FEATURE_COMMON_MAX_VAL};

static bool _cyhal_crypto_enabled(uint32_t instance_count)
{
    uint8_t reserved = (uint8_t)(_cyhal_crypto_features[instance_count][CYHAL_CRYPTO_CRC]  |
                                 _cyhal_crypto_features[instance_count][CYHAL_CRYPTO_TRNG] |
                                 _cyhal_crypto_features[instance_count][CYHAL_CRYPTO_VU]   |
                                 _cyhal_crypto_features[instance_count][CYHAL_CRYPTO_COMMON]);

    return (reserved != 0);
}

cy_rslt_t cyhal_crypto_reserve(CRYPTO_Type** base, cyhal_resource_inst_t *resource, cyhal_crypto_feature_t feature)
{
    cy_rslt_t result = CYHAL_HWMGR_RSLT_ERR_INUSE;

    for (uint32_t i = 0u; i < CYHAL_CRYPTO_INST_COUNT; i++)
    {
        if (_cyhal_crypto_features[i][feature] < _cyhal_crypto_features_max_val[feature])
        {
            resource->type = CYHAL_RSC_CRYPTO;
            resource->block_num = (uint8_t)i;
            resource->channel_num = 0;
            *base = _CYHAL_CRYPTO_BASE_ADDRESSES[i];

            result = CY_RSLT_SUCCESS;

            //Enable block if this as this first feature that is reserved in block
            if (!_cyhal_crypto_enabled(i))
            {
                result = cyhal_hwmgr_reserve(resource);
                if (result == CY_RSLT_SUCCESS)
                {
#if defined(CY_IP_MXCRYPTO)
                    Cy_Crypto_Core_Enable(*base);
#elif defined(CY_IP_M0S8CRYPTO) || defined(CY_IP_M0S8CRYPTOLITE)
                    Cy_Crypto_Enable(*base);
#endif
                }
            }

            if(result == CY_RSLT_SUCCESS)
            {
                ++_cyhal_crypto_features[i][feature];
                break;
            }
        }
    }
    return result;
}

void cyhal_crypto_free(CRYPTO_Type* base, cyhal_resource_inst_t *resource, cyhal_crypto_feature_t feature)
{
    if (_cyhal_crypto_features[resource->block_num][feature] != 0)
    {
        --_cyhal_crypto_features[resource->block_num][feature];
    }

    //If this was the last feature then free the underlying crypto block as well.
    if (!_cyhal_crypto_enabled(resource->block_num))
    {
#if defined(CY_IP_MXCRYPTO)
        if (Cy_Crypto_Core_IsEnabled(base))
        {
            Cy_Crypto_Core_Disable(base);
        }
#elif defined(CY_IP_M0S8CRYPTO) || defined(CY_IP_M0S8CRYPTOLITE)
        if (Cy_Crypto_IsEnabled(base))
        {
            Cy_Crypto_Disable(base);
        }
#else
        CY_UNUSED_PARAMETER(base);
#endif
        cyhal_hwmgr_free(resource);
        resource->type = CYHAL_RSC_INVALID;
    }
}

#if defined(__cplusplus)
}
#endif

#endif /* _CYHAL_DRIVER_AVAILABLE_CRYPTO */
