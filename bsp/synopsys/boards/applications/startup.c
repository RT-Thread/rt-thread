/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include <rt_board.h>

#ifdef RT_USING_HEAP
#define rt_system_heap_size 1024*64
static rt_uint32_t rt_system_heap[rt_system_heap_size/4] = {0};
#endif

extern int rt_application_init(void);

void rt_hw_interrupt_init(void)
{
    /* rt-thread specific interrupt and exception init */
}

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize board */
    rt_hw_board_init();

    /* show RT-Thread version */
    rt_show_version();

    /* initialize memory system */
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)rt_system_heap, (void *)(rt_system_heap+rt_system_heap_size));
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();

    /* initialize system timer */
    rt_system_timer_init();

    /* initialize soft timer thread */
    rt_system_timer_thread_init();

    /* initialize application */
    rt_application_init();

    /* initialize idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* invoke rtthread_startup */
    rtthread_startup();

    return 0;
}

