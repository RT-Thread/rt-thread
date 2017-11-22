/*
 * File      : drv_i2c.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-14     勤为本       first version
 */

#include <rtthread.h>
#include <drivers/i2c.h>
#include <drivers/i2c-bit-ops.h>
#include "drv_i2c.h"
#include "../libraries/ls1c_gpio.h"
#include "../libraries/ls1c_delay.h"


#define LS1C_I2C_SCL                (57)    // gpio57
#define LS1C_I2C_SDA                (56)    // gpio56

#define LS1C_SET_GPIO_MODE

static void ls1c_i2c_gpio_init(void)
{
    gpio_init(LS1C_I2C_SCL, gpio_mode_output);
    gpio_set(LS1C_I2C_SCL, gpio_level_high);

    gpio_init(LS1C_I2C_SDA, gpio_mode_output);
    gpio_set(LS1C_I2C_SDA, gpio_level_high);

    return ;
}


static void ls1c_udelay(rt_uint32_t us)
{
    delay_us((int)us);
}


static void ls1c_set_sda(void *data, rt_int32_t state)
{
#ifdef LS1C_SET_GPIO_MODE
    gpio_init(LS1C_I2C_SDA, gpio_mode_output);
    ls1c_udelay(5);
#endif
    gpio_set(LS1C_I2C_SDA, state);
    return ;
}


static void ls1c_set_scl(void *data, rt_int32_t state)
{
#ifdef LS1C_SET_GPIO_MODE
    gpio_init(LS1C_I2C_SCL, gpio_mode_output);
    ls1c_udelay(5);
#endif
    gpio_set(LS1C_I2C_SCL, state);
    return ;
}


static rt_int32_t ls1c_get_sda(void *data)
{
#ifdef LS1C_SET_GPIO_MODE
    gpio_init(LS1C_I2C_SDA, gpio_mode_input);
    ls1c_udelay(5);
#endif
    return gpio_get(LS1C_I2C_SDA);
}


static rt_int32_t ls1c_get_scl(void *data)
{
#ifdef LS1C_SET_GPIO_MODE
    gpio_init(LS1C_I2C_SCL, gpio_mode_input);
    ls1c_udelay(5);
#endif
    return gpio_get(LS1C_I2C_SCL);
}


static const struct rt_i2c_bit_ops bit_ops = {
    .data       = RT_NULL,
    .set_sda    = ls1c_set_sda,
    .set_scl    = ls1c_set_scl,
    .get_sda    = ls1c_get_sda,
    .get_scl    = ls1c_get_scl,

    .udelay     = ls1c_udelay,

    .delay_us   = 20,       // 此值为周期(us)
    .timeout    = 10,       // 单位为tick
};



int ls1c_i2c_init(void)
{
    static struct rt_i2c_bus_device bus = {0};

    bus.priv = (void *)&bit_ops;

    ls1c_i2c_gpio_init();

    rt_i2c_bit_add_bus(&bus, "i2c2");

    return RT_EOK;
}





