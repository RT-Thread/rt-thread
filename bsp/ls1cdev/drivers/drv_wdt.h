/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     sundm75       first version
 */

#ifndef WDT_H_
#define WDT_H_

struct wdt_driver
{
    unsigned long in_use;

    void* priv;
};

int rt_hw_wdt_init(void);

#endif /* WDT_H_ */
