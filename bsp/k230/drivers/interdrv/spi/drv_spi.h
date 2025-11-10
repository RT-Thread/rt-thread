/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <stdint.h>
#include <stdbool.h>

#define SSIC_HAS_DMA 2
#define SSIC_AXI_BLW 8
#define SSIC_TX_ABW 256
#define SSIC_RX_ABW 256

#define IRQN_SPI0 146
#define IRQN_SPI1 155
#define IRQN_SPI2 164

#ifndef L1_CACHE_BYTES
    #define L1_CACHE_BYTES 64
#endif

#define CACHE_ALIGN_TOP(x) (((x) + L1_CACHE_BYTES - 1) & ~(L1_CACHE_BYTES - 1))
#define CACHE_ALIGN_BOTTOM(x) ((x) & ~(L1_CACHE_BYTES - 1))
#define BIT(n) (1UL << (n))

enum
{
    SSI_TXE = 0,
    SSI_TXO,
    SSI_RXF,
    SSI_RXO,
    SSI_TXU,
    SSI_RXU,
    SSI_MST,
    SSI_DONE,
    SSI_AXIE,
};
/* SPI mode */
enum
{
    SPI_FRF_STD_SPI,
    SPI_FRF_DUAL_SPI,
    SPI_FRF_QUAD_SPI,
    SPI_FRF_OCT_SPI,
};

/* SPI transmit mode */
enum
{
    SPI_TMOD_TR,
    SPI_TMOD_TO,
    SPI_TMOD_RO,
    SPI_TMOD_EPROMREAD,
};

/* Qspi register */
typedef struct
{
    /* SPI Control Register 0                                    (0x00)*/
    volatile uint32_t ctrlr0;
    /* SPI Control Register 1                                    (0x04)*/
    volatile uint32_t ctrlr1;
    /* SPI Enable Register                                       (0x08)*/
    volatile uint32_t ssienr;
    /* SPI Microwire Control Register                            (0x0c)*/
    volatile uint32_t mwcr;
    /* SPI Slave Enable Register                                 (0x10)*/
    volatile uint32_t ser;
    /* SPI Baud Rate Select                                      (0x14)*/
    volatile uint32_t baudr;
    /* SPI Transmit FIFO Threshold Level                         (0x18)*/
    volatile uint32_t txftlr;
    /* SPI Receive FIFO Threshold Level                          (0x1c)*/
    volatile uint32_t rxftlr;
    /* SPI Transmit FIFO Level Register                          (0x20)*/
    volatile uint32_t txflr;
    /* SPI Receive FIFO Level Register                           (0x24)*/
    volatile uint32_t rxflr;
    /* SPI Status Register                                       (0x28)*/
    volatile uint32_t sr;
    /* SPI Interrupt Mask Register                               (0x2c)*/
    volatile uint32_t imr;
    /* SPI Interrupt Status Register                             (0x30)*/
    volatile uint32_t isr;
    /* SPI Raw Interrupt Status Register                         (0x34)*/
    volatile uint32_t risr;
    /* SPI Transmit FIFO Underflow Interrupt Clear Register      (0x38)*/
    volatile uint32_t txeicr;
    /* SPI Receive FIFO Overflow Interrupt Clear Register        (0x3c)*/
    volatile uint32_t rxoicr;
    /* SPI Receive FIFO Underflow Interrupt Clear Register       (0x40)*/
    volatile uint32_t rxuicr;
    /* SPI Multi-Master Interrupt Clear Register                 (0x44)*/
    volatile uint32_t msticr;
    /* SPI Interrupt Clear Register                              (0x48)*/
    volatile uint32_t icr;
    /* SPI DMA Control Register                                  (0x4c)*/
    volatile uint32_t dmacr;
#if SSIC_HAS_DMA == 1
    /* SPI DMA Transmit Data Level                               (0x50)*/
    volatile uint32_t dmatdlr;
    /* SPI DMA Receive Data Level                                (0x54)*/
    volatile uint32_t dmardlr;
#elif SSIC_HAS_DMA == 2
    /* SPI Destination Burst Length                              (0x50)*/
    volatile uint32_t axiawlen;
    /* SPI Source Burst Length                                   (0x54)*/
    volatile uint32_t axiarlen;
#else
    uint32_t resv0[2];
#endif
    /* SPI Identification Register                               (0x58)*/
    volatile const uint32_t idr;
    /* SPI DWC_ssi component version                             (0x5c)*/
    volatile uint32_t ssic_version_id;
    /* SPI Data Register 0-36                                    (0x60 -- 0xec)*/
    volatile uint32_t dr[36];
    /* SPI RX Sample Delay Register                              (0xf0)*/
    volatile uint32_t rx_sample_delay;
    /* SPI SPI Control Register                                  (0xf4)*/
    volatile uint32_t spi_ctrlr0;
    /* SPI Transmit Drive Edge Register                          (0xf8)*/
    volatile uint32_t ddr_drive_edge;
    /* SPI XIP Mode bits                                         (0xfc)*/
    volatile uint32_t xip_mode_bits;
    /* SPI XIP INCR transfer opcode                              (0x100)*/
    volatile uint32_t xip_incr_inst;
    /* SPI XIP WRAP transfer opcode                              (0x104)*/
    volatile uint32_t xip_wrap_inst;
#if SSIC_CONCURRENT_XIP_EN
    /* SPI XIP Control Register                                  (0x108)*/
    volatile uint32_t xip_ctrl;
    /* SPI XIP Slave Enable Register                             (0x10c)*/
    volatile uint32_t xip_ser;
    /* SPI XIP Receive FIFO Overflow Interrupt Clear Register    (0x110)*/
    volatile uint32_t xrxoicr;
    /* SPI XIP time out register for continuous transfers        (0x114)*/
    volatile uint32_t xip_cnt_time_out;
    /* not support dyn ws                                        (0x118)*/
    uint32_t resv1[1];
    /* SPI Transmit Error Interrupt Clear Register               (0x11c)*/
    volatile uint32_t spitecr;
#else
    uint32_t resv1[6];
#endif
#if SSIC_HAS_DMA == 2
    /* SPI Device Register                                       (0x120)*/
    volatile uint32_t spidr;
    /* SPI Device Address Register                               (0x124)*/
    volatile uint32_t spiar;
    /* AXI Address Register 0                                    (0x128)*/
    volatile uint32_t axiar0;
    /* AXI Address Register 1                                    (0x12c)*/
    volatile uint32_t axiar1;
    /* AXI Master Error Interrupt Clear Register                 (0x130)*/
    volatile uint32_t axiecr;
    /* Transfer Done Clear Interrupt Clear Register              (0x134)*/
    volatile uint32_t donecr;
#endif
    /* This register will not be used and is reserved.           (0x138 ~ 0x13c)*/
    uint32_t resv3[2];
#if SSIC_XIP_WRITE_REG_EN
    /* XIP_WRITE_INCR_INST - XIP Write INCR transfer opcode      (0x140)*/
    volatile uint32_t xip_write_incr_inst;
    /* XIP_WRITE_WRAP_INST - XIP Write WRAP transfer opcode      (0x144)*/
    volatile uint32_t xip_write_wrap_inst;
    /* XIP_WRITE_CTRL - XIP Write Control Register               (0x148)*/
    volatile uint32_t xip_write_ctrl;
#else
    uint32_t resv4[3];
#endif
    // volatile uint32_t endian;
} __attribute__((packed, aligned(4))) k230_spi_reg_t;


#endif
