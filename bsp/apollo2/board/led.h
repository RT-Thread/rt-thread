/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-14     Haley        the first version
 */

#ifndef __LED_H
#define __LED_H

#include <rtthread.h>

/**
 * @brief External function definitions
 *
 */
void rt_hw_led_init(void);
void rt_hw_led_on(rt_uint8_t LEDNum);
void rt_hw_led_off(rt_uint8_t LEDNum);

#endif // __LED_H
