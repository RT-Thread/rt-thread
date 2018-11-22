/*
 * File      : context.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
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
 * 2013-07-05     Bernard      the first version
 * 2018-11-22     Jesven       in the smp version, using macro to
 *                             define rt_hw_interrupt_enable and rt_hw_interrupt_disable
 *                             rt_hw_context_switch_interrupt switches to the new thread directly
 */

#include "rtconfig.h"
.section .text, "ax"

#ifdef RT_USING_SMP
#define rt_hw_interrupt_disable rt_hw_local_irq_disable
#define rt_hw_interrupt_enable  rt_hw_local_irq_enable
#endif

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mrs r0, cpsr
    cpsid i
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

#ifdef RT_USING_SMP
    mov     r0, r1
    bl      rt_cpus_lock_status_restore
#endif /*RT_USING_SMP*/

    ldmfd sp!, {r4}         @ pop new task spsr
    msr spsr_cxsf, r4

    ldmfd sp!, {r0-r12, lr, pc}^   @ pop new task r0-r12, lr & pc

.section .bss.share.isr
_guest_switch_lvl:
    .word 0

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
    orrne r4, r4, #0x20     @ it's thumb code

    stmfd sp!, {r4}         @ push cpsr

    str sp, [r0]            @ store sp in preempted tasks TCB
    ldr sp, [r1]            @ get new task stack pointer

#ifdef RT_USING_SMP
    mov     r0, r2
    bl      rt_cpus_lock_status_restore
#endif /*RT_USING_SMP*/

    ldmfd sp!, {r4}         @ pop new task cpsr to spsr
    msr spsr_cxsf, r4
    ldmfd sp!, {r0-r12, lr, pc}^  @ pop new task r0-r12, lr & pc, copy spsr to cpsr

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80            @ when I bit is set, IRQ is disabled
.equ F_Bit,           0x40            @ when F bit is set, FIQ is disabled

.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
#ifdef RT_USING_SMP
    /* r0 :irq_mod context
     * r1 :addr of from_thread's sp
     * r2 :addr of to_thread's sp
     * r3 :to_thread's tcb
     */

    @ r0 point to {r0-r3} in stack
    push    {r1 - r3}
    mov     r1, r0
    add     r0, r0, #4*4
    ldmfd   r0!, {r4-r12,lr}@ reload saved registers
    mrs     r3,  spsr       @ get cpsr of interrupt thread
    sub     r2,  lr, #4     @ save old task's pc to r2
    msr     cpsr_c, #I_Bit|F_Bit|Mode_SVC

    stmfd   sp!, {r2}       @ push old task's pc
    stmfd   sp!, {r4-r12,lr}@ push old task's lr,r12-r4
    ldmfd   r0,  {r4-r7}    @ restore r0-r3 of the interrupt thread
    stmfd   sp!, {r4-r7}    @ push old task's r0-r3
    stmfd   sp!, {r3}       @ push old task's cpsr

    msr     cpsr_c, #I_Bit|F_Bit|Mode_IRQ
    pop     {r1 - r3}
    mov     sp, r0
    msr     cpsr_c, #I_Bit|F_Bit|Mode_SVC
    str     sp, [r1]

    ldr     sp, [r2]
    mov     r0, r3
    bl      rt_cpus_lock_status_restore

    ldmfd   sp!, {r4}       @ pop new task's cpsr to spsr
    msr     spsr_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr

#else /*RT_USING_SMP*/
    ldr r2, =rt_thread_switch_interrupt_flag
    ldr r3, [r2]
    cmp r3, #1
    beq _reswitch
    ldr ip, =rt_interrupt_from_thread   @ set rt_interrupt_from_thread
    mov r3, #1              @ set rt_thread_switch_interrupt_flag to 1
    str r0, [ip]
    str r3, [r2]
_reswitch:
    ldr r2, =rt_interrupt_to_thread     @ set rt_interrupt_to_thread
    str r1, [r2]
    bx  lr
#endif /*RT_USING_SMP*/
