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
 * @file pci-host-generic.c
 * @brief Generic PCI host controller driver
 *
 * Supports multiple ECAM-based PCI host controller implementations
 * via device tree compatible strings:
 * - "pci-host-cam-generic": CAM mode (16-bit bus shift, older PCI)
 * - "pci-host-ecam-generic": Standard ECAM (20-bit bus shift, PCIe)
 * - "marvell,armada8k-pcie-ecam": Marvell Armada 8K
 * - "socionext,synquacer-pcie-ecam": Socionext SynQuacer
 * - "snps,dw-pcie-ecam": Synopsys DesignWare PCIe in ECAM mode
 *
 * The DesignWare variants use a custom map function that restricts
 * access to device 0 on the root bus (slot > 0 returns NULL) because
 * the DW controller handles its own configuration differently.
 */

#include <rtthread.h>

#include "../ecam.h"

/** @brief CAM-mode ECAM ops with 16-bit bus shift for legacy PCI */
static const struct pci_ecam_ops gen_pci_cfg_cam_bus_ops =
{
    .bus_shift = 16,
    .pci_ops =
    {
        .map = pci_ecam_map,
        .read = rt_pci_bus_read_config_uxx,
        .write = rt_pci_bus_write_config_uxx,
    }
};

/**
 * @brief DesignWare-specific ECAM map: restrict root bus to device 0 only
 *
 * On DesignWare controllers, the DBI (Data Bus Interface) is used for
 * the host bridge's own configuration. ECAM should only be used for
 * devices behind the root port, not for the root port itself.
 *
 * @param[in] bus   PCI bus
 * @param[in] devfn Device/function number
 * @param[in] where Register offset
 * @return Virtual address, or RT_NULL if access is prohibited
 */
static void *pci_dw_ecam_map_bus(struct rt_pci_bus *bus, rt_uint32_t devfn, int where)
{
    struct pci_ecam_config_window *conf_win = bus->sysdata;

    if (bus->number == conf_win->bus_range[0] && RT_PCI_SLOT(devfn) > 0)
    {
        return RT_NULL;
    }

    return pci_ecam_map(bus, devfn, where);
}

/** @brief DesignWare ECAM ops (common across multiple DW-based SoCs) */
static const struct pci_ecam_ops pci_dw_ecam_bus_ops =
{
    .pci_ops =
    {
        .map = pci_dw_ecam_map_bus,
        .read = rt_pci_bus_read_config_uxx,
        .write = rt_pci_bus_write_config_uxx,
    }
};

/** @brief Device tree compatible IDs for supported PCI host controllers */
static const struct rt_ofw_node_id gen_pci_ofw_ids[] =
{
    { .compatible = "pci-host-cam-generic", .data = &gen_pci_cfg_cam_bus_ops },
    { .compatible = "pci-host-ecam-generic", .data = &pci_generic_ecam_ops },
    { .compatible = "marvell,armada8k-pcie-ecam", .data = &pci_dw_ecam_bus_ops },
    { .compatible = "socionext,synquacer-pcie-ecam", .data = &pci_dw_ecam_bus_ops },
    { .compatible = "snps,dw-pcie-ecam", .data = &pci_dw_ecam_bus_ops },
    { /* sentinel */ }
};

/** @brief Generic PCI host platform driver */
static struct rt_platform_driver gen_pci_driver =
{
    .name = "pci-host-generic",
    .ids = gen_pci_ofw_ids,

    .probe = pci_host_common_probe,
    .remove = pci_host_common_remove,
};
RT_PLATFORM_DRIVER_EXPORT(gen_pci_driver);
