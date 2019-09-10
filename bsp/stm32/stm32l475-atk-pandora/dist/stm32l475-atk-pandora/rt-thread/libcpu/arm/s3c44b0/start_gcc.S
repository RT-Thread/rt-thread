/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-06     XuXinming    first version
 * 2006-09-20     Bernard      clean the code
 */

/**
 * @addtogroup S3C44B0
 */
/*@{*/

.section .init, "ax"
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

/*
 * rtthread kernel start and end
 * which are defined in linker script
 */
.globl _rtthread_start
_rtthread_start:.word _start
.globl _rtthread_end
_rtthread_end:	.word  _end

/*
 * rtthread bss start and end
 * which are defined in linker script
 */
.globl _bss_start
_bss_start:	.word __bss_start
.globl _bss_end
_bss_end:	.word __bss_end

#if defined(__FLASH_BUILD__)
/*
 * TEXT_BASE, 
 * which is defined in macro of make
 */
_TEXT_BASE: .word	TEXT_BASE
#endif

	.equ WTCON,		0x1d30000
	.equ INTCON,	0x1e00000
	.equ INTMSK, 	0x1e0000c

/* the system entry */
reset:
	/* enter svc mode */
	msr cpsr_c, #SVCMODE|NOINT

	/*watch dog disable */
	ldr r0,=WTCON
    ldr r1,=0x0 		
    str r1,[r0]
	
	/* all interrupt disable */
	ldr r0,=INTMSK
	ldr r1,=0x07ffffff
	str r1,[r0]
	
	ldr	r1, =INTCON
	ldr	r0, =0x05
	str	r0, [r1]

#if defined(__FLASH_BUILD__)
	/* init lowlevel */
	bl lowlevel_init
#endif

	/* setup stack */
	bl stack_setup
	
#if defined(__FLASH_BUILD__)
	mov r0, #0x0			/* r0 <- flash base address         */
	ldr r1, _TEXT_BASE		/* r1 <- the taget address          */
	
	ldr	r2, _rtthread_start
	ldr	r3, _bss_start
	sub	r2, r3, r2			/* r2 <- size of rtthread kernel    */
	add	r2, r0, r2			/* r2 <- source end address         */
	
copy_loop:
	ldmia	r0!, {r3-r10}	/* copy from source address [r0]    */
	stmia	r1!, {r3-r10}	/* copy to   target address [r1]    */
	cmp	r0, r2				/* until source end addreee [r2]    */
	ble	copy_loop
#endif
	
	/* start RT-Thread Kernel */
	ldr	pc, _rtthread_startup

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
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
vector_irq:	
	stmfd	sp!, {r0-r12,lr}
	bl  led_off
	bl	rt_interrupt_enter
	bl	rt_hw_trap_irq
	bl	rt_interrupt_leave

	/* if rt_thread_switch_interrupt_flag set, jump to _interrupt_thread_switch and don't return */
	ldr	r0, =rt_thread_switch_interrupt_flag
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
	mov	r1, #0				@ clear rt_thread_switch_interrupt_flag
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
UNDSTACK_START:	.word _undefined_stack_start + 128
ABTSTACK_START:	.word _abort_stack_start + 128
FIQSTACK_START:	.word _fiq_stack_start + 1024
IRQSTACK_START:	.word _irq_stack_start + 1024
SVCSTACK_START: .word _svc_stack_start + 4096

stack_setup:
	/* undefined instruction mode */
	msr cpsr_c, #UNDEFMODE|NOINT
	ldr sp, UNDSTACK_START

	/* abort mode */
	msr cpsr_c, #ABORTMODE|NOINT
	ldr sp, ABTSTACK_START

	/* FIQ mode */
	msr cpsr_c, #FIQMODE|NOINT
	ldr sp, FIQSTACK_START

	/* IRQ mode */
	msr cpsr_c, #IRQMODE|NOINT
	ldr sp, IRQSTACK_START

	/* supervisor mode */
	msr cpsr_c, #SVCMODE|NOINT
	ldr sp, SVCSTACK_START

	mov	pc,lr				@ The LR register may be not valid for the mode changes.

.globl led_on
led_on:
	ldr	r1,	=0x1d20014		@ r1<-PDATC
	ldr	r0,	[r1]			@ r0<-[r1]
	orr	r0,	r0, #0x0e		@ r0=r0 or 0x0e
	str	r0,	[r1]			@ r0->[r1]
	mov	pc, lr

.globl led_off
led_off:
	ldr	r1,	=0x1d20010		@ r1<-PCONC
	ldr	r0,	=0x5f555555		@ r0<-0x5f555555
	str	r0,	[r1]			@ r0->[r1]

	ldr	r1,	=0x1d20014		@ r1<-PDATC
	ldr	r0,	=0x0			@ r0<-00
	str	r0,	[r1]			@ r0->[r1]

	mov	pc, lr
