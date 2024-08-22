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
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "mmio.h"
#include "dw_spi.h"

#include <rthw.h>

#ifdef SPI_DEBUG
#define SP_DEBUG_LOG    printf
#else
#define SP_DEBUG_LOG
#endif

/* Restart the controller, disable all interrupts, clean rx fifo */
void spi_hw_init(struct dw_spi *dws)
{
    /*
     * Try to detect the FIFO depth if not set by interface driver,
     * the depth could be from 2 to 256 from HW spec
     */
    if (!dws->fifo_len) {
        uint32_t fifo;

        for (fifo = 1; fifo < 256; fifo++) {
            dw_writel(dws, CVI_DW_SPI_TXFTLR, fifo);
            if (fifo != dw_readl(dws, CVI_DW_SPI_TXFTLR))
                break;
        }
        dw_writel(dws, CVI_DW_SPI_TXFTLR, 0);

        dws->fifo_len = (fifo == 1) ? 0 : fifo;

        SP_DEBUG_LOG("Detected FIFO size: %u bytes\n", dws->fifo_len);
    }
}

uint32_t min3(uint32_t a, uint32_t b, uint32_t c)
{
    uint32_t tmp;

    tmp = (a < b) ? a : b;
    return (tmp < c) ? tmp : c;
}

static inline void cpu_relax(void)
{
    //asm volatile("" ::: "memory");
}

static inline uint32_t tx_max(struct dw_spi *dws)
{
    uint32_t tx_left, tx_room, rxtx_gap, temp;
    cpu_relax();
    tx_left = dws->tx_len;
    tx_room = dws->fifo_len - dw_readl(dws, CVI_DW_SPI_TXFLR);

    /*
     * Another concern is about the tx/rx mismatch, we
     * though to use (dws->fifo_len - rxflr - txflr) as
     * one maximum value for tx, but it doesn't cover the
     * data which is out of tx/rx fifo and inside the
     * shift registers. So a control from sw point of
     * view is taken.
     */

    SP_DEBUG_LOG("tx left: %#x, tx room: %#x\n", tx_left, tx_room);
    if (dws->rx != NULL && dws->tx != NULL) {
        cpu_relax();
        rxtx_gap =  dws->fifo_len - (dws->rx_len - dws->tx_len);
        temp = min3(tx_left, tx_room, (uint32_t)(rxtx_gap));
    } else {
        temp = tx_left < tx_room ? tx_left : tx_room;
    }

    SP_DEBUG_LOG("temp: %#x\n", temp);
    return temp;
}

void dw_writer(struct dw_spi *dws)
{
    uint32_t max;
    uint16_t txw = 0;

    max = tx_max(dws);
    SP_DEBUG_LOG("max: %#x \n", max);
    while (max--) {
        if (dws->tx) {
            if (dws->n_bytes == 1)
                txw = *(uint8_t *)(dws->tx);
            else
                txw = *(uint16_t *)(dws->tx);
        }
        dw_writel(dws, CVI_DW_SPI_DR, txw);
        dws->tx += dws->n_bytes;
        --dws->tx_len;
    }
}

static inline uint32_t rx_max(struct dw_spi *dws)
{
    uint32_t temp;
    uint32_t rx_left = dws->rx_len;
    uint32_t data_in_fifo = dw_readl(dws, CVI_DW_SPI_RXFLR);

    temp = (rx_left < data_in_fifo ? rx_left : data_in_fifo);
    SP_DEBUG_LOG("data_in_fifo:%u temp: %u\n", data_in_fifo, temp);
    return temp;
}

int dw_spi_check_status(struct dw_spi *dws, bool raw)
{
    uint32_t irq_status;
    int ret = 0;

    if (raw)
        irq_status = dw_readl(dws, CVI_DW_SPI_RISR);
    else
        irq_status = dw_readl(dws, CVI_DW_SPI_ISR);

    if (irq_status & CVI_SPI_INT_RXOI) {
        SP_DEBUG_LOG("RX FIFO overflow detected\n");
        ret = -1;
    }

    if (irq_status & CVI_SPI_INT_RXUI) {
        SP_DEBUG_LOG("RX FIFO underflow detected\n");
        ret = -1;
    }

    if (irq_status & CVI_SPI_INT_TXOI) {
        SP_DEBUG_LOG("TX FIFO overflow detected\n");
        ret = -1;
    }

    if (ret)
        spi_reset_chip(dws);

    return ret;
}

void dw_reader(struct dw_spi *dws)
{
    uint32_t max;
    uint16_t rxw;

    max = rx_max(dws);
    SP_DEBUG_LOG("max: %#x \n", max);
    while (max--) {
        rxw = dw_readl(dws, CVI_DW_SPI_DR);
        if (dws->rx) {
            if (dws->n_bytes == 1)
                *(uint8_t *)(dws->rx) = rxw;
            else
                *(uint16_t *)(dws->rx) = rxw;
            dws->rx += dws->n_bytes;
        }
        --dws->rx_len;
    }
}

int spi_delay_to_ns(struct spi_delay *_delay, struct dw_spi *dws)
{
    uint32_t delay = _delay->value;
    uint32_t unit = _delay->unit;
    uint32_t hz;

    if (!delay)
        return 0;

    switch (unit) {
        case SPI_DELAY_UNIT_USECS:
            delay *= 1000;
            break;
        case SPI_DELAY_UNIT_NSECS: /* nothing to do here */
            break;
        case SPI_DELAY_UNIT_SCK:
            /* clock cycles need to be obtained from spi_transfer */
            if (!dws)
                return -1;
            /* if there is no effective speed know, then approximate
             * by underestimating with half the requested hz
             */
            hz = dws->speed_hz / 2;
            if (!hz)
                return -1;
            delay *= DIV_ROUND_UP(1000000000, hz);
            break;
        default:
            return -EINVAL;
    }

    return delay;
}

static void _spi_transfer_delay_ns(uint32_t ns)
{
        if (!ns)
                return;
        if (ns <= 1000) {
        rt_hw_us_delay(1);
        } else {
                uint32_t us = DIV_ROUND_UP(ns, 1000);
                rt_hw_us_delay(us);
        }
}

int spi_delay_exec(struct spi_delay *_delay, struct dw_spi *dws)
{
        int delay;

        if (!_delay)
                return -1;

        delay = spi_delay_to_ns(_delay, dws);
        if (delay < 0)
                return delay;

        _spi_transfer_delay_ns(delay);

        return 0;
}

int poll_transfer(struct dw_spi *dws)
{
    struct spi_delay delay;
    uint16_t nbits;
    delay.unit = SPI_DELAY_UNIT_SCK;
    nbits = dws->n_bytes * BITS_PER_BYTE;
    int ret = 0;

    do
    {
        dw_writer(dws);
        cpu_relax();

        delay.value = nbits * (dws->rx_len - dws->tx_len);
        spi_delay_exec(&delay, dws);
        dw_reader(dws);
        cpu_relax();
        ret = dw_spi_check_status(dws, true);
        if (ret)
            return ret;
    } while (dws->rx_len && dws->tx_len);

    return 0;
}

void set_tran_mode(struct dw_spi *dws)
{
    uint32_t reg = dw_readl(dws, CVI_DW_SPI_CTRLR0);
    uint8_t tmode;

    if (dws->rx && dws->tx) {
        tmode = CVI_SPI_TMOD_TR;
    } else if (dws->rx) {
        tmode = CVI_SPI_TMOD_RO;
    } else {
        tmode = CVI_SPI_TMOD_TO;
    }
    reg &= ~CVI_SPI_TMOD_MASK;
    reg |= (tmode << CVI_SPI_TMOD_OFFSET);

    dw_writel(dws, CVI_DW_SPI_CTRLR0, reg);
}

void dw_spi_set_controller_mode(struct dw_spi *dws, uint8_t enable_master)
{
    /* do not support to switch controller mode, it is default master mode */
}

void dw_spi_set_cs(struct dw_spi *dws, bool enable, uint32_t index)
{
    uint32_t reg = dw_readl(dws, CVI_DW_SPI_SER);

    if (enable)
        dw_writel(dws, CVI_DW_SPI_SER, reg | BIT(index));
    else
        dw_writel(dws, CVI_DW_SPI_SER, reg & ~BIT(index));
}

void dw_spi_set_polarity_and_phase(struct dw_spi *dws, uint8_t format)
{
    uint32_t reg = dw_readl(dws, CVI_DW_SPI_CTRLR0);
    reg &= ~(0x3 << 6);

    switch (format) {
        case SPI_FORMAT_CPOL0_CPHA0:
            reg |= (SPI_MODE_0 << 6);
            break;

        case SPI_FORMAT_CPOL0_CPHA1:
            reg |= (SPI_MODE_1 << 6);
            break;

        case SPI_FORMAT_CPOL1_CPHA0:
            reg |= (SPI_MODE_2 << 6);
            break;

        case SPI_FORMAT_CPOL1_CPHA1:
            reg |= (SPI_MODE_3 << 6);
            break;

        default:
            reg = dw_readl(dws, CVI_DW_SPI_CTRLR0);
            break;
    }
    SP_DEBUG_LOG("set phase and polarity: %#x\n", reg);
    dw_writel(dws, CVI_DW_SPI_CTRLR0, reg);
}

uint32_t dw_spi_set_clock(struct dw_spi *dws, uint32_t clock_in, uint32_t clock_out)
{
    uint16_t div;

    div = (DIV_ROUND_UP(clock_in, clock_out) + 1) & 0xfffe;
    dws->speed_hz = clock_in / div;
    SP_DEBUG_LOG("clk div value is: %u, hz:%u\n", div, dws->speed_hz);
    spi_set_clk(dws, div);
    return dws->speed_hz;
}

int dw_spi_set_data_frame_len(struct dw_spi *dws, uint32_t size)
{
    uint32_t temp = dw_readl(dws, CVI_DW_SPI_CTRLR0);
    temp &= ~0xf;

    if (size == 8) {
        dws->n_bytes = 1;
    } else if (size == 16) {
        dws->n_bytes = 2;
    } else {
        SP_DEBUG_LOG("do not support %u bit data!\n", size);
        return -1;
    }
    temp |= (size - 1);
    dw_writel(dws, CVI_DW_SPI_CTRLR0, temp);
    SP_DEBUG_LOG("set data frame len: %#x\n", temp);
    return 0;
}

void dw_spi_show_regs(struct dw_spi *dws)
{
    SP_DEBUG_LOG("CTRLR0: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_CTRLR0));
    SP_DEBUG_LOG("CTRLR1: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_CTRLR1));
    SP_DEBUG_LOG("SSIENR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_SSIENR));
    SP_DEBUG_LOG("SER: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_SER));
    SP_DEBUG_LOG("BAUDR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_BAUDR));
    SP_DEBUG_LOG("TXFTLR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_TXFTLR));
    SP_DEBUG_LOG("RXFTLR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_RXFTLR));
    SP_DEBUG_LOG("TXFLR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_TXFLR));
    SP_DEBUG_LOG("RXFLR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_RXFLR));
    SP_DEBUG_LOG("SR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_SR));
    SP_DEBUG_LOG("IMR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_IMR));
    SP_DEBUG_LOG("ISR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_ISR));
    SP_DEBUG_LOG("DMACR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_DMACR));
    SP_DEBUG_LOG("DMATDLR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_DMATDLR));
    SP_DEBUG_LOG("DMARDLR: \t0x%08x\n", dw_readl(dws, CVI_DW_SPI_DMARDLR));
}
