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
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 */

#include <rtthread.h>

void init_thread(void* parameter)
{
    rt_components_init();
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init", init_thread, RT_NULL, 
        1024, RT_THREAD_PRIORITY_MAX/3, 10);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}

