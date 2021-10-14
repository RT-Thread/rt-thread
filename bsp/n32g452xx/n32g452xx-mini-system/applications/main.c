/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
#define LED1_PIN    57

int main(void)
{
    uint32_t Speed = 200;
    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(Speed);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(Speed);
    }
}

