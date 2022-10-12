/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef __RT_LS1C_SELFBOOT_H
#define __RT_LS1C_SELFBOOT_H

/* SDRAM PARAM macro */
#define SD_FREQ (((APB_CLK / 4) * (PLL_MULT / CPU_DIV)) / SDRAM_PARAM_DIV_NUM)


/* SDRAM ROW */
#define ROW_1K      0x7
#define ROW_2K      0x0
#define ROW_4K      0x1
#define ROW_8K      0x2
#define ROW_16K     0x3
/* SDRAM COL */
#define COL_256     0x7
#define COL_512     0x0
#define COL_1K      0x1
#define COL_2K      0x2
#define COL_4K      0x3
/* SDRAM WIDTH */
#define WIDTH_8     0x0
#define WIDTH_16    0x1
#define WIDTH_32    0x2

#define TRCD        3
#define TCL         3
#define TRP         3
#define TRFC        8
#define TRAS        6
#define TREF        0x818
#define TWR         2

#define DEF_SEL     0x1
#define DEF_SEL_N   0x0
#define HANG_UP     0x1
#define HANG_UP_N   0x0
#define CFG_VALID   0x1

#include "board.h"

#define SD_PARA0    (0x7f<<25 | \
                    (TRAS << 21) | \
                    (TRFC << 17) | (TRP << 14) | (TCL << 11) | \
                    (TRCD << 8) | (SDRAM_WIDTH << 6) | (SDRAM_COL << 3) | \
                    SDRAM_ROW)

#define SD_PARA1    ((HANG_UP_N << 8) | (DEF_SEL_N << 7) | (TWR << 5) | (TREF >> 7))

#define SD_PARA1_EN ((CFG_VALID << 9) | (HANG_UP_N << 8) | \
                    (DEF_SEL_N << 7) | (TWR << 5) | (TREF >> 7))

#define LS1C_CBUS_FIRST1      0xBFE011C4
#define LS1C_UART2_BASE       0xBFE48000

/* UART register offset*/
#define LS1C_UART_DAT_OFFSET            (0)
#define LS1C_UART_IER_OFFSET            (1)
#define LS1C_UART_IIR_OFFSET            (2)
#define LS1C_UART_FCR_OFFSET            (2)
#define LS1C_UART_LCR_OFFSET            (3)
#define LS1C_UART_MCR_OFFSET            (4)
#define LS1C_UART_LSR_OFFSET            (5)
#define LS1C_UART_MSR_OFFSET            (6)

#define LS1C_UART_LSB_OFFSET            (0)
#define LS1C_UART_MSB_OFFSET            (1)

/* interrupt enable register */
#define IER_IRxE    0x1
#define IER_ITxE    0x2
#define IER_ILE     0x4
#define IER_IME     0x8

/* interrupt identification register */
#define IIR_IMASK   0xf /* mask */
#define IIR_RXTOUT  0xc /* receive timeout */
#define IIR_RLS     0x6 /* receive line status */
#define IIR_RXRDY   0x4 /* receive ready */
#define IIR_TXRDY   0x2 /* transmit ready */
#define IIR_NOPEND  0x1 /* nothing */
#define IIR_MLSC    0x0 /* modem status */
#define IIR_FIFO_MASK   0xc0    /* set if FIFOs are enabled */

/* fifo control register */
#define FIFO_ENABLE 0x01    /* enable fifo */
#define FIFO_RCV_RST    0x02    /* reset receive fifo */
#define FIFO_XMT_RST    0x04    /* reset transmit fifo */
#define FIFO_DMA_MODE   0x08    /* enable dma mode */
#define FIFO_TRIGGER_1  0x00    /* trigger at 1 char */
#define FIFO_TRIGGER_4  0x40    /* trigger at 4 chars */
#define FIFO_TRIGGER_8  0x80    /* trigger at 8 chars */
#define FIFO_TRIGGER_14 0xc0    /* trigger at 14 chars */

/* character format control register */
#define CFCR_DLAB   0x80    /* divisor latch */
#define CFCR_SBREAK 0x40    /* send break */
#define CFCR_PZERO  0x30    /* zero parity */
#define CFCR_PONE   0x20    /* one parity */
#define CFCR_PEVEN  0x10    /* even parity */
#define CFCR_PODD   0x00    /* odd parity */
#define CFCR_PENAB  0x08    /* parity enable */
#define CFCR_STOPB  0x04    /* 2 stop bits */
#define CFCR_8BITS  0x03    /* 8 data bits */
#define CFCR_7BITS  0x02    /* 7 data bits */
#define CFCR_6BITS  0x01    /* 6 data bits */
#define CFCR_5BITS  0x00    /* 5 data bits */

/* modem control register */
#define MCR_LOOPBACK    0x10    /* loopback */
#define MCR_IENABLE 0x08    /* output 2 = int enable */
#define MCR_DRS     0x04    /* output 1 = xxx */
#define MCR_RTS     0x02    /* enable RTS */
#define MCR_DTR     0x01    /* enable DTR */

/* line status register */
#define LSR_RCV_FIFO    0x80    /* error in receive fifo */
#define LSR_TSRE    0x40    /* transmitter empty */
#define LSR_TXRDY   0x20    /* transmitter ready */
#define LSR_BI      0x10    /* break detected */
#define LSR_FE      0x08    /* framing error */
#define LSR_PE      0x04    /* parity error */
#define LSR_OE      0x02    /* overrun error */
#define LSR_RXRDY   0x01    /* receiver ready */
#define LSR_RCV_MASK    0x1f


/* External clock frequency */
#define AHB_CLK                 (24000000)
#define APB_CLK                 (AHB_CLK)


/* START_FREQ register bits */
#define M_PLL_SHIFT             (8)
#define M_PLL                   (0xff << M_PLL_SHIFT)
#define FRAC_N_SHIFT            (16)
#define FRAC_N                  (0xff << FRAC_N_SHIFT)
#define DIV_SDRAM_SHIFT         (0)
#define DIV_SDRAM               (0x3  << DIV_SDRAM_SHIFT)

/* CLK_DIV_PARAM register bits */
#define DIV_PIX_EN              (0x1  << 31)
#define DIV_PIX                 (0x7f << 24)
#define DIV_CAM_EN              (0x1  << 23)
#define DIV_CAM                 (0x7f << 16)
#define DIV_CPU_EN              (0x1  << 15)
#define DIV_CPU                 (0x7f << 8)
#define DIV_PIX_VALID           (0x1  << 5)
#define DIV_PIX_SEL             (0x1  << 4)
#define DIV_CAM_VALID           (0x1  << 3)
#define DIV_CAM_SEL             (0x1  << 2)
#define DIV_CPU_VALID           (0x1  << 1)
#define DIV_CPU_SEL             (0x1  << 0)

#define DIV_PIX_SHIFT           (24)
#define DIV_CAM_SHIFT           (16)
#define DIV_CPU_SHIFT           (8)

#endif
