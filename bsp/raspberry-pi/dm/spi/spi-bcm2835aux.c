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

#define DBG_TAG "spi.bcm2835.aux"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* SPI register offsets */
#define BCM2835_AUX_SPI_CNTL0               0x00
#define BCM2835_AUX_SPI_CNTL1               0x04
#define BCM2835_AUX_SPI_STAT                0x08
#define BCM2835_AUX_SPI_PEEK                0x0c
#define BCM2835_AUX_SPI_IO                  0x20
#define BCM2835_AUX_SPI_TXHOLD              0x30

/* Bitfields in CNTL0 */
#define BCM2835_AUX_SPI_CNTL0_SPEED         0xfff00000
#define BCM2835_AUX_SPI_CNTL0_SPEED_MAX     0xfff
#define BCM2835_AUX_SPI_CNTL0_SPEED_SHIFT   20
#define BCM2835_AUX_SPI_CNTL0_CS            0x000e0000
#define BCM2835_AUX_SPI_CNTL0_POSTINPUT     0x00010000
#define BCM2835_AUX_SPI_CNTL0_VAR_CS        0x00008000
#define BCM2835_AUX_SPI_CNTL0_VAR_WIDTH     0x00004000
#define BCM2835_AUX_SPI_CNTL0_DOUTHOLD      0x00003000
#define BCM2835_AUX_SPI_CNTL0_ENABLE        0x00000800
#define BCM2835_AUX_SPI_CNTL0_IN_RISING     0x00000400
#define BCM2835_AUX_SPI_CNTL0_CLEARFIFO     0x00000200
#define BCM2835_AUX_SPI_CNTL0_OUT_RISING    0x00000100
#define BCM2835_AUX_SPI_CNTL0_CPOL          0x00000080
#define BCM2835_AUX_SPI_CNTL0_MSBF_OUT      0x00000040
#define BCM2835_AUX_SPI_CNTL0_SHIFTLEN      0x0000003f

/* Bitfields in CNTL1 */
#define BCM2835_AUX_SPI_CNTL1_CSHIGH        0x00000700
#define BCM2835_AUX_SPI_CNTL1_TXEMPTY       0x00000080
#define BCM2835_AUX_SPI_CNTL1_IDLE          0x00000040
#define BCM2835_AUX_SPI_CNTL1_MSBF_IN       0x00000002
#define BCM2835_AUX_SPI_CNTL1_KEEP_IN       0x00000001

/* Bitfields in STAT */
#define BCM2835_AUX_SPI_STAT_TX_LVL         0xff000000
#define BCM2835_AUX_SPI_STAT_RX_LVL         0x00ff0000
#define BCM2835_AUX_SPI_STAT_TX_FULL        0x00000400
#define BCM2835_AUX_SPI_STAT_TX_EMPTY       0x00000200
#define BCM2835_AUX_SPI_STAT_RX_FULL        0x00000100
#define BCM2835_AUX_SPI_STAT_RX_EMPTY       0x00000080
#define BCM2835_AUX_SPI_STAT_BUSY           0x00000040
#define BCM2835_AUX_SPI_STAT_BITCOUNT       0x0000003f

#define POLLING_LIMIT_US                    30

struct bcm2835aux_spi
{
    struct rt_spi_bus parent;

    void *regs;
    int irq;
    struct rt_clk *clk;

    rt_uint8_t mode;

    rt_uint32_t cntl[2];
    rt_uint8_t *rx_buf;
    const rt_uint8_t *tx_buf;
    int tx_len;
    int rx_len;
    int pending;

    struct rt_completion done;
};

#define raw_to_bcm2835aux_spi(raw) rt_container_of(raw, struct bcm2835aux_spi, parent)

rt_inline rt_uint32_t bcm2835aux_rd(struct bcm2835aux_spi *bs, int reg)
{
    return HWREG32(bs->regs + reg);
}

rt_inline void bcm2835aux_wr(struct bcm2835aux_spi *bs, int reg, rt_uint32_t val)
{
    HWREG32(bs->regs + reg) = val;
}

rt_inline void bcm2835aux_rd_fifo(struct bcm2835aux_spi *bs)
{
    rt_uint32_t data;
    int count = rt_min(bs->rx_len, 3);

    data = bcm2835aux_rd(bs, BCM2835_AUX_SPI_IO);

    if (bs->rx_buf)
    {
        switch (count)
        {
        case 3:
            *bs->rx_buf++ = (data >> 16) & 0xff;
            /* fallthrough */;
        case 2:
            *bs->rx_buf++ = (data >> 8) & 0xff;
            /* fallthrough */;
        case 1:
            *bs->rx_buf++ = (data >> 0) & 0xff;
            /* fallthrough - no default */
        }
    }

    bs->rx_len -= count;
    bs->pending -= count;
}

rt_inline void bcm2835aux_wr_fifo(struct bcm2835aux_spi *bs)
{
    int count;
    rt_uint8_t byte;
    rt_uint32_t data = 0;

    /* Gather up to 3 bytes to write to the FIFO */
    count = rt_min(bs->tx_len, 3);
    for (int i = 0; i < count; ++i)
    {
        byte = bs->tx_buf ? *bs->tx_buf++ : 0;
        data |= byte << (8 * (2 - i));
    }

    /* and set the variable bit-length */
    data |= (count * 8) << 24;

    /* and decrement length */
    bs->tx_len -= count;
    bs->pending += count;

    /* write to the correct TX-register */
    if (bs->tx_len)
    {
        bcm2835aux_wr(bs, BCM2835_AUX_SPI_TXHOLD, data);
    }
    else
    {
        bcm2835aux_wr(bs, BCM2835_AUX_SPI_IO, data);
    }
}

static void bcm2835aux_spi_reset_hw(struct bcm2835aux_spi *bs)
{
    /* disable spi clearing fifo and interrupts */
    bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, 0);
    bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, BCM2835_AUX_SPI_CNTL0_CLEARFIFO);
}

static void bcm2835aux_spi_transfer_helper(struct bcm2835aux_spi *bs)
{
    rt_uint32_t stat = bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT);

    /* Check if we have data to read */
    for (; bs->rx_len && (stat & BCM2835_AUX_SPI_STAT_RX_LVL);
         stat = bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT))
    {
        bcm2835aux_rd_fifo(bs);
    }

    /* Check if we have data to write */
    while (bs->tx_len && bs->pending < 12 &&
        !(bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT) & BCM2835_AUX_SPI_STAT_TX_FULL))
    {
        bcm2835aux_wr_fifo(bs);
    }
}

rt_inline void bcm2835aux_spi_enable_irq(struct bcm2835aux_spi *bs)
{
    bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1] |
            BCM2835_AUX_SPI_CNTL1_TXEMPTY | BCM2835_AUX_SPI_CNTL1_IDLE);
}

static rt_err_t bcm2835aux_spi_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *conf)
{
    struct bcm2835aux_spi *bs = raw_to_bcm2835aux_spi(device->bus);

    if (!(conf->mode & RT_SPI_NO_CS))
    {
        return -RT_EINVAL;
    }

    /* Prepare message */
    bs->cntl[0] = BCM2835_AUX_SPI_CNTL0_ENABLE |
            BCM2835_AUX_SPI_CNTL0_VAR_WIDTH |
            BCM2835_AUX_SPI_CNTL0_MSBF_OUT;
    bs->cntl[1] = BCM2835_AUX_SPI_CNTL1_MSBF_IN;

    /* Handle all the modes */
    if (conf->mode & RT_SPI_CPOL)
    {
        bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_CPOL;
        bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_OUT_RISING;
    }
    else
    {
        bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_IN_RISING;
    }

    bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
    bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

    return RT_EOK;
}

static rt_ssize_t bcm2835aux_spi_xfer(struct rt_spi_device *device,
        struct rt_spi_message *msg)
{
    rt_ubase_t effective_speed_hz, spi_hz, clk_hz, speed, hz_per_byte, byte_limit;
    struct bcm2835aux_spi *bs = raw_to_bcm2835aux_spi(device->bus);

    spi_hz = device->config.max_hz;
    clk_hz = rt_clk_get_rate(bs->clk);

    if (spi_hz >= clk_hz / 2)
    {
        speed = 0;
    }
    else if (spi_hz)
    {
        speed = RT_DIV_ROUND_UP(clk_hz, 2 * spi_hz) - 1;

        if (speed >  BCM2835_AUX_SPI_CNTL0_SPEED_MAX)
        {
            speed = BCM2835_AUX_SPI_CNTL0_SPEED_MAX;
        }
    }
    else
    {
        speed = BCM2835_AUX_SPI_CNTL0_SPEED_MAX;
    }
    /* Mask out old speed from previous spi_transfer */
    bs->cntl[0] &= ~BCM2835_AUX_SPI_CNTL0_SPEED;
    /* set the new speed */
    bs->cntl[0] |= speed << BCM2835_AUX_SPI_CNTL0_SPEED_SHIFT;

    effective_speed_hz = clk_hz / (2 * (speed + 1));

    /* set transmit buffers and length */
    bs->tx_buf = msg->send_buf;
    bs->rx_buf = msg->recv_buf;
    bs->tx_len = msg->length;
    bs->rx_len = msg->length;
    bs->pending = 0;

    /*
     * Calculate the estimated time in us the transfer runs.
     * Note that there are 2 idle clocks cycles after each chunk getting
     * transferred - in our case the chunk size is 3 bytes, so we
     * approximate this by 9 cycles/byte.
     * This is used to find the number of Hz per byte per polling limit.
     * E.g., we can transfer 1 byte in 30 us per 300,000 Hz of bus clock.
     */
    hz_per_byte = POLLING_LIMIT_US ? (9 * 1000000) / POLLING_LIMIT_US : 0;
    byte_limit = hz_per_byte ? effective_speed_hz / hz_per_byte : 1;

    /* Polling mode for short transfers */
    if (msg->length < byte_limit)
    {
        rt_tick_t timeout;

        bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
        bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

        timeout = 2 + RT_TICK_PER_SECOND * POLLING_LIMIT_US / 1000000;
        timeout += rt_tick_get();

        while (bs->rx_len)
        {
            bcm2835aux_spi_transfer_helper(bs);

            if (bs->rx_len && rt_tick_get() > timeout)
            {
                LOG_E("%s: Timeout for poll mode", rt_dm_dev_get_name(&bs->parent.parent));
                goto _enable_irq;
            }
        }

        goto _out_unprepare;
    }

    /* IRQ mode */

    /* Fill in registers and fifos before enabling interrupts */
    bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
    bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

    /* Fill in tx fifo with data before enabling interrupts */
    while (bs->tx_len && bs->pending < 12 &&
            !(bcm2835aux_rd(bs, BCM2835_AUX_SPI_STAT) & BCM2835_AUX_SPI_STAT_TX_FULL))
    {
        bcm2835aux_wr_fifo(bs);
    }

_enable_irq:
    bcm2835aux_spi_enable_irq(bs);

    rt_completion_wait(&bs->done, RT_WAITING_FOREVER);

_out_unprepare:
    /* Unprepare message */
    bcm2835aux_spi_reset_hw(bs);

    return msg->length;
}

static struct rt_spi_ops bcm2835aux_spi_ops =
{
    .configure = bcm2835aux_spi_configure,
    .xfer = bcm2835aux_spi_xfer,
};

static void bcm2835aux_spi_isr(int irq, void *param)
{
    struct bcm2835aux_spi *bs = param;

    if (!(bcm2835aux_rd(bs, BCM2835_AUX_SPI_CNTL1) &
        (BCM2835_AUX_SPI_CNTL1_TXEMPTY | BCM2835_AUX_SPI_CNTL1_IDLE)))
    {
        return;
    }

    bcm2835aux_spi_transfer_helper(bs);

    if (!bs->tx_len)
    {
        /* Disable tx fifo empty interrupt */
        bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1] | BCM2835_AUX_SPI_CNTL1_IDLE);
    }

    if (!bs->rx_len)
    {
        bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
        rt_completion_done(&bs->done);

        /* Unprepare message */
        bcm2835aux_spi_reset_hw(bs);
    }
}

static void bcm2835aux_spi_free(struct bcm2835aux_spi *bs)
{
    if (bs->regs)
    {
        rt_iounmap(bs->regs);
    }

    if (!rt_is_err_or_null(bs->clk))
    {
        rt_clk_disable_unprepare(bs->clk);
    }

    rt_free(bs);
}

static rt_err_t bcm2835aux_spi_probe(struct rt_platform_device *pdev)
{
    int id;
    rt_err_t err;
    rt_ubase_t clk_hz;
    const char *bus_name;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835aux_spi *bs = rt_calloc(1, sizeof(*bs));

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

    if ((err = rt_clk_prepare_enable(bs->clk)))
    {
        goto _fail;
    }

    if (!(clk_hz = rt_clk_get_rate(bs->clk)))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    /* Reset SPI-HW block */
    bcm2835aux_spi_reset_hw(bs);

    bs->mode = RT_SPI_CPOL | RT_SPI_CS_HIGH | RT_SPI_NO_CS;
    bs->parent.num_chipselect = 1;
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

    rt_hw_interrupt_install(bs->irq, bcm2835aux_spi_isr, bs, bus_name);
    rt_hw_interrupt_umask(bs->irq);

    if ((err = rt_spi_bus_register(&bs->parent, bus_name, &bcm2835aux_spi_ops)))
    {
        goto _free_irq;
    }

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(bs->irq);
    rt_pic_detach_irq(bs->irq, bs);

_fail:
    bcm2835aux_spi_free(bs);

    return err;
}

static rt_err_t bcm2835aux_spi_remove(struct rt_platform_device *pdev)
{
    struct bcm2835aux_spi *bs = pdev->parent.user_data;

    rt_hw_interrupt_mask(bs->irq);
    rt_pic_detach_irq(bs->irq, bs);

    rt_device_unregister(&bs->parent.parent);

    bcm2835aux_spi_reset_hw(bs);

    bcm2835aux_spi_free(bs);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2835aux_spi_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-aux-spi", },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835aux_spi_driver =
{
    .name = "bcm2835-aux-spi",
    .ids = bcm2835aux_spi_ofw_ids,

    .probe = bcm2835aux_spi_probe,
    .remove = bcm2835aux_spi_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835aux_spi_driver);
