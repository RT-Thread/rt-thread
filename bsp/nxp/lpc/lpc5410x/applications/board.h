/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2010-02-04     Magicoe      add board.h to LPC176x bsp
 * 2013-12-18     Bernard      porting to LPC4088 bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

//#include "LPC54xxx.h"
#include "chip.h"


#include <rtthread.h>

/* disable SDRAM in default */
#ifndef LPC_EXT_SDRAM
#define LPC_EXT_SDRAM       0
#endif

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">
// <integer name="LPC_EXT_SDRAM" description="Begin Address of External SDRAM" default="0xA0000000" />
#define LPC_EXT_SDRAM_BEGIN    0xA0000000
// <integer name="LPC_EXT_SDRAM_END" description="End Address of External SDRAM" default="0xA2000000" />
#define LPC_EXT_SDRAM_END      0xA2000000
// </RDTConfigurator>

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
#define HEAP_END    (void*)(0x10000000 + 0x10000)

void rt_hw_board_init(void);
int  rt_hw_board_heap_init(void);

#ifdef RT_USING_RTGUI
int rtgui_lcd_init(void);
int touch_calibration_init(void);
#endif

#endif
