/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2020, Shenzhen Academy of Aerospace Technology
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <bm3803.h>

#define CPU_FREQ 90000000

void rt_hw_board_init(void);

#endif
