;
; Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
;
; SPDX-License-Identifier: Apache-2.0
;
; Change Logs:
; Date           Author       Notes
; 2021-11-16     Dystopia     the first version
;

;-----------------------------------------------------------
;               context switch for C6000 DSP
;-----------------------------------------------------------

    .include "contextinc.asm"
;-----------------------------------------------------------
;                      macro definition
;-----------------------------------------------------------
DP  .set    B14
SP  .set    B15
;
;-----------------------------------------------------------
;

;-----------------------------------------------------------
;                      global variable
;-----------------------------------------------------------
    .global rt_interrupt_from_thread
    .global rt_interrupt_to_thread
    .global rt_thread_switch_interrupt_flag
;
;-----------------------------------------------------------
;
    .sect   ".text"
;-----------------------------------------------------------
; void rt_hw_enable_exception(void)
;-----------------------------------------------------------
    .global rt_hw_enable_exception
rt_hw_enable_exception:
    DINT
    MVC .S2 TSR,B0
    MVC .S2 B3,NRP
    MVK .L2 0xC,B1
    OR  .D2 B0,B1,B0
    MVC .S2 B0,TSR    ; Set GEE and XEN in TSR
    B   .S2 NRP
    NOP 5

;-----------------------------------------------------------
; rt_base_t rt_hw_interrupt_enable(void)
;-----------------------------------------------------------
    .global rt_hw_interrupt_disable
rt_hw_interrupt_disable:
;{
    MVC CSR,B4
    MV  B4,A4
    AND 1,B4,B0
 [!B0]  CLR B4,1,1,B4
 [B0]   SET B4,1,1,B4
    CLR B4,0,0,B4
    MVC B4,CSR
    B   B3
    NOP 5
;}

;-----------------------------------------------------------
; void rt_hw_interrupt_enable(rt_base_t scr)
;-----------------------------------------------------------
    .global rt_hw_interrupt_enable
rt_hw_interrupt_enable:
;{
    MVC A4,CSR
    B   B3
    NOP 5
;}

;-----------------------------------------------------------
; rt_uint32_t rt_hw_get_current_dp(void)
;-----------------------------------------------------------
    .global rt_hw_get_current_dp
rt_hw_get_current_dp:
;{
    B   B3
    MV  B14,    A4
    NOP 4
;}

;-----------------------------------------------------------
; rt_int32_t __fls(rt_int32_t val)
;-----------------------------------------------------------
    .global __fls
__fls:
;{
    B   B3
    LMBD  .L1  1,A4,A4
    NOP 4
;}

;-----------------------------------------------------------
; rt_int32_t __ffs(rt_int32_t val)
;-----------------------------------------------------------
    .global __ffs
__ffs:
;{
    BITR  .M1  A4,A4
    B   B3
    LMBD  .L1  1,A4,A4
    NOP 4
;}

;
;-----------------------------------------------------------
;

;
; void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; A4 --> from
; B4 --> to
;
    .global rt_hw_context_switch
rt_hw_context_switch:
; {
    SUBAW   .D2 SP,2,SP
    ADD .D1X    SP,-8,A15
 || STDW    .D2T1   A15:A14,*SP--[3]    ; Store A15:A14

    STDW    .D2T2   B13:B12,*SP--[1]    ; Store B13:B12
 || STDW    .D1T1   A13:A12,*A15--[1]   ; Store A13:A12
 || MV      B3,B13
    STDW    .D2T2   B11:B10,*SP--[1]    ; Store B11:B10
 || STDW    .D1T1   A11:A10,*A15--[1]   ; Store A11:A10
 || MVC .S2 CSR,B12
    STDW    .D2T2   B13:B12,*SP--[1]    ; Store PC:CSR
 || MVC .S2 TSR,B5

    MVC .S2 ILC,B11
    MVC .S2 RILC,B10
    STDW    .D2T2   B11:B10,*SP--[1]    ; Store RILC:ILC
 || MV  .S1X    B5,A3

    ZERO    A2                          ;
    STDW    .D2T1   A3:A2,*SP--[1]      ; Store TSR:stack type
    STW SP,*A4                          ; Save thread's stack pointer
    B   rt_hw_context_switch_to
    MV  B4,A4
    NOP 4
;}

;
; void rt_hw_context_switch_to(rt_uint32 to);
; A4 --> to
;
    .global rt_hw_context_switch_to
rt_hw_context_switch_to:
;{
    LDW *A4,SP
    NOP 4
    LDDW    .D2T2   *++SP[1],B9:B8      ; get TSR (B9) and stack frame type (B8)
    LDDW    .D2T2   *++SP[1],B11:B10    ; get RILC (B11) and ILC (B10)
    LDDW    .D2T2   *++SP[1],B13:B12    ; get PC (B13) and CSR (B12)
    NOP 2
    MV  B8,B0
 [B0]  BNOP _rt_thread_interrupt_stack, 5
;
; this maybe do better
;
    LDDW    .D2T2   *++SP[1],B11:B10
 || MVC .S2 B11,RILC                    ; Restore RILC
    LDDW    .D2T2   *++SP[1],B13:B12
 || MVC .S2 B10,ILC                     ; Restore ILC
    LDDW    .D2T1   *++SP[1],A11:A10
 || MV  B13,B3                          ; Restore PC
    LDDW    .D2T1   *++SP[1],A13:A12
 || MVC .S2 B12,CSR                     ; Restore CSR
    LDDW    .D2T1   *++SP[1],A15:A14
    B   B3                              ; Return to caller
    ADDAW   .D2 SP,2,SP
    NOP 4                               ; Delay slots
_rt_thread_interrupt_stack:
    ADDAW   .D1X    SP,30,A15
    LDDW    .D1T1   *++A15[1],A17:A16
 || LDDW    .D2T2   *++SP[1],B17:B16
    LDDW    .D1T1   *++A15[1],A19:A18
 || LDDW    .D2T2   *++SP[1],B19:B18
    LDDW    .D1T1   *++A15[1],A21:A20
 || LDDW    .D2T2   *++SP[1],B21:B20
    LDDW    .D1T1   *++A15[1],A23:A22
 || LDDW    .D2T2   *++SP[1],B23:B22
    LDDW    .D1T1   *++A15[1],A25:A24
 || LDDW    .D2T2   *++SP[1],B25:B24
    LDDW    .D1T1   *++A15[1],A27:A26
 || LDDW    .D2T2   *++SP[1],B27:B26
    LDDW    .D1T1   *++A15[1],A29:A28
 || LDDW    .D2T2   *++SP[1],B29:B28
    LDDW    .D1T1   *++A15[1],A31:A30
 || LDDW    .D2T2   *++SP[1],B31:B30

    LDDW    .D1T1   *++A15[1],A1:A0
 || LDDW    .D2T2   *++SP[1],B1:B0

    LDDW    .D1T1   *++A15[1],A3:A2
 || LDDW    .D2T2   *++SP[1],B3:B2
 || MVC .S2 B9,ITSR                     ; Restore ITSR
    LDDW    .D1T1   *++A15[1],A5:A4
 || LDDW    .D2T2   *++SP[1],B5:B4
 || MVC .S2 B11,RILC                    ; Restore RILC
    LDDW    .D1T1   *++A15[1],A7:A6
 || LDDW    .D2T2   *++SP[1],B7:B6
 || MVC .S2 B10,ILC                     ; Restore ILC

    LDDW    .D1T1   *++A15[1],A9:A8
 || LDDW    .D2T2   *++SP[1],B9:B8
 || MVC .S2 B13,IRP                     ; Restore IPR

    LDDW    .D1T1   *++A15[1],A11:A10
 || LDDW    .D2T2   *++SP[1],B11:B10
 || MVC .S2 B12,CSR                     ; Restore CSR

    LDDW    .D1T1   *++A15[1],A13:A12
 || LDDW    .D2T2   *++SP[1],B13:B12

    MV  .D2X    A15,SP
    LDDW    .D2T1   *++SP[1],A15:A14
    B   IRP                             ; Return to point of interrupt
    LDDW    .D2T2   *+SP[1],SP:DP
    NOP 4                               ; Delay slots
;}

;
;-----------------------------------------------------------
;

;
; void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
; A4 --> from
; B4 --> to
;{
    .global rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    SUB     B15,0x8,B15
    STW     B4,*B15[2]
    STW     A4,*B15[1]
    LDW     *+B14(rt_thread_switch_interrupt_flag),B4
    NOP     4
    CMPEQ   1,B4,B0
    [ B0]  BNOP _reswitch,5
    MVK     1,B4
    STW     B4,*+B14(rt_thread_switch_interrupt_flag)
    MV          A4,B4
    STW     B4,*+B14(rt_interrupt_from_thread)
_reswitch:
    LDW     *B15[2],B4
    NOP     4
    STW     B4,*+B14(rt_interrupt_to_thread)
    ADD     8,B15,B15
    BNOP    B3,5
;}

;-----------------------------------------------------------
;
;void rt_interrupt_context_restore(void)
;
    .global rt_interrupt_context_restore
rt_interrupt_context_restore:
;{
    MVKL    rt_thread_switch_interrupt_flag,A3
    MVKH    rt_thread_switch_interrupt_flag,A3
    LDW     *A3,A1
    NOP     4
    CMPEQ   1,A1,A2
 [A2]  BNOP  rt_preempt_context_restore,5
    LDDW    .D2T2   *++SP[1],B9:B8      ; get TSR (B9)
    LDDW    .D2T2   *++SP[1],B11:B10    ; get RILC (B11) and ILC (B10)
    LDDW    .D2T2   *++SP[1],B13:B12    ; get PC (B13) and CSR (B12)

    ADDAW   .D1X    SP,30,A15

    LDDW    .D1T1   *++A15[1],A17:A16
 || LDDW    .D2T2   *++SP[1],B17:B16
    LDDW    .D1T1   *++A15[1],A19:A18
 || LDDW    .D2T2   *++SP[1],B19:B18
    LDDW    .D1T1   *++A15[1],A21:A20
 || LDDW    .D2T2   *++SP[1],B21:B20
    LDDW    .D1T1   *++A15[1],A23:A22
 || LDDW    .D2T2   *++SP[1],B23:B22
    LDDW    .D1T1   *++A15[1],A25:A24
 || LDDW    .D2T2   *++SP[1],B25:B24
    LDDW    .D1T1   *++A15[1],A27:A26
 || LDDW    .D2T2   *++SP[1],B27:B26
    LDDW    .D1T1   *++A15[1],A29:A28
 || LDDW    .D2T2   *++SP[1],B29:B28
    LDDW    .D1T1   *++A15[1],A31:A30
 || LDDW    .D2T2   *++SP[1],B31:B30

    LDDW    .D1T1   *++A15[1],A1:A0
 || LDDW    .D2T2   *++SP[1],B1:B0
    LDDW    .D1T1   *++A15[1],A3:A2
 || LDDW    .D2T2   *++SP[1],B3:B2
 || MVC .S2 B9,ITSR
    LDDW    .D1T1   *++A15[1],A5:A4
 || LDDW    .D2T2   *++SP[1],B5:B4
 || MVC .S2 B11,RILC
    LDDW    .D1T1   *++A15[1],A7:A6
 || LDDW    .D2T2   *++SP[1],B7:B6
 || MVC .S2 B10,ILC
    LDDW    .D1T1   *++A15[1],A9:A8
 || LDDW    .D2T2   *++SP[1],B9:B8
 || MVC .S2 B13,IRP

    LDDW    .D1T1   *++A15[1],A11:A10
 || LDDW    .D2T2   *++SP[1],B11:B10
 || MVC .S2 B12,CSR
    LDDW    .D1T1   *++A15[1],A13:A12
 || LDDW    .D2T2   *++SP[1],B13:B12

    MV  .D2X    A15,SP
 || MVKL    .S1 rt_system_stack_top,A15
    MVKH    .S1 rt_system_stack_top,A15
 || ADDAW   .D1X    SP,6,A14
    STW .D1T1   A14,*A15                ; save system stack pointer

    LDDW    .D2T1   *++SP[1],A15:A14
    B   .S2 IRP                         ; return from interruption
    LDDW    .D2T2   *+SP[1],SP:DP
    NOP     4
rt_preempt_context_restore:
    ZERO    A12
    STW A12,*A3                         ; clear rt_thread_switch_interrupt_flag
;
; restore saved registers by system stack
;
    RESTORE_ALL IRP,ITSR
;
; store registers to thread stack
;
    THREAD_SAVE_ALL IRP,ITSR

    MVKL    rt_interrupt_from_thread,A11
    MVKH    rt_interrupt_from_thread,A11
    LDW     *A11,A10
    NOP
    MVKL    rt_interrupt_to_thread,B10
    MVKH    rt_interrupt_to_thread,B10
    LDW     *B10,B11
    NOP     3
    STW     SP,*A10                     ; store sp in preempted tasks's TCB
    B       rt_hw_context_switch_to
    MV      B11,A4
    NOP     4
;}
    .end
