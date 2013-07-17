/*
 * File      : start.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-13     Peng Fan     First implementation
 */


#define CONFIG_STACKSIZE 	1024
#define S_FRAME_SIZE 		132

#define S_OLD_R0 			132
#define S_PSR  				128
#define S_PC  				124
#define S_LR  				120
#define S_SP  				116

#define S_IP  				112
#define S_FP  				108
#define S_R26  				104
#define S_R25  				100
#define S_R24  				96
#define S_R23  				92
#define S_R22  				88
#define S_R21  				84
#define S_R20 				80
#define S_R19  				76
#define S_R18  				72
#define S_R17  				68
#define S_R16  				64
#define S_R15  				60
#define S_R14  				56
#define S_R13  				52
#define S_R12  				48
#define S_R11  				44
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

.equ 	USERMODE,			0x10
.equ 	REALMODE,			0x11
.equ 	IRQMODE,			0x12
.equ 	PRIVMODE,			0x13
.equ 	TRAPMODE,			0x17
.equ 	EXTNMODE,			0x1b
.equ 	MODEMASK,			0x1f
.equ 	NOINT,				0xc0

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
     b   reset
     ldw pc, _extend_handle
     ldw pc, _swi_handle
     ldw pc, _iabort_handle
     ldw pc, _dabort_handle
     ldw pc, _reserve_handle
     ldw pc, _IRQ_handle
     ldw pc, _FIQ_handle

_extend_handle:     .word extend_handle
_swi_handle:        .word swi_handle
_iabort_handle:     .word iabort_handle
_dabort_handle:     .word dabort_handle
_reserve_handle:    .word reserve_handle
_IRQ_handle:        .word IRQ_handle
_FIQ_handle:        .word FIQ_handle
    .balignl 16,0xdeadbeef

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
.global _TEXT_BASE
_TEXT_BASE:
     .word   TEXT_BASE

.globl _rtthread_start
_rtthread_start:
     .word   _start

.globl _rtthread_end
_rtthread_end:
     .word   _end

.globl _bss_start
_bss_start:
     .word   __bss_start     @ load end address

.globl _bss_end
_bss_end:
    .word   __bss_end

.globl IRQ_STACK_START
IRQ_STACK_START:
    .word   _irq_stack_start + 1024

.globl FIQ_STACK_START
FIQ_STACK_START:
     .word   _fiq_stack_start +1024

.globl UNDEFINED_STACK_START
UNDEFINED_STACK_START:
	.word _undefined_stack_start + CONFIG_STACKSIZE

.globl ABORT_STACK_START
ABORT_STACK_START:
	.word _abort_stack_start + CONFIG_STACKSIZE

.globl _STACK_START
_STACK_START:
	.word _priv_stack_start + 4096

.equ  SEP6200_VIC_BASE,		 0xb0000000
.equ  SEP6200_SYSCTL_BASE,	 0xb0008000
/* ----------------------------------entry------------------------------*/
reset:
	/* set the cpu to PRIV mode and disable cpu interrupt */
	mov		r0, asr
	andn		r0, r0, #0xff
	or		r0, r0, #PRIVMODE|NOINT
	mov.a		asr, r0

	/* mask all IRQs by clearing all bits in the INTMRs */
	ldw	r1, =SEP6200_VIC_BASE
	ldw 	r0, =0xffffffff
	stw	r0, [r1+], #0x20 /*interrupt enable clear*/
	stw	r0, [r1+], #0x24


	/*remap ddr to 0x00000000 address*/
	ldw	r1, =SEP6200_SYSCTL_BASE
	ldw	r0, [r1+]
	ldw	r2, =0x80000000
	or	r0, r0, r2
	stw	r2, [r1+]

	/* set interrupt vector */
	/*do nothing here for vector*/

	/* setup stack */
	b.l		stack_setup

  /* copy the vector code to address 0 */
	ldw	r12, =0x100
	ldw	r0, = 0x40000000
	ldw	r1, = 0x00000000
copy_vetor:
	ldw	r2, [r0]
	stw	r2, [r1]
	add	r0, r0, #4
	add	r1, r1, #4
	sub	r12, r12, #4
	cmpsub.a	r12, #0
	bne	copy_vetor

	/* clear .bss */
	ldw   	r0, _bss_start         /* bss start   */
	ldw   	r1, _bss_end           /* bss end     */
	mov   	r2,#0                  /* get a zero  */


bss_loop:
	stw r2, [r0]            @ clear loop...
	add r0, r0, #4
	cmpsub.a    r0, r1
	bel bss_loop

	/* call C++ constructors of global objects 							*/
	ldw	r0, =__ctors_start__
	ldw	r1, =__ctors_end__

ctor_loop:
	cmpsub.a	r0, r1
	beq	ctor_end
	ldw.w	r2, [r0]+, #4
	stm.w	(r0, r1), [sp-]
	add	lr, pc, #4
	mov	pc, r2
	ldm.w	(r0, r1), [sp]+
	b ctor_loop
ctor_end:

  /*enable interrupt*/
	mov 	r0, asr
	andn 	r1, r0, #NOINT
	mov.a 	asr, r1

	/* start RT-Thread Kernel */
	ldw		pc, _rtthread_startup

_rtthread_startup:
	.word rtthread_startup

/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */

/* exception handlers */
/*Just simple implementation here */
	.align  5
extend_handle:
    b rt_hw_trap_extn
swi_handle:
    b rt_hw_trap_swi
iabort_handle:
    b rt_hw_trap_pabt
dabort_handle:
    b rt_hw_trap_dabt
reserve_handle:
    b rt_hw_trap_resv

.globl 		rt_interrupt_enter
.globl 		rt_interrupt_leave
.globl 		rt_thread_switch_interrupt_flag
.globl 		rt_interrupt_from_thread
.globl 		rt_interrupt_to_thread
IRQ_handle:

  stm.w (lr), [sp-]
  stm.w (r16 - r28), [sp-]
  stm.w (r0 - r15), [sp-]

	b.l		rt_interrupt_enter
	b.l		rt_hw_trap_irq
	b.l		rt_interrupt_leave

	/* if rt_thread_switch_interrupt_flag set, jump to _interrupt_thread_switch and don't return */
	ldw		r0, =rt_thread_switch_interrupt_flag
	ldw		r1, [r0+]
	cmpsub.a	r1, #1
	beq		_interrupt_thread_switch

  ldm.w (r0 - r15), [sp]+
  ldm.w (r16 - r28), [sp]+
  ldm.w (lr), [sp]+
  mov.a pc, lr

	.align	5
FIQ_handle:
  b rt_hw_trap_fiq

_interrupt_thread_switch:

	mov		r1,  #0	/* clear rt_thread_switch_interrupt_flag*/
	stw		r1,  [r0+]

	/*reload register*/
  ldm.w (r0 - r15), [sp]+
  ldm.w (r16 - r28), [sp]+
  ldm.w (lr), [sp]+

	stm.w	(r0 - r3), [sp-] /*save r0-r3*/

	mov		r1,  sp
	add		sp,  sp, #16 /* restore sp */
	mov		r2,  lr	/* save old task's pc to r2 */

  mov r3, bsr
  mov r0, #0xd3 /*I:F:0:PRIV*/
  mov.a asr, r0

	stm.w	(r2), [sp-] /* push old task's pc */

	/* push old task's registers */
  stm.w (lr), [sp-]
  stm.w (r16 - r28), [sp-]
  stm.w (r4 - r15), [sp-]
	mov		r4,  r1	/* Special optimised code below		*/
  mov		r5,  r3
  ldm.w (r0 - r3), [r4]+
  stm.w (r0 - r3), [sp-] /*push old task's r3-r0*/
	stm.w	(r5),	 [sp-] /* push old task's asr */
	mov	r4, bsr
	stm.w (r4), [sp-]	/* push old task's bsr*/

	ldw		r4,  =rt_interrupt_from_thread
	ldw		r5,  [r4+]
	stw		sp,  [r5+] /* store sp in preempted tasks's TCB*/

	ldw	r6,  =rt_interrupt_to_thread
	ldw	r6,  [r6+]
	ldw	sp,  [r6+] /* get new task's stack pointer	*/

	ldm.w	(r4), [sp]+	/* pop new task's spsr				*/
	mov.a	bsr, r4
	ldm.w	(r4), [sp]+	/* pop new task's psr				*/
	mov.a	asr, r4

	/* pop new task's r0-r28,lr & pc */

  ldm.w (r0 - r15), [sp]+
  ldm.w (r16 - r28), [sp]+
  ldm.w (lr), [sp]+
  ldm.w (pc), [sp]+

stack_setup:
	/*irq*/
  mov ip, lr
	mov		r0, asr
	andn  r0, r0, #0x1f
	or		r0, r0, #IRQMODE|NOINT
	mov.a		asr, r0 /*IRQMODE*/
  ldw   r0, =IRQ_STACK_START
  ldw   sp, [r0+]
	/*ldw		sp, IRQ_STACK_START*/

	/*priv*/
	mov		r0, asr
	andn    	r0, r0, #0x1f
	or		r0, r0, #PRIVMODE|NOINT
	mov.a		asr, r0 /*PRIVMODE*/
  ldw   r0, =_STACK_START
  ldw   sp, [r0+]
	/*ldw		sp, _STACK_START*/
  mov lr, ip
	/*fiq and other mode is not implemented in code here*/
	mov 		pc, lr /*lr may not be valid for the mode changes*/
/*/*}*/
