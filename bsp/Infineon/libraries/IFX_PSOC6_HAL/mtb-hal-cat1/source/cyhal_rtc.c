/***************************************************************************//**
* \file cyhal_rtc.c
*
* \brief
* Provides a high level interface for interacting with the Infineon Real-Time Clock.
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

#include "cy_rtc.h"
#include "cy_utils.h"
#include "cyhal_rtc.h"
#include "cyhal_system.h"
#include "cyhal_utils_impl.h"
#include "cyhal_irq_impl.h"

/**
* \addtogroup group_hal_impl_rtc RTC (Real Time Clock)
* \ingroup group_hal_impl
* \{
*
* Internally the CAT1 RTC only stores the year as a two digit BCD value
* (0-99); no century information is stored. On RTC initialization the HAL must,
* as a result, assume a default century. If cyhal_rtc_write has been called
* with a different century than the default, its value must be stored and that
* value must persist through deep sleep, hibernate, software resets, etc. CAT1
* hardware provides a number of BREG registers which exist in the BACKUP domain
* and will persist over these power modes and resets. The HAL uses the highest
* indexed BACKUP->BREG register to store the century for the RTC.
*
* Therefore do not use the highest indexed BACKUP->BREG register as it is
* reserved for internal HAL usage.
*
* \note A century rollover (eg: 1999 to 2000) will only be detected if the backup
* domain is reset. This happens automatically on a hardware reset, or can be done
* manually by calling Cy_SysLib_ResetBackupDomain(). Calling the reset function
* will clear any existing RTC/WCO/WDT configuration, so they must be setup after
* the reset.
*
* \} group_hal_impl_wdt
*/

#if (CYHAL_DRIVER_AVAILABLE_RTC)

#if defined(__cplusplus)
extern "C" {
#endif

#define _CYHAL_RTC_STATE_UNINITIALIZED 0
#define _CYHAL_RTC_STATE_ENABLED 1
#define _CYHAL_RTC_STATE_TIME_SET 2
#if (CORE == CM0P)
// To account for the lower __NVIC_PRIO_BITS value
#define _CYHAL_RTC_DEFAULT_PRIORITY 3
#else
#define _CYHAL_RTC_DEFAULT_PRIORITY 5
#endif // (defined(COMPONENT_CAT1C) && (CORE == CM0P))
#define _CYHAL_RTC_INIT_CENTURY 2000
#define _CYHAL_RTC_TM_YEAR_BASE 1900

#if defined(COMPONENT_CAT1A) || defined (COMPONENT_CAT1C)
#define _CYHAL_RTC_BREG (BACKUP->BREG[SRSS_BACKUP_NUM_BREG-1])
#elif defined(COMPONENT_CAT1B)
#if defined(SRSS_BACKUP_NUM_BREG3) && (SRSS_BACKUP_NUM_BREG3 > 0)
#define _CYHAL_RTC_BREG (BACKUP->BREG_SET3[SRSS_BACKUP_NUM_BREG3-1])
#elif defined(SRSS_BACKUP_NUM_BREG2) && (SRSS_BACKUP_NUM_BREG2 > 0)
#define _CYHAL_RTC_BREG (BACKUP->BREG_SET2[SRSS_BACKUP_NUM_BREG2-1])
#elif defined(SRSS_BACKUP_NUM_BREG1) && (SRSS_BACKUP_NUM_BREG1 > 0)
#define _CYHAL_RTC_BREG (BACKUP->BREG_SET1[SRSS_BACKUP_NUM_BREG1-1])
#elif defined(SRSS_BACKUP_NUM_BREG0) && (SRSS_BACKUP_NUM_BREG0 > 0)
#define _CYHAL_RTC_BREG (BACKUP->BREG_SET0[SRSS_BACKUP_NUM_BREG0-1])
#endif
#endif /* defined(COMPONENT_CAT1B) */

#define _CYHAL_RTC_BREG_CENTURY_Pos 0UL
#define _CYHAL_RTC_BREG_CENTURY_Msk 0x0000FFFFUL
#define _CYHAL_RTC_BREG_STATE_Pos 16UL
#define _CYHAL_RTC_BREG_STATE_Msk 0xFFFF0000UL

static const uint32_t _CYHAL_RTC_MAX_RETRY = 10;
static const uint32_t _CYHAL_RTC_RETRY_DELAY_MS = 1;

// Note: Use PDL directly rather than HAL. RTOS-aware delay is not needed and actually breaks functionality.
#define _CYHAL_RTC_WAIT_ONE_MS()   Cy_SysLib_Delay(_CYHAL_RTC_RETRY_DELAY_MS);

static void _cyhal_rtc_from_pdl_time(cy_stc_rtc_config_t *pdlTime, const int year, struct tm *time) {
    CY_ASSERT(NULL != pdlTime);
    CY_ASSERT(NULL != time);

    // The number of days that precede each month of the year, not including Feb 29
    static const uint16_t CUMULATIVE_DAYS[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    time->tm_sec = (int)pdlTime->sec;
    time->tm_min = (int)pdlTime->min;
    time->tm_hour = (int)pdlTime->hour;
    time->tm_mday = (int)pdlTime->date;
    time->tm_mon = (int)(pdlTime->month - 1u);
    time->tm_year = (int)(year - _CYHAL_RTC_TM_YEAR_BASE);
    time->tm_wday = (int)(pdlTime->dayOfWeek - 1u);
    time->tm_yday = (int)CUMULATIVE_DAYS[time->tm_mon] + (int)pdlTime->date - 1 +
        (((int)(pdlTime->month) >= 3 && (int)(Cy_RTC_IsLeapYear((uint32_t)year) ? 1u : 0u)));
    time->tm_isdst = -1;
}

/** Wrapper around the PDL Cy_RTC_DeepSleepCallback to adapt the function signature */
static cy_en_syspm_status_t _cyhal_rtc_syspm_callback(cy_stc_syspm_callback_params_t *params, cy_en_syspm_callback_mode_t mode)
{
    return Cy_RTC_DeepSleepCallback(params, mode);
}

static bool _cyhal_rtc_dst_skip_next_alarm = false;
static cy_stc_rtc_dst_t *_cyhal_rtc_dst;
static cy_stc_syspm_callback_params_t _cyhal_rtc_pm_cb_params = {NULL, NULL};
static cy_stc_syspm_callback_t _cyhal_rtc_pm_cb = {
    .callback = &_cyhal_rtc_syspm_callback,
    .type = CY_SYSPM_DEEPSLEEP,
    .callbackParams = &_cyhal_rtc_pm_cb_params,
};

static cyhal_rtc_event_callback_t _cyhal_rtc_user_handler;
static void *_cyhal_rtc_handler_arg;

/* Returns century portion of BREG register used to store century info */
static inline uint16_t _cyhal_rtc_get_century(void)
{
    return _FLD2VAL(_CYHAL_RTC_BREG_CENTURY, _CYHAL_RTC_BREG);
}

/* Sets century portion of BREG register used to store century info */
static inline void _cyhal_rtc_set_century(uint16_t century)
{
    _CYHAL_RTC_BREG &= _CYHAL_RTC_BREG_STATE_Msk;
    _CYHAL_RTC_BREG |= _VAL2FLD(_CYHAL_RTC_BREG_CENTURY, century);
}

/* Returns state portion of BREG register used to store century info */
static inline uint16_t _cyhal_rtc_get_state(void)
{
    return _FLD2VAL(_CYHAL_RTC_BREG_STATE, _CYHAL_RTC_BREG);
}

/* Sets state portion of BREG register used to store century info */
static inline void _cyhal_rtc_set_state(uint16_t init)
{
    _CYHAL_RTC_BREG &= _CYHAL_RTC_BREG_CENTURY_Msk;
    _CYHAL_RTC_BREG |= _VAL2FLD(_CYHAL_RTC_BREG_STATE, init);
}

static void _cyhal_rtc_initialize_dst(const cyhal_rtc_dst_t *hal, cy_stc_rtc_dst_format_t *pdl)
{
    pdl->format = (hal->format == CYHAL_RTC_DST_FIXED) ? CY_RTC_DST_FIXED : CY_RTC_DST_RELATIVE;
    pdl->hour = hal->hour;
    pdl->dayOfMonth = (hal->format == CYHAL_RTC_DST_FIXED) ? hal->dayOfMonth : 1;
    pdl->weekOfMonth = (hal->format == CYHAL_RTC_DST_FIXED) ? 1 : hal->weekOfMonth + 1;
    pdl->dayOfWeek = (hal->format == CYHAL_RTC_DST_FIXED) ? 1 : hal->dayOfWeek + 1;
    pdl->month = hal->month;
}

/** Wrapper around the PDL RTC interrupt handler to adapt the function signature */
static void _cyhal_rtc_isr_handler(void)
{
    Cy_RTC_Interrupt(_cyhal_rtc_dst, NULL != _cyhal_rtc_dst);
}

/* Override weak function from PDL */
void Cy_RTC_Alarm1Interrupt(void)
{
    if (_cyhal_rtc_dst_skip_next_alarm)
    {
        _cyhal_rtc_dst_skip_next_alarm = false;
    }
    else if (NULL != _cyhal_rtc_user_handler)
    {
        (*_cyhal_rtc_user_handler)(_cyhal_rtc_handler_arg, CYHAL_RTC_ALARM);
    }
}

void Cy_RTC_CenturyInterrupt(void)
{
    _cyhal_rtc_set_century(_cyhal_rtc_get_century() + 100);
}

static cy_rslt_t _cyhal_rtc_init_common(const cy_stc_rtc_config_t* default_time)
{
    cy_rslt_t rslt = CY_RSLT_SUCCESS;
    if (_cyhal_rtc_get_state() == _CYHAL_RTC_STATE_UNINITIALIZED)
    {
        if (Cy_RTC_IsExternalResetOccurred())
        {
            // Reset to default time
            Cy_RTC_SetDateAndTime(default_time);
            _cyhal_rtc_set_century(_CYHAL_RTC_INIT_CENTURY);
        }

        if (Cy_SysPm_RegisterCallback(&_cyhal_rtc_pm_cb))
        {
            _cyhal_rtc_set_state(_CYHAL_RTC_STATE_ENABLED);
        }
        else
        {
            rslt = CY_RSLT_RTC_NOT_INITIALIZED;
        }
    }
    else if(_cyhal_rtc_get_state() == _CYHAL_RTC_STATE_ENABLED || _cyhal_rtc_get_state() == _CYHAL_RTC_STATE_TIME_SET)
    {
        if (Cy_RTC_GetInterruptStatus() & CY_RTC_INTR_CENTURY)
            Cy_RTC_CenturyInterrupt();
    }

    Cy_RTC_ClearInterrupt(CY_RTC_INTR_CENTURY);
    Cy_RTC_SetInterruptMask(CY_RTC_INTR_CENTURY);
    _cyhal_irq_register(srss_interrupt_backup_IRQn, _CYHAL_RTC_DEFAULT_PRIORITY, _cyhal_rtc_isr_handler);

    if (rslt == CY_RSLT_SUCCESS)
    {
        _cyhal_rtc_dst = NULL;
        _cyhal_irq_enable(srss_interrupt_backup_IRQn);
    }

    return rslt;
}

cy_rslt_t cyhal_rtc_init(cyhal_rtc_t *obj)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    static const cy_stc_rtc_config_t default_time =
    {
        .dayOfWeek = CY_RTC_SATURDAY,
        .date = 1,
        .month = 1,
        .year = 0,
    };
    return _cyhal_rtc_init_common(&default_time);
}

cy_rslt_t cyhal_rtc_init_cfg(cyhal_rtc_t *obj, const cyhal_rtc_configurator_t *cfg)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    cy_rslt_t rslt = _cyhal_rtc_init_common(cfg->config);
    if (NULL != cfg->dst_config)
    {
        _cyhal_rtc_set_state(_CYHAL_RTC_STATE_TIME_SET);

        cy_stc_rtc_config_t dateTime;
        Cy_RTC_GetDateAndTime(&dateTime);
        rslt = Cy_RTC_EnableDstTime(cfg->dst_config, &dateTime);
        if (rslt == CY_RSLT_SUCCESS)
        {
            obj->dst = *(cfg->dst_config);
            _cyhal_rtc_dst = &(obj->dst);
        }
    }
    return rslt;
}

void cyhal_rtc_free(cyhal_rtc_t *obj)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
    _cyhal_irq_free(srss_interrupt_backup_IRQn);

    Cy_RTC_SetInterruptMask(CY_RTC_INTR_CENTURY);
    _cyhal_rtc_dst = NULL;
}

bool cyhal_rtc_is_enabled(cyhal_rtc_t *obj)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
    return (_cyhal_rtc_get_state() == _CYHAL_RTC_STATE_TIME_SET);
}

cy_rslt_t cyhal_rtc_read(cyhal_rtc_t *obj, struct tm *time)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    cy_stc_rtc_config_t dateTime = { .hrFormat = CY_RTC_24_HOURS };
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    Cy_RTC_GetDateAndTime(&dateTime);
    const int year = (int)(dateTime.year + _cyhal_rtc_get_century());
    cyhal_system_critical_section_exit(savedIntrStatus);

    _cyhal_rtc_from_pdl_time(&dateTime, year, time);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_rtc_write(cyhal_rtc_t *obj, const struct tm *time)
{
    CY_ASSERT(NULL != obj);
    return cyhal_rtc_write_direct(obj, time->tm_sec, time->tm_min, time->tm_hour, time->tm_mday,
                                    time->tm_mon + 1, _CYHAL_RTC_TM_YEAR_BASE + time->tm_year);
}

cy_rslt_t cyhal_rtc_write_direct(cyhal_rtc_t *obj, uint32_t sec, uint32_t min, uint32_t hour,
                                 uint32_t day, uint32_t month, uint32_t year)
{
    CY_UNUSED_PARAMETER(obj);
    uint32_t year2digit = year % 100;

    cy_rslt_t rslt;
    uint32_t retry = 0;
    if (!CY_RTC_IS_SEC_VALID(sec) || !CY_RTC_IS_MIN_VALID(min) || !CY_RTC_IS_HOUR_VALID(hour) || !CY_RTC_IS_MONTH_VALID(month) || !CY_RTC_IS_YEAR_SHORT_VALID(year2digit))
    {
        return CY_RSLT_RTC_BAD_ARGUMENT;
    }
    do
    {
        if (retry != 0)
            _CYHAL_RTC_WAIT_ONE_MS();
        uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
        rslt = Cy_RTC_SetDateAndTimeDirect(sec, min, hour, day, month, year2digit);
        if (rslt == CY_RSLT_SUCCESS)
            _cyhal_rtc_set_century((uint16_t)(year) - (uint16_t)(year2digit));
        cyhal_system_critical_section_exit(savedIntrStatus);
        ++retry;
    } while (rslt == CY_RTC_INVALID_STATE && retry < _CYHAL_RTC_MAX_RETRY);

    retry = 0;
    while (CY_RTC_BUSY == Cy_RTC_GetSyncStatus() && retry < _CYHAL_RTC_MAX_RETRY)
    {
        _CYHAL_RTC_WAIT_ONE_MS();
        ++retry;
    }

    if (rslt == CY_RSLT_SUCCESS)
    {
        _cyhal_rtc_set_state(_CYHAL_RTC_STATE_TIME_SET);
    }
    return rslt;
}

cy_rslt_t cyhal_rtc_set_dst(cyhal_rtc_t *obj, const cyhal_rtc_dst_t *start, const cyhal_rtc_dst_t *stop)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != start);
    CY_ASSERT(NULL != stop);

    _cyhal_rtc_initialize_dst(start, &(obj->dst.startDst));
    _cyhal_rtc_initialize_dst(stop, &(obj->dst.stopDst));

    cy_stc_rtc_config_t dateTime;
    Cy_RTC_GetDateAndTime(&dateTime);
    cy_rslt_t rslt = Cy_RTC_EnableDstTime(&(obj->dst), &dateTime);
    if (rslt == CY_RSLT_SUCCESS)
        _cyhal_rtc_dst = &(obj->dst);

    return rslt;
}

bool cyhal_rtc_is_dst(cyhal_rtc_t *obj)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    cy_stc_rtc_config_t dateTime;
    Cy_RTC_GetDateAndTime(&dateTime);
    return Cy_RTC_GetDstStatus(_cyhal_rtc_dst, &dateTime);
}

cy_rslt_t cyhal_rtc_set_alarm(cyhal_rtc_t *obj, const struct tm *time, cyhal_alarm_active_t active)
{
    // Note: the hardware does not support year matching
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
    _cyhal_rtc_dst_skip_next_alarm = false;
    cy_stc_rtc_alarm_t alarm =
    {
        .sec = (uint32_t)time->tm_sec,
        .secEn = active.en_sec ? CY_RTC_ALARM_ENABLE : CY_RTC_ALARM_DISABLE,
        .min = (uint32_t)time->tm_min,
        .minEn = active.en_min ? CY_RTC_ALARM_ENABLE : CY_RTC_ALARM_DISABLE,
        .hour = (uint32_t)time->tm_hour,
        .hourEn = active.en_hour ? CY_RTC_ALARM_ENABLE : CY_RTC_ALARM_DISABLE,
        .dayOfWeek = (uint32_t)(time->tm_wday + 1),
        .dayOfWeekEn = active.en_day ? CY_RTC_ALARM_ENABLE : CY_RTC_ALARM_DISABLE,
        .date = (uint32_t)time->tm_mday,
        .dateEn = active.en_date ? CY_RTC_ALARM_ENABLE : CY_RTC_ALARM_DISABLE,
        .month = (uint32_t)(time->tm_mon + 1),
        .monthEn = active.en_month ? CY_RTC_ALARM_ENABLE : CY_RTC_ALARM_DISABLE,
        .almEn = CY_RTC_ALARM_ENABLE
    };

    cy_rslt_t rslt;
    uint32_t retry = 0;
    do
    {
        if (retry != 0)
            _CYHAL_RTC_WAIT_ONE_MS();
        rslt = (cy_rslt_t)Cy_RTC_SetAlarmDateAndTime(&alarm, CY_RTC_ALARM_1);
        ++retry;
    } while (rslt == CY_RTC_INVALID_STATE && retry < _CYHAL_RTC_MAX_RETRY);

    return rslt;
}

static uint32_t _cyhal_rtc_update_field(uint32_t remaining, uint32_t* curr, uint32_t *next, uint32_t max)
{
    *curr += remaining % max;
    if (*curr >= max)
    {
        *curr %= max;
        (*next)++;
    }
    return remaining / max;
}

cy_rslt_t cyhal_rtc_set_alarm_by_seconds(cyhal_rtc_t *obj, const uint32_t seconds)
{
    CY_ASSERT(NULL != obj);
    static const uint32_t SECONDS_IN_YEAR = 365*24*60*60; // 31,536,000

    // Note: The hardware does not support year matching so return error if
    // seconds is greater than 1 year in the future
    if(seconds > SECONDS_IN_YEAR)
        return CY_RSLT_RTC_BAD_ARGUMENT;

    cy_stc_rtc_config_t now;
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    Cy_RTC_GetDateAndTime(&now);
    const int year = (int)(now.year + _cyhal_rtc_get_century());
    cyhal_system_critical_section_exit(savedIntrStatus);

    bool nowDst = (NULL != _cyhal_rtc_dst) && Cy_RTC_GetDstStatus(_cyhal_rtc_dst, &now);

    uint32_t remaining = seconds;
    remaining = _cyhal_rtc_update_field(remaining, &now.sec, &now.min, 60);
    remaining = _cyhal_rtc_update_field(remaining, &now.min, &now.hour, 60);
    remaining = _cyhal_rtc_update_field(remaining, &now.hour, &now.date, 24);

    uint32_t days;
    now.date += remaining;
    while (now.date > (days = Cy_RTC_DaysInMonth(now.month, year)))
    {
        now.date -= days;
        now.month++;
        if (now.month > 12)
        {
            now.year++;
            now.month = 1;
        }
    }

    bool setSkipNextAlarm = false;

    // Handle crossing of daylight savings time boundaries
    if (NULL != _cyhal_rtc_dst)
    {
        bool futureDst = Cy_RTC_GetDstStatus(_cyhal_rtc_dst, &now);

        if (nowDst && !futureDst)
        {
            // If the alarm time is within the hour following the end of DST,
            // ignore the first alarm since the adjusted time will be before
            // the DST boundary causing two alarms to occur: one before the
            // boundary and one after the boundary.
            if (now.hour == _cyhal_rtc_dst->stopDst.hour)
            {
                setSkipNextAlarm = true;
            }

            if (now.hour == 0)
            {
                now.hour = 23;
                now.date--;

                if (now.date < 1)
                {
                    now.month--;
                    if (now.month < 1)
                    {
                        now.month = 12;
                        now.year--;
                    }

                    now.date = Cy_RTC_DaysInMonth(now.month, year);
                }
            }
            else
            {
                now.hour--;
            }
        }
        else if (!nowDst && futureDst)
        {
            now.hour++;
            if (now.hour >= 24)
            {
                now.hour = 0;
                now.date++;

                if (now.date > days)
                {
                    now.date = 1;
                    now.month++;
                    if (now.month > 12)
                    {
                        now.month = 1;
                        // Increment year, but alarm doesn't care
                    }
                }
            }
        }
    }

    struct tm future;
    _cyhal_rtc_from_pdl_time(&now, year, &future);

    static const cyhal_alarm_active_t active =
    {
        .en_sec   = CY_RTC_ALARM_ENABLE,
        .en_min   = CY_RTC_ALARM_ENABLE,
        .en_hour  = CY_RTC_ALARM_ENABLE,
        .en_day   = CY_RTC_ALARM_DISABLE, // We do not actually compute the day as we don't care.
        .en_date  = CY_RTC_ALARM_ENABLE,  // The absolute time (eg: date) is what is important.
        .en_month = CY_RTC_ALARM_ENABLE
    };

    savedIntrStatus = cyhal_system_critical_section_enter();
    cy_rslt_t result = cyhal_rtc_set_alarm(obj, &future, active);
    _cyhal_rtc_dst_skip_next_alarm = setSkipNextAlarm;
    cyhal_system_critical_section_exit(savedIntrStatus);

    return result;
}

void cyhal_rtc_register_callback(cyhal_rtc_t *obj, cyhal_rtc_event_callback_t callback, void *callback_arg)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    _cyhal_rtc_handler_arg = callback_arg;
    _cyhal_rtc_user_handler = callback;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_rtc_enable_event(cyhal_rtc_t *obj, cyhal_rtc_event_t event, uint8_t intr_priority, bool enable)
{
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(event);
    CY_ASSERT(NULL != obj);
    CY_ASSERT(CYHAL_RTC_ALARM == event);
    Cy_RTC_ClearInterrupt(CY_RTC_INTR_ALARM1 | CY_RTC_INTR_ALARM2);
    uint32_t alarm2_status = (Cy_RTC_GetInterruptMask() & CY_RTC_INTR_ALARM2);
    Cy_RTC_SetInterruptMask((enable ? CY_RTC_INTR_ALARM1 : 0) | CY_RTC_INTR_CENTURY | alarm2_status);
    _cyhal_irq_set_priority(srss_interrupt_backup_IRQn, intr_priority);
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_RTC */
