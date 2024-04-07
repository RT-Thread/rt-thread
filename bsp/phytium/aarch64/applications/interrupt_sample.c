/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-24     yangjie      the first version
 * 2020-10-17     Meco Man     translate to English comment
 */

/*
 * Demo: interrupt
 *
 * This demo demonstrates how to disable and enable interrupt to access global variable.
 *
 * read more:
 *    https://www.rt-thread.io/document/site/interrupt/interrupt/
 */

#include <rthw.h>
#include <rtthread.h>

#define THREAD_PRIORITY      20
#define THREAD_STACK_SIZE    2048
#define THREAD_TIMESLICE     5

/* global variable */
static volatile rt_uint32_t cnt;

/* thread entry function */
/* threads #1 and #2 share one entry, but the entry parameter is different */
static void thread_entry(void *parameter)
{
    rt_uint32_t no;
    rt_uint32_t level;

    no = (rt_uint32_t) parameter;

    while (1)
    {
        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        cnt += no; /* critical sections (or critical region) */

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        rt_kprintf("protect thread[%d]'s counter is %d\n", no, cnt);
        rt_thread_mdelay(no * 10);
    }
}

int interrupt_sample(void)
{
    rt_thread_t thread;

    /* create thread #1 */
    thread = rt_thread_create("thread1", thread_entry, (void *)10,
                              THREAD_STACK_SIZE,
                              THREAD_PRIORITY, THREAD_TIMESLICE);
#ifdef RT_USING_SMP
    /* Bind threads to the same core to avoid messy log output when multiple cores are enabled */
    rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
#endif
    if (thread != RT_NULL)
        rt_thread_startup(thread); /* start thread #1 */

    /* create thread #2 */
    thread = rt_thread_create("thread2", thread_entry, (void *)20,
                              THREAD_STACK_SIZE,
                              THREAD_PRIORITY, THREAD_TIMESLICE);
#ifdef RT_USING_SMP
    /* Bind threads to the same core to avoid messy log output when multiple cores are enabled */
    rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
#endif
    if (thread != RT_NULL)
        rt_thread_startup(thread); /* start thread #2 */

    return 0;
}

/* export the msh command */
MSH_CMD_EXPORT(interrupt_sample, interrupt sample);
