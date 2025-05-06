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

#define DBG_TAG "pci.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pci.h>
#include <drivers/ofw.h>
#include <drivers/ofw_io.h>
#include <drivers/ofw_irq.h>
#include <drivers/ofw_fdt.h>

static rt_err_t pci_ofw_irq_parse(struct rt_pci_device *pdev, struct rt_ofw_cell_args *out_irq)
{
    rt_err_t err = RT_EOK;
    rt_uint8_t pin;
    fdt32_t map_addr[4];
    struct rt_pci_device *p2pdev;
    struct rt_ofw_node *dev_np, *p2pnode = RT_NULL;

    /* Parse device tree if dev have a device node */
    dev_np = pdev->parent.ofw_node;

    if (dev_np)
    {
        err = rt_ofw_parse_irq_cells(dev_np, 0, out_irq);

        if (err)
        {
            return err;
        }
    }

    /* Assume #interrupt-cells is 1 */
    if ((err = rt_pci_read_config_u8(pdev, PCIR_INTPIN, &pin)))
    {
        goto _err;
    }

    /* No pin, exit with no error message. */
    if (pin == 0)
    {
        return -RT_ENOSYS;
    }

    /* Try local interrupt-map in the device node */
    if (rt_ofw_prop_read_raw(dev_np, "interrupt-map", RT_NULL))
    {
        pin = rt_pci_irq_intx(pdev, pin);
        p2pnode = dev_np;
    }

    /* Walk up the PCI tree */
    while (!p2pnode)
    {
        p2pdev = pdev->bus->self;

        /* Is the root bus -> host bridge */
        if (rt_pci_is_root_bus(pdev->bus))
        {
            struct rt_pci_host_bridge *host_bridge = pdev->bus->host_bridge;

            p2pnode = host_bridge->parent.ofw_node;

            if (!p2pnode)
            {
                err = -RT_EINVAL;

                goto _err;
            }
        }
        else
        {
            /* Is P2P bridge */
            p2pnode = p2pdev->parent.ofw_node;
        }

        if (p2pnode)
        {
            break;
        }

        /* Try get INTx in P2P */
        pin = rt_pci_irq_intx(pdev, pin);
        pdev = p2pdev;
    }

    /* For more format detail, please read `components/drivers/ofw/irq.c:ofw_parse_irq_map` */
    out_irq->data = map_addr;
    out_irq->args_count = 2;
    out_irq->args[0] = 3;
    out_irq->args[1] = 1;

    /* In addr cells */
    map_addr[0] = cpu_to_fdt32((pdev->bus->number << 16) | (pdev->devfn << 8));
    map_addr[1] = cpu_to_fdt32(0);
    map_addr[2] = cpu_to_fdt32(0);
    /* In pin cells */
    map_addr[3] = cpu_to_fdt32(pin);

    err = rt_ofw_parse_irq_map(p2pnode, out_irq);

_err:
    if (err == -RT_EEMPTY)
    {
        LOG_W("PCI-Device<%s> no interrupt-map found, INTx interrupts not available",
                rt_dm_dev_get_name(&pdev->parent));
        LOG_W("PCI-Device<%s> possibly some PCI slots don't have level triggered interrupts capability",
                rt_dm_dev_get_name(&pdev->parent));
    }
    else if (err && err != -RT_ENOSYS)
    {
        LOG_E("PCI-Device<%s> irq parse failed with err = %s",
                rt_dm_dev_get_name(&pdev->parent), rt_strerror(err));
    }

    return err;
}

int rt_pci_ofw_irq_parse_and_map(struct rt_pci_device *pdev,
        rt_uint8_t slot, rt_uint8_t pin)
{
    int irq = -1;
    rt_err_t status;
    struct rt_ofw_cell_args irq_args;

    if (!pdev)
    {
        goto _end;
    }

    status = pci_ofw_irq_parse(pdev, &irq_args);

    if (status)
    {
        goto _end;
    }

    irq = rt_ofw_map_irq(&irq_args);

    if (irq >= 0)
    {
        pdev->intx_pic = rt_pic_dynamic_cast(rt_ofw_data(irq_args.data));
    }

_end:
    return irq;
}

static rt_err_t pci_ofw_parse_ranges(struct rt_ofw_node *dev_np, const char *propname,
        int phy_addr_cells, int phy_size_cells, int cpu_addr_cells,
        struct rt_pci_bus_region **out_regions, rt_size_t *out_regions_nr)
{
    const fdt32_t *cell;
    rt_ssize_t total_cells;
    int groups, space_code;
    rt_uint32_t phy_addr[3];
    rt_uint64_t cpu_addr, phy_addr_size;

    *out_regions = RT_NULL;
    *out_regions_nr = 0;
    cell = rt_ofw_prop_read_raw(dev_np, propname, &total_cells);

    if (!cell)
    {
        return -RT_EEMPTY;
    }

    groups = total_cells / sizeof(*cell) / (phy_addr_cells + phy_size_cells + cpu_addr_cells);
    *out_regions = rt_malloc(groups * sizeof(struct rt_pci_bus_region));

    if (!*out_regions)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < groups; ++i)
    {
        /*
         * ranges:
         *  phys.hi  cell: npt000ss bbbbbbbb dddddfff rrrrrrrr
         *  phys.low cell: llllllll llllllll llllllll llllllll
         *  phys.mid cell: hhhhhhhh hhhhhhhh hhhhhhhh hhhhhhhh
         *
         *  n: relocatable region flag (doesn't play a role here)
         *  p: prefetchable (cacheable) region flag
         *  t: aliased address flag (doesn't play a role here)
         *  ss: space code
         *      00: configuration space
         *      01: I/O space
         *      10: 32 bit memory space
         *      11: 64 bit memory space
         *  bbbbbbbb: The PCI bus number
         *  ddddd: The device number
         *  fff: The function number. Used for multifunction PCI devices.
         *  rrrrrrrr: Register number; used for configuration cycles.
         */

        for (int j = 0; j < phy_addr_cells; ++j)
        {
            phy_addr[j] = rt_fdt_read_number(cell++, 1);
        }

        space_code = (phy_addr[0] >> 24) & 0x3;

        cpu_addr = rt_fdt_read_number(cell, cpu_addr_cells);
        cell += cpu_addr_cells;
        phy_addr_size = rt_fdt_read_number(cell, phy_size_cells);
        cell += phy_size_cells;

        (*out_regions)[i].phy_addr = ((rt_uint64_t)phy_addr[1] << 32) | phy_addr[2];
        (*out_regions)[i].cpu_addr = cpu_addr;
        (*out_regions)[i].size = phy_addr_size;

        (*out_regions)[i].bus_start = (*out_regions)[i].phy_addr;

        if (space_code & 2)
        {
            (*out_regions)[i].flags = phy_addr[0] & (1U << 30) ?
                    PCI_BUS_REGION_F_PREFETCH : PCI_BUS_REGION_F_MEM;
        }
        else if (space_code & 1)
        {
            (*out_regions)[i].flags = PCI_BUS_REGION_F_IO;
        }
        else
        {
            (*out_regions)[i].flags = PCI_BUS_REGION_F_NONE;
        }

        ++*out_regions_nr;
    }

    return RT_EOK;
}

rt_err_t rt_pci_ofw_parse_ranges(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err;
    int phy_addr_cells = -1, phy_size_cells = -1, cpu_addr_cells;

    if (!dev_np || !host_bridge)
    {
        return -RT_EINVAL;
    }

    cpu_addr_cells = rt_ofw_io_addr_cells(dev_np);
    rt_ofw_prop_read_s32(dev_np, "#address-cells", &phy_addr_cells);
    rt_ofw_prop_read_s32(dev_np, "#size-cells", &phy_size_cells);

    if (phy_addr_cells != 3 || phy_size_cells < 1 || cpu_addr_cells < 1)
    {
        return -RT_EINVAL;
    }

    if (pci_ofw_parse_ranges(dev_np, "ranges",
        phy_addr_cells, phy_size_cells, cpu_addr_cells,
        &host_bridge->bus_regions, &host_bridge->bus_regions_nr))
    {
        return -RT_EINVAL;
    }

    if ((err = rt_pci_region_setup(host_bridge)))
    {
        rt_free(host_bridge->bus_regions);
        host_bridge->bus_regions_nr = 0;

        return err;
    }

    err = pci_ofw_parse_ranges(dev_np, "dma-ranges",
            phy_addr_cells, phy_size_cells, cpu_addr_cells,
            &host_bridge->dma_regions, &host_bridge->dma_regions_nr);

    if (err != -RT_EEMPTY)
    {
        rt_free(host_bridge->bus_regions);
        host_bridge->bus_regions_nr = 0;

        LOG_E("%s: Read dma-ranges error = %s", rt_ofw_node_full_name(dev_np),
                rt_strerror(err));

        return err;
    }

    return RT_EOK;
}

rt_err_t rt_pci_ofw_host_bridge_init(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge)
{
    rt_err_t err;
    const char *propname;

    if (!dev_np || !host_bridge)
    {
        return -RT_EINVAL;
    }

    host_bridge->irq_slot = rt_pci_irq_slot;
    host_bridge->irq_map = rt_pci_ofw_irq_parse_and_map;

    if (rt_ofw_prop_read_u32_array_index(dev_np, "bus-range", 0, 2, host_bridge->bus_range) < 0)
    {
        return -RT_EIO;
    }

    propname = rt_ofw_get_prop_fuzzy_name(dev_np, ",pci-domain$");
    rt_ofw_prop_read_u32(dev_np, propname, &host_bridge->domain);

    err = rt_pci_ofw_parse_ranges(dev_np, host_bridge);

    return err;
}

rt_err_t rt_pci_ofw_bus_init(struct rt_pci_bus *bus)
{
    rt_err_t err = RT_EOK;

    return err;
}

rt_err_t rt_pci_ofw_bus_free(struct rt_pci_bus *bus)
{
    rt_err_t err = RT_EOK;

    return err;
}

/*
 * RID (Requester ID) is formatted such that:
 *  Bits [15:8] are the Bus number.
 *  Bits [7:3] are the Device number.
 *  Bits [2:0] are the Function number.
 *
 * msi-map: Maps a Requester ID to an MSI controller and associated
 *  msi-specifier data. The property is an arbitrary number of tuples of
 *  (rid-base,msi-controller,msi-base,length), where:
 *
 *    - rid-base is a single cell describing the first RID matched by the entry.
 *
 *    - msi-controller is a single phandle to an MSI controller
 *
 *    - msi-base is an msi-specifier describing the msi-specifier produced for
 *      the first RID matched by the entry.
 *
 *    - length is a single cell describing how many consecutive RIDs are matched
 *      following the rid-base.
 *
 *  Any RID r in the interval [rid-base, rid-base + length) is associated with
 *  the listed msi-controller, with the msi-specifier (r - rid-base + msi-base).
 *
 * msi-map-mask: A mask to be applied to each Requester ID prior to being mapped
 *  to an msi-specifier per the msi-map property.
 *
 * msi-parent: Describes the MSI parent of the root complex itself. Where
 *  the root complex and MSI controller do not pass sideband data with MSI
 *  writes, this property may be used to describe the MSI controller(s)
 *  used by PCI devices under the root complex, if defined as such in the
 *  binding for the root complex.
 *
 *  / {
 *      #address-cells = <1>;
 *      #size-cells = <1>;
 *
 *      msi_a: msi-controller@a {
 *          reg = <0xa 0x1>;
 *          msi-controller;
 *          #msi-cells = <1>;
 *      };
 *
 *      msi_b: msi-controller@b {
 *          reg = <0xb 0x1>;
 *          msi-controller;
 *          #msi-cells = <1>;
 *      };
 *
 *      msi_c: msi-controller@c {
 *          reg = <0xc 0x1>;
 *          msi-controller;
 *          #msi-cells = <1>;
 *      };
 *
 *  Example (1)
 *  ===========
 *      pci: pci@f {
 *          reg = <0xf 0x1>;
 *          device_type = "pci";
 *
 *          // The sideband data provided to the MSI controller is
 *          //  the RID, identity-mapped.
 *          msi-map = <0x0 &msi_a 0x0 0x10000>;
 *      };
 *
 *  Example (2)
 *  ===========
 *      pci: pci@ff {
 *          reg = <0xff 0x1>;
 *          device_type = "pci";
 *
 *          // The sideband data provided to the MSI controller is
 *          //  the RID, masked to only the device and function bits.
 *          msi-map = <0x0 &msi_a 0x0 0x100>;
 *          msi-map-mask = <0xff>
 *      };
 *
 *  Example (3)
 *  ===========
 *      pci: pci@fff {
 *          reg = <0xfff 0x1>;
 *          device_type = "pci";
 *
 *          // The sideband data provided to the MSI controller is
 *          //  the RID, but the high bit of the bus number is ignored.
 *          msi-map = <0x0000 &msi_a 0x0000 0x8000>,
 *                    <0x8000 &msi_a 0x0000 0x8000>;
 *      };
 *
 *  Example (4)
 *  ===========
 *      pci: pci@f {
 *          reg = <0xf 0x1>;
 *          device_type = "pci";
 *
 *          // The sideband data provided to the MSI controller is
 *          //  the RID, but the high bit of the bus number is negated.
 *          msi-map = <0x0000 &msi 0x8000 0x8000>,
 *                    <0x8000 &msi 0x0000 0x8000>;
 *      };
 *
 *  Example (5)
 *  ===========
 *      pci: pci@f {
 *          reg = <0xf 0x1>;
 *          device_type = "pci";
 *
 *          // The sideband data provided to MSI controller a is the
 *          //  RID, but the high bit of the bus number is negated.
 *          // The sideband data provided to MSI controller b is the
 *          //  RID, identity-mapped.
 *          // MSI controller c is not addressable.
 *          msi-map = <0x0000 &msi_a 0x8000 0x08000>,
 *                    <0x8000 &msi_a 0x0000 0x08000>,
 *                    <0x0000 &msi_b 0x0000 0x10000>;
 *      };
 *  };
 */
static void ofw_msi_pic_init(struct rt_pci_device *pdev)
{
#ifdef RT_PCI_MSI
    rt_uint32_t rid;
    struct rt_pci_host_bridge *bridge;
    struct rt_ofw_node *np, *msi_ic_np = RT_NULL;

    /*
     * NOTE: Typically, a device's RID is equal to the PCI device's ID.
     * However, in complex bus management scenarios such as servers and PCs,
     * the RID needs to be associated with DMA. In these cases,
     * the RID should be equal to the DMA alias assigned to the
     * PCI device by the system bus.
     */
    rid = rt_pci_dev_id(pdev);

    bridge = rt_pci_find_host_bridge(pdev->bus);
    RT_ASSERT(bridge != RT_NULL);

    np = bridge->parent.ofw_node;

    if (!(msi_ic_np = rt_ofw_parse_phandle(np, "msi-parent", 0)))
    {
        rt_ofw_map_id(np, rid, "msi-map", "msi-map-mask", &msi_ic_np, RT_NULL);
    }

    if (!msi_ic_np)
    {
        LOG_W("%s: MSI PIC not found", rt_dm_dev_get_name(&pdev->parent));

        return;
    }

    pdev->msi_pic = rt_pic_dynamic_cast(rt_ofw_data(msi_ic_np));

    if (!pdev->msi_pic)
    {
        LOG_W("%s: '%s' not supported", rt_dm_dev_get_name(&pdev->parent), "msi-parent");

        goto _out_put_msi_parent_node;
    }

    if (!pdev->msi_pic->ops->irq_compose_msi_msg)
    {
        LOG_E("%s: MSI pic MUST implemented %s",
                rt_ofw_node_full_name(msi_ic_np), "irq_compose_msi_msg");
        RT_ASSERT(0);
    }

    if (!pdev->msi_pic->ops->irq_alloc_msi)
    {
        LOG_E("%s: MSI pic MUST implemented %s",
                rt_ofw_node_full_name(msi_ic_np), "irq_alloc_msi");
        RT_ASSERT(0);
    }

    if (!pdev->msi_pic->ops->irq_free_msi)
    {
        LOG_E("%s: MSI pic MUST implemented %s",
                rt_ofw_node_full_name(msi_ic_np), "irq_free_msi");
        RT_ASSERT(0);
    }

_out_put_msi_parent_node:
    rt_ofw_node_put(msi_ic_np);
#endif
}

static rt_int32_t ofw_pci_devfn(struct rt_ofw_node *np)
{
    rt_int32_t res;
    rt_uint32_t reg[5];

    res = rt_ofw_prop_read_u32_array_index(np, "reg", 0, RT_ARRAY_SIZE(reg), reg);

    return res > 0 ? ((reg[0] >> 8) & 0xff) : res;
}

static struct rt_ofw_node *ofw_find_device(struct rt_ofw_node *np, rt_uint32_t devfn)
{
    struct rt_ofw_node *dev_np, *mfd_np;

    rt_ofw_foreach_child_node(np, dev_np)
    {
        if (ofw_pci_devfn(dev_np) == devfn)
        {
            return dev_np;
        }

        if (rt_ofw_node_tag_equ(dev_np, "multifunc-device"))
        {
            rt_ofw_foreach_child_node(dev_np, mfd_np)
            {
                if (ofw_pci_devfn(mfd_np) == devfn)
                {
                    rt_ofw_node_put(dev_np);

                    return mfd_np;
                }
            }
        }
    }

    return RT_NULL;
}

rt_err_t rt_pci_ofw_device_init(struct rt_pci_device *pdev)
{
    struct rt_ofw_node *np = RT_NULL;

    if (!pdev)
    {
        return -RT_EINVAL;
    }

    ofw_msi_pic_init(pdev);

    if (rt_pci_is_root_bus(pdev->bus) || !pdev->bus->self)
    {
        struct rt_pci_host_bridge *host_bridge;

        host_bridge = rt_pci_find_host_bridge(pdev->bus);
        RT_ASSERT(host_bridge != RT_NULL);

        np = host_bridge->parent.ofw_node;
    }
    else
    {
        np = pdev->bus->self->parent.ofw_node;
    }

    if (np)
    {
        pdev->parent.ofw_node = ofw_find_device(np, pdev->devfn);
    }

    return RT_EOK;
}

rt_err_t rt_pci_ofw_device_free(struct rt_pci_device *pdev)
{
    if (!pdev)
    {
        return -RT_EINVAL;
    }

    rt_ofw_node_put(pdev->parent.ofw_node);

    return RT_EOK;
}
