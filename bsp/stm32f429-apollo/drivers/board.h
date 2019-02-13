/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

#if defined(__CC_ARM) || defined(__CLANG_ARM)
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

void rt_hw_board_init(void);

#define STM32F4xx_PIN_NUMBERS 176

void Error_Handler(void);

#endif

//*** <<< end of configuration section >>>    ***
