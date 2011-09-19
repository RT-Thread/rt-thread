/*
 * File      : start.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http:/*openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#define CONFIG_STACKSIZE 	512
#define S_FRAME_SIZE 		72

#define S_OLD_R0 			68
#define S_PSR  				64
#define S_PC  				60
#define S_LR  				56
#define S_SP  				52

#define S_IP  					48
#define S_FP  				44
#define S_R10  				40
#define S_R9  				36
#define S_R8  				32
#define S_R7  				28
#define S_R6  				24
#define S_R5  				20
#define S_R4  				16
#define S_R3  				12
#define S_R2  				8
#define S_R1  				4
#define S_R0 				0

.equ 	USERMODE, 			0x10
.equ 	FIQMODE,			0x11
.equ 	IRQMODE,			0x12
.equ 	SVCMODE,			0x13
.equ 	ABORTMODE,			0x17
.equ 	UNDEFMODE,			0x1b
.equ 	MODEMASK,			0x1f
.equ 	NOINT,				0xc0

.equ 	RAM_BASE,			0x00000000	/*Start address of RAM		*/
.equ 	ROM_BASE,			0x20000000	/*Start address of Flash	*/


#define		AT91_RSTC_PROCRST	(1 << 0)		/* Processor Reset */
#define		AT91_RSTC_PERRST	(1 << 2)
#define		AT91_RSTC_KEY		(0xa5 << 24)
#define AT91_MATRIX_BASE	0xffffee00
#define AT91_MATRIX_MRCR	(AT91_MATRIX_BASE + 0x100)	/* Master Remap Control Register */
#define		AT91_MATRIX_RCB0		(1 << 0)	/* Remap Command for AHB Master 0 (ARM926EJ-S Instruction Master) */
#define		AT91_MATRIX_RCB1		(1 << 1)	/* Remap Command for AHB Master 1 (ARM926EJ-S Data Master) */
#define		AT91_AIC_BASE	0xfffff000
#define		AT91_AIC_IDCR	0x124	/* Interrupt Disable Command Register */
#define		AT91_AIC_ICCR	0x128	/* Interrupt Clear Command Register */


/*
 *************************************************************************
 *
 * Jump vector table
 *
 *************************************************************************
 */

.section .init, "ax"
.code 32

.globl _start
_start:
	b		reset
	ldr		pc, _vector_undef
	ldr		pc, _vector_swi
	ldr		pc, _vector_pabt
	ldr		pc, _vector_dabt
	ldr		pc, _vector_resv
	ldr		pc, _vector_irq
	ldr		pc, _vector_fiq

_vector_undef:	.word vector_undef
_vector_swi:	.word vector_swi
_vector_pabt:	.word vector_pabt
_vector_dabt:	.word vector_dabt
_vector_resv:	.word vector_resv
_vector_irq:	.word vector_irq
_vector_fiq:	.word vector_fiq

.balignl 	16,0xdeadbeef

/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 * relocate armboot to ram
 * setup stack
 * jump to second stage
 *
 *************************************************************************
 */

_TEXT_BASE:
	.word	TEXT_BASE

/*
 * rtthread kernel start and end
 * which are defined in linker script
 */
.globl _rtthread_start
_rtthread_start:
	.word _start
	
.globl _rtthread_end
_rtthread_end:
	.word  _end

/*
 * rtthread bss start and end which are defined in linker script
 */
.globl _bss_start
_bss_start:	
	.word __bss_start
	
.globl _bss_end
_bss_end:
	.word __bss_end

/* IRQ stack memory (calculated at run-time) 						*/
.globl IRQ_STACK_START
IRQ_STACK_START:
	.word _irq_stack_start + 1024
	
.globl FIQ_STACK_START
FIQ_STACK_START:
	.word _fiq_stack_start + 1024
	
.globl UNDEFINED_STACK_START
UNDEFINED_STACK_START:
	.word _undefined_stack_start + CONFIG_STACKSIZE
	
.globl ABORT_STACK_START
ABORT_STACK_START:
	.word _abort_stack_start + CONFIG_STACKSIZE
	
.globl _STACK_START
_STACK_START:
	.word _svc_stack_start + 4096

/* ----------------------------------entry------------------------------*/
reset:
	
	/* set the cpu to SVC32 mode 	*/
	mrs		r0,cpsr
	bic		r0,r0,#MODEMASK
	orr		r0,r0,#SVCMODE
	msr		cpsr,r0

	/* mask all IRQs by clearing all bits in the INTMRs 				*/
	ldr	r1, =AT91_AIC_BASE
	ldr	r0, =0xffffffff
	str	r0, [r1, #AT91_AIC_IDCR]
	str	r0, [r1, #AT91_AIC_ICCR]
	

	/*remap internal ram to 0x00000000 address*/
	ldr	r0, =AT91_MATRIX_MRCR
	ldr	r1, =(AT91_MATRIX_RCB0|AT91_MATRIX_RCB1)
	str	r1, [r0]

	/* set interrupt vector 		*/
#if 1
	ldr 	r0, _TEXT_BASE//_load_address
	//ldr		r1, =0x200000				/* target address    				*/
	mov	r1, #0x00
	add	r2, r0, #0x40			/* size, 32bytes         			*/

copy_loop:
	ldmia	r0!, {r3-r10}			/* copy from source address [r0]    */
	stmia	r1!, {r3-r10}			/* copy to   target address [r1]    */
	cmp		r0, r2					/* until source end addreee [r2]    */
	ble		copy_loop
#endif
	
	/* setup stack */
	bl		stack_setup

	/* clear .bss */
	mov   	r0,#0                   /* get a zero 						*/
	ldr   	r1,=__bss_start         /* bss start 						*/
	ldr   	r2,=__bss_end           /* bss end 							*/
	
bss_loop:
	cmp   	r1,r2                   /* check if data to clear 			*/
	strlo 	r0,[r1],#4              /* clear 4 bytes 					*/
	blo   	bss_loop                /* loop until done 					*/

	/* call C++ constructors of global objects 							*/
	ldr 	r0, =__ctors_start__
	ldr 	r1, =__ctors_end__
	
ctor_loop:
	cmp 	r0, r1
	beq 	ctor_end
	ldr 	r2, [r0], #4
	stmfd 	sp!, {r0-r1}
	mov 	lr, pc
	bx 		r2
	ldmfd 	sp!, {r0-r1}
	b		ctor_loop
	
ctor_end:

	/* start RT-Thread Kernel 		*/
	ldr		pc, _rtthread_startup

_rtthread_startup: 
	.word rtthread_startup
#if defined (__FLASH_BUILD__)
_load_address: 
	.word ROM_BASE + _TEXT_BASE
#else
_load_address: 
	.word RAM_BASE + _TEXT_BASE
#endif

.global cpu_reset
cpu_reset:
	ldr	r0, =0xfffffd00
	ldr	r1, =(AT91_RSTC_KEY | AT91_RSTC_PROCRST | AT91_RSTC_PERRST)
	str	r1, [r0]
	mov	pc, lr

/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */

/* exception handlers 				*/
	.align  5
vector_undef:
	sub 	sp, sp, #S_FRAME_SIZE
	stmia 	sp, {r0 - r12}   		/* Calling r0-r12					*/
	add		r8, sp, #S_PC
	stmdb   r8, {sp, lr}^           /* Calling SP, LR					*/
	str		lr, [r8, #0]            /* Save calling PC					*/
	mrs		r6, spsr
	str		r6, [r8, #4]            /* Save CPSR						*/
	str		r0, [r8, #8]            /* Save OLD_R0						*/
	mov		r0, sp

	bl		rt_hw_trap_udef

	.align	5
vector_swi:
	bl 		rt_hw_trap_swi

	.align	5
vector_pabt:
	bl 		rt_hw_trap_pabt

	.align	5
vector_dabt:
	sub 	sp, sp, #S_FRAME_SIZE
	stmia 	sp, {r0 - r12}   		/* Calling r0-r12					*/
	add		r8, sp, #S_PC
	stmdb   r8, {sp, lr}^           /* Calling SP, LR					*/
	str		lr, [r8, #0]            /* Save calling PC					*/
	mrs		r6, spsr
	str		r6, [r8, #4]            /* Save CPSR						*/
	str		r0, [r8, #8]            /* Save OLD_R0						*/
	mov		r0, sp

	bl 		rt_hw_trap_dabt

	.align	5
vector_resv:
	bl 		rt_hw_trap_resv

.globl 		rt_interrupt_enter
.globl 		rt_interrupt_leave
.globl 		rt_thread_switch_interrupt_flag
.globl 		rt_interrupt_from_thread
.globl 		rt_interrupt_to_thread
vector_irq:
	stmfd	sp!, {r0-r12,lr}
	bl		rt_interrupt_enter
	bl		rt_hw_trap_irq
	bl		rt_interrupt_leave

	/* if rt_thread_switch_interrupt_flag set, jump to _interrupt_thread_switch and don't return */
	ldr		r0, =rt_thread_switch_interrupt_flag
	ldr		r1, [r0]
	cmp		r1, #1
	beq		_interrupt_thread_switch

	ldmfd	sp!, {r0-r12,lr}
	subs	pc, lr, #4

	.align	5
vector_fiq:
	stmfd	sp!,{r0-r7,lr}
	bl 		rt_hw_trap_fiq
	ldmfd	sp!,{r0-r7,lr}
	subs	pc,lr,#4

_interrupt_thread_switch:
	mov		r1,  #0					/* clear rt_thread_switch_interrupt_flag*/
	str		r1,  [r0]

	ldmfd	sp!, {r0-r12,lr}		/* reload saved registers			*/
	stmfd	sp!, {r0-r3}			/* save r0-r3						*/
	mov		r1,  sp
	add		sp,  sp, #16			/* restore sp						*/
	sub		r2,  lr, #4				/* save old task's pc to r2			*/
	
	mrs		r3,  spsr				/* disable interrupt				*/
	orr		r0,  r3, #NOINT
	msr		spsr_c, r0

	ldr		r0,  =.+8				/* switch to interrupted task's stack*/
	movs	pc,  r0

	stmfd	sp!, {r2}				/* push old task's pc				*/
	stmfd	sp!, {r4-r12,lr}		/* push old task's lr,r12-r4		*/
	mov		r4,  r1					/* Special optimised code below		*/
	mov		r5,  r3
	ldmfd	r4!, {r0-r3}
	stmfd	sp!, {r0-r3}			/* push old task's r3-r0			*/
	stmfd	sp!, {r5}				/* push old task's psr				*/
	mrs		r4,  spsr
	stmfd	sp!, {r4}				/* push old task's spsr				*/

	ldr		r4,  =rt_interrupt_from_thread
	ldr		r5,  [r4]
	str		sp,  [r5]				/* store sp in preempted tasks's TCB*/

	ldr	r6,  =rt_interrupt_to_thread
	ldr	r6,  [r6]
	ldr	sp,  [r6]					/* get new task's stack pointer		*/

	ldmfd	sp!, {r4}				/* pop new task's spsr				*/
	msr		SPSR_cxsf, r4
	ldmfd	sp!, {r4}				/* pop new task's psr				*/
	msr		CPSR_cxsf, r4

	ldmfd	sp!, {r0-r12,lr,pc}		/* pop new task's r0-r12,lr & pc	*/

stack_setup:
	mrs		r0, cpsr
	bic		r0, r0, #MODEMASK
	orr		r1, r0, #UNDEFMODE|NOINT
	msr		cpsr_cxsf, r1			/* undef mode						*/
	ldr		sp, UNDEFINED_STACK_START

	orr		r1,r0,#ABORTMODE|NOINT
	msr		cpsr_cxsf,r1			/* abort mode						*/
	ldr		sp, ABORT_STACK_START

	orr		r1,r0,#IRQMODE|NOINT
	msr		cpsr_cxsf,r1			/* IRQ mode							*/
	ldr		sp, IRQ_STACK_START

	orr		r1,r0,#FIQMODE|NOINT
	msr		cpsr_cxsf,r1			/* FIQ mode							*/
	ldr		sp, FIQ_STACK_START

	bic		r0,r0,#MODEMASK
	orr		r1,r0,#SVCMODE|NOINT
	msr		cpsr_cxsf,r1			/* SVC mode							*/

	ldr		sp, _STACK_START

	/* USER mode is not initialized. */
	mov		pc,lr					/* The LR register may be not valid for the mode changes.*/

/*/*}*/


