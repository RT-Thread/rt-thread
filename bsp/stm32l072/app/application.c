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
 * 2013-11-15     bright       add init thread and components initial
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <stdio.h>
#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include <rtthread.h>

static void rt_init_thread_entry(void* parameter)
{
extern void led_thread_entry(void* parameter);
	rt_thread_t thread;

/* Initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif

/* Set finsh device */
#ifdef  RT_USING_FINSH
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif  /* RT_USING_FINSH */

    /* Create led thread */
    thread = rt_thread_create("led",
		led_thread_entry, RT_NULL,
		256, 20, 20);
    if(thread != RT_NULL)
	rt_thread_startup(thread);
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
