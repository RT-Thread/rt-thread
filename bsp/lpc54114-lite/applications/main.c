/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <rtthread.h>
#include <rtdevice.h>

#define LED4_PIN  30   /* PIO0_30 */

int main(void)
{
    /* user app entry */
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED4_PIN, !rt_pin_read(LED4_PIN));
        rt_thread_delay(1000);
    }
}
