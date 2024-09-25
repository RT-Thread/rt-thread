/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifdef __riscv_flen

#if __riscv_flen != 64
# error single-float only is not supported
#endif

#define get_f32(which) fmv.x.s a0, which; jr t0
#define put_f32(which) fmv.s.x which, a0; jr t0
#if __riscv_xlen == 64
# define get_f64(which) fmv.x.d a0, which; jr t0
# define put_f64(which) fmv.d.x which, a0; jr t0
#else
# define get_f64(which) fsd which, 0(a0); jr t0
# define put_f64(which) fld which, 0(a0); jr t0
#endif

	.text
	.option norvc
	.globl get_f32_reg
	get_f32_reg:
		get_f32(f0)
		get_f32(f1)
		get_f32(f2)
		get_f32(f3)
		get_f32(f4)
		get_f32(f5)
		get_f32(f6)
		get_f32(f7)
		get_f32(f8)
		get_f32(f9)
		get_f32(f10)
		get_f32(f11)
		get_f32(f12)
		get_f32(f13)
		get_f32(f14)
		get_f32(f15)
		get_f32(f16)
		get_f32(f17)
		get_f32(f18)
		get_f32(f19)
		get_f32(f20)
		get_f32(f21)
		get_f32(f22)
		get_f32(f23)
		get_f32(f24)
		get_f32(f25)
		get_f32(f26)
		get_f32(f27)
		get_f32(f28)
		get_f32(f29)
		get_f32(f30)
		get_f32(f31)

	.text
	.globl put_f32_reg
	put_f32_reg:
		put_f32(f0)
		put_f32(f1)
		put_f32(f2)
		put_f32(f3)
		put_f32(f4)
		put_f32(f5)
		put_f32(f6)
		put_f32(f7)
		put_f32(f8)
		put_f32(f9)
		put_f32(f10)
		put_f32(f11)
		put_f32(f12)
		put_f32(f13)
		put_f32(f14)
		put_f32(f15)
		put_f32(f16)
		put_f32(f17)
		put_f32(f18)
		put_f32(f19)
		put_f32(f20)
		put_f32(f21)
		put_f32(f22)
		put_f32(f23)
		put_f32(f24)
		put_f32(f25)
		put_f32(f26)
		put_f32(f27)
		put_f32(f28)
		put_f32(f29)
		put_f32(f30)
		put_f32(f31)

	.text
	.globl get_f64_reg
	get_f64_reg:
		get_f64(f0)
		get_f64(f1)
		get_f64(f2)
		get_f64(f3)
		get_f64(f4)
		get_f64(f5)
		get_f64(f6)
		get_f64(f7)
		get_f64(f8)
		get_f64(f9)
		get_f64(f10)
		get_f64(f11)
		get_f64(f12)
		get_f64(f13)
		get_f64(f14)
		get_f64(f15)
		get_f64(f16)
		get_f64(f17)
		get_f64(f18)
		get_f64(f19)
		get_f64(f20)
		get_f64(f21)
		get_f64(f22)
		get_f64(f23)
		get_f64(f24)
		get_f64(f25)
		get_f64(f26)
		get_f64(f27)
		get_f64(f28)
		get_f64(f29)
		get_f64(f30)
		get_f64(f31)

	.text
	.globl put_f64_reg
	put_f64_reg:
		put_f64(f0)
		put_f64(f1)
		put_f64(f2)
		put_f64(f3)
		put_f64(f4)
		put_f64(f5)
		put_f64(f6)
		put_f64(f7)
		put_f64(f8)
		put_f64(f9)
		put_f64(f10)
		put_f64(f11)
		put_f64(f12)
		put_f64(f13)
		put_f64(f14)
		put_f64(f15)
		put_f64(f16)
		put_f64(f17)
		put_f64(f18)
		put_f64(f19)
		put_f64(f20)
		put_f64(f21)
		put_f64(f22)
		put_f64(f23)
		put_f64(f24)
		put_f64(f25)
		put_f64(f26)
		put_f64(f27)
		put_f64(f28)
		put_f64(f29)
		put_f64(f30)
		put_f64(f31)

#endif
