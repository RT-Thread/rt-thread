/*
 * Copyright (c) 2026 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DRV_SOFT_I2C__
#define __DRV_SOFT_I2C__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

/* HPM config class */
struct hpm_soft_i2c_config
{
    const char  *scl_pin_name;
    const char  *sda_pin_name;
    const char *bus_name;
};

/* HPM i2c driver class */
struct hpm_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

int rt_hw_i2c_init(void);

#endif /* __DRV_SOFT_I2C__ */
