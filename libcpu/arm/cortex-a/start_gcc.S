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

.equ I_Bit,           0x80   /* when I bit is set, IRQ is disabled */
.equ F_Bit,           0x40   /* when F bit is set, FIQ is disabled */

#ifdef RT_USING_SMART
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
    and r1, r1, #0x1f    /* CPSR_MODE_MASK */
    orr r1, r1, #0x13    /* CPSR_MODE_SUPERVISOR */
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
    and r1, r1, #0x1f    /* CPSR_MODE_MASK */
    orr r1, r1, #0x13    /* CPSR_MODE_SUPERVISOR */
    msr SPSR_hyp, r1
    eret

continue:
    /* set the cpu to SVC32 mode and disable interrupt */
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x13
    msr cpsr_c, r0
#endif

    /* invalid tlb before enable mmu */
    mrc p15, 0, r0, c1, c0, 0
    bic r0, #1
    mcr p15, 0, r0, c1, c0, 0
    dsb
    isb
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    mcr p15, 0, r0, c7, c5, 0    /* iciallu */
    mcr p15, 0, r0, c7, c5, 6    /* bpiall */
    dsb
    isb

#ifdef RT_USING_SMART
    /* load r5 with PV_OFFSET */
    ldr r7, =_reset
    adr r5, _reset
    sub r5, r5, r7

    mov r7, #0x100000
    sub r7, #1
    mvn r8, r7


    ldr r9, =KERNEL_VADDR_START

    ldr r6, =__bss_end
    add r6, r7
    and r6, r8    /* r6 end vaddr align up to 1M */
    sub r6, r9    /* r6 is size */

    ldr sp, =svc_stack_n_limit
    add sp, r5    /* use paddr */

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
    bic r1, #(1<<1)             /* Disable Alignment fault checking */
#ifndef RT_USING_SMART
    bic r1, #(1<<0)             /* Disable MMU */
    bic r1, #(1<<2)             /* Disable data cache */
    bic r1, #(1<<11)            /* Disable program flow prediction */
    bic r1, #(1<<12)            /* Disable instruction cache */
    bic r1, #(3<<19)            /* bit[20:19] must be zero */
#endif /* RT_USING_SMART */
    mcr p15, 0, r1, c1, c0, 0

    /* enable I cache + branch prediction */
    mrc p15, 0, r0, c1, c0, 0
    orr     r0, r0, #(1<<12)
    orr     r0, r0, #(1<<11)
    mcr p15, 0, r0, c1, c0, 0

    /* setup stack */
    bl  stack_setup

    /* clear .bss */
    mov r0,#0                   /* get a zero                       */
    ldr r1,=__bss_start         /* bss start                        */
    ldr r2,=__bss_end           /* bss end                          */

bss_loop:
    cmp r1,r2                   /* check if data to clear           */
    strlo r0,[r1],#4            /* clear 4 bytes                    */
    blo bss_loop                /* loop until done                  */

    mov r0, r5
    bl rt_kmem_pvoff_set

#ifdef RT_USING_SMP
    mrc p15, 0, r1, c1, c0, 1
    mov r0, #(1<<6)
    orr r1, r0
    mcr p15, 0, r1, c1, c0, 1   /* enable smp */
#endif

    /**
     * void rt_hw_init_mmu_table(struct mem_desc *mdesc, rt_uint32_t size)
     * initialize the mmu table and enable mmu
     */
    ldr r0, =platform_mem_desc
    ldr r1, =platform_mem_desc_size
    ldr r1, [r1]
    bl rt_hw_init_mmu_table

#ifdef RT_USING_SMART
    ldr r0, =MMUTable     /* vaddr    */
    add r0, r5            /* to paddr */
    bl  rt_hw_mmu_switch
#else
    bl rt_hw_mmu_init
#endif

    /* start RT-Thread Kernel */
    ldr     pc, _rtthread_startup
_rtthread_startup:
    .word rtthread_startup

.weak rt_asm_cpu_id 
rt_asm_cpu_id:
    mov r9, lr
    mrc p15, 0, r0, c0, c0, 5
    and r0, r0, #0xf
    mov lr, r9

stack_setup:

#ifdef RT_USING_SMP
    /* cpu id */
    mov r10, lr
    bl rt_asm_cpu_id
    mov lr, r10
    add r0, r0, #1
    
#else
    mov r0, #1
#endif

    cps #Mode_UND
    ldr r1, =und_stack_n
    add sp, r1, r0, asl #12

    cps #Mode_IRQ
    ldr r1, =irq_stack_n
    add sp, r1, r0, asl #12

    cps #Mode_FIQ
    ldr r1, =irq_stack_n
    add sp, r1, r0, asl #12

    cps #Mode_ABT
    ldr r1, =abt_stack_n
    add sp, r1, r0, asl #12

    cps #Mode_SVC
    ldr r1, =svc_stack_n
    add sp, r1, r0, asl #12

    bx      lr

#ifdef RT_USING_SMART
.align 2
.global enable_mmu
enable_mmu:
    orr r0, #0x18
    mcr p15, 0, r0, c2, c0, 0    /* ttbr0 */

    mov r0, #(1 << 5)            /* PD1=1 */
    mcr p15, 0, r0, c2, c0, 2    /* ttbcr */

    mov r0, #1
    mcr p15, 0, r0, c3, c0, 0    /* dacr */

    /* invalid tlb before enable mmu */
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    mcr p15, 0, r0, c7, c5, 0    /* iciallu */
    mcr p15, 0, r0, c7, c5, 6    /* bpiall */

    mrc p15, 0, r0, c1, c0, 0
    orr r0, #((1 << 12) | (1 << 11))    /* instruction cache, branch prediction */
    orr r0, #((1 << 2) | (1 << 0))      /* data cache, mmu enable */
    mcr p15, 0, r0, c1, c0, 0
    dsb
    isb
    mov pc, lr

.global rt_hw_set_process_id
rt_hw_set_process_id:
    LSL r0, r0, #8
    MCR p15, 0, r0, c13, c0, 1
    mov pc, lr

#endif
.global rt_hw_mmu_switch
rt_hw_mmu_switch:
    orr r0, #0x18
    mcr p15, 0, r0, c2, c0, 0       // ttbr0

                                    //invalid tlb
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    mcr p15, 0, r0, c7, c5, 0       //iciallu
    mcr p15, 0, r0, c7, c5, 6       //bpiall 

    dsb
    isb
    mov pc, lr

.global rt_hw_mmu_tbl_get
rt_hw_mmu_tbl_get:
    mrc p15, 0, r0, c2, c0, 0    /* ttbr0 */
    bic r0, #0x18
    mov pc, lr

_halt:
    wfe
    b _halt

#ifdef RT_USING_SMP

.global rt_secondary_cpu_entry
rt_secondary_cpu_entry:
#ifdef RT_USING_SMART
    ldr     r0, =_reset
    adr     r5, _reset
    sub     r5, r5, r0

    ldr     lr, =after_enable_mmu_n
    ldr     r0, =init_mtbl
    add     r0, r5
    b       enable_mmu

after_enable_mmu_n:
    ldr     r0, =MMUTable
    add     r0, r5
    bl      rt_hw_mmu_switch
#endif

#ifdef RT_USING_FPU
    mov r4, #0xfffffff
    mcr p15, 0, r4, c1, c0, 2
#endif

    mrc p15, 0, r1, c1, c0, 1
    mov r0, #(1<<6)
    orr r1, r0
    mcr p15, 0, r1, c1, c0, 1    /* enable smp */

    mrc p15, 0, r0, c1, c0, 0
    bic r0, #(1<<13)
    mcr p15, 0, r0, c1, c0, 0

    bl stack_setup

    /* initialize the mmu table and enable mmu */
#ifndef RT_USING_SMART
    bl rt_hw_mmu_init
#endif

    b rt_hw_secondary_cpu_bsp_start
#endif

/* exception handlers: undef, swi, padt, dabt, resv, irq, fiq */
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
    stmfd   r0!, {r1, lr}     /* svc_lr, svc_pc */
    stmfd   r0!, {r2 - r12}
    ldmfd   sp!, {r1, r2}     /* original r0, r1 */
    stmfd   r0!, {r1 - r2}
    mrs     r1,  spsr         /* original mode */
    stmfd   r0!, {r1}

#ifdef RT_USING_SMART
    stmfd   r0, {r13, r14}^   /* usr_sp, usr_lr */
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

    /* if rt_thread_switch_interrupt_flag set, jump to
     * rt_hw_context_switch_interrupt_do and don't return */
    ldr     r0, =rt_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq     rt_hw_context_switch_interrupt_do

#ifdef RT_USING_SMART
    ldmfd   sp!, {r0-r12,lr}
    cps     #Mode_SVC
    push    {r0-r12}
    mov     r7, lr
    cps     #Mode_IRQ
    mrs     r4, spsr
    sub     r5, lr, #4
    cps     #Mode_SVC
    and     r6, r4, #0x1f
    cmp     r6, #0x10
    bne     1f
    msr     spsr_csxf, r4
    mov     lr, r5
    pop     {r0-r12}
    b       arch_ret_to_user
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
    mov     r1,  #0             /* clear flag */
    str     r1,  [r0]

    mov     r1, sp              /* r1 point to {r0-r3} in stack */
    add     sp, sp, #4*4
    ldmfd   sp!, {r4-r12,lr}    /* reload saved registers */
    mrs     r0,  spsr           /* get cpsr of interrupt thread */
    sub     r2,  lr, #4         /* save old task's pc to r2 */

    /* Switch to SVC mode with no interrupt. If the usr mode guest is
     * interrupted, this will just switch to the stack of kernel space.
     * save the registers in kernel space won't trigger data abort. */
    msr     cpsr_c, #I_Bit|F_Bit|Mode_SVC

    stmfd   sp!, {r2}           /* push old task's pc */
    stmfd   sp!, {r4-r12,lr}    /* push old task's lr,r12-r4 */
    ldmfd   r1,  {r1-r4}        /* restore r0-r3 of the interrupt thread */
    stmfd   sp!, {r1-r4}        /* push old task's r0-r3 */
    stmfd   sp!, {r0}           /* push old task's cpsr */

#ifdef RT_USING_SMART
    stmfd   sp, {r13, r14}^     /*push usr_sp, usr_lr */
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
    str     sp,  [r5]       /* store sp in preempted tasks's TCB */

    ldr     r6,  =rt_interrupt_to_thread
    ldr     r6,  [r6]
    ldr     sp,  [r6]       /* get new task's stack pointer */

    bl      rt_thread_self
#ifdef RT_USING_SMART
    mov     r4, r0
    bl      lwp_aspace_switch
    mov     r0, r4
    bl      lwp_user_setting_restore
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

#ifdef RT_USING_SMART
    ldmfd sp, {r13, r14}^    /*pop usr_sp, usr_lr */
    add sp, #8
#endif

    ldmfd   sp!, {r4}        /* pop new task's cpsr to spsr */
    msr     spsr_cxsf, r4

#ifdef RT_USING_SMART
    and     r4, #0x1f
    cmp     r4, #0x10
    bne     1f
    ldmfd   sp!, {r0-r12,lr}
    ldmfd   sp!, {lr}
    b       arch_ret_to_user
1:
#endif
    /* pop new task's r0-r12,lr & pc, copy spsr to cpsr */
    ldmfd   sp!, {r0-r12,lr,pc}^

#endif

.macro push_svc_reg
    sub     sp, sp, #17 * 4         /* Sizeof(struct rt_hw_exp_stack)  */
    stmia   sp, {r0 - r12}          /* Calling r0-r12                  */
    mov     r0, sp
    add     sp, sp, #17 * 4
    mrs     r6, spsr                /* Save CPSR                       */
    str     lr, [r0, #15*4]         /* Push PC                         */
    str     r6, [r0, #16*4]         /* Push CPSR                       */
    and     r1, r6, #0x1f
    cmp     r1, #0x10
    cps     #Mode_SYS
    streq   sp, [r0, #13*4]         /* Save calling SP                 */
    streq   lr, [r0, #14*4]         /* Save calling PC                 */
    cps     #Mode_SVC
    strne   sp, [r0, #13*4]         /* Save calling SP                 */
    strne   lr, [r0, #14*4]         /* Save calling PC                 */
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
#ifdef RT_USING_SMART
    /* cp Mode_ABT stack to SVC */
    sub     sp, sp, #17 * 4     /* Sizeof(struct rt_hw_exp_stack)  */
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
    ldr     lr, [sp, #16*4]     /* orign spsr */
    msr     spsr_cxsf, lr
    ldr     lr, [sp, #15*4]     /* orign pc */
    ldmia   sp, {r0 - r12}
    add     sp, #17 * 4
    b       arch_ret_to_user
#else
    bl      rt_hw_trap_pabt
    b       .
#endif

    .align  5
    .globl  vector_dabt
vector_dabt:
    push_svc_reg
#ifdef RT_USING_SMART
    /* cp Mode_ABT stack to SVC */
    sub     sp, sp, #17 * 4    /* Sizeof(struct rt_hw_exp_stack)  */
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
    ldr     lr, [sp, #16*4]    /* orign spsr */
    msr     spsr_cxsf, lr
    ldr     lr, [sp, #15*4]    /* orign pc */
    ldmia   sp, {r0 - r12}
    add     sp, #17 * 4
    b       arch_ret_to_user
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

.global rt_hw_clz
rt_hw_clz:
    clz r0, r0
    bx lr

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif

#include "asm-generic.h"

START_POINT(_thread_start)
    mov     r10, lr
    blx     r1
    blx     r10
    b       .   /* never here */
START_POINT_END(_thread_start)

.bss
.align 3     /* align to  2~3=8 */
svc_stack_n:
    .space (RT_CPUS_NR << 12)
svc_stack_n_limit:

irq_stack_n:
    .space (RT_CPUS_NR << 12)

und_stack_n:
    .space (RT_CPUS_NR << 12)

abt_stack_n:
    .space (RT_CPUS_NR << 12)
