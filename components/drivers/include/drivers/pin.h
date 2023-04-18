/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-20     Bernard      the first version
 * 2017-10-20      ZYH          add mode open drain and input pull down
 */

#ifndef PIN_H__
#define PIN_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* pin device and operations for RT-Thread */
struct rt_device_pin
{
    struct rt_device parent;
    const struct rt_pin_ops *ops;
};

#define PIN_NONE                (-1)

#define PIN_LOW                 0x00
#define PIN_HIGH                0x01

#define PIN_MODE_OUTPUT         0x00
#define PIN_MODE_INPUT          0x01
#define PIN_MODE_INPUT_PULLUP   0x02
#define PIN_MODE_INPUT_PULLDOWN 0x03
#define PIN_MODE_OUTPUT_OD      0x04

#define PIN_IRQ_MODE_RISING             0x00
#define PIN_IRQ_MODE_FALLING            0x01
#define PIN_IRQ_MODE_RISING_FALLING     0x02
#define PIN_IRQ_MODE_HIGH_LEVEL         0x03
#define PIN_IRQ_MODE_LOW_LEVEL          0x04

#define PIN_IRQ_DISABLE                 0x00
#define PIN_IRQ_ENABLE                  0x01

#define PIN_IRQ_PIN_NONE                PIN_NONE

struct rt_device_pin_mode
{
    rt_base_t pin;
    rt_uint8_t mode; /* e.g. PIN_MODE_OUTPUT */
};

struct rt_device_pin_value
{
    rt_base_t pin;
    rt_uint8_t value; /* PIN_LOW or PIN_HIGH */
};

struct rt_pin_irq_hdr
{
    rt_base_t        pin;
    rt_uint8_t       mode; /* e.g. PIN_IRQ_MODE_RISING */
    void (*hdr)(void *args);
    void             *args;
};
struct rt_pin_ops
{
    void (*pin_mode)(struct rt_device *device, rt_base_t pin, rt_uint8_t mode);
    void (*pin_write)(struct rt_device *device, rt_base_t pin, rt_uint8_t value);
    rt_int8_t  (*pin_read)(struct rt_device *device, rt_base_t pin);
    rt_err_t (*pin_attach_irq)(struct rt_device *device, rt_base_t pin,
            rt_uint8_t mode, void (*hdr)(void *args), void *args);
    rt_err_t (*pin_detach_irq)(struct rt_device *device, rt_base_t pin);
    rt_err_t (*pin_irq_enable)(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled);
    rt_base_t (*pin_get)(const char *name);
};

int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data);
void rt_pin_mode(rt_base_t pin, rt_uint8_t mode);
void rt_pin_write(rt_base_t pin, rt_uint8_t value);
rt_int8_t rt_pin_read(rt_base_t pin);
rt_base_t rt_pin_get(const char *name);
rt_err_t rt_pin_attach_irq(rt_base_t pin, rt_uint8_t mode,
                           void (*hdr)(void *args), void  *args);
rt_err_t rt_pin_detach_irq(rt_base_t pin);
rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint8_t enabled);

#ifdef __cplusplus
}
#endif

#endif
