/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2020. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __DW_SPI_HEADER_H__
#define __DW_SPI_HEADER_H__

#include "stdint.h"
#include "stdbool.h"

#define SPI_REGBASE                     0x04180000
#define SPI_REF_CLK                     187500000
#define MAX_SPI_NUM                     4

#define CVI_DW_SPI_CTRLR0                   0x00
#define CVI_DW_SPI_CTRLR1                   0x04
#define CVI_DW_SPI_SSIENR                   0x08
#define CVI_DW_SPI_MWCR                     0x0c
#define CVI_DW_SPI_SER                      0x10
#define CVI_DW_SPI_BAUDR                    0x14
#define CVI_DW_SPI_TXFTLR                   0x18
#define CVI_DW_SPI_RXFTLR                   0x1c
#define CVI_DW_SPI_TXFLR                    0x20
#define CVI_DW_SPI_RXFLR                    0x24
#define CVI_DW_SPI_SR                       0x28
#define CVI_DW_SPI_IMR                      0x2c
#define CVI_DW_SPI_ISR                      0x30
#define CVI_DW_SPI_RISR                     0x34
#define CVI_DW_SPI_TXOICR                   0x38
#define CVI_DW_SPI_RXOICR                   0x3c
#define CVI_DW_SPI_RXUICR                   0x40
#define CVI_DW_SPI_MSTICR                   0x44
#define CVI_DW_SPI_ICR                      0x48
#define CVI_DW_SPI_DMACR                    0x4c
#define CVI_DW_SPI_DMATDLR                  0x50
#define CVI_DW_SPI_DMARDLR                  0x54
#define CVI_DW_SPI_IDR                      0x58
#define CVI_DW_SPI_VERSION                  0x5c
#define CVI_DW_SPI_DR                       0x60

/* Bit fields in CTRLR0 */
#define CVI_SPI_DFS_OFFSET                  0

#define CVI_SPI_FRF_OFFSET                  4
#define CVI_SPI_FRF_SPI                     0x0
#define CVI_SPI_FRF_SSP                     0x1
#define CVI_SPI_FRF_MICROWIRE               0x2
#define CVI_SPI_FRF_RESV                    0x3

#define CVI_SPI_MODE_OFFSET                 6
#define CVI_SPI_SCPH_OFFSET                 6
#define CVI_SPI_SCOL_OFFSET                 7

#define CVI_SPI_TMOD_OFFSET                 8
#define CVI_SPI_TMOD_MASK                   (0x3 << CVI_SPI_TMOD_OFFSET)
#define CVI_SPI_TMOD_TR                     0x0             /* xmit & recv */
#define CVI_SPI_TMOD_TO                     0x1             /* xmit only */
#define CVI_SPI_TMOD_RO                     0x2             /* recv only */
#define CVI_SPI_TMOD_EPROMREAD              0x3             /* eeprom read mode */

#define CVI_SPI_SLVOE_OFFSET                10
#define CVI_SPI_SRL_OFFSET                  11
#define CVI_SPI_CFS_OFFSET                  12

/* Bit fields in SR, 7 bits */
#define CVI_SR_MASK                         0x7f
#define CVI_SR_BUSY                         (1 << 0)
#define CVI_SR_TF_NOT_FULL                  (1 << 1)
#define CVI_SR_TF_EMPT                      (1 << 2)
#define CVI_SR_RF_NOT_EMPT                  (1 << 3)
#define CVI_SR_RF_FULL                      (1 << 4)
#define CVI_SR_TX_ERR                       (1 << 5)
#define SR_DCOL                         (1 << 6)

/* Bit fields in ISR, IMR, RISR, 7 bits */
#define CVI_SPI_INT_TXEI                    (1 << 0)
#define CVI_SPI_INT_TXOI                    (1 << 1)
#define CVI_SPI_INT_RXUI                    (1 << 2)
#define CVI_SPI_INT_RXOI                    (1 << 3)
#define CVI_SPI_INT_RXFI                    (1 << 4)
#define CVI_SPI_INT_MSTI                    (1 << 5)

/* Bit fields in DMACR */
#define CVI_SPI_DMA_RDMAE                   (1 << 0)
#define CVI_SPI_DMA_TDMAE                   (1 << 1)

/* TX RX interrupt level threshold, max can be 256 */
#define CVI_SPI_INT_THRESHOLD               32
#define BITS_PER_BYTE                       8
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

struct dw_spi {
    void                    *regs;
    int                     irq;
    int                     index;
    uint32_t                fifo_len;       /* depth of the FIFO buffer */
    uint16_t                num_cs;        /* supported slave numbers */
    uint32_t        speed_hz;
    /* Current message transfer state info */
    size_t                  len;
    const void              *tx;
    const void              *tx_end;
    void                    *rx;
    void                    *rx_end;
    uint32_t        rx_len;
    uint32_t        tx_len;
    uint8_t                 n_bytes;       /* current is a 1/2 bytes op */
    uint32_t                dma_width;
    int             (*transfer_handler)(struct dw_spi *dws);

    /* Bus interface info */
    void                    *priv;
};

struct spi_delay {
#define SPI_DELAY_UNIT_USECS    0
#define SPI_DELAY_UNIT_NSECS    1
#define SPI_DELAY_UNIT_SCK      2
        uint16_t     value;
        uint8_t      unit;
};

#define SPI_CPHA                0x01
#define SPI_CPOL                0x02

#define SPI_MODE_0              (0|0)
#define SPI_MODE_1              (0|SPI_CPHA)
#define SPI_MODE_2              (SPI_CPOL|0)
#define SPI_MODE_3              (SPI_CPOL|SPI_CPHA)

enum transfer_type {
    POLL_TRAN = 0,
    IRQ_TRAN,
    DMA_TRAN,
};

enum dw_ssi_type {
    SSI_MOTO_SPI = 0,
    SSI_TI_SSP,
    SSI_NS_MICROWIRE,
};

#define SPI_FORMAT_CPOL0_CPHA0  0
#define SPI_FORMAT_CPOL0_CPHA1  1
#define SPI_FORMAT_CPOL1_CPHA0  2
#define SPI_FORMAT_CPOL1_CPHA1  3

#ifndef BIT
#define BIT(_n)  ( 1 << (_n))
#endif

static void dw_writel(struct dw_spi *dws, uint32_t off, uint32_t val)
{
    writel(val, (dws->regs + off));
}

static uint32_t dw_readl(struct dw_spi *dws, uint32_t off)
{
    return readl(dws->regs + off);
}

static inline void spi_enable_chip(struct dw_spi *dws, int enable)
{
    dw_writel(dws, CVI_DW_SPI_SSIENR, (enable ? 1 : 0));
}

static inline void spi_set_clk(struct dw_spi *dws, uint16_t div)
{
    dw_writel(dws, CVI_DW_SPI_BAUDR, div);
}

/* Disable IRQ bits */
static inline void spi_mask_intr(struct dw_spi *dws, uint32_t mask)
{
    uint32_t new_mask;

    new_mask = dw_readl(dws, CVI_DW_SPI_IMR) & ~mask;
    dw_writel(dws, CVI_DW_SPI_IMR, new_mask);
}

static inline uint32_t spi_get_status(struct dw_spi *dws)
{
    return dw_readl(dws, CVI_DW_SPI_SR);
}

/* Enable IRQ bits */
static inline void spi_umask_intr(struct dw_spi *dws, uint32_t mask)
{
    uint32_t new_mask;

    new_mask = dw_readl(dws, CVI_DW_SPI_IMR) | mask;
    dw_writel(dws, CVI_DW_SPI_IMR, new_mask);
}

static inline void spi_reset_chip(struct dw_spi *dws)
{
    spi_enable_chip(dws, 0);
    spi_mask_intr(dws, 0xff);
    dw_readl(dws, CVI_DW_SPI_ICR);
    dw_writel(dws, CVI_DW_SPI_SER, 0);
    spi_enable_chip(dws, 1);
}

static inline void spi_enable_dma(struct dw_spi *dws, uint8_t is_tx, uint8_t op)
{
    /* 1: TDMAE, 0: RDMAE */
    uint32_t val = dw_readl(dws, CVI_DW_SPI_DMACR);

    if (op)
        val |= 1 << (!!is_tx);
    else
        val &= ~(1 << (!!is_tx));

    dw_writel(dws, CVI_DW_SPI_DMACR, val);
}

static inline void spi_shutdown_chip(struct dw_spi *dws)
{
    spi_enable_chip(dws, 0);
    spi_set_clk(dws, 0);
}

void spi_hw_init(struct dw_spi *dws);
void dw_spi_set_controller_mode(struct dw_spi *dws, uint8_t enable_master);
void dw_spi_set_polarity_and_phase(struct dw_spi *dws, uint8_t format);
uint32_t dw_spi_set_clock(struct dw_spi *dws, uint32_t clock_in, uint32_t clock_out);
int dw_spi_set_data_frame_len(struct dw_spi *dws, uint32_t size);
void dw_spi_set_cs(struct dw_spi *dws, bool enable, uint32_t index);
void dw_reader(struct dw_spi *dws);
void dw_writer(struct dw_spi *dws);
void set_tran_mode(struct dw_spi *dws);
void dw_spi_show_regs(struct dw_spi *dws);
int poll_transfer(struct dw_spi *dws);
int dw_spi_check_status(struct dw_spi *dws, bool raw);
#endif
