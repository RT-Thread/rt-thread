/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#define DBG_TAG "pcie.dw-host"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-dw.h"

static void dw_pcie_irq_ack(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;
    rt_uint32_t res, bit, ctrl;
    struct dw_pcie_port *port = pirq->pic->priv_data;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    ctrl = hwirq / MAX_MSI_IRQS_PER_CTRL;
    res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
    bit = hwirq % MAX_MSI_IRQS_PER_CTRL;

    dw_pcie_writel_dbi(pci, PCIE_MSI_INTR0_STATUS + res, RT_BIT(bit));
}

static void dw_pcie_irq_mask(struct rt_pic_irq *pirq)
{
    rt_ubase_t level;
    int hwirq = pirq->hwirq;
    rt_uint32_t res, bit, ctrl;
    struct dw_pcie_port *port = pirq->pic->priv_data;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    rt_pci_msi_mask_irq(pirq);

    level = rt_spin_lock_irqsave(&port->lock);

    ctrl = hwirq / MAX_MSI_IRQS_PER_CTRL;
    res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
    bit = hwirq % MAX_MSI_IRQS_PER_CTRL;

    port->irq_mask[ctrl] |= RT_BIT(bit);
    dw_pcie_writel_dbi(pci, PCIE_MSI_INTR0_MASK + res, port->irq_mask[ctrl]);

    rt_spin_unlock_irqrestore(&port->lock, level);
}

static void dw_pcie_irq_unmask(struct rt_pic_irq *pirq)
{
    rt_ubase_t level;
    int hwirq = pirq->hwirq;
    rt_uint32_t res, bit, ctrl;
    struct dw_pcie_port *port = pirq->pic->priv_data;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    rt_pci_msi_unmask_irq(pirq);

    level = rt_spin_lock_irqsave(&port->lock);

    ctrl = hwirq / MAX_MSI_IRQS_PER_CTRL;
    res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
    bit = hwirq % MAX_MSI_IRQS_PER_CTRL;

    port->irq_mask[ctrl] &= ~RT_BIT(bit);
    dw_pcie_writel_dbi(pci, PCIE_MSI_INTR0_MASK + res, port->irq_mask[ctrl]);

    rt_spin_unlock_irqrestore(&port->lock, level);
}

static void dw_pcie_compose_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    rt_uint64_t msi_target;
    struct dw_pcie_port *port = pirq->pic->priv_data;

    msi_target = (rt_uint64_t)port->msi_data_phy;

    msg->address_lo = rt_lower_32_bits(msi_target);
    msg->address_hi = rt_upper_32_bits(msi_target);

    msg->data = pirq->hwirq;
}

static int dw_pcie_irq_alloc_msi(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc)
{
    rt_ubase_t level;
    int irq, hwirq;
    struct rt_pic_irq *pirq;
    struct dw_pcie_port *port = pic->priv_data;

    level = rt_spin_lock_irqsave(&port->lock);
    hwirq = rt_bitmap_next_clear_bit(port->msi_map, 0, port->irq_count);

    if (hwirq >= port->irq_count)
    {
        irq = -RT_EEMPTY;
        goto _out_lock;
    }

    pirq = rt_pic_find_irq(pic, hwirq);

    irq = rt_pic_config_irq(pic, hwirq, hwirq);
    pirq->mode = RT_IRQ_MODE_EDGE_RISING;

    rt_bitmap_set_bit(port->msi_map, hwirq);

_out_lock:
    rt_spin_unlock_irqrestore(&port->lock, level);

    return irq;
}

static void dw_pcie_irq_free_msi(struct rt_pic *pic, int irq)
{
    rt_ubase_t level;
    struct rt_pic_irq *pirq;
    struct dw_pcie_port *port = pic->priv_data;

    pirq = rt_pic_find_pirq(pic, irq);

    if (!pirq)
    {
        return;
    }

    level = rt_spin_lock_irqsave(&port->lock);
    rt_bitmap_clear_bit(port->msi_map, pirq->hwirq);
    rt_spin_unlock_irqrestore(&port->lock, level);
}

const static struct rt_pic_ops dw_pci_msi_ops =
{
    .name = "DWPCI-MSI",
    .irq_ack = dw_pcie_irq_ack,
    .irq_mask = dw_pcie_irq_mask,
    .irq_unmask = dw_pcie_irq_unmask,
    .irq_compose_msi_msg = dw_pcie_compose_msi_msg,
    .irq_alloc_msi = dw_pcie_irq_alloc_msi,
    .irq_free_msi = dw_pcie_irq_free_msi,
    .flags = RT_PIC_F_IRQ_ROUTING,
};

/* MSI int handler */
rt_err_t dw_handle_msi_irq(struct dw_pcie_port *port)
{
    rt_err_t err;
    int i, pos;
    rt_bitmap_t status;
    rt_uint32_t num_ctrls;
    struct rt_pic_irq *pirq;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);
    struct rt_pic *msi_pic = port->msi_pic;

    err = -RT_EEMPTY;
    num_ctrls = RT_DIV_ROUND_UP(port->irq_count, MAX_MSI_IRQS_PER_CTRL);

    for (i = 0; i < num_ctrls; ++i)
    {
        status = dw_pcie_readl_dbi(pci, PCIE_MSI_INTR0_STATUS +
                    (i * MSI_REG_CTRL_BLOCK_SIZE));

        if (!status)
        {
            continue;
        }

        err = RT_EOK;

        rt_bitmap_for_each_set_bit(&status, pos, MAX_MSI_IRQS_PER_CTRL)
        {
            pirq = rt_pic_find_irq(msi_pic, pos + i * MAX_MSI_IRQS_PER_CTRL);

            dw_pcie_irq_ack(pirq);

            rt_pic_handle_isr(pirq);
        }
    }

    return err;
}

static void dw_pcie_msi_isr(int irqno, void *param)
{
    struct dw_pcie_port *port = param;

    dw_handle_msi_irq(port);
}

void dw_pcie_free_msi(struct dw_pcie_port *port)
{
    if (port->msi_irq >= 0)
    {
        rt_hw_interrupt_mask(port->msi_irq);
        rt_pic_detach_irq(port->msi_irq, port);
    }

    if (port->msi_data)
    {
        struct dw_pcie *pci = to_dw_pcie_from_port(port);

        rt_dma_free_coherent(pci->dev, sizeof(rt_uint64_t), port->msi_data,
                port->msi_data_phy);
    }
}

void dw_pcie_msi_init(struct dw_pcie_port *port)
{
#ifdef RT_PCI_MSI
    struct dw_pcie *pci = to_dw_pcie_from_port(port);
    rt_uint64_t msi_target = (rt_uint64_t)port->msi_data_phy;

    /* Program the msi_data_phy */
    dw_pcie_writel_dbi(pci, PCIE_MSI_ADDR_LO, rt_lower_32_bits(msi_target));
    dw_pcie_writel_dbi(pci, PCIE_MSI_ADDR_HI, rt_upper_32_bits(msi_target));
#endif
}

static const struct rt_pci_ops dw_child_pcie_ops;
static const struct rt_pci_ops dw_pcie_ops;

rt_err_t dw_pcie_host_init(struct dw_pcie_port *port)
{
    rt_err_t err;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);
    struct rt_device *dev = pci->dev;
    struct rt_pci_host_bridge *bridge;

    rt_spin_lock_init(&port->lock);

    rt_dm_dev_get_address_by_name(dev, "config", &port->cfg0_addr, &port->cfg0_size);

    if (port->cfg0_addr)
    {
        port->cfg0_base = rt_ioremap((void *)port->cfg0_addr, port->cfg0_size);

        if (!port->cfg0_base)
        {
            return -RT_EIO;
        }
    }
    else if (!port->cfg0_base)
    {
        LOG_E("Missing 'config' reg space");
    }

    if (!(bridge = rt_pci_host_bridge_alloc(0)))
    {
        return -RT_ENOMEM;
    }

    bridge->parent.ofw_node = dev->ofw_node;

    if ((err = rt_pci_host_bridge_init(bridge)))
    {
        goto _err_free_bridge;
    }

    port->bridge = bridge;

    for (int i = 0; i < bridge->bus_regions_nr; ++i)
    {
        struct rt_pci_bus_region *region = &bridge->bus_regions[i];

        switch (region->flags)
        {
        case PCI_BUS_REGION_F_IO:
            port->io_addr = region->cpu_addr;
            port->io_bus_addr = region->phy_addr;
            port->io_size = region->size;
            break;

        case PCI_BUS_REGION_F_NONE:
            port->cfg0_size = region->size;
            port->cfg0_addr = region->cpu_addr;

            if (!pci->dbi_base)
            {
                pci->dbi_base = rt_ioremap((void *)port->cfg0_addr, port->cfg0_size);

                if (!pci->dbi_base)
                {
                    LOG_E("Error with ioremap");
                    return -RT_ENOMEM;
                }
            }
            break;

        default:
            break;
        }
    }

    if (!port->cfg0_base && port->cfg0_addr)
    {
        port->cfg0_base = rt_ioremap((void *)port->cfg0_addr, port->cfg0_size);

        if (!port->cfg0_base)
        {
            return -RT_ENOMEM;
        }
    }

    if (rt_dm_dev_prop_read_u32(dev, "num-viewport", &pci->num_viewport))
    {
        pci->num_viewport = 2;
    }

    if (pci->link_gen < 1)
    {
        pci->link_gen = -1;
        rt_dm_dev_prop_read_u32(dev, "max-link-speed", &pci->link_gen);
    }

    /*
     * If a specific SoC driver needs to change the default number of vectors,
     * it needs to implement the set_irq_count callback.
     */
    if (!port->ops->set_irq_count)
    {
        port->irq_count = MSI_DEF_NUM_VECTORS;
    }
    else
    {
        port->ops->set_irq_count(port);

        if (port->irq_count > MAX_MSI_IRQS || port->irq_count == 0)
        {
            LOG_E("Invalid count of irq = %d", port->irq_count);

            return -RT_EINVAL;
        }
    }

    if (!port->ops->msi_host_init)
    {
        port->msi_pic = rt_calloc(1, sizeof(*port->msi_pic));

        if (!port->msi_pic)
        {
            return -RT_ENOMEM;
        }

        port->msi_pic->priv_data = port;
        port->msi_pic->ops = &dw_pci_msi_ops;
        rt_pic_linear_irq(port->msi_pic, port->irq_count);
        rt_pic_user_extends(port->msi_pic);

        if (port->msi_irq)
        {
            rt_hw_interrupt_install(port->msi_irq, dw_pcie_msi_isr, port, "dwc-pci-msi");
            rt_hw_interrupt_umask(port->msi_irq);
        }

        port->msi_data = rt_dma_alloc_coherent(pci->dev, sizeof(rt_uint64_t),
                &port->msi_data_phy);

        if (!port->msi_data)
        {
            err = -RT_ENOMEM;
            goto _err_free_msi;
        }
    }
    else
    {
        if ((err = port->ops->msi_host_init(port)))
        {
            return err;
        }
    }

    /* Set default bus ops */
    bridge->ops = &dw_pcie_ops;
    bridge->child_ops = &dw_child_pcie_ops;

    if (port->ops->host_init && (err = port->ops->host_init(port)))
    {
        goto _err_free_msi;
    }

    bridge->sysdata = port;

    if ((err = rt_pci_host_bridge_probe(bridge)))
    {
        goto _err_free_msi;
    }

    return RT_EOK;

_err_free_msi:
    if (!port->ops->msi_host_init)
    {
        dw_pcie_free_msi(port);

        rt_pic_cancel_irq(port->msi_pic);
        rt_free(port->msi_pic);
        port->msi_pic = RT_NULL;
    }

_err_free_bridge:
    rt_pci_host_bridge_free(bridge);
    port->bridge = RT_NULL;

    return err;
}

void dw_pcie_host_deinit(struct dw_pcie_port *port)
{
    if (!port->ops->msi_host_init)
    {
        dw_pcie_free_msi(port);
    }
}

void dw_pcie_host_free(struct dw_pcie_port *port)
{
    if (!port->ops->msi_host_init)
    {
        dw_pcie_free_msi(port);

        rt_pic_cancel_irq(port->msi_pic);
        rt_free(port->msi_pic);
    }

    if (port->bridge)
    {
        rt_pci_host_bridge_free(port->bridge);
    }
}

static void *dw_pcie_other_conf_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg)
{
    int type;
    rt_uint32_t busdev;
    struct dw_pcie_port *port = bus->sysdata;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    /*
     * Checking whether the link is up here is a last line of defense
     * against platforms that forward errors on the system bus as
     * SError upon PCI configuration transactions issued when the link is down.
     * This check is racy by definition and does not stop the system from
     * triggering an SError if the link goes down after this check is performed.
     */
    if (!dw_pcie_link_up(pci))
    {
        return RT_NULL;
    }

    busdev = PCIE_ATU_BUS(bus->number) | PCIE_ATU_DEV(RT_PCI_SLOT(devfn)) |
            PCIE_ATU_FUNC(RT_PCI_FUNC(devfn));

    if (rt_pci_is_root_bus(bus->parent))
    {
        type = PCIE_ATU_TYPE_CFG0;
    }
    else
    {
        type = PCIE_ATU_TYPE_CFG1;
    }

    dw_pcie_prog_outbound_atu(pci, 0, type, port->cfg0_addr, busdev, port->cfg0_size);

    return port->cfg0_base + reg;
}

static rt_err_t dw_pcie_other_read_conf(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t *value)
{
    rt_err_t err;
    struct dw_pcie_port *port = bus->sysdata;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    err = rt_pci_bus_read_config_uxx(bus, devfn, reg, width, value);

    if (!err && (pci->iatu_unroll_enabled & DWC_IATU_IOCFG_SHARED))
    {
        dw_pcie_prog_outbound_atu(pci, 0, PCIE_ATU_TYPE_IO,
                port->io_addr, port->io_bus_addr, port->io_size);
    }

    return err;
}

static rt_err_t dw_pcie_other_write_conf(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t value)
{
    rt_err_t err;
    struct dw_pcie_port *port = bus->sysdata;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    err = rt_pci_bus_write_config_uxx(bus, devfn, reg, width, value);

    if (!err && (pci->iatu_unroll_enabled & DWC_IATU_IOCFG_SHARED))
    {
        dw_pcie_prog_outbound_atu(pci, 0, PCIE_ATU_TYPE_IO,
                port->io_addr, port->io_bus_addr, port->io_size);
    }

    return err;
}

static const struct rt_pci_ops dw_child_pcie_ops =
{
    .map = dw_pcie_other_conf_map,
    .read = dw_pcie_other_read_conf,
    .write = dw_pcie_other_write_conf,
};

void *dw_pcie_own_conf_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg)
{
    struct dw_pcie_port *port = bus->sysdata;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    if (RT_PCI_SLOT(devfn) > 0)
    {
        return RT_NULL;
    }

    return pci->dbi_base + reg;
}

static const struct rt_pci_ops dw_pcie_ops =
{
    .map = dw_pcie_own_conf_map,
    .read = rt_pci_bus_read_config_uxx,
    .write = rt_pci_bus_write_config_uxx,
};

void dw_pcie_setup_rc(struct dw_pcie_port *port)
{
    rt_uint32_t val, num_ctrls;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    /*
     * Enable DBI read-only registers for writing/updating configuration.
     * Write permission gets disabled towards the end of this function.
     */
    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    dw_pcie_setup(pci);

    if (!port->ops->msi_host_init)
    {
        num_ctrls = RT_DIV_ROUND_UP(port->irq_count, MAX_MSI_IRQS_PER_CTRL);

        /* Initialize IRQ Status array */
        for (int ctrl = 0; ctrl < num_ctrls; ++ctrl)
        {
            port->irq_mask[ctrl] = ~0;

            dw_pcie_writel_dbi(pci, PCIE_MSI_INTR0_MASK +
                    (ctrl * MSI_REG_CTRL_BLOCK_SIZE), port->irq_mask[ctrl]);
            dw_pcie_writel_dbi(pci, PCIE_MSI_INTR0_ENABLE +
                    (ctrl * MSI_REG_CTRL_BLOCK_SIZE), ~0);
        }
    }

    /* Setup RC BARs */
    dw_pcie_writel_dbi(pci, PCIR_BAR(0), PCIM_BAR_MEM_TYPE_64);
    dw_pcie_writel_dbi(pci, PCIR_BAR(1), PCIM_BAR_MEM_TYPE_32);

    /* Setup interrupt pins */
    val = dw_pcie_readl_dbi(pci, PCIR_INTLINE);
    val &= 0xffff00ff;
    val |= 0x00000100;
    dw_pcie_writel_dbi(pci, PCIR_INTLINE, val);

    /* Setup bus numbers */
    val = dw_pcie_readl_dbi(pci, PCIR_PRIBUS_1);
    val &= 0xff000000;
    val |= 0x00ff0100;
    dw_pcie_writel_dbi(pci, PCIR_PRIBUS_1, val);

    /* Setup command register */
    val = dw_pcie_readl_dbi(pci, PCIR_COMMAND);
    val &= 0xffff0000;
    val |= PCIM_CMD_PORTEN | PCIM_CMD_MEMEN | PCIM_CMD_BUSMASTEREN | PCIM_CMD_SERRESPEN;
    dw_pcie_writel_dbi(pci, PCIR_COMMAND, val);

    /*
     * If the platform provides its own child bus config accesses, it means
     * the platform uses its own address translation component rather than
     * ATU, so we should not program the ATU here.
     */
    if (pci->port.bridge->child_ops == &dw_child_pcie_ops)
    {
        int atu_idx = 0;
        struct rt_pci_host_bridge *bridge = port->bridge;

        /* Get last memory resource entry */
        for (int i = 0; i < bridge->bus_regions_nr; ++i)
        {
            struct rt_pci_bus_region *region = &bridge->bus_regions[i];

            if (region->flags != PCI_BUS_REGION_F_MEM)
            {
                continue;
            }

            if (pci->num_viewport <= ++atu_idx)
            {
                break;
            }

            dw_pcie_prog_outbound_atu(pci, atu_idx,
                    PCIE_ATU_TYPE_MEM, region->cpu_addr,
                    region->phy_addr, region->size);
        }

        if (port->io_size)
        {
            if (pci->num_viewport > ++atu_idx)
            {
                dw_pcie_prog_outbound_atu(pci, atu_idx,
                        PCIE_ATU_TYPE_IO, port->io_addr,
                        port->io_bus_addr, port->io_size);
            }
            else
            {
                pci->iatu_unroll_enabled |= DWC_IATU_IOCFG_SHARED;
            }
        }

        if (pci->num_viewport <= atu_idx)
        {
            LOG_W("Resources exceed number of ATU entries (%d)", pci->num_viewport);
        }
    }

    dw_pcie_writel_dbi(pci, PCIR_BAR(0), 0);

    /* Program correct class for RC */
    dw_pcie_writew_dbi(pci, PCIR_SUBCLASS, PCIS_BRIDGE_PCI);

    val = dw_pcie_readl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
    val |= PORT_LOGIC_SPEED_CHANGE;
    dw_pcie_writel_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);

    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);
}
