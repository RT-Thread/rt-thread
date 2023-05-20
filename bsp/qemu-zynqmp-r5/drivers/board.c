/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_timer.h"
void idle_wfi(void)
{
    asm volatile ("wfi");
}

/**
 * This function will initialize board
 */

void rt_hw_board_init(void)
{
    /* initialize system heap */
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    rt_thread_idle_sethook(idle_wfi);
}

