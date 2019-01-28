/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-14     aubr.cool    1st version
 */

#ifndef __mb85rcXX_H__
#define __mb85rcXX_H__

#include <rtthread.h>

struct mb85rcxx_config
{
    rt_uint32_t              size;
    rt_uint16_t              addr;
    rt_uint16_t              flags;
};

extern rt_err_t mb85rcxx_register(const char *e2m_device_name,
                                  const char *i2c_bus, void *user_data);

#endif /*__mb85rcXX_H__*/

