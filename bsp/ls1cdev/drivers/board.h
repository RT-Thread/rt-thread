/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-06-25     Bernard        first version
 * 2011-08-08     lgnq             modified for Loongson LS1B
 * 2015-07-06     chinesebear   modified for Loongson LS1C
 */

#ifndef __BOARD_H__
#define __BOARD_H__

void rt_hw_board_init(void);

/* 32M SDRAM */
#define RT_HW_HEAP_END    (0x80000000 + 32 * 1024 * 1024)
#define CPU_HZ            (252 * 1000000)

#endif
