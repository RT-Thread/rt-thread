/*
 * Copyright (c) 2021 - 2022 hpmicro
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

typedef void (*isr_func_t)(void);

static volatile rt_hw_stack_frame_t *s_stack_frame;

static void rt_show_stack_frame(void);

__attribute((weak)) void mchtmr_isr(void)
{
}

__attribute__((weak)) void mswi_isr(void)
{
}

__attribute__((weak)) void syscall_handler(uint32_t n, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3)
{
}

uint32_t exception_handler(uint32_t cause, uint32_t epc)
{
    /* Unhandled Trap */
    uint32_t mdcause = read_csr(CSR_MDCAUSE);
    uint32_t mtval = read_csr(CSR_MTVAL);
    switch (cause)
    {
    case MCAUSE_INSTR_ADDR_MISALIGNED:
        rt_kprintf("exception: instruction address was mis-aligned, mtval=0x%08x\n", mtval);
        break;
    case MCAUSE_INSTR_ACCESS_FAULT:
        rt_kprintf("exception: instruction access fault happened, mtval=0x%08x, epc=0x%08x\n", mtval, epc);
        switch (mdcause & 0x07)
        {
        case 1:
            rt_kprintf("mdcause: ECC/Parity error\r\n");
            break;
        case 2:
            rt_kprintf("mdcause: PMP instruction access violation \r\n");
            break;
        case 3:
            rt_kprintf("mdcause: BUS error\r\n");
            break;
        case 4:
            rt_kprintf("mdcause: PMP empty hole access \r\n");
            break;
        default:
            rt_kprintf("mdcause: reserved \r\n");
            break;
        }
        break;
    case MCAUSE_ILLEGAL_INSTR:
        rt_kprintf("exception: illegal instruction was met, mtval=0x%08x\n", mtval);
        switch (mdcause & 0x07)
        {
        case 0:
            rt_kprintf("mdcause: the actual faulting instruction is stored in the mtval CSR\r\n");
            break;
        case 1:
            rt_kprintf("mdcause: FP disabled exception \r\n");
            break;
        case 2:
            rt_kprintf("mdcause: ACE disabled exception \r\n");
            break;
        default:
            rt_kprintf("mdcause: reserved \r\n");
            break;
        }
        break;
    case MCAUSE_BREAKPOINT:
        rt_kprintf("exception: breakpoint was hit, mtval=0x%08x\n", mtval);
        break;
    case MCAUSE_LOAD_ADDR_MISALIGNED:
        rt_kprintf("exception: load address was mis-aligned, mtval=0x%08x\n", mtval);
        break;
    case MCAUSE_LOAD_ACCESS_FAULT:
        rt_kprintf("exception: load access fault happened, epc=%08x, mdcause=0x%x\n", epc, mdcause);
        switch (mdcause & 0x07)
        {
        case 1:
            rt_kprintf("mdcause: ECC/Parity error\r\n");
            break;
        case 2:
            rt_kprintf("mdcause: PMP instruction access violation \r\n");
            break;
        case 3:
            rt_kprintf("mdcause: BUS error\r\n");
            break;
        case 4:
            rt_kprintf("mdcause: Misaligned access \r\n");
            break;
        case 5:
            rt_kprintf("mdcause: PMP empty hole access \r\n");
            break;
        case 6:
            rt_kprintf("mdcause: PMA attribute inconsistency\r\n");
            break;
        default:
            rt_kprintf("mdcause: reserved \r\n");
            break;
        }
        break;
    case MCAUSE_STORE_AMO_ADDR_MISALIGNED:
        rt_kprintf("exception: store amo address was misaligned, epc=%08x\n", epc);
        break;
    case MCAUSE_STORE_AMO_ACCESS_FAULT:
        rt_kprintf("exception: store amo access fault happened, epc=%08x\n", epc);
        switch (mdcause & 0x07)
        {
        case 1:
            rt_kprintf("mdcause: ECC/Parity error\r\n");
            break;
        case 2:
            rt_kprintf("mdcause: PMP instruction access violation \r\n");
            break;
        case 3:
            rt_kprintf("mdcause: BUS error\r\n");
            break;
        case 4:
            rt_kprintf("mdcause: Misaligned access \r\n");
            break;
        case 5:
            rt_kprintf("mdcause: PMP empty hole access \r\n");
            break;
        case 6:
            rt_kprintf("mdcause: PMA attribute inconsistency\r\n");
            break;
        case 7:
            rt_kprintf("mdcause: PMA NAMO exception \r\n");
        default:
            rt_kprintf("mdcause: reserved \r\n");
            break;
        }
        break;
    default:
        rt_kprintf("Unknown exception happened, cause=%d\n", cause);
        break;
    }

    rt_show_stack_frame();
    while (1)
    {
    }
}

void trap_entry(rt_hw_stack_frame_t *stack_frame);

void trap_entry(rt_hw_stack_frame_t *stack_frame)
{
    uint32_t mcause = read_csr(CSR_MCAUSE);
    uint32_t mepc = read_csr(CSR_MEPC);
    uint32_t mstatus = read_csr(CSR_MSTATUS);

    s_stack_frame = stack_frame;

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

static void rt_show_stack_frame(void)
{
    rt_kprintf("Stack frame:\r\n----------------------------------------\r\n");
    rt_kprintf("ra      : 0x%08x\r\n", s_stack_frame->ra);
    rt_kprintf("mstatus : 0x%08x\r\n", read_csr(CSR_MSTATUS));
    rt_kprintf("t0      : 0x%08x\r\n", s_stack_frame->t0);
    rt_kprintf("t1      : 0x%08x\r\n", s_stack_frame->t1);
    rt_kprintf("t2      : 0x%08x\r\n", s_stack_frame->t2);
    rt_kprintf("a0      : 0x%08x\r\n", s_stack_frame->a0);
    rt_kprintf("a1      : 0x%08x\r\n", s_stack_frame->a1);
    rt_kprintf("a2      : 0x%08x\r\n", s_stack_frame->a2);
    rt_kprintf("a3      : 0x%08x\r\n", s_stack_frame->a3);
    rt_kprintf("a4      : 0x%08x\r\n", s_stack_frame->a4);
    rt_kprintf("a5      : 0x%08x\r\n", s_stack_frame->a5);
    rt_kprintf("a6      : 0x%08x\r\n", s_stack_frame->a6);
    rt_kprintf("a7      : 0x%08x\r\n", s_stack_frame->a7);
    rt_kprintf("t3      : 0x%08x\r\n", s_stack_frame->t3);
    rt_kprintf("t4      : 0x%08x\r\n", s_stack_frame->t4);
    rt_kprintf("t5      : 0x%08x\r\n", s_stack_frame->t5);
    rt_kprintf("t6      : 0x%08x\r\n", s_stack_frame->t6);
}
