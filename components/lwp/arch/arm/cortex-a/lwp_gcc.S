/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Jesven       first version
 * 2023-07-16     Shell        Move part of the codes to C from asm in signal handling
 */

#include "rtconfig.h"
#include "asm-generic.h"

#define  Mode_USR       0x10
#define  Mode_FIQ       0x11
#define  Mode_IRQ       0x12
#define  Mode_SVC       0x13
#define  Mode_MON       0x16
#define  Mode_ABT       0x17
#define  Mode_UDF       0x1B
#define  Mode_SYS       0x1F

#define A_Bit        0x100 
#define I_Bit        0x80 @; when I bit is set, IRQ is disabled
#define F_Bit        0x40 @; when F bit is set, FIQ is disabled
#define T_Bit        0x20

.cpu cortex-a9
.syntax unified
.text

/*
 * void arch_start_umode(args, text, ustack, kstack);
 */
.global arch_start_umode
.type arch_start_umode, % function
arch_start_umode:
    mrs     r9, cpsr
    bic     r9, #0x1f
    orr     r9, #Mode_USR
    cpsid i
    msr     spsr, r9
    mov     sp, r3

    /* set user stack top */
    cps #Mode_SYS
    mov sp, r2
    cps #Mode_SVC
    mov     r3, r2

    /* set data address. */
    movs    pc, r1

/*
 * void arch_crt_start_umode(args, text, ustack, kstack);
 */
.global arch_crt_start_umode
.type arch_crt_start_umode, % function
arch_crt_start_umode:
    cps #Mode_SYS
    sub sp, r2, #16
    ldr r2, =lwp_thread_return
    ldr r4, [r2]
    str r4, [sp]
    ldr r4, [r2, #4]
    str r4, [sp, #4]
    ldr r4, [r2, #8]
    str r4, [sp, #8]

    mov r4, sp
    mcr p15, 0, r4, c7, c11, 1   ;//dc cmvau
    add r4, #4
    mcr p15, 0, r4, c7, c11, 1   ;//dc cmvau
    add r4, #4
    mcr p15, 0, r4, c7, c11, 1   ;//dc cmvau
    dsb
    isb
    mcr p15, 0, r4, c7, c5, 0   ;//iciallu
    dsb
    isb

    mov lr, sp
    cps #Mode_SVC

    mrs     r9, cpsr
    bic     r9, #0x1f
    orr     r9, #Mode_USR
    cpsid i
    msr     spsr, r9
    mov     sp, r3

    /* set data address. */
    movs    pc, r1

/*
void arch_set_thread_context(void *exit_addr, void *new_thread_stack, void *user_stack, void **thread_sp);
*/
.global arch_set_thread_context
arch_set_thread_context:
    sub r1, #(10 * 4 + 4 * 4) /* {r4 - r12, lr} , {r4, r5, spsr, u_pc} */
    stmfd r1!, {r0}
    mov r12, #0
    stmfd r1!, {r12}
    stmfd r1!, {r1 - r12}
    stmfd r1!, {r12} /* new thread return value */
    mrs r12, cpsr
    orr r12, #(1 << 7) /* disable irq */
    stmfd r1!, {r12} /* spsr */
    mov r12, #0
    stmfd r1!, {r12} /* now user lr is 0 */
    stmfd r1!, {r2} /* user sp */
#ifdef RT_USING_FPU
    stmfd r1!, {r12} /* not use fpu */
#endif
    str r1, [r3]
    mov pc, lr

.global arch_get_user_sp
arch_get_user_sp:
    cps #Mode_SYS
    mov r0, sp
    cps #Mode_SVC
    mov pc, lr

.global sys_fork
.global sys_vfork
.global arch_fork_exit
sys_fork:
sys_vfork:
    push {r4 - r12, lr}
    bl _sys_fork
arch_fork_exit:
    pop {r4 - r12, lr}
    b arch_syscall_exit

.global sys_clone
.global arch_clone_exit
sys_clone:
    push {r4 - r12, lr}
    bl _sys_clone
arch_clone_exit:
    pop {r4 - r12, lr}
    b arch_syscall_exit
/*
void lwp_exec_user(void *args, void *kernel_stack, void *user_entry)
*/
.global lwp_exec_user
lwp_exec_user:
    cpsid i
    mov sp, r1
    mov lr, r2
    mov r2, #Mode_USR
    msr spsr_cxsf, r2
    ldr r3, =0x80000000
    b arch_ret_to_user

/*
 * void SVC_Handler(void);
 */
.global vector_swi
.type vector_swi, % function
START_POINT(vector_swi)
    push {lr}
    mrs lr, spsr
    push {r4, r5, lr}

    cpsie i

    push {r0 - r3, r12}

    bl rt_thread_self
    bl lwp_user_setting_save

    and r0, r7, #0xf000
    cmp r0, #0xe000
    beq arch_signal_quit

    cmp r0, #0xf000
    beq ret_from_user
    and r0, r7, #0xff
    bl lwp_get_sys_api
    cmp r0, #0           /* r0 = api */
    mov lr, r0

    pop {r0 - r3, r12}
    beq arch_syscall_exit
    blx lr
START_POINT_END(vector_swi)

.global arch_syscall_exit
arch_syscall_exit:
    cpsid i
    pop {r4, r5, lr}
    msr spsr_cxsf, lr
    pop {lr}

.global arch_ret_to_user
arch_ret_to_user:
    push {r0-r12, lr}
    bl lwp_check_debug
    bl lwp_check_exit_request
    cmp r0, #0
    beq 1f
    mov r0, #0
    b sys_exit
1:
    mov r0, sp
    /* r0 -> exp frame */
    bl lwp_thread_signal_catch
    pop {r0-r12, lr}

    push {r0}
    ldr r0, =rt_dbg_ops
    ldr r0, [r0]
    cmp r0, #0
    pop  {r0}
    beq 2f
    push {r0-r3, r12, lr}
    mov r0, lr
    bl dbg_attach_req
    pop {r0-r3, r12, lr}
2:
    movs pc, lr

#ifdef RT_USING_SMART
.global lwp_check_debug
lwp_check_debug:
    ldr r0, =rt_dbg_ops
    ldr r0, [r0]
    cmp r0, #0
    bne 1f
    bx  lr
1:
    push {lr}
    bl dbg_check_suspend
    cmp r0, #0
    beq lwp_check_debug_quit

    cps #Mode_SYS
    sub sp, #8
    ldr r0, =lwp_debugreturn
    ldr r1, [r0]
    str r1, [sp]
    ldr r1, [r0, #4]
    str r1, [sp, #4]

    mov r1, sp
    mcr p15, 0, r1, c7, c11, 1   ;//dc cmvau
    add r1, #4
    mcr p15, 0, r1, c7, c11, 1   ;//dc cmvau
    dsb
    isb
    mcr p15, 0, r0, c7, c5, 0   ;//iciallu
    dsb
    isb

    mov r0, sp /* lwp_debugreturn */
    cps #Mode_SVC

    mrs r1, spsr
    push {r1}
    mov r1, #Mode_USR
    msr spsr_cxsf, r1
    movs pc, r0
ret_from_user:
    cps #Mode_SYS
    add sp, #8
    cps #Mode_SVC
    /*
    pop {r0 - r3, r12}
    pop {r4 - r6, lr}
    */
    add sp, #(4*9)
    pop {r4}
    msr spsr_cxsf, r4
lwp_check_debug_quit:
    pop {pc}

arch_signal_quit:
    cpsid i
    /* drop context of signal handler */
    pop {r0 - r3, r12}
    pop {r4, r5, lr}
    pop {lr}

    /* restore context */
    cps #Mode_SYS
    mov r0, sp
    cps #Mode_SVC
    bl arch_signal_ucontext_restore

    /* lr <- *(&frame.ip) */
    ldr lr, [r0]
    cps #Mode_SYS
    mov sp, r0

    /* drop ip in the frame and restore cpsr */
    pop {r0}
    pop {r0}
    msr spsr_cxsf, r0
    pop {r0-r12, lr}
    cps #Mode_SVC

    b arch_ret_to_user

/**
 * rt_noreturn
 * void arch_thread_signal_enter(
 *      int signo,                      -> r0
 *      siginfo_t *psiginfo,            -> r1
 *      void *exp_frame,                -> r2
 *      void *entry_uaddr,              -> r3
 *      lwp_sigset_t *save_sig_mask,    -> ??
 * )
 */
.global arch_thread_signal_enter
arch_thread_signal_enter:
    mov r4, r0
    mov r5, r3

    cps #Mode_SYS
    mov r0, lr
    mov r3, sp
    cps #Mode_SVC
    bl arch_signal_ucontext_save

    /* reset user sp */
    cps #Mode_SYS
    mov sp, r0
    mov lr, r0
    cps #Mode_SVC

    /* r1,r2 <- new_user_sp */
    mov r1, r0
    mov r2, r0
    /* r0 <- signo */
    mov r0, r4

    mov r1, r0
    mcr p15, 0, r1, c7, c11, 1   ;//dc cmvau
    add r1, #4
    mcr p15, 0, r1, c7, c11, 1   ;//dc cmvau
    dsb
    isb
    mcr p15, 0, r0, c7, c5, 0   ;//iciallu
    dsb
    isb

    /* r4 <- &sigreturn */
    mov r4, r2

    /* lr <- user_handler() */
    mov lr, r5
    cmp lr, #0
    moveq lr, r4

    /* r1 <- siginfo */
    mov r1, r2
    add r1, #8
    /* handler(signo, siginfo, ucontext) */
    movs pc, lr

lwp_debugreturn:
    mov r7, #0xf000
    svc #0

.global lwp_sigreturn
lwp_sigreturn:
    mov r7, #0xe000
    svc #0

lwp_thread_return:
    mov r0, #0
    mov r7, #0x01
    svc #0
#endif

.global check_vfp
check_vfp:
#ifdef RT_USING_FPU
    vmrs r0, fpexc
    ubfx r0, r0, #30, #1
#else
    mov r0, #0
#endif
    mov pc, lr

.global get_vfp
get_vfp:
#ifdef RT_USING_FPU
    vstmia r0!, {d0-d15}
    vstmia r0!, {d16-d31}
    vmrs r1, fpscr
    str  r1, [r0]
#endif
    mov pc, lr

.globl arch_get_tidr
arch_get_tidr:
    mrc p15, 0, r0, c13, c0, 3
    bx lr

.global arch_set_thread_area
arch_set_thread_area:
.globl arch_set_tidr
arch_set_tidr:
    mcr p15, 0, r0, c13, c0, 3
    bx lr

/* kuser suppurt */
    .macro  kuser_pad, sym, size
    .if (. - \sym) & 3
    .rept   4 - (. - \sym) & 3
    .byte   0
    .endr
    .endif
    .rept   (\size - (. - \sym)) / 4
    .word   0xe7fddef1
    .endr
    .endm

.align  5
.globl  __kuser_helper_start
__kuser_helper_start:
__kuser_cmpxchg64:              @ 0xffff0f60
    stmfd   sp!, {r4, r5, r6, lr}
    ldmia   r0, {r4, r5}            @ load old val
    ldmia   r1, {r6, lr}            @ load new val
1:  ldmia   r2, {r0, r1}            @ load current val
    eors    r3, r0, r4          @ compare with oldval (1)
    eorseq  r3, r1, r5          @ compare with oldval (2)
2:  stmiaeq r2, {r6, lr}            @ store newval if eq
    rsbs    r0, r3, #0          @ set return val and C flag
    ldmfd   sp!, {r4, r5, r6, pc}

    kuser_pad __kuser_cmpxchg64, 64

__kuser_memory_barrier:             @ 0xffff0fa0
    dmb
    mov pc, lr

    kuser_pad __kuser_memory_barrier, 32

__kuser_cmpxchg:                @ 0xffff0fc0
1:  ldr r3, [r2]            @ load current val
    subs    r3, r3, r0          @ compare with oldval
2:  streq   r1, [r2]            @ store newval if eq
    rsbs    r0, r3, #0          @ set return val and C flag
    mov pc, lr

kuser_pad __kuser_cmpxchg, 32

__kuser_get_tls:                @ 0xffff0fe0
    mrc p15, 0, r0, c13, c0, 3  @ 0xffff0fe8 hardware TLS code
    mov pc, lr
    ldr r0, [pc, #(16 - 8)] @ read TLS, set in kuser_get_tls_init

    kuser_pad __kuser_get_tls, 16

    .rep    3
    .word   0           @ 0xffff0ff0 software TLS value, then
    .endr               @ pad up to __kuser_helper_version

__kuser_helper_version:             @ 0xffff0ffc
    .word   ((__kuser_helper_end - __kuser_helper_start) >> 5)

    .globl  __kuser_helper_end
__kuser_helper_end:
