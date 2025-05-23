/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#ifndef __CPU_H__
#define __CPU_H__

#include <rtdef.h>

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif

struct cpu_ops_t
{
    const char *method;
    int     (*cpu_init)(rt_uint32_t id, void *param);
    int     (*cpu_boot)(rt_uint32_t id, rt_uint64_t entry);
    void    (*cpu_shutdown)(void);
};

extern rt_ubase_t boot_cpu_hartid;
extern void _secondary_cpu_entry(void);

#if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
extern char __percpu_real_end, __percpu_end, __percpu_start;
#endif /* RT_USING_SMP && ARCH_MM_MMU */

rt_ubase_t riscv_cpu_id_to_hartid(int cpu_id);
int riscv_hartid_to_cpu_id(rt_ubase_t hartid);
void riscv_hartid_remap_cpu_id(rt_ubase_t hartid, int cpu_id);

#endif /* __CPU_H__ */
