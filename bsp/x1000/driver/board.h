/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

#include "x1000.h"

#define RT_USING_JZ_X1000

// #define BOARD_PHOENIX
// #define BOARD_CANNA

#ifdef BOARD_PHOENIX
#define RT_USING_EMAC
#endif

/*********************************************************************************************************
**   Clock for Board
*********************************************************************************************************/
#define BOARD_EXTAL_CLK     24000000
#define BOARD_RTC_CLK       32768
#define BOARD_CPU_CLK       (1008 * 1000 * 1000UL)


/*********************************************************************************************************
**   HEAP Setting
*********************************************************************************************************/
extern unsigned char __bss_start;
extern unsigned char __bss_end;

#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(0x80000000 + 32 * 1024 * 1024)

/*********************************************************************************************************
**   UART Setting
*********************************************************************************************************/
#define RT_USING_UART2

#endif
