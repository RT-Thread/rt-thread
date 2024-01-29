/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtconfig.h>

extern rt_uint8_t HeapBase;
extern rt_uint8_t HeapLimit;

#define RT_HW_HEAP_BEGIN    (void *)&HeapBase
#define RT_HW_HEAP_END      (void *)&HeapLimit

void rt_hw_board_init(void);

#endif
