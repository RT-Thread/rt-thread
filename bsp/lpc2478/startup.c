/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    first version
 */

#include <rtthread.h>
#include <rthw.h>

#include <LPC24xx.h>
#include <board.h>

/**
 * @addtogroup LPC2478
 */
/*@{*/

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#else
extern char __rodata_start[];
extern char __rodata_end[];
extern char __data_start[];
extern char __bss_start[];
extern char __data_end[];
extern char __bss_end[];
extern char __Heap_start[];
extern char __Heap_end[];
#endif

#ifdef RT_USING_FINSH
extern void finsh_system_init(void);
#endif
extern int  rt_application_init(void);

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* init hardware Target */
	// TargetResetInit();

	/* init hardware interrupt */
	rt_hw_interrupt_init();
	
	/* init board */
	rt_hw_board_init();
	
	rt_show_version();

	/* init tick */
	rt_system_tick_init();
	
	/* init kernel object */
	rt_system_object_init();
	
	/* init timer system */
	rt_system_timer_init();

	/* init memory system */
#ifdef RT_USING_HEAP
#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)0x40010000);
#else
	rt_system_heap_init((void*)__Heap_start, 0x40010000);
#endif
#endif

	/* init scheduler system */
	rt_system_scheduler_init();
	
	/* init application */
	rt_application_init();
	
#ifdef RT_USING_FINSH
	/* init the finsh input */
	rt_hw_finsh_init();
	
	/* init finsh */
	finsh_system_init();
#endif
	
	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();	
	
	/* never reach here */
	return ;
}

#ifdef __CC_ARM
int main(void)
{
	rtthread_startup();
	
	return 0;
}
#endif

/*@}*/
