/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2017, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
