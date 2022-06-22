/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/04/24     Juice      The first version
 */

#include "cpuport.h"

.section      .text.entry
.align 2
.global trap_entry
trap_entry:

/* save thread context to thread stack */
addi sp, sp, -32 * REGBYTES

STORE x1,   1 * REGBYTES(sp)

csrr  x1, mstatus
STORE x1,   2 * REGBYTES(sp)

csrr  x1, mepc
STORE x1, 0 * REGBYTES(sp)

STORE x4,   4 * REGBYTES(sp)
STORE x5,   5 * REGBYTES(sp)
STORE x6,   6 * REGBYTES(sp)
STORE x7,   7 * REGBYTES(sp)
STORE x8,   8 * REGBYTES(sp)
STORE x9,   9 * REGBYTES(sp)
STORE x10, 10 * REGBYTES(sp)
STORE x11, 11 * REGBYTES(sp)
STORE x12, 12 * REGBYTES(sp)
STORE x13, 13 * REGBYTES(sp)
STORE x14, 14 * REGBYTES(sp)
STORE x15, 15 * REGBYTES(sp)
STORE x16, 16 * REGBYTES(sp)
STORE x17, 17 * REGBYTES(sp)
STORE x18, 18 * REGBYTES(sp)
STORE x19, 19 * REGBYTES(sp)
STORE x20, 20 * REGBYTES(sp)
STORE x21, 21 * REGBYTES(sp)
STORE x22, 22 * REGBYTES(sp)
STORE x23, 23 * REGBYTES(sp)
STORE x24, 24 * REGBYTES(sp)
STORE x25, 25 * REGBYTES(sp)
STORE x26, 26 * REGBYTES(sp)
STORE x27, 27 * REGBYTES(sp)
STORE x28, 28 * REGBYTES(sp)
STORE x29, 29 * REGBYTES(sp)
STORE x30, 30 * REGBYTES(sp)
STORE x31, 31 * REGBYTES(sp)

/* switch to interrupt stack */
move  s0, sp

/* handle interrupt */
call  rt_interrupt_enter
csrr  a0, mcause
csrr  a1, mepc
mv    a2, s0
call  handle_trap
call  rt_interrupt_leave


/* switch to from_thread stack */
move  sp, s0

/* need to switch new thread */
la    s0, rt_thread_switch_interrupt_flag
lw    s2, 0(s0)
beqz  s2, spurious_interrupt
sw    zero, 0(s0)

la    s0, rt_interrupt_from_thread
LOAD  s1, 0(s0)
STORE sp, 0(s1)

la    s0, rt_interrupt_to_thread
LOAD  s1, 0(s0)
LOAD  sp, 0(s1)

spurious_interrupt:
tail rt_hw_context_switch_exit
