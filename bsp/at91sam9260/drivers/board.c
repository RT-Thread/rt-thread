/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009 RT-Thread Develop Team
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

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include <mmu.h>

/**
 * @addtogroup at91sam9260
 */
/*@{*/


extern void rt_hw_clock_init(void);

extern void rt_hw_get_clock(void);
extern void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn);
extern void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv);
extern void rt_dbgu_isr(void);

static struct mem_desc at91_mem_desc[] = {
	{ 0x00000000, 0xFFFFFFFF, 0x00000000, RW_NCNB },     /* None cached for 4G memory */
	{ 0x20000000, 0x24000000-1, 0x20000000, RW_CB },     /* 64M cached SDRAM memory */
	{ 0x00000000, 0x100000, 0x20000000, RW_CB },         /* isr vector table */
	{ 0x90000000, 0x90400000 - 1, 0x00200000, RW_NCNB }, /* 4K SRAM0 + 4k SRAM1 */
	{ 0xA0000000, 0xA4000000-1, 0x20000000, RW_NCNB }   /* 64M none-cached SDRAM memory */
};


#define PIT_CPIV(x)	((x) & AT91_PIT_CPIV)
#define PIT_PICNT(x)	(((x) & AT91_PIT_PICNT) >> 20)

static rt_uint32_t pit_cycle;		/* write-once */
static rt_uint32_t pit_cnt;		/* access only w/system irq blocked */

/**
 * This function will handle rtos timer
 */
void rt_timer_handler(int vector, void *param)
{
	#ifdef RT_USING_DBGU
	if (at91_sys_read(AT91_DBGU + AT91_US_CSR) & 0x1)
	{
		rt_dbgu_isr();
	}
	#endif
	if (at91_sys_read(AT91_PIT_SR) & AT91_PIT_PITS)
	{
		unsigned nr_ticks;

		/* Get number of ticks performed before irq, and ack it */
		nr_ticks = PIT_PICNT(at91_sys_read(AT91_PIT_PIVR));
		rt_tick_increase();
	}
}

static void at91sam926x_pit_reset(void)
{
	/* Disable timer and irqs */
	at91_sys_write(AT91_PIT_MR, 0);

	/* Clear any pending interrupts, wait for PIT to stop counting */
	while (PIT_CPIV(at91_sys_read(AT91_PIT_PIVR)) != 0)
		;

	/* Start PIT but don't enable IRQ */
	//at91_sys_write(AT91_PIT_MR, (pit_cycle - 1) | AT91_PIT_PITEN);
	pit_cnt += pit_cycle * PIT_PICNT(at91_sys_read(AT91_PIT_PIVR));
	at91_sys_write(AT91_PIT_MR, (pit_cycle - 1) | AT91_PIT_PITEN
			| AT91_PIT_PITIEN);
	rt_kprintf("PIT_MR=0x%08x\n", at91_sys_read(AT91_PIT_MR));
}

/*
 * Set up both clocksource and clockevent support.
 */
static void at91sam926x_pit_init(void)
{
	rt_uint32_t	pit_rate;
	rt_uint32_t	bits;

	/*
	 * Use our actual MCK to figure out how many MCK/16 ticks per
	 * 1/HZ period (instead of a compile-time constant LATCH).
	 */
	pit_rate = clk_get_rate(clk_get("mck")) / 16;
	rt_kprintf("pit_rate=%dHZ\n", pit_rate);
	pit_cycle = (pit_rate + RT_TICK_PER_SECOND/2) / RT_TICK_PER_SECOND;

	/* Initialize and enable the timer */
	at91sam926x_pit_reset();

}

/**
 * This function will init pit for system ticks
 */
 void rt_hw_timer_init()
 {
 	at91sam926x_pit_init();

	/* install interrupt handler */
	rt_hw_interrupt_install(AT91_ID_SYS, rt_timer_handler, 
							RT_NULL, "system");
	rt_hw_interrupt_umask(AT91_ID_SYS);

 }
 
 void at91_tc1_init()
 {
 	at91_sys_write(AT91_PMC_PCER, 1<<AT91SAM9260_ID_TC0);
 	writel(AT91_TC_TC0XC0S_NONE | AT91_TC_TC1XC1S_NONE | AT91_TC_TC2XC2S_NONE, AT91SAM9260_BASE_TCB0 + AT91_TC_BMR);
 	writel(AT91_TC_CLKDIS, AT91SAM9260_BASE_TC0 + AT91_TC_CCR);
 	writel(AT91_TC_TIMER_CLOCK4, AT91SAM9260_BASE_TC0 + AT91_TC_CMR);
 	writel(0xffff, AT91SAM9260_BASE_TC0 + AT91_TC_CV);
 }

/**
 * This function will init at91sam9260 board
 */
void rt_hw_board_init()
{
	/* initialize the system clock */
	rt_hw_clock_init();

	/* initialize uart */
	rt_hw_uart_init();
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

	/* initialize mmu */
	rt_hw_mmu_init(at91_mem_desc, sizeof(at91_mem_desc)/sizeof(at91_mem_desc[0]));

	/* initialize timer0 */
	rt_hw_timer_init();

}

/*@}*/
