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

#include <rtthread.h>
#include <rtdevice.h>

#include "drv_qspi.h"
#include <drivers/dev_spi.h>
#include <string.h>
#include "drv_gpio.h"
#include "riscv_io.h"
#include "board.h"
#include "ioremap.h"
#include "sysctl_rst.h"
#include "sysctl_clk.h"
#include "cache.h"

#define DBG_TAG "qspi"
#include <rtdbg.h>

/**
 * @brief    QSPI bus structure for K230 platform.
 *
 * @note     This structure contains all the necessary information for the QSPI bus driver.
 *           It includes the SPI bus structure, base address, index, configuration parameters,
 *           and buffers for data transfer.
 */
typedef struct
{
    struct rt_spi_bus dev;
    void *base;
    rt_uint8_t idx;
    rt_uint8_t rdse;
    rt_uint8_t rdsd;
    rt_uint8_t max_line;
    rt_uint32_t max_hz;
    struct rt_event event;
    void *send_buf;
    void *recv_buf;
    rt_size_t send_length;
    rt_size_t recv_length;
    rt_uint8_t cell_size;
} k230_qspi_bus_t;

static rt_err_t k230_qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    k230_qspi_bus_t *qspi_bus = (k230_qspi_bus_t *)device->bus;
    k230_qspi_reg_t *qspi_reg = (k230_qspi_reg_t *)qspi_bus->base;
    struct rt_qspi_device *dev = (struct rt_qspi_device *)device;
    struct rt_qspi_configuration *qspi_cfg = &dev->config;
    rt_uint8_t dfs, mode;
    rt_uint32_t max_hz, qspi_clk;

    if (qspi_cfg->qspi_dl_width > qspi_bus->max_line || qspi_cfg->qspi_dl_width == 0)
    {
        return RT_EINVAL;
    }
    if (qspi_cfg->parent.data_width < 4 || qspi_cfg->parent.data_width > 32)
    {
        return RT_EINVAL;
    }

    /* Check if the clock frequency exceeds the hardware limits */
    max_hz = qspi_cfg->parent.max_hz;
    if (max_hz > qspi_bus->max_hz)
    {
        max_hz = qspi_bus->max_hz;
    }

    if (qspi_bus->idx == 0)
    {
        qspi_clk = sysctl_clk_get_leaf_freq(SYSCTL_CLK_SSI0);
    }
    else if (qspi_bus->idx == 1)
    {
        qspi_clk = sysctl_clk_get_leaf_freq(SYSCTL_CLK_SSI1);
    }
    else if (qspi_bus->idx == 2)
    {
        qspi_clk = sysctl_clk_get_leaf_freq(SYSCTL_CLK_SSI2);
    }
    else
    {
        return RT_EINVAL;
    }

    mode = qspi_cfg->parent.mode & RT_SPI_MODE_3;
    dfs = qspi_cfg->parent.data_width - 1;

    qspi_reg->ssienr = 0;
    qspi_reg->ser = 0;
    qspi_reg->baudr = qspi_clk / max_hz;
    qspi_reg->rx_sample_delay = qspi_bus->rdse << 16 | qspi_bus->rdsd;
    qspi_reg->axiawlen = SSIC_AXI_BLW << 8;
    qspi_reg->axiarlen = SSIC_AXI_BLW << 8;
    qspi_reg->ctrlr0 = (dfs) | (mode << 8);

    rt_memcpy(&dev->config, qspi_cfg, sizeof(struct rt_qspi_configuration));

    return RT_EOK;
}

static rt_ssize_t k230_qspi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    k230_qspi_bus_t *qspi_bus = (k230_qspi_bus_t *)device->bus;
    k230_qspi_reg_t *qspi_reg = (k230_qspi_reg_t *)qspi_bus->base;
    struct rt_qspi_device *dev = (struct rt_qspi_device *)device;
    struct rt_qspi_message *msg = (struct rt_qspi_message *)message;
    struct rt_qspi_configuration *qspi_cfg = (struct rt_qspi_configuration *)&dev->config;
    /* Multi-line SPI transfers (2, 4, or 8 lines) DSPI QSPI OSPI  */
    if (msg->qspi_data_lines > 1)
    {
        rt_uint8_t spi_ff;
        if (msg->qspi_data_lines > qspi_cfg->qspi_dl_width)
        {
            LOG_E("data line is invalid");
            return 0;
        }
        /* Check QSPI mode */
        if (msg->qspi_data_lines == 2)
        {
            spi_ff = SPI_FRF_DUAL_SPI;
        }
        else if (msg->qspi_data_lines == 4)
        {
            spi_ff = SPI_FRF_QUAD_SPI;
        }
        else if (msg->qspi_data_lines == 8)
        {
            spi_ff = SPI_FRF_OCT_SPI;
        }
        else
        {
            LOG_E("data line is invalid");
            return 0;
        }
        if (qspi_cfg->parent.data_width & (msg->qspi_data_lines - 1))
        {
            LOG_E("data line and data width do not match");
            return 0;
        }
        if (msg->instruction.qspi_lines != 1 && msg->instruction.qspi_lines != msg->qspi_data_lines)
        {
            LOG_E("instruction line is invalid");
            return 0;
        }
        if (msg->address.size & 3 || msg->address.size > 32)
        {
            LOG_E("address size is invalid");
            return 0;
        }
        if (msg->address.size && msg->address.qspi_lines != 1 && msg->address.qspi_lines != msg->qspi_data_lines)
        {
            LOG_E("address line is invalid");
            return 0;
        }
        if (msg->parent.length > 0x10000)
        {
            LOG_E("data length is invalid, more than 0x10000");
            return 0;
        }
        rt_uint8_t trans_type = 0;
        if (msg->instruction.qspi_lines != 1)
        {
            trans_type = 2;
        }
        if (msg->address.size)
        {
            if (msg->address.qspi_lines != 1)
            {
                trans_type = trans_type ? trans_type : 1;

            }
            else if (trans_type != 0)
            {
                LOG_E("instruction or address line is invalid");
                return 0;
            }
        }
        if (msg->dummy_cycles > 31)
        {
            LOG_E("dummy cycle is invalid");
            return 0;
        }
        rt_uint8_t tmod = msg->parent.recv_buf ? SPI_TMOD_RO : SPI_TMOD_TO;
        rt_size_t length = msg->parent.length;
        rt_size_t txfthr = length > (SSIC_TX_ABW / 2) ? (SSIC_TX_ABW / 2) : length - 1;
        rt_uint8_t cell_size = (qspi_cfg->parent.data_width + 7) >> 3;
        rt_uint8_t *buf = RT_NULL;
        if (length)
        {
            buf = rt_malloc_align(CACHE_ALIGN_TOP(length * cell_size), L1_CACHE_BYTES);
            if (buf == RT_NULL)
            {
                LOG_E("alloc mem error");
                return 0;
            }
        }
        qspi_reg->spi_ctrlr0 = trans_type | (msg->address.size >> 2 << 2) | 512 | (msg->dummy_cycles << 11);
        qspi_reg->ctrlr0 &= ~((3 << 22) | (3 << 10));
        if (length)
        {
            qspi_reg->ctrlr0 |= (spi_ff << 22) | (tmod << 10);
            qspi_reg->txftlr = (txfthr << 16) | (SSIC_TX_ABW / 2);
            qspi_reg->rxftlr = (SSIC_RX_ABW - 1);
            qspi_reg->imr = (1 << 11) | (1 << 8);
            qspi_reg->dmacr = (1 << 6) | (3 << 3) | (1 << 2);
            qspi_reg->ctrlr1 = length - 1;
            qspi_reg->spidr = msg->instruction.content;
            qspi_reg->spiar = msg->address.content;
            if (tmod == 1)
            {
                rt_memcpy(buf, msg->parent.send_buf, length * cell_size);
                rt_hw_cpu_dcache_clean(buf, CACHE_ALIGN_TOP(length * cell_size));
            }
            qspi_reg->axiar0 = (rt_uint32_t)((uint64_t)buf);
            qspi_reg->axiar1 = (rt_uint32_t)((uint64_t)buf >> 32);
        }
        else
        {
            tmod = SPI_TMOD_TO;
            qspi_reg->ctrlr0 |= (spi_ff << 22) | (tmod << 10);
            qspi_reg->txftlr = ((SSIC_TX_ABW - 1) << 16) | (SSIC_TX_ABW - 1);
            qspi_reg->rxftlr = (SSIC_RX_ABW - 1);
            qspi_reg->imr = 0;
            qspi_reg->dmacr = 0;
        }
        rt_event_control(&qspi_bus->event, RT_IPC_CMD_RESET, 0);

        qspi_reg->ser = 1 ;
        qspi_reg->ssienr = 1;
        rt_uint32_t event;
        rt_err_t err;
        if (length)
        {
            err = rt_event_recv(&qspi_bus->event, BIT(SSI_DONE) | BIT(SSI_AXIE),
                                RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 1000, &event);
        }
        else
        {
            err = RT_EOK;
            event = 0;
            qspi_reg->dr[0] = msg->instruction.content;
            length++;
            if (msg->address.size)
            {
                qspi_reg->dr[0] = msg->address.content;
                length++;
            }
            qspi_reg->txftlr = 0;
            while ((qspi_reg->sr & 0x5) != 0x4);
        }
        qspi_reg->ser = 0;
        qspi_reg->ssienr = 0;
        if (err == -RT_ETIMEOUT)
        {
            LOG_E("qspi%d transfer data timeout", qspi_bus->idx);
            if (buf)
            {
                rt_free_align(buf);
            }
            return 0;
        }
        if (event & BIT(SSI_AXIE))
        {
            LOG_E("qspi%d dma error", qspi_bus->idx);
            if (buf)
            {
                rt_free_align(buf);
            }
            return 0;
        }
        if (tmod == SPI_TMOD_RO)
        {
            rt_hw_cpu_dcache_invalidate(buf, CACHE_ALIGN_TOP(length * cell_size));
            rt_memcpy(msg->parent.recv_buf, buf, length * cell_size);
        }
        if (buf)
        {
            rt_free_align(buf);
        }
        return length;
    }
    /* Standard SPI transfers */
    else
    {
        if (msg->parent.length == 0)
        {
            return 0;
        }
        rt_uint8_t cell_size = (qspi_cfg->parent.data_width + 7) >> 3;
        rt_size_t length = msg->parent.length;
        rt_size_t count = length > 0x10000 ? 0x10000 : length;
        rt_size_t send_single = 0, send_length = 0, recv_single = 0, recv_length = 0;
        void *send_buf = msg->parent.send_buf;
        void *recv_buf = msg->parent.recv_buf;
        rt_uint8_t tmod = send_buf ? SPI_TMOD_TO : SPI_TMOD_EPROMREAD;
        tmod = recv_buf ? tmod & SPI_TMOD_RO : tmod;
        if (tmod == SPI_TMOD_EPROMREAD)
        {
            LOG_E("send_buf and recv_buf cannot both be empty");
            return 0 ;
        }
        if (tmod == SPI_TMOD_RO && qspi_cfg->parent.data_width == 8)
        {
            if ((msg->address.size & 7) || (msg->dummy_cycles & 7))
            {
                LOG_E("instruction, address, dummy_cycles invalid");
                LOG_E("For read-only mode the instruction, address, dummy_cycles must be set to zero");
                LOG_E("For eeprom-read mode the instruction, address, dummy_cycles must be set to multiples of 8");
                return 0;
            }
            else if (msg->address.size)
            {
                if (length > 0x10000)
                {
                    LOG_E("For eeprom-read mode, data length cannot exceed 0x10000");
                    return 0 ;
                }
                tmod = SPI_TMOD_EPROMREAD;
            }
        }
        if (send_buf)
        {
            send_single = count;
            send_buf = rt_malloc(count * cell_size);
            if (send_buf == RT_NULL)
            {
                LOG_E("alloc mem error");
                return 0;
            }
            rt_memcpy(send_buf, msg->parent.send_buf, count * cell_size);
        }
        else if (tmod == SPI_TMOD_EPROMREAD)
        {
            send_single = 1 + msg->address.size / 8 + msg->dummy_cycles / 8;
            send_buf = rt_malloc(send_single);
            if (send_buf == RT_NULL)
            {
                LOG_E("alloc mem error");
                return 0 ;
            }
            rt_uint8_t *temp = send_buf;
            *temp++ = msg->instruction.content;
            for (int i = msg->address.size / 8; i; i--)
            {
                *temp++ = msg->address.content >> ((i - 1) * 8);
            }
            for (int i = msg->dummy_cycles / 8; i; i--)
            {
                *temp++ = 0xFF;
            }
        }
        if (recv_buf)
        {
            recv_single = count;
            recv_buf = rt_malloc(count * cell_size);
            if (recv_buf == RT_NULL)
            {
                LOG_E("alloc mem error");
                if (send_buf)
                {
                    rt_free(send_buf);
                }
                return 0;
            }
        }
        send_length = 0;
        recv_length = 0;
        qspi_bus->cell_size = cell_size;
        qspi_bus->send_buf = send_buf;
        qspi_bus->recv_buf = recv_buf;
        qspi_bus->send_length = send_single;
        qspi_bus->recv_length = recv_single;
        qspi_reg->ctrlr0 &= ~((3 << 22) | (3 << 10));
        qspi_reg->ctrlr0 |= (tmod << 10);
        qspi_reg->ctrlr1 = count - 1;
        qspi_reg->txftlr = ((SSIC_TX_ABW / 2) << 16) | (SSIC_TX_ABW / 2);
        qspi_reg->rxftlr = count >= (SSIC_RX_ABW / 2) ? (SSIC_RX_ABW / 2 - 1) : count - 1;
        qspi_reg->dmacr = 0;
        qspi_reg->imr = (1 << 4) | (1 << 0);
        rt_event_control(&qspi_bus->event, RT_IPC_CMD_RESET, 0);
        qspi_reg->ser = 1;
        qspi_reg->ssienr = 1;
        if (tmod == SPI_TMOD_RO)
            qspi_reg->dr[0] = 0;
        rt_uint32_t event;
        rt_uint32_t cnt = 0;
        rt_err_t err;
        while (RT_TRUE)
        {
            /* Avoid endless loop */
#ifdef RT_USING_QSPI_XFER_LIMIT
            cnt++;
            if (cnt > RT_QSPI_MAX_XFER_SIZE)
            {
                return 0;
            }
#endif
            /* Waiting for transfer events */
            err = rt_event_recv(&qspi_bus->event, BIT(SSI_TXE) | BIT(SSI_RXF),
                                RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 10000, &event);
            if (err == -RT_ETIMEOUT)
            {
                LOG_E("qspi%d transfer data timeout", qspi_bus->idx);
                length = 0;
                if (send_buf)
                {
                    rt_free(send_buf);
                }
                if (recv_buf)
                {
                    rt_free(recv_buf);
                }
                return 0;
            }
            /* Handle Transmit buffer empty */
            if (event & BIT(SSI_TXE))
            {
                send_length += send_single;
                if (send_length < length && tmod <= SPI_TMOD_TO)
                {
                    count = length - send_length;
                    count = count > 0x10000 ? 0x10000 : count;
                    rt_memcpy(send_buf, msg->parent.send_buf + send_length * cell_size, count * cell_size);
                    qspi_bus->send_buf = send_buf;
                    qspi_bus->send_length = count;
                    send_single = count;
                    qspi_reg->txftlr = ((SSIC_TX_ABW / 2) << 16) | (SSIC_TX_ABW / 2);
                    if (tmod == SPI_TMOD_TO)
                        qspi_reg->imr |= (1 << 0);
                }
                else if (tmod == SPI_TMOD_TO)
                {
                    while ((qspi_reg->sr & 0x5) != 0x4);
                    break;
                }
            }
            /* Handle receive buffer full */
            if (event & BIT(SSI_RXF))
            {
                rt_memcpy(msg->parent.recv_buf + recv_length * cell_size, recv_buf, recv_single * cell_size);
                recv_length += recv_single;
                if (recv_length >= length)
                {
                    break;
                }
                count = length - recv_length;
                count = count > 0x10000 ? 0x10000 : count;
                qspi_bus->recv_buf = recv_buf;
                qspi_bus->recv_length = count;
                recv_single = count;
                qspi_reg->rxftlr = count >= (SSIC_RX_ABW / 2) ? (SSIC_RX_ABW / 2 - 1) : count - 1;
                if (tmod == SPI_TMOD_TR)
                {
                    qspi_reg->imr |= (1 << 0) | (1 << 4);
                }
                else if (tmod == SPI_TMOD_RO)
                {
                    qspi_reg->imr |= (1 << 4);
                    qspi_reg->ssienr = 0;
                    qspi_reg->ctrlr1 = count - 1;
                    qspi_reg->ssienr = 1;
                    qspi_reg->dr[0] = 0;
                    qspi_reg->dr[0] = 0;
                }
            }
        }
        qspi_reg->ser = 0;
        qspi_reg->ssienr = 0;
        if (send_buf)
        {
            rt_free(send_buf);
        }
        if (recv_buf)
        {
            rt_free(recv_buf);
        }
        return length;
    }
    return 0;
}

static const struct rt_spi_ops k230_qspi_ops =
{
    .configure = k230_qspi_configure,
    .xfer = k230_qspi_xfer,
};

static void k230_qspi_irq(int vector, void *param)
{
    k230_qspi_bus_t *qspi_bus = param;
    k230_qspi_reg_t *qspi_reg = (k230_qspi_reg_t *)qspi_bus->base;
    vector -= IRQN_OSPI0;
    vector %= (IRQN_QSPI0 - IRQN_OSPI0);

    /* Handle transmit buffer empty interrupt */
    if (vector == SSI_TXE)
    {
        if (qspi_bus->send_buf == RT_NULL)
        {
            qspi_reg->imr &= ~1;
        }
        else if (qspi_bus->cell_size == 1)
        {
            while ((qspi_bus->send_length) && (qspi_reg->sr & 2))
            {
                qspi_reg->dr[0] = *((rt_uint8_t *)qspi_bus->send_buf);
                qspi_bus->send_buf++;
                qspi_bus->send_length--;
            }
        }
        else if (qspi_bus->cell_size == 2)
        {
            while ((qspi_bus->send_length) && (qspi_reg->sr & 2))
            {
                qspi_reg->dr[0] = *((rt_uint16_t *)qspi_bus->send_buf);
                qspi_bus->send_buf += 2;
                qspi_bus->send_length--;
            }
        }
        else if (qspi_bus->cell_size == 4)
        {
            while ((qspi_bus->send_length) && (qspi_reg->sr & 2))
            {
                qspi_reg->dr[0] = *((rt_uint32_t *)qspi_bus->send_buf);
                qspi_bus->send_buf += 4;
                qspi_bus->send_length--;
            }
        }
        else
        {
            LOG_E("qspi%d datawidth error", qspi_bus->idx);
        }
        if (qspi_bus->send_length == 0)
        {
            if ((qspi_reg->ctrlr0 >> 10) & SPI_TMOD_EPROMREAD == SPI_TMOD_TO)
            {
                if (qspi_reg->txftlr)
                    return;
            }
            qspi_reg->txftlr = 0;
            qspi_reg->imr &= ~1;
            rt_event_send(&qspi_bus->event, BIT(SSI_TXE));
        }
    }
    /* Handle receive buffer full interrupt */
    else if (vector == SSI_RXF)
    {
        if (qspi_bus->recv_buf == RT_NULL)
        {
            qspi_reg->imr &= ~0x10;
        }
        else if (qspi_bus->cell_size == 1)
        {
            while ((qspi_bus->recv_length) && (qspi_reg->sr & 8))
            {
                *((rt_uint8_t *)qspi_bus->recv_buf) = qspi_reg->dr[0];
                qspi_bus->recv_buf++;
                qspi_bus->recv_length--;
            }
        }
        else if (qspi_bus->cell_size == 2)
        {
            while ((qspi_bus->recv_length) && (qspi_reg->sr & 8))
            {
                *((rt_uint16_t *)qspi_bus->recv_buf) = qspi_reg->dr[0];
                qspi_bus->recv_buf += 2;
                qspi_bus->recv_length--;
            }
        }
        else if (qspi_bus->cell_size == 4)
        {
            while ((qspi_bus->recv_length) && (qspi_reg->sr & 8))
            {
                *((rt_uint32_t *)qspi_bus->recv_buf) = qspi_reg->dr[0];
                qspi_bus->recv_buf += 4;
                qspi_bus->recv_length--;
            }
        }
        else
        {
            LOG_E("qspi%d datawidth error", qspi_bus->idx);
        }
        if (qspi_bus->recv_length == 0)
        {
            qspi_reg->imr &= ~0x10;
            rt_event_send(&qspi_bus->event, BIT(SSI_RXF));
        }
        else if (qspi_bus->recv_length <= qspi_reg->rxftlr)
        {
            qspi_reg->rxftlr = qspi_bus->recv_length - 1;
        }
    }
    /* Handle transfer complete interrupt */
    else if (vector == SSI_DONE)
    {
        qspi_reg->donecr;
        rt_event_send(&qspi_bus->event, BIT(SSI_DONE));
    }
    /* Handle DMA error interrupt */
    else if (vector == SSI_AXIE)
    {
        qspi_reg->axiecr;
        rt_event_send(&qspi_bus->event, BIT(SSI_AXIE));
    }
}



int rt_hw_qspi_bus_init(void)
{
    rt_err_t ret;
    
    /* Initialize OSPI bus */
#ifdef RT_USING_OSPI
    static k230_qspi_bus_t ospi_bus0;
    ospi_bus0.base = rt_ioremap((void *)SPI_OPI_BASE_ADDR, SPI_OPI_IO_SIZE);
    ospi_bus0.idx = 0;
    ospi_bus0.rdse = 0;
    ospi_bus0.rdsd = 0;
    ospi_bus0.max_line = 8;
    ospi_bus0.max_hz = 200000000;

    ret = rt_qspi_bus_register(&ospi_bus0.dev, "ospi", &k230_qspi_ops);
    if (ret)
    {
        LOG_E("ospi register fail");
        return ret;
    }
    rt_event_init(&ospi_bus0.event, "ospi_event", RT_IPC_FLAG_PRIO);
    rt_hw_interrupt_install(IRQN_OSPI0 + SSI_TXE, k230_qspi_irq, &ospi_bus0, "ospi");
    rt_hw_interrupt_umask(IRQN_OSPI0 + SSI_TXE);
    rt_hw_interrupt_install(IRQN_OSPI0 + SSI_RXF, k230_qspi_irq, &ospi_bus0, "ospi");
    rt_hw_interrupt_umask(IRQN_OSPI0 + SSI_RXF);
    rt_hw_interrupt_install(IRQN_OSPI0 + SSI_DONE, k230_qspi_irq, &ospi_bus0, "ospi");
    rt_hw_interrupt_umask(IRQN_OSPI0 + SSI_DONE);
    rt_hw_interrupt_install(IRQN_OSPI0 + SSI_AXIE, k230_qspi_irq, &ospi_bus0, "ospi");
    rt_hw_interrupt_umask(IRQN_OSPI0 + SSI_AXIE);
#endif

    /* Initialize QSPI0 bus */
#ifdef RT_USING_QSPI0
    static k230_qspi_bus_t qspi_bus0;
    qspi_bus0.base = rt_ioremap((void *)SPI_QOPI_BASE_ADDR, SPI_OPI_IO_SIZE);
    qspi_bus0.idx = 1;
    qspi_bus0.rdse = 0;
    qspi_bus0.rdsd = 0;
    qspi_bus0.max_line = 4;
    qspi_bus0.max_hz = 100000000;

    ret = rt_qspi_bus_register(&qspi_bus0.dev, "qspi0", &k230_qspi_ops);
    if (ret)
    {
        LOG_E("qspi0 register fail");
        return ret;
    }
    rt_event_init(&qspi_bus0.event, "qspi0_event", RT_IPC_FLAG_PRIO);
    rt_hw_interrupt_install(IRQN_QSPI0 + SSI_TXE, k230_qspi_irq, &qspi_bus0, "qspi0");
    rt_hw_interrupt_umask(IRQN_QSPI0 + SSI_TXE);
    rt_hw_interrupt_install(IRQN_QSPI0 + SSI_RXF, k230_qspi_irq, &qspi_bus0, "qspi0");
    rt_hw_interrupt_umask(IRQN_QSPI0 + SSI_RXF);
    rt_hw_interrupt_install(IRQN_QSPI0 + SSI_DONE, k230_qspi_irq, &qspi_bus0, "qspi0");
    rt_hw_interrupt_umask(IRQN_QSPI0 + SSI_DONE);
    rt_hw_interrupt_install(IRQN_QSPI0 + SSI_AXIE, k230_qspi_irq, &qspi_bus0, "qspi0");
    rt_hw_interrupt_umask(IRQN_QSPI0 + SSI_AXIE);
#endif

    /* Initialize QSPI1 bus */
#ifdef RT_USING_QSPI1
    static k230_qspi_bus_t qspi_bus1;
    qspi_bus1.base = rt_ioremap((void *)SPI_QOPI_BASE_ADDR + SPI_OPI_IO_SIZE, SPI_OPI_IO_SIZE);
    qspi_bus1.idx = 2;
    qspi_bus1.rdse = 0;
    qspi_bus1.rdsd = 0;
    qspi_bus1.max_line = 4;
    qspi_bus1.max_hz = 100000000;

    ret = rt_qspi_bus_register(&qspi_bus1.dev, "qspi1", &k230_qspi_ops);
    if (ret)
    {
        LOG_E("qspi1 register fail");
        return ret;
    }
    rt_event_init(&qspi_bus1.event, "qspi1_event", RT_IPC_FLAG_PRIO);
    rt_hw_interrupt_install(IRQN_QSPI1 + SSI_TXE, k230_qspi_irq, &qspi_bus1, "qspi1");
    rt_hw_interrupt_umask(IRQN_QSPI1 + SSI_TXE);
    rt_hw_interrupt_install(IRQN_QSPI1 + SSI_RXF, k230_qspi_irq, &qspi_bus1, "qspi1");
    rt_hw_interrupt_umask(IRQN_QSPI1 + SSI_RXF);
    rt_hw_interrupt_install(IRQN_QSPI1 + SSI_DONE, k230_qspi_irq, &qspi_bus1, "qspi1");
    rt_hw_interrupt_umask(IRQN_QSPI1 + SSI_DONE);
    rt_hw_interrupt_install(IRQN_QSPI1 + SSI_AXIE, k230_qspi_irq, &qspi_bus1, "qspi1");
    rt_hw_interrupt_umask(IRQN_QSPI1 + SSI_AXIE);
#endif
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_qspi_bus_init);