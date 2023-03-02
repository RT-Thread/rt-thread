/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-01     Rbb666        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: PA7 */
#define LED1_PIN    GET_PIN(A, 7)

int main(void)
{
    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
