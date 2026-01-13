/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include "sdio-dw-platform.h"

#include <mmu.h>

rt_err_t sdio_dw_platform_register(struct rt_platform_device *pdev,
        const struct sdio_dw_drv_data *drv_data)
{
    rt_err_t err = RT_EOK;
    struct rt_device *dev = &pdev->parent;
    struct sdio_dw *sd = rt_calloc(1, sizeof(*sd));

    if (!sd)
    {
        return -RT_ENOMEM;
    }

    sd->bus_dev = &pdev->parent;
    sd->base = rt_dm_dev_iomap(dev, 0);

    if (!sd->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    sd->irq = rt_dm_dev_get_irq(dev, 0);

    if (sd->irq < 0)
    {
        err = sd->irq;

        goto _fail;
    }

    sd->parent.ofw_node = dev->ofw_node;

    sd->base_phy = (rt_ubase_t)rt_kmem_v2p(sd->base);
    sd->drv_data = drv_data;

    pdev->parent.user_data = sd;

    if ((err = sdio_dw_probe(sd)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (sd->base)
    {
        rt_iounmap(sd->base);
    }

    rt_free(sd);

    return err;
}

static rt_err_t sdio_dw_platform_probe(struct rt_platform_device *pdev)
{
    const struct sdio_dw_drv_data *drv_data = RT_NULL;

    if (pdev->parent.ofw_node)
    {
        drv_data = pdev->id->data;
    }

    return sdio_dw_platform_register(pdev, drv_data);
}

static rt_err_t sdio_dw_platform_remove(struct rt_platform_device *pdev)
{
    struct sdio_dw *sd = pdev->parent.user_data;

    sdio_dw_remove(sd);

    rt_iounmap(sd->base);

    rt_free(sd);

    return RT_EOK;
}

static const struct rt_ofw_node_id sdio_dw_platform_ofw_ids[] =
{
    { .compatible = "snps,dw-mshc", },
    { .compatible = "img,pistachio-dw-mshc", },
    { /* sentinel */ }
};

static struct rt_platform_driver sdio_dw_platform_driver =
{
    .name = "dw-mmc",
    .ids = sdio_dw_platform_ofw_ids,

    .probe = sdio_dw_platform_probe,
    .remove = sdio_dw_platform_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sdio_dw_platform_driver);
