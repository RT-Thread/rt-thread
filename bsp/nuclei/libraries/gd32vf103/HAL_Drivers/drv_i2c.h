/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-27     hqfang       first implementation.
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_config.h>

/* gd32 config class */
struct gd32_i2c_config
{
    const char *name;
    rt_uint32_t i2c_periph;
    rt_uint32_t speed;
};

struct gd32_i2c
{
    struct rt_i2c_bus_device bus;
    struct gd32_i2c_config *config;
};

#endif
