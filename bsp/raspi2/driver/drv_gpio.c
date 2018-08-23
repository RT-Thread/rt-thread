/*
 * File      : drv_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "drv_gpio.h"

static void hw_pin_mode(struct rt_device *device, rt_base_t pin, rt_base_t mode)
{
    return ;
}

static void hw_pin_write(struct rt_device *device, rt_base_t pin, rt_base_t value)
{
    return ;
}

static int hw_pin_read(struct rt_device *device, rt_base_t pin)
{
    return 0;
}

static rt_err_t hw_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                  rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    return RT_EOK;
}

static rt_err_t hw_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    return RT_EOK;
}

static rt_err_t hw_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    return RT_EOK;
}

struct rt_pin_ops _hw_pin_ops =
{
    hw_pin_mode,
    hw_pin_write,
    hw_pin_read,

    hw_pin_attach_irq,
    hw_pin_detach_irq,
    hw_pin_irq_enable
};

int hw_gpio_init(void)
{
    rt_device_pin_register("gpio", &_hw_pin_ops , RT_NULL);

    return 0;
}
INIT_BOARD_EXPORT(hw_gpio_init);
