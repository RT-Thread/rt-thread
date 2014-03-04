/*
 * File      : watchdog.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012-2014, Shanghai Real-Thread Electronic Technology Co.,Ltd
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
 * 2012-09-12     heyuanjie87  first version.
 */

#ifndef  __WATCHDOG_H__
#define  __WATCHDOG_H__

#include <rtthread.h>

#define RT_DEVICE_CTRL_WDT_GET_TIMEOUT    (1) /* get timeout(in seconds) */
#define RT_DEVICE_CTRL_WDT_SET_TIMEOUT    (2) /* set timeout(in seconds) */
#define RT_DEVICE_CTRL_WDT_GET_TIMELEFT   (3) /* get the left time before reboot(in seconds) */
#define RT_DEVICE_CTRL_WDT_KEEPALIVE      (4) /* refresh watchdog */
#define RT_DEVICE_CTRL_WDT_START          (5) /* start watchdog */
#define RT_DEVICE_CTRL_WDT_STOP           (6) /* stop watchdog */

struct rt_watchdog_ops;
struct rt_watchdog_device
{
    struct rt_device parent;
    struct rt_watchdog_ops *ops;
};
typedef struct rt_watchdog_device rt_watchdog_t;

struct rt_watchdog_ops
{
    rt_err_t (*init)(rt_watchdog_t *wdt);
    rt_err_t (*control)(rt_watchdog_t *wdt, int cmd, void *arg);
};

rt_err_t rt_hw_watchdog_register(rt_watchdog_t *wdt,
                                 const char    *name,
                                 rt_uint32_t    flag,
                                 void          *data);

#endif /* __WATCHDOG_H__ */
