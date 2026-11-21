/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * E907 entry: no C907 msmpr / SMP secondary path.
 */

    .section .start, "ax"
    .globl _start
    .align 2
_start:
    /* Match e907-dual style: touch mxstatus, then continue. */
    li      t0, 0x00400000
    csrs    0x7c0, t0
    fence.i

    la      t0, trap_entry
    csrw    mtvec, t0

    .option push
    .option norelax
    la      gp, __global_pointer$
    .option pop

    la      sp, __rt_rvstack

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
