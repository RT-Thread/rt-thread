/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "mb9bf506r.h"
/**
 * @addtogroup FM3
 */

/*@{*/

extern int  rt_application_init(void);

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#elif __ICCARM__
#pragma section="HEAP"
#else
extern int __bss_end;
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* init board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

	/* init timer system */
	rt_system_timer_init();

#ifdef RT_USING_HEAP
	#ifdef __CC_ARM
		rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)FM3_SRAM_END);
	#elif __ICCARM__
		rt_system_heap_init(__segment_end("HEAP"), (void*)FM3_SRAM_END);
	#else
		/* init memory system */
		rt_system_heap_init((void*)&__bss_end, (void*)FM3_SRAM_END);
	#endif
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

#ifdef RT_USING_DEVICE
	/* init all device */
	rt_device_init_all();
#endif

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

int main(void)
{
	/* disable interrupt first */
	rt_hw_interrupt_disable();

	/* init system setting */
	SystemInit();
    
	/* startup RT-Thread RTOS */
	rtthread_startup();

	return 0;
}

/*@}*/
