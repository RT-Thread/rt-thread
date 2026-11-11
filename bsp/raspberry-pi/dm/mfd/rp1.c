/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "mfd.rp1"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dt-bindings/mfd/rp1.h>

#define PCI_DEVICE_ID_RP1_C0    0x0001

#define RP1_PCI_BAR0_OFFSET     0x410000ULL
#define RP1_PCI_BAR1_OFFSET     0x0ULL
#define RP1_PCI_BAR2_OFFSET     0x400000ULL



#define RP1_ACTUAL_IRQS         RP1_INT_END
#define RP1_IRQS                RP1_ACTUAL_IRQS

#define RP1_SYSCLK_RATE         200000000
#define RP1_SYSCLK_FPGA_RATE    60000000

#define REG_RW                  0x000
#define REG_SET                 0x800
#define REG_CLR                 0xc00

#define MSIX_CFG(x)             (0x8 + (4 * (x)))

#define MSIX_CFG_IACK_EN        RT_BIT(3)
#define MSIX_CFG_IACK           RT_BIT(2)
#define MSIX_CFG_TEST           RT_BIT(1)
#define MSIX_CFG_ENABLE         RT_BIT(0)

#define INTSTATL                0x108
#define INTSTATH                0x10c

struct rp1_device
{
    struct rt_pic parent;
    struct rt_pci_device *pdev;

    rt_ubase_t bar_start;
    rt_ubase_t bar_end;

    struct rt_clk *sys_clk;
    struct rt_pci_msix_entry msix_entries[RP1_IRQS];
    rt_bool_t rp1_level_triggered_irq[RP1_ACTUAL_IRQS];

    void *msix_cfg_regs;
    struct rt_pic *msi_pic;
};

#define raw_to_rp1(raw) rt_container_of(raw, struct rp1_device, parent)

extern void brcm_pcie_reapply_maps(struct rt_pci_device *pdev);

rt_inline rt_ubase_t rp1_io_to_phys(struct rp1_device *rp1, int offset)
{
    return rp1->bar_start + offset;
}

static void msix_cfg_set(struct rp1_device *rp1, int hwirq, rt_uint32_t value)
{
    HWREG32(rp1->msix_cfg_regs + REG_SET + MSIX_CFG(hwirq)) = value;
}

static void msix_cfg_clr(struct rp1_device *rp1, int hwirq, rt_uint32_t value)
{
    HWREG32(rp1->msix_cfg_regs + REG_CLR + MSIX_CFG(hwirq)) = value;
}

static void rp1_sync_pci_bar_config(struct rt_pci_device *pdev)
{
    rt_uint16_t cmd;
    rt_uint32_t bar0, bar1, bar2;
    static const rt_uint32_t want[] = {
        (rt_uint32_t)RP1_PCI_BAR0_OFFSET,
        (rt_uint32_t)RP1_PCI_BAR1_OFFSET,
        (rt_uint32_t)RP1_PCI_BAR2_OFFSET,
    };

    rt_pci_read_config_u32(pdev, PCIR_BAR(0), &bar0);
    rt_pci_read_config_u32(pdev, PCIR_BAR(1), &bar1);
    rt_pci_read_config_u32(pdev, PCIR_BAR(2), &bar2);

    if ((bar0 & ~0xfU) == want[0] && (bar1 & ~0xfU) == want[1] &&
            (bar2 & ~0xfU) == want[2])
    {
        return;
    }

    rt_pci_read_config_u16(pdev, PCIR_COMMAND, &cmd);
    rt_pci_write_config_u16(pdev, PCIR_COMMAND, cmd & ~PCIM_CMD_MEMEN);

    rt_pci_write_config_u32(pdev, PCIR_BAR(1), want[1]);
    rt_pci_write_config_u32(pdev, PCIR_BAR(1) + 4, 0);
    rt_pci_write_config_u32(pdev, PCIR_BAR(2), want[2]);
    rt_pci_write_config_u32(pdev, PCIR_BAR(2) + 4, 0);
    rt_pci_write_config_u32(pdev, PCIR_BAR(0), want[0]);

    rt_pci_write_config_u16(pdev, PCIR_COMMAND, cmd);
}

/*
 * RP1 BAR CPU bases come from the host bridge MEM window + fixed PCI decode
 * offsets (BAR1=0). Generic BAR assign may leave resource[1].base at the
 * wrong anchor (e.g. win+0x400000); never use that as the window base.
 */
static rt_ubase_t rp1_host_mem_cpu(struct rt_pci_device *pdev)
{
    struct rt_pci_host_bridge *hb = rt_pci_find_host_bridge(pdev->bus);

    if (!hb)
    {
        return 0;
    }

    for (int j = 0; j < hb->bus_regions_nr; ++j)
    {
        struct rt_pci_bus_region *mem = &hb->bus_regions[j];

        if (mem->flags == PCI_BUS_REGION_F_MEM && mem->size > 0)
        {
            rt_uint64_t pci = RP1_PCI_BAR1_OFFSET;

            if (pci >= mem->phy_addr &&
                    pci < mem->phy_addr + mem->size)
            {
                return mem->cpu_addr + (pci - mem->phy_addr);
            }
        }
    }

    return 0;
}

static void rp1_sync_bar_resources(struct rt_pci_device *pdev)
{
    rt_ubase_t win = rp1_host_mem_cpu(pdev);

    if (!win)
    {
        LOG_W("RP1: no MEM window anchor for BAR sync");
        return;
    }

    if (pdev->resource[0].size == 0 || (pdev->resource[0].flags & PCI_BUS_REGION_F_NONE))
    {
        pdev->resource[0].size = 0x4000;
        pdev->resource[0].flags = PCI_BUS_REGION_F_MEM;
    }
    pdev->resource[0].base = win + RP1_PCI_BAR0_OFFSET;

    if (pdev->resource[1].size == 0 || (pdev->resource[1].flags & PCI_BUS_REGION_F_NONE))
    {
        pdev->resource[1].size = 0x400000;
        pdev->resource[1].flags = PCI_BUS_REGION_F_MEM;
    }
    pdev->resource[1].base = win;

    if (pdev->resource[2].size == 0 || (pdev->resource[2].flags & PCI_BUS_REGION_F_NONE))
    {
        pdev->resource[2].size = 0x10000;
        pdev->resource[2].flags = PCI_BUS_REGION_F_MEM;
    }
    pdev->resource[2].base = win + RP1_PCI_BAR2_OFFSET;
}

/*
 * Reset RP1 BAR config + resource[] before MSI-X enable so generic
 * msix_table_remap() can use resource[bir].base (BIR 0 on Pi5).
 */
static void rp1_prepare_msix_bars(struct rt_pci_device *pdev)
{
    rp1_sync_pci_bar_config(pdev);
    rp1_sync_bar_resources(pdev);
}

static void rp1_msix_reprogram(struct rp1_device *rp1)
{
    struct rt_pci_device *pdev = rp1->pdev;
    struct rt_pic *msi_pic = rp1->msi_pic;
    struct rt_pci_msi_desc *desc;

    if (!pdev || !pdev->msix_enabled || !msi_pic || !msi_pic->ops->irq_compose_msi_msg)
    {
        return;
    }

    rt_pci_msi_for_each_desc(pdev, desc)
    {
        struct rt_pic_irq *pirq = rt_pic_find_pirq(msi_pic, desc->irq);

        if (!pirq)
        {
            continue;
        }

        msi_pic->ops->irq_compose_msi_msg(pirq, &desc->msg);
        rt_pci_msi_write_msg(desc, &desc->msg);
    }
}

static void rp1_irq_eoi(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;
    struct rp1_device *rp1 = raw_to_rp1(pirq->pic);

    /* Pulse IACK after the device ISR has cleared the level source, not before. */
    if (rp1->rp1_level_triggered_irq[hwirq])
    {
        msix_cfg_set(rp1, hwirq, MSIX_CFG_IACK);
    }
}

static void rp1_irq_mask(struct rt_pic_irq *pirq)
{
    struct rt_pic_irq *parent = pirq->parent;

    if (parent && parent->msi_desc)
    {
        rt_pci_msi_mask_irq(parent);
    }

    rt_pic_irq_parent_mask(pirq);
}

static void rp1_irq_unmask(struct rt_pic_irq *pirq)
{
    struct rt_pic_irq *parent = pirq->parent;

    /* Unmask the underlying PCI MSIX vector. */
    if (parent && parent->msi_desc)
    {
        rt_pci_msi_unmask_irq(parent);
    }

    rt_pic_irq_parent_unmask(pirq);
}

static rt_err_t rp1_irq_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    int hwirq = pirq->hwirq;
    struct rp1_device *rp1 = raw_to_rp1(pirq->pic);

    switch (mode)
    {
    case RT_IRQ_MODE_LEVEL_HIGH:
        msix_cfg_set(rp1, hwirq, MSIX_CFG_IACK_EN);
        rp1->rp1_level_triggered_irq[hwirq] = RT_TRUE;
        break;

    case RT_IRQ_MODE_EDGE_RISING:
        msix_cfg_clr(rp1, hwirq, MSIX_CFG_IACK_EN);
        rp1->rp1_level_triggered_irq[hwirq] = RT_FALSE;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static int rp1_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq;
    struct rp1_device *rp1 = raw_to_rp1(pic);
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    irq = rt_pic_config_irq(pic, hwirq, hwirq);

    pirq->mode = mode;
    rp1_irq_set_triger_mode(pirq, mode);

    /* Enable RP1-side MSIX routing. */
    msix_cfg_set(rp1, hwirq, MSIX_CFG_ENABLE);

    rt_pic_cascade(pirq, rp1->msix_entries[hwirq].irq);

    return irq;
}

static rt_err_t rp1_irq_parse(struct rt_pic *pic,
        struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    out_pirq->hwirq = args->args[0];
    out_pirq->mode = args->args[1] & RT_IRQ_MODE_MASK;

    return RT_EOK;
}

const static struct rt_pic_ops rp1_ops =
{
    .name = "RP1",
    .irq_eoi = rp1_irq_eoi,
    .irq_mask = rp1_irq_mask,
    .irq_unmask = rp1_irq_unmask,
    .irq_set_triger_mode = rp1_irq_set_triger_mode,
    .irq_map = rp1_irq_map,
    .irq_parse = rp1_irq_parse,
    .flags = RT_PIC_F_IRQ_ROUTING,
};

static rt_err_t rp1_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct rp1_device *rp1;
    struct rt_ofw_node *rp1_np, *pcie_np;

    pcie_np = rt_pci_find_host_bridge(pdev->bus)->parent.ofw_node;

    if (!pcie_np)
    {
        return -RT_EINVAL;
    }

    rp1 = rt_calloc(1, sizeof(*rp1));

    if (!rp1)
    {
        return -RT_ENOMEM;
    }

    rp1->pdev = pdev;

    rt_pci_pme_active(pdev, RT_TRUE);

    rt_pci_set_master(pdev);

    /*
     * Ensure PCIe inbound/outbound windows are active before MSIX table
     * programming and RP1 MMIO.
     */
    brcm_pcie_reapply_maps(pdev);

    rp1_prepare_msix_bars(pdev);

    rt_pci_msix_entry_index_linear(rp1->msix_entries, RP1_IRQS);

    if (rt_pci_msix_enable(pdev, rp1->msix_entries, RP1_IRQS) != RP1_IRQS)
    {
        err = -RT_ERROR;
        goto _fail;
    }

    rp1->msi_pic = pdev->msi_pic;
    rp1_msix_reprogram(rp1);
    rp1->bar_start = pdev->resource[1].base;
    rp1->bar_end = rp1->bar_start + pdev->resource[1].size;

    rp1->msix_cfg_regs = rt_ioremap((void *)rp1_io_to_phys(rp1, RP1_PCIE_APBS_BASE), 0x1000);

    if (!rp1->msix_cfg_regs)
    {
        err = -RT_EIO;
        goto _free_pci;
    }

    if (!(rp1_np = rt_ofw_get_child_by_tag(pcie_np, "rp1")))
    {
        LOG_E("Could not find RP1 node under %s", rt_ofw_node_full_name(pcie_np));
        err = -RT_EINVAL;
        goto _free_msix;
    }

    rp1->parent.priv_data = rp1;
    rp1->parent.ops = &rp1_ops;
    rt_pic_linear_irq(&rp1->parent, RP1_IRQS);
    rt_pic_user_extends(&rp1->parent);

    rt_ofw_data(rp1_np) = &rp1->parent;
    rt_platform_ofw_request(rp1_np);

    rt_ofw_node_put(rp1_np);

    return RT_EOK;

_free_msix:
    rt_iounmap(rp1->msix_cfg_regs);

_free_pci:
    rt_pci_free_vector(pdev);

_fail:
    rt_free(rp1);

    return err;
}

static const struct rt_pci_device_id rp1_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_RPI, PCI_DEVICE_ID_RP1_C0) },
    { /* sentinel */ }
};

static struct rt_pci_driver rp1_driver =
{
    .name = "rp1",

    .ids = rp1_ids,
    .probe = rp1_probe,
};
RT_PCI_DRIVER_EXPORT(rp1_driver);
