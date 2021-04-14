/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2011-03-04     lgnq         add board.h to FM3 bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

//Internal SRAM memory size[Kbytes] <8-64>
//MB9BF500 : 32
//MB9BF504 : 32
//MB9BF505 : 48
//MB9BF506 : 64
#define FM3_SRAM_SIZE         64
#define FM3_SRAM_END          (0x1FFF8000 + FM3_SRAM_SIZE * 1024)

void rt_hw_board_init(void);

#endif
