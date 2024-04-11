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

.globl _reset
_reset:
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

        cpsid  if, #19

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        @ Turn on FPV coprocessor
        mrc   p15,     #0x00,      r2,       c1, c0, #0x02
        orr   r2,      r2,         #0xF00000
        mcr   p15,     #0x00,      r2,       c1, c0, #0x02

        fmrx  r2,      fpexc
        orr   r2,      r2,   #0x40000000
        fmxr  fpexc,   r2
#endif

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

        bl    next1
next1:
        bl    next2
next2:
        bl    next3
next3:
        bl    next4
next4:
        ldr  lr, =_c_int00
        bx   lr

.globl data_init
data_init:
        /* copy .data to SRAM */
        ldr     r1, =_mdata            /* .data start in image */
        ldr     r2, =_data_end             /* .data end in image   */
        ldr     r3, =_data_start             /* sram data start      */
data_loop:
        ldr     r0, [r1, #0]
        str     r0, [r3]

        add     r1, r1, #4
        add     r3, r3, #4

        cmp     r3, r2                   /* check if data to clear */
        blo     data_loop                /* loop until done        */

        /* clear .bss */
        mov     r0,#0                   /* get a zero */
        ldr     r1,=__bss_start__         /* bss start  */
        ldr     r2,=__bss_end__           /* bss end    */

bss_loop:
        cmp     r1,r2                   /* check if data to clear */
        strlo   r0,[r1],#4              /* clear 4 bytes          */
        blo     bss_loop                /* loop until done        */

    /* call C++ constructors of global objects                          */
    ldr     r0, =__ctors_start__
    ldr     r1, =__ctors_end__

ctor_loop:
    cmp     r0, r1
    beq     ctor_end
    ldr     r2, [r0], #4
    stmfd   sp!, {r0-r3, ip, lr}
    mov     lr, pc
    bx      r2
    ldmfd   sp!, {r0-r3, ip, lr}
    b       ctor_loop
ctor_end:
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

    .globl  vector_svc
vector_svc:
        push_svc_reg
        bl      rt_hw_trap_svc
        b       .

    .globl  vector_pabort
vector_pabort:
        push_svc_reg
        bl      rt_hw_trap_pabt
        b       .

    .globl  vector_dabort
vector_dabort:
        push_svc_reg
        bl      rt_hw_trap_dabt
        b       .

    .globl  vector_resv
vector_resv:
        push_svc_reg
        bl      rt_hw_trap_resv
        b       .
