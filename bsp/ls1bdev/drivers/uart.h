/*
 * File      : uart.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-08-08     lgnq         first version for LS1B
 */

#ifndef __UART_H__
#define __UART_H__

#include "ls1b.h"
#include <rthw.h>

#define UART0_BASE		    0xBFE40000
#define UART0_1_BASE		0xBFE41000
#define UART0_2_BASE		0xBFE42000
#define UART0_3_BASE		0xBFE43000
#define UART1_BASE			0xBFE44000
#define UART1_1_BASE		0xBFE45000
#define UART1_2_BASE		0xBFE46000
#define UART1_3_BASE		0xBFE47000
#define UART2_BASE			0xBFE48000
#define UART3_BASE			0xBFE4C000
#define UART4_BASE			0xBFE6C000
#define UART5_BASE			0xBFE7C000

/* UART registers */
#define UART_DAT(base)		HWREG8(base + 0x00)
#define UART_IER(base)		HWREG8(base + 0x01)
#define UART_IIR(base)		HWREG8(base + 0x02)
#define UART_FCR(base)		HWREG8(base + 0x02)
#define UART_LCR(base)		HWREG8(base + 0x03)
#define UART_MCR(base)		HWREG8(base + 0x04)
#define UART_LSR(base)		HWREG8(base + 0x05)
#define UART_MSR(base)		HWREG8(base + 0x06)

#define UART_LSB(base)		HWREG8(base + 0x00)
#define UART_MSB(base)		HWREG8(base + 0x01)

/* UART0 registers */
#define UART0_DAT			HWREG8(UART0_BASE + 0x00)
#define UART0_IER			HWREG8(UART0_BASE + 0x01)
#define UART0_IIR			HWREG8(UART0_BASE + 0x02)
#define UART0_FCR			HWREG8(UART0_BASE + 0x02)
#define UART0_LCR			HWREG8(UART0_BASE + 0x03)
#define UART0_MCR			HWREG8(UART0_BASE + 0x04)
#define UART0_LSR			HWREG8(UART0_BASE + 0x05)
#define UART0_MSR			HWREG8(UART0_BASE + 0x06)

#define UART0_LSB			HWREG8(UART0_BASE + 0x00)
#define UART0_MSB			HWREG8(UART0_BASE + 0x01)

/* UART1 registers */
#define UART1_DAT			HWREG8(UART1_BASE + 0x00)
#define UART1_IER			HWREG8(UART1_BASE + 0x01)
#define UART1_IIR			HWREG8(UART1_BASE + 0x02)
#define UART1_FCR			HWREG8(UART1_BASE + 0x02)
#define UART1_LCR			HWREG8(UART1_BASE + 0x03)
#define UART1_MCR			HWREG8(UART1_BASE + 0x04)
#define UART1_LSR			HWREG8(UART1_BASE + 0x05)
#define UART1_MSR			HWREG8(UART1_BASE + 0x06)

#define UART1_LSB			HWREG8(UART1_BASE + 0x00)
#define UART1_MSB			HWREG8(UART1_BASE + 0x01)

/* UART interrupt enable register value */
#define UARTIER_IME		(1 << 3)
#define UARTIER_ILE		(1 << 2) 
#define UARTIER_ITXE	(1 << 1)
#define UARTIER_IRXE	(1 << 0)

/* UART line control register value */
#define UARTLCR_DLAB	(1 << 7)
#define UARTLCR_BCB		(1 << 6)
#define UARTLCR_SPB		(1 << 5)
#define UARTLCR_EPS		(1 << 4)
#define UARTLCR_PE		(1 << 3)
#define UARTLCR_SB		(1 << 2)

/* UART line status register value */
#define UARTLSR_ERROR	(1 << 7)
#define UARTLSR_TE		(1 << 6)
#define UARTLSR_TFE		(1 << 5)
#define UARTLSR_BI		(1 << 4)
#define UARTLSR_FE		(1 << 3)
#define UARTLSR_PE		(1 << 2)
#define UARTLSR_OE		(1 << 1)
#define UARTLSR_DR		(1 << 0)

void rt_hw_uart_init(void);

#endif
