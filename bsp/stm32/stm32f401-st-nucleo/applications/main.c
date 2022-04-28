/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2022-04-19     Meco Man     solve LED interferes with SPI
 */

#include <rtthread.h>

int main(void)
{
    while (1)
    {
        rt_kprintf("Hello RT-Thread!\n");
        rt_thread_mdelay(1000);
    }
}
