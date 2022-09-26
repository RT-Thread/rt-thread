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
; 2022-06-21     guyunjie     trim pendsv (RTOSINT_Handler)
; 2022-08-24     guyunjie     fix bugs in context switching

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
; ACC   --> from
; SP[4] --> to
;
    .asmfunc
_rt_hw_context_switch_interrupt:
    MOVL    XAR0, ACC
    MOVL    XAR4, *-SP[4]
    ; set rt_thread_switch_interrupt_flag to 1
    MOVL    XAR5, #_rt_thread_switch_interrupt_flag
    MOVL    ACC, *XAR5
    BF      _reswitch, NEQ                     ; ACC!=0
    MOVB    ACC, #1
    MOVL    *XAR5, ACC

    MOVL    XAR5, #_rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    MOVL    *XAR5, XAR0

_reswitch:
    MOVL    XAR5, #_rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    MOVL    *XAR5, XAR4

    LRETR
    .endasmfunc

;
; void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; ACC   --> from
; SP[4] --> to
;
    .asmfunc
_rt_hw_context_switch:
    MOVL    XAR0, ACC
    MOVL    XAR4, *-SP[4]
    ; set rt_thread_switch_interrupt_flag to 1
    MOVL    XAR5, #_rt_thread_switch_interrupt_flag
    MOVL    ACC, *XAR5
    BF      _reswitch2, NEQ                    ; ACC!=0
    MOVB    ACC, #1
    MOVL    *XAR5, ACC

    MOVL    XAR5, #_rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    MOVL    *XAR5, XAR0

_reswitch2:
    MOVL    XAR5, #_rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    MOVL    *XAR5, XAR4

    TRAP    #16
    LRETR
    .endasmfunc

;
; * void rt_hw_context_switch_to(rt_uint32 to);
; * ACC --> to
;
    .asmfunc
_rt_hw_context_switch_to:
    ; get to thread
    MOVL    XAR1, #_rt_interrupt_to_thread
    MOVL    *XAR1, ACC

    ; set from thread to 0
    MOVL    XAR1, #_rt_interrupt_from_thread
    MOVL    XAR0, #0
    MOVL    *XAR1, XAR0

    ; set interrupt flag to 1
    MOVL    XAR1, #_rt_thread_switch_interrupt_flag
    MOVL    XAR0, #1
    MOVL    *XAR1, XAR0

    TRAP    #16

    ; never reach here!
    .endasmfunc

    .asmfunc
_RTOSINT_Handler:
    ; disable interrupt to protect context switch
    ; DINT ;this is done by hardware so not needed

    ; get rt_thread_switch_interrupt_flag
    MOVL    XAR0, #_rt_thread_switch_interrupt_flag
    MOVL    ACC, *XAR0
    BF      rtosint_exit, EQ         ; pendsv already handled

    ; clear rt_thread_switch_interrupt_flag to 0
    MOVL    XAR1, #0
    MOVL    *XAR0, XAR1

    MOVL    XAR0, #_rt_interrupt_from_thread
    MOVL    ACC, *XAR0
    BF      switch_to_thread, EQ     ; skip register save at the first time

    RT_CTX_SAVE                      ; push cpu registers

    MOVL    ACC, *XAR0
    MOVL    XAR0, ACC
    MOVZ    AR1, @SP                 ; get from thread stack pointer
    MOVL    *XAR0, XAR1              ; update from thread stack pointer

switch_to_thread:
    MOVL    XAR1, #_rt_interrupt_to_thread
    MOVL    ACC, *XAR1
    MOVL    XAR1, ACC
    MOVL    ACC, *XAR1
    MOV     @SP, AL                  ; load thread stack pointer

    RT_CTX_RESTORE                   ; pop cpu registers

rtosint_exit:
    ; do not restore interrupt here: to be restored according to the
    ; switched-to context during IRET (automaticlly by hardware)

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

; compatible with old version
    .asmfunc
_rt_hw_interrupt_thread_switch:
    LRETR
    NOP
    .endasmfunc

.end
