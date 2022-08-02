/***************************************************************************//**
* \file cyhal_wdt.h
*
* \brief
* Provides a high level interface for interacting with the Watchdog Timer.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
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

/**
* \addtogroup group_hal_wdt WDT (Watchdog Timer)
* \ingroup group_hal
* \{
* High level interface to the Watchdog Timer (WDT).
*
* The WDT can be used for recovering from a CPU or firmware failure.
* The WDT is initialized with a timeout interval. Once the WDT is started, \ref
* cyhal_wdt_kick must be called at least once within each timeout interval to
* reset the count. In case the firmware fails to do so, it is considered to be a
* CPU crash or firmware failure and the device will be reset.
*
*\section subsection_wdt_features Features
* WDT resets the device if the WDT is not "kicked" using \ref cyhal_wdt_kick
* within the configured timeout interval.
*
* \section subsection_wdt_quickstart Quick Start
*
* \ref cyhal_wdt_init() is used to initialize the WDT by providing the WDT object
* (**obj**) and the timeout (**timeout_ms**) value in milliseconds.
* The timeout parameter can have a minimum value of 1ms. The maximum value of the
* timeout parameter can be obtained using the cyhal_wdt_get_max_timeout_ms().
*
* \section subsection_wdt_snippet Code Snippet
*
* \subsection subsection_wdt_snippet1 Snippet 1: Initialize the WDT and kick periodically
* The following snippet initializes the WDT and illustrates how to reset the WDT within
* the timeout interval.
* \snippet hal_wdt.c snippet_cyhal_wdt_init_and_reset
*/

#pragma once

#include "cyhal_hwmgr.h"
#include "cy_result.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_wdt WDT HAL Results
 *  WDT specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** WDT timeout out of range */
#define CY_RSLT_WDT_INVALID_TIMEOUT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_WDT, 0))
/** WDT already initialized */
#define CY_RSLT_WDT_ALREADY_INITIALIZED                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_WDT, 1))

/**
 * \}
 */

/** Initialize and start the WDT
*
* \note The specified timeout must be at least 1ms and at most the WDT's maximum timeout (see cyhal_wdt_get_max_timeout_ms()).
*
 * @param[out] obj  Pointer to a WDT object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
* @param[inout] timeout_ms The time in milliseconds before the WDT times out (1ms - max) (see cyhal_wdt_get_max_timeout_ms())
* @return The status of the init request
*
* Returns \ref CY_RSLT_SUCCESS if the operation was successfull.
*/
cy_rslt_t cyhal_wdt_init(cyhal_wdt_t *obj, uint32_t timeout_ms);

/** Free the WDT
*
* Powers down the WDT. Releases object (obj).
* After calling this function no other WDT functions should be called except
* cyhal_wdt_init().
*
* @param[inout] obj The WDT object
*/
void cyhal_wdt_free(cyhal_wdt_t *obj);

/** Resets the WDT
*
* This function must be called periodically to prevent the WDT from timing out and resetting the device.
*
* See \ref subsection_wdt_snippet1
*
* @param[inout] obj The WDT object
*/
void cyhal_wdt_kick(cyhal_wdt_t *obj);

/** Start (enable) the WDT
*
* @param[inout] obj The WDT object
*/
void cyhal_wdt_start(cyhal_wdt_t *obj);

/** Stop (disable) the WDT
*
* @param[inout] obj The WDT object
*/
void cyhal_wdt_stop(cyhal_wdt_t *obj);

/** Get the WDT timeout
*
* Gets the configured time, in milliseconds, before the WDT times out.
*
* @param[in] obj The WDT object
* @return The time in milliseconds before the WDT times out
*/
uint32_t cyhal_wdt_get_timeout_ms(cyhal_wdt_t *obj);

/** Gets the maximum WDT timeout in milliseconds
*
* @return The maximum timeout for the WDT
*/
uint32_t cyhal_wdt_get_max_timeout_ms(void);

/** Check if WDT is enabled
 *
 * This will return true after \ref cyhal_wdt_start is called. It will return false before the WDT is started, or after \ref cyhal_wdt_stop is called.
 *
 * @param[in] obj The WDT object
 * @return The status of WDT is_enabled request */
bool cyhal_wdt_is_enabled(cyhal_wdt_t *obj);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_WDT_IMPL_HEADER
#include CYHAL_WDT_IMPL_HEADER
#endif /* CYHAL_WDT_IMPL_HEADER */

/** \} group_hal_wdt */
