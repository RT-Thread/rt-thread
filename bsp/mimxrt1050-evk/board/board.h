/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <fsl_device_registers.h>


/* board configuration */

#define MIMXRT105x_SRAM_SIZE         16
#define MIMXRT105x_SRAM_END          ((uint8_t*)MIMXRT105x_SRAM_BEGIN + (MIMXRT105x_SRAM_SIZE * 1024))

#define RT_USING_UART1

#define MIMXRT105x_CONSOLE_USART        1

void rt_hw_board_init(void);

#if MIMXRT105x_CONSOLE_USART == 0
#define CONSOLE_DEVICE "uart0"
#elif MIMXRT105x_CONSOLE_USART == 1
#define CONSOLE_DEVICE "uart1"
#elif MIMXRT105x_CONSOLE_USART == 2
#define CONSOLE_DEVICE "uart2"
#elif MIMXRT105x_CONSOLE_USART == 3
#define CONSOLE_DEVICE "uart3"
#elif MIMXRT105x_CONSOLE_USART == 4
#define CONSOLE_DEVICE "uart4"
#elif MIMXRT105x_CONSOLE_USART == 5
#define CONSOLE_DEVICE "uart5"
#endif

#define FINSH_DEVICE_NAME   CONSOLE_DEVICE


#endif

