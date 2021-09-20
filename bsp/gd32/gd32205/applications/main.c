/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-21     iysheng      the first version
 */

#include <stdio.h>
#include <rtthread.h>
#include "rtdevice.h"

/* HEART PIN is GPIOB_15 */
#define HEART_PIN    31

int main(void)
{
    while(1)
    {
        rt_pin_write(HEART_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(HEART_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return 0;
}
