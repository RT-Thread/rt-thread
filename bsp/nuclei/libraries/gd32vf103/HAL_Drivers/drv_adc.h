/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-03     hqfang       first implementation.
 */

#ifndef __DRV_ADC__
#define __DRV_ADC__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_config.h>

/* gd32 config class */
struct gd32_adc_config
{
    const char *name;
    rt_uint32_t adc_periph;
};

struct gd32_adc
{
    struct rt_adc_device adc_device;
    struct gd32_adc_config *config;
};

#endif
