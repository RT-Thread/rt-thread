/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-05     Bernard      the first version
 * 2019-07-28     zdzn         add smp support
 */

#include "../rtconfig.h"
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
 * void rt_hw_context_switch_to(rt_uint32 to, struct rt_thread *to_thread);
 * r0 --> to (thread stack)
 * r1 --> to_thread
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    ldr sp, [r0]            @ get new task stack pointer

#ifdef RT_USING_SMP
    mov     r0, r1
    bl      rt_cpus_lock_status_restore
#endif /*RT_USING_SMP*/
    b       rt_hw_context_switch_exit

.section .bss.share.isr
_guest_switch_lvl:
    .word 0

.globl vmm_virq_update

.section .text.isr, "ax"
/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to, struct rt_thread *to_thread);
 * r0 --> from (from_thread stack)
 * r1 --> to (to_thread stack)
 * r2 --> to_thread
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    stmfd   sp!, {lr}       @ push pc (lr should be pushed in place of PC)
    stmfd   sp!, {r0-r12, lr}   @ push lr & register file

    mrs r4, cpsr
    tst lr, #0x01
    orrne r4, r4, #0x20     @ it's thumb code

    stmfd sp!, {r4}         @ push cpsr

#ifdef RT_USING_LWP
    stmfd sp, {r13, r14}^   @ push usr_sp usr_lr
    sub sp, #8
#endif
#ifdef RT_USING_FPU
    /* fpu context */
    vmrs r6, fpexc
    tst  r6, #(1<<30)
    beq 1f
    vstmdb sp!, {d0-d15}
    vstmdb sp!, {d16-d31}
    vmrs r5, fpscr
    stmfd sp!, {r5}
1:
    stmfd sp!, {r6}
#endif

    str sp, [r0]            @ store sp in preempted tasks TCB
    ldr sp, [r1]            @ get new task stack pointer

#ifdef RT_USING_SMP
    mov     r0, r2
    bl      rt_cpus_lock_status_restore
#endif /*RT_USING_SMP*/
    b       rt_hw_context_switch_exit

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
    /* r0 :svc_mod context
     * r1 :addr of from_thread's sp
     * r2 :addr of to_thread's sp
     * r3 :to_thread's tcb
     */

    str     r0, [r1]

    ldr     sp, [r2]
    mov     r0, r3
    bl      rt_cpus_lock_status_restore

    b       rt_hw_context_switch_exit

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

.global rt_hw_context_switch_exit
rt_hw_context_switch_exit:

#ifdef RT_USING_SMP
#ifdef RT_USING_SIGNALS
    mov     r0, sp
    cps #Mode_IRQ
    bl      rt_signal_check
    cps #Mode_SVC
    mov     sp, r0
#endif
#endif
#ifdef RT_USING_FPU
/* fpu context */
    ldmfd sp!, {r6}
    vmsr fpexc, r6
    tst  r6, #(1<<30)
    beq 1f
    ldmfd sp!, {r5}
    vmsr fpscr, r5
    vldmia sp!, {d16-d31}
    vldmia sp!, {d0-d15}

#endif

#ifdef RT_USING_LWP
    ldmfd   sp, {r13, r14}^ /* usr_sp, usr_lr */
    add     sp, #8
#endif
    ldmfd   sp!, {r4}
    msr     spsr_cxsf, r4        /* original mode */
    ldmfd   sp!, {r0-r12,lr,pc}^ /* irq return */

