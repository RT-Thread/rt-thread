/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "ccu_mix.h"

#define DBG_TAG "clk.ccu.mix"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define TIMEOUT_LIMIT   20000   /* Max timeout 10000us */

static int twsi8_reg_val = 0x04;
static const char *tswi8_clk_name = "twsi8_clk";

static void ccu_mix_disable(struct rt_clk_cell *cell)
{
    rt_uint32_t tmp;
    rt_ubase_t level, rate;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;
    struct ccu_gate_config *gate = mix->gate;

    if (!gate)
    {
        return;
    }

    if (!rt_strcmp(cell->name, tswi8_clk_name))
    {
        twsi8_reg_val &= ~gate->gate_mask;
        twsi8_reg_val |= gate->val_disable;
        tmp = twsi8_reg_val;

        if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
            common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
        {
            HWREG32(common->base + common->reg_sel) = tmp;
        }
        else
        {
            HWREG32(common->base + common->reg_ctrl) = tmp;
        }

        return;
    }

    if (common->lock)
    {
        level = rt_spin_lock_irqsave(common->lock);
    }

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        tmp = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        tmp = HWREG32(common->base + common->reg_ctrl);
    }

    tmp &= ~gate->gate_mask;
    tmp |= gate->val_disable;

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        HWREG32(common->base + common->reg_sel) = tmp;
    }
    else
    {
        HWREG32(common->base + common->reg_ctrl) = tmp;
    }

    if (common->lock)
    {
        rt_spin_unlock_irqrestore(common->lock, level);
    }

    if (gate->flags & SPACEMIT_CLK_GATE_NEED_DELAY)
    {
        rate = rt_clk_cell_get_rate(cell);

        if (rate == 0)
        {
            LOG_E("%s clock rate is 0", cell->name);
        }
        else
        {
            /* Need delay 2M cycles. */
            rt_hw_us_delay(RT_DIV_ROUND_UP(2000000, rate));
        }
    }
}

static rt_err_t ccu_mix_enable(struct rt_clk_cell *cell)
{
    rt_ubase_t level, rate;
    rt_uint32_t tmp, val = 0, timeout_power = 1;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;
    struct ccu_gate_config *gate = mix->gate;

    if (!gate)
    {
        return RT_EOK;
    }

    if (!rt_strcmp(cell->name, tswi8_clk_name))
    {
        twsi8_reg_val &= ~gate->gate_mask;
        twsi8_reg_val |= gate->val_enable;
        tmp = twsi8_reg_val;

        if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
            common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
        {
            HWREG32(common->base + common->reg_sel) = tmp;
        }
        else
        {
            HWREG32(common->base + common->reg_ctrl) = tmp;
        }

        return RT_EOK;
    }

    if (common->lock)
    {
        level = rt_spin_lock_irqsave(common->lock);
    }

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        tmp = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        tmp = HWREG32(common->base + common->reg_ctrl);
    }

    tmp &= ~gate->gate_mask;
    tmp |= gate->val_enable;

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        HWREG32(common->base + common->reg_sel) = tmp;
    }
    else
    {
        HWREG32(common->base + common->reg_ctrl) = tmp;
    }

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        val = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        val = HWREG32(common->base + common->reg_ctrl);
    }

    if (common->lock)
    {
        rt_spin_unlock_irqrestore(common->lock, level);
    }

    while ((val & gate->gate_mask) != gate->val_enable && timeout_power < TIMEOUT_LIMIT)
    {
        rt_hw_us_delay(timeout_power);

        if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
            common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
        {
            val = HWREG32(common->base + common->reg_sel);
        }
        else
        {
            val = HWREG32(common->base + common->reg_ctrl);
        }

        timeout_power *= 10;
    }

    if (timeout_power > 1)
    {
        if (val == tmp)
        {
            LOG_E("%s write clk_gate timeout occur, read pass after %d us delay",
                    cell->name, timeout_power);
        }
        else
        {
            LOG_E("%s write clk_gate timeout after %d us", cell->name, timeout_power);
        }
    }

    if (gate->flags & SPACEMIT_CLK_GATE_NEED_DELAY)
    {
        rate = rt_clk_cell_get_rate(cell);

        if (rate == 0)
        {
            LOG_E("%s clock rate is 0", cell->name);
        }
        else
        {
            /* Need delay 2M cycles. */
            rt_hw_us_delay(RT_DIV_ROUND_UP(2000000, rate));
        }
    }

    return RT_EOK;
}

static rt_bool_t ccu_mix_is_enabled(struct rt_clk_cell *cell)
{
    rt_uint32_t tmp;
    rt_ubase_t level;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;
    struct ccu_gate_config *gate = mix->gate;

    if (!gate)
    {
        return RT_TRUE;
    }

    if (!rt_strcmp(cell->name, tswi8_clk_name))
    {
        return (twsi8_reg_val & gate->gate_mask) == gate->val_enable;
    }

    if (common->lock)
    {
        level = rt_spin_lock_irqsave(common->lock);
    }

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        tmp = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        tmp = HWREG32(common->base + common->reg_ctrl);
    }

    if (common->lock)
    {
        rt_spin_unlock_irqrestore(common->lock, level);
    }

    return (tmp & gate->gate_mask) == gate->val_enable;
}

static rt_ubase_t ccu_mix_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_ubase_t val;
    rt_uint32_t reg, div_val = 0;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;
    struct ccu_div_config *div = mix->div;
    struct ccu_mux_config *mux = mix->mux ? mix->mux : RT_NULL;

    if (!div)
    {
        if (mux && common->rate && common->rate != parent_rate)
        {
            parent_rate = common->rate;
        }

        if (mix->factor)
        {
            val = parent_rate * mix->factor->mul / mix->factor->div;
        }
        else
        {
            val = parent_rate;
        }

        goto _end;
    }

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        reg = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        reg = HWREG32(common->base + common->reg_ctrl);
    }

    val = reg >> div->shift;
    val &= (1 << div->width) - 1;

    if (div->clk_flags & CLK_DIVIDER_POWER_OF_TWO)
    {
        div_val = 1 << val;
    }
    else if (div->table)
    {
        const struct ccu_div_table *clkt;

        for (clkt = div->table; clkt->div; ++clkt)
        {
            if (clkt->val == val)
            {
                div_val = clkt->div;
                break;
            }
        }
    }
    else
    {
        div_val = val + 1;
    }

    if (!div_val)
    {
        val = parent_rate;
    }
    else
    {
        val = RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, div_val);
    }

_end:
    common->rate = val;

    return val;
}

static rt_base_t ccu_mix_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate)
{
    return drate;
}

static rt_err_t ccu_mix_trigger_fc(struct rt_clk_cell *cell)
{
    rt_ubase_t val = 0;
    rt_err_t err = RT_EOK;
    rt_uint32_t timeout = 50;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;

    if (common->reg_type == CLK_DIV_TYPE_1REG_FC_V2 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4 ||
        common->reg_type == CLK_DIV_TYPE_1REG_FC_DIV_V5 ||
        common->reg_type == CLK_DIV_TYPE_1REG_FC_MUX_V6)
    {
        timeout = 50;
        val = HWREG32(common->base + common->reg_ctrl);
        val |= common->fc;
        HWREG32(common->base + common->reg_ctrl) = val;

        do {
            val = HWREG32(common->base + common->reg_ctrl);
            --timeout;

            if (!(val & common->fc))
            {
                break;
            }
        } while (timeout);

        if (timeout == 0)
        {
            timeout = 5000;

            do {
                val = HWREG32(common->base + common->reg_ctrl);
                --timeout;

                if (!(val & common->fc))
                {
                    break;
                }
            } while (timeout);

            if (timeout == 0)
            {
                err = -RT_ETIMEOUT;
            }
        }
    }

    return err;
}

static rt_ubase_t ccu_mix_calc_best_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_uint32_t *mux_val, rt_uint32_t *div_val)
{
    rt_uint32_t div_max;
    rt_ubase_t parent_rate = 0, best_rate = 0;
    struct rt_clk_cell *parent;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_div_config *div = mix->div? mix->div: RT_NULL;

    for (int i = 0; i < cell->parents_nr; ++i)
    {
        parent = rt_clk_cell_get_parent_by_index(cell, i);

        if (!parent)
        {
            continue;
        }

        parent_rate = rt_clk_cell_get_rate(parent);

        if (div)
        {
            div_max = 1 << div->width;
        }
        else
        {
            div_max = 1;
        }

        for (int j = 1; j <= div_max; ++j)
        {
            if (div && div->clk_flags & CLK_DIVIDER_POWER_OF_TWO)
            {
                int d;

                if (div->clk_flags & CLK_DIVIDER_ALLOW_ZERO)
                {
                    d = j - 1;
                }

                if (rt_abs(parent_rate / RT_BIT(d) - rate) < rt_abs(best_rate - rate))
                {
                    best_rate = RT_DIV_ROUND_UP_ULL(parent_rate, RT_BIT(d));
                    *mux_val = i;
                    *div_val = d;
                }

                continue;
            }

            if (rt_abs(parent_rate / j - rate) < rt_abs(best_rate - rate))
            {
                best_rate = RT_DIV_ROUND_UP_ULL(parent_rate, j);
                *mux_val = i;
                *div_val = j - 1;
            }
        }
    }

    return best_rate;
}

static rt_err_t ccu_mix_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_err_t err = RT_EOK;
    rt_ubase_t level, best_rate;
    rt_uint32_t cur_mux, cur_div, mux_val = 0, div_val = 0, reg = 0;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;
    struct ccu_div_config *div = mix->div? mix->div: RT_NULL;
    struct ccu_mux_config *mux = mix->mux? mix->mux: RT_NULL;

    if (!div && !mux)
    {
        return RT_EOK;
    }

    best_rate = ccu_mix_calc_best_rate(cell, rate, &mux_val, &div_val);
    common->rate = best_rate;

    if (!rt_strcmp(cell->name, tswi8_clk_name))
    {
        if (mux)
        {
            cur_mux = twsi8_reg_val >> mux->shift;
            cur_mux &= (1 << mux->width) - 1;

            if (cur_mux != mux_val)
            {
                rt_clk_cell_set_parent(cell, rt_clk_cell_get_parent_by_index(cell, mux_val));
            }
        }

        return RT_EOK;
    }

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        reg = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        reg = HWREG32(common->base + common->reg_ctrl);
    }

    if (mux)
    {
        cur_mux = reg >> mux->shift;
        cur_mux &= (1 << mux->width) - 1;

        if (cur_mux != mux_val)
        {
            rt_clk_cell_set_parent(cell, rt_clk_cell_get_parent_by_index(cell, mux_val));
        }
    }

    if (div)
    {
        cur_div = reg >> div->shift;
        cur_div &= (1 << div->width) - 1;

        if (cur_div == div_val)
        {
            return RT_EOK;
        }
    }
    else
    {
        return RT_EOK;
    }

    level = rt_spin_lock_irqsave(common->lock);

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        reg = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        reg = HWREG32(common->base + common->reg_ctrl);
    }

    reg &= ~RT_GENMASK(div->width + div->shift - 1, div->shift);

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        HWREG32(common->base + common->reg_sel) = reg | (div_val << div->shift);
    }
    else
    {
        HWREG32(common->base + common->reg_ctrl) = reg | (div_val << div->shift);
    }

    if (common->reg_type == CLK_DIV_TYPE_1REG_FC_V2 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4 ||
        common->reg_type == CLK_DIV_TYPE_1REG_FC_DIV_V5)
    {
        err = ccu_mix_trigger_fc(cell);
    }

    rt_spin_unlock_irqrestore(common->lock, level);

    if (err)
    {
        LOG_E("%s:%s timeout", __func__, cell->name);
    }

    return RT_EOK;
}

static rt_err_t ccu_mix_set_parent(struct rt_clk_cell *cell, rt_uint8_t idx)
{
    rt_ubase_t level;
    rt_uint32_t reg = 0;
    rt_err_t err = RT_EOK;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;
    struct ccu_mux_config *mux = mix->mux;

    if (!mux)
    {
        return RT_EOK;
    }

    if (mux->table)
    {
        idx = mux->table[idx];
    }

    if (!rt_strcmp(cell->name, tswi8_clk_name))
    {
        twsi8_reg_val &= ~RT_GENMASK(mux->width + mux->shift - 1, mux->shift);
        twsi8_reg_val |= (idx << mux->shift);
        reg = twsi8_reg_val;

        if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
            common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
        {
            HWREG32(common->base + common->reg_sel) = reg;
        }
        else
        {
            HWREG32(common->base + common->reg_ctrl) = reg;
        }

        return RT_EOK;
    }

    level = rt_spin_lock_irqsave(common->lock);

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        reg = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        reg = HWREG32(common->base + common->reg_ctrl);
    }

    reg &= ~RT_GENMASK(mux->width + mux->shift - 1, mux->shift);

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        HWREG32(common->base + common->reg_sel) = reg | (idx << mux->shift);
    }
    else
    {
        HWREG32(common->base + common->reg_ctrl) = reg | (idx << mux->shift);
    }

    if (common->reg_type == CLK_DIV_TYPE_1REG_FC_V2 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4 ||
        common->reg_type == CLK_DIV_TYPE_1REG_FC_MUX_V6)
    {
        err = ccu_mix_trigger_fc(cell);
    }

    rt_spin_unlock_irqrestore(common->lock, level);

    if (err)
    {
        LOG_E("%s:%s timeout", __func__, cell->name);
    }

    return RT_EOK;
}

static rt_uint8_t ccu_mix_get_parent(struct rt_clk_cell *cell)
{
    rt_uint32_t reg;
    rt_uint8_t parent;
    struct ccu_mix *mix = cell_to_ccu_mix(cell);
    struct ccu_common *common = &mix->common;
    struct ccu_mux_config *mux = mix->mux;

    if (!mux)
    {
        return 0;
    }

    if (!rt_strcmp(cell->name, tswi8_clk_name))
    {
        parent = twsi8_reg_val >> mux->shift;
        parent &= (1 << mux->width) - 1;

        return parent;
    }

    if (common->reg_type == CLK_DIV_TYPE_2REG_NOFC_V3 ||
        common->reg_type == CLK_DIV_TYPE_2REG_FC_V4)
    {
        reg = HWREG32(common->base + common->reg_sel);
    }
    else
    {
        reg = HWREG32(common->base + common->reg_ctrl);
    }

    parent = reg >> mux->shift;
    parent &= (1 << mux->width) - 1;

    if (mux->table)
    {
        for (int i = 0; i < cell->parents_nr; ++i)
        {
            if (mux->table[i] == parent)
            {
                return i;
            }
        }
    }

    return parent;
}

const struct rt_clk_ops ccu_mix_ops =
{
    .disable = ccu_mix_disable,
    .enable = ccu_mix_enable,
    .is_enabled = ccu_mix_is_enabled,
    .recalc_rate = ccu_mix_recalc_rate,
    .round_rate  = ccu_mix_round_rate,
    .set_rate = ccu_mix_set_rate,
    .set_parent = ccu_mix_set_parent,
    .get_parent  = ccu_mix_get_parent,
};
