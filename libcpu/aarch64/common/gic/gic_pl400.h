/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#ifndef __GIC_PL400_H__
#define __GIC_PL400_H__

#include <rthw.h>
#include <board.h>

#define __REG32(x) (*((volatile unsigned int*)((rt_uint64_t)x)))

#define GIC_CPU_CTRL(hw_base)               __REG32((hw_base) + 0x00)
#define GIC_CPU_PRIMASK(hw_base)            __REG32((hw_base) + 0x04)
#define GIC_CPU_BINPOINT(hw_base)           __REG32((hw_base) + 0x08)
#define GIC_CPU_INTACK(hw_base)             __REG32((hw_base) + 0x0c)
#define GIC_CPU_EOI(hw_base)                __REG32((hw_base) + 0x10)
#define GIC_CPU_RUNNINGPRI(hw_base)         __REG32((hw_base) + 0x14)
#define GIC_CPU_HIGHPRI(hw_base)            __REG32((hw_base) + 0x18)

#define GIC_DIST_CTRL(hw_base)              __REG32((hw_base) + 0x000)
#define GIC_DIST_TYPE(hw_base)              __REG32((hw_base) + 0x004)
#define GIC_DIST_IGROUP(hw_base, n)         __REG32((hw_base) + 0x080 + ((n)/32) * 4)
#define GIC_DIST_ENABLE_SET(hw_base, n)     __REG32((hw_base) + 0x100 + ((n)/32) * 4)
#define GIC_DIST_ENABLE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x180 + ((n)/32) * 4)
#define GIC_DIST_PENDING_SET(hw_base, n)    __REG32((hw_base) + 0x200 + ((n)/32) * 4)
#define GIC_DIST_PENDING_CLEAR(hw_base, n)  __REG32((hw_base) + 0x280 + ((n)/32) * 4)
#define GIC_DIST_ACTIVE_SET(hw_base, n)     __REG32((hw_base) + 0x300 + ((n)/32) * 4)
#define GIC_DIST_ACTIVE_CLEAR(hw_base, n)   __REG32((hw_base) + 0x380 + ((n)/32) * 4)
#define GIC_DIST_PRI(hw_base, n)            __REG32((hw_base) + 0x400 +  ((n)/4) * 4)
#define GIC_DIST_TARGET(hw_base, n)         __REG32((hw_base) + 0x800 +  ((n)/4) * 4)
#define GIC_DIST_CONFIG(hw_base, n)         __REG32((hw_base) + 0xc00 + ((n)/16) * 4)
#define GIC_DIST_SOFTINT(hw_base)           __REG32((hw_base) + 0xf00)
#define GIC_DIST_CPENDSGI(hw_base, n)       __REG32((hw_base) + 0xf10 + ((n)/4) * 4)
#define GIC_DIST_ICPIDR2(hw_base)           __REG32((hw_base) + 0xfe8)

int arm_gic_dist_init(rt_uint32_t index, rt_uint32_t dist_base, int irq_start);
int arm_gic_cpu_init(rt_uint32_t index, rt_uint32_t cpu_base);

void arm_gic_mask(rt_uint32_t index, int irq);
void arm_gic_umask(rt_uint32_t index, int irq);
void arm_gic_set_cpu(rt_uint32_t index, int irq, unsigned int cpumask);
void arm_gic_set_group(rt_uint32_t index, int vector, int group);

int arm_gic_get_active_irq(rt_uint32_t index);
void arm_gic_ack(rt_uint32_t index, int irq);

void arm_gic_clear_active(rt_uint32_t index, int irq);
void arm_gic_clear_pending(rt_uint32_t index, int irq);

void arm_gic_dump_type(rt_uint32_t index);
void arm_gic_dump(rt_uint32_t index);

#endif

