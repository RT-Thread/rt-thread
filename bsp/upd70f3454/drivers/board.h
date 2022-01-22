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

#include "rtdef.h"

#define LB900        1
#define LM600        2
#define LM201R       3
#define LM201P       4
#define LM101        5

#define PLATFORM     LM201R

#define ENTER_KEY    0x1d
#define UP_KEY       0x1b
#define DOWN_KEY     0x17
#define LEFT_KEY     0x0f
#define RIGHT_KEY    0x1e

void rt_hw_board_init(void);
rt_uint8_t get_key(void);

#endif
