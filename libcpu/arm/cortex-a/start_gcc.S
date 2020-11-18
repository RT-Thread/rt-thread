/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

.equ UND_Stack_Size,     0x00000400
.equ SVC_Stack_Size,     0x00000400
.equ ABT_Stack_Size,     0x00000400
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

#ifdef RT_USING_USERSPACE
.data
.align 14
init_mtbl:
    .space 16*1024
#endif

.text
/* reset entry */
.globl _reset
_reset:
#ifdef ARCH_ARMV8
    /* Check for HYP mode */
    mrs r0, cpsr_all
    and r0, r0, #0x1F
    mov r8, #0x1A
    cmp r0, r8
    beq overHyped
    b continue

overHyped: /* Get out of HYP mode */
    adr r1, continue
    msr ELR_hyp, r1
    mrs r1, cpsr_all
    and r1, r1, #0x1f    ;@ CPSR_MODE_MASK
    orr r1, r1, #0x13    ;@ CPSR_MODE_SUPERVISOR
    msr SPSR_hyp, r1
    eret

continue:
#endif

#ifdef SOC_BCM283x
    /* Suspend the other cpu cores */
    mrc p15, 0, r0, c0, c0, 5
    ands r0, #3
    bne _halt

    /* Disable IRQ & FIQ */
    cpsid if

    /* Check for HYP mode */
    mrs r0, cpsr_all
    and r0, r0, #0x1F
    mov r8, #0x1A
    cmp r0, r8
    beq overHyped
    b continue

overHyped: /* Get out of HYP mode */
    adr r1, continue
    msr ELR_hyp, r1
    mrs r1, cpsr_all
    and r1, r1, #0x1f    ;@ CPSR_MODE_MASK
    orr r1, r1, #0x13    ;@ CPSR_MODE_SUPERVISOR
    msr SPSR_hyp, r1
    eret

continue:
    /* set the cpu to SVC32 mode and disable interrupt */
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x13
    msr cpsr_c, r0
#endif

#ifdef RT_USING_USERSPACE
    ldr r5, =PV_OFFSET

    mov r7, #0x100000
    sub r7, #1
    mvn r8, r7

    ldr r9, =KERNEL_VADDR_START

    ldr r6, =__bss_end
    add r6, r7
    and r6, r8 //r6 end vaddr align up to 1M
    sub r6, r9 //r6 is size

    ldr sp, =stack_top
    add sp, r5 //use paddr

    ldr r0, =init_mtbl
    add r0, r5
    mov r1, r6
    mov r2, r5
    bl init_mm_setup

    ldr lr, =after_enable_mmu
    ldr r0, =init_mtbl
    add r0, r5
    b enable_mmu

after_enable_mmu:
#endif
#ifndef SOC_BCM283x
    /* set the cpu to SVC32 mode and disable interrupt */
    cps #Mode_SVC
#endif

#ifdef RT_USING_FPU
    mov r4, #0xfffffff
    mcr p15, 0, r4, c1, c0, 2
#endif

    /* disable the data alignment check */
    mrc p15, 0, r1, c1, c0, 0
    bic r1, #(1<<1)
    mcr p15, 0, r1, c1, c0, 0

    /* setup stack */
    bl      stack_setup

    /* clear .bss */
    mov r0,#0                   /* get a zero                       */
    ldr r1,=__bss_start         /* bss start                        */
    ldr r2,=__bss_end           /* bss end                          */

bss_loop:
    cmp r1,r2                   /* check if data to clear           */
    strlo r0,[r1],#4            /* clear 4 bytes                    */
    blo bss_loop                /* loop until done                  */

#ifdef RT_USING_SMP
    mrc p15, 0, r1, c1, c0, 1
    mov r0, #(1<<6)
    orr r1, r0
    mcr p15, 0, r1, c1, c0, 1 //enable smp
#endif

    /* initialize the mmu table and enable mmu */
    ldr r0, =platform_mem_desc
    ldr r1, =platform_mem_desc_size
    ldr r1, [r1]
    bl rt_hw_init_mmu_table

#ifdef RT_USING_USERSPACE
    ldr r0, =MMUTable    /* vaddr    */
    add r0, r5           /* to paddr */
    bl  switch_mmu
#else
    bl rt_hw_mmu_init
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

#ifdef RT_USING_USERSPACE
.align 2
.global enable_mmu
enable_mmu:
    orr r0, #0x18
    mcr p15, 0, r0, c2, c0, 0 //ttbr0

    mov r0, #(1 << 5)         //PD1=1
    mcr p15, 0, r0, c2, c0, 2 //ttbcr

    mov r0, #1
    mcr p15, 0, r0, c3, c0, 0 //dacr

    // invalid tlb before enable mmu
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    mcr p15, 0, r0, c7, c5, 0   ;//iciallu
    mcr p15, 0, r0, c7, c5, 6   ;//bpiall

    mrc p15, 0, r0, c1, c0, 0
    orr r0, #(1 | 4)
    orr r0, #(1 << 12)
    mcr p15, 0, r0, c1, c0, 0
    dsb
    isb
    mov pc, lr

.global set_process_id
set_process_id:
    MCR p15, 0, r0, c13, c0, 1
    mov pc, lr

.global switch_mmu
switch_mmu:
    orr r0, #0x18
    mcr p15, 0, r0, c2, c0, 0 //ttbr0

    // invalid tlb
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    mcr p15, 0, r0, c7, c5, 0   ;//iciallu
    mcr p15, 0, r0, c7, c5, 6   ;//bpiall

    dsb
    isb
    mov pc, lr
.global mmu_table_get
mmu_table_get:
    mrc p15, 0, r0, c2, c0, 0 //ttbr0
    bic r0, #0x18
    mov pc, lr
#endif

_halt:
    wfe
    b _halt

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
#ifdef RT_USING_SMP
    clrex

    stmfd   sp!, {r0, r1}
    cps     #Mode_SVC
    mov     r0, sp          /* svc_sp */
    mov     r1, lr          /* svc_lr */

    cps     #Mode_IRQ
    sub     lr, #4
    stmfd   r0!, {r1, lr}       /* svc_lr, svc_pc */
    stmfd   r0!, {r2 - r12}
    ldmfd   sp!, {r1, r2}     /* original r0, r1 */
    stmfd   r0!, {r1 - r2}
    mrs     r1,  spsr         /* original mode */
    stmfd   r0!, {r1}

#ifdef RT_USING_LWP
    stmfd   r0, {r13, r14}^ /* usr_sp, usr_lr */
    sub     r0, #8
#endif
#ifdef RT_USING_FPU
    /* fpu context */
    vmrs r6, fpexc
    tst  r6, #(1<<30)
    beq 1f
    vstmdb r0!, {d0-d15}
    vstmdb r0!, {d16-d31}
    vmrs r5, fpscr
    stmfd r0!, {r5}
1:
    stmfd r0!, {r6}
#endif

    /* now irq stack is clean */
    /* r0 is task svc_sp */
    /* backup r0 -> r8 */
    mov r8, r0

    cps     #Mode_SVC
    mov     sp, r8

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

    mov     r0, r8
    bl      rt_scheduler_do_irq_switch

    b       rt_hw_context_switch_exit

#else
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

#ifdef RT_USING_LWP
    ldmfd   sp!, {r0-r12,lr}
    cps     #Mode_SVC
    push    {r0-r12}
    mov     r7, lr
    cps     #Mode_IRQ
    mrs     r4, spsr
    sub     r5, lr, #4
    cps     #Mode_SVC
    bl      lwp_check_exit
    and     r6, r4, #0x1f
    cmp     r6, #0x10
    bne     1f
    msr     spsr_csxf, r4
    mov     lr, r5
    pop     {r0-r12}
    b       ret_to_user
1:
    mov     lr, r7
    cps     #Mode_IRQ
    msr     spsr_csxf, r4
    mov     lr, r5
    cps     #Mode_SVC
    pop     {r0-r12}
    cps     #Mode_IRQ
    movs    pc, lr
#else
    ldmfd   sp!, {r0-r12,lr}
    subs    pc,  lr, #4
#endif

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

#ifdef RT_USING_LWP
    stmfd   sp, {r13, r14}^  @push usr_sp, usr_lr
    sub     sp, #8
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

    ldr     r4,  =rt_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]       @ store sp in preempted tasks's TCB

    ldr     r6,  =rt_interrupt_to_thread
    ldr     r6,  [r6]
    ldr     sp,  [r6]       @ get new task's stack pointer

#ifdef RT_USING_USERSPACE
    ldr     r1, =rt_current_thread
    ldr     r0, [r1]
    bl      lwp_mmu_switch
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
1:
#endif

#ifdef RT_USING_LWP
    ldmfd sp, {r13, r14}^  @pop usr_sp, usr_lr
    add sp, #8
#endif

    ldmfd   sp!, {r4}       @ pop new task's cpsr to spsr
    msr     spsr_cxsf, r4

#ifdef RT_USING_GDBSERVER
    bl      lwp_check_debug
#endif

#ifdef RT_USING_LWP
    bl      lwp_check_exit
#endif

#ifdef RT_USING_LWP
    and     r4, #0x1f
    cmp     r4, #0x10
    bne     1f
    ldmfd   sp!, {r0-r12,lr}
    ldmfd   sp!, {lr}
    b       ret_to_user
1:
#endif
    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr

#endif

.macro push_svc_reg
    sub     sp, sp, #17 * 4         @/* Sizeof(struct rt_hw_exp_stack)  */
    stmia   sp, {r0 - r12}          @/* Calling r0-r12                  */
    mov     r0, sp
    add     sp, sp, #17 * 4
    mrs     r6, spsr                @/* Save CPSR                       */
    str     lr, [r0, #15*4]         @/* Push PC                         */
    str     r6, [r0, #16*4]         @/* Push CPSR                       */
    and     r1, r6, #0x1f
    cmp     r1, #0x10
    cps     #Mode_SYS
    streq   sp, [r0, #13*4]         @/* Save calling SP                 */
    streq   lr, [r0, #14*4]         @/* Save calling PC                 */
    cps     #Mode_SVC
    strne   sp, [r0, #13*4]         @/* Save calling SP                 */
    strne   lr, [r0, #14*4]         @/* Save calling PC                 */
.endm

    .align  5
.weak vector_swi
vector_swi:
    push_svc_reg
    bl      rt_hw_trap_swi
    b       .

    .align  5
    .globl  vector_undef
vector_undef:
    push_svc_reg
    bl      rt_hw_trap_undef
    cps     #Mode_UND
#ifdef RT_USING_FPU
    sub     sp, sp, #17 * 4
    ldr     lr, [sp, #15*4]
    ldmia   sp, {r0 - r12}
    add     sp, sp, #17 * 4
    movs    pc, lr
#endif
    b       .

    .align  5
    .globl  vector_pabt
vector_pabt:
    push_svc_reg
#ifdef RT_USING_USERSPACE
    /* cp Mode_ABT stack to SVC */
    sub     sp, sp, #17 * 4         @/* Sizeof(struct rt_hw_exp_stack)  */
    mov     lr, r0
    ldmia   lr, {r0 - r12}
    stmia   sp, {r0 - r12}
    add     r1, lr, #13 * 4
    add     r2, sp, #13 * 4
    ldmia   r1, {r4 - r7}
    stmia   r2, {r4 - r7}
    mov     r0, sp
    bl      rt_hw_trap_pabt
    /* return to user */
    ldr     lr, [sp, #16*4]  //orign spsr
    msr     spsr_cxsf, lr
    ldr     lr, [sp, #15*4]  //orign pc
    ldmia   sp, {r0 - r12}
    add     sp, #17 * 4
    b       ret_to_user
#else
    bl      rt_hw_trap_pabt
    b       .
#endif

    .align  5
    .globl  vector_dabt
vector_dabt:
    push_svc_reg
#ifdef RT_USING_USERSPACE
    /* cp Mode_ABT stack to SVC */
    sub     sp, sp, #17 * 4         @/* Sizeof(struct rt_hw_exp_stack)  */
    mov     lr, r0
    ldmia   lr, {r0 - r12}
    stmia   sp, {r0 - r12}
    add     r1, lr, #13 * 4
    add     r2, sp, #13 * 4
    ldmia   r1, {r4 - r7}
    stmia   r2, {r4 - r7}
    mov     r0, sp
    bl      rt_hw_trap_dabt
    /* return to user */
    ldr     lr, [sp, #16*4]  //orign spsr
    msr     spsr_cxsf, lr
    ldr     lr, [sp, #15*4]  //orign pc
    ldmia   sp, {r0 - r12}
    add     sp, #17 * 4
    b       ret_to_user
#else
    bl      rt_hw_trap_dabt
    b       .
#endif

    .align  5
    .globl  vector_resv
vector_resv:
    push_svc_reg
    bl      rt_hw_trap_resv
    b       .

#ifdef RT_USING_SMP
.global set_secondary_cpu_boot_address
set_secondary_cpu_boot_address:
#ifdef RT_USING_USERSPACE
    ldr     r2,  =secondary_cpu_start
    add     r0, r2

    mvn     r2, #0 //0xffffffff
    str     r2, [r1]
    str     r0, [r1, #-4]
#else
    ldr     r0, =secondary_cpu_start

    mvn     r1, #0 //0xffffffff
    ldr     r2, =0x10000034
    str     r1, [r2]
    str     r0, [r2, #-4]
#endif
    mov     pc, lr

.global secondary_cpu_start
secondary_cpu_start:
#ifdef RT_USING_USERSPACE
    ldr     r5, =PV_OFFSET

    ldr     lr, =after_enable_mmu2
    ldr     r0, =init_mtbl
    add     r0, r5
    b       enable_mmu

after_enable_mmu2:
    ldr     r0, =MMUTable
    add     r0, r5
    bl      switch_mmu
#endif

#ifdef RT_USING_FPU
    mov r4, #0xfffffff
    mcr p15, 0, r4, c1, c0, 2
#endif

    mrc p15, 0, r1, c1, c0, 1
    mov r0, #(1<<6)
    orr r1, r0
    mcr p15, 0, r1, c1, c0, 1 //enable smp

    mrc p15, 0, r0, c1, c0, 0
    bic r0, #(1<<13)
    mcr p15, 0, r0, c1, c0, 0

    cps #Mode_UND
    ldr sp, =und_stack_2_limit

    cps #Mode_IRQ
    ldr sp, =irq_stack_2_limit

    cps #Mode_FIQ
    ldr sp, =irq_stack_2_limit

    cps #Mode_SVC
    ldr sp, =svc_stack_2_limit

    cps #Mode_ABT
    ldr sp, =abt_stack_2_limit

    /* initialize the mmu table and enable mmu */
#ifndef RT_USING_USERSPACE
    bl rt_hw_mmu_init
#endif

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

und_stack_2:
    .space (1 << 10)
und_stack_2_limit:

abt_stack_2:
    .space (1 << 10)
abt_stack_2_limit:
