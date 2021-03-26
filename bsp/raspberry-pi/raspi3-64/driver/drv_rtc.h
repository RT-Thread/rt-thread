/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>
#include "bcm283x.h"

struct rt_rtc_device
{
    struct rt_device device;
};

int rt_hw_rtc_init(void);

#endif
