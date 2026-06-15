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
 * @file probe.c
 * @brief PCI bus scanning and device probing
 *
 * Implements the PCI bus enumeration process:
 * - Host bridge allocation and registration
 * - Bus scanning (depth-first tree walk)
 * - Device probing (vendor/device ID readout, resource allocation)
 * - Bridge scanning (recursive child bus discovery)
 * - Device and bus teardown
 *
 * The enumeration flow:
 * 1. Allocate host bridge → register root bus → scan child buses
 * 2. For each slot (devfn): read vendor, probe device, allocate BARs
 * 3. For each bridge: create child bus, configure bridge window, recurse
 */

#include <rtthread.h>

#define DBG_TAG "pci.probe"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pci.h>
#include <drivers/core/bus.h>

#include "procfs.h"

/** @brief Convenience wrapper for spinlock acquire */
rt_inline void spin_lock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_lock(&spinlock->lock);
}

/** @brief Convenience wrapper for spinlock release */
rt_inline void spin_unlock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_unlock(&spinlock->lock);
}

/**
 * @brief Allocate a PCI host bridge structure
 *
 * @param[in] priv_size Size in bytes of private data to reserve after the bridge
 * @return New host bridge (zeroed), or RT_NULL on allocation failure
 */
struct rt_pci_host_bridge *rt_pci_host_bridge_alloc(rt_size_t priv_size)
{
    struct rt_pci_host_bridge *bridge = rt_calloc(1, sizeof(*bridge) + priv_size);

    return bridge;
}

/**
 * @brief Free a PCI host bridge and its associated regions
 *
 * @param[in] bridge Host bridge to free
 * @return RT_EOK on success, -RT_EINVAL if bridge is NULL
 */
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

/**
 * @brief Initialize a host bridge from device tree data
 *
 * If the host bridge has an ofw_node (device tree node), parses
 * bus-range, domain, and ranges properties from the DT.
 *
 * @param[in] host_bridge PCI host bridge to initialize
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t rt_pci_host_bridge_init(struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err = RT_EOK;

    if (host_bridge->parent.ofw_node)
    {
        err = rt_pci_ofw_host_bridge_init(host_bridge->parent.ofw_node, host_bridge);
    }

    return err;
}

/**
 * @brief Allocate and initialize a new PCI device on a bus
 *
 * Initializes the device's linked list node, associates it with the bus,
 * sets default subsystem IDs to PCI_ANY_ID (wildcard), marks all resources
 * as unused, and initializes MSI descriptor list and lock.
 *
 * @param[in] bus Parent PCI bus (may be NULL for host bridge devices)
 * @return New PCI device (zeroed), or RT_NULL on failure
 */
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

/**
 * @brief Scan and probe a single PCI device at a given devfn
 *
 * Reads vendor and device IDs from config space. If valid,
 * allocates a pci_device structure, reads basic configuration,
 * sets up BAR resources, and registers the device on the PCI bus.
 *
 * @param[in] bus   PCI bus to scan on
 * @param[in] devfn Device/function number to probe
 * @return Pointer to the new PCI device, or RT_NULL if no device present
 */
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

    pci_procfs_attach(pdev);
    rt_pci_device_register(pdev);

_end:
    return pdev;
}

/**
 * @brief Detect whether INTx masking is broken on this device
 *
 * Writes a toggled INTx disable bit and reads back to verify.
 * If the read value doesn't match, the device doesn't support
 * INTx masking (common on some older PCI devices).
 *
 * @param[in] pdev PCI device
 * @return RT_TRUE if INTx masking is broken
 */
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

/**
 * @brief Read Interrupt Pin and Interrupt Line from config space
 *
 * @param[in] pdev PCI device (updated in place)
 */
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

/**
 * @brief Detect and record PCIe port type from the PCI Express capability
 *
 * @param[in] pdev PCI device (pcie_cap field updated in place)
 */
static void pcie_set_port_type(struct rt_pci_device *pdev)
{
    int pos;

    if (!(pos = rt_pci_find_capability(pdev, PCIY_EXPRESS)))
    {
        return;
    }

    pdev->pcie_cap = pos;
}

/**
 * @brief Configure ARI (Alternative Routing-ID Interpretation) on a PCIe device
 *
 * ARI extends the function number field from 3 to 8 bits, allowing
 * up to 256 functions per device (instead of 8). This must be
 * enabled on both the downstream port (bridge) and the device.
 *
 * @param[in] pdev PCI device (function 0 of a multi-function device)
 */
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

/**
 * @brief Determine the extended configuration space size
 *
 * Tries reading beyond the standard 256-byte config space (at offset 256).
 * If accessible, the device has PCIe extended config space (4KB).
 *
 * @param[in] pdev PCI device
 * @return PCIE_REGMAX+1 (4096) for extended space, or PCI_REGMAX+1 (256) for standard
 */
static rt_uint16_t pci_cfg_space_size_ext(struct rt_pci_device *pdev)
{
    rt_uint32_t status;

    if (rt_pci_read_config_u32(pdev, PCI_REGMAX + 1, &status))
    {
        return PCI_REGMAX + 1;
    }

    return PCIE_REGMAX + 1;
}

/**
 * @brief Determine the configuration space size for a device
 *
 * Host bridges, PCIe devices, and PCI-X 266/533-capable devices
 * have extended (4KB) config space. Others have standard 256 bytes.
 *
 * @param[in] pdev PCI device
 * @return Total config space size in bytes
 */
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

/**
 * @brief Initialize all capabilities for a newly probed device
 *
 * Sets up PME, MSI/MSI-X (disables them initially), PCIe port type,
 * config space size, and ARI configuration.
 *
 * @param[in] pdev PCI device
 */
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

/**
 * @brief Complete PCI device setup after initial probe
 *
 * Reads revision ID, class code, header type. Clears error status.
 * Detects multi-function devices. Checks INTx masking capability.
 * Allocates BAR resources. Initializes capabilities.
 *
 * @param[in] pdev PCI device (populated in place)
 * @return RT_EOK on success, -RT_EIO for unsupported header types
 */
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

    class = pdev->class >> 8;

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

/**
 * @brief Initialize a child PCI bus (for bridge devices)
 *
 * Sets up the bus number, attaches the bridge device as bus->self,
 * inherits sysdata and ops from the parent, and calls the bus's
 * add() operation if present.
 *
 * @param[in] bus         Child bus to initialize
 * @param[in] bus_no      Bus number to assign
 * @param[in] host_bridge Host bridge for this hierarchy
 * @param[in] pdev        Bridge device (bus->self)
 * @return RT_EOK on success
 */
static rt_err_t pci_child_bus_init(struct rt_pci_bus *bus, rt_uint32_t bus_no,
                                   struct rt_pci_host_bridge *host_bridge, struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct rt_pci_bus *parent_bus = bus->parent;

    bus->sysdata = parent_bus->sysdata;
    bus->self = pdev;
    bus->ops = host_bridge->child_ops ?: parent_bus->ops;

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

/**
 * @brief Check if the Enhanced Allocation capability specifies fixed bus numbers
 *
 * @param[in]  pdev Bridge device
 * @param[out] sec  Secondary bus number from EA
 * @param[out] sub  Subordinate bus number from EA
 * @return RT_TRUE if EA provides valid fixed bus numbers
 */
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
    if (ea_sec == 0 || ea_sub < ea_sec)
    {
        return RT_FALSE;
    }

    *sec = ea_sec;
    *sub = ea_sub;

    return RT_TRUE;
}

/**
 * @brief Fix up PCIe link speed after enumeration
 *
 * For PCIe root ports, downstream ports, and bridges:
 * retrain the link to negotiate the optimal speed.
 *
 * @param[in] pdev PCIe bridge device
 */
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

/**
 * @brief Scan behind a PCI bridge, extending the bus topology
 *
 * Creates a child bus, configures the bridge's primary/secondary/subordinate
 * bus numbers, scans child buses recursively, and writes back the final
 * subordinate bus number.
 *
 * @param[in] bus          Parent bus
 * @param[in] pdev         Bridge PCI device
 * @param[in] bus_no_start Starting bus number for allocation
 * @param[in] buses        Maximum number of buses to allocate (0 = unlimited)
 * @param[in] reconfigured Whether this is a reconfiguration
 * @return Final bus number allocated
 */
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

/**
 * @brief Scan behind a PCI bridge (convenience wrapper)
 *
 * @param[in] bus          Parent bus
 * @param[in] pdev         Bridge device
 * @param[in] bus_no_start Starting bus number
 * @param[in] reconfigured Whether reconfiguring
 * @return Final bus number
 */
rt_uint32_t rt_pci_scan_bridge(struct rt_pci_bus *bus, struct rt_pci_device *pdev,
                               rt_uint32_t bus_no_start, rt_bool_t reconfigured)
{
    if (!bus || !pdev)
    {
        return RT_UINT32_MAX;
    }

    return pci_scan_bridge_extend(bus, pdev, bus_no_start, 0, reconfigured);
}

/**
 * @brief Check if a PCI bus has only one child (for enumeration optimization)
 *
 * PCIe root ports, downstream ports, and PCIe bridges typically have
 * only one device on their secondary bus. This is used to avoid
 * scanning beyond function 0 on such buses.
 *
 * @param[in] bus PCI bus (must be non-root)
 * @return RT_TRUE if the bus is likely a point-to-point link
 */
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

/**
 * @brief Get the next function number to scan
 *
 * Handles ARI (Alternative Routing-ID Interpretation) where function
 * numbers go beyond the standard 0-7 range (up to 255).
 *
 * @param[in] bus  PCI bus
 * @param[in] pdev Current device (may be NULL for first call)
 * @param[in] fn   Current function number
 * @return Next function number, or negative on error/end
 */
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

/**
 * @brief Scan all functions in a PCI slot
 *
 * Iterates through function numbers starting from devfn, probing
 * each function. Stops when function 0 returns nothing (no device
 * in this slot) or when a non-multi-function device is found.
 *
 * @param[in] bus   PCI bus
 * @param[in] devfn Starting device/function number
 * @return Number of devices found in this slot
 */
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

/**
 * @brief Recursively scan child buses of a PCI bus
 *
 * Scans all slots (devfn 0..255 step 8), then for each bridge found,
 * creates a child bus and scans behind it. Bus numbers are allocated
 * incrementally.
 *
 * @param[in] bus   Parent PCI bus
 * @param[in] buses Maximum number of buses to allocate (0 = unlimited)
 * @return Final bus number used
 */
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

/**
 * @brief Scan all child buses of a PCI bus (unlimited buses)
 *
 * @param[in] bus PCI bus
 * @return Final bus number
 */
rt_uint32_t rt_pci_scan_child_bus(struct rt_pci_bus *bus)
{
    return rt_pci_scan_child_buses(bus, 0);
}

/**
 * @brief Allocate and initialize a new PCI bus structure
 *
 * @param[in] parent Parent bus (or NULL for root bus)
 * @return New bus, or RT_NULL on failure
 */
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

/**
 * @brief Register a host bridge's root bus
 *
 * Creates the root bus, links it to the host bridge, and calls
 * the bus's add() operation.
 *
 * @param[in] host_bridge Host bridge to register
 * @return RT_EOK on success
 */
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

/**
 * @brief Register a host bridge and scan its root bus
 *
 * This is the main entry point for initializing a PCI hierarchy:
 * register the root bus, then scan and enumerate all devices.
 *
 * @param[in] host_bridge Host bridge
 * @return RT_EOK on success
 */
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

/**
 * @brief Probe a host bridge (register + scan)
 *
 * @param[in] host_bridge Host bridge
 * @return RT_EOK on success
 */
rt_err_t rt_pci_host_bridge_probe(struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err;

    err = rt_pci_scan_root_bus_bridge(host_bridge);

    return err;
}

/**
 * @brief Enumeration callback: remove a device from its bus
 *
 * @param[in] pdev PCI device to remove
 * @param[in] data Unused
 * @return Always RT_FALSE (continue removal for all devices)
 */
static rt_bool_t pci_remove_bus_device(struct rt_pci_device *pdev, void *data)
{
    /* Bus will free if this is the last device */
    rt_bus_remove_device(&pdev->parent);

    /* To find all devices, always return false */
    return RT_FALSE;
}

/**
 * @brief Remove a host bridge and all its devices
 *
 * Enumerates all devices under the root bus and removes them.
 *
 * @param[in] host_bridge Host bridge to remove
 * @return RT_EOK on success, -RT_EINVAL if bridge is NULL
 */
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

/**
 * @brief Remove a PCI bus if it has no children or devices
 *
 * A bus can only be removed when both its children_nodes and
 * devices_nodes lists are empty.
 *
 * @param[in] bus PCI bus to remove
 * @return RT_EOK on success, -RT_EBUSY if bus still has children/devices
 */
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

/**
 * @brief Remove a PCI device from its bus
 *
 * Waits for any remaining references to be released (yielding),
 * then removes the device from the bus's device list and frees it.
 *
 * @param[in] pdev PCI device to remove
 * @return RT_EOK on success, -RT_EINVAL if device is NULL
 */
rt_err_t rt_pci_device_remove(struct rt_pci_device *pdev)
{
    rt_err_t err = RT_EOK;

    if (pdev)
    {
        struct rt_pci_bus *bus = pdev->bus;

        pci_procfs_detach(pdev);

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
