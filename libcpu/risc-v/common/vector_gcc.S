/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-02     Bernard      The first version
 * 2018-12-27     Jesven       Add SMP schedule
 * 2021-02-02     lizhirui     Add userspace support
 * 2021-12-24     JasonHu      Add user setting save/restore
 * 2022-10-22     Shell        Support kernel mode RVV;
 *                             Rewrite trap handling routine
 * 2025-04-20     GuEe-GUI     Support SMP
 */

#include <asm.h>
#include <csr.h>

    .section ".text","ax"
    .align 2
START_POINT(system_vectors)
    /* Distingush exception from kernel or user */
    csrrw   sp, CSR_SCRATCH, sp
    bnez    sp, _save_context

    /*
     * BE REALLY careful with xscratch,
     * if it's wrong, we could looping here forever
     * or accessing random memory and seeing things totally
     * messy after a long time and don't even know why
     */
_from_kernel:
    csrr    sp, CSR_SCRATCH
    j       _save_context

_save_context:
    SAVE_ALL

    /* Clear xscratch to say 'now in kernel mode' */
    csrw    CSR_SCRATCH, zero

    LOAD_GLOBAL_POINTER

    /* Now we are ready to enter interrupt / excepiton handler */
#ifdef RT_USING_SMART
_distinguish_syscall:
    csrr    t0, CSR_CAUSE
    li      t1, EXC_SYSCALL
    bne     t0, t1, _handle_interrupt_and_exception

    call    syscall_entry
    /* Syscall never return here */
#endif /* RT_USING_SMART */

_handle_interrupt_and_exception:
    mv      a0, sp
    call    rt_hw_trap

_interrupt_exit:
#ifdef RT_USING_SMP
    mv      a0, sp
    call    rt_scheduler_do_irq_switch
    j       rt_hw_resume_kernel
#else
    la      s0, rt_thread_switch_interrupt_flag
    lw      s1, 0(s0)
    beqz    s1, _resume_execution
    sw      zero, 0(s0)

_context_switch:
    la      t0, rt_interrupt_from_thread
    REG_L   a0, 0(t0)
    la      t0, rt_interrupt_to_thread
    REG_L   a1, 0(t0)
    csrr    t0, CSR_STATUS
    andi    t0, t0, ~SR_PIE
    csrw    CSR_STATUS, t0
    jal     rt_hw_context_switch
#endif /* RT_USING_SMP */

_resume_execution:
#ifdef RT_USING_SMART
    REG_L   t0, FRAME_OFF_XSTATUS(sp)
    andi    t0, t0, SR_PP
    bnez    t0, rt_hw_resume_kernel
    call    arch_ret_to_user
#endif /* RT_USING_SMART */

    j       rt_hw_resume_kernel
START_POINT_END(system_vectors)

.globl rt_hw_resume_kernel
rt_hw_resume_kernel:
    RESTORE_ALL
    csrw    CSR_SCRATCH, zero
    XRET

    .align 2
    .weak fast_irq_vectors
START_POINT(fast_irq_vectors)
    j   system_vectors
START_POINT_END(fast_irq_vectors)
