/*
 * Copyright (c) 2021-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2026-09-27     RT-Thread     first version (ESP32-S3-DevKitM-1)
 */

#include <rtthread.h>

/*
 * v1 of this BSP brings up msh over UART0.
 * GPIO, Wi-Fi, BLE and the on-board LED are left for later.
 */
int main(void)
{
    rt_kprintf("Hello! RT-Thread on ESP32-S3-DevKitM-1\r\n");
    while (1)
    {
        rt_thread_mdelay(10000);
    }
}
