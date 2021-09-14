/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-31     GuEe-GUI     the first version
 */

#ifndef GIC_PL390_H__
#define GIC_PL390_H__

#include <board.h>

#define GIC390_SPECIAL_IRQ_START    1020
#define GIC390_IRQ_NONE             1023

void arm_gic_irq_init(void);

int arm_gic_get_active_irq(void);
void arm_gic_ack(int irq);

void arm_gic_mask(int irq);
void arm_gic_umask(int irq);

#endif
