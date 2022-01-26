/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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

.equ SUB_UND_Stack_Size,     0x00000400
.equ SUB_SVC_Stack_Size,     0x00000400
.equ SUB_ABT_Stack_Size,     0x00000400
.equ SUB_RT_FIQ_STACK_PGSZ,  0x00000000
.equ SUB_RT_IRQ_STACK_PGSZ,  0x00000400
.equ SUB_USR_Stack_Size,     0x00000400

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 RT_FIQ_STACK_PGSZ + RT_IRQ_STACK_PGSZ)

#define SUB_ISR_Stack_Size  (SUB_UND_Stack_Size + SUB_SVC_Stack_Size + SUB_ABT_Stack_Size + \
                 SUB_RT_FIQ_STACK_PGSZ + SUB_RT_IRQ_STACK_PGSZ)

.section .bss.share.isr
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
    /* set the cpu to SVC32 mode and disable interrupt */
    cps #Mode_SVC

#ifdef RT_USING_FPU
    mov r4, #0xfffffff
    mcr p15, 0, r4, c1, c0, 2
#endif

    /* disable the data alignment check */
    mrc p15, 0, r1, c1, c0, 0
    bic r1, #(1<<0)             /* Disable MMU */
    bic r1, #(1<<1)             /* Disable Alignment fault checking */
    bic r1, #(1<<2)             /* Disable data cache */
    bic r1, #(1<<11)            /* Disable program flow prediction */
    bic r1, #(1<<12)            /* Disable instruction cache */
    bic r1, #(3<<19)            /* bit[20:19] must be zero */
    mcr p15, 0, r1, c1, c0, 0

    @ get cpu id, and subtract the offset from the stacks base address
    bl rt_hw_cpu_id
    mov r5, r0

    cmp     r5, #0              @ cpu id == 0
    beq     normal_setup

    @ cpu id > 0, stop or wait
#ifdef RT_SMP_AUTO_BOOT
    ldr r0, =secondary_cpu_entry
    mov r1, #0
    str r1, [r0] /* clean secondary_cpu_entry */
#endif /* RT_SMP_AUTO_BOOT */

secondary_loop:
    @ cpu core 1 goes into sleep until core 0 wakeup it
    wfe
#ifdef RT_SMP_AUTO_BOOT
    ldr r1, =secondary_cpu_entry
    ldr r0, [r1]
    cmp r0, #0
    blxne r0 /* if(secondary_cpu_entry) secondary_cpu_entry(); */
#endif /* RT_SMP_AUTO_BOOT */
    b secondary_loop

normal_setup:
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

#ifdef RT_USING_SMP
    mrc p15, 0, r1, c1, c0, 1
    mov r0, #(1<<6)
    orr r1, r0
    mcr p15, 0, r1, c1, c0, 1 //enable smp
#endif

    /* enable branch prediction */
    mrc p15, 0, r0, c1, c0, 0
    orr     r0, r0, #(1<<11)
    mcr p15, 0, r0, c1, c0, 0

    /* initialize the mmu table and enable mmu */
    ldr r0, =platform_mem_desc
    ldr r1, =platform_mem_desc_size
    ldr r1, [r1]
    bl rt_hw_init_mmu_table
    bl rt_hw_mmu_init

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
    sub     r0, r0, #SVC_Stack_Size

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
    sub   r0, #8
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

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

    cps     #Mode_SVC
    mov     sp, r8
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

#ifdef RT_USING_LWP
    stmfd sp, {r13, r14}^  @push usr_sp, usr_lr
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

    ldr     r4,  =rt_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]       @ store sp in preempted tasks's TCB

    ldr     r6,  =rt_interrupt_to_thread
    ldr     r6,  [r6]
    ldr     sp,  [r6]       @ get new task's stack pointer

    bl rt_interrupt_hook

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

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr

#endif

.macro push_svc_reg
    sub     sp, sp, #17 * 4         @/* Sizeof(struct rt_hw_exp_stack)  */
    stmia   sp, {r0 - r12}          @/* Calling r0-r12                  */
    mov     r0, sp
    mrs     r6, spsr                @/* Save CPSR                       */
    str     lr, [r0, #15*4]         @/* Push PC                         */
    str     r6, [r0, #16*4]         @/* Push CPSR                       */
    mrs     r5, cpsr                @/* Save CPSR                       */

    and     r4, r6, #0x1F
    cmp     r4, #Mode_USR
    moveq   r6, #Mode_SYS

    orr     r6, r6, #0x80           @/* Switch to previous mode, then save SP & PC */
    msr     cpsr_c, r6
    str     sp, [r0, #13*4]         @/* Save calling SP                 */
    str     lr, [r0, #14*4]         @/* Save calling PC                 */

    msr     cpsr_c, r5              @/* Switch back to current mode */
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
    cps #Mode_UND
    bl      rt_hw_trap_undef
#ifdef RT_USING_FPU
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
.global secondary_cpu_start
secondary_cpu_start:

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

    /* enable branch prediction */
    mrc p15, 0, r0, c1, c0, 0
    orr     r0, r0, #(1<<11)
    mcr p15, 0, r0, c1, c0, 0

    @ get cpu id, and subtract the offset from the stacks base address
    bl rt_hw_cpu_id
    sub r5, r0, #1

    ldr r0, =SUB_ISR_Stack_Size
    mul r0, r0, r5                      @r0 = SUB_ISR_Stack_Size * (cpuid - 1)
    ldr r1, =sub_stack_top
    sub r0, r1, r0                      @r0 = sub_stack_top - (SUB_ISR_Stack_Size * (cpuid - 1))

    cps #Mode_SVC
    mov     sp, r0
    sub     r0, r0, #SUB_SVC_Stack_Size

    cps #Mode_UND
    mov     sp, r0
    sub     r0, r0, #SUB_UND_Stack_Size

    cps #Mode_ABT
    mov     sp, r0
    sub     r0, r0, #SUB_ABT_Stack_Size

    cps #Mode_FIQ
    mov     sp, r0
    sub     r0, r0, #SUB_RT_FIQ_STACK_PGSZ

    cps #Mode_IRQ
    mov     sp, r0
    sub     r0, r0, #SUB_RT_IRQ_STACK_PGSZ

    cps #Mode_SVC

    /* initialize the mmu table and enable mmu */
    bl rt_hw_mmu_init

    b secondary_cpu_c_start

.bss
.align 2   //align to  2~2=4

.global sub_stack_top /* used for backtrace to calculate stack top of irq mode */

sub_stack_start:
    .space (SUB_ISR_Stack_Size * (RT_CPUS_NR-1))
sub_stack_top:

#endif
