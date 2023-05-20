/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#ifndef __DRV_UART_H
#define __DRV_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>

#define UART_CR(base)               __REG32(base + 0x00)
#define UART_CR_EN_DIS_MASK         0x0000003F
#define UART_CR_TX_DIS              (1 << 5)
#define UART_CR_TX_EN               (1 << 4)
#define UART_CR_RX_DIS              (1 << 3)
#define UART_CR_RX_EN               (1 << 2)

#define UART_IER(base)              __REG32(base + 0x08)
#define UART_IDR(base)              __REG32(base + 0x0C)
#define UART_ISR(base)              __REG32(base + 0x14)

#define UART_IXR_DIS_MASK           0x00003FFF
#define UART_IXR_TX_NFULL           (1 << 11)
#define UART_IXR_TX_TRIG            (1 << 10)
#define UART_IXR_RX_OVR             (1 << 5)
#define UART_IXR_TX_FULL            (1 << 4)
#define UART_IXR_TX_EMPTY           (1 << 3)
#define UART_IXR_RX_FULL            (1 << 2)
#define UART_IXR_RX_EMPTY           (1 << 1)
#define UART_IXR_RX_TRIG            (1 << 0)

#define UART_RX_TRIG_LVL(hw_base)   __REG32(hw_base + 0x20)
#define UART_TX_TRIG_LVL(hw_base)   __REG32(hw_base + 0x44)
#define UART_TRIG_LVL_MASK          0x0000003F
#define UART_TRIG_LVL               (1 << 0)

#define UART_SR(base)               __REG32(base + 0x2C)
#define UART_SR_TXFULL              (1 << 4)
#define UART_SR_RXFULL              (1 << 1)

#define UART_FIFO(base)             __REG32(base + 0x30)


#ifdef __cplusplus
}
#endif
#endif /*__DRV_UART_H*/
