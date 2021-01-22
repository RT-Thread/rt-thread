/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include <rthw.h>
#include <rtthread.h>
#include <mmu.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#ifdef RT_USING_DMA_MEM
#include "dma_mem.h"
#endif

#include "board_def.h"

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

static struct mem_desc fh_mem_desc[] = 
{
		{ 0xA0000000, FH_RTT_OS_MEM_END-1, 0xA0000000, SECT_RWX_CB, 0, SECT_MAPPED },
		{ FH_RTT_OS_MEM_END, FH_DDR_END-1, FH_RTT_OS_MEM_END, SECT_RWNX_NCNB, 0, SECT_MAPPED },
		{ 0xFFFF0000, 0xFFFF1000-1, 0xA0000000, SECT_TO_PAGE, PAGE_ROX_CB, PAGE_MAPPED }, /* isr vector table */
		{ 0xE0000000, 0xF1300000-1, 0xE0000000, SECT_RWNX_NCNB, 0, SECT_MAPPED },       /* io table */
		{ 0xF4000000, 0xF4100000-1, 0xF4000000, SECT_RWNX_NCNB, 0, SECT_MAPPED },       /* GPIO#1 io table */
};

rt_uint8_t _irq_stack_start[1024];
rt_uint8_t _fiq_stack_start[1024];
rt_uint8_t _undefined_stack_start[512];
rt_uint8_t _abort_stack_start[512];
rt_uint8_t _svc_stack_start[4096] SECTION(".nobss");
extern unsigned char __bss_start;
extern unsigned char __bss_end;

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
	/* disable interrupt first */
	rt_hw_interrupt_disable();
	/* initialize hardware interrupt */
	rt_hw_interrupt_init();

	/* initialize mmu */
	rt_hw_mmu_init(fh_mem_desc, sizeof(fh_mem_desc)/sizeof(fh_mem_desc[0]));

	rt_system_heap_init((void*)&__bss_end, (void*)FH_RTT_OS_MEM_END);

#ifdef RT_USING_DMA_MEM
	//just use the last 100KB
	fh_dma_mem_init((rt_uint32_t *)FH_RTT_OS_MEM_END, FH_DMA_MEM_SIZE);
#endif

	/* initialize board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

	/* initialize timer system */
	rt_system_timer_init();

	/* initialize scheduler system */
	rt_system_scheduler_init();

	/* initialize application */
	rt_application_init();

	/* initialize system timer thread */
	rt_system_timer_thread_init();

	/* initialize idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */

	return ;
}
