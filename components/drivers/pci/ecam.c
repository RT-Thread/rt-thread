/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "pci.ecam"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ecam.h"

struct pci_ecam_config_window *pci_ecam_create(struct rt_pci_host_bridge *host_bridge,
        const struct pci_ecam_ops *ops)
{
    struct pci_ecam_config_window *conf_win = rt_calloc(1, sizeof(*conf_win));

    if (!conf_win)
    {
        return RT_NULL;
    }

    conf_win->bus_range = host_bridge->bus_range;
    conf_win->bus_shift = ops->bus_shift;
    conf_win->ops = ops;

    host_bridge->ops = (const struct rt_pci_ops *)&ops->pci_ops;

    return conf_win;
}

void *pci_ecam_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int where)
{
    struct pci_ecam_config_window *conf_win = bus->sysdata;
    const struct pci_ecam_ops *eops = conf_win->ops;
    void *win = conf_win->win, *map;
    rt_uint32_t busn = bus->number, bus_shift = eops->bus_shift, devfn_shift = bus_shift - 8;

    busn -= conf_win->bus_range[0];

    if (bus_shift)
    {
        rt_uint32_t bus_offset = (busn & PCIE_ECAM_BUS_MASK) << bus_shift;
        rt_uint32_t devfn_offset = (devfn & PCIE_ECAM_DEVFN_MASK) << devfn_shift;

        where &= PCIE_ECAM_REG_MASK;
        map = win + (bus_offset | devfn_offset | where);
    }
    else
    {
        map = win + PCIE_ECAM_OFFSET(busn, devfn, where);
    }

    return map;
}

const struct pci_ecam_ops pci_generic_ecam_ops =
{
    .pci_ops =
    {
        .map = pci_ecam_map,
        .read = rt_pci_bus_read_config_uxx,
        .write = rt_pci_bus_write_config_uxx,
    }
};
