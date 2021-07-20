/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PL011_H__
#define __PL011_H__

/* PL011 Registers */
#define UARTDR                    0x000
#define UARTRSR                   0x004
#define UARTECR                   0x004
#define UARTFR                    0x018
#define UARTILPR                  0x020
#define UARTIBRD                  0x024
#define UARTFBRD                  0x028
#define UARTLCR_H                 0x02C
#define UARTCR                    0x030
#define UARTIFLS                  0x034
#define UARTIMSC                  0x038
#define UARTRIS                   0x03C
#define UARTMIS                   0x040
#define UARTICR                   0x044
#define UARTDMACR                 0x048

/* Data status bits */
#define UART_DATA_ERROR_MASK      0x0F00

/* Status reg bits */
#define UART_STATUS_ERROR_MASK    0x0F

/* Flag reg bits */
#define PL011_UARTFR_RI           (1 << 8)	/* Ring indicator */
#define PL011_UARTFR_TXFE         (1 << 7)	/* Transmit FIFO empty */
#define PL011_UARTFR_RXFF         (1 << 6)	/* Receive  FIFO full */
#define PL011_UARTFR_TXFF         (1 << 5)	/* Transmit FIFO full */
#define PL011_UARTFR_RXFE         (1 << 4)	/* Receive  FIFO empty */
#define PL011_UARTFR_BUSY         (1 << 3)	/* UART busy */
#define PL011_UARTFR_DCD          (1 << 2)	/* Data carrier detect */
#define PL011_UARTFR_DSR          (1 << 1)	/* Data set ready */
#define PL011_UARTFR_CTS          (1 << 0)	/* Clear to send */

#define PL011_UARTFR_TXFF_BIT	5	/* Transmit FIFO full bit in UARTFR register */
#define PL011_UARTFR_RXFE_BIT	4	/* Receive FIFO empty bit in UARTFR register */

/* Control reg bits */
#define PL011_UARTCR_CTSEN        (1 << 15)	/* CTS hardware flow control enable */
#define PL011_UARTCR_RTSEN        (1 << 14)	/* RTS hardware flow control enable */
#define PL011_UARTCR_RTS          (1 << 11)	/* Request to send */
#define PL011_UARTCR_DTR          (1 << 10)	/* Data transmit ready. */
#define PL011_UARTCR_RXE          (1 << 9)	/* Receive enable */
#define PL011_UARTCR_TXE          (1 << 8)	/* Transmit enable */
#define PL011_UARTCR_LBE          (1 << 7)	/* Loopback enable */
#define PL011_UARTCR_UARTEN       (1 << 0)	/* UART Enable */

#if !defined(PL011_LINE_CONTROL)
/* FIFO Enabled / No Parity / 8 Data bit / One Stop Bit */
#define PL011_LINE_CONTROL  (PL011_UARTLCR_H_FEN | PL011_UARTLCR_H_WLEN_8)
#endif

/* Line Control Register Bits */
#define PL011_UARTLCR_H_SPS       (1 << 7)	/* Stick parity select */
#define PL011_UARTLCR_H_WLEN_8    (3 << 5)
#define PL011_UARTLCR_H_WLEN_7    (2 << 5)
#define PL011_UARTLCR_H_WLEN_6    (1 << 5)
#define PL011_UARTLCR_H_WLEN_5    (0 << 5)
#define PL011_UARTLCR_H_FEN       (1 << 4)	/* FIFOs Enable */
#define PL011_UARTLCR_H_STP2      (1 << 3)	/* Two stop bits select */
#define PL011_UARTLCR_H_EPS       (1 << 2)	/* Even parity select */
#define PL011_UARTLCR_H_PEN       (1 << 1)	/* Parity Enable */
#define PL011_UARTLCR_H_BRK       (1 << 0)	/* Send break */

#endif	/* __PL011_H__ */
