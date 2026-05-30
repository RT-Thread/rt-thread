/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-13     yefeng       first implementation.
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <board.h>

struct gd32_i2c_config
{
    const char *name;
    rt_uint32_t i2c_periph;
    rcu_periph_enum rcu_clk;
    rt_uint32_t speed;
};

struct gd32_i2c_device
{
    struct rt_i2c_bus_device parent;
    struct gd32_i2c_config *config;
};

#endif
