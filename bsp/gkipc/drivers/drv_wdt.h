/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef WDT_H_
#define WDT_H_

struct wdt_driver
{
    unsigned long in_use;

    void* priv;
};

void rt_hw_wdt_init(void);

#endif /* WDT_H_ */
