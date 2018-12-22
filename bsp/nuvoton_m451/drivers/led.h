/*
 * File      : led.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-12-05     Pluto        first implementation
 */

#ifndef __LED_H__
#define __LED_H__

#include <rthw.h>
#include <rtthread.h>
#include "M451Series.h"

void rt_hw_led_on(void); 
void rt_hw_led_off(void);
int rt_hw_led_init(void);

#endif
