/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2020-01-15     bigmagic     the first version
 * 2020-08-10     SummerGift   support clang compiler
 * 2021-11-04     GuEe-GUI     set sp with SP_ELx
 */

.section ".text.entrypoint","ax"

.globl _start
_start:
    /* Read cpu id */
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, cpu_setup           /* If cpu id > 0, stop slave cores */

cpu_idle:
    wfe
    b       cpu_idle

cpu_setup:
    ldr     x1, =_start

    mrs     x0, CurrentEL           /* CurrentEL Register. bit 2, 3. Others reserved */
    and     x0, x0, #12             /* Clear reserved bits */

    /* Running at EL3? */
    cmp     x0, #12                 /* EL3 value is 0b1100 */
    bne     cpu_not_in_el3

    /* Should never be executed, just for completeness. (EL3) */
    mov     x2, #(1 << 0)           /* EL0 and EL1 are in Non-Secure state */
    orr     x2, x2, #(1 << 4)       /* RES1 */
    orr     x2, x2, #(1 << 5)       /* RES1 */
    orr     x2, x2, #(1 << 7)       /* SMC instructions are undefined at EL1 and above */
    orr     x2, x2, #(1 << 8)       /* HVC instructions are enabled at EL1 and above */
    orr     x2, x2, #(1 << 10)      /* The next lower level is AArch64 */
    msr     scr_el3, x2

    /* Change execution level to EL2 */
    mov     x2, #0x3c9
    msr     spsr_el3, x2            /* 0b1111001001 */
    adr     x2, cpu_not_in_el3
    msr     elr_el3, x2
    eret                            /* Exception Return: from EL3, continue from cpu_not_in_el3 */

cpu_not_in_el3:                     /* Running at EL2 or EL1 */
    cmp     x0, #4                  /* EL1 = 0100  */
    beq     cpu_in_el1              /* Halt this core if running in El1 */

cpu_in_el2:
    /* Enable CNTP for EL1 */
    mrs     x0, cnthctl_el2         /* Counter-timer Hypervisor Control register */
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr

    mov     x0, #(1 << 31)          /* Enable AArch64 in EL1 */
    orr     x0, x0, #(1 << 1)       /* SWIO hardwired on Pi3 */
    msr     hcr_el2, x0

    /* Change execution level to EL1 */
    mov     x2, #0x3c4
    msr     spsr_el2, x2            /* 0b1111000100 */
    adr     x2, cpu_in_el1
    msr     elr_el2, x2
    eret

cpu_in_el1:
    msr     spsel, #1
    mov     sp, x1                  /* Set sp in el1 */

    /* Avoid trap from SIMD or float point instruction */
    mov     x1, #0x00300000         /* Don't trap any SIMD/FP instructions in both EL0 and EL1 */
    msr     cpacr_el1, x1

    mrs     x1, sctlr_el1
    orr     x1, x1, #(1 << 12)      /* Enable Instruction */
    bic     x1, x1, #(3 << 3)       /* Disable SP Alignment check */
    bic     x1, x1, #(1 << 1)       /* Disable Alignment check */
    msr     sctlr_el1, x1

    ldr     x1, =__bss_start
    ldr     w2, =__bss_size

clean_bss_loop:
    cbz     w2, jump_to_entry
    str     xzr, [x1], #8
    sub     w2, w2, #8
    cbnz    w2, clean_bss_loop

jump_to_entry:
    b       rtthread_startup
    b       cpu_idle                /* For failsafe, halt this core too */
