/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 * 2018/12/27     Jesven       Add SMP support
 * 2020/6/12      Xim          Port to QEMU and remove SMP support
 */

#define XSTATUS_FS         (3 << 13) /* initial state of FPU, clear to disable */
#define XSTATUS_PUM        (1 << 18)
#include <cpuport.h>

boot_hartid: .int
  .global      boot_hartid

  .global   _start
  .section ".start", "ax"
_start:
#ifdef RISCV_S_MODE
  # save hartid
  la t0, boot_hartid                # global varible rt_boot_hartid
  mv t1, a0                         # get hartid in S-mode frome a0 register
  sw t1, (t0)                       # store t1 register low 4 bits in memory address which is stored in t0
#else
  # setup stacks per hart
  csrr t0, mhartid                  # read current hart id
  slli t0, t0, 10                   # shift left the hart id by 1024

  # park harts with id != 0
  csrr a0, mhartid                  # read current hart id
  bnez a0, park                     # if we're not on the hart 0
#endif

  csrw SRC_XIE, 0                   # clear Interrupt Registers
  csrw SRC_XIP, 0

  la t0, trap_entry
  csrw SRC_XTVEC, t0                # set Trap Vector Base Address Register

  /* set to disable FPU */
  li t0, XSTATUS_FS                 # close fpu
  csrc SRC_XSTATUS, t0
#ifdef RISCV_S_MODE
  li t0, XSTATUS_PUM                # PUM has no effect
  csrs SRC_XSTATUS, t0
#endif

.option push
.option norelax
  la gp, __global_pointer$
.option pop

  la   sp, __stack_start__
  li   t0, __STACKSIZE__
  add  sp, sp, t0
  csrw SRC_XSCRATCH, sp
  j primary_cpu_entry

park:
    wfi
    j park
