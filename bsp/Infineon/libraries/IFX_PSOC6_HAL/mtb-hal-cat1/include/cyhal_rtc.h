/***************************************************************************//**
* \file cyhal_rtc.h
*
* \brief
* Provides a high level interface for interacting with the Real Time Clock on
* Cypress devices.  This interface abstracts out the chip specific details.
* If any chip specific functionality is necessary, or performance is critical
* the low level functions can be used directly.
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
* \addtogroup group_hal_rtc RTC (Real-Time Clock)
* \ingroup group_hal
* \{
* High level interface for interacting with the real-time clock (RTC).
*
* The real time clock provides tracking of the current time and date, as
* well as the ability to trigger a callback at a specific time in the future.
*
* \section section_rtc_features Features
* * Configurable interrupt and callback assignment on RTC event \ref cyhal_rtc_event_t
* * Set alarm for a specific time and date \ref cyhal_rtc_set_alarm
* * Daylight Savings Time adjustment
*
* \section section_rtc_quickstart Quick Start
*
* Initialise the RTC using \ref cyhal_rtc_init. Set the current time and date using \ref cyhal_rtc_write. <br>
* See \ref subsection_rtc_snippet_1 to initialize RTC, read and write current date and time to the RTC peripheral.
* See \ref subsection_rtc_snippet_2 to set an alarm event on a specific time and date.
*
* \section section_rtc_snippets Code snippets
* \subsection subsection_rtc_snippet_1 Snippet 1: Initialize RTC, write and read current time and date
* The following code snippet initialises the RTC using the \ref cyhal_rtc_init. The current date and time are set using \ref cyhal_rtc_write.
* The current date and time is read from the RTC using \ref cyhal_rtc_read. The time structure <b> tm </b>, contains the calendar date and time which
* are broken down into its components. This structure is declared in standard C library time.h which is included by HAL.
* \snippet hal_rtc.c snippet_cyhal_rtc_read_write_data_time
*
* \subsection subsection_rtc_snippet_2 Snippet 2: RTC Alarm using Callbacks
*  The following code snippet configures the RTC to trigger an alarm event on a specified date and time using \ref cyhal_rtc_set_alarm.
*  A callback is registered to handle the alarm event using \ref cyhal_rtc_register_callback.
* \snippet hal_rtc.c snippet_cyhal_set_alarm_callback
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_rtc RTC HAL Results
 *  RTC specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** RTC not initialized */
#define CY_RSLT_RTC_NOT_INITIALIZED                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_RTC, 0))
/** Bad argument */
#define CY_RSLT_RTC_BAD_ARGUMENT                        \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_RTC, 1))
/** Unsupported feature */
#define CYHAL_RTC_RSLT_ERR_NOT_SUPPORTED      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_RTC, 2))

/**
 * \}
 */

/** RTC interrupt triggers */
typedef enum {
    CYHAL_RTC_ALARM, /**< Alarm triggered event */
} cyhal_rtc_event_t;

/** @brief Defines which fields should be active for the alarm. */
typedef struct
{
    uint8_t en_sec : 1; /**< Enable match of seconds */
    uint8_t en_min : 1; /**< Enable match of minutes */
    uint8_t en_hour : 1; /**< Enable match of hours */
    uint8_t en_day : 1; /**< Enable match of day of week */
    uint8_t en_date : 1; /**< Enable match of date in month */
    uint8_t en_month : 1; /**< Enable match of month */
} cyhal_alarm_active_t;

/** Enumeration used to configure the DST format
 *
 * \note In areas of the world that practice DST, when it should begin and end is not unique. It
 * can either be in fixed DST format or in relative DST format.
 */
typedef enum
{
    CYHAL_RTC_DST_RELATIVE,        /**< Relative DST format. eg: Begins on the last Sunday of March
                                    and ends on the last Sunday of October. */
    CYHAL_RTC_DST_FIXED            /**< Fixed DST format. eg: Begins on 21st March
                                    and ends on 21st September. */
} cyhal_rtc_dst_format_t;

/**
* Day Light Savings Time (DST) structure for setting when to apply. It allows to
* set the DST time and date using a fixed or relative time format.
*/
typedef struct
{
    cyhal_rtc_dst_format_t format;   /**< DST format. See /ref cyhal_rtc_dst_format_t.
                                          Based on this value other structure elements
                                          should be filled or could be ignored */
    uint32_t hour;                   /**< Hour in 24hour format, range[0-23] */
    union
    {
        uint32_t dayOfMonth;         /**< Day of Month, range[1-31]. */
        struct /* format = CYHAL_RTC_DST_FIXED */
        {
            uint32_t dayOfWeek;      /**< Day of the week, starting on Sunday, range[0-6] */
            uint32_t weekOfMonth;    /**< Week of month, range[0-5]. Where 5 => Last week of month */
        };                           /**< Anonymous struct specifying the week number plus day of week */
    };                               /**< Anonymous union for the day as either a specific day (dayOfMonth)
                                          or as a week number (weekOfMonth) plus day of week (dayOfWeek) */
    uint32_t month;                  /**< Month value, range[1-12]. */
} cyhal_rtc_dst_t;

/** Handler for RTC events (eg: alarm) */
typedef void (*cyhal_rtc_event_callback_t)(void *callback_arg, cyhal_rtc_event_t event);

/** Initialize the RTC peripheral
 *
 * Power up the RTC in preparation for access. This function must be called
 * before any other RTC functions are called. This does not change the state
 * of the RTC. It just enables access to it.
 * @note Before calling this, make sure all necessary System Clocks are setup
 * correctly. Generally this means making sure the RTC has access to a crystal
 * oscillator for optimal accuracy and operation in low power.
 * @note Previously set time configurations are retained. This will only reset
 * the time if no prior configuration can be determined.
 *
 * @param[out] obj  Pointer to an RTC object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @return The status of the init request
 */
cy_rslt_t cyhal_rtc_init(cyhal_rtc_t *obj);

/** Initialize the RTC peripheral using a configurator generated configuration struct
 *
 * Power up the RTC in preparation for access. This function must be called
 * before any other RTC functions are called. This does not change the state
 * of the RTC. It just enables access to it.
 * NOTE: Before calling this, make sure all necessary System Clocks are setup
 * correctly. Generally this means making sure the RTC has access to a crystal
 * oscillator for optimal accuracy and operation in low power.
 * NOTE: Previously set time configurations are retained. This will only reset
 * the time if no prior configuration can be determined.
 *
 * @param[out] obj  Pointer to an RTC object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in] cfg   Configuration structure generated by a configurator.
 * @return The status of the init request
 */
cy_rslt_t cyhal_rtc_init_cfg(cyhal_rtc_t *obj, const cyhal_rtc_configurator_t *cfg);

/** Deinitialize RTC
 *
 * Frees resources associated with the RTC and disables CPU access. This
 * only affects the CPU domain and not the time keeping logic.
 * After this function is called no other RTC functions should be called
 * except for rtc_init.
 *
 * @param[in,out] obj RTC object
 */
void cyhal_rtc_free(cyhal_rtc_t *obj);

/** Check if the RTC has the time set and is counting
 *
 * @param[in] obj RTC object
 * @return Whether the RTC is enabled or not
 */
bool cyhal_rtc_is_enabled(cyhal_rtc_t *obj);

/** Get the current time and date from the RTC peripheral
 *
 * @param[in]  obj RTC object
 * @param[out] time The current time (see: https://en.cppreference.com/w/cpp/chrono/c/tm)
 * @return The status of the read request
 */
cy_rslt_t cyhal_rtc_read(cyhal_rtc_t *obj, struct tm *time);

/** Write the specified time and date to the RTC peripheral
 *
 * @param[in] obj  RTC object
 * @param[in] time The time to be set (see: https://en.cppreference.com/w/cpp/chrono/c/tm)
 * @return The status of the write request
 */
cy_rslt_t cyhal_rtc_write(cyhal_rtc_t *obj, const struct tm *time);

/** Write the specified time and date values to the RTC peripheral
  * @param[in] obj   RTC object
  * @param[in] sec   Second to set (0-59)
  * @param[in] min   Minute to set (0-59)
  * @param[in] hour  Hour to set (0-23)
  * @param[in] day   Day of month to set (1-31)
  * @param[in] month Month to set (1-12)
  * @param[in] year  4-digit year to set
  * @return The status of the write request
  */
cy_rslt_t cyhal_rtc_write_direct(cyhal_rtc_t *obj, uint32_t sec, uint32_t min, uint32_t hour,
                                 uint32_t day, uint32_t month, uint32_t year);

/** Set the start and end time for Day Light Savings
 *
 * Calling this function will allow alarms to account for daylight saving time.
 * This means that the RTC will be adjusted when a daylight saving time
 * transition occurs, meaning times passed to \ref cyhal_rtc_set_alarm()
 * will be interpreted as being in DST/not in DST as appropriate.
 *
 * @param[in] obj  RTC object
 * @param[in] start When Day Light Savings time should start
 * @param[in] stop When Day Light Savings time should end
 * @return The status of the set_dst request
 */
cy_rslt_t cyhal_rtc_set_dst(cyhal_rtc_t *obj, const cyhal_rtc_dst_t *start, const cyhal_rtc_dst_t *stop);

/** Checks to see if Day Light Savings Time is currently active. This should only be called after
 * \ref cyhal_rtc_set_dst().
 *
 * @param[in] obj  RTC object
 * @return Boolean indicating whether the current date/time is within the specified DST start/stop window.
 */
bool cyhal_rtc_is_dst(cyhal_rtc_t *obj);

/** Set an alarm (interrupt) for the specified time and date using the RTC peripheral
 *
 * This requires that a callback handler is registered by \ref cyhal_rtc_register_callback and that
 * the \ref CYHAL_RTC_ALARM event is enabled by \ref cyhal_rtc_enable_event.
 *
 * @param[in] obj    RTC object
 * @param[in] time   The alarm time to be set (see: https://en.cppreference.com/w/cpp/chrono/c/tm)
 * @param[in] active The set of fields that are checked to trigger the alarm
 * @return The status of the set_alarm request
 */
cy_rslt_t cyhal_rtc_set_alarm(cyhal_rtc_t *obj, const struct tm *time, cyhal_alarm_active_t active);

/** Set an alarm (interrupt) at a specified number of seconds in the future
 *
 * This requires that a callback handler is registered by \ref cyhal_rtc_register_callback and that
 * the \ref CYHAL_RTC_ALARM event is enabled by \ref cyhal_rtc_enable_event.
 *
 * @param[in] obj     RTC object
 * @param[in] seconds The number of seconds in the future for the alarm to be
 * set to. Because alarms cannot match the year (see \ref cyhal_alarm_active_t)
 * the maximum number of seconds allowed is 365d*24h*60m*60s == 31,536,000s
 * @return The status of the set_alarm_by_seconds request
 */
cy_rslt_t cyhal_rtc_set_alarm_by_seconds(cyhal_rtc_t *obj, const uint32_t seconds);

/** Register a RTC event callback handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_rtc_enable_event occurs.
 *
 * @param[in] obj          The RTC object
 * @param[in] callback     The callback handler which will be invoked when the alarm event fires
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_rtc_register_callback(cyhal_rtc_t *obj, cyhal_rtc_event_callback_t callback, void *callback_arg);

/** Configure RTC event (eg: alarm) enablement.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_rtc_register_callback will be called.
 *
 * @param[in] obj            The RTC object
 * @param[in] event          The RTC event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on interrupts, False to turn off
 */
void cyhal_rtc_enable_event(cyhal_rtc_t *obj, cyhal_rtc_event_t event, uint8_t intr_priority, bool enable);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_RTC_IMPL_HEADER
#include CYHAL_RTC_IMPL_HEADER
#endif /* CYHAL_RTC_IMPL_HEADER */

/** \} group_hal_rtc */
