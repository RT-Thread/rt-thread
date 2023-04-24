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

#if defined(BSP_USING_GIC) && defined(BSP_USING_GICV2)

#include "gic.h"
#include "cp15.h"

struct arm_gic
{
    rt_uint64_t offset;         /* the first interrupt index in the vector table */

    rt_uint64_t dist_hw_base;   /* the base address of the gic distributor */
    rt_uint64_t cpu_hw_base;    /* the base addrees of the gic cpu interface */
};

/* 'ARM_GIC_MAX_NR' is the number of cores */
static struct arm_gic _gic_table[ARM_GIC_MAX_NR];

/** Macro to access the Generic Interrupt Controller Interface (GICC)
*/
#define GIC_CPU_CTRL(hw_base)               __REG32((hw_base) + 0x00U)
#define GIC_CPU_PRIMASK(hw_base)            __REG32((hw_base) + 0x04U)
#define GIC_CPU_BINPOINT(hw_base)           __REG32((hw_base) + 0x08U)
#define GIC_CPU_INTACK(hw_base)             __REG32((hw_base) + 0x0cU)
#define GIC_CPU_EOI(hw_base)                __REG32((hw_base) + 0x10U)
#define GIC_CPU_RUNNINGPRI(hw_base)         __REG32((hw_base) + 0x14U)
#define GIC_CPU_HIGHPRI(hw_base)            __REG32((hw_base) + 0x18U)
#define GIC_CPU_IIDR(hw_base)               __REG32((hw_base) + 0xFCU)

/** Macro to access the Generic Interrupt Controller Distributor (GICD)
*/
#define GIC_DIST_CTRL(hw_base)              __REG32((hw_base) + 0x000U)
#define GIC_DIST_TYPE(hw_base)              __REG32((hw_base) + 0x004U)
#define GIC_DIST_IGROUP(hw_base, n)         __REG32((hw_base) + 0x080U + ((n)/32U) * 4U)
#define GIC_DIST_ENABLE_SET(hw_base, n)     __REG32((hw_base) + 0x100U + ((n)/32U) * 4U)
#define GIC_DIST_ENABLE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x180U + ((n)/32U) * 4U)
#define GIC_DIST_PENDING_SET(hw_base, n)    __REG32((hw_base) + 0x200U + ((n)/32U) * 4U)
#define GIC_DIST_PENDING_CLEAR(hw_base, n)  __REG32((hw_base) + 0x280U + ((n)/32U) * 4U)
#define GIC_DIST_ACTIVE_SET(hw_base, n)     __REG32((hw_base) + 0x300U + ((n)/32U) * 4U)
#define GIC_DIST_ACTIVE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x380U + ((n)/32U) * 4U)
#define GIC_DIST_PRI(hw_base, n)            __REG32((hw_base) + 0x400U +  ((n)/4U) * 4U)
#define GIC_DIST_TARGET(hw_base, n)         __REG32((hw_base) + 0x800U +  ((n)/4U) * 4U)
#define GIC_DIST_CONFIG(hw_base, n)         __REG32((hw_base) + 0xc00U + ((n)/16U) * 4U)
#define GIC_DIST_SOFTINT(hw_base)           __REG32((hw_base) + 0xf00U)
#define GIC_DIST_CPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf10U + ((n)/4U) * 4U)
#define GIC_DIST_SPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf20U + ((n)/4U) * 4U)
#define GIC_DIST_ICPIDR2(hw_base)           __REG32((hw_base) + 0xfe8U)

static unsigned int _gic_max_irq;

int arm_gic_get_active_irq(rt_uint64_t index)
{
    int irq;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = GIC_CPU_INTACK(_gic_table[index].cpu_hw_base);
    irq += _gic_table[index].offset;
    return irq;
}

void arm_gic_ack(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_PENDING_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
    GIC_CPU_EOI(_gic_table[index].cpu_hw_base) = irq;
}

void arm_gic_mask(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_ENABLE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}

void arm_gic_umask(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_ENABLE_SET(_gic_table[index].dist_hw_base, irq) = mask;
}

rt_uint64_t arm_gic_get_pending_irq(rt_uint64_t index, int irq)
{
    rt_uint64_t pend;

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

void arm_gic_set_pending_irq(rt_uint64_t index, int irq)
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

void arm_gic_clear_pending_irq(rt_uint64_t index, int irq)
{
    rt_uint64_t mask;

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
        mask =  1U << ((irq % 4U) * 8U);
        GIC_DIST_CPENDSGI(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

void arm_gic_set_configuration(rt_uint64_t index, int irq, uint32_t config)
{
    rt_uint64_t icfgr;
    rt_uint64_t shift;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    icfgr = GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq);
    shift = (irq % 16U) << 1U;

    icfgr &= (~(3U << shift));
    icfgr |= (config << (shift + 1));

    GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) = icfgr;
}

rt_uint64_t arm_gic_get_configuration(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) >> ((irq % 16U) >> 1U));
}

void arm_gic_clear_active(rt_uint64_t index, int irq)
{
    rt_uint64_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_ACTIVE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}

/* Set up the cpu mask for the specific interrupt */
void arm_gic_set_cpu(rt_uint64_t index, int irq, unsigned int cpumask)
{
    rt_uint64_t old_tgt;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    old_tgt = GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq);

    old_tgt &= ~(0x0FFUL << ((irq % 4U)*8U));
    old_tgt |= cpumask << ((irq % 4U)*8U);

    GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) = old_tgt;
}

rt_uint64_t arm_gic_get_target_cpu(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
}

void arm_gic_set_priority(rt_uint64_t index, int irq, rt_uint64_t priority)
{
    rt_uint64_t mask;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    mask = GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq);
    mask &= ~(0xFFUL << ((irq % 4U) * 8U));
    mask |= ((priority & 0xFFUL) << ((irq % 4U) * 8U));
    GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) = mask;
}

rt_uint64_t arm_gic_get_priority(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
}

void arm_gic_set_interface_prior_mask(rt_uint64_t index, rt_uint64_t priority)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    /* set priority mask */
    GIC_CPU_PRIMASK(_gic_table[index].cpu_hw_base) = priority & 0xFFUL;
}

rt_uint64_t arm_gic_get_interface_prior_mask(rt_uint64_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    return GIC_CPU_PRIMASK(_gic_table[index].cpu_hw_base);
}

void arm_gic_set_binary_point(rt_uint64_t index, rt_uint64_t binary_point)
{
    GIC_CPU_BINPOINT(_gic_table[index].cpu_hw_base) = binary_point & 0x7U;
}

rt_uint64_t arm_gic_get_binary_point(rt_uint64_t index)
{
    return GIC_CPU_BINPOINT(_gic_table[index].cpu_hw_base);
}

rt_uint64_t arm_gic_get_irq_status(rt_uint64_t index, int irq)
{
    rt_uint64_t pending;
    rt_uint64_t active;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    active = (GIC_DIST_ACTIVE_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;
    pending = (GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;

    return ((active << 1U) | pending);
}

void arm_gic_send_sgi(rt_uint64_t index, int irq, rt_uint64_t target_list, rt_uint64_t filter_list)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_SOFTINT(_gic_table[index].dist_hw_base) =
        ((filter_list & 0x3U) << 24U) | ((target_list & 0xFFUL) << 16U) | (irq & 0x0FUL);
}

rt_uint64_t arm_gic_get_high_pending_irq(rt_uint64_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    return GIC_CPU_HIGHPRI(_gic_table[index].cpu_hw_base);
}

rt_uint64_t arm_gic_get_interface_id(rt_uint64_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    return GIC_CPU_IIDR(_gic_table[index].cpu_hw_base);
}

void arm_gic_set_group(rt_uint64_t index, int irq, rt_uint64_t group)
{
    uint32_t igroupr;
    uint32_t shift;

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

rt_uint64_t arm_gic_get_group(rt_uint64_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;
}

int arm_gic_dist_init(rt_uint64_t index, rt_uint64_t dist_base, int irq_start)
{
    unsigned int gic_type, i;
    rt_uint64_t cpumask = 1U << 0U;

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
    {
        _gic_max_irq = 1020U;
    }
    if (_gic_max_irq > ARM_GIC_NR_IRQS) /* the platform maximum interrupts */
    {
        _gic_max_irq = ARM_GIC_NR_IRQS;
    }

    cpumask |= cpumask << 8U;
    cpumask |= cpumask << 16U;
    cpumask |= cpumask << 24U;

    GIC_DIST_CTRL(dist_base) = 0x0U;

    /* Set all global interrupts to be level triggered, active low. */
    for (i = 32U; i < _gic_max_irq; i += 16U)
    {
        GIC_DIST_CONFIG(dist_base, i) = 0x0U;
    }

    /* Set all global interrupts to this CPU only. */
    for (i = 32U; i < _gic_max_irq; i += 4U)
    {
        GIC_DIST_TARGET(dist_base, i) = cpumask;
    }

    /* Set priority on all interrupts. */
    for (i = 0U; i < _gic_max_irq; i += 4U)
    {
        GIC_DIST_PRI(dist_base, i) = 0xa0a0a0a0U;
    }

    /* Disable all interrupts. */
    for (i = 0U; i < _gic_max_irq; i += 32U)
    {
        GIC_DIST_ENABLE_CLEAR(dist_base, i) = 0xffffffffU;
    }

    /* All interrupts defaults to IGROUP1(IRQ). */
    /*
    for (i = 0; i < _gic_max_irq; i += 32)
    {
        GIC_DIST_IGROUP(dist_base, i) = 0xffffffffU;
    }
    */
    for (i = 0U; i < _gic_max_irq; i += 32U)
    {
        GIC_DIST_IGROUP(dist_base, i) = 0U;
    }

    /* Enable group0 and group1 interrupt forwarding. */
    GIC_DIST_CTRL(dist_base) = 0x01U;

    return 0;
}

int arm_gic_cpu_init(rt_uint64_t index, rt_uint64_t cpu_base)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (!_gic_table[index].cpu_hw_base)
    {
        _gic_table[index].cpu_hw_base = cpu_base;
    }
    cpu_base = _gic_table[index].cpu_hw_base;

    GIC_CPU_PRIMASK(cpu_base) = 0xf0U;
    GIC_CPU_BINPOINT(cpu_base) = 0x7U;
    /* Enable CPU interrupt */
    GIC_CPU_CTRL(cpu_base) = 0x01U;

    return 0;
}

void arm_gic_dump_type(rt_uint64_t index)
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

void arm_gic_dump(rt_uint64_t index)
{
    unsigned int i, k;

    k = GIC_CPU_HIGHPRI(_gic_table[index].cpu_hw_base);
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

#endif /* defined(BSP_USING_GIC) && defined(BSP_USING_GICV2) */
