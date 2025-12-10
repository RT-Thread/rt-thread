/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include <rtatomic.h>
#include "rtc_dm.h"

#define DBG_TAG "rtc.dm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

int rtc_dev_set_name(struct rt_device *rtc_dev)
{
    int id;
    static volatile rt_atomic_t uid = 1;

    RT_ASSERT(rtc_dev != RT_NULL)

    if (rt_device_find("rtc"))
    {
        id = (int)rt_atomic_add(&uid, 1);

        return rt_dm_dev_set_name(rtc_dev, "rtc%u", id);
    }
    else
    {
        return rt_dm_dev_set_name(rtc_dev, "rtc");
    }
}

time_t rtc_wkalarm_to_timestamp(struct rt_rtc_wkalarm *alarm)
{
    struct tm tm_time;
    time_t current_time;

    current_time = time(RT_NULL);
    localtime_r(&current_time, &tm_time);

    tm_time.tm_sec = alarm->tm_sec;
    tm_time.tm_min = alarm->tm_min;
    tm_time.tm_hour = alarm->tm_hour;

    return timegm(&tm_time);
}

void rtc_timestamp_to_wkalarm(time_t timestamp, struct rt_rtc_wkalarm *alarm)
{
    struct tm tm_time;

    localtime_r(&timestamp, &tm_time);

    alarm->tm_sec = tm_time.tm_sec;
    alarm->tm_min = tm_time.tm_min;
    alarm->tm_hour = tm_time.tm_hour;
}
