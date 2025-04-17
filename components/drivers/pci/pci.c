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
#include <rtservice.h>

#define DBG_TAG "rtdm.pci"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pci.h>
#include <drivers/misc.h>
#include <drivers/core/bus.h>

rt_inline void spin_lock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_lock(&spinlock->lock);
}

rt_inline void spin_unlock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_unlock(&spinlock->lock);
}

rt_uint32_t rt_pci_domain(struct rt_pci_device *pdev)
{
    struct rt_pci_host_bridge *host_bridge;

    if (!pdev)
    {
        return RT_UINT32_MAX;
    }

    if ((host_bridge = rt_pci_find_host_bridge(pdev->bus)))
    {
        return host_bridge->domain;
    }

    return RT_UINT32_MAX;
}

static rt_uint8_t pci_find_next_cap_ttl(struct rt_pci_bus *bus,
        rt_uint32_t devfn, rt_uint8_t pos, int cap, int *ttl)
{
    rt_uint8_t ret = 0, id;
    rt_uint16_t ent;

    rt_pci_bus_read_config_u8(bus, devfn, pos, &pos);

    while ((*ttl)--)
    {
        if (pos < 0x40)
        {
            break;
        }

        pos &= ~3;
        rt_pci_bus_read_config_u16(bus, devfn, pos, &ent);

        id = ent & 0xff;
        if (id == 0xff)
        {
            break;
        }
        if (id == cap)
        {
            ret = pos;
            break;
        }
        pos = (ent >> 8);
    }

    return ret;
}

static rt_uint8_t pci_find_next_cap(struct rt_pci_bus *bus,
        rt_uint32_t devfn, rt_uint8_t pos, int cap)
{
    int ttl = RT_PCI_FIND_CAP_TTL;

    return pci_find_next_cap_ttl(bus, devfn, pos, cap, &ttl);
}

static rt_uint8_t pci_bus_find_cap_start(struct rt_pci_bus *bus,
        rt_uint32_t devfn, rt_uint8_t hdr_type)
{
    rt_uint8_t res = 0;
    rt_uint16_t status;

    rt_pci_bus_read_config_u16(bus, devfn, PCIR_STATUS, &status);

    if (status & PCIM_STATUS_CAPPRESENT)
    {
        switch (hdr_type)
        {
        case PCIM_HDRTYPE_NORMAL:
        case PCIM_HDRTYPE_BRIDGE:
            res = PCIR_CAP_PTR;
            break;

        case PCIM_HDRTYPE_CARDBUS:
            res = PCIR_CAP_PTR_2;
            break;
        }
    }

    return res;
}

rt_uint8_t rt_pci_bus_find_capability(struct rt_pci_bus *bus, rt_uint32_t devfn, int cap)
{
    rt_uint8_t hdr_type, ret = RT_UINT8_MAX;

    if (bus)
    {
        rt_pci_bus_read_config_u8(bus, devfn, PCIR_HDRTYPE, &hdr_type);

        ret = pci_bus_find_cap_start(bus, devfn, hdr_type & PCIM_HDRTYPE);

        if (ret)
        {
            ret = pci_find_next_cap(bus, devfn, ret, cap);
        }
    }

    return ret;
}

rt_uint8_t rt_pci_find_capability(struct rt_pci_device *pdev, int cap)
{
    rt_uint8_t res = RT_UINT8_MAX;

    if (pdev)
    {
        res = pci_bus_find_cap_start(pdev->bus, pdev->devfn, pdev->hdr_type);

        if (res)
        {
            res = pci_find_next_cap(pdev->bus, pdev->devfn, res, cap);
        }
    }

    return res;
}

rt_uint8_t rt_pci_find_next_capability(struct rt_pci_device *pdev, rt_uint8_t pos, int cap)
{
    rt_uint8_t res = RT_UINT8_MAX;

    if (pdev)
    {
        res = pci_find_next_cap(pdev->bus, pdev->devfn, pos + PCICAP_NEXTPTR, cap);
    }

    return res;
}

rt_uint16_t rt_pci_find_ext_capability(struct rt_pci_device *pdev, int cap)
{
    return rt_pci_find_ext_next_capability(pdev, 0, cap);
}

rt_uint16_t rt_pci_find_ext_next_capability(struct rt_pci_device *pdev, rt_uint16_t pos, int cap)
{
    int ttl;
    rt_uint32_t header;
    rt_uint16_t start = pos;

    /* minimum 8 bytes per capability */
    ttl = ((PCIE_REGMAX + 1) - (PCI_REGMAX + 1)) / 8;

    if (pdev->cfg_size <= PCI_REGMAX + 1)
    {
        return 0;
    }

    if (!pos)
    {
        pos = PCI_REGMAX + 1;
    }

    if (rt_pci_read_config_u32(pdev, pos, &header))
    {
        return 0;
    }

    /*
     * If we have no capabilities, this is indicated by cap ID,
     * cap version and next pointer all being 0.
     */
    if (header == 0)
    {
        return 0;
    }

    while (ttl-- > 0)
    {
        if (PCI_EXTCAP_ID(header) == cap && pos != start)
        {
            return pos;
        }

        pos = PCI_EXTCAP_NEXTPTR(header);

        if (pos < PCI_REGMAX + 1)
        {
            break;
        }

        if (rt_pci_read_config_u32(pdev, pos, &header))
        {
            break;
        }
    }

    return 0;
}

static void pci_set_master(struct rt_pci_device *pdev, rt_bool_t enable)
{
    rt_uint16_t old_cmd, cmd;

    rt_pci_read_config_u16(pdev, PCIR_COMMAND, &old_cmd);

    if (enable)
    {
        cmd = old_cmd | PCIM_CMD_BUSMASTEREN;
    }
    else
    {
        cmd = old_cmd & ~PCIM_CMD_BUSMASTEREN;
    }

    if (cmd != old_cmd)
    {
        rt_pci_write_config_u16(pdev, PCIR_COMMAND, cmd);
    }

    pdev->busmaster = !!enable;
}

void rt_pci_set_master(struct rt_pci_device *pdev)
{
    if (pdev)
    {
        pci_set_master(pdev, RT_TRUE);
    }
}

void rt_pci_clear_master(struct rt_pci_device *pdev)
{
    if (pdev)
    {
        pci_set_master(pdev, RT_FALSE);
    }
}

void rt_pci_intx(struct rt_pci_device *pdev, rt_bool_t enable)
{
    rt_uint16_t pci_command, new;

    if (!pdev)
    {
        return;
    }

    rt_pci_read_config_u16(pdev, PCIR_COMMAND, &pci_command);

    if (enable)
    {
        new = pci_command & ~PCIM_CMD_INTxDIS;
    }
    else
    {
        new = pci_command | PCIM_CMD_INTxDIS;
    }

    if (new != pci_command)
    {
        rt_pci_write_config_u16(pdev, PCIR_COMMAND, new);
    }
}

static rt_bool_t pci_check_and_set_intx_mask(struct rt_pci_device *pdev, rt_bool_t mask)
{
    rt_ubase_t level;
    rt_bool_t irq_pending;
    rt_bool_t res = RT_TRUE;
    rt_uint16_t origcmd, newcmd;
    rt_uint32_t cmd_status_dword;
    struct rt_pci_bus *bus = pdev->bus;

    level = rt_spin_lock_irqsave(&rt_pci_lock);

    bus->ops->read(bus, pdev->devfn, PCIR_COMMAND, 4, &cmd_status_dword);

    irq_pending = (cmd_status_dword >> 16) & PCIM_STATUS_INTxSTATE;

    /*
     * Check interrupt status register to see whether our device
     * triggered the interrupt (when masking) or the next IRQ is
     * already pending (when unmasking).
     */
    if (mask != irq_pending)
    {
        res = RT_FALSE;
    }
    else
    {
        origcmd = cmd_status_dword;
        newcmd = origcmd & ~PCIM_CMD_INTxDIS;

        if (mask)
        {
            newcmd |= PCIM_CMD_INTxDIS;
        }
        if (newcmd != origcmd)
        {
            bus->ops->write(bus, pdev->devfn, PCIR_COMMAND, 2, newcmd);
        }
    }

    rt_spin_unlock_irqrestore(&rt_pci_lock, level);

    return res;
}

rt_bool_t rt_pci_check_and_mask_intx(struct rt_pci_device *pdev)
{
    rt_bool_t res = RT_FALSE;

    if (pdev)
    {
        res = pci_check_and_set_intx_mask(pdev, RT_TRUE);
    }

    return res;
}

rt_bool_t rt_pci_check_and_unmask_intx(struct rt_pci_device *pdev)
{
    rt_bool_t res = RT_FALSE;

    if (pdev)
    {
        res = pci_check_and_set_intx_mask(pdev, RT_FALSE);
    }

    return res;
}

void rt_pci_irq_mask(struct rt_pci_device *pdev)
{
    if (pdev)
    {
        rt_bool_t unused;
        struct rt_pic_irq *pirq;

        rt_pci_intx(pdev, RT_FALSE);

        pirq = rt_pic_find_pirq(pdev->intx_pic, pdev->irq);
        RT_ASSERT(pirq != RT_NULL);

        rt_hw_spin_lock(&pirq->rw_lock.lock);
        unused = rt_list_isempty(&pirq->isr.list);
        rt_hw_spin_unlock(&pirq->rw_lock.lock);

        if (unused)
        {
            rt_hw_interrupt_mask(pdev->irq);
        }
    }
}

void rt_pci_irq_unmask(struct rt_pci_device *pdev)
{
    if (pdev)
    {
        rt_hw_interrupt_umask(pdev->irq);
        rt_pci_intx(pdev, RT_TRUE);
    }
}

struct rt_pci_bus *rt_pci_find_root_bus(struct rt_pci_bus *bus)
{
    if (!bus)
    {
        return RT_NULL;
    }

    while (bus->parent)
    {
        bus = bus->parent;
    }

    return bus;
}

struct rt_pci_host_bridge *rt_pci_find_host_bridge(struct rt_pci_bus *bus)
{
    if (!bus)
    {
        return RT_NULL;
    }

    if ((bus = rt_pci_find_root_bus(bus)))
    {
        return rt_container_of(bus->host_bridge, struct rt_pci_host_bridge, parent);
    }

    return RT_NULL;
}

rt_uint8_t rt_pci_irq_intx(struct rt_pci_device *pdev, rt_uint8_t pin)
{
    int slot = 0;

    if (!pdev->ari_enabled)
    {
        slot = RT_PCI_SLOT(pdev->devfn);
    }

    return (((pin - 1) + slot) % 4) + 1;
}

rt_uint8_t rt_pci_irq_slot(struct rt_pci_device *pdev, rt_uint8_t *pinp)
{
    rt_uint8_t pin = *pinp;

    while (!rt_pci_is_root_bus(pdev->bus))
    {
        pin = rt_pci_irq_intx(pdev, pin);
        pdev = pdev->bus->self;
    }

    *pinp = pin;

    return RT_PCI_SLOT(pdev->devfn);
}

rt_err_t rt_pci_region_setup(struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err = host_bridge->bus_regions_nr == 0 ? -RT_EEMPTY : RT_EOK;

    for (int i = 0; i < host_bridge->bus_regions_nr; ++i)
    {
        struct rt_pci_bus_region *region = &host_bridge->bus_regions[i];
        /*
         * Avoid allocating PCI resources from address 0 -- this is illegal
         * according to PCI 2.1 and moreover. Use a reasonable starting value of
         * 0x1000 instead if the bus start address is below 0x1000.
         */
        region->bus_start = rt_max_t(rt_size_t, 0x1000, region->phy_addr);

        LOG_I("Bus %s region(%d):",
            region->flags == PCI_BUS_REGION_F_MEM ? "Memory" :
                    (region->flags == PCI_BUS_REGION_F_PREFETCH ? "Prefetchable Mem" :
                            (region->flags == PCI_BUS_REGION_F_IO ? "I/O" : "Unknown")), i);
        LOG_I("  cpu:      [%p, %p]", region->cpu_addr, (region->cpu_addr + region->size - 1));
        LOG_I("  physical: [%p, %p]", region->phy_addr, (region->phy_addr + region->size - 1));
    }

    return err;
}

struct rt_pci_bus_region *rt_pci_region_alloc(struct rt_pci_host_bridge *host_bridge,
        void **out_addr, rt_size_t size, rt_ubase_t flags, rt_bool_t mem64)
{
    struct rt_pci_bus_region *bus_region, *region = RT_NULL;

    bus_region = &host_bridge->bus_regions[0];

    for (int i = 0; i < host_bridge->bus_regions_nr; ++i, ++bus_region)
    {
        if (bus_region->flags == flags && bus_region->size > 0)
        {
            void *addr;

            region = bus_region;
            addr = (void *)(((region->bus_start - 1) | (size - 1)) + 1);

            if ((rt_uint64_t)addr - region->phy_addr + size <= region->size)
            {
                rt_bool_t addr64 = !!rt_upper_32_bits((rt_ubase_t)addr);

                if (mem64)
                {
                    if (!addr64)
                    {
                        region = RT_NULL;

                        /* Try again */
                        continue;
                    }
                }
                else if (addr64)
                {
                    region = RT_NULL;

                    /* Try again */
                    continue;
                }

                region->bus_start = ((rt_uint64_t)addr + size);
                *out_addr = addr;
            }

            break;
        }
    }

    if (!region && mem64)
    {
        /* Retry */
        region = rt_pci_region_alloc(host_bridge, out_addr, size, flags, RT_FALSE);
    }

    return region;
}

rt_err_t rt_pci_device_alloc_resource(struct rt_pci_host_bridge *host_bridge,
        struct rt_pci_device *pdev)
{
    rt_err_t err = RT_EOK;
    rt_size_t size;
    rt_ubase_t addr = 0;
    rt_uint32_t cfg;
    rt_size_t bars_nr;
    rt_uint8_t hdr_type;
    rt_bool_t prefetch = RT_FALSE;
    rt_uint16_t class, command = 0;

    for (int i = 0; i < host_bridge->bus_regions_nr; ++i)
    {
        if (host_bridge->bus_regions[i].flags == PCI_BUS_REGION_F_PREFETCH)
        {
            prefetch = RT_TRUE;
            break;
        }
    }

    rt_pci_read_config_u16(pdev, PCIR_COMMAND, &command);
    command = (command & ~(PCIM_CMD_PORTEN | PCIM_CMD_MEMEN)) | PCIM_CMD_BUSMASTEREN;
    rt_pci_read_config_u8(pdev, PCIR_HDRTYPE, &hdr_type);

    if (pdev->hdr_type != hdr_type)
    {
        LOG_W("%s may not initialized", rt_dm_dev_get_name(&pdev->parent));
    }

    switch (hdr_type)
    {
    case PCIM_HDRTYPE_NORMAL:
        bars_nr = PCI_STD_NUM_BARS;
        break;

    case PCIM_HDRTYPE_BRIDGE:
        bars_nr = 2;
        break;

    case PCIM_HDRTYPE_CARDBUS:
        bars_nr = 0;
        break;

    default:
        bars_nr = 0;
        break;
    }

    for (int i = 0; i < bars_nr; ++i)
    {
        rt_ubase_t flags;
        rt_ubase_t bar_base;
        rt_bool_t mem64 = RT_FALSE;
        struct rt_pci_bus_region *region;

        cfg = 0;
        bar_base = PCIR_BAR(i);

        rt_pci_write_config_u32(pdev, bar_base, RT_UINT32_MAX);
        rt_pci_read_config_u32(pdev, bar_base, &cfg);

        if (!cfg)
        {
            continue;
        }
        else if (cfg == RT_UINT32_MAX)
        {
            rt_pci_write_config_u32(pdev, bar_base, 0UL);
            continue;
        }

        if (cfg & PCIM_BAR_SPACE)
        {
            mem64 = RT_FALSE;
            flags = PCI_BUS_REGION_F_IO;

            size = cfg & PCIM_BAR_IO_MASK;
            size &= ~(size - 1);
        }
        else
        {
            /* memory */
            if ((cfg & PCIM_BAR_MEM_TYPE_MASK) == PCIM_BAR_MEM_TYPE_64)
            {
                /* 64bits */
                rt_uint32_t cfg64;
                rt_uint64_t bar64;

                mem64 = RT_TRUE;

                rt_pci_write_config_u32(pdev, bar_base + sizeof(rt_uint32_t), RT_UINT32_MAX);
                rt_pci_read_config_u32(pdev, bar_base + sizeof(rt_uint32_t), &cfg64);

                bar64 = ((rt_uint64_t)cfg64 << 32) | cfg;

                size = ~(bar64 & PCIM_BAR_MEM_MASK) + 1;
            }
            else
            {
                /* 32bits */
                mem64 = RT_FALSE;
                size = (rt_uint32_t)(~(cfg & PCIM_BAR_MEM_MASK) + 1);
            }

            if (prefetch && (cfg & PCIM_BAR_MEM_PREFETCH))
            {
                flags = PCI_BUS_REGION_F_PREFETCH;
            }
            else
            {
                flags = PCI_BUS_REGION_F_MEM;
            }
        }

        region = rt_pci_region_alloc(host_bridge, (void **)&addr, size, flags, mem64);

        if (region)
        {
            rt_pci_write_config_u32(pdev, bar_base, addr);

            if (mem64)
            {
                bar_base += sizeof(rt_uint32_t);
            #ifdef RT_PCI_SYS_64BIT
                rt_pci_write_config_u32(pdev, bar_base, (rt_uint32_t)(addr >> 32));
            #else
                /*
                 * If we are a 64-bit decoder then increment to the upper 32 bits
                 * of the bar and force it to locate in the lower 4GB of memory.
                 */
                rt_pci_write_config_u32(pdev, bar_base, 0UL);
            #endif
            }

            pdev->resource[i].size = size;
            pdev->resource[i].base = region->cpu_addr + (addr - region->phy_addr);
            pdev->resource[i].flags = flags;

            if (mem64)
            {
                ++i;
                pdev->resource[i].flags = PCI_BUS_REGION_F_NONE;
            }
        }
        else
        {
            err = -RT_ERROR;
            LOG_W("%s alloc bar(%d) address fail", rt_dm_dev_get_name(&pdev->parent), i);
        }

        command |= (cfg & PCIM_BAR_SPACE) ? PCIM_CMD_PORTEN : PCIM_CMD_MEMEN;
    }

    if (hdr_type == PCIM_HDRTYPE_NORMAL || hdr_type == PCIM_HDRTYPE_BRIDGE)
    {
        int rom_addr = (hdr_type == PCIM_HDRTYPE_NORMAL) ? PCIR_BIOS : PCIR_BIOS_1;

        rt_pci_write_config_u32(pdev, rom_addr, 0xfffffffe);
        rt_pci_read_config_u32(pdev, rom_addr, &cfg);

        if (cfg)
        {
            size = -(cfg & ~1);

            if (rt_pci_region_alloc(host_bridge, (void **)&addr, size, PCI_BUS_REGION_F_MEM, RT_FALSE))
            {
                rt_pci_write_config_u32(pdev, rom_addr, addr);
            }
            command |= PCIM_CMD_MEMEN;
        }
    }

    rt_pci_read_config_u16(pdev, PCIR_SUBCLASS, &class);

    if (class == PCIS_DISPLAY_VGA)
    {
        command |= PCIM_CMD_PORTEN;
    }

    rt_pci_write_config_u16(pdev, PCIR_COMMAND, command);
    rt_pci_write_config_u8(pdev, PCIR_CACHELNSZ, RT_PCI_CACHE_LINE_SIZE);
    rt_pci_write_config_u8(pdev, PCIR_LATTIMER, 0x80);

    return err;
}

struct rt_pci_bus_resource *rt_pci_find_bar(struct rt_pci_device* pdev,rt_ubase_t flags,int index)
{
    for (int i = 0; i < RT_PCI_BAR_NR_MAX; i++)
    {
        if (pdev->resource[i].flags == flags)
        {
            index--;
            if (index == 0)
                return &pdev->resource[i];
        }
    }
    return RT_NULL;
}

void rt_pci_enum_device(struct rt_pci_bus *bus,
        rt_bool_t (callback(struct rt_pci_device *, void *)), void *data)
{
    rt_bool_t is_end = RT_FALSE;
    struct rt_spinlock *lock;
    struct rt_pci_bus *parent;
    struct rt_pci_device *pdev, *last_pdev = RT_NULL;

    /* Walk tree */
    while (bus && !is_end)
    {
        /* Goto bottom */
        for (;;)
        {
            lock = &bus->lock;

            spin_lock(lock);
            if (rt_list_isempty(&bus->children_nodes))
            {
                parent = bus->parent;
                break;
            }
            bus = rt_list_entry(&bus->children_nodes, struct rt_pci_bus, list);
            spin_unlock(lock);
        }

        rt_list_for_each_entry(pdev, &bus->devices_nodes, list)
        {
            if (last_pdev)
            {
                spin_unlock(lock);

                if (callback(last_pdev, data))
                {
                    spin_lock(lock);
                    --last_pdev->parent.ref_count;

                    is_end = RT_TRUE;
                    break;
                }

                spin_lock(lock);
                --last_pdev->parent.ref_count;
            }
            ++pdev->parent.ref_count;
            last_pdev = pdev;
        }

        if (!is_end && last_pdev)
        {
            spin_unlock(lock);

            if (callback(last_pdev, data))
            {
                is_end = RT_TRUE;
            }

            spin_lock(lock);
            --last_pdev->parent.ref_count;
        }
        last_pdev = RT_NULL;
        spin_unlock(lock);

        /* Up a level or goto next */
        while (!is_end)
        {
            lock = &bus->lock;

            if (!parent)
            {
                /* Root bus, is end */
                bus = RT_NULL;
                break;
            }

            spin_lock(lock);
            if (bus->list.next != &parent->children_nodes)
            {
                /* Has next sibling */
                bus = rt_list_entry(bus->list.next, struct rt_pci_bus, list);
                spin_unlock(lock);
                break;
            }

            /* All device on this buss' parent */
            rt_list_for_each_entry(pdev, &parent->devices_nodes, list)
            {
                if (last_pdev)
                {
                    spin_unlock(lock);

                    if (callback(last_pdev, data))
                    {
                        spin_lock(lock);
                        --last_pdev->parent.ref_count;

                        is_end = RT_TRUE;
                        break;
                    }

                    spin_lock(lock);
                    --last_pdev->parent.ref_count;
                }
                ++pdev->parent.ref_count;
                last_pdev = pdev;
            }

            if (!is_end && last_pdev)
            {
                spin_unlock(lock);

                if (callback(last_pdev, data))
                {
                    is_end = RT_TRUE;
                }

                spin_lock(lock);
                --last_pdev->parent.ref_count;
            }
            last_pdev = RT_NULL;

            bus = parent;
            parent = parent->parent;
            spin_unlock(lock);
        }
    }
}

const struct rt_pci_device_id *rt_pci_match_id(struct rt_pci_device *pdev,
        const struct rt_pci_device_id *id)
{
    if ((id->vendor == PCI_ANY_ID || id->vendor == pdev->vendor) &&
        (id->device == PCI_ANY_ID || id->device == pdev->device) &&
        (id->subsystem_vendor == PCI_ANY_ID || id->subsystem_vendor == pdev->subsystem_vendor) &&
        (id->subsystem_device == PCI_ANY_ID || id->subsystem_device == pdev->subsystem_device) &&
        !((id->class ^ pdev->class) & id->class_mask))
    {
        return id;
    }

    return RT_NULL;
}

const struct rt_pci_device_id *rt_pci_match_ids(struct rt_pci_device *pdev,
        const struct rt_pci_device_id *ids)
{
    while (ids->vendor || ids->subsystem_vendor || ids->class_mask)
    {
        if (rt_pci_match_id(pdev, ids))
        {
            return ids;
        }

        ++ids;
    }

    return RT_NULL;
}

static struct rt_bus pci_bus;

rt_err_t rt_pci_driver_register(struct rt_pci_driver *pdrv)
{
    RT_ASSERT(pdrv != RT_NULL);

    pdrv->parent.bus = &pci_bus;
#if RT_NAME_MAX > 0
    rt_strcpy(pdrv->parent.parent.name, pdrv->name);
#else
    pdrv->parent.parent.name = pdrv->name;
#endif

    return rt_driver_register(&pdrv->parent);
}

rt_err_t rt_pci_device_register(struct rt_pci_device *pdev)
{
    rt_err_t err;
    RT_ASSERT(pdev != RT_NULL);

    if ((err = rt_bus_add_device(&pci_bus, &pdev->parent)))
    {
        return err;
    }

    return RT_EOK;
}

static rt_bool_t pci_match(rt_driver_t drv, rt_device_t dev)
{
    rt_bool_t match = RT_FALSE;
    struct rt_pci_driver *pdrv = rt_container_of(drv, struct rt_pci_driver, parent);
    struct rt_pci_device *pdev = rt_container_of(dev, struct rt_pci_device, parent);

    if (pdrv->name && pdev->name)
    {
        match = rt_strcmp(pdrv->name, pdev->name) ? RT_FALSE : RT_TRUE;
    }

    if (!match)
    {
        pdev->id = rt_pci_match_ids(pdev, pdrv->ids);

        match = pdev->id ? RT_TRUE : RT_FALSE;
    }

    return match;
}

static rt_err_t pci_probe(rt_device_t dev)
{
    rt_err_t err = RT_EOK;
    struct rt_pci_driver *pdrv = rt_container_of(dev->drv, struct rt_pci_driver, parent);
    struct rt_pci_device *pdev = rt_container_of(dev, struct rt_pci_device, parent);

    rt_pci_assign_irq(pdev);
    rt_pci_enable_wake(pdev, RT_PCI_D0, RT_TRUE);

    err = pdrv->probe(pdev);

    if (err)
    {
        rt_pci_enable_wake(pdev, RT_PCI_D0, RT_FALSE);
    }

    return err;
}

static rt_err_t pci_remove(rt_device_t dev)
{
    rt_err_t err = RT_EOK;
    struct rt_pci_bus *bus;
    struct rt_pci_driver *pdrv = rt_container_of(dev->drv, struct rt_pci_driver, parent);
    struct rt_pci_device *pdev = rt_container_of(dev, struct rt_pci_device, parent);

    if (pdrv && pdrv->remove)
    {
        if ((err = pdrv->remove(pdev)))
        {
            return err;
        }
    }

    rt_pci_enable_wake(pdev, RT_PCI_D0, RT_FALSE);

    bus = pdev->bus;
    rt_pci_device_remove(pdev);
    /* Just try to remove */
    rt_pci_bus_remove(bus);

    return err;
}

static rt_err_t pci_shutdown(rt_device_t dev)
{
    struct rt_pci_bus *bus;
    struct rt_pci_driver *pdrv = rt_container_of(dev->drv, struct rt_pci_driver, parent);
    struct rt_pci_device *pdev = rt_container_of(dev, struct rt_pci_device, parent);

    if (pdrv && pdrv->shutdown)
    {
        pdrv->shutdown(pdev);
    }

    rt_pci_enable_wake(pdev, RT_PCI_D0, RT_FALSE);

    bus = pdev->bus;
    rt_pci_device_remove(pdev);
    /* Just try to remove */
    rt_pci_bus_remove(bus);

    return RT_EOK;
}

static struct rt_bus pci_bus =
{
    .name = "pci",
    .match = pci_match,
    .probe = pci_probe,
    .remove = pci_remove,
    .shutdown = pci_shutdown,
};

static int pci_bus_init(void)
{
    rt_bus_register(&pci_bus);

    return 0;
}
INIT_CORE_EXPORT(pci_bus_init);
