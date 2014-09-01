/*
 * File      : start_gcc.S
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

.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80            @ when I bit is set, IRQ is disabled
.equ F_Bit,           0x40            @ when F bit is set, FIQ is disabled

.equ UND_Stack_Size,  0x00000000
.equ SVC_Stack_Size,  0x00000100
.equ ABT_Stack_Size,  0x00000000
.equ FIQ_Stack_Size,  0x00000000
.equ IRQ_Stack_Size,  0x00000100
.equ USR_Stack_Size,  0x00000100

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 FIQ_Stack_Size + IRQ_Stack_Size)

/* stack */
.globl stack_start
.globl stack_top

stack_start:
.rept ISR_Stack_Size
.long 0
.endr
stack_top:

/* reset entry */
.globl _reset
_reset:
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
    ldr     pc, _rtthread_startup
_rtthread_startup:
    .word rtthread_startup

stack_setup:
    ldr     r0, =stack_top

    @  Enter Undefined Instruction Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_UND|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #UND_Stack_Size

    @  Enter Abort Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_ABT|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #ABT_Stack_Size

    @  Enter FIQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_FIQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #FIQ_Stack_Size

    @  Enter IRQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_IRQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #IRQ_Stack_Size

    @  Enter Supervisor Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_SVC|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #SVC_Stack_Size

    @  Enter User Mode and set its Stack Pointer
    mov     sp, r0
    sub     sl, sp, #USR_Stack_Size
    bx      lr

/* exception handlers: undef, swi, padt, dabt, resv, irq, fiq          */
    .align  5
.globl vector_undef
vector_undef:
    sub     sp, sp, #72
    stmia   sp, {r0 - r12}          @/* Calling r0-r12                  */
    add     r8, sp, #60
    stmdb   r8, {sp, lr}            @/* Calling SP, LR                  */
    str     lr, [r8, #0]            @/* Save calling PC                 */
    mrs     r6, spsr
    str     r6, [r8, #4]            @/* Save CPSR                       */
    str     r0, [r8, #8]            @/* Save OLD_R0                     */
    mov     r0, sp

    bl      rt_hw_trap_udef

    .align  5
.globl vector_swi
vector_swi:
    bl      rt_hw_trap_swi

    .align	5
.globl vector_pabt
vector_pabt:
    bl      rt_hw_trap_pabt

    .align  5
.globl vector_dabt
vector_dabt:
    sub     sp, sp, #72
    stmia   sp, {r0 - r12}          @/* Calling r0-r12                  */
    add     r8, sp, #60
    stmdb   r8, {sp, lr}            @/* Calling SP, LR                  */
    str     lr, [r8, #0]            @/* Save calling PC                 */
    mrs     r6, spsr
    str     r6, [r8, #4]            @/* Save CPSR                       */
    str     r0, [r8, #8]            @/* Save OLD_R0                     */
    mov     r0, sp

    bl      rt_hw_trap_dabt

    .align 5
.globl vector_resv
vector_resv:
    b       .

    .align  5
.globl vector_fiq
vector_fiq:
    stmfd   sp!,{r0-r7,lr}
    bl      rt_hw_trap_fiq
    ldmfd   sp!,{r0-r7,lr}
    subs    pc,lr,#4

.globl      rt_interrupt_enter
.globl      rt_interrupt_leave
.globl      rt_thread_switch_interrupt_flag
.globl      rt_interrupt_from_thread
.globl      rt_interrupt_to_thread

.globl      rt_current_thread
.globl      vmm_thread
.globl      vmm_virq_check

.globl vector_irq
vector_irq:
    stmfd   sp!, {r0-r12,lr}

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

    @ if rt_thread_switch_interrupt_flag set, jump to
    @ rt_hw_context_switch_interrupt_do and don't return
    ldr     r0, =rt_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq     rt_hw_context_switch_interrupt_do

    ldmfd   sp!, {r0-r12,lr}
    subs    pc, lr, #4

rt_hw_context_switch_interrupt_do:
    mov     r1,  #0         @ clear flag
    str     r1,  [r0]

    ldmfd   sp!, {r0-r12,lr}@ reload saved registers
    stmfd   sp,  {r0-r2}    @ save r0-r2

    mrs     r0,  spsr       @ get cpsr of interrupt thread

    sub     r1,  sp, #4*3
    sub     r2,  lr, #4     @ save old task's pc to r2

    @ switch to SVC mode with no interrupt
    msr     cpsr_c, #I_Bit|F_Bit|Mode_SVC

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

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr
