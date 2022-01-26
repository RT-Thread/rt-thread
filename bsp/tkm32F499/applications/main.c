/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-10-02     spaceman           first version
 */

#include <rtdbg.h>
#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"


#define LED0_PIN    GET_PIN(B, 14)
#define LED1_PIN    GET_PIN(B, 15)


int main(void)
{
    /* set LED pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(LED0_PIN, PIN_LOW);
    rt_pin_write(LED1_PIN, PIN_LOW);

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
