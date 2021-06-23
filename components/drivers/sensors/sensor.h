/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-31     flybreak     first version
 * 2021-06-23     linpeng      added function declaration
 */

#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

int rt_hw_sensor_register(rt_sensor_t sensor,
                          const char *name,
                          rt_uint32_t flag,
                          void *data);

#ifdef __cplusplus
}
#endif

#endif /*__SENSOR_H__*/
