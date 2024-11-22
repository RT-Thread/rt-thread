/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "pic.gic*"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <drivers/pic.h>

#include "pic-gicv2.h"
#include "pic-gic-common.h"

void gic_common_init_quirk_ofw(const struct rt_ofw_node *ic_np, const struct gic_quirk *quirks, void *data)
{
    for (; quirks->desc; ++quirks)
    {
        if (!quirks->compatible || !rt_ofw_node_is_compatible(ic_np, quirks->compatible))
        {
            continue;
        }

        RT_ASSERT(quirks->init != RT_NULL);

        if (!quirks->init(data))
        {
            LOG_I("Enable workaround for %s", quirks->desc);
        }
    }
}

void gic_common_init_quirk_hw(rt_uint32_t iidr, const struct gic_quirk *quirks, void *data)
{
    for (; quirks->desc; ++quirks)
    {
        if (quirks->compatible)
        {
            continue;
        }

        if (quirks->iidr == (iidr & quirks->iidr_mask))
        {
            RT_ASSERT(quirks->init != RT_NULL);

            if (!quirks->init(data))
            {
                LOG_I("Enable workaround for %s", quirks->desc);
            }
        }
    }
}

void gic_common_sgi_config(void *base, void *data, int irq_base)
{
#ifdef RT_USING_SMP
    if (irq_base < 2)
    {
        struct rt_pic_irq *pirq;

#define DECLARE_GIC_IPI(ipi, hwirq)             \
        rt_pic_config_ipi(data, ipi, hwirq);    \
        pirq = rt_pic_find_ipi(data, ipi);      \
        pirq->mode = RT_IRQ_MODE_EDGE_RISING;   \

        DECLARE_GIC_IPI(RT_SCHEDULE_IPI, RT_SCHEDULE_IPI);
        DECLARE_GIC_IPI(RT_STOP_IPI, RT_STOP_IPI);
        DECLARE_GIC_IPI(RT_SMP_CALL_IPI, RT_SMP_CALL_IPI);

#undef DECLARE_GIC_IPI
    }
#endif /* RT_USING_SMP */
}

rt_err_t gic_common_configure_irq(void *base, int irq, rt_uint32_t mode, void (*sync_access)(void *), void *data)
{
    rt_err_t err = RT_EOK;
    rt_ubase_t level;
    rt_uint32_t val, oldval;
    rt_uint32_t confoff = (irq / 16) * 4;
    rt_uint32_t confmask = 0x2 << ((irq % 16) * 2);
    static struct rt_spinlock ic_lock = { 0 };

    level = rt_spin_lock_irqsave(&ic_lock);

    val = oldval = HWREG32(base + confoff);

    if (mode & RT_IRQ_MODE_LEVEL_MASK)
    {
        /* Level-sensitive */
        val &= ~confmask;
    }
    else if (mode & RT_IRQ_MODE_EDGE_BOTH)
    {
        /* Edge-triggered */
        val |= confmask;
    }

    if (val != oldval)
    {
        HWREG32(base + confoff) = val;

        if (HWREG32(base + confoff) != val)
        {
            err = -RT_EINVAL;
        }
        if (sync_access)
        {
            sync_access(data);
        }
    }

    rt_spin_unlock_irqrestore(&ic_lock, level);

    return err;
}

void gic_common_dist_config(void *base, int max_irqs, void (*sync_access)(void *), void *data)
{
    rt_uint32_t i;

    /* Set all global interrupts to be level triggered, active low. */
    for (i = 32; i < max_irqs; i += 16)
    {
        HWREG32(base + GIC_DIST_CONFIG + i / 4) = GICD_INT_ACTLOW_LVLTRIG;
    }

    /* Set priority on all global interrupts. */
    for (i = 32; i < max_irqs; i += 4)
    {
        HWREG32(base + GIC_DIST_PRI + i * 4 / 4) = GICD_INT_DEF_PRI_X4;
    }

    /* Disable all SPIs. */
    for (i = 32; i < max_irqs; i += 32)
    {
        HWREG32(base + GIC_DIST_ACTIVE_CLEAR + i / 8) = GICD_INT_EN_CLR_X32;
        HWREG32(base + GIC_DIST_ENABLE_CLEAR + i / 8) = GICD_INT_EN_CLR_X32;
    }

    if (sync_access)
    {
        sync_access(data);
    }
}

void gic_common_cpu_config(void *base, int nr, void (*sync_access)(void *), void *data)
{
    rt_uint32_t i;

    /* Disable all SGIs, PPIs. */
    for (i = 0; i < nr; i += 32)
    {
        HWREG32(base + GIC_DIST_ACTIVE_CLEAR + i / 8) = GICD_INT_EN_CLR_X32;
        HWREG32(base + GIC_DIST_ENABLE_CLEAR + i / 8) = GICD_INT_EN_CLR_X32;
    }

    /* Set priority on all PPI and SGI. */
    for (i = 0; i < nr; i += 4)
    {
        HWREG32(base + GIC_DIST_PRI + i * 4 / 4) = GICD_INT_DEF_PRI_X4;
    }

    if (sync_access)
    {
        sync_access(data);
    }
}

void gic_fill_ppi_affinity(rt_bitmap_t *affinity)
{
    for (int cpuid = 0; cpuid < RT_CPUS_NR; ++cpuid)
    {
        RT_IRQ_AFFINITY_SET(affinity, cpuid);
    }
}
