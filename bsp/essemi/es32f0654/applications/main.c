/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-28     wangyq        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_gpio.h"

#ifdef ES_RTT_APP_LED_PIN
#define LED_PIN    ES_RTT_APP_LED_PIN
#else
#define LED_PIN    GET_PIN( C , 8 )
#endif

int main(void)
{
    int count = 1;
    /* set PC08 pin mode to output */
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
