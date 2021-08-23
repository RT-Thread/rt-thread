/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     AisinoChip   first implementation
 */

#include <rtthread.h>
#include "board.h"

#define led1_gpio                   GPIOA
#define led1_pin                    (GPIO_PIN_1)

void rt_hw_led_init(void)
{
    GPIO_InitTypeDef GPIO_Handle;

    GPIO_Handle.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_Handle.Pull      = GPIO_PULLUP;
    GPIO_Handle.Alternate = GPIO_FUNCTION_0;

    GPIO_Handle.Pin       = led1_pin;
    HAL_GPIO_Init(led1_gpio, &GPIO_Handle);
}

void rt_hw_led_on(rt_uint32_t n)
{
    switch (n)
    {
    case 0:
        HAL_GPIO_WritePin(led1_gpio, led1_pin, GPIO_PIN_SET);
        break;
    default:
        break;
    }
}

void rt_hw_led_off(rt_uint32_t n)
{
    switch (n)
    {
    case 0:
        HAL_GPIO_WritePin(led1_gpio, led1_pin, GPIO_PIN_CLEAR);
        break;
    default:
        break;
    }
}

void rt_hw_led_toggle(rt_uint32_t n)
{
    static rt_bool_t stat = RT_TRUE;

    if (stat == RT_TRUE)
    {
        rt_hw_led_on(n);
        stat = RT_FALSE;
    }
    else
    {
        rt_hw_led_off(n);
        stat = RT_TRUE;
    }
}
