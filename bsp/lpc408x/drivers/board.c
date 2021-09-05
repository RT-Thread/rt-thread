/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */

#include <board.h>

#if defined(BSP_USING_SDRAM) && defined(RT_USING_MEMHEAP_AS_HEAP)
    #include "drv_sdram.h"
    extern void rt_hw_sdram_init(void);
    static struct rt_memheap system_heap;
#endif

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial LPC40xx board.
 */
void rt_hw_board_init()
{
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x00000000 */
    SCB->VTOR  = (0x00000000 & NVIC_VTOR_MASK);
#endif

    /* init systick */
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND - 1);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

#ifdef RT_USING_HEAP

#if defined(BSP_USING_SDRAM) && defined(RT_USING_MEMHEAP_AS_HEAP)
    rt_hw_sdram_init();
    rt_system_heap_init((void *)EXT_SDRAM_BEGIN, (void *)EXT_SDRAM_END);
    rt_memheap_init(&system_heap, "sdram", (void *)HEAP_BEGIN, ((rt_uint32_t)HEAP_END - (rt_uint32_t)HEAP_BEGIN));
#else
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#endif /* RT_USING_HEAP */

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
