/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#ifndef __RT_PCI_ECAM_H__
#define __RT_PCI_ECAM_H__

#include <drivers/pci.h>
#include <drivers/ofw.h>
#include <drivers/ofw_io.h>
#include <drivers/platform.h>

/*
 * Memory address shift values for the byte-level address that
 * can be used when accessing the PCI Express Configuration Space.
 */

/*
 * Enhanced Configuration Access Mechanism (ECAM)
 *
 * See PCI Express Base Specification, Revision 5.0, Version 1.0,
 * Section 7.2.2, Table 7-1, p. 677.
 */
#define PCIE_ECAM_BUS_SHIFT     20 /* Bus number */
#define PCIE_ECAM_DEVFN_SHIFT   12 /* Device and Function number */

#define PCIE_ECAM_BUS_MASK      0xff
#define PCIE_ECAM_DEVFN_MASK    0xff
#define PCIE_ECAM_REG_MASK      0xfff /* Limit offset to a maximum of 4K */

#define PCIE_ECAM_BUS(x)        (((x) & PCIE_ECAM_BUS_MASK) << PCIE_ECAM_BUS_SHIFT)
#define PCIE_ECAM_DEVFN(x)      (((x) & PCIE_ECAM_DEVFN_MASK) << PCIE_ECAM_DEVFN_SHIFT)
#define PCIE_ECAM_REG(x)        ((x) & PCIE_ECAM_REG_MASK)

#define PCIE_ECAM_OFFSET(bus, devfn, where) \
        (PCIE_ECAM_BUS(bus) |  PCIE_ECAM_DEVFN(devfn) | PCIE_ECAM_REG(where))

struct pci_ecam_ops
{
    rt_uint32_t bus_shift;
    const struct rt_pci_ops pci_ops;
};

struct pci_ecam_config_window
{
    rt_uint32_t *bus_range;
    rt_uint32_t bus_shift;

    void *win;
    void *priv;
    const struct pci_ecam_ops *ops;
};

/* Default ECAM ops */
extern const struct pci_ecam_ops pci_generic_ecam_ops;

void *pci_ecam_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int where);
struct pci_ecam_config_window *pci_ecam_create(struct rt_pci_host_bridge *host_bridge,
        const struct pci_ecam_ops *ops);
rt_err_t pci_host_common_probe(struct rt_platform_device *pdev);
rt_err_t pci_host_common_remove(struct rt_platform_device *pdev);

#endif /* __RT_PCI_ECAM_H__ */
