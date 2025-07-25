/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "reset-simple.h"

struct reset_simple_data
{
    rt_uint32_t reg_offset;
    rt_bool_t active_low;
    rt_bool_t status_active_low;
};

#define raw_to_reset_simple(raw) rt_container_of(raw, struct reset_simple, parent)

static rt_err_t reset_simple_update(struct reset_simple *rsts, int id, rt_bool_t assert)
{
    rt_uint32_t reg;
    rt_ubase_t level;
    int reg_width = sizeof(rt_uint32_t);
    int bank = id / (reg_width * 8);
    int offset = id % (reg_width * 8);

    level = rt_spin_lock_irqsave(&rsts->lock);

    reg = HWREG32(rsts->mmio_base + (bank * reg_width));

    if (assert ^ rsts->active_low)
    {
        reg |= RT_BIT(offset);
    }
    else
    {
        reg &= ~RT_BIT(offset);
    }

    HWREG32(rsts->mmio_base + (bank * reg_width)) = reg;

    rt_spin_unlock_irqrestore(&rsts->lock, level);

    return RT_EOK;
}

static rt_err_t reset_simple_assert(struct rt_reset_control *rstc)
{
    struct reset_simple *rsts = raw_to_reset_simple(rstc);

    return reset_simple_update(rsts, rstc->id, RT_TRUE);
}

static rt_err_t reset_simple_deassert(struct rt_reset_control *rstc)
{
    struct reset_simple *rsts = raw_to_reset_simple(rstc);

    return reset_simple_update(rsts, rstc->id, RT_FALSE);
}

static rt_err_t reset_simple_reset(struct rt_reset_control *rstc)
{
    rt_err_t err;
    struct reset_simple *rsts = raw_to_reset_simple(rstc);

    if (!rsts->reset_us)
    {
        return -RT_ENOSYS;
    }

    if ((err = reset_simple_assert(rstc)))
    {
        return err;
    }

    rt_hw_us_delay(rsts->reset_us + (rsts->reset_us >> 1));

    return reset_simple_deassert(rstc);
}

static int reset_simple_status(struct rt_reset_control *rstc)
{
    rt_uint32_t value;
    int reg_width = sizeof(rt_uint32_t);
    int bank = rstc->id / (reg_width * 8);
    int offset = rstc->id % (reg_width * 8);
    struct reset_simple *rsts = raw_to_reset_simple(rstc);

    value = HWREG32(rsts->mmio_base + (bank * reg_width));

    return !(value & RT_BIT(offset)) ^ !rsts->status_active_low;
}

const struct rt_reset_control_ops reset_simple_ops =
{
    .reset = reset_simple_reset,
    .assert = reset_simple_assert,
    .deassert = reset_simple_deassert,
    .status = reset_simple_status,
};

static rt_err_t reset_simple_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_reset_controller *rstcer;
    struct rt_device *dev = &pdev->parent;
    const struct reset_simple_data *rsts_data = pdev->id->data;
    struct reset_simple *rsts = rt_calloc(1, sizeof(*rsts));

    if (!rsts)
    {
        return -RT_ENOMEM;
    }

    rsts->mmio_base = rt_dm_dev_iomap(dev, 0);

    if (!rsts->mmio_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rt_spin_lock_init(&rsts->lock);

    rstcer = &rsts->parent;

    rstcer->priv = rsts;
    rstcer->ofw_node = dev->ofw_node;
    rstcer->ops = &reset_simple_ops;

    if ((err = rt_reset_controller_register(rstcer)))
    {
        goto _fail;
    }

    if (rsts_data)
    {
        rsts->mmio_base += rsts_data->reg_offset;
        rsts->active_low = rsts_data->active_low;
        rsts->status_active_low = rsts_data->status_active_low;
    }

    return RT_EOK;

_fail:
    if (rsts->mmio_base)
    {
        rt_iounmap(rsts->mmio_base);
    }

    rt_free(rsts);

    return err;
}

static const struct reset_simple_data reset_simple_socfpga =
{
    .reg_offset = 0x20,
    .status_active_low = RT_TRUE,
};

static const struct reset_simple_data reset_simple_active_low =
{
    .active_low = RT_TRUE,
    .status_active_low = RT_TRUE,
};

static const struct rt_ofw_node_id reset_simple_ofw_ids[] =
{
    { .compatible = "altr,stratix10-rst-mgr", .data = &reset_simple_socfpga },
    { .compatible = "st,stm32-rcc", },
    { .compatible = "allwinner,sun6i-a31-clock-reset", .data = &reset_simple_active_low },
    { .compatible = "zte,zx296718-reset", .data = &reset_simple_active_low },
    { .compatible = "aspeed,ast2400-lpc-reset" },
    { .compatible = "aspeed,ast2500-lpc-reset" },
    { .compatible = "aspeed,ast2600-lpc-reset" },
    { .compatible = "bitmain,bm1880-reset", .data = &reset_simple_active_low },
    { .compatible = "brcm,bcm4908-misc-pcie-reset", .data = &reset_simple_active_low },
    { .compatible = "snps,dw-high-reset" },
    { .compatible = "snps,dw-low-reset", .data = &reset_simple_active_low },
    { .compatible = "sophgo,sg2042-reset", .data = &reset_simple_active_low },
    { /* sentinel */ }
};

static struct rt_platform_driver reset_simple_driver =
{
    .name = "reset-simple",
    .ids = reset_simple_ofw_ids,

    .probe = reset_simple_probe,
};

static int reset_simple_register(void)
{
    rt_platform_driver_register(&reset_simple_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(reset_simple_register);
