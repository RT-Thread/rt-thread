/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#define RT_HW_HEAP_BEGIN    (void*)0x0C000000
#define RT_HW_HEAP_END      (void*)0x0C100000

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */

