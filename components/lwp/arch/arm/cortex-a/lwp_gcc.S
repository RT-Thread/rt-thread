/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Jesven       first version
 */

#include "rtconfig.h"

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
 * void lwp_user_entry(args, text, data);
 */
.global lwp_user_entry
.type lwp_user_entry, % function
lwp_user_entry:
    mrs     r9, cpsr
    bic     r9, #0x1f
    orr     r9, #Mode_USR
    cpsid i
    msr     spsr, r9

    ldr     r3, =0x80000000 ;/* user stack top */
    /* set data address. */
    movs    pc, r1

.global set_user_context
set_user_context:
    cps #Mode_SYS
    sub sp, r0, #12
    ldr r0, =lwp_thread_return
    ldr r1, [r0]
    str r1, [sp]
    ldr r1, [r0, #4]
    str r1, [sp, #4]
    ldr r1, [r0, #8]
    str r1, [sp, #8]
    mov lr, sp
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0   ;//iciallu
    dsb
    cps #Mode_SVC
    mov pc, lr

/*
int lwp_set_thread_context(void *new_thread_stack, void *origin_thread_stack, void *user_stack, void **thread_sp, int tid);
*/
.global lwp_set_thread_context
lwp_set_thread_context:
    sub r12, r1, sp /* origin, r12 = origin sp offset */
    sub r0, r0, r12 /* new sp */
    stmfd r0!, {lr}
    stmfd r0!, {lr}
    stmfd r0!, {r12}
    sub r12, sp, fp  /* new, r1 = origin fp offset */
    sub r1, r0, r12
    add r1, #12  /* new fp */
    stmfd r0!, {r1} /* fp */
    stmfd r0!, {r1 - r10}
    mov r12, #0
    stmfd r0!, {r12} /* new thread return value */
    mrs r1, cpsr
    stmfd r0!, {r1} /* spsr */
    mov r1, #0
    stmfd r0!, {r1} /* now user lr is 0 */
    stmfd r0!, {r2} /* user sp */
#ifdef RT_USING_FPU
    stmfd r0!, {r1} /* not use fpu */
#endif
    str r0, [r3]
    ldr r0, [sp]
    mov pc, lr

/*
 * void SVC_Handler(void);
 */
.global vector_swi
.type vector_swi, % function
vector_swi:
    push {lr}
    mrs lr, spsr
    push {r4, r5, lr}
    tst lr, #(1 << 7)   /* mask irq ? */
    bne 1f
    cpsie i
1:
    push {r0 - r3, r12}
    and r0, r7, #0xff
    cmp r0, #0xfe
    beq lwp_signal_quit
#ifdef RT_USING_GDBSERVER
    cmp r0, #0xff
    beq ret_from_user
#endif
    bl lwp_get_sys_api
    cmp r0, #0           /* r0 = api */
    mov lr, r0
    pop {r0 - r3, r12}
    beq svc_exit
    blx lr

svc_exit:
    mrs r4, cpsr
    cpsid i
    tst r4, #(1 << 7)   /* mask irq ? */
    pop {r4, r5, lr}
    orrne lr, #(1 << 7)
    msr spsr_cxsf, lr
    pop {lr}

.global ret_to_user
ret_to_user:
    push {r0-r3, r12, lr}
    bl lwp_signal_check
    cmp r0, #0
    pop {r0-r3, r12, lr}
    bne user_do_signal

    movs pc, lr

#ifdef RT_USING_LWP
.global lwp_check_exit
lwp_check_exit:
    push {r0 - r12, lr}
    bl lwp_check_exit_request
    cmp r0, #0
    beq 1f
    mov r0, #0
    bl sys_exit
1:
    pop {r0 - r12, pc}
#endif

#ifdef RT_USING_GDBSERVER
.global lwp_check_debug
lwp_check_debug:
    push {r0 - r12, lr}
    bl lwp_check_debug_suspend
    cmp r0, #0
    beq lwp_check_debug_quit

    cps #Mode_SYS
    sub sp, #8
    ldr r0, =lwp_debugreturn
    ldr r1, [r0]
    str r1, [sp]
    ldr r1, [r0, #4]
    str r1, [sp, #4]
    mov r0, #0
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
    pop {r0 - r12, pc}
#endif

lwp_signal_quit:
    cpsid i
    pop {r0 - r3, r12}
    pop {r4, r5, lr}
    pop {lr}
    bl lwp_signal_restore
    /* r0 is user_ctx : ori sp, pc, cpsr*/
    ldr r1, [r0]
    ldr r2, [r0, #4]
    ldr r3, [r0, #8]
    msr spsr_cxsf, r3
    mov lr, r2
    cps #Mode_SYS
    mov sp, r1
    pop {r0-r12, lr}
    cps #Mode_SVC
    b ret_to_user

user_do_signal:
    mov r0, r0
    cps #Mode_SYS
    push {r0-r12, lr}

    sub sp, #8
    ldr r0, =lwp_sigreturn
    ldr r1, [r0]
    str r1, [sp]
    ldr r1, [r0, #4]
    str r1, [sp, #4]
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0   ;//iciallu
    dsb

    mov r5, sp  ;//if func is 0
    mov lr, sp

    add r0, sp, #8 /* lwp_sigreturn */
    cps #Mode_SVC
    mov r1, lr
    mrs r2, spsr
    bl  lwp_signal_backup
    /* r0 is signal */
    mov r4, r0
    bl lwp_sighandler_get
    mov lr, r0
    cmp lr, #0
    moveq lr, r5
    mov r0, r4
    movs pc, lr

lwp_debugreturn:
    mov r7, #0xff
    svc #0

lwp_sigreturn:
    mov r7, #0xfe
    svc #0

lwp_thread_return:
    mov r0, #0
    mov r7, #0x01
    svc #0

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

.globl rt_cpu_get_thread_idr
rt_cpu_get_thread_idr:
    mrc p15, 0, r0, c13, c0, 3
    bx lr

.global lwp_set_thread_area
lwp_set_thread_area:
.globl rt_cpu_set_thread_idr
rt_cpu_set_thread_idr:
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
