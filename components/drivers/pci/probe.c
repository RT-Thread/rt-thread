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

#define DBG_TAG "pci.probe"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pci.h>

struct rt_pci_host_bridge *rt_pci_host_bridge_alloc(rt_size_t priv_size)
{
    struct rt_pci_host_bridge *bridge = rt_calloc(1, sizeof(*bridge) + priv_size);

    return bridge;
}

rt_err_t rt_pci_host_bridge_init(struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err = RT_EOK;

    if (host_bridge->parent.ofw_node)
    {
        err = rt_pci_ofw_host_bridge_init(host_bridge->parent.ofw_node, host_bridge);
    }

    return err;
}

struct rt_pci_device *rt_pci_alloc_device(struct rt_pci_bus *bus)
{
    struct rt_pci_device *pdev = rt_calloc(1, sizeof(*pdev));

    if (!pdev)
    {
        return RT_NULL;
    }

    rt_list_init(&pdev->list_in_bus);
    pdev->bus = bus;

    if (bus)
    {
        rt_list_insert_before(&bus->devices_nodes, &pdev->list_in_bus);
    }

    pdev->subsystem_vendor = PCI_ANY_ID;
    pdev->subsystem_device = PCI_ANY_ID;

    pdev->irq = -1;

    for (int i = 0; i < RT_ARRAY_SIZE(pdev->resource); ++i)
    {
        pdev->resource[i].flags = PCI_BUS_REGION_F_NONE;
    }

#ifdef RT_PCI_MSI
    rt_list_init(&pdev->msi_desc_nodes);
    rt_spin_lock_init(&pdev->msi_lock);
#endif

    return pdev;
}

struct rt_pci_device *rt_pci_scan_single_device(struct rt_pci_bus *bus, rt_uint32_t devfn)
{
    struct rt_pci_device *pdev = RT_NULL;
    rt_uint16_t vendor = PCI_ANY_ID, device = PCI_ANY_ID;

    if (!bus)
    {
        goto _end;
    }

    rt_pci_bus_read_config_u16(bus, devfn, PCIR_VENDOR, &vendor);
    rt_pci_bus_read_config_u16(bus, devfn, PCIR_DEVICE, &device);

    if (vendor == (typeof(vendor))PCI_ANY_ID)
    {
        goto _end;
    }

    if (!(pdev = rt_pci_alloc_device(bus)))
    {
        goto _end;
    }

    pdev->devfn = devfn;
    pdev->vendor = vendor;
    pdev->device = device;

    rt_dm_dev_set_name(&pdev->parent, "%04x:%02x:%02x.%d",
            rt_pci_domain(pdev), pdev->bus->number, RT_PCI_SLOT(pdev->devfn), RT_PCI_FUNC(pdev->devfn));

    if (rt_pci_setup_device(pdev))
    {
        rt_free(pdev);
        pdev = RT_NULL;

        goto _end;
    }

    rt_pci_device_register(pdev);

_end:
    return pdev;
}

static rt_bool_t pci_intx_mask_broken(struct rt_pci_device *pdev)
{
    rt_bool_t res = RT_FALSE;
    rt_uint16_t orig, toggle, new;

    rt_pci_read_config_u16(pdev, PCIR_COMMAND, &orig);
    toggle = orig ^ PCIM_CMD_INTxDIS;
    rt_pci_write_config_u16(pdev, PCIR_COMMAND, toggle);
    rt_pci_read_config_u16(pdev, PCIR_COMMAND, &new);

    rt_pci_write_config_u16(pdev, PCIR_COMMAND, orig);

    if (new != toggle)
    {
        res = RT_TRUE;
    }

    return res;
}

static void pci_read_irq(struct rt_pci_device *pdev)
{
    rt_uint8_t irq = 0;

    rt_pci_read_config_u8(pdev, PCIR_INTPIN, &irq);
    pdev->pin = irq;

    if (irq)
    {
        rt_pci_read_config_u8(pdev, PCIR_INTLINE, &irq);
    }
    pdev->irq = irq;
}

static void pcie_set_port_type(struct rt_pci_device *pdev)
{
    int pos;

    if (!(pos = rt_pci_find_capability(pdev, PCIY_EXPRESS)))
    {
        return;
    }

    pdev->pcie_cap = pos;
}

static void pci_init_capabilities(struct rt_pci_device *pdev)
{
    rt_pci_pme_init(pdev);

#ifdef RT_PCI_MSI
    rt_pci_msi_init(pdev);  /* Disable MSI */
    rt_pci_msix_init(pdev); /* Disable MSI-X */
#endif

    pcie_set_port_type(pdev);

    pdev->no_msi = RT_FALSE;
    pdev->msi_enabled = RT_FALSE;
    pdev->msix_enabled = RT_FALSE;
}

rt_err_t rt_pci_setup_device(struct rt_pci_device *pdev)
{
    rt_uint8_t pos;
    rt_uint32_t class = 0;
    struct rt_pci_host_bridge *host_bridge;

    if (!pdev)
    {
        return -RT_EINVAL;
    }

    if (!(host_bridge = rt_pci_find_host_bridge(pdev->bus)))
    {
        return -RT_EINVAL;
    }

    rt_pci_ofw_device_init(pdev);

    rt_pci_read_config_u32(pdev, PCIR_REVID, &class);

    pdev->revision = class & 0xff;
    pdev->class = class >> 8;   /* Upper 3 bytes */
    rt_pci_read_config_u8(pdev, PCIR_HDRTYPE, &pdev->hdr_type);

    /* Clear errors left from system firmware */
    rt_pci_write_config_u16(pdev, PCIR_STATUS, 0xffff);

    if (pdev->hdr_type & 0x80)
    {
        pdev->multi_function = RT_TRUE;
    }
    pdev->hdr_type &= PCIM_HDRTYPE;

    if (pci_intx_mask_broken(pdev))
    {
        pdev->broken_intx_masking = RT_TRUE;
    }

    rt_dm_dev_set_name(&pdev->parent, "%04x:%02x:%02x.%d", rt_pci_domain(pdev),
            pdev->bus->number, RT_PCI_SLOT(pdev->devfn), RT_PCI_FUNC(pdev->devfn));

    switch (pdev->hdr_type)
    {
    case PCIM_HDRTYPE_NORMAL:
        if (class == PCIS_BRIDGE_PCI)
        {
            goto error;
        }
        pci_read_irq(pdev);
        rt_pci_device_alloc_resource(host_bridge, pdev);
        rt_pci_read_config_u16(pdev, PCIR_SUBVEND_0, &pdev->subsystem_vendor);
        rt_pci_read_config_u16(pdev, PCIR_SUBDEV_0, &pdev->subsystem_device);
        break;

    case PCIM_HDRTYPE_BRIDGE:
        pci_read_irq(pdev);
        rt_pci_device_alloc_resource(host_bridge, pdev);
        pos = rt_pci_find_capability(pdev, PCIY_SUBVENDOR);
        if (pos)
        {
            rt_pci_read_config_u16(pdev, PCIR_SUBVENDCAP, &pdev->subsystem_vendor);
            rt_pci_read_config_u16(pdev, PCIR_SUBDEVCAP, &pdev->subsystem_device);
        }
        break;

    case PCIM_HDRTYPE_CARDBUS:
        if (class != PCIS_BRIDGE_CARDBUS)
        {
            goto error;
        }
        pci_read_irq(pdev);
        rt_pci_device_alloc_resource(host_bridge, pdev);
        rt_pci_read_config_u16(pdev, PCIR_SUBVEND_2, &pdev->subsystem_vendor);
        rt_pci_read_config_u16(pdev, PCIR_SUBDEV_2, &pdev->subsystem_device);
        break;

    default:
        LOG_E("Ignoring device unknown header type %02x", pdev->hdr_type);
        return -RT_EIO;

    error:
        LOG_E("Ignoring class %08x (doesn't match header type %02x)", pdev->class, pdev->hdr_type);
        pdev->class = PCIC_NOT_DEFINED << 8;
    }

    pci_init_capabilities(pdev);

    return RT_EOK;
}

static rt_uint32_t pci_scan_bridge_extend(struct rt_pci_bus *bus, struct rt_pci_device *pdev,
        rt_uint32_t bus_no_start, rt_uint32_t buses, rt_bool_t reconfigured)
{
    rt_bool_t broken = RT_FALSE, is_cardbus;
    rt_uint8_t primary, secondary, subordinate;
    rt_uint32_t value, bus_no = bus_no_start, next_busnr;

    is_cardbus = (pdev->hdr_type == PCIM_HDRTYPE_CARDBUS);

    rt_pci_read_config_u32(pdev, PCIR_PRIBUS_1, &value);
    primary = value & 0xff;
    secondary = (value >> 8) & 0xff;
    subordinate = (value >> 16) & 0xff;

    LOG_D("Scanning [bus %02x-%02x] behind bridge, reconfigured %d",
        secondary, subordinate, reconfigured);

    if (!primary && (primary != bus->number) && secondary && subordinate)
    {
        LOG_W("Primary bus is hard wired to 0");

        primary = bus->number;
    }

    /* Check if setup is sensible at all */
    if (!reconfigured && (primary != bus->number || secondary <= bus->number ||
        secondary > subordinate))
    {
        LOG_I("Bridge configuration invalid ([bus %02x-%02x]), reconfiguring",
                secondary, subordinate);

        broken = RT_TRUE;
    }

    if ((secondary || subordinate) && !is_cardbus && !broken)
    {
        next_busnr = secondary;
    }
    else
    {
        next_busnr = bus_no_start + 1;
    }

    LOG_I("Found: PCI %sBus %04x:%02x", is_cardbus ? "Card" : "",
            rt_pci_domain(pdev), next_busnr);

    /*
     * We should init bridge here, but the PCI bridges are always used in the PC
     * servers. We just output the bridge information to develop.
     */

    return bus_no;
}

rt_uint32_t rt_pci_scan_bridge(struct rt_pci_bus *bus, struct rt_pci_device *pdev,
        rt_uint32_t bus_no_start, rt_bool_t reconfigured)
{
    if (!bus || !pdev)
    {
        return RT_UINT32_MAX;
    }

    return pci_scan_bridge_extend(bus, pdev, bus_no_start, 0, reconfigured);
}

rt_size_t rt_pci_scan_slot(struct rt_pci_bus *bus, rt_uint32_t devfn)
{
    rt_size_t nr = 0;

    if (!bus)
    {
        goto _end;
    }

    for (int func = 0; func < RT_PCI_FUNCTION_MAX; ++func, ++devfn)
    {
        struct rt_pci_device *pdev = rt_pci_scan_single_device(bus, devfn);

        if (pdev)
        {
            ++nr;

            /* If this is a single function device, don't scan past the first function. */
            if (!pdev->multi_function)
            {
                if (func > 0)
                {
                    pdev->multi_function = RT_TRUE;
                }
                else
                {
                    break;
                }
            }
        }
        else if (func == 0)
        {
            break;
        }
    }

_end:
    return nr;
}

rt_uint32_t rt_pci_scan_child_buses(struct rt_pci_bus *bus, rt_size_t buses)
{
    rt_uint32_t bus_no;
    struct rt_pci_device *pdev = RT_NULL;

    if (!bus)
    {
        bus_no = RT_UINT32_MAX;

        goto _end;
    }

    bus_no = bus->number;

    for (rt_uint32_t devfn = 0;
        devfn < RT_PCI_DEVFN(RT_PCI_DEVICE_MAX - 1, RT_PCI_FUNCTION_MAX - 1);
        devfn += RT_PCI_FUNCTION_MAX)
    {
        rt_pci_scan_slot(bus, devfn);
    }

    rt_pci_foreach_bridge(pdev, bus)
    {
        int offset;

        bus_no = pci_scan_bridge_extend(bus, pdev, bus_no, buses, RT_FALSE);
        offset = bus_no - bus->number;

        if (buses > offset)
        {
            buses -= offset;
        }
        else
        {
            break;
        }
    }

_end:
    return bus_no;
}

rt_uint32_t rt_pci_scan_child_bus(struct rt_pci_bus *bus)
{
    return rt_pci_scan_child_buses(bus, 0);
}

static struct rt_pci_bus *pci_alloc_bus(struct rt_pci_bus *parent)
{
    struct rt_pci_bus *bus = rt_calloc(1, sizeof(*bus));

    if (!bus)
    {
        return RT_NULL;
    }

    bus->parent = parent;

    rt_list_init(&bus->list);
    rt_list_init(&bus->children_nodes);
    rt_list_init(&bus->devices_nodes);

    return bus;
}

rt_err_t rt_pci_host_bridge_register(struct rt_pci_host_bridge *host_bridge)
{
    struct rt_pci_bus *bus = pci_alloc_bus(RT_NULL);

    if (!bus)
    {
        return -RT_ENOMEM;
    }

    host_bridge->root_bus = bus;

    bus->sysdata = host_bridge->sysdata;
    bus->host_bridge = host_bridge;
    bus->ops = host_bridge->ops;

    rt_sprintf(bus->name, "%04x:%02x", host_bridge->domain, host_bridge->busnr);

    if (bus->ops->add)
    {
        rt_err_t err = bus->ops->add(bus);

        if (err)
        {
            LOG_E("PCI-Bus<%s> add bus failed with err = %s", bus->name, rt_strerror(err));
        }
    }

    return RT_EOK;
}

rt_err_t rt_pci_scan_root_bus_bridge(struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err;

    if ((err = rt_pci_host_bridge_register(host_bridge)))
    {
        return err;
    }

    rt_pci_scan_child_bus(host_bridge->root_bus);

    return err;
}

rt_err_t rt_pci_host_bridge_probe(struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err;

    err = rt_pci_scan_root_bus_bridge(host_bridge);

    return err;
}
