/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-07     GuEe-GUI     first version
 */

#ifndef __PCI_PROCFS_H__
#define __PCI_PROCFS_H__

#include <drivers/pci.h>

#ifdef RT_USING_DFS_PROCFS
#include <proc.h>

void pci_procfs_attach(struct rt_pci_device *pdev);
void pci_procfs_detach(struct rt_pci_device *pdev);
#else
rt_inline void pci_procfs_attach(struct rt_pci_device *pdev)
{
}

rt_inline void pci_procfs_detach(struct rt_pci_device *pdev)
{
}
#endif /* RT_USING_DFS_PROCFS */

#endif /* __PCI_PROCFS_H__ */
