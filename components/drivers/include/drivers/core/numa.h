/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-24     GuEe-GUI     the first version
 */

#ifndef __RT_DM_NUMA_H__
#define __RT_DM_NUMA_H__

#include <rthw.h>
#include <rtthread.h>

#include <bitmap.h>

/* NUMA: Non-Uniform Memory Access */

int rt_numa_cpu_id(int cpuid);
int rt_numa_device_id(struct rt_device *dev);
rt_err_t rt_numa_memory_affinity(rt_uint64_t phy_addr, rt_bitmap_t *out_affinity);

#endif /* __RT_DM_NUMA_H__ */
