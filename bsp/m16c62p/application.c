/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-04-09     fify         modified for M16C
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
*/

#include <rtthread.h>
#include "bsp.h"

static struct rt_thread led;

static rt_uint8_t led_stack[256];

static void rt_thread_entry_led(void* parameter)
{
    while (1)
    {
        /* led off */
        led_off();
        rt_thread_delay(100); /* sleep 1 second and switch to other thread */
        /* led on */
        led_on();
        rt_thread_delay(100);
    }
}

int rt_application_init(void)
{
    /* create led thread */
	rt_thread_init(&led,
		"led",
		rt_thread_entry_led, RT_NULL,
		&led_stack[0], sizeof(led_stack),
		5, 32);
    
    if (&led != RT_NULL)
        rt_thread_startup(&led);
        
    return 0;
}
