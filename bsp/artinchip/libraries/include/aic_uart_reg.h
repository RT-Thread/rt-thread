/*
 * Copyright (c) 2021-2026, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * ArtInChip UART register layout.
 *
 * Register offsets and fields used by the D213 UART controllers.
 *
 * Derived from the ArtInChip Luban-Lite HAL
 * (bsp/artinchip/hal/uart/aic_hal_uart.c, Apache-2.0).
 */

#ifndef __AIC_UART_REG_H__
#define __AIC_UART_REG_H__

/* Register offsets */
#define UART_RBR 0x00
#define UART_THR 0x00
#define UART_DLL 0x00
#define UART_DLH 0x04
#define UART_IER 0x04
#define UART_FCR 0x08
#define UART_LCR 0x0C
#define UART_MCR 0x10
#define UART_LSR 0x14
#define UART_USR 0x7C

/* Line status register */
#define UART_LSR_DR   0x01
#define UART_LSR_THRE 0x20

/* UART status register */
#define UART_USR_BUSY 0x01
#define UART_USR_TFNF 0x02

/* Line control register */
#define UART_LCR_DLAB   0x80
#define UART_LCR_8N1    0x03
#define UART_LCR_STOP   0x04
#define UART_LCR_PARITY 0x08
#define UART_LCR_EVEN   0x10

/* FIFO control register */
#define UART_FCR_ENABLE   0x01
#define UART_FCR_RX_RESET 0x02
#define UART_FCR_TX_RESET 0x04

/* Vendor non-DMA FIFO thresholds: TX level 3, RX level 2. */
#define UART_FCR_TX_TRIGGER (3U << 4)
#define UART_FCR_RX_TRIGGER (2U << 6)

#endif /* __AIC_UART_REG_H__ */
