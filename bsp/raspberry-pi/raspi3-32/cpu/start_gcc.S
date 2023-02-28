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
.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80            @ when I bit is set, IRQ is disabled
.equ F_Bit,           0x40            @ when F bit is set, FIQ is disabled

#ifdef RT_USING_FPU
.equ UND_Stack_Size,     0x00000400
#else
.equ UND_Stack_Size,     0x00000000
#endif
.equ SVC_Stack_Size,     0x00000400
.equ ABT_Stack_Size,     0x00000000
.equ RT_FIQ_STACK_PGSZ,  0x00000000
.equ RT_IRQ_STACK_PGSZ,  0x00000800
.equ USR_Stack_Size,     0x00000400

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 RT_FIQ_STACK_PGSZ + RT_IRQ_STACK_PGSZ)

.section .data.share.isr
/* stack */

#ifdef RT_USING_SMP
.globl stack_start0
.globl stack_top0
.globl stack_start1
.globl stack_top1
.globl stack_start2
.globl stack_top2
.globl stack_start3
.globl stack_top3
stack_start0:
.rept ISR_Stack_Size
.byte 0
.endr
stack_top0:

stack_start1:
.rept ISR_Stack_Size
.byte 0
.endr
stack_top1:

stack_start2:
.rept ISR_Stack_Size
.byte 0
.endr
stack_top2:

stack_start3:
.rept ISR_Stack_Size
.byte 0
.endr
stack_top3:

.globl boot_indicate
boot_indicate:
.rept 16
.byte 0
.endr

#else
.globl stack_start
.globl stack_top
stack_start:
.rept ISR_Stack_Size
.byte 0
.endr
stack_top:
#endif


.text
/* reset entry */
.globl _reset
_reset:

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
    ldr r1, =continue
    msr ELR_hyp, r1
    mrs r1, cpsr_all
    and r1, r1, #0x1f    ;@ CPSR_MODE_MASK
    orr r1, r1, #0x13    ;@ CPSR_MODE_SUPERVISOR
    msr SPSR_hyp, r1
    eret

continue:

    /* disable mmu */
    bl      rt_cpu_mmu_disable
    /* set the cpu to SVC32 mode and disable interrupt */
    mrs     r0, cpsr
    bic     r0, r0, #0x1f
    orr     r0, r0, #0x13
    msr     cpsr_c, r0
#ifdef RT_USING_SMP
    mrc     p15, 0, r0, c0, c0, 5
    ubfx    r0, r0, #0, #2
    cmp     r0, #0
    beq     1f
    /* write boot indicate */
    ldr     r5, = boot_indicate
    str     r0, [r5, r0, lsl #2]
    bl secondary_cpu_start
    b .
1:
#endif
    /* setup stack */
#ifdef RT_USING_SMP
    ldr     r0, =stack_top0
#else
    ldr     r0, =stack_top
#endif
    bl      stack_setup
      
    /* clear .bss */
    mov     r0,#0                   /* get a zero                       */
    ldr     r1,=__bss_start         /* bss start                        */
    ldr     r2,=__bss_end           /* bss end                          */

bss_loop:
    cmp     r1,r2                   /* check if data to clear           */
    strlo   r0,[r1],#4              /* clear 4 bytes                    */
    blo     bss_loop                /* loop until done                  */
    bl rt_hw_init_mmu_table
    bl init_mbox_mmu_map
    bl rt_hw_mmu_init

    /* start RT-Thread Kernel */
    ldr     pc, _rtthread_startup
_rtthread_startup:
    .word rtthread_startup

stack_setup:

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

.text

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
    sub     lr, lr, #4
    stmfd   r0!, {r1, lr}       /* svc_lr, svc_pc */
    stmfd   r0!, {r2 - r12}
    ldmfd   sp!, {r1, r2}     /* original r0, r1 */
    stmfd   r0!, {r1 - r2}
    mrs     r1,  spsr         /* original mode */
    stmfd   r0!, {r1}

#ifdef RT_USING_SMART
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
    mov     r8, r0

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

#ifdef RT_USING_SMART
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
    /* set vector base */
    mrc p15, 0, r0, c1, c0, 0        
    bic r0, #(1<<13)
    mcr p15, 0, r0, c1, c0, 0
    
    /* setup stack */
    mrc p15, 0, r0, c0, c0, 5
    ubfx    r0, r0, #0, #2
    ldr r1, =stack_top0
    ldr r2, =ISR_Stack_Size
    mul r3, r2, r0
    add r0, r1, r3
    bl  stack_setup
    /* initialize the mmu table and enable mmu */
    bl  rt_hw_mmu_init
    b   secondary_cpu_c_start

#endif

;@ void arm_smp_enable(void);
.globl arm_smp_enable
arm_smp_enable:
    mrc p15, 0, r0, c1, c0, 1   ;@ set SMP bit in ACTLR
    orr r0, r0, #0x40
    mcr p15, 0, r0, c1, c0, 1
    bx lr
/*
    mrrc p15, 1, r0, r1, c15
    orr r0, r0, #0x40
    mcrr p15, 1, r0, r1, c15
    dsb
    isb
    bx lr
*/
.text
;@ void arm_smp_disable(void);
.globl arm_smp_disable

arm_smp_disable:
    mrc p15, 0, r0, c1, c0, 1   ;@ clear SMP bit in ACTLR
    bic r0, r0, #0x40
    mcr p15, 0, r0, c1, c0, 1
    bx lr
/*
    mrrc p15, 1, r0, r1, c15
    bic r0, r0, #0x40
    mcrr p15, 1, r0, r1, c15
    bx lr
*/

