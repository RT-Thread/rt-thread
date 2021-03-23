/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-30     ZeroFree     the first version
 */

#ifndef __DRV_WLAN_H__
#define __DRV_WLAN_H__

#include <rtthread.h>

int rt_hw_wlan_init(void);
int rt_hw_wlan_get_initialize_status(void);
int rt_hw_wlan_wait_init_done(rt_uint32_t time_ms);

#endif
