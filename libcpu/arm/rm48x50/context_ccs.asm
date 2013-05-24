;/*
; * File      : context_rvds.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006, RT-Thread Development Team
; *
; * The license and distribution terms for this file may be
; * found in the file LICENSE in this distribution or at
; * http://www.rt-thread.org/license/LICENSE
; *
; * Change Logs:
; * Date       Author       Notes
; * 2009-01-20     Bernard      first version
; * 2011-07-22     Bernard      added thumb mode porting
; * 2013-05-24     Grissiom     port to CCS
; */

   .text
   .arm
   .ref rt_thread_switch_interrupt_flag
   .ref rt_interrupt_from_thread
   .ref rt_interrupt_to_thread
   .ref rt_interrupt_enter
   .ref rt_interrupt_leave
   .ref rt_hw_trap_irq

;/*
; * rt_base_t rt_hw_interrupt_disable();
; */
    .def rt_hw_interrupt_disable
rt_hw_interrupt_disable
    MRS r0, cpsr
    ORR r1, r0, #0xc0 ; disable irq and fiq in psr
    MSR cpsr_c, r1
    BX  lr

;/*
; * void rt_hw_interrupt_enable(rt_base_t level);
; */
    .def rt_hw_interrupt_enable
rt_hw_interrupt_enable
    MSR cpsr_c, r0
    BX  lr

;/*
; * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; * r0 --> from
; * r1 --> to
; */
    .def rt_hw_context_switch
rt_hw_context_switch
    DSB
    STMFD   sp!, {lr}           ; push pc (lr should be pushed in place of PC)
    STMFD   sp!, {r0-r12, lr}   ; push lr & register file

    MRS     r4, cpsr
    TST     lr, #0x01
    BEQ     _ARM_MODE
    ORR     r4, r4, #0x20       ; it's thumb code

_ARM_MODE
    STMFD   sp!, {r4}           ; push cpsr

    STR     sp, [r0]            ; store sp in preempted tasks TCB
    LDR     sp, [r1]            ; get new task stack pointer

    LDMFD   sp!, {r4}           ; pop new task cpsr to spsr
    MSR     spsr_cxsf, r4
    BIC     r4, r4, #0x20       ; must be ARM mode
    MSR     cpsr_cxsf, r4

    DSB
    LDMFD   sp!, {r0-r12, lr, pc}^ ; pop new task r0-r12, lr & pc, copy spsr to cpsr

;/*
; * void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
; */
    .def rt_hw_context_switch_to
rt_hw_context_switch_to
    LDR     sp, [r0]            ; get new task stack pointer

    LDMFD   sp!, {r4}           ; pop new task cpsr to spsr
    MSR     spsr_cxsf, r4
    BIC     r4, r4, #0x20       ; must be ARM mode
    MSR     spsr_cxsf, r4

    LDMFD   sp!, {r0-r12, lr, pc}^ ; pop new task r0-r12, lr & pc, copy spsr to cpsr

;/*
; * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
; */

    .def rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt
    LDR r2, pintflag
    LDR r3, [r2]
    CMP r3, #1
    BEQ _reswitch
    MOV r3, #1              ; set rt_thread_switch_interrupt_flag to 1
    STR r3, [r2]
    LDR r2, pfromthread     ; set rt_interrupt_from_thread
    STR r0, [r2]
_reswitch
    LDR r2, ptothread       ; set rt_interrupt_to_thread
    STR r1, [r2]
    BX  lr

    .def IRQ_Handler
IRQ_Handler
    STMFD   sp!, {r0-r12,lr}
    BL  rt_interrupt_enter
    BL  rt_hw_trap_irq
    BL  rt_interrupt_leave

    ; if rt_thread_switch_interrupt_flag set, jump to
    ; rt_hw_context_switch_interrupt_do and don't return
    LDR r0, pintflag
    LDR r1, [r0]
    CMP r1, #1
    BEQ rt_hw_context_switch_interrupt_do

    LDMFD   sp!, {r0-r12,lr}
    SUBS    pc, lr, #4

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
    .def rt_hw_context_switch_interrupt_do
rt_hw_context_switch_interrupt_do
    MOV     r1,  #0           ; clear flag
    STR     r1,  [r0]

    LDMFD   sp!, {r0-r12,lr}  ; reload saved registers
    STMFD   sp!, {r0-r3}      ; save r0-r3
    MOV     r1,  sp
    ADD     sp,  sp, #16      ; restore sp
    SUB     r2,  lr, #4       ; save old task's pc to r2

    MRS     r3,  spsr         ; get cpsr of interrupt thread

    ; switch to SVC mode and no interrupt
    MSR     cpsr_c, #0xD3

    STMFD   sp!, {r2}         ; push old task's pc
    STMFD   sp!, {r4-r12,lr}  ; push old task's lr,r12-r4
    MOV     r4,  r1           ; Special optimised code below
    MOV     r5,  r3
    LDMFD   r4!, {r0-r3}
    STMFD   sp!, {r0-r3}      ; push old task's r3-r0
    STMFD   sp!, {r5}         ; push old task's cpsr

    LDR     r4,  pfromthread
    LDR     r5,  [r4]
    STR     sp,  [r5]         ; store sp in preempted tasks's TCB

    LDR     r6,  ptothread
    LDR     r6,  [r6]
    LDR     sp,  [r6]         ; get new task's stack pointer

    LDMFD   sp!, {r4}         ; pop new task's cpsr to spsr
    MSR     spsr_cxsf, r4
    BIC     r4, r4, #0x20     ; must be ARM mode
    MSR     cpsr_cxsf, r4

    LDMFD   sp!, {r0-r12,lr,pc}^ ; pop new task's r0-r12,lr & pc, copy spsr to cpsr

pintflag     .word   rt_thread_switch_interrupt_flag
pfromthread  .word   rt_interrupt_from_thread
ptothread    .word   rt_interrupt_to_thread
