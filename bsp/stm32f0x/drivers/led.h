/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-13-05     bright       the first version
 */

#ifndef __LED_H__
#define __LED_H__

#include <rtthread.h>
#include <stm32f0xx.h>

#define rt_hw_led_on()   GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define rt_hw_led_off()  GPIO_ResetBits(GPIOC, GPIO_Pin_9)

int rt_hw_led_init(void);

#endif

