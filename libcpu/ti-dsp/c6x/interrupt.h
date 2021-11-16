/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <rthw.h>
#include <rtthread.h>

void rt_hw_interrupt_init(void);
void rt_hw_interrupt_mask(int vector);
void rt_hw_interrupt_umask(int vector);
void rt_hw_interrupt_clear(int vector);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name);

#endif /* __INTERRUPT_H__ */
