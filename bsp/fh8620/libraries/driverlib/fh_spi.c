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

#include "fh_def.h"
#include "fh_arch.h"
#include "inc/fh_driverlib.h"

void SPI_EnableSlaveen(struct fh_spi_obj *spi_obj, rt_uint32_t port)
{
    rt_uint32_t reg;

    reg = GET_REG(spi_obj->base + OFFSET_SPI_SER);
    reg |= (1 << port);
    SET_REG(spi_obj->base + OFFSET_SPI_SER, reg);
}

void SPI_DisableSlaveen(struct fh_spi_obj *spi_obj, rt_uint32_t port)
{
    rt_uint32_t reg;

    reg = GET_REG(spi_obj->base + OFFSET_SPI_SER);
    reg &= ~(1 << port);
    SET_REG(spi_obj->base + OFFSET_SPI_SER, reg);
}

void SPI_SetTxLevel(struct fh_spi_obj *spi_obj, rt_uint32_t level)
{
    SET_REG(spi_obj->base + OFFSET_SPI_TXFTLR, level);
}

void SPI_EnableInterrupt(struct fh_spi_obj *spi_obj, rt_uint32_t flag)
{
    rt_uint32_t reg;

    reg = GET_REG(spi_obj->base + OFFSET_SPI_IMR);
    reg |= flag;
    SET_REG(spi_obj->base + OFFSET_SPI_IMR, reg);
}


void SPI_EnableDma(struct fh_spi_obj *spi_obj, rt_uint32_t channel)
{
    rt_uint32_t reg;

    reg = GET_REG(spi_obj->base + OFFSET_SPI_DMACTRL);
    reg |= channel;
    SET_REG(spi_obj->base + OFFSET_SPI_DMACTRL, reg);
}


void SPI_DisableDma(struct fh_spi_obj *spi_obj, rt_uint32_t channel)
{
    rt_uint32_t reg;

    reg = GET_REG(spi_obj->base + OFFSET_SPI_DMACTRL);
    reg &= ~channel;
    SET_REG(spi_obj->base + OFFSET_SPI_DMACTRL, reg);

}


void SPI_DisableInterrupt(struct fh_spi_obj *spi_obj, rt_uint32_t flag)
{
    rt_uint32_t reg;

    reg = GET_REG(spi_obj->base + OFFSET_SPI_IMR);
    reg &= ~flag;
    SET_REG(spi_obj->base + OFFSET_SPI_IMR, reg);

}

rt_uint32_t SPI_InterruptStatus(struct fh_spi_obj *spi_obj)
{
    return GET_REG(spi_obj->base + OFFSET_SPI_ISR);
}

void SPI_ClearInterrupt(struct fh_spi_obj *spi_obj)
{
    GET_REG(spi_obj->base + OFFSET_SPI_ICR);
}

rt_uint32_t SPI_ReadTxFifoLevel(struct fh_spi_obj *spi_obj)
{
    return GET_REG(spi_obj->base + OFFSET_SPI_TXFLR);
}

rt_uint32_t SPI_ReadRxFifoLevel(struct fh_spi_obj *spi_obj)
{
    return GET_REG(spi_obj->base + OFFSET_SPI_RXFLR);
}

UINT8 SPI_ReadData(struct fh_spi_obj *spi_obj)
{
    return GET_REG(spi_obj->base + OFFSET_SPI_DR) & 0xff;
}

void SPI_WriteData(struct fh_spi_obj *spi_obj, UINT8 data)
{
    SET_REG(spi_obj->base + OFFSET_SPI_DR, data);
}

rt_uint32_t SPI_ReadStatus(struct fh_spi_obj *spi_obj)
{
    return GET_REG(spi_obj->base + OFFSET_SPI_SR);
}

void SPI_Enable(struct fh_spi_obj *spi_obj, int enable)
{
    SET_REG(spi_obj->base + OFFSET_SPI_SSIENR, enable);
}

void SPI_WriteTxDmaLevel(struct fh_spi_obj *spi_obj, rt_uint32_t data)
{
    SET_REG(spi_obj->base + OFFSET_SPI_DMATDL, data);
}

void SPI_WriteRxDmaLevel(struct fh_spi_obj *spi_obj, rt_uint32_t data)
{
    SET_REG(spi_obj->base + OFFSET_SPI_DMARDL, data);
}

void SPI_SetParameter(struct fh_spi_obj *spi_obj)
{
    rt_uint32_t reg;
    struct spi_config *config;

    config = &spi_obj->config;

    SET_REG(spi_obj->base + OFFSET_SPI_BAUD, config->clk_div);

    reg = GET_REG(spi_obj->base + OFFSET_SPI_CTRL0);

    reg &= ~(0x3ff);
    reg |= config->data_size        \
         | config->frame_format     \
         | config->clk_phase        \
         | config->clk_polarity     \
         | config->transfer_mode;

    SET_REG(spi_obj->base + OFFSET_SPI_CTRL0, reg);
}
