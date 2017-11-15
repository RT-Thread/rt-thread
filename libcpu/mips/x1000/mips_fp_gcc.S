/*
 * File      : mips_vfp32_asm.S
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
 * 2016Äê9ÔÂ9ÈÕ     Urey         the first version
 */

#ifndef __ASSEMBLY__
#	define __ASSEMBLY__
#endif

#ifdef __mips_hard_float

.module hardfloat
.module doublefloat
.set nomips16

#include "../common/mips.h"
#undef fp

	.global mips_vfp32_init
LEAF(mips_vfp32_init)
    mfc0 	t0, CP0_STATUS
    or      t0 , M_StatusCU1
    mtc0 	t0, CP0_STATUS
    jr      ra
    nop
END(mips_vfp32_init)

#
# FUNCTION:	_fpctx_save
#
# DESCRIPTION:	save floating point registers to memory starting at a0
#
# RETURNS:	int
#			0:	No context saved
#			CTX_*:	Type of context stored
#
	.global _fpctx_save
LEAF(_fpctx_save)
	sw 		zero, LINKCTX_NEXT(a0)
	mfc0	t0, CP0_STATUS
	li		t1, M_StatusCU1
	and		t1, t0, t1
	bnez	t1, 1f
	# FP not enabled, bail out
	move	v0, zero
	jr		ra

1:	# Save FP32 base
	li		t1, ST0_FR
	and		t0, t0, t1
	cfc1	t2, $31
	sw		t2, FP32CTX_CSR(a0)
	sdc1	$f0, FP32CTX_0(a0)
	sdc1	$f2, FP32CTX_2(a0)
	sdc1	$f4, FP32CTX_4(a0)
	sdc1	$f6, FP32CTX_6(a0)
	sdc1	$f8, FP32CTX_8(a0)
	sdc1	$f10, FP32CTX_10(a0)
	sdc1	$f12, FP32CTX_12(a0)
	sdc1	$f14, FP32CTX_14(a0)
	sdc1	$f16, FP32CTX_16(a0)
	sdc1	$f18, FP32CTX_18(a0)
	sdc1	$f20, FP32CTX_20(a0)
	sdc1	$f22, FP32CTX_22(a0)
	sdc1	$f24, FP32CTX_24(a0)
	sdc1	$f26, FP32CTX_26(a0)
	sdc1	$f28, FP32CTX_28(a0)
	sdc1	$f30, FP32CTX_30(a0)
	bnez	t0, 2f
	li		v0, LINKCTX_TYPE_FP32
	sw		v0, LINKCTX_ID(a0)
	jr		ra

2:	# Save FP64 extra
.set	push
.set	fp=64
	sdc1	$f1, FP64CTX_1(a0)
	sdc1	$f3, FP64CTX_3(a0)
	sdc1	$f5, FP64CTX_5(a0)
	sdc1	$f7, FP64CTX_7(a0)
	sdc1	$f9, FP64CTX_9(a0)
	sdc1	$f11, FP64CTX_11(a0)
	sdc1	$f13, FP64CTX_13(a0)
	sdc1	$f15, FP64CTX_15(a0)
	sdc1	$f17, FP64CTX_17(a0)
	sdc1	$f19, FP64CTX_19(a0)
	sdc1	$f21, FP64CTX_21(a0)
	sdc1	$f23, FP64CTX_23(a0)
	sdc1	$f25, FP64CTX_25(a0)
	sdc1	$f27, FP64CTX_27(a0)
	sdc1	$f29, FP64CTX_29(a0)
	sdc1	$f31, FP64CTX_31(a0)
.set	pop
	li	v0, LINKCTX_TYPE_FP64
	sw	v0, LINKCTX_ID(a0)
	jr	ra
END(_fpctx_save)

#
# FUNCTION:	_fpctx_load
#
# DESCRIPTION:	load floating point registers from context chain starting at a0
#
# RETURNS:	int
#			0:	Unrecognised context
#			CTX_*:	Type of context restored
#
	.global _fpctx_load
LEAF(_fpctx_load)
	lw	v0, LINKCTX_ID(a0)
	# Detect type
	li	t0, LINKCTX_TYPE_FP64
	li	t1, LINKCTX_TYPE_FP32
	li	t2, M_StatusCU1
	beq	v0, t0, 0f
	beq	v0, t1, 1f
	# Don't recognise this context, fail
	move	v0, zero
	jr	ra

0: 	# FP64 context
	# Enable CU1
	di	t3
	ehb
	or	t3, t3, t2
	mtc0	t3, CP0_STATUS
	ehb
	# Load FP64 extra
.set	push
.set	fp=64
	ldc1	$f1, FP64CTX_1(a0)
	ldc1	$f3, FP64CTX_3(a0)
	ldc1	$f5, FP64CTX_5(a0)
	ldc1	$f7, FP64CTX_7(a0)
	ldc1	$f9, FP64CTX_9(a0)
	ldc1	$f11, FP64CTX_11(a0)
	ldc1	$f13, FP64CTX_13(a0)
	ldc1	$f15, FP64CTX_15(a0)
	ldc1	$f17, FP64CTX_17(a0)
	ldc1	$f19, FP64CTX_19(a0)
	ldc1	$f21, FP64CTX_21(a0)
	ldc1	$f23, FP64CTX_23(a0)
	ldc1	$f25, FP64CTX_25(a0)
	ldc1	$f27, FP64CTX_27(a0)
	ldc1	$f29, FP64CTX_29(a0)
	ldc1	$f31, FP64CTX_31(a0)
.set	pop
1: 	# FP32 context
	# Enable CU1
	di	t3
	ehb
	or	t3, t3, t2
	mtc0	t3, CP0_STATUS
	ehb
	# Load FP32 base
	lw	t1, FP32CTX_CSR(a0)
	ctc1	t1, $31
	ldc1	$f0, FP32CTX_0(a0)
	ldc1	$f2, FP32CTX_2(a0)
	ldc1	$f4, FP32CTX_4(a0)
	ldc1	$f6, FP32CTX_6(a0)
	ldc1	$f8, FP32CTX_8(a0)
	ldc1	$f10, FP32CTX_10(a0)
	ldc1	$f12, FP32CTX_12(a0)
	ldc1	$f14, FP32CTX_14(a0)
	ldc1	$f16, FP32CTX_16(a0)
	ldc1	$f18, FP32CTX_18(a0)
	ldc1	$f20, FP32CTX_20(a0)
	ldc1	$f22, FP32CTX_22(a0)
	ldc1	$f24, FP32CTX_24(a0)
	ldc1	$f26, FP32CTX_26(a0)
	ldc1	$f28, FP32CTX_28(a0)
	ldc1	$f30, FP32CTX_30(a0)
	# Return CTX_FP32/64
	jr	ra
END(_fpctx_load)

#endif
