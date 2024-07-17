/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_common.h"
#include "hpm_soc.h"
#include <rtthread.h>
#include "rt_hw_stack_frame.h"

#define MCAUSE_INSTR_ADDR_MISALIGNED (0U)       //!< Instruction Address misaligned
#define MCAUSE_INSTR_ACCESS_FAULT (1U)          //!< Instruction access fault
#define MCAUSE_ILLEGAL_INSTR (2U)               //!< Illegal instruction
#define MCAUSE_BREAKPOINT (3U)                  //!< Breakpoint
#define MCAUSE_LOAD_ADDR_MISALIGNED (4U)        //!< Load address misaligned
#define MCAUSE_LOAD_ACCESS_FAULT (5U)           //!< Load access fault
#define MCAUSE_STORE_AMO_ADDR_MISALIGNED (6U)   //!< Store/AMO address misaligned
#define MCAUSE_STORE_AMO_ACCESS_FAULT (7U)      //!< Store/AMO access fault
#define MCAUSE_ECALL_FROM_USER_MODE (8U)        //!< Environment call from User mode
#define MCAUSE_ECALL_FROM_SUPERVISOR_MODE (9U)  //!< Environment call from Supervisor mode
#define MCAUSE_ECALL_FROM_MACHINE_MODE (11U)    //!< Environment call from machine mode
#define MCAUSE_INSTR_PAGE_FAULT (12U)           //!< Instruction page fault
#define MCAUSE_LOAD_PAGE_FAULT (13)             //!< Load page fault
#define MCAUSE_STORE_AMO_PAGE_FAULT (15U)       //!< Store/AMO page fault

#define IRQ_S_SOFT              1
#define IRQ_H_SOFT              2
#define IRQ_M_SOFT              3
#define IRQ_S_TIMER             5
#define IRQ_H_TIMER             6
#define IRQ_M_TIMER             7
#define IRQ_S_EXT               9
#define IRQ_H_EXT               10
#define IRQ_M_EXT               11
#define IRQ_COP                 12
#define IRQ_HOST                13

#ifdef DEBUG
#define RT_EXCEPTION_TRACE rt_kprintf
#else
#define RT_EXCEPTION_TRACE(...)
#endif

typedef void (*isr_func_t)(void);

static volatile rt_hw_stack_frame_t *s_stack_frame;

__attribute((weak)) void mchtmr_isr(void)
{
}

__attribute__((weak)) void mswi_isr(void)
{
}

__attribute__((weak)) void syscall_handler(uint32_t n, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3)
{
}

void rt_show_stack_frame(void)
{
    RT_EXCEPTION_TRACE("Stack frame:\r\n----------------------------------------\r\n");
    RT_EXCEPTION_TRACE("ra      : 0x%08x\r\n", s_stack_frame->ra);
    RT_EXCEPTION_TRACE("mstatus : 0x%08x\r\n", read_csr(0x300));//mstatus
    RT_EXCEPTION_TRACE("t0      : 0x%08x\r\n", s_stack_frame->t0);
    RT_EXCEPTION_TRACE("t1      : 0x%08x\r\n", s_stack_frame->t1);
    RT_EXCEPTION_TRACE("t2      : 0x%08x\r\n", s_stack_frame->t2);
    RT_EXCEPTION_TRACE("a0      : 0x%08x\r\n", s_stack_frame->a0);
    RT_EXCEPTION_TRACE("a1      : 0x%08x\r\n", s_stack_frame->a1);
    RT_EXCEPTION_TRACE("a2      : 0x%08x\r\n", s_stack_frame->a2);
    RT_EXCEPTION_TRACE("a3      : 0x%08x\r\n", s_stack_frame->a3);
    RT_EXCEPTION_TRACE("a4      : 0x%08x\r\n", s_stack_frame->a4);
    RT_EXCEPTION_TRACE("a5      : 0x%08x\r\n", s_stack_frame->a5);
#ifndef __riscv_32e
    RT_EXCEPTION_TRACE("a6      : 0x%08x\r\n", s_stack_frame->a6);
    RT_EXCEPTION_TRACE("a7      : 0x%08x\r\n", s_stack_frame->a7);
    RT_EXCEPTION_TRACE("t3      : 0x%08x\r\n", s_stack_frame->t3);
    RT_EXCEPTION_TRACE("t4      : 0x%08x\r\n", s_stack_frame->t4);
    RT_EXCEPTION_TRACE("t5      : 0x%08x\r\n", s_stack_frame->t5);
    RT_EXCEPTION_TRACE("t6      : 0x%08x\r\n", s_stack_frame->t6);
#endif
}

uint32_t exception_handler(uint32_t cause, uint32_t epc)
{
    /* Unhandled Trap */
    uint32_t mdcause = read_csr(CSR_MDCAUSE);
    uint32_t mtval = read_csr(CSR_MTVAL);
    rt_uint32_t mscratch = read_csr(0x340);

    s_stack_frame = (rt_hw_stack_frame_t *)mscratch;
    rt_show_stack_frame();

    switch (cause)
    {
    case MCAUSE_INSTR_ADDR_MISALIGNED:
        RT_EXCEPTION_TRACE("exception: instruction address was mis-aligned, mtval=0x%08x\n", mtval);
        break;
    case MCAUSE_INSTR_ACCESS_FAULT:
        RT_EXCEPTION_TRACE("exception: instruction access fault happened, mtval=0x%08x, epc=0x%08x\n", mtval, epc);
        switch (mdcause & 0x07)
        {
        case 1:
            RT_EXCEPTION_TRACE("mdcause: ECC/Parity error\r\n");
            break;
        case 2:
            RT_EXCEPTION_TRACE("mdcause: PMP instruction access violation \r\n");
            break;
        case 3:
            RT_EXCEPTION_TRACE("mdcause: BUS error\r\n");
            break;
        case 4:
            RT_EXCEPTION_TRACE("mdcause: PMP empty hole access \r\n");
            break;
        default:
            RT_EXCEPTION_TRACE("mdcause: reserved \r\n");
            break;
        }
        break;
    case MCAUSE_ILLEGAL_INSTR:
        RT_EXCEPTION_TRACE("exception: illegal instruction was met, mtval=0x%08x\n", mtval);
        switch (mdcause & 0x07)
        {
        case 0:
            RT_EXCEPTION_TRACE("mdcause: the actual faulting instruction is stored in the mtval CSR\r\n");
            break;
        case 1:
            RT_EXCEPTION_TRACE("mdcause: FP disabled exception \r\n");
            break;
        case 2:
            RT_EXCEPTION_TRACE("mdcause: ACE disabled exception \r\n");
            break;
        default:
            RT_EXCEPTION_TRACE("mdcause: reserved \r\n");
            break;
        }
        break;
    case MCAUSE_BREAKPOINT:
        RT_EXCEPTION_TRACE("exception: breakpoint was hit, mtval=0x%08x\n", mtval);
        break;
    case MCAUSE_LOAD_ADDR_MISALIGNED:
        RT_EXCEPTION_TRACE("exception: load address was mis-aligned, mtval=0x%08x\n", mtval);
        break;
    case MCAUSE_LOAD_ACCESS_FAULT:
        RT_EXCEPTION_TRACE("exception: load access fault happened, epc=%08x, mdcause=0x%x\n", epc, mdcause);
        switch (mdcause & 0x07)
        {
        case 1:
            RT_EXCEPTION_TRACE("mdcause: ECC/Parity error\r\n");
            break;
        case 2:
            RT_EXCEPTION_TRACE("mdcause: PMP instruction access violation \r\n");
            break;
        case 3:
            RT_EXCEPTION_TRACE("mdcause: BUS error\r\n");
            break;
        case 4:
            RT_EXCEPTION_TRACE("mdcause: Misaligned access \r\n");
            break;
        case 5:
            RT_EXCEPTION_TRACE("mdcause: PMP empty hole access \r\n");
            break;
        case 6:
            RT_EXCEPTION_TRACE("mdcause: PMA attribute inconsistency\r\n");
            break;
        default:
            RT_EXCEPTION_TRACE("mdcause: reserved \r\n");
            break;
        }
        break;
    case MCAUSE_STORE_AMO_ADDR_MISALIGNED:
        RT_EXCEPTION_TRACE("exception: store amo address was misaligned, epc=%08x\n", epc);
        break;
    case MCAUSE_STORE_AMO_ACCESS_FAULT:
        RT_EXCEPTION_TRACE("exception: store amo access fault happened, epc=%08x\n", epc);
        switch (mdcause & 0x07)
        {
        case 1:
            RT_EXCEPTION_TRACE("mdcause: ECC/Parity error\r\n");
            break;
        case 2:
            RT_EXCEPTION_TRACE("mdcause: PMP instruction access violation \r\n");
            break;
        case 3:
            RT_EXCEPTION_TRACE("mdcause: BUS error\r\n");
            break;
        case 4:
            RT_EXCEPTION_TRACE("mdcause: Misaligned access \r\n");
            break;
        case 5:
            RT_EXCEPTION_TRACE("mdcause: PMP empty hole access \r\n");
            break;
        case 6:
            RT_EXCEPTION_TRACE("mdcause: PMA attribute inconsistency\r\n");
            break;
        case 7:
            RT_EXCEPTION_TRACE("mdcause: PMA NAMO exception \r\n");
        default:
            RT_EXCEPTION_TRACE("mdcause: reserved \r\n");
            break;
        }
        break;
    default:
        RT_EXCEPTION_TRACE("Unknown exception happened, cause=%d\n", cause);
        break;
    }

    rt_kprintf("cause=0x%08x, epc=0x%08x, ra=0x%08x\n", cause, epc, s_stack_frame->ra);
    while(1) {
    }
}

void trap_entry(void);

void trap_entry(void)
{
    uint32_t mcause = read_csr(CSR_MCAUSE);
    uint32_t mepc = read_csr(CSR_MEPC);
    uint32_t mstatus = read_csr(CSR_MSTATUS);

#if SUPPORT_PFT_ARCH
    uint32_t mxstatus = read_csr(CSR_MXSTATUS);
#endif
#ifdef __riscv_dsp
    int ucode = read_csr(CSR_UCODE);
#endif
#ifdef __riscv_flen
    int fcsr = read_fcsr();
#endif

    /* clobbers list for ecall */
#ifdef __riscv_32e
    __asm volatile("" : : :"t0", "a0", "a1", "a2", "a3");
#else
    __asm volatile("" : : :"a7", "a0", "a1", "a2", "a3");
#endif

    /* Do your trap handling */
    uint32_t cause_type = mcause & CSR_MCAUSE_EXCEPTION_CODE_MASK;
    uint32_t irq_index;
    if (mcause & CSR_MCAUSE_INTERRUPT_MASK)
    {
        switch (cause_type)
        {
        /* Machine timer interrupt */
        case IRQ_M_TIMER:
            mchtmr_isr();
            break;
            /* Machine EXT interrupt */
        case IRQ_M_EXT:
            /* Claim interrupt */
            irq_index = __plic_claim_irq(HPM_PLIC_BASE, HPM_PLIC_TARGET_M_MODE);
            /* Execute EXT interrupt handler */
            if (irq_index > 0)
            {
                ((isr_func_t) __vector_table[irq_index])();
                /* Complete interrupt */
                __plic_complete_irq(HPM_PLIC_BASE, HPM_PLIC_TARGET_M_MODE, irq_index);
            }
            break;
            /* Machine SWI interrupt */
        case IRQ_M_SOFT:
            mswi_isr();
            intc_m_complete_swi();
            break;
        }
    }
    else if (cause_type == MCAUSE_ECALL_FROM_MACHINE_MODE)
    {
        /* Machine Syscal call */
        __asm volatile(
                "mv a4, a3\n"
                "mv a3, a2\n"
                "mv a2, a1\n"
                "mv a1, a0\n"
#ifdef __riscv_32e
                "mv a0, t0\n"
#else
                "mv a0, a7\n"
#endif
                "call syscall_handler\n"
                : : : "a4"
        );
        mepc += 4;
    }
    else
    {
        mepc = exception_handler(mcause, mepc);
    }

    /* Restore CSR */
    write_csr(CSR_MSTATUS, mstatus);
    write_csr(CSR_MEPC, mepc);
#if SUPPORT_PFT_ARCH
    write_csr(CSR_MXSTATUS, mxstatus);
#endif
#ifdef __riscv_dsp
    write_csr(CSR_UCODE, ucode);
#endif
#ifdef __riscv_flen
    write_fcsr(fcsr);
#endif
}

/**
 * Trap Handler
 */
rt_weak void handle_trap(rt_uint32_t mcause, rt_uint32_t mepc, rt_uint32_t sp)
{
}