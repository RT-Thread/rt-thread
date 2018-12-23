;
; Copyright (c) 2006-2018, RT-Thread Development Team
;
; SPDX-License-Identifier: Apache-2.0
;
; Change Logs:
; Date           Author       Notes
; 2018-09-01     xuzhuoyi     the first version.
;

    .ref   _rt_interrupt_to_thread
    .ref   _rt_interrupt_from_thread
    .ref   _rt_thread_switch_interrupt_flag

    .def   _RTOSINT_Handler
    .def   _rt_hw_get_st0
    .def   _rt_hw_get_st1
    .def   _rt_hw_context_switch_interrupt
    .def   _rt_hw_context_switch
    .def   _rt_hw_context_switch_to
    .def   _rt_hw_interrupt_thread_switch
    .def   _rt_hw_interrupt_disable
    .def   _rt_hw_interrupt_enable


RT_CTX_SAVE  .macro      


    PUSH    AR1H:AR0H
    PUSH    XAR2
    PUSH    XAR3
    PUSH    XAR4
    PUSH    XAR5
    PUSH    XAR6
    PUSH    XAR7
    PUSH    XT
    PUSH    RPC

 
    .endm


RT_CTX_RESTORE  .macro
                                  
    POP     RPC
    POP     XT
    POP     XAR7
    POP     XAR6
    POP     XAR5
    POP     XAR4
    POP     XAR3
    POP     XAR2


    MOVZ    AR0 , @SP                                           
    SUBB    XAR0, #6
    MOVL    ACC , *XAR0
    AND     ACC, #0xFFFF << 16
    MOV     AL, IER
    MOVL   *XAR0, ACC


    POP     AR1H:AR0H

    .endm


.text
    .newblock

;
; rt_base_t rt_hw_interrupt_disable();
;
    .asmfunc
_rt_hw_interrupt_disable:
    DINT
    LRETR
    .endasmfunc

;
; void rt_hw_interrupt_enable(rt_base_t level);
;
    .asmfunc
_rt_hw_interrupt_enable:
    EINT
    LRETR
    .endasmfunc
    
;
; void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; r0 --> from
; r4 --> to

 
    .asmfunc
_rt_hw_context_switch_interrupt:
_rt_hw_context_switch:
    MOVL    XAR0, #0
    MOV     AR0, AL
    MOVL    XAR4, *-SP[4]
    ; set rt_thread_switch_interrupt_flag to 1 
    MOVL    XAR5, #_rt_thread_switch_interrupt_flag
    MOVL    XAR6, *XAR5
    MOVL    ACC, XAR6
    CMPB    AL, #1
    B       _reswitch, EQ
    MOVL     XAR6, #1
    MOVL    *XAR5, XAR6

    MOVL    XAR5, #_rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    MOVL    *XAR5, XAR0

_reswitch:
    MOVL    XAR5, #_rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    MOVL    *XAR5, XAR4

    TRAP    #16
    LRETR
    .endasmfunc
     
     .asmfunc
_RTOSINT_Handler:
; disable interrupt to protect context switch 
    DINT

    ; get rt_thread_switch_interrupt_flag 
    MOV     AR0, #_rt_thread_switch_interrupt_flag
    MOV     AL, *AR0
    MOV     AR1, AL
    CMP     AR1, #0
    B       rtosint_exit, EQ         ; pendsv already handled 

    ; clear rt_thread_switch_interrupt_flag to 0 
    MOV     AR1, #0x00
    MOV     *AR0, AR1

    MOV     AR0, #_rt_interrupt_from_thread
    MOV     AL, *AR0
    MOV     AR1, AL
    CMP     AR1, #0
    B       switch_to_thread, EQ    ; skip register save at the first time 

    ;MOVZ    AR1, @SP                 ; get from thread stack pointer 
    
;#if defined (__VFP_FP__) && !defined(__SOFTFP__)
;    TST     lr, #0x10           ; if(!EXC_RETURN[4]) 
;    VSTMDBEQ r1!, {d8 - d15}    ; push FPU register s16~s31 
;#endif
    
    RT_CTX_SAVE     ; push r4 - r11 register 

;#if defined (__VFP_FP__) && !defined(__SOFTFP__)
;    MOV     r4, #0x00           ; flag = 0 

;    TST     lr, #0x10           ; if(!EXC_RETURN[4]) 
;    MOVEQ   r4, #0x01           ; flag = 1 

;    STMFD   r1!, {r4}           ; push flag 
;#endif

    MOV     AL, *AR0
    MOV     AR1, AL
    MOVZ    AR1, @SP                 ; get from thread stack pointer
    MOV     *AR0, AR1                ; update from thread stack pointer 

switch_to_thread:
    MOV     AR1, #_rt_interrupt_to_thread
    MOV     AL, *AR1
    MOV     AR1, AL
    MOV     AL, *AR1
    MOV     AR1, AL                ; load thread stack pointer 

;#if defined (__VFP_FP__) && !defined(__SOFTFP__)
;    LDMFD   r1!, {r3}           ; pop flag 
;#endif

    MOV     @SP, AR1
    INC     SP
    RT_CTX_RESTORE     ; pop r4 - r11 register

rtosint_exit:
    ; restore interrupt 
    EINT

    IRET
    .endasmfunc

    .asmfunc
_rt_hw_get_st0:
    PUSH    ST0
    POP     AL
    LRETR
    .endasmfunc

    .asmfunc
_rt_hw_get_st1:
    PUSH    ST1
    POP     AL
    LRETR
    .endasmfunc

;
; * void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
 
    .asmfunc
_rt_hw_context_switch_to:
    MOV     AR1, #_rt_interrupt_to_thread
    MOV     *AR1, AL

;#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ; CLEAR CONTROL.FPCA 
;    MRS     r2, CONTROL         ; read 
;    BIC     r2, #0x04           ; modify 
;    MSR     CONTROL, r2         ; write-back 
;#endif

    ; set from thread to 0 
    MOV     AR1, #_rt_interrupt_from_thread
    MOV     AR0, #0x0
    MOV     *AR1, AR0

    ; set interrupt flag to 1 
    MOV     AR1, #_rt_thread_switch_interrupt_flag
    MOV     AR0, #1
    MOV     *AR1, AR0

    TRAP    #16


    ; never reach here! 
    .endasmfunc
    
; compatible with old version 
    .asmfunc
_rt_hw_interrupt_thread_switch:
    LRETR
    NOP
    .endasmfunc
    
.end
