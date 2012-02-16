/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.fayfayspace.org/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 * 2006-10-10     Bernard      add hardware related of finsh
 */
 
#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>

/**
 * @addtogroup QEMU
 */
/*@{*/

static void rt_timer_handler(int vector)
{
	rt_tick_increase();
}

/**
 * This function will init QEMU
 *
 */
void rt_hw_board_init(void)
{
	/* initialize 8253 clock to interrupt 100 times/sec */
	outb(TIMER_MODE, TIMER_SEL0|TIMER_RATEGEN|TIMER_16BIT);
	outb(IO_TIMER1, TIMER_DIV(100) % 256);
	outb(IO_TIMER1, TIMER_DIV(100) / 256);

	/* install interrupt handler */
	rt_hw_interrupt_install(INTTIMER0, rt_timer_handler, RT_NULL);
	rt_hw_interrupt_umask(INTTIMER0);
}

#ifdef RT_USING_FINSH
extern void finsh_notify(void);
static void rt_serial_isr(int vector)
{
	finsh_notify();
}

/** 
 * This function will init hardware related in finsh shell
 */
void rt_hw_finsh_init()
{
	/* install UART isr */
	rt_hw_interrupt_install(INTUART0_RX, rt_serial_isr, RT_NULL);
	rt_hw_interrupt_umask(INTUART0_RX);
	
	/* install  keyboard isr */
	rt_hw_interrupt_install(INTKEYBOARD, rt_serial_isr, RT_NULL);
	rt_hw_interrupt_umask(INTKEYBOARD);
}
#endif

/*@}*/
