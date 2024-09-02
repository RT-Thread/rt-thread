/*
 * COPYRIGHT (C) 2011-2023, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-12     heyuanjie87  first version.
 */

#ifndef  __DEV_WATCHDOG_H__
#define  __DEV_WATCHDOG_H__

#include <rtthread.h>

#define RT_DEVICE_CTRL_WDT_GET_TIMEOUT    (RT_DEVICE_CTRL_BASE(WDT) + 1) /* get timeout(in seconds) */
#define RT_DEVICE_CTRL_WDT_SET_TIMEOUT    (RT_DEVICE_CTRL_BASE(WDT) + 2) /* set timeout(in seconds) */
#define RT_DEVICE_CTRL_WDT_GET_TIMELEFT   (RT_DEVICE_CTRL_BASE(WDT) + 3) /* get the left time before reboot(in seconds) */
#define RT_DEVICE_CTRL_WDT_KEEPALIVE      (RT_DEVICE_CTRL_BASE(WDT) + 4) /* refresh watchdog */
#define RT_DEVICE_CTRL_WDT_START          (RT_DEVICE_CTRL_BASE(WDT) + 5) /* start watchdog */
#define RT_DEVICE_CTRL_WDT_STOP           (RT_DEVICE_CTRL_BASE(WDT) + 6) /* stop watchdog */

struct rt_watchdog_ops;
struct rt_watchdog_device
{
    struct rt_device parent;
    const struct rt_watchdog_ops *ops;
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

#endif /* __DEV_WATCHDOG_H__ */
