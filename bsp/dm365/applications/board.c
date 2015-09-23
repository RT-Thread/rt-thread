/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 * Date           Author		Notes
 * 2010-11-13     weety		first version
 */


#include <rtthread.h>
#include <rthw.h>
#include <mmu.h>
#include "board.h"

/**
 * @addtogroup dm365
 */
/*@{*/

extern void rt_hw_clock_init(void);
extern void rt_hw_uart_init(void);

static struct mem_desc dm365_mem_desc[] = {
	{ 0x80000000, 0x88000000-1, 0x80000000, SECT_RW_CB, 0, SECT_MAPPED },       /* 128M cached SDRAM memory */
	{ 0xA0000000, 0xA8000000-1, 0x80000000, SECT_RW_NCNB, 0, SECT_MAPPED },     /* 128M No cached SDRAM memory */
	{ 0xFFFF0000, 0xFFFF1000-1, 0x80000000, SECT_TO_PAGE, PAGE_RO_CB, PAGE_MAPPED }, /* isr vector table */
	{ 0x01C00000, 0x02000000-1, 0x01C00000, SECT_RW_NCNB, 0, SECT_MAPPED },       /* CFG BUS peripherals */
	{ 0x02000000, 0x0A000000-1, 0x02000000, SECT_RW_NCNB, 0, SECT_MAPPED },       /* AEMIF */
};


/**
 * This function will handle rtos timer
 */
void rt_timer_handler(int vector, void *param)
{
	rt_tick_increase();
}

/**
 * This function will init timer0 for system ticks
 */
 void rt_hw_timer_init()
 {
	/* timer0, input clocks 24MHz */
	volatile timer_regs_t *regs =
		(volatile timer_regs_t*)DAVINCI_TIMER1_BASE;//DAVINCI_TIMER0_BASE;

	/*disable timer*/
	regs->tcr &= ~(0x3UL << 6);

	//TIMMODE 32BIT UNCHAINED MODE
	regs->tgcr |=(0x1UL << 2);

	/*not in reset timer */
	regs->tgcr |= (0x1UL << 0);

	//regs->tgcr &= ~(0x1UL << 1);

	/* set Period Registers */
	regs->prd12 = 24000000/RT_TICK_PER_SECOND;
	regs->tim12 = 0;

	/* Set enable mode */
	regs->tcr |= (0x2UL << 6); //period mode
	

	/* install interrupt handler */
	rt_hw_interrupt_install(IRQ_DM365_TINT2, rt_timer_handler,
							RT_NULL, "timer1_12");//IRQ_DM365_TINT0_TINT12
	rt_hw_interrupt_umask(IRQ_DM365_TINT2);//IRQ_DM365_TINT2

 }

/**
 * This function will init dm365 board
 */
void rt_hw_board_init()
{
	psc_change_state(DAVINCI_DM365_LPSC_TIMER0, 3);
	psc_change_state(DAVINCI_DM365_LPSC_TIMER1, 3);
	/* initialize the system clock */
	//rt_hw_clock_init();
	davinci_clk_init();

	/* initialize uart */
	rt_hw_uart_init();
#ifdef RT_USING_CONSOLE
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

	/* initialize mmu */
	rt_hw_mmu_init(dm365_mem_desc, sizeof(dm365_mem_desc)/sizeof(dm365_mem_desc[0]));

	/* initialize timer0 */
	rt_hw_timer_init();

}

/*@}*/
