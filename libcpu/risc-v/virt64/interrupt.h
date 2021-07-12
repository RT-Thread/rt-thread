/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     bigmagic      The first version
 */

#ifndef INTERRUPT_H__
#define INTERRUPT_H__

#include <rthw.h>
#include "stack.h"

int rt_hw_clint_ipi_enable(void);
int rt_hw_clint_ipi_disable(void);
int rt_hw_plic_irq_enable(int irq_number);
int rt_hw_plic_irq_disable(int irq_number);
void rt_hw_interrupt_init(void);
void rt_hw_interrupt_mask(int vector);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name);
void handle_trap(rt_size_t xcause,rt_size_t xtval,rt_size_t xepc,struct rt_hw_stack_frame *sp);

#endif
