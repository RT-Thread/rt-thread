/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2029-06-02     hqfang       first implementation.
 */

#ifndef __DRV_PWM__
#define __DRV_PWM__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_config.h>

/* gd32 config class */
struct gd32_pwm_config
{
    const char *name;
    rt_uint32_t periph;
    rt_uint32_t period;
    rt_uint32_t pulse;
};

struct gd32_pwm
{
    struct rt_device_pwm pwm_device;
    struct gd32_pwm_config *config;
};

#endif
