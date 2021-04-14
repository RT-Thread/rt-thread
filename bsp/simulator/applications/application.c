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
#include <stdio.h>
#include <board.h>

extern int platform_init(void);
extern int platform_post_init(void);
extern int mnt_init(void);

void rt_init_thread_entry(void *parameter)
{
    rt_kprintf("Hello RT-Thread!\n");

    platform_init();
    mnt_init();

    platform_post_init();

#if defined(PKG_USING_GUIENGINE) && defined(GUIENGINE_USING_DEMO)
    {
        extern int rt_gui_demo_init(void);
        rt_gui_demo_init();
    }
#endif
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
