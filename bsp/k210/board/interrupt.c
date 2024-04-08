/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 * 2018/12/27     Jesven       Change irq enable/disable to cpu0
 */

#include <rtthread.h>

#include "tick.h"

#include <plic.h>
#include <clint.h>
#include <interrupt.h>

#define CPU_NUM         2
#define MAX_HANDLERS    IRQN_MAX

static struct rt_irq_desc irq_desc[MAX_HANDLERS];

static rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", vector);
    return RT_NULL;
}

int rt_hw_clint_ipi_enable(void)
{
    /* Set the Machine-Software bit in MIE */
    set_csr(mie, MIP_MSIP);
    return 0;
}

int rt_hw_clint_ipi_disable(void)
{
    /* Clear the Machine-Software bit in MIE */
    clear_csr(mie, MIP_MSIP);
    return 0;
}

int rt_hw_plic_irq_enable(plic_irq_t irq_number)
{
    unsigned long core_id = 0;

    /* Check parameters */
    if (PLIC_NUM_SOURCES < irq_number || 0 > irq_number)
        return -1;
    /* Get current enable bit array by IRQ number */
    uint32_t current = plic->target_enables.target[core_id].enable[irq_number / 32];
    /* Set enable bit in enable bit array */
    current |= (uint32_t)1 << (irq_number % 32);
    /* Write back the enable bit array */
    plic->target_enables.target[core_id].enable[irq_number / 32] = current;
    return 0;
}

int rt_hw_plic_irq_disable(plic_irq_t irq_number)
{
    unsigned long core_id = 0;

    /* Check parameters */
    if (PLIC_NUM_SOURCES < irq_number || 0 > irq_number)
        return -1;
    /* Get current enable bit array by IRQ number */
    uint32_t current = plic->target_enables.target[core_id].enable[irq_number / 32];
    /* Clear enable bit in enable bit array */
    current &= ~((uint32_t)1 << (irq_number % 32));
    /* Write back the enable bit array */
    plic->target_enables.target[core_id].enable[irq_number / 32] = current;
    return 0;
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    int idx;
    int cpuid;

    cpuid = current_coreid();

    /* Disable all interrupts for the current core. */
    for (idx = 0; idx < ((PLIC_NUM_SOURCES + 32u) / 32u); idx ++)
        plic->target_enables.target[cpuid].enable[idx] = 0;

    /* Set priorities to zero. */
    for (idx = 0; idx < PLIC_NUM_SOURCES; idx++)
        plic->source_priorities.priority[idx] = 0;

    /* Set the threshold to zero. */
    plic->targets.target[cpuid].priority_threshold = 0;

    /* init exceptions table */
    for (idx = 0; idx < MAX_HANDLERS; idx++)
    {
        rt_hw_interrupt_mask(idx);
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif
    }

    /* Enable machine external interrupts. */
    set_csr(mie, MIP_MEIP);
}

void rt_hw_scondary_interrupt_init(void)
{
    int idx;
    int cpuid;

    cpuid = current_coreid();

    /* Disable all interrupts for the current core. */
    for (idx = 0; idx < ((PLIC_NUM_SOURCES + 32u) / 32u); idx ++)
        plic->target_enables.target[cpuid].enable[idx] = 0;

    /* Set the threshold to zero. */
    plic->targets.target[cpuid].priority_threshold = 0;

    /* Enable machine external interrupts. */
    set_csr(mie, MIP_MEIP);
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    rt_hw_plic_irq_disable(vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    plic_set_priority(vector, 1);
    rt_hw_plic_irq_enable(vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[vector].handler;
        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[vector].counter = 0;
#endif
        }
    }

    return old_handler;
}

static void plic_irq_handle(plic_irq_t irq)
{
    plic_instance_t (*plic_instance)[IRQN_MAX] = plic_get_instance();
    if (plic_instance[0][irq].callback)
    {
        plic_instance[0][irq].callback(
            plic_instance[0][irq].ctx);
    }
    else if (plic_instance[1][irq].callback)
    {
        plic_instance[1][irq].callback(
            plic_instance[1][irq].ctx);
    }
}

void rt_hw_soft_irq_isr(void)
{
    uint64_t core_id = current_coreid();

    clint_ipi_clear(core_id);
    rt_schedule();
}

void rt_hw_irq_isr(void)
{
    /*
     * After the highest-priority pending interrupt is claimed by a target
     * and the corresponding IP bit is cleared, other lower-priority
     * pending interrupts might then become visible to the target, and so
     * the PLIC EIP bit might not be cleared after a claim. The interrupt
     * handler can check the local meip/heip/seip/ueip bits before exiting
     * the handler, to allow more efficient service of other interrupts
     * without first restoring the interrupted context and taking another
     * interrupt trap.
     */
    if (read_csr(mip) & MIP_MEIP)
    {
        /* Get current core id */
        uint64_t core_id = current_coreid();
        /* Get primitive interrupt enable flag */
        uint64_t ie_flag = read_csr(mie);
        /* Get current IRQ num */
        uint32_t int_num = plic->targets.target[core_id].claim_complete;
        /* Get primitive IRQ threshold */
        uint32_t int_threshold = plic->targets.target[core_id].priority_threshold;
        /* Set new IRQ threshold = current IRQ threshold */
        plic->targets.target[core_id].priority_threshold = plic->source_priorities.priority[int_num];

        /* Disable software interrupt and timer interrupt */
        clear_csr(mie, MIP_MTIP | MIP_MSIP);

        if (irq_desc[int_num].handler == (rt_isr_handler_t)rt_hw_interrupt_handle)
        {
            /* default handler, route to kendryte bsp plic driver */
            plic_irq_handle(int_num);
        }
        else if (irq_desc[int_num].handler)
        {
            irq_desc[int_num].handler(int_num, irq_desc[int_num].param);
        }

        /* Perform IRQ complete */
        plic->targets.target[core_id].claim_complete = int_num;
        /* Set MPIE and MPP flag used to MRET instructions restore MIE flag */
        set_csr(mstatus, MSTATUS_MPIE | MSTATUS_MPP);
        /* Restore primitive interrupt enable flag */
        write_csr(mie, ie_flag);
        /* Restore primitive IRQ threshold */
        plic->targets.target[core_id].priority_threshold = int_threshold;
    }
}

