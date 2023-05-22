/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-13     flybreak     the first version
 */

#ifndef __RT_DEV_BUS_H__
#define __RT_DEV_BUS_H__
#include <rtthread.h>

rt_device_t rt_device_bus_create(char *name, int attach_size);
rt_err_t rt_device_bus_destroy(rt_device_t dev);

#endif /* __RT_BUS_H__ */
