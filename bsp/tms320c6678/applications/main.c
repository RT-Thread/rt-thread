/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

void rt_init_thread_entry(void *parameter)
{
    rt_kprintf("hello rt-thread\n");
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 4096, 3, 200);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    } else {
        return -1;
    }

    return 0;
}

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

void main(void)
{
    /* startup RT-Thread RTOS */
    rtthread_startup();

    for(;;){}
}

