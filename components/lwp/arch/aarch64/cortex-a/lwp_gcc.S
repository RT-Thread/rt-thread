/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       first version
 * 2023-07-16     Shell        Move part of the codes to C from asm in signal handling
 * 2023-08-03     Shell        Support of syscall restart (SA_RESTART)
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "rtconfig.h"
#include "asm-generic.h"
#include "asm-fpu.h"
#include "armv8.h"
#include "lwp_arch.h"

/*********************
 *      SPSR BIT     *
 *********************/

#define  SPSR_Mode(v)          ((v) << 0)
#define  SPSR_A64              (0 << 4)
#define  SPSR_RESEVRED_5       (0 << 5)
#define  SPSR_FIQ_MASKED(v)    ((v) << 6)
#define  SPSR_IRQ_MASKED(v)    ((v) << 7)
#define  SPSR_SERROR_MASKED(v) ((v) << 8)
#define  SPSR_D_MASKED(v)      ((v) << 9)
#define  SPSR_RESEVRED_10_19   (0 << 10)
#define  SPSR_IL(v)            ((v) << 20)
#define  SPSR_SS(v)            ((v) << 21)
#define  SPSR_RESEVRED_22_27   (0 << 22)
#define  SPSR_V(v)             ((v) << 28)
#define  SPSR_C(v)             ((v) << 29)
#define  SPSR_Z(v)             ((v) << 30)
#define  SPSR_N(v)             ((v) << 31)

/**************************************************/

.text

/*
 * void arch_start_umode(args, text, ustack, kstack);
 */
.global arch_start_umode
.type arch_start_umode, % function
arch_start_umode:
    mov sp, x3
    mov x4, #(SPSR_Mode(0) | SPSR_A64)
    msr daifset, #3
    dsb sy
    mrs x30, sp_el0
    /* user stack top */
    msr sp_el0, x2
    mov x3, x2
    msr spsr_el1, x4
    msr elr_el1, x1
    eret

/*
 * void arch_crt_start_umode(args, text, ustack, kstack);
 */
.global arch_crt_start_umode
.type arch_crt_start_umode, % function
arch_crt_start_umode:
    sub x4, x2, #0x10
    adr x2, lwp_thread_return
    ldr x5, [x2]
    str x5, [x4]
    ldr x5, [x2, #4]
    str x5, [x4, #4]
    ldr x5, [x2, #8]
    str x5, [x4, #8]

    mov x5, x4
    dc cvau, x5
    add x5, x5, #8
    dc cvau, x5
    dsb sy
    ic ialluis
    dsb sy

    msr sp_el0, x4

    mov sp, x3
    mov x4, #(SPSR_Mode(0) | SPSR_A64)
    msr daifset, #3
    dsb sy
    mrs x30, sp_el0
    msr spsr_el1, x4
    msr elr_el1, x1
    eret

.global arch_get_user_sp
arch_get_user_sp:
    mrs x0, sp_el0
    ret

.global arch_fork_exit
.global arch_clone_exit
arch_fork_exit:
arch_clone_exit:
    b  arch_syscall_exit

/*
void lwp_exec_user(void *args, void *kernel_stack, void *user_entry)
*/
.global lwp_exec_user
lwp_exec_user:
    mov sp, x1
    mov x4, #(SPSR_Mode(0) | SPSR_A64)
    ldr x3, =0x0000ffff80000000
    msr daifset, #3
    msr spsr_el1, x4
    msr elr_el1, x2
    eret

/*
 * void SVC_Handler(regs);
 * since this routine reset the SP, we take it as a start point
 */
START_POINT(SVC_Handler)
    /* x0 is initial sp */
    mov sp, x0

    msr daifclr, #3  /* enable interrupt */

    bl  rt_thread_self
    bl  lwp_user_setting_save

    ldp x8, x9, [sp, #(CONTEXT_OFFSET_X8)]
    and x0, x8, #0xf000
    cmp x0, #0xe000
    beq arch_signal_quit

    cmp x0, #0xf000
    beq ret_from_user

    uxtb x0, w8
    bl lwp_get_sys_api
    cmp x0, xzr
    mov x30, x0
    beq arch_syscall_exit
    ldp x0, x1, [sp, #(CONTEXT_OFFSET_X0)]
    ldp x2, x3, [sp, #(CONTEXT_OFFSET_X2)]
    ldp x4, x5, [sp, #(CONTEXT_OFFSET_X4)]
    ldp x6, x7, [sp, #(CONTEXT_OFFSET_X6)]
    blr x30
    /* jump explictly, make this code position independant */
    b arch_syscall_exit
START_POINT_END(SVC_Handler)

.global arch_syscall_exit
arch_syscall_exit:

    /**
     * @brief back up former x0 which is required to restart syscall, then setup
     * syscall return value in stack frame
     */
    mov x1, sp
    bl arch_syscall_prepare_signal

    msr daifset, #3

    ldp x2, x3, [sp], #0x10  /* SPSR and ELR. */
    msr spsr_el1, x3
    msr elr_el1, x2

    ldp x29, x30, [sp], #0x10
    msr sp_el0, x29
    ldp x28, x29, [sp], #0x10
    msr fpcr, x28
    msr fpsr, x29
    ldp x28, x29, [sp], #0x10
    ldp x26, x27, [sp], #0x10
    ldp x24, x25, [sp], #0x10
    ldp x22, x23, [sp], #0x10
    ldp x20, x21, [sp], #0x10
    ldp x18, x19, [sp], #0x10
    ldp x16, x17, [sp], #0x10
    ldp x14, x15, [sp], #0x10
    ldp x12, x13, [sp], #0x10
    ldp x10, x11, [sp], #0x10
    ldp x8, x9, [sp], #0x10
    ldp x6, x7, [sp], #0x10
    ldp x4, x5, [sp], #0x10
    ldp x2, x3, [sp], #0x10
    ldp x0, x1, [sp], #0x10
    RESTORE_FPU sp

/* the sp is reset to the outer most level, irq and fiq are disabled */
START_POINT(arch_ret_to_user)
    msr daifset, #3
    /* save exception frame */
    SAVE_FPU sp
    stp x0, x1, [sp, #-0x10]!
    stp x2, x3, [sp, #-0x10]!
    stp x4, x5, [sp, #-0x10]!
    stp x6, x7, [sp, #-0x10]!
    stp x8, x9, [sp, #-0x10]!
    stp x10, x11, [sp, #-0x10]!
    stp x12, x13, [sp, #-0x10]!
    stp x14, x15, [sp, #-0x10]!
    stp x16, x17, [sp, #-0x10]!
    stp x18, x19, [sp, #-0x10]!
    stp x20, x21, [sp, #-0x10]!
    stp x22, x23, [sp, #-0x10]!
    stp x24, x25, [sp, #-0x10]!
    stp x26, x27, [sp, #-0x10]!
    stp x28, x29, [sp, #-0x10]!

    mrs x0, fpcr
    mrs x1, fpsr
    stp x0, x1, [sp, #-0x10]!
    stp x29, x30, [sp, #-0x10]!

    /* pre-action */
    bl lwp_check_debug

    bl lwp_check_exit_request
    cbz w0, 1f
    /* exit on event */
    msr daifclr, #3
    mov x0, xzr
    b sys_exit
1:
    /* check if dbg ops exist */
    ldr x0, =rt_dbg_ops
    ldr x0, [x0]
    cbz x0, 3f
    bl dbg_thread_in_debug
    mov x1, #(1 << 21)
    mrs x2, spsr_el1
    cbz w0, 2f
    orr x2, x2, x1
    msr spsr_el1, x2
    b 3f
2:
    bic x2, x2, x1
    msr spsr_el1, x2
3:

    /**
     * push 2 dummy words to simulate a exception frame of interrupt
     * Note: in kernel state, the context switch dont saved the context
     */
    mrs x0, spsr_el1
    mrs x1, elr_el1
    stp x1, x0, [sp, #-0x10]!
    mov x0, sp
    msr daifclr, #3
    bl lwp_thread_signal_catch
    msr daifset, #3
    ldp x1, x0, [sp], #0x10
    msr spsr_el1, x0
    msr elr_el1, x1

    /* check debug */
    /* restore exception frame */
    ldp x29, x30, [sp], #0x10
    ldp x0, x1, [sp], #0x10
    msr fpcr, x0
    msr fpsr, x1

    ldp x28, x29, [sp], #0x10
    ldp x26, x27, [sp], #0x10
    ldp x24, x25, [sp], #0x10
    ldp x22, x23, [sp], #0x10
    ldp x20, x21, [sp], #0x10
    ldp x18, x19, [sp], #0x10
    ldp x16, x17, [sp], #0x10
    ldp x14, x15, [sp], #0x10
    ldp x12, x13, [sp], #0x10
    ldp x10, x11, [sp], #0x10
    ldp x8, x9, [sp], #0x10
    ldp x6, x7, [sp], #0x10
    ldp x4, x5, [sp], #0x10
    ldp x2, x3, [sp], #0x10
    ldp x0, x1, [sp], #0x10
    RESTORE_FPU sp

    stp x0, x1, [sp, #-0x10]!
    ldr x0, =rt_dbg_ops
    ldr x0, [x0]
    cmp x0, xzr
    ldp x0, x1, [sp], #0x10
    beq 1f

    /* save */
    SAVE_FPU sp
    stp x0, x1, [sp, #-0x10]!
    stp x2, x3, [sp, #-0x10]!
    stp x4, x5, [sp, #-0x10]!
    stp x6, x7, [sp, #-0x10]!
    stp x8, x9, [sp, #-0x10]!
    stp x10, x11, [sp, #-0x10]!
    stp x12, x13, [sp, #-0x10]!
    stp x14, x15, [sp, #-0x10]!
    stp x16, x17, [sp, #-0x10]!
    stp x18, x19, [sp, #-0x10]!
    stp x20, x21, [sp, #-0x10]!
    stp x22, x23, [sp, #-0x10]!
    stp x24, x25, [sp, #-0x10]!
    stp x26, x27, [sp, #-0x10]!
    stp x28, x29, [sp, #-0x10]!
    mrs x0, fpcr
    mrs x1, fpsr
    stp x0, x1, [sp, #-0x10]!
    stp x29, x30, [sp, #-0x10]!

    mrs x0, elr_el1
    bl dbg_attach_req

    /* restore */
    ldp x29, x30, [sp], #0x10
    ldp x0, x1, [sp], #0x10
    msr fpcr, x0
    msr fpsr, x1
    ldp x28, x29, [sp], #0x10
    ldp x26, x27, [sp], #0x10
    ldp x24, x25, [sp], #0x10
    ldp x22, x23, [sp], #0x10
    ldp x20, x21, [sp], #0x10
    ldp x18, x19, [sp], #0x10
    ldp x16, x17, [sp], #0x10
    ldp x14, x15, [sp], #0x10
    ldp x12, x13, [sp], #0x10
    ldp x10, x11, [sp], #0x10
    ldp x8, x9, [sp], #0x10
    ldp x6, x7, [sp], #0x10
    ldp x4, x5, [sp], #0x10
    ldp x2, x3, [sp], #0x10
    ldp x0, x1, [sp], #0x10
    RESTORE_FPU sp
1:
    eret
START_POINT_END(arch_ret_to_user)

.global lwp_check_debug
lwp_check_debug:
    ldr x0, =rt_dbg_ops
    ldr x0, [x0]
    cbnz x0, 1f
    ret
1:
    stp x29, x30, [sp, #-0x10]!
    bl dbg_check_suspend
    cbz w0, lwp_check_debug_quit

    mrs x2, sp_el0
    sub x2, x2, #0x10
    mov x3, x2
    msr sp_el0, x2
    ldr x0, =lwp_debugreturn
    ldr w1, [x0]
    str w1, [x2]
    ldr w1, [x0, #4]
    str w1, [x2, #4]

    dc cvau, x2
    add x2, x2, #4
    dc cvau, x2

    dsb sy
    isb sy

    ic ialluis
    isb sy

    mrs x0, elr_el1
    mrs x1, spsr_el1
    stp x0, x1, [sp, #-0x10]!
    msr elr_el1, x3 /* lwp_debugreturn */
    mov x1, #(SPSR_Mode(0) | SPSR_A64)
    orr x1, x1, #(1 << 21)
    msr spsr_el1, x1
    eret
ret_from_user:
    /* sp_el0 += 16 for drop ins lwp_debugreturn */
    mrs x0, sp_el0
    add x0, x0, #0x10
    msr sp_el0, x0
    /* now is el1, sp is pos(empty) - sizeof(context) */
    mov x0, sp
    add x0, x0, #0x220
    mov sp, x0
    ldp x0, x1, [sp], #0x10  /* x1 is origin spsr_el1 */
    msr elr_el1, x0          /* x0 is origin elr_el1 */
    msr spsr_el1, x1
lwp_check_debug_quit:
    ldp x29, x30, [sp], #0x10
    ret

.global arch_syscall_restart
arch_syscall_restart:
    msr daifset, 3

    mov sp, x1
    /* drop exception frame in user stack */
    msr sp_el0, x0

    /* restore previous exception frame */
    msr spsel, #0

    ldp x2, x3, [sp], #0x10
    msr elr_el1, x2
    msr spsr_el1, x3

    ldp x29, x30, [sp], #0x10

    ldp x28, x29, [sp], #0x10
    msr fpcr, x28
    msr fpsr, x29

    ldp x28, x29, [sp], #0x10
    ldp x26, x27, [sp], #0x10
    ldp x24, x25, [sp], #0x10
    ldp x22, x23, [sp], #0x10
    ldp x20, x21, [sp], #0x10
    ldp x18, x19, [sp], #0x10
    ldp x16, x17, [sp], #0x10
    ldp x14, x15, [sp], #0x10
    ldp x12, x13, [sp], #0x10
    ldp x10, x11, [sp], #0x10
    ldp x8, x9, [sp], #0x10
    ldp x6, x7, [sp], #0x10
    ldp x4, x5, [sp], #0x10
    ldp x2, x3, [sp], #0x10
    ldp x0, x1, [sp], #0x10
    RESTORE_FPU sp

    msr spsel, #1

    b vector_exception

arch_signal_quit:

    /* drop current exception frame */
    add sp, sp, #CONTEXT_SIZE
    mov x1, sp
    mrs x0, sp_el0
    bl  arch_signal_ucontext_restore
    add x0, x0, #-CONTEXT_SIZE
    msr sp_el0, x0

    /**
     * Note: Since we will reset spsr, but the reschedule will
     * corrupt the spsr, we diable irq for a short period here
     */
    msr daifset, #3

    /* restore previous exception frame */
    msr spsel, #0

    ldp x2, x3, [sp], #0x10
    msr elr_el1, x2
    msr spsr_el1, x3

    ldp x29, x30, [sp], #0x10

    ldp x28, x29, [sp], #0x10
    msr fpcr, x28
    msr fpsr, x29

    ldp x28, x29, [sp], #0x10
    ldp x26, x27, [sp], #0x10
    ldp x24, x25, [sp], #0x10
    ldp x22, x23, [sp], #0x10
    ldp x20, x21, [sp], #0x10
    ldp x18, x19, [sp], #0x10
    ldp x16, x17, [sp], #0x10
    ldp x14, x15, [sp], #0x10
    ldp x12, x13, [sp], #0x10
    ldp x10, x11, [sp], #0x10
    ldp x8, x9, [sp], #0x10
    ldp x6, x7, [sp], #0x10
    ldp x4, x5, [sp], #0x10
    ldp x2, x3, [sp], #0x10
    ldp x0, x1, [sp], #0x10
    RESTORE_FPU sp

    msr spsel, #1

    b arch_ret_to_user

/**
 * rt_noreturn
 * void arch_thread_signal_enter(
 *      int signo,                      -> x0
 *      siginfo_t *psiginfo,            -> x1
 *      void *exp_frame,                -> x2
 *      void *entry_uaddr,              -> x3
 *      lwp_sigset_t *save_sig_mask,    -> x4
 *      )
 */
.global arch_thread_signal_enter
arch_thread_signal_enter:
    mov x19, x0
    mov x20, x2 /* exp_frame */
    mov x21, x3

    /**
     * move exception frame to user stack
     */
    mrs x0, sp_el0
    mov x3, x4

    /* arch_signal_ucontext_save(user_sp, psiginfo, exp_frame, save_sig_mask); */
    bl arch_signal_ucontext_save
    mov x22, x0
    /* get and saved pointer to uframe */
    bl arch_signal_ucontext_get_frame
    mov x2, x0
    mov x0, x22

    dc cvau, x0
    dsb sy
    ic ialluis
    dsb sy

    /**
     * Brief: Prepare the environment for signal handler
     */

    /**
     * reset the cpsr
     * and drop exp frame on kernel stack, reset kernel sp
     *
     * Note: Since we will reset spsr, but the reschedule will
     * corrupt the spsr, we diable irq for a short period here
     */
    msr daifset, #3
    ldr x1, [x20, #CONTEXT_OFFSET_SPSR_EL1]
    msr spsr_el1, x1
    add sp, x20, #CONTEXT_SIZE

    /** reset user sp */
    msr sp_el0, x0
    /** set the return address to the sigreturn */
    mov x30, x0

    cbnz x21, 1f
    mov x21, x30
1:
    /** set the entry address of signal handler */
    msr elr_el1, x21

    /* siginfo is above the return address */
    add x1, x30, UCTX_ABI_OFFSET_TO_SI
    /* uframe is saved in x2 */
    mov x0, x19

    /**
     * handler(signo, psi, ucontext);
     *
     */
    eret

lwp_debugreturn:
    mov x8, 0xf000
    svc #0

.global lwp_sigreturn
lwp_sigreturn:
    mov x8, #0xe000
    svc #0

lwp_thread_return:
    mov x0, xzr
    mov x8, #0x01
    svc #0

.globl arch_get_tidr
arch_get_tidr:
    mrs x0, tpidr_el0
    ret

.global arch_set_thread_area
arch_set_thread_area:
.globl arch_set_tidr
arch_set_tidr:
    msr tpidr_el0, x0
    ret
