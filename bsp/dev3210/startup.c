/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <cache.h>

#include "board.h"
#define A_K0BASE		0x80000000

/**
 * @addtogroup Loongson SoC3210
 */

/*@{*/
extern unsigned char __bss_start;
extern unsigned char __bss_end;

extern int rt_application_init(void);

extern void tlb_refill_exception(void);
extern void general_exception(void);
extern void irq_exception(void);

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* init cache */
	rt_hw_cache_init();
	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* copy vector */
	memcpy((void *)A_K0BASE, tlb_refill_exception, 0x20);
	memcpy((void *)(A_K0BASE + 0x180), general_exception, 0x20);
	memcpy((void *)(A_K0BASE + 0x200), irq_exception, 0x20);

	/* init board */
	rt_hw_board_init();
	rt_show_version();

	/* init tick */
	rt_system_tick_init();

	/* init timer system */
	rt_system_timer_init();

#ifdef RT_USING_HEAP
	rt_system_heap_init((void*)&__bss_end, (void*)RT_HW_HEAP_END);
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

	/* init application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
	finsh_set_device(FINSH_DEVICE_NAME);
#endif

	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;
}

/*@}*/
