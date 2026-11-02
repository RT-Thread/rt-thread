/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.brcmstb_l2"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct brcmstb_intc_init_params
{
    int cpu_status;
    int cpu_clear;
    int cpu_mask_status;
    int cpu_mask_set;
    int cpu_mask_clear;
};

struct brcmstb_l2_intc
{
    struct rt_pic parent;

    int irq;
    void *regs;
    rt_bool_t can_wake;
    struct rt_ofw_node *np;

    const struct brcmstb_intc_init_params *params;
};

#define raw_to_brcmstb_l2_intc(raw) rt_container_of(raw, struct brcmstb_l2_intc, parent)

/* Register offsets in the L2 latched interrupt controller */
static const struct brcmstb_intc_init_params l2_edge_intc =
{
    .cpu_status         = 0x00,
    .cpu_clear          = 0x08,
    .cpu_mask_status    = 0x0c,
    .cpu_mask_set       = 0x10,
    .cpu_mask_clear     = 0x14
};

/* Register offsets in the L2 level interrupt controller */
static const struct brcmstb_intc_init_params l2_lvl_intc =
{
    .cpu_status         = 0x00,
    .cpu_clear          = -1, /* Register not present */
    .cpu_mask_status    = 0x04,
    .cpu_mask_set       = 0x08,
    .cpu_mask_clear     = 0x0c
};

/* Register offsets in the 2711 L2 level interrupt controller */
static const struct brcmstb_intc_init_params l2_2711_lvl_intc =
{
    .cpu_status         = 0x00,
    .cpu_clear          = 0x08,
    .cpu_mask_status    = 0x0c,
    .cpu_mask_set       = 0x10,
    .cpu_mask_clear     = 0x14
};

static void brcmstb_l2_intc_isr(int irqno, void *params);

static rt_err_t brcmstb_l2_intc_irq_init(struct rt_pic *pic)
{
    struct brcmstb_l2_intc *bl2 = raw_to_brcmstb_l2_intc(pic);

    bl2->irq = rt_ofw_get_irq(bl2->np, 0);

    if (bl2->irq < 0)
    {
        LOG_E("Failed to find parent interrupt");
        return -RT_EINVAL;
    }

    rt_hw_interrupt_install(bl2->irq, brcmstb_l2_intc_isr, bl2, "BRCMSTB-L2-INTC");
    rt_hw_interrupt_umask(bl2->irq);

    return RT_EOK;
}

static void brcmstb_l2_intc_irq_ack(struct rt_pic_irq *pirq)
{
    struct brcmstb_l2_intc *bl2 = raw_to_brcmstb_l2_intc(pirq->pic);

    if (bl2->params->cpu_clear >= 0)
    {
        HWREG32(bl2->regs + bl2->params->cpu_clear) = RT_BIT(pirq->hwirq);
    }
}

static void brcmstb_l2_intc_irq_mask(struct rt_pic_irq *pirq)
{
    struct brcmstb_l2_intc *bl2 = raw_to_brcmstb_l2_intc(pirq->pic);

    HWREG32(bl2->regs + bl2->params->cpu_mask_set) = RT_BIT(pirq->hwirq);
}

static void brcmstb_l2_intc_irq_unmask(struct rt_pic_irq *pirq)
{
    struct brcmstb_l2_intc *bl2 = raw_to_brcmstb_l2_intc(pirq->pic);

    HWREG32(bl2->regs + bl2->params->cpu_mask_clear) = RT_BIT(pirq->hwirq);
}

static int brcmstb_l2_intc_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    RT_IRQ_AFFINITY_SET(pirq->affinity, rt_hw_cpu_id());
    pirq->mode = mode;

    return rt_pic_config_irq(pic, hwirq, hwirq);
}

static rt_err_t brcmstb_l2_intc_irq_parse(struct rt_pic *pic,
        struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;
    struct brcmstb_l2_intc *bl2 = rt_container_of(pic, struct brcmstb_l2_intc, parent);

    if (args->args_count == 1)
    {
        out_pirq->hwirq = args->args[0];

        if (bl2->params == &l2_edge_intc)
        {
            out_pirq->mode = RT_IRQ_MODE_EDGE_RISING;
        }
        else if (bl2->params == &l2_lvl_intc || bl2->params == &l2_2711_lvl_intc)
        {
            out_pirq->mode = RT_IRQ_MODE_LEVEL_HIGH;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

const static struct rt_pic_ops brcmstb_l2_intc_ops =
{
    .name = "BRCMSTB-L2-INTC",
    .irq_init = brcmstb_l2_intc_irq_init,
    .irq_ack = brcmstb_l2_intc_irq_ack,
    .irq_mask = brcmstb_l2_intc_irq_mask,
    .irq_unmask = brcmstb_l2_intc_irq_unmask,
    .irq_map = brcmstb_l2_intc_irq_map,
    .irq_parse = brcmstb_l2_intc_irq_parse,
};

static void brcmstb_l2_intc_isr(int irqno, void *params)
{
    struct rt_pic_irq *pirq;
    rt_uint32_t hwirq, raw_status, mask_status, status;
    struct brcmstb_l2_intc *bl2 = params;

    RT_UNUSED(irqno);

    raw_status = HWREG32(bl2->regs + bl2->params->cpu_status);
    mask_status = HWREG32(bl2->regs + bl2->params->cpu_mask_status);
    status = raw_status & ~mask_status;

    if (!status)
    {
        return;
    }

    do {
        hwirq = __rt_ffs(status) - 1;
        status &= ~RT_BIT(hwirq);

        pirq = rt_pic_find_irq(&bl2->parent, hwirq);
        if (!pirq)
        {
            if (bl2->params->cpu_clear >= 0)
            {
                HWREG32(bl2->regs + bl2->params->cpu_clear) = RT_BIT(hwirq);
            }
            continue;
        }

        brcmstb_l2_intc_irq_ack(pirq);

        rt_pic_handle_isr(pirq);
    } while (status);
}

static rt_err_t brcmstb_l2_intc_ofw_intc(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err;
    const struct brcmstb_intc_init_params *params;
    struct brcmstb_l2_intc *bl2 = rt_calloc(1, sizeof(*bl2));

    if (!bl2)
    {
        return -RT_ENOMEM;
    }

    bl2->regs = rt_ofw_iomap(np, 0);

    if (!bl2->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    bl2->params = params = id->data;
    bl2->irq = -RT_EEMPTY;

    /* Disable all interrupts by default */
    HWREG32(bl2->regs + params->cpu_mask_set) = 0xffffffff;

    /* Wakeup interrupts may be retained from S5 (cold boot) */
    bl2->can_wake = rt_ofw_prop_read_bool(np, "brcm,irq-can-wake");
    if (!bl2->can_wake && params->cpu_clear >= 0)
    {
        HWREG32(bl2->regs + params->cpu_clear) = 0xffffffff;
    }

    bl2->parent.priv_data = bl2;
    bl2->parent.ops = &brcmstb_l2_intc_ops;

    bl2->np = np;
    rt_ofw_data(np) = &bl2->parent;

    rt_pic_linear_irq(&bl2->parent, 32);

    return RT_EOK;

_fail:
    if (bl2->regs)
    {
        rt_iounmap(bl2->regs);
    }

    rt_free(bl2);

    return err;
}

static const struct rt_ofw_node_id brcmstb_l2_intc_ofw_ids[] =
{
    { .compatible = "brcm,l2-intc", .data = &l2_edge_intc },
    { .compatible = "brcm,hif-spi-l2-intc", .data = &l2_edge_intc },
    { .compatible = "brcm,upg-aux-aon-l2-intc", .data = &l2_edge_intc },
    { .compatible = "brcm,bcm7271-l2-intc", .data = &l2_lvl_intc },
    { .compatible = "brcm,bcm2711-l2-intc", .data = &l2_2711_lvl_intc },
    { /* sentinel */ }
};

rt_err_t brcmstb_l2_intc_request_node(struct rt_ofw_node *np)
{
    rt_err_t err;
    struct rt_pic *pic;
    struct brcmstb_l2_intc *bl2;
    struct rt_ofw_prop *compat_prop;
    struct rt_ofw_node_id *id;

    if (!np || !rt_ofw_node_is_available(np))
    {
        return -RT_EINVAL;
    }

    pic = rt_pic_dynamic_cast(rt_ofw_data(np));
    if (pic)
    {
        bl2 = raw_to_brcmstb_l2_intc(pic);
        if (bl2->irq < 0)
        {
            err = brcmstb_l2_intc_irq_init(pic);
            if (!err)
            {
                rt_ofw_node_set_flag(np, RT_OFW_F_READLY);
            }

            return err;
        }

        return RT_EOK;
    }

    compat_prop = rt_ofw_get_prop(np, "compatible", RT_NULL);
    id = rt_ofw_prop_match(compat_prop, brcmstb_l2_intc_ofw_ids);
    if (!id)
    {
        return -RT_ENOSYS;
    }

    err = brcmstb_l2_intc_ofw_intc(np, id);
    if (err)
    {
        return err;
    }

    pic = rt_pic_dynamic_cast(rt_ofw_data(np));
    if (!pic)
    {
        return -RT_EIO;
    }

    err = brcmstb_l2_intc_irq_init(pic);
    if (err)
    {
        return err;
    }
    rt_ofw_node_set_flag(np, RT_OFW_F_READLY);

    return RT_EOK;
}

RT_PIC_OFW_DECLARE(brcmstb_l2_intc, brcmstb_l2_intc_ofw_ids, brcmstb_l2_intc_ofw_intc);
