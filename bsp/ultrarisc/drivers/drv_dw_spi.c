/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * spi driver for synopsys dw apb spi
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-03     ZhangJing   first version
 */
#include <rtconfig.h>

#ifdef BSP_USING_DW_SPI
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_dw_spi.h"
#include <rtdbg.h>
#include <io.h>
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif
#define SPI0_BUS_NAME      "spi0"
#define SPI0_BUS_DEVICE0_NAME      "spi00"

static struct dw_spi dw_spi_device =
{
    .device_name = "spi0",
    .irq = DW_SPI_IRQ_BASE,
    .max_freq = DW_SPI_MAX_FREQ,
    .bits_per_word = 8,
    .cs = 0,
    .fifo_len = 0,
    .type = DW_SPI_CTRLR0_FRF_MOT,
};

static rt_uint32_t update_control_reg_16(struct dw_spi *dw_spi_dev)
{
    return ((dw_spi_dev->bits_per_word - 1) << CTRLR0_DFS_SHIFT) |
           (dw_spi_dev->type << DW_SPI_CTRLR0_FRF_SHIFT) |
           (dw_spi_dev->mode << DW_SPI_CTRLR0_MODE_SHIFT) |
           (dw_spi_dev->tmode << DW_SPI_CTRLR0_TMOD_SHIFT);
}

static rt_uint32_t update_control_reg_32(struct dw_spi *dw_spi_dev)
{
    return ((dw_spi_dev->bits_per_word - 1) << CTRLR0_DFS_32_SHIFT) |
           (dw_spi_dev->type << DW_SPI_CTRLR0_FRF_SHIFT) |
           (dw_spi_dev->mode << DW_SPI_CTRLR0_MODE_SHIFT) |
           (dw_spi_dev->tmode << DW_SPI_CTRLR0_TMOD_SHIFT);
}

static rt_err_t _dw_drv_spi_configure(struct rt_spi_device *device,
                                      struct rt_spi_configuration *config)
{
    struct dw_spi *dw_spi_dev = (struct dw_spi *)(device->bus->parent.user_data);
    if (!dw_spi_dev)
    {
        LOG_E("SPI device is null");
        return -RT_ERROR;
    }

    struct dw_spi_regs *regs = dw_spi_dev->reg;
    writel(0, &regs->ssienr);
    writel(0, &regs->ser);
    writel(0, &regs->imr);
    writel(0, &regs->dmacr);

    rt_uint32_t ctrl = 0;
    switch (config->mode & (RT_SPI_CPHA | RT_SPI_CPOL))
    {
    case RT_SPI_MODE_0:
        ctrl |= 0;
        break;
    case RT_SPI_MODE_1:
        ctrl |= DW_SPI_CTRLR0_SCPH;
        break;
    case RT_SPI_MODE_2:
        ctrl |= DW_SPI_CTRLR0_SCPOL;
        break;
    case RT_SPI_MODE_3:
        ctrl |= DW_SPI_CTRLR0_SCPH | DW_SPI_CTRLR0_SCPOL;
        break;
    }

    dw_spi_dev->mode = ctrl;


    /* div = dw_spi_dev->max_freq / configuration->max_hz;*/
    rt_uint32_t div = 0;
    div = dw_spi_dev->max_freq / 15625000;
    if (div % 2)
        div++;
    /* TODO: */
    /* write clock divider register */
    writel(div, &regs->baudr);

    /* write TX threshold register */
    writel(0, &regs->txflr);
    /* write RX threshold register */
    writel(0, &regs->rxflr);
    /* enable spi */
    writel(1, &regs->ssienr);

    return RT_EOK;
}

static rt_uint32_t min3(rt_uint32_t a, rt_uint32_t b, rt_uint32_t c)
{
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}


static inline rt_uint32_t tx_max(struct dw_spi *dw_spi_dev)
{
    rt_uint32_t tx_left, tx_room, rxtx_gap;
    struct dw_spi_regs *regs = dw_spi_dev->reg;

    tx_left = dw_spi_dev->tx_len;
    tx_room = dw_spi_dev->fifo_len - (rt_uint32_t)(readl(&regs->txflr));

    /*
     * Another concern is about the tx/rx mismatch, we
     * thought about using (priv->fifo_len - rxflr - txflr) as
     * one maximum value for tx, but it doesn't cover the
     * data which is out of tx/rx fifo and inside the
     * shift registers. So a control from sw point of
     * view is taken.
     */
    if (dw_spi_dev->rx != NULL && dw_spi_dev->tx != NULL)
    {
        rxtx_gap = dw_spi_dev->fifo_len - (dw_spi_dev->rx_len - dw_spi_dev->tx_len);
        return min3(tx_left, tx_room, (rt_uint32_t)(rxtx_gap));

    }
    else
    {
        return tx_left < tx_room ? tx_left : tx_room;
    }
}

static inline rt_uint32_t rx_max(struct dw_spi *dw_spi_dev)
{
    rt_uint32_t rx_left = dw_spi_dev->rx_len;
    struct dw_spi_regs *regs = dw_spi_dev->reg;

    rt_uint32_t val = readl(&regs->rxflr);
    return (rx_left < val) ? rx_left : val;
}

/* write data to spi */
static void dw_spi_writer(struct dw_spi *dw_spi_dev)
{
    rt_uint32_t max = tx_max(dw_spi_dev);
    rt_uint32_t txw = 0xFF;
    struct dw_spi_regs *regs = dw_spi_dev->reg;

    while (max--)
    {
        /* Set the tx word if the transfer's original "tx" is not null */
        if (dw_spi_dev->tx)
        {
            if (dw_spi_dev->bits_per_word == 8)
                txw = *(rt_uint8_t *)(dw_spi_dev->tx);
            else
                txw = *(rt_uint16_t *)(dw_spi_dev->tx);

            dw_spi_dev->tx += dw_spi_dev->bits_per_word >> 3;
        }
        writel(txw, &regs->dr);
        dw_spi_dev->tx_len--;
    }
}

/* read data from spi */
static void dw_spi_reader(struct dw_spi *dw_spi_dev)
{
    struct dw_spi_regs *regs = dw_spi_dev->reg;
    rt_uint32_t max = rx_max(dw_spi_dev);
    rt_uint16_t rxw;

    while (max--)
    {
        rxw = readl(&regs->dr);
        if (dw_spi_dev->rx)
        {
            if (dw_spi_dev->bits_per_word == 8)
                *(rt_uint8_t *)(dw_spi_dev->rx) = rxw;
            else
                *(rt_uint16_t *)(dw_spi_dev->rx) = rxw;

            dw_spi_dev->rx += dw_spi_dev->bits_per_word >> 3;

        }
        dw_spi_dev->rx_len--;
    }
}

static void wait_for_idle(struct dw_spi *dw_spi_dev)
{
    rt_uint32_t status;
    struct dw_spi_regs *regs = dw_spi_dev->reg;

    while (1)
    {
        status = readl(&regs->sr);
        if (!(status & DW_SPI_SR_BUSY))
        {
            if (status & DW_SPI_SR_TX_EMPTY)
            {
                break;
            }
        }
        rt_thread_yield();
    }
}

static int dw_spi_poll_transfer(struct dw_spi *dw_spi_dev)
{
    do
    {
        dw_spi_writer(dw_spi_dev);
        wait_for_idle(dw_spi_dev);
        dw_spi_reader(dw_spi_dev);
    }
    while (dw_spi_dev->rx_len && dw_spi_dev->tx_len);

    return 0;
}

static rt_ssize_t _dw_spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct dw_spi *dw_spi_dev = (struct dw_spi *)(device->bus->parent.user_data);
    if (!dw_spi_dev)
    {
        LOG_E("SPI device is null");
        return -RT_ERROR;
    }

    dw_spi_dev->tx = (void *)message->send_buf;
    dw_spi_dev->tx_end = dw_spi_dev->tx + dw_spi_dev->tx_len;

    dw_spi_dev->rx = (void *)message->recv_buf;
    dw_spi_dev->rx_end = dw_spi_dev->rx + dw_spi_dev->rx_len;

    dw_spi_dev->tx_len = message->length;
    dw_spi_dev->rx_len = message->length;

    if (dw_spi_dev->tx && dw_spi_dev->rx)
    {
        /* set mode to Tx & Rx */
        dw_spi_dev->tmode = DW_SPI_CTRLR0_TMOD_TX_RX;
    }
    else if (dw_spi_dev->rx)
    {
        /* set mode to Rx only */
        dw_spi_dev->tmode = DW_SPI_CTRLR0_TMOD_RX;
    }
    else
    {
        /* set mode to Tx only */
        dw_spi_dev->tmode = DW_SPI_CTRLR0_TMOD_TX;
    }

    struct dw_spi_regs *regs = dw_spi_dev->reg;
    /* disable spi */
    writel(0, &regs->ssienr);

    LOG_D("dw_spixfer:tx 0x%x rx 0x%x len %d\n", dw_spi_dev->tx, dw_spi_dev->rx, message->length);

    rt_uint32_t cr0 = dw_spi_dev->update_cr0(dw_spi_dev);
    /* write control register */
    if (cr0 != readl(&regs->ctrl0))
    {
        writel(cr0, &regs->ctrl0);
    }
    /* set slave select */
    writel(1 << (dw_spi_dev->cs), &regs->ser);

    /* enable spi */
    writel(1, &regs->ssienr);
    /* transfer data */
    dw_spi_poll_transfer(dw_spi_dev);

    /* wait for transfer complete */
    wait_for_idle(dw_spi_dev);

    return message->length;
}

const static struct rt_spi_ops dw_drv_spi_ops =
{
    _dw_drv_spi_configure,
    _dw_spixfer,
};


static int dw_spi_hw_init(struct dw_spi *dw_spi_dev)
{
    struct dw_spi_regs *regs = dw_spi_dev->reg;

    /* disable spi */
    writel(0, &regs->ssienr);
    /* disbale all interrupts */
    writel(0, &regs->imr);
    /* read and clear interrupt status */
    readl(&regs->icr);
    /* set slave select */
    writel(0, &regs->ser);
    /* enable spi */
    writel(1, &regs->ssienr);

    dw_spi_dev->version = readl(&regs->version);
    rt_kprintf("ssi_version_id=%c.%c%c%c\n",
               dw_spi_dev->version >> 24, dw_spi_dev->version >> 16,
               dw_spi_dev->version >> 8, dw_spi_dev->version);

    /* detect the FIFO depth if not set by interface driver */
    if (!dw_spi_dev->fifo_len)
    {
        uint32_t fifo;
        for (fifo = 1; fifo < 256; fifo++)
        {
            writel(fifo, &regs->txftlr);
            if (fifo != readl(&regs->txftlr))
            {
                break;
            }
        }
        dw_spi_dev->fifo_len = (fifo == 1) ? 0 : fifo;
        writel(0, &regs->txftlr);
        rt_kprintf("fifo length is %d\n", dw_spi_dev->fifo_len);
    }

    rt_uint32_t cr0, tmp = readl(&regs->ctrl0);
    writel(0, &regs->ssienr);

    writel(0xffffffff, &regs->ctrl0);
    cr0 = readl(&regs->ctrl0);
    writel(tmp, &regs->ctrl0);

    writel(1, &regs->ssienr);

    if (cr0 & DW_SPI_CTRLR0_DFS_MASK)
    {
        dw_spi_device.update_cr0 = update_control_reg_16;
    }
    else
    {
        dw_spi_device.update_cr0 = update_control_reg_32;
    }
    return 0;
}

int rt_hw_dw_spi_init(void)
{
    rt_err_t ret = RT_EOK;
    struct dw_spi_regs *reg = NULL;

    /* set reg base */
#ifdef RT_USING_SMART
    reg = (struct dw_spi_regs *)rt_ioremap((void *)DW_SPI_BASE_ADDR, sizeof(struct dw_spi_regs));
#else
    reg = (struct dw_spi_regs *)DW_SPI_BASE_ADDR;
#endif
    LOG_D("%s: reg base %p\n", __func__, reg);
    if (!reg)
        return -RT_ERROR;

    dw_spi_device.reg = reg;
    dw_spi_device.spi_bus.parent.user_data = &dw_spi_device;

    dw_spi_device.tmode = 0; /* Tx & Rx */
    dw_spi_device.bits_per_word = 8;

    /* init spi */
    dw_spi_hw_init(&dw_spi_device);

    /* Register SPI bus*/
    ret = rt_spi_bus_register(&dw_spi_device.spi_bus, dw_spi_device.device_name, &dw_drv_spi_ops);
    if (ret == RT_EOK)
    {
        static struct rt_spi_device spi_device0;
        rt_spi_bus_attach_device(&spi_device0, SPI0_BUS_DEVICE0_NAME, SPI0_BUS_NAME, (void *)&dw_spi_device);
    }
    return ret;
}
INIT_BOARD_EXPORT(rt_hw_dw_spi_init);

#endif /* BSP_USING_DW_SPI */