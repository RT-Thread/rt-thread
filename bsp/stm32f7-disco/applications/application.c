/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup.
 */

#include <rtthread.h>
#include <components.h>

#include "drv_led.h"

static void led_thread_entry(void *parameter)
{

    led_hw_init();

    while (1)
    {
        led_on();
        rt_thread_delay(RT_TICK_PER_SECOND);
        led_off();
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

void rt_init_thread_entry(void *parameter)
{

    rt_thread_t tid;

    rt_components_init();

    tid = rt_thread_create("led",
                           led_thread_entry, RT_NULL,
                           512, 12, 5);

    if (tid != RT_NULL)
        rt_thread_startup(tid);
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

/*@}*/
