/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32e23x.h"
#include "drv_gpio.h"

#include "gd32e23x_exti.h"


#define GD32_SRAM_SIZE         8

#define GD32_SRAM_BEGIN        (0x20000000)
#define GD32_SRAM_END          (GD32_SRAM_BEGIN + GD32_SRAM_SIZE * 1024)

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN    (__segment_end("CSTACK"))
#else /* GCC */
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END          GD32_SRAM_END

#endif

