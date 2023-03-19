/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/03/15     flyingcys    first version
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#define RT_HEAP_SIZE 1024
static uint32_t user_heap[RT_HEAP_SIZE];     // heap default size: 4K(1024 * 4)

/* This is the timer interrupt service routine. */
static void systick_isr(void)
{
    rt_tick_increase();
}

void rt_hw_board_init(void)
{
    bflb_irq_initialize();

    CPU_Set_MTimer_CLK(ENABLE, CPU_Get_MTimer_Source_Clock() / 1000 / 1000 - 1);
    bflb_mtimer_config(HW_MTIMER_CLOCK * 2 / RT_TICK_PER_SECOND, systick_isr);

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init((void *)user_heap, (void *)user_heap + RT_HEAP_SIZE);
#endif

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void rt_hw_cpu_reset(void)
{
    GLB_SW_POR_Reset();
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
