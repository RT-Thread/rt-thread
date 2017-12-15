/*
 * File      : drv_reset.h
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
 * 2016Äê7ÔÂ29ÈÕ     Urey         the first version
 */

#ifndef _DRV_RESET_H_
#define _DRV_RESET_H_

/* WDT */
void wdt_start_count(int msecs);
void wdt_stop_count(void);
void wdt_clear(void);

/* hibernate */
void x1000_hibernate(void);


/* Reset */
/* reset_cmd[] = "wdt","hibernate","recovery" */
int x1000_reset(const char *reset_cmd);


#define RESET_HR_BIT	(0x01 << 3)
#define RESET_P0R_BIT	(0x01 << 2)
#define RESET_WR_BIT	(0x01 << 1)
#define RESET_PR_BIT	(0x01 << 0)
uint32_t x1000_get_last_reset(void);


#endif /* _DRV_RESET_H_ */
