/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-10     aozima       first version.
 */

#ifndef __RTC_H__
#define __RTC_H__

#include <rtconfig.h>

rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day);
rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second);

#ifdef RTC_SYNC_USING_NTP
int rt_soft_rtc_init(void);
int rt_rtc_ntp_sync_init(void);
#endif /* RTC_SYNC_USING_NTP */

#endif /* __RTC_H__ */
