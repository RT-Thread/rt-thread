/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Hart 0: clear BSS, enter RT-Thread.
 * Hart 1: wait for secondary_boot_flag, then secondary_cpu_c_start.
 */

#include <rtconfig.h>

/* Must match __STACKSIZE__ in link.lds */
.equ STACK_SIZE, 8192

    .section .start, "ax"
    .globl _start
    .align 2
_start:
    /* Enable C907 cache coherency before sharing DRAM. */
    li      t0, 1
    csrw    0x7f3, t0          /* msmpr */
    csrr    t0, 0x7c0          /* mxstatus */
    li      t1, (1 << 17)      /* CLINTEE */
    or      t0, t0, t1
    csrw    0x7c0, t0

    la      t0, trap_entry
    csrw    mtvec, t0

    .option push
    .option norelax
    la      gp, __global_pointer$
    .option pop

    csrr    a0, mhartid
    la      sp, __stack_start__
    addi    t1, a0, 1
    li      t2, STACK_SIZE
    mul     t1, t1, t2
    add     sp, sp, t1

    bnez    a0, secondary_cpu_entry
    j       primary_cpu_entry

primary_cpu_entry:
    la      a0, __bss_start
    la      a1, __bss_end
.Lbss:
    bgeu    a0, a1, .Lbss_done
    sw      zero, 0(a0)
    addi    a0, a0, 4
    j       .Lbss
.Lbss_done:
    call    entry

.Lpark:
    wfi
    j       .Lpark

secondary_cpu_entry:
#ifdef RT_USING_SMP
1:
    la      t0, secondary_boot_flag
    lw      t0, 0(t0)
    li      t1, 0xa55a
    beq     t0, t1, 2f
    j       1b
2:
    call    secondary_cpu_c_start
#endif
    j       .Lpark

#ifdef RT_USING_SMP
    .data
    .globl secondary_boot_flag
    .align 2
secondary_boot_flag:
    .word  0
#endif
