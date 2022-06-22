;
; Copyright (c) 2006-2022, RT-Thread Development Team
;
; SPDX-License-Identifier: Apache-2.0
;
; Change Logs:
; Date           Author       Notes
; 2018-09-01     xuzhuoyi     the first version.
; 2019-06-17     zhaoxiaowei  fix bugs of old c28x interrupt api.
; 2019-07-03     zhaoxiaowei  add _rt_hw_calc_csb function to support __rt_ffs.
; 2019-12-05     xiaolifan    add support for hardware fpu32
;

    .ref   _rt_interrupt_to_thread
    .ref   _rt_interrupt_from_thread
    .ref   _rt_thread_switch_interrupt_flag

    .def   _RTOSINT_Handler
    .def   _rt_hw_get_st0
    .def   _rt_hw_get_st1
    .def   _rt_hw_calc_csb
    .def   _rt_hw_context_switch_interrupt
    .def   _rt_hw_context_switch
    .def   _rt_hw_context_switch_to
    .def   _rt_hw_interrupt_thread_switch
    .def   _rt_hw_interrupt_disable
    .def   _rt_hw_interrupt_enable

;workaround for importing fpu settings from the compiler
    .cdecls C,NOLIST
    %{
        #ifdef __TMS320C28XX_FPU32__
            #define __FPU32__ 1
        #else
            #define __FPU32__ 0
        #endif
    %}


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

    .if __FPU32__
    PUSH    RB
    MOV32   *SP++, STF
    MOV32   *SP++, R0H
    MOV32   *SP++, R1H
    MOV32   *SP++, R2H
    MOV32   *SP++, R3H
    MOV32   *SP++, R4H
    MOV32   *SP++, R5H
    MOV32   *SP++, R6H
    MOV32   *SP++, R7H
    .endif

    .endm


RT_CTX_RESTORE  .macro

    .if __FPU32__
    MOV32   R7H, *--SP, UNCF
    MOV32   R6H, *--SP, UNCF
    MOV32   R5H, *--SP, UNCF
    MOV32   R4H, *--SP, UNCF
    MOV32   R3H, *--SP, UNCF
    MOV32   R2H, *--SP, UNCF
    MOV32   R1H, *--SP, UNCF
    MOV32   R0H, *--SP, UNCF
    MOV32   STF, *--SP
    POP     RB
    .endif

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
    PUSH  ST1
    SETC  INTM,DBGM
    MOV   AL, *--SP
    LRETR
    .endasmfunc

;
; void rt_hw_interrupt_enable(rt_base_t level);
;
    .asmfunc
_rt_hw_interrupt_enable:
    MOV   *SP++, AL
    POP   ST1
    LRETR
    .endasmfunc

;
; void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; r0 --> from
; r4 --> to


    .asmfunc
_rt_hw_context_switch_interrupt:
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

    LRETR
    .endasmfunc

;
; void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; r0 --> from
; r4 --> to


    .asmfunc
_rt_hw_context_switch:
    MOVL    XAR0, #0
    MOV     AR0, AL
    MOVL    XAR4, *-SP[4]
    ; set rt_thread_switch_interrupt_flag to 1
    MOVL    XAR5, #_rt_thread_switch_interrupt_flag
    MOVL    XAR6, *XAR5
    MOVL    ACC, XAR6
    CMPB    AL, #1
    B       _reswitch2, EQ
    MOVL     XAR6, #1
    MOVL    *XAR5, XAR6

    MOVL    XAR5, #_rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    MOVL    *XAR5, XAR0

_reswitch2:
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
    MOV     AR0, AL
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

; C28x do not have a build-in "__ffs" func in its C compiler.
; We can use the "Count Sign Bits" (CSB) instruction to make one.
; CSB will return the number of 0's minus 1 above the highest set bit.
; The count is placed in T. For example:
;    ACC        T     maxbit
; 0x00000001    30      0
; 0x00000010    26      4
; 0x000001FF    22      8
; 0x000001F0    22      8
    .asmfunc
_rt_hw_calc_csb:
    MOV     AH, #0
    CSB     ACC                   ; T = no. of sign bits - 1
    MOVU    ACC, T                ; ACC = no. of sign bits - 1
    SUBB    ACC, #30              ; ACC = ACC - 30
    ABS     ACC                   ; ACC = |ACC|
    lretr
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
