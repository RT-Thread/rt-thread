/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-23     liYony       first version
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
