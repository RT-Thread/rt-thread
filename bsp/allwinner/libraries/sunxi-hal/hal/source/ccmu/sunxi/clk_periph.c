/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 *the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sunxi_hal_common.h"
#include "clk_periph.h"

#define NEW_RATE_CALCULATE 1

hal_clk_status_t sunxi_clk_periph_get_parent(clk_periph_pt clk, u8 *parent_index)
{
    u32 reg = 0;
    struct sunxi_clk_periph *periph = clk->config;

    CCMU_TRACE();
    if (!periph->mux.reg)
    {
        *parent_index = 0;
        return HAL_CLK_STATUS_OK;
    }

    //if (periph->lock)
    //  spin_lock_irqsave(periph->lock, flags);

    reg = readl(periph->mux.reg);
    *parent_index = GET_BITS(periph->mux.shift, periph->mux.width, reg);

    //if (periph->lock)
    //  spin_unlock_irqrestore(periph->lock, flags);

    CCMU_DBG("parent index %d \n", (*parent_index));
    return HAL_CLK_STATUS_OK;
}


hal_clk_status_t sunxi_clk_periph_set_parent(clk_periph_pt clk, u8 index)
{
    unsigned long reg, flags = 0;
    struct sunxi_clk_periph *periph = clk->config;

    //if (periph->flags & CLK_READONLY)
    //  return 0;

    if (!periph->mux.reg)
    {
        return HAL_CLK_STATUS_OK;
    }

    //if (periph->lock)
    //  spin_lock_irqsave(periph->lock, flags);

    reg = readl(periph->mux.reg);
    reg = SET_BITS(periph->mux.shift, periph->mux.width, reg, index);
    writel(reg, periph->mux.reg);

    //if (periph->lock)
    //  spin_unlock_irqrestore(periph->lock, flags);

    return HAL_CLK_STATUS_OK;
}

hal_clk_status_t __sunxi_clk_periph_enable_shared(struct sunxi_clk_periph *periph)
{
    unsigned long reg;
    struct sunxi_clk_periph_gate *gate = &periph->gate;

    if (!periph->com_gate->val)
    {
        /* de-assert module */
        if (gate->reset && IS_SHARE_RST_GATE(periph))
        {
            reg = readl(gate->reset);
            reg = SET_BITS(gate->rst_shift, 1, reg, 1);
            writel(reg, gate->reset);
        }
        /* enable bus gating */
        if (gate->bus && IS_SHARE_BUS_GATE(periph))
        {
            reg = readl(gate->bus);
            reg = SET_BITS(gate->bus_shift, 1, reg, 1);
            writel(reg, gate->bus);
        }

        /* enable module gating */
        if (gate->enable && IS_SHARE_MOD_GATE(periph))
        {
            reg = readl(gate->enable);
            reg = SET_BITS(gate->enb_shift, 1, reg, 1);
            writel(reg, gate->enable);
        }

        /* enable dram gating */
        if (gate->dram && IS_SHARE_MBUS_GATE(periph))
        {
            reg = readl(gate->dram);
            reg = SET_BITS(gate->ddr_shift, 1, reg, 1);
            writel(reg, gate->dram);
        }
    }
    periph->com_gate->val |= 1 << periph->com_gate_off;

    return HAL_CLK_STATUS_OK;
}

hal_clk_status_t __sunxi_clk_periph_enable(struct sunxi_clk_periph *periph)
{
    u32 reg;
    struct sunxi_clk_periph_gate *gate = &periph->gate;

    /* de-assert module */
    if (gate->reset && !IS_SHARE_RST_GATE(periph))
    {
        reg = readl(gate->reset);
        reg = SET_BITS(gate->rst_shift, 1, reg, 1);
        writel(reg, gate->reset);
    }

    /* enable bus gating */
    if (gate->bus && !IS_SHARE_BUS_GATE(periph))
    {
        reg = readl(gate->bus);
        reg = SET_BITS(gate->bus_shift, 1, reg, 1);
        writel(reg, gate->bus);
    }

    /* enable module gating */
    if (gate->enable && !IS_SHARE_MOD_GATE(periph))
    {
        reg = readl(gate->enable);
        //if (periph->flags & CLK_REVERT_ENABLE)
        //  reg = SET_BITS(gate->enb_shift, 1, reg, 0);
        //else
        reg = SET_BITS(gate->enb_shift, 1, reg, 1);
        writel(reg, gate->enable);
    }

    /* enable dram gating */
    if (gate->dram && !IS_SHARE_MBUS_GATE(periph))
    {
        reg = readl(gate->dram);
        reg = SET_BITS(gate->ddr_shift, 1, reg, 1);
        writel(reg, gate->dram);
    }

    return HAL_CLK_STATUS_OK;
}

hal_clk_status_t sunxi_clk_periph_enable(clk_periph_pt clk)
{
    //unsigned long flags = 0;
    hal_clk_status_t ret = 0;
    struct sunxi_clk_periph *periph = NULL;

    //if (periph->flags & CLK_READONLY)
    //  return 0;
    periph = clk->config;

    //if (periph->lock)
    //  spin_lock_irqsave(periph->lock, flags);

    /* if common gate exist, enable it first */
    if (periph->com_gate)
    {
        ret = __sunxi_clk_periph_enable_shared(periph);
    }
    if (!ret)
    {
        ret = __sunxi_clk_periph_enable(periph);
    }

    //if (periph->lock)
    //  spin_unlock_irqrestore(periph->lock, flags);

    return ret == HAL_CLK_STATUS_OK ?      \
           HAL_CLK_STATUS_ENABLED : HAL_CLK_STATUS_ERROR_CLK_ENABLED_FAILED;
}

hal_clk_status_t sunxi_clk_periph_is_enabled(clk_periph_pt clk)
{
    u32 state = 0, reg = 0;
    //unsigned long flags = 0;
    struct sunxi_clk_periph *periph = NULL;
    struct sunxi_clk_periph_gate *gate = NULL;

    periph = clk->config;
    gate = &periph->gate;
    //if (periph->lock)
    //  spin_lock_irqsave(periph->lock, flags);

    /* enable bus gating */
    if (gate->bus)
    {
        reg = readl(gate->bus);
        state &= GET_BITS(gate->bus_shift, 1, reg);
    }

    /* enable module gating */
    if (gate->enable)
    {
        reg = readl(gate->enable);
        state &= GET_BITS(gate->enb_shift, 1, reg);
    }

    /* de-assert module */
    if (gate->reset)
    {
        reg = readl(gate->reset);
        state &= GET_BITS(gate->rst_shift, 1, reg);
    }

    /* enable dram gating */
    if (gate->dram)
    {
        reg = readl(gate->dram);
        state &= GET_BITS(gate->ddr_shift, 1, reg);
    }

    //if (periph->lock)
    //  spin_unlock_irqrestore(periph->lock, flags);

    return state ? HAL_CLK_STATUS_ENABLED : HAL_CLK_STATUS_DISABLED;
}

static void __sunxi_clk_periph_disable_shared(struct sunxi_clk_periph *periph)
{
    unsigned long reg;
    struct sunxi_clk_periph_gate *gate = &periph->gate;

    if (!periph->com_gate->val)
    {
        return;
    }

    periph->com_gate->val &= ~(1 << periph->com_gate_off);

    if (!periph->com_gate->val)
    {
        /* disable dram gating */
        if (gate->dram && IS_SHARE_MBUS_GATE(periph))
        {
            reg = readl(gate->dram);
            reg = SET_BITS(gate->ddr_shift, 1, reg, 0);
            writel(reg, gate->dram);
        }

        /* disable module gating */
        if (gate->enable && IS_SHARE_MOD_GATE(periph))
        {
            reg = readl(gate->enable);
            reg = SET_BITS(gate->enb_shift, 1, reg, 0);
            writel(reg, gate->enable);
        }

        /* disable bus gating */
        if (gate->bus && IS_SHARE_BUS_GATE(periph))
        {
            reg = readl(gate->bus);
            reg = SET_BITS(gate->bus_shift, 1, reg, 0);
            writel(reg, gate->bus);
        }

        /* assert module */
        if (gate->reset  && IS_SHARE_RST_GATE(periph))
        {
            reg = readl(gate->reset);
            reg = SET_BITS(gate->rst_shift, 1, reg, 0);
            writel(reg, gate->reset);
        }
    }

}

static void __sunxi_clk_periph_disable(struct sunxi_clk_periph *periph)
{
    u32 reg;
    struct sunxi_clk_periph_gate *gate = &periph->gate;

    /* disable dram gating */
    if (gate->dram && !IS_SHARE_MBUS_GATE(periph))
    {
        reg = readl(gate->dram);
        reg = SET_BITS(gate->ddr_shift, 1, reg, 0);
        writel(reg, gate->dram);
    }

    /* disable module gating */
    if (gate->enable && !IS_SHARE_MOD_GATE(periph))
    {
        reg = readl(gate->enable);
        //if (periph->flags & CLK_REVERT_ENABLE)
        //  reg = SET_BITS(gate->enb_shift, 1, reg, 1);
        //else
        reg = SET_BITS(gate->enb_shift, 1, reg, 0);

        writel(reg, gate->enable);
    }

    /* disable bus gating */
    if (gate->bus && !IS_SHARE_BUS_GATE(periph))
    {
        reg = readl(gate->bus);
        reg = SET_BITS(gate->bus_shift, 1, reg, 0);
        writel(reg, gate->bus);
    }

    /* assert module */
    if (gate->reset && !IS_SHARE_RST_GATE(periph))
    {
        reg = readl(gate->reset);
        reg = SET_BITS(gate->rst_shift, 1, reg, 0);
        writel(reg, gate->reset);
    }
}

hal_clk_status_t sunxi_clk_periph_disable(clk_periph_pt clk)
{
    //unsigned long flags = 0;
    struct sunxi_clk_periph *periph = NULL;

    //if (periph->flags & CLK_READONLY)
    //  return 0;
    periph = clk->config;

    //if (periph->lock)
    //  spin_lock_irqsave(periph->lock, flags);

    __sunxi_clk_periph_disable(periph);

    /* if common gate exist, disable it */
    if (periph->com_gate)
    {
        __sunxi_clk_periph_disable_shared(periph);
    }

    //if (periph->lock)
    //  spin_unlock_irqrestore(periph->lock, flags);
    return HAL_CLK_STATUS_DISABLED;
}

hal_clk_status_t sunxi_clk_periph_recalc_rate(clk_periph_pt clk, u32 *rate)
{
    u32 reg = 0, parent_rate = 0;
    u64 div, div_m = 0, div_n = 0, clk_rate = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    struct sunxi_clk_periph *periph = NULL;
    struct sunxi_clk_periph_div *divider = NULL;

    periph = clk->config;
    divider = &periph->divider;
    parent_rate = clk->clk_core.parent_rate;
    clk_rate = (u64)parent_rate;
    if (!divider->reg)
    {
        *rate = parent_rate;
        return ret;
    }

    //if (periph->lock)
    //  spin_lock_irqsave(periph->lock, flags);

    reg = readl(divider->reg);
    if (divider->mwidth)
    {
        div_m = GET_BITS(divider->mshift, divider->mwidth, reg);
    }
    if (divider->nwidth)
    {
        div_n = GET_BITS(divider->nshift, divider->nwidth, reg);
    }
    div = (div_m + 1) * (1 << div_n);
    do_div(clk_rate, div);

    //if (periph->lock)
    //  spin_unlock_irqrestore(periph->lock, flags);
    *rate = (u32)clk_rate;
    return ret;
}


u32 sunxi_clk_periph_round_rate(clk_periph_pt clk, u32 rate, u32 prate)
{
    struct sunxi_clk_periph *periph = NULL;
    struct sunxi_clk_periph_div *divider = NULL;

    u32 i = 0, round_rate = 0;
    u64 div, div_m = 0, div_n = 0;
    u64 factor_m = 0, factor_n = 0, found = 0;

    CCMU_TRACE();
    periph = clk->config;
    divider = &periph->divider;

    round_rate = (prate + rate / 2 - 1);
    if (!rate)
    {
        return 0;
    }

    do_div(round_rate, rate);
    div = round_rate;
    if (!div)
    {
        return prate;
    }

    round_rate = prate;
    div_m = 1 << divider->mwidth;
    if (divider->nwidth)
    {
        div_n = 1 << divider->nwidth;
        div_n = 1 << (div_n - 1);
    }
    else
    {
        div_n = 1;
    }

    /* NEW_RATE_CALCULATE */
    while (i < (1 << divider->nwidth))
    {
        if (div <= div_m)
        {
            factor_m = div - 1;
            factor_n = i;
            do_div(round_rate, (factor_m + 1) * (1 << factor_n));
            found = 1;
            break;
        }
        div = div >> 1;
        i++;

        if (!div)
        {
            factor_m = 0;
            factor_n = i;
            do_div(round_rate, (factor_m + 1) * (1 << factor_n));
            found = 1;
            break;
        }
    }
    if (!found)
    {
        factor_m = (div > div_m ? div_m : div) - 1;
        factor_n = (1 << divider->nwidth) - 1;
        do_div(round_rate, (factor_m + 1) * (1 << factor_n));
    }

    CCMU_DBG("parent rate %dHZ, target rate %dHZ, round rate %dHZ\n", prate, rate, round_rate);
    CCMU_TRACE();
    return round_rate;
}

hal_clk_status_t sunxi_clk_periph_set_rate(clk_periph_pt clk, u32 rate)
{
    u32 i = 0, factor_m = 0, factor_n = 0, found = 0, parent_rate = 0;
    u32 reg = 0;
    struct sunxi_clk_periph *periph = NULL;
    struct sunxi_clk_periph_div *divider = NULL;
    u32 div, div_m = 0, div_n = 0;

    CCMU_TRACE();
    periph = clk->config;
    divider = &periph->divider;
    parent_rate = clk->clk_core.parent_rate;

    CCMU_DBG("parent rate %dHZ, set rate %dHZ\n", parent_rate, rate);
    u64 tmp_rate = parent_rate;
    do_div(tmp_rate, rate);
    div = tmp_rate;

    if (!div)
    {
        div_m = div_n = 0;
    }
    else
    {
        div_m = 1 << divider->mwidth;
        div_n = (1 << divider->nwidth) - 1;

        if (div > (div_m << div_n))
        {
            //WARN(1, "clk %s rate is too large : %lu\n", hw->init->name, rate);
            div = div_m << div_n;
        }
        found = 0;
        while (i < (1 << divider->nwidth))
        {
            if (div <= div_m)
            {
                factor_m = div - 1;
                factor_n = i;
                found = 1;
                break;
            }
            div = div >> 1;
            i++;
            if (!div)
            {
                factor_m = 0;
                factor_n = i;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            factor_m = (div > div_m ? div_m : div) - 1;
            factor_n = (1 << divider->nwidth) - 1;
        }
        div_m = factor_m;
        div_n = factor_n;
    }

    CCMU_DBG("divider->reg %d divider->mwidth %d divider->nshift %d \n", divider->reg, divider->mwidth, divider->nshift);
    if (!divider->reg)
    {
        return HAL_CLK_STATUS_OK;
    }
    reg = readl(divider->reg);
    if (divider->mwidth)
    {
        reg = SET_BITS(divider->mshift, divider->mwidth, reg, div_m);
    }
    if (divider->nwidth)
    {
        reg = SET_BITS(divider->nshift, divider->nwidth, reg, div_n);
    }
    writel(reg, divider->reg);

    CCMU_TRACE();
    return HAL_CLK_STATUS_OK;
}
