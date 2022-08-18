/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-04     iysheng           first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <target.h>

#include "drv_gpio.h"

#define V85XX_SRAM_SIZE         32
#define V85XX_SRAM_END          (0x20000000 + V85XX_SRAM_SIZE * 1024)


#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN  (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN   (&__bss_end)
#endif

#define HEAP_END          V85XX_SRAM_END

#endif
