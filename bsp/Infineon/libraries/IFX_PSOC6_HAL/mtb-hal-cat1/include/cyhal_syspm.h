/***************************************************************************//**
* \file cyhal_syspm.h
*
* \brief
* Provides a high level interface for interacting with the Infineon power
* management configuration. This interface abstracts out the
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
* \addtogroup group_hal_syspm System Power Management
* \ingroup group_hal
* \{
* Interface for changing power states and restricting when they are allowed.
*
* Power management is handled both at a system level and at a peripheral driver
* level. The system wide API (this) allows the user to interact with the product
* as a whole. Additionally, each peripheral keeps track of what its state is and
* whether it can safely move to a new state while still maintaining any current
* operations. To initialize the system wide power management, \ref cyhal_syspm_init
* should be called as part of the initial device startup.
*
* At the System level, the APIs are intended to allow the application to specify
* exactly what is happening. It can request changes to both the MCU Power State
* as well as the System Wide Power State. There are three supported MCU Power
* States:
* * Active - This is the normal operating state of the MCU
* * Sleep - In this state the MCU is no longer running. It can be woken up again
* from an interrupt. This state is reached by calling \ref cyhal_syspm_sleep.
* * Deep Sleep - In this state the MCU is no longer running. It can only be woken
* up by select interrupts. This state is reached by calling \ref
* cyhal_syspm_deepsleep.
* <p>Additionally, there are three supported system states:
* * Normal (\ref CYHAL_SYSPM_SYSTEM_NORMAL) - This is a normal operating state
* for the device. This is exposed by \ref cyhal_syspm_set_system_state.
* * Low (\ref CYHAL_SYSPM_SYSTEM_LOW) - This is a lower power operating state
* that may be supported by the device. This state often imposes specific
* requirements on clock speeds and voltage levels. See the device specific
* documentation for any device specific requirements for this mode, or whether
* it is even supported. If the device supports this mode, it is exposed by
* \ref cyhal_syspm_set_system_state.
* * Hibernate - This is the lowest available power state. In this state most of
* the chip is powered down. It has a very limited number of wakeup sources, and
* may require the device to reboot in order to come back up. It can be accessed
* by calling \ref cyhal_syspm_hibernate.

* Any time a power state transition is requested a series of callbacks are invoked.
* This allows peripherals, or other parts of the application, to confirm they are
* not currently doing something that would not work in the requested power state.
* HAL Peripheral drivers automatically register these callbacks when they are
* initialized. The application also has the option to register a callback
* function(s) to be called on requested state transitions by callling \ref
* cyhal_syspm_register_callback. If registered, the application level callbacks
* are invoked first. This gives the application a chance stop any peripherals, if
* appropriate, to ensure the power transition can actually happen. Alternatively
* it can directly reject the transition. Each callback registered can specify
* the exact set of states ( \ref cyhal_syspm_callback_state_t ) that it should
* be called for. Each callback is invoked multiple times as part of the transition
* process as defined by \ref cyhal_syspm_callback_mode_t.
*
* At any point the code can lock the ability to enter deep sleep by calling \ref
* cyhal_syspm_lock_deepsleep. This should be done in critical blocks that need to
* continue remain active. When the critical work is complete, and the lock is no
* longer needed, it can be released by calling \ref cyhal_syspm_unlock_deepsleep.
* The lock is a counter with a max count of USHRT_MAX. It must be locked/unlocked
* an equal number of times before the device is actually able to enter deep sleep.
*
* All peripherals are expected to operate in the default Active/Normal power
* state. Some peripherals (primarily analog) can operate in lower power states as
* well. These drivers will operate in all power states that the hardware supports.
*
* When power transitions are requested each type of peripheral has a default
* behavior. Peripherals that can continue to operate in the requested power mode
* do not interfere. Peripherals that are not currently active allow the transition,
* but make sure they restore their state if needed for when the device comes back.
* Peripherals that are active and cannot continue to work in the requested power
* state will block the transition.
*
* \note The power management functionality available depends on the availability
* of the features in the hardware. For detailed information about exactly what is
* supported on each device, refer to the Device Datasheet or Technical Reference
* Manual (TRM).

* \section section_syspm_features Features
* This driver provides control over multiple different types of power management
* and when those transitions are allowed:
* * Change CPU Power State: APIs to allow changing the current CPU state into
* one of the lower power CPU states (SLEEP, DEEPSLEEP)
* * Change System Power State: An API allows for changing the system wide power
* state between one of states (NORMAL, LOW)
* - Hibernate: An API that allows to set the hibernate
* wakeup source and set the system state to Hibernate.
* * General Purpose Power State Transition Callback: APIs allow for
* registering/unregistering a callback function to be notified when various power
* state transitions happen. If registered, the application can do anything necessary
* at power transitions. It can even prevent the transition if need-be.
* * Peripheral Specific Power State Transition Callback: APIs allow for
* registering/unregistering a callback function to be called when a peripheral with
* a CUSTOM power mode strategy exists and a power mode transition is requested.
* This allows the application to customize when it is OK for the peripheral to enter
* a low power state.
* - Lock DeepSleep: APIs to prevent/allow the CPU from going to deep sleep. This
* is a convenience API rather than needing to implement a full Transition Callback
* handler.
*
* \section section_syspm_quickstart Quick Start
*
* Unlike most HAL drivers this does not require initializing an instance object. The
* APIs provided here can be called at anytime. See the snippets below for examples
* of how to use this driver.
*
* \section section_syspm_snippets Code Snippets
*
* \subsection subsection_syspm_snippet_1 Snippet 1: Simple deep sleep locking
* The following snippet shows how to use the deep sleep locking APIs to restrict
* when the device can enter deep sleep. In between the lock/unlock calls any
* attempt to change power modes will automatically be canceled.
* \snippet hal_syspm.c snippet_cyhal_syspm_simple_locking
*
* \subsection subsection_syspm_snippet_2 Snippet 2: Calling different power state functions
* The following snippet shows the different functions that exist to change power states
* on the device and how they can each be called.
* \snippet hal_syspm.c snippet_cyhal_syspm_power_transitions
*
* \subsection subsection_syspm_snippet_3 Snippet 3: Using callbacks for application power management
* The following snippet shows how to use the callback mechanisms to manage whether
* it is safe to enter low power modes.
* \snippet hal_syspm.c snippet_cyhal_syspm_app_callback
*/
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_general_types.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_syspm SYSPM HAL Results
 *  SYSPM specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Incorrect argument passed into a function. */
#define CYHAL_SYSPM_RSLT_BAD_ARGUMENT               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSPM, 0))
/** Driver was unable to be initialized. */
#define CYHAL_SYSPM_RSLT_INIT_ERROR                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSPM, 1))
/** Failed to register callback */
#define CYHAL_SYSPM_RSLT_CB_REGISTER_ERROR          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSPM, 2))
/** Power Management transition is pending, data cannot be transferred */
#define CYHAL_SYSPM_RSLT_ERR_PM_PENDING             \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSPM, 3))
/** Functionality not supported on the current platform */
#define CYHAL_SYSPM_RSLT_ERR_NOT_SUPPORTED           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSPM, 4))
/** Deepsleep has been locked */
#define CYHAL_SYSPM_RSLT_DEEPSLEEP_LOCKED           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SYSPM, 5))

/**
 * \}
 */

/** \cond INTERNAL */
/** Sentinel value to indicate end of callback list */
#define CYHAL_SYSPM_END_OF_LIST ((cyhal_syspm_callback_data_t*)0x789)
/** \endcond */

/** Enumeration of the system wide power modes. These modes are device specifc and
 * may not be supported on all devices. Refer to the device specific documentation
 * or the Data Sheet to determine what is allowed. Devices that do support these
 * modes may have requirements for adjusting system settings such as clocks or
 * voltage levels before transition.
 */
typedef enum
{
    CYHAL_SYSPM_SYSTEM_NORMAL,      /**< Normal Mode. */
    CYHAL_SYSPM_SYSTEM_LOW,         /**< Low Power Mode. */
} cyhal_syspm_system_state_t;

/** Flags enum for the hibernate wakeup sources.
 * \note Not all wakeup sources are valid on devices. Refer to the datasheet for
 * device specifics.
 */
typedef enum
{
    CYHAL_SYSPM_HIBERNATE_LPCOMP0_LOW   = 0x01U,    /**< Wake on a low logic level for the LPComp0. */
    CYHAL_SYSPM_HIBERNATE_LPCOMP0_HIGH  = 0x02U,    /**< Wake on a high logic level for the LPComp0. */
    CYHAL_SYSPM_HIBERNATE_LPCOMP1_LOW   = 0x04U,    /**< Wake on a low logic level for the LPComp1. */
    CYHAL_SYSPM_HIBERNATE_LPCOMP1_HIGH  = 0x08U,    /**< Wake on a high logic level for the LPComp1. */
    CYHAL_SYSPM_HIBERNATE_RTC_ALARM     = 0x10U,    /**< Configure the RTC alarm as wakeup source. */
    CYHAL_SYSPM_HIBERNATE_WDT           = 0x20U,    /**< Configure the WDT interrupt as wakeup source. */
    CYHAL_SYSPM_HIBERNATE_PINA_LOW      = 0x40U,    /**< Configure a low logic level for the first wakeup-pin.
                                                        See device datasheet for specific pin. */
    CYHAL_SYSPM_HIBERNATE_PINA_HIGH     = 0x80U,    /**< Configure a high logic level for the first wakeup-pin.
                                                        See device datasheet for specific pin. */
    CYHAL_SYSPM_HIBERNATE_PINB_LOW      = 0x100U,   /**< Configure a low logic level for the second wakeup-pin.
                                                        See device datasheet for specific pin. */
    CYHAL_SYSPM_HIBERNATE_PINB_HIGH     = 0x200U    /**< Configure a high logic level for the second wakeup-pin.
                                                        See device datasheet for specific pin. */
} cyhal_syspm_hibernate_source_t;

/** Supply voltages whose levels can be specified and queried via \ref cyhal_syspm_set_supply_voltage and
  * \ref cyhal_syspm_get_supply_voltage, respectively.
  *
  * \note Not all supplies which are present are included here. This enum only contains the voltage supplies
  * whose values are relevant to the operation of one or more HAL drivers.
  */
typedef enum
{
    CYHAL_VOLTAGE_SUPPLY_VDDA = 0u,                       //!< VDDA - Analog supply voltage
    CYHAL_VOLTAGE_SUPPLY_MAX  = CYHAL_VOLTAGE_SUPPLY_VDDA //!< Alias for the highest value in this enum
} cyhal_syspm_voltage_supply_t;


/**
 * Performs any system wide power management initialization that is needed for future operations.
 * This can include things like unlocking IOs that might have been frozen when entering a low
 * power state or registering callback functions that are necessary to allow notifications of
 * power events. This should be called as part of initializing the device in a Board Support Package
 * (BSP).
 *
 * @return Returns CY_RSLT_SUCCESS if the processor successfully entered the hibernate mode,
 * otherwise error.
 */
cy_rslt_t cyhal_syspm_init(void);

 /** Sets the system mode to hibernate.
 *
 * This function configures the sources to wake up the device from hibernate mode
 * and then sets the system to hibernate mode.
 *
 * In hibernate mode, all internal supplies are off and no internal state is retained.
 *
 * Sources can be wakeup pins, LPComparators, Watchdog (WDT) interrupt, or a Real-Time
 * clock (RTC) alarm (interrupt). Wakeup from system hibernate always results in a device
 * reset and normal boot process.
 *
 * Wakeup pins:
 *
 * A wakeup is supported by pins with programmable polarity. These pins
 * are typically connected to the GPIO pins or on-chip peripherals under some
 * conditions. See device datasheet to check if this feature is supported and for specific
 * pin connections. Setting the wakeup pin to this level will cause a wakeup from
 * system hibernate mode.
 *
 * LPComparators:
 *
 * A wakeup is supported by LPComps with programmable polarity.
 * Setting the LPComp to this level will cause a wakeup from system hibernate
 * mode.
 *
 * Watchdog Timer:
 *
 * A wakeup is performed by a WDT interrupt.
 *
 * Real-time Clock:
 *
 * A wakeup is performed by the RTC alarm.
 *
 * For information about hibernate behavior, wakeup sources and their assignment in specific
 * devices, refer to the appropriate device TRM.
 *
 * @param[in] wakeup_source
 * The source to be configured as a wakeup source from the system hibernate power mode,
 * see @ref cyhal_syspm_hibernate_source_t. The input parameter values can be ORed.
 * For example, if you want to enable LPComp0 (active high) and WDT, call this function:
 * cyhal_syspm_hibernate(CYHAL_SYSPM_HIBERNATE_LPCOMP0_HIGH | CYHAL_SYSPM_HIBERNATE_WDT).
 *
 * @warning Do not call this function with different polarity levels for the same
 * wakeup source. For example, do not call a function like this:
 * cyhal_syspm_hibernate(CYHAL_SYSPM_HIBERNATE_LPCOMP0_LOW | CYHAL_SYSPM_HIBERNATE_LPCOMP0_HIGH);
 *
 * @return Returns CY_RSLT_SUCCESS if the processor successfully entered the hibernate mode,
 * otherwise error.
 */
cy_rslt_t cyhal_syspm_hibernate(cyhal_syspm_hibernate_source_t wakeup_source);

/** Set the system-wide state of the device. This is used to change the power state
 * within the Active power mode. \ref cyhal_syspm_get_system_state can be used to
 * get the current state.
 * \note Not all devices support different states within the Active power mode. If
 * the device does not support changing state, an error will be returned.
 *
 * @param[in] state System wide state.
 *
 * @return Returns CY_RSLT_SUCCESS if the processor successfully entered the requested system state,
 * otherwise error.
 */
cy_rslt_t cyhal_syspm_set_system_state(cyhal_syspm_system_state_t state);

/** Gets the system-wide state of the device. States can be changed by calling
 * \ref cyhal_syspm_set_system_state.
 * \note Not all devices support different states within the Active power mode. If
 * the device does not support changing state, this will return \ref
 * CYHAL_SYSPM_SYSTEM_NORMAL.
 * @return Returns the current system-wide power state of the device.
 */
cyhal_syspm_system_state_t cyhal_syspm_get_system_state(void);

/** Register the specified handler with the power manager to be notified of power
 * state changes. This is intended for application wide decisions. Peripherals handle
 * their ability to perform power transitions internally. This callback will be called
 * before any of the peripheral callbacks for \ref CYHAL_SYSPM_CHECK_READY and
 * \ref CYHAL_SYSPM_BEFORE_TRANSITION. This callback will be called after all peripheral
 * callback for \ref CYHAL_SYSPM_CHECK_FAIL and \ref CYHAL_SYSPM_AFTER_TRANSITION.
 * \note The callback will be executed from a critical section
 *
 * @param[in] callback_data The data for the callback to register
 */
void cyhal_syspm_register_callback(cyhal_syspm_callback_data_t *callback_data);

/** Removes the registered handler from the power manager so no future notifications are made.
 *
 * * @param[in] callback_data The data for the callback to unregister
*/
void cyhal_syspm_unregister_callback(cyhal_syspm_callback_data_t *callback_data);

/** Set CPU to sleep mode.
 *
 * @return  Returns CY_RSLT_SUCCESS if the processor successfully entered the sleep mode ,
 * otherwise error.
 */
cy_rslt_t cyhal_syspm_sleep(void);

/** Set CPU to deep sleep mode.
 *
 * @return  Returns CY_RSLT_SUCCESS if the processor successfully entered the deep sleep mode,
 * otherwise error.
 */
cy_rslt_t cyhal_syspm_deepsleep(void);

/** Lock deep sleep.
 *
 * This function prevents the CPU from going to deep sleep. The lock is implemented as a counter
 * from 0 to USHRT_MAX. Each call to this function increments the counter by 1.
 * \ref cyhal_syspm_unlock_deepsleep must be called an equal number of times to fully unlock.
 * Deepsleep will only be allowed when the counter is equal to 0.
 */
void cyhal_syspm_lock_deepsleep(void);

/** Unlock deep sleep.
 *
 * This function decrements the lock counter by 1 and must be called an equal number of times as
 * @ref cyhal_syspm_lock_deepsleep is called to fully unlock. Deepsleep will only be allowed
 * when the counter is equal to 0.
 */
void cyhal_syspm_unlock_deepsleep(void);

/** Timed deep-sleep without system timer.
 *
 * Provides a way to deep-sleep for a desired number of milliseconds(ms) with the system timer disabled.
 * The system timer is disabled before sleeping and a low power timer is setup to wake
 * the device from deep-sleep after the desired number of ms have elapsed.
 *
 * @note The actual ms in the best case will be 1 ms less than the desired time to
 * prevent the device from over-sleeping due to low clock accuracy.
 *
 * @param[in]   obj         Pre-Initialized LPTimer object.
 * @param[in]   desired_ms  Desired number of ms to deep-sleep.
 * @param[out]  actual_ms   Actual number of ms that was spent in deep-sleep.
 *                          This value can range from 0 to desired_ms - 1
 *                          depending on how long the device was able to deep-sleep.
 * @return The status of the deep-sleep request.
 */
cy_rslt_t cyhal_syspm_tickless_deepsleep(cyhal_lptimer_t *obj, uint32_t desired_ms, uint32_t *actual_ms);

/** Timed sleep without system timer.
 *
 * Provides a way to sleep for a desired number of milliseconds(ms) with the system timer disabled.
 * The system timer is disabled before sleeping and a low power timer is setup to wake
 * the device from sleep after the desired number of ms have elapsed.
 *
 * @note The actual ms in the best case will be 1 ms less than the desired time to
 * prevent the device from over-sleeping due to low clock accuracy.
 *
 * @param[in]   obj         Pre-Initialized LPTimer object.
 * @param[in]   desired_ms  Desired number of ms to sleep.
 * @param[out]  actual_ms   Actual number of ms that was spent in sleep.
 *                          This value can range from 0 to desired_ms - 1
 *                          depending on how long the device was able to sleep.
 * @return The status of the sleep request.
 */
cy_rslt_t cyhal_syspm_tickless_sleep(cyhal_lptimer_t *obj, uint32_t desired_ms, uint32_t *actual_ms);

/** Informs the system of the current voltage level on the specified supply.
  *
  * This is generally expected to be set once at system startup, but it may be set repeatedly during
  * runtime if operating conditions change.
  * Once set, this value can be queried via \ref cyhal_syspm_get_supply_voltage.
  *
  * \note This only informs the system of the voltage level. It does not alter any of the device operating conditions.
  *
  * @param supply The supply whose voltage is being specified.
  * @param mvolts The voltage level on the specified supply, in millivolts.
  */
void cyhal_syspm_set_supply_voltage(cyhal_syspm_voltage_supply_t supply, uint32_t mvolts);

/** Retrieves the current voltage level on the specified supply, as set in \ref cyhal_syspm_set_supply_voltage.
  *
  * \note This only returns the value provided to \ref cyhal_syspm_set_supply_voltage. It does not perform any
  * measurements of the current supply level.
  *
  * @param supply The supply whose voltage is being specified.
  * @return The voltage level on the specified supply, in millivolts. If the voltage has not been specified,
  * returns 0.
  */
uint32_t cyhal_syspm_get_supply_voltage(cyhal_syspm_voltage_supply_t supply);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_SYSPM_IMPL_HEADER
#include CYHAL_SYSPM_IMPL_HEADER
#endif /* CYHAL_SYSTEM_IMPL_HEADER */

/** \} group_hal_system */
