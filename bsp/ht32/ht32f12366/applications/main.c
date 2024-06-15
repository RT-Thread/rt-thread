/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

/* defined the led1 pin: pd15 */
#define LED1_PIN    GET_PIN(D, 15)
/* defined the led2 pin: pe0 */
#define LED2_PIN    GET_PIN(E, 0)

int main(void)
{
    rt_uint32_t speed = 200;
    /* set led1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    /* set led2 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
    }
}
