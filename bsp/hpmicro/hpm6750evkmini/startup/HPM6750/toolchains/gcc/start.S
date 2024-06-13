/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
 #include <rtconfig.h>
 #include "hpm_csr_regs.h"
    .section .start, "ax"

    .global _start
    .type _start,@function

_start:
    /* Initialize global pointer */
    .option push
    .option norelax
    la gp, __global_pointer$
    la tp, __thread_pointer
    .option pop

    /* Enable LMM1 clock */
    la t0, 0xF4000800
    lw t1, 0(t0)
    ori t1, t1, 0x80
    sw t1, 0(t0)

#ifdef __riscv_flen
    /* Enable FPU */
    li t0, CSR_MSTATUS_FS_MASK
    csrrs t0, mstatus, t0

    /* Initialize FCSR */
    fscsr zero
#endif

#ifdef INIT_EXT_RAM_FOR_DATA
    la t0, _stack_in_dlm
    mv sp, t0
    call _init_ext_ram
#endif

    /* Initialize stack pointer */
    la t0, _stack
    mv sp, t0

#ifdef __nds_execit
    /* Initialize EXEC.IT table */
    la t0, _ITB_BASE_
    csrw uitb, t0
#endif

#ifdef __riscv_flen
    /* Enable FPU */
    li t0, CSR_MSTATUS_FS_MASK
    csrrs t0, mstatus, t0

    /* Initialize FCSR */
    fscsr zero
#endif
    /* Disable Vector mode */
    csrci CSR_MMISC_CTL, 2
    /* Initialize trap_entry base */
    la t0, SW_handler
    csrw mtvec, t0


    /* System reset handler */
    call reset_handler

    /* Infinite loop, if returned accidently */
1:    j 1b

    .weak nmi_handler
nmi_handler:
1:    j 1b

    .global default_irq_handler
    .weak default_irq_handler
    .align 2
default_irq_handler:
1:    j 1b

    .macro IRQ_HANDLER irq
    .weak default_isr_\irq
    .set default_isr_\irq, default_irq_handler
    .long default_isr_\irq
    .endm

#include "vectors.S"
