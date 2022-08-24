/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-23     liYony       first version
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include "ch32v30x.h"

/* board configuration */
#define SRAM_SIZE  96
#define SRAM_END (0x20000000 + SRAM_SIZE * 1024)

extern int _ebss;
#define HEAP_BEGIN  ((void *)&_ebss)
#define HEAP_END    (SRAM_END-_stack_size)

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
