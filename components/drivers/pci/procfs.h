/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-07     GuEe-GUI     first version
 */

/**
 * @file procfs.h
 * @brief PCI procfs interface declarations
 *
 * Provides /proc/pci/<BDF> per-device configuration space files
 * and /proc/pci/devices enumeration for userspace access.
 * When RT_USING_DFS_PROCFS is disabled, the attach/detach
 * functions are no-ops.
 */

#ifndef __PCI_PROCFS_H__
#define __PCI_PROCFS_H__

#include <drivers/pci.h>

#ifdef RT_USING_DFS_PROCFS
#include <proc.h>

/**
 * @brief Create /proc/pci/<BDF> entry for a PCI device
 *
 * @param[in] pdev  PCI device to attach
 */
void pci_procfs_attach(struct rt_pci_device *pdev);

/**
 * @brief Remove /proc/pci/<BDF> entry for a PCI device
 *
 * @param[in] pdev  PCI device to detach
 */
void pci_procfs_detach(struct rt_pci_device *pdev);
#else
/**
 * @brief No-op: create /proc/pci/<BDF> entry (procfs disabled)
 *
 * @param[in] pdev  PCI device
 */
rt_inline void pci_procfs_attach(struct rt_pci_device *pdev)
{
}

/**
 * @brief No-op: remove /proc/pci/<BDF> entry (procfs disabled)
 *
 * @param[in] pdev  PCI device
 */
rt_inline void pci_procfs_detach(struct rt_pci_device *pdev)
{
}
#endif /* RT_USING_DFS_PROCFS */

#endif /* __PCI_PROCFS_H__ */
