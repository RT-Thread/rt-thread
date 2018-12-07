/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-05-31     ZYH          first version
 */
#include <board.h>
#if defined(BSP_USING_EXT_SRAM) && defined(RT_USING_MEMHEAP_AS_HEAP)
static struct rt_memheap system_heap;
#endif
static void bsp_clock_config(void)
{
    SystemInit();
    SysTick_Config(SystemCoreClock/RT_TICK_PER_SECOND);
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
extern int drv_sram_init(void);
#endif
void rt_hw_board_init()
{
    bsp_clock_config();
//    PORT_Init(PORTA, PIN0, PORTA_PIN0_SWCLK, 1);	
//	PORT_Init(PORTA, PIN1, PORTA_PIN1_SWDIO, 1);
#ifdef BSP_USING_EXT_SRAM
    drv_sram_init();
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
