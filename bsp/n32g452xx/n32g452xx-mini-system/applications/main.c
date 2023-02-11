/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <stdint.h>
#include <rtthread.h>
#include <rtdevice.h>

/* defined the LED1 pin: PB5 */
#define LED1_NAME "PB.5"
rt_base_t led1_pin;

int main(void)
{
    uint32_t Speed = 200;

    /* get LED1 pin id by name */
    led1_pin = rt_pin_get(LED1_NAME);

    /* set LED1 pin mode to output */
    rt_pin_mode(led1_pin, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(led1_pin, PIN_LOW);
        rt_thread_mdelay(Speed);
        rt_pin_write(led1_pin, PIN_HIGH);
        rt_thread_mdelay(Speed);
    }
}

