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
; interrupt handler for C6678 DSP
;-----------------------------------------------------------

;-----------------------------------------------------------
; 						macro definition
;-----------------------------------------------------------
DP	.set	B14
SP	.set	B15
;
;-----------------------------------------------------------
;

;-----------------------------------------------------------
; 						global function
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
; 						extern function
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

;
;-----------------------------------------------------------
;

;-----------------------------------------------------------
; 						macro definition
;-----------------------------------------------------------
SAVE_ALL	.macro  __rp, __tsr
	STDW	.D2T2	SP:DP,*--SP[1]
	SUBAW	.D2	SP,2,SP
	ADD	.D1X	SP,-8,A15
 ||	STDW	.D2T1	A15:A14,*SP--[16]	; save A15:A14

	STDW	.D2T2	B13:B12,*SP--[1]
 ||	STDW	.D1T1	A13:A12,*A15--[1]
 ||	MVC	.S2	__rp,B13

	STDW	.D2T2	B11:B10,*SP--[1]
 ||	STDW	.D1T1	A11:A10,*A15--[1]
 ||	MVC	.S2	CSR,B12

	STDW	.D2T2	B9:B8,*SP--[1]
 ||	STDW	.D1T1	A9:A8,*A15--[1]
 ||	MVC	.S2	RILC,B11
	STDW	.D2T2	B7:B6,*SP--[1]
 ||	STDW	.D1T1	A7:A6,*A15--[1]
 ||	MVC	.S2	ILC,B10

	STDW	.D2T2	B5:B4,*SP--[1]
 ||	STDW	.D1T1	A5:A4,*A15--[1]

	STDW	.D2T2	B3:B2,*SP--[1]
 ||	STDW	.D1T1	A3:A2,*A15--[1]
 ||	MVC	.S2	__tsr,B5

	STDW	.D2T2	B1:B0,*SP--[1]
 ||	STDW	.D1T1	A1:A0,*A15--[1]
 ||	MV	.S1X	B5,A5

	STDW	.D2T2	B31:B30,*SP--[1]
 ||	STDW	.D1T1	A31:A30,*A15--[1]
 || MVKL	1,A4

	STDW	.D2T2	B29:B28,*SP--[1]
 ||	STDW	.D1T1	A29:A28,*A15--[1]
	STDW	.D2T2	B27:B26,*SP--[1]
 ||	STDW	.D1T1	A27:A26,*A15--[1]
	STDW	.D2T2	B25:B24,*SP--[1]
 ||	STDW	.D1T1	A25:A24,*A15--[1]
	STDW	.D2T2	B23:B22,*SP--[1]
 ||	STDW	.D1T1	A23:A22,*A15--[1]
	STDW	.D2T2	B21:B20,*SP--[1]
 ||	STDW	.D1T1	A21:A20,*A15--[1]
	STDW	.D2T2	B19:B18,*SP--[1]
 ||	STDW	.D1T1	A19:A18,*A15--[1]
	STDW	.D2T2	B17:B16,*SP--[1]
 ||	STDW	.D1T1	A17:A16,*A15--[1]

	STDW	.D2T2	B13:B12,*SP--[1]	; save PC and CSR

	STDW	.D2T2	B11:B10,*SP--[1]	; save RILC and ILC
	STDW	.D2T1	A5:A4,*SP--[1]		; save TSR and orig A4
			.endm

RESTORE_ALL	.macro  __rp, __tsr
	LDDW	.D2T2	*++SP[1],B9:B8		; get TSR (B9)
	LDDW	.D2T2	*++SP[1],B11:B10	; get RILC (B11) and ILC (B10)
	LDDW	.D2T2	*++SP[1],B13:B12	; get PC (B13) and CSR (B12)

	ADDAW	.D1X	SP,30,A15

	LDDW	.D1T1	*++A15[1],A17:A16
 ||	LDDW	.D2T2	*++SP[1],B17:B16
	LDDW	.D1T1	*++A15[1],A19:A18
 ||	LDDW	.D2T2	*++SP[1],B19:B18
	LDDW	.D1T1	*++A15[1],A21:A20
 ||	LDDW	.D2T2	*++SP[1],B21:B20
	LDDW	.D1T1	*++A15[1],A23:A22
 ||	LDDW	.D2T2	*++SP[1],B23:B22
	LDDW	.D1T1	*++A15[1],A25:A24
 ||	LDDW	.D2T2	*++SP[1],B25:B24
	LDDW	.D1T1	*++A15[1],A27:A26
 ||	LDDW	.D2T2	*++SP[1],B27:B26
	LDDW	.D1T1	*++A15[1],A29:A28
 ||	LDDW	.D2T2	*++SP[1],B29:B28
	LDDW	.D1T1	*++A15[1],A31:A30
 ||	LDDW	.D2T2	*++SP[1],B31:B30

	LDDW	.D1T1	*++A15[1],A1:A0
 ||	LDDW	.D2T2	*++SP[1],B1:B0
	LDDW	.D1T1	*++A15[1],A3:A2
 ||	LDDW	.D2T2	*++SP[1],B3:B2
 ||	MVC	.S2	B9,__tsr
	LDDW	.D1T1	*++A15[1],A5:A4
 ||	LDDW	.D2T2	*++SP[1],B5:B4
 ||	MVC	.S2	B11,RILC
	LDDW	.D1T1	*++A15[1],A7:A6
 ||	LDDW	.D2T2	*++SP[1],B7:B6
 ||	MVC	.S2	B10,ILC
	LDDW	.D1T1	*++A15[1],A9:A8
 ||	LDDW	.D2T2	*++SP[1],B9:B8
 ||	MVC	.S2	B13,__rp

	LDDW	.D1T1	*++A15[1],A11:A10
 ||	LDDW	.D2T2	*++SP[1],B11:B10
 ||	MVC	.S2	B12,CSR
	LDDW	.D1T1	*++A15[1],A13:A12
 ||	LDDW	.D2T2	*++SP[1],B13:B12

	MV	.D2X	A15,SP
 	LDDW	.D2T1	*++SP[1],A15:A14
	B	.S2	__rp		; return from interruption
	LDDW	.D2T2	*+SP[1],SP:DP
	NOP		4
			.endm
;-----------------------------------------------------------
; 				interrupt macro definition
;-----------------------------------------------------------
RT_INTERRUPT_ENTRY	.macro
	SAVE_ALL	IRP,ITSR
					.endm

RT_CALL_INT .macro __isr
	CALLP	__isr,B3
	B	.S1	rt_interrupt_context_restore
	NOP    	5
					.endm
;-----------------------------------------------------------
; 				execption macro definition
;-----------------------------------------------------------
RT_EXECPTION_ENTRY	.macro
	SAVE_ALL NRP,NTSR
					.endm

RT_EXECPTION_EXIT	.macro
	RESTORE_ALL NRP,NTSR
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
	MVC	.S2	EFR,B2
	CMPEQ	.L2	1,B2,B2
 ||	MVC	.S2	TSR,B1
	MV	.D1X	B2,A2
 ||	CLR	.S2	B1,10,10,B1
	MVC	.S2	B1,TSR
 [!A2]	MVKL	.S1	rt_hw_process_exception,A0
 ||[B2]	MVKL	.S2	rt_hw_software_exception,B1
 [!A2]	MVKH	.S1	rt_hw_process_exception,A0
 ||[B2]	MVKH	.S2	rt_hw_software_exception,B1
 [!B2]	B	.S2X	A0
 [B2]	B	.S2	B1
 [!B2]	ADDAW	.D2	SP,2,B1
 [!B2]	MV	.D1X	B1,A4
	ADDKPC	.S2	ret_from_trap,B3,2
;
; return from trap
;
ret_from_trap:
	MV	.D2X	A4,B0
 [!B0]	MVKL	.S2	ret_from_exception,B3
 [!B0]	MVKH	.S2	ret_from_exception,B3
 [!B0]	BNOP	.S2	B3,5
;
; return from trap£¬restore exception context
;
ret_from_exception:
	RT_EXECPTION_EXIT
;
rt_hw_software_exception:
	MVKL	.S1	rt_hw_process_exception,A0
	MVKH	.S1	rt_hw_process_exception,A0
	B	.S2X	A0
	ADDAW	.D2	SP,2,B1
	MV	.D1X	B1,A4
	ADDKPC	.S2	ret_from_trap,B3,2
	NOP	2
;}

;-----------------------------------------------------------
; handler bad interrupt
;-----------------------------------------------------------
_bad_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_bad_handler
;}

;-----------------------------------------------------------
; handler INT4 interrupt
;-----------------------------------------------------------
_int4_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int4_handler
;}

;-----------------------------------------------------------
; handler INT5 interrupt
;-----------------------------------------------------------
_int5_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int5_handler
;}

;-----------------------------------------------------------
; handler INT6 interrupt
;-----------------------------------------------------------
_int6_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int6_handler
;}

;-----------------------------------------------------------
; handler INT7 interrupt
;-----------------------------------------------------------
_int7_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int7_handler
;}
;-----------------------------------------------------------
; handler INT8 interrupt
;-----------------------------------------------------------
_int8_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int8_handler
;}

;-----------------------------------------------------------
; handler INT9 interrupt
;-----------------------------------------------------------
_int9_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int9_handler
;}

;-----------------------------------------------------------
; handler INT10 interrupt
;-----------------------------------------------------------
_int10_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int10_handler
;}

;-----------------------------------------------------------
; handler INT11 interrupt
;-----------------------------------------------------------
_int11_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int11_handler
;}

;-----------------------------------------------------------
; handler INT12 interrupt
;-----------------------------------------------------------
_int12_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int12_handler
;}

;-----------------------------------------------------------
; handler INT13 interrupt
;-----------------------------------------------------------
_int13_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int13_handler
;}

;-----------------------------------------------------------
; handler INT14 interrupt
;-----------------------------------------------------------
_int14_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int14_handler
;}
;-----------------------------------------------------------
; handler INT15 interrupt
;-----------------------------------------------------------
_int15_handler:
;{
	RT_INTERRUPT_ENTRY
	RT_CALL_INT	hw_int15_handler
;}
	.end
