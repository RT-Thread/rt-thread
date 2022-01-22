/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 * 2014-04-03     Grissiom     many enhancements
 * 2018-11-22     Jesven       add rt_hw_ipi_send()
 *                             add rt_hw_ipi_handler_install()
 */

#include <rthw.h>
#include <rtthread.h>

#include "gicv3.h"
#include "cp15.h"

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif

struct arm_gic_v3
{
    rt_uint32_t offset;                     /* the first interrupt index in the vector table */
    rt_uint32_t redist_hw_base[RT_CPUS_NR]; /* the pointer of the gic redistributor */
    rt_uint32_t dist_hw_base;               /* the base address of the gic distributor */
    rt_uint32_t cpu_hw_base[RT_CPUS_NR];    /* the base addrees of the gic cpu interface */
};

/* 'ARM_GIC_MAX_NR' is the number of cores */
static struct arm_gic_v3 _gic_table[ARM_GIC_MAX_NR];
static unsigned int _gic_max_irq;

/**
 * @name: arm_gic_cpumask_to_affval
 * @msg:
 * @in param cpu_mask:
 * @out param cluster_id: aff1 [0:7],aff2 [8:15],aff3 [16:23]
 * @out param target_list:  Target List. The set of PEs for which SGI interrupts will be generated. Each bit corresponds to the
 *                          PE within a cluster with an Affinity 0 value equal to the bit number.
 * @return {rt_uint32_t} 0 is finish , 1 is data valid
 */
RT_WEAK rt_uint32_t arm_gic_cpumask_to_affval(rt_uint32_t *cpu_mask, rt_uint32_t *cluster_id, rt_uint32_t *target_list)
{
    return 0;
}

RT_WEAK rt_uint64_t get_main_cpu_affval(void)
{
    return 0;
}

int arm_gic_get_active_irq(rt_uint32_t index)
{
    int irq;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    __get_gicv3_reg(ICC_IAR1, irq);

    irq = (irq & 0x1FFFFFF) + _gic_table[index].offset;
    return irq;
}

void arm_gic_ack(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    RT_ASSERT(irq >= 0U);

    __asm__ volatile("dsb 0xF" ::
                         : "memory");
    __set_gicv3_reg(ICC_EOIR1, irq);
}

void arm_gic_mask(rt_uint32_t index, int irq)
{
    rt_uint32_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq < 32U)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();
        RT_ASSERT((cpu_id) < RT_CPUS_NR);
        GIC_RDISTSGI_ICENABLER0(_gic_table[index].redist_hw_base[cpu_id]) = mask;
    }
    else
    {
        GIC_DIST_ENABLE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

void arm_gic_umask(rt_uint32_t index, int irq)
{
    rt_uint32_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq < 32U)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();
        RT_ASSERT((cpu_id) < RT_CPUS_NR);
        GIC_RDISTSGI_ISENABLER0(_gic_table[index].redist_hw_base[cpu_id]) = mask;
    }
    else
    {
        GIC_DIST_ENABLE_SET(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

rt_uint32_t arm_gic_get_pending_irq(rt_uint32_t index, int irq)
{
    rt_uint32_t pend;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq >= 16U)
    {
        pend = (GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;
    }
    else
    {
        /* INTID 0-15 Software Generated Interrupt */
        pend = (GIC_DIST_SPENDSGI(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
        /* No CPU identification offered */
        if (pend != 0U)
        {
            pend = 1U;
        }
        else
        {
            pend = 0U;
        }
    }

    return (pend);
}

void arm_gic_set_pending_irq(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq >= 16U)
    {
        GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) = 1U << (irq % 32U);
    }
    else
    {
        /* INTID 0-15 Software Generated Interrupt */
        /* Forward the interrupt to the CPU interface that requested it */
        GIC_DIST_SOFTINT(_gic_table[index].dist_hw_base) = (irq | 0x02000000U);
    }
}

void arm_gic_clear_pending_irq(rt_uint32_t index, int irq)
{
    rt_uint32_t mask;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq >= 16U)
    {
        mask = 1U << (irq % 32U);
        GIC_DIST_PENDING_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
    }
    else
    {
        mask = 1U << ((irq % 4U) * 8U);
        GIC_DIST_CPENDSGI(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

void arm_gic_set_configuration(rt_uint32_t index, int irq, rt_uint32_t config)
{
    rt_uint32_t icfgr;
    rt_uint32_t shift;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    icfgr = GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq);
    shift = (irq % 16U) << 1U;

    icfgr &= (~(3U << shift));
    icfgr |= (config << shift);

    GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) = icfgr;
}

rt_uint32_t arm_gic_get_configuration(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) >> ((irq % 16U) >> 1U));
}

void arm_gic_clear_active(rt_uint32_t index, int irq)
{
    rt_uint32_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_ACTIVE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}

/* Set up the cpu mask for the specific interrupt */
void arm_gic_set_cpu(rt_uint32_t index, int irq, unsigned int cpumask)
{
    rt_uint32_t old_tgt;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    old_tgt = GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq);

    old_tgt &= ~(0x0FFUL << ((irq % 4U) * 8U));
    old_tgt |= cpumask << ((irq % 4U) * 8U);

    GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) = old_tgt;
}

rt_uint32_t arm_gic_get_target_cpu(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
}

void arm_gic_set_priority(rt_uint32_t index, int irq, rt_uint32_t priority)
{
    rt_uint32_t mask;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq < 32U)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();
        RT_ASSERT((cpu_id) < RT_CPUS_NR);

        mask = GIC_RDISTSGI_IPRIORITYR(_gic_table[index].redist_hw_base[cpu_id], irq);
        mask &= ~(0xFFUL << ((irq % 4U) * 8U));
        mask |= ((priority & 0xFFUL) << ((irq % 4U) * 8U));
        GIC_RDISTSGI_IPRIORITYR(_gic_table[index].redist_hw_base[cpu_id], irq) = mask;
    }
    else
    {
        mask = GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq);
        mask &= ~(0xFFUL << ((irq % 4U) * 8U));
        mask |= ((priority & 0xFFUL) << ((irq % 4U) * 8U));
        GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

rt_uint32_t arm_gic_get_priority(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq < 32U)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        RT_ASSERT((cpu_id) < RT_CPUS_NR);
        return (GIC_RDISTSGI_IPRIORITYR(_gic_table[index].redist_hw_base[cpu_id], irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
    }
    else
    {
        return (GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
    }
}

void arm_gic_set_system_register_enable_mask(rt_uint32_t index, rt_uint32_t value)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    value &= 0xFFUL;
    /* set priority mask */
    __set_gicv3_reg(ICC_SRE, value);
    __asm__ volatile ("isb 0xF"::
                        :"memory");
}

rt_uint32_t arm_gic_get_system_register_enable_mask(rt_uint32_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    rt_uint32_t value;

    __get_gicv3_reg(ICC_SRE, value);
    return value;
}

void arm_gic_set_interface_prior_mask(rt_uint32_t index, rt_uint32_t priority)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    priority &= 0xFFUL;
    /* set priority mask */
    __set_gicv3_reg(ICC_PMR, priority);
}

rt_uint32_t arm_gic_get_interface_prior_mask(rt_uint32_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    rt_uint32_t priority;

    __get_gicv3_reg(ICC_PMR, priority);
    return priority;
}

void arm_gic_set_binary_point(rt_uint32_t index, rt_uint32_t binary_point)
{
    index = index;
    binary_point &= 0x7U;

    __set_gicv3_reg(ICC_BPR1, binary_point);
}

rt_uint32_t arm_gic_get_binary_point(rt_uint32_t index)
{
    rt_uint32_t binary_point;

    index = index;
    __get_gicv3_reg(ICC_BPR1, binary_point);
    return binary_point;
}

rt_uint32_t arm_gic_get_irq_status(rt_uint32_t index, int irq)
{
    rt_uint32_t pending;
    rt_uint32_t active;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    active = (GIC_DIST_ACTIVE_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;
    pending = (GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;

    return ((active << 1U) | pending);
}

void arm_gic_send_affinity_sgi(rt_uint32_t index, int irq, rt_uint32_t cpu_mask, rt_uint32_t routing_mode)
{
    rt_uint64_t sgi_val;

    if (routing_mode)
    {
        sgi_val = (1ULL << 40) | ((irq & 0x0FULL) << 24); //Interrupts routed to all PEs in the system, excluding "self".
        /*  Write the ICC_SGI1R registers */
        __asm__ volatile("dsb 0xF" ::
                            : "memory");
        __set_cp64(15, 0, sgi_val, 12);
        __asm__ volatile("isb 0xF" ::
                            : "memory");
    }
    else
    {
        rt_uint32_t cluster_id, target_list;
        while (arm_gic_cpumask_to_affval(&cpu_mask, &cluster_id, &target_list))
        {
            sgi_val = ((irq & 0x0FULL) << 24 |
                       target_list |
                       ((cluster_id >> 8) & 0xFFULL) << GIC_RSGI_AFF1_OFFSET |
                       ((cluster_id >> 16) & 0xFFULL) << GIC_RSGI_AFF2_OFFSET |
                       ((cluster_id >> 24) & 0xFFull) << GIC_RSGI_AFF3_OFFSET);

            __asm__ volatile("dsb 0xF" ::
                                : "memory");
            __set_cp64(15, 0, sgi_val, 12);
            __asm__ volatile("isb 0xF" ::
                                : "memory");
        }
    }
}

rt_uint32_t arm_gic_get_high_pending_irq(rt_uint32_t index)
{
    rt_uint32_t irq;
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    index = index;
    __get_gicv3_reg(ICC_HPPIR1, irq);
    return irq;
}

rt_uint32_t arm_gic_get_interface_id(rt_uint32_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    return GIC_CPU_IIDR(_gic_table[index].cpu_hw_base);
}

void arm_gic_set_group(rt_uint32_t index, int irq, rt_uint32_t group)
{
    rt_uint32_t igroupr;
    rt_uint32_t shift;

    RT_ASSERT(index < ARM_GIC_MAX_NR);
    RT_ASSERT(group <= 1U);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    igroupr = GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq);
    shift = (irq % 32U);
    igroupr &= (~(1U << shift));
    igroupr |= ((group & 0x1U) << shift);

    GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq) = igroupr;
}

rt_uint32_t arm_gic_get_group(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;
}

static int arm_gicv3_wait_rwp(rt_uint32_t index, rt_uint32_t irq)
{
    rt_uint32_t rwp_bit;
    rt_uint32_t base;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (irq < 32u)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        RT_ASSERT((cpu_id) < RT_CPUS_NR);
        base = _gic_table[index].redist_hw_base[cpu_id];
        rwp_bit = GICR_CTLR_RWP;
    }
    else
    {
        base = _gic_table[index].dist_hw_base;
        rwp_bit = GICD_CTLR_RWP;
    }

    while (__REG32(base) & rwp_bit)
    {
        ;
    }

    return 0;
}

int arm_gic_dist_init(rt_uint32_t index, rt_uint32_t dist_base, int irq_start)
{
    rt_uint64_t cpu0_affval;
    unsigned int gic_type, i;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    _gic_table[index].dist_hw_base = dist_base;
    _gic_table[index].offset = irq_start;

    /* Find out how many interrupts are supported. */
    gic_type = GIC_DIST_TYPE(dist_base);
    _gic_max_irq = ((gic_type & 0x1fU) + 1U) * 32U;

    /*
     * The GIC only supports up to 1020 interrupt sources.
     * Limit this to either the architected maximum, or the
     * platform maximum.
     */
    if (_gic_max_irq > 1020U)
        _gic_max_irq = 1020U;
    if (_gic_max_irq > ARM_GIC_NR_IRQS) /* the platform maximum interrupts */
        _gic_max_irq = ARM_GIC_NR_IRQS;

    GIC_DIST_CTRL(dist_base) = 0x0U;
    /* Wait for register write pending */
    arm_gicv3_wait_rwp(0, 32);

    /* Set all global interrupts to be level triggered, active low. */
    for (i = 32U; i < _gic_max_irq; i += 16U)
        GIC_DIST_CONFIG(dist_base, i) = 0x0U;

    arm_gicv3_wait_rwp(0, 32);

    cpu0_affval = get_main_cpu_affval();
    /* Set all global interrupts to this CPU only. */
    for (i = 32U; i < _gic_max_irq; i++)
    {
        GIC_DIST_IROUTER_LOW(dist_base, i) = cpu0_affval;
        GIC_DIST_IROUTER_HIGH(dist_base, i) = cpu0_affval >> 32;
    }

    arm_gicv3_wait_rwp(0, 32);

    /* Set priority on spi interrupts. */
    for (i = 32U; i < _gic_max_irq; i += 4U)
        GIC_DIST_PRI(dist_base, i) = 0xa0a0a0a0U;

    arm_gicv3_wait_rwp(0, 32);
    /* Disable all interrupts. */
    for (i = 0U; i < _gic_max_irq; i += 32U)
    {
        GIC_DIST_PENDING_CLEAR(dist_base, i) = 0xffffffffU;
        GIC_DIST_ENABLE_CLEAR(dist_base, i) = 0xffffffffU;
    }

    arm_gicv3_wait_rwp(0, 32);
    /* All interrupts defaults to IGROUP1(IRQ). */
    for (i = 0U; i < _gic_max_irq; i += 32U)
        GIC_DIST_IGROUP(dist_base, i) = 0xffffffffU;

    arm_gicv3_wait_rwp(0, 32);

    /*
            The Distributor control register (GICD_CTLR) must be configured to enable the interrupt groups and to set the routing mode.
            Enable Affinity routing (ARE bits) The ARE bits in GICD_CTLR control whether affinity routing is enabled.
            If affinity routing is not enabled, GICv3 can be configured for legacy operation.
            Whether affinity routing is enabled or not can be controlled separately for Secure and Non-secure state.
            Enables GICD_CTLR contains separate enable bits for Group 0, Secure Group 1 and Non-secure Group 1:
            GICD_CTLR.EnableGrp1S enables distribution of Secure Group 1 interrupts.
            GICD_CTLR.EnableGrp1NS enables distribution of Non-secure Group 1 interrupts.
            GICD_CTLR.EnableGrp0 enables distribution of Group 0 interrupts.
      */
    GIC_DIST_CTRL(dist_base) = GICD_CTLR_ARE_NS | GICD_CTLR_ENGRP1NS;

    return 0;
}

int arm_gic_redist_address_set(rt_uint32_t index, rt_uint32_t redist_addr, rt_uint32_t cpu_id)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    RT_ASSERT((cpu_id) < RT_CPUS_NR);
    _gic_table[index].redist_hw_base[cpu_id] = redist_addr;

    return 0;
}

int arm_gic_cpu_interface_address_set(rt_uint32_t index, rt_uint32_t interface_addr, rt_uint32_t cpu_id)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);
    RT_ASSERT((cpu_id) < RT_CPUS_NR);
    _gic_table[index].cpu_hw_base[cpu_id] = interface_addr;

    return 0;
}

int arm_gic_redist_init(rt_uint32_t index)
{
    unsigned int i;
    rt_uint32_t base;
    rt_int32_t cpu_id = rt_hw_cpu_id();

    RT_ASSERT(index < ARM_GIC_MAX_NR);
    RT_ASSERT((cpu_id) < RT_CPUS_NR);

    base = _gic_table[index].redist_hw_base[cpu_id];
    /* redistributor enable */
    GIC_RDIST_WAKER(base) &= ~(1U << 1);
    while (GIC_RDIST_WAKER(base) & (1 << 2))
    {
        ;
    }

    /* Disable all sgi and ppi interrupt */
    GIC_RDISTSGI_ICENABLER0(base) = 0xFFFFFFFF;
    arm_gicv3_wait_rwp(0, 0);

    /* Clear all inetrrupt pending */
    GIC_RDISTSGI_ICPENDR0(base) = 0xFFFFFFFF;

    /* the corresponding interrupt is Group 1 or Non-secure Group 1. */
    GIC_RDISTSGI_IGROUPR0(base, 0) = 0xFFFFFFFF;
    GIC_RDISTSGI_IGRPMODR0(base, 0) = 0xFFFFFFFF;

    /* Configure default priorities for SGI 0:15 and PPI 16:31. */
    for (i = 0; i < 32; i += 4)
    {
        GIC_RDISTSGI_IPRIORITYR(base, i) = 0xa0a0a0a0U;
    }

    /* Trigger level for PPI interrupts*/
    GIC_RDISTSGI_ICFGR1(base) = 0x0U; // PPI is level-sensitive.
    return 0;
}

int arm_gic_cpu_init(rt_uint32_t index)
{
    rt_uint32_t value;
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    value = arm_gic_get_system_register_enable_mask(index);
    value |= (1U << 0);
    arm_gic_set_system_register_enable_mask(index, value);
    __set_gicv3_reg(ICC_CTLR, 0);

    arm_gic_set_interface_prior_mask(index, 0xFFU);

    /* Enable group1 interrupt */
    value = 0x1U;
    __set_gicv3_reg(ICC_IGRPEN1, value);

    arm_gic_set_binary_point(0, 0);

    /* ICC_BPR0_EL1 determines the preemption group for both
       Group 0 and Group 1 interrupts.
       */
    value = 0x1U;
    __set_gicv3_reg(ICC_CTLR, value);

    return 0;
}

#ifdef RT_USING_SMP
void arm_gic_secondary_cpu_init(void)
{
    arm_gic_redist_init(0);

    arm_gic_cpu_init(0);
}
#endif

void arm_gic_dump_type(rt_uint32_t index)
{
    unsigned int gic_type;

    gic_type = GIC_DIST_TYPE(_gic_table[index].dist_hw_base);
    rt_kprintf("GICv%d on %p, max IRQs: %d, %s security extension(%08x)\n",
               (GIC_DIST_ICPIDR2(_gic_table[index].dist_hw_base) >> 4U) & 0xfUL,
               _gic_table[index].dist_hw_base,
               _gic_max_irq,
               gic_type & (1U << 10U) ? "has" : "no",
               gic_type);
}

void arm_gic_dump(rt_uint32_t index)
{
    unsigned int i, k;

    k = arm_gic_get_high_pending_irq(0);
    rt_kprintf("--- high pending priority: %d(%08x)\n", k, k);
    rt_kprintf("--- hw mask ---\n");
    for (i = 0U; i < _gic_max_irq / 32U; i++)
    {
        rt_kprintf("0x%08x, ",
                   GIC_DIST_ENABLE_SET(_gic_table[index].dist_hw_base,
                                       i * 32U));
    }
    rt_kprintf("\n--- hw pending ---\n");
    for (i = 0U; i < _gic_max_irq / 32U; i++)
    {
        rt_kprintf("0x%08x, ",
                   GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base,
                                        i * 32U));
    }
    rt_kprintf("\n--- hw active ---\n");
    for (i = 0U; i < _gic_max_irq / 32U; i++)
    {
        rt_kprintf("0x%08x, ",
                   GIC_DIST_ACTIVE_SET(_gic_table[index].dist_hw_base,
                                       i * 32U));
    }
    rt_kprintf("\n");
}

long gic_dump(void)
{
    arm_gic_dump_type(0);
    arm_gic_dump(0);

    return 0;
}
MSH_CMD_EXPORT(gic_dump, show gic status);
