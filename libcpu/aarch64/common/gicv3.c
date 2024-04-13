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

#if !defined(RT_USING_SMP) && !defined(RT_USING_AMP)
#define RT_CPUS_NR 1
#else
extern rt_uint64_t rt_cpu_mpidr_early[];
#endif /* RT_USING_SMP */

/* 'ARM_GIC_MAX_NR' is the number of cores */
static struct arm_gic _gic_table[ARM_GIC_MAX_NR];
static unsigned int _gic_max_irq;

int arm_gic_get_active_irq(rt_uint64_t index)
{
    rt_base_t irq;

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
    SET_GICV3_REG(ICC_EOIR1_EL1, (rt_base_t)irq);
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

void arm_gic_set_router_cpu(rt_uint64_t index, int irq, rt_uint64_t aff)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 32);

    GIC_DIST_IROUTER(_gic_table[index].dist_hw_base, irq) = aff & 0xff00ffffffULL;
}

rt_uint64_t arm_gic_get_router_cpu(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 32);

    return GIC_DIST_IROUTER(_gic_table[index].dist_hw_base, irq);
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
        mask &= ~(0xffUL << ((irq % 4) * 8));
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
    RT_UNUSED(index);
    binary_point &= 0x7;

    SET_GICV3_REG(ICC_BPR1_EL1, binary_point);
}

rt_uint64_t arm_gic_get_binary_point(rt_uint64_t index)
{
    rt_uint64_t binary_point;

    RT_UNUSED(index);
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

    RT_UNUSED(index);
    GET_GICV3_REG(ICC_HPPIR1_EL1, irq);

    return irq;
}

rt_uint64_t arm_gic_get_interface_id(rt_uint64_t index)
{
    rt_uint64_t ret = 0;
    rt_base_t level;
    int cpuid;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    level = rt_hw_local_irq_disable();
    cpuid = rt_hw_cpu_id();
    if (_gic_table[index].cpu_hw_base[cpuid] != RT_NULL)
    {
        ret = GIC_CPU_IIDR(_gic_table[index].cpu_hw_base[cpuid]);
    }
    rt_hw_local_irq_enable(level);

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
    SET_GICV3_REG(ICC_CTLR_EL1, 0l);

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

rt_uint64_t *arm_gic_get_gic_table_addr(void)
{
    return (rt_uint64_t *)&_gic_table[0];
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

#endif /* defined(BSP_USING_GIC) && defined(BSP_USING_GICV3) */
