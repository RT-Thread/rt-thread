/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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

#include <rtthread.h>
#include <stdint.h>
#include "x1000.h"

#define RT_USING_JZ_X1000
#define X1000

#ifdef BOARD_HALLEY2_FIR
#include "board/halley2_fir/board_halley2_fir.h"
#endif

#ifdef BOARD_HALLEY2_REALBOARD
#include "board/halley2_realboard/board_halley2_readboard.h"
#endif

#ifdef BOARD_HALLEY2_REALBOARD_V2
#include "board/halley2_realboard_v2/board_halley2_readboard_v2.h"
#endif

#ifdef BOARD_HALLEY2
#include "board/halley2/board_halley2.h"
#endif

#ifdef BOARD_PHOENIX
#include "board/phoenix/board_phoenix.h"
#endif

/*
 * Clock setting
 */
#define BOARD_EXTAL_CLK     24000000
#define BOARD_RTC_CLK       32768
#define BOARD_CPU_CLK       (1008 * 1000 * 1000UL)

#define BOARD_APLL_FREQ     1008000000  /*If APLL not use mast be set 0*/
#define BOARD_MPLL_FREQ     600000000   /*If MPLL not use mast be set 0*/

/*
 * Heap setting
 */
extern unsigned char __bss_start;
extern unsigned char __bss_end;

#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(0x80000000 + 32 * 1024 * 1024)

/* HW EVENT */
#define EVENT_NONE                  0x0000

#define EVENT_TYPE_MSK              0xFF00
#define EVENT_VALUE_MSK             0x00FF

#define EVENT_LINEIN                0x0100
#define EVENT_LINEIN_INSERT         0x0101
#define EVENT_LINEIN_REMOVE         0x0102
#define EVENT_LINEIN_SHUTDOWN       0x0103

#define EVENT_BAT                   0x0200
#define EVENT_BAT_ALONE             0x0201
#define EVENT_BAT_CHARGE_IN         0x0202
#define EVENT_BAT_CHARGE_FULL       0x0203
#define EVENT_BAT_ERROR             0x0204

#define EVENT_KEY_DOWN              0x0300
#define EVENT_KEY_UP                0x0400

#endif /* _BOARD_H_ */
