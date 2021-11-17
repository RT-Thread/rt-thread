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
; 			build thread stack for C6000 DSP
;-----------------------------------------------------------

;-----------------------------------------------------------
;					macro definition
;-----------------------------------------------------------
ADDRESS_MSK .set    0xFFFFFFF0

;
;-----------------------------------------------------------
;

    .sect   ".text"
;
;-----------------------------------------------------------
;

;
; rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit)
; tentry  --> A4
; parameter --> B4
; stack_addr --> A6
; texit  --> B6
;{
    .global rt_hw_stack_init
rt_hw_stack_init:
	SUB		A6,1,B1			;
	MVKL	ADDRESS_MSK,A1	;
	MVKH	ADDRESS_MSK,A1	; Build address mask
	MVC		CSR,B0			;
	AND		-2,B0,B0		; Clear GIE bit
	OR		2,B0,B0			; Set PGIE bit for interrupt return
	AND		A1,B1,B1		; Ensure alignment
;
; Actually build the stack frame.
;
	MV	B1,A3
	MV	B14,A2
	STDW	A3:A2,*--B1[1]	; Initial B15:B14
	SUBAW	.D2	B1,2,B1
	ZERO	A2
	ZERO	A3              ; Clear value
	STDW	A3:A2,*B1--[1]	; Initial A15:A14
	STDW	A3:A2,*B1--[1]	; Initial A13:A12
	STDW	A3:A2,*B1--[1]	; Initial A11:A10
	STDW	A3:A2,*B1--[1]	; Initial A9:A8
	STDW	A3:A2,*B1--[1]	; Initial A7:A6
	MV	B4,A2
	STDW	A3:A2,*B1--[1]	; Initial A5:A4
	ZERO	A2
	STDW	A3:A2,*B1--[1]	; Initial A3:A2
	STDW	A3:A2,*B1--[1]	; Initial A1:A0

	STDW	A3:A2,*B1--[1]	; Initial A31:A30
	STDW	A3:A2,*B1--[1]	; Initial A29:A28
	STDW	A3:A2,*B1--[1]	; Initial A27:A26
	STDW	A3:A2,*B1--[1]	; Initial A25:A24
	STDW	A3:A2,*B1--[1]	; Initial A23:A22
	STDW	A3:A2,*B1--[1]	; Initial A21:A20
	STDW	A3:A2,*B1--[1]	; Initial A19:A18
	STDW	A3:A2,*B1--[1]	; Initial A17:A16

	STDW	A3:A2,*B1--[1]	; Initial B13:B12
	STDW	A3:A2,*B1--[1]	; Initial B11:B10
	STDW	A3:A2,*B1--[1]	; Initial B9:B8
	STDW	A3:A2,*B1--[1]	; Initial B7:B6
	STDW	A3:A2,*B1--[1]	; Initial B5:B4
	MV	B6,A3
	STDW	A3:A2,*B1--[1]	; Initial B3:B2
	ZERO	A3
	STDW	A3:A2,*B1--[1]	; Initial B1:B0

	STDW	A3:A2,*B1--[1]	; Initial B31:B30
	STDW	A3:A2,*B1--[1]	; Initial B29:B28
	STDW	A3:A2,*B1--[1]	; Initial B27:B26
	STDW	A3:A2,*B1--[1]	; Initial B25:B24
	STDW	A3:A2,*B1--[1]	; Initial B23:B22
	STDW	A3:A2,*B1--[1]	; Initial B21:B20
	STDW	A3:A2,*B1--[1]	; Initial B19:B18
	STDW	A3:A2,*B1--[1]	; Initial B17:B16

	MV	A4,A3
	MV	B0,A2
	STDW	A3:A2,*B1--[1]	; Initial PC:CSR

	ZERO	A2
	ZERO	A3
	STDW	A3:A2,*B1--[1]	; Initial ILC:RILC
	B	B3
	MVKL	0x3,B0
	MV	B0,A3
	MVKL	1,A2
	STDW	A3:A2,*B1--[1]	; Initial TSR:stack type
	MV	B1,A4				; Save to TCB
;}
	.end
