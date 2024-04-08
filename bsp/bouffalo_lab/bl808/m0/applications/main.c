/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 * 2023/11/23     flyingcys    add wifi driver
  */

#include <rtthread.h>
#include <stdio.h>
#include <rtdevice.h>

int main(void)
{
    rt_kprintf("Hello, RISC-V!\n");

#ifdef BSP_USING_WIFI
    /* set wifi work mode */
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);
#endif /* BSP_USING_WIFI */

    return 0;
}
