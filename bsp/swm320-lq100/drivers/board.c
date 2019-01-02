/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#include <board.h>
#if defined(BSP_USING_EXT_SRAM) && defined(RT_USING_MEMHEAP_AS_HEAP)
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
#ifdef BSP_USING_EXT_SRAM
    extern int rt_hw_sram_init(void);
#endif
void rt_hw_board_init()
{
    bsp_clock_config();

#ifdef BSP_USING_EXT_SRAM
    rt_hw_sram_init();
#endif
#if defined(BSP_USING_EXT_SRAM) && defined(RT_USING_MEMHEAP_AS_HEAP)
    rt_system_heap_init((void *)EXT_SRAM_BEGIN, (void *)EXT_SRAM_END);
    rt_memheap_init(&system_heap, "sram", (void *)HEAP_BEGIN, HEAP_SIZE);
#elif defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
