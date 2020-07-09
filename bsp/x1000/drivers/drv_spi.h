/*
 * File      : board_spi_master.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */



#ifndef DRV_SPI_H__
#define DRV_SPI_H__

#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_gpio.h"

/* SSI REGISTER */
#define SSI_DR       0x00
#define SSI_CR0      0x04
#define SSI_CR1      0x08
#define SSI_SR       0x0C
#define SSI_ITR      0x10
#define SSI_ICR      0x14
#define SSI_GR       0x18

/* SSI Data Register (SSI_DR) */
#define DR_GPC_BIT          0
#define DR_GPC_MASK         (0x1ff << SSI_DR_GPC_BIT)

/* SSI Control Register 0 (SSI_CR0) */
#define CR0_TENDIAN_BIT     18
#define CR0_TENDIAN_MASK    (3 << CR0_TENDIAN_BIT)
#define CR0_RENDIAN_BIT     16
#define CR0_RENDIAN_MASK    (3 << CR0_RENDIAN_BIT)
#define CR0_SSIE            (1 << 15)
#define CR0_TIE             (1 << 14)
#define CR0_RIE             (1 << 13)
#define CR0_TEIE            (1 << 12)
#define CR0_REIE            (1 << 11)
#define CR0_LOOP            (1 << 10)
#define CR0_RFINE           (1 << 9)
#define CR0_RFINC           (1 << 8)
#define CR0_EACLRUN         (1 << 7) /* hardware auto clear underrun when TxFifo no empty */
#define CR0_FSEL            (1 << 6)
#define CR0_VRCNT           (1 << 4)
#define CR0_TFMODE          (1 << 3)
#define CR0_TFLUSH          (1 << 2)
#define CR0_RFLUSH          (1 << 1)
#define CR0_DISREV          (1 << 0)

/* SSI Control Register 1 (SSI_CR1) */
#define CR1_FRMHL_BIT           30
#define CR1_FRMHL_MASK          (0x3 << CR1_FRMHL_BIT)
#define CR1_FRMHL_CELOW_CE2LOW  (0 << CR1_FRMHL_BIT) /* SSI_CE_ is low valid and SSI_CE2_ is low valid */
#define CR1_FRMHL_CEHIGH_CE2LOW (1 << CR1_FRMHL_BIT) /* SSI_CE_ is high valid and SSI_CE2_ is low valid */
#define CR1_FRMHL_CELOW_CE2HIGH (2 << CR1_FRMHL_BIT) /* SSI_CE_ is low valid  and SSI_CE2_ is high valid */
#define CR1_FRMHL_CEHIGH_CE2HIGH    (3 << CR1_FRMHL_BIT) /* SSI_CE_ is high valid and SSI_CE2_ is high valid */
#define CR1_TFVCK_BIT           28
#define CR1_TFVCK_MASK          (0x3 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_0               (0 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_1               (1 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_2               (2 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_3               (3 << CR1_TFVCK_BIT)
#define CR1_TCKFI_BIT           26
#define CR1_TCKFI_MASK          (0x3 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_0               (0 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_1               (1 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_2               (2 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_3               (3 << CR1_TCKFI_BIT)
#define CR1_ITFRM       (1 << 24)
#define CR1_UNFIN       (1 << 23)
#define CR1_FMAT_BIT        20
#define CR1_FMAT_MASK       (0x3 << CR1_FMAT_BIT)
  #define CR1_FMAT_SPI        (0 << CR1_FMAT_BIT) /* Motorola¡¯s SPI format */
  #define CR1_FMAT_SSP        (1 << CR1_FMAT_BIT) /* TI's SSP format */
  #define CR1_FMAT_MW1        (2 << CR1_FMAT_BIT) /* National Microwire 1 format */
  #define CR1_FMAT_MW2        (3 << CR1_FMAT_BIT) /* National Microwire 2 format */
#define CR1_TTRG_BIT        16 /* SSI1 TX trigger */
#define CR1_TTRG_MASK       (0xf << CR1_TTRG_BIT)
#define CR1_MCOM_BIT        12
#define CR1_MCOM_MASK       (0xf << CR1_MCOM_BIT)
//  #define CR1_MCOM_BIT(NO)      (##NO## << CR1_MCOM_BIT) /* N-bit command selected */
#define CR1_RTRG_BIT        8 /* SSI RX trigger */
#define CR1_RTRG_MASK       (0xf << CR1_RTRG_BIT)
#define CR1_FLEN_BIT        3
#define CR1_FLEN_MASK       (0x1f << CR1_FLEN_BIT)
  #define CR1_FLEN_2BIT       (0x0 << CR1_FLEN_BIT)
#define CR1_PHA         (1 << 1)
#define CR1_POL         (1 << 0)

/* SSI Status Register (SSI_SR) */
#define SR_TFIFONUM_BIT     16
#define SR_TFIFONUM_MASK    (0xff << SR_TFIFONUM_BIT)
#define SR_RFIFONUM_BIT     8
#define SR_RFIFONUM_MASK    (0xff << SR_RFIFONUM_BIT)
#define SR_END          (1 << 7)
#define SR_BUSY         (1 << 6)
#define SR_TFF          (1 << 5)
#define SR_RFE          (1 << 4)
#define SR_TFHE         (1 << 3)
#define SR_RFHF         (1 << 2)
#define SR_UNDR         (1 << 1)
#define SR_OVER         (1 << 0)

/* SSI Interval Time Control Register (SSI_ITR) */
#define ITR_CNTCLK          (1 << 15)
#define ITR_IVLTM_BIT       0
#define ITR_IVLTM_MASK      (0x7fff << ITR_IVLTM_BIT)



#define R_MODE              0x1
#define W_MODE              0x2
#define RW_MODE             (R_MODE | W_MODE)

#define R_DMA               0x4
#define W_DMA               0x8
#define RW_DMA              (R_DMA |W_DMA)

#define SPI_DMA_ACK         0x1

#define SPI_DMA_ERROR       -3
#define SPI_CPU_ERROR       -4

#define SPI_COMPLETE        5

#define JZ_SSI_MAX_FIFO_ENTRIES     128
#define JZ_SSI_DMA_BURST_LENGTH     16

#define FIFO_W8         8
#define FIFO_W16        16
#define FIFO_W32        32

#define SPI_BITS_8      8
#define SPI_BITS_16     16
#define SPI_BITS_32     32

#define SPI_8BITS       1
#define SPI_16BITS      2
#define SPI_32BITS      4


/* tx rx threshold from 0x0 to 0xF */
#define SSI_FULL_THRESHOLD          0xF
#define SSI_TX_FIFO_THRESHOLD       0x1
#define SSI_RX_FIFO_THRESHOLD       (SSI_FULL_THRESHOLD - SSI_TX_FIFO_THRESHOLD)
#define SSI_SAFE_THRESHOLD          0x1

#define CPU_ONCE_BLOCK_ENTRIES      ((SSI_FULL_THRESHOLD-SSI_TX_FIFO_THRESHOLD)*8)

#define MAX_SSI_INTR        10000

#define MAX_SSICDR          63
#define MAX_CGV             255

#define SSI_DMA_FASTNESS_CHNL    0   // SSI controller [n] FASTNESS when probe();

#define JZ_NEW_CODE_TYPE

#define BUFFER_SIZE PAGE_SIZE

#define CONFIG_DMA_ENGINE 1

#define SUSPND    (1<<0)
#define SPIBUSY   (1<<1)
#define RXBUSY    (1<<2)
#define TXBUSY    (1<<3)


struct jz_spi_rx_fifo
{
    /* software fifo */
    rt_uint8_t *buffer;

    rt_uint16_t put_index, get_index;
};

struct jz_spi_tx_fifo
{
    struct rt_completion completion;
};

struct jz_spi_rx_dma
{
    rt_bool_t activated;
};

struct jz_spi_tx_dma
{
    rt_bool_t activated;
    struct rt_data_queue data_queue;
};


typedef struct jz_spi
{
    struct rt_spi_bus       parent;
//    struct rt_semaphore     spi_done_sem;
    struct rt_completion    completion;

    struct clk  *clk;
    struct clk  *clk_gate;

    uint32_t    base;
    uint8_t     is_first;
    uint8_t     xfer_unit_size; /* 1,2,4 */

    uint32_t    totalCount;
    uint32_t    sendCount;
    uint32_t    recvCount;

    uint8_t     tx_trigger;     /* 0-128 */
    uint8_t     rx_trigger;     /* 0-128 */

    uint8_t     *rx_buf;
    uint8_t     *tx_buf;

    uint32_t    (*rx_func)(struct jz_spi *);
    uint32_t    (*tx_func)(struct jz_spi *);
}jz_spi_bus_t;

struct jz_spi_cs
{
    enum gpio_port    port;
    enum gpio_pin     pin;
};

static uint32_t spi_readl(struct jz_spi *spi_bus,uint32_t offset)
{
    return readl(spi_bus->base + offset);
}

static void spi_writel(struct jz_spi *spi_bus, uint32_t offset,uint32_t value)
{
    writel(value, spi_bus->base + offset);
}

static inline void spi_set_frmhl(struct jz_spi *spi, unsigned int frmhl)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp = (tmp & ~CR1_FRMHL_MASK) | frmhl;
    spi_writel(spi, SSI_CR1, tmp);
}
static inline void spi_set_clock_phase(struct jz_spi *spi, unsigned int cpha)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp = (tmp & ~CR1_PHA) | (cpha ? CR1_PHA : 0);
    spi_writel(spi, SSI_CR1, tmp);
}

static inline void spi_set_clock_polarity(struct jz_spi *spi, unsigned int cpol)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp = (tmp & ~CR1_POL) | (cpol ? CR1_POL : 0);
    spi_writel(spi, SSI_CR1, tmp);
}

static inline void spi_set_tx_msb(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_TENDIAN_MASK;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_set_tx_lsb(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= (tmp & ~CR0_TENDIAN_MASK) | (0x3 << CR0_TENDIAN_BIT);
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_set_rx_msb(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_RENDIAN_MASK;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_set_rx_lsb(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= (tmp & ~CR0_RENDIAN_MASK) | (0x3 << CR0_RENDIAN_BIT);
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_enable_loopback(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_LOOP;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_loopback(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_LOOP;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_set_frame_length(struct jz_spi *spi, u32 len)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp = (tmp & ~CR1_FLEN_MASK) | (((len) - 2) << CR1_FLEN_BIT);
    spi_writel(spi, SSI_CR1, tmp);
}

static inline void spi_set_tx_trigger(struct jz_spi *spi, u32 val)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp = (tmp & ~CR1_TTRG_MASK) | ((val)/8) << CR1_TTRG_BIT;
    spi_writel(spi, SSI_CR1, tmp);
}

static inline void spi_set_rx_trigger(struct jz_spi *spi, u32 val)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp = (tmp & ~CR1_RTRG_MASK) | ((val)/8) << CR1_RTRG_BIT;
    spi_writel(spi, SSI_CR1, tmp);
}

static inline void spi_enable_txfifo_half_empty_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_TIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_txfifo_half_empty_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_TIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_enable_rxfifo_half_full_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_RIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_rxfifo_half_full_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_RIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_enable_tx_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_TIE | CR0_TEIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_tx_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~(CR0_TIE | CR0_TEIE);
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_enable_rx_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_RIE | CR0_REIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_rx_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~(CR0_RIE | CR0_REIE);
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_enable_tx_error_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_TEIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_tx_error_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_TEIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_enable_rx_error_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_REIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_rx_error_intr(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_REIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_underrun_auto_clear(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_EACLRUN;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_clear_errors(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_SR);
    tmp &= ~(SR_UNDR | SR_OVER);
    spi_writel(spi, SSI_SR, tmp);
}

static inline void spi_set_format(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp &= ~CR1_FMAT_MASK;
    tmp |= CR1_FMAT_SPI;
    tmp &= ~(CR1_TFVCK_MASK | CR1_TCKFI_MASK);
    tmp |= (CR1_TFVCK_0 | CR1_TCKFI_0);
//  tmp |= (CR1_TFVCK_1 | CR1_TCKFI_1);
//  tmp |= (CR1_TFVCK_2 | CR1_TCKFI_2);
//  tmp |= (CR1_TFVCK_3 | CR1_TCKFI_3);
    spi_writel(spi, SSI_CR1, tmp);
}

static inline void spi_enable_receive(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_DISREV;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_disable_receive(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_DISREV;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_flush_fifo(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_TFLUSH | CR0_RFLUSH;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_finish_transmit(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp &= ~CR1_UNFIN;
    spi_writel(spi, SSI_CR1, tmp);
}

static inline void spi_start_transmit(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR1);
    tmp |= CR1_UNFIN;
    spi_writel(spi, SSI_CR1, tmp);
}

static inline int spi_is_rxfifo_empty(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_SR) & SR_RFE;
}

static inline int spi_check_busy(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_SR) & SR_BUSY;
}

static inline void spi_disable(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_SSIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_enable(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_SSIE;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline u32 spi_get_rxfifo_count(struct jz_spi *spi)
{
    return (spi_readl(spi, SSI_SR) & SR_RFIFONUM_MASK) >> SR_RFIFONUM_BIT;
}

static inline void spi_flush_txfifo(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_TFLUSH;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_flush_rxfifo(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_RFLUSH;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline int spi_get_underrun(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_SR) & SR_UNDR;
}

static inline int spi_get_overrun(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_SR) & SR_OVER;
}

static inline int spi_get_transfer_end(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_SR) & SR_END;
}

static inline int spi_get_tx_error_intr(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_CR0) & CR0_TEIE;
}

static inline int spi_get_rx_error_intr(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_CR0) & CR0_REIE;
}

static inline int spi_get_rxfifo_half_full(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_SR) & SR_RFHF;
}

static inline int spi_get_txfifo_half_empty(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_SR) & SR_TFHE;
}

static inline int spi_get_txfifo_half_empty_intr(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_CR0) & CR0_TIE;
}

static inline int spi_get_rxfifo_half_full_intr(struct jz_spi *spi)
{
    return spi_readl(spi, SSI_CR0) & CR0_RIE;
}

static inline void spi_select_ce0(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp &= ~CR0_FSEL;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_select_ce1(struct jz_spi *spi)
{
    u32 tmp;
    tmp = spi_readl(spi, SSI_CR0);
    tmp |= CR0_FSEL;
    spi_writel(spi, SSI_CR0, tmp);
}

static inline void spi_send_data(struct jz_spi *spi, u32 value)
{
    spi_writel(spi, SSI_DR, value);
}

/* the spi->mode bits understood by this driver: */
#define MODEBITS (SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST | SPI_LOOP)
#define SPI_BITS_SUPPORT  (SPI_BITS_8 | SPI_BITS_16 | SPI_BITS_32)

#endif /* _SPI_MASTER_H_ */
