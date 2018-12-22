/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-05     Bernard      the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <board.h>

extern int  rt_application_init(void);
extern void rt_hw_board_init(void);

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    // platform_init();
    // print_version();

    /* initialzie hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize board */
    rt_hw_board_init();

    /* show RT-Thread version */
    rt_show_version();

    /* initialize memory system */
#ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();

    /* initialize timer and soft timer thread */
    rt_system_timer_init();
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
