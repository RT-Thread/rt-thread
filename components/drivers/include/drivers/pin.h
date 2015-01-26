/*
 * File      : pin.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
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
 * 2015-01-20     Bernard      the first version
 */

#ifndef PIN_H__
#define PIN_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* pin device and operations for RT-Thread */
struct rt_device_pin
{
    struct rt_device parent;
    const struct rt_pin_ops *ops;
};

#define PIN_LOW                 0x00
#define PIN_HIGH                0x01

#define PIN_MODE_OUTPUT         0x00
#define PIN_MODE_INPUT          0x01
#define PIN_MODE_INPUT_PULLUP   0x02

struct rt_device_pin_mode
{
    rt_uint16_t pin;
    rt_uint16_t mode;
};
struct rt_device_pin_status
{
    rt_uint16_t pin;
    rt_uint16_t status;
};

struct rt_pin_ops
{
    void (*pin_mode)(struct rt_device *device, rt_base_t pin, rt_base_t mode);
    void (*pin_write)(struct rt_device *device, rt_base_t pin, rt_base_t value);
    int (*pin_read)(struct rt_device *device, rt_base_t pin);

    /* TODO: add GPIO interrupt */
};

int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data);

void rt_pin_mode(rt_base_t pin, rt_base_t mode);
void rt_pin_write(rt_base_t pin, rt_base_t value);
int  rt_pin_read(rt_base_t pin);

#ifdef __cplusplus
}
#endif

#endif
