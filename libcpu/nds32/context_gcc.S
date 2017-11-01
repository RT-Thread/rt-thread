#include "nds32.h"
#include "os_cpu_common.h"
#include "config.h"

	.align 4
! void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
! R0 --> from
! R1 --> to
    .section .text
    .global rt_hw_context_switch_interrupt
    .global rt_hw_context_switch
rt_hw_context_switch_interrupt:
rt_hw_context_switch:
	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}

    la     $r2, rt_thread_switch_interrupt_flag
    lw     $r3, [$r2]
    movi   $r4, #1
    beq    $r3, $r4, _reswitch
    sw     $r4, [$r2]                           ! set rt_thread_switch_interrupt_flag to 1

    la     $r2, rt_interrupt_from_thread
    sw     $r0, [$r2]                           ! set rt_interrupt_from_thread
_reswitch:
	la     $r2, rt_interrupt_to_thread
    sw     $r1, [$r2]                           ! set rt_interrupt_to_thread
    bal    hal_intc_swi_trigger                 ! trigger the swi exception (causes context switch)

	pop25  $r6,#8    ! {$r6, $fp, $gp, $lp}

! R0 --> switch from thread stack
! R1 --> switch to thread stack
! psr, pc, LR, R12, R3, R2, R1, R0 are pushed into [from] stack

	.align 4
	.global OS_Trap_Interrupt_SWI
OS_Trap_Interrupt_SWI:
!	pushm $r0, $r5
    setgie.d                                     ! disable interrupt to protect context switch
	dsb

    IntlDescend                                  ! Descend interrupt level

	movi	$r0, 0x0
	mtsr	$r0, $INT_PEND                       ! clean SWI pending

	la      $r0, rt_thread_switch_interrupt_flag ! get rt_thread_switch_interrupt_flag
	lw      $r1, [$r0]
	beqz    $r1, pendsv_exit                     ! swi has already been handled

	movi    $r1, #0
	sw      $r1, [$r0]                           ! clear rt_thread_switch_interrupt_flag to 0

	la      $r0, rt_interrupt_from_thread
	lw      $r1, [$r0]
	beqz    $r1, switch_to_thread                ! skip register save at the first time(os startup phase)

	SAVE_ALL

	move    $r1, $sp
	la      $r0, rt_interrupt_from_thread
	lw      $r0, [$r0]
	sw      $r1, [$r0]

switch_to_thread:
    la     $r1, rt_interrupt_to_thread
    lw     $r1, [$r1]
    lw     $r1, [$r1]                            ! load thread stack pointer
	move   $sp, $r1                              ! update stack pointer
	RESTORE_ALL                                  ! pop registers

pendsv_exit:
	setgie.e
	iret

	.align 4
! void rt_hw_context_switch_to(rt_uint32 to);
! R0 --> to
    .global rt_hw_context_switch_to
rt_hw_context_switch_to:
    la     $r1, rt_interrupt_to_thread
    sw     $r0, [$r1]

    ! set from thread to 0
    la     $r1, rt_interrupt_from_thread
    movi   $r0, #0
    sw     $r0, [$r1]

    ! set interrupt flag to 1
    la     $r1, rt_thread_switch_interrupt_flag
    movi   $r0, #1
    sw     $r0, [$r1]

    ! set the SWI exception priority(must be the lowest level)
	! todo

    ! trigger the SWI exception (causes context switch)
    jal    hal_intc_swi_trigger

    setgie.e            ! enable interrupts at processor level

1:
	b   1b              ! never reach here

#ifndef VECTOR_NUMINTRS
#define VECTOR_NUMINTRS		32
#endif

	.global OS_Trap_Int_Common

	! Set up Interrupt vector ISR
	! HW#IRQ_SWI_VECTOR : OS_Trap_Interrupt_SWI (SWI)
	! HW#n : OS_Trap_Int_Common

	.macro	SET_HWISR num
	.global OS_Trap_Interrupt_HW\num
	.if	\num == IRQ_SWI_VECTOR
	.set	OS_Trap_Interrupt_HW\num, OS_Trap_Interrupt_SWI
	.else
	.set	OS_Trap_Interrupt_HW\num, OS_Trap_Int_Common
	.endif
	.endm

	.altmacro
	.set	irqno, 0
	.rept	VECTOR_NUMINTRS
	SET_HWISR %irqno
	.set	irqno, irqno+1
	.endr
	.noaltmacro

!	.global OS_Trap_Int_Common
OS_Trap_Int_Common:
#ifdef MPU_SUPPORT
	mfsr	$p1, $PSW
	ori	$p1, $p1, (PSW_mskIT | PSW_mskDT)
	mtsr	$p1, $PSW                       ! enable IT/DT
	dsb
	pushm	$r0, $r5
	move	$r0, $p0                        ! IRQ number
#endif
	! $r0 : HW Interrupt vector number
	SAVE_CALLER

	IntlDescend                             ! Descend interrupt level

	mfsr	$r1, $IPSW                      ! Use IPSW.CPL to check come from thread or ISR
	srli45	$r1, #PSW_offCPL
	fexti33	$r1, #0x2                       ! IPSW.CPL
	bnec	$r1, #0x7, 2f                   ! IPSW.CPL != 7, come form ISR, reentrant

	move	$fp, $sp                        ! save old stack pointer
	la	    $sp, __OS_Int_Stack             ! switch to interrupt stack
2:
	setgie.e                                ! allow nested now

	! The entire CPU state is now stashed on the stack,
	! and the stack is also 8-byte alignment.
	! We can call C program based interrupt handler now.
	la	    $r1, OS_CPU_Vector_Table
	lw	    $r1, [$r1+($r0<<2)]             ! ISR function pointer
	jral	$r1                             ! Call ISR

	la	    $r1, __OS_Int_Stack             ! Check for nested interruption return
	bne	    $r1, $sp, 3f                    ! $sp != __OS_Int_Stack?

	move	$sp, $fp                        ! Move back to the thread stack
3:
	RESTORE_CALLER

	iret

!	.set	OS_Trap_Interrupt_HW9, OS_Trap_Interrupt_SWI
!	.set	OS_Trap_Interrupt_HW19, OS_Trap_Int_Common

!*********************************************
! POINTERS TO VARIABLES
!*********************************************
#ifdef MPU_SUPPORT
	.section privileged_data
#else
	.section .bss
#endif
	.skip IRQ_STACK_SIZE
	.align 3
__OS_Int_Stack:

	.end
