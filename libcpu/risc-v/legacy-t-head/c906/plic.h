/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-19     JasonHu      first version
 * 2023-04-22     flyingcys    add C906_PLIC_PHY_ADDR macro judge
 */

#ifndef __RISCV64_PLIC_H__
#define __RISCV64_PLIC_H__

#include <interrupt.h>

#ifndef C906_PLIC_PHY_ADDR
#define C906_PLIC_PHY_ADDR              (0x10000000)
#endif
#define C906_PLIC_NR_EXT_IRQS           (IRQ_MAX_NR)
#define C906_NR_CPUS                    (NR_CPUS)

/* M and S mode context. */
#define C906_NR_CONTEXT                 (2)

#define MAX_DEVICES                     1024
#define MAX_CONTEXTS                    15872

/*
 *  Each interrupt source has a priority register associated with it.
 *  We always hardwire it to one in Linux.
 */
#define PRIORITY_BASE                   0
#define PRIORITY_PER_ID                 4

/*
 *  Each hart context has a vector of interrupt enable bits associated with it.
 *  There's one bit for each interrupt source.
 */
#define ENABLE_BASE                     0x2000
#define ENABLE_PER_HART                 0x80

/*
 *  Each hart context has a set of control registers associated with it.  Right
 *  now there's only two: a source priority threshold over which the hart will
 *  take an interrupt, and a register to claim interrupts.
 */
#define CONTEXT_BASE                    0x200000
#define CONTEXT_PER_HART                0x1000
#define CONTEXT_THRESHOLD               0x00
#define CONTEXT_CLAIM                   0x04

void plic_init(void);
void plic_enable_irq(int irqno);
void plic_disable_irq(int irqno);
// tell PLIC that we've served this IRQ
void plic_complete(int irq);
void plic_handle_irq(void);

#endif
