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

#include "LPC177x_8x.h"

/* whether use board external SDRAM memory */
// <e>Use external SDRAM memory on the board
// 	<i>Enable External SDRAM memory
#define LPC_EXT_SDRAM          0
//	<o>Begin Address of External SDRAM
//		<i>Default: 0x60000000
#define LPC_EXT_SDRAM_BEGIN    0xA0000000 /* the begining address of external SDRAM */
//	<o>End Address of External SDRAM
//		<i>Default: 0x60000000
#define LPC_EXT_SDRAM_END      0xA4000000 /* the end address of external SDRAM */
// </e>

/* RT_USING_UART */
#define RT_UART_RX_BUFFER_SIZE	64
#define RT_USING_UART0
//#define RT_USING_UART1
//#define RT_USING_UART2

#define CONSOLE_DEVICE      "uart0"
#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

void rt_hw_board_init(void);

#endif
