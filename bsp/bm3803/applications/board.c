/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <finsh.h>

#include "board.h"
#include <interrupt.h>

extern int __bss_end;

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();
    /* timer interrupt cleared by hardware */
}

int rt_hw_timer_init(void)
{
    unsigned int counter = 1000000 / RT_TICK_PER_SECOND;
    volatile struct lregs *regs = (struct lregs *)PREGS;

    regs->scalercnt = CPU_FREQ / 1000000 - 1;
    regs->scalerload = CPU_FREQ / 1000000 - 1;
    regs->timercnt2 = counter - 1;
    regs->timerload2 = counter - 1;

    rt_hw_interrupt_install(TIMER2_TT, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(TIMER2_TT);

    /* start timer */
    regs->timerctrl2 = 0x7;

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void)
{
    rt_system_heap_init((void *)&__bss_end, (unsigned char *)&__bss_end + 0x01000000);
    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}
