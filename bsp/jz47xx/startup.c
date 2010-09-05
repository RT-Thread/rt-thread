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
 * 2010-06-25     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

/**
 * @addtogroup jz47xx
 */

/*@{*/
extern unsigned char __bss_start;
extern unsigned char __bss_end;

extern int rt_application_init(void);

void dump_memory(rt_uint8_t* ptr, rt_size_t size)
{
	rt_size_t index;

	for (index = 0; index < size; index ++)
	{
		rt_kprintf("%02x ", ptr[index] & 0xff);
		if ((index + 1) % 16 == 0) rt_kprintf("\n");
	}
}

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

	dump_memory((rt_uint8_t*)0x80000200, 32);

	/* init tick */
	rt_system_tick_init();

	/* init timer system */
	rt_system_timer_init();

#ifdef RT_USING_HEAP
	rt_system_heap_init((void*)&__bss_end, (void*)RT_HW_HEAP_END);
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

#ifdef RT_USING_DEVICE
	/* init all device */
	rt_device_init_all();
#endif

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
