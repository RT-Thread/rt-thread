/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtconfig.h>

#include "core_rv32.h"
#include "bl_sys.h"
#include "bl_irq.h"
#include "bl808_clock.h"

#ifdef BL808
#include "bl808.h"
#elif defined(BL606P)
#include "bl606p.h"
#endif

extern uint8_t _heap_start;
extern uint8_t _heap_size;

#define RT_HW_HEAP_BEGIN    (void*)&_heap_start
#define RT_HW_HEAP_END      (void*)(&_heap_start + (rt_ubase_t)&_heap_size)

void rt_hw_board_init(void);

#endif
