/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei  the first version
 * 2021-11-04     GuEe-GUI     set sp with SP_ELx
 */

/*
 *enable gtimer
 */
.globl rt_hw_gtimer_enable
rt_hw_gtimer_enable:
	MOV X0,#1
	MSR CNTP_CTL_EL0,X0
	RET

/*
 *disable gtimer
 */
.globl rt_hw_gtimer_disable
rt_hw_gtimer_disable:
    MSR CNTP_CTL_EL0,XZR
    RET

/*
 *set gtimer CNTP_TVAL_EL0 value
 */
.globl rt_hw_set_gtimer_val
rt_hw_set_gtimer_val:
	MSR CNTP_TVAL_EL0,X0
	RET

/*
 *get gtimer CNTP_TVAL_EL0 value
 */
.globl rt_hw_get_gtimer_val
rt_hw_get_gtimer_val:
	MRS X0,CNTP_TVAL_EL0
	RET


.globl rt_hw_get_cntpct_val
rt_hw_get_cntpct_val:
	MRS X0, CNTPCT_EL0
	RET

/*
 *get gtimer frq value
 */
.globl rt_hw_get_gtimer_frq
rt_hw_get_gtimer_frq:
	MRS X0,CNTFRQ_EL0
	RET

.macro SAVE_CONTEXT
    /* Save the entire context. */
    STP 	X0, X1, [SP, #-0x10]!
    STP 	X2, X3, [SP, #-0x10]!
    STP 	X4, X5, [SP, #-0x10]!
    STP 	X6, X7, [SP, #-0x10]!
    STP 	X8, X9, [SP, #-0x10]!
    STP 	X10, X11, [SP, #-0x10]!
    STP 	X12, X13, [SP, #-0x10]!
    STP 	X14, X15, [SP, #-0x10]!
    STP 	X16, X17, [SP, #-0x10]!
    STP 	X18, X19, [SP, #-0x10]!
    STP 	X20, X21, [SP, #-0x10]!
    STP 	X22, X23, [SP, #-0x10]!
    STP 	X24, X25, [SP, #-0x10]!
    STP 	X26, X27, [SP, #-0x10]!
    STP 	X28, X29, [SP, #-0x10]!
    STP 	X30, XZR, [SP, #-0x10]!

    MRS		X0, CurrentEL
    CMP		X0, 0xc
    B.EQ	3f
    CMP		X0, 0x8
    B.EQ	2f
    CMP		X0, 0x4
    B.EQ	1f
    B 		.
3:
    MRS		X3, SPSR_EL3
    /* Save the ELR. */
    MRS		X2, ELR_EL3
    B		0f
2:
    MRS		X3, SPSR_EL2
    /* Save the ELR. */
    MRS		X2, ELR_EL2
    B		0f
1:
    MRS		X3, SPSR_EL1
    MRS		X2, ELR_EL1
    B		0f
0:

    STP 	X2, X3, [SP, #-0x10]!

    MOV 	X0, SP   /* Move SP into X0 for saving. */

    .endm

.macro SAVE_CONTEXT_T
    /* Save the entire context. */
    STP 	X0, X1, [SP, #-0x10]!
    STP 	X2, X3, [SP, #-0x10]!
    STP 	X4, X5, [SP, #-0x10]!
    STP 	X6, X7, [SP, #-0x10]!
    STP 	X8, X9, [SP, #-0x10]!
    STP 	X10, X11, [SP, #-0x10]!
    STP 	X12, X13, [SP, #-0x10]!
    STP 	X14, X15, [SP, #-0x10]!
    STP 	X16, X17, [SP, #-0x10]!
    STP 	X18, X19, [SP, #-0x10]!
    STP 	X20, X21, [SP, #-0x10]!
    STP 	X22, X23, [SP, #-0x10]!
    STP 	X24, X25, [SP, #-0x10]!
    STP 	X26, X27, [SP, #-0x10]!
    STP 	X28, X29, [SP, #-0x10]!
    STP 	X30, XZR, [SP, #-0x10]!

    MRS		X0, CurrentEL
    CMP		X0, 0xc
    B.EQ	3f
    CMP		X0, 0x8
    B.EQ	2f
    CMP		X0, 0x4
    B.EQ	1f
    B 		.
3:
    MOV		X3, 0x0d
    MOV		X2, X30
    B		0f
2:
    MOV		X3, 0x09
    MOV		X2, X30
    B		0f
1:
    MOV		X3, 0x05
    MOV		X2, X30
    B		0f
0:

    STP 	X2, X3, [SP, #-0x10]!

    MOV 	X0, SP   /* Move SP into X0 for saving. */

    .endm

.macro RESTORE_CONTEXT

    /* Set the SP to point to the stack of the task being restored. */
    MOV		SP, X0

    LDP 	X2, X3, [SP], #0x10  /* SPSR and ELR. */

    MRS		X0, CurrentEL
    CMP		X0, 0xc
    B.EQ	3f
    CMP		X0, 0x8
    B.EQ	2f
    CMP		X0, 0x4
    B.EQ	1f
    B 		.
3:
    MSR		SPSR_EL3, X3
    MSR		ELR_EL3, X2
    B		0f
2:
    MSR		SPSR_EL2, X3
    MSR		ELR_EL2, X2
    B		0f
1:
    MSR		SPSR_EL1, X3
    MSR		ELR_EL1, X2
    B		0f
0:

    LDP 	X30, XZR, [SP], #0x10
    LDP 	X28, X29, [SP], #0x10
    LDP 	X26, X27, [SP], #0x10
    LDP 	X24, X25, [SP], #0x10
    LDP 	X22, X23, [SP], #0x10
    LDP 	X20, X21, [SP], #0x10
    LDP 	X18, X19, [SP], #0x10
    LDP 	X16, X17, [SP], #0x10
    LDP 	X14, X15, [SP], #0x10
    LDP 	X12, X13, [SP], #0x10
    LDP 	X10, X11, [SP], #0x10
    LDP 	X8, X9, [SP], #0x10
    LDP 	X6, X7, [SP], #0x10
    LDP 	X4, X5, [SP], #0x10
    LDP 	X2, X3, [SP], #0x10
    LDP 	X0, X1, [SP], #0x10

    ERET

    .endm

.text
/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    MRS      X0, DAIF
    MSR      DAIFSet, #3
    DSB      SY
    RET

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    DSB     SY
    MOV     X1, #0xC0
    ANDS    X0, X0, X1
    B.NE    rt_hw_interrupt_enable_exit
    MSR     DAIFClr, #3
rt_hw_interrupt_enable_exit:
    RET

/*
 * void rt_hw_context_switch_to(rt_ubase_t to);
 * r0 --> to
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    LDR		X0, [X0]
    RESTORE_CONTEXT

.text
/*
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to);
 * r0 --> from
 * r1 --> to
 */
.globl rt_hw_context_switch
rt_hw_context_switch:

    MOV		X8,X0
    MOV		X9,X1

    SAVE_CONTEXT_T
    
    STR		X0, [X8]            // store sp in preempted tasks TCB
    LDR		X0, [X9]            // get new task stack pointer
    
    RESTORE_CONTEXT

/*
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to);
 */
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    ADR 	X2, rt_thread_switch_interrupt_flag
    LDR 	X3, [X2]
    CMP 	X3, #1
    B.EQ 	_reswitch
    ADR 	X4, rt_interrupt_from_thread   // set rt_interrupt_from_thread
    MOV 	X3, #1              // set rt_thread_switch_interrupt_flag to 1
    STR 	X0, [X4]
    STR 	X3, [X2]
_reswitch:
    ADR 	X2, rt_interrupt_to_thread     // set rt_interrupt_to_thread
    STR 	X1, [X2]
    RET

.text

// -- Exception handlers ----------------------------------

    .align  8
.globl vector_fiq
vector_fiq:
    SAVE_CONTEXT
    STP 	X0, X1, [SP, #-0x10]!
    BL      rt_hw_trap_fiq
    LDP 	X0, X1, [SP], #0x10
    RESTORE_CONTEXT

.globl      rt_interrupt_enter
.globl      rt_interrupt_leave
.globl      rt_thread_switch_interrupt_flag
.globl      rt_interrupt_from_thread
.globl      rt_interrupt_to_thread


// -------------------------------------------------------------------

    .align  8
.globl vector_irq
vector_irq:
    SAVE_CONTEXT
    STP 	X0, X1, [SP, #-0x10]!

    BL      rt_interrupt_enter
    BL      rt_hw_trap_irq
    BL      rt_interrupt_leave
    
    LDP 	X0, X1, [SP], #0x10

    // if rt_thread_switch_interrupt_flag set, jump to
    // rt_hw_context_switch_interrupt_do and don't return
    ADR 	X1, rt_thread_switch_interrupt_flag
    LDR     X2, [X1]
    CMP     X2, #1
    B.NE     vector_irq_exit

    MOV     X2,  #0         // clear flag
    STR     X2,  [X1]

    ADR     X3,  rt_interrupt_from_thread
    LDR     X4,  [X3]
    STR     x0,  [X4]       // store sp in preempted tasks's TCB

    ADR     x3,  rt_interrupt_to_thread
    LDR     X4,  [X3]
    LDR     x0,  [X4]       // get new task's stack pointer
    
vector_irq_exit:	
    RESTORE_CONTEXT

// -------------------------------------------------

    .align  8
    .globl  vector_error
vector_error:
    SAVE_CONTEXT
    BL      rt_hw_trap_error
    B       .
