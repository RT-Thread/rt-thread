/*
 * File      : mips_context_asm.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016年9月7日     Urey         the first version
 */

#ifndef _MIPS_CONTEXT_ASM_H_
#define _MIPS_CONTEXT_ASM_H_

#define CONTEXT_SIZE	( STK_CTX_SIZE + FPU_ADJ )
#ifdef __mips_hard_float
#define FPU_ADJ			(32 * 4 + 8)		/* FP0-FP31 + CP1_STATUS */
#define FPU_CTX			( CONTEXT_SIZE - FPU_ADJ )
#else
#define FPU_ADJ			0
#endif



#ifdef __ASSEMBLY__

#ifdef __mips_hard_float
.global _fpctx_save
.global _fpctx_load
#endif

.macro SAVE_CONTEXT
	.set    push
	.set    noat
	.set    noreorder
	.set    volatile

	//save SP
	move	k1, 	sp
	move	k0, 	sp
	subu 	sp, 	k1, 	CONTEXT_SIZE
	sw		k0, 	(29 * 4)(sp)

	//save REG
	sw		$0, 	( 0 * 4)(sp)
	sw		$1, 	( 1 * 4)(sp)
	sw		$2, 	( 2 * 4)(sp)
	sw		$3, 	( 3 * 4)(sp)
	sw		$4, 	( 4 * 4)(sp)
	sw		$5, 	( 5 * 4)(sp)
	sw		$6, 	( 6 * 4)(sp)
	sw		$7, 	( 7 * 4)(sp)
	sw		$8,     ( 8 * 4)(sp)
	sw		$9,     ( 9 * 4)(sp)
	sw		$10,    (10 * 4)(sp)
	sw		$11,    (11 * 4)(sp)
	sw		$12,    (12 * 4)(sp)
	sw		$13,    (13 * 4)(sp)
	sw		$14,    (14 * 4)(sp)
	sw		$15,    (15 * 4)(sp)
	sw		$16,    (16 * 4)(sp)
	sw		$17,    (17 * 4)(sp)
	sw		$18,    (18 * 4)(sp)
	sw		$19,    (19 * 4)(sp)
	sw		$20,    (20 * 4)(sp)
	sw		$21,    (21 * 4)(sp)
	sw		$22,    (22 * 4)(sp)
	sw		$23,    (23 * 4)(sp)
	sw		$24,    (24 * 4)(sp)
	sw		$25, 	(25 * 4)(sp)
	/* K0 K1 */
	sw		$28, 	(28 * 4)(sp)
	/* SP */
	sw		$30,    (30 * 4)(sp)
	sw		$31, 	(31 * 4)(sp)

	/* STATUS CAUSE EPC.... */
	mfc0	$2, 	CP0_STATUS
	sw		$2, 	STK_OFFSET_SR(sp)

	mfc0	$2, 	CP0_CAUSE
	sw		$2, 	STK_OFFSET_CAUSE(sp)

	mfc0	$2, 	CP0_BADVADDR
	sw		$2, 	STK_OFFSET_BADVADDR(sp)

	MFC0	$2, 	CP0_EPC
	sw		$2, 	STK_OFFSET_EPC(sp)

	mfhi	$2
	sw		$2,     STK_OFFSET_HI(sp)

	mflo	$2
	sw		$2,     STK_OFFSET_LO(sp)
#ifdef __mips_hard_float
	add		a0,		sp,STK_CTX_SIZE

    mfc0 	t0, 	CP0_STATUS
    .set	push
    .set	at
    or      t0,   	M_StatusCU1
    .set 	push
    mtc0 	t0, 	CP0_STATUS

    cfc1 	t0,  	CP1_STATUS
    sw      t0   ,  0x00(a0)
	swc1    $f0,(0x04 *  1)(a0)
	swc1    $f1,(0x04 *  2)(a0)
	swc1    $f2,(0x04 *  3)(a0)
	swc1    $f3,(0x04 *  4)(a0)
	swc1    $f4,(0x04 *  5)(a0)
	swc1    $f5,(0x04 *  6)(a0)
	swc1    $f6,(0x04 *  7)(a0)
	swc1    $f7,(0x04 *  8)(a0)
	swc1    $f8,(0x04 *  9)(a0)
	swc1    $f9,(0x04 * 10)(a0)
	swc1   $f10,(0x04 * 11)(a0)
	swc1   $f11,(0x04 * 12)(a0)
	swc1   $f12,(0x04 * 13)(a0)
	swc1   $f13,(0x04 * 14)(a0)
	swc1   $f14,(0x04 * 15)(a0)
	swc1   $f15,(0x04 * 16)(a0)
	swc1   $f16,(0x04 * 17)(a0)
	swc1   $f17,(0x04 * 18)(a0)
	swc1   $f18,(0x04 * 19)(a0)
	swc1   $f19,(0x04 * 20)(a0)
	swc1   $f20,(0x04 * 21)(a0)
	swc1   $f21,(0x04 * 22)(a0)
	swc1   $f22,(0x04 * 23)(a0)
	swc1   $f23,(0x04 * 24)(a0)
	swc1   $f24,(0x04 * 25)(a0)
	swc1   $f25,(0x04 * 26)(a0)
	swc1   $f26,(0x04 * 27)(a0)
	swc1   $f27,(0x04 * 28)(a0)
	swc1   $f28,(0x04 * 29)(a0)
	swc1   $f29,(0x04 * 30)(a0)
	swc1   $f30,(0x04 * 31)(a0)
	swc1   $f31,(0x04 * 32)(a0)

	nop
#endif

	//restore a0
	lw		a0,		(REG_A0 * 4)(sp)

	.set	pop
.endm


.macro RESTORE_CONTEXT
	.set    push
	.set    noat
	.set    noreorder
	.set    volatile

#ifdef __mips_hard_float
	add		a0,	sp,STK_CTX_SIZE

    mfc0 	t0, CP0_STATUS
    .set	push
    .set	at
    or      t0, M_StatusCU1
    .set	noat
    mtc0	t0, CP0_STATUS

    lw      t0   ,   0x00(a0)
	lwc1    $f0,(0x04 *  1)(a0)
	lwc1    $f1,(0x04 *  2)(a0)
	lwc1    $f2,(0x04 *  3)(a0)
	lwc1    $f3,(0x04 *  4)(a0)
	lwc1    $f4,(0x04 *  5)(a0)
	lwc1    $f5,(0x04 *  6)(a0)
	lwc1    $f6,(0x04 *  7)(a0)
	lwc1    $f7,(0x04 *  8)(a0)
	lwc1    $f8,(0x04 *  9)(a0)
	lwc1    $f9,(0x04 * 10)(a0)
	lwc1   $f10,(0x04 * 11)(a0)
	lwc1   $f11,(0x04 * 12)(a0)
	lwc1   $f12,(0x04 * 13)(a0)
	lwc1   $f13,(0x04 * 14)(a0)
	lwc1   $f14,(0x04 * 15)(a0)
	lwc1   $f15,(0x04 * 16)(a0)
	lwc1   $f16,(0x04 * 17)(a0)
	lwc1   $f17,(0x04 * 18)(a0)
	lwc1   $f18,(0x04 * 19)(a0)
	lwc1   $f19,(0x04 * 20)(a0)
	lwc1   $f20,(0x04 * 21)(a0)
	lwc1   $f21,(0x04 * 22)(a0)
	lwc1   $f22,(0x04 * 23)(a0)
	lwc1   $f23,(0x04 * 24)(a0)
	lwc1   $f24,(0x04 * 25)(a0)
	lwc1   $f25,(0x04 * 26)(a0)
	lwc1   $f26,(0x04 * 27)(a0)
	lwc1   $f27,(0x04 * 28)(a0)
	lwc1   $f28,(0x04 * 29)(a0)
	lwc1   $f29,(0x04 * 30)(a0)
	lwc1   $f30,(0x04 * 31)(a0)
	lwc1   $f31,(0x04 * 32)(a0)
    ctc1 	t0,     CP1_STATUS                                            ;/*  restore fpp status reg      */

	nop
#endif

	/* 通用寄存器 */
	/* ZERO */
	lw		$1,  	( 1 * 4)(sp)
	/* V0   */
	lw		$3,  	( 3 * 4)(sp)
	lw		$4,  	( 4 * 4)(sp)
	lw		$5,  	( 5 * 4)(sp)
	lw		$6,  	( 6 * 4)(sp)
	lw		$7,  	( 7 * 4)(sp)
	lw		$8, 	( 8 * 4)(sp)
	lw		$9, 	( 9 * 4)(sp)
	lw		$10,    (10 * 4)(sp)
	lw		$11,    (11 * 4)(sp)
	lw		$12,    (12 * 4)(sp)
	lw		$13,    (13 * 4)(sp)
	lw		$14,    (14 * 4)(sp)
	lw		$15,    (15 * 4)(sp)
	lw		$16,    (16 * 4)(sp)
	lw		$17,    (17 * 4)(sp)
	lw		$18,    (18 * 4)(sp)
	lw		$19,    (19 * 4)(sp)
	lw		$20,    (20 * 4)(sp)
	lw		$21,    (21 * 4)(sp)
	lw		$22,    (22 * 4)(sp)
	lw		$23, 	(23 * 4)(sp)
	lw		$24, 	(24 * 4)(sp)
	lw		$25, 	(25 * 4)(sp)
	lw		$26, 	(26 * 4)(sp)
	lw		$27, 	(27 * 4)(sp)
	lw		$28, 	(28 * 4)(sp)
	/* SP */
	lw		$30, 	(30 * 4)(sp)
	lw		$31, 	(31 * 4)(sp)


	/* STATUS CAUSE EPC.... */
	lw		$2,    STK_OFFSET_HI(sp)
	mthi	$2
	lw		$2, 	STK_OFFSET_LO(sp)
	mtlo	$2

	lw		$2, 	STK_OFFSET_SR(sp)
	mtc0	$2, 	CP0_STATUS

	lw		$2, 	STK_OFFSET_BADVADDR(sp)
	mtc0	$2, 	CP0_BADVADDR

	lw		$2, 	STK_OFFSET_CAUSE(sp)
	mtc0	$2, 	CP0_CAUSE

	lw		$2, 	STK_OFFSET_EPC(sp)
	MTC0	$2, 	CP0_EPC

	//restore $2
	lw		$2,  	( 2 * 4)(sp)
	//restore sp
	lw		$29, 	(29 * 4)(sp)

	eret
	nop
    .set    pop
.endm
#endif
#endif /* _MIPS_CONTEXT_ASM_H_ */
