/*******************************************************************************
* File Name: cyhal_clock_impl.h
*
* Description:
* Device specific implementation for clocks API.
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

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * \ingroup group_hal_impl_adc
 * \{
 * \section group_hal_impl_adc_interconnect Interconnect
 * In PSoCâ„¢ each ADC has a single input trigger which, when activated, will
 * initiate an ADC scan. Each ADC also has an output trigger which will be
 * activated when a scan is completed.
 */

/** Convert all samples to be averaged back to back, before proceeding to the next channel.
  * This is the default behavior. */
#define CYHAL_ADC_AVG_MODE_SEQUENTIAL (1u << (CYHAL_ADC_AVG_MODE_MAX_SHIFT + 1u))

#if defined(CY_IP_MXS40PASS_SAR_INSTANCES)
/** Convert one sample to be averaged per scan, interleaved with the rest of the channels.
  * This maintains a consistent spacing of samples regardless of whether samples are averaged
  * or not. However, it also means that a new value will only be provided once every n scans,
  * where n is the configured averaging count. At the conclusion of any other scan, the read
  * operation will return the same value as the previous scan. The application is responsible
  * for keeping tracks of the scans on which the value will be updated.
  * \note This mode is incompatible with \ref CYHAL_ADC_AVG_MODE_ACCUMULATE
  * \note In this mode, the averaging count should be set to less than 16 to avoid overflowing
  * the working register that is used to accumulate intermediate results.
  */
#define CYHAL_ADC_AVG_MODE_INTERLEAVED (1u << (CYHAL_ADC_AVG_MODE_MAX_SHIFT + 2u))
#endif

/** \} group_hal_impl_adc */

#if defined(__cplusplus)
}
#endif
