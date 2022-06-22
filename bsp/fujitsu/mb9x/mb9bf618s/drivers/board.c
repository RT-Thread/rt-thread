/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#include "serial.h"

/**
 * @addtogroup FM3
 */

/*@{*/

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

/**
 * This fucntion returns milliseconds since system passed
 */
rt_uint32_t rt_hw_tick_get_millisecond(void)
{
    rt_tick_t tick;
    rt_uint32_t value;

#define TICK_MS (1000/RT_TICK_PER_SECOND)

    tick = rt_tick_get();
    value = tick * TICK_MS + (SysTick->LOAD - SysTick->VAL) * TICK_MS / SysTick->LOAD;

    return value;
}

/**
 * This fucntion returns microseconds since system passed
 */
rt_uint32_t rt_hw_tick_get_microsecond(void)
{
    rt_tick_t tick;
    rt_uint32_t value;

#define TICK_US (1000000/RT_TICK_PER_SECOND)

    tick = rt_tick_get();
    value = tick * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;

    return value;
}

/**
* This function will initial FM3 Easy Kit board.
 */
void rt_hw_board_init(void)
{
    /* disable all analog input. */
    FM3_GPIO->ADE = 0;

    /* init systick */
    SysTick_Config(SystemCoreClock/RT_TICK_PER_SECOND);

    /* initialize UART device */
    rt_hw_serial_init();
    /* set console as UART device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/*@}*/
