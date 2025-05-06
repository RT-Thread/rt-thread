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
#include <drivers/core/bus.h>

rt_inline void spin_lock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_lock(&spinlock->lock);
}

rt_inline void spin_unlock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_unlock(&spinlock->lock);
}

struct rt_pci_host_bridge *rt_pci_host_bridge_alloc(rt_size_t priv_size)
{
    struct rt_pci_host_bridge *bridge = rt_calloc(1, sizeof(*bridge) + priv_size);

    return bridge;
}

rt_err_t rt_pci_host_bridge_free(struct rt_pci_host_bridge *bridge)
{
    if (!bridge)
    {
        return -RT_EINVAL;
    }

    if (bridge->bus_regions)
    {
        rt_free(bridge->bus_regions);
    }

    if (bridge->dma_regions)
    {
        rt_free(bridge->dma_regions);
    }

    rt_free(bridge);

    return RT_EOK;
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

    rt_list_init(&pdev->list);
    pdev->bus = bus;

    if (bus)
    {
        spin_lock(&bus->lock);
        rt_list_insert_before(&bus->devices_nodes, &pdev->list);
        spin_unlock(&bus->lock);
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
    rt_err_t err;
    struct rt_pci_device *pdev = RT_NULL;
    rt_uint16_t vendor = PCI_ANY_ID, device = PCI_ANY_ID;

    if (!bus)
    {
        goto _end;
    }

    err = rt_pci_bus_read_config_u16(bus, devfn, PCIR_VENDOR, &vendor);
    rt_pci_bus_read_config_u16(bus, devfn, PCIR_DEVICE, &device);

    if (vendor == (typeof(vendor))PCI_ANY_ID ||
        vendor == (typeof(vendor))0x0000 || err)
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

    rt_dm_dev_set_name(&pdev->parent, "%04x:%02x:%02x.%u",
            rt_pci_domain(pdev), pdev->bus->number,
            RT_PCI_SLOT(pdev->devfn), RT_PCI_FUNC(pdev->devfn));

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

static void pci_configure_ari(struct rt_pci_device *pdev)
{
    rt_uint32_t cap, ctl2_ari;
    struct rt_pci_device *bridge;

    if (!rt_pci_is_pcie(pdev) || pdev->devfn)
    {
        return;
    }

    bridge = pdev->bus->self;

    if (rt_pci_is_root_bus(pdev->bus) || !bridge)
    {
        return;
    }

    rt_pci_read_config_u32(bridge, bridge->pcie_cap + PCIER_DEVICE_CAP2, &cap);
    if (!(cap & PCIEM_CAP2_ARI))
    {
        return;
    }

    rt_pci_read_config_u32(bridge, bridge->pcie_cap + PCIER_DEVICE_CTL2, &ctl2_ari);

    if (rt_pci_find_ext_capability(pdev, PCIZ_ARI))
    {
        ctl2_ari |= PCIEM_CTL2_ARI;
        bridge->ari_enabled = RT_TRUE;
    }
    else
    {
        ctl2_ari &= ~PCIEM_CTL2_ARI;
        bridge->ari_enabled = RT_FALSE;
    }

    rt_pci_write_config_u32(bridge, bridge->pcie_cap + PCIER_DEVICE_CTL2, ctl2_ari);
}

static rt_uint16_t pci_cfg_space_size_ext(struct rt_pci_device *pdev)
{
    rt_uint32_t status;

    if (rt_pci_read_config_u32(pdev, PCI_REGMAX + 1, &status))
    {
        return PCI_REGMAX + 1;
    }

    return PCIE_REGMAX + 1;
}

static rt_uint16_t pci_cfg_space_size(struct rt_pci_device *pdev)
{
    int pos;
    rt_uint32_t status;
    rt_uint16_t class = pdev->class >> 8;

    if (class == PCIS_BRIDGE_HOST)
    {
        return pci_cfg_space_size_ext(pdev);
    }

    if (rt_pci_is_pcie(pdev))
    {
        return pci_cfg_space_size_ext(pdev);
    }

    pos = rt_pci_find_capability(pdev, PCIY_PCIX);
    if (!pos)
    {
        return PCI_REGMAX + 1;
    }

    rt_pci_read_config_u32(pdev, pos + PCIXR_STATUS, &status);
    if (status & (PCIXM_STATUS_266CAP | PCIXM_STATUS_533CAP))
    {
        return pci_cfg_space_size_ext(pdev);
    }

    return PCI_REGMAX + 1;
}

static void pci_init_capabilities(struct rt_pci_device *pdev)
{
    rt_pci_pme_init(pdev);

#ifdef RT_PCI_MSI
    rt_pci_msi_init(pdev);  /* Disable MSI */
    rt_pci_msix_init(pdev); /* Disable MSI-X */
#endif

    pcie_set_port_type(pdev);
    pdev->cfg_size = pci_cfg_space_size(pdev);
    pci_configure_ari(pdev);

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

    rt_dm_dev_set_name(&pdev->parent, "%04x:%02x:%02x.%u", rt_pci_domain(pdev),
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

    if (rt_pci_is_pcie(pdev))
    {
        rt_pci_read_config_u16(pdev, pdev->pcie_cap + PCIER_FLAGS, &pdev->exp_flags);
    }

    return RT_EOK;
}

static struct rt_pci_bus *pci_alloc_bus(struct rt_pci_bus *parent);

static rt_err_t pci_child_bus_init(struct rt_pci_bus *bus, rt_uint32_t bus_no,
        struct rt_pci_host_bridge *host_bridge, struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct rt_pci_bus *parent_bus = bus->parent;

    bus->sysdata = parent_bus->sysdata;
    bus->self = pdev;
    bus->ops = host_bridge->child_ops ? : parent_bus->ops;

    bus->number = bus_no;
    rt_sprintf(bus->name, "%04x:%02x", host_bridge->domain, bus_no);

    rt_pci_ofw_bus_init(bus);

    if (bus->ops->add)
    {
        if ((err = bus->ops->add(bus)))
        {
            rt_pci_ofw_bus_free(bus);

            LOG_E("PCI-Bus<%s> add bus failed with err = %s",
                    bus->name, rt_strerror(err));

            return err;
        }
    }

    return RT_EOK;
}

static rt_bool_t pci_ea_fixed_busnrs(struct rt_pci_device *pdev,
        rt_uint8_t *sec, rt_uint8_t *sub)
{
    int pos, offset;
    rt_uint32_t dw;
    rt_uint8_t ea_sec, ea_sub;

    pos = rt_pci_find_capability(pdev, PCIY_EA);
    if (!pos)
    {
        return RT_FALSE;
    }

    offset = pos + PCIR_EA_FIRST_ENT;
    rt_pci_read_config_u32(pdev, offset, &dw);
    ea_sec = PCIM_EA_SEC_NR(dw);
    ea_sub = PCIM_EA_SUB_NR(dw);
    if (ea_sec  == 0 || ea_sub < ea_sec)
    {
        return RT_FALSE;
    }

    *sec = ea_sec;
    *sub = ea_sub;

    return RT_TRUE;
}

static void pcie_fixup_link(struct rt_pci_device *pdev)
{
    int pos = pdev->pcie_cap;
    rt_uint16_t exp_lnkctl, exp_lnkctl2, exp_lnksta;
    rt_uint16_t exp_type = pdev->exp_flags & PCIEM_FLAGS_TYPE;

    if ((pdev->exp_flags & PCIEM_FLAGS_VERSION) < 2)
    {
        return;
    }

    if (exp_type != PCIEM_TYPE_ROOT_PORT &&
        exp_type != PCIEM_TYPE_DOWNSTREAM_PORT &&
        exp_type != PCIEM_TYPE_PCIE_BRIDGE)
    {
        return;
    }

    rt_pci_read_config_u16(pdev, pos + PCIER_LINK_CTL, &exp_lnkctl);
    rt_pci_read_config_u16(pdev, pos + PCIER_LINK_CTL2, &exp_lnkctl2);

    rt_pci_write_config_u16(pdev, pos + PCIER_LINK_CTL2,
            (exp_lnkctl2 & ~PCIEM_LNKCTL2_TLS) | PCIEM_LNKCTL2_TLS_2_5GT);
    rt_pci_write_config_u16(pdev, pos + PCIER_LINK_CTL,
            exp_lnkctl | PCIEM_LINK_CTL_RETRAIN_LINK);

    for (int i = 0; i < 20; ++i)
    {
        rt_pci_read_config_u16(pdev, pos + PCIER_LINK_STA, &exp_lnksta);

        if (!!(exp_lnksta & PCIEM_LINK_STA_DL_ACTIVE))
        {
            goto _status_sync;
        }

        rt_thread_mdelay(10);
    }

    /* Fail, restore */
    rt_pci_write_config_u16(pdev, pos + PCIER_LINK_CTL2, exp_lnkctl2);
    rt_pci_write_config_u16(pdev, pos + PCIER_LINK_CTL,
            exp_lnkctl | PCIEM_LINK_CTL_RETRAIN_LINK);

_status_sync:
    /* Wait a while for success or failure */
    rt_thread_mdelay(100);
}

static rt_uint32_t pci_scan_bridge_extend(struct rt_pci_bus *bus, struct rt_pci_device *pdev,
        rt_uint32_t bus_no_start, rt_uint32_t buses, rt_bool_t reconfigured)
{
    rt_bool_t fixed_buses;
    rt_uint8_t fixed_sub, fixed_sec;
    rt_uint8_t primary, secondary, subordinate;
    rt_uint32_t value, bus_no = bus_no_start;
    struct rt_pci_bus *next_bus;
    struct rt_pci_host_bridge *host_bridge;

    /* We not supported init CardBus, it always used in the PC servers. */
    if (pdev->hdr_type == PCIM_HDRTYPE_CARDBUS)
    {
        LOG_E("CardBus is not supported in system");

        goto _end;
    }

    rt_pci_read_config_u32(pdev, PCIR_PRIBUS_1, &value);
    primary = value & 0xff;
    secondary = (value >> 8) & 0xff;
    subordinate = (value >> 16) & 0xff;

    if (primary == bus->number && bus->number > secondary && secondary > subordinate)
    {
        if (!reconfigured)
        {
            goto _end;
        }

        LOG_I("Bridge configuration: primary(%02x) secondary(%02x) subordinate(%02x)",
                primary, secondary, subordinate);
    }

    if (pdev->pcie_cap)
    {
        pcie_fixup_link(pdev);
    }

    ++bus_no;
    /* Count of subordinate */
    buses -= !!buses;

    host_bridge = rt_pci_find_host_bridge(bus);
    RT_ASSERT(host_bridge != RT_NULL);

    /* Clear errors */
    rt_pci_write_config_u16(pdev, PCIR_STATUS, RT_UINT16_MAX);

    fixed_buses = pci_ea_fixed_busnrs(pdev, &fixed_sec, &fixed_sub);

    if (!(next_bus = pci_alloc_bus(bus)))
    {
        goto _end;
    }

    /* Clear bus info */
    rt_pci_write_config_u32(pdev, PCIR_PRIBUS_1, value & ~0xffffff);

    if (!(next_bus = pci_alloc_bus(bus)))
    {
        LOG_E("Alloc bus(%02x) fail", bus_no);
        goto _end;
    }

    if (pci_child_bus_init(next_bus, bus_no, host_bridge, pdev))
    {
        goto _end;
    }

    /* Fill primary, secondary */
    value = (buses & 0xff000000) | (bus->number << 0) | (next_bus->number << 8);
    rt_pci_write_config_u32(pdev, PCIR_PRIBUS_1, value);

    bus_no = rt_pci_scan_child_buses(next_bus, buses);

    /* Fill subordinate */
    value |= next_bus->number + rt_list_len(&next_bus->children_nodes);
    rt_pci_write_config_u32(pdev, PCIR_PRIBUS_1, value);

    if (fixed_buses)
    {
        bus_no = fixed_sub;
    }
    rt_pci_write_config_u8(pdev, PCIR_SUBBUS_1, bus_no);

_end:
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

rt_inline rt_bool_t only_one_child(struct rt_pci_bus *bus)
{
    struct rt_pci_device *pdev;

    if (rt_pci_is_root_bus(bus))
    {
        return RT_FALSE;
    }

    pdev = bus->self;

    if (rt_pci_is_pcie(pdev))
    {
        rt_uint16_t exp_type = pdev->exp_flags & PCIEM_FLAGS_TYPE;

        if (exp_type == PCIEM_TYPE_ROOT_PORT ||
            exp_type == PCIEM_TYPE_DOWNSTREAM_PORT ||
            exp_type == PCIEM_TYPE_PCIE_BRIDGE)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static int next_fn(struct rt_pci_bus *bus, struct rt_pci_device *pdev, int fn)
{
    if (!rt_pci_is_root_bus(bus) && bus->self->ari_enabled)
    {
        int pos, next_fn;
        rt_uint16_t cap = 0;

        if (!pdev)
        {
            return -RT_EINVAL;
        }

        pos = rt_pci_find_ext_capability(pdev, PCIZ_ARI);

        if (!pos)
        {
            return -RT_EINVAL;
        }

        rt_pci_read_config_u16(pdev, pos + PCIR_ARI_CAP, &cap);
        next_fn = PCIM_ARI_CAP_NFN(cap);

        if (next_fn <= fn)
        {
            return -RT_EINVAL;
        }

        return next_fn;
    }

    if (fn >= RT_PCI_FUNCTION_MAX - 1)
    {
        return -RT_EINVAL;
    }

    if (pdev && !pdev->multi_function)
    {
        return -RT_EINVAL;
    }

    return fn + 1;
}

rt_size_t rt_pci_scan_slot(struct rt_pci_bus *bus, rt_uint32_t devfn)
{
    rt_size_t nr = 0;
    struct rt_pci_device *pdev = RT_NULL;

    if (!bus)
    {
        return nr;
    }

    if (devfn > 0 && only_one_child(bus))
    {
        return nr;
    }

    for (int func = 0; func >= 0; func = next_fn(bus, pdev, func))
    {
        pdev = rt_pci_scan_single_device(bus, devfn + func);

        if (pdev)
        {
            ++nr;

            if (func > 0)
            {
                pdev->multi_function = RT_TRUE;
            }
        }
        else if (func == 0)
        {
            break;
        }
    }

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

        bus_no = pci_scan_bridge_extend(bus, pdev, bus_no, buses, RT_TRUE);
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

    rt_spin_lock_init(&bus->lock);

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

    bus->number = host_bridge->bus_range[0];
    rt_sprintf(bus->name, "%04x:%02x", host_bridge->domain, bus->number);

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

static rt_bool_t pci_remove_bus_device(struct rt_pci_device *pdev, void *data)
{
    /* Bus will free if this is the last device */
    rt_bus_remove_device(&pdev->parent);

    /* To find all devices, always return false */
    return RT_FALSE;
}

rt_err_t rt_pci_host_bridge_remove(struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err = RT_EOK;

    if (host_bridge && host_bridge->root_bus)
    {
        rt_pci_enum_device(host_bridge->root_bus, pci_remove_bus_device, RT_NULL);
        host_bridge->root_bus = RT_NULL;
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pci_bus_remove(struct rt_pci_bus *bus)
{
    rt_err_t err = RT_EOK;

    if (bus)
    {
        spin_lock(&bus->lock);

        if (rt_list_isempty(&bus->children_nodes) &&
            rt_list_isempty(&bus->devices_nodes))
        {
            rt_list_remove(&bus->list);
            spin_unlock(&bus->lock);

            if (bus->ops->remove)
            {
                bus->ops->remove(bus);
            }

            rt_pci_ofw_bus_free(bus);
            rt_free(bus);
        }
        else
        {
            spin_unlock(&bus->lock);

            err = -RT_EBUSY;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pci_device_remove(struct rt_pci_device *pdev)
{
    rt_err_t err = RT_EOK;

    if (pdev)
    {
        struct rt_pci_bus *bus = pdev->bus;

        spin_lock(&bus->lock);

        while (pdev->parent.ref_count > 1)
        {
            spin_unlock(&bus->lock);

            rt_thread_yield();

            spin_lock(&bus->lock);
        }
        rt_list_remove(&pdev->list);

        spin_unlock(&bus->lock);

        rt_free(pdev);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}
