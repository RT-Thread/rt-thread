/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */

#ifndef __AM33XX_H__
#define __AM33XX_H__

#include "armv7.h"

#define __REG32(x)  (*((volatile unsigned int *)(x)))
#define __REG16(x)  (*((volatile unsigned short *)(x)))

#define Zynq7000_UART0_BASE              0xE0000000
#define Zynq7000_UART1_BASE              0xE0001000

#define Zynq7000_SLCR_BASE               0xF8000000
#define Zynq7000_SLCR_LOCK               0x004
#define Zynq7000_SLCR_UNLOCK             0x008
#define Zynq7000_SLCR_APER_CLK_CTRL      0x12C
#define Zynq7000_SLCR_UART_CLK_CTRL      0x154
#define Zynq7000_SLCR_UART_RST_CTRL      0x228
#define Zynq7000_SLCR_MIO_LOOPBACK       0x804
#define Zynq7000_SLCR_MIO_MST_TRI0       0x80C
#define Zynq7000_SLCR_MIO_MST_TRI1       0x810

#define Zynq7000_SCTL_BASE               0xF8F00000  /* System Controller */
#define Zynq7000_TIMER_GLOBAL_BASE       0xF8F00200  /* Global 64bit timer */

#define Zynq7000_GIC_CPU_BASE            0xF8F00100  /* Generic interrupt controller CPU interface */
#define Zynq7000_GIC_DIST_BASE           0xF8F01000  /* Generic interrupt controller distributor */

/* zynq on-board gic irq sources */
#define IRQ_Zynq7000_GTIMER      27
#define IRQ_Zynq7000_PTIMER      29
#define IRQ_Zynq7000_AWDT        30
#define IRQ_Zynq7000_UART0       59
#define IRQ_Zynq7000_UART1       82
#define IRQ_Zynq7000_MAXNR       94

#define ARM_GIC_NR_IRQS     IRQ_Zynq7000_MAXNR
/* only one GIC available */
#define ARM_GIC_MAX_NR      1

#endif
