;/*
; * Copyright (c) 2006-2018, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2009-01-17     Bernard      first version
; * 2009-09-27     Bernard      add protect when contex switch occurs
; * 2012-01-01     aozima       support context switch load/store FPU register.
; * 2013-06-18     aozima       add restore MSP feature.
; * 2013-06-23     aozima       support lazy stack optimized.
; * 2018-07-24     aozima       enhancement hard fault exception handler.
; */

;/**
; * @addtogroup cortex-m4
; */
;/*@{*/

SCB_VTOR        EQU     0xE000ED08               ; Vector Table Offset Register
NVIC_INT_CTRL   EQU     0xE000ED04               ; interrupt control state register
NVIC_SYSPRI2    EQU     0xE000ED20               ; system priority register (2)
NVIC_PENDSV_PRI EQU     0x00FF0000               ; PendSV priority value (lowest)
NVIC_PENDSVSET  EQU     0x10000000               ; value to trigger PendSV exception

    SECTION    .text:CODE(2)
    THUMB
    REQUIRE8
    PRESERVE8

    IMPORT rt_thread_switch_interrupt_flag
    IMPORT rt_interrupt_from_thread
    IMPORT rt_interrupt_to_thread

;/*
; * rt_base_t rt_hw_interrupt_disable();
; */
    EXPORT rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    MRS     r0, PRIMASK
    CPSID   I
    BX      LR

;/*
; * void rt_hw_interrupt_enable(rt_base_t level);
; */
    EXPORT  rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    MSR     PRIMASK, r0
    BX      LR

;/*
; * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; * r0 --> from
; * r1 --> to
; */
    EXPORT rt_hw_context_switch_interrupt
    EXPORT rt_hw_context_switch
rt_hw_context_switch_interrupt:
rt_hw_context_switch:
    ; set rt_thread_switch_interrupt_flag to 1
    LDR     r2, =rt_thread_switch_interrupt_flag
    LDR     r3, [r2]
    CMP     r3, #1
    BEQ     _reswitch
    MOV     r3, #1
    STR     r3, [r2]

    LDR     r2, =rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    STR     r0, [r2]

_reswitch
    LDR     r2, =rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    STR     r1, [r2]

    LDR     r0, =NVIC_INT_CTRL              ; trigger the PendSV exception (causes context switch)
    LDR     r1, =NVIC_PENDSVSET
    STR     r1, [r0]
    BX      LR

; r0 --> switch from thread stack
; r1 --> switch to thread stack
; psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
    EXPORT PendSV_Handler
PendSV_Handler:

    ; disable interrupt to protect context switch
    MRS     r2, PRIMASK
    CPSID   I

    ; get rt_thread_switch_interrupt_flag
    LDR     r0, =rt_thread_switch_interrupt_flag
    LDR     r1, [r0]
    CBZ     r1, pendsv_exit         ; pendsv already handled

    ; clear rt_thread_switch_interrupt_flag to 0
    MOV     r1, #0x00
    STR     r1, [r0]

    LDR     r0, =rt_interrupt_from_thread
    LDR     r1, [r0]
    CBZ     r1, switch_to_thread    ; skip register save at the first time

    MRS     r1, psp                 ; get from thread stack pointer

#if defined ( __ARMVFP__ )
    TST     lr, #0x10               ; if(!EXC_RETURN[4])
    BNE     skip_push_fpu
    VSTMDB  r1!, {d8 - d15}         ; push FPU register s16~s31
skip_push_fpu
#endif

    STMFD   r1!, {r4 - r11}         ; push r4 - r11 register

#if defined ( __ARMVFP__ )
    MOV     r4, #0x00               ; flag = 0
    TST     lr, #0x10               ; if(!EXC_RETURN[4])
    BNE     push_flag
    MOV     r4, #0x01               ; flag = 1
push_flag
    ;STMFD   r1!, {r4}              ; push flag
    SUB     r1, r1, #0x04
    STR     r4, [r1]
#endif

    LDR     r0, [r0]
    STR     r1, [r0]                ; update from thread stack pointer

switch_to_thread
    LDR     r1, =rt_interrupt_to_thread
    LDR     r1, [r1]
    LDR     r1, [r1]                ; load thread stack pointer

#if defined ( __ARMVFP__ )
    LDMFD   r1!, {r3}               ; pop flag
#endif

    LDMFD   r1!, {r4 - r11}         ; pop r4 - r11 register

#if defined ( __ARMVFP__ )
    CBZ     r3, skip_pop_fpu
    VLDMIA  r1!, {d8 - d15}         ; pop FPU register s16~s31
skip_pop_fpu
#endif

    MSR     psp, r1                 ; update stack pointer

#if defined ( __ARMVFP__ )
    ORR     lr, lr, #0x10           ; lr |=  (1 << 4), clean FPCA.
    CBZ     r3, return_without_fpu  ; if(flag_r3 != 0)
    BIC     lr, lr, #0x10           ; lr &= ~(1 << 4), set FPCA.
return_without_fpu
#endif

pendsv_exit
    ; restore interrupt
    MSR     PRIMASK, r2

    ORR     lr, lr, #0x04
    BX      lr

;/*
; * void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
; */
    EXPORT rt_hw_context_switch_to
rt_hw_context_switch_to:
    LDR     r1, =rt_interrupt_to_thread
    STR     r0, [r1]

#if defined ( __ARMVFP__ )
    ; CLEAR CONTROL.FPCA
    MRS     r2, CONTROL             ; read
    BIC     r2, r2, #0x04           ; modify
    MSR     CONTROL, r2             ; write-back
#endif

    ; set from thread to 0
    LDR     r1, =rt_interrupt_from_thread
    MOV     r0, #0x0
    STR     r0, [r1]

    ; set interrupt flag to 1
    LDR     r1, =rt_thread_switch_interrupt_flag
    MOV     r0, #1
    STR     r0, [r1]

    ; set the PendSV exception priority
    LDR     r0, =NVIC_SYSPRI2
    LDR     r1, =NVIC_PENDSV_PRI
    LDR.W   r2, [r0,#0x00]       ; read
    ORR     r1,r1,r2             ; modify
    STR     r1, [r0]             ; write-back

    LDR     r0, =NVIC_INT_CTRL      ; trigger the PendSV exception (causes context switch)
    LDR     r1, =NVIC_PENDSVSET
    STR     r1, [r0]

    ; restore MSP
    LDR     r0, =SCB_VTOR
    LDR     r0, [r0]
    LDR     r0, [r0]
    NOP
    MSR     msp, r0

    ; enable interrupts at processor level
    CPSIE   F
    CPSIE   I

    ; never reach here!

; compatible with old version
    EXPORT rt_hw_interrupt_thread_switch
rt_hw_interrupt_thread_switch:
    BX      lr

    IMPORT rt_hw_hard_fault_exception
    EXPORT HardFault_Handler
HardFault_Handler:

    ; get current context
    MRS     r0, msp                 ; get fault context from handler.
    TST     lr, #0x04               ; if(!EXC_RETURN[2])
    BEQ     _get_sp_done
    MRS     r0, psp                 ; get fault context from thread.
_get_sp_done

    STMFD   r0!, {r4 - r11}         ; push r4 - r11 register
    ;STMFD   r0!, {lr}               ; push exec_return register
#if defined ( __ARMVFP__ )
    SUB     r0, r0, #0x04           ; push dummy for flag
    STR     lr, [r0]
#endif
    SUB     r0, r0, #0x04
    STR     lr, [r0]

    TST     lr, #0x04               ; if(!EXC_RETURN[2])
    BEQ     _update_msp
    MSR     psp, r0                 ; update stack pointer to PSP.
    B       _update_done
_update_msp
    MSR     msp, r0                 ; update stack pointer to MSP.
_update_done

    PUSH    {lr}
    BL      rt_hw_hard_fault_exception
    POP     {lr}

    ORR     lr, lr, #0x04
    BX      lr

    END
