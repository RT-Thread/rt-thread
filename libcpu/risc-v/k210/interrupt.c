/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 */

#include <rthw.h>

#include "tick.h"

#include <plic.h>
#include <clint.h>
#include <interrupt.h>

#define CPU_NUM         2
#define MAX_HANDLERS    IRQN_MAX

static struct rt_irq_desc irq_desc[CPU_NUM][MAX_HANDLERS];

static rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", vector);
    return RT_NULL;
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
        irq_desc[cpuid][idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[cpuid][idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[cpuid][idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx][cpuid].counter = 0;
#endif
    }

    /* Enable machine external interrupts. */
    set_csr(mie, MIP_MEIP);
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    plic_irq_disable(vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    plic_set_priority(vector, 1);
    plic_irq_enable(vector);
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
    int cpuid;
    rt_isr_handler_t old_handler = RT_NULL;

    cpuid = current_coreid();

    if(vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[cpuid][vector].handler;
        if (handler != RT_NULL)
        {
            irq_desc[cpuid][vector].handler = (rt_isr_handler_t)handler;
            irq_desc[cpuid][vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[cpuid][vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[cpuid][vector].counter = 0;
#endif
        }
    }

    return old_handler;
}

uintptr_t handle_irq_m_ext(uintptr_t cause, uintptr_t epc)
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

        if (irq_desc[core_id][int_num].handler)
        {
            irq_desc[core_id][int_num].handler(int_num, irq_desc[core_id][int_num].param);
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
    else
    {
        rt_kprintf("unhandled trap!\n");
    }

    return epc;
}

uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
{
    int cause = mcause & CAUSE_MACHINE_IRQ_REASON_MASK;

    if (mcause & (1UL << 63))
    {
        switch (cause)
        {
            case IRQ_M_SOFT:
                break;
            case IRQ_M_EXT:
                handle_irq_m_ext(mcause, epc);
                break;
            case IRQ_M_TIMER:
                tick_isr();
                break;
        }
    }
    else
    {
        rt_thread_t tid;
        extern long list_thread();

        rt_hw_interrupt_disable();

        tid = rt_thread_self();
        rt_kprintf("\n");
        rt_kprintf("unhandled trap, epc => 0x%08x, INT[%d]\n", epc, rt_interrupt_get_nest());
        rt_kprintf("current thread: %.*s\n", RT_NAME_MAX, tid->name);
#ifdef RT_USING_FINSH
        list_thread();
#endif
        while(1);
    }

    return epc;
}
