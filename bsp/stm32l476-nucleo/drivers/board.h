/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
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
 * 2009-09-22     Bernard      add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32l4xx.h>

// <o> Internal SRAM memory size[Kbytes] <8-64>
//	<i>Default: 64
#ifdef __ICCARM__
// Use *.icf ram symbal, to avoid hardcode.
extern char __ICFEDIT_region_RAM_end__;
#define STM32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
#define STM32_SRAM_SIZE         96
#define STM32_SRAM_END          (0x20000000 + STM32_SRAM_SIZE * 1024)
#endif

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END          STM32_SRAM_END

// <o> Console on USART: <0=> no console <1=>USART 1 <2=>USART 2 <3=> USART 3
// 	<i>Default: 1
#define STM32_CONSOLE_USART		2

void rt_hw_board_init(void);

#if STM32_CONSOLE_USART == 0
#define CONSOLE_DEVICE "no"
#elif STM32_CONSOLE_USART == 1
#define CONSOLE_DEVICE "uart1"
#elif STM32_CONSOLE_USART == 2
#define CONSOLE_DEVICE "uart2"
#elif STM32_CONSOLE_USART == 3
#define CONSOLE_DEVICE "uart3"
#elif STM32_CONSOLE_USART == 4
#define CONSOLE_DEVICE "uart4"
#elif STM32_CONSOLE_USART == 5
#define CONSOLE_DEVICE "uart5"
#elif STM32_CONSOLE_USART == 6
#define CONSOLE_DEVICE "lpuart1"
#endif

#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

void Error_Handler(void);

#endif

//*** <<< end of configuration section >>>    ***
