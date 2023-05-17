/*
 * Copyright (C) 2022 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-05-08     liuhy          the first version
 */

#include "board.h"

#ifdef ES_RTT_APP_LED_PIN
#define LED_PIN    ES_RTT_APP_LED_PIN
#else
#define LED_PIN    GET_PIN( C , 12 )
#endif

int main(void)
{
    int count = 1;
    /* set pin mode to output */
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

