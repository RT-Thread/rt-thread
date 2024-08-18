/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <rtconfig.h>

#define NR_CPUS       1

#define IRQ_OFFSET          16
#define INTERRUPTS_MAX      (IRQ_OFFSET + IRQ_MAX_NR)

#define PLIC_BASE               0x70000000
#define PLIC_PRIORITY0          (PLIC_BASE + 0x0)
#define PLIC_PRIORITY1          (PLIC_BASE + 0x4)
#define PLIC_PRIORITY2          (PLIC_BASE + 0x8)
#define PLIC_PRIORITY3          (PLIC_BASE + 0xc)
#define PLIC_PRIORITY4          (PLIC_BASE + 0x10)

#define PLIC_PENDING1           (PLIC_BASE + 0x1000)
#define PLIC_PENDING2           (PLIC_BASE + 0x1004)
#define PLIC_PENDING3           (PLIC_BASE + 0x1008)
#define PLIC_PENDING4           (PLIC_BASE + 0x100C)

#define PLIC_ENABLE1            (PLIC_BASE + 0x2000)
#define PLIC_ENABLE2            (PLIC_BASE + 0x2004)
#define PLIC_ENABLE3            (PLIC_BASE + 0x2008)
#define PLIC_ENABLE4            (PLIC_BASE + 0x200C)

#define PLIC_THRESHOLD          (PLIC_BASE + 0x200000)
#define PLIC_CLAIM              (PLIC_BASE + 0x200004)

#define PLIC_PRIORITY_OFFSET            (0x0)
#define PLIC_PENDING_OFFSET             (0x1000)
#define PLIC_ENABLE_OFFSET              (0x2000)

#define PLIC_ENABLE_STRIDE              0x80
#define PLIC_CONTEXT_STRIDE             0x1000

#define PLIC_PRIORITY(id)               (BSP_PLIC_PHY_ADDR + PLIC_PRIORITY_OFFSET + (id) * 4)
#define PLIC_PENDING(id)                (BSP_PLIC_PHY_ADDR + PLIC_PENDING_OFFSET + ((id) / 32))
#define PLIC_ENABLE(id)                 (BSP_PLIC_PHY_ADDR + PLIC_ENABLE_OFFSET + ((id) / 32))

void rt_hw_interrupt_init(void);
void rt_hw_interrupt_mask(int vector);
void rt_hw_interrupt_umask(int vector);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, void *param, const char *name);

#endif
