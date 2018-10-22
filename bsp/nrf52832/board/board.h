/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>

#include "nrf.h"

#define CHIP_SRAM_END       (0x20000000 + 64*1024)

void rt_hw_board_init(void);

#endif

