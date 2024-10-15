/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-15     flyingcys    1st version
 */

#ifndef DRV_RTC_H__
#define DRV_RTC_H__

#include <rtdevice.h>

#ifdef RT_USING_ALARM
#include "drivers/dev_alarm.h"
#endif

struct rt_rtc_device
{
    struct rt_device        device;
#ifdef RT_USING_ALARM
    struct rt_rtc_wkalarm   wkalarm;
#endif
};

int wm_hw_rtc_init(void);

#endif
