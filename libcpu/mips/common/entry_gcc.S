/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include <mips.h>
#include <rtconfig.h>

#include "asm.h"
#include <rtconfig.h>

    .section ".start", "ax"
    .set noreorder

    /* the program entry */
    .globl  _rtthread_entry
_rtthread_entry:
#ifndef RT_USING_SELF_BOOT
    .globl  _start
_start:
#endif
    PTR_LA  ra, _rtthread_entry

    /* disable interrupt */
    MTC0    zero, CP0_CAUSE
    MTC0    zero, CP0_STATUS    # Set CPU to disable interrupt.
    ehb

#ifdef ARCH_MIPS64
    dli     t0, ST0_KX
    MTC0    t0, CP0_STATUS
#endif

    /* setup stack pointer */
    PTR_LA  sp, _system_stack
    PTR_LA  gp, _gp

    bal rt_cpu_early_init
    nop

    /* clear bss */
    PTR_LA  t0, __bss_start
    PTR_LA  t1, __bss_end

_clr_bss_loop:
    sw  zero, 0(t0)
    bne t1, t0, _clr_bss_loop
    addu    t0, 4
    /* jump to RT-Thread RTOS */
    jal rtthread_startup
    nop

    /* restart, never die */
    j   _start
    nop
