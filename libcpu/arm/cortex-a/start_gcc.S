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
 * 2024-01-16     huanghe      restructure this code section following the aarch64 architectural style
 */

#include "rtconfig.h"

#define ARM_CPU_STACK_SIZE_OFFSET   12
#define ARM_CPU_STACK_SIZE  (1<<ARM_CPU_STACK_SIZE_OFFSET)

.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80   /* when I bit is set, IRQ is disabled */
.equ F_Bit,           0x40   /* when F bit is set, FIQ is disabled */

/*Load the physical address of a symbol into a register. 
  Through pv_off calculates the offset of the physical address */
.macro get_phy, reg, symbol, _pvoff
    ldr \reg, =\symbol
    add \reg, \_pvoff
.endm
/*Calculate the offset between the physical address and the virtual address of the "_reset".*/
.macro get_pvoff, tmp, out
    ldr     \tmp, =_reset
    adr     \out, _reset
    sub     \out, \out, \tmp
.endm

pv_off       .req r11 /* Used to store the offset between physical address and the virtual address */
cpu_id       .req r10 /* Used to store the cpu id */

/* reset entry */
    .globl _reset
_reset:
    /* Calculate the offset between the physical address and the virtual address */
    get_pvoff r0, pv_off

    /* exit hyp mode  */
    bl init_cpu_mode
    /* clear bss section */
    bl init_kernel_bss
    /* Initializes the assembly environment stack  */
    bl init_cpu_stack_early

    /* init mmu  */
    b init_mmu_page_table_early

init_cpu_stack_early:

    cps #Mode_SVC
    
    get_phy r0, svc_stack_top, pv_off
    mov     sp, r0

#ifdef RT_USING_FPU
    mov r4, #0xfffffff
    mcr p15, 0, r4, c1, c0, 2
#endif

    mov pc, lr

init_kernel_bss:

    /* enable I cache + branch prediction */
    mrc p15, 0, r0, c1, c0, 0
    orr     r0, r0, #(1<<12)
    orr     r0, r0, #(1<<11)
    mcr p15, 0, r0, c1, c0, 0

    mov r0,#0                   /* get a zero      */
    get_phy r1, __bss_start, pv_off
    get_phy r2, __bss_end, pv_off

bss_loop:
    cmp r1,r2                   /* check if data to clear           */
    strlo r0,[r1],#4            /* clear 4 bytes                    */
    blo bss_loop                /* loop until done                  */

    mov pc, lr

init_cpu_mode:

#ifdef ARCH_ARMV8
    /* Check for HYP mode */
    mrs r0, cpsr_all
    and r0, r0, #0x1F
    mov r8, #0x1A
    cmp r0, r8
    beq overHyped
    b continue_exit

overHyped: /* Get out of HYP mode */
    mov r9, lr 
    /* HYP mode has a dedicated register, called ELR_hyp, 
    to store the exception return address.
    The lr register needs to be temporarily saved,
    otherwise "mov pc lr" cannot be used after switching modes. */
    adr r1, continue_exit
    msr ELR_hyp, r1
    mrs r1, cpsr_all
    and r1, r1, #0xFFFFFFE0    /* CPSR_MODE_MASK */
    orr r1, r1, #0x13          /* CPSR_MODE_SUPERVISOR */
    msr SPSR_hyp, r1
    eret

continue_exit:
    mov lr ,r9
    
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
    b continue_exit

overHyped: /* Get out of HYP mode */
    mov r9, lr 
    /* HYP mode has a dedicated register, called ELR_hyp, 
    to store the exception return address.
    The lr register needs to be temporarily saved,
    otherwise "mov pc lr" cannot be used after switching modes. */
    adr r1, continue_exit
    msr ELR_hyp, r1
    mrs r1, cpsr_all
    and r1, r1, #0xFFFFFFE0    /* CPSR_MODE_MASK */
    orr r1, r1, #0x13          /* CPSR_MODE_SUPERVISOR */
    msr SPSR_hyp, r1
    eret

continue_exit:
    mov lr ,r9
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

    mov pc, lr

init_mmu_page_table_early:
    get_phy r0, init_mtbl, pv_off
    mov r1, pv_off
    bl rt_hw_mem_setup_early

    /* get cpu id */
    bl rt_hw_cpu_id_early
    mov cpu_id ,r0
    /* enable_mmu_page_table_early is changed to master_core_startup */
    ldr     lr, =master_core_startup
    
    cmp cpu_id, #0
    beq enable_mmu_page_table_early


#ifdef RT_USING_SMP
#ifdef RT_SMP_AUTO_BOOT
    /* if cpu id > 0, stop or wait */
    ldr r0, =secondary_cpu_entry
    mov r1, #0
    str r1, [r0] /* clean secondary_cpu_entry */
#endif
#endif

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
    
enable_mmu_page_table_early:
    /* init TTBR0  */
    get_phy r0, init_mtbl, pv_off
    mcr     p15, #0, r0, c2, c0, #0
    dmb
    
    ldr     r0,=#0x55555555
    mcr     p15, #0, r0, c3, c0, #0

    /* disable ttbr1 */
    mov r0, #(1 << 5)            /* PD1=1 */
    mcr p15, 0, r0, c2, c0, 2    /* ttbcr */

    
    /*  init stack for cpu mod */
    cps #Mode_UND
    ldr r1,=und_stack_top
    sub sp, r1, cpu_id, asl #ARM_CPU_STACK_SIZE_OFFSET


    cps #Mode_IRQ
    ldr r1, =irq_stack_top
    sub sp, r1, cpu_id, asl #ARM_CPU_STACK_SIZE_OFFSET


    cps #Mode_FIQ
    ldr r1, =irq_stack_top
    sub sp, r1, cpu_id, asl #ARM_CPU_STACK_SIZE_OFFSET


    cps #Mode_ABT
    ldr r1, =abt_stack_top
    sub sp, r1, cpu_id, asl #ARM_CPU_STACK_SIZE_OFFSET


    cps #Mode_SVC
    ldr r1, =svc_stack_top
    sub sp, r1, cpu_id, asl #ARM_CPU_STACK_SIZE_OFFSET


    /* invalid tlb before enable mmu */
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    mcr p15, 0, r0, c7, c5, 0    /* iciallu */
    mcr p15, 0, r0, c7, c5, 6    /* bpiall */

    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #0x7                    /* clear bit1~3 */
    orr r0, #((1 << 12) | (1 << 11))    /* instruction cache, branch prediction */
    orr r0, #((1 << 2) | (1 << 0))      /* data cache, mmu enable */
    mcr p15, 0, r0, c1, c0, 0
    dsb
    isb

    mov pc, lr

master_core_startup :
    mov r0 ,pv_off
    bl rt_kmem_pvoff_set

    ldr     lr, =rtthread_startup
    mov pc, lr

.global rt_hw_mmu_tbl_get
rt_hw_mmu_tbl_get:
    mrc p15, 0, r0, c2, c0, 0    /* ttbr0 */
    bic r0, #0x18
    mov pc, lr

.weak rt_hw_cpu_id_early
rt_hw_cpu_id_early:
    mrc p15, 0, r0, c0, c0, 5
    and r0, r0, #0xf
    mov pc, lr

#ifdef RT_USING_SMP
.global rt_secondary_cpu_entry
rt_secondary_cpu_entry:
    ldr r0, =_reset
    adr pv_off, _reset
    sub pv_off, pv_off, r0

    bl init_cpu_stack_early

    /* init mmu  */
    bl rt_hw_cpu_id_early
    mov cpu_id ,r0

    ldr lr ,= rt_hw_secondary_cpu_bsp_start
    b enable_mmu_page_table_early
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

#ifdef RT_USING_SMART
    bl      rt_thread_self
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
#ifdef RT_USING_FPU
    cps     #Mode_UND
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


#include "asm-generic.h"

START_POINT(_thread_start)
    mov     r10, lr
    blx     r1
    blx     r10
    b       .   /* never here */
START_POINT_END(_thread_start)

.data
.align 14
init_mtbl:
    .space  (4*4096) /* The  L1 translation table therefore contains 4096 32-bit (word-sized) entries.  */

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


.global rt_hw_set_process_id
rt_hw_set_process_id:
    LSL r0, r0, #8
    MCR p15, 0, r0, c13, c0, 1
    mov pc, lr


.bss
.align 3     /* align to  2~3=8 */

.cpus_stack:
svc_stack_n:
#if defined(RT_USING_SMP) && (RT_CPUS_NR > 1)
    .space ((RT_CPUS_NR - 1) * ARM_CPU_STACK_SIZE)
#endif
    .space (ARM_CPU_STACK_SIZE)
svc_stack_top:

irq_stack_n:
#if defined(RT_USING_SMP) && (RT_CPUS_NR > 1)
    .space ((RT_CPUS_NR - 1) * ARM_CPU_STACK_SIZE)
#endif
    .space (ARM_CPU_STACK_SIZE)
irq_stack_top:


und_stack_n:
#if defined(RT_USING_SMP) && (RT_CPUS_NR > 1)
    .space ((RT_CPUS_NR - 1) * ARM_CPU_STACK_SIZE)
#endif
    .space (ARM_CPU_STACK_SIZE)
und_stack_top:

abt_stack_n:
#if defined(RT_USING_SMP) && (RT_CPUS_NR > 1)
    .space ((RT_CPUS_NR - 1) * ARM_CPU_STACK_SIZE)
#endif
    .space (ARM_CPU_STACK_SIZE)
abt_stack_top:




