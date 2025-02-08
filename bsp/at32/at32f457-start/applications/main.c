/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-28     shelton      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "drv_gpio.h"

/* defined the led2 pin: pd13 */
#define LED2_PIN    GET_PIN(D, 13)
/* defined the led3 pin: pd14 */
#define LED3_PIN    GET_PIN(D, 14)
/* defined the led4 pin: pd15 */
#define LED4_PIN    GET_PIN(D, 15)

int main(void)
{
    rt_uint32_t speed = 200;
    /* set led2 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    /* set led3 pin mode to output */
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    /* set led4 pin mode to output */
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED3_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED4_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
        rt_pin_write(LED4_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
    }
}
