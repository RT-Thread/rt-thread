/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/serial_dm.h>

#include <cpuport.h>
#include "8250/8250.h"

#define UART_XMIT_SIZE          RT_DMA_PAGE_SIZE
#define DMA_BLOCK               UART_XMIT_SIZE
#define DMA_BURST_SIZE          8

struct serial_pxa
{
    struct serial8250 parent;

    rt_bool_t device_ctrl_rts;

    struct rt_dma_slave_config rx_config;
    struct rt_dma_slave_config tx_config;
    struct rt_dma_slave_transfer rx_transfer;
    struct rt_dma_slave_transfer tx_transfer;

    struct rt_dma_chan *dma_rx;
    struct rt_dma_chan *dma_tx;

    struct rt_clk *fclk;
    struct rt_clk *gclk;
    struct rt_reset_control *rstc;
};

#define raw_to_serial_pxa(raw) rt_container_of(raw, struct serial_pxa, parent)

static rt_err_t serial_pxa_isr(struct serial8250 *serial, int irq)
{
    rt_uint8_t iir;
    rt_uint32_t ier;

    while (!((iir = serial->serial_in(serial, UART_IIR)) & UART_IIR_NO_INT))
    {
        switch (iir & UART_IIR_ID)
        {
        /* RX data available */
        case UART_IIR_RDI:
        /* RX timeout pending */
        case UART_IIR_RX_TIMEOUT:
            while (serial->serial_in(serial, UART_LSR) & UART_LSR_DR)
            {
                rt_hw_serial_isr(&serial->parent, RT_SERIAL_EVENT_RX_IND);
            }
            break;

        /* TX holding register empty */
        case UART_IIR_THRI:
            ier = serial->serial_in(serial, UART_IER);
            ier &= ~UART_IER_THRI; /* Disable THRI */
            serial->serial_out(serial, UART_IER, ier);
            break;

        /* Line status */
        case UART_IIR_RLSI:
            /* Read to clear */
            serial->serial_in(serial, UART_LSR);
            break;
        }
    }

    return RT_EOK;
}

static rt_err_t serial_pxa_dma_enable(struct serial8250 *serial, rt_bool_t enabled)
{
    struct serial_pxa *pxa = raw_to_serial_pxa(serial);

    if (enabled)
    {
        rt_dma_chan_pause(pxa->dma_rx);
        rt_dma_chan_pause(pxa->dma_tx);
    }
    else
    {
        rt_dma_chan_stop(pxa->dma_rx);
        rt_dma_chan_stop(pxa->dma_tx);
    }

    return RT_EOK;
}

static rt_ssize_t serial_pxa_dma_tx(struct serial8250 *serial, const rt_uint8_t *buf, rt_size_t size)
{
    rt_err_t err;
    struct serial_pxa *pxa = raw_to_serial_pxa(serial);

    pxa->tx_config.src_addr = (rt_ubase_t)rt_kmem_v2p((void *)buf);

    if ((err = rt_dma_chan_config(pxa->dma_tx, &pxa->tx_config)))
    {
        return err;
    }

    pxa->tx_transfer.buffer_len = size;
    pxa->tx_transfer.src_addr = pxa->tx_config.src_addr;

    if ((err = rt_dma_prep_single(pxa->dma_tx, &pxa->tx_transfer)))
    {
        return err;
    }

    if ((err = rt_dma_chan_start(pxa->dma_tx)))
    {
        return err;
    }

    return size;
}

static rt_ssize_t serial_pxa_dma_rx(struct serial8250 *serial, rt_uint8_t *buf, rt_size_t size)
{
    rt_err_t err;
    struct serial_pxa *pxa = raw_to_serial_pxa(serial);

    pxa->rx_config.dst_addr = (rt_ubase_t)rt_kmem_v2p(buf);

    if ((err = rt_dma_chan_config(pxa->dma_rx, &pxa->rx_config)))
    {
        return err;
    }

    pxa->rx_transfer.buffer_len = size;
    pxa->rx_transfer.dst_addr = pxa->rx_config.dst_addr;

    if ((err = rt_dma_prep_single(pxa->dma_rx, &pxa->rx_transfer)))
    {
        return err;
    }

    if ((err = rt_dma_chan_start(pxa->dma_rx)))
    {
        return err;
    }

    return size;
}

static rt_err_t serial_pxa_early_setup(struct rt_fdt_earlycon *con, const char *options)
{
    struct serial8250 *serial = &early_serial8250;

    serial->base = (void *)con->mmio;
    serial->size = con->size;
    serial->iotype = PORT_MMIO32;
    serial->regshift = 2;
    fdt_getprop_u32(con->fdt, con->nodeoffset, "reg-shift", &serial->regshift, RT_NULL);

    return serial8250_early_fdt_setup(serial, con, options);
}
RT_FDT_EARLYCON_EXPORT(serial_pxa, "uart8250", "spacemit,pxa-uart", serial_pxa_early_setup);

static void serial_pxa_8250_remove(struct serial8250 *serial)
{
    struct serial_pxa *pxa = rt_container_of(serial, struct serial_pxa, parent);

    if (serial->base)
    {
        rt_iounmap(serial->base);
    }

    if (!rt_is_err_or_null(pxa->rstc))
    {
        rt_reset_control_assert(pxa->rstc);
        rt_reset_control_put(pxa->rstc);
    }

    if (!rt_is_err_or_null(pxa->fclk))
    {
        rt_clk_unprepare(pxa->fclk);
        rt_clk_put(pxa->fclk);
    }

    if (!rt_is_err_or_null(pxa->gclk))
    {
        rt_clk_unprepare(pxa->gclk);
        rt_clk_put(pxa->gclk);
    }

    if (!rt_is_err_or_null(pxa->dma_tx))
    {
        rt_dma_chan_release(pxa->dma_tx);
    }

    if (!rt_is_err_or_null(pxa->dma_rx))
    {
        rt_dma_chan_release(pxa->dma_rx);
    }

    rt_free(pxa);
}

static rt_err_t serial_pxa_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_ubase_t fifo_addr_phys;
    struct serial8250 *serial;
    struct rt_device *dev = &pdev->parent;
    struct serial_pxa *pxa = serial8250_alloc(pxa);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (!pxa)
    {
        return -RT_ENOMEM;
    }
    serial = &pxa->parent;

    serial->base = rt_dm_dev_iomap(dev, 0);
    if (!serial->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    serial->irq = rt_dm_dev_get_irq(dev, 0);
    if (serial->irq < 0)
    {
        err = serial->irq;
        goto _fail;
    }

    pxa->gclk = rt_clk_get_by_name(dev, "gate");
    if (rt_is_err(pxa->gclk))
    {
        err = rt_ptr_err(pxa->gclk);
        goto _fail;
    }

    pxa->fclk = rt_clk_get_by_name(dev, "func");
    if (rt_is_err(pxa->fclk))
    {
        err = rt_ptr_err(pxa->fclk);
        goto _fail;
    }

    if ((err = rt_clk_prepare(pxa->gclk)))
    {
        goto _fail;
    }

    if ((err = rt_clk_prepare(pxa->fclk)))
    {
        goto _fail;
    }

    pxa->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(pxa->rstc))
    {
        err = rt_ptr_err(pxa->rstc);
        goto _fail;
    }
    rt_reset_control_deassert(pxa->rstc);

    fifo_addr_phys = (rt_ubase_t)rt_kmem_v2p(serial->base);
    pxa->device_ctrl_rts = rt_dm_dev_prop_read_bool(dev, "device-control-rts");

    pxa->dma_tx = rt_dma_chan_request(dev, "tx");

    if (!rt_is_err_or_null(pxa->dma_tx))
    {
        pxa->tx_config.dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_1_BYTE;
        pxa->tx_config.dst_maxburst = DMA_BURST_SIZE;
        pxa->tx_config.direction = RT_DMA_MEM_TO_DEV;
        pxa->tx_config.dst_addr = fifo_addr_phys;

        pxa->tx_transfer.dst_addr = pxa->tx_config.dst_addr;
    }

    pxa->dma_rx = rt_dma_chan_request(dev, "rx");

    if (!rt_is_err_or_null(pxa->dma_rx))
    {
        pxa->rx_config.src_addr_width = RT_DMA_SLAVE_BUSWIDTH_1_BYTE;
        pxa->rx_config.src_maxburst = DMA_BURST_SIZE;
        pxa->rx_config.direction = RT_DMA_MEM_TO_DEV;
        pxa->rx_config.src_addr = fifo_addr_phys;

        pxa->rx_transfer.src_addr = pxa->rx_config.src_addr;
    }

    serial->clk = pxa->fclk;
    serial->freq = rt_clk_get_rate(pxa->fclk);
    serial->regshift = 2;
    serial->iotype = PORT_MMIO32;
    serial->parent.ops = &serial8250_uart_ops;
    serial->parent.config = config;
    serial->handle_irq = serial_pxa_isr;
    serial->remove = serial_pxa_8250_remove;
    if (!rt_is_err_or_null(pxa->dma_rx) && !rt_is_err_or_null(pxa->dma_tx))
    {
        serial->serial_dma_enable = serial_pxa_dma_enable;
        serial->serial_dma_tx = serial_pxa_dma_tx;
        serial->serial_dma_rx = serial_pxa_dma_rx;
    }
    serial->data = dev;

    if ((err = serial8250_setup(serial)))
    {
        goto _fail;
    }

    rt_dm_dev_bind_fwdata(&serial->parent.parent, dev->ofw_node, &serial->parent);

    dev->user_data = pxa;

    return RT_EOK;

_fail:
    pxa->parent.data = dev;
    serial_pxa_8250_remove(&pxa->parent);

    return err;
}

static rt_err_t serial_pxa_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct serial8250 *serial = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    return serial8250_remove(serial);
}

static const struct rt_ofw_node_id serial_pxa_ofw_ids[] =
{
    { .type = "ttyS", .compatible = "spacemit,pxa-uart" },
    { /* sentinel */ }
};

static struct rt_platform_driver serial_pxa_driver =
{
    .name = "serial-pxa",
    .ids = serial_pxa_ofw_ids,

    .probe = serial_pxa_probe,
    .remove = serial_pxa_remove,
};

static int serial_pxa_drv_register(void)
{
    rt_platform_driver_register(&serial_pxa_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(serial_pxa_drv_register);
