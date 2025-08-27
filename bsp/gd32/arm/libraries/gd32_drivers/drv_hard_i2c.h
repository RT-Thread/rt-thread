/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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
    uint32_t i2c_periph;             //Todo: 3bits

    rcu_periph_enum per_clk;         //Todo: 5bits
    rcu_periph_enum scl_gpio_clk;    //Todo: 5bits
    rcu_periph_enum sda_gpio_clk;    //Todo: 5bits

    uint32_t scl_port;               //Todo: 4bits
    uint16_t scl_af;                 //Todo: 4bits
    uint16_t scl_pin;                //Todo: 4bits
    
    uint32_t sda_port;               //Todo: 4bits
    uint16_t sda_af;                 //Todo: 4bits
    uint16_t sda_pin;                //Todo: 4bits

    struct rt_i2c_bus_device *i2c_bus;
    char *device_name;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_I2C__ */
