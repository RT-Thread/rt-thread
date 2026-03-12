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

#include "gic.h"
#include "cp15.h"

struct arm_gic
{
    rt_uint32_t offset;         /* the first interrupt index in the vector table */

    rt_uint32_t dist_hw_base;   /* the base address of the gic distributor */
    rt_uint32_t cpu_hw_base;    /* the base addrees of the gic cpu interface */
};

static struct arm_gic _gic_table[ARM_GIC_MAX_NR];

/** Macro to access the Generic Interrupt Controller Interface (GICC)
*/
#define GIC_CPU_CTRL(hw_base)               __REG32((hw_base) + 0x00U)  /* GICC_CTLR  */
#define GIC_CPU_PRIMASK(hw_base)            __REG32((hw_base) + 0x04U)  /* GICC_PMR   */
#define GIC_CPU_BINPOINT(hw_base)           __REG32((hw_base) + 0x08U)  /* GICC_BPR   */
#define GIC_CPU_INTACK(hw_base)             __REG32((hw_base) + 0x0cU)  /* GICC_IAR   */
#define GIC_CPU_EOI(hw_base)                __REG32((hw_base) + 0x10U)  /* GICC_EOIR  */
#define GIC_CPU_RUNNINGPRI(hw_base)         __REG32((hw_base) + 0x14U)  /* GICC_RPR   */
#define GIC_CPU_HIGHPRI(hw_base)            __REG32((hw_base) + 0x18U)  /* GICC_HPPIR */
#define GIC_CPU_IIDR(hw_base)               __REG32((hw_base) + 0xFCU)  /* GICC_IIDR  */

/** Macro to access the Generic Interrupt Controller Distributor (GICD)
*/
#define GIC_DIST_CTRL(hw_base)              __REG32((hw_base) + 0x000U)                     /* GICD_CTLR        */
#define GIC_DIST_TYPE(hw_base)              __REG32((hw_base) + 0x004U)                     /* GICD_TYPER       */
#define GIC_DIST_IGROUP(hw_base, n)         __REG32((hw_base) + 0x080U + ((n)/32U) * 4U)    /* GICD_IGROUPRn    */
#define GIC_DIST_ENABLE_SET(hw_base, n)     __REG32((hw_base) + 0x100U + ((n)/32U) * 4U)    /* GICD_ISENABLERn  */
#define GIC_DIST_ENABLE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x180U + ((n)/32U) * 4U)    /* GICD_ICENABLERn  */
#define GIC_DIST_PENDING_SET(hw_base, n)    __REG32((hw_base) + 0x200U + ((n)/32U) * 4U)    /* GICD_ISPENDRn    */
#define GIC_DIST_PENDING_CLEAR(hw_base, n)  __REG32((hw_base) + 0x280U + ((n)/32U) * 4U)    /* GICD_ICPENDRn    */
#define GIC_DIST_ACTIVE_SET(hw_base, n)     __REG32((hw_base) + 0x300U + ((n)/32U) * 4U)    /* GICD_ISACTIVERn  */
#define GIC_DIST_ACTIVE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x380U + ((n)/32U) * 4U)    /* GICD_ICACTIVERn  */
#define GIC_DIST_PRI(hw_base, n)            __REG32((hw_base) + 0x400U +  ((n)/4U) * 4U)    /* GICD_IPRIORITYRn */
#define GIC_DIST_TARGET(hw_base, n)         __REG32((hw_base) + 0x800U +  ((n)/4U) * 4U)    /* GICD_ITARGETSRn  */
#define GIC_DIST_CONFIG(hw_base, n)         __REG32((hw_base) + 0xc00U + ((n)/16U) * 4U)    /* GICD_ICFGRn      */
#define GIC_DIST_SOFTINT(hw_base)           __REG32((hw_base) + 0xf00U)                     /* GICD_SGIR        */
#define GIC_DIST_CPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf10U + ((n)/4U) * 4U)     /* GICD_CPENDSGIRn  */
#define GIC_DIST_SPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf20U + ((n)/4U) * 4U)     /* GICD_SPENDSGIRn  */
#define GIC_DIST_ICPIDR2(hw_base)           __REG32((hw_base) + 0xfe8U)                     /* ICPIDR2          */

static unsigned int _gic_max_irq;

/**
 * @brief Get the active interrupt number
 *
 * @note Read the GICC_IAR register and add the interrupt number offset to get
 *       the actual interrupt number.
 *       This read acts as an acknowledge for the interrupt, changing the interrupt
 *       state from pending to active.
 *
 *       GICC_IAR register bit fields:
 *       - GICC_IAR[31:13]: Reserved, read as 0
 *       - GICC_IAR[12:10]: CPUID
 *                          For SGIs: This value is the CPUID that requested the interrupt.
 *                          For other interrupts: This value reads as 0 (RAZ).
 *       - GICC_IAR[9:0]:  Interrupt ID
 *
 * @param index GIC controller index
 *
 * @return The actual interrupt number (with offset added).
 *         Note: For SGIs, the return value may include CPUID information in the upper bits.
 */
int arm_gic_get_active_irq(rt_uint32_t index)
{
    int irq;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = GIC_CPU_INTACK(_gic_table[index].cpu_hw_base);
    irq += _gic_table[index].offset;
    return irq;
}

/**
 * @brief Acknowledge and end the interrupt
 *
 * @note This function completes the interrupt handling by:
 *       1. Clearing the pending status of the interrupt in the Distributor (GICD_ICPENDRn).
 *       2. Writing the interrupt ID to the End of Interrupt Register (GICC_EOIR).
 *          This signals the GIC that interrupt processing is complete and changes
 *          the interrupt state from active to inactive.
 *
 *       This function should be called after the interrupt handler has finished
 *       processing the interrupt, typically at the end of the interrupt service routine.
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number (with offset) to acknowledge
 */
void arm_gic_ack(rt_uint32_t index, int irq)
{
    rt_uint32_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_PENDING_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
    GIC_CPU_EOI(_gic_table[index].cpu_hw_base) = irq;
}

/**
 * @brief Disable the forwarding of the corresponding interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 */
void arm_gic_mask(rt_uint32_t index, int irq)
{
    rt_uint32_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_ENABLE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}

/**
 * @brief Enables the forwarding of the corresponding interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 */
void arm_gic_umask(rt_uint32_t index, int irq)
{
    rt_uint32_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_ENABLE_SET(_gic_table[index].dist_hw_base, irq) = mask; /* GICD_ISENABLERn */
}

/**
 * @brief Identifies whether the interrupt is pending
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 *
 * @return 0: not pending, 1: pending
 */
rt_uint32_t arm_gic_get_pending_irq(rt_uint32_t index, int irq)
{
    rt_uint32_t pend;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    if (irq >= 16U)
    {
        pend = (GIC_DIST_PENDING_SET(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;      /* GICD_ISPENDRn */
    }
    else
    {
        /* INTID 0-15 Software Generated Interrupt */
        pend = (GIC_DIST_SPENDSGI(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;  /* GICD_SPENDSGIRn */
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

/**
 * @brief Set the interrupt as pending
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 */
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

/**
 * @brief clears the pending state of the interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 */
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
        mask =  1U << ((irq % 4U) * 8U);
        GIC_DIST_CPENDSGI(_gic_table[index].dist_hw_base, irq) = mask;
    }
}

/**
 * @brief Configure whether the corresponding interrupt is edge-triggered or level-sensitive
 *
 * @note  For SGIs (interrupt IDs 0-15), the Int_config fields are read-only,
 *        meaning that GICD_ICFGR0 is read-only. Writing to this register for SGIs
 *        will have no effect.
 *
 *        For PPIs (interrupt IDs 16-31), it is IMPLEMENTATION DEFINED whether
 *        the most significant bit of the Int_config field is programmable.
 *        Some implementations may make PPI configuration registers read-only.
 *
 *        This function is primarily intended for configuring SPIs (interrupt IDs 32+),
 *        which have fully programmable configuration registers.
 *
 * @param index  GIC controller index
 * @param irq    The actual interrupt number (with offset)
 * @param config 0: level-sensitive, 1: edge-triggered
 */
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
    icfgr |= (config << (shift + 1));

    GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) = icfgr;
}

/**
 * @brief Identifies whether the corresponding interrupt is edge-triggered or level-sensitive
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 *
 * @return 0: level-sensitive, 1: edge-triggered
 */
rt_uint32_t arm_gic_get_configuration(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_CONFIG(_gic_table[index].dist_hw_base, irq) >> ((irq % 16U) >> 1U));
}

/**
 * @brief Deactivates the corresponding interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 */
void arm_gic_clear_active(rt_uint32_t index, int irq)
{
    rt_uint32_t mask = 1U << (irq % 32U);

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_ACTIVE_CLEAR(_gic_table[index].dist_hw_base, irq) = mask;
}

/**
 * @brief Set up the cpu mask for the specific interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 *
 * @param cpumask CPU targets. Only the lower 8 bits are valid (bits [7:0]).
 */
void arm_gic_set_cpu(rt_uint32_t index, int irq, unsigned int cpumask)
{
    rt_uint32_t old_tgt;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    old_tgt = GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq);

    old_tgt &= ~(0x0FFUL << ((irq % 4U)*8U));
    old_tgt |= cpumask << ((irq % 4U)*8U);

    GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) = old_tgt;
}

/**
 * @brief Get the CPU targets for the specific interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 *
 * @return CPU targets
 */
rt_uint32_t arm_gic_get_target_cpu(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_TARGET(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
}

/**
 * @brief Set the priority for the specific interrupt
 *
 * @note The lower the value, the greater the priority of the corresponding interrupt.
 *
 * @param index    GIC controller index
 * @param irq      The actual interrupt number (with offset)
 * @param priority The priority to set.Only the lower 8 bits are valid (bits [7:0]).
 */
void arm_gic_set_priority(rt_uint32_t index, int irq, rt_uint32_t priority)
{
    rt_uint32_t mask;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    mask = GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq);
    mask &= ~(0xFFUL << ((irq % 4U) * 8U));
    mask |= ((priority & 0xFFUL) << ((irq % 4U) * 8U));
    GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) = mask;
}


/**
 * @brief Get the priority for the specific interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number(with offset)
 *
 * @return The priority of the corresponding interrupt.Only the lower 8 bits are valid (bits [7:0]).
 */
rt_uint32_t arm_gic_get_priority(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_PRI(_gic_table[index].dist_hw_base, irq) >> ((irq % 4U) * 8U)) & 0xFFUL;
}

/**
 * @brief Set the priority mask for the specific CPU
 *
 * @note Only interrupts with higher priority than the value in this
 *       register are signaled to the processor.
 *
 * @param index    GIC controller index
 * @param priority The priority mask to set.Only the lower 8 bits are valid (bits [7:0]).
 */
void arm_gic_set_interface_prior_mask(rt_uint32_t index, rt_uint32_t priority)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    /* set priority mask */
    GIC_CPU_PRIMASK(_gic_table[index].cpu_hw_base) = priority & 0xFFUL;
}

/**
 * @brief Get the priority mask for the specific CPU
 *
 * @param index GIC controller index
 *
 * @return The priority mask to return. Only the lower 8 bits are valid (bits [7:0]).
 */
rt_uint32_t arm_gic_get_interface_prior_mask(rt_uint32_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    return GIC_CPU_PRIMASK(_gic_table[index].cpu_hw_base);
}

/**
 * @brief Set the binary point value for interrupt priority splitting
 *
 * @note This function sets the GICC_BPR (Binary Point Register) value, which is used
 *       to split the priority field into group priority and subpriority fields.
 *       The binary point determines how many bits are used for group priority:
 *       - A larger value results in fewer bits for group priority,
 *         reducing interrupt preemption capability.
 *       - A smaller value results in more bits for group priority,
 *         increasing interrupt preemption capability.
 *       - Only the lower 3 bits are valid (bits [2:0], range 0-7).
 *
 * @param index        GIC controller index
 * @param binary_point Binary point value. Only the lower 3 bits are valid (bits [2:0]).
 */
void arm_gic_set_binary_point(rt_uint32_t index, rt_uint32_t binary_point)
{
    GIC_CPU_BINPOINT(_gic_table[index].cpu_hw_base) = binary_point & 0x7U;
}

/**
 * @brief Get the binary point value for interrupt priority splitting
 *
 * @param index GIC controller index
 * @return      Binary point value. Only the lower 3 bits are valid (bits [2:0]).
 */
rt_uint32_t arm_gic_get_binary_point(rt_uint32_t index)
{
    return GIC_CPU_BINPOINT(_gic_table[index].cpu_hw_base);
}

/**
 * @brief Get the status of the specified interrupt
 *
 * @note This function reads both the active and pending status of the interrupt
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number (with offset)
 *
 * @return Encoded interrupt status:
 *         - Bit 0: Pending status
 *         - Bit 1: Active status
 */
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

/**
 * @brief Send a Software Generated Interrupt (SGI) to specified CPU(s)
 *
 * @note This function writes to the GICD_SGIR (Software Generated Interrupt Register)
 *       to generate an SGI. The register value is constructed as follows:
 *       - Bits [25:24]: TargetListFilter - determines how the SGI is forwarded
 *         * 0b00: Forward to CPUs specified in CPUTargetList
 *         * 0b01: Forward to all CPUs except the requesting CPU
 *         * 0b10: Forward only to the requesting CPU
 *         * 0b11: Reserved
 *       - Bits [23:16]: CPUTargetList - 8-bit mask specifying target CPUs
 *         (only used when TargetListFilter = 0b00)
 *         * Each bit represents a CPU: bit 0 = CPU 0, bit 1 = CPU 1, etc.
 *       - Bits [3:0]: SGIINTID - the SGI interrupt ID (0-15)
 *
 * @param index       GIC controller index
 * @param irq         The actual interrupt number (with offset).
 * @param target_list CPU target mask. Only the lower 8 bits are valid (bits [7:0]).
 *                    Each bit represents a CPU. Used when filter_list = 0b00.
 * @param filter_list Target list filter mode. Only the lower 2 bits are valid (bits [1:0]).
 *                    Determines how the SGI is forwarded to CPUs.
 */
void arm_gic_send_sgi(rt_uint32_t index, int irq, rt_uint32_t target_list, rt_uint32_t filter_list)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    GIC_DIST_SOFTINT(_gic_table[index].dist_hw_base) = ((filter_list & 0x3U) << 24U) | ((target_list & 0xFFUL) << 16U) | (irq & 0x0FUL);
}

/**
 * @brief Get the highest priority pending interrupt ID without acknowledging it
 *
 * @note This function reads the GICC_HPPIR (Highest Priority Pending Interrupt Register)
 *       to get the interrupt ID of the highest priority pending interrupt.
 *
 *       Unlike reading GICC_IAR (via arm_gic_get_active_irq()), reading GICC_HPPIR
 *       does NOT acknowledge the interrupt. This means:
 *       - The interrupt state remains unchanged (still pending)
 *
 * @param index GIC controller index
 *
 * @return The 32-bit value read from the GICC_HPPIR register.
 *        The caller can extract specific fields (hardware interrupt ID without offset added).
 */
rt_uint32_t arm_gic_get_high_pending_irq(rt_uint32_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    return GIC_CPU_HIGHPRI(_gic_table[index].cpu_hw_base);
}

/**
 * @brief Get the CPU Interface Identification Register (GICC_IIDR) value
 *
 * @param index GIC controller index
 *
 * @return The 32-bit value read from the GICC_IIDR register.
 *         The caller can extract specific fields (implementer, product ID, revision, architecture version.)
 */
rt_uint32_t arm_gic_get_interface_id(rt_uint32_t index)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    return GIC_CPU_IIDR(_gic_table[index].cpu_hw_base);
}

/**
 * @brief Set the interrupt group for the specified interrupt
 *
 * @note This function configures the interrupt group in the GICD_IGROUPRn register.
 *       The interrupt group determines the security classification of the interrupt
 *       when the GIC implements Security Extensions:
 *       - Group 0 (group = 0): Secure interrupts, used for secure world
 *       - Group 1 (group = 1): Non-secure interrupts, used for non-secure world
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number (with offset)
 * @param group Interrupt group: 0 for Group 0 (secure), 1 for Group 1 (non-secure)
 */
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
    igroupr |= ( (group & 0x1U) << shift);

    GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq) = igroupr;
}

/**
 * @brief Get the interrupt group for the specified interrupt
 *
 * @note This function reads the interrupt group from the GICD_IGROUPRn register.
 *       The return value indicates which security group the interrupt belongs to:
 *       - 0: Group 0 (Secure interrupt)
 *       - 1: Group 1 (Non-secure interrupt)
 *
 * @param index GIC controller index
 * @param irq   The actual interrupt number (with offset)
 *
 * @return The interrupt group: 0 for Group 0 (secure), 1 for Group 1 (non-secure)
 */
rt_uint32_t arm_gic_get_group(rt_uint32_t index, int irq)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    irq = irq - _gic_table[index].offset;
    RT_ASSERT(irq >= 0U);

    return (GIC_DIST_IGROUP(_gic_table[index].dist_hw_base, irq) >> (irq % 32U)) & 0x1UL;
}

/**
 * @brief Initialize the GIC Distributor (GICD)
 *
 * @note: The exact bit definitions and behavior may vary depending on
 *        the GIC implementation (GICv1/GICv2) and security context.
 *
 *
 * @param index     GIC controller index
 * @param dist_base Base address of the GIC Distributor (GICD)
 * @param irq_start The first interrupt index offset in the vector table
 *
 * @return 0
 */
int arm_gic_dist_init(rt_uint32_t index, rt_uint32_t dist_base, int irq_start)
{
    unsigned int gic_type, i;
    rt_uint32_t cpumask = 1U << 0U;

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

    cpumask |= cpumask << 8U;
    cpumask |= cpumask << 16U;
    cpumask |= cpumask << 24U;

    GIC_DIST_CTRL(dist_base) = 0x0U;

    /* Set all global interrupts to be level triggered, active low. */
    for (i = 32U; i < _gic_max_irq; i += 16U)
        GIC_DIST_CONFIG(dist_base, i) = 0x0U;

    /* Set all global interrupts to this CPU only. */
    for (i = 32U; i < _gic_max_irq; i += 4U)
        GIC_DIST_TARGET(dist_base, i) = cpumask;

    /* Set priority on all interrupts. */
    for (i = 0U; i < _gic_max_irq; i += 4U)
        GIC_DIST_PRI(dist_base, i) = 0xa0a0a0a0U;

    /* Disable all interrupts. */
    for (i = 0U; i < _gic_max_irq; i += 32U)
        GIC_DIST_ENABLE_CLEAR(dist_base, i) = 0xffffffffU;

#if 0
    /* All interrupts defaults to IGROUP1(IRQ). */
    for (i = 0; i < _gic_max_irq; i += 32)
        GIC_DIST_IGROUP(dist_base, i) = 0xffffffff;
#endif
    for (i = 0U; i < _gic_max_irq; i += 32U)
        GIC_DIST_IGROUP(dist_base, i) = 0U;

    /* Enable group0 and group1 interrupt forwarding. */
    GIC_DIST_CTRL(dist_base) = 0x01U;

    return 0;
}

/**
 * @brief Initialize the GIC CPU Interface (GICC)
 *
 * @note: The exact bit definitions and behavior may vary depending on
 *        the GIC implementation (GICv1/GICv2) and security context.
 *
 * @param index    GIC controller index
 * @param cpu_base Base address of the GIC CPU Interface (GICC)
 *
 * @return 0
 */
int arm_gic_cpu_init(rt_uint32_t index, rt_uint32_t cpu_base)
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

/**
 * @brief Print the GIC information (version, base addr, max irq nums, security extension)
 *
 * @param index GIC controller index
 */
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

/**
 * @brief Print the GIC status (highest priority pending interrupt, enable status, pending status , active status)
 *
 * @param index
 */
void arm_gic_dump(rt_uint32_t index)
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

