/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   change to new framework
 */
 
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

int main(void)
{
    while (1)
    {
        rt_pin_write(LED0_PIN, !rt_pin_read(LED0_PIN));
        rt_thread_mdelay(500);
    }
}
