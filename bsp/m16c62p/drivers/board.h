/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2010-02-04     Magicoe      add board.h to LPC176x bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#define M16C62P_SRAM_SIZE         31L
#define M16C62P_SRAM_END          (0x400 + M16C62P_SRAM_SIZE * 1024 - 1)

void rt_hw_board_init(void);

#endif
