/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2018-11-27     balanceTWK   change to new framework
=======
 * 2018-11-27     balanceTWK   first version
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
<<<<<<< HEAD
#include "drv_gpio.h"
=======

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
/* defined the LED0 pin: PC0 */
#define LED0_PIN    GET_PIN(C, 0)

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
