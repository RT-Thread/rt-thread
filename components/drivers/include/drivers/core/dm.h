/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-20     ErikChan     the first version
 */

#ifndef __RT_DM_H__
#define __RT_DM_H__

#include <rthw.h>
#include <rtdef.h>
#include <drivers/misc.h>
#include <drivers/byteorder.h>

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif

#ifndef RT_USING_SMP
extern int rt_hw_cpu_id(void);
#endif

void rt_dm_secondary_cpu_init(void);

int rt_dm_set_dev_name_auto(rt_device_t dev, const char *prefix);
int rt_dm_get_dev_name_id(rt_device_t dev);

int rt_dm_set_dev_name(rt_device_t dev, const char *format, ...);
const char *rt_dm_get_dev_name(rt_device_t dev);

#endif /* __RT_DM_H__ */
