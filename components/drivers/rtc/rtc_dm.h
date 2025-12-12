/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#ifndef __RTC_DM_H__
#define __RTC_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <sys/time.h>

int rtc_dev_set_name(struct rt_device *rtc_dev);
time_t rtc_wkalarm_to_timestamp(struct rt_rtc_wkalarm *alarm);
void rtc_timestamp_to_wkalarm(time_t timestamp, struct rt_rtc_wkalarm *alarm);

#endif /* __RTC_DM_H__ */
