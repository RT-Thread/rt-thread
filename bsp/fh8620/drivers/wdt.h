/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef WDT_H_
#define WDT_H_



struct wdt_driver
{
    //struct clk          *clk;
    unsigned long       in_use;
    unsigned long       next_heartbeat;
    //struct timer_list   timer;
    int                 expect_close;

    void* priv;
};




#endif /* WDT_H_ */
