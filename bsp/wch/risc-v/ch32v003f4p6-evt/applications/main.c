/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-25     seteiro      CH32V003F4P6-EVT
 */

#include <rtthread.h>

int main(void)
{
    rt_kprintf("MCU: CH32V003F4P6\n");
    while (1)
        rt_thread_mdelay(1000);
}
