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

// </RDTConfigurator>

#ifdef __CC_ARM
extern int Image$$RTT_HEAP$$ZI$$Base;
extern int Image$$RTT_HEAP$$ZI$$Limit;
#define HEAP_BEGIN          (&Image$$RTT_HEAP$$ZI$$Base)
#define HEAP_END            (&Image$$RTT_HEAP$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN  (__segment_end("HEAP"))
extern void __RTT_HEAP_END;
#define HEAP_END            (&__RTT_HEAP_END)
#else
extern int heap_start;
extern int heap_end;
#define HEAP_BEGIN          (&heap_start)
#define HEAP_END            (&heap_end)
#endif
//#define HEAP_END    (void*)(0x20000000 + 0x28000)

extern void rt_hw_board_init(void);
#endif
