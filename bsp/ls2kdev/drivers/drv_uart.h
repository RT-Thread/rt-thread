/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-05     bigmagic     Initial version
 */

#ifndef _DRV_UART_H__
#define _DRV_UART_H__

#include "ls2k1000.h"
#include <rthw.h>

/* UART registers */
#define UART_DAT(base)        HWREG8(base + 0x00)
#define UART_IER(base)        HWREG8(base + 0x01)
#define UART_IIR(base)        HWREG8(base + 0x02)
#define UART_FCR(base)        HWREG8(base + 0x02)
#define UART_LCR(base)        HWREG8(base + 0x03)
#define UART_MCR(base)        HWREG8(base + 0x04)
#define UART_LSR(base)        HWREG8(base + 0x05)
#define UART_MSR(base)        HWREG8(base + 0x06)

#define UART_LSB(base)        HWREG8(base + 0x00)
#define UART_MSB(base)        HWREG8(base + 0x01)

/* interrupt enable register */
#define    IER_IRxE         0x1
#define    IER_ITxE         0x2
#define    IER_ILE          0x4
#define    IER_IME          0x8

/* interrupt identification register */
#define    IIR_IMASK        0xf    /* mask */
#define    IIR_RXTOUT       0xc    /* receive timeout */
#define    IIR_RLS          0x6    /* receive line status */
#define    IIR_RXRDY        0x4    /* receive ready */
#define    IIR_TXRDY        0x2    /* transmit ready */
#define    IIR_NOPEND       0x1    /* nothing */
#define    IIR_MLSC         0x0    /* modem status */
#define    IIR_FIFO_MASK    0xc0    /* set if FIFOs are enabled */

/* fifo control register */
#define    FIFO_ENABLE      0x01    /* enable fifo */
#define    FIFO_RCV_RST     0x02    /* reset receive fifo */
#define    FIFO_XMT_RST     0x04    /* reset transmit fifo */
#define    FIFO_DMA_MODE    0x08    /* enable dma mode */
#define    FIFO_TRIGGER_1   0x00    /* trigger at 1 char */
#define    FIFO_TRIGGER_4   0x40    /* trigger at 4 chars */
#define    FIFO_TRIGGER_8   0x80    /* trigger at 8 chars */
#define    FIFO_TRIGGER_14  0xc0    /* trigger at 14 chars */

/* character format control register */
#define    CFCR_DLAB        0x80    /* divisor latch */
#define    CFCR_SBREAK      0x40    /* send break */
#define    CFCR_PZERO       0x30    /* zero parity */
#define    CFCR_PONE        0x20    /* one parity */
#define    CFCR_PEVEN       0x10    /* even parity */
#define    CFCR_PODD        0x00    /* odd parity */
#define    CFCR_PENAB       0x08    /* parity enable */
#define    CFCR_STOPB       0x04    /* 2 stop bits */
#define    CFCR_8BITS       0x03    /* 8 data bits */
#define    CFCR_7BITS       0x02    /* 7 data bits */
#define    CFCR_6BITS       0x01    /* 6 data bits */
#define    CFCR_5BITS       0x00    /* 5 data bits */

/* modem control register */
#define    MCR_LOOPBACK     0x10    /* loopback */
#define    MCR_IENABLE      0x08    /* output 2 = int enable */
#define    MCR_DRS          0x04    /* output 1 = xxx */
#define    MCR_RTS          0x02    /* enable RTS */
#define    MCR_DTR          0x01    /* enable DTR */

/* line status register */
#define    LSR_RCV_FIFO     0x80    /* error in receive fifo */
#define    LSR_TSRE         0x40    /* transmitter empty */
#define    LSR_TXRDY        0x20    /* transmitter ready */
#define    LSR_BI           0x10    /* break detected */
#define    LSR_FE           0x08    /* framing error */
#define    LSR_PE           0x04    /* parity error */
#define    LSR_OE           0x02    /* overrun error */
#define    LSR_RXRDY        0x01    /* receiver ready */
#define    LSR_RCV_MASK     0x1f


/* UART interrupt enable register value */
#define UARTIER_IME       (1 << 3)
#define UARTIER_ILE       (1 << 2)
#define UARTIER_ITXE      (1 << 1)
#define UARTIER_IRXE      (1 << 0)

/* UART line control register value */
#define UARTLCR_DLAB      (1 << 7)
#define UARTLCR_BCB       (1 << 6)
#define UARTLCR_SPB       (1 << 5)
#define UARTLCR_EPS       (1 << 4)
#define UARTLCR_PE        (1 << 3)
#define UARTLCR_SB        (1 << 2)

/* UART line status register value */
#define UARTLSR_ERROR     (1 << 7)
#define UARTLSR_TE        (1 << 6)
#define UARTLSR_TFE       (1 << 5)
#define UARTLSR_BI        (1 << 4)
#define UARTLSR_FE        (1 << 3)
#define UARTLSR_PE        (1 << 2)
#define UARTLSR_OE        (1 << 1)
#define UARTLSR_DR        (1 << 0)

#endif
