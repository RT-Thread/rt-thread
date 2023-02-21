/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rthw.h>
#include <rtthread.h>

#include "cpu.h"

#ifdef RT_USING_SMART
#include <ioremap.h>
#else
#define rt_ioremap(x, ...) (x)
#define rt_iounmap(x)
#endif

#define DBG_TAG "libcpu.aarch64.cpu_spin_table"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include "cpu_ops_common.h"

#ifdef RT_USING_SMP
#ifdef RT_USING_FDT
#include <dtb_node.h>

static rt_uint64_t cpu_release_addr[RT_CPUS_NR];

static int spin_table_cpu_init(rt_uint32_t cpuid)
{
    struct dtb_node *cpu = get_cpu_node(cpuid);
    if (!cpu)
        return -1; /* uninitialized cpu node in fdt */

    int size;
    rt_uint64_t *phead = (rt_uint64_t*)dtb_node_get_dtb_node_property_value(cpu, "cpu-release-addr", &size);
    cpu_release_addr[cpuid] = fdt64_to_cpu(*phead);

    LOG_D("Using release address 0x%p for CPU %d", cpu_release_addr[cpuid], cpuid);
    return 0;
}

static int spin_table_cpu_boot(rt_uint32_t cpuid)
{
    rt_uint64_t secondary_entry_pa = get_secondary_entry_pa();
    if (!secondary_entry_pa)
        return -1;

    // map release_addr to addressable place
    void *rel_va = (void *)cpu_release_addr[cpuid];

#ifdef RT_USING_SMART
    rel_va = rt_ioremap(rel_va, sizeof(cpu_release_addr[0]));
#endif
    if (!rel_va)
    {
        LOG_E("IO remap failing");
        return -1;
    }

    __asm__ volatile("str %0, [%1]" ::"rZ"(secondary_entry_pa), "r"(rel_va));
    __asm__ volatile("dsb sy");
    __asm__ volatile("sev");
    rt_iounmap(rel_va);
    return 0;
}
#endif /* RT_USING_FDT */

struct cpu_ops_t cpu_ops_spin_tbl = {
    .method = "spin-table",
#ifdef RT_USING_FDT
    .cpu_init = spin_table_cpu_init,
    .cpu_boot = spin_table_cpu_boot,
#endif
};

#endif /* RT_USING_SMP */