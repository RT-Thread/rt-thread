/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

unsigned long gkosGetTicks(void);
void rt_hw_board_init(void);
int rt_board_driver_init(void);

#endif
