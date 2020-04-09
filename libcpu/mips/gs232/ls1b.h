/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-08-08     lgnq         first version
 */

#ifndef __LS1B_H__
#define __LS1B_H__

#include <gs232.h>

#define LS1B_ACPI_IRQ	0
#define LS1B_HPET_IRQ	1
#define LS1B_UART0_IRQ	2
#define LS1B_UART1_IRQ	3
#define LS1B_UART2_IRQ	4
#define LS1B_UART3_IRQ	5
#define LS1B_CAN0_IRQ	6
#define LS1B_CAN1_IRQ	7
#define LS1B_SPI0_IRQ	8
#define LS1B_SPI1_IRQ	9
#define LS1B_AC97_IRQ	10
#define LS1B_MS_IRQ		11
#define LS1B_KB_IRQ		12
#define LS1B_DMA0_IRQ	13
#define LS1B_DMA1_IRQ	14
#define LS1B_NAND_IRQ	15
#define LS1B_I2C0_IRQ	16
#define LS1B_I2C1_IRQ	17
#define LS1B_PWM0_IRQ	18
#define LS1B_PWM1_IRQ	19
#define LS1B_PWM2_IRQ	20
#define LS1B_PWM3_IRQ	21
#define LS1B_LPC_IRQ	22
#define LS1B_EHCI_IRQ	32
#define LS1B_OHCI_IRQ	33
#define LS1B_GMAC1_IRQ	34
#define LS1B_GMAC2_IRQ	35
#define LS1B_SATA_IRQ	36
#define LS1B_GPU_IRQ	37
#define LS1B_PCI_INTA_IRQ 38
#define LS1B_PCI_INTB_IRQ 39
#define LS1B_PCI_INTC_IRQ 40
#define LS1B_PCI_INTD_IRQ 41

#define LS1B_GPIO_IRQ 64
#define LS1B_GPIO_FIRST_IRQ 64
#define LS1B_GPIO_IRQ_COUNT 96
#define LS1B_GPIO_LAST_IRQ  (LS1B_GPIO_FIRST_IRQ + LS1B_GPIO_IRQ_COUNT-1)

#define INT_PCI_INTA	(1<<6)
#define INT_PCI_INTB	(1<<7)
#define INT_PCI_INTC	(1<<8)
#define INT_PCI_INTD	(1<<9)

#define LS1B_LAST_IRQ 159
#define MIPS_CPU_TIMER_IRQ	167
#define LS1B_INTREG_BASE 0xbfd01040

#define LS1B_DMA_IRQ_BASE 168
#define LS1B_DMA_IRQ_COUNT 16

#endif
