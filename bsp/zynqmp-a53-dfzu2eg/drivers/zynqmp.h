/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-11     liYony       the first version
 */

#ifndef __ZYNQMP_H__
#define __ZYNQMP_H__

#include <rtdef.h>
#include <ioremap.h>

#ifdef RT_USING_SMART
#include <mmu.h>
#endif

#define __REG32(x)          (*((volatile unsigned int *)(x)))
#define __REG16(x)          (*((volatile unsigned short *)(x)))

/* UART */
#define ZYNQMP_UART0_BASE    0xFF000000
#define ZYNQMP_UART0_SIZE    0x00010000
#define ZYNQMP_UART0_IRQNUM  (32 + 21)
#define ZYNQMP_UART0_CLK_FREQ_HZ (99999001)

/* GIC */
#define MAX_HANDLERS        195
#define GIC_IRQ_START       0
#define ARM_GIC_NR_IRQS     195
#define ARM_GIC_MAX_NR      1

/* GICv2 */
#define GIC400_DISTRIBUTOR_PPTR      0xF9010000U
#define GIC400_CONTROLLER_PPTR       0xF9020000U
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

#endif /* __ZYNQMP_H__ */
