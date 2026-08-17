/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "dwmac-platform.h"

rt_err_t dwmac_platform_register(struct rt_platform_device *pdev,
        const struct dwmac_config *config)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct dwmac_eth *eth = rt_calloc(1, sizeof(*eth));

    if (!eth)
    {
        return -RT_ENOMEM;
    }

    eth->dev = dev;
    eth->config = config;

    eth->irq = rt_dm_dev_get_irq(dev, 0);
    eth->mac_base = rt_dm_dev_iomap(dev, 0);
    if (!eth->mac_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

#ifdef RT_USING_OFW
    if (rt_ofw_get_mac_addr(dev->ofw_node, eth->mac))
#endif
    {
        ethernet_random_addr(&eth->parent, eth->mac);
    }

    dev->user_data = eth;

    if ((err = dwmac_probe(eth)))
    {
        goto _fail_unmap;
    }

    return RT_EOK;

_fail_unmap:
    dev->user_data = RT_NULL;
    rt_iounmap(eth->mac_base);

_fail:
    rt_free(eth);

    return err;
}

rt_err_t dwmac_platform_remove(struct rt_platform_device *pdev)
{
    struct dwmac_eth *eth = pdev->parent.user_data;

    if (!eth)
    {
        return RT_EOK;
    }

    dwmac_remove(eth);
    rt_iounmap(eth->mac_base);
    rt_free(eth);
    pdev->parent.user_data = RT_NULL;

    return RT_EOK;
}
