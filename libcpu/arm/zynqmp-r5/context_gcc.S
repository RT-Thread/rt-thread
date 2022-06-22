/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19     WangHuachen  first version
 */

.section .text, "ax"
/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mrs r0, cpsr
    cpsid if
    bx  lr

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    msr cpsr, r0
    bx  lr

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    ldr sp, [r0]            @ get new task stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}             /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    ldmfd sp!, {r4}         @ pop new task spsr
    msr spsr_cxsf, r4

    ldmfd sp!, {r0-r12, lr, pc}^   @ pop new task r0-r12, lr & pc


.section .text.isr, "ax"
/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    stmfd   sp!, {lr}       @ push pc (lr should be pushed in place of PC)
    stmfd   sp!, {r0-r12, lr}   @ push lr & register file

    mrs r4, cpsr
    tst lr, #0x01
    beq _ARM_MODE
    orr r4, r4, #0x20       @ it's thumb code

_ARM_MODE:
    stmfd sp!, {r4}         @ push cpsr

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    vstmdb sp!, {d0-d15}     /* Store floating point registers */
    vmrs r4, FPSCR
    stmfd sp!,{r4}
    vmrs r4, FPEXC
    stmfd sp!,{r4}
#endif

    str sp, [r0]            @ store sp in preempted tasks TCB
    ldr sp, [r1]            @ get new task stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}             /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    ldmfd sp!, {r4}         @ pop new task cpsr to spsr
    msr spsr_cxsf, r4

    ldmfd sp!, {r0-r12, lr, pc}^  @ pop new task r0-r12, lr & pc, copy spsr to cpsr

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    ldr r2, =rt_thread_switch_interrupt_flag
    ldr r3, [r2]
    cmp r3, #1
    beq _reswitch
    mov r3, #1              @ set rt_thread_switch_interrupt_flag to 1
    str r3, [r2]
    ldr r2, =rt_interrupt_from_thread   @ set rt_interrupt_from_thread
    str r0, [r2]
_reswitch:
    ldr r2, =rt_interrupt_to_thread     @ set rt_interrupt_to_thread
    str r1, [r2]
    bx  lr
