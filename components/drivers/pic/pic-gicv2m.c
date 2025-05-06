/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-07     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.gicv2m"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <cpuport.h>
#include "pic-gic-common.h"

/*
* MSI_TYPER:
*   [31:26] Reserved
*   [25:16] lowest SPI assigned to MSI
*   [15:10] Reserved
*   [9:0]   Numer of SPIs assigned to MSI
*/
#define V2M_MSI_TYPER                   0x008
#define V2M_MSI_TYPER_BASE_SHIFT        16
#define V2M_MSI_TYPER_BASE_MASK         0x3ff
#define V2M_MSI_TYPER_NUM_MASK          0x3ff
#define V2M_MSI_SETSPI_NS               0x040
#define V2M_MIN_SPI                     32
#define V2M_MAX_SPI                     1019
#define V2M_MSI_IIDR                    0xfcc

#define V2M_MSI_TYPER_BASE_SPI(x)       (((x) >> V2M_MSI_TYPER_BASE_SHIFT) & V2M_MSI_TYPER_BASE_MASK)
#define V2M_MSI_TYPER_NUM_SPI(x)        ((x) & V2M_MSI_TYPER_NUM_MASK)

/* APM X-Gene with GICv2m MSI_IIDR register value */
#define XGENE_GICV2M_MSI_IIDR           0x06000170
/* Broadcom NS2 GICv2m MSI_IIDR register value */
#define BCM_NS2_GICV2M_MSI_IIDR         0x0000013f

/* List of flags for specific v2m implementation */
#define GICV2M_NEEDS_SPI_OFFSET         0x00000001
#define GICV2M_GRAVITON_ADDRESS_ONLY    0x00000002

struct gicv2m
{
    struct rt_pic parent;

    void *base;
    void *base_phy;
    rt_uint32_t spi_start;  /* The SPI number that MSIs start */
    rt_uint32_t spis_nr;    /* The number of SPIs for MSIs */
    rt_uint32_t spi_offset; /* Offset to be subtracted from SPI number */

    rt_bitmap_t *vectors;   /* MSI vector bitmap */
    rt_uint32_t flags;      /* Flags for v2m's specific implementation */

    void *gic;
    struct rt_spinlock lock;
};

#define raw_to_gicv2m(raw) rt_container_of(raw, struct gicv2m, parent)

static rt_ubase_t gicv2m_get_msi_addr(struct gicv2m *v2m, int hwirq)
{
    rt_ubase_t addr;

    if (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)
    {
        addr = (rt_ubase_t)v2m->base_phy | ((hwirq - 32) << 3);
    }
    else
    {
        addr = (rt_ubase_t)v2m->base_phy + V2M_MSI_SETSPI_NS;
    }

    return addr;
}

static rt_bool_t is_msi_spi_valid(rt_uint32_t base, rt_uint32_t num)
{
    if (base < V2M_MIN_SPI)
    {
        LOG_E("Invalid MSI base SPI (base: %u)", base);

        return RT_FALSE;
    }
    else if ((num == 0) || (base + num > V2M_MAX_SPI))
    {
        LOG_E("Number of SPIs (%u) exceed maximum (%u)", num, V2M_MAX_SPI - V2M_MIN_SPI + 1);

        return RT_FALSE;
    }

    return RT_TRUE;
}

static void gicv2m_irq_mask(struct rt_pic_irq *pirq)
{
    rt_pci_msi_mask_irq(pirq);
    rt_pic_irq_parent_mask(pirq);
}

static void gicv2m_irq_unmask(struct rt_pic_irq *pirq)
{
    rt_pci_msi_unmask_irq(pirq);
    rt_pic_irq_parent_unmask(pirq);
}

static void gicv2m_compose_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    rt_ubase_t addr;
    struct gicv2m *v2m = raw_to_gicv2m(pirq->pic);

    addr = gicv2m_get_msi_addr(v2m, pirq->hwirq);

    msg->address_hi = rt_upper_32_bits(addr);
    msg->address_lo = rt_lower_32_bits(addr);

    if (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)
    {
        msg->data = 0;
    }
    else
    {
        msg->data = pirq->hwirq;
    }

    if (v2m->flags & GICV2M_NEEDS_SPI_OFFSET)
    {
        msg->data -= v2m->spi_offset;
    }
}

static int gicv2m_irq_alloc_msi(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc)
{
    rt_ubase_t level;
    int irq, parent_irq, hwirq, hwirq_index;
    struct rt_pic_irq *pirq;
    struct gicv2m *v2m = raw_to_gicv2m(pic);
    struct rt_pic *ppic = v2m->gic;

    level = rt_spin_lock_irqsave(&v2m->lock);
    hwirq_index = rt_bitmap_next_clear_bit(v2m->vectors, 0, v2m->spis_nr);

    if (hwirq_index >= v2m->spis_nr)
    {
        irq = -RT_EEMPTY;
        goto _out_lock;
    }

    hwirq = v2m->spi_start + v2m->spi_offset + hwirq_index;

    parent_irq = ppic->ops->irq_map(ppic, hwirq, RT_IRQ_MODE_EDGE_RISING);
    if (parent_irq < 0)
    {
        irq = parent_irq;
        goto _out_lock;
    }

    irq = rt_pic_config_irq(pic, hwirq_index, hwirq);
    if (irq < 0)
    {
        goto _out_lock;
    }
    pirq = rt_pic_find_irq(pic, hwirq_index);

    pirq->mode = RT_IRQ_MODE_EDGE_RISING;
    rt_pic_cascade(pirq, parent_irq);

    rt_bitmap_set_bit(v2m->vectors, hwirq_index);

_out_lock:
    rt_spin_unlock_irqrestore(&v2m->lock, level);

    return irq;
}

static void gicv2m_irq_free_msi(struct rt_pic *pic, int irq)
{
    rt_ubase_t level;
    struct rt_pic_irq *pirq;
    struct gicv2m *v2m = raw_to_gicv2m(pic);

    pirq = rt_pic_find_pirq(pic, irq);

    if (!pirq)
    {
        return;
    }

    rt_pic_uncascade(pirq);

    level = rt_spin_lock_irqsave(&v2m->lock);
    rt_bitmap_clear_bit(v2m->vectors, pirq->hwirq - (v2m->spi_start + v2m->spi_offset));
    rt_spin_unlock_irqrestore(&v2m->lock, level);
}

static rt_err_t gicv2m_irq_set_state(struct rt_pic *pic, int hwirq, int type, rt_bool_t state)
{
    struct gicv2m *v2m = raw_to_gicv2m(pic);
    struct rt_pic *ppic = v2m->gic;

    return ppic->ops->irq_set_state(ppic, hwirq, type, state);
}

static rt_err_t gicv2m_irq_get_state(struct rt_pic *pic, int hwirq, int type, rt_bool_t *out_state)
{
    struct gicv2m *v2m = raw_to_gicv2m(pic);
    struct rt_pic *ppic = v2m->gic;

    return ppic->ops->irq_get_state(ppic, hwirq, type, out_state);
}

const static struct rt_pic_ops gicv2m_ops =
{
    .name = "GICv2m",
    .irq_ack = rt_pic_irq_parent_ack,
    .irq_mask = gicv2m_irq_mask,
    .irq_unmask = gicv2m_irq_unmask,
    .irq_eoi = rt_pic_irq_parent_eoi,
    .irq_set_priority = rt_pic_irq_parent_set_priority,
    .irq_set_affinity = rt_pic_irq_parent_set_affinity,
    .irq_compose_msi_msg = gicv2m_compose_msi_msg,
    .irq_alloc_msi = gicv2m_irq_alloc_msi,
    .irq_free_msi = gicv2m_irq_free_msi,
    .irq_set_state = gicv2m_irq_set_state,
    .irq_get_state = gicv2m_irq_get_state,
    .flags = RT_PIC_F_IRQ_ROUTING,
};

static const struct rt_ofw_node_id gicv2m_ofw_match[] =
{
    { .compatible = "arm,gic-v2m-frame" },
    { /* sentinel */ }
};

rt_err_t gicv2m_ofw_probe(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_node *v2m_np;

    rt_ofw_foreach_available_child_node(np, v2m_np)
    {
        struct gicv2m *v2m;
        rt_size_t bitmap_size;
        rt_uint32_t spi_start = 0, spis_nr = 0;

        if (!rt_ofw_node_match(v2m_np, gicv2m_ofw_match))
        {
            continue;
        }

        if (!rt_ofw_prop_read_bool(v2m_np, "msi-controller"))
        {
            continue;
        }

        if (!(v2m = rt_malloc(sizeof(*v2m))))
        {
            rt_ofw_node_put(v2m_np);

            err = -RT_ENOMEM;
            break;
        }

        v2m->base = rt_ofw_iomap(v2m_np, 0);

        if (!v2m->base)
        {
            LOG_E("%s: IO map failed", rt_ofw_node_full_name(v2m_np));
            continue;
        }

        v2m->base_phy = rt_kmem_v2p(v2m->base);
        v2m->flags = 0;

        if (!rt_ofw_prop_read_u32(v2m_np, "arm,msi-base-spi", &spi_start) &&
            !rt_ofw_prop_read_u32(v2m_np, "arm,msi-num-spis", &spis_nr))
        {
            LOG_I("DT overriding V2M MSI_TYPER (base:%u, num:%u)", spi_start, spis_nr);
        }

        if (spi_start && spis_nr)
        {
            v2m->spi_start = spi_start;
            v2m->spis_nr = spis_nr;
        }
        else
        {
            rt_uint32_t typer;

            /* Graviton should always have explicit spi_start/spis_nr */
            if (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)
            {
                goto _fail;
            }
            typer = HWREG32(v2m->base + V2M_MSI_TYPER);

            v2m->spi_start = V2M_MSI_TYPER_BASE_SPI(typer);
            v2m->spis_nr = V2M_MSI_TYPER_NUM_SPI(typer);
        }

        if (!is_msi_spi_valid(v2m->spi_start, v2m->spis_nr))
        {
            goto _fail;
        }

        /*
         * APM X-Gene GICv2m implementation has an erratum where
         * the MSI data needs to be the offset from the spi_start
         * in order to trigger the correct MSI interrupt. This is
         * different from the standard GICv2m implementation where
         * the MSI data is the absolute value within the range from
         * spi_start to (spi_start + num_spis).
         *
         * Broadcom NS2 GICv2m implementation has an erratum where the MSI data
         * is 'spi_number - 32'
         *
         * Reading that register fails on the Graviton implementation
         */
        if (!(v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY))
        {
            switch (HWREG32(v2m->base + V2M_MSI_IIDR))
            {
            case XGENE_GICV2M_MSI_IIDR:
                v2m->flags |= GICV2M_NEEDS_SPI_OFFSET;
                v2m->spi_offset = v2m->spi_start;
                break;

            case BCM_NS2_GICV2M_MSI_IIDR:
                v2m->flags |= GICV2M_NEEDS_SPI_OFFSET;
                v2m->spi_offset = 32;
                break;
            }
        }

        bitmap_size = RT_BITMAP_LEN(v2m->spis_nr) * sizeof(rt_bitmap_t);

        if (!(v2m->vectors = rt_calloc(1, bitmap_size)))
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        rt_spin_lock_init(&v2m->lock);

        v2m->parent.priv_data = v2m;
        v2m->parent.ops = &gicv2m_ops;
        v2m->gic = rt_ofw_data(np);

        rt_pic_linear_irq(&v2m->parent, v2m->spis_nr);
        rt_pic_user_extends(&v2m->parent);

        rt_ofw_data(v2m_np) = &v2m->parent;
        rt_ofw_node_set_flag(v2m_np, RT_OFW_F_READLY);

        continue;

    _fail:
        rt_iounmap(v2m->base);
        rt_free(v2m);

        if (err)
        {
            rt_ofw_node_put(v2m_np);
            break;
        }
    }

    return err;
}
