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
 */

#include <rtconfig.h>

#ifdef RT_USING_VMM
#include <vmm.h>
#endif

.section .text, "ax"
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

    ldmfd sp!, {r4}         @ pop new task spsr
    msr spsr_cxsf, r4

    ldmfd sp!, {r0-r12, lr, pc}^   @ pop new task r0-r12, lr & pc

.section .bss.share.isr
_guest_switch_lvl:
    .word 0

.globl vmm_virq_update

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

#ifdef RT_USING_VMM
#ifdef RT_VMM_USING_DOMAIN
    @ need to make sure we are in vmm domain as we would use rt_current_thread
    ldr     r2, =vmm_domain_val
    ldr     r7, [r2]
    mcr     p15, 0, r7, c3, c0
#endif

    /* check whether vmm thread, otherwise, update vIRQ */
    ldr     r3, =rt_current_thread
    ldr     r4, [r3]
    ldr     r5, =vmm_thread
    cmp     r4, r5
    beq     switch_to_guest

    @ not falling into guest. Simple task ;-)
    ldmfd sp!, {r6}         @ pop new task cpsr to spsr
    msr spsr_cxsf, r6
    ldmfd sp!, {r0-r12, lr, pc}^

switch_to_guest:
#ifdef RT_VMM_USING_DOMAIN
    @ the stack is saved in the guest domain so we need to
    @ come back to the guest domain to get the registers.
    ldr     r1, =super_domain_val
    ldr     r0, [r1]
    mcr     p15, 0, r0, c3, c0
#endif
    /* The user can do nearly anything in rt_thread_idle_excute because it will
    call the thread->cleanup. One common thing is sending events and wake up
    threads. So the guest thread will be preempted. This is the only point that
    the guest thread would call rt_hw_context_switch and "yield".

    More over, rt_schedule will call this function and this function *will*
    reentrant. If that happens, we need to make sure that call the
    rt_thread_idle_excute and vmm_virq_update again and we are in super domain.
    I use a "reference count" to achieve such behaviour. If you have better
    idea, tell me. */
    ldr     r4, =_guest_switch_lvl
    ldr     r5, [r4]
    add     r5, r5, #1
    str     r5, [r4]
    cmp     r5, #1
    bne     _switch_through

    bl      rt_thread_idle_excute
    bl      vmm_virq_update

    /* we need _guest_switch_lvl to protect until _switch_through, but it's OK
     * to cleanup the reference count here because the code below will not be
     * reentrant. */
    sub     r5, r5, #1
    str     r5, [r4]

#ifdef RT_VMM_USING_DOMAIN
    ldr     r1, =guest_domain_val
    ldr     r0, [r1]
    mcr     p15, 0, r0, c3, c0
#endif
_switch_through:
#endif /* RT_USING_VMM */
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
    ldr ip, =rt_interrupt_from_thread   @ set rt_interrupt_from_thread
    mov r3, #1              @ set rt_thread_switch_interrupt_flag to 1
    str r0, [ip]
    str r3, [r2]
_reswitch:
    ldr r2, =rt_interrupt_to_thread     @ set rt_interrupt_to_thread
    str r1, [r2]
    bx  lr
