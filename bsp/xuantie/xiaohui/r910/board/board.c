/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-23     Wangshun     first version
 */

#include <board.h>
#include <rthw.h>
#include <rtthread.h>
#include <drv_usart.h>

extern unsigned long __heap_start;
extern unsigned long __heap_end;

/**
 * This function will initialize your board.
 */
void rt_hw_board_init()
{
    rt_hw_interrupt_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)&__heap_start, (void *)&__heap_end);
#endif

#ifdef BSP_USING_UART
    rt_hw_usart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
