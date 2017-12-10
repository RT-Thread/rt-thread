/*
 * File      : drv_gpio.c
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
 * 2017-11-24     ÇÚÎª±¾       first version
 */

#include <rtthread.h>
#include <drivers/pin.h>
#include "../libraries/ls1c_gpio.h"


void ls1c_pin_mode(struct rt_device *device, rt_base_t pin, rt_base_t mode)
{
    unsigned int gpio = pin;
    
    if (PIN_MODE_OUTPUT == mode)
    {
        gpio_init(gpio, gpio_mode_output);
    }
    else
    {
        gpio_init(gpio, gpio_mode_input);
    }

    return ;
}


void ls1c_pin_write(struct rt_device *device, rt_base_t pin, rt_base_t value)
{
    unsigned int gpio = pin;
    
    if (PIN_LOW == value)
    {
        gpio_set(gpio, gpio_level_low);
    }
    else
    {
        gpio_set(gpio, gpio_level_high);
    }

    return ;
}


int ls1c_pin_read(struct rt_device *device, rt_base_t pin)
{
    unsigned int gpio = pin;
    int value = PIN_LOW;

    if (0 == gpio_get(gpio))
    {
        value = PIN_LOW;
    }
    else
    {
        value = PIN_HIGH;
    }

    return value;
}


const static struct rt_pin_ops _ls1c_pin_ops = 
{
    ls1c_pin_mode,
    ls1c_pin_write,
    ls1c_pin_read,
};


int hw_pin_init(void)
{
    rt_device_pin_register("pin", &_ls1c_pin_ops, RT_NULL);
    return 0;
}
INIT_BOARD_EXPORT(hw_pin_init);


