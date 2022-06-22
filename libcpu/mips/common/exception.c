/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#include <rtthread.h>
#include <rthw.h>
#include "exception.h"
#include "mips_regs.h"

/**
 * @addtogroup MIPS
 */

/*@{*/

extern rt_ubase_t __ebase_entry;
rt_ubase_t rt_interrupt_from_thread;
rt_ubase_t rt_interrupt_to_thread;
rt_ubase_t rt_thread_switch_interrupt_flag;

const char *exception_name[] = {
                                "Interrupt",
                                "(X)TLB Modify Exception",
                                "(X)TLB Read/Fetch Exception",
                                "(X)TLB Write Exception",
                                "Address Read/Fetch Exception",
                                "Address Write Exception",
                                "",
                                "",
                                "Syscall",
                                "Breakpoint",
                                "Reversed Instruction Exception",
                                "Coprocessor Unit Invalid",
                                "Overflow",
                                "Trap",
                                "FPU Exception in Vector Instruction",
                                "FPU Exception",
                                "Loongson Custom Exception",
                                "",
                                "",
                                "(X)TLB Read Denied Exception",
                                "(X)TLB Execute Denied Exception",
                                "Vector Module Disabled Exception",
                                "",
                                "",
                                "",
                                "",
                                "",
                                "",
                                "",
                                "",
                                "Cache Error Exception",
                                ""
                                };

rt_base_t rt_hw_interrupt_disable(void)
{
    register rt_base_t status = read_c0_status();
    clear_c0_status(ST0_IE);
    return status;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    write_c0_status(level);
}

/**
 * exception handle table
 */
#define RT_EXCEPTION_MAX 32
exception_func_t sys_exception_handlers[RT_EXCEPTION_MAX];

/**
 * setup the exception handle
 */
exception_func_t rt_set_except_vector(int n, exception_func_t func)
{
    exception_func_t old_handler = sys_exception_handlers[n];

    if ((n == 0) || (n > RT_EXCEPTION_MAX) || (!func))
    {
        return 0;
    }

    sys_exception_handlers[n] = func;

    return old_handler;
}

void mips_dump_regs(struct pt_regs *regs)
{
    int i, j;
    for (i = 0; i < 32 / 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            int reg = 4 * i + j;
            rt_kprintf("%d: 0x%08x, ", reg, regs->regs[reg]);
        }
        rt_kprintf("\n");
    }
}

void tlb_refill_handler(void)
{
    rt_kprintf("TLB-Miss Happens, EPC: 0x%08x\n", read_c0_epc());
    rt_hw_cpu_shutdown();
}

void cache_error_handler(void)
{
    rt_kprintf("Cache Exception Happens, EPC: 0x%08x\n", read_c0_epc());
    rt_hw_cpu_shutdown();
}

static void unhandled_exception_handle(struct pt_regs *regs)
{
    rt_kprintf("Unknown Exception, EPC: 0x%p, CAUSE: 0x%08x\n", read_c0_epc(), read_c0_cause());
    rt_kprintf("Exception Name:%s\n",exception_name[(read_c0_cause() >> 2) & 0x1f]);
#ifdef SOC_LS2K1000
    rt_kprintf("ExeCode = 0x%08x,BadAddr = 0x%p\n",(read_c0_cause() >> 2) & 0x1f,mmu_tlb_get_bad_vaddr());
#else
    rt_kprintf("ExeCode = 0x%08x\n",(read_c0_cause() >> 2) & 0x1f);
#endif
    rt_kprintf("ST0: 0x%08x ",regs->cp0_status);
    rt_kprintf("ErrorPC: 0x%p\n",read_c0_errorepc());
    mips_dump_regs(regs);
    rt_hw_cpu_shutdown();
}

static void install_default_exception_handler(void)
{
    rt_int32_t i;

    for (i = 0; i < RT_EXCEPTION_MAX; i++)
        sys_exception_handlers[i] =
                (exception_func_t)unhandled_exception_handle;
}

int rt_hw_exception_init(void)
{
    rt_ubase_t ebase = (rt_ubase_t)&__ebase_entry;
#ifdef ARCH_MIPS64
    ebase |= 0xffffffff00000000;
#endif
    write_c0_ebase(ebase);
    clear_c0_status(ST0_BEV | ST0_ERL | ST0_EXL);
    clear_c0_status(ST0_IM | ST0_IE);
    set_c0_status(ST0_CU0);
    /* install the default exception handler */
    install_default_exception_handler();

    return RT_EOK;
}

void rt_general_exc_dispatch(struct pt_regs *regs)
{
    rt_ubase_t cause, exccode;
    cause = read_c0_cause();
    exccode = (cause & CAUSEF_EXCCODE) >> CAUSEB_EXCCODE;

    if (exccode == 0)
    {
        rt_ubase_t status, pending;

        status = read_c0_status();
        pending = (cause & CAUSEF_IP) & (status & ST0_IM);
        if (pending & CAUSEF_IP0)
            rt_do_mips_cpu_irq(0);
        if (pending & CAUSEF_IP1)
            rt_do_mips_cpu_irq(1);
        if (pending & CAUSEF_IP2)
            rt_do_mips_cpu_irq(2);
        if (pending & CAUSEF_IP3)
            rt_do_mips_cpu_irq(3);
        if (pending & CAUSEF_IP4)
            rt_do_mips_cpu_irq(4);
        if (pending & CAUSEF_IP5)
            rt_do_mips_cpu_irq(5);
        if (pending & CAUSEF_IP6)
            rt_do_mips_cpu_irq(6);
        if (pending & CAUSEF_IP7)
            rt_do_mips_cpu_irq(7);
    }
    else
    {
        if (sys_exception_handlers[exccode])
            sys_exception_handlers[exccode](regs);
    }
}

/* Mask means disable the interrupt */
void mips_mask_cpu_irq(rt_uint32_t irq)
{
    clear_c0_status(1 << (STATUSB_IP0 + irq));
}

/* Unmask means enable the interrupt */
void mips_unmask_cpu_irq(rt_uint32_t irq)
{
    set_c0_status(1 << (STATUSB_IP0 + irq));
}

/*@}*/
