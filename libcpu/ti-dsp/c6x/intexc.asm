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
;      interrupt and execption handler for C6000 DSP
;-----------------------------------------------------------

;-----------------------------------------------------------
;                    macro definition
;-----------------------------------------------------------
DP  .set    B14
SP  .set    B15
;
;-----------------------------------------------------------
;
    .include "contextinc.asm"
;-----------------------------------------------------------
;                     global function
;-----------------------------------------------------------
    .global _nmi_handler
    .global _bad_handler
    .global _int4_handler
    .global _int5_handler
    .global _int6_handler
    .global _int7_handler
    .global _int8_handler
    .global _int9_handler
    .global _int10_handler
    .global _int11_handler
    .global _int12_handler
    .global _int13_handler
    .global _int14_handler
    .global _int15_handler
;
;-----------------------------------------------------------
;

;-----------------------------------------------------------
;                     extern function
;-----------------------------------------------------------
    .ref hw_nmi_handler
    .ref hw_bad_handler
    .ref hw_int4_handler
    .ref hw_int5_handler
    .ref hw_int6_handler
    .ref hw_int7_handler
    .ref hw_int8_handler
    .ref hw_int9_handler
    .ref hw_int10_handler
    .ref hw_int11_handler
    .ref hw_int12_handler
    .ref hw_int13_handler
    .ref hw_int14_handler
    .ref hw_int15_handler
    .ref rt_hw_process_exception
    .ref rt_interrupt_context_restore
;
;-----------------------------------------------------------
;

;-----------------------------------------------------------
;               interrupt macro definition
;-----------------------------------------------------------
RT_INTERRUPT_ENTRY  .macro
    SAVE_ALL    IRP,ITSR
                    .endm

RT_CALL_INT .macro __isr
    B   __isr
    ADDKPC  $1  ,B3,4
$1:
    B   .S1 rt_interrupt_context_restore
    NOP 5
            .endm
;-----------------------------------------------------------
;               execption macro definition
;-----------------------------------------------------------
RT_EXECPTION_ENTRY  .macro
    SAVE_ALL NRP,NTSR
                    .endm

RT_EXECPTION_EXIT   .macro
    RESTORE_ALL NRP,NTSR
    B   .S2 NRP   ; return from execption
    NOP 5
                    .endm

;
;-----------------------------------------------------------
;

    .sect   ".text"
;
;-----------------------------------------------------------
;

;-----------------------------------------------------------
; handler NMI interrupt
;-----------------------------------------------------------
_nmi_handler:
;{
    RT_EXECPTION_ENTRY
    MVC .S2 EFR,B2
    CMPEQ   .L2 1,B2,B2
 || MVC .S2 TSR,B1
    MV  .D1X    B2,A2
 || CLR .S2 B1,10,10,B1
    MVC .S2 B1,TSR
 [!A2]  MVKL    .S1 rt_hw_process_exception,A0
 ||[B2] MVKL    .S2 rt_hw_software_exception,B1
 [!A2]  MVKH    .S1 rt_hw_process_exception,A0
 ||[B2] MVKH    .S2 rt_hw_software_exception,B1
 [!B2]  B   .S2X    A0
 [B2]   B   .S2 B1
 [!B2]  ADDAW   .D2 SP,2,B1
 [!B2]  MV  .D1X    B1,A4
    ADDKPC  .S2 ret_from_trap,B3,2
;
; return from trap
;
ret_from_trap:
    MV  .D2X    A4,B0
 [!B0]  MVKL    .S2 ret_from_exception,B3
 [!B0]  MVKH    .S2 ret_from_exception,B3
 [!B0]  BNOP    .S2 B3,5
;
; return from trap restore exception context
;
ret_from_exception:
    RT_EXECPTION_EXIT
;
rt_hw_software_exception:
    MVKL    .S1 rt_hw_process_exception,A0
    MVKH    .S1 rt_hw_process_exception,A0
    B   .S2X    A0
    ADDAW   .D2 SP,2,B1
    MV  .D1X    B1,A4
    ADDKPC  .S2 ret_from_trap,B3,2
    NOP 2
;}

;-----------------------------------------------------------
; handler bad interrupt
;-----------------------------------------------------------
_bad_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_bad_handler
;}

;-----------------------------------------------------------
; handler INT4 interrupt
;-----------------------------------------------------------
_int4_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int4_handler
;}

;-----------------------------------------------------------
; handler INT5 interrupt
;-----------------------------------------------------------
_int5_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int5_handler
;}

;-----------------------------------------------------------
; handler INT6 interrupt
;-----------------------------------------------------------
_int6_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int6_handler
;}

;-----------------------------------------------------------
; handler INT7 interrupt
;-----------------------------------------------------------
_int7_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int7_handler
;}
;-----------------------------------------------------------
; handler INT8 interrupt
;-----------------------------------------------------------
_int8_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int8_handler
;}

;-----------------------------------------------------------
; handler INT9 interrupt
;-----------------------------------------------------------
_int9_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int9_handler
;}

;-----------------------------------------------------------
; handler INT10 interrupt
;-----------------------------------------------------------
_int10_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int10_handler
;}

;-----------------------------------------------------------
; handler INT11 interrupt
;-----------------------------------------------------------
_int11_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int11_handler
;}

;-----------------------------------------------------------
; handler INT12 interrupt
;-----------------------------------------------------------
_int12_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int12_handler
;}

;-----------------------------------------------------------
; handler INT13 interrupt
;-----------------------------------------------------------
_int13_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int13_handler
;}

;-----------------------------------------------------------
; handler INT14 interrupt
;-----------------------------------------------------------
_int14_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int14_handler
;}
;-----------------------------------------------------------
; handler INT15 interrupt
;-----------------------------------------------------------
_int15_handler:
;{
    RT_INTERRUPT_ENTRY
    RT_CALL_INT hw_int15_handler
;}
    .end
