/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2020-01-15     bigmagic     the first version
 * 2020-08-10     SummerGift   support clang compiler
 * 2021-11-04     GuEe-GUI     set sp with SP_ELx
 * 2021-12-28     GuEe-GUI     add smp support
 */

#include "rtconfig.h"

#define SECONDARY_STACK_SIZE 4096

.section ".text.entrypoint","ax"

.globl _start
.globl secondary_cpu_start
_start:
#ifdef RT_USING_SMP
    mrs     x1, mpidr_el1
    adr     x4, .boot_cpu_mpidr
    str     x1, [x4]
    dsb     sy
#endif

    bl      __asm_flush_dcache_all  /* The kernel and data must flush to DDR */

secondary_cpu_start:
#ifdef RT_USING_SMP
    adr     x4, .boot_cpu_mpidr
    ldr     x4, [x4]
    dsb     sy
    /* Read cpu mpidr_el1 */
    mrs     x1, mpidr_el1

    /* Read cpu id */
    ldr     x0, =rt_cpu_mpidr_early /* BSP must be defined `rt_cpu_mpidr_early' table in smp */
    mov     x2, #0

cpu_id_confirm:
    add     x2, x2, #1              /* Next cpu id inc */
    ldr     x3, [x0], #8
    dsb     sy
    cmp     x3, #0
    beq     cpu_idle                /* Mean that `rt_cpu_mpidr_early' table is end */
    cmp     x3, x1
    bne     cpu_id_confirm

    /* Get cpu id success */
    sub     x0, x2, #1
    msr     tpidr_el1, x0           /* Save cpu id global */
    cmp     x3, x4                  /* If it is boot cpu */
    beq     boot_cpu_setup

    /* Set current cpu's stack top */
    sub     x0, x0, #1
    mov     x1, #SECONDARY_STACK_SIZE
    adr     x2, .secondary_cpu_stack_top
    msub    x1, x0, x1, x2

    b       cpu_check_el
#else
    msr     tpidr_el1, xzr
#endif /* RT_USING_SMP */

boot_cpu_setup:
    ldr     x1, =_start

cpu_check_el:
    mrs     x0, CurrentEL           /* CurrentEL Register. bit 2, 3. Others reserved */
    and     x0, x0, #12             /* Clear reserved bits */

    /* Running at EL3? */
    cmp     x0, #12                 /* EL3 value is 0b1100 */
    bne     cpu_not_in_el3

    /* Should never be executed, just for completeness. (EL3) */
    mov     x2, #(1 << 0)           /* EL0 and EL1 are in Non-Secure state */
    orr     x2, x2, #(1 << 4)       /* RES1 */
    orr     x2, x2, #(1 << 5)       /* RES1 */
    bic     x2, x2, #(1 << 7)       /* SMC instructions are enabled at EL1 and above */
    orr     x2, x2, #(1 << 8)       /* HVC instructions are enabled at EL1 and above */
    orr     x2, x2, #(1 << 10)      /* The next lower level is AArch64 */
    msr     scr_el3, x2

    mov     x2, #9                  /* Next level is 0b1001->EL2h */
    orr     x2, x2, #(1 << 6)       /* Mask FIQ */
    orr     x2, x2, #(1 << 7)       /* Mask IRQ */
    orr     x2, x2, #(1 << 8)       /* Mask SError */
    orr     x2, x2, #(1 << 9)       /* Mask Debug Exception */
    msr     spsr_el3, x2
    adr     x2, cpu_in_el2
    msr     elr_el3, x2
    eret

cpu_not_in_el3:                     /* Running at EL2 or EL1 */
    cmp     x0, #4                  /* EL1 = 0100 */
    beq     cpu_in_el1

cpu_in_el2:
    /* Enable CNTP for EL1 */
    mrs     x0, cnthctl_el2         /* Counter-timer Hypervisor Control register */
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr

    mov     x0, #(1 << 31)          /* Enable AArch64 in EL1 */
    orr     x0, x0, #(1 << 1)       /* SWIO hardwired on Pi3 */
    msr     hcr_el2, x0

    mov     x2, #5                  /* Next level is 0b0101->EL1h */
    orr     x2, x2, #(1 << 6)       /* Mask FIQ */
    orr     x2, x2, #(1 << 7)       /* Mask IRQ */
    orr     x2, x2, #(1 << 8)       /* Mask SError */
    orr     x2, x2, #(1 << 9)       /* Mask Debug Exception */
    msr     spsr_el2, x2
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

#ifdef RT_USING_SMP
    ldr     x1, =_start
    cmp     sp, x1
    bne     secondary_cpu_c_start
#endif /* RT_USING_SMP */

    ldr     x0, =__bss_start
    ldr     x1, =__bss_end
    sub     x2, x1, x0
    mov     x3, x1
    cmp     x2, #7
    bls     clean_bss_check

clean_bss_loop_quad:
    str     xzr, [x0], #8
    sub     x2, x3, x0
    cmp     x2, #7
    bhi     clean_bss_loop_quad
    cmp     x1, x0
    bls     jump_to_entry

clean_bss_loop_byte:
    str     xzr, [x0], #1

clean_bss_check:
    cmp     x1, x0
    bhi     clean_bss_loop_byte

jump_to_entry:
    b       rtthread_startup

cpu_idle:
    wfe
    b       cpu_idle

#ifdef RT_USING_SMP
.align 3
.boot_cpu_mpidr:
    .quad 0x0

.align 12
.secondary_cpu_stack:
.space (SECONDARY_STACK_SIZE * (RT_CPUS_NR - 1))
.secondary_cpu_stack_top:
#endif
