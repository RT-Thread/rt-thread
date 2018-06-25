#include "context.h"
#define SPRG0	0x110	/* Special Purpose Register General 0 */
#define SPRG1	0x111	/* Special Purpose Register General 1 */

#define STACK_BALANCE_DEBUG	1
/*栈平衡调试开关， 如果该开关打开后，
每次任务切换 都会测试OFFSET R1的值是否为1A2B。
如果 *OFFSET R1的值是0x1A2B的话，说明任务切换是OK的*/


    .globl rt_hw_interrupt_disable
    .globl rt_hw_interrupt_enable
    .globl rt_hw_context_switch
    .globl rt_hw_context_switch_to
    .globl rt_hw_context_switch_interrupt
    .globl rt_hw_systemcall_entry
    .globl rt_interrupt_enter
    .globl rt_interrupt_leave

	.section  .handlers, "axv"


/*
 * rt_base_t rt_hw_interrupt_disable();
 * return the interrupt status and disable interrupt
 */

rt_hw_interrupt_disable:
    wrteei  0	//By Snikeguo
    se_blr


/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 * restore interrupt
 */
rt_hw_interrupt_enable:
    wrteei  1	//By Snikeguo
    se_blr


 	.align    4
    .globl    IVOR8_Handler
    .type     IVOR8_Handler, @function

IVOR8_Handler:
rt_hw_systemcall_entry:
	//入栈
	//wrteei  0
	mtsprg0	r1	/*sprg0 sprg 1没有定义功能，这里可以用来暂时保存r1*/
	mtsprg1	r3	/*sprg0 sprg 1没有定义功能，这里可以用来暂时保存r3*/

	e_lis     r3,rt_interrupt_from_thread@h
    e_or2i    r3,rt_interrupt_from_thread@l
    e_lwz     r3,0(r3)	/*r3=rt_interrupt_from_thread	SP的地址*/
    e_subi	  r1,r1,STACK_FRAME_SIZES
    e_stw	  r1,0(r3) 	/* *rt_interrupt_from_thread=当前栈指针*/
	e_stw	  r0   ,OFFSET_R0(r1)
	e_stw	  r2   ,OFFSET_R2(r1)
	mfsprg1	  r3
	e_stw	  r3   ,OFFSET_R3(r1)
	e_stw	  r4   ,OFFSET_R4(r1)
	e_stw	  r5   ,OFFSET_R5(r1)
	e_stw	  r6   ,OFFSET_R6(r1)
	e_stw	  r7   ,OFFSET_R7(r1)
	e_stw	  r8   ,OFFSET_R8(r1)
	e_stw	  r9   ,OFFSET_R9(r1)
	e_stw	  r10  ,OFFSET_R10(r1)
	e_stw	  r11  ,OFFSET_R11(r1)
	e_stw	  r12  ,OFFSET_R12(r1)
	e_stw	  r13  ,OFFSET_R13(r1)
	e_stw	  r14  ,OFFSET_R14(r1)
	e_stw	  r15  ,OFFSET_R15(r1)
	e_stw	  r16  ,OFFSET_R16(r1)
	e_stw	  r17  ,OFFSET_R17(r1)
	e_stw	  r18  ,OFFSET_R18(r1)
	e_stw	  r19  ,OFFSET_R19(r1)
	e_stw	  r20  ,OFFSET_R20(r1)
	e_stw	  r21  ,OFFSET_R21(r1)
	e_stw	  r22  ,OFFSET_R22(r1)
	e_stw	  r23  ,OFFSET_R23(r1)
	e_stw	  r24  ,OFFSET_R24(r1)
	e_stw	  r25  ,OFFSET_R25(r1)
	e_stw	  r26  ,OFFSET_R26(r1)
	e_stw	  r27  ,OFFSET_R27(r1)
	e_stw	  r28  ,OFFSET_R28(r1)
	e_stw	  r29  ,OFFSET_R29(r1)
	e_stw	  r30  ,OFFSET_R30(r1)
	e_stw	  r31  ,OFFSET_R31(r1)
	mfcr	  r0
	e_stw	  r0	,OFFSET_CR(r1)
	mflr	  r0
	e_stw	  r0	,OFFSET_LR(r1)
	mfctr	  r0
	e_stw	  r0	,OFFSET_CTR(r1)
	mfxer	  r0
	e_stw	  r0	,OFFSET_XER(r1)
	mfsrr1	  r0
	e_stw	  r0	,OFFSET_SRR1(r1)
	mfsrr0	  r0
	e_stw	  r0	,OFFSET_SRR0(r1)
	mfmsr	  r0
	e_stw	  r0	,OFFSET_MSR(r1)

	e_li	  r0,	0x1A2B
	e_stw	  r0	,OFFSET_R1(r1)

	//出战
	e_lis     r4,rt_interrupt_to_thread@h
    e_or2i    r4,rt_interrupt_to_thread@l/*R4此时是rt_interrupt_to_thread的地址*/
    e_lwz     r4,0(r4)/*R4此时是rt_interrupt_to_thread	也就是SP的地址*/
    e_lwz     r1,0(r4)/*R1此时是*rt_interrupt_to_thread	也就是SP的值*/

    /*e_lwz	  r5,0(r4)
    e_addi	  r5,r5,STACK_FRAME_SIZES
    e_stw	  r5,0(r4)*/
#if STACK_BALANCE_DEBUG==1
	e_lwz	r0,OFFSET_R1(r1)
	e_cmp16i	r0,0x1A2B
	e_beq	ivor8_stack_balance_success
ivor8_stack_balance_error:
	e_b		ivor8_stack_balance_error
ivor8_stack_balance_success:
#endif
	e_lwz	r0,OFFSET_MSR(r1)
	mtmsr	r0
	e_lwz	r0,OFFSET_SRR0(r1)
	mtsrr0	r0
	e_lwz	r0,OFFSET_SRR1(r1)
	mtsrr1	r0
	e_lwz	r0,OFFSET_XER(r1)
	mtxer	r0
	e_lwz	r0,OFFSET_CTR(r1)
	mtctr	r0
	e_lwz	r0,OFFSET_LR(r1)
	mtlr	r0
	e_lwz	r0,OFFSET_CR(r1)
	mtcr	r0
	e_lwz	r31,OFFSET_R31(r1)
	e_lwz	r30,OFFSET_R30(r1)
	e_lwz	r29,OFFSET_R29(r1)
	e_lwz	r28,OFFSET_R28(r1)
	e_lwz	r27,OFFSET_R27(r1)
	e_lwz	r26,OFFSET_R26(r1)
	e_lwz	r25,OFFSET_R25(r1)
	e_lwz	r24,OFFSET_R24(r1)
	e_lwz	r23,OFFSET_R23(r1)
	e_lwz	r22,OFFSET_R22(r1)
	e_lwz	r21,OFFSET_R21(r1)
	e_lwz	r20,OFFSET_R20(r1)
	e_lwz	r19,OFFSET_R19(r1)
	e_lwz	r18,OFFSET_R18(r1)
	e_lwz	r17,OFFSET_R17(r1)
	e_lwz	r16,OFFSET_R16(r1)
	e_lwz	r15,OFFSET_R15(r1)
	e_lwz	r14,OFFSET_R14(r1)
	e_lwz	r13,OFFSET_R13(r1)
	e_lwz	r12,OFFSET_R12(r1)
	e_lwz	r11,OFFSET_R11(r1)
	e_lwz	r9,OFFSET_R9(r1)
	e_lwz	r8,OFFSET_R8(r1)
	e_lwz	r7,OFFSET_R7(r1)
	e_lwz	r6,OFFSET_R6(r1)
	e_lwz	r5,OFFSET_R5(r1)
	e_lwz	r4,OFFSET_R4(r1)
	e_lwz	r3,OFFSET_R3(r1)
	e_lwz	r2,OFFSET_R2(r1)
	e_lwz	r0,OFFSET_R0(r1)
	e_addi	r1,r1,STACK_FRAME_SIZES
	//wrteei  1
	se_rfi   ;# End of Interrupt Handler - re-enables interrupts

		.align    4
    	.globl    rt_frist_switch
    	.type     rt_frist_switch, @function
rt_frist_switch:
	e_lis     r4,rt_interrupt_to_thread@h
    e_or2i    r4,rt_interrupt_to_thread@l/*R4此时是rt_interrupt_to_thread的地址*/
    e_lwz     r4,0(r4)/*R4此时是*rt_interrupt_to_thread	SP的地址*/
    e_lwz     r1,0(r4)/*R1此时是**rt_interrupt_to_thread	SP的值*/

    e_lwz	  r5,0(r4)
    e_addi	  r5,r5,STACK_FRAME_SIZES
    e_stw	  r5,0(r4)

#if STACK_BALANCE_DEBUG==1
	e_lwz	r0,OFFSET_R1(r1)
	e_cmp16i	r0,0x1A2B
	e_beq	rt_frist_switch_stack_balance_success
rt_frist_switch_stack_balance_error:
	e_b		rt_frist_switch_stack_balance_error
rt_frist_switch_stack_balance_success:
#endif
	e_lwz	r0,OFFSET_MSR(r1)
	mtmsr	r0
	e_lwz	r0,OFFSET_SRR0(r1)
	mtsrr0	r0
	e_lwz	r0,OFFSET_SRR1(r1)
	mtsrr1	r0
	e_lwz	r0,OFFSET_XER(r1)
	mtxer	r0
	e_lwz	r0,OFFSET_CTR(r1)
	mtctr	r0
	e_lwz	r0,OFFSET_LR(r1)
	mtlr	r0
	e_lwz	r0,OFFSET_CR(r1)
	mtcr	r0
	e_lwz	r31,OFFSET_R31(r1)
	e_lwz	r30,OFFSET_R30(r1)
	e_lwz	r29,OFFSET_R29(r1)
	e_lwz	r28,OFFSET_R28(r1)
	e_lwz	r27,OFFSET_R27(r1)
	e_lwz	r26,OFFSET_R26(r1)
	e_lwz	r25,OFFSET_R25(r1)
	e_lwz	r24,OFFSET_R24(r1)
	e_lwz	r23,OFFSET_R23(r1)
	e_lwz	r22,OFFSET_R22(r1)
	e_lwz	r21,OFFSET_R21(r1)
	e_lwz	r20,OFFSET_R20(r1)
	e_lwz	r19,OFFSET_R19(r1)
	e_lwz	r18,OFFSET_R18(r1)
	e_lwz	r17,OFFSET_R17(r1)
	e_lwz	r16,OFFSET_R16(r1)
	e_lwz	r15,OFFSET_R15(r1)
	e_lwz	r14,OFFSET_R14(r1)
	e_lwz	r13,OFFSET_R13(r1)
	e_lwz	r12,OFFSET_R12(r1)
	e_lwz	r11,OFFSET_R11(r1)
	e_lwz	r9,OFFSET_R9(r1)
	e_lwz	r8,OFFSET_R8(r1)
	e_lwz	r7,OFFSET_R7(r1)
	e_lwz	r6,OFFSET_R6(r1)
	e_lwz	r5,OFFSET_R5(r1)
	e_lwz	r4,OFFSET_R4(r1)
	e_lwz	r3,OFFSET_R3(r1)
	e_lwz	r2,OFFSET_R2(r1)
	e_lwz	r0,OFFSET_R0(r1)
	e_addi	r1,r1,STACK_FRAME_SIZES
	se_rfi

#if 1

	.globl   IVOR4_Handler
	.globl	 rt_current_thread_sp
	#ifdef __ghs__
	.section    .vletext, axv
	.vle
	#endif

	.equ  INTC_IACKR, 0xFFF48010   ;# Interrupt Acknowledge Register address
	.equ  INTC_EOIR,  0xFFF48018   ;# End Of Interrupt Register address

	.align 4

IVOR4_Handler:
	//wrteei    0//关中断
	//入栈
	e_subi	  r1,	r1,STACK_FRAME_SIZES
	e_stw	  r0   ,OFFSET_R0(r1)

    e_li	  r0,	0x1A2B/*将0x1A2B付给r0*/
    e_stw	  r0	,OFFSET_R1(r1)/*将当前SP指针保存起来*/

	e_stw	  r2   ,OFFSET_R2(r1)
	e_stw	  r3   ,OFFSET_R3(r1)
	e_stw	  r4   ,OFFSET_R4(r1)
	e_stw	  r5   ,OFFSET_R5(r1)
	e_stw	  r6   ,OFFSET_R6(r1)
	e_stw	  r7   ,OFFSET_R7(r1)
	e_stw	  r8   ,OFFSET_R8(r1)
	e_stw	  r9   ,OFFSET_R9(r1)
	e_stw	  r10  ,OFFSET_R10(r1)
	e_stw	  r11  ,OFFSET_R11(r1)
	e_stw	  r12  ,OFFSET_R12(r1)
	e_stw	  r13  ,OFFSET_R13(r1)
	e_stw	  r14  ,OFFSET_R14(r1)
	e_stw	  r15  ,OFFSET_R15(r1)
	e_stw	  r16  ,OFFSET_R16(r1)
	e_stw	  r17  ,OFFSET_R17(r1)
	e_stw	  r18  ,OFFSET_R18(r1)
	e_stw	  r19  ,OFFSET_R19(r1)
	e_stw	  r20  ,OFFSET_R20(r1)
	e_stw	  r21  ,OFFSET_R21(r1)
	e_stw	  r22  ,OFFSET_R22(r1)
	e_stw	  r23  ,OFFSET_R23(r1)
	e_stw	  r24  ,OFFSET_R24(r1)
	e_stw	  r25  ,OFFSET_R25(r1)
	e_stw	  r26  ,OFFSET_R26(r1)
	e_stw	  r27  ,OFFSET_R27(r1)
	e_stw	  r28  ,OFFSET_R28(r1)
	e_stw	  r29  ,OFFSET_R29(r1)
	e_stw	  r30  ,OFFSET_R30(r1)
	e_stw	  r31  ,OFFSET_R31(r1)
	mfcr	  r0
	e_stw	  r0	,OFFSET_CR(r1)
	mflr	  r0
	e_stw	  r0	,OFFSET_LR(r1)
	mfctr	  r0
	e_stw	  r0	,OFFSET_CTR(r1)
	mfxer	  r0
	e_stw	  r0	,OFFSET_XER(r1)
	mfsrr1	  r0
	e_stw	  r0	,OFFSET_SRR1(r1)
	mfsrr0	  r0
	e_stw	  r0	,OFFSET_SRR0(r1)
	mfmsr	  r0
	e_stw	  r0	,OFFSET_MSR(r1)

	e_subi	  r1,  r1,16				/*可能是PPC GCC的BUG,假设r1(SP)的地址是0x4A4，然后会进入中断程序，会占用0x4A4以上的内存空间，所以这里给出16个字节的余量*/
	e_lis     r3,  INTC_IACKR@h
	e_or2i    r3,  INTC_IACKR@l
	e_lwz     r3,  0(r3)           		/* load the base adress of Vector Table */
	e_lwz     r3,  0(r3)
	mtctr     r3                   		/* load ISR handler in CTR */

	mfSRR1    %r0						/* Restoring pre-IRQ MSR register value.*/

	se_bclri  %r0, 16             		/* No preemption, keeping EE disabled.*/ /* EE = bit 16 */
	mtMSR     %r0
	//wrteei    1
	se_bctrl                       			/* branch to handler */
	//wrteei    0
	mbar      0                    			/* complete all pending operations */
	e_lis     r3,  INTC_EOIR@h
	e_or2i    r3,  INTC_EOIR@l
	e_stw     r3,  0(r3)           			/* write 0 to INTC_EOIR_BASE */
   	e_addi	r1,r1,16						/*恢复16个字节的余量*/

	e_lis     r3,rt_thread_switch_interrput_flag@h
    e_or2i    r3,rt_thread_switch_interrput_flag@l
    e_lwz     r4,0(r3)
    e_cmpi    cr0,r4,0x0                     /* By Snikeguo    whether is 0     */
    e_beq     _no_switch                     /* no switch, exit  */
    e_li      r4,0x0                         /* set rt_thread_switch_interrput_flag to 0 */
    e_stw     r4,0(r3)

	e_lis     r3,rt_interrupt_from_thread@h
    e_or2i    r3,rt_interrupt_from_thread@l	/*r3是rt_interrupt_from_thread的地址*/
    e_lwz     r3,0(r3)						/*r3是rt_interrupt_from_thread的值。也就是SP的地址*/
	e_stw	  r1,0(r3)						/**rt_interrupt_from_thread=sp;*/

	e_lis     r4,rt_interrupt_to_thread@h
    e_or2i    r4,rt_interrupt_to_thread@l	/*R4此时是rt_interrupt_to_thread的地址*/
    e_lwz     r4,0(r4)						/*R1此时是rt_interrupt_to_thread,也就是SP的地址*/
    e_lwz     r1,0(r4)						/*R1此时是*rt_interrupt_to_thread，也就是SP的值*/
//出栈
_no_switch:
#if STACK_BALANCE_DEBUG==1
	e_lwz	r0,OFFSET_R1(r1)
	e_cmp16i	r0,0x1A2B
	e_beq	ivor4_stack_balance_success
ivor4_stack_balance_error:
	e_b		ivor4_stack_balance_error
ivor4_stack_balance_success:
#endif
	e_lwz	r0,OFFSET_MSR(r1)
	mtmsr	r0
	e_lwz	r0,OFFSET_SRR0(r1)
	mtsrr0	r0
	e_lwz	r0,OFFSET_SRR1(r1)
	mtsrr1	r0
	e_lwz	r0,OFFSET_XER(r1)
	mtxer	r0
	e_lwz	r0,OFFSET_CTR(r1)
	mtctr	r0
	e_lwz	r0,OFFSET_LR(r1)
	mtlr	r0
	e_lwz	r0,OFFSET_CR(r1)
	mtcr	r0
	e_lwz	r31,OFFSET_R31(r1)
	e_lwz	r30,OFFSET_R30(r1)
	e_lwz	r29,OFFSET_R29(r1)
	e_lwz	r28,OFFSET_R28(r1)
	e_lwz	r27,OFFSET_R27(r1)
	e_lwz	r26,OFFSET_R26(r1)
	e_lwz	r25,OFFSET_R25(r1)
	e_lwz	r24,OFFSET_R24(r1)
	e_lwz	r23,OFFSET_R23(r1)
	e_lwz	r22,OFFSET_R22(r1)
	e_lwz	r21,OFFSET_R21(r1)
	e_lwz	r20,OFFSET_R20(r1)
	e_lwz	r19,OFFSET_R19(r1)
	e_lwz	r18,OFFSET_R18(r1)
	e_lwz	r17,OFFSET_R17(r1)
	e_lwz	r16,OFFSET_R16(r1)
	e_lwz	r15,OFFSET_R15(r1)
	e_lwz	r14,OFFSET_R14(r1)
	e_lwz	r13,OFFSET_R13(r1)
	e_lwz	r12,OFFSET_R12(r1)
	e_lwz	r11,OFFSET_R11(r1)
	e_lwz	r9,OFFSET_R9(r1)
	e_lwz	r8,OFFSET_R8(r1)
	e_lwz	r7,OFFSET_R7(r1)
	e_lwz	r6,OFFSET_R6(r1)
	e_lwz	r5,OFFSET_R5(r1)
	e_lwz	r4,OFFSET_R4(r1)
	e_lwz	r3,OFFSET_R3(r1)
	e_lwz	r2,OFFSET_R2(r1)
	e_lwz	r0,OFFSET_R0(r1)
	e_addi	r1,r1,STACK_FRAME_SIZES
	//wrteei  1
	se_rfi
#endif
