/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 * 2024-06-28     yuanzihao    adaptation for SkyStar HC32F4A0PITB version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED_GREEN pin: PB2 */
#define LED_GREEN_PIN GET_PIN(B, 2)


int main(void)
{
    /* set LED_GREEN_PIN pin mode to output */
    rt_pin_mode(LED_GREEN_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_GREEN_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_GREEN_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

