/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-01     Tanek        the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "Device.h"                     // Keil::Board Support:V2M-MPS2:Common

static void *rt_heap_begin_get(void)
{
    extern int Image$$RTT_HEAP$$Base;
    return &Image$$RTT_HEAP$$Base;
}

static void *rt_heap_end_get(void)
{
    extern int Image$$RTT_HEAP$$ZI$$Limit;
    return &Image$$RTT_HEAP$$ZI$$Limit;
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);    /* Generate interrupt each 10 ms  */

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

void SysTick_Handler (void)
{
	rt_interrupt_enter();

	rt_tick_increase();

	rt_interrupt_leave();
}
