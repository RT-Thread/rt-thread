/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Jesven       first version
 * 2021-02-03     lizhirui     port to riscv64
 * 2021-02-19     lizhirui     port to new version of rt-smart
 * 2022-11-08     Wangxiaoyao  Cleanup codes;
 *                             Support new context switch
 * 2023-07-16     Shell        Move part of the codes to C from asm in signal handling
 */

#include "rtconfig.h"

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif /* __ASSEMBLY__ */

#include "asm.h"
#include "csr.h"

.section      .text.lwp

/*
 * void arch_start_umode(args, text, ustack, kstack);
 */
.global arch_start_umode
.type arch_start_umode, % function
arch_start_umode:
    // load kstack for user process
    csrw CSR_SCRATCH, a3
    li t0, SR_PP | SR_IE    // set as user mode, close interrupt
    csrc CSR_STATUS, t0
    li t0, SR_PIE // enable interrupt when return to user mode
    csrs CSR_STATUS, t0

    csrw CSR_EPC, a1
    mv sp, a2
    sret//enter user mode

/*
 * void arch_crt_start_umode(args, text, ustack, kstack);
 */
.global arch_crt_start_umode
.type arch_crt_start_umode, % function
arch_crt_start_umode:
    li t0, SR_PP | SR_IE    // set as user mode, close interrupt
    csrc CSR_STATUS, t0
    li t0, SR_PIE // enable interrupt when return to user mode
    csrs CSR_STATUS, t0

    csrw CSR_EPC, a1
    mv s0, a0
    mv s1, a1
    mv s2, a2
    mv s3, a3
    mv a0, s2
    call lwp_copy_return_code_to_user_stack
    mv a0, s2
    call lwp_fix_sp
    mv sp, a0//user_sp
    mv ra, a0//return address
    mv a0, s0//args

    csrw CSR_SCRATCH, s3
    sret//enter user mode

/**
 * Unify exit point from kernel mode to enter user space
 * we handle following things here:
 * 1. restoring user mode debug state (not support yet)
 * 2. handling thread's exit request
 * 3. handling POSIX signal
 * 4. restoring user context
 * 5. jump to user mode
 */
.global arch_ret_to_user
arch_ret_to_user:
    // TODO: we don't support kernel gdb server in risc-v yet
    // so we don't check debug state here and handle debugging bussiness

    call lwp_check_exit_request
    beqz a0, 1f
    mv a0, x0
    call sys_exit

1:
    mv a0, sp
    call lwp_thread_signal_catch

ret_to_user_exit:
    RESTORE_ALL
    // `RESTORE_ALL` also reset sp to user sp, and setup xscratch
    sret

/**
 * Restore user context from exception frame stroraged in ustack
 * And handle pending signals;
 */
arch_signal_quit:
    REG_L a0, FRAME_OFF_SP(sp)
    call arch_signal_ucontext_restore

    /* reset kernel sp to the stack */
    addi sp, sp, CTX_ALL_REG_NR * SZREG
    REG_S sp, FRAME_OFF_SP(a0)
    /* return value is user sp */
    mv sp, a0

    /* restore user sp before enter trap */
    addi a0, sp, CTX_ALL_REG_NR * SZREG
    csrw CSR_SCRATCH, a0


    RESTORE_ALL
    SAVE_ALL
    j arch_ret_to_user

/**
 * rt_noreturn
 * void arch_thread_signal_enter(
 *      int signo,                      -> a0
 *      siginfo_t *psiginfo,            -> a1
 *      void *exp_frame,                -> a2
 *      void *entry_uaddr,              -> a3
 *      lwp_sigset_t *save_sig_mask,    -> a4
 *      )
 */
.global arch_thread_signal_enter
arch_thread_signal_enter:
    mv s3, a2
    mv s2, a0
    mv s1, a3

    REG_L t0, FRAME_OFF_SP(a2)
    mv a3, t0
    call arch_signal_ucontext_save

    /** restore kernel sp */
    addi sp, s3, CTX_ALL_REG_NR * SZREG

    /**
     * set regiter RA to user signal handler
     * set sp to user sp & save kernel sp in xscratch
     */
    mv ra, a0
    csrw CSR_SCRATCH, sp
    mv sp, a0

    /**
     * s1 is signal_handler,
     * s1 = !s1 ? lwp_sigreturn : s1;
     */
    bnez s1, 1f
    mv s1, ra

1:
    /* enter user mode and enable interrupt when return to user mode */
    li t0, SR_PP
    csrc CSR_STATUS, t0
    li t0, SR_PIE
    csrs CSR_STATUS, t0

    /* xepc <- signal_handler */
    csrw CSR_EPC, s1
    /* a0 <- signal id */
    mv a0, s2
    /* a1 <- siginfo */
    add a1, sp, 16
    /* dummy a2 */
    mv a2, a1

    /* restore user GP */
    REG_L gp, FRAME_OFF_GP(s3)

    /**
     * handler(signo, psi, ucontext);
     */
    sret

.align 3
lwp_debugreturn:
    li a7, 0xff
    ecall

.align 3
.global lwp_sigreturn
lwp_sigreturn:
    li a7, 0xfe
    ecall

.align 3
lwp_sigreturn_end:

.align 3
.global lwp_thread_return
lwp_thread_return:
    li a0, 0
    li a7, 1
    ecall

.align 3
.global lwp_thread_return_end
lwp_thread_return_end:

.globl arch_get_tidr
arch_get_tidr:
    mv a0, tp
    ret

.global arch_set_thread_area
arch_set_thread_area:
.globl arch_set_tidr
arch_set_tidr:
    mv tp, a0
    ret

.global arch_clone_exit
.global arch_fork_exit
arch_fork_exit:
arch_clone_exit:
    j arch_syscall_exit

START_POINT(syscall_entry)
#ifndef ARCH_USING_NEW_CTX_SWITCH
    //swap to thread kernel stack
    csrr t0, CSR_STATUS
    andi t0, t0, 0x100
    beqz t0, __restore_sp_from_tcb

__restore_sp_from_CSR_SCRATCH: // from kernel
    csrr t0, CSR_SCRATCH
    j __move_stack_context

__restore_sp_from_tcb: // from user
    jal rt_thread_self
    jal get_thread_kernel_stack_top
    mv t0, a0

__move_stack_context:
    mv t1, sp//src
    mv sp, t0//switch stack
    addi sp, sp, -CTX_ALL_REG_NR * SZREG
    //copy context
    li s0, CTX_ALL_REG_NR//cnt
    mv t2, sp//dst

copy_context_loop:
    REG_L t0, 0(t1)
    REG_S t0, 0(t2)
    addi s0, s0, -1
    addi t1, t1, 8
    addi t2, t2, 8
    bnez s0, copy_context_loop
#endif /* ARCH_USING_NEW_CTX_SWITCH */

    /* fetch SYSCALL ID */
    REG_L a7, 17 * SZREG(sp)
    addi a7, a7, -0xfe
    beqz a7, arch_signal_quit

#ifdef ARCH_MM_MMU
    /* save setting when syscall enter */
    call  rt_thread_self
    call  lwp_user_setting_save
#endif

    mv a0, sp
    OPEN_INTERRUPT
    call syscall_handler
    j arch_syscall_exit
START_POINT_END(syscall_entry)

.global arch_syscall_exit
arch_syscall_exit:
    CLOSE_INTERRUPT

    #if defined(ARCH_MM_MMU)
        REG_L s0, FRAME_OFF_XSTATUS(sp)
        andi s0, s0, 0x100
        bnez s0, dont_ret_to_user
        j arch_ret_to_user
    #endif
dont_ret_to_user:

#ifdef ARCH_MM_MMU
    /* restore setting when syscall exit */
    call  rt_thread_self
    call  lwp_user_setting_restore

    /* after restore the reg `tp`, need modify context */
    REG_S tp, 4 * SZREG(sp)
#endif

    //restore context
    RESTORE_ALL
    csrw CSR_SCRATCH, zero
    sret
