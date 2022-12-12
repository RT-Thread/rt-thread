;/*
; * Copyright (c) 2006-2022, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2009-01-20     Bernard      first version
; * 2011-07-22     Bernard      added thumb mode porting
; */

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled

NOINT           EQU     0xc0    ; disable interrupt in psr

    AREA |.text|, CODE, READONLY, ALIGN=2
    ARM
    REQUIRE8
    PRESERVE8

;/*
; * rt_base_t rt_hw_interrupt_disable();
; */
rt_hw_interrupt_disable PROC
    EXPORT rt_hw_interrupt_disable
    MRS r0, cpsr
    ORR r1, r0, #NOINT
    MSR cpsr_c, r1
    BX  lr
    ENDP

;/*
; * void rt_hw_interrupt_enable(rt_base_t level);
; */
rt_hw_interrupt_enable  PROC
    EXPORT rt_hw_interrupt_enable
    MSR cpsr_c, r0
    BX  lr
    ENDP

;/*
; * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; * r0 --> from
; * r1 --> to
; */
rt_hw_context_switch    PROC
    EXPORT rt_hw_context_switch
    STMFD   sp!, {lr}           ; push pc (lr should be pushed in place of PC)
    STMFD   sp!, {r0-r12, lr}   ; push lr & register file

    MRS     r4, cpsr
        TST     lr, #0x01
        BEQ     _ARM_MODE
        ORR     r4, r4, #0x20           ; it's thumb code
_ARM_MODE
    STMFD   sp!, {r4}           ; push cpsr

    STR sp, [r0]                ; store sp in preempted tasks TCB
    LDR sp, [r1]                ; get new task stack pointer

    LDMFD   sp!, {r4}               ; pop new task cpsr to spsr
    MSR spsr_cxsf, r4
    BIC     r4, r4, #0x20           ; must be ARM mode
    MSR cpsr_cxsf, r4

    LDMFD   sp!, {r0-r12, lr, pc}^  ; pop new task r0-r12, lr & pc, copy spsr to cpsr
    ENDP

;/*
; * void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
; */
rt_hw_context_switch_to PROC
    EXPORT rt_hw_context_switch_to
    LDR sp, [r0]                ; get new task stack pointer

    LDMFD   sp!, {r4}               ; pop new task cpsr to spsr
    MSR spsr_cxsf, r4
    BIC     r4, r4, #0x20           ; must be ARM mode
    MSR cpsr_cxsf, r4

    LDMFD   sp!, {r0-r12, lr, pc}^  ; pop new task r0-r12, lr & pc, copy spsr to cpsr
    ENDP

;/*
; * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
; */
    IMPORT rt_thread_switch_interrupt_flag
    IMPORT rt_interrupt_from_thread
    IMPORT rt_interrupt_to_thread

rt_hw_context_switch_interrupt  PROC
    EXPORT rt_hw_context_switch_interrupt
    LDR r2, =rt_thread_switch_interrupt_flag
    LDR r3, [r2]
    CMP r3, #1
    BEQ _reswitch
    MOV r3, #1                          ; set rt_thread_switch_interrupt_flag to 1
    STR r3, [r2]
    LDR r2, =rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    STR r0, [r2]
_reswitch
    LDR r2, =rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    STR r1, [r2]
    BX  lr
    ENDP

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
rt_hw_context_switch_interrupt_do   PROC
    EXPORT rt_hw_context_switch_interrupt_do
    MOV     r1,  #0         ; clear flag
    STR     r1,  [r0]

    LDMFD   sp!, {r0-r12,lr}; reload saved registers
    STMFD   sp!, {r0-r3}    ; save r0-r3
    MOV     r1,  sp
    ADD     sp,  sp, #16    ; restore sp
    SUB     r2,  lr, #4     ; save old task's pc to r2

    MRS     r3,  spsr       ; get cpsr of interrupt thread

    ; switch to SVC mode and no interrupt
    MSR     cpsr_c, #I_Bit:OR:F_Bit:OR:Mode_SVC

    STMFD   sp!, {r2}       ; push old task's pc
    STMFD   sp!, {r4-r12,lr}; push old task's lr,r12-r4
    MOV     r4,  r1         ; Special optimised code below
    MOV     r5,  r3
    LDMFD   r4!, {r0-r3}
    STMFD   sp!, {r0-r3}    ; push old task's r3-r0
    STMFD   sp!, {r5}       ; push old task's cpsr

    LDR     r4,  =rt_interrupt_from_thread
    LDR     r5,  [r4]
    STR     sp,  [r5]       ; store sp in preempted tasks's TCB

    LDR     r6,  =rt_interrupt_to_thread
    LDR     r6,  [r6]
    LDR     sp,  [r6]       ; get new task's stack pointer

    LDMFD   sp!, {r4}       ; pop new task's cpsr to spsr
    MSR     spsr_cxsf, r4
    BIC     r4, r4, #0x20   ; must be ARM mode
    MSR     cpsr_cxsf, r4

    LDMFD   sp!, {r0-r12,lr,pc}^ ; pop new task's r0-r12,lr & pc, copy spsr to cpsr
    ENDP

    END
