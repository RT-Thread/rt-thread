/***************************************************************************//**
* \file cyhal_lptimer.h
*
* \brief
* Provides a high level interface for interacting with the Infineon Low-Power Timer.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
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

/**
* \addtogroup group_hal_lptimer LPTimer (Low-Power Timer)
* \ingroup group_hal
* \{
* High level interface for interacting with the low-power timer (LPTimer).
*
* LPTimer can operate in all possible low power modes. It can be used either to measure timing between events, or to perform
* some action after a specified interval of time.
* \section subsection_lptimer_features Features
* * Wake the device up from deepsleep
* * Configurable to create a free-running timer or generate periodic interrupts.
* * Configurable to update the match value of an already configured LPTimer set up to generate an interrupt on match.
* * Used for measuring time between events in free-running mode.
*
* \section subsection_lptimer_quickstart Quick Start
*
* \ref cyhal_lptimer_init can be used for a LPTimer initialization which resets all the clocking and prescaler registers, along with disabling the compare interrupt.
*
* See \ref subsection_lptimer_snippet_2.
*
* \section subsection_lptimer_snippets Code snippets
*
* \subsection subsection_lptimer_snippet_1 Snippet 1: LPTimer initialization with Default configuration
* The following snippet initializes a LPTimer in free running mode.
* \snippet hal_lptimer.c snippet_cyhal_lptimer_simple_init_def
*
* \subsection subsection_lptimer_snippet_2 Snippet 2: LPTimer interrupts
* The following snippet initializes a LPTimer and uses \ref cyhal_lptimer_set_match() to trigger an interrupt
* on match. Subsequent interrupts can be triggered at required times using \ref cyhal_lptimer_set_delay() called from the ISR.
* \snippet hal_lptimer.c snippet_cyhal_lptimer_interrupt
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_lptimer LPTimer HAL Results
 *  LPTimer specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Failed to configure power management callback */
#define CYHAL_LPTIMER_RSLT_ERR_PM_CALLBACK              \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_LPTIMER, 0))

/** Failed to execute not supported API */
#define CYHAL_LPTIMER_RSLT_ERR_NOT_SUPPORTED            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_LPTIMER, 1))

/** Timer is not enabled or it is not clocked */
#define CYHAL_LPTIMER_RSLT_ERR_DISABLED            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_LPTIMER, 2))

/** Bad argument. eg: null pointer */
#define CYHAL_LPTIMER_RSLT_ERR_BAD_ARGUMENT            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_LPTIMER, 3))

/**
 * \}
 */

/** LPTimer Information */
typedef struct cyhal_lptimer_info {
    uint32_t frequency_hz;      /**< Operating clock frequency the LPTimer is running on. */
    uint8_t  min_set_delay;     /**< Minimum permitted value for the delay parameter in \ref cyhal_lptimer_set_delay. */
    uint32_t max_counter_value; /**< Maximum value of the counter. */
} cyhal_lptimer_info_t;

/** LPTimer interrupt triggers */
typedef enum {
    CYHAL_LPTIMER_COMPARE_MATCH,
} cyhal_lptimer_event_t;

/** Handler for LPTimer interrupts */
typedef void (*cyhal_lptimer_event_callback_t)(void *callback_arg, cyhal_lptimer_event_t event);

/** Initialize the LPTimer
 *
 * Initialize or re-initialize the LPTimer. This resets all the
 * clocking and prescaler registers, along with disabling
 * the compare interrupt. Refer to the BSP for the clock source
 * for the LPTimer.
 *
 * @param[out] obj  Pointer to an LPTimer object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @return The status of the init request. On success it returns \ref CY_RSLT_SUCCESS.
 */

cy_rslt_t cyhal_lptimer_init(cyhal_lptimer_t *obj);

/** Deinitialize the LPTimer
 *
 * Powers down the LPTimer.
 * After calling this function no other LPTimer functions should be called except
 * cyhal_lptimer_init(). Calling any function other than init after freeing is
 * undefined.
 *
 * @param[inout] obj The LPTimer object
 */
void cyhal_lptimer_free(cyhal_lptimer_t *obj);

/** Reload/Reset the Low-Power timer.
 *
 * @param[in] obj   The LPTimer object
 * @return The status of the reload request. On success it returns \ref CY_RSLT_SUCCESS.
 */
cy_rslt_t cyhal_lptimer_reload(cyhal_lptimer_t *obj);

/** Deprecated. Call cyhal_lptimer_set_match instead. */
#define cyhal_lptimer_set_time cyhal_lptimer_set_match

/** Update the match/compare value
 *
 * Update the match value of an already configured LPTimer set up
 * to generate an interrupt on match. Note that this function does not
 * reinitialize the counter or the associated peripheral initialization
 * sequence.
 * \note This does not reset the counter.
 *
 * @param[in] obj   The LPTimer object
 * @param[in] ticks The tick value to match
 *
 * @return The status of the set_match request. On success it returns \ref CY_RSLT_SUCCESS.
 */
cy_rslt_t cyhal_lptimer_set_match(cyhal_lptimer_t *obj, uint32_t ticks);

/** Update the match/compare value
 *
 * Update the match value of an already configured LPTimer set up
 * to generate an interrupt on match delay from the current counter value.
 * Note that this function does not reinitialize the counter or the
 * associated peripheral initialization
 * sequence.
 * \note This does not reset the counter.
 *
 * @param[in] obj   The LPTimer object
 * @param[in] delay The ticks to wait. The minimum permitted delay value can be
 *                  queried using \ref cyhal_lptimer_get_info
 *
 * @return The status of the set_match request. On success it returns \ref CY_RSLT_SUCCESS.
 */
cy_rslt_t cyhal_lptimer_set_delay(cyhal_lptimer_t *obj, uint32_t delay);

/** Read the current tick
 *
 * If no rollover has occurred, the seconds passed since cyhal_lptimer_init() or cyhal_lptimer_set_time()
 * was called can be found by dividing the ticks returned by this function
 * by the frequency of the source clock (Refer to BSP Settings section in the kit's BSP API Reference Manual for details on the clock source for LPTimer).
 *
 * @param[in] obj    The LPTimer object
 * @return The timer's timer value in ticks
 */
uint32_t cyhal_lptimer_read(const cyhal_lptimer_t *obj);

/** Register a LPTimer match event handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_lptimer_enable_event occurs.
 *
 * @param[in] obj          The LPTimer object
 * @param[in] callback     The callback handler which will be invoked when the interrupt triggers
 * @param[in] callback_arg Generic argument that will be provided to the handler when called
 */
void cyhal_lptimer_register_callback(cyhal_lptimer_t *obj, cyhal_lptimer_event_callback_t callback, void *callback_arg);

/** Configure and Enable/Disable the LPTimer events
 *
 * When an enabled event occurs, the function specified by \ref cyhal_lptimer_register_callback will be called.
 *
 * @param[in] obj            The LPTimer object
 * @param[in] event          The LPTimer event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on event, False to turn off
 */
void cyhal_lptimer_enable_event(cyhal_lptimer_t *obj, cyhal_lptimer_event_t event, uint8_t intr_priority, bool enable);

/** Manually trigger the LPTimer interrupt.
 *
 * @param[in] obj      The LPTimer object
 */
void cyhal_lptimer_irq_trigger(cyhal_lptimer_t *obj);

/** Get information about the LPTimer.
 *
 * Provides information such as operating frequency, etc.
 *
 * @param[in]   obj     The LPTimer object.
 * @param[out]  info    Information about the LPtimer.
 */
void cyhal_lptimer_get_info(cyhal_lptimer_t *obj, cyhal_lptimer_info_t *info);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_LPTIMER_IMPL_HEADER
#include CYHAL_LPTIMER_IMPL_HEADER
#endif /* CYHAL_LPTIMER_IMPL_HEADER */

/** \} group_hal_lptimer */
