/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#include "board.h"

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
