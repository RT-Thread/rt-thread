/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-21     GuEe-GUI     replace with ofw
 */
#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "cpu.aa64"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpu.h>
#include <cpuport.h>

#include <ioremap.h>
#include <drivers/core/dm.h>

#ifdef RT_USING_OFW

static rt_uint64_t cpu_release_addr[RT_CPUS_NR];

static int spin_table_cpu_init(rt_uint32_t cpuid, void *param)
{
   struct rt_ofw_node *cpu_np = param;

   rt_ofw_prop_read_u64(cpu_np, "cpu-release-addr", &cpu_release_addr[cpuid]);

   LOG_D("Using release address 0x%p for CPU %d", cpu_release_addr[cpuid], cpuid);

   return 0;
}

static int spin_table_cpu_boot(rt_uint32_t cpuid, rt_uint64_t entry)
{
    void *cpu_release_vaddr;

    cpu_release_vaddr = rt_ioremap((void *)cpu_release_addr[cpuid], sizeof(cpu_release_addr[0]));

    if (!cpu_release_vaddr)
    {
        LOG_E("IO remap failing");
        return -1;
    }

    __asm__ volatile ("str %0, [%1]" ::"rZ"(entry), "r"(cpu_release_vaddr));
    rt_hw_barrier(dsb, sy);
    rt_hw_sev();

    rt_iounmap(cpu_release_vaddr);

    return 0;
}

struct cpu_ops_t cpu_spin_table_ops =
{
    .method = "spin-table",
    .cpu_init = spin_table_cpu_init,
    .cpu_boot = spin_table_cpu_boot,
};
#endif
