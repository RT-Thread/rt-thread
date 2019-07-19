/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-09-04     bernard      porting to Jz47xx
 * 2019-07-19     Zhou Yanjie  clean up code
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "../common/mips_def.h"
#include "../common/stackframe.h"

	.section ".start", "ax"
	.set noreorder

	/* the program entry */
	.globl  _start
_start:
	.set	noreorder
	la	ra, _start

	/* disable interrupt */
	mfc0	t0, CP0_STATUS
	and 	t0, 0xfffffffe	# By default it will be disabled.
	mtc0	t0, CP0_STATUS	# Set CPU to disable interrupt.
	nop

	/* disable cache */
	mfc0	t0, CP0_CONFIG
	and	t0, 0xfffffff8
	or	t0, 0x2		# disable,!default value is not it!
	mtc0	t0, CP0_CONFIG	# Set CPU to disable cache.
	nop

	/* setup stack pointer */
	li	sp, SYSTEM_STACK
	la	gp, _gp

	/* clear bss */
	la	t0, __bss_start
	la	t1, __bss_end
_clr_bss_loop:
	sw	zero, 0(t0)
	bne	t0, t1, _clr_bss_loop
	addiu	t0, t0, 4

	/* jump to RT-Thread RTOS */
	jal	rtthread_startup
	nop

	/* restart, never die */
	j	_start
	nop
	.set	reorder

	.globl  cp0_get_cause
cp0_get_cause:
	mfc0	v0, CP0_CAUSE
	jr	ra
	nop

	.globl  cp0_get_status
cp0_get_status:
	mfc0	v0, CP0_STATUS
	jr	ra
	nop

	.globl	cp0_get_hi
cp0_get_hi:
	mfhi	v0
	jr	ra
	nop

	.globl	cp0_get_lo
cp0_get_lo:
	mflo	v0
	jr	ra
	nop

	.extern tlb_refill_handler
	.extern cache_error_handler

	/* Exception Handler */

	/* 0x0 - TLB refill handler */
	.section .vectors.1, "ax", %progbits
	.global tlb_refill_exception
	.type	tlb_refill_exception,@function
tlb_refill_exception:
	j	tlb_refill_handler
	nop
	
	/* 0x100 - Cache error handler */
	.section .vectors.2, "ax", %progbits
	j	cache_error_handler
	nop
    
	/* 0x180 - Exception/Interrupt handler */
	.section .vectors.3, "ax", %progbits
	.global general_exception
	.type	general_exception,@function
general_exception:
	j	_general_exception_handler
	nop
    
	/* 0x200 - Special Exception Interrupt handler (when IV is set in CP0_CAUSE) */
	.section .vectors.4, "ax", %progbits
	.global irq_exception
	.type	irq_exception,@function
irq_exception:
	j	_irq_handler
	nop
	
	.section .vectors, "ax", %progbits
	.extern mips_irq_handle

	/* general exception handler */
_general_exception_handler:
	.set	noreorder
	la	k0, mips_irq_handle
	jr	k0
	nop
	.set	reorder

	/* interrupt handler */
_irq_handler:
	.set	noreorder
	la	k0, mips_irq_handle
	jr	k0
	nop
	.set	reorder
