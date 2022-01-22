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
 * 2017-08-02     XiaoYang     porting to LPC54608 bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__


#include <stdint.h>

#include <rtthread.h>

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">

// <integer name="LPC_EXT_SDRAM" description="Begin Address of External SDRAM" default="0xA0000000" />
#define LPC_EXT_SDRAM_BEGIN    0xA0000000
// <integer name="LPC_EXT_SDRAM_END" description="End Address of External SDRAM" default="0xA2000000" />
#define LPC_EXT_SDRAM_END      0xA0800000


// </RDTConfigurator>

#ifdef __CC_ARM
extern int Image$$RTT_HEAP$$ZI$$Base;
#define HEAP_BEGIN  ((void *)&Image$$RTT_HEAP$$ZI$$Base)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN  (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN  ((void *)&__bss_end)
#endif
#define HEAP_END    (void*)(0x20000000 + 0x28000)

void rt_hw_board_init(void);

#endif
