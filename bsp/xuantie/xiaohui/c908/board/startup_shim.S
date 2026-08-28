/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mem_layout.h"

    .section .boot.text, "ax"
    .align 2
    .global Reset_Handler
Reset_Handler:
    /* mask and clear all M-mode interrupts */
    csrw    mie, zero
    csrw    mip, zero

    /* park any unexpected early M-mode trap */
    la      t0, _m_trap_park
    csrw    mtvec, t0

    /* small boot stack inside the .boot region, 0x1000 bytes per hart */
    la      sp, __boot_stack_top
    csrr    t0, mhartid
    slli    t0, t0, 12
    sub     sp, sp, t0

    /* machine-level platform init */
    call    m_mode_init

    csrr    a0, mhartid
    beqz    a0, _boot_go

    /*
     * Secondary harts park here until the kernel releases   
     * them through sbi_hsm_hart_start()
     */
_park_loop:
    li      t0, MEM_PHYS_BASE + MEM_BOOT_SCRATCH_OFF + 8
    ld      t1, 0(t0)
    srl     t1, t1, a0
    andi    t1, t1, 1
    beqz    t1, _park_loop
    fence   r, rw

_boot_go:
    /* pass hartid to the kernel */
    la      t0, __kernel_entry_phys
    csrw    mepc, t0

    /* mstatus MPP = S-mode, FS/VS = Initial */
    li      t0, 0x1800              /* MPP mask */
    csrc    mstatus, t0
    li      t0, 0x0800              /* MPP = 01 (S) */
    csrs    mstatus, t0
    li      t0, (1 << 13) | (1 << 9) /* FS = Initial, VS = Initial */
    csrs    mstatus, t0

    mret

    .align 2
_m_trap_park:
    j       _m_trap_park
