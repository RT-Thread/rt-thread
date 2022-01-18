/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 * 2020-07-26     lizhirui     Add xtlb exception entry
 */
#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include <mips.h>

    .section ".exc_vectors", "ax"
    .extern tlb_refill_handler
    .extern cache_error_handler
    .extern mips_irq_handle

    /* 0x0 - TLB refill handler */
    .global tlb_refill_exception
    .type   tlb_refill_exception,@function
ebase_start:
tlb_refill_exception:
    b   _general_exception_handler
    nop

    /* 0x080 - XTLB refill handler */
    .org ebase_start + 0x080
    b   _general_exception_handler
    nop

    /* 0x100 - Cache error handler */
    .org ebase_start + 0x100
    j   cache_error_handler
    nop

    /* 0x180 - Exception/Interrupt handler */
    .global general_exception
    .type   general_exception,@function
    .org ebase_start + 0x180
general_exception:
    b   _general_exception_handler
    nop

    /* 0x200 - Special Exception Interrupt handler (when IV is set in CP0_CAUSE) */
    .global irq_exception
    .type   irq_exception,@function
    .org ebase_start + 0x200
irq_exception:
    b   _general_exception_handler
    nop

    /* general exception handler */
_general_exception_handler:
    .set    noreorder
    PTR_LA  k0, mips_irq_handle
    jr  k0
    nop
    .set    reorder

    /* interrupt handler */
_irq_handler:
    .set    noreorder
    PTR_LA  k0, mips_irq_handle
    jr  k0
    nop
    .set    reorder
