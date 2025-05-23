/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-08     RT-Thread    first version
 * 2025-04-20     GuEe-GUI     Port to the DM
 */

#include <rthw.h>
#include <rtthread.h>

#include <csr.h>
#include <sbi.h>
#include <stack.h>
#include <mm_aspace.h>
#include <riscv_timer.h>
#ifdef RT_USING_DM
#include <drivers/pic.h>
#else
#include <interrupt.h>
#endif
#ifdef RT_USING_SMART
#include <lwp_arch.h>
#endif

#define DBG_TAG "libcpu.trap"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

#ifdef RT_USING_LWP
#include <lwp.h>
#include <lwp_arch.h>

#ifdef LWP_USING_CORE_DUMP
#include <lwp_core_dump.h>
#endif

static void _check_fault(struct rt_hw_stack_frame *regs, uint32_t pc_adj, char *info)
{
    rt_thread_t th;
    rt_bool_t is_user_fault = !!(regs->xstatus & SR_PP);

    if (is_user_fault)
    {
        rt_kprintf("%s! pc = %p\n", info, regs->epc - pc_adj);
    }

    /* User stack backtrace */
    th = rt_thread_self();
    if (th && th->lwp)
    {
        arch_backtrace_uthread(th);
    }

    if (is_user_fault)
    {
    #ifdef LWP_USING_CORE_DUMP
        lwp_core_dump(regs, pc_adj);
    #endif
        sys_exit_group(-1);
    }
}

rt_inline rt_bool_t user_fault_fixable(struct rt_hw_stack_frame *regs, rt_ubase_t xcause, rt_ubase_t tval)
{
    struct rt_lwp *lwp;
    enum rt_mm_fault_op fault_op;
    enum rt_mm_fault_type fault_type;

    switch (xcause)
    {
    case EXC_LOAD_PAGE_FAULT:
        fault_op = MM_FAULT_OP_READ;
        fault_type = MM_FAULT_TYPE_GENERIC_MMU;
        break;
    case EXC_LOAD_ACCESS:
        fault_op = MM_FAULT_OP_READ;
        fault_type = MM_FAULT_TYPE_BUS_ERROR;
        break;
    case EXC_LOAD_MISALIGNED:
        fault_op = MM_FAULT_OP_READ;
        fault_type = MM_FAULT_TYPE_BUS_ERROR;
        break;
    case EXC_STORE_PAGE_FAULT:
        fault_op = MM_FAULT_OP_WRITE;
        fault_type = MM_FAULT_TYPE_GENERIC_MMU;
        break;
    case EXC_STORE_ACCESS:
        fault_op = MM_FAULT_OP_WRITE;
        fault_type = MM_FAULT_TYPE_BUS_ERROR;
        break;
    case EXC_STORE_MISALIGNED:
        fault_op = MM_FAULT_OP_WRITE;
        fault_type = MM_FAULT_TYPE_BUS_ERROR;
        break;
    case EXC_INST_PAGE_FAULT:
        fault_op = MM_FAULT_OP_EXECUTE;
        fault_type = MM_FAULT_TYPE_GENERIC_MMU;
        break;
    case EXC_INST_ACCESS:
        fault_op = MM_FAULT_OP_EXECUTE;
        fault_type = MM_FAULT_TYPE_BUS_ERROR;
        break;
    case EXC_INST_MISALIGNED:
        fault_op = MM_FAULT_OP_EXECUTE;
        fault_type = MM_FAULT_TYPE_BUS_ERROR;
        break;
    default:
        fault_op = 0;
        break;
    }

    if (fault_op)
    {
        rt_base_t saved_stat;
        struct rt_aspace_fault_msg msg =
        {
            .fault_op = fault_op,
            .fault_type = fault_type,
            .fault_vaddr = (void *)tval,
        };

        lwp = lwp_self();

        saved_stat = csr_read_clear(CSR_STATUS, SR_IE);

        if (lwp && rt_aspace_fault_try_fix(lwp->aspace, &msg))
        {
            csr_write(CSR_STATUS, saved_stat);
            return RT_TRUE;
        }

        csr_write(CSR_STATUS, saved_stat);
    }

    return RT_FALSE;
}
#endif /* RT_USING_LWP */

#ifdef ARCH_RISCV_VECTOR
rt_inline void vector_enable(struct rt_hw_stack_frame *regs)
{
    regs->xstatus |= SR_VS_INITIAL;
}

/**
 * detect V/D support, and do not distinguish V/D instruction
 */
rt_inline rt_bool_t illegal_inst_recoverable(struct rt_hw_stack_frame *regs, rt_ubase_t tval)
{
    /* first 7 bits is opcode */
    int opcode = tval & 0x7f;
    int csr = (tval & 0xfff00000) >> 20;
    /* ref riscv-v-spec-1.0, [Vector Instruction Formats] */
    int width = ((tval & 0x7000) >> 12) - 1;

    switch (opcode)
    {
    case 0x57: /* V */
    case 0x27: /* scalar FLOAT */
    case 0x07:
    case 0x73: /* CSR */
        vector_enable(regs);
        return RT_TRUE;

    default:
        break;
    }

    return RT_FALSE;
}
#endif /* ARCH_RISCV_VECTOR */

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */
void rt_hw_show_register(struct rt_hw_stack_frame *regs)
{
#ifndef ARCH_RISCV_M_MODE
    const char *sv_mode;
    rt_ubase_t satp = csr_read(CSR_SATP);

    switch (satp & SATP_MODE_MASK)
    {
    case SATP_MODE_BARE:
        sv_mode = "Bare";
        break;
#if __riscv_xlen == 32
    case SATP_MODE_32:
        sv_mode = "Sv32";
        break;
#else
    case SATP_MODE_39:
        sv_mode = "Sv39";
        break;
    case SATP_MODE_48:
        sv_mode = "Sv48";
        break;
    case SATP_MODE_57:
        sv_mode = "Sv57";
        break;
    case SATP_MODE_64:
        sv_mode = "Sv64";
        break;
#endif /* __riscv_xlen == 32 */
    default:
        sv_mode = "Reserved";
        break;
    }
#endif /* !ARCH_RISCV_M_MODE */

#if __riscv_xlen == 64
#define F "0x%016lx"
#elif __riscv_xlen == 32
#define F "0x%08lx"
#else
#error "Unexpected __riscv_xlen"
#endif
    rt_kprintf("Execption:\n");
    rt_kprintf("x0/zero: " F " x1/ra : " F " x2/sp  : " F " x3/gp  : " F "\n", 0UL, regs->user_sp_exc_stack, regs->ra, regs->gp);
    rt_kprintf("x4/tp  : " F " x5/t0 : " F " x6/t1  : " F " x7/t2  : " F "\n", regs->tp, regs->t0, regs->t1, regs->t2);
    rt_kprintf("x8/s0  : " F " x9/s1 : " F " x10/a0 : " F " x11/a1 : " F "\n", regs->s0_fp, regs->s1, regs->a0, regs->a1);
    rt_kprintf("x12/a2 : " F " x13/a3: " F " x14/a4 : " F " x15/a5 : " F "\n", regs->a2, regs->a3, regs->a4, regs->a5);
#ifndef ARCH_RISCV_32E
    rt_kprintf("x16/a6 : " F " x17/a7: " F " x18/s2 : " F " x19/s3 : " F "\n", regs->a6, regs->a7, regs->s2, regs->s3);
    rt_kprintf("x20/s4 : " F " x21/s5: " F " x22/s6 : " F " x23/s7 : " F "\n", regs->s4, regs->s5, regs->s6, regs->s7);
    rt_kprintf("x24/s8 : " F " x25/s9: " F " x26/s10: " F " x27/s11: " F "\n", regs->s8, regs->s9, regs->s10, regs->s11);
    rt_kprintf("x28/t3 : " F " x29/t4: " F " x30/t5 : " F " x31/t6 : " F "\n", regs->t3, regs->t4, regs->t5, regs->t6);
#endif /* !ARCH_RISCV_32E */
#ifdef ARCH_RISCV_M_MODE
    rt_kprintf("status : " F " (%s %s %s)\n", regs->xstatus,
            (regs->xstatus & SR_IE) ? "IE" : "--",
            (regs->xstatus & SR_PIE) ? "PIE" : "---",
            (regs->xstatus & SR_PP) ? "PP" : "--");
#else
    rt_kprintf("status : " F " (%s %s %s %s %s)\n", regs->xstatus,
            (regs->xstatus & SR_IE) ? "IE" : "--",
            (regs->xstatus & SR_PIE) ? "PIE" : "---",
            (regs->xstatus & SR_PP) ? "PP" : "--",
            (regs->xstatus & SR_SUM) ? "SUM" : "---",
            (regs->xstatus & SR_MXR) ? "MXR" : "---");
    rt_kprintf("satp   : " F " (ASID: " F ", %s)\n", satp, (satp >> SATP_ASID_SHIFT) & SATP_ASID_MASK, sv_mode);
#endif
    rt_kprintf("cause  : " F "\n", regs->xcause);
    rt_kprintf("pc     : " F "\n", regs->epc);
#undef F
}

static const char * const irq_name[] =
{
    [IRQ_S_SOFT]    = "Software Interrupt (User)",
    [IRQ_VS_SOFT]   = "Software Interrupt (Supervisor)",
    [IRQ_M_SOFT]    = "Software Interrupt (Machine)",
    [IRQ_S_TIMER]   = "Timer Interrupt (User)",
    [IRQ_VS_TIMER]  = "Timer Interrupt (Supervisor)",
    [IRQ_M_TIMER]   = "Timer Interrupt (Machine)",
    [IRQ_S_EXT]     = "External Interrupt (User)",
    [IRQ_VS_EXT]    = "External Interrupt (Supervisor)",
    [IRQ_M_EXT]     = "External Interrupt (Machine)",
    [IRQ_S_GEXT]    = "External Interrupt (Supervisor Guest)",
    [IRQ_PMU_OVF]   = "Performance Monitor Unit Overflow",
};

static const char * const exception_name[] =
{
    [EXC_INST_MISALIGNED]           = "INST Misaligned",
    [EXC_INST_ACCESS]               = "INST Access",
    [EXC_INST_ILLEGAL]              = "INST Illegal",
    [EXC_BREAKPOINT]                = "Breakpoint",
    [EXC_LOAD_MISALIGNED]           = "Load Misaligned",
    [EXC_LOAD_ACCESS]               = "Load Access",
    [EXC_STORE_MISALIGNED]          = "Store Misaligned",
    [EXC_STORE_ACCESS]              = "Store Access",
    [EXC_SYSCALL]                   = "Syscall",
    [EXC_HYPERVISOR_SYSCALL]        = "Hypervisor Syscall",
    [EXC_SUPERVISOR_SYSCALL]        = "Supervisor Syscall",
    [EXC_INST_PAGE_FAULT]           = "INST Page Fault",
    [EXC_LOAD_PAGE_FAULT]           = "Load Page Fault",
    [EXC_STORE_PAGE_FAULT]          = "Store Page Fault",
    [EXC_INST_GUEST_PAGE_FAULT]     = "INST Guest Page Fault",
    [EXC_LOAD_GUEST_PAGE_FAULT]     = "Load Guest Page Fault",
    [EXC_VIRTUAL_INST_FAULT]        = "Virtual INST Fault",
    [EXC_STORE_GUEST_PAGE_FAULT]    = "Store Guest Page Fault",
};

void rt_hw_trap(struct rt_hw_stack_frame *regs)
{
    rt_ubase_t xcause = regs->xcause;
    rt_ubase_t tval = csr_read_clear(CSR_TVAL, 0);

    /* IRQ */
    if (xcause & CAUSE_IRQ_FLAG)
    {
        rt_interrupt_enter();

        xcause &= ~CAUSE_IRQ_FLAG;

        switch (xcause)
        {
        case RV_IRQ_TIMER:
            riscv_timer_isr();
            break;

        case RV_IRQ_SOFT:
        case RV_IRQ_EXT:
        #ifdef RT_USING_DM
            rt_pic_do_traps();
        #else
            rt_hw_interrupt_handle(xcause, regs);
        #endif
            break;

        default:
            LOG_E("Unhandle IRQ: (%d) %s", xcause,
                    xcause >= sizeof(irq_name) / sizeof(irq_name[0]) ? "Reserved" : irq_name[xcause]);
            break;
        }

        rt_interrupt_leave();
    }
    /* Execption */
    else
    {
        struct rt_hw_backtrace_frame frame;

        switch (xcause)
        {
        case EXC_INST_ILLEGAL:
        #ifdef ARCH_RISCV_VECTOR
            if (!(regs->xstatus & SR_VS))
            {
                if (illegal_inst_recoverable(regs, tval))
                {
                    return;
                }
            }
        #endif /* ARCH_RISCV_VECTOR */
            break;

        case EXC_LOAD_GUEST_PAGE_FAULT:
        case EXC_STORE_GUEST_PAGE_FAULT:
        #ifdef RT_USING_SMART
            if ((regs->xstatus & SR_PP) &&
                (tval >= USER_VADDR_START && tval < USER_VADDR_TOP))
            {
                if (user_fault_fixable(regs, xcause, tval))
                {
                    return;
                }
            }
        #endif /* RT_USING_SMART */

        default:
            LOG_E("Unhandle Execption: (%d) %s, TVAL = %p", xcause,
                    xcause >= sizeof(exception_name) / sizeof(exception_name[0]) ? "Reserved" : exception_name[xcause],
                    tval);
        }

        rt_hw_show_register(regs);

        if (rt_thread_self())
        {
            LOG_E("current thread: %s\n", rt_thread_self()->parent.name);

        #ifdef RT_USING_FINSH
            list_thread();
        #endif

        #ifdef RT_USING_LWP
            _check_fault(regs, 0, "user fault");
        #endif
        }

        frame.fp = regs->s0_fp;
        frame.pc = regs->epc;
        rt_backtrace_frame(rt_thread_self(), &frame);
        rt_hw_cpu_shutdown();
    }
}
