/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk.h"

struct rockchip_softrst
{
    const int *lut;

    void *regs;
    int num_per_reg;
    rt_uint8_t flags;

    struct rt_spinlock lock;
};

static rt_err_t rockchip_softrst_assert(struct rt_reset_control *rstc)
{
    int id = rstc->id, bank, offset;
    struct rockchip_softrst *softrst = rstc->rstcer->priv;

    if (softrst->lut)
    {
        id = softrst->lut[id];
    }

    bank = id / softrst->num_per_reg;
    offset = id % softrst->num_per_reg;

    if (softrst->flags & ROCKCHIP_SOFTRST_HIWORD_MASK)
    {
        HWREG32(softrst->regs + (bank * 4)) = RT_BIT(offset) | (RT_BIT(offset) << 16);
    }
    else
    {
        rt_uint32_t reg;
        rt_ubase_t level;

        level = rt_spin_lock_irqsave(&softrst->lock);

        reg = HWREG32(softrst->regs + (bank * 4));
        HWREG32(softrst->regs + (bank * 4)) = reg | RT_BIT(offset);

        rt_spin_unlock_irqrestore(&softrst->lock, level);
    }

    return RT_EOK;
}

static rt_err_t rockchip_softrst_deassert(struct rt_reset_control *rstc)
{
    int id = rstc->id, bank, offset;
    struct rockchip_softrst *softrst = rstc->rstcer->priv;

    if (softrst->lut)
    {
        id = softrst->lut[id];
    }

    bank = id / softrst->num_per_reg;
    offset = id % softrst->num_per_reg;

    if (softrst->flags & ROCKCHIP_SOFTRST_HIWORD_MASK)
    {
        HWREG32(softrst->regs + (bank * 4)) = RT_BIT(offset) << 16;
    }
    else
    {
        rt_uint32_t reg;
        rt_ubase_t level;

        level = rt_spin_lock_irqsave(&softrst->lock);

        reg = HWREG32(softrst->regs + (bank * 4));
        HWREG32(softrst->regs + (bank * 4)) = reg & ~RT_BIT(offset);

        rt_spin_unlock_irqrestore(&softrst->lock, level);
    }

    return RT_EOK;
}

static const struct rt_reset_control_ops rockchip_softrst_ops =
{
    .assert = rockchip_softrst_assert,
    .deassert = rockchip_softrst_deassert,
};

rt_err_t rockchip_register_softrst(struct rt_reset_controller *rstcer,
        struct rt_ofw_node *np, const int *lookup_table, void *regs, rt_uint8_t flags)
{
    rt_err_t err;
    struct rockchip_softrst *softrst = rt_calloc(1, sizeof(*softrst));

    if (!softrst)
    {
        return -RT_ENOMEM;
    }

    softrst->lut = lookup_table;
    softrst->regs = regs;
    softrst->flags = flags;
    softrst->num_per_reg = (flags & ROCKCHIP_SOFTRST_HIWORD_MASK) ? 16 : 32;

    rt_spin_lock_init(&softrst->lock);
    rstcer->priv = softrst;
    rstcer->ops = &rockchip_softrst_ops;
    rstcer->ofw_node = np;

    if ((err = rt_reset_controller_register(rstcer)))
    {
        rt_free(softrst);
    }

    return err;
}
