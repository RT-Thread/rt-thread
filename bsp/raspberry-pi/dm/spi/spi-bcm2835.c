/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "spi.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

/* SPI register offsets */
#define BCM2835_SPI_CS                  0x00
#define BCM2835_SPI_FIFO                0x04
#define BCM2835_SPI_CLK                 0x08
#define BCM2835_SPI_DLEN                0x0c
#define BCM2835_SPI_LTOH                0x10
#define BCM2835_SPI_DC                  0x14

/* Bitfields in CS */
#define BCM2835_SPI_CS_LEN_LONG         0x02000000
#define BCM2835_SPI_CS_DMA_LEN          0x01000000
#define BCM2835_SPI_CS_CSPOL2           0x00800000
#define BCM2835_SPI_CS_CSPOL1           0x00400000
#define BCM2835_SPI_CS_CSPOL0           0x00200000
#define BCM2835_SPI_CS_RXF              0x00100000
#define BCM2835_SPI_CS_RXR              0x00080000
#define BCM2835_SPI_CS_TXD              0x00040000
#define BCM2835_SPI_CS_RXD              0x00020000
#define BCM2835_SPI_CS_DONE             0x00010000
#define BCM2835_SPI_CS_LEN              0x00002000
#define BCM2835_SPI_CS_REN              0x00001000
#define BCM2835_SPI_CS_ADCS             0x00000800
#define BCM2835_SPI_CS_INTR             0x00000400
#define BCM2835_SPI_CS_INTD             0x00000200
#define BCM2835_SPI_CS_DMAEN            0x00000100
#define BCM2835_SPI_CS_TA               0x00000080
#define BCM2835_SPI_CS_CSPOL            0x00000040
#define BCM2835_SPI_CS_CLEAR_RX         0x00000020
#define BCM2835_SPI_CS_CLEAR_TX         0x00000010
#define BCM2835_SPI_CS_CPOL             0x00000008
#define BCM2835_SPI_CS_CPHA             0x00000004
#define BCM2835_SPI_CS_CS_10            0x00000002
#define BCM2835_SPI_CS_CS_01            0x00000001

#define BCM2835_SPI_FIFO_SIZE           64
#define BCM2835_SPI_FIFO_SIZE_3_4       48
#define BCM2835_SPI_DMA_MIN_LENGTH      96
#define BCM2835_SPI_POLLING_LIMIT_US    30

struct bcm2835_spi
{
    struct rt_spi_bus parent;

    rt_uint8_t mode;
    rt_ubase_t max_speed_hz;

    int irq;
    void *regs;

    rt_ubase_t clk_hz;
    struct rt_clk *clk;
    struct rt_spi_message *msg;

    const rt_uint8_t *tx_buf;
    rt_uint8_t *rx_buf;
    int tx_len;
    int rx_len;
    int tx_prologue;
    int rx_prologue;
    rt_uint32_t tx_spillover;

    rt_uint32_t prepare_cs;
    rt_uint32_t clear_rx_cs;

    struct rt_completion done;
};

#define raw_to_bcm2835_spi(raw) rt_container_of(raw, struct bcm2835_spi, parent)

rt_inline rt_uint32_t bcm2835_rd(struct bcm2835_spi *bs, int reg)
{
    return HWREG32(bs->regs + reg);
}

rt_inline void bcm2835_wr(struct bcm2835_spi *bs, int reg, rt_uint32_t val)
{
    HWREG32(bs->regs + reg) = val;
}

rt_inline void bcm2835_rd_fifo(struct bcm2835_spi *bs)
{
    rt_uint8_t byte;

    while (bs->rx_len && (bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_RXD))
    {
        /* Read flush */
        byte = bcm2835_rd(bs, BCM2835_SPI_FIFO);

        if (bs->rx_buf)
        {
            *bs->rx_buf++ = byte;
        }

        --bs->rx_len;
    }
}

rt_inline void bcm2835_wr_fifo(struct bcm2835_spi *bs)
{
    rt_uint8_t byte;

    while (bs->tx_len && (bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_TXD))
    {
        byte = bs->tx_buf ? *bs->tx_buf++ : 0;
        bcm2835_wr(bs, BCM2835_SPI_FIFO, byte);
        --bs->tx_len;
    }
}

rt_inline void bcm2835_rd_fifo_count(struct bcm2835_spi *bs, int count)
{
    int len;
    rt_uint32_t val;

    bs->rx_len -= count;

    do {
        val = bcm2835_rd(bs, BCM2835_SPI_FIFO);
        len = rt_min(count, 4);
        rt_memcpy(bs->rx_buf, &val, len);
        bs->rx_buf += len;
        count -= 4;
    } while (count > 0);
}

rt_inline void bcm2835_wr_fifo_count(struct bcm2835_spi *bs, int count)
{
    int len;
    rt_uint32_t val;

    bs->tx_len -= count;

    do {
        if (bs->tx_buf)
        {
            len = rt_min(count, 4);
            rt_memcpy(&val, bs->tx_buf, len);
            bs->tx_buf += len;
        }
        else
        {
            val = 0;
        }

        bcm2835_wr(bs, BCM2835_SPI_FIFO, val);
        count -= 4;
    } while (count > 0);
}

rt_inline void bcm2835_wait_tx_fifo_empty(struct bcm2835_spi *bs)
{
    while (!(bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_DONE))
    {
        rt_hw_cpu_relax();
    }
}

rt_inline void bcm2835_rd_fifo_blind(struct bcm2835_spi *bs, int count)
{
    rt_uint8_t val;

    count = rt_min(count, bs->rx_len);
    bs->rx_len -= count;

    do {
        val = bcm2835_rd(bs, BCM2835_SPI_FIFO);

        if (bs->rx_buf)
        {
            *bs->rx_buf++ = val;
        }
    } while (--count);
}

rt_inline void bcm2835_wr_fifo_blind(struct bcm2835_spi *bs, int count)
{
    rt_uint8_t val;

    count = rt_min(count, bs->tx_len);
    bs->tx_len -= count;

    do {
        val = bs->tx_buf ? *bs->tx_buf++ : 0;
        bcm2835_wr(bs, BCM2835_SPI_FIFO, val);
    } while (--count);
}

static void bcm2835_spi_reset_hw(struct bcm2835_spi *bs)
{
    rt_uint32_t cs = bcm2835_rd(bs, BCM2835_SPI_CS);

    /* Disable SPI interrupts and transfer */
    cs &= ~(BCM2835_SPI_CS_INTR | BCM2835_SPI_CS_INTD | BCM2835_SPI_CS_DMAEN | BCM2835_SPI_CS_TA);

    /*
     * Transmission sometimes breaks unless the DONE bit is written at the
     * end of every transfer.  The spec says it's a RO bit.  Either the
     * spec is wrong and the bit is actually of type RW1C, or it's a
     * hardware erratum.
     */
    cs |= BCM2835_SPI_CS_DONE;
    /* Reset RX/TX FIFOS */
    cs |= BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX;

    /* Reset the SPI_HW */
    bcm2835_wr(bs, BCM2835_SPI_CS, cs);
    /* Reset the DLEN */
    bcm2835_wr(bs, BCM2835_SPI_DLEN, 0);
}

static void bcm2835_spi_transfer_one_irq(struct bcm2835_spi *bs,
        rt_uint32_t cs, rt_bool_t fifo_empty)
{
    /*
     * Enable HW block, but with interrupts still disabled.
     * Otherwise the empty TX FIFO would immediately trigger an interrupt.
     */
    bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

    /* Fill TX FIFO as much as possible */
    if (fifo_empty)
    {
        bcm2835_wr_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);
    }
    bcm2835_wr_fifo(bs);

    /* Enable interrupts */
    cs |= BCM2835_SPI_CS_INTR | BCM2835_SPI_CS_INTD | BCM2835_SPI_CS_TA;
    bcm2835_wr(bs, BCM2835_SPI_CS, cs);
}

static rt_err_t bcm2835_spi_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *conf)
{
    rt_uint32_t prepare_cs;
    struct bcm2835_spi *bs = raw_to_bcm2835_spi(device->bus);

    prepare_cs = BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01;

    if (conf->mode & RT_SPI_CPOL)
    {
        prepare_cs |= BCM2835_SPI_CS_CPOL;
    }
    if (conf->mode & RT_SPI_CPHA)
    {
        prepare_cs |= BCM2835_SPI_CS_CPHA;
    }
    device->user_data = (void *)(rt_ubase_t)prepare_cs;

    if (conf->mode & RT_SPI_NO_CS)
    {
        return RT_EOK;
    }

    bcm2835_wr(bs, BCM2835_SPI_CS, prepare_cs);

    return RT_EOK;
}

static rt_ssize_t bcm2835_spi_xfer(struct rt_spi_device *device,
        struct rt_spi_message *msg)
{
    rt_bool_t fifo_empty = RT_TRUE;
    rt_ubase_t spi_hz, cdiv, hz_per_byte, byte_limit, effective_speed_hz;
    rt_uint32_t cs = (rt_ubase_t)device->user_data;
    struct bcm2835_spi *bs = raw_to_bcm2835_spi(device->bus);

    spi_hz = device->config.max_hz;

    if (spi_hz >= bs->clk_hz / 2)
    {
        cdiv = 2;
    }
    else if (spi_hz)
    {
        cdiv = RT_DIV_ROUND_UP(bs->clk_hz, spi_hz);
        cdiv += (cdiv % 2);

        if (cdiv >= 65536)
        {
            cdiv = 0;
        }
    }
    else
    {
        cdiv = 0;
    }
    effective_speed_hz = cdiv ? (bs->clk_hz / cdiv) : (bs->clk_hz / 65536);
    bcm2835_wr(bs, BCM2835_SPI_CLK, cdiv);

    /* Handle all the 3-wire mode */
    if (device->config.mode & RT_SPI_3WIRE && msg->recv_buf)
    {
        cs |= BCM2835_SPI_CS_REN;
    }

    /* Set transmit buffers and length */
    bs->tx_buf = msg->send_buf;
    bs->rx_buf = msg->recv_buf;
    bs->tx_len = msg->length;
    bs->rx_len = msg->length;

    /*
     * Calculate the estimated time in us the transfer runs.  Note that
     * there is 1 idle clocks cycles after each byte getting transferred
     * so we have 9 cycles/byte.  This is used to find the number of Hz
     * per byte per polling limit.  E.g., we can transfer 1 byte in 30 us
     * per 300,000 Hz of bus clock.
     */
    hz_per_byte = BCM2835_SPI_POLLING_LIMIT_US ? (9 * 1000000) / BCM2835_SPI_POLLING_LIMIT_US : 0;
    byte_limit = hz_per_byte ? effective_speed_hz / hz_per_byte : 1;

    /* Run in polling mode for short transfers */
    if (msg->length < byte_limit)
    {
        rt_tick_t timeout;

        /* Enable HW block without interrupts */
        bcm2835_wr(bs, BCM2835_SPI_CS, cs | BCM2835_SPI_CS_TA);

        /*
         * Fill in the fifo before timeout calculations
         * if we are interrupted here, then the data is
         * getting transferred by the HW while we are interrupted
         */
        bcm2835_wr_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);

        /* Set the timeout to at least 2 jiffies */
        timeout = 2 + RT_TICK_PER_SECOND * BCM2835_SPI_POLLING_LIMIT_US / 1000000;
        timeout += rt_tick_get();

        while (bs->rx_len)
        {
            /* Fill in tx fifo with remaining data */
            bcm2835_wr_fifo(bs);

            /* Read from fifo as much as possible */
            bcm2835_rd_fifo(bs);

            if (bs->rx_len && rt_tick_get() > timeout)
            {
                LOG_E("%s: Timeout for poll mode", rt_dm_dev_get_name(&bs->parent.parent));

                fifo_empty = RT_FALSE;
                goto _irq_mode;
            }
        }

        /* Transfer complete - reset SPI HW */
        bcm2835_spi_reset_hw(bs);
        goto _end;
    }

_irq_mode:
    bcm2835_spi_transfer_one_irq(bs, cs, fifo_empty);

    rt_completion_wait(&bs->done, RT_WAITING_FOREVER);

_end:
    return msg->length;
}

static struct rt_spi_ops bcm2835_spi_ops =
{
    .configure = bcm2835_spi_configure,
    .xfer = bcm2835_spi_xfer,
};

static void bcm2835_spi_isr(int irq, void *param)
{
    rt_uint32_t cs;
    struct bcm2835_spi *bs = param;

    cs = bcm2835_rd(bs, BCM2835_SPI_CS);

    /* Bail out early if interrupts are not enabled */
    if (!(cs & BCM2835_SPI_CS_INTR))
    {
        return;
    }

    /*
     * An interrupt is signaled either if DONE is set (TX FIFO empty)
     * or if RXR is set (RX FIFO >= 3/4 full).
     */
    if (cs & BCM2835_SPI_CS_RXF)
    {
        bcm2835_rd_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);
    }
    else if (cs & BCM2835_SPI_CS_RXR)
    {
        bcm2835_rd_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE_3_4);
    }

    if (bs->tx_len && cs & BCM2835_SPI_CS_DONE)
    {
        bcm2835_wr_fifo_blind(bs, BCM2835_SPI_FIFO_SIZE);
    }

    /* Read as many bytes as possible from FIFO */
    bcm2835_rd_fifo(bs);
    /* Write as many bytes as possible to FIFO */
    bcm2835_wr_fifo(bs);

    if (!bs->rx_len)
    {
        /* Transfer complete - reset SPI HW */
        bcm2835_spi_reset_hw(bs);
        rt_completion_done(&bs->done);
    }
}

static void bcm2835_spi_free(struct bcm2835_spi *bs)
{
    if (!rt_is_err_or_null(bs->clk))
    {
        rt_clk_disable_unprepare(bs->clk);
    }
}

static rt_err_t bcm2835_spi_probe(struct rt_platform_device *pdev)
{
    int id;
    rt_err_t err;
    const char *bus_name;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_spi *bs = rt_calloc(1, sizeof(*bs));

    if (!bs)
    {
        return -RT_ENOMEM;
    }

    bs->regs = rt_dm_dev_iomap(dev, 0);

    if (!bs->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    bs->irq = rt_dm_dev_get_irq(dev, 0);

    if (bs->irq < 0)
    {
        err = bs->irq;
        goto _fail;
    }

    bs->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(bs->clk))
    {
        err = rt_ptr_err(bs->clk);
        goto _fail;
    }

    rt_clk_prepare_enable(bs->clk);
    bs->max_speed_hz = rt_clk_get_rate(bs->clk);

    bcm2835_wr(bs, BCM2835_SPI_CS, BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX);

    bs->mode = RT_SPI_CPOL | RT_SPI_CPHA | RT_SPI_CS_HIGH | RT_SPI_NO_CS | RT_SPI_3WIRE;
    bs->parent.num_chipselect = 3;
    rt_completion_init(&bs->done);

    dev->user_data = bs;

    bs->parent.parent.ofw_node = dev->ofw_node;

    if ((id = pdev->dev_id) >= 0)
    {
        rt_dm_dev_set_name(&bs->parent.parent, "spi%u", id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&bs->parent.parent, "spi");
    }
    bus_name = rt_dm_dev_get_name(&bs->parent.parent);

    rt_hw_interrupt_install(bs->irq, bcm2835_spi_isr, bs, bus_name);
    rt_hw_interrupt_umask(bs->irq);

    if ((err = rt_spi_bus_register(&bs->parent, bus_name, &bcm2835_spi_ops)))
    {
        goto _free_irq;
    }

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(bs->irq);
    rt_pic_detach_irq(bs->irq, bs);

_fail:
    bcm2835_spi_free(bs);

    return err;
}

static rt_err_t bcm2835_spi_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_spi *bs = pdev->parent.user_data;

    rt_hw_interrupt_mask(bs->irq);
    rt_pic_detach_irq(bs->irq, bs);

    rt_device_unregister(&bs->parent.parent);

    /* Clear FIFOs, and disable the HW block */
    bcm2835_wr(bs, BCM2835_SPI_CS, BCM2835_SPI_CS_CLEAR_RX | BCM2835_SPI_CS_CLEAR_TX);

    bcm2835_spi_free(bs);

    return RT_EOK;
}

static rt_err_t bcm2835_spi_shutdown(struct rt_platform_device *pdev)
{
    return bcm2835_spi_remove(pdev);
}

static const struct rt_ofw_node_id bcm2835_spi_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-spi", },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_spi_driver =
{
    .name = "bcm2835-spi",
    .ids = bcm2835_spi_ofw_ids,

    .probe = bcm2835_spi_probe,
    .remove = bcm2835_spi_remove,
    .shutdown = bcm2835_spi_shutdown,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_spi_driver);
