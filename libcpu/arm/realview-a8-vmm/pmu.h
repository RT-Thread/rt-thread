/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __PMU_H__
#define __PMU_H__

#include "board.h"

/* Number of counters */
#define ARM_PMU_CNTER_NR 4

enum rt_hw_pmu_event_type {
    ARM_PMU_EVENT_PMNC_SW_INCR      = 0x00,
    ARM_PMU_EVENT_L1_ICACHE_REFILL  = 0x01,
    ARM_PMU_EVENT_ITLB_REFILL       = 0x02,
    ARM_PMU_EVENT_L1_DCACHE_REFILL  = 0x03,
    ARM_PMU_EVENT_L1_DCACHE_ACCESS  = 0x04,
    ARM_PMU_EVENT_DTLB_REFILL       = 0x05,
    ARM_PMU_EVENT_MEM_READ          = 0x06,
    ARM_PMU_EVENT_MEM_WRITE         = 0x07,
    ARM_PMU_EVENT_INSTR_EXECUTED    = 0x08,
    ARM_PMU_EVENT_EXC_TAKEN         = 0x09,
    ARM_PMU_EVENT_EXC_EXECUTED      = 0x0A,
    ARM_PMU_EVENT_CID_WRITE         = 0x0B,
};

/* Enable bit */
#define ARM_PMU_PMCR_E   (0x01 << 0)
/* Event counter reset */
#define ARM_PMU_PMCR_P   (0x01 << 1)
/* Cycle counter reset */
#define ARM_PMU_PMCR_C   (0x01 << 2)
/* Cycle counter divider */
#define ARM_PMU_PMCR_D   (0x01 << 3)

#ifdef __GNUC__
rt_inline void rt_hw_pmu_enable_cnt(int divide64)
{
    unsigned long pmcr;
    unsigned long pmcntenset;

    asm volatile ("mrc p15, 0, %0, c9, c12, 0" : "=r"(pmcr));
    pmcr |= ARM_PMU_PMCR_E | ARM_PMU_PMCR_P | ARM_PMU_PMCR_C;
    if (divide64)
        pmcr |= ARM_PMU_PMCR_D;
    else
        pmcr &= ~ARM_PMU_PMCR_D;
    asm volatile ("mcr p15, 0, %0, c9, c12, 0" :: "r"(pmcr));

    /* enable all the counters */
    pmcntenset = ~0;
    asm volatile ("mcr p15, 0, %0, c9, c12, 1" :: "r"(pmcntenset));
    /* clear overflows(just in case) */
    asm volatile ("mcr p15, 0, %0, c9, c12, 3" :: "r"(pmcntenset));
}

rt_inline unsigned long rt_hw_pmu_get_control(void)
{
    unsigned long pmcr;
    asm ("mrc p15, 0, %0, c9, c12, 0" : "=r"(pmcr));
    return pmcr;
}

rt_inline unsigned long rt_hw_pmu_get_ceid(void)
{
    unsigned long reg;
    /* only PMCEID0 is supported, PMCEID1 is RAZ. */
    asm ("mrc p15, 0, %0, c9, c12, 6" : "=r"(reg));
    return reg;
}

rt_inline unsigned long rt_hw_pmu_get_cnten(void)
{
    unsigned long pmcnt;
    asm ("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcnt));
    return pmcnt;
}

rt_inline void rt_hw_pmu_reset_cycle(void)
{
    unsigned long pmcr;

    asm volatile ("mrc p15, 0, %0, c9, c12, 0" : "=r"(pmcr));
    pmcr |= ARM_PMU_PMCR_C;
    asm volatile ("mcr p15, 0, %0, c9, c12, 0" :: "r"(pmcr));
    asm volatile ("isb");
}

rt_inline void rt_hw_pmu_reset_event(void)
{
    unsigned long pmcr;

    asm volatile ("mrc p15, 0, %0, c9, c12, 0" : "=r"(pmcr));
    pmcr |= ARM_PMU_PMCR_P;
    asm volatile ("mcr p15, 0, %0, c9, c12, 0" :: "r"(pmcr));
    asm volatile ("isb");
}

rt_inline unsigned long rt_hw_pmu_get_cycle(void)
{
    unsigned long cyc;
    asm volatile ("isb");
    asm volatile ("mrc  p15, 0, %0, c9, c13, 0" : "=r"(cyc));
    return cyc;
}

rt_inline void rt_hw_pmu_select_counter(int idx)
{
    RT_ASSERT(idx < ARM_PMU_CNTER_NR);

    asm volatile ("mcr p15, 0, %0, c9, c12, 5" : : "r"(idx));
    /* Linux add an isb here, don't know why here. */
    asm volatile ("isb");
}

rt_inline void rt_hw_pmu_select_event(int idx,
                                      enum rt_hw_pmu_event_type eve)
{
    RT_ASSERT(idx < ARM_PMU_CNTER_NR);

    rt_hw_pmu_select_counter(idx);
    asm volatile ("mcr p15, 0, %0, c9, c13, 1" : : "r"(eve));
}

rt_inline unsigned long rt_hw_pmu_read_counter(int idx)
{
    unsigned long reg;

    rt_hw_pmu_select_counter(idx);
    asm volatile ("isb");
    asm volatile ("mrc p15, 0, %0, c9, c13, 2" : "=r"(reg));
    return reg;
}

rt_inline unsigned long rt_hw_pmu_get_ovsr(void)
{
    unsigned long reg;
    asm volatile ("isb");
    asm ("mrc  p15, 0, %0, c9, c12, 3" : "=r"(reg));
    return reg;
}

rt_inline void rt_hw_pmu_clear_ovsr(unsigned long reg)
{
    asm ("mcr  p15, 0, %0, c9, c12, 3" : : "r"(reg));
    asm volatile ("isb");
}

#endif

void rt_hw_pmu_dump_feature(void);

#endif /* end of include guard: __PMU_H__ */

