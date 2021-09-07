/*
 * Copyright (C) 2021, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     pjq          first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "ddl.h"
#include "gpio.h"
#include "drv_gpio.h"

/* board configuration */
#define SRAM_BASE 0x20000000
#define SRAM_SIZE 0x2000
#define SRAM_END (SRAM_BASE + SRAM_SIZE)

/* High speed sram. */
#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN              (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN              (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN              (&__bss_end)
#endif

#ifdef __ICCARM__
#define HEAP_END                SRAM_END
#else
#define HEAP_END                SRAM_END
#endif

void rt_hw_board_init(void);
void rt_hw_us_delay(rt_uint32_t us);

#endif

// <<< Use Configuration Wizard in Context Menu >>>
