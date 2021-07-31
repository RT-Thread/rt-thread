/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-31     GUI          first version
 */

#ifndef __GIC_PL390_H__
#define __GIC_PL390_H__

#include <rtdef.h>
#include <board.h>

void arm_gic_irq_init(void);
rt_uint16_t arm_gic_get_active_irq(void);
void arm_gic_mask(int irq);
void arm_gic_umask(int irq);
void arm_gic_ack(int irq);

#endif
