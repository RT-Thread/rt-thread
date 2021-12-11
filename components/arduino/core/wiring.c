/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */
#include <rtthread.h>
#include <rthw.h>

void init(void)
{

}

unsigned long millis(void)
{
    return rt_tick_get_millisecond();
}

unsigned long micros(void)
{
    return millis()*1000;
}

void delay(unsigned long ms)
{
    rt_thread_mdelay(ms);
}

void delayMicroseconds(unsigned int us)
{
    rt_hw_us_delay(us);
}
