/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <rtthread.h>

#include "../ecam.h"

rt_err_t pci_host_common_probe(struct rt_platform_device *pdev)
{
    void *base;
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct pci_ecam_config_window *conf_win;
    struct rt_pci_host_bridge *host_bridge = rt_pci_host_bridge_alloc(0);

    if (!host_bridge)
    {
        return -RT_ENOMEM;
    }

    if (!(base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    host_bridge->parent.ofw_node = dev->ofw_node;

    if ((err = rt_pci_host_bridge_init(host_bridge)))
    {
        goto _fail;
    }

    host_bridge->sysdata = conf_win = pci_ecam_create(host_bridge,
            (const struct pci_ecam_ops *)pdev->id->data);

    if (!conf_win)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    conf_win->win = base;
    conf_win->priv = host_bridge;

    if ((err = rt_pci_host_bridge_probe(host_bridge)))
    {
        goto _fail;
    }

    dev->user_data = host_bridge;

    return RT_EOK;

_fail:
    if (base)
    {
        rt_iounmap(base);
    }
    rt_pci_host_bridge_free(host_bridge);

    return err;
}

rt_err_t pci_host_common_remove(struct rt_platform_device *pdev)
{
    struct pci_ecam_config_window *conf_win;
    struct rt_pci_host_bridge *host_bridge = pdev->parent.user_data;

    rt_pci_host_bridge_remove(host_bridge);

    conf_win = host_bridge->sysdata;

    rt_iounmap(conf_win->win);
    rt_pci_host_bridge_free(host_bridge);

    return RT_EOK;
}
