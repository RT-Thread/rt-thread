/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     dw_usart.h
 * @brief    header file for usart driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef __DW_USART_H
#define __DW_USART_H

#include <stdio.h>
#include "errno.h"
#include "soc.h"

#define BAUDRATE_DEFAULT       19200
#define UART_BUSY_TIMEOUT      1000000
#define UART_RECEIVE_TIMEOUT   1000
#define UART_TRANSMIT_TIMEOUT  1000
#define UART_MAX_FIFO		   0x10
/* UART register bit definitions */

#define USR_UART_BUSY           0x01
#define USR_UART_TFE            0x04
#define USR_UART_RFNE           0x08
#define LSR_DATA_READY          0x01
#define LSR_THR_EMPTY           0x20
#define IER_RDA_INT_ENABLE      0x01
#define IER_THRE_INT_ENABLE     0x02
#define IIR_NO_ISQ_PEND         0x01

#define LCR_SET_DLAB            0x80   /* enable r/w DLR to set the baud rate */
#define LCR_PARITY_ENABLE	    0x08   /* parity enabled */
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
#define	DW_LSR_BI               0x10
#define	DW_LSR_FE               0x08
#define	DW_LSR_PE               0x04
#define	DW_LSR_OE               0x02
#define	DW_LSR_DR               0x01
#define DW_LSR_TRANS_EMPTY      0x20

#define DW_FCR_FIFOE            0x01
#define DW_FCR_RFIFOR           0x02
#define DW_FCR_XFIFOR           0x04
#define DW_FCR_RT_FIFO_SINGLE   0x00    /* rcvr trigger 1 character in the FIFO */
#define DW_FCR_RT_FIFO_QUARTER  0x01    /* rcvr trigger FIFO 1/4 full */
#define DW_FCR_RT_FIFO_HALF     0x10    /* rcvr trigger FIFO 1/2 full */
#define DW_FCR_RT_FIFO_LESSTWO  0x11    /* rcvr trigger FIFO 2 less than full */
#define DW_FCR_TET_FIFO_EMPTY   0x00    /* tx empty trigger FIFO empty */
#define DW_FCR_TET_FIFO_TWO     0x01    /* tx empty trigger 2 characters in the FIFO */
#define DW_FCR_TET_FIFO_QUARTER 0x10    /* tx empty trigger FIFO 1/4 full */
#define DW_FCR_TET_FIFO_HALF    0x11    /* tx empty trigger FIFO 1/2 full*/

#define DW_IIR_THR_EMPTY        0x02    /* threshold empty */
#define DW_IIR_RECV_DATA        0x04    /* received data available */

typedef struct {
    union {
        __IM uint32_t RBR;           /* Offset: 0x000 (R/ )  Receive buffer register */
        __OM uint32_t THR;           /* Offset: 0x000 ( /W)  Transmission hold register */
        __IOM uint32_t DLL;          /* Offset: 0x000 (R/W)  Clock frequency division low section register */
    };
    union {
        __IOM uint32_t DLH;          /* Offset: 0x004 (R/W)  Clock frequency division high section register */
        __IOM uint32_t IER;          /* Offset: 0x004 (R/W)  Interrupt enable register */
    };
    union {
        __IM uint32_t IIR;             /* Offset: 0x008 (R/ )  Interrupt indicia register */
        __OM uint32_t FCR;             /* Offset: 0x008 ( /W)  FIFO control register */
    };
    __IOM uint32_t LCR;            /* Offset: 0x00C (R/W)  Transmission control register */
    __IOM uint32_t MCR;            /* Offset: 0x010 (R/W)  Modem control register */
    __IM uint32_t LSR;             /* Offset: 0x014 (R/ )  Transmission state register */
    __IM uint32_t MSR;             /* Offset: 0x018 (R/ )  Modem state register */
    uint32_t RESERVED1[21];
    __IOM uint32_t FAR;            /* Offset: 0x070 (R/W)  FIFO accesss register */
    __IM uint32_t TFR;             /* Offset: 0x074 (R/ )  transmit FIFO read */
    __OM uint32_t RFW;             /* Offset: 0x078 ( /W)  receive FIFO write */
    __IM uint32_t USR;             /* Offset: 0x07c (R/ )  UART state register */
    __IM uint32_t TFL;             /* Offset: 0x080 (R/ )  transmit FIFO level */
    __IM uint32_t RFL;             /* Offset: 0x084 (R/ )  receive FIFO level */
} dw_usart_reg_t;


#endif /* __DW_USART_H */

