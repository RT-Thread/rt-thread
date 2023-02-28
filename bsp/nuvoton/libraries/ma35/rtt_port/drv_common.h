/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rtthread.h>
#include "NuMicro.h"
#include "interrupt.h"

#if !defined(USE_MA35D1_SUBM)

#include "gic.h"
#include "mmu.h"
#if defined(USE_MA35D1_AARCH32)
    #include "cp15.h"
#endif
#include "gtimer.h"

#define __REG32(x) (*((volatile unsigned int*)((rt_ubase_t)x)))

#define GIC_ACK_INTID_MASK  0x000003ff
#define ARM_GIC_NR_IRQS   256
#define MAX_HANDLERS      ARM_GIC_NR_IRQS
#define ARM_GIC_MAX_NR    1
#define GIC_IRQ_START     0

#define DDR_LIMIT_SIZE      0xC0000000u
#define UNCACHEABLE         0x40000000u

/* the basic constants needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GIC_DISTRIBUTOR_BASE;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return GIC_INTERFACE_BASE;
}

rt_inline rt_uint32_t nu_cpu_dcache_line_size(void)
{
    rt_uint32_t ctr = 0;
#if defined(USE_MA35D1_AARCH32)
    asm volatile("mrc p15, 0, %0, c0, c0, 1" : "=r"(ctr));
#elif defined(USE_MA35D1_AARCH64)
    asm volatile("mrs %0, ctr_el0" : "=r"(ctr));
#endif
    return 4 << ((ctr >> 16) & 0xF);
}
extern void rt_hw_cpu_dcache_clean(void *addr, int size);
extern void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, int size);
extern void rt_hw_cpu_dcache_invalidate(void *addr, int size);
#else
#define UNCACHEABLE        0
#endif

#define REGION_ADDR_SRAM0     0x24000000
#define REGION_ADDR_DDR       (0x80020000|UNCACHEABLE)
#define REGION_MAXSIZE_SRAM0  (128*1024)
#define REGION_MAXSIZE_DDR    (4*1024*1024-REGION_MAXSIZE_SRAM0)
#define REGION_MAXSIZE_LIMIT  (REGION_MAXSIZE_SRAM0+REGION_MAXSIZE_DDR)

#endif /* __DRV_COMMON_H__ */
