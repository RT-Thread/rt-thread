/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-16     GuEe-GUI     first version
 */

#include <rtthread.h>

#include "8250.h"

#define BCM2835_AUX_UART_CNTL           8
#define BCM2835_AUX_UART_CNTL_RXEN      0x01 /* Receiver enable */
#define BCM2835_AUX_UART_CNTL_TXEN      0x02 /* Transmitter enable */
#define BCM2835_AUX_UART_CNTL_AUTORTS   0x04 /* RTS set by RX fill level */
#define BCM2835_AUX_UART_CNTL_AUTOCTS   0x08 /* CTS stops transmitter */
#define BCM2835_AUX_UART_CNTL_RTS3      0x00 /* RTS set until 3 chars left */
#define BCM2835_AUX_UART_CNTL_RTS2      0x10 /* RTS set until 2 chars left */
#define BCM2835_AUX_UART_CNTL_RTS1      0x20 /* RTS set until 1 chars left */
#define BCM2835_AUX_UART_CNTL_RTS4      0x30 /* RTS set until 4 chars left */
#define BCM2835_AUX_UART_CNTL_RTSINV    0x40 /* Invert auto RTS polarity */
#define BCM2835_AUX_UART_CNTL_CTSINV    0x80 /* Invert auto CTS polarity */

struct bcm2835aux
{
    struct serial8250 parent;
    rt_uint32_t cntl;
};

#define to_bcm2835aux(serial8250) rt_container_of(serial8250, struct bcm2835aux, parent)

static void bcm2835aux_free_resource(struct bcm2835aux *bcm2835aux)
{
    struct serial8250 *serial = &bcm2835aux->parent;

    if (serial->base)
    {
        rt_iounmap(serial->base);
    }

    if (!rt_is_err_or_null(serial->clk))
    {
        rt_clk_disable_unprepare(serial->clk);
        rt_clk_put(serial->clk);
    }

    rt_free(bcm2835aux);
}

static void bcm2835aux_serial_remove(struct serial8250 *serial)
{
    struct bcm2835aux *bcm2835aux = to_bcm2835aux(serial);

    bcm2835aux_free_resource(bcm2835aux);
}

static rt_err_t bcm2835aux_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    struct serial8250 *serial;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835aux *bcm2835aux = serial8250_alloc(bcm2835aux);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (!bcm2835aux)
    {
        return -RT_ENOMEM;
    }

    serial = &bcm2835aux->parent;

    serial->base = rt_dm_dev_iomap(dev, 0);

    if (!serial->base)
    {
        err = -RT_ERROR;
        goto _free_res;
    }

    serial->irq = rt_dm_dev_get_irq(dev, 0);

    if (serial->irq < 0)
    {
        err = serial->irq;
        goto _free_res;
    }

    serial->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(serial->clk))
    {
        err = rt_ptr_err(serial->clk);
        goto _free_res;
    }

    if ((err = rt_clk_enable(serial->clk)))
    {
        goto _free_res;
    }

    serial->freq = rt_clk_get_rate(serial->clk);

    dev->user_data = serial;

    rt_dm_dev_bind_fwdata(&serial->parent.parent, pdev->parent.ofw_node, &serial->parent);

    serial->parent.ops = &serial8250_uart_ops;
    serial->parent.config = config;
    serial->regshift = 2;
    serial->iotype = PORT_MMIO;
    serial->remove = &bcm2835aux_serial_remove;
    serial->data = bcm2835aux;

    bcm2835aux->cntl = BCM2835_AUX_UART_CNTL_RXEN | BCM2835_AUX_UART_CNTL_TXEN;

    if ((err = serial8250_setup(serial)))
    {
        goto _free_res;
    }

    return RT_EOK;

_free_res:
    bcm2835aux_free_resource(bcm2835aux);

    return err;
}

static rt_err_t bcm2835aux_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct serial8250 *serial = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    return serial8250_remove(serial);
}

static const struct rt_ofw_node_id bcm2835aux_ofw_ids[] =
{
    { .type = "ttyS", .compatible = "brcm,bcm2835-aux-uart" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835aux_driver =
{
    .name = "bcm2835-aux-uart",
    .ids = bcm2835aux_ofw_ids,

    .probe = bcm2835aux_probe,
    .remove = bcm2835aux_remove,
};

static int bcm2835aux_drv_register(void)
{
    rt_platform_driver_register(&bcm2835aux_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(bcm2835aux_drv_register);
