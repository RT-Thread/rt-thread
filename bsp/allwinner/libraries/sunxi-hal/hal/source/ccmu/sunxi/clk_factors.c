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
#include "clk_factors.h"
#include "clk.h"

static int sunxi_clk_disable_plllock(struct factor_init_data *factor)
{
    volatile u32 reg;

    switch (factor->lock_mode)
    {
        case PLL_LOCK_NEW_MODE:
        case PLL_LOCK_OLD_MODE:
            /* make sure pll new mode is disable */
            reg = readl(factor->pll_lock_ctrl_reg);
            reg = SET_BITS(factor->lock_en_bit, 1, reg, 0);
            writel(reg, factor->pll_lock_ctrl_reg);

            reg = readl(factor->pll_lock_ctrl_reg);
            reg = SET_BITS(28, 1, reg, 0);
            writel(reg, factor->pll_lock_ctrl_reg);
            break;
        case PLL_LOCK_NONE_MODE:
            break;
        default:
            //WARN(1, "invaild pll lock mode:%u\n", factor->lock_mode);
            return -1;
    }

    return 0;
}

static int sunxi_clk_is_lock(struct factor_init_data *factor)
{
    volatile u32 reg;
    u32 loop = 5000;

    if (factor->lock_mode >= PLL_LOCK_MODE_MAX)
    {
        //WARN(1, "invaild pll lock mode:%u\n", factor->lock_mode);
        return -1;
    }

    if (factor->lock_mode == PLL_LOCK_NEW_MODE)
    {
        /* enable pll new mode */
        reg = readl(factor->pll_lock_ctrl_reg);
        reg = SET_BITS(28, 1, reg, 1);
        writel(reg, factor->pll_lock_ctrl_reg);

        reg = readl(factor->pll_lock_ctrl_reg);
        reg = SET_BITS(factor->lock_en_bit, 1, reg, 1);
        writel(reg, factor->pll_lock_ctrl_reg);
    }

    while (--loop)
    {
        reg = readl(factor->lock_reg);
        if (GET_BITS(factor->lock_bit, 1, reg))
        {
            clk_udelay(20);
            break;
        }

        clk_udelay(1);
    }

    if (factor->lock_mode == PLL_LOCK_NEW_MODE)
    {
        /* disable pll new mode */
        reg = readl(factor->pll_lock_ctrl_reg);
        reg = SET_BITS(factor->lock_en_bit, 1, reg, 0);
        writel(reg, factor->pll_lock_ctrl_reg);

        reg = readl(factor->pll_lock_ctrl_reg);
        reg = SET_BITS(28, 1, reg, 0);
        writel(reg, factor->pll_lock_ctrl_reg);
    }

    if (!loop)
    {
        //#if (defined CONFIG_FPGA_V4_PLATFORM) || (defined CONFIG_FPGA_V7_PLATFORM)
        //      pr_err("clk %s wait lock timeout\n",
        //             clk_hw_get_name(&factor->hw));
        return 0;
        //#else
        //      return -1;
        //#endif
    }

    return 0;
}

hal_clk_status_t sunxi_clk_fators_enable(clk_factor_pt clk)
{
    u32 reg = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_ENABLED;
    struct factor_init_data *factor = NULL;
    struct sunxi_clk_factors_config *config = NULL;

    factor = clk->factor_data;
    config = factor->config;

    /* check if the pll enabled already */
    reg = readl(factor->reg);
    if (GET_BITS(config->enshift, 1, reg))
    {
        sunxi_clk_disable_plllock(factor);
        /* get factor register value */
        reg = readl(factor->reg);
        goto enable_sdm;
    }

    //  if (factor->lock)
    //      spin_lock_irqsave(factor->lock, flags);

    sunxi_clk_disable_plllock(factor);

    /* get factor register value */
    reg = readl(factor->reg);

    /* enable the register */
    reg = SET_BITS(config->enshift, 1, reg, 1);

    /* update for pll_ddr register */
    if (config->updshift)
    {
        reg = SET_BITS(config->updshift, 1, reg, 1);
    }

    if (config->out_enshift)
    {
        reg = SET_BITS(config->out_enshift, 1, reg, 1);
    }

    if (config->mux_inshift)
    {
        reg = SET_BITS(config->mux_inshift, 1, reg, 1);
    }

enable_sdm:
    if (config->sdmwidth)
    {
        writel(config->sdmval,
               (volatile uint32_t *)config->sdmpat);
        reg = SET_BITS(config->sdmshift, config->sdmwidth, reg, 1);
    }

    writel(reg, factor->reg);

    if (sunxi_clk_is_lock(factor))
    {
        //  if (factor->lock)
        //      spin_unlock_irqrestore(factor->lock, flags);
        //  WARN(1, "clk %s wait lock timeout\n", clk_hw_get_name(&factor->hw));
        ret = HAL_CLK_STATUS_DISABLED;
    }

    //if (factor->lock)
    //  spin_unlock_irqrestore(factor->lock, flags);

    return ret;
}

hal_clk_status_t sunxi_clk_fators_disable(clk_factor_pt clk)
{
    u32 reg = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_DISABLED;
    struct factor_init_data *factor = NULL;
    struct sunxi_clk_factors_config *config = NULL;

    factor = clk->factor_data;
    config = factor->config;;

    //if (factor->flags & CLK_NO_DISABLE)
    //  return;

    /* check if the pll disabled already */
    reg = readl(factor->reg);
    if (!GET_BITS(config->enshift, 1, reg))
    {
        return ret;
    }

    /* When the pll is not in use, just set it to the minimum frequency */
    /* if (factor->flags & CLK_IGNORE_DISABLE) {
        //clk_set_rate(hw->clk, 0);
        return;
    }
    */

    //if (factor->lock)
    //  spin_lock_irqsave(factor->lock, flags);

    reg = readl(factor->reg);
    if (config->sdmwidth)
    {
        reg = SET_BITS(config->sdmshift, config->sdmwidth, reg, 0);
    }

    /* update for pll_ddr register */
    if (config->updshift)
    {
        reg = SET_BITS(config->updshift, 1, reg, 1);
    }

    /* disable Pll-enable-bit*/
    reg = SET_BITS(config->enshift, 1, reg, 0);
    writel(reg, factor->reg);

    /* disable Pll-lock-bit if needed */
    sunxi_clk_disable_plllock(factor);

    //if (factor->lock)
    //  spin_unlock_irqrestore(factor->lock, flags);
    return ret;
}

hal_clk_status_t sunxi_clk_fators_is_enabled(clk_factor_pt clk)
{
    u32 reg = 0, val = 0;
    hal_clk_status_t ret;
    struct factor_init_data *factor = NULL;
    struct sunxi_clk_factors_config *config = NULL;
    CCMU_TRACE();

    //  unsigned long flags = 0;
    factor = clk->factor_data;
    config = factor->config;
    //  if (factor->flags & CLK_NO_DISABLE)
    //      return __clk_get_enable_count(hw->clk);

    //if (factor->lock)
    //  spin_lock_irqsave(factor->lock, flags);

    reg = readl(factor->reg);
    val = GET_BITS(config->enshift, 1, reg);

    //if (factor->lock)
    //  spin_unlock_irqrestore(factor->lock, flags);

    return val ? HAL_CLK_STATUS_ENABLED : HAL_CLK_STATUS_DISABLED;
}

hal_clk_status_t sunxi_clk_factors_recalc_rate(clk_factor_pt clk, u32 *rate)
{
    u32 reg = 0,  flags = 0,  parent_rate = 0;
    struct clk_factors_value factor_val;
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    struct factor_init_data *factor = NULL;
    struct sunxi_clk_factors_config *config = NULL;

    CCMU_TRACE();

    factor = clk->factor_data;
    if (!factor->calc_rate)
    {
        return HAL_CLK_STATUS_UNINITIALIZED;
    }

    config = factor->config;
    parent_rate = clk->clk_core.parent_rate;

    //if (factor->lock)
    //  spin_lock_irqsave(factor->lock, flags);

    reg = readl(factor->reg);

    //if (factor->lock)
    //  spin_unlock_irqrestore(factor->lock, flags);

    if (config->nwidth)
    {
        factor_val.factorn = GET_BITS(config->nshift, config->nwidth, reg);
    }
    else
    {
        factor_val.factorn = 0xffff;
    }

    if (config->kwidth)
    {
        factor_val.factork = GET_BITS(config->kshift, config->kwidth, reg);
    }
    else
    {
        factor_val.factork = 0xffff;
    }

    if (config->mwidth)
    {
        factor_val.factorm = GET_BITS(config->mshift, config->mwidth, reg);
    }
    else
    {
        factor_val.factorm = 0xffff;
    }

    if (config->pwidth)
    {
        factor_val.factorp = GET_BITS(config->pshift, config->pwidth, reg);
    }
    else
    {
        factor_val.factorp = 0xffff;
    }

    if (config->d1width)
    {
        factor_val.factord1 = GET_BITS(config->d1shift, config->d1width, reg);
    }
    else
    {
        factor_val.factord1 = 0xffff;
    }

    if (config->d2width)
    {
        factor_val.factord2 = GET_BITS(config->d2shift, config->d2width, reg);
    }
    else
    {
        factor_val.factord2 = 0xffff;
    }

    if (config->frac)
    {
        factor_val.frac_mode = GET_BITS(config->modeshift, 1, reg);
        factor_val.frac_freq = GET_BITS(config->outshift, 1, reg);
    }
    else
    {
        factor_val.frac_mode = 0xffff;
        factor_val.frac_freq = 0xffff;
    }
    if (factor->calc_rate)
    {
        (*rate)  = factor->calc_rate(parent_rate, &factor_val);
    }

    return ret;
}

hal_clk_status_t sunxi_clk_factors_set_rate(clk_factor_pt clk, u32 rate)
{
    u32 reg = 0, parent_rate = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    struct clk_factors_value factor_val;
    struct factor_init_data *factor = NULL;
    struct sunxi_clk_factors_config *config = NULL;

    factor = clk->factor_data;
    config = factor->config;
    parent_rate = clk->clk_core.parent_rate;
    CCMU_TRACE();
    if (!factor->get_factors)
    {
        return HAL_CLK_STATUS_UNINITIALIZED;
    }

    /* factor_val is initialized with its original value,
     * it's factors(such as:M,N,K,P,d1,d2...) are Random Value.
     * if donot judge the return value of "factor->get_factors",
     * it may change the original register value.
     */
    if (factor->get_factors(rate, parent_rate, &factor_val) < 0)
    {
        /* cannot get right factors for clk,just break */
        CCMU_ERR("clk %d set rate failed! Because cannot get right factors for clk\n", clk->clk_core.clk);
        return HAL_CLK_STATUS_UNINITIALIZED;
    }
#if 0
    if (factor->flags & CLK_RATE_FLAT_FACTORS)
    {
        return sunxi_clk_factors_set_flat_facotrs(factor, &factor_val);
    }
#endif
    //if (factor->lock)
    //  spin_lock_irqsave(factor->lock, flags);

    sunxi_clk_disable_plllock(factor);

    reg = readl(factor->reg);
    if (config->sdmwidth)
    {
        writel(config->sdmval, (volatile uint32_t *)config->sdmpat);
        reg = SET_BITS(config->sdmshift, config->sdmwidth, reg, 1);
    }
    if (config->nwidth)
    {
        reg = SET_BITS(config->nshift, config->nwidth, reg, factor_val.factorn);
    }
    if (config->kwidth)
    {
        reg = SET_BITS(config->kshift, config->kwidth, reg, factor_val.factork);
    }
    if (config->mwidth)
    {
        reg = SET_BITS(config->mshift, config->mwidth, reg, factor_val.factorm);
    }
    if (config->pwidth)
    {
        reg = SET_BITS(config->pshift, config->pwidth, reg, factor_val.factorp);
    }
    if (config->d1width)
    {
        reg = SET_BITS(config->d1shift, config->d1width, reg, factor_val.factord1);
    }
    if (config->d2width)
    {
        reg = SET_BITS(config->d2shift, config->d2width, reg, factor_val.factord2);
    }
    if (config->frac)
    {
        reg = SET_BITS(config->modeshift, 1, reg, factor_val.frac_mode);
        reg = SET_BITS(config->outshift, 1, reg, factor_val.frac_freq);
    }
    if (config->updshift)
    {
        reg = SET_BITS(config->updshift, 1, reg, 1);
    }
    writel(reg, factor->reg);

    if (GET_BITS(config->enshift, 1, reg))
    {
        if (sunxi_clk_is_lock(factor))
        {
            //if (factor->lock)
            //spin_unlock_irqrestore(factor->lock, flags);
            CCMU_ERR("clk %d wait lock timeout\n", clk->clk_core.clk);
            return -1;
        }
    }

    //if (factor->lock)
    //  spin_unlock_irqrestore(factor->lock, flags);

    return ret;
}


/*
 * sunxi_clk_set_factor_lock_mode() - Set factor lock mode
 */
void sunxi_clk_set_factor_lock_mode(struct factor_init_data *factor,
                                    const char *lock_mode)
{
    if (!strcmp(lock_mode, "new"))
    {
        factor->lock_mode = PLL_LOCK_NEW_MODE;
    }
    else if (!strcmp(lock_mode, "old"))
    {
        factor->lock_mode = PLL_LOCK_OLD_MODE;
    }
    else
    {
        factor->lock_mode = PLL_LOCK_NONE_MODE;
    }
}


u32 sunxi_clk_factors_round_rate(clk_factor_pt clk, u32 rate)
{
    u32 parent_rate = 0;
    struct clk_factors_value factor_val;
    struct factor_init_data *factor = clk->factor_data;

    if (!factor->get_factors || !factor->calc_rate)
    {
        return rate;
    }

    parent_rate = clk->clk_core.parent_rate;
    factor->get_factors(rate, parent_rate, &factor_val);
    return factor->calc_rate(parent_rate, &factor_val);
}


int sunxi_clk_get_common_factors(struct sunxi_clk_factors_config *f_config, struct clk_factors_value *factor,
                                 struct sunxi_clk_factor_freq table[], unsigned long index, unsigned long tbl_size)
{
    if (index >= tbl_size / sizeof(struct sunxi_clk_factor_freq))
    {
        return -1;
    }

    factor->factorn = (table[index].factor >> f_config->nshift) & ((1 << (f_config->nwidth)) - 1);
    factor->factork = (table[index].factor >> f_config->kshift) & ((1 << (f_config->kwidth)) - 1);
    factor->factorm = (table[index].factor >> f_config->mshift) & ((1 << (f_config->mwidth)) - 1);
    factor->factorp = (table[index].factor >> f_config->pshift) & ((1 << (f_config->pwidth)) - 1);
    factor->factord1 = (table[index].factor >> f_config->d1shift) & ((1 << (f_config->d1width)) - 1);
    factor->factord2 = (table[index].factor >> f_config->d2shift) & ((1 << (f_config->d2width)) - 1);

    if (f_config->frac)
    {
        factor->frac_mode = (table[index].factor >> f_config->modeshift) & 1;
        factor->frac_freq = (table[index].factor >> f_config->outshift) & 1;
    }

    return 0;
}

int sunxi_clk_freq_search(struct sunxi_clk_factor_freq tbl[],
                          unsigned long freq, int low, int high)
{
    int mid;
    unsigned long checkfreq;

    if (low > high)
    {
        return (high == -1) ? 0 : high;
    }

    mid = (low + high) / 2;
    checkfreq = tbl[mid].freq / 1000000;

    if (checkfreq == freq)
    {
        return mid;
    }
    else if (checkfreq > freq)
    {
        return sunxi_clk_freq_search(tbl, freq, low, mid - 1);
    }
    else
    {
        return sunxi_clk_freq_search(tbl, freq, mid + 1, high);
    }
}

int sunxi_clk_freq_find(struct sunxi_clk_factor_freq tbl[],
                        unsigned long n, unsigned long freq)
{
    int delta1, delta2;
    int i = sunxi_clk_freq_search(tbl, freq, 0, n - 1);

    if (i != n - 1)
    {

        delta1 = (freq > tbl[i].freq / 1000000)
                 ? (freq - tbl[i].freq / 1000000)
                 : (tbl[i].freq / 1000000 - freq);

        delta2 = (freq > tbl[i + 1].freq / 1000000)
                 ? (freq - tbl[i + 1].freq / 1000000)
                 : (tbl[i + 1].freq / 1000000 - freq);

        if (delta2 < delta1)
        {
            i++;
        }
    }

    return i;
}


int sunxi_clk_com_ftr_sr(struct sunxi_clk_factors_config *f_config,
                         struct clk_factors_value *factor,
                         struct sunxi_clk_factor_freq table[],
                         unsigned long index, unsigned long tbl_count)
{
    int i = sunxi_clk_freq_find(table, tbl_count, index);

    if (i >= tbl_count)
    {
        return -1;
    }

    factor->factorn = (table[i].factor >> f_config->nshift) & ((1 << (f_config->nwidth)) - 1);
    factor->factork = (table[i].factor >> f_config->kshift) & ((1 << (f_config->kwidth)) - 1);
    factor->factorm = (table[i].factor >> f_config->mshift) & ((1 << (f_config->mwidth)) - 1);
    factor->factorp = (table[i].factor >> f_config->pshift) & ((1 << (f_config->pwidth)) - 1);
    factor->factord1 = (table[i].factor >> f_config->d1shift) & ((1 << (f_config->d1width)) - 1);
    factor->factord2 = (table[i].factor >> f_config->d2shift) & ((1 << (f_config->d2width)) - 1);

    if (f_config->frac)
    {
        factor->frac_mode = (table[i].factor >> f_config->modeshift) & 1;
        factor->frac_freq = (table[i].factor >> f_config->outshift) & 1;
    }

    return 0;
}


