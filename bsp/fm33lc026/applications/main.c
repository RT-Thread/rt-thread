/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-08-27     Jiao           first version
 * 2022-07-20     wudiyidashi    support gpio
 */

#include <rtthread.h>
#include "board.h"

#define LED1    GET_PIN(D, 4)

int main(void)

{
        rt_pin_mode(LED1, PIN_MODE_OUTPUT);
        rt_pin_write(LED1, PIN_HIGH);

    while (1)
    {
        rt_pin_write(LED1, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1, PIN_LOW);
        rt_thread_mdelay(500);
    }

}
