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
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32f4xx.h>
#include <drv_sdram.h>
#include <drv_nand.h>

/* board configuration */
// <o> SDCard Driver <1=>SDIO sdcard <0=>SPI MMC card
// 	<i>Default: 1
#define STM32_USE_SDIO			0

#define IS42S16400J_SIZE             0x400000
#define W9825G6KH_SIZE               (32*1024*1024)

//	<o>Begin Address of External SDRAM
//		<i>Default: 0xD0000000
#define EXT_SDRAM_BEGIN    SDRAM_BANK_ADDR /* the begining address of external SDRAM */
//	<o>End Address of External SRAM
//		<i>Default: 0xD0800000
#define EXT_SDRAM_END      (SDRAM_BANK_ADDR + W9825G6KH_SIZE) /* the end address of external SDRAM */

// <o> Internal SRAM memory size[Kbytes] <8-64>
//	<i>Default: 64
#ifdef __ICCARM__
// Use *.icf ram symbal, to avoid hardcode.
extern char __ICFEDIT_region_RAM_end__;
#define STM32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
#define STM32_SRAM_SIZE         128
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
#define STM32_CONSOLE_USART		1

void rt_hw_board_init(void);

#if STM32_CONSOLE_USART == 0
#define CONSOLE_DEVICE "no"
#elif STM32_CONSOLE_USART == 1
#define CONSOLE_DEVICE "uart1"
#elif STM32_CONSOLE_USART == 2
#define CONSOLE_DEVICE "uart2"
#elif STM32_CONSOLE_USART == 3
#define CONSOLE_DEVICE "uart3"
#endif

#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

#define STM32F4xx_PIN_NUMBERS 176

void Error_Handler(void);

#endif

//*** <<< end of configuration section >>>    ***
