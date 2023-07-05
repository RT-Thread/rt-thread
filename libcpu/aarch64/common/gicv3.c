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
#include <rtatomic.h>
#include <cache.h>
#include <mm_aspace.h>
#include <ioremap.h>

#define DBG_LEVEL   DBG_ERROR
#include "rtdbg.h"

#ifndef ARM_SPI_BIND_CPU_ID
#define ARM_SPI_BIND_CPU_ID 0
#endif

#if !defined(RT_USING_SMP) && !defined(RT_USING_AMP)
#define RT_CPUS_NR 1
#else
extern rt_uint64_t rt_cpu_mpidr_early[];
#endif /* RT_USING_SMP */

struct its_cmd_block
{
    rt_uint64_t raw_cmd[4];
};

struct gicv3_its_data
{
    rt_uint64_t base_pa;
    rt_uint64_t base_va;
    struct its_cmd_block *cmd_base;
    struct its_cmd_block *cmd_write;
    rt_bool_t dev_table_is_indirect;
    rt_uint64_t *indirect_dev_lvl1_table;
    rt_size_t indirect_dev_lvl1_width;
    rt_size_t indirect_dev_lvl2_width;
    rt_size_t indirect_dev_page_size;
    rt_size_t cmd_queue_size;
    rt_uint64_t rdbase[ARM_GIC_CPU_NUM];
    rt_uint64_t redist_base[ARM_GIC_CPU_NUM];
};

struct arm_gic
{
    rt_uint64_t offset;                          /* the first interrupt index in the vector table */
    rt_uint64_t dist_hw_base;                    /* the base address of the gic distributor */
    rt_uint64_t cpu_hw_base[ARM_GIC_CPU_NUM];    /* the base address of the gic cpu interface */
    rt_uint64_t redist_hw_base[ARM_GIC_CPU_NUM]; /* the pointer of the gic redistributor */
    rt_bool_t lpi_init_flag;
    rt_uint64_t gicr_propbaser_base;
    rt_uint64_t msi_address;
    struct gicv3_its_data its_config;            /* the base address of the its descriptions */
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

/* GITS_CTLR */
#define GITS_CTLR_Enabled   (1 << 0)
#define GITS_CTLR_Quiescent (1 << 31)

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
#define GIC_DIST_IIDR(hw_base)              HWREG32((hw_base) + 0x008U)
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
#define GIC_RDIST_SETLPIR_ADDR(hw_base)     ((hw_base) + 0x040U)
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

/* ITS registers */
#define GITS_CTLR(hw_base)                  HWREG32((hw_base) + 0x0000)
#define GITS_IIDR(hw_base)                  HWREG32((hw_base) + 0x0004)
#define GITS_TYPER(hw_base)                 HWREG64((hw_base) + 0x0008)
#define GITS_FCTLR(hw_base)                 HWREG32((hw_base) + 0x0020)
#define GITS_CBASER(hw_base)                HWREG64((hw_base) + 0x0080)
#define GITS_CWRITER(hw_base)               HWREG64((hw_base) + 0x0088)
#define GITS_CREADR(hw_base)                HWREG64((hw_base) + 0x0090)
#define GITS_BASER(hw_base, n)              HWREG64((hw_base) + 0x0100 + ((n) * 8))
#define GITS_TRANSLATER_ADDR(hw_base)       ((hw_base) + 0x10040)

static void lpi_init(rt_uint64_t index);
static void gicv3_lpi_mask(rt_uint64_t index, rt_uint32_t irq);
static void gicv3_lpi_umask(rt_uint64_t index, rt_uint32_t irq);
static rt_uint64_t gicv3_lpi_get_priority(rt_uint64_t index, rt_uint32_t irq);
static void gicv3_lpi_set_priority(rt_uint64_t index, rt_uint32_t irq, rt_uint64_t priority);

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

    if (irq >= GIC_LPI_INTID_START)
    {
        gicv3_lpi_mask(index, irq);
        return;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        gicv3_lpi_umask(index, irq);
        return;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return -RT_ERROR;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return -RT_ERROR;
    }

    return (GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) >> ((irq % 16) >> 1));
}

void arm_gic_clear_active(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1 << (irq % 32);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq >= GIC_LPI_INTID_START)
    {
        return;
    }

    GIC_DIST_ACTIVE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}

void arm_gic_set_router_cpu(rt_uint64_t index, int irq, rt_uint64_t aff)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (irq >= GIC_LPI_INTID_START)
    {
        return;
    }

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 32);

    GIC_DIST_IROUTER(_gic_table[index].dist_hw_base, irq) = aff & 0xff00ffffffULL;
}

rt_uint64_t arm_gic_get_router_cpu(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 32);

    if (irq >= GIC_LPI_INTID_START)
    {
        return -RT_ERROR;
    }

    return GIC_DIST_IROUTER(_gic_table[index].dist_hw_base, irq);
}

/* Set up the cpu mask for the specific interrupt */
void arm_gic_set_cpu(rt_uint64_t index, int irq, unsigned int cpumask)
{
    rt_uint64_t old_tgt;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq >= GIC_LPI_INTID_START)
    {
        return;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return -RT_ERROR;
    }

    return (GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) >> ((irq % 4) * 8)) & 0xff;
}

void arm_gic_set_priority(rt_uint64_t index, int irq, rt_uint64_t priority)
{
    rt_uint64_t mask;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0);

    if (irq >= GIC_LPI_INTID_START)
    {
        gicv3_lpi_set_priority(index, (rt_uint32_t) irq, priority);
        return;
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return gicv3_lpi_get_priority(index, (rt_uint32_t) irq);
    }

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

    if (irq >= GIC_LPI_INTID_START)
    {
        return -RT_ERROR;
    }

    active = (GIC_DIST_ACTIVE_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32)) & 0x1;
    pending = (GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32)) & 0x1;

    return ((active << 1) | pending);
}

#if defined(RT_USING_SMP) || defined(RT_USING_AMP)
struct gicv3_sgi_aff
{
    rt_uint64_t aff;
    rt_uint32_t cpu_mask[(RT_CPUS_NR + 31) >> 5];
    rt_uint16_t target_list;
};

static struct gicv3_sgi_aff sgi_aff_table[RT_CPUS_NR];
static rt_uint64_t sgi_aff_table_num;
static void sgi_aff_add_table(rt_uint64_t aff, rt_uint64_t cpu_index)
{
    rt_uint64_t i;

    for (i = 0; i < sgi_aff_table_num; i++)
    {
        if (sgi_aff_table[i].aff == aff)
        {
            sgi_aff_table[i].cpu_mask[cpu_index >> 5] |= (1 << (cpu_index & 0x1F));
            return;
        }
    }

    sgi_aff_table[sgi_aff_table_num].aff = aff;
    sgi_aff_table[sgi_aff_table_num].cpu_mask[cpu_index >> 5] |= (1 << (cpu_index & 0x1F));
    sgi_aff_table_num++;
}

static rt_uint64_t gicv3_sgi_init(void)
{
    rt_uint64_t i, icc_sgi1r_value;

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        icc_sgi1r_value =  (rt_uint64_t)((rt_cpu_mpidr_early[i] >> 8)  & 0xFF) << 16;
        icc_sgi1r_value |= (rt_uint64_t)((rt_cpu_mpidr_early[i] >> 16) & 0xFF) << 32;
        icc_sgi1r_value |= (rt_uint64_t)((rt_cpu_mpidr_early[i] >> 32) & 0xFF) << 48;
        icc_sgi1r_value |= (rt_uint64_t)((rt_cpu_mpidr_early[i] >> 4)  & 0xF)  << 44;
        sgi_aff_add_table(icc_sgi1r_value, i);
    }

    return (RT_CPUS_NR + 31) >> 5;
}

rt_inline void gicv3_sgi_send(rt_uint64_t int_id)
{
    rt_uint64_t i;
    for (i = 0; i < sgi_aff_table_num; i++)
    {
        if (sgi_aff_table[i].target_list)
        {
            __DSB();
            /* Interrupts routed to the PEs specified by Aff3.Aff2.Aff1.<target list>. */
            SET_GICV3_REG(ICC_SGI1R_EL1, sgi_aff_table[i].aff | int_id | sgi_aff_table[i].target_list);
            __ISB();
            sgi_aff_table[i].target_list = 0;
        }
    }
}

rt_inline void gicv3_sgi_target_list_set(rt_uint64_t array, rt_uint32_t cpu_mask)
{
    rt_uint64_t i, value;

    for (i = 0; i < sgi_aff_table_num; i++)
    {
        if (sgi_aff_table[i].cpu_mask[array] & cpu_mask)
        {
            while (cpu_mask)
            {
                value = __builtin_ctzl(cpu_mask);
                cpu_mask &= ~(1 << value);
                sgi_aff_table[i].target_list |= 1 << (rt_cpu_mpidr_early[(array << 5) | value] & 0xF);
            }
        }
    }
}

void arm_gic_send_affinity_sgi(rt_uint64_t index, int irq, rt_uint32_t cpu_masks[], rt_uint64_t routing_mode)
{
    rt_uint64_t i;
    rt_uint64_t int_id = (irq & 0xf) << 24;
    static rt_uint64_t masks_nrs = 0;

    if (routing_mode == GICV3_ROUTED_TO_SPEC)
    {
        if (!masks_nrs)
        {
            masks_nrs = gicv3_sgi_init();
        }

        for (i = 0; i < masks_nrs; i++)
        {
            if (cpu_masks[i] == 0)
            {
                continue;
            }

            gicv3_sgi_target_list_set(i, cpu_masks[i]);
        }

        gicv3_sgi_send(int_id);
    }
    else
    {
        __DSB();
        /* Interrupts routed to all PEs in the system, excluding "self". */
        SET_GICV3_REG(ICC_SGI1R_EL1, (0x10000000000ULL) | int_id);
        __ISB();
    }
}
#endif /* defined(RT_USING_SMP) || defined(RT_USING_AMP) */

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

    RT_UNUSED(i);
    RT_UNUSED(main_cpu_affinity_val);
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

#ifndef RT_AMP_SLAVE

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

#endif /* RT_AMP_SLAVE */
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
        master_cpu_id = 0;
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

    lpi_init(index);

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


/* LPI and ITS */
#define ITS_CMD_QUEUE_SIZE          1024 * 64
#define ITS_CMD_QUEUE_NR_ENTRIES    (ITS_CMD_QUEUE_SIZE / sizeof(struct its_cmd_block))

#define GITS_BASER_TYPE_NONE        0
#define GITS_BASER_TYPE_DEVICE      1
#define GITS_BASER_TYPE_COLLECTION  4

/* cmd */
#define GITS_CMD_ID_MOVI            0x01
#define GITS_CMD_ID_INT             0x03
#define GITS_CMD_ID_CLEAR           0x04
#define GITS_CMD_ID_SYNC            0x05
#define GITS_CMD_ID_MAPD            0x08
#define GITS_CMD_ID_MAPC            0x09
#define GITS_CMD_ID_MAPTI           0x0a
#define GITS_CMD_ID_MAPI            0x0b
#define GITS_CMD_ID_INV             0x0c
#define GITS_CMD_ID_INVALL          0x0d
#define GITS_CMD_ID_MOVALL          0x0e
#define GITS_CMD_ID_DISCARD         0x0f

#define GITS_CMD_ID_OFFSET          0
#define GITS_CMD_ID_SHIFT           0
#define GITS_CMD_ID_MASK            0xffUL

#define GITS_CMD_DEVICEID_OFFSET    0
#define GITS_CMD_DEVICEID_SHIFT     32
#define GITS_CMD_DEVICEID_MASK      0xffffffffUL

#define GITS_CMD_SIZE_OFFSET        1
#define GITS_CMD_SIZE_SHIFT         0
#define GITS_CMD_SIZE_MASK          0x1fUL

#define GITS_CMD_EVENTID_OFFSET     1
#define GITS_CMD_EVENTID_SHIFT      0
#define GITS_CMD_EVENTID_MASK       0xffffffffUL

#define GITS_CMD_PINTID_OFFSET      1
#define GITS_CMD_PINTID_SHIFT       32
#define GITS_CMD_PINTID_MASK        0xffffffffUL

#define GITS_CMD_ICID_OFFSET        2
#define GITS_CMD_ICID_SHIFT         0
#define GITS_CMD_ICID_MASK          0xffffUL

#define GITS_CMD_ITTADDR_OFFSET     2
#define GITS_CMD_ITTADDR_SHIFT      8
#define GITS_CMD_ITTADDR_MASK       0xffffffffffUL
#define GITS_CMD_ITTADDR_ALIGN      GITS_CMD_ITTADDR_SHIFT
#define GITS_CMD_ITTADDR_ALIGN_SZ   (BIT(0) << GITS_CMD_ITTADDR_ALIGN)

#define GITS_CMD_RDBASE_OFFSET      2
#define GITS_CMD_RDBASE_SHIFT       16
#define GITS_CMD_RDBASE_MASK        0xffffffffUL
#define GITS_CMD_RDBASE_ALIGN       GITS_CMD_RDBASE_SHIFT

#define GITS_CMD_VALID_OFFSET       2
#define GITS_CMD_VALID_SHIFT        63
#define GITS_CMD_VALID_MASK         0x1UL

/* Cache and Share ability for ITS & Redistributor LPI state tables */
#define GIC_BASER_CACHE_NGNRNE      0x0UL /* Device-nGnRnE */
#define GIC_BASER_CACHE_INNERLIKE   0x0UL /* Same as Inner Cacheability. */
#define GIC_BASER_CACHE_NCACHEABLE  0x1UL /* Non-cacheable */
#define GIC_BASER_CACHE_RAWT        0x2UL /* Cacheable R-allocate, W-through */
#define GIC_BASER_CACHE_RAWB        0x3UL /* Cacheable R-allocate, W-back */
#define GIC_BASER_CACHE_WAWT        0x4UL /* Cacheable W-allocate, W-through */
#define GIC_BASER_CACHE_WAWB        0x5UL /* Cacheable W-allocate, W-back */
#define GIC_BASER_CACHE_RAWAWT      0x6UL /* Cacheable R-allocate, W-allocate, W-through */
#define GIC_BASER_CACHE_RAWAWB      0x7UL /* Cacheable R-allocate, W-allocate, W-back */
#define GIC_BASER_SHARE_NO          0x0UL /* Non-shareable */
#define GIC_BASER_SHARE_INNER       0x1UL /* Inner Shareable */
#define GIC_BASER_SHARE_OUTER       0x2UL /* Outer Shareable */

/* ITS TYPER register */
#define GITS_TYPER_PHY_SHIFT              0
#define GITS_TYPER_PHY_MASK               0x1UL
#define GITS_TYPER_VIRT_SHIFT             1
#define GITS_TYPER_VIRT_MASK              0x1UL
#define GITS_TYPER_ITT_ENTRY_SIZE_SHIFT   4
#define GITS_TYPER_ITT_ENTRY_SIZE_MASK    0xfUL
#define GITS_TYPER_IDBITS_SHIFT           8
#define GITS_TYPER_IDBITS_MASK            0x1fUL
#define GITS_TYPER_DEVBITS_SHIFT          13
#define GITS_TYPER_DEVBITS_MASK           0x1fUL
#define GITS_TYPER_SEIS_SHIFT             18
#define GITS_TYPER_SEIS_MASK              0x1UL
#define GITS_TYPER_PTA_SHIFT              19
#define GITS_TYPER_PTA_MASK               0x1UL
#define GITS_TYPER_HCC_SHIFT              24
#define GITS_TYPER_HCC_MASK               0xffUL
#define GITS_TYPER_CIDBITS_SHIFT          32
#define GITS_TYPER_CIDBITS_MASK           0xfUL
#define GITS_TYPER_CIL_SHIFT              36
#define GITS_TYPER_CIL_MASK               0x1UL

/* ITS CBASER register */
#define GITS_CBASER_SIZE_SHIFT            0
#define GITS_CBASER_SIZE_MASK             0xffUL
#define GITS_CBASER_SHAREABILITY_SHIFT    10
#define GITS_CBASER_SHAREABILITY_MASK     0x3UL
#define GITS_CBASER_ADDR_SHIFT            12
#define GITS_CBASER_ADDR_MASK             0xfffffffffUL
#define GITS_CBASER_OUTER_CACHE_SHIFT     53
#define GITS_CBASER_OUTER_CACHE_MASK      0x7UL
#define GITS_CBASER_INNER_CACHE_SHIFT     59
#define GITS_CBASER_INNER_CACHE_MASK      0x7UL
#define GITS_CBASER_VALID_SHIFT           63
#define GITS_CBASER_VALID_MASK            0x1UL

/* ITS BASER<n> register */
#define GITS_BASER_SIZE_SHIFT             0
#define GITS_BASER_SIZE_MASK              0xffUL
#define GITS_BASER_PAGE_SIZE_SHIFT        8
#define GITS_BASER_PAGE_SIZE_MASK         0x3UL
#define GITS_BASER_PAGE_SIZE_4K           0
#define GITS_BASER_PAGE_SIZE_16K          1
#define GITS_BASER_PAGE_SIZE_64K          2
#define GITS_BASER_SHAREABILITY_SHIFT     10
#define GITS_BASER_SHAREABILITY_MASK      0x3UL
#define GITS_BASER_ADDR_SHIFT             12
#define GITS_BASER_ADDR_MASK              0xfffffffff
#define GITS_BASER_ENTRY_SIZE_SHIFT       48
#define GITS_BASER_ENTRY_SIZE_MASK        0x1fUL
#define GITS_BASER_OUTER_CACHE_SHIFT      53
#define GITS_BASER_OUTER_CACHE_MASK       0x7UL
#define GITS_BASER_TYPE_SHIFT             56
#define GITS_BASER_TYPE_MASK              0x7UL
#define GITS_BASER_INNER_CACHE_SHIFT      59
#define GITS_BASER_INNER_CACHE_MASK       0x7UL
#define GITS_BASER_INDIRECT_SHIFT         62
#define GITS_BASER_INDIRECT_MASK          0x1UL
#define GITS_BASER_VALID_SHIFT            63
#define GITS_BASER_VALID_MASK             0x1UL

#define MASK(__basename)                (__basename##_MASK << __basename##_SHIFT)
#define MASK_SET(__val, __basename)     (((__val) & __basename##_MASK) << __basename##_SHIFT)
#define MASK_GET(__reg, __basename)     (((__reg) >> __basename##_SHIFT) & __basename##_MASK)

/* Temporarily do not make its affinity, only use Collection 0 */
#define ICID_NO 0

rt_inline rt_size_t fls_z(rt_uint32_t x)
{
    rt_uint32_t bits = sizeof(x) * 8;
    rt_uint32_t cmp = 1 << (bits - 1);

    while (bits) {
        if (x & cmp) {
            return bits;
        }
        cmp >>= 1;
        bits--;
    }

    return 0;
}

static rt_err_t its_force_quiescent(struct gicv3_its_data *its_data)
{
    rt_uint32_t reg, count = 500;
    rt_uint64_t its_base =  its_data->base_va;

    reg = GITS_CTLR(its_base);
    if (reg & GITS_CTLR_Enabled)
    {
        reg &= ~GITS_CTLR_Enabled;
        GITS_CTLR(its_base) = reg;
    }

    while (!(reg & GITS_CTLR_Quiescent))
    {
        count--;
        if (!count)
        {
            return -RT_ETIMEOUT;
        }

        rt_hw_us_delay(1000);
        reg = GITS_CTLR(its_base);
    }

    return RT_EOK;
}

/* Probe the BASER(i) to get the largest supported page size */
static rt_size_t its_probe_baser_page_size(struct gicv3_its_data *its_data, rt_uint32_t i)
{
    rt_uint64_t its_base =  its_data->base_va;
    rt_size_t page_size = GITS_BASER_PAGE_SIZE_64K;

    while (page_size > GITS_BASER_PAGE_SIZE_4K)
    {
        rt_uint64_t reg = GITS_BASER(its_base, i);

        reg &= ~MASK(GITS_BASER_PAGE_SIZE);
        reg |= MASK_SET(page_size, GITS_BASER_PAGE_SIZE);

        GITS_BASER(its_base, i) = reg;

        reg = GITS_BASER(its_base, i);

        if (MASK_GET(reg, GITS_BASER_PAGE_SIZE) == page_size)
        {
            break;
        }

        switch (page_size)
        {
        case GITS_BASER_PAGE_SIZE_64K:
            page_size = GITS_BASER_PAGE_SIZE_16K;
            break;
        default:
            page_size = GITS_BASER_PAGE_SIZE_4K;
            break;
        }
    }

    switch (page_size)
    {
    case GITS_BASER_PAGE_SIZE_64K:
        return 1024 * 64;
    case GITS_BASER_PAGE_SIZE_16K:
        return 1024 * 16;
    default:
        return 1024 * 4;
    }
}

static rt_err_t its_alloc_tables(struct gicv3_its_data *its_data)
{
#define GITS_BASER_NR_REGS              8

    rt_uint32_t device_ids, i;
    rt_uint64_t reg, type;
    rt_uint64_t its_base =  its_data->base_va;

    device_ids = MASK_GET(GITS_TYPER(its_base), GITS_TYPER_DEVBITS) + 1;

    for (i = 0; i < GITS_BASER_NR_REGS; i++)
    {
        rt_size_t page_size, entry_size, page_cnt, lvl2_width = 0;
        rt_bool_t indirect = RT_FALSE;
        void *alloc_addr, *alloc_addr_pa;

        reg = GITS_BASER(its_base, i);
        type = MASK_GET(reg, GITS_BASER_TYPE);
        entry_size = MASK_GET(reg, GITS_BASER_ENTRY_SIZE) + 1;

        switch (MASK_GET(reg, GITS_BASER_PAGE_SIZE))
        {
        case GITS_BASER_PAGE_SIZE_4K:
            page_size = 1024 * 4;
            break;
        case GITS_BASER_PAGE_SIZE_16K:
            page_size = 1024 * 16;
            break;
        case GITS_BASER_PAGE_SIZE_64K:
            page_size = 1024 * 64;
            break;
        default:
            page_size = 1024 * 4;
            break;
        }

        LOG_I("BASER  type: %d  page_size: %d  entry_size: %d device_ids: %d  reg: %p",
                    type, page_size, entry_size, device_ids, reg);
        switch (type)
        {
        case GITS_BASER_TYPE_DEVICE:
            if (device_ids > 16)
            {
                /* Use the largest possible page size for indirect */
                page_size = its_probe_baser_page_size(its_data, i);

                /*
                 * lvl1 table size:
                 * subtract ID bits that sparse lvl2 table from 'ids'
                 * which is reported by ITS hardware times lvl1 table
                 * entry size.
                 */
                lvl2_width = fls_z(page_size / entry_size) - 1;
                device_ids -= lvl2_width + 1;

                /* The level 1 entry size is a 64bit pointer */
                entry_size = sizeof(rt_uint64_t);

                indirect = RT_TRUE;
            }

            page_cnt = RT_ALIGN(entry_size << device_ids, page_size) / page_size;
            break;

        case GITS_BASER_TYPE_COLLECTION:
            page_cnt = RT_ALIGN(entry_size * ARM_GIC_CPU_NUM, page_size) / page_size;
            break;

        default:
            continue;
        }

        LOG_I("Allocating table of %ldx%ldK pages (%ld bytes entry)",
                            page_cnt, page_size / 1024, entry_size);

        alloc_addr = rt_malloc_align(page_size * page_cnt, page_size);
        if (!alloc_addr)
        {
            return -RT_ENOMEM;
        }

        rt_memset(alloc_addr, 0, page_size * page_cnt);
        alloc_addr_pa = rt_kmem_v2p(alloc_addr);
        alloc_addr = rt_ioremap(alloc_addr, page_size * page_cnt);

        switch (page_size)
        {
        case 1024 * 4:
            reg = GITS_BASER_PAGE_SIZE_4K << 8;
            break;

        case 1024 * 16:
            reg = GITS_BASER_PAGE_SIZE_16K << 8;
            break;

        case 1024 * 64:
            reg = GITS_BASER_PAGE_SIZE_64K << 8;
            break;
        }

        reg |= MASK_SET(page_cnt - 1, GITS_BASER_SIZE);
        reg |= MASK_SET(GIC_BASER_SHARE_INNER, GITS_BASER_SHAREABILITY);    /* Inner Shareable */
        reg |= MASK_SET((rt_uint64_t) alloc_addr_pa >> GITS_BASER_ADDR_SHIFT, GITS_BASER_ADDR);
        reg |= MASK_SET(GIC_BASER_CACHE_INNERLIKE, GITS_BASER_OUTER_CACHE); /* OuterCache */
        reg |= MASK_SET(GIC_BASER_CACHE_RAWAWB, GITS_BASER_INNER_CACHE);    /* Cacheable */
        reg |= MASK_SET(indirect ? 1 : 0, GITS_BASER_INDIRECT);             /* Indirect */
        reg |= MASK_SET(1, GITS_BASER_VALID);                               /* Valid */

        GITS_BASER(its_base, i) = reg;

        /* TOFIX: check page size & SHAREABILITY validity after write */
        if (type == GITS_BASER_TYPE_DEVICE && indirect)
        {
            its_data->dev_table_is_indirect   = indirect;
            its_data->indirect_dev_lvl1_table = alloc_addr;
            its_data->indirect_dev_lvl1_width = device_ids;
            its_data->indirect_dev_lvl2_width = lvl2_width;
            its_data->indirect_dev_page_size  = page_size;
            LOG_D("table Indirection enabled");
        }
    }

    return RT_EOK;
}

static rt_bool_t its_queue_full(struct gicv3_its_data *its_data)
{
    rt_size_t widx;
    rt_size_t ridx;

    widx = its_data->cmd_write - its_data->cmd_base;
    ridx = GITS_CREADR( its_data->base_va) / sizeof(struct its_cmd_block);

    /* This is incredibly unlikely to happen, unless the ITS locks up. */
    return (((widx + 1) % ITS_CMD_QUEUE_NR_ENTRIES) == ridx);
}

static struct its_cmd_block *its_allocate_entry(struct gicv3_its_data *its_data)
{
    struct its_cmd_block *cmd;
    unsigned int count = 1000000;   /* 1s! */

    while (its_queue_full(its_data))
    {
        count--;
        if (!count)
        {
            LOG_E("ITS queue not draining");
            return RT_NULL;
        }
        rt_hw_us_delay(1);
    }

    cmd = its_data->cmd_write++;

    /* Handle queue wrapping */
    if (its_data->cmd_write == (its_data->cmd_base + ITS_CMD_QUEUE_NR_ENTRIES))
    {
        its_data->cmd_write = its_data->cmd_base;
    }

    /* Clear command  */
    cmd->raw_cmd[0] = 0;
    cmd->raw_cmd[1] = 0;
    cmd->raw_cmd[2] = 0;
    cmd->raw_cmd[3] = 0;

    return cmd;
}

static rt_err_t its_post_command(struct gicv3_its_data *its_data, struct its_cmd_block *cmd)
{
    rt_uint64_t wr_idx, rd_idx, idx;
    rt_uint32_t count = 1000000;   /* 1s! */

    wr_idx = (its_data->cmd_write - its_data->cmd_base) * sizeof(*cmd);
    rd_idx = GITS_CREADR( its_data->base_va);

    rt_hw_wmb();

    GITS_CWRITER( its_data->base_va) = wr_idx;

    while (1)
    {
        idx = GITS_CREADR( its_data->base_va);
        if (idx == wr_idx)
        {
            break;
        }

        count--;
        if (!count)
        {
            LOG_D("cmd[0] %p", cmd->raw_cmd[0]);
            LOG_D("cmd[1] %p", cmd->raw_cmd[1]);
            LOG_D("cmd[2] %p", cmd->raw_cmd[2]);
            LOG_D("cmd[3] %p", cmd->raw_cmd[3]);

            LOG_E("ITS queue timeout (rd 0x%X => 0x%X => wr 0x%X)", rd_idx, idx, wr_idx);
            LOG_E("GITS_TYPER: %p", GITS_TYPER( its_data->base_va));
            LOG_E("GITS_FCTLR: 0x%X", GITS_FCTLR( its_data->base_va));
            return -RT_ETIMEOUT;
        }
        rt_hw_us_delay(1);
    }

    return RT_EOK;
}

static rt_err_t its_send_sync_cmd(struct gicv3_its_data *its_data, rt_uint64_t rd_addr)
{
    struct its_cmd_block *cmd = its_allocate_entry(its_data);

    if (!cmd)
    {
        return -RT_EBUSY;
    }

    cmd->raw_cmd[0] = MASK_SET(GITS_CMD_ID_SYNC, GITS_CMD_ID);
    cmd->raw_cmd[2] = MASK_SET(rd_addr >> GITS_CMD_RDBASE_ALIGN, GITS_CMD_RDBASE);

    return its_post_command(its_data, cmd);
}

static rt_err_t its_send_mapc_cmd(struct gicv3_its_data *its_data, rt_uint32_t icid, rt_uint32_t cpuid, rt_bool_t valid)
{
    struct its_cmd_block *cmd = its_allocate_entry(its_data);

    if (!cmd)
    {
        return -RT_EBUSY;
    }

    cmd->raw_cmd[0] =   MASK_SET(GITS_CMD_ID_MAPC, GITS_CMD_ID);
    cmd->raw_cmd[2] =   MASK_SET(icid, GITS_CMD_ICID)                                               |
                        MASK_SET(its_data->rdbase[cpuid] >> GITS_CMD_RDBASE_ALIGN, GITS_CMD_RDBASE) |
                        MASK_SET(valid ? 1 : 0, GITS_CMD_VALID);

    return its_post_command(its_data, cmd);
}

static rt_err_t its_send_mapd_cmd(struct gicv3_its_data *its_data, rt_uint32_t device_id,
                        rt_uint32_t size, rt_uint64_t itt_addr, rt_bool_t valid)
{
    struct its_cmd_block *cmd = its_allocate_entry(its_data);

    if (!cmd)
    {
        return -RT_EBUSY;
    }

    cmd->raw_cmd[0] = MASK_SET(GITS_CMD_ID_MAPD, GITS_CMD_ID) | MASK_SET(device_id, GITS_CMD_DEVICEID);
    cmd->raw_cmd[1] = MASK_SET(size, GITS_CMD_SIZE);
    cmd->raw_cmd[2] = MASK_SET(itt_addr >> GITS_CMD_ITTADDR_ALIGN, GITS_CMD_ITTADDR) | MASK_SET(valid ? 1 : 0, GITS_CMD_VALID);

    return its_post_command(its_data, cmd);
}

static rt_err_t its_send_mapti_cmd(struct gicv3_its_data *its_data, rt_uint32_t device_id,
                    rt_uint32_t event_id, rt_uint32_t intid, rt_uint32_t icid)
{
    struct its_cmd_block *cmd = its_allocate_entry(its_data);

    if (!cmd)
    {
        return -RT_EBUSY;
    }

    cmd->raw_cmd[0] = MASK_SET(GITS_CMD_ID_MAPTI, GITS_CMD_ID) | MASK_SET(device_id, GITS_CMD_DEVICEID);
    cmd->raw_cmd[1] = MASK_SET(event_id, GITS_CMD_EVENTID) | MASK_SET(intid, GITS_CMD_PINTID);
    cmd->raw_cmd[2] = MASK_SET(icid, GITS_CMD_ICID);

    return its_post_command(its_data, cmd);
}

static rt_err_t its_send_int_cmd(struct gicv3_its_data *its_data, rt_uint32_t device_id, rt_uint32_t event_id)
{
    struct its_cmd_block *cmd = its_allocate_entry(its_data);

    if (!cmd)
    {
        return -RT_EBUSY;
    }

    cmd->raw_cmd[0] = MASK_SET(GITS_CMD_ID_INT, GITS_CMD_ID) | MASK_SET(device_id, GITS_CMD_DEVICEID);
    cmd->raw_cmd[1] = MASK_SET(event_id, GITS_CMD_EVENTID);

    return its_post_command(its_data, cmd);
}

static void its_setup_cmd_queue(struct gicv3_its_data *its_data)
{
    rt_uint64_t its_base =  its_data->base_va;
    rt_uint64_t reg = 0;
    void *cmd_base_pa;

    its_data->cmd_queue_size = ITS_CMD_QUEUE_SIZE;
    its_data->cmd_base = rt_malloc_align(its_data->cmd_queue_size, 0x10000);

    cmd_base_pa = rt_kmem_v2p(its_data->cmd_base);
    its_data->cmd_base = rt_ioremap(cmd_base_pa, its_data->cmd_queue_size);
    its_data->cmd_write = its_data->cmd_base;

    /* Zero out cmd table */
    rt_memset(its_data->cmd_base, 0, its_data->cmd_queue_size);

    LOG_D("cmd base va cache:   %p", its_data->cmd_base);
    LOG_D("cmd base pa: [%p : %p]", cmd_base_pa, cmd_base_pa + its_data->cmd_queue_size);

    reg |= MASK_SET(its_data->cmd_queue_size / 4096, GITS_CBASER_SIZE);
    reg |= MASK_SET(GIC_BASER_SHARE_INNER, GITS_CBASER_SHAREABILITY);/* Inner Shareable */
    reg |= MASK_SET((rt_uint64_t) cmd_base_pa >> GITS_CBASER_ADDR_SHIFT, GITS_CBASER_ADDR);
    reg |= MASK_SET(GIC_BASER_CACHE_RAWAWB, GITS_CBASER_OUTER_CACHE);/* Cacheable R-allocate, W-allocate, W-back */
    reg |= MASK_SET(GIC_BASER_CACHE_RAWAWB, GITS_CBASER_INNER_CACHE); /* Cacheable R-allocate, W-allocate, W-back */
    reg |= MASK_SET(1, GITS_CBASER_VALID);  /* Valid */


    GITS_CBASER(its_base) = reg;

    LOG_I("GITS_CBASER: %p  %p", GITS_CBASER(its_base), reg);
    LOG_I("Allocated %ld entries for command table %p", ITS_CMD_QUEUE_NR_ENTRIES, its_data->cmd_base);

    GITS_CWRITER(its_base) = 0;
}

static rt_uint64_t its_rdist_get_rdbase(rt_uint64_t index, rt_uint32_t cpuid)
{
    rt_uint64_t rdbase;
    struct gicv3_its_data *its_data = &_gic_table[index].its_config;

    if (cpuid >= ARM_GIC_CPU_NUM)
    {
        LOG_E("cpuid: %d > ARM_GIC_CPU_NUM", cpuid);
    }

    if (MASK_GET(GITS_TYPER( its_data->base_va), GITS_TYPER_PTA))
    {
        rdbase = _gic_table[index].its_config.redist_base[cpuid];
    }
    else
    {
        rdbase = (GIC_RDIST_TYPER(_gic_table[index].redist_hw_base[0] + cpuid * 0x20000) >> 8) & 0xFFFF;
        rdbase <<= GITS_CMD_RDBASE_SHIFT;
    }

    LOG_I("PTA: %d  rdbase: 0x%X", MASK_GET(GITS_TYPER( its_data->base_va), GITS_TYPER_PTA), rdbase);
    return rdbase;
}

static rt_uint64_t gicv3_lpi_get_priority(rt_uint64_t index, rt_uint32_t irq)
{
    if (!_gic_table[index].lpi_init_flag)
    {
        return -RT_ERROR;
    }

    irq -= GIC_LPI_INTID_START;
    return HWREG8(_gic_table[index].gicr_propbaser_base + irq) & 0xFC;
}

static void gicv3_lpi_set_priority(rt_uint64_t index, rt_uint32_t irq, rt_uint64_t priority)
{
    rt_uint8_t reg;

    if (!_gic_table[index].lpi_init_flag)
    {
        return;
    }

    irq -= GIC_LPI_INTID_START;
    reg = HWREG8(_gic_table[index].gicr_propbaser_base + irq);
    reg &= 0x01;
    reg |= priority & 0xFC;
    HWREG8(_gic_table[index].gicr_propbaser_base + irq) = reg;
    rt_hw_cpu_dcache_clean((void *) _gic_table[index].gicr_propbaser_base + irq, 1);
}

static void gicv3_lpi_mask(rt_uint64_t index, rt_uint32_t irq)
{
    rt_uint8_t reg;

    if (!_gic_table[index].lpi_init_flag)
    {
        return;
    }

    irq -= GIC_LPI_INTID_START;
    reg = HWREG8(_gic_table[index].gicr_propbaser_base + irq);
    reg &= ~0x1;
    HWREG8(_gic_table[index].gicr_propbaser_base + irq) = reg;
    rt_hw_cpu_dcache_clean((void *) _gic_table[index].gicr_propbaser_base + irq, 1);
}

static void gicv3_lpi_umask(rt_uint64_t index, rt_uint32_t irq)
{
    rt_uint8_t reg;

    if (!_gic_table[index].lpi_init_flag)
    {
        return;
    }

    irq -= GIC_LPI_INTID_START;
    reg = HWREG8(_gic_table[index].gicr_propbaser_base + irq);
    reg |= 0x1;
    HWREG8(_gic_table[index].gicr_propbaser_base + irq) = reg;
    rt_hw_cpu_dcache_clean((void *) _gic_table[index].gicr_propbaser_base + irq, 1);
}

static rt_err_t its_init(rt_uint64_t index)
{
    rt_err_t ret;
    rt_uint32_t reg, i;
    struct gicv3_its_data *its_data = &_gic_table[index].its_config;

    LOG_W("GITS_TYPER: %p", GITS_TYPER(its_data->base_va));

    for (i = 0; i < ARM_GIC_CPU_NUM; i++)
    {
        its_data->rdbase[i] = its_rdist_get_rdbase(index, i);
    }

    ret = its_force_quiescent(its_data);
    if (ret)
    {
        LOG_E("Failed to quiesce, giving up");
        return ret;
    }

    ret = its_alloc_tables(its_data);
    if (ret)
    {
        LOG_E("Failed to allocate tables, giving up");
        return ret;
    }

    its_setup_cmd_queue(its_data);

    reg = GITS_CTLR( its_data->base_va);
    reg |= GITS_CTLR_Enabled;
    GITS_CTLR( its_data->base_va) = reg;

    /* Map the boot CPU id to the CPU redistributor */
    ret = its_send_mapc_cmd(its_data, ICID_NO, rt_hw_cpu_id(), RT_TRUE);
    if (ret)
    {
        LOG_E("Failed to map boot CPU redistributor");
        return ret;
    }

    return RT_EOK;
}

static void lpi_init(rt_uint64_t index)
{
    rt_ubase_t base;
    rt_uint32_t val, val1, i, lpi_id_bits, prop_size, pend_size;
    void *propbaser_pa, *propbaser_va, *pendbaser_pa, *pendbaser_va;
    rt_err_t ret = -RT_ERROR;

    if (_gic_table[index].lpi_init_flag)
    {
        return;
    }

    if (_gic_table[index].its_config.base_pa)
    {
        ret = its_init(index);
    }

    if (ret != RT_EOK)
    {
        /* LPIS, bit [17]: Indicates whether the implementation supports LPIs */
        val = (GIC_DIST_TYPE(_gic_table[index].dist_hw_base) >> 17) & 0X1;
        if (!val)
        {
            LOG_E("no supports LPI");
            return;
        }
        _gic_table[index].msi_address = GIC_RDIST_SETLPIR_ADDR(_gic_table[index].redist_hw_base[rt_hw_cpu_id()]);
    }
    else
    {
        _gic_table[index].msi_address = GITS_TRANSLATER_ADDR(_gic_table[index].its_config.base_pa);
    }

    lpi_id_bits = (GIC_DIST_TYPE(_gic_table[index].dist_hw_base) >> 19) & 0x1F;
    prop_size = 1 << (lpi_id_bits + 1);
    pend_size = RT_ALIGN(prop_size / 8, 0x10000);

    propbaser_va = rt_malloc_align(prop_size, 0x10000);
    pendbaser_va = rt_malloc_align(pend_size * ARM_GIC_CPU_NUM, 0x10000);

    rt_memset(propbaser_va, 0, prop_size);
    rt_memset(pendbaser_va, 0, pend_size * ARM_GIC_CPU_NUM);

    rt_hw_cpu_dcache_clean(propbaser_va, prop_size);
    rt_hw_cpu_dcache_clean(pendbaser_va, pend_size * ARM_GIC_CPU_NUM);

    propbaser_pa = rt_kmem_v2p(propbaser_va);
    pendbaser_pa = rt_kmem_v2p(pendbaser_va);

    _gic_table[index].gicr_propbaser_base = (rt_uint64_t)propbaser_va;

    base = _gic_table[index].redist_hw_base[0];

    for (i = 0; i < ARM_GIC_CPU_NUM; i++)
    {
        val = GIC_RDIST_CTRL(base);
        val &= ~GICR_CTLR_EnableLPI;
        GIC_RDIST_CTRL(base) = val;

        val = (rt_uint64_t) propbaser_pa | 0x780 | lpi_id_bits;
        val1 = (rt_uint64_t) pendbaser_pa | 0x4000000000000780;
        GIC_RDIST_PROPBASER(base) = val;
        GIC_RDIST_PENDBASER(base) = val1;

        val = GIC_RDIST_CTRL(base);
        val |= GICR_CTLR_EnableLPI;
        GIC_RDIST_CTRL(base) = val;

        GIC_RDIST_INVALLR(base) = 0;
        GIC_RDIST_SYNCR(base) = 0;

        pendbaser_pa += pend_size;
        base += 0x20000;
    }

    _gic_table[index].lpi_init_flag = RT_TRUE;
}

void gicv3_its_base_set(rt_uint64_t index, rt_uint64_t its_base, rt_uint64_t rd_base)
{
    rt_uint32_t i;

    _gic_table[index].its_config.base_pa = its_base;
    _gic_table[index].its_config.base_va = (rt_uint64_t) rt_ioremap((void *) its_base, 0x20000);

    for (i = 0; i < ARM_GIC_CPU_NUM; i++)
    {
        _gic_table[index].its_config.redist_base[i] = rd_base + 0x20000 * i;
    }
}

rt_uint32_t gicv3_lpi_alloc_irq(void)
{
    static volatile rt_atomic_t lpi_intid = GIC_LPI_INTID_START;
    return (rt_uint32_t) rt_atomic_add(&lpi_intid, 1);
}

rt_uint64_t gicv3_msi_address_get(rt_uint64_t index)
{
    return _gic_table[index].msi_address;
}

rt_err_t gicv3_its_map_intid(rt_uint64_t index, rt_uint32_t device_id,
                                rt_uint32_t event_id, rt_uint32_t intid)
{
    rt_err_t ret;
    struct gicv3_its_data *its_data = &_gic_table[index].its_config;

    /* TOFIX check device_id, event_id & intid bounds */
    if (intid < GIC_LPI_INTID_START)
    {
        return -RT_EINVAL;
    }

    /* The CPU id directly maps as ICID for the current CPU redistributor */
    ret = its_send_mapti_cmd(its_data, device_id, event_id, intid, ICID_NO);
    if (ret)
    {
        LOG_E("Failed to map eventid %d to intid %d for deviceid %x", event_id, intid, device_id);
        return ret;
    }

    return its_send_sync_cmd(its_data, its_data->rdbase[rt_hw_cpu_id()]);
}

rt_err_t gicv3_its_init_device_id(rt_uint64_t index, rt_uint32_t device_id, rt_uint32_t nites)
{
    rt_size_t entry_size, alloc_size;
    rt_uint32_t nr_ites;
    rt_err_t ret;
    void *itt;
    struct gicv3_its_data *its_data = &_gic_table[index].its_config;

    /* TOFIX check device_id & nites bounds */

    entry_size = MASK_GET(GITS_TYPER( its_data->base_va), GITS_TYPER_ITT_ENTRY_SIZE) + 1;
    if (its_data->dev_table_is_indirect)
    {
        size_t offset = device_id >> its_data->indirect_dev_lvl2_width;

        /* Check if DeviceID can fit in the Level 1 table */
        if (offset > (1 << its_data->indirect_dev_lvl1_width))
        {
            return -RT_EINVAL;
        }

        /* Check if a Level 2 table has already been allocated for the DeviceID */
        if (!its_data->indirect_dev_lvl1_table[offset])
        {
            void *alloc_addr, *alloc_addr_pa;

            LOG_I("Allocating Level 2 Device %ldK table", its_data->indirect_dev_page_size / 1024);

            alloc_addr = rt_malloc_align(its_data->indirect_dev_page_size, its_data->indirect_dev_page_size);
            if (!alloc_addr)
            {
                return -RT_ENOMEM;
            }

            alloc_addr_pa = rt_kmem_v2p(alloc_addr);
            alloc_addr = rt_ioremap(alloc_addr_pa, its_data->indirect_dev_page_size);

            rt_memset(alloc_addr, 0, its_data->indirect_dev_page_size);

            its_data->indirect_dev_lvl1_table[offset] = (uintptr_t) alloc_addr | MASK_SET(1, GITS_BASER_VALID);

            rt_hw_isb();
        }
    }

    /* ITT must be of power of 2 */
    nr_ites = nites > 2 ? nites : 2;
    alloc_size = RT_ALIGN(nr_ites * entry_size, 256);

    LOG_I("Allocating ITT for DeviceID 0x%x and %d vectors (%ld bytes entry)",
        device_id, nr_ites, entry_size);

    itt = rt_malloc_align(alloc_size, 256);
    if (!itt)
    {
        return -RT_ENOMEM;
    }

    /* size is log2(ites) - 1, equivalent to (fls(ites) - 1) - 1 */
    itt = rt_kmem_v2p(itt);
    ret = its_send_mapd_cmd(its_data, device_id, fls_z(nr_ites) - 2, (uintptr_t) itt, RT_TRUE);
    if (ret)
    {
        LOG_E("Failed to map device id %x ITT table", device_id);
        return ret;
    }

    return RT_EOK;
}

void arm_gic_dump_type(rt_uint64_t index)
{
    unsigned int gic_type;
    unsigned int gic_version;
    unsigned int gic_rp;

    gic_version = (GIC_DIST_IIDR(_gic_table[index].dist_hw_base) >> 24) & 0xfUL;
    gic_rp = (GIC_DIST_IIDR(_gic_table[index].dist_hw_base) >> 12) & 0xfUL;
    gic_type = GIC_DIST_TYPE(_gic_table[index].dist_hw_base);
    rt_kprintf("GICv3-%d r%dp%d on %p, max IRQs: %d, %s security extension(%08x)\n",
               (gic_version == 0) ? 500 : (gic_version == 2) ? 600 : 0,
               (gic_rp >> 4) & 0xF,
                gic_rp & 0xF,
               _gic_table[index].dist_hw_base,
               _gic_max_irq,
               gic_type & (1U << 10U) ? "has" : "no",
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

static void arm_gic_bind_dump(void)
{
#ifdef BSP_USING_GICV3
    int i;
    for (i = 32; i < _gic_max_irq; i++)
    {
        rt_kprintf("irq(%d) -> 0x%X\n", i, arm_gic_get_router_cpu(0, i));
    }
#endif  /* BSP_USING_GICV3 */
}

static void arm_gic_sgi_dump(rt_uint64_t index)
{
    rt_int32_t cpu_id = rt_hw_cpu_id();

    rt_kprintf("redist_hw_base = 0x%X\n", _gic_table[index].redist_hw_base[cpu_id]);
    rt_kprintf("--- sgi mask ---\n");
    rt_kprintf("0x%08x\n", GIC_RDISTSGI_ISENABLER0(_gic_table[index].redist_hw_base[cpu_id]));
    rt_kprintf("--- sgi pending ---\n");
    rt_kprintf("0x%08x\n", GIC_RDISTSGI_ISPENDR0(_gic_table[index].redist_hw_base[cpu_id]));
    rt_kprintf("--- sgi active ---\n");
    rt_kprintf("0x%08x\n", GIC_RDISTSGI_ISACTIVER0(_gic_table[index].redist_hw_base[cpu_id]));
}

long gic_dump(void)
{
    arm_gic_dump_type(0);
    arm_gic_dump(0);
    arm_gic_bind_dump();
    arm_gic_sgi_dump(0);

    return 0;
}
MSH_CMD_EXPORT(gic_dump, show gic status);

#ifdef LPI_DEBUG
#include "interrupt.h"

static int gicv3_its_send_int(struct gicv3_its_data *its_data, rt_uint32_t device_id, rt_uint32_t event_id)
{
    /* TOFIX check device_id & event_id bounds */
    return its_send_int_cmd(its_data, device_id, event_id);
}

static void lpi_test_isr(int vector, void *param)
{
    rt_kprintf("lpi_test_isr  vector %d\n", vector);
}

static void lpi_init_test(int argc, char *argv)
{
    rt_err_t ret = 0;
    rt_uint32_t irq, device_id, event_id, i;

    device_id = 0x123;
    event_id = 0x5;

    lpi_init(0);

    gicv3_its_init_device_id(0, device_id, 32);

    for (i = 0; i < 5; i++)
    {
        irq = gicv3_lpi_alloc_irq();
        ret |= gicv3_its_map_intid(0, device_id, event_id + i, irq);
        if (ret)
        {
            LOG_E("Failed to map boot CPU gicv3_its_map_intid");
            return;
        }

        gicv3_lpi_umask(0, irq);
    }

    rt_thread_mdelay(100);

    for (i = 0; i < 5; i++)
    {
        gicv3_its_send_int(&_gic_table[0].its_config, device_id, event_id + i);
    }

    irq = rt_hw_interrupt_msi_alloc_irq();
    rt_hw_interrupt_msi_setup_deviceid(device_id + 1, 32);
    rt_hw_interrupt_msi_map_irq(device_id + 1, 0x02, irq);
    rt_hw_interrupt_install(irq, lpi_test_isr, RT_NULL, "msi");
    rt_hw_interrupt_umask(irq);
    gicv3_its_send_int(&_gic_table[0].its_config, device_id + 1, 0x02);
}
MSH_CMD_EXPORT(lpi_init_test, lpi_init_test);
#endif /* LPI_DEBUG */

#endif /* defined(BSP_USING_GIC) && defined(BSP_USING_GICV3) */
