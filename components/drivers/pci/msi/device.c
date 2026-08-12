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
 * @file device.c
 * @brief MSI/MSI-X capability initialization and discovery
 *
 * Initializes (and disables) MSI and MSI-X capabilities for a newly
 * probed PCI device. The capabilities are discovered via the PCI
 * capability linked list and disabled as a safe default state.
 * Drivers must explicitly enable MSI/MSI-X when needed.
 */

#include <drivers/pci.h>

/**
 * @brief Initialize the MSI capability for a device (disable MSI)
 *
 * Finds the MSI capability (PCIY_MSI), checks if MSI is currently
 * enabled (left over from firmware), and disables it. Also records
 * whether the device supports 64-bit MSI addresses.
 *
 * @param[in] pdev PCI device (msi_cap and no_64bit_msi fields updated)
 */
void rt_pci_msi_init(struct rt_pci_device *pdev)
{
    if (pdev && (pdev->msi_cap = rt_pci_find_capability(pdev, PCIY_MSI)))
    {
        rt_uint16_t ctrl;

        rt_pci_read_config_u16(pdev, pdev->msi_cap + PCIR_MSI_CTRL, &ctrl);

        if (ctrl & PCIM_MSICTRL_MSI_ENABLE)
        {
            rt_pci_write_config_u16(pdev, pdev->msi_cap + PCIR_MSI_CTRL, ctrl & ~PCIM_MSICTRL_MSI_ENABLE);
        }

        if (!(ctrl & PCIM_MSICTRL_64BIT))
        {
            pdev->no_64bit_msi = RT_TRUE;
        }
    }
}

/**
 * @brief Initialize the MSI-X capability for a device (disable MSI-X)
 *
 * Finds the MSI-X capability (PCIY_MSIX), checks if MSI-X is currently
 * enabled (left over from firmware), and disables it.
 *
 * @param[in] pdev PCI device (msix_cap field updated)
 */
void rt_pci_msix_init(struct rt_pci_device *pdev)
{
    if (pdev && (pdev->msix_cap = rt_pci_find_capability(pdev, PCIY_MSIX)))
    {
        rt_uint16_t ctrl;

        rt_pci_read_config_u16(pdev, pdev->msix_cap + PCIR_MSIX_CTRL, &ctrl);

        if (ctrl & PCIM_MSIXCTRL_MSIX_ENABLE)
        {
            rt_pci_write_config_u16(pdev, pdev->msix_cap + PCIR_MSIX_CTRL, ctrl & ~PCIM_MSIXCTRL_MSIX_ENABLE);
        }
    }
}
