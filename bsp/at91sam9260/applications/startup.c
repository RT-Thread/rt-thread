/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <at91sam926x.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif
extern void rt_hw_interrupt_init(void);
extern void rt_hw_board_init(void);
extern void rt_system_timer_init(void);
extern void rt_system_scheduler_init(void);
extern void rt_thread_idle_init(void);
extern void mmu_invalidate_icache();
extern void rt_hw_cpu_icache_enable(void);
extern void rt_show_version(void);
extern void rt_system_heap_init(void*, void*);
extern void rt_hw_finsh_init(void);
extern void rt_application_init(void);

/**
 * @addtogroup at91sam9260
 */

/*@{*/
#if defined(__CC_ARM)
	extern int Image$$ER_ZI$$ZI$$Base;
	extern int Image$$ER_ZI$$ZI$$Length;
	extern int Image$$ER_ZI$$ZI$$Limit;
#elif (defined (__GNUC__))
	rt_uint8_t _irq_stack_start[1024];
	rt_uint8_t _fiq_stack_start[1024];
	rt_uint8_t _undefined_stack_start[512];
	rt_uint8_t _abort_stack_start[512];
	rt_uint8_t _svc_stack_start[4096] SECTION(".nobss");
	extern unsigned char __bss_start;
	extern unsigned char __bss_end;
#endif

#ifdef RT_USING_FINSH
extern void finsh_system_init(void);
#endif


/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* disable interrupt first */
	rt_hw_interrupt_disable();
	/* enable cpu cache */
	rt_hw_cpu_icache_disable();
	mmu_invalidate_icache();
	rt_hw_cpu_icache_enable();

	/* initialize hardware interrupt */
	rt_hw_interrupt_init();

	/* initialize board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();
	
	/* initialize tick */
	rt_system_tick_init();

	/* initialize kernel object */
	rt_system_object_init();

	/* initialize timer system */
	rt_system_timer_init();

	/* initialize heap memory system */
#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$ER_ZI$$ZI$$Limit, (void*)0x24000000);
#else
	rt_system_heap_init((void*)&__bss_end, (void*)0x23f00000);
#endif

#ifdef RT_USING_MODULE
	/* initialize module system*/
	rt_system_module_init();
#endif

	/* initialize scheduler system */
	rt_system_scheduler_init();

	/* initialize application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
#ifdef RT_USING_DEVICE
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#endif

	/* initialize system timer thread */
	rt_system_timer_thread_init();

	/* initialize idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;
}

int main(void)
{
	/* startup RT-Thread RTOS */
	rtthread_startup();

	return 0;
}

/*@}*/
