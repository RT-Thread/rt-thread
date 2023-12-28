/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2023/12/01     Raman Gopalan    First version
 */

#ifndef __DRV_SOFT_I2C__
#define __DRV_SOFT_I2C__

#include <rtdevice.h>
#include "drv_gpio.h"
#include "gpio.h"

#ifdef BSP_USING_SOFT_I2C
/* AVR32 software I2C driver class */
struct avr32_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c_bus;
};

/* AVR32 config class */
struct avr32_soft_i2c_config
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

int rt_sw_i2c_init(void);

#endif /* BSP_USING_SOFT_I2C */
#endif /* #ifndef __DRV_SOFT_I2C__ */
