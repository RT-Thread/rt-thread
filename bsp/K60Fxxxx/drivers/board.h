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
 * 2013-07-11     reynolds     port to TWR-K60F120M
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <MK60F12.H>


/* board configuration */

// <o> Internal SRAM memory size[Kbytes] <8-64>
// <i>Default: 64
#define k60_SRAM_SIZE         128
#define k60_SRAM_END          (0x20000000 + (k60_SRAM_SIZE * 1024)/2)

//#define RT_USING_UART1
#define RT_USING_UART5
//#define RT_USING_UART3

// <o> Console on USART: <0=> no console <1=>USART 1 <2=>USART 2 <3=> USART 3
// <i>Default: 1
#define k60_CONSOLE_USART        5

#define USE_UART_TX_FIFO

void rt_hw_board_init(void);

#if k60_CONSOLE_USART == 0
    #define CONSOLE_DEVICE              "uart0"
    #define UART_FIFO_TX_ENTRY          (8)
    #define UART_FIFO_TX_WATERMARK      (0)
    #define k60_uasrt_irq_num           (45)
#elif k60_CONSOLE_USART == 1
    #define CONSOLE_DEVICE              "uart1"
    #define UART_FIFO_TX_ENTRY          (8)
    #define UART_FIFO_TX_WATERMARK      (0)
    #define k60_uasrt_irq_num           (47)
#elif k60_CONSOLE_USART == 2
    #define CONSOLE_DEVICE              "uart2"
    #define UART_FIFO_TX_ENTRY          (1)
    #define UART_FIFO_TX_WATERMARK      (0)
    #define k60_uasrt_irq_num           (49)
#elif k60_CONSOLE_USART == 3
    #define CONSOLE_DEVICE              "uart3"
    #define UART_FIFO_TX_ENTRY          (1)
    #define UART_FIFO_TX_WATERMARK      (0)
    #define k60_uasrt_irq_num           (51)
#elif k60_CONSOLE_USART == 4
    #define CONSOLE_DEVICE              "uart4"
    #define UART_FIFO_TX_ENTRY          (1)
    #define UART_FIFO_TX_WATERMARK      (0)
    #define k60_uasrt_irq_num           (53)
#elif k60_CONSOLE_USART == 5
    #define CONSOLE_DEVICE              "uart5"
    #define UART_FIFO_TX_ENTRY          (1)
    #define UART_FIFO_TX_WATERMARK      (0)
    #define k60_uasrt_irq_num           (55)
#endif

#define USE_UART_TX_FIFO
#define UART_FIFO_TX_ENTRY        (1)
#define UART_FIFO_TX_WATERMARK    (0)
#define k60_uasrt_irq_num   (55)


#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

#endif

// <<< Use Configuration Wizard in Context Menu >>>
