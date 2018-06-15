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
 * @file     dw_spi.h
 * @brief    header file for spi driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef __DW_SPI_H
#define __DW_SPI_H

#include <stdio.h>
#include "soc.h"

/*
 * SPI register bit definitions
 */
#define DW_SPI_ENABLE           0x01
#define DW_SPI_DISABLE          0x00
#define DW_SPI_TMOD_BIT8        0x0100
#define DW_SPI_TMOD_BIT9        0x0200
#define DW_SPI_POLARITY         0x80
#define DW_SPI_PHASE            0x40
#define DW_SPI_BUSY             0x01
#define DW_SPI_TFE              0x04
#define DW_SPI_RFNE             0x08
#define DW_SPI_INT_EN           0x19
#define DW_SPI_RINT_EN          0x3e
#define DW_SPI_TINT_EN          0x3f
#define DW_SPI_INT_DISABLE      0x00
#define DW_SPI_INT_MASK_RX      0x27
#define DW_SPI_INT_MASKTX       0x3e
#define DW_SPI_RDMAE            0x1
#define DW_SPI_TDMAE            0x2
#define DW_SPI_TXFIFO_LV        0x0
#define DW_SPI_RXFIFO_LV        0x1d
#define DW_SPI_RXFIFO_NOT_EMPTY 0x08
#define DW_SPI_START_RX         0x0
#define DW_SPI_FIFO_MAX_LV      0x20
#define DW_SPI_FIFO_OVER_LV     0x18
#define DW_SPI_RXFIFO_OVERFLOW  0x08
#define DW_SPI_RXFIFO_FULL      0x10
#define DW_SPI_TXFIFO_EMPTY     0x01
#define SPI_CS_SELECTED         0x0
#define DW_SPI_IMR_TXEIM        0x01    /* Transmit FIFO Empty Interrupt Mask */
#define DW_SPI_IMR_RXFIM        0x10    /* Receive FIFO Full Interrupt Mask */


/* some infoermationgs of SPI for special MCU */
#define DW_SPI_DEFAULT_BAUDR    10000000   /* 10M */
#define DW_SPI_MAXID            0x1

#define SPI_INITIALIZED         ((uint8_t)(1U))             // SPI initalized
#define SPI_POWERED             ((uint8_t)(1U<< 1))         // SPI powered on
#define SPI_CONFIGURED          ((uint8_t)(1U << 2))        // SPI configured
#define SPI_DATA_LOST           ((uint8_t)(1U << 3))        // SPI data lost occurred
#define SPI_MODE_FAULT          ((uint8_t)(1U << 4))        // SPI mode fault occurred


typedef enum {
    DWENUM_SPI_DMACR_RXE = 0,
    DWENUM_SPI_DMACR_TXE = 1,
} DWENUM_SPI_DMACR;


typedef enum {
    DWENUM_SPI_TXRX = 0,
    DWENUM_SPI_TX   = 1,
    DWENUM_SPI_RX   = 2,
    DWENUM_SPI_EERX = 3
} DWENUM_SPI_MODE;

typedef enum {
    DWENUM_SPI_CLOCK_POLARITY_LOW   = 0,
    DWENUM_SPI_CLOCK_POLARITY_HIGH  = 1
} DWENUM_SPI_POLARITY;

typedef enum {
    DWENUM_SPI_CLOCK_PHASE_MIDDLE   = 0,
    DWENUM_SPI_CLOCK_PHASE_START    = 1
} DWENUM_SPI_PHASE;

typedef enum {
    DWENUM_SPI_DATASIZE_4   = 3,
    DWENUM_SPI_DATASIZE_5   = 4,
    DWENUM_SPI_DATASIZE_6   = 5,
    DWENUM_SPI_DATASIZE_7   = 6,
    DWENUM_SPI_DATASIZE_8   = 7,
    DWENUM_SPI_DATASIZE_9   = 8,
    DWENUM_SPI_DATASIZE_10  = 9,
    DWENUM_SPI_DATASIZE_11  = 10,
    DWENUM_SPI_DATASIZE_12  = 11,
    DWENUM_SPI_DATASIZE_13  = 12,
    DWENUM_SPI_DATASIZE_14  = 13,
    DWENUM_SPI_DATASIZE_15  = 14,
    DWENUM_SPI_DATASIZE_16  = 15
} DWENUM_SPI_DATAWIDTH;

typedef enum {
    DWENUM_SPI_CS0 = 1,
    DWENUM_SPI_CS1 = 2
} DWENUM_SPI_SLAVE;

typedef struct {
    __IOM uint16_t CTRLR0;      /* Offset: 0x000 (R/W)  Control register 0 */
    uint16_t RESERVED0;
    __IOM uint16_t CTRLR1;      /* Offset: 0x004 (R/W)  Control register 1 */
    uint16_t RESERVED1;
    __IOM uint8_t  SPIENR;      /* Offset: 0x008 (R/W)  SSI enable regiseter */
    uint8_t  RESERVED2[7];
    __IOM uint32_t SER;         /* Offset: 0x010 (R/W)  Slave enable register */
    __IOM uint16_t BAUDR;       /* Offset: 0x014 (R/W)  Baud rate select */
    uint16_t RESERVED3;
    __IOM uint32_t TXFTLR;      /* Offset: 0x018 (R/W)  Transmit FIFO Threshold Level */
    __IOM uint32_t RXFTLR;      /* Offset: 0x01c (R/W)  Receive FIFO Threshold Level */
    __IOM uint32_t TXFLR;       /* Offset: 0x020 (R/W)  Transmit FIFO Level register */
    __IOM uint32_t RXFLR;       /* Offset: 0x024 (R/W)  Receive FIFO Level Register */
    __IOM uint8_t  SR;          /* Offset: 0x028 (R/W)  status register */
    uint8_t  RESERVED4[3];
    __IOM uint32_t IMR;         /* Offset: 0x02C (R/W)  Interrupt Mask Register */
    __IM uint32_t ISR;          /* Offset: 0x030 (R/W)  interrupt status register */
    __IM uint32_t RISR;         /* Offset: 0x034 (R/W)  Raw Interrupt Status Register */
    __IM uint8_t TXOICR;        /* Offset: 0x038 (R/W)  Transmit FIFO Overflow Interrupt Clear Register */
    uint8_t  RESERVED5[3];
    __IM uint8_t RXOICR;        /* Offset: 0x03C (R/W)  Receive FIFO Overflow Interrupt Clear Register*/
    uint8_t  RESERVED6[3];
    __IM uint8_t RXUICR;        /* Offset: 0x040 (R/W)  Receive FIFO Underflow Interrupt Clear Register */
    uint8_t  RESERVED7[3];
    __IM uint8_t MSTICR;        /* Offset: 0x044 (R/W)  Multi-Master Interrupt Clear Register */
    uint8_t  RESERVED8[3];
    __IM uint8_t ICR;           /* Offset: 0x048 (R/W)  Interrupt Clear Register */
    uint8_t  RESERVED9[3];
    __IOM uint8_t DMACR;        /* Offset: 0x04C (R/W) DMA Control Register */
    uint8_t  RESERVED10[3];
    __IOM uint8_t DMATDLR;      /* Offset: 0x050 (R/W)  DMA Transmoit Data Level */
    uint8_t  RESERVED11[3];
    __IOM uint8_t DMARDLR;      /* Offset: 0x054 (R/W)  DMA Receive Data Level */
    uint8_t  RESERVED12[3];
    __IM uint32_t IDR;          /* Offset: 0x058 (R/W)  identification register */
    uint32_t RESERVED13;
    __IOM uint16_t DR;          /* Offset: 0x060 (R/W)  Data Register */
    uint16_t RESERVED14[17];
    __IOM uint8_t WR;           /* Offset: 0x0A0 (R/W)  SPI is Master or Slave Select Register */
} dw_spi_reg_t;

#endif /* __DW_SPI_H */
