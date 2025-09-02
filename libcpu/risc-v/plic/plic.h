/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     bigmagic     first version
 * 2021-10-20     bernard      fix s-mode issue
 */

#ifndef __PLIC_H__
#define __PLIC_H__

struct plic_handler
{
    void *base;
    void *hart_base;
    void *enable_base;
};

void plic_set_priority(struct plic_handler *handler, int irq, int priority);
void plic_irq_enable(struct plic_handler *handler, int irq);
void plic_irq_disable(struct plic_handler *handler, int irq);
void plic_set_threshold(struct plic_handler *handler, int mthreshold);
int  plic_claim(struct plic_handler *handler);
void plic_complete(struct plic_handler *handler, int irq);
void plic_handler_init(struct plic_handler *handler, void *base, unsigned int context_id);

#endif
