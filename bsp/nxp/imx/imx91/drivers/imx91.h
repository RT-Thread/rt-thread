/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 */

#ifndef __IMX91_H__
#define __IMX91_H__

#include <rtthread.h>

/* 'ARM_GIC_MAX_NR' is the number of cores, gicv3.c required */
#define ARM_GIC_MAX_NR 1

/* The platform maximum interrupts, interrupt.c required */
#define ARM_GIC_NR_IRQS 256

/* Number of interrupts in the Vector table, interrupt.c required */
#define MAX_HANDLERS 256

/* interrupt.c required. */
rt_base_t platform_get_gic_dist_base(void);
rt_base_t platform_get_gic_redist_base(void);
rt_base_t platform_get_gic_cpu_base(void);

/* interrupt.c required */
#define GIC_IRQ_START 0

/* gic.c required */
#define __REG32(x) (*((volatile unsigned int *)(x)))

#define KB_SIZE(x) ((x) * 1024)
#define MB_SIZE(x) ((x) * 1024 * 1024)

#define GIC_DISTRIBUTOR_SIZE   KB_SIZE(64)
#define GIC_REDISTRIBUTOR_SIZE KB_SIZE(768)

#define LPUART1_SIZE  KB_SIZE(64)
#define CCM_CTRL_SIZE KB_SIZE(64)

#endif  /* __IMX91_H__ */

