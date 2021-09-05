/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-09     shelton      first version
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

/* at32 config class */
struct at32_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};
/* at32 i2c dirver class */
struct at32_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

#ifdef BSP_USING_I2C1
#define I2C1_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C1_SCL_PIN,                         \
        .sda = BSP_I2C1_SDA_PIN,                         \
        .bus_name = "i2c1",                              \
    }
#endif

#ifdef BSP_USING_I2C2
#define i2c_bus_CONFIG                                   \
    {                                                    \
        .scl = BSP_I2C2_SCL_PIN,                         \
        .sda = BSP_I2C2_SDA_PIN,                         \
        .bus_name = "i2c2",                              \
    }
#endif

#ifdef BSP_USING_I2C3
#define I2C3_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C3_SCL_PIN,                         \
        .sda = BSP_I2C3_SDA_PIN,                         \
        .bus_name = "i2c3",                              \
    }
#endif

#ifdef BSP_USING_I2C4
#define I2C4_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C4_SCL_PIN,                         \
        .sda = BSP_I2C4_SDA_PIN,                         \
        .bus_name = "i2c4",                              \
    }
#endif
int rt_hw_i2c_init(void);

#endif
