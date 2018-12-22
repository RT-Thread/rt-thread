/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2017-10-20     ZYH          emmm...setup for HAL Libraries
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f1xx_hal.h"
/* board configuration */
#if \
    defined(STM32F101TB)||\
    defined(STM32F103T8)||\
    defined(STM32F103TB)
#define STM32F10X_PIN_NUMBERS	36
#elif \
    defined(STM32F101CB)||\
    defined(STM32F102CB)||\
    defined(STM32F103C8)||\
    defined(STM32F103CB)
#define STM32F10X_PIN_NUMBERS	48
#elif \
    defined(STM32F100RC)||\
    defined(STM32F100RD)||\
    defined(STM32F100RE)||\
    defined(STM32F101RB)||\
    defined(STM32F101RC)||\
    defined(STM32F101RD)||\
    defined(STM32F101RE)||\
    defined(STM32F101RF)||\
    defined(STM32F101RG)||\
    defined(STM32F102RB)||\
    defined(STM32F103R8)||\
    defined(STM32F103RB)||\
    defined(STM32F103RC)||\
    defined(STM32F103RD)||\
    defined(STM32F103RE)||\
    defined(STM32F103RF)||\
    defined(STM32F103RG)||\
    defined(STM32F105R8)||\
    defined(STM32F105RB)||\
    defined(STM32F105RC)||\
    defined(STM32F107RB)||\
    defined(STM32F107RC)
#define STM32F10X_PIN_NUMBERS 64
#elif \
    defined(STM32F100VC)||\
    defined(STM32F100VD)||\
    defined(STM32F100VE)||\
    defined(STM32F101VB)||\
    defined(STM32F101VC)||\
    defined(STM32F101VD)||\
    defined(STM32F101VE)||\
    defined(STM32F101VF)||\
    defined(STM32F101VG)||\
    defined(STM32F103V8)||\
    defined(STM32F103VB)||\
    defined(STM32F103VC)||\
    defined(STM32F103VD)||\
    defined(STM32F103VE)||\
    defined(STM32F103VF)||\
    defined(STM32F103VG)||\
    defined(STM32F105V8)||\
    defined(STM32F105VB)||\
    defined(STM32F105VC)||\
    defined(STM32F107VB)||\
    defined(STM32F107VC)
#define STM32F10X_PIN_NUMBERS 100
#elif \
    defined(STM32F100ZC)||\
    defined(STM32F100ZD)||\
    defined(STM32F100ZE)||\
    defined(STM32F101ZC)||\
    defined(STM32F101ZD)||\
    defined(STM32F101ZE)||\
    defined(STM32F101ZF)||\
    defined(STM32F101ZG)||\
    defined(STM32F103ZC)||\
    defined(STM32F103ZD)||\
    defined(STM32F103ZE)||\
    defined(STM32F103ZF)||\
    defined(STM32F103ZG)
#define STM32F10X_PIN_NUMBERS 144
#endif

#if \
    defined(STM32F100RC)||\
    defined(STM32F100VC)||\
    defined(STM32F100ZC)
#define STM32_SRAM_SIZE 24
//#define STM32F100xE
#elif \
    defined(STM32F100RD)||\
    defined(STM32F100RE)||\
    defined(STM32F100VD)||\
    defined(STM32F100VE)||\
    defined(STM32F100ZD)||\
    defined(STM32F100ZE)
#define STM32_SRAM_SIZE 32
//#define STM32F100xE
#elif \
    defined(STM32F101TB)||\
    defined(STM32F101CB)||\
    defined(STM32F101RB)||\
    defined(STM32F101VB)
#define STM32_SRAM_SIZE 16
//#define STM32F101xB
#elif \
    defined(STM32F101RC)||\
    defined(STM32F101VC)||\
    defined(STM32F101ZC)
#define STM32_SRAM_SIZE 32
//#define STM32F101xE
#elif \
    defined(STM32F101RD)||\
    defined(STM32F101RE)||\
    defined(STM32F101VD)||\
    defined(STM32F101VE)||\
    defined(STM32F101ZD)||\
    defined(STM32F101ZE)
#define STM32_SRAM_SIZE 48
//#define STM32F101xE
#elif \
    defined(STM32F101RF)||\
    defined(STM32F101RG)||\
    defined(STM32F101VF)||\
    defined(STM32F101VG)||\
    defined(STM32F101ZF)||\
    defined(STM32F101ZG)
#define STM32_SRAM_SIZE 80
//#define STM32F101xG
#elif \
    defined(STM32F102CB)||\
    defined(STM32F102RB)
#define STM32_SRAM_SIZE 16
//#define STM32F102xB
#elif \
    defined(STM32F103T8)||\
    defined(STM32F103TB)||\
    defined(STM32F103C8)||\
    defined(STM32F103CB)||\
    defined(STM32F103R8)||\
    defined(STM32F103RB)||\
    defined(STM32F103V8)||\
    defined(STM32F103VB)
#define STM32_SRAM_SIZE 20
//#define STM32F103xB
#elif \
    defined(STM32F103RC)||\
    defined(STM32F103VC)||\
    defined(STM32F103ZC)
#define STM32_SRAM_SIZE 48 
//#define STM32F103xE
#elif \
    defined(STM32F103RD)||\
    defined(STM32F103RE)||\
    defined(STM32F103VD)||\
    defined(STM32F103VE)||\
    defined(STM32F103ZD)||\
    defined(STM32F103ZE)
#define STM32_SRAM_SIZE 64
//#define STM32F103xE
#elif \
    defined(STM32F103RF)||\
    defined(STM32F103RG)||\
    defined(STM32F103VF)||\
    defined(STM32F103VG)||\
    defined(STM32F103ZF)||\
    defined(STM32F103ZG)
#define STM32_SRAM_SIZE 96
//#define STM32F103xG
#elif \
    defined(STM32F105R8)||\
    defined(STM32F105RB)||\
    defined(STM32F105RC)||\
    defined(STM32F105V8)||\
    defined(STM32F105VB)||\
    defined(STM32F105VC)
#define STM32_SRAM_SIZE 64
//#define STM32F105xC
#elif \
    defined(STM32F107RB)||\
    defined(STM32F107RC)||\
    defined(STM32F107VB)||\
    defined(STM32F107VC)
#define STM32_SRAM_SIZE 64
//#define STM32F107xC
#endif
/* whether use board external SRAM memory */
// <e>Use external SRAM memory on the board
// 	<i>Enable External SRAM memory
#define STM32_EXT_SRAM 0
//	<o>Begin Address of External SRAM
//		<i>Default: 0x68000000
#define STM32_EXT_SRAM_BEGIN 0x68000000 /* the begining address of external SRAM */
//	<o>End Address of External SRAM
//		<i>Default: 0x68080000
#define STM32_EXT_SRAM_END 0x68080000 /* the end address of external SRAM */
// </e>
// <o> Internal SRAM memory size[Kbytes] <8-64>
//	<i>Default: 64
#define STM32_SRAM_END (0x20000000 + STM32_SRAM_SIZE * 1024)
#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN  ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN  (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN  ((void *)&__bss_end)
#endif
#define HEAP_END    STM32_SRAM_END

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
