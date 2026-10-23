/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "spi.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_SPI_GBL_CTL          0x04
#define SUNXI_SPI_TFR_CTL          0x08
#define SUNXI_SPI_INT_CTL          0x10
#define SUNXI_SPI_INT_STA          0x14
#define SUNXI_SPI_FIFO_CTL         0x18
#define SUNXI_SPI_FIFO_STA         0x1c
#define SUNXI_SPI_BURST_CNT        0x30
#define SUNXI_SPI_XMIT_CNT         0x34
#define SUNXI_SPI_BURST_CTL_CNT    0x38
#define SUNXI_SPI_TXDATA           0x200
#define SUNXI_SPI_RXDATA           0x300

#define SUNXI_SPI_GBL_BUS_ENABLE   RT_BIT(0)
#define SUNXI_SPI_GBL_MASTER       RT_BIT(1)
#define SUNXI_SPI_GBL_TP           RT_BIT(7)
#define SUNXI_SPI_GBL_RESET        RT_BIT(31)

#define SUNXI_SPI_TFR_CPHA         RT_BIT(0)
#define SUNXI_SPI_TFR_CPOL         RT_BIT(1)
#define SUNXI_SPI_TFR_CS_MASK      RT_GENMASK(5, 4)
#define SUNXI_SPI_TFR_CS(cs)       (((cs) & 0x3) << 4)
#define SUNXI_SPI_TFR_CS_MANUAL    RT_BIT(6)
#define SUNXI_SPI_TFR_CS_LEVEL     RT_BIT(7)
#define SUNXI_SPI_TFR_DHB          RT_BIT(8)
#define SUNXI_SPI_TFR_FBS          RT_BIT(12)
#define SUNXI_SPI_TFR_SDDM         RT_BIT(14)
#define SUNXI_SPI_TFR_XCH          RT_BIT(31)

#define SUNXI_SPI_FIFO_RX_RESET    RT_BIT(15)
#define SUNXI_SPI_FIFO_TX_RESET    RT_BIT(31)
#define SUNXI_SPI_FIFO_RX_COUNT    RT_GENMASK(7, 0)
#define SUNXI_SPI_FIFO_TX_COUNT    RT_GENMASK(23, 16)

#define SUNXI_SPI_INT_TC            RT_BIT(12)
#define SUNXI_SPI_BCC_STC_MASK      RT_GENMASK(23, 0)
#define SUNXI_SPI_BCC_DUAL_ENABLE   RT_BIT(28)
#define SUNXI_SPI_BCC_QUAD_ENABLE   RT_BIT(29)
#define SUNXI_SPI_MAX_TRANSFER      0x00ffffff
#define SUNXI_SPI_FIFO_DEPTH        64
#define SUNXI_SPI_QSPI_PREFIX_MAX   5

struct sunxi_spi
{
    struct rt_spi_bus parent;
    struct rt_clk *bus_clk;
    struct rt_clk *mod_clk;
    struct rt_reset_control *reset;
    void *base;
    rt_bool_t qspi;
};

#define to_sunxi_spi(raw) rt_container_of(raw, struct sunxi_spi, parent)

static rt_uint32_t sunxi_spi_read(struct sunxi_spi *spi, rt_uint32_t offset)
{
    return HWREG32(spi->base + offset);
}

static void sunxi_spi_write(struct sunxi_spi *spi, rt_uint32_t offset,
        rt_uint32_t value)
{
    HWREG32(spi->base + offset) = value;
}

static void sunxi_spi_set_cs(struct sunxi_spi *spi, struct rt_spi_device *device,
        rt_bool_t asserted)
{
    rt_uint32_t control = sunxi_spi_read(spi, SUNXI_SPI_TFR_CTL);

    if (device->config.mode & RT_SPI_NO_CS)
    {
        return;
    }

    control &= ~SUNXI_SPI_TFR_CS_MASK;
    control |= SUNXI_SPI_TFR_CS(device->chip_select[0]) |
            SUNXI_SPI_TFR_CS_MANUAL;
    if (asserted)
    {
        control &= ~SUNXI_SPI_TFR_CS_LEVEL;
    }
    else
    {
        control |= SUNXI_SPI_TFR_CS_LEVEL;
    }
    sunxi_spi_write(spi, SUNXI_SPI_TFR_CTL, control);
}

static rt_err_t sunxi_spi_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *configuration)
{
    rt_uint32_t control;
    struct sunxi_spi *spi = to_sunxi_spi(device->bus);

    if (!configuration->max_hz || configuration->data_width != 8)
    {
        return -RT_EINVAL;
    }

    if (rt_clk_set_rate(spi->mod_clk, configuration->max_hz))
    {
        return -RT_EINVAL;
    }

    control = sunxi_spi_read(spi, SUNXI_SPI_TFR_CTL);
    control &= ~(SUNXI_SPI_TFR_CPHA | SUNXI_SPI_TFR_CPOL |
            SUNXI_SPI_TFR_FBS | SUNXI_SPI_TFR_CS_MASK);
    control |= SUNXI_SPI_TFR_CS(device->chip_select[0]) |
            SUNXI_SPI_TFR_CS_MANUAL;
    if (configuration->mode & RT_SPI_CPHA)
    {
        control |= SUNXI_SPI_TFR_CPHA;
    }
    if (configuration->mode & RT_SPI_CPOL)
    {
        control |= SUNXI_SPI_TFR_CPOL;
    }
    if (configuration->mode & RT_SPI_LSB)
    {
        control |= SUNXI_SPI_TFR_FBS;
    }
    sunxi_spi_write(spi, SUNXI_SPI_TFR_CTL, control);

    return RT_EOK;
}

static rt_err_t sunxi_spi_wait_complete(struct sunxi_spi *spi,
        rt_size_t transfer_length, rt_size_t receive_length,
        rt_size_t *received, void *buffer)
{
    rt_tick_t timeout = rt_tick_get() + rt_tick_from_millisecond(
            rt_max_t(rt_size_t, 20, transfer_length / 64 + 20));
    rt_uint8_t *rx = buffer;

    for (;;)
    {
        rt_uint32_t status;
        rt_uint32_t available = sunxi_spi_read(spi, SUNXI_SPI_FIFO_STA) &
                SUNXI_SPI_FIFO_RX_COUNT;

        while (available-- && *received < receive_length)
        {
            rt_uint8_t value = *(volatile rt_uint8_t *)(spi->base + SUNXI_SPI_RXDATA);

            if (rx)
            {
                rx[*received] = value;
            }
            ++*received;
        }

        status = sunxi_spi_read(spi, SUNXI_SPI_INT_STA);
        if (status & SUNXI_SPI_INT_TC)
        {
            sunxi_spi_write(spi, SUNXI_SPI_INT_STA, status);
            return RT_EOK;
        }
        if ((rt_int32_t)(rt_tick_get() - timeout) >= 0)
        {
            return -RT_ETIMEOUT;
        }
        rt_hw_cpu_relax();
    }
}

static rt_err_t sunxi_spi_qspi_prefix(const struct rt_qspi_message *message,
        rt_uint8_t *prefix, rt_size_t *prefix_length)
{
    rt_size_t address_bytes;

    if (message->instruction.qspi_lines != 1 ||
            (message->address.size && message->address.qspi_lines != 1) ||
            message->address.size > 32 || message->address.size % 8 ||
            message->alternate_bytes.size || message->dummy_cycles)
    {
        return -RT_EINVAL;
    }

    prefix[0] = message->instruction.content;
    address_bytes = message->address.size / 8;

    for (rt_size_t i = 0; i < address_bytes; ++i)
    {
        prefix[i + 1] = message->address.content >>
                ((address_bytes - i - 1) * 8);
    }

    *prefix_length = address_bytes + 1;

    return RT_EOK;
}

static rt_uint8_t sunxi_spi_tx_byte(const rt_uint8_t *prefix,
        rt_size_t prefix_length, const rt_uint8_t *data, rt_size_t offset)
{
    if (offset < prefix_length)
    {
        return prefix[offset];
    }

    return data ? data[offset - prefix_length] : 0;
}

static rt_ssize_t sunxi_spi_xfer(struct rt_spi_device *device,
        struct rt_spi_message *message)
{
    rt_size_t sent = 0;
    rt_size_t received = 0;
    rt_size_t wanted_rx;
    rt_size_t prefix_length = 0;
    rt_size_t transfer_length;
    rt_size_t transmit_length;
    rt_uint8_t prefix[SUNXI_SPI_QSPI_PREFIX_MAX];
    const rt_uint8_t *tx = message->send_buf;
    struct sunxi_spi *spi = to_sunxi_spi(device->bus);
    const struct rt_qspi_message *qspi_message = RT_NULL;
    rt_uint8_t data_lines = 1;
    rt_uint32_t control;
    rt_uint32_t burst_control;
    rt_tick_t refill_timeout;
    rt_err_t err;

    if (spi->qspi)
    {
        qspi_message = (const struct rt_qspi_message *)message;
        data_lines = qspi_message->qspi_data_lines ?
                qspi_message->qspi_data_lines : 1;

        if (data_lines != 1 && data_lines != 2 && data_lines != 4)
        {
            return -RT_EINVAL;
        }
        if ((err = sunxi_spi_qspi_prefix(qspi_message, prefix,
                &prefix_length)) != RT_EOK)
        {
            return err;
        }
        if (message->recv_buf)
        {
            return -RT_ENOSYS;
        }
    }

    transfer_length = message->length + prefix_length;
    /*
     * XMIT_CNT must remain zero for RX-only bursts.  The controller still
     * needs its initial dummy FIFO seed to start the exchange, but it must
     * never be refilled as a transmit transfer.
     */
    transmit_length = (message->send_buf || prefix_length) ?
            transfer_length : 0;

    if (message->cs_take)
    {
        sunxi_spi_set_cs(spi, device, RT_TRUE);
    }

    if (!transfer_length)
    {
        if (message->cs_release)
        {
            sunxi_spi_set_cs(spi, device, RT_FALSE);
        }
        return 0;
    }
    if ((!message->send_buf && !message->recv_buf && !prefix_length) ||
            transfer_length > SUNXI_SPI_MAX_TRANSFER)
    {
        err = -RT_EINVAL;
        goto _release;
    }

    sunxi_spi_write(spi, SUNXI_SPI_INT_CTL, 0);
    sunxi_spi_write(spi, SUNXI_SPI_INT_STA, ~0u);
    sunxi_spi_write(spi, SUNXI_SPI_FIFO_CTL,
            SUNXI_SPI_FIFO_RX_RESET | SUNXI_SPI_FIFO_TX_RESET);

    control = sunxi_spi_read(spi, SUNXI_SPI_TFR_CTL);
    control &= ~(SUNXI_SPI_TFR_DHB | SUNXI_SPI_TFR_SDDM |
            SUNXI_SPI_TFR_XCH);
    if (!message->recv_buf)
    {
        control |= SUNXI_SPI_TFR_DHB;
    }
    /*
     * The controller needs one delayed clock edge when changing from a
     * single-line prefix to dual/quad payload data in SPI mode 0.
     */
    if (spi->qspi && prefix_length && data_lines > 1 &&
            !(device->config.mode & (RT_SPI_CPHA | RT_SPI_CPOL)))
    {
        control |= SUNXI_SPI_TFR_SDDM;
    }
    sunxi_spi_write(spi, SUNXI_SPI_TFR_CTL, control);

    burst_control = sunxi_spi_read(spi, SUNXI_SPI_BURST_CTL_CNT);
    burst_control &= ~(SUNXI_SPI_BCC_STC_MASK | SUNXI_SPI_BCC_DUAL_ENABLE |
            SUNXI_SPI_BCC_QUAD_ENABLE);
    if (spi->qspi)
    {
        if (data_lines == 2)
        {
            burst_control |= SUNXI_SPI_BCC_DUAL_ENABLE;
        }
        else if (data_lines == 4)
        {
            burst_control |= SUNXI_SPI_BCC_QUAD_ENABLE;
        }
        burst_control |= (data_lines == 1 ? transfer_length : prefix_length) &
                SUNXI_SPI_BCC_STC_MASK;
    }
    else
    {
        burst_control |= (message->send_buf ? message->length : 0) &
                SUNXI_SPI_BCC_STC_MASK;
    }
    sunxi_spi_write(spi, SUNXI_SPI_BURST_CTL_CNT, burst_control);
    sunxi_spi_write(spi, SUNXI_SPI_BURST_CNT, transfer_length);
    sunxi_spi_write(spi, SUNXI_SPI_XMIT_CNT, transmit_length);

    while (sent < transfer_length && sent < SUNXI_SPI_FIFO_DEPTH)
    {
        *(volatile rt_uint8_t *)(spi->base + SUNXI_SPI_TXDATA) =
                sunxi_spi_tx_byte(prefix, prefix_length, tx, sent);
        ++sent;
    }

    control = sunxi_spi_read(spi, SUNXI_SPI_GBL_CTL);
    sunxi_spi_write(spi, SUNXI_SPI_GBL_CTL, control | SUNXI_SPI_GBL_BUS_ENABLE);
    control = sunxi_spi_read(spi, SUNXI_SPI_TFR_CTL);
    sunxi_spi_write(spi, SUNXI_SPI_TFR_CTL, control | SUNXI_SPI_TFR_XCH);

    wanted_rx = message->recv_buf ? transfer_length : 0;
    refill_timeout = rt_tick_get() + rt_tick_from_millisecond(
            rt_max_t(rt_size_t, 20, transfer_length / 64 + 20));

    while (sent < transmit_length)
    {
        rt_uint32_t tx_count = (sunxi_spi_read(spi, SUNXI_SPI_FIFO_STA) &
                SUNXI_SPI_FIFO_TX_COUNT) >> 16;
        rt_uint32_t rx_count = sunxi_spi_read(spi, SUNXI_SPI_FIFO_STA) &
                SUNXI_SPI_FIFO_RX_COUNT;
        rt_bool_t progressed = RT_FALSE;

        while (rx_count-- && received < wanted_rx)
        {
            ((rt_uint8_t *)message->recv_buf)[received++] =
                    *(volatile rt_uint8_t *)(spi->base + SUNXI_SPI_RXDATA);
            progressed = RT_TRUE;
        }
        while (sent < transmit_length && tx_count++ < SUNXI_SPI_FIFO_DEPTH)
        {
            *(volatile rt_uint8_t *)(spi->base + SUNXI_SPI_TXDATA) =
                    sunxi_spi_tx_byte(prefix, prefix_length, tx, sent);
            ++sent;
            progressed = RT_TRUE;
        }
        if (!progressed)
        {
            if ((rt_int32_t)(rt_tick_get() - refill_timeout) >= 0)
            {
                err = -RT_ETIMEOUT;
                goto _release;
            }
            rt_hw_cpu_relax();
        }
    }

    err = sunxi_spi_wait_complete(spi, transfer_length, wanted_rx,
            &received, message->recv_buf);

_release:
    if (message->cs_release)
    {
        sunxi_spi_set_cs(spi, device, RT_FALSE);
    }

    return err ? err : transfer_length;
}

static const struct rt_spi_ops sunxi_spi_ops =
{
    .configure = sunxi_spi_configure,
    .xfer = sunxi_spi_xfer,
};

static void sunxi_spi_free(struct sunxi_spi *spi)
{
    if (!rt_is_err_or_null(spi->reset))
    {
        rt_reset_control_put(spi->reset);
    }
    if (!rt_is_err_or_null(spi->mod_clk))
    {
        rt_clk_disable_unprepare(spi->mod_clk);
        rt_clk_put(spi->mod_clk);
    }
    if (!rt_is_err_or_null(spi->bus_clk))
    {
        rt_clk_disable_unprepare(spi->bus_clk);
        rt_clk_put(spi->bus_clk);
    }
    if (spi->base)
    {
        rt_iounmap(spi->base);
    }
    rt_free(spi);
}

static rt_err_t sunxi_spi_probe(struct rt_platform_device *pdev)
{
    int id;
    rt_err_t err;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_spi *spi = rt_calloc(1, sizeof(*spi));

    if (!spi)
    {
        return -RT_ENOMEM;
    }

    spi->base = rt_dm_dev_iomap(dev, 0);
    if (!spi->base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    spi->bus_clk = rt_clk_get_by_index(dev, 0);
    spi->mod_clk = rt_clk_get_by_index(dev, 1);
    if (rt_is_err(spi->bus_clk) || rt_is_err(spi->mod_clk))
    {
        err = rt_is_err(spi->bus_clk) ? rt_ptr_err(spi->bus_clk) :
                rt_ptr_err(spi->mod_clk);
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(spi->bus_clk)) ||
            (err = rt_clk_prepare_enable(spi->mod_clk)))
    {
        goto _fail;
    }
    spi->reset = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(spi->reset))
    {
        err = rt_ptr_err(spi->reset);
        goto _fail;
    }
    if (spi->reset && (err = rt_reset_control_deassert(spi->reset)))
    {
        goto _fail;
    }

    sunxi_spi_write(spi, SUNXI_SPI_GBL_CTL, SUNXI_SPI_GBL_RESET);
    rt_hw_us_delay(2);
    sunxi_spi_write(spi, SUNXI_SPI_GBL_CTL,
            SUNXI_SPI_GBL_MASTER | SUNXI_SPI_GBL_TP);
    sunxi_spi_write(spi, SUNXI_SPI_TFR_CTL, SUNXI_SPI_TFR_CS_LEVEL);
    spi->parent.mode = RT_SPI_CPHA | RT_SPI_CPOL | RT_SPI_LSB | RT_SPI_NO_CS;
    spi->parent.num_chipselect = 4;
    spi->parent.parent.ofw_node = dev->ofw_node;
    spi->qspi = rt_dm_dev_prop_read_bool(dev, "allwinner,qspi-mode");

    id = rt_ofw_get_alias_id(dev->ofw_node, "spi");
    if (id >= 0)
    {
        rt_dm_dev_set_name(&spi->parent.parent, "spi%u", id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&spi->parent.parent, "spi");
    }
    name = rt_dm_dev_get_name(&spi->parent.parent);
    dev->user_data = spi;

    if (spi->qspi)
    {
#ifdef RT_USING_QSPI
        err = rt_qspi_bus_register(&spi->parent, name, &sunxi_spi_ops);
#else
        err = -RT_ENOSYS;
#endif
    }
    else
    {
        err = rt_spi_bus_register(&spi->parent, name, &sunxi_spi_ops);
    }
    if (err)
    {
        goto _fail;
    }
    rt_dm_dev_bind_fwdata(dev, RT_NULL, spi);

    return RT_EOK;

_fail:
    sunxi_spi_free(spi);
    return err;
}

static rt_err_t sunxi_spi_remove(struct rt_platform_device *pdev)
{
    struct sunxi_spi *spi = pdev->parent.user_data;

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    rt_device_unregister(&spi->parent.parent);
    sunxi_spi_free(spi);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_spi_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-spi" },
    { .compatible = "allwinner,sun50i-h616-spi" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_spi_driver =
{
    .name = "sunxi-spi",
    .ids = sunxi_spi_ofw_ids,
    .probe = sunxi_spi_probe,
    .remove = sunxi_spi_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_spi_driver);
