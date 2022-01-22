/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-10-28     luhuadong         first version
 */

#include <rtdevice.h>
#include <hifive1.h>
#include <platform.h>
#include <gpio.h>
#include "led.h"

#define USER_LED_OFFSET    5

static void _led_init(rt_uint8_t offset)
{
    GPIO_REG(GPIO_IOF_EN) &= ~(1UL << offset);

    GPIO_REG(GPIO_OUTPUT_EN) |= (1UL << offset);
}

static void _led_set(rt_uint8_t offset, rt_uint8_t val)
{
    switch (val)
    {
        case LED_ON:
            GPIO_REG(GPIO_OUTPUT_VAL) |= (1UL << offset);
            break;
        case LED_OFF:
            GPIO_REG(GPIO_OUTPUT_VAL) &= ~(1UL << offset);
            break;
        default:
            break;
    }
}

static void _led_toggle(rt_uint8_t offset)
{
    GPIO_REG(GPIO_OUTPUT_VAL) ^= (1UL << offset);
}

void led_init(void)
{
    _led_init(USER_LED_OFFSET);
}

void led_set(rt_uint8_t val)
{
    _led_set(USER_LED_OFFSET, val);
}

void led_toggle(void)
{
    _led_toggle(USER_LED_OFFSET);
}
