/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#include <backtrace.h>
#include <board.h>
#include <rthw.h>
#include <rtthread.h>

#include "interrupt.h"
#include "mm_fault.h"

#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

#ifdef RT_USING_SMART
#include <lwp.h>
#include <lwp_arch.h>

#ifdef LWP_USING_CORE_DUMP
#include <lwp_core_dump.h>
#endif

void sys_exit(int value);
void check_user_fault(struct rt_hw_exp_stack *regs, uint32_t pc_adj, char *info)
{
    uint32_t mode = regs->cpsr;

    if ((mode & 0x1f) == 0x10)
    {
        rt_kprintf("%s! pc = 0x%08x\n", info, regs->pc - pc_adj);
#ifdef LWP_USING_CORE_DUMP
        lwp_core_dump(regs, pc_adj);
#endif
        sys_exit(-1);
    }
}

int check_user_stack(struct rt_hw_exp_stack *regs)
{
    void *dfar = RT_NULL;
    struct rt_lwp *lwp;
    asm volatile("MRC p15, 0, %0, c6, c0, 0" : "=r"(dfar));

    if ((dfar >= (void *)USER_STACK_VSTART) && (dfar < (void *)USER_STACK_VEND))
    {
        struct rt_aspace_fault_msg msg = {
            .fault_op = MM_FAULT_OP_WRITE,
            .fault_type = MM_FAULT_TYPE_PAGE_FAULT,
            .fault_vaddr = dfar,
        };
        lwp = lwp_self();
        if (lwp && rt_aspace_fault_try_fix(lwp->aspace, &msg))
        {
            regs->pc -= 8;
            return 1;
        }
    }

    return 0;
}
#endif

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */
void rt_hw_show_register(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("Execption:\n");
    rt_kprintf("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\n", regs->r0, regs->r1, regs->r2, regs->r3);
    rt_kprintf("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\n", regs->r4, regs->r5, regs->r6, regs->r7);
    rt_kprintf("r08:0x%08x r09:0x%08x r10:0x%08x\n", regs->r8, regs->r9, regs->r10);
    rt_kprintf("fp :0x%08x ip :0x%08x\n", regs->fp, regs->ip);
    rt_kprintf("sp :0x%08x lr :0x%08x pc :0x%08x\n", regs->sp, regs->lr, regs->pc);
    rt_kprintf("cpsr:0x%08x\n", regs->cpsr);
#ifdef RT_USING_SMART
    {
        uint32_t v;
        asm volatile ("MRC p15, 0, %0, c5, c0, 0":"=r"(v));
        rt_kprintf("dfsr:0x%08x\n", v);
        asm volatile ("MRC p15, 0, %0, c2, c0, 0":"=r"(v));
        rt_kprintf("ttbr0:0x%08x\n", v);
        asm volatile ("MRC p15, 0, %0, c6, c0, 0":"=r"(v));
        rt_kprintf("dfar:0x%08x\n", v);
        rt_kprintf("0x%08x -> 0x%08x\n", v, rt_kmem_v2p((void *)v));
    }
#endif
}

/**
 * When comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
#ifdef RT_USING_FPU
void set_fpexc(rt_uint32_t val);
#endif
void rt_hw_trap_undef(struct rt_hw_exp_stack *regs)
{
#ifdef RT_USING_FPU
    {
        uint32_t ins;
        uint32_t addr;

        if (regs->cpsr & (1 << 5))
        {
            /* thumb mode */
            addr = regs->pc - 2;
            ins = (uint32_t)*(uint16_t *)addr;
            if ((ins & (3 << 11)) != 0)
            {
                /* 32 bit ins */
                ins <<= 16;
                ins += *(uint16_t *)(addr + 2);
            }
        }
        else
        {
            addr = regs->pc - 4;
            ins = *(uint32_t *)addr;
        }
        if ((ins & 0xe00) == 0xa00)
        {
            /* float ins */
            set_fpexc(1U << 30);
            regs->pc = addr;
            return;
        }
    }
#endif
#ifdef RT_USING_SMART
    check_user_fault(regs, 4, "User undefined instruction");
#endif
    rt_unwind(regs, 4);
    rt_kprintf("undefined instruction:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * The software interrupt instruction (SWI) is used for entering
 * Supervisor mode, usually to request a particular supervisor
 * function.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_swi(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("software interrupt:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * An abort indicates that the current memory access cannot be completed,
 * which occurs during an instruction prefetch.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_pabt(struct rt_hw_exp_stack *regs)
{
#ifdef RT_USING_SMART
    if (dbg_check_event(regs, 4))
    {
        return;
    }
    check_user_fault(regs, 4, "User prefetch abort");
#endif
    rt_unwind(regs, 4);
    rt_kprintf("prefetch abort:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * An abort indicates that the current memory access cannot be completed,
 * which occurs during a data access.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_dabt(struct rt_hw_exp_stack *regs)
{
#ifdef RT_USING_SMART
    if (dbg_check_event(regs, 8))
    {
        return;
    }
    if (check_user_stack(regs))
    {
        return;
    }
    check_user_fault(regs, 8, "User data abort");
#endif
    rt_unwind(regs, 8);
    rt_kprintf("data abort:");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * Normally, system will never reach here
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_resv(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("reserved trap:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

void rt_hw_trap_irq(void)
{
#ifdef SOC_BCM283x
    extern rt_uint8_t core_timer_flag;
    void *param;
    uint32_t irq;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];
    uint32_t value = 0;
    value = IRQ_PEND_BASIC & 0x3ff;

    if(core_timer_flag != 0)
    {
        uint32_t cpu_id = rt_hw_cpu_id();
        uint32_t int_source = CORE_IRQSOURCE(cpu_id);
        if (int_source & 0x0f)
        {
            if (int_source & 0x08)
            {
                isr_func = isr_table[IRQ_ARM_TIMER].handler;
                #ifdef RT_USING_INTERRUPT_INFO
                            isr_table[IRQ_ARM_TIMER].counter++;
                #endif
                if (isr_func)
                {
                    param = isr_table[IRQ_ARM_TIMER].param;
                    isr_func(IRQ_ARM_TIMER, param);
                }
            }
        }
    }

    /* local interrupt*/
    if (value)
    {
        if (value & (1 << 8))
        {
            value = IRQ_PEND1;
            irq = __rt_ffs(value) - 1;
        }
        else if (value & (1 << 9))
        {
            value = IRQ_PEND2;
            irq = __rt_ffs(value) + 31;
        }
        else
        {
            value &= 0x0f;
            irq = __rt_ffs(value) + 63;
        }

        /* get interrupt service routine */
        isr_func = isr_table[irq].handler;
#ifdef RT_USING_INTERRUPT_INFO
        isr_table[irq].counter++;
#endif
        if (isr_func)
        {
            /* Interrupt for myself. */
            param = isr_table[irq].param;
            /* turn to interrupt service routine */
            isr_func(irq, param);
        }
    }
#else
    void *param;
    int ir, ir_real;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    ir = rt_hw_interrupt_get_irq();

    ir_real = ir & 0x3ff;
    if (ir == 1023)
    {
        /* Spurious interrupt */
        return;
    }

    /* get interrupt service routine */
    isr_func = isr_table[ir_real].handler;
#ifdef RT_USING_INTERRUPT_INFO
    isr_table[ir_real].counter++;
#endif
    if (isr_func)
    {
        /* Interrupt for myself. */
        param = isr_table[ir_real].param;
        /* turn to interrupt service routine */
        isr_func(ir, param);
    }

    /* end of interrupt */
    rt_hw_interrupt_ack(ir);
#endif
}

void rt_hw_trap_fiq(void)
{
    void *param;
    int ir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    ir = rt_hw_interrupt_get_irq();

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
    param = isr_table[ir].param;

    /* turn to interrupt service routine */
    isr_func(ir, param);

    /* end of interrupt */
    rt_hw_interrupt_ack(ir);
}

