/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#include <armv8.h>
#include <gicv3.h>
#include <rtthread.h>
#include <rthw.h>
//#include <board.h>

#include "interrupt.h"

#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
extern long list_thread(void);
#endif

/**
 * The software interrupt instruction (SWI) is used for entering
 * Supervisor mode, usually to request a particular supervisor
 * function.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_svc(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("software interrupt\n");
    rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

static rt_err_t (*rt_exception_hook)(void *context) = RT_NULL;

/**
 * This function set the hook, which is invoked on fault exception handling.
 *
 * @param exception_handle the exception handling hook function.
 */
void rt_hw_exception_install(rt_err_t (*exception_handle)(void *context))
{
    rt_exception_hook = exception_handle;
}

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
    if (rt_exception_hook != RT_NULL)
    {
        rt_err_t result;

        result = rt_exception_hook(regs);
        if (result == RT_EOK) return;
    }
}

void (*rt_trap_hook)(struct rt_hw_exp_stack *regs, const char *ex, unsigned int exception_type);

/**
 * This function will set a hook function to trap handler.
 *
 * @param hook the hook function
 */
void rt_hw_trap_set_hook(void (*hook)(struct rt_hw_exp_stack *regs, const char *ex, unsigned int exception_type))
{
    rt_trap_hook = hook;
}

/**
 * When comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_undef(struct rt_hw_exp_stack *regs)
{
#ifdef RT_USING_FPU
    {
        uint32_t val;
        uint32_t addr;

        if (regs->cpsr & (1 << 5))
        {
            /* thumb mode */
            addr = regs->pc - 2;
        }
        else
        {
            addr = regs->pc - 4;
        }
        asm volatile ("vmrs %0, fpexc" : "=r"(val)::"memory");

        if (!(val & 0x40000000))
        {
            /* float ins */
            val = (1U << 30);

            asm volatile ("vmsr fpexc, %0"::"r"(val):"memory");
            regs->pc = addr;
            return;
        }
    }
#endif

    if (rt_trap_hook == RT_NULL)
    {
        rt_kprintf("undefined instruction:\n");
        rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        list_thread();
#endif
        rt_hw_cpu_shutdown();
    }
    else
    {
        rt_trap_hook(regs, "undefined instruction", UND_EXCEPTION);
    }
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
    if (rt_trap_hook == RT_NULL)
    {
        rt_kprintf("software interrupt:\n");
        rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        list_thread();
#endif
        rt_hw_cpu_shutdown();
    }
    else
    {
        rt_trap_hook(regs, "software instruction", SWI_EXCEPTION);
    }
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
    if (rt_trap_hook == RT_NULL)
    {
        rt_kprintf("prefetch abort:\n");
        rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        list_thread();
#endif
        rt_hw_cpu_shutdown();
    }
    else
    {
        rt_trap_hook(regs, "prefetch abort", PABT_EXCEPTION);
    }
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
    if (rt_trap_hook == RT_NULL)
    {
        rt_kprintf("data abort:");
        rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        list_thread();
#endif
        rt_hw_cpu_shutdown();
    }
    else
    {
        rt_trap_hook(regs, "data abort", DABT_EXCEPTION);
    }
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
    if (rt_trap_hook == RT_NULL)
    {
        rt_kprintf("reserved trap:\n");
        rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
        list_thread();
#endif
        rt_hw_cpu_shutdown();
    }
    else
    {
        rt_trap_hook(regs, "reserved trap", RESV_EXCEPTION);
    }
}

void rt_hw_trap_irq(void)
{
    void *param;
    int int_ack;
    int ir;
    volatile rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    int_ack = rt_hw_interrupt_get_irq();

    ir = int_ack & GIC_ACK_INTID_MASK;
    if (ir == 1023)
    {
        /* Spurious interrupt */
        return;
    }

#ifdef SOC_SERIES_R9A07G0
    extern fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES];

    bsp_common_interrupt_handler((uint32_t)ir);
    if (ir < MAX_HANDLERS)
    {
        /* get interrupt service routine */
        isr_table[ir].handler = (rt_isr_handler_t)g_vector_table[ir];
        isr_table[ir].param = RT_NULL;
    }
#endif
    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;

#ifdef RT_USING_INTERRUPT_INFO
    isr_table[ir].counter++;
#endif
    if (isr_func)
    {
        /* Interrupt for myself. */
        param = isr_table[ir].param;
        /* turn to interrupt service routine */
        isr_func(ir, param);
    }

    /* end of interrupt */
    rt_hw_interrupt_ack(int_ack);
}

void rt_hw_trap_fiq(void)
{
    void *param;
    int ir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    ir = rt_hw_interrupt_get_irq();

#ifdef SOC_SERIES_R9A07G0
    extern fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES];

    bsp_common_interrupt_handler((uint32_t)ir);
    if (ir < MAX_HANDLERS)
    {
        /* get interrupt service routine */
        isr_table[ir].handler = (rt_isr_handler_t)g_vector_table[ir];
        isr_table[ir].param = RT_NULL;
    }
#endif
    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
    param = isr_table[ir].param;

    /* turn to interrupt service routine */
    isr_func(ir, param);

    /* end of interrupt */
    rt_hw_interrupt_ack(ir);
}

