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

void __rt_libc_exit(int status)
{
    rt_thread_t self = rt_thread_self();

    if (self != RT_NULL)
    {
        rt_kprintf("thread:%s exit:%d!\n", self->name, status);
        rt_thread_control(self, RT_THREAD_CTRL_CLOSE, RT_NULL);
    }
}

int __rt_libc_system(const char *string)
{
    /* TODO */
    return 0;
}
