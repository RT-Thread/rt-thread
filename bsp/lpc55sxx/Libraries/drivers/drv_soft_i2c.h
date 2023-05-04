/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-11     linshrie     first version
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <drv_pin.h>

/* Notice: PIO0_15(scl) --> 22; PIO1_8(sda) --> 24 */

#define BSP_SOFT_I2C1_SCL_PIN GET_PINS(0,15)
#define BSP_SOFT_I2C1_SCL_PIN GET_PINS(1,8)

/* Notice: PIO0_18(scl) --> 56; PIO1_10(sda) --> 40 */

#define BSP_SOFT_I2C2_SCL_PIN GET_PINS(0,18)
#define BSP_SOFT_I2C2_SDA_PIN GET_PINS(1,10)

/* lpc55s69 config class */
struct lpc55s69_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};
/* lpc55s69 i2c dirver class */
struct lpc55s69_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c2_bus;
};

#ifdef BSP_USING_SOFT_I2C1
#define SOFT_I2C1_BUS_CONFIG                             \
    {                                                    \
        .scl = BSP_SOFT_I2C1_SCL_PIN,                    \
        .sda = BSP_SOFT_I2C1_SDA_PIN,                    \
        .bus_name = "i2c1",                              \
    }
#endif

#ifdef BSP_USING_SOFT_I2C2
#define SOFT_I2C2_BUS_CONFIG                             \
    {                                                    \
        .scl = BSP_SOFT_I2C2_SCL_PIN,                    \
        .sda = BSP_SOFT_I2C2_SDA_PIN,                    \
        .bus_name = "i2c2",                              \
    }
#endif /*BSP_USING_I2C2*/

int rt_hw_i2c_init(void);

#endif
