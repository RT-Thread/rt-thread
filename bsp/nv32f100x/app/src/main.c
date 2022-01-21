/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 * 2017-09-20     Quintin.Z    modify for nv32
 */
#include "rtthread.h"
#include "finsh.h"

extern void led_thread_entry(void* parameter);

int main(void)
{
    rt_thread_t thread;

#ifdef RT_USING_FINSH
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#endif

    /* Create led thread */
    thread = rt_thread_create("led",
                              led_thread_entry, RT_NULL,
                              256, 20, 20);
    if(thread != RT_NULL)
        rt_thread_startup(thread);

    return 0;
}
