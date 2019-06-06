/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>

<<<<<<< HEAD
void rt_init_thread_entry(void* parameter)
{
    /* initialization RT-Thread Components */
    rt_components_init();
	
=======
#ifdef RT_USING_FINSH
#include "shell.h"
#endif

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_FINSH
    finsh_system_init();
#endif
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
