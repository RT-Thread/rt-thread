/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

/**
 * @file pci-host-common.c
 * @brief Common PCI host controller probe/remove logic
 *
 * Provides a shared probe sequence for ECAM-based PCI host controllers:
 * 1. Allocate host bridge
 * 2. IOMap the ECAM configuration space window
 * 3. Parse device tree properties (bus-range, ranges, domain)
 * 4. Create ECAM config window
 * 5. Probe the host bridge (register root bus + scan)
 */

#include <rtthread.h>

#include "../ecam.h"

/**
 * @brief Common probe function for ECAM-based PCI host controllers
 *
 * Maps the config space MMIO region, initializes the host bridge
 * from device tree data, creates an ECAM configuration window,
 * and probes the PCI hierarchy.
 *
 * @param[in] pdev Platform device representing the PCI host controller
 * @return RT_EOK on success, error code otherwise
 */
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

/**
 * @brief Common remove function for ECAM-based PCI host controllers
 *
 * Removes the host bridge and all enumerated devices, unmaps the
 * ECAM window, and frees the host bridge.
 *
 * @param[in] pdev Platform device to remove
 * @return RT_EOK
 */
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
