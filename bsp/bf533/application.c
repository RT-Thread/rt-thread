/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date         Author      Notes
 * 2012-02-13   mojingxian  first version
 */

#include "application.h"
#include "board.h"
#include "rtthread.h"

void app_init_entry(void *parg)
{
    parg = parg;

    rt_hw_core_timer_init();//start system tick in first thread.

    rt_hw_isr_install();
}


void rt_application_init(void)
{
    rt_thread_t led_thread;

#ifdef RT_USING_HEAP
    led_thread = rt_thread_create("init", app_init_entry, RT_NULL, 512, 200, 20);
#endif

    if (led_thread != RT_NULL)
    {
        rt_thread_startup(led_thread);
    }
}
