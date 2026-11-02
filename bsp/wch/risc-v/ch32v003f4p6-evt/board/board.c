/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-25     seteiro      CH32V003F4P6-EVT: SysTick on the QingKe V2 PFIC
 */

#include "board.h"
#include <rtthread.h>

#ifdef BSP_USING_UART
#include "drv_usart.h"
#endif

extern uint32_t SystemCoreClock;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    NVIC_SetPriority(SysTicK_IRQn, 0xf0);
    NVIC_SetPriority(Software_IRQn, 0xf0);
    NVIC_EnableIRQ(SysTicK_IRQn);
    NVIC_EnableIRQ(Software_IRQn);
    SysTick->CTLR = 0;
    SysTick->SR = 0;
    SysTick->CNT = 0;
    SysTick->CMP = ticks - 1;
    SysTick->CTLR = 0xF;
    return 0;
}

void rt_hw_board_init(void)
{
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
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

void SysTick_Handler(void) __attribute__((interrupt()));
void SysTick_Handler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    SysTick->SR = 0;
    rt_hw_usart_rx_poll();
    rt_tick_increase();
    rt_interrupt_leave();
    FREE_INT_SP();
}
