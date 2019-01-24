;/*
; * Copyright (c) 2006-2018, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2011-08-14     weety    copy from mini2440
; */

NOINT    EQU        0XC0    ; disable interrupt in psr

    AREA |.TEXT|, CODE, READONLY, ALIGN=2
    ARM
    REQUIRE8
    PRESERVE8

;/*
; * rt_base_t rt_hw_interrupt_disable();
; */
rt_hw_interrupt_disable    PROC
    EXPORT rt_hw_interrupt_disable
    MRS     R0, CPSR
    ORR     R1, R0, #NOINT
    MSR     CPSR_C, R1
    BX      LR
    ENDP

;/*
; * void rt_hw_interrupt_enable(rt_base_t level);
; */
rt_hw_interrupt_enable    proc
    export rt_hw_interrupt_enable
    msr     cpsr_c, r0
    bx      lr
    endp

;/*
; * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; * r0 --> from
; * r1 --> to
; */
rt_hw_context_switch    proc
    export rt_hw_context_switch
    stmfd   sp!, {lr}           ; push pc (lr should be pushed in place of pc)
    stmfd   sp!, {r0-r12, lr}       ; push lr & register file
    mrs     r4, cpsr
    stmfd   sp!, {r4}               ; push cpsr
    str     sp, [r0]                ; store sp in preempted tasks tcb
    ldr     sp, [r1]                ; get new task stack pointer
    ldmfd   sp!, {r4}               ; pop new task spsr
    msr     spsr_cxsf, r4
    ldmfd   sp!, {r0-r12, lr, pc}^  ; pop new task r0-r12, lr & pc
    endp

;/*
; * void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
; */
rt_hw_context_switch_to    proc
    export rt_hw_context_switch_to
    ldr     sp, [r0]                ; get new task stack pointer
    ldmfd   sp!, {r4}               ; pop new task spsr
    msr     spsr_cxsf, r4
    ldmfd   sp!, {r0-r12, lr, pc}^   ; pop new task r0-r12, lr & pc
    endp

;/*
; * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
; */
    import rt_thread_switch_interrupt_flag
    import rt_interrupt_from_thread
    import rt_interrupt_to_thread

rt_hw_context_switch_interrupt    proc
    export rt_hw_context_switch_interrupt
    ldr     r2, =rt_thread_switch_interrupt_flag
    ldr     r3, [r2]
    cmp     r3, #1
    beq     _reswitch
    mov     r3, #1                          ; set flag to 1
    str     r3, [r2]
    ldr     r2, =rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    str     r0, [r2]
_reswitch
    ldr     r2, =rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    str     r1, [r2]
    bx      lr
    endp

    end
