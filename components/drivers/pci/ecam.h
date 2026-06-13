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
 * @file ecam.h
 * @brief PCI Express ECAM (Enhanced Configuration Access Mechanism) definitions
 *
 * PCI Express Base Specification, Revision 5.0, Section 7.2.2 defines
 * the ECAM addressing scheme for mapping configuration space into
 * memory-mapped I/O regions.
 *
 * Standard ECAM layout:
 * - Bus Number:  bits [27:20]  (256 buses)
 * - Device Num:  bits [19:15]  (32 devices)
 * - Function:    bits [14:12]  (8 functions)
 * - Register:    bits [11:0]   (4KB config space)
 */

#ifndef __RT_PCI_ECAM_H__
#define __RT_PCI_ECAM_H__

#include <drivers/pci.h>
#include <drivers/ofw.h>
#include <drivers/ofw_io.h>
#include <drivers/platform.h>

/** @brief Bus number shift in ECAM address (20 bits for PCIe) */
#define PCIE_ECAM_BUS_SHIFT     20
/** @brief Device/Function number shift in ECAM address */
#define PCIE_ECAM_DEVFN_SHIFT   12

/** @brief Mask for bus number field (8 bits, 256 buses) */
#define PCIE_ECAM_BUS_MASK      0xff
/** @brief Mask for device/function field (8 bits, 32 dev × 8 func) */
#define PCIE_ECAM_DEVFN_MASK    0xff
/** @brief Mask for register offset (12 bits, 4KB max) */
#define PCIE_ECAM_REG_MASK      0xfff

/** @brief Extract bus portion of ECAM address */
#define PCIE_ECAM_BUS(x)        (((x) & PCIE_ECAM_BUS_MASK) << PCIE_ECAM_BUS_SHIFT)
/** @brief Extract devfn portion of ECAM address */
#define PCIE_ECAM_DEVFN(x)      (((x) & PCIE_ECAM_DEVFN_MASK) << PCIE_ECAM_DEVFN_SHIFT)
/** @brief Extract register portion of ECAM address */
#define PCIE_ECAM_REG(x)        ((x) & PCIE_ECAM_REG_MASK)

/** @brief Compute full ECAM MMIO offset from bus, devfn, and register */
#define PCIE_ECAM_OFFSET(bus, devfn, where) \
        (PCIE_ECAM_BUS(bus) |  PCIE_ECAM_DEVFN(devfn) | PCIE_ECAM_REG(where))

/**
 * @brief ECAM operations descriptor
 *
 * Each ECAM variant may have a different bus_shift.
 * - Standard ECAM: bus_shift = 20
 * - CAM (legacy PCI): bus_shift = 16
 */
struct pci_ecam_ops
{
    rt_uint32_t bus_shift;           /**< Bus number shift for address calculation */
    const struct rt_pci_ops pci_ops; /**< PCI bus operations (map, read, write) */
};

/**
 * @brief ECAM configuration window instance
 *
 * Represents one ECAM memory window covering a bus range.
 * The window maps a contiguous MMIO region to the configuration
 * space of all devices on the buses in bus_range.
 */
struct pci_ecam_config_window
{
    rt_uint32_t *bus_range;          /**< [start_bus, end_bus] for this window */
    rt_uint32_t bus_shift;           /**< Bus number shift (20 for ECAM, 16 for CAM) */

    void *win;                       /**< Virtual base address of the ECAM MMIO window */
    void *priv;                      /**< Private data (typically the host bridge) */
    const struct pci_ecam_ops *ops;  /**< ECAM operations (bus_shift + pci_ops) */
};

/** @brief Standard ECAM operations (20-bit bus shift, direct MMIO) */
extern const struct pci_ecam_ops pci_generic_ecam_ops;

/** @brief Map a PCI config space register to a virtual address via ECAM */
void *pci_ecam_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int where);

/** @brief Create an ECAM configuration window and attach it to a host bridge */
struct pci_ecam_config_window *pci_ecam_create(struct rt_pci_host_bridge *host_bridge,
        const struct pci_ecam_ops *ops);

/** @brief Common probe function for ECAM-based PCI host controllers */
rt_err_t pci_host_common_probe(struct rt_platform_device *pdev);

/** @brief Common remove function for ECAM-based PCI host controllers */
rt_err_t pci_host_common_remove(struct rt_platform_device *pdev);

#endif /* __RT_PCI_ECAM_H__ */
