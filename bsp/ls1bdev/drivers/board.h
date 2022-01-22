/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 * 2011-08-08     lgnq         modified for Loongson LS1B
 */

#ifndef __BOARD_H__
#define __BOARD_H__

void rt_hw_board_init(void);

/* 64M SDRAM */
#define RT_HW_HEAP_END  (0x80000000 + RT_MEM_SIZE * 1024 * 1024)
#define CPU_HZ          (125 * 1000000)

#endif
