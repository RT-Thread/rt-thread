/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(2, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(2, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(2, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
