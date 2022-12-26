/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-11-4      GuEe-GUI       first version
 */

#ifndef DRV_RTC_H__
#define DRV_RTC_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>

struct hw_rtc_device
{
    struct rt_device device;
};

int rt_hw_rtc_init(void);

#endif
