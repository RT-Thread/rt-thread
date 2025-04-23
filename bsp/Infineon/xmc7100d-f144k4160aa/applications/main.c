/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-15     Hydevcode    first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_gpio.h"

#define LED_PIN     GET_PIN(10, 3)

int main(void)
{
    rt_kprintf("\nHello RT-Thread!\n");
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}