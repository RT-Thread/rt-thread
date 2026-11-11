/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-05     Chushicheng  the first version
 */

#ifndef DRV_WDT_H
#define DRV_WDT_H

#include <rtdevice.h>

/* pico wdt driver class */
struct pico_wdt
{
    rt_watchdog_t watchdog;
    rt_uint16_t is_start;
};

int rt_hw_wdt_init(void);

#endif  /* DRV_WDT_H */
