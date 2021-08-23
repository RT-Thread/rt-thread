/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-25     AisinoChip   the first version
 */

#ifndef __LED_H__
#define __LED_H__

#include <rtthread.h>

void rt_hw_led_init(void);
void rt_hw_led_on(rt_uint32_t led);
void rt_hw_led_off(rt_uint32_t led);
void rt_hw_led_toggle(rt_uint32_t led);

#endif
