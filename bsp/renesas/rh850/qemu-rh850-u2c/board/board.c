/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_ostm.h"
#include "drv_usart.h"
#include "rh850_cpu.h"

extern char rh850_heap_start[];
extern char rh850_heap_end[];

#ifdef RT_USING_IDLE_HOOK
static void idle_halt(void)
{
    rh850_halt();
}
#endif

void rt_hw_board_init(void)
{
    soc_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init(rh850_heap_start, rh850_heap_end);
#endif

    rt_hw_usart_init();
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    rh850_tick_init(BOARD_TICK_OSTM_BASE, BOARD_TICK_VECTOR, SOC_CLK_HSB_HZ);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_IDLE_HOOK
    rt_thread_idle_sethook(idle_halt);
#endif
}
