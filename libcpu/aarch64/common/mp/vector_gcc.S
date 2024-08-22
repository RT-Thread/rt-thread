/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28     Shell        Move vector handling codes from context_gcc.S
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "../include/vector_gcc.h"
#include "context_gcc.h"

.section .text

.globl vector_fiq
vector_fiq:
    b       .

.globl rt_hw_irq_exit

START_POINT(vector_irq)
    SAVE_IRQ_CONTEXT
    stp     x0, x1, [sp, #-0x10]!   /* X0 is thread sp */

    bl      rt_interrupt_enter
    ldp     x0, x1, [sp]

#ifdef RT_USING_SMART
    SAVE_USER_CTX
#endif /* RT_USING_SMART */

    bl      rt_hw_trap_irq

#ifdef RT_USING_SMART
    ldp     x0, x1, [sp]
    RESTORE_USER_CTX x0
#endif /* RT_USING_SMART */

    bl      rt_interrupt_leave

    ldp     x0, x1, [sp], #0x10
    bl      rt_scheduler_do_irq_switch

rt_hw_irq_exit:
    RESTORE_IRQ_CONTEXT

START_POINT_END(vector_irq)
