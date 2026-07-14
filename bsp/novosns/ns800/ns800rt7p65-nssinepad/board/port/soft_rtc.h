/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-30     rcitach    first version
 */
#ifndef __SOFT_RTC_H__
#define __SOFT_RTC_H__

#include <rtthread.h>
#include <time.h>

rt_err_t soft_rtc_init(void);
rt_err_t soft_rtc_get_time(struct tm *time);
rt_err_t soft_rtc_set_time(const struct tm *time);
int rt_hw_soft_rtc_init(void);

#endif /* __SOFT_RTC_H__ */

