/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include "board.h"

#ifdef BSP_USING_DEBUG_UART
#include "drv_uart_no_device.h"
#endif

extern void board_init(void);

void systick_isr(void)
{
    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}

void rt_hw_board_init(void)
{
    board_init();
    mtimer_set_alarm_time(RT_TICK_PER_SECOND, systick_isr);

    /* USART driver initialization is open by default */
#ifdef BSP_USING_DEBUG_UART
    rt_hw_debug_uart_init();
#endif

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#ifdef RT_USING_DEVICE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    return;
}

