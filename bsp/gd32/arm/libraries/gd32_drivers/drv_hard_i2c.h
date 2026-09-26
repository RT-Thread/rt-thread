/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-20     BruceOu      the first version
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GD32 i2c driver */
struct gd32_i2c_bus
{
    uint32_t i2c_periph;
    rcu_periph_enum per_clk;

    const char *scl_pin_name;
    const char *sda_pin_name;
    const char *alternate;

    struct rt_i2c_bus_device *i2c_bus;
    char *device_name;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_I2C__ */

