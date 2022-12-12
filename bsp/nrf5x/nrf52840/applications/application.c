/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-29     supperthomas first version
 * 2021-06-26     supperthomas fix led
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

int main(void)
{
    int count = 1;
    rt_pin_mode(RT_BSP_LED_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(RT_BSP_LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        rt_pin_write(RT_BSP_LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}

