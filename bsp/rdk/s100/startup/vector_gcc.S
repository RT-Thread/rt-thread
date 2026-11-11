/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-05     Bernard      the first version
 */
 
.macro push_svc_reg pc_adjust
    sub     sp, sp, #17 * 4         @/* Sizeof(struct rt_hw_exp_stack)  */
    stmia   sp, {r0 - r12}          @/* Calling r0-r12                  */
    mov     r0, sp
    mrs     r6, spsr                @/* Save CPSR                       */
    sub     r5, lr, #\pc_adjust
    str     r5, [r0, #15*4]         @/* Push fault PC                   */
    str     r6, [r0, #16*4]         @/* Push CPSR                       */
    cps     #0x13                   @/* Switch to SVC mode               */
    str     sp, [r0, #13*4]         @/* Save calling SP                 */
    str     lr, [r0, #14*4]         @/* Save calling PC                 */
.endm

/*
    * EL2 exceptions are unexpected in the normal RT-Thread runtime because
    * the core has already descended into EL1. Keep the SDK policy simple:
    * capture a minimal register frame for diagnostics, then stop.
    */
.macro push_hyp_reg pc_adjust
    mov     r7, sp
    sub     sp, sp, #17 * 4
    stmia   sp, {r0 - r12}
    mov     r0, sp
    str     r7, [r0, #13*4]
    str     lr, [r0, #14*4]
    sub     r6, lr, #\pc_adjust
    str     r6, [r0, #15*4]
    mrs     r6, spsr
    str     r6, [r0, #16*4]
.endm

.globl SWI_Handler
SWI_Handler:
    push_svc_reg 4
    bl      rt_hw_trap_swi
    b       .

.globl Undefined_Handler
Undefined_Handler:
    push_svc_reg 4
	bl	rt_hw_trap_undef
    b   .

.globl SVC_Handler
SVC_Handler:
	push_svc_reg 4
	b	rt_hw_trap_svc
    b   .

.globl Prefetch_Handler
Prefetch_Handler:
    push_svc_reg 4
	b	rt_hw_trap_pabt
    b   .

.globl Abort_Handler
Abort_Handler:
    push_svc_reg 8
	b	rt_hw_trap_dabt
    b   .

.globl Reserved_Handler
Reserved_Handler:
    push_svc_reg 4
	b	rt_hw_trap_resv
    b   .

.globl FIQ_Handler
FIQ_Handler:
    stmdb   sp!, {r0-r12, lr}

#ifdef RT_USING_FPU
    vmrs    r0, fpexc
    tst     r0, #0x40000000
    beq     __no_vfp_frame_str_fiq
    vstmdb  sp!, {d0-d15}
    vmrs    r1, fpscr
    stmdb   sp!, {r1}
__no_vfp_frame_str_fiq:
    stmdb   sp!, {r0}
#endif

    bl      rt_interrupt_enter
    bl      rt_hw_trap_fiq
    bl      rt_interrupt_leave

#ifdef RT_USING_FPU
    ldmia   sp!, {r0}
    vmsr    fpexc, r0
    tst     r0, #0x40000000
    beq     __no_vfp_frame_ldr_fiq
    ldmia   sp!, {r1}
    vmsr    fpscr, r1
    vldmia  sp!, {d0-d15}
__no_vfp_frame_ldr_fiq:
#endif

    ldmia   sp!, {r0-r12, lr}
    subs    pc, lr, #4

.globl EL2_Undefined_Handler
EL2_Undefined_Handler:
    push_hyp_reg 4
    mov r1, #0
    b   .

.globl EL2_Prefetch_Handler
EL2_Prefetch_Handler:
    push_hyp_reg 4
    mov r1, #1
    b   .

.globl EL2_Abort_Handler
EL2_Abort_Handler:
    push_hyp_reg 8
    mov r1, #2
    b   .

.globl EL2_IRQ_Handler
EL2_IRQ_Handler:
    push_hyp_reg 4
    mov r1, #3
    b   .

.globl EL2_FIQ_Handler
EL2_FIQ_Handler:
    push_hyp_reg 4
    mov r1, #4
    b   .

.globl  EL2_HVC_Handler
EL2_HVC_Handler:
    push_hyp_reg 4
    mov r1, #5
    b   .

.globl  EL2_Trap_Handler
EL2_Trap_Handler:
    push_hyp_reg 4
    mov r1, #6
    b   .
