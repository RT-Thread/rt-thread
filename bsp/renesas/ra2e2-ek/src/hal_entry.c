/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-10     Sherman       first version
 */
#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>

#define LED3_PIN    "P015" /* Onboard LED pins */

void hal_entry(void)
{
    rt_uint32_t led3_pin = rt_pin_get(LED3_PIN);

    while (1)
    {
        rt_pin_write(led3_pin, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(led3_pin, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
