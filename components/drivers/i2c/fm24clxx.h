/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-14     aubr.cool    1st version
 */

#ifndef __FM24CLXX_H__
#define __FM24CLXX_H__

#include <rtthread.h>

struct fm24clxx_config
{
    rt_uint32_t              size;
    rt_uint16_t              addr;
    rt_uint16_t              flags;
};

extern rt_err_t fm24clxx_register(const char *e2m_device_name,
                                  const char *i2c_bus, void *user_data);

#endif /*__FM24CLXX_H__*/