/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-13     ChuShicheng   first version
 */

#ifndef __DRV_I2C_SOFT__
#define __DRV_I2C_SOFT__

#include <rtdevice.h>

struct soft_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

struct soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};

int rt_hw_i2c_init(void);

#endif /* __DRV_I2C_SOFT__ */
