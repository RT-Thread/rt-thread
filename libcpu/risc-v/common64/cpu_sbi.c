/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <sbi.h>
#include <cpu.h>
#include <cpuport.h>

static int sbi_cpu_boot(rt_uint32_t cpuid, rt_uint64_t entry)
{
    rt_ubase_t hartid = cpuid;

    return sbi_hsm_hart_start(hartid, entry, entry);
}

static void sbi_cpu_shutdown(void)
{
    sbi_hsm_hart_stop();
}

struct cpu_ops_t cpu_sbi_ops =
{
    .method = "sbi",
    .cpu_boot = sbi_cpu_boot,
    .cpu_shutdown = sbi_cpu_shutdown,
};
