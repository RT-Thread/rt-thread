/*
 * Copyright (c) 2006-2021, YICHIP Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WSY          first version
 */

#include <board.h>
#if defined(BSP_USING_EXT_SRAM) && defined(RT_USING_MEMHEAP_AS_HEAP)
    static struct rt_memheap system_heap;
#endif
#define SystemCoreClock (48000000)

static void bsp_clock_config(void)
{
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_USING_SERIAL
    extern int rt_hw_uart_init(void);
#endif

void rt_hw_board_init()
{
    bsp_clock_config();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

