/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>

#include "clock_config.h"
#include "fsl_common.h"

#define GET_PINS(port, pin) ((port) * 32 + (pin))

#define LED_RED_PIN   GET_PINS(2, 3)
#define LED_GREEN_PIN GET_PINS(2, 7)
#define LED_BLUE_PIN  GET_PINS(1, 10)
#define SW2_PIN       GET_PINS(3, 14)
#define SW3_PIN       GET_PINS(3, 29)

#if defined(__ARMCC_VERSION)
extern int Image$$ARM_LIB_HEAP$$ZI$$Base;
extern int Image$$ARM_LIB_STACK$$ZI$$Base;
#define HEAP_BEGIN ((void *)&Image$$ARM_LIB_HEAP$$ZI$$Base)
#define HEAP_END   ((void *)&Image$$ARM_LIB_STACK$$ZI$$Base)
#elif defined(__ICCARM__)
#pragma section = "HEAP"
#define HEAP_BEGIN (__segment_end("HEAP"))
extern void __RTT_HEAP_END;
#define HEAP_END   (&__RTT_HEAP_END)
#elif defined(__GNUC__)
extern int __HeapBase;
extern int __HeapLimit;
#define HEAP_BEGIN ((void *)&__HeapBase)
#define HEAP_END   ((void *)&__HeapLimit)
#endif

void rt_hw_board_init(void);
void rt_hw_us_delay(rt_uint32_t us);
void rt_hw_cpu_reset(void);

#endif
