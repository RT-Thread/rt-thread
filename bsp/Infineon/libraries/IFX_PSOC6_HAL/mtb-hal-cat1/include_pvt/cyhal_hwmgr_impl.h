/***************************************************************************//**
* \file cyhal_hwmgr_impl.h
*
* Description:
* This file provides internal device specific hardware manager utilities.
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

#include "cyhal_hw_resources.h"
#include "cyhal_triggers.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** Function pointer for use with _cyhal_hwmgr_reserve_instance for getting the input
 * destination of the specified hardware type given a specific block/channel */
typedef cyhal_dest_t (*_cyhal_hwmgr_get_input_dest_t)(uint8_t block_num, uint8_t channel_num);
/** Function pointer for use with _cyhal_hwmgr_reserve_instance for getting the output
 * source of the specified hardware type given a specific block/channel */
typedef cyhal_source_t (*_cyhal_hwmgr_get_output_source_t)(uint8_t block_num, uint8_t channel_num);


/** Attempts to reserve a resource of the specified \p type that is able to connect to the
 * \p src and \p dest signals if provided.
 * @param[in] type      The type of resource to reserve
 * @param[in] src       The optional input source to the resource type to be reserved
 * @param[in] dest      The optional destination target of the resource type to be reserved
 * @param[in] get_src   Function to use to get a source for a specific block/channel
 * @param[in] get_dest  Function to use to get a destination for a specific block/channel
 * @param[out] obj      The reserved resource if successful
 * @return The status of the reservation request
 */
cy_rslt_t _cyhal_hwmgr_allocate_with_connection(cyhal_resource_t type, const cyhal_source_t *src, const cyhal_dest_t *dest,
    _cyhal_hwmgr_get_output_source_t get_src, _cyhal_hwmgr_get_input_dest_t get_dest, cyhal_resource_inst_t *obj);

#if defined(__cplusplus)
}
#endif
