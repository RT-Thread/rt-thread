/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-16     Pillar       first version
 */

#include "board.h"
#include "drv_uart.h"

static inline uint32_t SysTick_Config(uint32_t ticks)
{
    if ((ticks - 1UL) > S32_SysTick_RVR_RELOAD_MASK)
    {
        return 1;
    }

    S32_SysTick->RVR  = (uint32_t)(ticks - 1UL);
    S32_SysTick->CVR  = 0UL;
    S32_SysTick->CSRr = S32_SysTick_CSR_ENABLE(1)   |
                        S32_SysTick_CSR_TICKINT(1)  |
                        S32_SysTick_CSR_CLKSOURCE(1);
    return 0;
}

#define SYSCLK 48000000

void rt_hw_board_init(void)
{
    SysTick_Config(SYSCLK / RT_TICK_PER_SECOND);

#if defined(RT_USING_HEAP)
    /* Heap initialization */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}