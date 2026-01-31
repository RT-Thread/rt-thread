/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2029-05-06     hqfang       first implementation.
 */

#ifndef __DRV_CLOCK_TIMER__
#define __DRV_CLOCK_TIMER__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_config.h>

/* gd32 config class */
struct gd32_clock_timer_config
{
    const char *name;
    rt_uint32_t timer_periph;
    IRQn_Type irqn;
};

struct gd32_clock_timer
{
    rt_clock_timer_t time_device;
    struct gd32_clock_timer_config *config;
};

#endif
