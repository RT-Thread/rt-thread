/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include <rthw.h>

#define NR_INTERNAL_IRQS 56
#define NR_EXTERNAL_IRQS 64

void rt_hw_interrupt_init(void);
void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_umask(int irq);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
		void *param, char *name);

#endif /* INTERRUPT_H_ */
