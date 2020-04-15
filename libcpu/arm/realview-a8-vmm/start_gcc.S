/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-05     Bernard      the first version
 */

#include <rtconfig.h>

#ifdef RT_USING_VMM
#include <vmm.h>
.equ orig_irq_isr,    LINUX_VECTOR_POS+0x18
#else
#undef RT_VMM_USING_DOMAIN
#endif

.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80            @ when I bit is set, IRQ is disabled
.equ F_Bit,           0x40            @ when F bit is set, FIQ is disabled

#ifndef RT_USING_VMM
.equ UND_Stack_Size,     0x00000000
.equ SVC_Stack_Size,     0x00000100
.equ ABT_Stack_Size,     0x00000000
.equ RT_FIQ_STACK_PGSZ,  0x00000000
.equ RT_IRQ_STACK_PGSZ,  0x00000100
.equ USR_Stack_Size,     0x00000100

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 RT_FIQ_STACK_PGSZ + RT_IRQ_STACK_PGSZ)
#else
#define ISR_Stack_Size  (RT_FIQ_STACK_PGSZ + RT_IRQ_STACK_PGSZ)
#endif

.section .data.share.isr
/* stack */
.globl stack_start
.globl stack_top

.align 3
stack_start:
.rept ISR_Stack_Size
.byte 0
.endr
stack_top:

.text
/* reset entry */
.globl _reset
_reset:
#ifdef RT_USING_VMM
    /* save all the parameter and variable registers */
    stmfd   sp!, {r0-r12, lr}
#endif
    /* set the cpu to SVC32 mode and disable interrupt */
    mrs     r0, cpsr
    bic     r0, r0, #0x1f
    orr     r0, r0, #0x13
    msr     cpsr_c, r0

    /* setup stack */
    bl      stack_setup

    /* clear .bss */
    mov     r0,#0                   /* get a zero                       */
    ldr     r1,=__bss_start         /* bss start                        */
    ldr     r2,=__bss_end           /* bss end                          */

bss_loop:
    cmp     r1,r2                   /* check if data to clear           */
    strlo   r0,[r1],#4              /* clear 4 bytes                    */
    blo     bss_loop                /* loop until done                  */

#ifdef RT_USING_VMM
    /* clear .bss.share */
    mov     r0,#0                   /* get a zero                       */
    ldr     r1,=__bss_share_start   /* bss start                        */
    ldr     r2,=__bss_share_end     /* bss end                          */

bss_share_loop:
    cmp     r1,r2                   /* check if data to clear           */
    strlo   r0,[r1],#4              /* clear 4 bytes                    */
    blo     bss_share_loop                /* loop until done                  */
#endif

    /* call C++ constructors of global objects                          */
    ldr     r0, =__ctors_start__
    ldr     r1, =__ctors_end__

ctor_loop:
    cmp     r0, r1
    beq     ctor_end
    ldr     r2, [r0], #4
    stmfd   sp!, {r0-r1}
    mov     lr, pc
    bx      r2
    ldmfd   sp!, {r0-r1}
    b       ctor_loop
ctor_end:

    /* start RT-Thread Kernel */
#ifdef RT_USING_VMM
    /* restore the parameter */
    ldmfd   sp!, {r0-r3}
    bl      vmm_entry
    ldmfd   sp!, {r4-r12, pc}
#else
    ldr     pc, _rtthread_startup
_rtthread_startup:
    .word rtthread_startup
#endif

stack_setup:
    ldr     r0, =stack_top
#ifdef RT_USING_VMM
    @ Linux use stmia to save r0, lr and spsr. To align to 8 byte boundary,
    @ just allocate 16 bytes for it.
    sub     r0, r0, #16
#endif

#ifndef RT_USING_VMM
    @  Set the startup stack for svc
    mov     sp, r0
#endif

#ifndef RT_USING_VMM
    @  Enter Undefined Instruction Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_UND|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #UND_Stack_Size

    @  Enter Abort Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_ABT|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #ABT_Stack_Size
#endif

    @  Enter FIQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_FIQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #RT_FIQ_STACK_PGSZ

    @  Enter IRQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_IRQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #RT_IRQ_STACK_PGSZ

    /* come back to SVC mode */
    msr     cpsr_c, #Mode_SVC|I_Bit|F_Bit
    bx      lr

/* exception handlers: undef, swi, padt, dabt, resv, irq, fiq          */
.section .text.isr, "ax"
    .align  5
.globl vector_fiq
vector_fiq:
    stmfd   sp!,{r0-r7,lr}
    bl      rt_hw_trap_fiq
    ldmfd   sp!,{r0-r7,lr}
    subs    pc, lr, #4

.globl      rt_interrupt_enter
.globl      rt_interrupt_leave
.globl      rt_thread_switch_interrupt_flag
.globl      rt_interrupt_from_thread
.globl      rt_interrupt_to_thread

.globl      rt_current_thread
.globl      vmm_thread
.globl      vmm_virq_check

    .align  5
.globl vector_irq
vector_irq:
    stmfd   sp!, {r0-r12,lr}

#ifdef RT_VMM_USING_DOMAIN
    @ save the last domain
    mrc     p15, 0, r5, c3, c0
    @ switch to vmm domain as we are going to call vmm codes
    ldr     r1, =vmm_domain_val
    ldr     r4, [r1]
    mcr     p15, 0, r4, c3, c0
#endif

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

#ifdef RT_VMM_USING_DOMAIN
    @ restore the last domain. It do some redundant work but simplify the
    @ logic. It might be the guest domain so rt_thread_switch_interrupt_flag
    @ should lay in .bss.share
    mcr     p15, 0, r5, c3, c0
#endif

    @ if rt_thread_switch_interrupt_flag set, jump to
    @ rt_hw_context_switch_interrupt_do and don't return
    ldr     r0, =rt_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq     rt_hw_context_switch_interrupt_do

#ifndef RT_USING_VMM
    ldmfd   sp!, {r0-r12,lr}
    subs    pc,  lr, #4
#else
#ifdef RT_VMM_USING_DOMAIN
    @ r4 is vmm_domain_val
    @ back to vmm domain as we need access rt_current_thread
    mcr     p15, 0, r4, c3, c0
#endif
    /* check whether we need to do IRQ routing
     * ensure the int is disabled. Or there will be an infinite loop. */
    ldr     r0, =rt_current_thread
    ldr     r0, [r0]
    ldr     r1, =vmm_thread
    cmp     r0, r1
    beq     switch_to_guest

#ifdef RT_VMM_USING_DOMAIN
    @ r5 is domain of interrupted context
    @ it might be super_domain_val or vmm_domain_val so we need to restore it.
    mcr     p15, 0, r5, c3, c0
#endif
    @ switch back if the interrupted thread is not vmm
    ldmfd sp!, {r0-r12,lr}
    subs  pc, lr, #4

switch_to_guest:
#ifdef RT_VMM_USING_DOMAIN
    @ We are going to execute rt-thread code but accessing the content of the
    @ guest. So switch to super domain.
    ldr     r1, =super_domain_val
    ldr     r0, [r1]
    mcr     p15, 0, r0, c3, c0
#endif
	/* check whether there is a pending interrupt for Guest OS */
	bl      vmm_virq_check

#ifdef RT_VMM_USING_DOMAIN
    @ All done, restore the guest domain.
    mcr     p15, 0, r5, c3, c0
#endif

	cmp     r0, #0x0
	beq     route_irq_to_guest

    ldmfd   sp!, {r0-r12,lr}
    subs    pc, lr, #4

route_irq_to_guest:
    ldmfd   sp!, {r0-r12,lr}
    b       orig_irq_isr
#endif /* RT_USING_VMM */

rt_hw_context_switch_interrupt_do:
    mov     r1,  #0         @ clear flag
    str     r1,  [r0]

    mov     r1, sp          @ r1 point to {r0-r3} in stack
    add     sp, sp, #4*4
    ldmfd   sp!, {r4-r12,lr}@ reload saved registers
    mrs     r0,  spsr       @ get cpsr of interrupt thread
    sub     r2,  lr, #4     @ save old task's pc to r2

    @ Switch to SVC mode with no interrupt. If the usr mode guest is
    @ interrupted, this will just switch to the stack of kernel space.
    @ save the registers in kernel space won't trigger data abort.
    msr     cpsr_c, #I_Bit|F_Bit|Mode_SVC

    stmfd   sp!, {r2}       @ push old task's pc
    stmfd   sp!, {r4-r12,lr}@ push old task's lr,r12-r4
    ldmfd   r1,  {r1-r4}    @ restore r0-r3 of the interrupt thread
    stmfd   sp!, {r1-r4}    @ push old task's r0-r3
    stmfd   sp!, {r0}       @ push old task's cpsr

    ldr     r4,  =rt_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]       @ store sp in preempted tasks's TCB

#ifdef RT_VMM_USING_DOMAIN
    @ If a thread is wake up by interrupt, it should be RTT thread.
    @ Make sure the domain is correct.
    ldr     r1, =vmm_domain_val
    ldr     r2, [r1]
    mcr     p15, 0, r2, c3, c0
#endif
    ldr     r6,  =rt_interrupt_to_thread
    ldr     r6,  [r6]
    ldr     sp,  [r6]       @ get new task's stack pointer

    ldmfd   sp!, {r4}       @ pop new task's cpsr to spsr
    msr     spsr_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr

.macro push_svc_reg
    sub     sp, sp, #17 * 4         @/* Sizeof(struct rt_hw_exp_stack)  */
    stmia   sp, {r0 - r12}          @/* Calling r0-r12                  */
    mov     r0, sp
    mrs     r6, spsr                @/* Save CPSR                       */
    str     lr, [r0, #15*4]         @/* Push PC                         */
    str     r6, [r0, #16*4]         @/* Push CPSR                       */
    cps     #Mode_SVC
    str     sp, [r0, #13*4]         @/* Save calling SP                 */
    str     lr, [r0, #14*4]         @/* Save calling PC                 */
.endm

    .align  5
    .globl	vector_swi
vector_swi:
    push_svc_reg
    bl      rt_hw_trap_swi
    b       .

    .align  5
    .globl	vector_undef
vector_undef:
    push_svc_reg
    bl      rt_hw_trap_undef
    b       .

    .align  5
    .globl	vector_pabt
vector_pabt:
    push_svc_reg
    bl      rt_hw_trap_pabt
    b       .

    .align  5
    .globl	vector_dabt
vector_dabt:
    push_svc_reg
    bl      rt_hw_trap_dabt
    b       .

    .align  5
    .globl	vector_resv
vector_resv:
    push_svc_reg
    bl      rt_hw_trap_resv
    b       .
