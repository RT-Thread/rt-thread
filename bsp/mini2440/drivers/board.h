/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-10-08     Bernard      add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <s3c24x0.h>

void rt_hw_board_init(void);
void rt_hw_sdcard_init(void);

#endif
