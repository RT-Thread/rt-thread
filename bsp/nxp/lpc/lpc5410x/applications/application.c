/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

extern int demo_init(void);

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_FINSH
    /* initialization finsh shell Component */
    finsh_system_init();
#endif

    demo_init();
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
