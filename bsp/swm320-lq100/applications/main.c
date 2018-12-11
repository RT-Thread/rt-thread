/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define LED4_PIN 100

int main(void)
{
    /* user app entry */
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(LED4_PIN, !rt_pin_read(LED4_PIN));
        rt_thread_mdelay(1000);
    }

    return 0;
}
