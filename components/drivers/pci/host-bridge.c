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
 * @file host-bridge.c
 * @brief PCI Host Bridge Driver
 *
 * This driver handles the PCI host bridge itself as a PCI device.
 * It manages bus mastering, optional power management for the entire
 * PCI hierarchy under this bridge (suspend/resume via PME# signals),
 * and matches against standard PCI-to-PCI bridge class codes.
 */

#include <rtthread.h>

#include <drivers/pm.h>
#include <drivers/pci.h>

#ifdef RT_USING_PM

/**
 * @brief Runtime PM status passed to enumeration callback
 */
struct host_bridge_pm_status
{
    rt_uint8_t mode;    /**< Target sleep mode */
    rt_bool_t enable;   /**< RT_TRUE for resume (enable wake), RT_FALSE for suspend (disable wake) */
};

/**
 * @brief Mapping from system sleep modes to PCI power states
 *
 * Determines which PCI power state each system sleep mode targets:
 * - NONE    → D0   (fully operational)
 * - IDLE    → D3hot (light sleep)
 * - LIGHT   → D1   (medium sleep)
 * - DEEP    → D1
 * - STANDBY → D2
 * - SHUTDOWN→ D3cold
 */
static const enum rt_pci_power system_pci_pm_mode[] =
{
    [PM_SLEEP_MODE_NONE]        = RT_PCI_D0,
    [PM_SLEEP_MODE_IDLE]        = RT_PCI_D3HOT,
    [PM_SLEEP_MODE_LIGHT]       = RT_PCI_D1,
    [PM_SLEEP_MODE_DEEP]        = RT_PCI_D1,
    [PM_SLEEP_MODE_STANDBY]     = RT_PCI_D2,
    [PM_SLEEP_MODE_SHUTDOWN]    = RT_PCI_D3COLD,
};

/**
 * @brief PM enumeration callback for each PCI device
 *
 * Enables or disables wake (PME#) on every device in the hierarchy.
 * Always returns RT_FALSE to continue enumeration through all devices.
 *
 * @param[in] pdev PCI device being visited
 * @param[in] data Pointer to host_bridge_pm_status struct
 * @return Always RT_FALSE (continue enumeration)
 */
static rt_bool_t pci_device_pm_ops(struct rt_pci_device *pdev, void *data)
{
    struct host_bridge_pm_status *status = data;

    rt_pci_enable_wake(pdev, system_pci_pm_mode[status->mode], status->enable);

    /* To find all devices, always return false */
    return RT_FALSE;
}

/**
 * @brief Suspend all PCI devices under this host bridge
 *
 * Disables PME# wake for all devices in the hierarchy.
 *
 * @param[in] device PCI host bridge device
 * @param[in] mode   Target sleep mode
 * @return RT_EOK
 */
static rt_err_t host_bridge_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    struct host_bridge_pm_status status;
    struct rt_pci_device *pdev = rt_container_of(device, struct rt_pci_device, parent);

    status.mode = mode;
    status.enable = RT_FALSE;
    rt_pci_enum_device(pdev->bus, pci_device_pm_ops, &status);

    return RT_EOK;
}

/**
 * @brief Resume all PCI devices under this host bridge
 *
 * Re-enables PME# wake for all devices in the hierarchy.
 *
 * @param[in] device PCI host bridge device
 * @param[in] mode   Sleep mode being exited
 */
static void host_bridge_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    struct host_bridge_pm_status status;
    struct rt_pci_device *pdev = rt_container_of(device, struct rt_pci_device, parent);

    status.mode = mode;
    status.enable = RT_TRUE;
    rt_pci_enum_device(pdev->bus, pci_device_pm_ops, &status);
}

/** @brief PM operations vtable for host bridge */
static const struct rt_device_pm_ops host_bridge_pm_ops =
{
    .suspend = host_bridge_pm_suspend,
    .resume = host_bridge_pm_resume,
};
#endif /* RT_USING_PM */

/**
 * @brief Free host bridge PM resources
 *
 * @param[in] pdev PCI host bridge device
 */
static void host_bridge_free(struct rt_pci_device *pdev)
{
#ifdef RT_USING_PM
    rt_pm_device_unregister(&pdev->parent);
#endif
}

/**
 * @brief Probe a host bridge PCI device
 *
 * Enables bus mastering so the bridge can forward DMA transactions,
 * and registers the device with the power management framework.
 *
 * @param[in] pdev PCI host bridge device
 * @return RT_EOK on success
 */
static rt_err_t host_bridge_probe(struct rt_pci_device *pdev)
{
    rt_err_t err = RT_EOK;

    rt_pci_set_master(pdev);

#ifdef RT_USING_PM
    rt_pm_device_register(&pdev->parent, &host_bridge_pm_ops);
#endif

    return err;
}

/**
 * @brief Remove a host bridge PCI device
 *
 * Disables bus mastering and frees PM resources.
 *
 * @param[in] pdev PCI host bridge device
 * @return RT_EOK
 */
static rt_err_t host_bridge_remove(struct rt_pci_device *pdev)
{
    host_bridge_free(pdev);
    rt_pci_clear_master(pdev);

    return RT_EOK;
}

/**
 * @brief Shutdown a host bridge PCI device
 *
 * @param[in] pdev PCI host bridge device
 * @return RT_EOK
 */
static rt_err_t host_bridge_shutdown(struct rt_pci_device *pdev)
{
    host_bridge_free(pdev);

    return RT_EOK;
}

/**
 * @brief Device ID table for matching host bridges
 *
 * Matches:
 * - Red Hat PCI host bridge (vendor 0x1b36, device 0x0008)
 * - Any standard PCI Express port (class PCIS_BRIDGE_PCI_NORMAL)
 * - Any subtractive PCI-to-PCI bridge (class PCIS_BRIDGE_PCI_SUBTRACTIVE)
 * - Any Root Complex Event Collector (class PCIS_SYSTEM_RCEC)
 */
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

/** @brief Host bridge PCI driver descriptor */
static struct rt_pci_driver host_bridge_driver =
{
    .name = "host-bridge",

    .ids = host_bridge_pci_ids,
    .probe = host_bridge_probe,
    .remove = host_bridge_remove,
    .shutdown = host_bridge_shutdown,
};
RT_PCI_DRIVER_EXPORT(host_bridge_driver);
