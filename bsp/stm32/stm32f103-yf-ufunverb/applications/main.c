/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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

/* defined the LED_B pin: PA0 */
#define LED_B    GET_PIN(A, 0)

int main(void)
{
    int count = 1;
    /* set LED_B pin mode to output */
    rt_pin_mode(LED_B, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED_B, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_B, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
