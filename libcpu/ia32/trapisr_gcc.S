/*
 * File      : trapisr_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        The first version.
 */

/**
 * @addtogroup I386
 */
/*@{*/

#define ENTRY(proc)\
	.align 2;\
	.globl proc;\
	.type proc,@function;\
	proc:
#define TRAPFNC(name,num)\
	ENTRY(name)\
	pushl $(num);\
	jmp _traps;\
	.data;\
	.long name;\
	.text
#define TRAPFNC_NOEC(name,num)\
	ENTRY(name)\
	pushl $0;\
	pushl $(num);\
	jmp _traps;\
	.data;\
	.long name;\
	.text

.globl trap_func
	.data
	.align 4
	.type trap_func,@object
	trap_func :
.text

/* CPU traps */
TRAPFNC_NOEC(Xdivide, 0)
TRAPFNC_NOEC(Xdebug,  1)
TRAPFNC_NOEC(Xnmi,    2)
TRAPFNC_NOEC(Xbrkpt,  3)
TRAPFNC_NOEC(Xoflow,  4)
TRAPFNC_NOEC(Xbound,  5)
TRAPFNC_NOEC(Xillop,  6)
TRAPFNC_NOEC(Xdevice, 7)
TRAPFNC     	(Xdblflt, 8)
TRAPFNC    	(Xtss,    9)
TRAPFNC     	(Xsegnp,  10)
TRAPFNC     	(Xstack,  11)
TRAPFNC     	(Xgpflt,  12)
TRAPFNC     	(Xpgflt,  13)
TRAPFNC_NOEC(Xfperr,  14)
TRAPFNC     	(Xalign,  15)

/* default handler -- not for any specific trap */
TRAPFNC     (Xdefault, 500)

.p2align 4,0x90
.globl	_traps
.type	_traps,@function
.globl rt_interrupt_enter
.globl rt_interrupt_leave

_traps:
	push %ds
	push %es
	pushal
	movw $0x10,%ax
	movw %ax,%ds
	movw %ax,%es
	pushl %esp
	call rt_interrupt_enter
	movl %esp, %eax		
	addl $0x2c,%eax		/*get trapno*/
	movl (%eax),%eax
	pushl %eax			/*push trapno*/
	call rt_hw_trap_irq
	addl $4,%esp
	call rt_interrupt_leave
	popl %esp
	popal
	pop %es
	pop %ds
	add $8,%esp
	iret

/*@}*/
