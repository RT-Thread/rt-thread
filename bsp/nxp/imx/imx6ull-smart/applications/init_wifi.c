/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/01/20     bernard      the first version
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <rtthread.h>

#ifdef PKG_USING_RW007
#define WIFI_SH_PATH "/sd/wifi.sh"

int rw007_wifi_init(void)
{
    if (access(WIFI_SH_PATH, 0) != -1)
    {
        msh_exec(WIFI_SH_PATH, rt_strlen(WIFI_SH_PATH));
    }
    else
    {
        rt_kprintf("%s wi-fi configuration file not exist in sd card!\n", WIFI_SH_PATH);
    }

    return 0;
}
INIT_APP_EXPORT(rw007_wifi_init);
#endif
