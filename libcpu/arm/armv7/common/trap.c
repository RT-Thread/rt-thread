/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rtthread.h>
#include <rthw.h>
#include "armv7.h"
#ifdef RT_USING_GDB
#include "gdb_stub.h"
#endif

extern struct rt_thread *rt_current_thread;
#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

struct rt_hw_register
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t fp;
    uint32_t ip;
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
    uint32_t cpsr;
    uint32_t rev; // Make the number of registers pushed in even(8 bytes align)
};

// this function will show registers of CPU
// @param regs the registers point
void rt_hw_show_register(struct rt_hw_register *regs)
{
    rt_kprintf("Execption:\n");
    rt_kprintf("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\n", regs->r0, regs->r1, regs->r2, regs->r3);
    rt_kprintf("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\n", regs->r4, regs->r5, regs->r6, regs->r7);
    rt_kprintf("r08:0x%08x r09:0x%08x r10:0x%08x\n", regs->r8, regs->r9, regs->r10);
    rt_kprintf("fp :0x%08x ip :0x%08x\n", regs->fp, regs->ip);
    rt_kprintf("sp :0x%08x lr :0x%08x pc :0x%08x\n", regs->sp, regs->lr, regs->pc);
    rt_kprintf("cpsr:0x%08x\n", regs->cpsr);
}

// trap of the undefined instruction
// @param regs system registers
// @note never invoke this function in application
void rt_hw_trap_undef(struct rt_hw_register *regs)
{

#ifdef RT_USING_GDB
    regs->pc -= 4; //lr in undef is pc + 4
    if (gdb_undef_hook(regs))
        return;
#endif

    rt_hw_show_register(regs);

    rt_kprintf("undefined instruction\n");
    rt_kprintf("thread %.*s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

// The software interrupt instruction (SWI) is used for entering
// Supervisor mode, usually to request a particular supervisor
// function.
// @param regs system registers
// @note never invoke this function in application
void rt_hw_trap_swi(struct rt_hw_register *regs)
{
    rt_hw_show_register(regs);

    rt_kprintf("software interrupt\n");
    rt_hw_cpu_shutdown();
}

// An abort indicates that the current memory access cannot be completed,
// which occurs during an instruction prefetch.
// @param regs system registers
// @note never invoke this function in application
void rt_hw_trap_pabt(struct rt_hw_register *regs)
{
    rt_hw_show_register(regs);

    rt_kprintf("prefetch abort\n");
    rt_kprintf("thread %.*s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

// An abort indicates that the current memory access cannot be completed,
// which occurs during a data access.
// @param regs system registers
// @note never invoke this function in application
void rt_hw_trap_dabt(struct rt_hw_register *regs)
{

#ifdef RT_USING_GDB
    if (gdb_mem_fault_handler) {
        regs->pc = (unsigned long)gdb_mem_fault_handler; 
        return;
    }
#endif
    rt_hw_show_register(regs);

    rt_kprintf("data abort\n");
    rt_kprintf("thread %.*s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}
