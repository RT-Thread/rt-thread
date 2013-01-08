/*
 * File      : hdisr_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        The first version
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
#define HDINTERRUPTFNC(name,num) \
	ENTRY(name)\
	pushl $(num);\
	jmp _hdinterrupts;\
	.data;\
	.long name;\
	.text

.globl hdinterrupt_func
	.data
	.align 4
	.type hdinterrupt_func,@object
	hdinterrupt_func :
.text

/* the external device interrupts */
HDINTERRUPTFNC(irq0, 0)
HDINTERRUPTFNC(irq1, 1)
HDINTERRUPTFNC(irq2, 2)
HDINTERRUPTFNC(irq3, 3)
HDINTERRUPTFNC(irq4, 4)
HDINTERRUPTFNC(irq5, 5)
HDINTERRUPTFNC(irq6, 6)
HDINTERRUPTFNC(irq7, 7)
HDINTERRUPTFNC(irq8, 8)
HDINTERRUPTFNC(irq9, 9)
HDINTERRUPTFNC(irq10, 10)
HDINTERRUPTFNC(irq11, 11)
HDINTERRUPTFNC(irq12, 12)
HDINTERRUPTFNC(irq13, 13)
HDINTERRUPTFNC(irq14, 14)
HDINTERRUPTFNC(irq15, 15)

.p2align 4,0x90
.globl _hdinterrupts
.type _hdinterrupts,@function
.globl rt_interrupt_enter
.globl rt_interrupt_leave
.globl isr_table
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread

_hdinterrupts:
	push %ds
	push %es
	pushal
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	pushl %esp

	call rt_interrupt_enter

	movl %esp, %eax	      /* copy esp to eax */
	addl $0x2c, %eax      /* move to vector address */
	movl (%eax), %eax     /* vector(eax) = *eax */

	pushl %eax            /* push argument : int vector */
	shll $0x2, %eax       /* each item takes up 4bytes in isr_table. */
	movl $isr_table, %ebx /* ebx = &isr_table[0] */
	addl %eax, %ebx       /* eax = &isr_table[vector] */
	call *(%ebx)
	add $4, %esp          /* restore argument */

	call rt_interrupt_leave

	/* if rt_thread_switch_interrupt_flag set, jump to _interrupt_thread_switch and don't return */
	movl $rt_thread_switch_interrupt_flag, %eax
	movl (%eax), %ebx
	cmp $0x1, %ebx
	jz _interrupt_thread_switch

	popl %esp
	popal
	pop %es
	pop %ds
	add $4,%esp
	iret

_interrupt_thread_switch:
	popl %esp

	movl $0x0, %ebx
	movl %ebx, (%eax)

	movl $rt_interrupt_from_thread, %eax
	movl (%eax), %ebx
	movl %esp, (%ebx)

	movl $rt_interrupt_to_thread, %ecx
	movl (%ecx), %edx
	movl (%edx), %esp

	popal
	pop %es
	pop %ds
	add $4,%esp
	iret

/*@}*/
