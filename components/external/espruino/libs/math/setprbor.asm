;
; Borland assembler header
;
; Microsoft MASM subroutines for setting coprocessor precision
;
.286
.287
PREC_TEXT	SEGMENT  BYTE PUBLIC 'CODE'
PREC_TEXT	ENDS
DGROUP	group	_DATA,_BSS
	assume	cs:PREC_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends

; exception masks (1 = masked)
;   1  invalid operation
;   2  denormalized operand
;   4  zero divide
;   8  overflow
;  10  underflow
;  20  precision

_DATA SEGMENT

; double precision setting
;;ctlwrd dw 01230h ; note this traps on denormal operands!
;;ctld dw 0133fh   ; this doesn't trap
ctld dw 01230h

; single precision
ctls dw 01030h

; long double precision
ctlld dw 01320h

_DATA ENDS

PREC_TEXT	segment byte public 'CODE'
	assume	cs:PREC_TEXT,ds:DGROUP
; Set coprocessor to single precision float
	PUBLIC	_sprec
_sprec	PROC FAR
	fclex
	fwait
	finit
	fwait
	fldcw word ptr ctls
	fwait
	ret
_sprec ENDP

; set coprocessor to long double precision
	PUBLIC	_ldprec
_ldprec PROC far
	fclex
	fwait
	finit
	fwait
	fldcw word ptr ctlld
	fwait
	ret
_ldprec ENDP

; set coprocessor to double precision
	PUBLIC	_dprec
_dprec PROC far
	fclex
	fwait
	finit
	fwait
	fldcw word ptr ctld
	fwait
	ret
_dprec ENDP


; get a double promoted to long double size
; getld( &doub, &ldoub );
	PUBLIC	_getld
_getld	PROC far
	push bp
	mov bp,sp
	push bx
	mov bx, word ptr [bp+4]
;	fld st(0)
	fld qword ptr [bx]
	mov bx, word ptr [bp+6]
	fstp tbyte ptr [bx]
	mov bx, word ptr [bp+4]
	fld qword ptr [bx]
	mov bx, word ptr [bp+8]
	fstp qword ptr [bx]
	pop bx
	pop bp
	ret
_getld	ENDP

	PUBLIC	_getprec
_getprec	PROC far
	push bp
	mov bp,sp
	sub sp,4
	fstcw [bp-4]
	fwait
	mov ax,[bp-4]
	add sp,4
	pop bp
	ret
_getprec	ENDP


	PUBLIC	_fpclear
_fpclear	PROC far
	push bp
	mov bp,sp
	fnclex
	fwait
	pop bp
	ret
_fpclear	ENDP


	PUBLIC	_noexcept
_noexcept	PROC far
	push bp
	mov bp,sp
	push ax
	sub sp,4
	fnclex
	fwait
	fstcw [bp-4]
	fwait
	mov ax,[bp-4]
	and ax,0FFC0h
	or ax,003fh
	mov [bp-4],ax
	fldcw [bp-4]
	add sp,4
	pop ax
	pop bp
	ret
_noexcept	ENDP

; single precision square root
; assumes coprocessor precision already set up
; return value in static __fac
	PUBLIC	_sqrtf
_sqrtf	PROC FAR
	push bp
	mov bp,sp
	fld	DWORD PTR [bp+6]
	fsqrt
	fwait	
	mov	sp,bp
	pop bp
	ret
_sqrtf	ENDP

; double precision square root
; assumes coprocessor precision already set up
; return value in static __fac
	PUBLIC	_sqrt
_sqrt	PROC FAR
	push bp
	mov bp,sp
	fld	QWORD PTR [bp+6]
	fsqrt
	fwait	
	mov	sp,bp
	pop bp
	ret
_sqrt	ENDP


; long double precision square root
; assumes coprocessor precision already set up
; return value in fp register
	PUBLIC	_sqrtl
_sqrtl	PROC FAR
	push bp
	mov bp,sp
	fld tbyte ptr [bp+6]
	fsqrt
	fwait	
	mov	sp,bp
	pop bp
	ret
_sqrtl	ENDP


PREC_TEXT	ends
_DATA	segment word public 'DATA'
s@	label	byte
_DATA	ends
PREC_TEXT	segment byte public 'CODE'
PREC_TEXT	ends
_s@	equ	s@
	public _sprec
	public _dprec
	public _ldprec
	end
