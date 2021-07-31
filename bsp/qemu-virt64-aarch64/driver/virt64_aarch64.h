/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-7-31      GUI          Add PL011's some definition
 */
#ifndef __VIRT64_AARCH64_H__
#define __VIRT64_AARCH64_H__

/* UART */
#define PL011_UARTDR                0x000
#define PL011_UARTFR                0x018
#define PL011_UARTFR_TXFF_BIT       5
#define PL011_UART0_BASE            0x09000000

#define SPECIAL_IRQ_START           1020
#define ARM_GIC_NR_IRQS             (SPECIAL_IRQ_START - 1)

#define GIC_PL390_DISTRIBUTOR_PPTR  0x08000000
#define GIC_PL390_CONTROLLER_PPTR   0x08010000

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void)
{
    return GIC_PL390_DISTRIBUTOR_PPTR;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void)
{
    return GIC_PL390_CONTROLLER_PPTR;
}

#endif
