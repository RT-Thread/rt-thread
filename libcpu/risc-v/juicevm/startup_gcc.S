/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/04/24     Juice      The first version
 */


.global   _start
.section ".start", "ax"
_start:
.align 3
csrw mideleg, 0
csrw medeleg, 0
csrw mie, 0
csrw mip, 0
la t0, trap_entry
csrw mtvec, t0

li x1, 0
li x2, 0
li x3, 0
li x4, 0
li x5, 0
li x6, 0
li x7, 0
li x8, 0
li x9, 0
li x10, 0
li x11, 0
li x12, 0
li x13, 0
li x14, 0
li x15, 0
li x16, 0
li x17, 0
li x18, 0
li x19, 0
li x20, 0
li x21, 0
li x22, 0
li x23, 0
li x24, 0
li x25, 0
li x26, 0
li x27, 0
li x28, 0
li x29, 0
li x30, 0
li x31, 0

/* set to initial state of FPU and disable interrupt */
li t0, 0
csrs mstatus, t0

.option push
.option norelax
la gp, __global_pointer$
la   sp, __stack
call entry
call exit
.option pop
