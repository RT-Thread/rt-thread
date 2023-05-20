/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#include "rtconfig.h"
.equ    MODE_USR,    0x10
.equ    MODE_FIQ,    0x11
.equ    MODE_IRQ,    0x12
.equ    MODE_SVC,    0x13
.equ    MODE_ABT,    0x17
.equ    MODE_UND,    0x1B
.equ    MODE_SYS,    0x1F
.equ    I_BIT   ,    0x80
.equ    F_BIT   ,    0x40

.section .text.init, "ax"
.global _reset
_reset:

    ldr     r0, =__bss_start
    ldr     r1, =__bss_end
    mov     r2, #0
loop:
    str     r2, [r0], #4
    cmp     r0, r1
    bne     loop

    cps     #MODE_UND
    ldr     sp, =und_stack_bottom
    cps     #MODE_ABT
    ldr     sp, =abt_stack_bottom
    cps     #MODE_IRQ
    ldr     sp, =irq_stack_bottom
    cps     #MODE_SVC
    ldr     sp, =svc_stack_bottom

    ldr     pc, =rtthread_startup

.section .text.isr, "ax"

.macro push_svc_reg
    sub     sp, sp, #17*4
    str     lr, [sp, #15*4] // pc
    mrs     lr, spsr
    str     lr, [sp, #16*4] // cpsr
    stmia   sp, {r0-r12}
    add     sp, sp, #17*4
    mov     r0, sp
    and     r1, lr, #0x1F
    cmp     r1, #0x10
    cps     #MODE_SYS
    streq   sp, [r0, #13*4]
    streq   lr, [r0, #14*4]
    cps     #MODE_SVC
    strne   sp, [r0, #13*4]
    strne   lr, [r0, #14*4]
.endm

.align 5
.global vector_undef
vector_undef:
    push_svc_reg
    bl      rt_hw_trap_undef
    b .

.global vector_swi
vector_swi:
    push_svc_reg
    bl      rt_hw_trap_undef
    b       .

.global vector_pabt
vector_pabt:
    push_svc_reg
    bl      rt_hw_trap_pabt
    b       .

.global vector_dabt
vector_dabt:
    push_svc_reg
    bl      rt_hw_trap_dabt
    b       .

.global vector_resv
vector_resv:
    push_svc_reg
    bl      rt_hw_trap_resv
    b       .

.global vector_irq
vector_irq:
    sub     lr, lr, #4
    stmfd   sp!, {r0-r12, lr}

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

    ldr     lr, =rt_thread_switch_interrupt_flag
    ldr     r0, [lr]
    mov     r1, #1
    cmp     r0, r1
    beq     rt_hw_context_switch_interrupt_do

    ldmfd   sp!, {r0-r12, pc}^

rt_hw_context_switch_interrupt_do:
    mov     r1, #0
    str     r1, [lr]

    mov     r0, sp
    mrs     r1, spsr

    add     sp, #14*4

    msr     cpsr_c, #MODE_SVC | I_BIT | F_BIT
    ldr     r2, [r0, #13*4]
    stmfd   sp!, {r2}
    stmfd   sp!, {lr}
    add     r0, #4*4
    ldmfd   r0, {r4-r12}
    stmfd   sp!, {r4-r12}
    ldmdb   r0, {r4-r7}
    stmfd   sp!, {r4-r7}
    stmfd   sp!, {r1}

    ldr     lr, =rt_interrupt_from_thread
    ldr     lr, [lr]
    str     sp, [lr]

    ldr     lr, =rt_interrupt_to_thread
    ldr     lr, [lr]
    ldr     sp, [lr]

    ldmfd   sp!, {lr}
    msr     spsr_cxsf, lr
    ldmfd   sp!, {r0-r12, lr, pc}^

.global vector_fiq
vector_fiq:
    sub     lr, #4
    stmfd   sp!, {r0-r7, lr}
    bl      rt_hw_trap_fiq
    ldmfd   sp!, {r0-r7, pc}^

.bss
.align 3
svc_stack_top:
    .space (1 << 12)
svc_stack_bottom:

.bss
.align 3
und_stack_top:
    .space (1 << 12)
und_stack_bottom:

.bss
.align 3
abt_stack_top:
    .space (1 << 12)
abt_stack_bottom:

.bss
.align 3
irq_stack_top:
    .space (1 << 12)
irq_stack_bottom:

.bss
.align 3
fiq_stack_top:
    .space (1 << 12)
frq_stack_bottom:
