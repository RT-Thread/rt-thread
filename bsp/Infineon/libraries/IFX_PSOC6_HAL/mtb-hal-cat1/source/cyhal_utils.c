/***************************************************************************//**
* \file cyhal_utils.c
*
* \brief
* Provides utility functions for working with the CAT1/CAT2 HAL implementation.
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

#include <stdlib.h>
#include <stdarg.h>
#include "cyhal_utils.h"
#include "cyhal_hwmgr.h"
#include "cyhal_gpio.h"

#if defined(__cplusplus)
extern "C"
{
#endif

const cyhal_resource_pin_mapping_t *_cyhal_utils_get_resource(cyhal_gpio_t pin, const cyhal_resource_pin_mapping_t* mappings, size_t count,
    const cyhal_resource_inst_t* block_res, bool ignore_channel)
{
    if (NC != pin)
    {
        for (uint32_t i = 0; i < count; i++)
        {
            if (pin == mappings[i].pin)
            {
                if ((NULL == block_res) || (_cyhal_utils_map_resource_equal(block_res, &(mappings[i]), ignore_channel)))
                {
                    return &mappings[i];
                }
            }
        }
    }
    return NULL;
}

const cyhal_resource_pin_mapping_t* _cyhal_utils_try_alloc(cyhal_gpio_t pin, cyhal_resource_t rsc, const cyhal_resource_pin_mapping_t *pin_map, size_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        if (pin == pin_map[i].pin)
        {
            cyhal_resource_inst_t inst = { rsc, pin_map[i].block_num, pin_map[i].channel_num };
            if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&inst))
            {
                return &pin_map[i];
            }
        }
    }
    return NULL;
}

void _cyhal_utils_release_if_used(cyhal_gpio_t *pin)
{
    if (CYHAL_NC_PIN_VALUE != *pin)
    {
#if defined(COMPONENT_CAT4)
        cyhal_resource_inst_t rsc = { CYHAL_RSC_GPIO, *pin, 0 };
        cyhal_hwmgr_free(&rsc);
#else
        _cyhal_utils_disconnect_and_free(*pin);
#endif
        *pin = CYHAL_NC_PIN_VALUE;
    }
}

bool _cyhal_utils_map_resources_equal_all(uint32_t count, ...)
{
    CY_ASSERT(count >= 2);

    va_list args;
    bool equal = true;
    const cyhal_resource_pin_mapping_t *curr;

    va_start(args, count);
    const cyhal_resource_pin_mapping_t *first = va_arg(args, const cyhal_resource_pin_mapping_t *);
    for (uint32_t i = 1; i < count; i++)
    {
        curr = va_arg(args, const cyhal_resource_pin_mapping_t *);
        equal &= _cyhal_utils_map_resources_equal(first, curr);
    }

    va_end(args);
    return equal;
}

uint32_t _cyhal_utils_convert_flags(const uint32_t map[], uint32_t count, uint32_t source_flags)
{
    uint32_t result_flags = 0;
    // Index 0 is the default value if nothing else is set.
    for (uint8_t i = 1; i < count; i++)
    {
        if (source_flags & (1 << (i - 1)))
            result_flags |= map[i];
    }
    if (0 == result_flags)
        result_flags = map[0];
    return result_flags;
}


#if defined(__cplusplus)
}
#endif
