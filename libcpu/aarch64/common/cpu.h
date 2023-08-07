/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RT_HW_CPU_H__
#define __RT_HW_CPU_H__

#include <rthw.h>
#include <rtthread.h>
#include <stdbool.h>

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif /* RT_CPUS_NR */

#ifdef RT_USING_SMP
struct cpu_ops_t
{
    const char *method;
    int     (*cpu_init)(rt_uint32_t id);
    int     (*cpu_boot)(rt_uint32_t id);
    void    (*cpu_shutdown)(void);
};

/**
 * Identifier to mark a wrong CPU MPID.
 * All elements in rt_cpu_mpidr_early[] should be initialized with this value
 */
#define ID_ERROR __INT64_MAX__

extern rt_uint64_t rt_cpu_mpidr_early[];
extern struct dtb_node *_cpu_node[];

#define cpuid_to_hwid(cpuid) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? rt_cpu_mpidr_early[cpuid] : ID_ERROR)
#define set_hwid(cpuid, hwid) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? (rt_cpu_mpidr_early[cpuid] = (hwid)) : ID_ERROR)
#define get_cpu_node(cpuid) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? _cpu_node[cpuid] : NULL)
#define set_cpu_node(cpuid, node) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? (_cpu_node[cpuid] = node) : NULL)

extern int rt_hw_cpu_init();

extern int rt_hw_cpu_boot_secondary(int num_cpus, rt_uint64_t *cpu_hw_ids, struct cpu_ops_t *cpu_ops[]);

extern void rt_hw_secondary_cpu_idle_exec(void);

extern struct cpu_ops_t cpu_ops_psci;

extern struct cpu_ops_t cpu_ops_spin_tbl;

#endif /* RT_USING_SMP */

extern void (*system_off)(void);

#endif /* __RT_HW_CPU_H__ */