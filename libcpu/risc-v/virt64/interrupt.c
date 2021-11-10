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
#include "tick.h"
#include <plic.h>
#include "encoding.h"
#include "riscv.h"
#include "interrupt.h"

#define MAX_HANDLERS    128

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

int rt_hw_plic_irq_enable(int irq_number)
{
    plic_irq_enable(irq_number);
    return 0;
}

int rt_hw_plic_irq_disable(int irq_number)
{
    plic_irq_disable(irq_number);
    return 0;
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    int idx = 0;
    /* init exceptions table */
    for (idx = 0; idx < MAX_HANDLERS; idx++)
    {
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif
    }

    plic_set_threshold(0);
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
void plic_irq_handle(int irq)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", irq);
    return ;
}

void dump_regs(struct rt_hw_stack_frame *regs)
{
    rt_kprintf("--------------Dump Registers-----------------\n");

    rt_kprintf("Function Registers:\n");
    rt_kprintf("\tra(x1) = 0x%p\tuser_sp = 0x%p\n",regs -> ra,regs -> user_sp_exc_stack);
    rt_kprintf("\tgp(x3) = 0x%p\ttp(x4) = 0x%p\n",regs -> gp,regs -> tp);
    rt_kprintf("Temporary Registers:\n");
    rt_kprintf("\tt0(x5) = 0x%p\tt1(x6) = 0x%p\n",regs -> t0,regs -> t1);
    rt_kprintf("\tt2(x7) = 0x%p\n",regs -> t2);
    rt_kprintf("\tt3(x28) = 0x%p\tt4(x29) = 0x%p\n",regs -> t3,regs -> t4);
    rt_kprintf("\tt5(x30) = 0x%p\tt6(x31) = 0x%p\n",regs -> t5,regs -> t6);
    rt_kprintf("Saved Registers:\n");
    rt_kprintf("\ts0/fp(x8) = 0x%p\ts1(x9) = 0x%p\n",regs -> s0_fp,regs -> s1);
    rt_kprintf("\ts2(x18) = 0x%p\ts3(x19) = 0x%p\n",regs -> s2,regs -> s3);
    rt_kprintf("\ts4(x20) = 0x%p\ts5(x21) = 0x%p\n",regs -> s4,regs -> s5);
    rt_kprintf("\ts6(x22) = 0x%p\ts7(x23) = 0x%p\n",regs -> s6,regs -> s7);
    rt_kprintf("\ts8(x24) = 0x%p\ts9(x25) = 0x%p\n",regs -> s8,regs -> s9);
    rt_kprintf("\ts10(x26) = 0x%p\ts11(x27) = 0x%p\n",regs -> s10,regs -> s11);
    rt_kprintf("Function Arguments Registers:\n");
    rt_kprintf("\ta0(x10) = 0x%p\ta1(x11) = 0x%p\n",regs -> a0,regs -> a1);
    rt_kprintf("\ta2(x12) = 0x%p\ta3(x13) = 0x%p\n",regs -> a2,regs -> a3);
    rt_kprintf("\ta4(x14) = 0x%p\ta5(x15) = 0x%p\n",regs -> a4,regs -> a5);
    rt_kprintf("\ta6(x16) = 0x%p\ta7(x17) = 0x%p\n",regs -> a6,regs -> a7);
    rt_kprintf("xstatus = 0x%p\n",regs -> xstatus);
    rt_kprintf("\t%s\n",(regs -> xstatus & SSTATUS_SIE) ? "Supervisor Interrupt Enabled" : "Supervisor Interrupt Disabled");
    rt_kprintf("\t%s\n",(regs -> xstatus & SSTATUS_SPIE) ? "Last Time Supervisor Interrupt Enabled" : "Last Time Supervisor Interrupt Disabled");
    rt_kprintf("\t%s\n",(regs -> xstatus & SSTATUS_SPP) ? "Last Privilege is Supervisor Mode" : "Last Privilege is User Mode");
    rt_kprintf("\t%s\n",(regs -> xstatus & SSTATUS_PUM) ? "Permit to Access User Page" : "Not Permit to Access User Page");
    rt_kprintf("\t%s\n",(regs -> xstatus & (1 << 19)) ? "Permit to Read Executable-only Page" : "Not Permit to Read Executable-only Page");
    rt_size_t satp_v = read_csr(satp);
    rt_kprintf("satp = 0x%p\n",satp_v);
    const char *mode_str = "Unknown Address Translation/Protection Mode";

    switch(__MASKVALUE(satp_v >> 60,__MASK(4)))
    {
        case 0:
            mode_str = "No Address Translation/Protection Mode";
            break;

        case 8:
            mode_str = "Page-based 39-bit Virtual Addressing Mode";
            break;

        case 9:
            mode_str = "Page-based 48-bit Virtual Addressing Mode";
            break;
    }

    rt_kprintf("\tMode = %s\n",mode_str);
    rt_kprintf("-----------------Dump OK---------------------\n");
}

void handle_trap(rt_size_t xcause,rt_size_t xtval,rt_size_t xepc,struct rt_hw_stack_frame *sp)
{
    int cause = (xcause & 0xFFFFFFFF);
    int plic_irq = 0;

    if (xcause & (1UL << 63))
    {
        switch (cause)
        {
            case IRQ_M_SOFT:
                {

                }
                break;
            case IRQ_M_TIMER:
                tick_isr();
                break;
            case IRQ_S_TIMER:
                tick_isr();
                break;

            case IRQ_S_EXT:
                plic_irq = plic_claim();
                plic_complete(plic_irq);
                irq_desc[plic_irq].handler(plic_irq, irq_desc[plic_irq].param);
                break;

            case IRQ_M_EXT:
                plic_irq = plic_claim();
                plic_complete(plic_irq);
                irq_desc[plic_irq].handler(plic_irq, irq_desc[plic_irq].param);
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

        rt_kprintf("xcause = %08x,xtval = %08x,xepc = %08x\n", xcause, xtval, xepc);
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
        dump_regs(sp);
        rt_kprintf("exception pc => 0x%08x\n", xepc);
        rt_kprintf("current thread: %.*s\n", RT_NAME_MAX, tid->name);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        list_thread();
#endif
        while(1);
    }
    rt_hw_interrupt_enable(0);
}
