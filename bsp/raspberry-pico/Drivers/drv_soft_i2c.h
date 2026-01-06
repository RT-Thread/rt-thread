/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/01     chushicheng  first version
 */

#ifndef __DRV_SOFT_I2C__
#define __DRV_SOFT_I2C__

#include <rtdevice.h>
#include "drv_gpio.h"
#include "board.h"

#ifdef BSP_USING_SOFT_I2C
/* pico i2c dirver class */
struct pico_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

/* pico config class */
struct pico_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};

#ifdef BSP_USING_SOFT_I2C1
#define I2C1_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_SOFT_I2C1_SCL_PIN,                    \
        .sda = BSP_SOFT_I2C1_SDA_PIN,                    \
        .bus_name = "i2c1",                              \
    }
#endif

int rt_soft_i2c_init(void);

#endif /* BSP_USING_SOFT_I2C */
#endif
