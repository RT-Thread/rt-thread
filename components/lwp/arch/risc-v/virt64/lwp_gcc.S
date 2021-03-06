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
 */

#include "rtconfig.h"

#include "cpuport.h"
#include "encoding.h"
#include "stackframe.h"

.section      .text.lwp

/*
 * void lwp_user_entry(args, text, data);
 */
.global lwp_user_entry
.type lwp_user_entry, % function
lwp_user_entry:
    csrci sstatus, 8//set sstatus.spp = 0
    csrw sepc, a1
    mv s0, a0
    mv a0, a3
    call lwp_fix_sp
    mv sp, a0//user_sp
    mv ra, a0//return address
    mv a0, s0//args
    sret//enter user mode

.global set_user_context
set_user_context:
    addi sp, sp, -8
    STORE ra, 0(sp)
    call lwp_copy_return_code_to_user_stack
    LOAD ra, 0(sp)
    addi sp, sp, 8
    ret

/*
int lwp_set_thread_context(void *new_thread_stack, void *origin_thread_stack, void *user_stack, void **thread_sp, int tid);
*/
.global lwp_set_thread_context
lwp_set_thread_context:
    ret//don't support this temporarily

.global ret_to_user
ret_to_user:
    call lwp_signal_check
    beqz a0, ret_to_user_exit
    RESTORE_ALL
    //now sp is user sp
    J user_do_signal

ret_to_user_exit:
    RESTORE_ALL
    sret

/*#ifdef RT_USING_LWP
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
#endif*/

/*#ifdef RT_USING_GDBSERVER
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
    mov r0, sp // lwp_debugreturn
    cps #Mode_SVC

    mrs r1, spsr
    push {r1}
    mov r1, #Mode_USR
    msr spsr_cxsf, r1
    movs pc, r0
ret_from_user:
    cps #Mode_SYS
    add sp, #8
    cps #Mode_SVC*/
    /*
    pop {r0 - r3, r12}
    pop {r4 - r6, lr}
    */
    /*add sp, #(4*9)
    pop {r4}
    msr spsr_cxsf, r4
lwp_check_debug_quit:
    pop {r0 - r12, pc}
//#endif
*/

.global lwp_signal_quit
lwp_signal_quit:
    call lwp_signal_restore
    //a0 is user_ctx
    mv sp, a0
    RESTORE_ALL
    sret
    

user_do_signal:
    //now sp is user sp
    //save context to user sp
    SAVE_ALL
    //ensure original user sp correct
    mv t0, sp
    addi t0, t0, 33 * REGBYTES
    STORE t0, 33 * REGBYTES(sp)
    OPEN_INTERRUPT
    mv s0, sp
    la t0, lwp_sigreturn//t0 = src
    la t1, lwp_sigreturn_end
    sub t1, t1, t0//t1 = size
    sub s0, s0, t1//s0 = dst

lwp_sigreturn_copy_loop:
    addi t2, t1, -1//t2 = memory index
    add t3, t0, t2//t3 = src addr
    add t4, s0, t2//t4 = dst addr
    lb t5, 0(t3)
    sb t5, 0(t4)
    mv t1, t2
    bnez t1, lwp_sigreturn_copy_loop

    mv a0, sp//sp
    li a1, 0//pc
    li a2, 0//flag
    call lwp_signal_backup
    //a0 = signal id
    mv sp, s0//update new sp
    mv s2, a0//signal id backup
    call lwp_sighandler_get//need a0 returned by lwp_signal_backup
    mv ra, s0//lwp_sigreturn func addr
    mv s1, s0//if func = 0,s1 = lwp_sigreturn func
    beqz a0, skip_user_signal_handler
    mv s1, a0

skip_user_signal_handler:
    li t0, 0x100
    csrc sstatus, t0
    csrw sepc, s1
    mv a0, s2//signal id as arg 0
    sret//enter lwp signal handler

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

.global check_vfp
check_vfp:
    //don't use fpu temporarily
    li a0, 0
    ret

.global get_vfp
get_vfp:
    //don't use fpu temporarily
    li a0, 0
    ret

.global lwp_set_thread_area
lwp_set_thread_area:
    mv tp, a0
    ret

/*
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

// kuser suppurt
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
*/
