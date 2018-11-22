/*
 * File      : context_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-29     tanek        first implementation
 */

  .section      .text.entry
  .align 2
  .global trap_entry
trap_entry:

    // save all from thread context
    addi sp, sp, -32 * 4

    sw x1,   1 * 4(sp)
    li t0, 0x80
    sw t0,   2 * 4(sp)

    sw x4,   4 * 4(sp)
    sw x5,   5 * 4(sp)
    sw x6,   6 * 4(sp)
    sw x7,   7 * 4(sp)
    sw x8,   8 * 4(sp)
    sw x9,   9 * 4(sp)
    sw x10, 10 * 4(sp)
    sw x11, 11 * 4(sp)
    sw x12, 12 * 4(sp)
    sw x13, 13 * 4(sp)
    sw x14, 14 * 4(sp)
    sw x15, 15 * 4(sp)
    sw x16, 16 * 4(sp)
    sw x17, 17 * 4(sp)
    sw x18, 18 * 4(sp)
    sw x19, 19 * 4(sp)
    sw x20, 20 * 4(sp)
    sw x21, 21 * 4(sp)
    sw x22, 22 * 4(sp)
    sw x23, 23 * 4(sp)
    sw x24, 24 * 4(sp)
    sw x25, 25 * 4(sp)
    sw x26, 26 * 4(sp)
    sw x27, 27 * 4(sp)
    sw x28, 28 * 4(sp)
    sw x29, 29 * 4(sp)
    sw x30, 30 * 4(sp)
    sw x31, 31 * 4(sp)

    // switch to interrupt stack
    move s0, sp
    la   sp, _sp

    // interrupt handle
    call rt_interrupt_enter
    csrr a0, mcause
    csrr a1, mepc
    mv a2, sp
    call handle_trap
    call rt_interrupt_leave

    // switch to from thread stack
    move sp, s0

    // need to switch new thread
    la   s0, rt_thread_switch_interrupt_flag
    lw   s2, 0(s0)
    beqz s2, spurious_interrupt
    sw   zero, 0(s0)

    csrr a0, mepc
    sw a0,  0 * 4(sp)

    la   s0, rt_interrupt_from_thread
    lw   s1, 0(s0)
    sw   sp, 0(s1)

    la   s0, rt_interrupt_to_thread
    lw   s1, 0(s0)
    lw   sp, 0(s1)

    lw  a0,  0 * 4(sp)
    csrw mepc, a0

spurious_interrupt:
    lw x1,   1 * 4(sp)
    
    // Remain in M-mode after mret
    li t0, 0x00001800
    csrs mstatus, t0
    lw t0,   2 * 4(sp)
    csrs mstatus, t0 
    
    lw x4,   4 * 4(sp)
    lw x5,   5 * 4(sp)
    lw x6,   6 * 4(sp)
    lw x7,   7 * 4(sp)
    lw x8,   8 * 4(sp)
    lw x9,   9 * 4(sp)
    lw x10, 10 * 4(sp)
    lw x11, 11 * 4(sp)
    lw x12, 12 * 4(sp)
    lw x13, 13 * 4(sp)
    lw x14, 14 * 4(sp)
    lw x15, 15 * 4(sp)
    lw x16, 16 * 4(sp)
    lw x17, 17 * 4(sp)
    lw x18, 18 * 4(sp)
    lw x19, 19 * 4(sp)
    lw x20, 20 * 4(sp)
    lw x21, 21 * 4(sp)
    lw x22, 22 * 4(sp)
    lw x23, 23 * 4(sp)
    lw x24, 24 * 4(sp)
    lw x25, 25 * 4(sp)
    lw x26, 26 * 4(sp)
    lw x27, 27 * 4(sp)
    lw x28, 28 * 4(sp)
    lw x29, 29 * 4(sp)
    lw x30, 30 * 4(sp)
    lw x31, 31 * 4(sp)

    addi sp, sp, 32 * 4
    mret

.weak handle_trap
handle_trap:
1:
    j 1b
