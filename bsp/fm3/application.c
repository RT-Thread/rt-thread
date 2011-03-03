/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      the first version
 */

/**
 * @addtogroup FM3
 */
/*@{*/

#include <rtthread.h>
#include "board.h"

void rt_init_thread_entry(void *parameter)
{
    while(1)
    {
        rt_hw_led_on(LED1);
        rt_hw_led_off(LED2);
        rt_thread_delay(100);        
        rt_hw_led_off(LED1);
        rt_hw_led_on(LED2);
        rt_thread_delay(100);
    }
}

int rt_application_init()
{
    rt_thread_t init_thread;

    init_thread = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 1024, 21, 20);
    if(init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    return 0;
}

/*@}*/
