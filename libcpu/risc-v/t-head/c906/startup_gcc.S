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
 */

#define __ASSEMBLY__
#define SSTATUS_FS      0x00006000U /* initial state of FPU, clear to disable */
#include <cpuport.h>

  .global	_start
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
  csrw sie, 0
  csrw sip, 0
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
  li t0, SSTATUS_FS
  csrc sstatus, t0
  li t0, 0x40000 // SUM in sstatus
  csrs sstatus, t0

.option push
.option norelax
  la gp, __global_pointer$
.option pop

  // removed SMP support here
  la   sp, __stack_start__
  li   t0, __STACKSIZE__
  add  sp, sp, t0
  csrw sscratch, sp
  j primary_cpu_entry
