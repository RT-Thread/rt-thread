/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * 2013-7-14      Peng Fan     Modified from mini4020
 */

#include <rthw.h>
#include <rtthread.h>

#include <board.h>
#include <serial.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <netif/ethernetif.h>
#endif

#include <sep6200.h>

rt_uint8_t _irq_stack_start[1024];
rt_uint8_t _fiq_stack_start[1024];
rt_uint8_t _undefined_stack_start[512];
rt_uint8_t _abort_stack_start[512];
rt_uint8_t _priv_stack_start[4096]; SECTION(".nobss");
extern unsigned char __bss_start;
extern unsigned char __bss_end;


extern void rt_hw_board_init(void);
extern void rt_application_init(void);
extern int finsh_system_init(void);
extern void sd_init(void);

void rtthread_startup()
{
	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* init board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

	/* init tick */
	rt_system_tick_init();

	/* init kernel object */
	rt_system_object_init();

	/* init timer system */
	rt_system_timer_init();

	/* init heap memory system */
	rt_system_heap_init(&__bss_end, (void*)0x45000000);

	/* init scheduler system */
	rt_system_scheduler_init();

	/* init application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
#ifdef RT_USING_DEVICE
	finsh_set_device("uart0");
#endif
#endif

  rt_system_timer_thread_init();

	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return ;

}
