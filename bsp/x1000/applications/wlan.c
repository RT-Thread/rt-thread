/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>

#ifdef RT_USING_WIFI
#include "wlan_wiced.h"

int wifi_init(void)
{
    wifi_hw_init();
}
INIT_ENV_EXPORT(wifi_init);
#endif
