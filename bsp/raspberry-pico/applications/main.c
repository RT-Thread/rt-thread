/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <rtthread.h>
#include <rtdevice.h>

#define LED_PIN 25

int main(void)
{
    rt_kprintf("Hello, RT-Thread!\n");

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_PIN, 1);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_PIN, 0);
        rt_thread_mdelay(1000);
    }
}

