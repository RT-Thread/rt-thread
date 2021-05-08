/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-09     forest-rain   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* STM32WL55JC_NUCLEO Color led  */
#define LED_BLUE_PIN       GET_PIN(B,15)  /* defined the LED_BLUE pin: PB15 */
#define LED_GREEN_PIN      GET_PIN(B,9)
#define LED_RED_PIN        GET_PIN(B,11)

int main(void)
{
    /* set LED_BLUE pin mode to output */
    rt_pin_mode(LED_BLUE_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_BLUE_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_BLUE_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
