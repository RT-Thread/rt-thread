/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <rthw.h>

#include <cpu.h>

rt_uint8_t riscv_spinwait_table = 0;

static int spinwait_cpu_boot(rt_uint32_t cpuid, rt_uint64_t entry)
{
    rt_hw_barrier();

    HWREG8(&riscv_spinwait_table) = RT_UINT8_MAX;
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, &riscv_spinwait_table, sizeof(riscv_spinwait_table));

    return 0;
}

struct cpu_ops_t cpu_spinwait_ops =
{
    .method = "spinwait",
    .cpu_boot = spinwait_cpu_boot,
};
