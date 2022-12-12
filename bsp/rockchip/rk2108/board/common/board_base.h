/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-12     Steven Liu   first implementation
 */

#ifndef __BOARD_BASE_H__
#define __BOARD_BASE_H__

#include "rtconfig.h"
#include "hal_base.h"

extern uint32_t __heap_begin[];
extern uint32_t __heap_end[];

#define RT_HW_HEAP_BEGIN    (void*)&__heap_begin
#define RT_HW_HEAP_END      (void*)&__heap_end

void rt_hw_board_init(void);

#endif
