/*
 * Copyright (c) 2017-2019, MindMotion AE Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-13     henryhuang   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "HAL_device.h"
/* defined the LED pin: PA15 */
#define LED_PIN    38
int main(void)
{
   int count = 1;
    /* set LED4 pin mode to output */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
