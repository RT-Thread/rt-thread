/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_RTC_DRV_H
#define HPM_RTC_DRV_H

/**
 * @brief RTC driver APIs
 * @defgroup rtc_interface RTC driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

#include "hpm_common.h"
#include "hpm_rtc_regs.h"
#ifndef __ICCRISCV__
#include <sys/time.h>
#endif
#include <time.h>

/**
 * @brief RTC alarm configuration
 */
typedef struct {
    uint16_t index;         /**< RTC alarm index */
    uint16_t type;          /**< Alarm type */
    time_t period;          /**< Alarm period */
} rtc_alarm_config_t;

/**
 * @brief RTC Alarm type
 */
#define RTC_ALARM_TYPE_ONE_SHOT (0U) /**<  The RTC alarm will be triggered only once */
#define RTC_ALARM_TYPE_PERIODIC (1U) /**< The RTC alarm will be triggered periodically */
#define RTC_ALARM_TYPE_ABSOLUTE_TIME_ONE_SHOT (2U) /**< The RTC alarm will be triggered via the absolute time provided via period */

/**
 * @brief Typical RTC alarm period definitions
 */
#define ALARM_PERIOD_ONE_SEC  (1UL)                             /**< Alarm period: 1 second */
#define ALARM_PERIOD_ONE_MIN  (60UL)                            /**< Alarm period: 1 minute */
#define ALARM_PERIOD_ONE_HOUR (3600U)                           /**< Alarm period: 1 hour */
#define ALARM_PERIOD_ONE_DAY  (ALARM_PERIOD_ONE_HOUR * 24UL)    /**< Alarm period: 1 day */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configure the RTC time
 * @param [in] base RTC base address
 * @param [in] time seconds since 1970.1.1, 0:0:0
 * @retval API execution status status_success or status_invalid_argument
 */
hpm_stat_t rtc_config_time(RTC_Type *base, time_t time);

/**
 * @brief Configure RTC Alarm
 * @param [in] base RTC base address
 * @param [in] config RTC alarm configuration pointer
 * @retval API execution status status_success or status_invalid_argument;
 */
hpm_stat_t rtc_config_alarm(RTC_Type *base, rtc_alarm_config_t *config);

/**
 * @brief Get the time returned by RTC module
 * @param [in] base RTC base address
 * @retval RTC time
 */
time_t rtc_get_time(RTC_Type *base);


/**
 * @brief Get accurate time return by RTC module
 * @param [in] base RTC base address
 *
 * @return accurate time(including second and subsecond)
 */
struct timeval rtc_get_timeval(RTC_Type *base);

/**
 * @brief Enable RTC alarm interrupt
 * @param [in] base RTC base address
 * @param [in] index RTC alarm index, valid value is 0 or 1
 * @param [in] enable RTC alarm enable flag
 *  @arg true Enable specified RTC alarm
 *  @arg false Disable specified RTC alarm
 */
static inline void rtc_enable_alarm_interrupt(RTC_Type *base, uint32_t index, bool enable)
{
    if (index > 1) {
        return;
    }

    uint32_t mask = (index == 0U) ? RTC_ALARM_EN_ENABLE0_MASK : RTC_ALARM_EN_ENABLE1_MASK;

    if (enable) {
        base->ALARM_EN |= mask;
    } else {
        base->ALARM_EN &= ~mask;
    }
}

/**
 * @brief Clear RTC alarm flag based on alarm index
 * @param [in] base RTC base address
 * @param [in] index RTC alarm index, valid value is 0 or 1
 */
static inline void rtc_clear_alarm_flag(RTC_Type *base, uint32_t index)
{
    if (index > 1) {
        return;
    }
    uint32_t mask = (index == 0U) ? RTC_ALARM_FLAG_ALARM0_MASK : RTC_ALARM_FLAG_ALARM1_MASK;

    base->ALARM_FLAG = mask;
}

/**
 * @brief Clear RTC alarm flags based on flag masks
 * @param [in] base RTC base address
 * @param [in] masks RTC alarm masks
 */
static inline void rtc_clear_alarm_flags(RTC_Type *base, uint32_t masks)
{
    base->ALARM_FLAG = masks;
}

/**
 * @brief Check whether RTC alarm flag is set or not
 * @param [in] base RTC base address
 * @param [in] index RTC alarm index, valid value is 0 or 1
 * @retval RTC alarm flag. Valid value is true or false
 */
static inline bool rtc_is_alarm_flag_asserted(RTC_Type *base, uint32_t index)
{
    if (index > 1) {
        return false;
    }
    uint32_t mask = (index == 0U) ? RTC_ALARM_FLAG_ALARM0_MASK : RTC_ALARM_FLAG_ALARM1_MASK;

    return IS_HPM_BITMASK_SET(base->ALARM_FLAG, mask);
}

/**
 * @brief Get the RTC alarm flags
 * @param [in] base RTC base address
 * @return RTC alarm flags
 */
static inline uint32_t rtc_get_alarm_flags(RTC_Type *base)
{
    return base->ALARM_FLAG;
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 *
 */

#endif /* HPM_RTC_DRV_H */
