/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-08     RT-Thread    first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include <mm_fault.h>
#include "mmu.h"
#include "encoding.h"
#include "stack.h"
#include "sbi.h"
#include "riscv.h"
#include "interrupt.h"
#include "plic.h"
#include "tick.h"

#ifdef RT_USING_SMART
#include <lwp_arch.h>
#else
#define rt_hw_backtrace(...) (0)
#endif

#define DBG_TAG "libcpu.trap"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void dump_regs(struct rt_hw_stack_frame *regs)
{
    rt_kprintf("--------------Dump Registers-----------------\n");

    rt_kprintf("Function Registers:\n");
    rt_kprintf("\tra(x1) = 0x%p\tuser_sp = 0x%p\n", regs->ra, regs->user_sp_exc_stack);
    rt_kprintf("\tgp(x3) = 0x%p\ttp(x4) = 0x%p\n", regs->gp, regs->tp);
    rt_kprintf("Temporary Registers:\n");
    rt_kprintf("\tt0(x5) = 0x%p\tt1(x6) = 0x%p\n", regs->t0, regs->t1);
    rt_kprintf("\tt2(x7) = 0x%p\n", regs->t2);
    rt_kprintf("\tt3(x28) = 0x%p\tt4(x29) = 0x%p\n", regs->t3, regs->t4);
    rt_kprintf("\tt5(x30) = 0x%p\tt6(x31) = 0x%p\n", regs->t5, regs->t6);
    rt_kprintf("Saved Registers:\n");
    rt_kprintf("\ts0/fp(x8) = 0x%p\ts1(x9) = 0x%p\n", regs->s0_fp, regs->s1);
    rt_kprintf("\ts2(x18) = 0x%p\ts3(x19) = 0x%p\n", regs->s2, regs->s3);
    rt_kprintf("\ts4(x20) = 0x%p\ts5(x21) = 0x%p\n", regs->s4, regs->s5);
    rt_kprintf("\ts6(x22) = 0x%p\ts7(x23) = 0x%p\n", regs->s6, regs->s7);
    rt_kprintf("\ts8(x24) = 0x%p\ts9(x25) = 0x%p\n", regs->s8, regs->s9);
    rt_kprintf("\ts10(x26) = 0x%p\ts11(x27) = 0x%p\n", regs->s10, regs->s11);
    rt_kprintf("Function Arguments Registers:\n");
    rt_kprintf("\ta0(x10) = 0x%p\ta1(x11) = 0x%p\n", regs->a0, regs->a1);
    rt_kprintf("\ta2(x12) = 0x%p\ta3(x13) = 0x%p\n", regs->a2, regs->a3);
    rt_kprintf("\ta4(x14) = 0x%p\ta5(x15) = 0x%p\n", regs->a4, regs->a5);
    rt_kprintf("\ta6(x16) = 0x%p\ta7(x17) = 0x%p\n", regs->a6, regs->a7);
    rt_kprintf("sstatus = 0x%p\n", regs->sstatus);
    rt_kprintf("\t%s\n", (regs->sstatus & SSTATUS_SIE) ? "Supervisor Interrupt Enabled" : "Supervisor Interrupt Disabled");
    rt_kprintf("\t%s\n", (regs->sstatus & SSTATUS_SPIE) ? "Last Time Supervisor Interrupt Enabled" : "Last Time Supervisor Interrupt Disabled");
    rt_kprintf("\t%s\n", (regs->sstatus & SSTATUS_SPP) ? "Last Privilege is Supervisor Mode" : "Last Privilege is User Mode");
    rt_kprintf("\t%s\n", (regs->sstatus & SSTATUS_SUM) ? "Permit to Access User Page" : "Not Permit to Access User Page");
    rt_kprintf("\t%s\n", (regs->sstatus & (1 << 19)) ? "Permit to Read Executable-only Page" : "Not Permit to Read Executable-only Page");
    rt_size_t satp_v = read_csr(satp);
    rt_kprintf("satp = 0x%p\n", satp_v);
    rt_kprintf("\tCurrent Page Table(Physical) = 0x%p\n", __MASKVALUE(satp_v, __MASK(44)) << PAGE_OFFSET_BIT);
    rt_kprintf("\tCurrent ASID = 0x%p\n", __MASKVALUE(satp_v >> 44, __MASK(16)) << PAGE_OFFSET_BIT);
    const char *mode_str = "Unknown Address Translation/Protection Mode";

    switch (__MASKVALUE(satp_v >> 60, __MASK(4)))
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

    rt_kprintf("\tMode = %s\n", mode_str);
    rt_kprintf("-----------------Dump OK---------------------\n");
}

static const char *Exception_Name[] =
    {
        "Instruction Address Misaligned",
        "Instruction Access Fault",
        "Illegal Instruction",
        "Breakpoint",
        "Load Address Misaligned",
        "Load Access Fault",
        "Store/AMO Address Misaligned",
        "Store/AMO Access Fault",
        "Environment call from U-mode",
        "Environment call from S-mode",
        "Reserved-10",
        "Reserved-11",
        "Instruction Page Fault",
        "Load Page Fault",
        "Reserved-14",
        "Store/AMO Page Fault"};

static const char *Interrupt_Name[] =
    {
        "User Software Interrupt",
        "Supervisor Software Interrupt",
        "Reversed-2",
        "Reversed-3",
        "User Timer Interrupt",
        "Supervisor Timer Interrupt",
        "Reversed-6",
        "Reversed-7",
        "User External Interrupt",
        "Supervisor External Interrupt",
        "Reserved-10",
        "Reserved-11",
};

extern struct rt_irq_desc irq_desc[];

#ifndef RT_USING_SMP
static volatile int nested = 0;
#define ENTER_TRAP \
    nested += 1
#define EXIT_TRAP \
    nested -= 1
#define CHECK_NESTED_PANIC(cause, tval, epc, eframe) \
    if (nested != 1)                                 \
    handle_nested_trap_panic(cause, tval, epc, eframe)
#endif /* RT_USING_SMP */

static const char *get_exception_msg(int id)
{
    const char *msg;
    if (id < sizeof(Exception_Name) / sizeof(const char *))
    {
        msg = Exception_Name[id];
    }
    else
    {
        msg = "Unknown Exception";
    }
    return msg;
}

#ifdef RT_USING_SMART
void handle_user(rt_size_t scause, rt_size_t stval, rt_size_t sepc, struct rt_hw_stack_frame *sp)
{
    rt_size_t id = __MASKVALUE(scause, __MASK(63UL));

    /* user page fault */
    enum rt_mm_fault_op fault_op;
    enum rt_mm_fault_type fault_type;
    switch (id)
    {
        case EP_LOAD_PAGE_FAULT:
            fault_op = MM_FAULT_OP_READ;
            fault_type = MM_FAULT_TYPE_PAGE_FAULT;
            break;
        case EP_LOAD_ACCESS_FAULT:
            fault_op = MM_FAULT_OP_READ;
            fault_type = MM_FAULT_TYPE_ACCESS_FAULT;
            break;
        case EP_LOAD_ADDRESS_MISALIGNED:
            fault_op = MM_FAULT_OP_READ;
            fault_type = MM_FAULT_TYPE_BUS_ERROR;
            break;
        case EP_STORE_PAGE_FAULT:
            fault_op = MM_FAULT_OP_WRITE;
            fault_type = MM_FAULT_TYPE_PAGE_FAULT;
            break;
        case EP_STORE_ACCESS_FAULT:
            fault_op = MM_FAULT_OP_WRITE;
            fault_type = MM_FAULT_TYPE_ACCESS_FAULT;
            break;
        case EP_STORE_ADDRESS_MISALIGNED:
            fault_op = MM_FAULT_OP_WRITE;
            fault_type = MM_FAULT_TYPE_BUS_ERROR;
            break;
        case EP_INSTRUCTION_PAGE_FAULT:
            fault_op = MM_FAULT_OP_EXECUTE;
            fault_type = MM_FAULT_TYPE_PAGE_FAULT;
            break;
        case EP_INSTRUCTION_ACCESS_FAULT:
            fault_op = MM_FAULT_OP_EXECUTE;
            fault_type = MM_FAULT_TYPE_ACCESS_FAULT;
            break;
        case EP_INSTRUCTION_ADDRESS_MISALIGNED:
            fault_op = MM_FAULT_OP_EXECUTE;
            fault_type = MM_FAULT_TYPE_BUS_ERROR;
            break;
        default:
            fault_op = 0;
    }

    if (fault_op)
    {
        struct rt_aspace_fault_msg msg = {
            .fault_op = fault_op,
            .fault_type = fault_type,
            .fault_vaddr = (void *)stval,
        };

        if (rt_aspace_fault_try_fix(&msg))
        {
            return;
        }
    }
    LOG_E("[FATAL ERROR] Exception %ld:%s\n", id, get_exception_msg(id));
    LOG_E("scause:0x%p,stval:0x%p,sepc:0x%p\n", scause, stval, sepc);
    dump_regs(sp);

    rt_hw_backtrace((uint32_t *)sp->s0_fp, sepc);

    LOG_E("User Fault, killing thread: %s", rt_thread_self()->parent.name);

    EXIT_TRAP;
    sys_exit(-1);
}
#endif

#ifdef ENABLE_VECTOR
static void vector_enable(struct rt_hw_stack_frame *sp)
{
    sp->sstatus |= SSTATUS_VS_INITIAL;
}

/**
 * detect V/D support, and do not distinguish V/D instruction
 */
static int illegal_inst_recoverable(rt_ubase_t stval, struct rt_hw_stack_frame *sp)
{
    // first 7 bits is opcode
    int opcode = stval & 0x7f;
    int csr = (stval & 0xFFF00000) >> 20;
    // ref riscv-v-spec-1.0, [Vector Instruction Formats]
    int width = ((stval & 0x7000) >> 12) - 1;
    int flag = 0;

    switch (opcode)
    {
    case 0x57: // V
    case 0x27: // scalar FLOAT
    case 0x07:
    case 0x73: // CSR
        flag = 1;
        break;
    }

    if (flag)
    {
        vector_enable(sp);
    }

    return flag;
}
#endif

static void handle_nested_trap_panic(
    rt_size_t cause,
    rt_size_t tval,
    rt_size_t epc,
    struct rt_hw_stack_frame *eframe)
{
    LOG_E("\n-------- [SEVER ERROR] --------");
    LOG_E("Nested trap detected");
    LOG_E("scause:0x%p,stval:0x%p,sepc:0x%p\n", cause, tval, epc);
    dump_regs(eframe);
    rt_hw_cpu_shutdown();
}

#define IN_USER_SPACE (stval >= USER_VADDR_START && stval < USER_VADDR_TOP)
#define PAGE_FAULT (id == EP_LOAD_PAGE_FAULT || id == EP_STORE_PAGE_FAULT)

/* Trap entry */
void handle_trap(rt_size_t scause, rt_size_t stval, rt_size_t sepc, struct rt_hw_stack_frame *sp)
{
    ENTER_TRAP;
    rt_size_t id = __MASKVALUE(scause, __MASK(63UL));
    const char *msg;

    /* supervisor external interrupt */
    if (scause == (uint64_t)(0x8000000000000005))
    {
        rt_interrupt_enter();
        tick_isr();
        rt_interrupt_leave();
    }
    else if (scause == (uint64_t)(0x8000000000000009))
    {
        rt_interrupt_enter();
        int plic_irq = plic_claim();
        plic_complete(plic_irq);
        irq_desc[plic_irq].handler(plic_irq, irq_desc[plic_irq].param);
        rt_interrupt_leave();
    }
    else
    {
        // trap cannot nested when handling another trap / interrupt
        CHECK_NESTED_PANIC(scause, stval, sepc, sp);
        rt_size_t id = __MASKVALUE(scause, __MASK(63UL));
        const char *msg;

        if (scause >> 63)
        {
            if (id < sizeof(Interrupt_Name) / sizeof(const char *))
            {
                msg = Interrupt_Name[id];
            }
            else
            {
                msg = "Unknown Interrupt";
            }

            rt_kprintf("Unhandled Interrupt %ld:%s\n", id, msg);
        }
        else
        {
#ifdef ENABLE_VECTOR
            if (scause == 0x2)
            {
                if (!(sp->sstatus & SSTATUS_VS) && illegal_inst_recoverable(stval, sp))
                    goto _exit;
            }
#endif /* ENABLE_VECTOR */
#ifdef RT_USING_SMART
            if (!(sp->sstatus & 0x100) || (PAGE_FAULT && IN_USER_SPACE))
            {
                handle_user(scause, stval, sepc, sp);
                // if handle_user() return here, jump to u mode then
                goto _exit;
            }
#endif

            // handle kernel exception:
            rt_kprintf("Unhandled Exception %ld:%s\n", id, get_exception_msg(id));
        }

        rt_kprintf("scause:0x%p,stval:0x%p,sepc:0x%p\n", scause, stval, sepc);
        dump_regs(sp);
        rt_kprintf("--------------Thread list--------------\n");
        rt_kprintf("current thread: %s\n", rt_thread_self()->parent.name);

        extern struct rt_thread *rt_current_thread;
        rt_kprintf("--------------Backtrace--------------\n");
        rt_hw_backtrace((uint32_t *)sp->s0_fp, sepc);

        while (1)
            ;
    }
_exit:
    EXIT_TRAP;
    return ;
}
