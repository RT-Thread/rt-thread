/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

/* thread phase init */
static void rt_init_thread_entry(void *parameter)
{
    /* do component initialization */
    rt_components_init();

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

