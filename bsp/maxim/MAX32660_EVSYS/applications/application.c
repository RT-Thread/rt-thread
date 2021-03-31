/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     supperthomas first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#define GPIO_LED_PIN  13

int main(void)
{
    int count = 1;
    rt_pin_mode(GPIO_LED_PIN, PIN_MODE_OUTPUT);
    while (count++)
    {
        rt_pin_write(GPIO_LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        rt_pin_write(GPIO_LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}
