/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include "board.h"
#include "trap.h"
#include "interrupt.h"
#include "drv_timer.h"
#include "KeyStone_common.h"

#include <rtthread.h>

/**
 * This is the timer interrupt service routine.
 *
 */
void rt_hw_systick_isr(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial board.
 */
void rt_hw_board_init(void)
{
	// initial CPU core
	KeyStone_common_CPU_init();

	// initial interrupt controller
	rt_hw_interrupt_init();

	// initial system trap
	rt_trap_init();

	// initial system timer
    hw_system_timer_init();

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif
    // ......

    hw_system_timer_start();
}

