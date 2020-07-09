/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef FH_WDT_H_
#define FH_WDT_H_

#include "fh_def.h"

#define WDOG_CONTROL_REG_OFFSET                  0x00
#define WDOG_CONTROL_REG_WDT_EN_MASK             0x01
#define WDOG_CONTROL_REG_RMOD_MASK               0x02
#define WDOG_TIMEOUT_RANGE_REG_OFFSET            0x04
#define WDOG_CURRENT_COUNT_REG_OFFSET            0x08
#define WDOG_COUNTER_RESTART_REG_OFFSET          0x0c

#define WDOG_COUNTER_RESTART_KICK_VALUE      0x76

/* Hardware timeout in seconds */
#define WDT_HW_TIMEOUT 2
/* User land timeout */
#define WDT_HEARTBEAT 15

/* The maximum TOP (timeout period) value that can be set in the watchdog. */
#define FH_WDT_MAX_TOP      15

#define WDT_TIMEOUT     (HZ / 2)

struct fh_wdt_obj
{
    int                 id;
    int                 irq;
    unsigned int         base;
};

void WDT_Enable(struct fh_wdt_obj *wdt_obj, int enable);

rt_inline int WDT_IsEnable(struct fh_wdt_obj *wdt_obj)
{
    return GET_REG(wdt_obj->base + WDOG_CONTROL_REG_OFFSET) &
        WDOG_CONTROL_REG_WDT_EN_MASK;
}

void WDT_SetTopValue(struct fh_wdt_obj *wdt_obj, int top);
void WDT_SetCtrl(struct fh_wdt_obj *wdt_obj, UINT32 reg);
void WDT_Kick(struct fh_wdt_obj *wdt_obj);
unsigned int  WDT_GetCurrCount(struct fh_wdt_obj *wdt_obj);

#endif /* FH_WDT_H_ */
