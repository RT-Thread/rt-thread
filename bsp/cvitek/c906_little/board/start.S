/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */
#include "riscv-virt.h"
.org 0
	.section .vectors, "ax"
	.globl _start
	.type _start,@function
_start:
	.cfi_startproc
	.cfi_undefined ra
.option push
.option norelax
//	la  gp, __global_pointer$
.option pop

	// Continue primary hart
	csrr a0, mhartid
	li   a1, PRIM_HART
	bne  a0, a1, secondary

	li x1, 0
	li x2, 0
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
	li x10, 0
	li x11, 0
	li x12, 0
	li x13, 0
	li x14, 0
	li x15, 0
	li x16, 0
	li x17, 0
	li x18, 0
	li x19, 0
	li x20, 0
	li x21, 0
	li x22, 0
	li x23, 0
	li x24, 0
	li x25, 0
	li x26, 0
	li x27, 0
	li x28, 0
	li x29, 0
	li x30, 0
	li x31, 0

	// enable interrupt
//	li x3, 0x880
//	csrw mie, x3

	csrw mie, 0
	csrw mip, 0
   	la t0, trap_entry
 	csrw mtvec, t0
	
#ifndef RISCV_QEMU
	// invalidate all memory for BTB,BHT,DCACHE,ICACHE
	li x3, 0x30013
	csrs mcor, x3
	// enable ICACHE,DCACHE,BHT,BTB,RAS,WA
	li x3, 0x7f
	csrs mhcr, x3
	// enable data_cache_prefetch, amr
	li x3, 0x610c
	csrs mhint, x3 #mhint
#endif
	# enable fp
	li x3, 0x1 << 13
	csrs mstatus, x3

	// Primary hart
	la sp, _stack_top

	// Load data section
	la a0, _data_lma
	la a1, _data
	la a2, _edata
	bgeu a1, a2, 2f
1:
	LOAD t0, (a0)
	STOR t0, (a1)
	addi a0, a0, REGSIZE
	addi a1, a1, REGSIZE
	bltu a1, a2, 1b
2:

	// Clear bss section
	la a0, _bss
	la a1, _ebss
	bgeu a0, a1, 2f
1:
	// reduce branch time, be sure about bss alignment in linker script
	STOR zero, 0x00 (a0)
	STOR zero, 0x08 (a0)
	STOR zero, 0x10 (a0)
	STOR zero, 0x18 (a0)
	STOR zero, 0x20 (a0)
	STOR zero, 0x28 (a0)
	STOR zero, 0x30 (a0)
	STOR zero, 0x38 (a0)
	addi a0, a0, REGSIZE * 8
	bltu a0, a1, 1b
2:

	// argc, argv, envp is 0
	li  a0, 0
	li  a1, 0
	li  a2, 0
	jal entry
1:
	wfi
	j 1b

secondary:
	// TODO: Multicore is not supported
	wfi
	j secondary
	.cfi_endproc
