/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     supperthomas first version
 *
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>
#include "board.h"
#include "mxc_sys.h"
#ifdef RT_USING_SERIAL
#include "drv_usart.h"
#endif

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

void rt_hw_systick_init(void)
{
    uint32_t error;
    error = SYS_SysTick_Config(SYS_SysTick_GetFreq() / RT_TICK_PER_SECOND, 1, MXC_TMR0);

    if (error != E_NO_ERROR)
    {
        rt_kprintf("ERROR: Ticks is not valid");
    }
}

void rt_hw_board_init(void)
{

    rt_hw_systick_init();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)(HEAP_BEGIN), (void *)(HEAP_END));
#endif

#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t start, now, delta, reload, us_tick;
    start = SysTick->VAL;
    reload = SysTick->LOAD;
    us_tick = SystemCoreClock / 1000000UL;
    do
    {
        now = SysTick->VAL;
        delta = start >= now ? start - now : reload + start - now;
    }
    while (delta < us_tick * us);
}
