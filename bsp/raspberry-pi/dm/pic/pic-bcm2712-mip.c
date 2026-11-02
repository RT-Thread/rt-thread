/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 * 2025-06-19     GuEe-GUI     support upstream brcm,bcm2712-mip DT format
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.mip-msi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MIP_INT_RAISE           0x00
#define MIP_INT_CLEARE          0x10
#define MIP_INT_CFGL_HOST       0x20
#define MIP_INT_CFGH_HOST       0x30
#define MIP_INT_MASKL_HOST      0x40
#define MIP_INT_MASKH_HOST      0x50
#define MIP_INT_MASKL_VPU       0x60
#define MIP_INT_MASKH_VPU       0x70
#define MIP_INT_STATUSL_HOST    0x80
#define MIP_INT_STATUSH_HOST    0x90
#define MIP_INT_STATUSL_VPU     0xa0
#define MIP_INT_STATUSH_VPU     0xb0

struct mip_msi
{
    struct rt_pic parent;
    struct rt_pic *ppic;
    struct rt_ofw_node *pic_np;

    void *base;
    rt_ubase_t msg_addr;
    rt_uint32_t msi_base;       /* The SGI/SPI number that MSIs start */
    rt_uint32_t spi_base;       /* msi_base + 32, GIC INTID for MIP hwirq 0 */
    rt_uint32_t num_msis;       /* The number of SGIs for MSIs */
    rt_uint32_t msi_offset;     /* Shift the allocated msi up by N */
    rt_ubase_t *msi_map;

    struct rt_spinlock msi_map_lock;
};

#define raw_to_mip_msi(raw) rt_container_of(raw, struct mip_msi, parent)

static rt_err_t mip_msi_parse_pci_addr(struct rt_ofw_node *np, rt_uint64_t *addr)
{
    int nr;
    rt_uint32_t cells[2];

    nr = rt_ofw_prop_read_u32_array_index(np, "brcm,msi-pci-addr", 0, 2, cells);

    if (nr < 2)
    {
        LOG_E("brcm,msi-pci-addr needs two u32 cells, got %d", nr);
        return -RT_EINVAL;
    }

    *addr = ((rt_uint64_t)cells[0] << 32) | cells[1];

    if (rt_upper_32_bits(*addr) != 0xffU)
    {
        LOG_E("brcm,msi-pci-addr hi=%#x lo=%#x (expected hi=0xff)",
                rt_upper_32_bits(*addr), rt_lower_32_bits(*addr));
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t mip_msi_parse_intc_dt(struct mip_msi *mip, struct rt_ofw_node *np)
{
    mip->pic_np = rt_ofw_find_irq_parent(np, RT_NULL);
    if (!mip->pic_np)
    {
        LOG_E("Unable to find PIC parent");
        return -RT_EINVAL;
    }

    if (rt_ofw_prop_read_u32(np, "brcm,msi-base-spi", &mip->msi_base))
    {
        LOG_E("Unable to parse MSI base");
        return -RT_EINVAL;
    }

    if (rt_ofw_prop_read_u32(np, "brcm,msi-num-spis", &mip->num_msis))
    {
        LOG_E("Unable to parse MSI numbers");
        return -RT_EINVAL;
    }

    if (rt_ofw_prop_read_u32(np, "brcm,msi-offset", &mip->msi_offset))
    {
        mip->msi_offset = 0;
    }

    if (mip_msi_parse_pci_addr(np, &mip->msg_addr))
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t mip_msi_parse_upstream_dt(struct mip_msi *mip, struct rt_ofw_node *np)
{
    rt_err_t err;
    rt_uint64_t size;
    struct rt_ofw_cell_args args;

    if (rt_ofw_prop_read_u32(np, "brcm,msi-offset", &mip->msi_offset))
    {
        mip->msi_offset = 0;
    }

    err = rt_ofw_parse_phandle_cells(np, "msi-ranges", "#interrupt-cells", 0, &args);
    if (err)
    {
        LOG_E("Unable to parse msi-ranges");
        return err;
    }

    mip->pic_np = args.data;
    if (!mip->pic_np)
    {
        LOG_E("Unable to find MSI parent from msi-ranges");
        return -RT_EINVAL;
    }

    if (args.args_count < 2)
    {
        LOG_E("Invalid msi-ranges interrupt specifier");
        return -RT_EINVAL;
    }

    mip->msi_base = args.args[1];

    if (rt_ofw_prop_read_u32_index(np, "msi-ranges", args.args_count + 1, &mip->num_msis))
    {
        LOG_E("Unable to parse MSI count from msi-ranges");
        return -RT_EINVAL;
    }

    if (rt_ofw_get_address(np, 1, &mip->msg_addr, &size))
    {
        LOG_E("Unable to parse MSI doorbell address");
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t mip_msi_irq_init(struct rt_pic *pic)
{
    struct mip_msi *mip = raw_to_mip_msi(pic);

    mip->ppic = rt_ofw_data(mip->pic_np);

    return mip->ppic ? RT_EOK : -RT_ENOSYS;
}

static int mip_msi_parent_hwirq(struct mip_msi *mip, int hwirq)
{
    return hwirq + mip->spi_base;
}

static rt_err_t mip_msi_link_parent(struct mip_msi *mip, struct rt_pic_irq *pirq)
{
    rt_err_t err;
    int parent_irq;

    if (!mip || !pirq || !mip->ppic)
    {
        return -RT_EINVAL;
    }

    if (pirq->parent)
    {
        return RT_EOK;
    }

    parent_irq = mip->ppic->ops->irq_map(mip->ppic,
            mip_msi_parent_hwirq(mip, pirq->hwirq), RT_IRQ_MODE_EDGE_RISING);
    if (parent_irq < 0)
    {
        return parent_irq;
    }

    err = rt_pic_cascade(pirq, parent_irq);
    if (err)
    {
        LOG_E("MIP cascade virq=%d parent_irq=%d err=%d", pirq->irq, parent_irq, err);
    }

    return err;
}

static void mip_msi_irq_mask(struct rt_pic_irq *pirq)
{
    rt_pci_msi_mask_irq(pirq);
    rt_pic_irq_parent_mask(pirq);
}

static void mip_msi_irq_unmask(struct rt_pic_irq *pirq)
{
    struct mip_msi *mip = raw_to_mip_msi(pirq->pic);

    mip_msi_link_parent(mip, pirq);
    rt_pci_msi_unmask_irq(pirq);
    rt_pic_irq_parent_unmask(pirq);
}

static void mip_msi_compose_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    struct mip_msi *mip = raw_to_mip_msi(pirq->pic);

    msg->address_hi = rt_upper_32_bits(mip->msg_addr);
    msg->address_lo = rt_lower_32_bits(mip->msg_addr);
    msg->data = pirq->hwirq;
}

static int mip_msi_irq_alloc_msi(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc)
{
    rt_ubase_t level;
    rt_err_t err;
    int irq, hwirq, hwirq_index;
    struct rt_pic_irq *pirq;
    struct mip_msi *mip = raw_to_mip_msi(pic);

    RT_UNUSED(msi_desc);

    if (!mip->ppic)
    {
        LOG_E("MIP parent PIC not ready");
        return -RT_ENOSYS;
    }

    level = rt_spin_lock_irqsave(&mip->msi_map_lock);
    hwirq_index = rt_bitmap_next_clear_bit(mip->msi_map, 0, mip->num_msis);

    if (hwirq_index >= mip->num_msis)
    {
        irq = -RT_EEMPTY;
        goto _out_lock;
    }

    hwirq = hwirq_index + mip->msi_offset;

    irq = rt_pic_config_irq(pic, hwirq_index, hwirq);
    if (irq < 0)
    {
        goto _out_lock;
    }
    pirq = rt_pic_find_irq(pic, hwirq_index);

    pirq->mode = RT_IRQ_MODE_EDGE_RISING;
    err = mip_msi_link_parent(mip, pirq);
    if (err)
    {
        irq = err;
        goto _out_lock;
    }

    rt_bitmap_set_bit(mip->msi_map, hwirq_index);

_out_lock:
    rt_spin_unlock_irqrestore(&mip->msi_map_lock, level);

    return irq;
}

static void mip_msi_irq_free_msi(struct rt_pic *pic, int irq)
{
    rt_ubase_t level;
    struct rt_pic_irq *pirq;
    struct mip_msi *mip = raw_to_mip_msi(pic);

    pirq = rt_pic_find_pirq(pic, irq);

    if (!pirq)
    {
        return;
    }

    rt_hw_interrupt_mask(irq);
    rt_pic_uncascade(pirq);

    level = rt_spin_lock_irqsave(&mip->msi_map_lock);
    rt_bitmap_clear_bit(mip->msi_map, pirq->hwirq - mip->msi_offset);
    rt_spin_unlock_irqrestore(&mip->msi_map_lock, level);
}

static rt_err_t mip_msi_irq_set_state(struct rt_pic *pic, int hwirq, int type, rt_bool_t state)
{
    struct mip_msi *mip = raw_to_mip_msi(pic);
    struct rt_pic *ppic = mip->ppic;

    if (ppic->ops->irq_set_state)
    {
        return ppic->ops->irq_set_state(ppic, mip_msi_parent_hwirq(mip, hwirq),
                type, state);
    }

    return -RT_ENOSYS;
}

static rt_err_t mip_msi_irq_get_state(struct rt_pic *pic, int hwirq, int type, rt_bool_t *out_state)
{
    struct mip_msi *mip = raw_to_mip_msi(pic);
    struct rt_pic *ppic = mip->ppic;

    if (ppic->ops->irq_get_state)
    {
        return ppic->ops->irq_get_state(ppic, mip_msi_parent_hwirq(mip, hwirq),
                type, out_state);
    }

    return -RT_ENOSYS;
}

const static struct rt_pic_ops mip_msi_ops =
{
    .name = "MIP-MSI",
    .irq_init = mip_msi_irq_init,
    .irq_mask = mip_msi_irq_mask,
    .irq_unmask = mip_msi_irq_unmask,
    /* irq_eoi omitted: GIC root handler performs a single EOI. */
    .irq_set_affinity = rt_pic_irq_parent_set_affinity,
    .irq_set_triger_mode = rt_pic_irq_parent_set_triger_mode,
    .irq_compose_msi_msg = mip_msi_compose_msi_msg,
    .irq_alloc_msi = mip_msi_irq_alloc_msi,
    .irq_free_msi = mip_msi_irq_free_msi,
    .irq_set_state = mip_msi_irq_set_state,
    .irq_get_state = mip_msi_irq_get_state,
    .flags = RT_PIC_F_IRQ_ROUTING,
};

static rt_err_t mip_msi_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err;
    struct mip_msi *mip = rt_calloc(1, sizeof(*mip));

    if (!mip)
    {
        return -RT_ENOMEM;
    }

    if (!rt_strcmp(id->compatible, "brcm,bcm2712-mip-intc"))
    {
        err = mip_msi_parse_intc_dt(mip, np);
    }
    else
    {
        err = mip_msi_parse_upstream_dt(mip, np);
    }

    if (err)
    {
        goto _fail;
    }

    /* SPI offset from MSI base */
    mip->spi_base = mip->msi_base + 32;

    mip->base = rt_ofw_iomap(np, 0);

    if (!mip->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    mip->msi_map = rt_calloc(RT_BITS_TO_LONGS(mip->num_msis), sizeof(*mip->msi_map));

    if (!mip->msi_map)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    /*
     * Begin with all MSI-Xs masked in for the host, masked out for the VPU,
     * and edge-triggered.
     */
    HWREG32(mip->base + MIP_INT_MASKL_HOST) = 0;
    HWREG32(mip->base + MIP_INT_MASKH_HOST) = 0;
    HWREG32(mip->base + MIP_INT_MASKL_VPU) = ~0;
    HWREG32(mip->base + MIP_INT_MASKH_VPU) = ~0;
    HWREG32(mip->base + MIP_INT_CFGL_HOST) = ~0;
    HWREG32(mip->base + MIP_INT_CFGH_HOST) = ~0;

    LOG_D("Found %d MSIx, starting at %d (offset %d)", mip->num_msis, mip->msi_base, mip->msi_offset);

    rt_spin_lock_init(&mip->msi_map_lock);

    mip->parent.priv_data = mip;
    mip->parent.ops = &mip_msi_ops;

    rt_pic_linear_irq(&mip->parent, mip->num_msis);
    rt_pic_user_extends(&mip->parent);

    rt_ofw_data(np) = &mip->parent;
    rt_ofw_node_set_flag(np, RT_OFW_F_READLY);

    return RT_EOK;

_fail:
    if (mip->base)
    {
        rt_iounmap(mip->base);
    }

    if (mip->msi_map)
    {
        rt_free(mip->msi_map);
    }

    rt_free(mip);

    return err;
}

static const struct rt_ofw_node_id mip_msi_ofw_ids[] =
{
    { .compatible = "brcm,bcm2712-mip-intc" },
    { .compatible = "brcm,bcm2712-mip" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(mip_msi, mip_msi_ofw_ids, mip_msi_ofw_init);
