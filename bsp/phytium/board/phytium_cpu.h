/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 *
 */

#ifndef __PHYTIUM_CPU_H__
#define __PHYTIUM_CPU_H__

#include <rthw.h>
#include <rtthread.h>
#include <gicv3.h>
#include "fparameters.h"
#include "fio.h"
#include "faarch.h"

#ifdef RT_USING_SMART
#include"ioremap.h"
#endif

#define ARM_GIC_MAX_NR 1

#if defined(TARGET_FT2000_4) || defined(TARGET_D2000)
    #define MAX_HANDLERS 160
#endif

#if defined(TARGET_E2000)
    #define MAX_HANDLERS 270
#endif

#define GIC_IRQ_START 0
#define GIC_ACK_INTID_MASK 0x000003ff


rt_uint64_t get_main_cpu_affval(void);

rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GICV3_DISTRIBUTOR_BASE_ADDR;
}

/* the basic constants and interfaces needed by gic */
rt_inline uintptr_t platform_get_gic_redist_base(void)
{
    uintptr_t redis_base, mpidr_aff, gicr_typer_aff;
    mpidr_aff = (uintptr_t)(GetAffinity() & 0xfff);

    for (redis_base = GICV3_RD_BASE_ADDR; redis_base < GICV3_RD_BASE_ADDR + GICV3_RD_SIZE; redis_base += GICV3_RD_OFFSET)
    {
#ifdef RT_USING_SMART
        uintptr_t redis_base_virtual = (uintptr_t)rt_ioremap((void *)redis_base, GICV3_RD_OFFSET);
        if (redis_base_virtual == 0)
        {
            continue;
        }
#if defined(TARGET_ARMV8_AARCH64)
        gicr_typer_aff = GIC_RDIST_TYPER(redis_base_virtual) >> 32;
#else
        gicr_typer_aff = GIC_RDIST_TYPER(redis_base_virtual + 0x4);
#endif
        if (mpidr_aff == gicr_typer_aff)
        {
            return redis_base_virtual;
        }
        else
        {
            rt_iounmap(redis_base_virtual);
        }
#else
#if defined(TARGET_ARMV8_AARCH64)
        gicr_typer_aff = GIC_RDIST_TYPER(redis_base) >> 32;
#else
        gicr_typer_aff = GIC_RDIST_TYPER(redis_base + 0x4);
#endif
        if (mpidr_aff == gicr_typer_aff)
        {
            return redis_base;
        }
#endif
    }

    return 0;
}


#if defined(TARGET_ARMV8_AARCH64)

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return 0; /* unused in gicv3 */
}

#endif


int phytium_cpu_id_mapping(int cpu_id);

#endif // !
