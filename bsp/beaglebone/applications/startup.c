/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-05     Bernard      the first version
 * 2015-11-11     zchong     support iar compiler
 */

#include <rthw.h>
#include <rtthread.h>

#include <board.h>

extern int  rt_application_init(void);
#ifdef __ICCARM__
#pragma section="HEAP"
#endif
/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* initialzie hardware interrupt */
	rt_hw_interrupt_init();

	/* initialize board */
	rt_hw_board_init();
	/* show RT-Thread version */
	rt_show_version();

	/* initialize memory system */
#ifdef RT_USING_HEAP
#ifdef __ICCARM__
rt_system_heap_init(__segment_end("HEAP"), (void*)0x8FFFFFFF);
#else
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif
#endif

	/* initialize scheduler system */
	rt_system_scheduler_init();

    /* initialize timer */
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
