/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_rtc_drv.h"


hpm_stat_t rtc_config_time(RTC_Type *base, time_t time)
{
    base->SECOND = (uint32_t)time;
    return status_success;
}

time_t rtc_get_time(RTC_Type *base)
{
    time_t time = (time_t)base->SECOND;
    return time;
}

hpm_stat_t rtc_config_alarm(RTC_Type *base, rtc_alarm_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        if ((config == NULL) || (config->index > 1U) || (config->type > RTC_ALARM_TYPE_ABSOLUTE_TIME_ONE_SHOT)) {
            break;
        }
        uint32_t alarm_inc = 0;
        uint32_t alarm;
        if (config->type == RTC_ALARM_TYPE_ONE_SHOT) {
            uint32_t current_sec = base->SECOND;
            alarm = current_sec + config->period;
            if (alarm < current_sec) {
                break;
            }
        } else if (config->type == RTC_ALARM_TYPE_PERIODIC) {
            uint32_t current_sec = base->SECOND;
            alarm_inc = config->period;
            alarm = current_sec + config->period;
            if (alarm < current_sec) {
                break;
            }
        } else {
            alarm = config->period;
        }

        if (config->index == 0U) {
            base->ALARM0 = alarm;
            base->ALARM0_INC = alarm_inc;
        } else {
            base->ALARM1 = alarm;
            base->ALARM1_INC = alarm_inc;
        }

        status = status_success;
    } while (false);

    return status;
}
