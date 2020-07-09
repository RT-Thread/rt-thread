/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#ifndef __LED_H__
#define __LED_H__

#include <rtthread.h>

enum LED_NUM
{
    LED_BLUE,
    LED_RED,
    LED_GREEN,
    LED_MAX
};

void rt_hw_led_init(void);
void rt_hw_led_uninit(void);
void rt_hw_led_on(rt_uint32_t n);
void rt_hw_led_off(rt_uint32_t n);

#endif /* end  of __LED_H__ */
