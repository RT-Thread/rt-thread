;/*
;* Copyright (c) 2006-2018, RT-Thread Development Team
;*
;* SPDX-License-Identifier: Apache-2.0
;*
; * Change Logs:
; * Date           Author       Notes
; * 2009-01-17     Bernard      first version.
; * 2012-01-01     aozima       support context switch load/store FPU register.
; * 2013-06-18     aozima       add restore MSP feature.
; * 2013-06-23     aozima       support lazy stack optimized.
; * 2018-07-24     aozima       enhancement hard fault exception handler.
; */

;/**
; * @addtogroup cortex-m33
; */
;/*@{*/

SCB_VTOR        EQU     0xE000ED08               ; Vector Table Offset Register
NVIC_INT_CTRL   EQU     0xE000ED04               ; interrupt control state register
NVIC_SYSPRI2    EQU     0xE000ED20               ; system priority register (2)
NVIC_PENDSV_PRI EQU     0x00FF0000               ; PendSV priority value (lowest)
NVIC_PENDSVSET  EQU     0x10000000               ; value to trigger PendSV exception

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

    IMPORT rt_thread_switch_interrupt_flag
    IMPORT rt_interrupt_from_thread
    IMPORT rt_interrupt_to_thread
    IMPORT rt_trustzone_current_context
    IMPORT rt_trustzone_context_load
    IMPORT rt_trustzone_context_store

;/*
; * rt_base_t rt_hw_interrupt_disable();
; */
rt_hw_interrupt_disable    PROC
    EXPORT  rt_hw_interrupt_disable
    MRS     r0, PRIMASK
    CPSID   I
    BX      LR
    ENDP

;/*
; * void rt_hw_interrupt_enable(rt_base_t level);
; */
rt_hw_interrupt_enable    PROC
    EXPORT  rt_hw_interrupt_enable
    MSR     PRIMASK, r0
    BX      LR
    ENDP

;/*
; * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; * r0 --> from
; * r1 --> to
; */
rt_hw_context_switch_interrupt
    EXPORT rt_hw_context_switch_interrupt
rt_hw_context_switch    PROC
    EXPORT rt_hw_context_switch

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
    ENDP

; r0 --> switch from thread stack
; r1 --> switch to thread stack
; psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
PendSV_Handler   PROC
    EXPORT PendSV_Handler

    ; disable interrupt to protect context switch
    MRS     r2, PRIMASK                             ; R2 = PRIMASK
    CPSID   I                                       ; disable all interrupt

    ; get rt_thread_switch_interrupt_flag
    LDR     r0, =rt_thread_switch_interrupt_flag    ; r0 = &rt_thread_switch_interrupt_flag
    LDR     r1, [r0]                                ; r1 = *r1
    CMP     r1, #0x00                               ; compare r1 == 0x00
    BNE     schedule
    MSR     PRIMASK, r2                             ; if r1 == 0x00, do msr PRIMASK, r2
    BX      lr                                      ; if r1 == 0x00, do bx lr

schedule
    PUSH    {r2}                                    ; store interrupt state

    ; clear rt_thread_switch_interrupt_flag to 0
    MOV     r1, #0x00                               ; r1 = 0x00
    STR     r1, [r0]                                ; *r0 = r1

    ; skip register save at the first time
    LDR     r0, =rt_interrupt_from_thread           ; r0 = &rt_interrupt_from_thread
    LDR     r1, [r0]                                ; r1 = *r0
    CBZ     r1, switch_to_thread                    ; if r1 == 0, goto switch_to_thread

    ; Whether TrustZone thread stack exists
    LDR     r1,  =rt_trustzone_current_context      ; r1 = &rt_secure_current_context
    LDR     r1, [r1]                                ; r1 = *r1
    CBZ     r1, contex_ns_store                     ; if r1 == 0, goto contex_ns_store

    ;call TrustZone fun, Save TrustZone stack
    STMFD   sp!, {r0-r1, lr}                        ; push register
    MOV     r0, r1                                  ; r0 = rt_secure_current_context
    BL rt_trustzone_context_store                   ; call TrustZone store fun
    LDMFD   sp!, {r0-r1, lr}                        ; pop register

    ; check break from TrustZone
    MOV     r2, lr                                  ; r2 = lr
    TST     r2, #0x40                               ; if EXC_RETURN[6] is 1, TrustZone stack was used
    BEQ     contex_ns_store                         ; if r2 & 0x40 == 0, goto contex_ns_store

    ; push PSPLIM CONTROL PSP LR current_context to stack
    MRS     r3, psplim                              ; r3 = psplim
    MRS     r4, control                             ; r4 = control
    MRS     r5, psp                                 ; r5 = psp
    STMFD   r5!, {r1-r4}                            ; push to thread stack

    ; update from thread stack pointer
    LDR     r0, [r0]                                ; r0 = rt_thread_switch_interrupt_flag
    STR     r5, [r0]                                ; *r0 = r5
    b switch_to_thread                              ; goto switch_to_thread

contex_ns_store

    MRS     r1, psp                                 ; get from thread stack pointer

    IF      {FPU} != "SoftVFP"
    TST     lr, #0x10                               ; if(!EXC_RETURN[4])
    VSTMFDEQ  r1!, {d8 - d15}                       ; push FPU register s16~s31
    ENDIF

    STMFD   r1!, {r4 - r11}                         ; push r4 - r11 register

    LDR     r2,  =rt_trustzone_current_context      ; r2 = &rt_secure_current_context
    LDR     r2, [r2]                                ; r2 = *r2
    MOV     r3, lr                                  ; r3 = lr
    MRS     r4, psplim                              ; r4 = psplim
    MRS     r5, control                             ; r5 = control
    STMFD   r1!, {r2-r5}                            ; push to thread stack

    LDR     r0, [r0]
    STR     r1, [r0]                                ; update from thread stack pointer

switch_to_thread
    LDR     r1, =rt_interrupt_to_thread
    LDR     r1, [r1]
    LDR     r1, [r1]                                ; load thread stack pointer

    ; update current TrustZone context
    LDMFD   r1!, {r2-r5}                            ; pop thread stack
    MSR     psplim, r4                              ; psplim = r4
    MSR     control, r5                             ; control = r5
    MOV     lr, r3                                  ; lr = r3
    LDR     r6,  =rt_trustzone_current_context      ; r6 = &rt_secure_current_context
    STR     r2, [r6]                                ; *r6 = r2
    MOV     r0, r2                                  ; r0 = r2

    ; Whether TrustZone thread stack exists
    CBZ     r0, contex_ns_load                      ; if r0 == 0, goto contex_ns_load
    PUSH    {r1, r3}                                ; push lr, thread_stack
    BL rt_trustzone_context_load                    ; call TrustZone load fun
    POP     {r1, r3}                                ; pop lr, thread_stack
    MOV     lr, r3                                  ; lr = r1
    TST     r3, #0x40                               ; if EXC_RETURN[6] is 1, TrustZone stack was used
    BEQ     contex_ns_load                          ; if r1 & 0x40 == 0, goto contex_ns_load
    B pendsv_exit

contex_ns_load
    LDMFD   r1!, {r4 - r11}                         ; pop r4 - r11 register

    IF      {FPU} != "SoftVFP"
    TST     lr, #0x10                               ; if(!EXC_RETURN[4])
    VLDMFDEQ  r1!, {d8 - d15}                       ; pop FPU register s16~s31
    ENDIF

pendsv_exit
    MSR     psp, r1                                 ; update stack pointer
    ; restore interrupt
    POP    {r2}
    MSR     PRIMASK, r2

    BX      lr
    ENDP

;/*
; * void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
; * this fucntion is used to perform the first thread switch
; */
rt_hw_context_switch_to    PROC
    EXPORT rt_hw_context_switch_to
    ; set to thread
    LDR     r1, =rt_interrupt_to_thread
    STR     r0, [r1]

    IF      {FPU} != "SoftVFP"
    ; CLEAR CONTROL.FPCA
    MRS     r2, CONTROL             ; read
    BIC     r2, #0x04               ; modify
    MSR     CONTROL, r2             ; write-back
    ENDIF

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

    ; trigger the PendSV exception (causes context switch)
    LDR     r0, =NVIC_INT_CTRL
    LDR     r1, =NVIC_PENDSVSET
    STR     r1, [r0]

    ; restore MSP
    LDR     r0, =SCB_VTOR
    LDR     r0, [r0]
    LDR     r0, [r0]
    MSR     msp, r0

    ; enable interrupts at processor level
    CPSIE   F
    CPSIE   I

    ; never reach here!
    ENDP

; compatible with old version
rt_hw_interrupt_thread_switch PROC
    EXPORT rt_hw_interrupt_thread_switch
    BX      lr
    ENDP

    IMPORT rt_hw_hard_fault_exception
    EXPORT HardFault_Handler
HardFault_Handler    PROC

    ; get current context
    MRS     r0, msp                 ;get fault context from handler
    TST     lr, #0x04               ;if(!EXC_RETURN[2])
    BEQ     get_sp_done
    MRS     r0, psp                 ;get fault context from thread
get_sp_done

    STMFD   r0!, {r4 - r11}         ; push r4 - r11 register

    LDR     r2,  =rt_trustzone_current_context      ; r2 = &rt_secure_current_context
    LDR     r2, [r2]                                ; r2 = *r2
    MOV     r3, lr                                  ; r3 = lr
    MRS     r4, psplim                              ; r4 = psplim
    MRS     r5, control                             ; r5 = control
    STMFD   r0!, {r2-r5}                            ; push to thread stack

    STMFD   r0!, {lr}               ; push exec_return register

    TST     lr, #0x04               ; if(!EXC_RETURN[2])
    BEQ     update_msp
    MSR     psp, r0                 ; update stack pointer to PSP
    B       update_done
update_msp
    MSR     msp, r0                 ; update stack pointer to MSP
update_done

    PUSH    {lr}
    BL      rt_hw_hard_fault_exception
    POP     {lr}

    ORR     lr, lr, #0x04
    BX      lr
    ENDP

    ALIGN   4

    END
