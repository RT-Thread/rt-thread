/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       first version
 */

#include "rtconfig.h"
#include "asm-generic.h"
#include "asm-fpu.h"

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

/*********************
 *   CONTEXT_OFFSET  *
 *********************/

#define CONTEXT_OFFSET_ELR_EL1    0x0
#define CONTEXT_OFFSET_SPSR_EL1   0x8
#define CONTEXT_OFFSET_SP_EL0     0x10
#define CONTEXT_OFFSET_X30        0x18
#define CONTEXT_OFFSET_FPCR       0x20
#define CONTEXT_OFFSET_FPSR       0x28
#define CONTEXT_OFFSET_X28        0x30
#define CONTEXT_OFFSET_X29        0x38
#define CONTEXT_OFFSET_X26        0x40
#define CONTEXT_OFFSET_X27        0x48
#define CONTEXT_OFFSET_X24        0x50
#define CONTEXT_OFFSET_X25        0x58
#define CONTEXT_OFFSET_X22        0x60
#define CONTEXT_OFFSET_X23        0x68
#define CONTEXT_OFFSET_X20        0x70
#define CONTEXT_OFFSET_X21        0x78
#define CONTEXT_OFFSET_X18        0x80
#define CONTEXT_OFFSET_X19        0x88
#define CONTEXT_OFFSET_X16        0x90
#define CONTEXT_OFFSET_X17        0x98
#define CONTEXT_OFFSET_X14        0xa0
#define CONTEXT_OFFSET_X15        0xa8
#define CONTEXT_OFFSET_X12        0xb0
#define CONTEXT_OFFSET_X13        0xb8
#define CONTEXT_OFFSET_X10        0xc0
#define CONTEXT_OFFSET_X11        0xc8
#define CONTEXT_OFFSET_X8         0xd0
#define CONTEXT_OFFSET_X9         0xd8
#define CONTEXT_OFFSET_X6         0xe0
#define CONTEXT_OFFSET_X7         0xe8
#define CONTEXT_OFFSET_X4         0xf0
#define CONTEXT_OFFSET_X5         0xf8
#define CONTEXT_OFFSET_X2         0x100
#define CONTEXT_OFFSET_X3         0x108
#define CONTEXT_OFFSET_X0         0x110
#define CONTEXT_OFFSET_X1         0x118

#define CONTEXT_OFFSET_Q15        0x120
#define CONTEXT_OFFSET_Q14        0x130
#define CONTEXT_OFFSET_Q13        0x140
#define CONTEXT_OFFSET_Q12        0x150
#define CONTEXT_OFFSET_Q11        0x160
#define CONTEXT_OFFSET_Q10        0x170
#define CONTEXT_OFFSET_Q9         0x180
#define CONTEXT_OFFSET_Q8         0x190
#define CONTEXT_OFFSET_Q7         0x1a0
#define CONTEXT_OFFSET_Q6         0x1b0
#define CONTEXT_OFFSET_Q5         0x1c0
#define CONTEXT_OFFSET_Q4         0x1d0
#define CONTEXT_OFFSET_Q3         0x1e0
#define CONTEXT_OFFSET_Q2         0x1f0
#define CONTEXT_OFFSET_Q1         0x200
#define CONTEXT_OFFSET_Q0         0x210

#define CONTEXT_FPU_SIZE          0x100
#define CONTEXT_SIZE              0x220

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
    mov x3, x2 ;/* user stack top */
    msr daifset, #3
    dsb sy
    mrs x30, sp_el0
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

/*
void arch_set_thread_context(void *exit_addr, void *new_thread_stack, void *user_stack, void **thread_sp);
*/
.global arch_set_thread_context
arch_set_thread_context:
    sub x1, x1, #CONTEXT_SIZE
    str x2, [x1, #CONTEXT_OFFSET_SP_EL0]
    sub x1, x1, #CONTEXT_SIZE
    str xzr, [x1, #CONTEXT_OFFSET_X0]       /* new thread return 0 */
    mov x4, #((3 << 6) | 0x4 | 0x1)         /* el1h, disable interrupt */
    str x4, [x1, #CONTEXT_OFFSET_SPSR_EL1]
    str x0, [x1, #CONTEXT_OFFSET_ELR_EL1]
    str x1, [x3]
    ret

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
    add sp, sp, #0x40
    RESTORE_FPU sp

.global arch_ret_to_user
arch_ret_to_user:
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

    bl lwp_check_debug
    bl lwp_check_exit_request
    cbz w0, 1f
    mov x0, xzr
    b sys_exit
1:
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
    bl lwp_signal_check
    cmp x0, xzr

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

    bne user_do_signal

    stp x0, x1, [sp, #-0x10]!
    ldr x0, =rt_dbg_ops
    ldr x0, [x0]
    cmp x0, xzr
    ldp x0, x1, [sp], #0x10
    beq 1f
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

/*
struct rt_hw_exp_stack
{
    unsigned long pc;     0
    unsigned long cpsr;
    unsigned long sp_el0; 0x10
    unsigned long x30;
    unsigned long fpcr;   0x20
    unsigned long fpsr;
    unsigned long x28;    0x30
    unsigned long x29;
    unsigned long x26;    0x40
    unsigned long x27;
    unsigned long x24;    0x50
    unsigned long x25;
    unsigned long x22;    0x60
    unsigned long x23;
    unsigned long x20;    0x70
    unsigned long x21;
    unsigned long x18;    0x80
    unsigned long x19;
    unsigned long x16;    0x90
    unsigned long x17;
    unsigned long x14;    0xa0
    unsigned long x15;
    unsigned long x12;    0xb0
    unsigned long x13;
    unsigned long x10;    0xc0
    unsigned long x11;
    unsigned long x8;     0xd0
    unsigned long x9;
    unsigned long x6;     0xe0
    unsigned long x7;
    unsigned long x4;     0xf0
    unsigned long x5;
    unsigned long x2;     0x100
    unsigned long x3;
    unsigned long x0;     0x110
    unsigned long x1;

    unsigned long long fpu[16]; 0x120
                                0x220 = 0x120 + 0x10 * 0x10
};
*/
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

arch_signal_quit:
    msr daifset, #3
/*
    drop stack data
*/
    add sp, sp, #CONTEXT_SIZE
    bl lwp_signal_restore
    /* x0 is user_ctx : ori sp, pc, cpsr */
    ldr x1, [x0]
    ldr x2, [x0, #8]
    ldr x3, [x0, #16]
    msr spsr_el1, x3
    msr elr_el1, x2
    add x1, x1, #16
    msr sp_el0, x1

    msr spsel, #0

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

user_do_signal:
    msr spsel, #0
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
    mrs x28, fpcr
    mrs x29, fpsr
    stp x28, x29, [sp, #-0x10]!
    stp x29, x30, [sp, #-0x10]!

    sub sp, sp, #0x10
    adr x0, lwp_sigreturn
    ldr w1, [x0]
    str w1, [sp]
    ldr w1, [x0, #4]
    str w1, [sp, #4]

    mov x20, sp /* lwp_sigreturn */
    mov x0, sp

    dc cvau, x0
    dsb sy
    ic ialluis
    dsb sy

    msr spsel, #1

    mrs x1, elr_el1
    mrs x2, spsr_el1
    bl lwp_signal_backup
    /* x0 is signal */
    mov x19, x0
    bl lwp_sighandler_get
    adds x1, x0, xzr
    mov x0, x19
    bne 1f
    mov x1, x20
1:
    msr elr_el1, x1
    mov x30, x20
    eret

lwp_debugreturn:
    mov x8, 0xf000
    svc #0

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
