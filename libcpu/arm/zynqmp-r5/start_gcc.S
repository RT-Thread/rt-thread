/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19     WangHuachen  first version
 * 2021-05-11     WangHuachen  Added call to Xil_InitializeExistingMPURegConfig to
 *                             initialize the MPU configuration table with the MPU
 *                             configurations already set in Init_Mpu function.
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
.equ SVC_Stack_Size,  0x00000000
.equ ABT_Stack_Size,  0x00000000
.equ FIQ_Stack_Size,  0x00000200
.equ IRQ_Stack_Size,  0x00000200
.equ USR_Stack_Size,  0x00000000

.set RPU_GLBL_CNTL, 0xFF9A0000
.set RPU_ERR_INJ,   0xFF9A0020
.set RPU_0_CFG,     0xFF9A0100
.set RPU_1_CFG,     0xFF9A0200
.set RST_LPD_DBG,   0xFF5E0240
.set BOOT_MODE_USER,    0xFF5E0200
.set fault_log_enable,  0x101

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 FIQ_Stack_Size + IRQ_Stack_Size)

.section .data.share.isr
/* stack */
.globl stack_start
.globl stack_top

.align 3
.bss
stack_start:
.rept ISR_Stack_Size
.long 0
.endr
stack_top:

.section .boot,"axS"
/* reset entry */
.globl _reset
_reset:

    /* Initialize processor registers to 0 */
    mov r0,#0
    mov r1,#0
    mov r2,#0
    mov r3,#0
    mov r4,#0
    mov r5,#0
    mov r6,#0
    mov r7,#0
    mov r8,#0
    mov r9,#0
    mov r10,#0
    mov r11,#0
    mov r12,#0

    /* set the cpu to SVC32 mode and disable interrupt */
    cpsid  if, #Mode_SVC

    /* setup stack */
    bl      stack_setup

    /*
    * Enable access to VFP by enabling access to Coprocessors 10 and 11.
    * Enables Full Access i.e. in both privileged and non privileged modes
    */
    mrc     p15, 0, r0, c1, c0, 2       /* Read Coprocessor Access Control Register (CPACR) */
    orr     r0, r0, #(0xF << 20)        /* Enable access to CP 10 & 11 */
    mcr     p15, 0, r0, c1, c0, 2       /* Write Coprocessor Access Control Register (CPACR) */
    isb

    /* enable fpu access  */
    vmrs    r3, FPEXC
    orr r1, r3, #(1<<30)
    vmsr    FPEXC, r1

    /* clear the floating point register*/
    mov     r1,#0
    vmov    d0,r1,r1
    vmov    d1,r1,r1
    vmov    d2,r1,r1
    vmov    d3,r1,r1
    vmov    d4,r1,r1
    vmov    d5,r1,r1
    vmov    d6,r1,r1
    vmov    d7,r1,r1
    vmov    d8,r1,r1
    vmov    d9,r1,r1
    vmov    d10,r1,r1
    vmov    d11,r1,r1
    vmov    d12,r1,r1
    vmov    d13,r1,r1
    vmov    d14,r1,r1
    vmov    d15,r1,r1

#ifdef __SOFTFP__
/* Disable the FPU if SOFTFP is defined*/
    vmsr    FPEXC,r3
#endif

    /* Disable MPU and caches */
    mrc     p15, 0, r0, c1, c0, 0           /* Read CP15 Control Register*/
    bic     r0, r0, #0x05                   /* Disable MPU (M bit) and data cache (C bit) */
    bic     r0, r0, #0x1000                 /* Disable instruction cache (I bit) */
    dsb                                     /* Ensure all previous loads/stores have completed */
    mcr     p15, 0, r0, c1, c0, 0           /* Write CP15 Control Register */
    isb                                     /* Ensure subsequent insts execute wrt new MPU settings */

    /* Disable Branch prediction, TCM ECC checks */
    mrc     p15, 0, r0, c1, c0, 1           /* Read ACTLR */
    orr     r0, r0, #(0x1 << 17)            /* Enable RSDIS bit 17 to disable the return stack */
    orr     r0, r0, #(0x1 << 16)            /* Clear BP bit 15 and set BP bit 16:*/
    bic     r0, r0, #(0x1 << 15)            /* Branch always not taken and history table updates disabled*/
    orr     r0, r0, #(0x1 << 27)            /* Enable B1TCM ECC check */
    orr     r0, r0, #(0x1 << 26)            /* Enable B0TCM ECC check */
    orr     r0, r0, #(0x1 << 25)            /* Enable ATCM ECC check */
    bic     r0, r0, #(0x1 << 5)             /* Generate abort on parity errors, with [5:3]=b 000*/
    bic     r0, r0, #(0x1 << 4)
    bic     r0, r0, #(0x1 << 3)
    mcr     p15, 0, r0, c1, c0, 1           /* Write ACTLR*/
    dsb                                     /* Complete all outstanding explicit memory operations*/

    /* Invalidate caches */
    mov     r0,#0                           /* r0 = 0  */
    dsb
    mcr     p15, 0, r0, c7, c5, 0           /* invalidate icache */
    mcr     p15, 0, r0, c15, c5, 0          /* Invalidate entire data cache*/
    isb

    /* enable fault log for lock step */
    ldr     r0,=RPU_GLBL_CNTL
    ldr     r1, [r0]
    ands    r1, r1, #0x8
    /* branch to initialization if split mode*/
    bne     init
    /* check for boot mode if in lock step, branch to init if JTAG boot mode*/
    ldr     r0,=BOOT_MODE_USER
    ldr     r1, [r0]
    ands    r1, r1, #0xF
    beq     init
    /* reset the debug logic */
    ldr     r0,=RST_LPD_DBG
    ldr     r1, [r0]
    orr     r1, r1, #(0x1 << 4)
    orr     r1, r1, #(0x1 << 5)
    str     r1, [r0]
    /* enable fault log */
    ldr     r0,=RPU_ERR_INJ
    ldr     r1,=fault_log_enable
    ldr     r2, [r0]
    orr     r2, r2, r1
    str     r2, [r0]
    nop
    nop

init:
    bl  Init_MPU                            /* Initialize MPU */

    /* Enable Branch prediction */
    mrc     p15, 0, r0, c1, c0, 1       /* Read ACTLR*/
    bic     r0, r0, #(0x1 << 17)        /* Clear RSDIS bit 17 to enable return stack*/
    bic     r0, r0, #(0x1 << 16)        /* Clear BP bit 15 and BP bit 16:*/
    bic     r0, r0, #(0x1 << 15)        /* Normal operation, BP is taken from the global history table.*/
    orr     r0, r0, #(0x1 << 14)        /* Disable DBWR for errata 780125 */
    mcr     p15, 0, r0, c1, c0, 1       /* Write ACTLR*/

    /* Enable icahce and dcache */
    mrc     p15,0,r1,c1,c0,0
    ldr     r0, =0x1005
    orr     r1,r1,r0
    dsb
    mcr     p15,0,r1,c1,c0,0            /* Enable cache  */
    isb                                 /* isb  flush prefetch buffer */

    /* Set vector table in TCM/LOVEC */
    mrc     p15, 0, r0, c1, c0, 0
    mvn     r1, #0x2000
    and     r0, r0, r1
    mcr     p15, 0, r0, c1, c0, 0

    /* Clear VINITHI to enable LOVEC on reset */
#if 1
    ldr     r0, =RPU_0_CFG
#else
    ldr     r0, =RPU_1_CFG
#endif
    ldr     r1, [r0]
    bic     r1, r1, #(0x1 << 2)
    str     r1, [r0]

    /* enable asynchronous abort exception */
    mrs     r0, cpsr
    bic     r0, r0, #0x100
    msr     cpsr_xsf, r0

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

    bl  Xil_InitializeExistingMPURegConfig  /* Initialize MPU config */
    /* start RT-Thread Kernel       */
    ldr     pc, _entry

_entry:
    .word entry

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
    sub     r0, r0, #FIQ_Stack_Size

    @  Enter IRQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_IRQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #IRQ_Stack_Size

    @  Switch back to SVC
    msr     cpsr_c, #Mode_SVC|I_Bit|F_Bit

    bx      lr

.section .text.isr, "ax"
/* exception handlers: undef, swi, padt, dabt, resv, irq, fiq          */
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

    .align  5
.globl vector_irq
vector_irq:
    stmfd   sp!, {r0-r12,lr}
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    vstmdb sp!, {d0-d15}     /* Store floating point registers */
    vmrs r1, FPSCR
    stmfd sp!,{r1}
    vmrs r1, FPEXC
    stmfd sp!,{r1}
#endif

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

    @ if rt_thread_switch_interrupt_flag set, jump to
    @ rt_hw_context_switch_interrupt_do and don't return
    ldr     r0, =rt_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq rt_hw_context_switch_interrupt_do

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif
    ldmfd   sp!, {r0-r12,lr}
    subs    pc, lr, #4

rt_hw_context_switch_interrupt_do:
    mov     r1,  #0         @ clear flag
    str     r1,  [r0]

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    mov     r1, sp          @ r1 point to {r0-r3} in stack
    add     sp, sp, #4*4
    ldmfd   sp!, {r4-r12,lr}@ reload saved registers
    mrs     r0,  spsr       @ get cpsr of interrupt thread
    sub     r2,  lr, #4     @ save old task's pc to r2

    @ Switch to SVC mode with no interrupt.
    msr     cpsr_c, #I_Bit|F_Bit|Mode_SVC

    stmfd   sp!, {r2}       @ push old task's pc
    stmfd   sp!, {r4-r12,lr}@ push old task's lr,r12-r4
    ldmfd   r1,  {r1-r4}    @ restore r0-r3 of the interrupt thread
    stmfd   sp!, {r1-r4}    @ push old task's r0-r3
    stmfd   sp!, {r0}       @ push old task's cpsr

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    vstmdb sp!, {d0-d15}    /* Store floating point registers */
    vmrs r1, FPSCR
    stmfd sp!,{r1}
    vmrs r1, FPEXC
    stmfd sp!,{r1}
#endif

    ldr     r4,  =rt_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]       @ store sp in preempted tasks's TCB

    ldr     r6,  =rt_interrupt_to_thread
    ldr     r7,  [r6]
    ldr     sp,  [r7]       @ get new task's stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

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
