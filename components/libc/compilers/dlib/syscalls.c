/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-13     Meco Man     implement exit() and abort()
 */
#include <rtthread.h>

void exit (int status)
{
    rt_thread_t self = rt_thread_self();

#ifdef RT_USING_MODULE
    if (dlmodule_self())
    {
        dlmodule_exit(status);
    }
#endif

    if (self != RT_NULL)
    {
        rt_kprintf("thread:%-8.*s exit:%d!\n", RT_NAME_MAX, self->name, status);
        rt_thread_suspend(self);
        rt_schedule();
    }

    while(1); /* noreturn */
}

void abort(void)
{
    rt_thread_t self = rt_thread_self();

#ifdef RT_USING_MODULE
    if (dlmodule_self())
    {
        dlmodule_exit(-1);
    }
#endif

    if (self != RT_NULL)
    {
        rt_kprintf("thread:%-8.*s abort!\n", RT_NAME_MAX, self->name);
        rt_thread_suspend(self);
        rt_schedule();
    }

    while(1); /* noreturn */
}
