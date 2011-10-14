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
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2010-02-04     Magicoe      add board.h to LPC176x bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

/* RT_USING_UART */
#define RT_UART_RX_BUFFER_SIZE	64
#define RT_USING_UART0
#define RT_USING_UART1
#define RT_USING_UART2

#define CONSOLE_DEVICE      "uart1"
#define FINSH_DEVICE_NAME   "uart1"

void rt_hw_board_init(void);

#endif
