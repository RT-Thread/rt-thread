/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-23     Bright      first implementation
 */

#include "led.h"



/* Initial led gpio pin  */
int rt_hw_led_init(void)
{

    return 0;
}

void rt_hw_led_on(void)
{

}

void rt_hw_led_off(void)
{
  
}

/* Initial components for device */
INIT_DEVICE_EXPORT(rt_hw_led_init);
