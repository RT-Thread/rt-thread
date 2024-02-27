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
#include "fparameters.h"
#include "fio.h"
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

#if defined(TARGET_ARMV8_AARCH64)

rt_inline rt_uint32_t FGicRedistrubutiorIterate_rt(void)
{
    rt_uint32_t redis_base = 0;
    rt_uint64_t mpidr_aff = 0;
    rt_uint32_t mpidr_aff_32 = 0;
    rt_uint32_t gicr_typer_aff = 0;

    __asm__ volatile ("mrs %0, mpidr_el1":"=r"(mpidr_aff));
    mpidr_aff_32 = (rt_uint32_t) (mpidr_aff & 0xfff);

    for(redis_base = GICV3_RD_BASE_ADDR; redis_base < GICV3_RD_BASE_ADDR + GICV3_RD_SIZE; redis_base += GICV3_RD_OFFSET)
    {
        #ifdef RT_USING_SMART
        rt_uint64_t temp= (rt_uint64_t)rt_ioremap((void*)redis_base,(2 << 16));
        #else
        rt_uint64_t temp= redis_base;
        #endif
        gicr_typer_aff = FtIn32(temp + 12);
        #ifdef RT_USING_SMART
        rt_iounmap((void*)temp);
        #endif
        if (mpidr_aff_32 == gicr_typer_aff)
        {
#if RT_CPUS_NR <= 2
            return redis_base;
#else
            return GICV3_RD_BASE_ADDR;
#endif
        }
    }

    return 0;
}
/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_redist_base(void)
{
    rt_uint32_t redis_base = 0;
    redis_base = FGicRedistrubutiorIterate_rt();
    return redis_base;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return 0U; /* unused in gicv3 */
}

#endif


int phytium_cpu_id_mapping(int cpu_id);



#endif // !
