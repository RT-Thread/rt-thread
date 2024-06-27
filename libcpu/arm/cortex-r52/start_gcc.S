/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
@-------------------------------------------------------------------------------
@ sys_core.asm
@
@ (c) Texas Instruments 2009-2013, All rights reserved.
@

//#include <rtconfig.h>

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
.equ SVC_Stack_Size,  0x00000000
.equ ABT_Stack_Size,  0x00000000
.equ FIQ_Stack_Size,  0x00001000
.equ IRQ_Stack_Size,  0x00001000

.section .bss.noinit
/* stack */
.globl stack_start
.globl stack_top

.align 3
stack_start:
.rept (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + FIQ_Stack_Size + IRQ_Stack_Size)
.byte 0
.endr
stack_top:

.section .text, "ax"
    .text
    .arm

    .globl _c_int00

.globl Reset_Handler
Reset_Handler:
@-------------------------------------------------------------------------------
@ Initialize CPU Registers
@ After reset, the CPU is in the Supervisor mode (M = 10011)
        mov r0, #0x0000
        mov r1, #0x0000
        mov r2, #0x0000
        mov r3, #0x0000
        mov r4, #0x0000
        mov r5, #0x0000
        mov r6, #0x0000
        mov r7, #0x0000
        mov r8, #0x0000
        mov r9, #0x0000
        mov r10, #0x0000
        mov r11, #0x0000
        mov r12, #0x0000
        mov r13, #0x0000
        mrs r1, cpsr
        msr spsr_cxsf, r1

        bl init_cpu_mode

        @ Turn on FPV coprocessor
        mrc   p15,     #0x00,      r2,       c1, c0, #0x02
        orr   r2,      r2,         #0xF00000
        mcr   p15,     #0x00,      r2,       c1, c0, #0x02

        fmrx  r2,      fpexc
        orr   r2,      r2,   #0x40000000
        fmxr  fpexc,   r2

.global stack_init
stack_init:
@-------------------------------------------------------------------------------
@ Initialize Stack Pointers
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
    sub     r0, r0, #FIQ_Stack_Size

    @  Enter IRQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_IRQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #IRQ_Stack_Size

    @  Switch back to SVC
    msr     cpsr_c, #Mode_SVC|I_Bit|F_Bit

.globl bss_init
bss_init:
        /* clear .bss */
        mov     r0,#0                   /* get a zero */
        ldr     r1,=__bss_start__         /* bss start  */
        ldr     r2,=__bss_end__           /* bss end    */

bss_loop:
        cmp     r1,r2                   /* check if data to clear */
        strlo   r0,[r1],#4              /* clear 4 bytes          */
        blo     bss_loop                /* loop until done        */

_c_int00:
        ldr lr, =rtthread_startup
        bx lr

.global init_cpu_mode
init_cpu_mode:
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
    bx lr

@-------------------------------------------------------------------------------
@ Enable RAM ECC Support

    .globl     _coreEnableRamEcc_
_coreEnableRamEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

@-------------------------------------------------------------------------------
@ Disable RAM ECC Support

    .globl     _coreDisableRamEcc_
_coreDisableRamEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr


@-------------------------------------------------------------------------------
@ Enable Flash ECC Support

    .globl     _coreEnableFlashEcc_
_coreEnableFlashEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x02000000
        dmb
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

@-------------------------------------------------------------------------------
@ Disable Flash ECC Support

    .globl     _coreDisableFlashEcc_
_coreDisableFlashEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x02000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr


@-------------------------------------------------------------------------------
@ Get data fault status register

    .globl     _coreGetDataFault_
_coreGetDataFault_:

        mrc   p15, #0, r0, c5, c0,  #0
        bx    lr



@-------------------------------------------------------------------------------
@ Clear data fault status register

    .globl     _coreClearDataFault_
_coreClearDataFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0,  #0
        ldmfd sp!, {r0}
        bx    lr



@-------------------------------------------------------------------------------
@ Get instruction fault status register

    .globl     _coreGetInstructionFault_
_coreGetInstructionFault_:

        mrc   p15, #0, r0, c5, c0, #1
        bx    lr



@-------------------------------------------------------------------------------
@ Clear instruction fault status register

    .globl     _coreClearInstructionFault_
_coreClearInstructionFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0, #1
        ldmfd sp!, {r0}
        bx    lr



@-------------------------------------------------------------------------------
@ Get data fault address register

    .globl     _coreGetDataFaultAddress_
_coreGetDataFaultAddress_:

        mrc   p15, #0, r0, c6, c0,  #0
        bx    lr



@-------------------------------------------------------------------------------
@ Clear data fault address register

    .globl     _coreClearDataFaultAddress_
_coreClearDataFaultAddress_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0,  #0
        ldmfd sp!, {r0}
        bx    lr



@-------------------------------------------------------------------------------
@ Get instruction fault address register

    .globl     _coreGetInstructionFaultAddress_
_coreGetInstructionFaultAddress_:

        mrc   p15, #0, r0, c6, c0, #2
        bx    lr



@-------------------------------------------------------------------------------
@ Clear instruction fault address register

    .globl     _coreClearInstructionFaultAddress_
_coreClearInstructionFaultAddress_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0, #2
        ldmfd sp!, {r0}
        bx    lr



@-------------------------------------------------------------------------------
@ Get auxiliary data fault status register

    .globl     _coreGetAuxiliaryDataFault_
_coreGetAuxiliaryDataFault_:

        mrc   p15, #0, r0, c5, c1, #0
        bx    lr



@-------------------------------------------------------------------------------
@ Clear auxiliary data fault status register

    .globl     _coreClearAuxiliaryDataFault_
_coreClearAuxiliaryDataFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c1, #0
        ldmfd sp!, {r0}
        bx    lr



@-------------------------------------------------------------------------------
@ Get auxiliary instruction fault status register

    .globl     _coreGetAuxiliaryInstructionFault_
_coreGetAuxiliaryInstructionFault_:

        mrc   p15, #0, r0, c5, c1, #1
        bx    lr


@-------------------------------------------------------------------------------
@ Clear auxiliary instruction fault status register

    .globl     _coreClearAuxiliaryInstructionFault_
_coreClearAuxiliaryInstructionFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mrc   p15, #0, r0, c5, c1, #1
        ldmfd sp!, {r0}
        bx    lr


@-------------------------------------------------------------------------------
@ Clear ESM CCM errorss

       .globl _esmCcmErrorsClear_
_esmCcmErrorsClear_:

        stmfd sp!, {r0-r2}
        ldr   r0, ESMSR1_REG    @ load the ESMSR1 status register address
        ldr   r2, ESMSR1_ERR_CLR
        str   r2, [r0]         @ clear the ESMSR1 register

        ldr   r0, ESMSR2_REG    @ load the ESMSR2 status register address
        ldr   r2, ESMSR2_ERR_CLR
        str   r2, [r0]         @ clear the ESMSR2 register

        ldr   r0, ESMSSR2_REG    @ load the ESMSSR2 status register address
        ldr   r2, ESMSSR2_ERR_CLR
        str   r2, [r0]             @ clear the ESMSSR2 register

        ldr   r0, ESMKEY_REG    @ load the ESMKEY register address
        mov   r2, #0x5             @ load R2 with 0x5
        str   r2, [r0]             @ clear the ESMKEY register

        ldr   r0, VIM_INTREQ    @ load the INTREQ register address
        ldr   r2, VIM_INT_CLR
        str   r2, [r0]         @ clear the INTREQ register
        ldr   r0, CCMR4_STAT_REG    @ load the CCMR4 status register address
        ldr   r2, CCMR4_ERR_CLR
        str   r2, [r0]         @ clear the CCMR4 status register
        ldmfd sp!, {r0-r2}
        bx    lr

ESMSR1_REG:        .word 0xFFFFF518
ESMSR2_REG:       .word 0xFFFFF51C
ESMSR3_REG:       .word 0xFFFFF520
ESMKEY_REG:       .word 0xFFFFF538
ESMSSR2_REG:       .word 0xFFFFF53C
CCMR4_STAT_REG:    .word 0xFFFFF600
ERR_CLR_WRD:       .word 0xFFFFFFFF
CCMR4_ERR_CLR:     .word 0x00010000
ESMSR1_ERR_CLR:    .word 0x80000000
ESMSR2_ERR_CLR:    .word 0x00000004
ESMSSR2_ERR_CLR:   .word 0x00000004
VIM_INT_CLR:       .word 0x00000001
VIM_INTREQ:        .word 0xFFFFFE20


@-------------------------------------------------------------------------------
@ Work Around for Errata CORTEX-R4#57:
@
@ Errata Description:
@            Conditional VMRS APSR_Nzcv, FPSCR May Evaluate With Incorrect Flags
@ Workaround:
@            Disable out-of-order single-precision floating point
@            multiply-accumulate instruction completion

        .globl     _errata_CORTEXR4_57_
_errata_CORTEXR4_57_:

        push {r0}
        mrc p15, #0, r0, c15, c0, #0 @ Read Secondary Auxiliary Control Register
        orr r0, r0, #0x10000         @ Set BIT 16 (Set DOOFMACS)
        mcr p15, #0, r0, c15, c0, #0 @ Write Secondary Auxiliary Control Register
        pop {r0}
        bx lr

@-------------------------------------------------------------------------------
@ Work Around for Errata CORTEX-R4#66:
@
@ Errata Description:
@            Register Corruption During A Load-Multiple Instruction At
@            an Exception Vector
@ Workaround:
@            Disable out-of-order completion for divide instructions in
@            Auxiliary Control register

        .globl     _errata_CORTEXR4_66_
_errata_CORTEXR4_66_:

        push {r0}
        mrc p15, #0, r0, c1, c0, #1 @ Read Auxiliary Control register
          orr r0, r0, #0x80           @ Set BIT 7 (Disable out-of-order completion
                                    @ for divide instructions.)
           mcr p15, #0, r0, c1, c0, #1 @ Write Auxiliary Control register
        pop {r0}
        bx lr

    .globl     turnon_VFP
turnon_VFP:
        @ Enable FPV
        STMDB sp!,     {r0}
        fmrx  r0,      fpexc
        orr   r0,      r0,   #0x40000000
        fmxr  fpexc,   r0
        LDMIA sp!,     {r0}
        subs  pc,      lr,   #4


@-------------------------------------------------------------------------------
@ vector_isr

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


@-------------------------------------------------------------------------------
@ vector_irq

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
    ldmfd   sp!, {r1, r2}     /* original rf0, r1 */
    stmfd   r0!, {r1 - r2}
    mrs     r1,  spsr         /* original mode */
    stmfd   r0!, {r1}

#ifdef RT_USING_SMART
    stmfd   r0, {r13, r14}^   /* usr_sp, usr_lr */
    sub     r0, #8
#endif /* RT_USING_SMART */
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
#endif /* RT_USING_FPU */

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
#endif /* RT_USING_SMART */
#endif /* RT_USING_SMP */

@-------------------------------------------------------------------------------
@ push_svc_reg function

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

@-------------------------------------------------------------------------------
@ vector_swi

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

@-------------------------------------------------------------------------------
@ vector_pabt

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

@-------------------------------------------------------------------------------
@ vector_dabt

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

@-------------------------------------------------------------------------------
@ vector_resv

    .align  5
    .globl  vector_resv
vector_resv:
    push_svc_reg
    bl      rt_hw_trap_resv
    b       .
