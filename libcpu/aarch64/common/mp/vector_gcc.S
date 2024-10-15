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

#include "vector_gcc.h"
#include "context_gcc.h"

.section .text

vector_fiq:
    .globl vector_fiq
    b       .

.globl rt_hw_irq_exit

/**
 * void rt_hw_vector_irq_sched(void *eframe)
 * @brief do IRQ scheduling
 */
rt_hw_vector_irq_sched:
    .globl rt_hw_vector_irq_sched

    bl      rt_scheduler_do_irq_switch
    b       rt_hw_irq_exit
