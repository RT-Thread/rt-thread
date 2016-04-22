/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef FH_SPI_H_
#define FH_SPI_H_

#include "fh_def.h"
#include "fh_arch.h"

#define OFFSET_SPI_CTRL0                        (0x00)
#define OFFSET_SPI_CTRL1                        (0x04)
#define OFFSET_SPI_SSIENR                       (0x08)
#define OFFSET_SPI_MWCR                         (0x0c)
#define OFFSET_SPI_SER                          (0x10)
#define OFFSET_SPI_BAUD                         (0x14)
#define OFFSET_SPI_TXFTLR                       (0x18)
#define OFFSET_SPI_RXFTLR                       (0x1c)
#define OFFSET_SPI_TXFLR                        (0x20)
#define OFFSET_SPI_RXFLR                        (0x24)
#define OFFSET_SPI_SR                           (0x28)
#define OFFSET_SPI_IMR                          (0x2c)
#define OFFSET_SPI_ISR                          (0x30)
#define OFFSET_SPI_RISR                         (0x34)
#define OFFSET_SPI_TXOIC                        (0x38)
#define OFFSET_SPI_RXOIC                        (0x3c)
#define OFFSET_SPI_RXUIC                        (0x40)
#define OFFSET_SPI_MSTIC                        (0x44)
#define OFFSET_SPI_ICR                          (0x48)
#define OFFSET_SPI_DMACTRL                      (0x4c)
#define OFFSET_SPI_DMATDL                       (0x50)
#define OFFSET_SPI_DMARDL                       (0x54)
#define OFFSET_SPI_IDR                          (0x58)
#define OFFSET_SPI_SSI_COMPVER                  (0x5c)
#define OFFSET_SPI_DR                           (0x60)


#define SPI_FORMAT_MOTOROLA         (0x00)
#define SPI_FORMAT_TI               (0x10)
#define SPI_FORMAT_MICROWIRE        (0x20)

#define SPI_MODE_TX_RX              (0x000)
#define SPI_MODE_TX_ONLY            (0x100)
#define SPI_MODE_RX_ONLY            (0x200)
#define SPI_MODE_EEPROM             (0x300)

#define SPI_DATA_SIZE_4BIT          (0x03)
#define SPI_DATA_SIZE_5BIT          (0x04)
#define SPI_DATA_SIZE_6BIT          (0x05)
#define SPI_DATA_SIZE_7BIT          (0x06)
#define SPI_DATA_SIZE_8BIT          (0x07)
#define SPI_DATA_SIZE_9BIT          (0x08)
#define SPI_DATA_SIZE_10BIT         (0x09)
#define SPI_DATA_SIZE_16BIT         (0x0f)

#define SPI_POLARITY_HIGH           (1<<7)
#define SPI_POLARITY_LOW            (0<<7)

#define SPI_PHASE_RX_FIRST          (0<<6)
#define SPI_PHASE_TX_FIRST          (1<<6)

#define SPI_FIFO_DEPTH              (32)

#define SPI_IRQ_TXEIM               (1<<0)
#define SPI_IRQ_TXOIM               (1<<1)
#define SPI_IRQ_RXUIM               (1<<2)
#define SPI_IRQ_RXOIM               (1<<3)
#define SPI_IRQ_RXFIM               (1<<4)
#define SPI_IRQ_MSTIM               (1<<5)
#define SPI_IRQ_ALL                 (0x3f)

#define SPI_ISR_FLAG        (SPI_IRQ_TXEIM|SPI_IRQ_TXOIM|SPI_IRQ_RXUIM|SPI_IRQ_RXOIM)
#define SPI_ISR_ERROR       (SPI_IRQ_TXOIM | SPI_IRQ_RXUIM | SPI_IRQ_RXOIM)

#define SPI_STATUS_BUSY             (1)


#define SPI_TX_DMA			(1<<1)
#define SPI_RX_DMA			(1<<0)


struct spi_config
{
    rt_uint32_t        frame_format;
    rt_uint32_t        transfer_mode;
    rt_uint32_t        clk_polarity;
    rt_uint32_t        clk_phase;
    rt_uint32_t        data_size;
    rt_uint32_t        clk_div;
};




struct fh_spi_obj
{
    rt_uint32_t        id;
    rt_uint32_t        irq;
    rt_uint32_t        base;
    rt_uint32_t        fifo_len;
    rt_uint32_t        transfered_len;
    rt_uint32_t        received_len;
    rt_uint32_t        cs_gpio_pin;

    struct spi_config config;
};

void SPI_EnableSlaveen(struct fh_spi_obj *spi_obj, rt_uint32_t port);
void SPI_DisableSlaveen(struct fh_spi_obj *spi_obj, rt_uint32_t port);
void SPI_SetTxLevel(struct fh_spi_obj *spi_obj, rt_uint32_t level);
void SPI_EnableIrq(struct fh_spi_obj *spi_obj, rt_uint32_t flag);
void SPI_DisableIrq(struct fh_spi_obj *spi_obj, rt_uint32_t flag);
rt_uint32_t SPI_InterruptStatus(struct fh_spi_obj *spi_obj);
void SPI_ClearInterrupt(struct fh_spi_obj *spi_obj);
rt_uint32_t SPI_ReadTxFifoLevel(struct fh_spi_obj *spi_obj);
rt_uint32_t SPI_ReadRxFifoLevel(struct fh_spi_obj *spi_obj);
UINT8 SPI_ReadData(struct fh_spi_obj *spi_obj);
void SPI_WriteData(struct fh_spi_obj *spi_obj, UINT8 data);
rt_uint32_t SPI_ReadStatus(struct fh_spi_obj *spi_obj);
void SPI_Enable(struct fh_spi_obj *spi_obj, int enable);
void SPI_SetParameter(struct fh_spi_obj *spi_obj);
void SPI_EnableDma(struct fh_spi_obj *spi_obj, rt_uint32_t channel);
void SPI_DisableDma(struct fh_spi_obj *spi_obj, rt_uint32_t channel);
void SPI_WriteTxDmaLevel(struct fh_spi_obj *spi_obj, rt_uint32_t data);
void SPI_WriteRxDmaLevel(struct fh_spi_obj *spi_obj, rt_uint32_t data);
#endif /* FH_SPI_H_ */
