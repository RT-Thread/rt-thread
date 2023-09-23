/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     yby          the first version
 */

#include "board.h"

#define LED_N0 rt_pin_get("PN.0")
#define LED_N1 rt_pin_get("PN.1")
#define LED_F0 GET_PIN(F, 0)
#define LED_F4 GET_PIN(F, 4)

int main(void)
{
    rt_uint32_t count = 1;

    rt_pin_mode(LED_N0, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_N1, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_F0, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_F4, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED_N0, PIN_HIGH);
        rt_pin_write(LED_N1, PIN_HIGH);
        rt_pin_write(LED_F0, PIN_HIGH);
        rt_pin_write(LED_F4, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_N0, PIN_LOW);
        rt_pin_write(LED_N1, PIN_LOW);
        rt_pin_write(LED_F0, PIN_LOW);
        rt_pin_write(LED_F4, PIN_LOW);
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
