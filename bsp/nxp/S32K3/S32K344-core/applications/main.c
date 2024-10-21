/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-16     Pillar       first version
 */

#include <rtthread.h>
#include <board.h>

void print_thread(void *parameter)
{
    while (1)
    {
        rt_kprintf("hello\n");
        rt_thread_mdelay(2000);
    }
}

int main(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("print", print_thread, RT_NULL, 512, 16, 10);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}
