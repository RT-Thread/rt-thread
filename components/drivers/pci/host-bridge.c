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

#include <drivers/pci.h>

static rt_err_t host_bridge_probe(struct rt_pci_device *pdev)
{
    rt_err_t err = -RT_EINVAL;

    if (pdev->class >> 8 == PCIS_BRIDGE_HOST)
    {
        err = RT_EOK;
    }

    return err;
}

static const struct rt_pci_device_id host_bridge_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0008) },
    { /* sentinel */ }
};

static struct rt_pci_driver host_bridge_driver =
{
    .name = "host-bridge",

    .ids = host_bridge_pci_ids,
    .probe = host_bridge_probe,
};
RT_PCI_DRIVER_EXPORT(host_bridge_driver);
