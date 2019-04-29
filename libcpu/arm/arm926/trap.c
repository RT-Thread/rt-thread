/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      modified from mini2440
 * 2015-04-15     ArdaFu     Split from AT91SAM9260 BSP
 */

#include <rtthread.h>
#include <rthw.h>

#include "unwind.h"
#define INT_IRQ     0x00
#define INT_FIQ     0x01

extern struct rt_thread *rt_current_thread;
#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

struct rt_hw_register
{
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t fp;
    rt_uint32_t ip;
    rt_uint32_t sp;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t cpsr;
    rt_uint32_t ORIG_r0;
};
#ifdef RT_DEBUG_UNWIND

#define RT_DUMP_STACK_SIZE 512

void rt_hw_show_system_info(struct rt_hw_register *regs, unsigned int pc_adj)
{
    unsigned char *sp, *sp_limit, *spd;
    int i, dump_size;
    char curname[RT_NAME_MAX + 1];

    if (rt_current_thread != RT_NULL)
    {
        rt_strncpy(curname, rt_current_thread->name, RT_NAME_MAX);
        curname[RT_NAME_MAX] = '\0';
        rt_kprintf("Current thread: %s\n", curname);
    }

    sp = (unsigned char*)regs->sp;
    sp_limit = (unsigned char*)(rt_current_thread->stack_addr + rt_current_thread->stack_size);
    if (sp >= (unsigned char*)(rt_current_thread->stack_addr) && sp < sp_limit)
    {

        spd = (unsigned char*)(regs->sp & ~0xf);
        rt_kprintf("----------------------------------------------------------\n");
        rt_kprintf("  stack  | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
        rt_kprintf("----------------------------------------------------------\n");
        dump_size = sp_limit - sp;
        if (dump_size > RT_DUMP_STACK_SIZE)
            dump_size = RT_DUMP_STACK_SIZE;
        dump_size += (unsigned int)sp & 0xf;
        for (i = 0; i < dump_size; i++)
        {
            if ((i & 0xf) == 0)
            {
                rt_kprintf("%08x | ", (unsigned long)spd);
            }
            if (spd < sp)
                rt_kprintf("   ");
            else
                rt_kprintf("%02x ", *spd);
            spd++;
            if ((i & 0xf) == 0xf)
            {
                rt_kprintf("\n");
            }
        }
        if ((unsigned int)spd & 0xf)
            rt_kprintf("\n");
        rt_kprintf("----------------------------------------------------------\n");
        {
            struct pt_regs e_regs;
            e_regs.ARM_fp = regs->fp;
            e_regs.ARM_sp = regs->sp;
            e_regs.ARM_lr = regs->lr;
            e_regs.ARM_pc = regs->pc - pc_adj;
            rt_kprintf("backtrace:\n");
            unwind_backtrace(&e_regs);
        }
    }
    rt_kprintf("----------------------------------------------------------\n");
}

#endif /* RT_DEBUG_UNWIND */

static rt_err_t (*rt_exception_hook)(void *context) = RT_NULL;
void rt_hw_exception_install(rt_err_t (*exception_handle)(void *context))
{
    rt_exception_hook = exception_handle;
}
/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */

void rt_hw_show_register(struct rt_hw_register *regs)
{
    rt_kprintf("Execption:\n");
    rt_kprintf("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\n",
               regs->r0, regs->r1, regs->r2, regs->r3);
    rt_kprintf("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\n",
               regs->r4, regs->r5, regs->r6, regs->r7);
    rt_kprintf("r08:0x%08x r09:0x%08x r10:0x%08x\n",
               regs->r8, regs->r9, regs->r10);
    rt_kprintf("fp :0x%08x ip :0x%08x\n",
               regs->fp, regs->ip);
    rt_kprintf("sp :0x%08x lr :0x%08x pc :0x%08x\n",
               regs->sp, regs->lr, regs->pc);
    rt_kprintf("cpsr:0x%08x\n", regs->cpsr);
}

/**
 * When ARM7TDMI comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_udef(struct rt_hw_register *regs)
{
    if (rt_exception_hook != RT_NULL)
    {
        rt_err_t result;

        result = rt_exception_hook(regs);
        if (result == RT_EOK) return;
    }
    rt_hw_show_register(regs);

    rt_kprintf("undefined instruction\n");
    rt_kprintf("thread - %s stack:\n", rt_current_thread->name);

#ifdef RT_USING_FINSH
    list_thread();
#endif
#ifdef RT_DEBUG_UNWIND
    rt_hw_show_system_info(regs, 4);
#endif /* RT_DEBUG_UNWIND */
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
void rt_hw_trap_swi(struct rt_hw_register *regs)
{
    if (rt_exception_hook != RT_NULL)
    {
        rt_err_t result;

        result = rt_exception_hook(regs);
        if (result == RT_EOK) return;
    }
    rt_hw_show_register(regs);

    rt_kprintf("software interrupt\n");
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
void rt_hw_trap_pabt(struct rt_hw_register *regs)
{
    if (rt_exception_hook != RT_NULL)
    {
        rt_err_t result;

        result = rt_exception_hook(regs);
        if (result == RT_EOK) return;
    }
    rt_hw_show_register(regs);

    rt_kprintf("prefetch abort\n");
    rt_kprintf("thread - %s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#ifdef RT_USING_FINSH
    list_thread();
#endif
#ifdef RT_DEBUG_UNWIND
    rt_hw_show_system_info(regs, 4);
#endif /* RT_DEBUG_UNWIND */
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
void rt_hw_trap_dabt(struct rt_hw_register *regs)
{
    if (rt_exception_hook != RT_NULL)
    {
        rt_err_t result;

        result = rt_exception_hook(regs);
        if (result == RT_EOK) return;
    }
    rt_hw_show_register(regs);

    rt_kprintf("data abort\n");
    rt_kprintf("thread - %s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#ifdef RT_USING_FINSH
    list_thread();
#endif
#ifdef RT_DEBUG_UNWIND
    rt_hw_show_system_info(regs, 8);
#endif /* RT_DEBUG_UNWIND */
    rt_hw_cpu_shutdown();
}

/**
 * Normally, system will never reach here
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_resv(struct rt_hw_register *regs)
{
    if (rt_exception_hook != RT_NULL)
    {
        rt_err_t result;

        result = rt_exception_hook(regs);
        if (result == RT_EOK) return;
    }
    rt_kprintf("not used\n");
    rt_hw_show_register(regs);
    rt_hw_cpu_shutdown();
}

extern void rt_interrupt_dispatch(void);

void rt_hw_trap_irq(void)
{
    rt_interrupt_dispatch();
}

void rt_hw_trap_fiq(void)
{
    rt_interrupt_dispatch();
}
