/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-19     Quintin.Z    the first version
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdint.h>
#include <stdbool.h>


// <o> Internal SRAM memory size[Kbytes] <8>
#define NV32_SRAM_SIZE         8
#define NV32_SRAM_END          (0x1FFFF800 + NV32_SRAM_SIZE * 1024)

void rt_hw_board_init(void);


#endif
