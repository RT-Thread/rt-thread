/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-05     thread-liu   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LD4 pin: PD8 */
#define LED4_PIN    GET_PIN(D, 8)

int main(void)
{
    /* set LD8 pin mode to output */
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED4_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED4_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
