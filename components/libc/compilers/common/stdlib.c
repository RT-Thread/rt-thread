/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-15     Meco Man     first version
 */

#include <rtthread.h>

#define  ABORT_STATUS   2

void __exit__(int status)
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
        if(status == ABORT_STATUS) /* abort() */
        {
            rt_kprintf("thread:%s abort!\n", RT_NAME_MAX, self->name);
        }
        else /* exit() */
        {
            rt_kprintf("thread:%s exit:%d!\n", RT_NAME_MAX, self->name, status);
        }
        rt_thread_suspend(self);
        rt_schedule();
    }
}

void __abort__(void)
{
    __exit__(ABORT_STATUS);
}

int __system__(const char *string)
{
    /* TODO */
    return 0;
}
