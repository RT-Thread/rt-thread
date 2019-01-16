/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     gztss        write for stm32g072rb-necleo board
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_gpio.h"

/* defined the LED pin: PA5 */
#define LED_PIN     GET_PIN(A, 5)

int main(void)
{
    while (1)
    {
        rt_pin_write(LED_PIN, !rt_pin_read(LED_PIN));
        rt_thread_mdelay(400);
    }
}
