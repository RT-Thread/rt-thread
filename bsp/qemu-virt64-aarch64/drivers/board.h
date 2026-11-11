/*
 * File      : board.h
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard    the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

extern unsigned char __bss_start;
extern unsigned char __bss_end;

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
