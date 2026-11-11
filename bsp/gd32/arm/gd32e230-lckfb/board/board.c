/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "gd32e23x.h"

#ifdef RT_USING_SERIAL
#if defined(RT_USING_SERIAL_V2)
#include "drv_usart_v2.h"
#else
#include "drv_usart.h"
#endif
#endif

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void)
{
    rt_kprintf("\nError_Handler triggered! System halted.\n");
    while (1)
    {
    }
}

/**
 * @brief  This is the timer interrupt service routine.
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

/**
 * @brief This function will initial GD32 board.
 * @note  This function is called from the RT-Thread startup code.
 */
void rt_hw_board_init(void)
{
#ifdef VECT_TAB_RAM
    SCB->VTOR = 0x20000000;
#else  /* VECT_TAB_FLASH is the default */
    SCB->VTOR = 0x08000000;
#endif

    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
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

