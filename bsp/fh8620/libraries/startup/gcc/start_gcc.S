/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include <rtconfig.h>
#include <armv6.h>

#define CONFIG_STACKSIZE 	512

#define FPEXC_EN            (1 << 30) /* VFP enable bit */
.equ    I_BIT,              0x80    @ when I bit is set, IRQ is disabled
.equ    F_BIT,              0x40    @ when F bit is set, FIQ is disabled

#.equ 	USERMODE, 			0x10
#.equ 	FIQMODE,			0x11
#.equ 	IRQMODE,			0x12
#.equ 	SVCMODE,			0x13
#.equ 	ABORTMODE,			0x17
#.equ 	UNDEFMODE,			0x1b
#.equ 	MODEMASK,			0x1f
#.equ 	NOINT,				0xc0


.equ    RAM_BASE,           0x00000000  /*Start address of RAM*/
.equ    ROM_BASE,           0xA0000000  /*Start address of Flash*/

#define    FH81_INTC_BASE   0xE0200000

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

    @vector 0x0
	@enable icaches
	@little endian
	@disable dcaches, mmu
	//ldr r0, =0x00400078
	@ldr r0, =0x0000107a
   // mcr p15, 0, r0, c1, c0, 0

   //read
	ldr r0, =0x0
	mrc p15, 0, r0, c1, c0, 0

	//change
	ldr r0, =0x00400078
	mcr p15, 0, r0, c1, c0, 0
	//check
	ldr r0, =0x0
	mrc p15, 0, r0, c1, c0, 0

    ldr r0, =0x00000000
    mcr p15, 0, r0, c8, c7, 0 	@ Flush TLB
  	mcr p15, 0, r0, c7, c7, 0 	@ Flush Caches
    mcr p15, 0, r0, c7, c10, 4 	@ Flush Write Buffer

    /* mask all IRQs by clearing all bits in the INTMRs     set low and high to 0 */
    ldr	r1, =FH81_INTC_BASE
    ldr	r0, =0x0
    str	r0, [r1]
    str	r0, [r1, #4]


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

    /* enable_unaligned_access */
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #0x02        /*Clear the A bit, bit 1*/
    and r0, r0, #(1 << 22)   /*Set the U bit, bit 22*/
    mcr p15, 0, r0, c1, c0, 0

#ifdef RT_USING_VFP
    bl      vfp_init
#endif

	/* start RT-Thread Kernel 		*/
	ldr		pc, _rtthread_startup

_rtthread_startup: 
	.word rtthread_startup

.global cpu_reset
cpu_reset:

	#ldr	r0, =0xfffffd00
	#ldr	r1, =(AT91_RSTC_KEY | AT91_RSTC_PROCRST | AT91_RSTC_PERRST)
	#str	r1, [r0]
	#mov	pc, lr
	B cpu_reset

/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */

.macro push_exp_reg
    sub     sp, sp, #S_FRAME_SIZE   @/* Sizeof(struct rt_hw_stack)  */
    stmib   sp, {r0 - r12}          @/* Calling r0-r12                  */
    mov     r0, sp
    mrs     r6, spsr                @/* Save CPSR                       */
    str     lr, [r0, #S_PC]         @/* Push PC                         */
    str     r6, [r0, #S_CPSR]       @/* Push CPSR                       */
    @ switch to SVC mode with no interrupt
    msr     cpsr_c, #I_BIT|F_BIT|SVCMODE
    str     sp, [r0, #S_SP]         @/* Save calling SP                 */
    str     lr, [r0, #S_LR]         @/* Save calling PC                 */
.endm

#ifdef RT_USING_VFP
__ret_to_undef:
    ldmfd   sp!, {r4}       @ pop task's cpsr to spsr
    msr     spsr_cxsf, r4
    ldmfd   sp!, {r0-r12}
    add     sp, sp, #4
    ldmfd   sp!, {lr,pc}^
#endif

/* exception handlers    */
    .align  5
vector_undef:
    push_exp_reg
#ifdef RT_USING_VFP
    cps     #UNDEFMODE
    ldr     r2, [r0, #S_PC]     @ r2=faulted PC+4
    adr     r9, __ret_to_undef  @ r9=exception success return
    sub     r1, r2, #4
    ldr     r0, [r1]            @ r0=faulted instruction
    bl      undef_entry
    mov     r0, sp
#endif
    bl     rt_hw_trap_udef

    .align  5
vector_swi:
    push_exp_reg
    bl     rt_hw_trap_swi

    .align  5
vector_pabt:
    push_exp_reg
    bl     rt_hw_trap_pabt

    .align  5
vector_dabt:
    push_exp_reg
    bl     rt_hw_trap_dabt

    .align  5
vector_resv:
    push_exp_reg
    bl     rt_hw_trap_resv

.globl     rt_interrupt_enter
.globl     rt_interrupt_leave
.globl     rt_thread_switch_interrupt_flag
.globl     rt_interrupt_from_thread
.globl     rt_interrupt_to_thread
vector_irq:
    stmfd   sp!, {r0-r12,lr}
@
#ifdef RT_USING_VFP
    vmrs    r0, fpexc
    stmfd   sp!, {r0}            @ save VFP status -- irq_fpexc = fpexc
    bic     r0, r0, #FPEXC_EN    @ always disable VFP so we can
                                 @ lazily save/restore the old state.
    vmsr    fpexc, r0
#endif

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

#ifdef RT_USING_VFP
    ldmfd   sp!, {r1}
    vmrs    r0, fpexc
    tst     r0, #FPEXC_EN        @ irq used VFP?
    bicne   r1, r0, #FPEXC_EN    @ if irq used VFP, then clear fpexc.en bit
    vmsr    fpexc, r1            @ restore VFP status
                                 @ if irq not used VFP, then fpexc = irq_fpexc
                                 @ if irq used VFP, then disable VFP
#endif

    @ if rt_thread_switch_interrupt_flag set, jump to
    @ rt_hw_context_switch_interrupt_do and don't return
    ldr     r0, =rt_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq     rt_hw_context_switch_interrupt_do

    ldmfd   sp!, {r0-r12,lr}
    @mrs r8,spsr
    @msr cpsr, r8
    subs    pc, lr, #4

    .align  5
vector_fiq:
    stmfd   sp!,{r0-r7,lr}
    bl      rt_hw_trap_fiq
    ldmfd   sp!,{r0-r7,lr}
    subs    pc,lr,#4

rt_hw_context_switch_interrupt_do:
    mov     r1,  #0         @ clear flag
    str     r1,  [r0]

    ldmfd   sp!, {r0-r12,lr}@ reload saved registers
    stmfd   sp,  {r0-r2}    @ save r0-r2

    mrs     r0,  spsr       @ get cpsr of interrupt thread

    sub     r1,  sp, #4*3
    sub     r2,  lr, #4     @ save old task's pc to r2

    @ switch to SVC mode with no interrupt
    msr     cpsr_c, #I_BIT|F_BIT|SVCMODE

    stmfd   sp!, {r2}       @ push old task's pc
    stmfd   sp!, {r3-r12,lr}@ push old task's lr,r12-r4
    ldmfd   r1,  {r1-r3}    @ restore r0-r2 of the interrupt thread
    stmfd   sp!, {r1-r3}    @ push old task's r0-r2
    stmfd   sp!, {r0}       @ push old task's cpsr

    ldr     r4,  =rt_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]       @ store sp in preempted tasks's TCB

    ldr     r6,  =rt_interrupt_to_thread
    ldr     r6,  [r6]
    ldr     sp,  [r6]       @ get new task's stack pointer

    ldmfd   sp!, {r4}       @ pop new task's cpsr to spsr
    msr     spsr_cxsf, r4

#ifdef RT_USING_VFP
    vmrs    r0, fpexc
    bic     r0, r0, #FPEXC_EN    @ always disable VFP so we can
                                 @ lazily save/restore the old state.
    vmsr    fpexc, r0
#endif

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr


stack_setup:
    mrs     r0, cpsr
    bic     r0, r0, #MODEMASK
    orr     r1, r0, #UNDEFMODE|NOINT
    msr     cpsr_cxsf, r1           /* undef mode          */
    ldr     sp, UNDEFINED_STACK_START

    orr     r1,r0,#ABORTMODE|NOINT
    msr     cpsr_cxsf,r1            /* abort mode          */
    ldr     sp, ABORT_STACK_START

    orr     r1,r0,#IRQMODE|NOINT
    msr     cpsr_cxsf,r1            /* IRQ mode            */
    ldr     sp, IRQ_STACK_START

    orr     r1,r0,#FIQMODE|NOINT
    msr     cpsr_cxsf,r1            /* FIQ mode            */
    ldr     sp, FIQ_STACK_START

    bic     r0,r0,#MODEMASK
    orr     r1,r0,#SVCMODE|NOINT
    msr     cpsr_cxsf,r1            /* SVC mode            */

    ldr     sp, _STACK_START

    /* USER mode is not initialized. */
    bx      lr    /* The LR register may be not valid for the mode changes.*/

/*/*}*/
