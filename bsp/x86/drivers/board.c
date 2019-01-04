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

static void rt_timer_handler(int vector, void* param)
{
	rt_tick_increase();
}

#ifdef RT_USING_HOOK
static void idle_hook(void)
{
	asm volatile("sti; hlt": : :"memory");
}
#endif

/**
 * This function will init QEMU
 *
 */
void rt_hw_board_init(void)
{
	/* initialize 8253 clock to interrupt 1000 times/sec */
	outb(TIMER_MODE, TIMER_SEL0|TIMER_RATEGEN|TIMER_16BIT);
	outb(IO_TIMER1, TIMER_DIV(RT_TICK_PER_SECOND) % 256);
	outb(IO_TIMER1, TIMER_DIV(RT_TICK_PER_SECOND) / 256);

	/* install interrupt handler */
	rt_hw_interrupt_install(INTTIMER0, rt_timer_handler, RT_NULL, "tick");
	rt_hw_interrupt_umask(INTTIMER0);

#ifdef RT_USING_HOOK
	rt_thread_idle_sethook(idle_hook);
#endif
}

void restart(void)
{
    outb(KBSTATP, 0xFE); /* pulse reset low */
    while(1);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(restart, reboot PC)

void reboot(void)
{
    restart();
}
FINSH_FUNCTION_EXPORT(reboot, reboot PC)
#endif
/*@}*/
