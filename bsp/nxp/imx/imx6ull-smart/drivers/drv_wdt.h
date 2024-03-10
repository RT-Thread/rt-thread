/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-07-28     songchao           first version
 */

#ifndef  __WATCHDOG_H__
#define  __WATCHDOG_H__

#include <rtthread.h>
#include "fsl_wdog.h"

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
    const struct rt_watchdog_ops *ops;
    const char                  *name;
    rt_uint32_t                 paddr;
    rt_uint32_t                 vaddr;
    rt_uint32_t                 irqno;
    wdog_config_t *config;
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
