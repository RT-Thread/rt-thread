/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <drivers/pci.h>

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
