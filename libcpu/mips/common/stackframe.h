/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994, 95, 96, 99, 2001 Ralf Baechle
 * Copyright (C) 1994, 1995, 1996 Paul M. Antoine.
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2007  Maciej W. Rozycki
 */
#ifndef __STACKFRAME_H__
#define __STACKFRAME_H__

#include "asm.h"
#include "mipsregs.h"

/*
 * Stack layout for the INT exception handler
 * Derived from the stack layout described in asm-mips/stackframe.h
 *
 * The first PTRSIZE*6 bytes are argument save space for C subroutines.
 */

//#define PT_R0		(PTRSIZE*6)			/* 0 */
#define PT_R0		(0)						/* 0 */
#define PT_R1		((PT_R0) + LONGSIZE)	/* 1 */
#define PT_R2		((PT_R1) + LONGSIZE)	/* 2 */
#define PT_R3		((PT_R2) + LONGSIZE)	/* 3 */
#define PT_R4		((PT_R3) + LONGSIZE)	/* 4 */
#define PT_R5		((PT_R4) + LONGSIZE)	/* 5 */
#define PT_R6		((PT_R5) + LONGSIZE)	/* 6 */
#define PT_R7		((PT_R6) + LONGSIZE)	/* 7 */
#define PT_R8		((PT_R7) + LONGSIZE)	/* 8 */
#define PT_R9		((PT_R8) + LONGSIZE)	/* 9 */
#define PT_R10		((PT_R9) + LONGSIZE)	/* 10 */
#define PT_R11		((PT_R10) + LONGSIZE)	/* 11 */
#define PT_R12		((PT_R11) + LONGSIZE)	/* 12 */
#define PT_R13		((PT_R12) + LONGSIZE)	/* 13 */
#define PT_R14		((PT_R13) + LONGSIZE)	/* 14 */
#define PT_R15		((PT_R14) + LONGSIZE)	/* 15 */
#define PT_R16		((PT_R15) + LONGSIZE)	/* 16 */
#define PT_R17		((PT_R16) + LONGSIZE)	/* 17 */
#define PT_R18		((PT_R17) + LONGSIZE)	/* 18 */
#define PT_R19		((PT_R18) + LONGSIZE)	/* 19 */
#define PT_R20		((PT_R19) + LONGSIZE)	/* 20 */
#define PT_R21		((PT_R20) + LONGSIZE)	/* 21 */
#define PT_R22		((PT_R21) + LONGSIZE)	/* 22 */
#define PT_R23		((PT_R22) + LONGSIZE)	/* 23 */
#define PT_R24		((PT_R23) + LONGSIZE)	/* 24 */
#define PT_R25		((PT_R24) + LONGSIZE)	/* 25 */
#define PT_R26		((PT_R25) + LONGSIZE)	/* 26 */
#define PT_R27		((PT_R26) + LONGSIZE)	/* 27 */
#define PT_R28		((PT_R27) + LONGSIZE)	/* 28 */
#define PT_R29		((PT_R28) + LONGSIZE)	/* 29 */
#define PT_R30		((PT_R29) + LONGSIZE)	/* 30 */
#define PT_R31		((PT_R30) + LONGSIZE)	/* 31 */

/*
 * Saved special registers
 */
#define PT_STATUS	((PT_R31) + LONGSIZE)	/* 32 */
#define PT_HI		((PT_STATUS) + LONGSIZE)	/* 33 */
#define PT_LO		((PT_HI) + LONGSIZE)	/* 34 */
#define PT_BADVADDR	((PT_LO) + LONGSIZE)	/* 35 */
#define PT_CAUSE	((PT_BADVADDR) + LONGSIZE)	/* 36 */
#define PT_EPC		((PT_CAUSE) + LONGSIZE)	/* 37 */

#define PT_SIZE		((((PT_EPC) + LONGSIZE) + (PTRSIZE-1)) & ~(PTRSIZE-1))


		.macro	SAVE_AT
		.set	push
		.set	noat
		LONG_S	$1, PT_R1(sp)
		.set	pop
		.endm

		.macro	SAVE_TEMP
		mfhi	v1
		LONG_S	$8, PT_R8(sp)
		LONG_S	$9, PT_R9(sp)
		LONG_S	v1, PT_HI(sp)
		mflo	v1
		LONG_S	$10, PT_R10(sp)
		LONG_S	$11, PT_R11(sp)
		LONG_S	v1,  PT_LO(sp)
		LONG_S	$12, PT_R12(sp)
		LONG_S	$13, PT_R13(sp)
		LONG_S	$14, PT_R14(sp)
		LONG_S	$15, PT_R15(sp)
		LONG_S	$24, PT_R24(sp)
		.endm

		.macro	SAVE_STATIC
		LONG_S	$16, PT_R16(sp)
		LONG_S	$17, PT_R17(sp)
		LONG_S	$18, PT_R18(sp)
		LONG_S	$19, PT_R19(sp)
		LONG_S	$20, PT_R20(sp)
		LONG_S	$21, PT_R21(sp)
		LONG_S	$22, PT_R22(sp)
		LONG_S	$23, PT_R23(sp)
		LONG_S	$30, PT_R30(sp)
		.endm

		.macro	get_saved_sp
		nop
		.endm

		.macro	SAVE_SOME
		.set	push
		.set	noat
		.set	reorder
        move	k1, sp
8:		move	k0, sp
		PTR_SUBU sp, k1, PT_SIZE
		LONG_S	k0, PT_R29(sp)
		LONG_S	$3, PT_R3(sp)
		LONG_S	$0, PT_R0(sp)
		mfc0	v1, CP0_STATUS
		LONG_S	$2, PT_R2(sp)
		LONG_S	v1, PT_STATUS(sp)
		LONG_S	$4, PT_R4(sp)
		mfc0	v1, CP0_CAUSE
		LONG_S	$5, PT_R5(sp)
		LONG_S	v1, PT_CAUSE(sp)
		LONG_S	$6, PT_R6(sp)
		MFC0	v1, CP0_EPC
		LONG_S	$7, PT_R7(sp)
		LONG_S	v1, PT_EPC(sp)
		LONG_S	$25, PT_R25(sp)
		LONG_S	$28, PT_R28(sp)
		LONG_S	$31, PT_R31(sp)
		.set	pop
		.endm

		.macro	SAVE_ALL
		SAVE_SOME
		SAVE_AT
		SAVE_TEMP
		SAVE_STATIC
		.endm

		.macro	RESTORE_AT
		.set	push
		.set	noat
		LONG_L	$1,  PT_R1(sp)
		.set	pop
		.endm

		.macro	RESTORE_TEMP
		LONG_L	$24, PT_LO(sp)
		LONG_L	$8, PT_R8(sp)
		LONG_L	$9, PT_R9(sp)
		mtlo	$24
		LONG_L	$24, PT_HI(sp)
		LONG_L	$10, PT_R10(sp)
		LONG_L	$11, PT_R11(sp)
		mthi	$24
		LONG_L	$12, PT_R12(sp)
		LONG_L	$13, PT_R13(sp)
		LONG_L	$14, PT_R14(sp)
		LONG_L	$15, PT_R15(sp)
		LONG_L	$24, PT_R24(sp)
		.endm

		.macro	RESTORE_STATIC
		LONG_L	$16, PT_R16(sp)
		LONG_L	$17, PT_R17(sp)
		LONG_L	$18, PT_R18(sp)
		LONG_L	$19, PT_R19(sp)
		LONG_L	$20, PT_R20(sp)
		LONG_L	$21, PT_R21(sp)
		LONG_L	$22, PT_R22(sp)
		LONG_L	$23, PT_R23(sp)
		LONG_L	$30, PT_R30(sp)
		.endm

		.macro	RESTORE_SOME
		.set	push
		.set	reorder
		.set	noat
		LONG_L	v0, PT_STATUS(sp)
		mtc0	v0, CP0_STATUS
		LONG_L	v1, PT_EPC(sp)
		MTC0	v1, CP0_EPC
		LONG_L	$31, PT_R31(sp)
		LONG_L	$28, PT_R28(sp)
		LONG_L	$25, PT_R25(sp)
		LONG_L	$7,  PT_R7(sp)
		LONG_L	$6,  PT_R6(sp)
		LONG_L	$5,  PT_R5(sp)
		LONG_L	$4,  PT_R4(sp)
		LONG_L	$3,  PT_R3(sp)
		LONG_L	$2,  PT_R2(sp)
		.set	pop
		.endm

		.macro	RESTORE_SP_AND_RET
		LONG_L	sp, PT_R29(sp)
		.set	mips3
		eret
		.set	mips0
		.endm


		.macro	RESTORE_SP
		LONG_L	sp, PT_R29(sp)
		.endm

		.macro	RESTORE_ALL
		RESTORE_TEMP
		RESTORE_STATIC
		RESTORE_AT
		RESTORE_SOME
		RESTORE_SP
		.endm

		.macro	RESTORE_ALL_AND_RET
		RESTORE_TEMP
		RESTORE_STATIC
		RESTORE_AT
		RESTORE_SOME
		RESTORE_SP_AND_RET
		.endm

#endif /* end of __STACKFRAME_H__ */

