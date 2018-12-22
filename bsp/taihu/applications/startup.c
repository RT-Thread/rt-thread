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
 * 2011-04-16     nsj          first version
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
extern int finsh_system_init(void);
#endif

extern int  rt_application_init(void);
#ifdef RT_USING_DEVICE
extern rt_err_t rt_hw_serial_init(void);
#endif

extern int __heap_start;
extern int __heap_end;

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* init board */
	rt_hw_board_init();
	rt_show_version();

	/* init tick */
	rt_system_tick_init();

	/* init timer system */
	rt_system_timer_init();

	/* init memory system */
#ifdef RT_USING_HEAP
	rt_system_heap_init((void*)&__heap_start, (void*)&__heap_end);
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

	/* init application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
	finsh_set_device("uart1");
#endif

	/* init soft timer thread */
	rt_system_timer_thread_init();

	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;
}
