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
 * 2017-08-25     LongfeiMa    transplantation for stm32h7xx
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32h7xx.h>
#include "stm32h7xx_hal.h"

// <<< Use Configuration Wizard in Context Menu >>>
/* board configuration */
#define RT_USING_UART1
#define RT_USING_UART2
#define RT_USING_UART3

// <o> SDCard Driver <1=>SDIO sdcard <0=>SPI MMC card
//  <i>Default: 1
#define STM32_USE_SDIO          0

/* whether use board external SDRAM memory */
// <e>Use external SDRAM memory on the board
//  <o>Begin Address of External SDRAM
#define EXT_SDRAM_BEGIN    0xC0000000
//  <o>Size of External SDRAM
#define EXT_SDRAM_SIZE     (0x800000)
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + EXT_SDRAM_SIZE)
// </e>

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

// <o> Internal SRAM memory size[Kbytes] <8-64>
//  <i>Default: 64
#define STM32_SRAM_SIZE   (512 * 1024)
#define HEAP_END          (0x24000000 + STM32_SRAM_SIZE)

void rt_hw_board_init(void);

#endif

