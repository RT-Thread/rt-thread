/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-15     flyingcys    1st version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN    (__segment_end("CSTACK"))
#else
extern int __bss_end__;
#define HEAP_BEGIN    (&__bss_end__)
#endif

#define HEAP_END           (0x20028000UL)

#define HARDWARE_VERSION 0x0003U
#include "pin_config.h"

void rt_hw_board_init(void);

#endif
