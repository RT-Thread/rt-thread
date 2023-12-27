/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "board.h"

#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

static void bsp_clock_config(void)
{
    SystemInit();
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    SysTick->CTRL |= 0x00000004UL;
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

void rt_hw_board_init()
{
    bsp_clock_config();
    /* Heap initialization */
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#if defined(BSP_USING_SDRAM) && defined(RT_USING_MEMHEAP_AS_HEAP)
    swm_sdram_init();
    /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
    rt_memheap_init(&system_heap, "sdram", (void *)SDRAMM_BASE, BSP_SDRAM_SIZE);
#endif
    /* Pin driver initialization is open by default */
#ifdef RT_USING_PIN
    swm_pin_init();
#endif
    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    swm_uart_init();
#endif
    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}
