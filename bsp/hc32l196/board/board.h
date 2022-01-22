/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     DongBowen    first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "hc32l196_ddl.h"
#include "drv_gpio.h"

/* board configuration */
#define SRAM_BASE 0x20000000
#define SRAM_SIZE 0x8000
#define SRAM_END (SRAM_BASE + SRAM_SIZE)

/* High speed sram. */
#ifdef __CC_ARM
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN              (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
    #pragma section="HEAP"
    #define HEAP_BEGIN              (__segment_end("HEAP"))
#else
    extern int __bss_end;
    #define HEAP_BEGIN              (&__bss_end)
#endif

#ifdef __ICCARM__
    // Use *.icf ram symbal, to avoid hardcode.
    extern char __ICFEDIT_region_RAM_end__;
    #define HEAP_END                (&__ICFEDIT_region_RAM_end__)
#else
    #define HEAP_END                SRAM_END
#endif

void rt_hw_board_init(void);
void rt_hw_us_delay(rt_uint32_t us);

#endif
