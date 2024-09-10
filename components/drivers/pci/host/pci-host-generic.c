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

#include "../ecam.h"

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

static void *pci_dw_ecam_map_bus(struct rt_pci_bus *bus, rt_uint32_t devfn, int where)
{
    struct pci_ecam_config_window *conf_win = bus->sysdata;

    if (bus->number == conf_win->bus_range[0] && RT_PCI_SLOT(devfn) > 0)
    {
        return RT_NULL;
    }

    return pci_ecam_map(bus, devfn, where);
}

static const struct pci_ecam_ops pci_dw_ecam_bus_ops =
{
    .pci_ops =
    {
        .map = pci_dw_ecam_map_bus,
        .read = rt_pci_bus_read_config_uxx,
        .write = rt_pci_bus_write_config_uxx,
    }
};

static const struct rt_ofw_node_id gen_pci_ofw_ids[] =
{
    { .compatible = "pci-host-cam-generic", .data = &gen_pci_cfg_cam_bus_ops },
    { .compatible = "pci-host-ecam-generic", .data = &pci_generic_ecam_ops },
    { .compatible = "marvell,armada8k-pcie-ecam", .data = &pci_dw_ecam_bus_ops },
    { .compatible = "socionext,synquacer-pcie-ecam", .data = &pci_dw_ecam_bus_ops },
    { .compatible = "snps,dw-pcie-ecam", .data = &pci_dw_ecam_bus_ops },
    { /* sentinel */ }
};

static struct rt_platform_driver gen_pci_driver =
{
    .name = "pci-host-generic",
    .ids = gen_pci_ofw_ids,

    .probe = pci_host_common_probe,
    .remove = pci_host_common_remove,
};
RT_PLATFORM_DRIVER_EXPORT(gen_pci_driver);
