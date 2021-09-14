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

#include <rthw.h>

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

RT_WEAK
void plic_irq_handle(plic_irq_t irq)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", irq);
    return ;
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

    return epc;
}
struct exception_stack_frame
{
    uint64_t x1;
    uint64_t x2;
    uint64_t x3;
    uint64_t x4;
    uint64_t x5;
    uint64_t x6;
    uint64_t x7;
    uint64_t x8;
    uint64_t x9;
    uint64_t x10;
    uint64_t x11;
    uint64_t x12;
    uint64_t x13;
    uint64_t x14;
    uint64_t x15;
    uint64_t x16;
    uint64_t x17;
    uint64_t x18;
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t x29;
    uint64_t x30;
    uint64_t x31;
};

void print_stack_frame(uintptr_t * sp)
{
    struct exception_stack_frame * esf = (struct exception_stack_frame *)(sp+1);

    rt_kprintf("\n=================================================================\n");
    rt_kprintf("x1 (ra   : Return address                ) ==> 0x%08x%08x\n", esf->x1 >> 32  , esf->x1 & UINT32_MAX);
    rt_kprintf("x2 (sp   : Stack pointer                 ) ==> 0x%08x%08x\n", esf->x2 >> 32  , esf->x2 & UINT32_MAX);
    rt_kprintf("x3 (gp   : Global pointer                ) ==> 0x%08x%08x\n", esf->x3 >> 32  , esf->x3 & UINT32_MAX);
    rt_kprintf("x4 (tp   : Thread pointer                ) ==> 0x%08x%08x\n", esf->x4 >> 32  , esf->x4 & UINT32_MAX);
    rt_kprintf("x5 (t0   : Temporary                     ) ==> 0x%08x%08x\n", esf->x5 >> 32  , esf->x5 & UINT32_MAX);
    rt_kprintf("x6 (t1   : Temporary                     ) ==> 0x%08x%08x\n", esf->x6 >> 32  , esf->x6 & UINT32_MAX);
    rt_kprintf("x7 (t2   : Temporary                     ) ==> 0x%08x%08x\n", esf->x7 >> 32  , esf->x7 & UINT32_MAX);
    rt_kprintf("x8 (s0/fp: Save register,frame pointer   ) ==> 0x%08x%08x\n", esf->x8 >> 32  , esf->x8 & UINT32_MAX);
    rt_kprintf("x9 (s1   : Save register                 ) ==> 0x%08x%08x\n", esf->x9 >> 32  , esf->x9 & UINT32_MAX);
    rt_kprintf("x10(a0   : Function argument,return value) ==> 0x%08x%08x\n", esf->x10 >> 32 , esf->x10 & UINT32_MAX);
    rt_kprintf("x11(a1   : Function argument,return value) ==> 0x%08x%08x\n", esf->x11 >> 32 , esf->x11 & UINT32_MAX);
    rt_kprintf("x12(a2   : Function argument             ) ==> 0x%08x%08x\n", esf->x12 >> 32 , esf->x12 & UINT32_MAX);
    rt_kprintf("x13(a3   : Function argument             ) ==> 0x%08x%08x\n", esf->x13 >> 32 , esf->x13 & UINT32_MAX);
    rt_kprintf("x14(a4   : Function argument             ) ==> 0x%08x%08x\n", esf->x14 >> 32 , esf->x14 & UINT32_MAX);
    rt_kprintf("x15(a5   : Function argument             ) ==> 0x%08x%08x\n", esf->x15 >> 32 , esf->x15 & UINT32_MAX);
    rt_kprintf("x16(a6   : Function argument             ) ==> 0x%08x%08x\n", esf->x16 >> 32 , esf->x16 & UINT32_MAX);
    rt_kprintf("x17(a7   : Function argument             ) ==> 0x%08x%08x\n", esf->x17 >> 32 , esf->x17 & UINT32_MAX);
    rt_kprintf("x18(s2   : Save register                 ) ==> 0x%08x%08x\n", esf->x18 >> 32 , esf->x18 & UINT32_MAX);
    rt_kprintf("x19(s3   : Save register                 ) ==> 0x%08x%08x\n", esf->x19 >> 32 , esf->x19 & UINT32_MAX);
    rt_kprintf("x20(s4   : Save register                 ) ==> 0x%08x%08x\n", esf->x20 >> 32 , esf->x20 & UINT32_MAX);
    rt_kprintf("x21(s5   : Save register                 ) ==> 0x%08x%08x\n", esf->x21 >> 32 , esf->x21 & UINT32_MAX);
    rt_kprintf("x22(s6   : Save register                 ) ==> 0x%08x%08x\n", esf->x22 >> 32 , esf->x22 & UINT32_MAX);
    rt_kprintf("x23(s7   : Save register                 ) ==> 0x%08x%08x\n", esf->x23 >> 32 , esf->x23 & UINT32_MAX);
    rt_kprintf("x24(s8   : Save register                 ) ==> 0x%08x%08x\n", esf->x24 >> 32 , esf->x24 & UINT32_MAX);
    rt_kprintf("x25(s9   : Save register                 ) ==> 0x%08x%08x\n", esf->x25 >> 32 , esf->x25 & UINT32_MAX);
    rt_kprintf("x26(s10  : Save register                 ) ==> 0x%08x%08x\n", esf->x26 >> 32 , esf->x26 & UINT32_MAX);
    rt_kprintf("x27(s11  : Save register                 ) ==> 0x%08x%08x\n", esf->x27 >> 32 , esf->x27 & UINT32_MAX);
    rt_kprintf("x28(t3   : Temporary                     ) ==> 0x%08x%08x\n", esf->x28 >> 32 , esf->x28 & UINT32_MAX);
    rt_kprintf("x29(t4   : Temporary                     ) ==> 0x%08x%08x\n", esf->x29 >> 32 , esf->x29 & UINT32_MAX);
    rt_kprintf("x30(t5   : Temporary                     ) ==> 0x%08x%08x\n", esf->x30 >> 32 , esf->x30 & UINT32_MAX);
    rt_kprintf("x31(t6   : Temporary                     ) ==> 0x%08x%08x\n", esf->x31 >> 32 , esf->x31 & UINT32_MAX);
    rt_kprintf("=================================================================\n");
}


uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc, uintptr_t * sp)
{
    int cause = mcause & CAUSE_MACHINE_IRQ_REASON_MASK;

    if (mcause & (1UL << 63))
    {
        switch (cause)
        {
            case IRQ_M_SOFT:
                {
                    uint64_t core_id = current_coreid();

                    clint_ipi_clear(core_id);
                    rt_schedule();
                }
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
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        extern long list_thread();
#endif

        rt_hw_interrupt_disable();

        tid = rt_thread_self();
        rt_kprintf("\nException:\n");
        switch (cause)
        {
            case CAUSE_MISALIGNED_FETCH:
                rt_kprintf("Instruction address misaligned");
                break;
            case CAUSE_FAULT_FETCH:
                rt_kprintf("Instruction access fault");
                break;
            case CAUSE_ILLEGAL_INSTRUCTION:
                rt_kprintf("Illegal instruction");
                break;
            case CAUSE_BREAKPOINT:
                rt_kprintf("Breakpoint");
                break;
            case CAUSE_MISALIGNED_LOAD:
                rt_kprintf("Load address misaligned");
                break;
            case CAUSE_FAULT_LOAD:
                rt_kprintf("Load access fault");
                break;
            case CAUSE_MISALIGNED_STORE:
                rt_kprintf("Store address misaligned");
                break;
            case CAUSE_FAULT_STORE:
                rt_kprintf("Store access fault");
                break;
            case CAUSE_USER_ECALL:
                rt_kprintf("Environment call from U-mode");
                break;
            case CAUSE_SUPERVISOR_ECALL:
                rt_kprintf("Environment call from S-mode");
                break;
            case CAUSE_HYPERVISOR_ECALL:
                rt_kprintf("Environment call from H-mode");
                break;
            case CAUSE_MACHINE_ECALL:
                rt_kprintf("Environment call from M-mode");
                break;
            default:
                rt_kprintf("Uknown exception : %08lX", cause);
                break;
        }
        rt_kprintf("\n");
        print_stack_frame(sp);
        rt_kprintf("exception pc => 0x%08x\n", epc);
        rt_kprintf("current thread: %.*s\n", RT_NAME_MAX, tid->name);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        list_thread();
#endif
        while(1);
    }

    return epc;
}
