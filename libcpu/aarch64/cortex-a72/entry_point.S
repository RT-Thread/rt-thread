/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2020-01-15     bigmagic    the first version
 */

.section ".text.entrypoint"

.set EL1_stack,         __el1_stack

.global _start

// This symbol is set to 0x80000 in ld script. That is the address that raspi3's firmware
// loads 'kernel8.img' file in.
_start:
    // read cpu id, stop slave cores
    mrs     x1, mpidr_el1            // MPIDR_EL1: Multi-Processor Affinity Register
    and     x1, x1, #3
    cbz     x1, .L__cpu_0             // .L prefix is the local label in ELF 

    // cpu id > 0, stop
    // cpu id == 0 will also goto here after returned from entry() if possible
.L__current_cpu_idle:
    wfe
    b       .L__current_cpu_idle

.L__cpu_0:  // cpu id == 0

    // set stack before our code

	/* Define stack pointer for current exception level */
	// ldr	x2, =EL1_stack
	// mov	sp, x2

    ldr     x1, =_start

    // set up EL1
    mrs     x0, CurrentEL           // CurrentEL Register. bit 2, 3. Others reserved
    and     x0, x0, #12             // clear reserved bits

    // running at EL3?
    cmp     x0, #12                // 1100b. So, EL3
    bne     .L__not_in_el3         // 11?  !EL3 -> 5:

    // should never be executed, just for completeness. (EL3)
    mov     x2, #0x5b1
    msr     scr_el3, x2            // SCR_ELn  Secure Configuration Register
    mov     x2, #0x3c9
    msr     spsr_el3, x2           // SPSR_ELn. Saved Program Status Register. 1111001001
    adr     x2, .L__not_in_el3   
    msr     elr_el3, x2
    eret                           // Exception Return: from EL3, continue from .L__not_in_el3

    // running at EL2 or EL1
.L__not_in_el3:    
    cmp     x0, #4                 // 0x04  0100 EL1
    beq     .L__in_el1             // EL1 -> 5:

    // in EL2
    msr     sp_el1, x1             // Set sp of EL1 to _start

    // enable CNTP for EL1
    mrs     x0, cnthctl_el2         // Counter-timer Hypervisor Control register
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr

    // enable AArch64 in EL1
    mov     x0, #(1 << 31)          // AArch64
    orr     x0, x0, #(1 << 1)       // SWIO hardwired on Pi3
    msr     hcr_el2, x0
    mrs     x0, hcr_el2

    // change execution level to EL1
    mov     x2, #0x3c4
    msr     spsr_el2, x2        // 1111000100
    adr     x2, .L__in_el1
    msr     elr_el2, x2
    eret                        // exception return. from EL2. continue from .L__in_el1

.L__in_el1:
    mov     sp, x1             // in EL1. Set sp to _start

    // Set CPACR_EL1 (Architecture Feature Access Control Register) to avoid trap from SIMD or float point instruction
    mov     x1, #0x00300000       // Don't trap any SIMD/FP instructions in both EL0 and EL1
    msr     cpacr_el1, x1

    mrs x1, sctlr_el1
    orr x1, x1, #(1 << 12)
    bic x1, x1, #(3 << 3)
    bic x1, x1, #(1 << 1)
    msr sctlr_el1, x1

    // clear bss
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size

.L__clean_bss_loop:
    cbz     w2, .L__jump_to_entry
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, .L__clean_bss_loop

    // jump to C code, should not return
.L__jump_to_entry:
    bl      entry
    // for failsafe, halt this core too
    b       .L__current_cpu_idle
