/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-22     LZero        first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "drv_gpio.h"

#define LED_PIN     GET_PIN(16, 1)

int main(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    for (;;)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
