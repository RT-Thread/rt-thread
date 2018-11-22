/*
 * File      : start_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2014, RT-Thread Development Team
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
 * 2018-11-22     Jesven       in the interrupt context, use rt_scheduler_do_irq_switch checks
 *                             and switches to a new thread
 */

#include "rtconfig.h"

.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80            @ when I bit is set, IRQ is disabled
.equ F_Bit,           0x40            @ when F bit is set, FIQ is disabled

.equ UND_Stack_Size,     0x00000000
.equ SVC_Stack_Size,     0x00000400
.equ ABT_Stack_Size,     0x00000000
.equ RT_FIQ_STACK_PGSZ,  0x00000000
.equ RT_IRQ_STACK_PGSZ,  0x00000800
.equ USR_Stack_Size,     0x00000400

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 RT_FIQ_STACK_PGSZ + RT_IRQ_STACK_PGSZ)

.section .data.share.isr
/* stack */
.globl stack_start
.globl stack_top

stack_start:
.rept ISR_Stack_Size
.byte 0
.endr
stack_top:

.text
/* reset entry */
.globl _reset
_reset:
    /* set the cpu to SVC32 mode and disable interrupt */
    mrs     r0, cpsr
    bic     r0, r0, #0x1f
    orr     r0, r0, #0x13
    msr     cpsr_c, r0

    mrc p15, 0, r1, c1, c0, 1
    mov r0, #(1<<6)
    orr r1, r0
    mcr p15, 0, r1, c1, c0, 1 //enable smp

    ldr lr, =after_enable_mmu
    ldr r0, =mtbl
    b enable_mmu

after_enable_mmu:

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
    bl      flush_cache_all
    ldr     pc, _rtthread_startup
_rtthread_startup:
    .word rtthread_startup

stack_setup:
    ldr     r0, =stack_top

    @  Set the startup stack for svc
    mov     sp, r0

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
    sub     r0, r0, #RT_FIQ_STACK_PGSZ

    @  Enter IRQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_IRQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #RT_IRQ_STACK_PGSZ

    /* come back to SVC mode */
    msr     cpsr_c, #Mode_SVC|I_Bit|F_Bit
    bx      lr

    .global enable_mmu
enable_mmu:
    orr r0, #0x18
    mcr p15, 0, r0, c2, c0, 0 @ttbr0

    mov r0, #(1 << 5)         @PD1=1
    mcr p15, 0, r0, c2, c0, 2 @ttbcr

    mov r0, #1
    mcr p15, 0, r0, c3, c0, 0 @dacr

    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    mcr p15, 0, r0, c7, c5, 0 @iciallu
    mcr p15, 0, r0, c7, c5, 6 @bpiall

    mrc p15, 0, r0, c1, c0, 0
    orr r0, #(1 | 4)
    orr r0, #(1 << 12)
    mcr p15, 0, r0, c1, c0, 0
    dsb
    isb
    mov pc, lr

.global flush_cache_all
flush_cache_all:
    stmfd   sp!, {r0-r12, lr}
    bl  v7_flush_dcache_all
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0       @ I+BTB cache invalidate
    dsb
    isb
    ldmfd   sp!, {r0-r12, lr}
    mov pc, lr

    v7_flush_dcache_all:
    dmb                 @ ensure ordering with previous memory accesses
    mrc p15, 1, r0, c0, c0, 1       @ read clidr
    ands    r3, r0, #0x7000000      @ extract loc from clidr
    mov r3, r3, lsr #23         @ left align loc bit field
    beq finished            @ if loc is 0, then no need to clean
    mov r10, #0             @ start clean at cache level 0
loop1:
    add r2, r10, r10, lsr #1        @ work out 3x current cache level
    mov r1, r0, lsr r2          @ extract cache type bits from clidr
    and r1, r1, #7          @ mask of the bits for current cache only
    cmp r1, #2              @ see what cache we have at this level
    blt skip                @ skip if no cache, or just i-cache
    mcr p15, 2, r10, c0, c0, 0      @ select current cache level in cssr
    isb                 @ isb to sych the new cssr&csidr
    mrc p15, 1, r1, c0, c0, 0       @ read the new csidr
    and r2, r1, #7          @ extract the length of the cache lines
    add r2, r2, #4          @ add 4 (line length offset)
    ldr r4, =0x3ff
    ands    r4, r4, r1, lsr #3      @ find maximum number on the way size
    clz r5, r4              @ find bit position of way size increment
    ldr r7, =0x7fff
    ands    r7, r7, r1, lsr #13     @ extract max number of the index size
loop2:
    mov r9, r4              @ create working copy of max way size
loop3:
    orr r11, r10, r9, lsl r5        @ factor way and cache number into r11
    orr r11, r11, r7, lsl r2        @ factor index number into r11
    mcr p15, 0, r11, c7, c14, 2     @ clean & invalidate by set/way
    subs    r9, r9, #1          @ decrement the way
    bge loop3
    subs    r7, r7, #1          @ decrement the index
    bge loop2
skip:
    add r10, r10, #2            @ increment cache number
    cmp r3, r10
    bgt loop1
finished:
    mov r10, #0             @ swith back to cache level 0
    mcr p15, 2, r10, c0, c0, 0      @ select current cache level in cssr
    dsb
    isb
    mov pc, lr

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

    .align  5
.globl vector_irq
vector_irq:
#ifdef RT_USING_SMP
    clrex
#endif
    stmfd   sp!, {r0-r12,lr}

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

#ifdef RT_USING_SMP
    mov     r0, sp
    bl      rt_scheduler_do_irq_switch

    ldmfd   sp!, {r0-r12,lr}
    subs    pc,  lr, #4
#else
    @ if rt_thread_switch_interrupt_flag set, jump to
    @ rt_hw_context_switch_interrupt_do and don't return
    ldr     r0, =rt_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq     rt_hw_context_switch_interrupt_do

    ldmfd   sp!, {r0-r12,lr}
    subs    pc,  lr, #4

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

    ldr     r6,  =rt_interrupt_to_thread
    ldr     r6,  [r6]
    ldr     sp,  [r6]       @ get new task's stack pointer

    ldmfd   sp!, {r4}       @ pop new task's cpsr to spsr
    msr     spsr_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr

#endif

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
    .globl  vector_swi
vector_swi:
    push_svc_reg
    bl      rt_hw_trap_swi
    b       .

    .align  5
    .globl  vector_undef
vector_undef:
    push_svc_reg
    bl      rt_hw_trap_undef
    b       .

    .align  5
    .globl  vector_pabt
vector_pabt:
    push_svc_reg
    bl      rt_hw_trap_pabt
    b       .

    .align  5
    .globl  vector_dabt
vector_dabt:
    push_svc_reg
    bl      rt_hw_trap_dabt
    b       .

    .align  5
    .globl  vector_resv
vector_resv:
    push_svc_reg
    bl      rt_hw_trap_resv
    b       .

#ifdef RT_USING_SMP
.global set_secondary_cpu_boot_address
set_secondary_cpu_boot_address:
    ldr r0, =secondary_cpu_start

    mvn r1, #0 //0xffffffff
    ldr r2, =0x10000034
    str r1, [r2]
    str r0, [r2, #-4]
    mov pc, lr

.global secondary_cpu_start
secondary_cpu_start:
    mrc p15, 0, r1, c1, c0, 1
    mov r0, #(1<<6)
    orr r1, r0
    mcr p15, 0, r1, c1, c0, 1 //enable smp

    ldr r0, =mtbl
    ldr lr, =1f

    b enable_mmu
1:
    mrc p15, 0, r0, c1, c0, 0
    bic r0, #(1<<13)
    mcr p15, 0, r0, c1, c0, 0

    cps #Mode_IRQ
    ldr sp, =irq_stack_2_limit

    cps #Mode_FIQ
    ldr sp, =irq_stack_2_limit

    cps #Mode_SVC
    ldr sp, =svc_stack_2_limit

    b secondary_cpu_c_start
#endif

.bss
.align 2   //align to  2~2=4
svc_stack_2:
    .space (1 << 10)
svc_stack_2_limit:

irq_stack_2:
    .space (1 << 10)
irq_stack_2_limit:

.data
#define DEVICE_MEM  0x10406
#define NORMAL_MEM  0x1140e
.align 14
mtbl:

    //vaddr: 0x00000000
    .rept 0x100
    .word 0x0
    .endr

    //vaddr: 0x10000000
    .equ mmu_tbl_map_paddr, 0x10000000
    .rept 0x400
    .word mmu_tbl_map_paddr | DEVICE_MEM
    .equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
    .endr

    //vaddr: 0x50000000
    .rept 0x100
    .word 0x0
    .endr

    //vaddr: 0x60000000
    .equ mmu_tbl_map_paddr, 0x60000000
    .rept 0x800
    .word mmu_tbl_map_paddr | NORMAL_MEM
    .equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
    .endr

    //vaddr: 0xe0000000
    .rept 0x200
    .word 0x0
    .endr
