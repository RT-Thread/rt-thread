/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */


#include <rtthread.h>

#include <cp15.h>

/* thread phase init */
static void rt_init_thread_entry(void *parameter)
{
    /* do component initialization */
    rt_components_init();
    rt_kprintf("running on cpu %d\n",
               rt_cpu_get_smp_id() & 0x0f);

    /* add your initialization here */
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 2048,
                            RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

