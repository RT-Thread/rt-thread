/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-22     balanceTWK   first version
 */

#ifndef __DRV_SOFT_I2C__
#define __DRV_SOFT_I2C__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

/* w60x config class */
struct w60x_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};
/* w60x i2c dirver class */
struct w60x_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c2_bus;
};

#ifdef BSP_USING_SOFT_I2C1
#define I2C1_BUS_CONFIG                                  \
    {                                                    \
        .scl = SOFT_I2C1_SCL_PIN,                        \
        .sda = SOFT_I2C1_SDA_PIN,                        \
        .bus_name = "i2c1soft",                          \
    }
#endif

#ifdef BSP_USING_SOFT_I2C2
#define I2C2_BUS_CONFIG                                  \
    {                                                    \
        .scl = SOFT_I2C2_SCL_PIN,                        \
        .sda = SOFT_I2C2_SDA_PIN,                        \
        .bus_name = "i2c2soft",                          \
    }
#endif

#ifdef BSP_USING_SOFT_I2C3
#define I2C3_BUS_CONFIG                                  \
    {                                                    \
        .scl = SOFT_I2C3_SCL_PIN,                        \
        .sda = SOFT_I2C3_SDA_PIN,                        \
        .bus_name = "i2c3soft",                          \
    }
#endif

int rt_hw_i2c_init(void);

#endif
