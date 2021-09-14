/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

int main(void)
{
    /* LED pin: PB13 */
    rt_uint16_t led = rt_pin_get("PB.13");

    /* set LED pin mode to output */
    rt_pin_mode(led, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(led, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(led, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
