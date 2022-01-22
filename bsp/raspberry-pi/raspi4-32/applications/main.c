/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define     ACTLED      (42)

int main(int argc, char** argv)
{
    rt_kprintf("Hi, this is RT-Thread!!\n");

    rt_pin_mode(ACTLED, PIN_MODE_OUTPUT);

    while(1)
    {
        rt_pin_write(ACTLED, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(ACTLED, PIN_LOW);
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
