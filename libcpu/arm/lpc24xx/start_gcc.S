/*
 * File      : start.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     XuXinming    first version
 */

/**
 * @addtogroup LPC2478
 */
/*@{*/

#define WDMOD          (0xE0000000 + 0x00)
#define VICIntEnClr    (0xFFFFF000 + 0x014)
#define VICVectAddr    (0xFFFFF000 + 0xF00)
#define VICIntSelect   (0xFFFFF000 + 0x00C)
#define PLLCFG         (0xE01FC000 + 0x084)
#define PLLCON         (0xE01FC000 + 0x080)
#define PLLFEED        (0xE01FC000 + 0x08C)
#define PLLSTAT        (0xE01FC000 + 0x088)
#define CCLKCFG        (0xE01FC000 + 0x104)
#define MEMMAP         (0xE01FC000 + 0x040)	
#define SCS            (0xE01FC000 + 0x1A0)	
#define CLKSRCSEL      (0xE01FC000 + 0x10C)
#define MAMCR          (0xE01FC000 + 0x000)
#define MAMTIM         (0xE01FC000 + 0x004)


/*.section .init, "ax"*/
.section .vectors
.code 32
.globl _start
_start:
	b reset
	ldr	pc, _vector_undef
	ldr	pc, _vector_swi
	ldr	pc, _vector_pabt
	ldr	pc, _vector_dabt
	ldr	pc, _vector_resv
	ldr	pc, _vector_irq
	ldr	pc, _vector_fiq

_vector_undef:	.word vector_undef
_vector_swi:	.word vector_swi
_vector_pabt:	.word vector_pabt
_vector_dabt:	.word vector_dabt
_vector_resv:	.word vector_resv
_vector_irq:	.word vector_irq
_vector_fiq:	.word vector_fiq

.text
.code 32

/* the system entry */
reset:
	/* enter svc mode */
	msr cpsr_c, #SVCMODE|NOINT
	
	/*watch dog disable */
	ldr r0,=WDMOD
	ldr r1,=0x0 		
	str r1,[r0]
	
	/* all interrupt disable */
	ldr r0,=VICIntEnClr
	ldr r1,=0xffffffff
	str r1,[r0]
	
	ldr	r1, =VICVectAddr
	ldr	r0, =0x00
	str	r0, [r1]
	
	ldr	r1, =VICIntSelect
	ldr	r0, =0x00
	str	r0, [r1]	
	
	/* setup stack */
	bl stack_setup		

_rtthread_startup: .word rtthread_startup

	.equ USERMODE, 	0x10
	.equ FIQMODE, 	0x11
	.equ IRQMODE, 	0x12
	.equ SVCMODE, 	0x13
	.equ ABORTMODE, 0x17
	.equ UNDEFMODE, 0x1b
	.equ MODEMASK, 	0x1f
	.equ NOINT,		0xc0

/* exception handlers */
vector_undef:	bl rt_hw_trap_udef
vector_swi:		bl rt_hw_trap_swi
vector_pabt: 	bl rt_hw_trap_pabt
vector_dabt:	bl rt_hw_trap_dabt
vector_resv: 	bl rt_hw_trap_resv

.globl rt_interrupt_enter
.globl rt_interrupt_leave
.globl rt_thread_switch_interrput_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
vector_irq:	
	stmfd	sp!, {r0-r12,lr}
	bl	rt_interrupt_enter
	bl	rt_hw_trap_irq
	bl	rt_interrupt_leave

	/* if rt_thread_switch_interrput_flag set, jump to _interrupt_thread_switch and don't return */
	ldr	r0, =rt_thread_switch_interrput_flag
	ldr	r1, [r0]
	cmp	r1, #1
	beq	_interrupt_thread_switch

	ldmfd	sp!, {r0-r12,lr}
	subs	pc, lr, #4

	.align	5
vector_fiq:
	stmfd sp!,{r0-r7,lr}
	bl rt_hw_trap_fiq
	ldmfd sp!,{r0-r7,lr}
	subs pc,lr,#4

_interrupt_thread_switch:
	mov	r1, #0				@ clear rt_thread_switch_interrput_flag
	str	r1, [r0]

	ldmfd sp!, {r0-r12,lr}	@ reload saved registers
	stmfd sp!, {r0-r3}		@ save r0-r3
	mov	r1, sp
	add	sp, sp, #16			@ restore sp
	sub	r2, lr, #4			@ save old task's pc to r2

	mrs	r3, spsr			@ disable interrupt
	orr	r0, r3, #NOINT
	msr	spsr_c, r0

	ldr	r0,  =.+8			@ switch to interrupted task's stack
	movs pc, r0

	stmfd sp!, {r2}			@ push old task's pc
	stmfd sp!, {r4-r12,lr}	@ push old task's lr,r12-r4
	mov	r4, r1				@ Special optimised code below
	mov	r5, r3
	ldmfd r4!, {r0-r3}
	stmfd sp!, {r0-r3}		@ push old task's r3-r0
	stmfd sp!, {r5}			@ push old task's psr
	mrs	r4, spsr
	stmfd sp!, {r4}			@ push old task's spsr

	ldr	r4, =rt_interrupt_from_thread
	ldr	r5, [r4]
	str	sp, [r5]			@ store sp in preempted tasks's TCB

	ldr	r6, =rt_interrupt_to_thread
	ldr	r6, [r6]
	ldr	sp, [r6]			@ get new task's stack pointer

	ldmfd sp!, {r4}			@ pop new task's spsr
	msr	SPSR_cxsf, r4
	ldmfd sp!, {r4}			@ pop new task's psr
	msr CPSR_cxsf, r4

	ldmfd sp!, {r0-r12,lr,pc}	@ pop new task's r0-r12,lr & pc

/* each mode stack memory */
stack_setup:
	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK
	orr	r1, r0, #UNDEFMODE|NOINT
	msr	cpsr_cxsf, r1		@ undef mode
	ldr	sp, =__UndStack_end

	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK
	orr	r1,r0,#ABORTMODE|NOINT
	msr	cpsr_cxsf,r1		@ abort mode
	ldr	sp,=__ABTStack_end

	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK
	orr	r1,r0,#IRQMODE|NOINT
	msr	cpsr_cxsf,r1		@ IRQ mode
	ldr	sp,=__IRQStack_end

	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK
	orr	r1,r0,#FIQMODE|NOINT
	msr	cpsr_cxsf,r1		@ FIQ mode
	ldr	sp,=__FIQStack_end

	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK
	orr	r1,r0,#SVCMODE|NOINT
	msr	cpsr_cxsf,r1		@ SVC mode
	ldr	sp,=__SVCStack_end

	/* USER mode is not initialized. */
	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK|0x80		//IRQ enable and FIQ disable
	orr	r1,r0,#USERMODE
	msr	cpsr_cxsf,r1		@ usr mode	
	ldr	sp,=__USRStack_end		
		
	ldr	pc, _rtthread_startup

