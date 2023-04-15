/***************************************************************************//**
* \file cyhal_system.h
*
* \brief
* Provides a high level interface for interacting with the Infineon power
* management and system clock configuration. This interface abstracts out the
* chip specific details. If any chip specific functionality is necessary, or
* performance is critical the low level functions can be used directly.
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
* \addtogroup group_hal_system System
* \ingroup group_hal
* \{
* High level interface for interacting with reset and delays.
*
* \section section_system_features Features
* This driver provides three categories of functionality:
* * Ability to get the last reset reason.
* * Ability to delay for a period of time.
* * The ability to disable interrupts during a critical section.
*
* \section subsection_system_quickstart Quick Start
* * \ref cyhal_system_critical_section_enter and \ref
* cyhal_system_critical_section_exit are used to enable/disable global interrupts
* * \ref cyhal_system_delay_ms and \ref cyhal_system_delay_us are delay functions
* used to halt the CPU exectution for a specified period of time
* * \ref cyhal_system_get_reset_reason gets the cause of latest system reset and
* \ref cyhal_system_clear_reset_reason clears the reset cause registers
*
* \section subsection_system_codesnippet Code Snippets
* \subsection subsection_system_snippet1 Snippet 1: Critical Section
* Critical section is a portion in the code where all active interrupts are
* disabled. This is usually provided in places where the code execution must not
* be disturbed by an interrupt. An example is a firmware controlled communication
* protocol where timing of each byte must be maintained and any interrupt might
* cause loss of data. <br>
* \ref cyhal_system_critical_section_enter returns the current state of interrupts
* which denote the active interrupts in the system. This must be passed as argument
* to \ref cyhal_system_critical_section_exit while exiting the critical section.
* \snippet hal_system.c snippet_cyhal_system_critical_section
*
* \subsection subsection_system_snippet2 Snippet 2: Reset reason
* \ref cyhal_system_get_reset_reason must be called at the beginning of the main to
* determine the reason for reset. The return parameters are present in \ref
* cyhal_reset_reason_t.
* \snippet hal_system.c snippet_cyhal_system_reset_reason
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_system SYSTEM HAL Results
 *  SYSTEM specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Functionality not supported on the current platform */
#define CYHAL_SYSTEM_RSLT_ERR_NOT_SUPPORTED           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSTEM, 0))
/** Incorrect argument passed into a function */
#define CYHAL_SYSTEM_RSLT_BAD_ARGUMENT           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSTEM, 1))
/** Failed to reset the device */
#define CYHAL_SYSTEM_RSLT_FAILED_RESET           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSTEM, 2))

/**
 * \}
 */

/** Flags enum of possible system reset causes */
typedef enum
{
    CYHAL_SYSTEM_RESET_NONE            = 0,      /**< No cause */
    CYHAL_SYSTEM_RESET_WDT             = 1 << 0, /**< A watchdog timer (WDT) reset has occurred */
    CYHAL_SYSTEM_RESET_ACTIVE_FAULT    = 1 << 1, /**< The fault logging system requested a reset from its Active logic. */
    CYHAL_SYSTEM_RESET_DEEPSLEEP_FAULT = 1 << 2, /**< The fault logging system requested a reset from its Deep-Sleep logic. */
    CYHAL_SYSTEM_RESET_SOFT            = 1 << 3, /**< The CPU requested a system reset through it's SYSRESETREQ. */
    CYHAL_SYSTEM_RESET_HIB_WAKEUP      = 1 << 4, /**< A reset has occurred due to a a wakeup from hibernate power mode. */
    CYHAL_SYSTEM_RESET_WCO_ERR         = 1 << 5, /**< A reset has occurred due to a watch-crystal clock error */
    CYHAL_SYSTEM_RESET_SYS_CLK_ERR     = 1 << 6, /**< A reset has occurred due to a system clock error */
    CYHAL_SYSTEM_RESET_PROTECTION      = 1 << 7, /**< A reset has occurred due to a protection violation */
} cyhal_reset_reason_t;

/** Function pointer for IRQ handlers ( \ref cyhal_system_set_isr). */
typedef void (* cyhal_irq_handler)(void);

/** Enter a critical section
 *
 * Disables interrupts and returns a value indicating whether the interrupts were previously
 * enabled.
 *
 * @return Returns the state before entering the critical section. This value must be provided
 * to \ref cyhal_system_critical_section_exit() to properly restore the state
 *
 * See \ref subsection_system_snippet1 for code snippet on critical section
 */
uint32_t cyhal_system_critical_section_enter(void);

/** Exit a critical section
 *
 * Re-enables the interrupts if they were enabled before
 *  cyhal_system_critical_section_enter() was called. The argument should be the value
 *  returned from \ref cyhal_system_critical_section_enter().
 *
 * @param[in] old_state The state of interrupts from cyhal_system_critical_section_enter()
 *
 * See \ref subsection_system_snippet1 for code snippet on critical section
 */
void cyhal_system_critical_section_exit(uint32_t old_state);

/**
 * Requests that the current operation delays for at least the specified length of time.
 * If this is running in an RTOS aware environment (COMPONENTS+=RTOS_AWARE) or
 * (DEFINES+=CY_RTOS_AWARE) it will attempt to have the RTOS suspend the current task
 * so others can continue to run. If this is not run under an RTOS it will then defer to
 * the standard system delay which is likely to be a busy loop.
 * If this is part of an application that is build with RTOS awareness, but the delay
 * should not depend on the RTOS for whatever reason, use cyhal_system_delay_us() with
 * the appropriate 1000x multiplier to the delay time.
 *
 * @param[in] milliseconds The number of milliseconds to delay for
 * @return Returns CY_RSLT_SUCCESS if the delay request was successful, otherwise error
 */
cy_rslt_t cyhal_system_delay_ms(uint32_t milliseconds);

/**
 * Requests that the current operation delay for at least the specified number of
 * micro-seconds. This will generally keep the processor active in a loop for the
 * specified length of time. If this is running under an RTOS, it will NOT attempt to
 * run any other RTOS tasks, however if the scheduler or a high priority interrupt
 * comes it they can take over anyway.
 *
 * @param[in] microseconds The number of micro-seconds to delay for
 */
void cyhal_system_delay_us(uint16_t microseconds);

/** Gets the cause of the latest reset or resets that occurred in the system.
 *
 * @return Returns an enum of flags with the cause of the last reset(s)
 *
 * Refer \ref subsection_system_snippet2 for code snippet on cyhal_system_get_reset_reason
 */
cyhal_reset_reason_t cyhal_system_get_reset_reason(void);

/** Clears the reset cause registers. This should be done after calling
 * \ref cyhal_system_get_reset_reason to make sure the reason does not persist between resets.
 */
void cyhal_system_clear_reset_reason(void);

/** Resets the device
 *
 * The mechanism used to reset the device is implementation-specific and the reset
 * behavior differs between devices.
 *
 * @return This function does not return if successful. Otherwise an error is returned.
 */
cy_rslt_t cyhal_system_reset_device(void);

/** Registers the specified handler as the callback function for the specified irq_num with the
 * given priority. For devices that mux interrupt sources into mcu interrupts, the irq_src defines
 * the source of the interrupt.
 *
 * @param[in] irq_num   The MCU interrupt number to register the handler for.
 * @param[in] irq_src   The interrupt source that feeds the MCU interrupt. For devices that have a
 * 1:1 mapping between interrupt sources and MCU interrupts this should be the same as the irq_num.
 * @param[in] priority  The MCU interrupt priority.
 * @param[in] handler   The function pointer to call when the interrupt is triggered.
 * @return Returns CY_RSLT_SUCCESS if the set_isr request was successful, otherwise an error
 */
cy_rslt_t cyhal_system_set_isr(int32_t irq_num, int32_t irq_src, uint8_t priority, cyhal_irq_handler handler);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_SYSTEM_IMPL_HEADER
#include CYHAL_SYSTEM_IMPL_HEADER
#endif /* CYHAL_SYSTEM_IMPL_HEADER */

/** \} group_hal_system */
