/*
 * File      : board_coretimer.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-01-01     Urey      first version
 */
#ifndef _BOARD_CORETIMER_H_
#define _BOARD_CORETIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CK_TIMER_BASE     (0xE000E000)

#define CORET_CSR         (volatile unsigned int *)(CK_TIMER_BASE + 0x10)
#define CORET_RVR         (volatile unsigned int *)(CK_TIMER_BASE + 0x14)
#define CORET_CVR         (volatile unsigned int *)(CK_TIMER_BASE + 0x18)
#define CORET_CALIB       (volatile unsigned int *)(CK_TIMER_BASE + 0x1c)

/*
 *  define the bits for TxControl
 */
#define CORETIM_TXCONTROL_ENABLE      (1UL << 0)
#define CORETIM_TXCONTROL_INTMASK     (1UL << 1)
#define CORETIM_TXCONTROL_MODE        (1UL << 16)


#ifdef __cplusplus
}
#endif

#endif /* _BOARD_CORETIMER_H_ */
