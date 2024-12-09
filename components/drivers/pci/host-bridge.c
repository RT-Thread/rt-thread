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

#include <drivers/pm.h>
#include <drivers/pci.h>

#ifdef RT_USING_PM
struct host_bridge_pm_status
{
    rt_uint8_t mode;
    rt_bool_t enable;
};

static const enum rt_pci_power system_pci_pm_mode[] =
{
    [PM_SLEEP_MODE_NONE]        = RT_PCI_D0,
    [PM_SLEEP_MODE_IDLE]        = RT_PCI_D3HOT,
    [PM_SLEEP_MODE_LIGHT]       = RT_PCI_D1,
    [PM_SLEEP_MODE_DEEP]        = RT_PCI_D1,
    [PM_SLEEP_MODE_STANDBY]     = RT_PCI_D2,
    [PM_SLEEP_MODE_SHUTDOWN]    = RT_PCI_D3COLD,
};

static rt_bool_t pci_device_pm_ops(struct rt_pci_device *pdev, void *data)
{
    struct host_bridge_pm_status *status = data;

    rt_pci_enable_wake(pdev, system_pci_pm_mode[status->mode], status->enable);

    /* To find all devices, always return false */
    return RT_FALSE;
}

static rt_err_t host_bridge_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    struct host_bridge_pm_status status;
    struct rt_pci_device *pdev = rt_container_of(device, struct rt_pci_device, parent);

    status.mode = mode;
    status.enable = RT_FALSE;
    rt_pci_enum_device(pdev->bus, pci_device_pm_ops, &status);

    return RT_EOK;
}

static void host_bridge_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    struct host_bridge_pm_status status;
    struct rt_pci_device *pdev = rt_container_of(device, struct rt_pci_device, parent);

    status.mode = mode;
    status.enable = RT_TRUE;
    rt_pci_enum_device(pdev->bus, pci_device_pm_ops, &status);
}

static const struct rt_device_pm_ops host_bridge_pm_ops =
{
    .suspend = host_bridge_pm_suspend,
    .resume = host_bridge_pm_resume,
};
#endif /* RT_USING_PM */

static void host_bridge_free(struct rt_pci_device *pdev)
{
#ifdef RT_USING_PM
    rt_pm_device_unregister(&pdev->parent);
#endif
}

static rt_err_t host_bridge_probe(struct rt_pci_device *pdev)
{
    rt_err_t err = RT_EOK;

    rt_pci_set_master(pdev);

#ifdef RT_USING_PM
    rt_pm_device_register(&pdev->parent, &host_bridge_pm_ops);
#endif

    return err;
}

static rt_err_t host_bridge_remove(struct rt_pci_device *pdev)
{
    host_bridge_free(pdev);
    rt_pci_clear_master(pdev);

    return RT_EOK;
}

static rt_err_t host_bridge_shutdown(struct rt_pci_device *pdev)
{
    host_bridge_free(pdev);

    return RT_EOK;
}

static const struct rt_pci_device_id host_bridge_pci_ids[] =
{
    /* PCI host bridges */
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0008) },
    /* Any PCI-Express port */
    { RT_PCI_DEVICE_CLASS(PCIS_BRIDGE_PCI_NORMAL, ~0) },
    /* PCI-to-PCI bridge */
    { RT_PCI_DEVICE_CLASS(PCIS_BRIDGE_PCI_SUBTRACTIVE, ~0) },
    /* Any Root Complex Event Collector */
    { RT_PCI_DEVICE_CLASS(((PCIS_SYSTEM_RCEC << 8) | 0x00), ~0) },
    { /* sentinel */ }
};

static struct rt_pci_driver host_bridge_driver =
{
    .name = "host-bridge",

    .ids = host_bridge_pci_ids,
    .probe = host_bridge_probe,
    .remove = host_bridge_remove,
    .shutdown = host_bridge_shutdown,
};
RT_PCI_DRIVER_EXPORT(host_bridge_driver);
