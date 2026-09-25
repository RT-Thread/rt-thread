/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-25     seteiro      CH32V003F4P6-EVT: 16KB flash, 2KB RAM
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "ch32v00x.h"
#include <rthw.h>

#define SRAM_SIZE  2
#define SRAM_END (0x20000000 + SRAM_SIZE * 1024)

extern int _ebss;
extern int _susrstack;
#define HEAP_BEGIN  ((void *)&_ebss)
#define HEAP_END    ((void *)&_susrstack)

#define GET_INT_SP()   asm volatile("csrrw sp,mscratch,sp")
#define FREE_INT_SP()  asm volatile("csrrw sp,mscratch,sp")

void rt_hw_board_init(void);

#endif
