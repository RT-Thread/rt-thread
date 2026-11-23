/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-21     seteiro      CH32V203C8T6-EVT-R0: print chip id, no LED default
 */

#include <rtthread.h>

int main(void)
{
    rt_kprintf("MCU: CH32V203C8T6\n");

    while (1)
    {
        rt_thread_mdelay(1000);
    }
}
