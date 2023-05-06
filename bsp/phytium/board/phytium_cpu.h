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

#define ARM_GIC_MAX_NR 1

#if defined(TARGET_FT2000_4) || defined(TARGET_D2000)
#define MAX_HANDLERS 160
#endif

#if defined(TARGET_E2000)
#define MAX_HANDLERS 270
#define ARM_GIC_CPU_NUM 4
#endif

#define GIC_IRQ_START 0
#define GIC_ACK_INTID_MASK 0x000003ff


rt_uint64_t get_main_cpu_affval(void);

rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GICV3_DISTRIBUTOR_BASE_ADDR;
}

#if defined(TARGET_ARMV8_AARCH64)

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_redist_base(void)
{
    extern int phytium_cpu_id(void);

#if RT_CPUS_NR <= 2
    s32 cpu_offset = 0;
#if defined(FT_GIC_REDISTRUBUTIOR_OFFSET)
    cpu_offset = FT_GIC_REDISTRUBUTIOR_OFFSET ;
#endif

#if defined(TARGET_E2000Q)
    u32 cpu_id = 0;
    cpu_id = phytium_cpu_id();

    switch (cpu_id)
    {
    case 0:
    case 1:
        cpu_offset = 2;
        break;
    case 2:
    case 3:
        cpu_offset = -2;
    default:
        break;
    }

    rt_kprintf("cpu_id is %d \r\n",cpu_id);
#endif
    rt_kprintf("offset  is %d\n", cpu_offset);

    return (GICV3_RD_BASE_ADDR + (cpu_offset) * GICV3_RD_OFFSET);
#else
    return (GICV3_RD_BASE_ADDR);
#endif
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return 0U; /* unused in gicv3 */
}

#endif


int phytium_cpu_id_mapping(int cpu_id);



#endif // !
