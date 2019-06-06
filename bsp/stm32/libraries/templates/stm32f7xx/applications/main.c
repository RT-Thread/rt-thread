/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2018-11-06     SummerGift   change to new framework
=======
 * 2018-11-06     SummerGift   first version
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

int main(void)
{
    int count = 1;
    while (count++)
    {
        // rt_pin_write(LED0_PIN, !rt_pin_read(LED0_PIN));
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}
