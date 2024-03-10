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

#include "LPC407x_8x_177x_8x.h"
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SRAM allocation for Peripherals */
#define USB_RAM_BASE        0x20000000
#define MCI_RAM_BASE        0x20002000
#define ETH_RAM_BASE        0x20004000

/* Internal SRAM memory size[Kbytes] <16-256>, Default: 64*/
#define SRAM_SIZE      64 * 1024
#define SRAM_END       (0x10000000 + SRAM_SIZE)

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
#define HEAP_END    SRAM_END

void rt_hw_board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
