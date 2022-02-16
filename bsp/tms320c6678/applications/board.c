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
#include "interrupt.h"
#include "drv_timer.h"
#include "common.h"

#include <rtthread.h>

/**
 * This function will initial board.
 */
void rt_hw_board_init(void)
{
    // initial CPU core
    keystone_cpu_init();

    // initial interrupt controller
    rt_hw_interrupt_init();

    // initial system timer
    rt_hw_system_timer_init();

    /* initialize memory system */
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);

    rt_hw_system_timer_start();
}
