/***************************************************************************//**
* \file cyhal_wdt_impl_common.h
*
* \brief
* Common code for WDT API implementations.
*
********************************************************************************
* \copyright
* Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company) or
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

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
* \cond INTERNAL
*/

typedef struct {
    uint32_t min_period_ms; // Minimum period in milliseconds that can be represented with this many ignored bits
    uint32_t round_threshold_ms; // Timeout threshold in milliseconds from which to round up to the minimum period
    // uint32_t pre_match_cycles; // The number of clock cycles in the first two full counter cycles (before the match value matters)
} _cyhal_wdt_ignore_bits_data_t;

/** \endcond */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
