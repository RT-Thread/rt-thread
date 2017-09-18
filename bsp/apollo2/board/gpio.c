/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-09-16     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"

#ifdef RT_USING_PIN

void am_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_OUTPUT);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_INPUT);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_OPENDRAIN);
    }
    else
    {
        /* input setting:default. */
        am_hal_gpio_pin_config(pin, AM_HAL_GPIO_INPUT);
    }
}

void am_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    if (value == PIN_LOW)
    {
        am_hal_gpio_out_bit_clear(pin);
    }
    else
    {
        am_hal_gpio_out_bit_set(pin);
    }
}

int am_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value = PIN_LOW;

    if (am_hal_gpio_input_bit_read(pin) == 0)
    {
        value = PIN_LOW;
    }
    else
    {
        value = PIN_HIGH;
    }

    return value;
}

const static struct rt_pin_ops _am_pin_ops =
{
    am_pin_mode,
    am_pin_write,
    am_pin_read,
};

int hw_pin_init(void)
{
    rt_device_pin_register("pin", &_am_pin_ops, RT_NULL);
    return 0;
}

INIT_BOARD_EXPORT(hw_pin_init);
#endif

/*@}*/
