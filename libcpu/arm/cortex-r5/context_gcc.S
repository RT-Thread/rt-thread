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

.section .text, "ax"

/*
 * rt_base_t rt_hw_interrupt_disable(void);
 */
.global rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mrs     r0, cpsr
    orr     r1, r0, #I_BIT
    msr     cpsr, r1
    bx      lr

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.global rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    msr     cpsr, r0
    bx      lr

/*
 * void rt_hw_context_switch_to(rt_uint32_t to);
 */
.global rt_hw_context_switch_to
rt_hw_context_switch_to:
    ldr     sp, [r0]
    ldmfd   sp!, {lr}
    msr     spsr_cxsf, lr
    ldmfd   sp!, {r0-r12, lr, pc}^

.section .text.isr, "ax"
/*
 * void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to);
 */
.global rt_hw_context_switch
rt_hw_context_switch:
    stmfd   sp!, {lr}
    stmfd   sp!, {r0-r12, lr}
    mrs     r4, cpsr
    tst     lr, #0x01
    orrne   r4, r4, #0x20
    stmfd   sp!, {r4}
    str     sp, [r0]

    ldr     sp, [r1]
    ldmfd   sp!, {lr}
    msr     spsr_cxsf, lr
    ldmfd   sp!, {r0-r12, lr, pc}^

/*
 * void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to);
 */
.global rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    ldr     r2, =rt_thread_switch_interrupt_flag
    ldr     r3, [r2]
    mov     r4, #1
    cmp     r3, r4
    beq     label
    // set flag
    str     r4, [r2]
    // set from
    ldr     r2, =rt_interrupt_from_thread
    str     r0, [r2]
label:
    // set to
    ldr     r2, =rt_interrupt_to_thread
    str     r1, [r2]
    bx      lr
