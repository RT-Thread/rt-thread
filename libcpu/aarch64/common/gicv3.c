/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 * 2014-04-03     Grissiom     many enhancements
 * 2018-11-22     Jesven       add rt_hw_ipi_send()
 *                             add rt_hw_ipi_handler_install()
 * 2022-03-08     GuEe-GUI     add BSP bind SPI CPU self support
 *                             add GICv3 AArch64 system register interface
 *                             modify arm_gic_redist_init() args
 *                             modify arm_gic_cpu_init() args
 *                             modify arm_gic_send_affinity_sgi() args
 *                             remove arm_gic_redist_address_set()
 *                             remove arm_gic_cpu_interface_address_set()
 *                             remove arm_gic_secondary_cpu_init()
 *                             remove get_main_cpu_affval()
 *                             remove arm_gic_cpumask_to_affval()
 */

#include <rthw.h>
#include <rtthread.h>

#if defined(BSP_USING_GIC) && defined(BSP_USING_GICV3)

#include <gicv3.h>
#include <cp15.h>

#include <board.h>

#ifndef ARM_SPI_BIND_CPU_ID
#define ARM_SPI_BIND_CPU_ID 0
#endif

#ifndef RT_USING_SMP
#define RT_CPUS_NR 1
extern int rt_hw_cpu_id(void);
#else
extern rt_uint64_t rt_cpu_mpidr_early[];
#endif /* RT_USING_SMP */

struct arm_gic
{
    rt_uint64_t offset;                     /* the first interrupt index in the vector table */
    rt_uint64_t redist_hw_base[RT_CPUS_NR]; /* the pointer of the gic redistributor */
    rt_uint64_t dist_hw_base;               /* the base address of the gic distributor */
    rt_uint64_t cpu_hw_base[RT_CPUS_NR];    /* the base address of the gic cpu interface */
};

/* 'ARM_GIC_MAX_NR' is the number of cores */
static struct arm_gic _gic_table[ARM_GIC_MAX_NR];
static unsigned int _gic_max_irq;

#define GET_GICV3_REG(reg, out) __asm__ volatile ("mrs %0, " reg:"=r"(out)::"memory");
#define SET_GICV3_REG(reg, in)  __asm__ volatile ("msr " reg ", %0"::"r"(in):"memory");

/* AArch64 System register interface to GICv3 */
#define ICC_IAR0_EL1    "S3_0_C12_C8_0"
#define ICC_IAR1_EL1    "S3_0_C12_C12_0"
#define ICC_EOIR0_EL1   "S3_0_C12_C8_1"
#define ICC_EOIR1_EL1   "S3_0_C12_C12_1"
#define ICC_HPPIR0_EL1  "S3_0_C12_C8_2"
#define ICC_HPPIR1_EL1  "S3_0_C12_C12_2"
#define ICC_BPR0_EL1    "S3_0_C12_C8_3"
#define ICC_BPR1_EL1    "S3_0_C12_C12_3"
#define ICC_DIR_EL1     "S3_0_C12_C11_1"
#define ICC_PMR_EL1     "S3_0_C4_C6_0"
#define ICC_RPR_EL1     "S3_0_C12_C11_3"
#define ICC_CTLR_EL1    "S3_0_C12_C12_4"
#define ICC_CTLR_EL3    "S3_6_C12_C12_4"
#define ICC_SRE_EL1     "S3_0_C12_C12_5"
#define ICC_SRE_EL2     "S3_4_C12_C9_5"
#define ICC_SRE_EL3     "S3_6_C12_C12_5"
#define ICC_IGRPEN0_EL1 "S3_0_C12_C12_6"
#define ICC_IGRPEN1_EL1 "S3_0_C12_C12_7"
#define ICC_IGRPEN1_EL3 "S3_6_C12_C12_7"
#define ICC_SGI0R_EL1   "S3_0_C12_C11_7"
#define ICC_SGI1R_EL1   "S3_0_C12_C11_5"
#define ICC_ASGI1R_EL1  "S3_0_C12_C11_6"

/* Macro to access the Distributor Control Register (GICD_CTLR) */
#define GICD_CTLR_RWP       (1 << 31)
#define GICD_CTLR_E1NWF     (1 << 7)
#define GICD_CTLR_DS        (1 << 6)
#define GICD_CTLR_ARE_NS    (1 << 5)
#define GICD_CTLR_ARE_S     (1 << 4)
#define GICD_CTLR_ENGRP1S   (1 << 2)
#define GICD_CTLR_ENGRP1NS  (1 << 1)
#define GICD_CTLR_ENGRP0    (1 << 0)

/* Macro to access the Redistributor Control Register (GICR_CTLR) */
#define GICR_CTLR_UWP       (1 << 31)
#define GICR_CTLR_DPG1S     (1 << 26)
#define GICR_CTLR_DPG1NS    (1 << 25)
#define GICR_CTLR_DPG0      (1 << 24)
#define GICR_CTLR_RWP       (1 << 3)
#define GICR_CTLR_IR        (1 << 2)
#define GICR_CTLR_CES       (1 << 1)
#define GICR_CTLR_EnableLPI (1 << 0)

/* Macro to access the Generic Interrupt Controller Interface (GICC) */
#define GIC_CPU_CTRL(hw_base)               HWREG32((hw_base) + 0x00U)
#define GIC_CPU_PRIMASK(hw_base)            HWREG32((hw_base) + 0x04U)
#define GIC_CPU_BINPOINT(hw_base)           HWREG32((hw_base) + 0x08U)
#define GIC_CPU_INTACK(hw_base)             HWREG32((hw_base) + 0x0cU)
#define GIC_CPU_EOI(hw_base)                HWREG32((hw_base) + 0x10U)
#define GIC_CPU_RUNNINGPRI(hw_base)         HWREG32((hw_base) + 0x14U)
#define GIC_CPU_HIGHPRI(hw_base)            HWREG32((hw_base) + 0x18U)
#define GIC_CPU_IIDR(hw_base)               HWREG32((hw_base) + 0xFCU)

/* Macro to access the Generic Interrupt Controller Distributor (GICD) */
#define GIC_DIST_CTRL(hw_base)              HWREG32((hw_base) + 0x000U)
#define GIC_DIST_TYPE(hw_base)              HWREG32((hw_base) + 0x004U)
#define GIC_DIST_IGROUP(hw_base, n)         HWREG32((hw_base) + 0x080U + ((n) / 32U) * 4U)
#define GIC_DIST_ENABLE_SET(hw_base, n)     HWREG32((hw_base) + 0x100U + ((n) / 32U) * 4U)
#define GIC_DIST_ENABLE_CLEAR(hw_base, n)   HWREG32((hw_base) + 0x180U + ((n) / 32U) * 4U)
#define GIC_DIST_PENDING_SET(hw_base, n)    HWREG32((hw_base) + 0x200U + ((n) / 32U) * 4U)
#define GIC_DIST_PENDING_CLEAR(hw_base, n)  HWREG32((hw_base) + 0x280U + ((n) / 32U) * 4U)
#define GIC_DIST_ACTIVE_SET(hw_base, n)     HWREG32((hw_base) + 0x300U + ((n) / 32U) * 4U)
#define GIC_DIST_ACTIVE_CLEAR(hw_base, n)   HWREG32((hw_base) + 0x380U + ((n) / 32U) * 4U)
#define GIC_DIST_PRI(hw_base, n)            HWREG32((hw_base) + 0x400U + ((n) / 4U) * 4U)
#define GIC_DIST_TARGET(hw_base, n)         HWREG32((hw_base) + 0x800U + ((n) / 4U) * 4U)
#define GIC_DIST_CONFIG(hw_base, n)         HWREG32((hw_base) + 0xc00U + ((n) / 16U) * 4U)
#define GIC_DIST_SOFTINT(hw_base)           HWREG32((hw_base) + 0xf00U)
#define GIC_DIST_CPENDSGI(hw_base, n)       HWREG32((hw_base) + 0xf10U + ((n) / 4U) * 4U)
#define GIC_DIST_SPENDSGI(hw_base, n)       HWREG32((hw_base) + 0xf20U + ((n) / 4U) * 4U)
#define GIC_DIST_ICPIDR2(hw_base)           HWREG32((hw_base) + 0xfe8U)
#define GIC_DIST_IROUTER(hw_base, n)        HWREG64((hw_base) + 0x6000U + (n) * 8U)

/* SGI base address is at 64K offset from Redistributor base address */
#define GIC_RSGI_OFFSET 0x10000

/* Macro to access the Generic Interrupt Controller Redistributor (GICR) */
#define GIC_RDIST_CTRL(hw_base)             HWREG32((hw_base) + 0x000U)
#define GIC_RDIST_IIDR(hw_base)             HWREG32((hw_base) + 0x004U)
#define GIC_RDIST_TYPER(hw_base)            HWREG64((hw_base) + 0x008U)
#define GIC_RDIST_TSTATUSR(hw_base)         HWREG32((hw_base) + 0x010U)
#define GIC_RDIST_WAKER(hw_base)            HWREG32((hw_base) + 0x014U)
#define GIC_RDIST_SETLPIR(hw_base)          HWREG32((hw_base) + 0x040U)
#define GIC_RDIST_CLRLPIR(hw_base)          HWREG32((hw_base) + 0x048U)
#define GIC_RDIST_PROPBASER(hw_base)        HWREG32((hw_base) + 0x070U)
#define GIC_RDIST_PENDBASER(hw_base)        HWREG32((hw_base) + 0x078U)
#define GIC_RDIST_INVLPIR(hw_base)          HWREG32((hw_base) + 0x0A0U)
#define GIC_RDIST_INVALLR(hw_base)          HWREG32((hw_base) + 0x0B0U)
#define GIC_RDIST_SYNCR(hw_base)            HWREG32((hw_base) + 0x0C0U)

#define GIC_RDISTSGI_IGROUPR0(hw_base, n)   HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x080U + (n) * 4U)
#define GIC_RDISTSGI_ISENABLER0(hw_base)    HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x100U)
#define GIC_RDISTSGI_ICENABLER0(hw_base)    HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x180U)
#define GIC_RDISTSGI_ISPENDR0(hw_base)      HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x200U)
#define GIC_RDISTSGI_ICPENDR0(hw_base)      HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x280U)
#define GIC_RDISTSGI_ISACTIVER0(hw_base)    HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x300U)
#define GIC_RDISTSGI_ICACTIVER0(hw_base)    HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x380U)
#define GIC_RDISTSGI_IPRIORITYR(hw_base, n) HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x400U + ((n) / 4U) * 4U)
#define GIC_RDISTSGI_ICFGR0(hw_base)        HWREG32((hw_base) + GIC_RSGI_OFFSET + 0xC00U)
#define GIC_RDISTSGI_ICFGR1(hw_base)        HWREG32((hw_base) + GIC_RSGI_OFFSET + 0xC04U)
#define GIC_RDISTSGI_IGRPMODR0(hw_base, n)  HWREG32((hw_base) + GIC_RSGI_OFFSET + 0xD00U + (n) * 4)
#define GIC_RDISTSGI_NSACR(hw_base)         HWREG32((hw_base) + GIC_RSGI_OFFSET + 0xE00U)

int arm_gic_get_active_irq(rt_uint64_t index)
{
    int irq;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    GET_GICV3_REG(ICC_IAR1_EL1, irq);

    irq = (irq & 0x1ffffff) + _gic_table[index].offset;
    return irq;
}

void arm_gic_ack(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    RT_ASSERT(irq >= 0);

    __DSB();
    SET_GICV3_REG(ICC_EOIR1_EL1, irq);
}

void arm_gic_mask(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1 << (irq % 32);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq < 32)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        GIC_RDISTSGI_ICENABLER0(_gic_table[index].redist_hw_base[cpu_id]) = mask;
    }
    else
    {
        GIC_DIST_ENABLE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

void arm_gic_umask(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1 << (irq % 32);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq < 32)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        GIC_RDISTSGI_ISENABLER0(_gic_table[index].redist_hw_base[cpu_id]) = mask;
    }
    else
    {
        GIC_DIST_ENABLE_SET(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

rt_uint64_t arm_gic_get_pending_irq(rt_uint64_t index, int irq)
{
    rt_uint64_t pend;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq >= 16)
    {
        pend = (GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32)) & 0x1;
    }
    else
    {
        /* INTID 0-15 Software Generated Interrupt */
        pend = (GIC_DIST_SPENDSGI(_gic_table[index].dist_hw_base, irq) >> ((irq % 4) * 8)) & 0xff;
        /* No CPU identification offered */
        if (pend != 0)
        {
            pend = 1;
        }
        else
        {
            pend = 0;
        }
    }

    return pend;
}

void arm_gic_set_pending_irq(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq >= 16)
    {
        GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) = 1 << (irq % 32);
    }
    else
    {
        /* INTID 0-15 Software Generated Interrupt */
        /* Forward the interrupt to the CPU interface that requested it */
        GIC_DIST_SOFTINT(_gic_table[index].dist_hw_base) = (irq | 0x02000000);
    }
}

void arm_gic_clear_pending_irq(rt_uint64_t index, int irq)
{
    rt_uint64_t mask;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq >= 16)
    {
        mask = 1 << (irq % 32);
        GIC_DIST_PENDING_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
    }
    else
    {
        mask = 1 << ((irq % 4) * 8);
        GIC_DIST_CPENDSGI(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

void arm_gic_set_configuration(rt_uint64_t index, int irq, rt_uint32_t config)
{
    rt_uint64_t icfgr;
    rt_uint64_t shift;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    icfgr = GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq);
    shift = (irq % 16) << 1;

    icfgr &= (~(3 << shift));
    icfgr |= (config << (shift + 1));

    GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) = icfgr;
}

rt_uint64_t arm_gic_get_configuration(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    return (GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) >> ((irq % 16) >> 1));
}

void arm_gic_clear_active(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1 << (irq % 32);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    GIC_DIST_ACTIVE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}

/* Set up the cpu mask for the specific interrupt */
void arm_gic_set_cpu(rt_uint64_t index, int irq, unsigned int cpumask)
{
    rt_uint64_t old_tgt;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    old_tgt = GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq);

    old_tgt &= ~(0x0ff << ((irq % 4) * 8));
    old_tgt |= cpumask << ((irq % 4) * 8);

    GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) = old_tgt;
}

rt_uint64_t arm_gic_get_target_cpu(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    return (GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) >> ((irq % 4) * 8)) & 0xff;
}

void arm_gic_set_priority(rt_uint64_t index, int irq, rt_uint64_t priority)
{
    rt_uint64_t mask;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq < 32)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        mask = GIC_RDISTSGI_IPRIORITYR(_gic_table[index].redist_hw_base[cpu_id], irq);
        mask &= ~(0xff << ((irq % 4) * 8));
        mask |= ((priority & 0xff) << ((irq % 4) * 8));
        GIC_RDISTSGI_IPRIORITYR(_gic_table[index].redist_hw_base[cpu_id], irq) = mask;
    }
    else
    {
        mask = GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq);
        mask &= ~(0xff << ((irq % 4) * 8));
        mask |= ((priority & 0xff) << ((irq % 4) * 8));
        GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

rt_uint64_t arm_gic_get_priority(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq < 32)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        return (GIC_RDISTSGI_IPRIORITYR(_gic_table[index].redist_hw_base[cpu_id], irq) >> ((irq % 4) * 8)) & 0xff;
    }
    else
    {
        return (GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) >> ((irq % 4) * 8)) & 0xff;
    }
}

void arm_gic_set_system_register_enable_mask(rt_uint64_t index, rt_uint64_t value)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    value &= 0xff;
    /* set priority mask */
    SET_GICV3_REG(ICC_SRE_EL1, value);
    __ISB();
}

rt_uint64_t arm_gic_get_system_register_enable_mask(rt_uint64_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    rt_uint64_t value;

    GET_GICV3_REG(ICC_SRE_EL1, value);
    return value;
}

void arm_gic_set_interface_prior_mask(rt_uint64_t index, rt_uint64_t priority)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    priority &= 0xff;
    /* set priority mask */
    SET_GICV3_REG(ICC_PMR_EL1, priority);
}

rt_uint64_t arm_gic_get_interface_prior_mask(rt_uint64_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    rt_uint64_t priority;

    GET_GICV3_REG(ICC_PMR_EL1, priority);
    return priority;
}

void arm_gic_set_binary_point(rt_uint64_t index, rt_uint64_t binary_point)
{
    index = index;
    binary_point &= 0x7;

    SET_GICV3_REG(ICC_BPR1_EL1, binary_point);
}

rt_uint64_t arm_gic_get_binary_point(rt_uint64_t index)
{
    rt_uint64_t binary_point;

    index = index;
    GET_GICV3_REG(ICC_BPR1_EL1, binary_point);
    return binary_point;
}

rt_uint64_t arm_gic_get_irq_status(rt_uint64_t index, int irq)
{
    rt_uint64_t pending, active;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    active = (GIC_DIST_ACTIVE_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32)) & 0x1;
    pending = (GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32)) & 0x1;

    return ((active << 1) | pending);
}

#ifdef RT_USING_SMP
void arm_gic_send_affinity_sgi(rt_uint64_t index, int irq, rt_uint32_t cpu_masks[], rt_uint64_t routing_mode)
{
    const int cpu_mask_cpu_max_nr = sizeof(cpu_masks[0]) * 8;
    rt_uint64_t int_id = (irq & 0xf) << 24;
    rt_uint64_t irm = routing_mode << 40; /* Interrupt Routing Mode */

    if (routing_mode == GICV3_ROUTED_TO_SPEC)
    {
        int cpu_id, cpu_mask_bit, i, cpu_masks_nr = RT_CPUS_NR / cpu_mask_cpu_max_nr;
        rt_uint16_t target_list;
        rt_uint64_t rs = 0; /* Range Selector */
        rt_uint64_t affinity_val, next_affinity_val;

        if (cpu_masks_nr * cpu_mask_cpu_max_nr != RT_CPUS_NR)
        {
            ++cpu_masks_nr;
        }

        for (i = cpu_id = 0; i < cpu_masks_nr;)
        {
            /* No cpu in this mask */
            if (cpu_masks[i] == 0)
            {
                ++i;
                cpu_id += cpu_mask_cpu_max_nr;
                continue;
            }

            /* Get last cpu affinity value */
            affinity_val = rt_cpu_mpidr_early[cpu_id] & 0xff00ffff00ULL;

            /* Read 16 cpus information */
            for (cpu_mask_bit = 0; cpu_mask_bit < 16; ++cpu_mask_bit, ++cpu_id)
            {
                /* MPIDR_EL1: aff3[39:32], aff2[23:16], aff1[15:8] */
                next_affinity_val = rt_cpu_mpidr_early[cpu_id] & 0xff00ffff00ULL;

                /* Affinity value is different, read end */
                if (affinity_val != next_affinity_val)
                {
                    break;
                }
            }

            /* Get all valid cpu mask */
            target_list = (0xffff >> (16 - cpu_mask_bit)) & cpu_masks[i];
            /* Clear read mask */
            cpu_masks[i] >>= cpu_mask_bit;
            /* ICC_SGI1R_EL1: aff3[55:48], aff2[39:32], aff1[23:16] */
            affinity_val <<= 8;

            __DSB();
            /* Interrupts routed to the PEs specified by Aff3.Aff2.Aff1.<target list>. */
            SET_GICV3_REG(ICC_SGI1R_EL1, affinity_val | (rs << 44) | irm | int_id | target_list);
            __ISB();

            /* Check if reset the range selector */
            rs = affinity_val != next_affinity_val ? 0 : rs + 1;
        }
    }
    else
    {
        __DSB();
        /* Interrupts routed to all PEs in the system, excluding "self". */
        SET_GICV3_REG(ICC_SGI1R_EL1, irm | int_id);
        __ISB();
    }
}
#endif /* RT_USING_SMP */

rt_uint64_t arm_gic_get_high_pending_irq(rt_uint64_t index)
{
    rt_uint64_t irq;
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    index = index;
    GET_GICV3_REG(ICC_HPPIR1_EL1, irq);

    return irq;
}

rt_uint64_t arm_gic_get_interface_id(rt_uint64_t index)
{
    rt_uint64_t ret = 0;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (_gic_table[index].cpu_hw_base != RT_NULL)
    {
        ret = GIC_CPU_IIDR(_gic_table[index].cpu_hw_base);
    }

    return ret;
}

void arm_gic_set_group(rt_uint64_t index, int irq, rt_uint64_t group)
{
    rt_uint64_t igroupr;
    rt_uint64_t shift;

    RT_ASSERT(index < ARM_GIC_MAX_NR);
    RT_ASSERT(group <= 1);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    igroupr = GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq);
    shift = (irq % 32);
    igroupr &= (~(1U << shift));
    igroupr |= ((group & 0x1U) << shift);

    GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq) = igroupr;
}

rt_uint64_t arm_gic_get_group(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    return (GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq) >> (irq % 32)) & 0x1UL;
}

static int arm_gicv3_wait_rwp(rt_uint64_t index, rt_uint64_t irq)
{
    rt_uint64_t rwp_bit;
    rt_uint64_t base;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (irq < 32)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        base = _gic_table[index].redist_hw_base[cpu_id];
        rwp_bit = GICR_CTLR_RWP;
    }
    else
    {
        base = _gic_table[index].dist_hw_base;
        rwp_bit = GICD_CTLR_RWP;
    }

    while (HWREG32(base) & rwp_bit)
    {
    }

    return 0;
}

int arm_gic_dist_init(rt_uint64_t index, rt_uint64_t dist_base, int irq_start)
{
    int i;
    unsigned int gic_type;
    rt_uint64_t main_cpu_affinity_val;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    _gic_table[index].dist_hw_base = dist_base;
    _gic_table[index].offset = irq_start;


    /* Find out how many interrupts are supported. */
    gic_type = GIC_DIST_TYPE(dist_base);
    _gic_max_irq = ((gic_type & 0x1f) + 1) * 32;

    /*
     * The GIC only supports up to 1020 interrupt sources.
     * Limit this to either the architected maximum, or the
     * platform maximum.
     */
    if (_gic_max_irq > 1020)
    {
        _gic_max_irq = 1020;
    }
    if (_gic_max_irq > ARM_GIC_NR_IRQS) /* the platform maximum interrupts */
    {
        _gic_max_irq = ARM_GIC_NR_IRQS;
    }

    GIC_DIST_CTRL(dist_base) = 0;
    /* Wait for register write pending */
    arm_gicv3_wait_rwp(0, 32);

    /* Set all global interrupts to be level triggered, active low. */
    for (i = 32; i < _gic_max_irq; i += 16)
    {
        GIC_DIST_CONFIG(dist_base, i) = 0;
    }

    arm_gicv3_wait_rwp(0, 32);

#ifdef RT_USING_SMP
    main_cpu_affinity_val = rt_cpu_mpidr_early[ARM_SPI_BIND_CPU_ID];
#else
    __asm__ volatile ("mrs %0, mpidr_el1":"=r"(main_cpu_affinity_val));
#endif

    /* aff3[39:32], aff2[23:16], aff1[15:8], aff0[7:0] */
    main_cpu_affinity_val &= 0xff00ffffffULL;

    /* Set all global interrupts to this CPU only. */
    for (i = 32; i < _gic_max_irq; i++)
    {
        GIC_DIST_IROUTER(dist_base, i) = main_cpu_affinity_val | (GICV3_ROUTED_TO_SPEC << 31);
    }

    arm_gicv3_wait_rwp(0, 32);

    /* Set priority on spi interrupts. */
    for (i = 32; i < _gic_max_irq; i += 4)
    {
        GIC_DIST_PRI(dist_base, i) = 0xa0a0a0a0;
    }

    arm_gicv3_wait_rwp(0, 32);
    /* Disable all interrupts. */
    for (i = 0; i < _gic_max_irq; i += 32)
    {
        GIC_DIST_PENDING_CLEAR(dist_base, i) = 0xffffffff;
        GIC_DIST_ENABLE_CLEAR(dist_base, i) = 0xffffffff;
    }

    arm_gicv3_wait_rwp(0, 32);
    /* All interrupts defaults to IGROUP1(IRQ). */
    for (i = 0; i < _gic_max_irq; i += 32)
    {
        GIC_DIST_IGROUP(dist_base, i) = 0xffffffff;
    }

    arm_gicv3_wait_rwp(0, 32);

    /*
     * The Distributor control register (GICD_CTLR) must be configured to enable the interrupt groups and to set the routing mode.
     * Enable Affinity routing (ARE bits) The ARE bits in GICD_CTLR control whether affinity routing is enabled.
     * If affinity routing is not enabled, GICv3 can be configured for legacy operation.
     * Whether affinity routing is enabled or not can be controlled separately for Secure and Non-secure state.
     * Enables GICD_CTLR contains separate enable bits for Group 0, Secure Group 1 and Non-secure Group 1:
     * GICD_CTLR.EnableGrp1S enables distribution of Secure Group 1 interrupts.
     * GICD_CTLR.EnableGrp1NS enables distribution of Non-secure Group 1 interrupts.
     * GICD_CTLR.EnableGrp0 enables distribution of Group 0 interrupts.
     */
    GIC_DIST_CTRL(dist_base) = GICD_CTLR_ARE_NS | GICD_CTLR_ENGRP1NS;

    return 0;
}

int arm_gic_redist_init(rt_uint64_t index, rt_uint64_t redist_base)
{
    int i;
    int cpu_id = rt_hw_cpu_id();
    static int master_cpu_id = -1;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (master_cpu_id < 0)
    {
        master_cpu_id = cpu_id;
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, &master_cpu_id, sizeof(master_cpu_id));
    }

    if (!_gic_table[index].redist_hw_base[master_cpu_id])
    {
        _gic_table[index].redist_hw_base[master_cpu_id] = redist_base;
    }
    redist_base = _gic_table[index].redist_hw_base[master_cpu_id];

    redist_base += cpu_id * (2 << 16);
    _gic_table[index].redist_hw_base[cpu_id] = redist_base;

    /* redistributor enable */
    GIC_RDIST_WAKER(redist_base) &= ~(1 << 1);
    while (GIC_RDIST_WAKER(redist_base) & (1 << 2))
    {
    }

    /* Disable all sgi and ppi interrupt */
    GIC_RDISTSGI_ICENABLER0(redist_base) = 0xffffffff;
    arm_gicv3_wait_rwp(0, 0);

    /* Clear all inetrrupt pending */
    GIC_RDISTSGI_ICPENDR0(redist_base) = 0xffffffff;

    /* the corresponding interrupt is Group 1 or Non-secure Group 1. */
    GIC_RDISTSGI_IGROUPR0(redist_base, 0) = 0xffffffff;
    GIC_RDISTSGI_IGRPMODR0(redist_base, 0) = 0xffffffff;

    /* Configure default priorities for SGI 0:15 and PPI 16:31. */
    for (i = 0; i < 32; i += 4)
    {
        GIC_RDISTSGI_IPRIORITYR(redist_base, i) = 0xa0a0a0a0U;
    }

    /* Trigger level for PPI interrupts*/
    GIC_RDISTSGI_ICFGR1(redist_base) = 0;
    return 0;
}

int arm_gic_cpu_init(rt_uint64_t index, rt_uint64_t cpu_base)
{
    rt_uint64_t value;
    int cpu_id = rt_hw_cpu_id();

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    _gic_table[index].cpu_hw_base[cpu_id] = cpu_base;

    value = arm_gic_get_system_register_enable_mask(index);
    value |= (1 << 0);
    arm_gic_set_system_register_enable_mask(index, value);
    SET_GICV3_REG(ICC_CTLR_EL1, 0);

    arm_gic_set_interface_prior_mask(index, 0xff);

    /* Enable group1 interrupt */
    value = 1;
    SET_GICV3_REG(ICC_IGRPEN1_EL1, value);

    arm_gic_set_binary_point(0, 0);

    /* ICC_BPR0_EL1 determines the preemption group for both Group 0 and Group 1 interrupts. */
    value  = 1;         /* ICC_BPR0_EL1 determines the preemption group for both Group 0 and Group 1 interrupts.*/
    value |= 1 << 18;   /* Targeted SGIs with affinity level 0 values of 0 - 255 are supported. */
    SET_GICV3_REG(ICC_CTLR_EL1, value);

    return 0;
}

void arm_gic_dump_type(rt_uint64_t index)
{
    unsigned int gic_type;

    gic_type = GIC_DIST_TYPE(_gic_table[index].dist_hw_base);
    rt_kprintf("GICv%d on %p, max IRQs: %d, %s security extension(%08x)\n",
               (GIC_DIST_ICPIDR2(_gic_table[index].dist_hw_base) >> 4) & 0xf,
               _gic_table[index].dist_hw_base,
               _gic_max_irq,
               gic_type & (1 << 10) ? "has" : "no",
               gic_type);
}

void arm_gic_dump(rt_uint64_t index)
{
    int i;
    unsigned int val;

    val = arm_gic_get_high_pending_irq(0);
    rt_kprintf("--- high pending priority: %d(%08x)\n", val, val);

    rt_kprintf("--- hw mask ---\n");
    for (i = 0; i < _gic_max_irq / 32; ++i)
    {
        rt_kprintf("0x%08x, ", GIC_DIST_ENABLE_SET(_gic_table[index].dist_hw_base, i * 32));
    }

    rt_kprintf("\b\b\n--- hw pending ---\n");
    for (i = 0; i < _gic_max_irq / 32; ++i)
    {
        rt_kprintf("0x%08x, ", GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, i * 32));
    }

    rt_kprintf("\b\b\n--- hw active ---\n");
    for (i = 0; i < _gic_max_irq / 32; ++i)
    {
        rt_kprintf("0x%08x, ", GIC_DIST_ACTIVE_SET(_gic_table[index].dist_hw_base, i * 32));
    }

    rt_kprintf("\b\b\n");
}

long gic_dump(void)
{
    arm_gic_dump_type(0);
    arm_gic_dump(0);

    return 0;
}
MSH_CMD_EXPORT(gic_dump, show gic status);

#endif /* defined(BSP_USING_GIC) && defined(BSP_USING_GICV3) */
