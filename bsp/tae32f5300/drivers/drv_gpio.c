/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-05     qinweizhong   first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <tae32f53xx_ll_gpio.h>
#include <tae32f53xx_ll_cortex.h>
#include "drv_gpio.h"

#define TAE32_PIN(index, gpio, gpio_index)                                                                                    \
{                                                                                                                             \
    0,  GPIO##gpio, GPIO_PIN_##gpio_index \
}

#define TAE32_PIN_DEFAULT  \
{                     \
    -1, 0, 0 \
}

/* TAE32 GPIO driver */
struct pin_index
{
    int index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index _pin_map[] =
{
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
    TAE32_PIN(2, C, 13),
    TAE32_PIN(3, C, 14),
    TAE32_PIN(4, C, 15),
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
    TAE32_PIN(10, A, 0),
    TAE32_PIN(11, A, 1),
    TAE32_PIN(12, A, 2),
    TAE32_PIN(13, A, 3),
    TAE32_PIN(14, A, 4),
    TAE32_PIN(15, A, 5),
    TAE32_PIN(16, A, 6),
    TAE32_PIN(17, A, 7),
    TAE32_PIN(18, B, 0),
    TAE32_PIN(19, B, 1),
    TAE32_PIN(20, B, 2),
    TAE32_PIN(21, B, 10),
    TAE32_PIN(22, B, 11),
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
    TAE32_PIN(25, B, 12),
    TAE32_PIN(26, B, 13),
    TAE32_PIN(27, B, 14),
    TAE32_PIN(28, B, 15),
    TAE32_PIN(29, A, 8),
    TAE32_PIN(30, A, 9),
    TAE32_PIN(31, A, 10),
    TAE32_PIN(32, A, 11),
    TAE32_PIN(33, A, 12),
    TAE32_PIN(34, A, 13),
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
    TAE32_PIN(37, A, 14),
    TAE32_PIN(38, A, 15),
    TAE32_PIN(39, B, 3),
    TAE32_PIN(40, B, 4),
    TAE32_PIN(41, B, 5),
    TAE32_PIN(42, B, 6),
    TAE32_PIN(43, B, 7),
    TAE32_PIN_DEFAULT,
    TAE32_PIN(45, B, 8),
    TAE32_PIN(46, B, 9),
    TAE32_PIN_DEFAULT,
    TAE32_PIN_DEFAULT,
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(_pin_map))
    {
        index = &_pin_map[pin];
        if (index->gpio == 0)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }
    return index;
};

void _pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    if (value == PIN_LOW)
    {
        LL_GPIO_WritePin(index->gpio, index->pin, GPIO_PIN_RESET);
    }
    else
    {
        LL_GPIO_WritePin(index->gpio, index->pin, GPIO_PIN_SET);
    }
}

rt_int8_t _pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_int8_t value;
    const struct pin_index *index;

    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return PIN_LOW;
    }
    if (LL_GPIO_ReadPin(index->gpio, index->pin) == GPIO_PIN_RESET)
    {
        value = PIN_LOW;
    }
    else
    {
        value = PIN_HIGH;
    }
    return value;
}

void _pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    GPIO_InitTypeDef GPIO_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.Pin = index->pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStructure.OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT;
        GPIO_InitStructure.OType = GPIO_OTYPE_PP;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT;
        GPIO_InitStructure.OType = GPIO_OTYPE_OD;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    }
    else
    {
        /* input setting:default. */
        GPIO_InitStructure.Pull = GPIO_PULLDOWN;
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    }
    LL_GPIO_Init(index->gpio, &GPIO_InitStructure);
}

rt_err_t _pin_attach_irq(struct rt_device *device, rt_base_t pin,
                              rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    return -RT_ERROR;
}

rt_err_t _pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    return -RT_ERROR;
}

rt_err_t _pin_irq_enable(struct rt_device *device, rt_base_t pin,
                              rt_uint8_t enabled)
{
    return -RT_ERROR;
}

const static struct rt_pin_ops _pin_ops =
{
    _pin_mode,
    _pin_write,
    _pin_read,
    _pin_attach_irq,
    _pin_detach_irq,
    _pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);
