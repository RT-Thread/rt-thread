/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
