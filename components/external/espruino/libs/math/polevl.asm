;	Static Name Aliases
;
	TITLE   polevl

_TEXT	SEGMENT  BYTE PUBLIC 'CODE'
_TEXT	ENDS
CONST	SEGMENT  WORD PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS
_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS
DGROUP	GROUP	CONST,	_BSS,	_DATA
	ASSUME  CS: _TEXT, DS: DGROUP, SS: DGROUP, ES: DGROUP
PUBLIC  _polevl
PUBLIC  _p1evl
_DATA	SEGMENT
EXTRN	__chkstk:NEAR
EXTRN	__fac:NEAR
EXTRN	__fltused:NEAR
$T20001		DQ	0000000000H    ;	.0000000000000000
ans	DQ	0
ctrlw	DW	0
_DATA ENDS
_TEXT      SEGMENT
	PUBLIC	_polevl
_polevl	PROC NEAR
	push	bp
	mov	bp,sp
	mov	ax,12
	call	__chkstk
	push	si
	mov	si,[bp+12]
;	fstcw	ctrlw
;	fwait
;	mov	ax,ctrlw
;	or	ax,00100h
;	mov	ctrlw,ax
;	fldcw	ctrlw

	fldz
	fwait	
	mov	ax,[bp+14]
	inc	ax
	mov	[bp-12],ax
$D15:
	fmul	QWORD PTR [bp+4]
	add	si,8
	fwait
	fadd	QWORD PTR [si-8]
	fwait	
	dec	WORD PTR [bp-12]
	jne	$D15
	fstp	ans
;	fstcw	ctrlw
;	fwait
;	mov	ax,ctrlw
;	and	ax,0feffh
;	mov	ctrlw,ax
;	fldcw	ctrlw

	lea	ax, ans
	fwait	
	pop	si
	mov	sp,bp
	pop	bp
	ret	
_polevl	ENDP

	PUBLIC	_p1evl
_p1evl	PROC NEAR
	push	bp
	mov	bp,sp
	mov	ax,12
	call	__chkstk
	push	si

;	fstcw	ctrlw
;	fwait
;	mov	ax,ctrlw
;	or	ax,00100h
;	mov	ctrlw,ax
;	fldcw	ctrlw

	mov	si,[bp+12]
	fld	QWORD PTR [bp+4]
	add	si,8
	fadd	QWORD PTR [si-8]
	fwait	
	mov	ax,[bp+14]
	dec	ax
	mov	[bp-12],ax
$D26:
	fmul	QWORD PTR [bp+4]
	add	si,8
	fadd	QWORD PTR [si-8]
	fwait	
	dec	WORD PTR [bp-12]
	jne	$D26
	fstp	ans
	lea	ax, ans
;	fstcw	ctrlw
;	fwait
;	mov	ax,ctrlw
;	and	ax,0feffh
;	mov	ctrlw,ax
;	fldcw	ctrlw
	fwait	
	pop	si
	mov	sp,bp
	pop	bp
	ret	
_p1evl	ENDP

_TEXT	ENDS
END
