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

#include <fsl_common.h>
#include <fsl_lpuart.h>
#include <fsl_iomuxc.h>

#ifdef __CC_ARM
extern int Image$$RW_m_data$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_m_data$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __data_end__;
#define HEAP_BEGIN    (&__data_end__)
#endif

#define HEAP_END          0x81DFFFFF
//#define HEAP_END          0x2001FFFF

void rt_hw_board_init(void);

#endif

//*** <<< end of configuration section >>>    ***
