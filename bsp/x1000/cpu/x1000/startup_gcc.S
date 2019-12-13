/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-07     Urey         first version
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "../common/mips.h"

#define IRQ_STACK_SIZE		0x2000
#define EXC_STACK_SIZE		0x2000


	.section ".bss"
    ALIGN(4)
irq_stack_low:
	.space IRQ_STACK_SIZE
irq_stack_top:
	.space 8

	    ALIGN(4)
exc_stack_low:
	.space EXC_STACK_SIZE
exc_stack_top:
	.space 8

#define SYSTEM_STACK		0x80003fe8

;/*********************************************************************************************************
;  入口
;*********************************************************************************************************/
	.global	rtthread_startup
	.global 	mips_vfp32_init

	.global	_start
    .section ".start", "ax"
    .set noreorder
_start:
    .set    noreorder
    la      ra, _start

    li      t1, 0x00800000
    mtc0    t1, CP0_CAUSE

    /* init cp0 registers. */
    li      t0, 0x1000FC00 /* BEV = 0 and mask all interrupt */
    mtc0    t0, CP0_STATUS

#ifdef __mips_hard_float
	jal 	mips_vfp32_init
	nop
#endif

    /* setup stack pointer */
    li      sp, SYSTEM_STACK
    la      gp, _gp

_cache_init:
    /* init caches, assumes a 4way * 128set * 32byte I/D cache */
    mtc0    zero, CP0_TAGLO  /* TAGLO reg */
    mtc0    zero, CP0_TAGHI  /* TAGHI reg */
    li      t0, 3            /* enable cache for kseg0 accesses */
    mtc0    t0, CP0_CONFIG   /* CONFIG reg */
    la      t0, 0x80000000   /* an idx op should use an unmappable address */
    ori     t1, t0, 0x4000   /* 16kB cache */

_cache_loop:
    cache   0x8, 0(t0)       /* index store icache tag */
    cache   0x9, 0(t0)       /* index store dcache tag */
    bne     t0, t1, _cache_loop
    addiu   t0, t0, 0x20     /* 32 bytes per cache line */
    nop

    /* invalidate BTB */
    mfc0    t0, CP0_CONFIG
    nop
    ori     t0, 2
    mtc0    t0, CP0_CONFIG
    nop


    /* jump to RT-Thread RTOS */
    jal     rtthread_startup
    nop

    /* restart, never die */
    j       _start
    nop
    .set    reorder


;/*********************************************************************************************************
;  异常向量表
;*********************************************************************************************************/
    /* 0x0 - TLB refill handler */
    .section .vectors.1, "ax", %progbits
    j       mips_tlb_refill_entry
    nop

    /* 0x100 - Cache error handler */
    .section .vectors.2, "ax", %progbits
    j       mips_cache_error_entry
    nop

    /* 0x180 - Exception/Interrupt handler */
    .section .vectors.3, "ax", %progbits
    j       mips_exception_entry
    nop

    /* 0x200 - Special Exception Interrupt handler (when IV is set in CP0_CAUSE) */
    .section .vectors.4, "ax", %progbits
    j       mips_interrupt_entry
    nop
    .section .vectors, "ax", %progbits

	.global	mips_exception_handler
//	.global	mips_syscall
LEAF(mips_exception_entry)
    .set    push
    .set    noat
    .set    noreorder
    .set    volatile

	mfc0	k0, C0_CAUSE
	andi	k0, k0, 0x7c
	beq		zero, k0, except_do_intr
	nop

	andi	k0,(0x08 << 2)
	beq		zero,k0,except_do
	nop
except_do_intr:
	la		k0,mips_interrupt_entry
	jr		k0
	nop
except_do_syscall:
//	la		k0,mips_syscall
//	jr		k0
	nop
except_do:
	//save sp
	move	k0,sp
	//la		sp,	exc_stack_top
	subu 	sp, sp, CONTEXT_SIZE
	//save context
	sw	$0, (4*0)(sp);
	sw	$1, (4*1)(sp);
	sw	$2, (4*2)(sp);
	sw	$3, (4*3)(sp);
	sw	$4, (4*4)(sp);
	sw	$5, (4*5)(sp);
	sw	$6, (4*6)(sp);
	sw	$7, (4*7)(sp);
	sw	$8, (4*8)(sp);
	sw	$9, (4*9)(sp);
	sw	$10, (4*10)(sp);
	sw	$11, (4*11)(sp);
	sw	$12, (4*12)(sp);
	sw	$13, (4*13)(sp);
	sw	$14, (4*14)(sp);
	sw	$15, (4*15)(sp);
	sw	$16, (4*16)(sp);
	sw	$17, (4*17)(sp);
	sw	$18, (4*18)(sp);
	sw	$19, (4*19)(sp);
	sw	$20, (4*20)(sp);
	sw	$21, (4*21)(sp);
	sw	$22, (4*22)(sp);
	sw	$23, (4*23)(sp);
	sw	$24, (4*24)(sp);
	sw	$25, (4*25)(sp);
	sw	$26, (4*26)(sp);
	sw	$27, (4*27)(sp);
	sw	$28, (4*28)(sp);
	sw	k0,  (4*29)(sp);	//old sp
	sw	$30, (4*30)(sp);
	sw	$31, (4*31)(sp);

	/* STATUS CAUSE EPC.... */
	mfc0	$2, CP0_STATUS
	sw		$2, STK_OFFSET_SR(sp)

	mfc0	$2, CP0_CAUSE
	sw		$2, STK_OFFSET_CAUSE(sp)

	mfc0	$2, CP0_BADVADDR
	sw		$2, STK_OFFSET_BADVADDR(sp)

	MFC0	$2, CP0_EPC
	sw		$2, STK_OFFSET_EPC(sp)

	mfhi	$2
	sw		$2, STK_OFFSET_HI(sp)

	mflo	$2
	sw		$2, STK_OFFSET_LO(sp)

	move	a0, sp
	la		k0,	mips_exception_handler
	j		k0
	nop

	//

	.set	pop
END(mips_exception_entry)

	.global	mips_tlb_refill_handler
LEAF(mips_tlb_refill_entry)
    .set    push
    .set    noat
    .set    noreorder
    .set    volatile

	la		k0,mips_tlb_refill_handler
	jr		k0

	nop
    eret
	nop

	.set	pop
END(mips_tlb_refill_entry)

	.global	mips_cache_error_handler
LEAF(mips_cache_error_entry)
    .set    push
    .set    noat
    .set    noreorder
    .set    volatile

	la		k0,mips_cache_error_handler
	jr		k0
    nop
    eret
	nop

	.set	pop
END(mips_cache_error_entry)



.global	rt_interrupt_dispatch
.global	rt_interrupt_enter
.global	rt_interrupt_leave
LEAF(mips_interrupt_entry)
    .set    push
    .set    noat
    .set    noreorder
    .set    volatile

    //mfc0	k0,CP0_EPC
    SAVE_CONTEXT

    mfc0    t0, CP0_CAUSE
    mfc0    t1, CP0_STATUS
    and     t0, t1

    andi    t0, 0xff00
    beqz    t0, spurious_interrupt
    nop

	/* let k0 keep the current context sp */
	move 	k0, sp

	/* switch to kernel stack */
	la 		sp, irq_stack_top
	jal 	rt_interrupt_enter
	nop
    jal     rt_interrupt_dispatch
    nop
    jal     rt_interrupt_leave
    nop

    /* switch sp back to thread's context */
    move    sp, k0

    /*
     * if rt_thread_switch_interrupt_flag set, jump to
     * rt_hw_context_switch_interrupt_do and don't return
     */
    la      k0, rt_thread_switch_interrupt_flag
    lw      k1, 0(k0)
    beqz    k1, spurious_interrupt
    nop
    sw      zero, 0(k0)                     /* clear flag */
    nop

    /*
     * switch to the new thread
     */
    la      k0, rt_interrupt_from_thread
    lw      k1, 0(k0)
    nop
    sw      sp, 0(k1)                       /* store sp in preempted tasks's TCB */

    la      k0, rt_interrupt_to_thread
    lw      k1, 0(k0)
    nop
    lw      sp, 0(k1)                       /* get new task's stack pointer */
    j       spurious_interrupt
    nop
spurious_interrupt:
    RESTORE_CONTEXT

	.set	pop
END(mips_interrupt_entry)
