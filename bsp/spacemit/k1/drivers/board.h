/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

extern unsigned int __bss_start;
extern unsigned int __bss_end;

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
