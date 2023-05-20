/*
 * Copyright (c) 2020-2023, Chertsoft Development Team
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#ifndef __ZYNQMP_R5_H
#define __ZYNQMP_R5_H

#ifdef __cplusplus
extern "C" {
#endif

#define __REG32(x)  (*((volatile unsigned int *)(x)))
#define __REG16(x)  (*((volatile unsigned short *)(x)))

/*
 * Peripheral addresses
 */
#define ZYNQMP_UART0_BASE       0xFF000000UL
#define ZYNQMP_TTC0_BASE        0xFF110000UL
#define ZYNQMP_TTC1_BASE        0xFF120000UL
#define ZYNQMP_TTC2_BASE        0xFF130000UL
#define ZYNQMP_TTC3_BASE        0xFF140000UL

#define ZYNQMP_GIC_DIST_BASE    0xF9000000UL
#define ZYNQMP_GIC_CPU_BASE     0xF9001000UL

/*
 * Zynqmp on-board gic irq source
 */
#define IRQ_ZYNQMP_GIC_START    (32 + 8)

#define IRQ_UART_0              (IRQ_ZYNQMP_GIC_START + 13UL)
#define IRQ_TTC0_0              (IRQ_ZYNQMP_GIC_START + 28UL)
#define IRQ_TTC0_1              (IRQ_ZYNQMP_GIC_START + 29UL)
#define IRQ_TTC0_2              (IRQ_ZYNQMP_GIC_START + 30UL)
#define IRQ_TTC1_0              (IRQ_ZYNQMP_GIC_START + 31UL)

#define IRQ_ZYNQMP_MAX_NR       187UL

/* number of interrupts on board */
#define ARM_GIC_NR_IRQS         IRQ_ZYNQMP_MAX_NR
/* only one GIC available */
#define ARM_GIC_MAX_NR  1

#define GIC_ACK_INTID_MASK      0x3FF

#define MAX_HANDLERS            IRQ_ZYNQMP_MAX_NR

#define GIC_IRQ_START           0

#ifdef __cplusplus
}
#endif
#endif /*__ZYNQMP_R5_H*/
