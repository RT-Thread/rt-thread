/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/25     flyingcys    first version
 */
#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

#include "pinctrl.h"
#include "mmio.h"

#define UART_REG_SHIFT      0x2     /* Register Shift*/
#define UART_INPUT_CLK      25000000

#define UART0_BASE          0x04140000
#define UART1_BASE          0x04150000
#define UART2_BASE          0x04160000
#define UART3_BASE          0x04170000
#define UART4_BASE          0x041C0000

#define UART0_IRQ           (BSP_UART_IRQ_BASE + 0)
#define UART1_IRQ           (BSP_UART_IRQ_BASE + 1)
#define UART2_IRQ           (BSP_UART_IRQ_BASE + 2)
#define UART3_IRQ           (BSP_UART_IRQ_BASE + 3)
#define UART4_IRQ           (BSP_UART_IRQ_BASE + 4)

/*
 * The Synopsys DesignWare 8250 has an extra feature whereby it detects if the
 * LCR is written whilst busy. If it is, then a busy detect interrupt is
 * raised, the LCR needs to be rewritten and the uart status register read.
 */

#define UART_RX             0    /* In: Receive buffer */
#define UART_TX             0    /* Out: Transmit buffer */

#define UART_DLL            0    /* Out: Divisor Latch Low */
#define UART_DLM            1    /* Out: Divisor Latch High */

#define UART_IER            1    /* Out: Interrupt Enable Register */
#define UART_IER_RDI        0x01 /* Enable receiver data interrupt */

#define UART_SSR            0x22 /* In: Software Reset Register */
#define UART_USR            0x1f /* UART Status Register */

#define UART_IIR            2    /* In: Interrupt ID Register */
#define UART_IIR_NO_INT     0x01 /* No interrupts pending */
#define UART_IIR_BUSY       0x07 /* DesignWare APB Busy Detect */
#define UART_IIR_RX_TIMEOUT 0x0c /* OMAP RX Timeout interrupt */

#define UART_FCR            2    /* Out: FIFO Control Register */
#define UART_FCR_FIFO_EN    0x01 /* Fifo enable */
#define UART_FCR_RXSR       0x02 /* Receiver soft reset */
#define UART_FCR_TXSR       0x04 /* Transmitter soft reset */

#define UART_LCR            3    /* Out: Line Control Register */
#define UART_LCR_WLS_MSK    0x03 /* character length select mask */
#define UART_LCR_WLS_5      0x00 /* 5 bit character length */
#define UART_LCR_WLS_6      0x01 /* 6 bit character length */
#define UART_LCR_WLS_7      0x02 /* 7 bit character length */
#define UART_LCR_WLS_8      0x03 /* 8 bit character length */
#define UART_LCR_STB        0x04 /* # stop Bits, off=1, on=1.5 or 2) */
#define UART_LCR_PEN        0x08 /* Parity eneble */
#define UART_LCR_EPS        0x10 /* Even Parity Select */
#define UART_LCR_STKP       0x20 /* Stick Parity */
#define UART_LCR_SBRK       0x40 /* Set Break */
#define UART_LCR_BKSE       0x80 /* Bank select enable */
#define UART_LCR_DLAB       0x80 /* Divisor latch access bit */


#define UART_MCR            4    /* Out: Modem Control Register */
#define UART_MCR_DTR        0x01 /* DTR   */
#define UART_MCR_RTS        0x02 /* RTS   */

#define UART_LSR            5    /* In: Line Status Register */
#define UART_LSR_BI         0x10 /* Break interrupt indicator */
#define UART_LSR_DR         0x01 /* Receiver data ready */
#define UART_LSR_TEMT       0x40 /* Transmitter empty */
#define UART_LSR_THRE       0x20 /* Transmit-hold-register empty */

#define UART_MCRVAL         (UART_MCR_DTR | UART_MCR_RTS) /* RTS/DTR */

/* Clear & enable FIFOs */
#define UART_FCR_DEFVAL     (UART_FCR_FIFO_EN | UART_FCR_RXSR | UART_FCR_TXSR)

#define UART_LCR_8N1        0x03

int rt_hw_uart_init(void);

#endif  /* __DRV_USART_H__ */
