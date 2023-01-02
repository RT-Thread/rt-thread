/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 */
#include "cpuport.h"

.align 2
.global IRQ_Handler
IRQ_Handler:
#ifdef ARCH_RISCV_FPU
    addi    sp, sp, -32 * FREGBYTES

    FSTORE  f0, 0 * FREGBYTES(sp)
    FSTORE  f1, 1 * FREGBYTES(sp)
    FSTORE  f2, 2 * FREGBYTES(sp)
    FSTORE  f3, 3 * FREGBYTES(sp)
    FSTORE  f4, 4 * FREGBYTES(sp)
    FSTORE  f5, 5 * FREGBYTES(sp)
    FSTORE  f6, 6 * FREGBYTES(sp)
    FSTORE  f7, 7 * FREGBYTES(sp)
    FSTORE  f8, 8 * FREGBYTES(sp)
    FSTORE  f9, 9 * FREGBYTES(sp)
    FSTORE  f10, 10 * FREGBYTES(sp)
    FSTORE  f11, 11 * FREGBYTES(sp)
    FSTORE  f12, 12 * FREGBYTES(sp)
    FSTORE  f13, 13 * FREGBYTES(sp)
    FSTORE  f14, 14 * FREGBYTES(sp)
    FSTORE  f15, 15 * FREGBYTES(sp)
    FSTORE  f16, 16 * FREGBYTES(sp)
    FSTORE  f17, 17 * FREGBYTES(sp)
    FSTORE  f18, 18 * FREGBYTES(sp)
    FSTORE  f19, 19 * FREGBYTES(sp)
    FSTORE  f20, 20 * FREGBYTES(sp)
    FSTORE  f21, 21 * FREGBYTES(sp)
    FSTORE  f22, 22 * FREGBYTES(sp)
    FSTORE  f23, 23 * FREGBYTES(sp)
    FSTORE  f24, 24 * FREGBYTES(sp)
    FSTORE  f25, 25 * FREGBYTES(sp)
    FSTORE  f26, 26 * FREGBYTES(sp)
    FSTORE  f27, 27 * FREGBYTES(sp)
    FSTORE  f28, 28 * FREGBYTES(sp)
    FSTORE  f29, 29 * FREGBYTES(sp)
    FSTORE  f30, 30 * FREGBYTES(sp)
    FSTORE  f31, 31 * FREGBYTES(sp)
#endif

	addi sp, sp, - (32 * REGBYTES)
	STORE x1, 1 * REGBYTES( sp )			//x1:ra

	STORE x4, 4 * REGBYTES( sp )
	STORE x5, 5 * REGBYTES( sp )
	STORE x6, 6 * REGBYTES( sp )
	STORE x7, 7 * REGBYTES( sp )
	STORE x8, 8 * REGBYTES( sp )
	STORE x9, 9 * REGBYTES( sp )
	STORE x10, 10 * REGBYTES( sp )
	STORE x11, 11 * REGBYTES( sp )
	STORE x12, 12 * REGBYTES( sp )
	STORE x13, 13 * REGBYTES( sp )
	STORE x14, 14 * REGBYTES( sp )
	STORE x15, 15 * REGBYTES( sp )
	STORE x16, 16 * REGBYTES( sp )
	STORE x17, 17 * REGBYTES( sp )
	STORE x18, 18 * REGBYTES( sp )
	STORE x19, 19 * REGBYTES( sp )
	STORE x20, 20 * REGBYTES( sp )
	STORE x21, 21 * REGBYTES( sp )
	STORE x22, 22 * REGBYTES( sp )
	STORE x23, 23 * REGBYTES( sp )
	STORE x24, 24 * REGBYTES( sp )
	STORE x25, 25 * REGBYTES( sp )
	STORE x26, 26 * REGBYTES( sp )
	STORE x27, 27 * REGBYTES( sp )
	STORE x28, 28 * REGBYTES( sp )
	STORE x29, 29 * REGBYTES( sp )
	STORE x30, 30 * REGBYTES( sp )
	STORE x31, 31 * REGBYTES( sp )

    csrr a0, mepc
	STORE a0, 0 * REGBYTES( sp )			//epc

    csrr a0, mstatus
	STORE a0, 2 * REGBYTES( sp )			//mstatus

    /* Save the thread stack frame base to mscratch */
    csrw mscratch, sp

    /* switch to interrupt stack */
    la sp, __StackTop

    /* interrupt handle */
	la a0, rt_interrupt_enter
	jalr a0

	csrr a0, mcause
	li t0, 0x807FFFFF
	and a0, a0, t0

	srli a2, a0, __riscv_xlen - 1		/* MSB of mcause is 1 if handing an asynchronous interrupt - shift to LSB to clear other bits. */
	beq a2, x0, handle_synchronous		/* Branch past interrupt handing if not asynchronous. */

	csrr  t1, mcause
	andi  t1, t1, 0x3FF
	slli  t1, t1, 2
	la  t0, g_irqvector
	add t0, t0, t1
	lw  t2, 0(t0)
	jalr t2
	
	j processed_source

handle_synchronous:
//	la t0, exception_entry
//	jalr t0

processed_source:

	la a0, rt_interrupt_leave
	jalr a0

    /* switch to thread stack */
    csrr  sp, mscratch

   /* need to switch new thread */
    la    a0, rt_thread_switch_interrupt_flag
    lw    a1, 0(a0)
    beqz  a1, interrupt_exit
	
	sw zero, 0(a0)

	la    a0, rt_interrupt_from_thread
	LOAD  a1, 0(a0)
	STORE sp, 0(a1)

	la    a0, rt_interrupt_to_thread
	LOAD  a1, 0(a0)
	LOAD  sp, 0(a1)

interrupt_exit:
    /* resw ra to mepc */
    LOAD a0,   0 * REGBYTES(sp)
    csrw mepc, a0

    LOAD x1,   1 * REGBYTES(sp)

    li    t0, 0x00007800
    csrw  mstatus, t0

    LOAD a0,   2 * REGBYTES(sp)
    csrs mstatus, a0

    LOAD x4,   4 * REGBYTES(sp)
    LOAD x5,   5 * REGBYTES(sp)
    LOAD x6,   6 * REGBYTES(sp)
    LOAD x7,   7 * REGBYTES(sp)
    LOAD x8,   8 * REGBYTES(sp)
    LOAD x9,   9 * REGBYTES(sp)
    LOAD x10, 10 * REGBYTES(sp)
    LOAD x11, 11 * REGBYTES(sp)
    LOAD x12, 12 * REGBYTES(sp)
    LOAD x13, 13 * REGBYTES(sp)
    LOAD x14, 14 * REGBYTES(sp)
    LOAD x15, 15 * REGBYTES(sp)
    LOAD x16, 16 * REGBYTES(sp)
    LOAD x17, 17 * REGBYTES(sp)
    LOAD x18, 18 * REGBYTES(sp)
    LOAD x19, 19 * REGBYTES(sp)
    LOAD x20, 20 * REGBYTES(sp)
    LOAD x21, 21 * REGBYTES(sp)
    LOAD x22, 22 * REGBYTES(sp)
    LOAD x23, 23 * REGBYTES(sp)
    LOAD x24, 24 * REGBYTES(sp)
    LOAD x25, 25 * REGBYTES(sp)
    LOAD x26, 26 * REGBYTES(sp)
    LOAD x27, 27 * REGBYTES(sp)
    LOAD x28, 28 * REGBYTES(sp)
    LOAD x29, 29 * REGBYTES(sp)
    LOAD x30, 30 * REGBYTES(sp)
    LOAD x31, 31 * REGBYTES(sp)

    addi sp,  sp, 32 * REGBYTES
#ifdef ARCH_RISCV_FPU
    FLOAD   f0, 0 * FREGBYTES(sp)
    FLOAD   f1, 1 * FREGBYTES(sp)
    FLOAD   f2, 2 * FREGBYTES(sp)
    FLOAD   f3, 3 * FREGBYTES(sp)
    FLOAD   f4, 4 * FREGBYTES(sp)
    FLOAD   f5, 5 * FREGBYTES(sp)
    FLOAD   f6, 6 * FREGBYTES(sp)
    FLOAD   f7, 7 * FREGBYTES(sp)
    FLOAD   f8, 8 * FREGBYTES(sp)
    FLOAD   f9, 9 * FREGBYTES(sp)
    FLOAD   f10, 10 * FREGBYTES(sp)
    FLOAD   f11, 11 * FREGBYTES(sp)
    FLOAD   f12, 12 * FREGBYTES(sp)
    FLOAD   f13, 13 * FREGBYTES(sp)
    FLOAD   f14, 14 * FREGBYTES(sp)
    FLOAD   f15, 15 * FREGBYTES(sp)
    FLOAD   f16, 16 * FREGBYTES(sp)
    FLOAD   f17, 17 * FREGBYTES(sp)
    FLOAD   f18, 18 * FREGBYTES(sp)
    FLOAD   f19, 19 * FREGBYTES(sp)
    FLOAD   f20, 20 * FREGBYTES(sp)
    FLOAD   f21, 21 * FREGBYTES(sp)
    FLOAD   f22, 22 * FREGBYTES(sp)
    FLOAD   f23, 23 * FREGBYTES(sp)
    FLOAD   f24, 24 * FREGBYTES(sp)
    FLOAD   f25, 25 * FREGBYTES(sp)
    FLOAD   f26, 26 * FREGBYTES(sp)
    FLOAD   f27, 27 * FREGBYTES(sp)
    FLOAD   f28, 28 * FREGBYTES(sp)
    FLOAD   f29, 29 * FREGBYTES(sp)
    FLOAD   f30, 30 * FREGBYTES(sp)
    FLOAD   f31, 31 * FREGBYTES(sp)

    addi    sp, sp, 32 * FREGBYTES
#endif

	mret
