/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-17     supperthomas first version
 */

#include "drivers/dev_pin.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PO1 */
#define LED_RED_PIN 	GET_PIN(O, 1)
#define LED_BLUE_PIN 	GET_PIN(O, 5)

int main(void)
{
    rt_pin_mode(LED_RED_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_BLUE_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(LED_BLUE_PIN, PIN_HIGH);

    while(1)
    {
        rt_thread_mdelay(500);
        rt_pin_write(LED_RED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_RED_PIN, PIN_LOW);
    }
    return RT_EOK;
}
