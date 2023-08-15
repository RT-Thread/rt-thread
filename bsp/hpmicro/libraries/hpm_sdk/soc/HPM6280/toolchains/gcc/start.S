/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_csr_regs.h"

    .section .start, "ax"

    .global _start
    .type _start,@function

_start:
    /* Initialize global pointer */
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    /* reset mstatus to 0*/
    csrrw x0, mstatus, x0

#ifdef __riscv_flen
    /* Enable FPU */
    li t0, CSR_MSTATUS_FS_MASK
    csrrs t0, mstatus, t0

    /* Initialize FCSR */
    fscsr zero
#endif

    /* Initialize stack pointer */
    la t0, _stack
    mv sp, t0

    /*
     * Initialize LMA/VMA sections.
     * Relocation for any sections that need to be copied from LMA to VMA.
     */
    call c_startup

#if defined(__SES_RISCV)
    /* Initialize the heap */
    la a0, __heap_start__
    la a1, __heap_end__
    sub a1, a1, a0
    la t1, __SEGGER_RTL_init_heap
    jalr t1
#endif

    /* Do global constructors */
    call __libc_init_array

#ifndef NO_CLEANUP_AT_START
    /* clean up */
    call _clean_up
#endif

#ifdef __nds_execit
    /* Initialize EXEC.IT table */
    la t0, _ITB_BASE_
    csrw uitb, t0
#endif

#if defined(CONFIG_FREERTOS) && CONFIG_FREERTOS
    #define HANDLER_TRAP freertos_risc_v_trap_handler
    #define HANDLER_S_TRAP freertos_risc_v_trap_handler

    /* Use mscratch to store isr level */
    csrw mscratch, 0
#elif defined(CONFIG_UCOS_III) && CONFIG_UCOS_III
    #define HANDLER_TRAP ucos_risc_v_trap_handler
    #define HANDLER_S_TRAP ucos_risc_v_trap_handler

    /* Use mscratch to store isr level */
    csrw mscratch, 0
#elif defined(CONFIG_THREADX) && CONFIG_THREADX
    #define HANDLER_TRAP tx_risc_v_trap_handler
    #define HANDLER_S_TRAP tx_risc_v_trap_handler

    /* Use mscratch to store isr level */
    csrw mscratch, 0
#else
    #define HANDLER_TRAP irq_handler_trap
    #define HANDLER_S_TRAP irq_handler_s_trap
#endif

#ifndef USE_NONVECTOR_MODE
    /* Initial machine trap-vector Base */
    la t0, __vector_table
    csrw mtvec, t0

#if defined (USE_S_MODE_IRQ)
    la t0, __vector_s_table
    csrw stvec, t0
#endif
    /* Enable vectored external PLIC interrupt */
    csrsi CSR_MMISC_CTL, 2
#else
    /* Initial machine trap-vector Base */
    la t0, HANDLER_TRAP
    csrw mtvec, t0
#if defined (USE_S_MODE_IRQ)
    la t0, HANDLER_S_TRAP
    csrw stvec, t0
#endif

    /* Disable vectored external PLIC interrupt */
    csrci CSR_MMISC_CTL, 2
#endif

    /* System reset handler */
    call reset_handler

    /* Infinite loop, if returned accidentally */
1:    j 1b

    .weak exit
exit:
1:    j 1b

    .section .isr_vector, "ax"
    .weak nmi_handler
nmi_handler:
1:    j 1b

#include "../vectors.h"
