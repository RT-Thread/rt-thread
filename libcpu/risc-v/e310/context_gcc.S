;/*
; * File      : context_gcc.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006, RT-Thread Development Team
; *
; *  This program is free software; you can redistribute it and/or modify
; *  it under the terms of the GNU General Public License as published by
; *  the Free Software Foundation; either version 2 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License along
; *  with this program; if not, write to the Free Software Foundation, Inc.,
; *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
; *
; * Change Logs:
; * Date           Author       Notes
; * 2017-07-16     zhangjun    for hifive1
; */

#include "encoding.h"
#include "sifive/bits.h"

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
    .globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
  addi sp, sp, -12
  sw a5, (sp)
  li a5, 0x800
  csrr a0, mie
  blt a0, a5, 1f
/*  interrupt is enable before disable it*/
  addi a0, a0, 1

  li a5, 0x1
  addi a5, a5, -2048
  csrrc a5, mie, a5
/*  csrrc a5, mie, 128*/
  j 2f
/*  interrupt is disabled before disable it*/
1:
  li a0, 0
2:
  lw a5, (sp)
  addi sp, sp, 12
  ret

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
    .globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
  addi sp, sp, -12
  sw a5, (sp)
  beqz a0, 1f
  li a5, 0x1
  addi a5, a5, -2048
  csrrs a5, mie, a5
/*  csrrs a5, mie, 128*/
1:
  lw a5, (sp)
  addi sp, sp, 12
  ret

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * a0 --> from
 * a1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
  addi  sp,  sp, -32*REGBYTES

  STORE sp,  (a0)
  STORE x30, 1*REGBYTES(sp)
  STORE x31, 2*REGBYTES(sp)
  STORE x3,  3*REGBYTES(sp)
  STORE x4,  4*REGBYTES(sp)
  STORE x5,  5*REGBYTES(sp)
  STORE x6,  6*REGBYTES(sp)
  STORE x7,  7*REGBYTES(sp)
  STORE x8,  8*REGBYTES(sp)
  STORE x9,  9*REGBYTES(sp)
  STORE x10, 10*REGBYTES(sp)
  STORE x11, 11*REGBYTES(sp)
  STORE x12, 12*REGBYTES(sp)
  STORE x13, 13*REGBYTES(sp)
  STORE x14, 14*REGBYTES(sp)
  STORE x15, 15*REGBYTES(sp)
  STORE x16, 16*REGBYTES(sp)
  STORE x17, 17*REGBYTES(sp)
  STORE x18, 18*REGBYTES(sp)
  STORE x19, 19*REGBYTES(sp)
  STORE x20, 20*REGBYTES(sp)
  STORE x21, 21*REGBYTES(sp)
  STORE x22, 22*REGBYTES(sp)
  STORE x23, 23*REGBYTES(sp)
  STORE x24, 24*REGBYTES(sp)
  STORE x25, 25*REGBYTES(sp)
  STORE x26, 26*REGBYTES(sp)
  STORE x27, 27*REGBYTES(sp)
  STORE x28, 28*REGBYTES(sp)
  STORE x10, 29*REGBYTES(sp)
  STORE x1,  30*REGBYTES(sp)
  STORE x1,  31*REGBYTES(sp)
  csrr  x10, mie
  STORE x10, 0*REGBYTES(sp)
/*
 *Remain in M-mode after mret
 *enable interrupt in M-mode
 */
  li t0, 136
  csrrs t0, mstatus, t0

  LOAD sp,  (a1)
  LOAD x30, 1*REGBYTES(sp)
  LOAD x31, 2*REGBYTES(sp)
  LOAD x3,  3*REGBYTES(sp)
  LOAD x4,  4*REGBYTES(sp)
  LOAD x5,  5*REGBYTES(sp)
  LOAD x6,  6*REGBYTES(sp)
  LOAD x7,  7*REGBYTES(sp)
  LOAD x8,  8*REGBYTES(sp)
  LOAD x9,  9*REGBYTES(sp)
  LOAD x29, 10*REGBYTES(sp)
  LOAD x11, 11*REGBYTES(sp)
  LOAD x12, 12*REGBYTES(sp)
  LOAD x13, 13*REGBYTES(sp)
  LOAD x14, 14*REGBYTES(sp)
  LOAD x15, 15*REGBYTES(sp)
  LOAD x16, 16*REGBYTES(sp)
  LOAD x17, 17*REGBYTES(sp)
  LOAD x18, 18*REGBYTES(sp)
  LOAD x19, 19*REGBYTES(sp)
  LOAD x20, 20*REGBYTES(sp)
  LOAD x21, 21*REGBYTES(sp)
  LOAD x22, 22*REGBYTES(sp)
  LOAD x23, 23*REGBYTES(sp)
  LOAD x24, 24*REGBYTES(sp)
  LOAD x25, 25*REGBYTES(sp)
  LOAD x26, 26*REGBYTES(sp)
  LOAD x27, 27*REGBYTES(sp)
  LOAD x28, 28*REGBYTES(sp)
  LOAD x10, 31*REGBYTES(sp)
  csrw mepc,x10
  LOAD x10, 0*REGBYTES(sp)
  csrw mie, x10
  LOAD x10, 29*REGBYTES(sp)
  LOAD x1,  30*REGBYTES(sp)
  
  addi sp,  sp, 32*REGBYTES
  mret
	
/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * a0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
  LOAD sp,  (a0)
  LOAD x30, 1*REGBYTES(sp)
  LOAD x31, 2*REGBYTES(sp)
  LOAD x3,  3*REGBYTES(sp)
  LOAD x4,  4*REGBYTES(sp)
  LOAD x5,  5*REGBYTES(sp)
  LOAD x6,  6*REGBYTES(sp)
  LOAD x7,  7*REGBYTES(sp)
  LOAD x8,  8*REGBYTES(sp)
  LOAD x9,  9*REGBYTES(sp)
  LOAD x29, 10*REGBYTES(sp)
  LOAD x11, 11*REGBYTES(sp)
  LOAD x12, 12*REGBYTES(sp)
  LOAD x13, 13*REGBYTES(sp)
  LOAD x14, 14*REGBYTES(sp)
  LOAD x15, 15*REGBYTES(sp)
  LOAD x16, 16*REGBYTES(sp)
  LOAD x17, 17*REGBYTES(sp)
  LOAD x18, 18*REGBYTES(sp)
  LOAD x19, 19*REGBYTES(sp)
  LOAD x20, 20*REGBYTES(sp)
  LOAD x21, 21*REGBYTES(sp)
  LOAD x22, 22*REGBYTES(sp)
  LOAD x23, 23*REGBYTES(sp)
  LOAD x24, 24*REGBYTES(sp)
  LOAD x25, 25*REGBYTES(sp)
  LOAD x26, 26*REGBYTES(sp)
  LOAD x27, 27*REGBYTES(sp)
  LOAD x28, 28*REGBYTES(sp)
  LOAD x10, 31*REGBYTES(sp)
  csrw mepc,a0
  LOAD x10, 29*REGBYTES(sp)
  LOAD x1,  30*REGBYTES(sp)
  

  addi sp,  sp, 32*REGBYTES
  mret
	

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
    .globl rt_thread_switch_interrupt_flag
    .globl rt_interrupt_from_thread
    .globl rt_interrupt_to_thread
    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
  addi sp, sp, -16
  sw   s0, 12(sp)
  sw   a0, 8(sp)
  sw   a5, 4(sp)

  la   a0, rt_thread_switch_interrupt_flag
  lw   a5, (a0)
  bnez a5, _reswitch
  li   a5, 1
  sw   a5, (a0)

  la   a5, rt_interrupt_from_thread
  lw   a0, 8(sp)
  sw   a0, (a5)

_reswitch:
  la   a5, rt_interrupt_to_thread
  sw   a1, (a5)

  lw   a5, 4(sp)
  lw   a0, 8(sp)
  lw   s0, 12(sp)
  addi sp, sp, 16
  ret
