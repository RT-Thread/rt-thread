/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-10-08     Bernard      add board.h to this bsp
 * 2009-12-25     yi.qiu          add LM3S configration
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

/* whether use board external SRAM memory */
// <e>Use external SRAM memory on the board
// 	<i>Enable External SRAM memory
#define LM3S_EXT_SRAM          0
//	<o>Begin Address of External SRAM
//		<i>Default: 0x60000000
#define LM3S_EXT_SRAM_BEGIN    0x60000000 /* the begining address of external SRAM */
//	<o>End Address of External SRAM
//		<i>Default: 0x60000000
#define LM3S_EXT_SRAM_END      0x607FFFFF /* the end address of external SRAM */
// </e>

// <o> Internal SRAM memory size[Kbytes] <8-64>
//	<i>Default: 64
#define LM3S_SRAM_SIZE         32
#define LM3S_SRAM_END          (0x20000000 + LM3S_SRAM_SIZE * 1024)

// For lm3s9b9x, it should be SYSCTL_XTAL_16MHZ
#define LM3S_XTAL_TYPE      	SYSCTL_XTAL_168MHZ

/* RT_USING_UART */
#define RT_UART_RX_BUFFER_SIZE	64
#define RT_USING_UART0
#define RT_USING_UART1
//#define RT_USING_UART2

#define CONSOLE_DEVICE      "uart0"
#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

void rt_hw_board_led_on(int n);
void rt_hw_board_led_off(int n);
void rt_hw_board_init(void);

void rt_hw_usart_init(void);
void rt_hw_sdcard_init(void);

#endif
