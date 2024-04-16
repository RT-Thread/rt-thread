/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-15     liYony       the first version
 */

#ifndef __CV18XX_H__
#define __CV18XX_H__

#include <rtdef.h>
#include <ioremap.h>

#ifdef RT_USING_SMART
#include <mmu.h>
#endif

#define __REG32(x)          (*((volatile unsigned int *)(x)))
#define __REG16(x)          (*((volatile unsigned short *)(x)))

/* GIC */
#define MAX_HANDLERS        116
#define GIC_IRQ_START       0
#define ARM_GIC_NR_IRQS     116
#define ARM_GIC_MAX_NR      1

/* GICv2 */
#define GIC400_DISTRIBUTOR_PPTR      0x01F01000U
#define GIC400_CONTROLLER_PPTR       0x01F02000U
#define GIC400_SIZE                  0x00001000U

/* the basic constants and interfaces needed by gic */
rt_inline rt_ubase_t platform_get_gic_dist_base(void)
{
    return GIC400_DISTRIBUTOR_PPTR;
}

rt_inline rt_ubase_t platform_get_gic_cpu_base(void)
{
    return GIC400_CONTROLLER_PPTR;
}

#endif /* __CV18XX_H__ */
