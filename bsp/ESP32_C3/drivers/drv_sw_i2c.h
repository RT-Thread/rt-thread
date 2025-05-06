/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-07     wumingzi     first version
 */
#ifndef __DRV_HW_I2C_H__
#define __DRV_HW_I2C_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "sdkconfig.h"

/* esp32c3 config class */
struct esp32c3_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};

/* esp32c3 i2c dirver class */
struct esp32c3_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

int rt_hw_i2c_init(void);

#endif /* __DRV_HW_I2C_H__ */