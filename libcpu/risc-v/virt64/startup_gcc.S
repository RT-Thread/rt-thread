/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 * 2018/12/27     Jesven       Add SMP support
 * 2020/6/12      Xim          Port to QEMU and remove SMP support
 * 2024-06-30     Shell        Support of kernel remapping
 */

#include <encoding.h>
#include <cpuport.h>

    .data
    .global boot_hartid    /* global varible rt_boot_hartid in .data section */
boot_hartid:
    .word 0xdeadbeef

    .global         _start
    .section ".start", "ax"
_start:
    j 1f
    .word 0xdeadbeef
    .align 3
    .global g_wake_up
    g_wake_up:
        .dword 1
        .dword 0
1:
    /* save hartid */
    la t0, boot_hartid                /* global varible rt_boot_hartid */
    mv t1, a0                         /* get hartid in S-mode frome a0 register */
    sw t1, (t0)                       /* store t1 register low 4 bits in memory address which is stored in t0 */

    /* clear Interrupt Registers */
    csrw sie, 0
    csrw sip, 0
    /* set Trap Vector Base Address Register */
    la t0, trap_entry
    csrw stvec, t0

    li x1, 0
    li x2, 0
    li x3, 0
    li x4, 0
    li x5, 0
    li x6, 0
    li x7, 0
    li x8, 0
    li x9, 0
    li x10,0
    li x11,0
    li x12,0
    li x13,0
    li x14,0
    li x15,0
    li x16,0
    li x17,0
    li x18,0
    li x19,0
    li x20,0
    li x21,0
    li x22,0
    li x23,0
    li x24,0
    li x25,0
    li x26,0
    li x27,0
    li x28,0
    li x29,0
    li x30,0
    li x31,0

    /* set to disable FPU */
    li t0, SSTATUS_FS + SSTATUS_VS
    csrc sstatus, t0
    li t0, SSTATUS_SUM
    csrs sstatus, t0

.option push
.option norelax
    la gp, __global_pointer$
.option pop

    /* removed SMP support here */
    la   sp, __stack_start__
    li   t0, __STACKSIZE__
    add  sp, sp, t0

    /**
     * sscratch is always zero on kernel mode
     */
    csrw sscratch, zero
    call init_bss
#ifdef ARCH_MM_MMU
    call    rt_hw_mem_setup_early
    call    rt_kmem_pvoff
    /* a0 := pvoff  */
    beq     a0, zero, 1f

    /* relocate pc */
    la      x1, _after_pc_relocation
    sub     x1, x1, a0
    ret
_after_pc_relocation:
    /* relocate gp */
    sub     gp, gp, a0

    /* relocate context: sp */
    la      sp, __stack_start__
    li      t0, __STACKSIZE__
    add     sp, sp, t0

    /* reset s0-fp */
    mv      s0, zero

    /* relocate stvec */
    la      t0, trap_entry
    csrw    stvec, t0
1:
#endif
    call    sbi_init
    call    primary_cpu_entry

_never_return_here:
    j       .

.global _start_link_addr
_start_link_addr:
    .dword __text_start
