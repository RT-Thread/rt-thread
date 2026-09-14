/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "pin_mux.h"

void SysTick_Handler(void)
{
    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}

void rt_hw_board_init(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();

    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(PendSV_IRQn, (1U << __NVIC_PRIO_BITS) - 1U);

#ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

void rt_hw_us_delay(rt_uint32_t us)
{
    uint32_t cycles = SystemCoreClock / 1000000U * us;
    uint32_t start = SysTick->VAL;
    uint32_t elapsed = 0;
    uint32_t reload = SysTick->LOAD + 1U;

    while (elapsed < cycles)
    {
        uint32_t now = SysTick->VAL;
        elapsed += (start >= now) ? (start - now) : (start + reload - now);
        start = now;
    }
}

void rt_hw_cpu_reset(void)
{
    NVIC_SystemReset();
}
