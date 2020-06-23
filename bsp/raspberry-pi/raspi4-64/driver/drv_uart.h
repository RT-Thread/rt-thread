/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#ifndef DRV_UART_H__
#define DRV_UART_H__

// register's bit
#define PL011_FR_RI          (1 << 8)
#define PL011_FR_TXFE        (1 << 7)
#define PL011_FR_RXFF        (1 << 6)
#define PL011_FR_TXFF        (1 << 5)
#define PL011_FR_RXFE        (1 << 4)
#define PL011_FR_BUSY        (1 << 3)
#define PL011_FR_DCD         (1 << 2)
#define PL011_FR_DSR         (1 << 1)
#define PL011_FR_CTS         (1 << 0)

#define PL011_LCRH_SPS       (1 << 7)
#define PL011_LCRH_WLEN_8    (3 << 5)
#define PL011_LCRH_WLEN_7    (2 << 5)
#define PL011_LCRH_WLEN_6    (1 << 5)
#define PL011_LCRH_WLEN_5    (0 << 5)
#define PL011_LCRH_FEN       (1 << 4)
#define PL011_LCRH_STP2      (1 << 3)
#define PL011_LCRH_EPS       (1 << 2)
#define PL011_LCRH_PEN       (1 << 1)
#define PL011_LCRH_BRK       (1 << 0)

#define PL011_CR_CTSEN       (1 << 15)
#define PL011_CR_RTSEN       (1 << 14)
#define PL011_CR_RTS         (1 << 11)
#define PL011_CR_DTR         (1 << 10)
#define PL011_CR_RXE         (1 << 9)
#define PL011_CR_TXE         (1 << 8)
#define PL011_CR_LBE         (1 << 7)
#define PL011_CR_SIRLP       (1 << 2)
#define PL011_CR_SIREN       (1 << 1)
#define PL011_CR_UARTEN      (1 << 0)

#define PL011_IMSC_TXIM      (1 << 5)
#define PL011_IMSC_RXIM      (1 << 4)

#define PL011_INTERRUPT_OVERRUN_ERROR   (1 << 10)
#define PL011_INTERRUPT_BREAK_ERROR     (1 << 9)
#define PL011_INTERRUPT_PARITY_ERROR    (1 << 8)
#define PL011_INTERRUPT_FRAMING_ERROR   (1 << 7)
#define PL011_INTERRUPT_RECEIVE_TIMEOUT (1 << 6)
#define PL011_INTERRUPT_TRANSMIT        (1 << 5)
#define PL011_INTERRUPT_RECEIVE         (1 << 4)
#define PL011_INTERRUPT_nUARTCTS        (1 << 1)

#define PL011_REG_DR(BASE)              HWREG32(BASE + 0x00)
#define PL011_REG_RSRECR(BASE)          HWREG32(BASE + 0x04)
#define PL011_REG_RESERVED0(BASE)       HWREG32(BASE + 0x08)
#define PL011_REG_FR(BASE)              HWREG32(BASE + 0x18)
#define PL011_REG_RESERVED1(BASE)       HWREG32(BASE + 0x1C)
#define PL011_REG_ILPR(BASE)            HWREG32(BASE + 0x20)
#define PL011_REG_IBRD(BASE)            HWREG32(BASE + 0x24)
#define PL011_REG_FBRD(BASE)            HWREG32(BASE + 0x28)
#define PL011_REG_LCRH(BASE)            HWREG32(BASE + 0x2C)
#define PL011_REG_CR(BASE)              HWREG32(BASE + 0x30)
#define PL011_REG_IFLS(BASE)            HWREG32(BASE + 0x34)
#define PL011_REG_IMSC(BASE)            HWREG32(BASE + 0x38)
#define PL011_REG_RIS(BASE)             HWREG32(BASE + 0x3C)
#define PL011_REG_MIS(BASE)             HWREG32(BASE + 0x40)
#define PL011_REG_ICR(BASE)             HWREG32(BASE + 0x44)
#define PL011_REG_DMACR(BASE)           HWREG32(BASE + 0x48)
#define PL011_REG_RESERVED2(BASE)       HWREG32(BASE + 0x4C)
#define PL011_REG_ITCR(BASE)            HWREG32(BASE + 0x80)
#define PL011_REG_ITIP(BASE)            HWREG32(BASE + 0x84)
#define PL011_REG_ITOP(BASE)            HWREG32(BASE + 0x88)
#define PL011_REG_TDR(BASE)             HWREG32(BASE + 0x8C)

int rt_hw_uart_init(void);

#endif /* DRV_UART_H__ */
