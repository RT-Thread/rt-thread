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
; 2022-10-15     guyunjie     add zero-latency interrupt

    .ref   rt_interrupt_to_thread
    .ref   rt_interrupt_from_thread
    .ref   rt_thread_switch_interrupt_flag

    .def   rtosint_handler
    .def   rt_hw_get_st0
    .def   rt_hw_get_st1
    .def   rt_hw_calc_csb
    .def   rt_hw_context_switch_interrupt
    .def   rt_hw_context_switch
    .def   rt_hw_context_switch_to
    .def   rt_hw_interrupt_thread_switch
    .def   rt_hw_interrupt_disable
    .def   rt_hw_interrupt_enable

    ;importing settings from compiler and config
    .cdecls C,NOLIST
    %{
        #include <rtconfig.h>

        #ifdef __TMS320C28XX_FPU32__
            #define __FPU32__ 1
        #else
            #define __FPU32__ 0
        #endif

        #ifdef __TMS320C28XX_FPU64__
            #define __FPU64__ 1
        #else
            #define __FPU64__ 0
        #endif

        #ifdef __TMS320C28XX_VCRC__
            #define __VCRC__ 1
        #else
            #define __VCRC__ 0
        #endif

        #ifdef RT_USING_ZERO_LATENCY
            #define ZERO_LATENCY 1
            #ifndef ZERO_LATENCY_INT_MASK
                #error ZERO_LATENCY_INT_MASK must be defined for zero latency interrupt
            #elif ZERO_LATENCY_INT_MASK & 0x8000
                #error RTOS bit (0x8000) must not be set in ZERO_LATENCY_INT_MASK
            #endif
        #else
            #define ZERO_LATENCY 0
        #endif
    %}


.text
    .newblock

;
; rt_base_t rt_hw_interrupt_disable();
;
    .asmfunc
rt_hw_interrupt_disable:
    .if ZERO_LATENCY
    MOV   AL, IER
    AND   IER, #ZERO_LATENCY_INT_MASK
    .else
    PUSH  ST1
    SETC  INTM
    POP   AL
    .endif
    MOV   AH, #0
    LRETR
    .endasmfunc

;
; void rt_hw_interrupt_enable(rt_base_t level);
;
    .asmfunc
rt_hw_interrupt_enable:
    .if ZERO_LATENCY
    MOV   IER, AL
    .else
    PUSH  AL
    POP   ST1
    .endif
    LRETR
    .endasmfunc

;
; void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; ACC   --> from
; SP[4] --> to
;
    .asmfunc
rt_hw_context_switch_interrupt:

; ACC, XAR4-7 are "save on call" following TI C28x C/C++ compiler convention
; and therefore can be used in a function without being saved on stack first
; (the compiler has already saved it before the call).
; Reference: TMS320C28x Optimizing CC++ Compiler
; note this convention is only applicable to normal functions not to isrs

    MOVL    XAR6, ACC
    MOVL    XAR4, *-SP[4]
    ; set rt_thread_switch_interrupt_flag to 1
    MOVL    XAR5, #rt_thread_switch_interrupt_flag
    MOVL    ACC, *XAR5
    BF      reswitch2, NEQ                    ; ACC!=0
    MOVB    ACC, #1
    MOVL    *XAR5, ACC

    MOVL    XAR5, #rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    MOVL    *XAR5, XAR6

reswitch2:
    MOVL    XAR5, #rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    MOVL    *XAR5, XAR4
    LRETR
    .endasmfunc

;
; void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; ACC   --> from
; SP[4] --> to
;
    .asmfunc
rt_hw_context_switch:

    MOVL    XAR6, ACC
    MOVL    XAR4, *-SP[4]
    ; set rt_thread_switch_interrupt_flag to 1
    MOVL    XAR5, #rt_thread_switch_interrupt_flag
    MOVL    ACC, *XAR5
    BF      reswitch1, NEQ                    ; ACC!=0
    MOVB    ACC, #1
    MOVL    *XAR5, ACC

    MOVL    XAR5, #rt_interrupt_from_thread   ; set rt_interrupt_from_thread
    MOVL    *XAR5, XAR6

reswitch1:
    MOVL    XAR5, #rt_interrupt_to_thread     ; set rt_interrupt_to_thread
    MOVL    *XAR5, XAR4
    OR      IFR, #0x8000
    LRETR
    .endasmfunc
;
; * void rt_hw_context_switch_to(rt_uint32 to);
; * ACC --> to
;
    .asmfunc
rt_hw_context_switch_to:
    ; get to thread
    MOVL    XAR5, #rt_interrupt_to_thread
    MOVL    *XAR5, ACC

    ; set from thread to 0
    MOVL    XAR5, #rt_interrupt_from_thread
    MOVL    XAR4, #0
    MOVL    *XAR5, XAR4

    ; set interrupt flag to 1
    MOVL    XAR5, #rt_thread_switch_interrupt_flag
    MOVL    XAR4, #1
    MOVL    *XAR5, XAR4

    ; trigger rtos interrupt
    OR      IFR, #0x8000
    OR      IER, #0x8000
    CLRC    INTM

    ; never reach here!
    .endasmfunc

    .asmfunc
rtosint_handler:

    .if ZERO_LATENCY
    ; mask out non-critical interrupts and enable global interrupt
    ; so rtosint_handler won't block critical interrupts
    AND  IER, #ZERO_LATENCY_INT_MASK
    CLRC INTM
    .endif

    MOVL ACC, *-SP[4]
    MOV  AR0, AL   ; save original IER

    PUSH    AR1H:AR0H
    PUSH    XAR2

    ; get rt_thread_switch_interrupt_flag
    MOVL    XAR1, #rt_thread_switch_interrupt_flag
    MOVL    ACC, *XAR1
    BF      rtosint_exit, EQ         ; rtos_int already handled

    ; clear rt_thread_switch_interrupt_flag to 0
    MOVL    XAR2, #0
    MOVL    *XAR1, XAR2

    MOVL    XAR1, #rt_interrupt_from_thread
    MOVL    ACC, *XAR1
    BF      switch_to_thread, EQ     ; skip register save at the first time

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

    .if __FPU64__
    MOV32   *SP++, R0L
    MOV32   *SP++, R1L
    MOV32   *SP++, R2L
    MOV32   *SP++, R3L
    MOV32   *SP++, R4L
    MOV32   *SP++, R5L
    MOV32   *SP++, R6L
    MOV32   *SP++, R7L
    .endif

    .if __VCRC__
    VMOV32  *SP++, VCRC
    VMOV32  *SP++, VSTATUS
    VMOV32  *SP++, VCRCPOLY
    VMOV32  *SP++, VCRCSIZE
    .endif

    MOVL    ACC, *XAR1
    MOVL    XAR1, ACC
    MOVZ    AR2, @SP                 ; get from thread stack pointer
    MOVL    *XAR1, XAR2              ; update from thread stack pointer

switch_to_thread:
    MOVL    XAR1, #rt_interrupt_to_thread
    MOVL    ACC, *XAR1
    MOVL    XAR1, ACC
    MOVL    ACC, *XAR1
    MOV     @SP, AL                  ; load thread stack pointer

    .if __VCRC__
    VMOV32  VCRCSIZE, *--SP
    VMOV32  VCRCPOLY, *--SP
    VMOV32  VSTATUS, *--SP
    VMOV32  VCRC, *--SP
    .endif

    .if __FPU64__
    MOV32   R7L, *--SP
    MOV32   R6L, *--SP
    MOV32   R5L, *--SP
    MOV32   R4L, *--SP
    MOV32   R3L, *--SP
    MOV32   R2L, *--SP
    MOV32   R1L, *--SP
    MOV32   R0L, *--SP
    .endif

    .if __FPU32__
    MOV32   R7H, *--SP
    MOV32   R6H, *--SP
    MOV32   R5H, *--SP
    MOV32   R4H, *--SP
    MOV32   R3H, *--SP
    MOV32   R2H, *--SP
    MOV32   R1H, *--SP
    MOV32   R0H, *--SP
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

rtosint_exit:
    ; do not restore interrupt here: to be restored according to the
    ; switched-to context during IRET (automaticlly by hardware)

    POP     XAR2
    POP     AR1H:AR0H

    MOVL    ACC , *-SP[4]
    MOV     AL, AR0
    MOVL    *-SP[4], ACC

    IRET
    .endasmfunc

    .asmfunc
rt_hw_get_st0:
    PUSH    ST0
    POP     AL
    LRETR
    .endasmfunc

    .asmfunc
rt_hw_get_st1:
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
rt_hw_calc_csb:
    MOV     AH, #0
    CSB     ACC                   ; T = no. of sign bits - 1
    MOVU    ACC, T                ; ACC = no. of sign bits - 1
    SUBB    ACC, #30              ; ACC = ACC - 30
    ABS     ACC                   ; ACC = |ACC|
    LRETR
    .endasmfunc

; compatible with old version
    .asmfunc
rt_hw_interrupt_thread_switch:
    LRETR
    NOP
    .endasmfunc

.end
