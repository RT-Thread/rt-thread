/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RT_HW_CPU_H__
#define __RT_HW_CPU_H__

#include <rtdef.h>
#include <cpuport.h>
#include <mm_aspace.h>

#ifdef RT_USING_OFW
#include <drivers/ofw.h>
#endif

#define ID_ERROR __INT64_MAX__
#define MPIDR_AFFINITY_MASK         0x000000ff00ffffffUL

struct cpu_ops_t
{
    const char *method;
    int     (*cpu_init)(rt_uint32_t id, void *param);
    int     (*cpu_boot)(rt_uint32_t id, rt_uint64_t entry);
    void    (*cpu_shutdown)(void);
};

extern rt_uint64_t rt_cpu_mpidr_table[];

#endif /* __RT_HW_CPU_H__ */
