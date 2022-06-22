/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      header file for usart driver
 */

#ifndef __CK_USART_H
#define __CK_USART_H

#include <stdio.h>
#include "errno.h"
#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BAUDRATE_DEFAULT    19200
#define UART_BUSY_TIMEOUT       1000000
#define UART_RECEIVE_TIMEOUT    1000
#define UART_TRANSMIT_TIMEOUT   1000
#define UART_MAX_FIFO           0x10
/* UART register bit definitions */

#define USR_UART_BUSY           0x01
#define USR_UART_TFE            0x04
#define USR_UART_RFNE           0x08
#define LSR_DATA_READY          0x01
#define LSR_THR_EMPTY           0x20
#define IER_RDA_INT_ENABLE      0x01
#define IER_THRE_INT_ENABLE     0x02
#define IIR_RECV_LINE_ENABLE    0x04
#define IIR_NO_ISQ_PEND         0x01

#define LCR_SET_DLAB            0x80   /* enable r/w DLR to set the baud rate */
#define LCR_PARITY_ENABLE       0x08   /* parity enabled */
#define LCR_PARITY_EVEN         0x10   /* Even parity enabled */
#define LCR_PARITY_ODD          0xef   /* Odd parity enabled */
#define LCR_WORD_SIZE_5         0xfc   /* the data length is 5 bits */
#define LCR_WORD_SIZE_6         0x01   /* the data length is 6 bits */
#define LCR_WORD_SIZE_7         0x02   /* the data length is 7 bits */
#define LCR_WORD_SIZE_8         0x03   /* the data length is 8 bits */
#define LCR_STOP_BIT1           0xfb   /* 1 stop bit */
#define LCR_STOP_BIT2           0x04   /* 1.5 stop bit */

#define DW_LSR_PFE              0x80
#define DW_LSR_TEMT             0x40
#define DW_LSR_THRE             0x40
#define DW_LSR_BI               0x10
#define DW_LSR_FE               0x08
#define DW_LSR_PE               0x04
#define DW_LSR_OE               0x02
#define DW_LSR_DR               0x01
#define DW_LSR_TRANS_EMPTY      0x20

#define DW_IIR_THR_EMPTY        0x02    /* threshold empty */
#define DW_IIR_RECV_DATA        0x04    /* received data available */
#define DW_IIR_RECV_LINE        0x06    /* receiver line status */
#define DW_IIR_CHAR_TIMEOUT     0x0c    /* character timeout */

typedef struct
{
    union
    {
        __IM uint32_t RBR;           /* Offset: 0x000 (R/ )  Receive buffer register */
        __OM uint32_t THR;           /* Offset: 0x000 ( /W)  Transmission hold register */
        __IOM uint32_t DLL;          /* Offset: 0x000 (R/W)  Clock frequency division low section register */
    };
    union
    {
        __IOM uint32_t DLH;          /* Offset: 0x004 (R/W)  Clock frequency division high section register */
        __IOM uint32_t IER;          /* Offset: 0x004 (R/W)  Interrupt enable register */
    };
    __IM uint32_t IIR;             /* Offset: 0x008 (R/ )  Interrupt indicia register */
    __IOM uint32_t LCR;            /* Offset: 0x00C (R/W)  Transmission control register */
    uint32_t RESERVED0;
    __IM uint32_t LSR;             /* Offset: 0x014 (R/ )  Transmission state register */
    __IM uint32_t MSR;             /* Offset: 0x018 (R/ )  Modem state register */
    uint32_t RESERVED1[24];
    __IM uint32_t USR;             /* Offset: 0x07c (R/ )  UART state register */
} ck_usart_reg_t;

#ifdef __cplusplus
}
#endif

#endif /* __CK_USART_H */

