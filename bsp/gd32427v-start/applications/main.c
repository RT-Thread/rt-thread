/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                Notes
 * 2018-05-18     dozingfiretruck       first implementation
 */

#include <stdio.h>
#include <rtthread.h>

#include "drv_gpio.h"

#define LED2_PIN    GET_PIN(C, 6)

int main(void)
{
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
    }

}
