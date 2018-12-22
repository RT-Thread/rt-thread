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

#include "inc/fh_driverlib.h"

void WDT_Enable(struct fh_wdt_obj *wdt_obj, int enable)
{
    SET_REG(wdt_obj->base + WDOG_CONTROL_REG_OFFSET, enable);
}

void WDT_SetTopValue(struct fh_wdt_obj *wdt_obj, int top)
{
    SET_REG(wdt_obj->base + WDOG_TIMEOUT_RANGE_REG_OFFSET, top);
}

void WDT_SetCtrl(struct fh_wdt_obj *wdt_obj, UINT32 reg)
{
    SET_REG(wdt_obj->base + WDOG_CONTROL_REG_OFFSET, reg);
}

void WDT_Kick(struct fh_wdt_obj *wdt_obj)
{
    SET_REG(wdt_obj->base + WDOG_COUNTER_RESTART_REG_OFFSET, WDOG_COUNTER_RESTART_KICK_VALUE);
}

UINT32 WDT_GetCurrCount(struct fh_wdt_obj *wdt_obj)
{
    return GET_REG(wdt_obj->base + WDOG_CURRENT_COUNT_REG_OFFSET);
}
