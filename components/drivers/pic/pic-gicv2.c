/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 * 2014-04-03     Grissiom     many enhancements
 * 2018-11-22     Jesven       add rt_hw_ipi_send()
 *                             add rt_hw_ipi_handler_install()
 * 2022-08-24     GuEe-GUI     add pic support
 * 2022-11-07     GuEe-GUI     add v2m support
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.gicv2"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

#include <ioremap.h>

#include "pic-gicv2.h"
#include "pic-gic-common.h"

#define GIC_CPU_IMAX 8

#define raw_to_gicv2(raw) rt_container_of(raw, struct gicv2, parent)

static rt_bool_t needs_rmw_access = RT_FALSE;
static int _gicv2_nr = 0, _init_cpu_id = 0;
static struct gicv2 _gicv2_list[RT_PIC_ARM_GIC_MAX_NR] = {};
static rt_bool_t _gicv2_eoi_mode_ns = RT_FALSE;
static rt_uint8_t _gicv2_cpumask_map[GIC_CPU_IMAX] =
{
    [0 ... GIC_CPU_IMAX - 1] = 0xff,
};

static rt_uint8_t gicv2_cpumask_map(struct gicv2 *gic)
{
    rt_uint32_t mask, i;

    for (i = mask = 0; i < 32; i += 4)
    {
        mask = HWREG32(gic->dist_base + GIC_DIST_TARGET + i);
        mask |= mask >> 16;
        mask |= mask >> 8;

        if (mask)
        {
            break;
        }
    }

    return mask;
}

static void gicv2_dist_init(struct gicv2 *gic)
{
    void *base = gic->dist_base;
    rt_uint32_t i;
    rt_uint32_t cpumask = gicv2_cpumask_map(gic);

    gic->max_irq = HWREG32(base + GIC_DIST_TYPE) & 0x1f;
    gic->max_irq = (gic->max_irq + 1) * 32;

    /*
     * The GIC only supports up to 1020 interrupt sources.
     * Limit this to either the architected maximum, or the
     * platform maximum.
     */
    if (gic->max_irq > 1020)
    {
        gic->max_irq = 1020;
    }

    LOG_D("Max irq = %d", gic->max_irq);

    HWREG32(base + GIC_DIST_CTRL) = GICD_DISABLE;

    /* Set all global (unused) interrupts to this CPU only. */
    cpumask |= cpumask << 8;
    cpumask |= cpumask << 16;

    for (i = 32; i < gic->max_irq; i += 4)
    {
        HWREG32(base + GIC_DIST_TARGET + i * 4 / 4) = cpumask;
    }

    gic_common_dist_config(base, gic->max_irq, RT_NULL, RT_NULL);

    HWREG32(base + GIC_DIST_CTRL) = GICD_ENABLE;
}

static void gicv2_cpu_init(struct gicv2 *gic)
{
    rt_uint32_t cpumask;
    void *base = gic->cpu_base;
    rt_uint32_t config = GICC_ENABLE;
    int cpu_id = _init_cpu_id = rt_hw_cpu_id();

    cpumask = gicv2_cpumask_map(gic);
    _gicv2_cpumask_map[cpu_id] = cpumask;

    /*
     * Clear our mask from the other map entries in case they're
     * still undefined.
     */
    for (int i = 0; i < RT_ARRAY_SIZE(_gicv2_cpumask_map); ++i)
    {
        if (i != cpu_id)
        {
            _gicv2_cpumask_map[i] &= ~cpumask;
        }
    }

    gic_common_cpu_config(gic->dist_base, 32, RT_NULL, RT_NULL);

    HWREG32(base + GIC_CPU_PRIMASK) = GICC_INT_PRI_THRESHOLD;
    HWREG32(base + GIC_CPU_BINPOINT) = 0x7;

#ifdef ARCH_SUPPORT_HYP
    _gicv2_eoi_mode_ns = RT_TRUE;
#endif

    if (_gicv2_eoi_mode_ns)
    {
        config |= GIC_CPU_CTRL_EOI_MODE_NS;
    }

    HWREG32(base + GIC_CPU_CTRL) = config;
}

static rt_err_t gicv2_irq_init(struct rt_pic *pic)
{
    gicv2_cpu_init(rt_container_of(pic, struct gicv2, parent));

    return RT_EOK;
}

static void gicv2_irq_ack(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;
    struct gicv2 *gic = raw_to_gicv2(pirq->pic);

    if (!_gicv2_eoi_mode_ns)
    {
        HWREG32(gic->dist_base + GIC_DIST_PENDING_CLEAR + hwirq / 32 * 4) = 1U << (hwirq % 32);
    }

    HWREG32(gic->cpu_base + GIC_CPU_EOI) = hwirq;
}

static void gicv2_irq_mask(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;
    struct gicv2 *gic = raw_to_gicv2(pirq->pic);

    HWREG32(gic->dist_base + GIC_DIST_ENABLE_CLEAR + hwirq / 32 * 4) = 1U << (hwirq % 32);
}

static void gicv2_irq_unmask(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;
    struct gicv2 *gic = raw_to_gicv2(pirq->pic);

    HWREG32(gic->dist_base + GIC_DIST_ENABLE_SET + hwirq / 32 * 4) = 1U << (hwirq % 32);
}

static void gicv2_irq_eoi(struct rt_pic_irq *pirq)
{
    struct gicv2 *gic = raw_to_gicv2(pirq->pic);

    if (_gicv2_eoi_mode_ns)
    {
        HWREG32(gic->cpu_base + GIC_CPU_DIR) = pirq->hwirq;
    }
}

static rt_err_t gicv2_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    rt_uint32_t mask;
    int hwirq = pirq->hwirq;
    struct gicv2 *gic = raw_to_gicv2(pirq->pic);

    mask = HWREG32(gic->dist_base + GIC_DIST_PRI + hwirq / 4 * 4);
    mask &= ~(0xffU << ((hwirq % 4) * 8));
    mask |= ((priority & 0xffU) << ((hwirq % 4) * 8));
    HWREG32(gic->dist_base + GIC_DIST_PRI + hwirq / 4 * 4) = mask;

    return RT_EOK;
}

static rt_err_t gicv2_irq_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    int hwirq = pirq->hwirq;
    struct gicv2 *gic = raw_to_gicv2(pirq->pic);
    rt_uint32_t target_list = ((rt_uint8_t *)affinity)[gic - &_gicv2_list[0]];
    rt_uint8_t valb = _gicv2_cpumask_map[__rt_ffs(target_list) - 1];
    void *io_addr = gic->dist_base + GIC_DIST_TARGET + hwirq;

    if (needs_rmw_access)
    {
        /* RMW write byte */
        rt_uint32_t val;
        rt_ubase_t level;
        rt_ubase_t offset = (rt_ubase_t)io_addr & 3UL, shift = offset * 8;
        static struct rt_spinlock rmw_lock = {};

        level = rt_spin_lock_irqsave(&rmw_lock);

        io_addr -= offset;
        val = HWREG32(io_addr);
        val &= ~RT_GENMASK(shift + 7, shift);
        val |= valb << shift;
        HWREG32(io_addr) = val;

        rt_spin_unlock_irqrestore(&rmw_lock, level);
    }
    else
    {
        HWREG8(io_addr) = valb;
    }

    return RT_EOK;
}

static rt_err_t gicv2_irq_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    rt_err_t err = RT_EOK;
    int hwirq = pirq->hwirq;
    struct gicv2 *gic = raw_to_gicv2(pirq->pic);

    if (hwirq >= GIC_SGI_NR)
    {
        err = gic_common_configure_irq(gic->dist_base + GIC_DIST_CONFIG, pirq->hwirq, mode, RT_NULL, RT_NULL);
    }
    else
    {
        err = -RT_ENOSYS;
    }

    return err;
}

static void gicv2_irq_send_ipi(struct rt_pic_irq *pirq, rt_bitmap_t *cpumask)
{
    struct gicv2 *gic;
    int sgi = pirq->hwirq;
    rt_uint8_t *target_list = (rt_uint8_t *)cpumask;

    for (int i = 0; i < _gicv2_nr; ++i)
    {
        if (*target_list)
        {
            gic = &_gicv2_list[i];

            HWREG32(gic->dist_base + GIC_DIST_SOFTINT) = ((*target_list & 0xffU) << 16) | (sgi & 0xf);

            rt_hw_dsb();
        }

        ++target_list;
    }
}

static int gicv2_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq, irq_index = hwirq - GIC_SGI_NR;
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, irq_index);

    if (pirq && hwirq >= GIC_SGI_NR)
    {
        pirq->mode = mode;
        pirq->priority = GICD_INT_DEF_PRI;
        rt_bitmap_set_bit(pirq->affinity, _init_cpu_id);

        irq = rt_pic_config_irq(pic, irq_index, hwirq);

        if (irq >= 0 && mode != RT_IRQ_MODE_LEVEL_HIGH)
        {
            gicv2_irq_set_triger_mode(pirq, mode);
        }
    }
    else
    {
        irq = -1;
    }

    return irq;
}

static rt_err_t gicv2_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;

    if (args->args_count == 3)
    {
        out_pirq->mode = args->args[2] & RT_IRQ_MODE_MASK;

        switch (args->args[0])
        {
        case 0:
            /* SPI */
            out_pirq->hwirq = args->args[1] + 32;
            break;
        case 1:
            /* PPI */
            out_pirq->hwirq = args->args[1] + 16;
            break;
        default:
            err = -RT_ENOSYS;
            break;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static struct rt_pic_ops gicv2_ops =
{
    .name = "GICv2",
    .irq_init = gicv2_irq_init,
    .irq_ack = gicv2_irq_ack,
    .irq_mask = gicv2_irq_mask,
    .irq_unmask = gicv2_irq_unmask,
    .irq_eoi = gicv2_irq_eoi,
    .irq_set_priority = gicv2_irq_set_priority,
    .irq_set_affinity = gicv2_irq_set_affinity,
    .irq_set_triger_mode = gicv2_irq_set_triger_mode,
    .irq_send_ipi = gicv2_irq_send_ipi,
    .irq_map = gicv2_irq_map,
    .irq_parse = gicv2_irq_parse,
};

static rt_bool_t gicv2_handler(void *data)
{
    rt_bool_t res = RT_FALSE;
    int hwirq;
    struct gicv2 *gic = data;

    hwirq = HWREG32(gic->cpu_base + GIC_CPU_INTACK) & 0x3ffUL;

    if (!(hwirq >= 1020 && hwirq <= 1023))
    {
        struct rt_pic_irq *pirq;

        if (hwirq < GIC_SGI_NR)
        {
            rt_hw_rmb();

            pirq = rt_pic_find_ipi(&gic->parent, hwirq);
        }
        else
        {
            pirq = rt_pic_find_irq(&gic->parent, hwirq - GIC_SGI_NR);
        }

        gicv2_irq_ack(pirq);

        rt_pic_handle_isr(pirq);

        gicv2_irq_eoi(pirq);

        res = RT_TRUE;
    }

    return res;
}

static rt_err_t gicv2_enable_rmw_access(void *data)
{
    if (rt_ofw_machine_is_compatible("renesas,emev2"))
    {
        needs_rmw_access = RT_TRUE;
        return RT_EOK;
    }

    return -RT_EINVAL;
}

static const struct gic_quirk _gicv2_quirks[] =
{
    {
        .desc       = "GICv2: Broken byte access",
        .compatible = "arm,pl390",
        .init       = gicv2_enable_rmw_access,
    },
    { /* sentinel */ }
};

static rt_err_t gicv2_iomap_init(struct gicv2 *gic, rt_uint64_t *regs)
{
    rt_err_t err = RT_EOK;
    int idx;
    const char *name[] =
    {
        "Distributor",
        "CPU interfaces",
        "Virtual interface control",
        "Virtual CPU interface",
    };

    do {
        /* GICD->GICC->GICH->GICV */
        gic->dist_size = regs[1];
        gic->dist_base = rt_ioremap((void *)regs[0], gic->dist_size);
        if (!gic->dist_base)
        {
            idx = 0;
            err = -RT_ERROR;
            break;
        }

        gic->cpu_size = regs[3];
        gic->cpu_base = rt_ioremap((void *)regs[2], gic->cpu_size);
        if (!gic->cpu_base)
        {
            idx = 1;
            err = -RT_ERROR;
            break;
        }

        /* ArchRev[4:7] */
        gic->version = HWREG32(gic->dist_base + GIC_DIST_ICPIDR2) >> 4;

    #ifdef ARCH_SUPPORT_HYP
        if (gic->version == 1)
        {
            break;
        }

        gic->hyp_size = regs[5];
        gic->hyp_base = rt_ioremap((void *)regs[4], gic->hyp_size);
        if (!gic->hyp_base)
        {
            idx = 2;
            err = -RT_ERROR;
            break;
        }

        gic->vcpu_size = regs[7];
        gic->vcpu_base = rt_ioremap((void *)regs[6], gic->vcpu_size);
        if (!gic->vcpu_base)
        {
            idx = 3;
            err = -RT_ERROR;
            break;
        }
    #endif /* ARCH_SUPPORT_HYP */
    } while (0);

    if (err)
    {
        RT_UNUSED(idx);
        RT_UNUSED(name);

        LOG_E("gic[%d] %s IO[%p, %p] map fail", _gicv2_nr, name[idx], regs[idx * 2], regs[idx * 2 + 1]);
    }

    return err;
}

static void gicv2_init(struct gicv2 *gic)
{
    gicv2_dist_init(gic);

    gic->parent.priv_data = gic;
    gic->parent.ops = &gicv2_ops;

    rt_pic_linear_irq(&gic->parent, gic->max_irq + 1 - GIC_SGI_NR);
    gic_common_sgi_config(gic->dist_base, &gic->parent, _gicv2_nr * GIC_SGI_NR);

    rt_pic_add_traps(gicv2_handler, gic);

    rt_pic_user_extends(&gic->parent);
}

static void gicv2_init_fail(struct gicv2 *gic)
{
    if (gic->dist_base)
    {
        rt_iounmap(gic->dist_base);
    }
    if (gic->cpu_base)
    {
        rt_iounmap(gic->cpu_base);
    }
    if (gic->hyp_base)
    {
        rt_iounmap(gic->hyp_base);
    }
    if (gic->vcpu_base)
    {
        rt_iounmap(gic->vcpu_base);
    }
    rt_memset(gic, 0, sizeof(*gic));
}

static rt_err_t gicv2_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err = RT_EOK;
    struct gicv2 *gic = RT_NULL;

    do {
        rt_uint64_t regs[8];

        if (_gicv2_nr >= RT_PIC_ARM_GIC_MAX_NR)
        {
            LOG_W("GICv2/v1 table is full");
            err = -RT_EFULL;
            break;
        }

        gic = &_gicv2_list[_gicv2_nr];

        rt_ofw_get_address_array(np, RT_ARRAY_SIZE(regs), regs);

        if ((err = gicv2_iomap_init(gic, regs)))
        {
            break;
        }

        if (gic->version != 1 && gic->version != 2)
        {
            LOG_E("Version = %d is not support", gic->version);
            err = -RT_EINVAL;
            break;
        }

        gic_common_init_quirk_ofw(np, _gicv2_quirks, gic);
        gicv2_init(gic);

        rt_ofw_data(np) = &gic->parent;

        if (gic->version == 2)
        {
        #ifdef RT_PIC_ARM_GIC_V2M
            gicv2m_ofw_probe(np, id);
        #endif
        }

        ++_gicv2_nr;
    } while (0);

    if (err && gic)
    {
        gicv2_init_fail(gic);
    }

    return err;
}

static const struct rt_ofw_node_id gicv2_ofw_ids[] =
{
    { .compatible = "arm,gic-400" },
    { .compatible = "arm,arm11mp-gic" },
    { .compatible = "arm,arm1176jzf-devchip-gic" },
    { .compatible = "arm,cortex-a15-gic" },
    { .compatible = "arm,cortex-a9-gic" },
    { .compatible = "arm,cortex-a7-gic" },
    { .compatible = "qcom,msm-8660-qgic" },
    { .compatible = "qcom,msm-qgic2" },
    { .compatible = "arm,pl390" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(gicv2, gicv2_ofw_ids, gicv2_ofw_init);
