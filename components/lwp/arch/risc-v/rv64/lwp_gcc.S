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
 */

#include "rtconfig.h"

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif /* __ASSEMBLY__ */

#include "cpuport.h"
#include "encoding.h"
#include "stackframe.h"

.section      .text.lwp

/*
 * void arch_start_umode(args, text, ustack, kstack);
 */
.global arch_start_umode
.type arch_start_umode, % function
arch_start_umode:
    // load kstack for user process
    csrw sscratch, a3
    li t0, SSTATUS_SPP | SSTATUS_SIE    // set as user mode, close interrupt
    csrc sstatus, t0 
    li t0, SSTATUS_SPIE // enable interrupt when return to user mode
    csrs sstatus, t0

    csrw sepc, a1
    mv a3, a2
    sret//enter user mode

/*
 * void arch_crt_start_umode(args, text, ustack, kstack);
 */
.global arch_crt_start_umode
.type arch_crt_start_umode, % function
arch_crt_start_umode:
    li t0, SSTATUS_SPP | SSTATUS_SIE    // set as user mode, close interrupt
    csrc sstatus, t0
    li t0, SSTATUS_SPIE // enable interrupt when return to user mode
    csrs sstatus, t0

    csrw sepc, a1
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

    csrw sscratch, s3
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
    call lwp_signal_check
    beqz a0, ret_to_user_exit
    J user_do_signal

ret_to_user_exit:
    RESTORE_ALL
    // `RESTORE_ALL` also reset sp to user sp, and setup sscratch
    sret

/**
 * Restore user context from exception frame stroraged in ustack
 * And handle pending signals;
 */
arch_signal_quit:
    call lwp_signal_restore
    call arch_get_usp_from_uctx
    // return value is user sp
    mv sp, a0

    // restore user sp before enter trap
    addi a0, sp, CTX_REG_NR * REGBYTES 
    csrw sscratch, a0

    RESTORE_ALL
    SAVE_ALL
    j arch_ret_to_user

/**
 * Prepare and enter user signal handler
 * Move user exception frame and setup signal return
 * routine in user stack
 */
user_do_signal:
    /* prefetch ustack to avoid corrupted status in RESTORE/STORE pair below */
    LOAD t0, FRAME_OFF_SP(sp)
    addi t1, t0, -CTX_REG_NR * REGBYTES
    LOAD t2, (t0)
    li t3, -0x1000
1:
    add t0, t0, t3
    LOAD t2, (t0)
    bgt t0, t1, 1b

    /** restore and backup kernel sp carefully to avoid leaking */
    addi t0, sp, CTX_REG_NR * REGBYTES
    csrw sscratch, t0

    RESTORE_ALL
    SAVE_ALL

    /**
     * save lwp_sigreturn in user memory
     */
    mv s0, sp
    la t0, lwp_sigreturn
    la t1, lwp_sigreturn_end
    // t1 <- size
    sub t1, t1, t0
    // s0 <- dst
    sub s0, s0, t1
    mv s2, t1
lwp_sigreturn_copy_loop:
    addi t2, t1, -1
    add t3, t0, t2
    add t4, s0, t2
    lb t5, 0(t3)
    sb t5, 0(t4)
    mv t1, t2
    bnez t1, lwp_sigreturn_copy_loop

    /**
     * 1. clear sscratch & restore kernel sp to 
     *    enter kernel mode routine
     * 2. storage exp frame address to restore context, 
     *    by calling to lwp_signal_backup
     * 3. storage lwp_sigreturn entry address
     * 4. get signal id as param for signal handler
     */
    mv s1, sp
    csrrw sp, sscratch, x0

    /**
     * synchronize dcache & icache if target is
     * a Harvard Architecture machine, otherwise
     * do nothing
     */
    mv a0, s0
    mv a1, s2
    call rt_hw_sync_cache_local

    /**
     * backup user sp (point to saved exception frame, skip sigreturn routine)
     * And get signal id

     * a0: user sp 
     * a1: user_pc (not used, marked as 0 to avoid abuse)
     * a2: user_flag (not used, marked as 0 to avoid abuse)
     */
    mv a0, s1
    mv a1, zero
    mv a2, zero
    call lwp_signal_backup

    /**
     * backup signal id in s2, 
     * and get sighandler by signal id
     */
    mv s2, a0
    call lwp_sighandler_get

    /**
     * set regiter RA to user signal handler
     * set sp to user sp & save kernel sp in sscratch
     */
    mv ra, s0
    csrw sscratch, sp
    mv sp, s0

    /**
     * a0 is signal_handler,
     * s1 = s0 == NULL ? lwp_sigreturn : s0;
     */
    mv s1, s0
    beqz a0, skip_user_signal_handler
    mv s1, a0

skip_user_signal_handler:
    // enter user mode and enable interrupt when return to user mode
    li t0, SSTATUS_SPP
    csrc sstatus, t0
    li t0, SSTATUS_SPIE
    csrs sstatus, t0

    // sepc <- signal_handler
    csrw sepc, s1
    // a0 <- signal id
    mv a0, s2
    sret

.align 3
lwp_debugreturn:
    li a7, 0xff
    ecall

.align 3
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

.global syscall_entry
syscall_entry:
#ifndef ARCH_USING_NEW_CTX_SWITCH
    //swap to thread kernel stack
    csrr t0, sstatus
    andi t0, t0, 0x100
    beqz t0, __restore_sp_from_tcb

__restore_sp_from_sscratch: // from kernel
    csrr t0, sscratch
    j __move_stack_context

__restore_sp_from_tcb: // from user
    la a0, rt_current_thread
    LOAD a0, 0(a0)
    jal get_thread_kernel_stack_top
    mv t0, a0

__move_stack_context:
    mv t1, sp//src
    mv sp, t0//switch stack
    addi sp, sp, -CTX_REG_NR * REGBYTES
    //copy context
    li s0, CTX_REG_NR//cnt
    mv t2, sp//dst

copy_context_loop:
    LOAD t0, 0(t1)
    STORE t0, 0(t2)
    addi s0, s0, -1
    addi t1, t1, 8
    addi t2, t2, 8
    bnez s0, copy_context_loop
#endif /* ARCH_USING_NEW_CTX_SWITCH */

    /* fetch SYSCALL ID */
    LOAD a7, 17 * REGBYTES(sp)
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
    
.global arch_syscall_exit
arch_syscall_exit:
    CLOSE_INTERRUPT

    #if defined(ARCH_MM_MMU)
        LOAD s0, 2 * REGBYTES(sp)
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
    STORE tp, 4 * REGBYTES(sp)
#endif

    //restore context
    RESTORE_ALL
    csrw sscratch, zero
    sret
