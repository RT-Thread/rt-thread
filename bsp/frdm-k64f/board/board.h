/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <MK64F12.h>


/* board configuration */

// <o> Internal SRAM memory size[Kbytes] <8-64>
// <i>Default: 64
#define K64_SRAM_SIZE         192
#define K64_SRAM_END          (0x20000000 + (K64_SRAM_SIZE * 1024))

//#define RT_USING_UART1
#define RT_USING_UART0
//#define RT_USING_UART3

// <o> Console on USART: <0=> no console <1=>USART 1 <2=>USART 2 <3=> USART 3
// <i>Default: 1
#define K64_CONSOLE_USART        0

void rt_hw_board_init(void);

#if K64_CONSOLE_USART == 0
#define CONSOLE_DEVICE "uart0"
#elif K64_CONSOLE_USART == 1
#define CONSOLE_DEVICE "uart1"
#elif K64_CONSOLE_USART == 2
#define CONSOLE_DEVICE "uart2"
#elif K64_CONSOLE_USART == 3
#define CONSOLE_DEVICE "uart3"
#elif K64_CONSOLE_USART == 4
#define CONSOLE_DEVICE "uart4"
#elif K64_CONSOLE_USART == 5
#define CONSOLE_DEVICE "uart5"
#endif

#define FINSH_DEVICE_NAME   CONSOLE_DEVICE


#endif

// <<< Use Configuration Wizard in Context Menu >>>
