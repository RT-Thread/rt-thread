;/*
; * File      : start_gcc.S
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
#include "sifive/smp.h"
#define CLINT_CTRL_ADDR 0x02000000

.section .init
.globl _start
.type _start,@function

_start:
    .cfi_startproc
    .cfi_undefined ra
.option push
.option norelax
    la gp, __global_pointer$
.option pop
    la sp, _sp
/*
 *disable all interrupt at startup
 */
    csrrc a5, mstatus, 0xb

#if defined(ENABLE_SMP)
    smp_pause(t0, t1)
#endif

    /* Load data section */
    la a0, _data_lma
    la a1, _data
    la a2, _edata
    bgeu a1, a2, 2f
1:
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:

    /* Clear bss section */
    la a0, __bss_start
    la a1, _end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b
2:

    /* Call global constructors */
    la a0, __libc_fini_array
    call atexit
    call __libc_init_array
    /*call _init directly in rt-thread*/
        call _init

#ifndef __riscv_float_abi_soft
    /* Enable FPU */
    li t0, MSTATUS_FS
    csrs mstatus, t0
    csrr t1, mstatus
    and t1, t1, t0
    beqz t1, 1f
    fssr x0
1:
#endif

#if defined(ENABLE_SMP)
    smp_resume(t0, t1)

    csrr a0, mhartid
    bnez a0, 2f
#endif

    auipc ra, 0
    addi sp, sp, -16
#if __riscv_xlen == 32
    sw ra, 8(sp)
#else
    sd ra, 8(sp)
#endif

    /* argc = argv = 0 */
    li a0, 0
    li a1, 0
    call main
    tail exit
1:
    j 1b

#if defined(ENABLE_SMP)
2:
    la t0, trap_entry
    csrw mtvec, t0

    csrr a0, mhartid
    la t1, _sp
    slli t0, a0, 10
    sub sp, t1, t0

    auipc ra, 0
    addi sp, sp, -16
#if __riscv_xlen == 32
    sw ra, 8(sp)
#else
    sd ra, 8(sp)
#endif

    call secondary_main
    tail exit

1:
    j 1b
#endif
    .cfi_endproc

#include "encoding.h"
#include "sifive/bits.h"

  .section      .text.entry 
  .align 2
  .global trap_entry
trap_entry:
  addi  sp,  sp, -32*REGBYTES

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
  csrr  x10, mepc
  STORE x10, 31*REGBYTES(sp)
  csrr  x10, mie
  STORE x10, 0*REGBYTES(sp)


/*
 *Remain in M-mode after mret
 *enable interrupt in M-mode
 */
  li    t0, MSTATUS_MPP
  csrrs t0, mstatus, t0

  call rt_interrupt_enter
  csrr a0, mcause
  lui  a5, 0x80000 
  not  a5, a5
  and  a5, a5, a0
  li   a4, 11
  mv   s1, a1
  /*Machine external interrupt*/
  bne  a5, a4, 1f
  call rt_hw_trap_irq
1:
  /*Machine timer interrupt*/
  li   a4, 7
  bne  a5, a4, 2f
  call rt_systick_handler
2:
  call rt_interrupt_leave

  la   a0, rt_thread_switch_interrupt_flag
  lw   a1, (a0)
  bnez a1, rt_hw_context_switch_interrupt_do


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

rt_hw_context_switch_interrupt_do:
  /*clear rt_thread_switch_interrupt_flag*/
  la   a0, rt_thread_switch_interrupt_flag
  li   a5, 0
  sw   a5, (a0)

  LOAD a0,  rt_interrupt_from_thread
  STORE sp,  (a0)
  LOAD a0,  rt_interrupt_to_thread
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
  csrw mepc,x10
  LOAD x10, 0*REGBYTES(sp)
  csrw mie, x10
  LOAD x10, 29*REGBYTES(sp)
  LOAD x1,  30*REGBYTES(sp)
  
  addi sp, sp, 32*REGBYTES
  mret
