/*
 * File      : application.c
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
/**
 * @addtogroup NUVOTON_M451
 */

/*@{*/

#include <stdio.h>

#include <board.h>
#include <rtthread.h>

#include "led.h"

/* led thread entry */
static void led_thread_entry(void* parameter)
{
    rt_hw_led_init();
	while(1)
	{
        rt_hw_led_on();
        rt_thread_delay(RT_TICK_PER_SECOND);
        rt_hw_led_off();
        rt_thread_delay(RT_TICK_PER_SECOND);
	}
}

static void rt_init_thread_entry(void* parameter)
{
	rt_thread_t led_thread;

/* Initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif

    /* Create led thread */
    led_thread = rt_thread_create("led",
    		led_thread_entry, RT_NULL,
    		256, 20, 20);
    if(led_thread != RT_NULL)
    	rt_thread_startup(led_thread);
}

int rt_application_init()
{
	rt_thread_t init_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   512, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   512, 80, 20);
#endif
    if(init_thread != RT_NULL)
    	rt_thread_startup(init_thread);

    return 0;
}


/*@}*/
