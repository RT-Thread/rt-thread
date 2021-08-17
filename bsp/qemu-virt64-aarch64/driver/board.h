/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 * 2021-07-31     GuEe-GUI     add ARM GIC definitions
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rthw.h>

extern unsigned char __bss_start;
extern unsigned char __bss_end;

#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(RT_HW_HEAP_BEGIN + 1 * 1024 * 1024)

/* UART */
#define PL011_UARTDR                0x000
#define PL011_UARTFR                0x018
#define PL011_UARTFR_TXFF_BIT       5
#define PL011_UART0_BASE            0x09000000
#define PL011_UART0_SIZE            0x00001000

/* DIST and CPU */
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

void rt_hw_board_init(void);

#endif
