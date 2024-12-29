/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/12/11     flyingcys    The first version
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtconfig.h>

extern unsigned long __heap_start;
extern unsigned long __heap_end;

#define RT_HW_HEAP_BEGIN    (void *)&__heap_start
#define RT_HW_HEAP_END      (void *)&__heap_end

void rt_hw_board_init(void);

#endif