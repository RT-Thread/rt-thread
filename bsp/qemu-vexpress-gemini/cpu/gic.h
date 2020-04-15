/*
 * File      : gic.h, ARM Generic Interrupt Controller
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#ifndef __GIC_H__
#define __GIC_H__

int arm_gic_dist_init(rt_uint32_t index, rt_uint32_t dist_base, int irq_start);
int arm_gic_cpu_init(rt_uint32_t index, rt_uint32_t cpu_base);

void arm_gic_mask(rt_uint32_t index, int irq);
void arm_gic_umask(rt_uint32_t index, int irq);
void arm_gic_set_cpu(rt_uint32_t index, int irq, unsigned int cpumask);
void arm_gic_set_group(rt_uint32_t index, int vector, int group);

int arm_gic_get_active_irq(rt_uint32_t index);
void arm_gic_ack(rt_uint32_t index, int irq);

void arm_gic_trigger(rt_uint32_t index, int target_cpu, int irq);
void arm_gic_clear_sgi(rt_uint32_t index, int target_cpu, int irq);

void arm_gic_dump_type(rt_uint32_t index);

#endif

