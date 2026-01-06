/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     GuEe-GUI     first version
 */

#include <rtthread.h>

#include "8250.h"

struct ofw_platform_8250
{
    struct serial8250 parent;

    struct rt_reset_control *rstc;
};

#define to_ofw_platform_8250(serial8250) rt_container_of(serial8250, struct ofw_platform_8250, parent)

static void ofw_platform_8250_free_resource(struct ofw_platform_8250 *op8250)
{
    struct serial8250 *serial = &op8250->parent;

    if (serial->base)
    {
        rt_iounmap(serial->base);
    }

    if (!rt_is_err_or_null(serial->clk))
    {
        rt_clk_disable_unprepare(serial->clk);
        rt_clk_put(serial->clk);
    }

    if (!rt_is_err_or_null(op8250->rstc))
    {
        rt_reset_control_put(op8250->rstc);
    }

    rt_free(op8250);
}

static void op8250_remove(struct serial8250 *serial)
{
    struct ofw_platform_8250 *op8250 = to_ofw_platform_8250(serial);

    ofw_platform_8250_free_resource(op8250);
}

static rt_err_t ofw_platform_8250_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t val;
    struct serial8250 *serial;
    struct ofw_platform_8250 *op8250;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (rt_ofw_prop_read_bool(np, "used-by-rtas"))
    {
        return -RT_EBUSY;
    }

    op8250 = serial8250_alloc(op8250);

    if (!op8250)
    {
        return -RT_ENOMEM;
    }

    serial = &op8250->parent;
    serial->base = rt_ofw_iomap(np, 0);

    if (!serial->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    serial->irq = rt_ofw_get_irq(np, 0);

    if (serial->irq < 0)
    {
        err = serial->irq;

        goto _fail;
    }

    if (!rt_ofw_prop_read_u32(np, "clock-frequency", &val))
    {
        serial->freq = val;
    }
    else
    {
        serial->clk = rt_ofw_get_clk(np, 0);

        if (rt_is_err(serial->clk))
        {
            err = rt_ptr_err(serial->clk);
            goto _fail;
        }

        if ((err = rt_clk_prepare_enable(serial->clk)))
        {
            goto _fail;
        }

        serial->freq = rt_clk_get_rate(serial->clk);
    }

    if (!rt_ofw_prop_read_u32(np, "reg-shift", &val))
    {
        serial->regshift = val;
    }

    serial->iotype = PORT_MMIO;
    if (!rt_ofw_prop_read_u32(np, "reg-io-width", &val))
    {
        switch (val)
        {
        case 1:
            serial->iotype = PORT_MMIO;
            break;

        case 2:
            serial->iotype = PORT_MMIO16;
            break;

        case 4:
            serial->iotype = rt_ofw_prop_read_bool(np, "big-endian") ?
                    PORT_MMIO32BE : PORT_MMIO32;
            break;
        }
    }

    op8250->rstc = rt_ofw_get_reset_control_by_index(np, 0);

    if (rt_is_err(op8250->rstc))
    {
        err = rt_ptr_err(op8250->rstc);
        goto _fail;
    }

    if (op8250->rstc && (err = rt_reset_control_deassert(op8250->rstc)))
    {
        goto _fail;
    }

    rt_dm_dev_bind_fwdata(&serial->parent.parent, pdev->parent.ofw_node, &serial->parent);

    pdev->parent.user_data = serial;

    serial->parent.ops = &serial8250_uart_ops;
    serial->parent.config = config;
    serial->remove = &op8250_remove;
    serial->data = op8250;

    if ((err = serial8250_setup(serial)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    ofw_platform_8250_free_resource(op8250);

    return err;
}

static rt_err_t ofw_platform_8250_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct serial8250 *serial = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    return serial8250_remove(serial);
}

static const struct rt_ofw_node_id ofw_platform_8250_ofw_ids[] =
{
    { .type = "ttyS", .compatible = "ns16550a" },
    { .type = "ttyS", .compatible = "ns16550" },
#ifndef RT_SERIAL_8250_BCM7271
    { .type = "ttyS", .compatible = "brcm,bcm7271-uart" },
#endif
    { /* sentinel */ }
};

static struct rt_platform_driver ofw_platform_8250_driver =
{
    .name = "8250-ofw",
    .ids = ofw_platform_8250_ofw_ids,

    .probe = ofw_platform_8250_probe,
    .remove = ofw_platform_8250_remove,
};

static int ofw_platform_8250_drv_register(void)
{
    rt_platform_driver_register(&ofw_platform_8250_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(ofw_platform_8250_drv_register);
