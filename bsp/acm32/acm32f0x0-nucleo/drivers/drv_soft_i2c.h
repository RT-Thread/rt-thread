/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-23     LZero        Modify the I2C framework.
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include <rtthread.h>
#include <board.h>
#include <rtdbg.h>
#include <rtdevice.h>
#include <drivers/dev_pin.h>

/* acm32 config class */
struct acm32_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};
/* acm32 i2c dirver class */

struct acm32_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

#ifdef BSP_USING_I2C0
#define I2C0_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C0_SCL_PIN,                         \
        .sda = BSP_I2C0_SDA_PIN,                         \
        .bus_name = "i2c0",                              \
    }
#endif

#endif //__DRV_I2C__
