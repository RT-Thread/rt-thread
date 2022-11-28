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
#include "clk.h"
#include "clk_periph.h"
#include "clk_factors.h"
#include <stdio.h>
#include <string.h>

extern clk_core_pt sunxi_clk_fixed_src_arry[];
extern clk_fixed_factor_pt sunxi_clk_fixed_factor_arry[];
extern clk_factor_pt sunxi_clk_factor_arry[];
extern clk_periph_pt sunxi_clk_periph_arry[];
extern clk_base_pt sunxi_periph_clk_init_arry[];
extern hal_clk_status_t (*sunxi_clk_factor_init[])(void);
static hal_clk_status_t sunxi_clk_set_parent(hal_clk_id_t clk,  hal_clk_id_t parent_clk);
static hal_clk_status_t sunxi_clk_get_parent(hal_clk_id_t clk,  hal_clk_id_t *parent_clk);
static hal_clk_status_t sunxi_clk_disable(hal_clk_id_t clk);
static hal_clk_status_t sunxi_clk_enabled(hal_clk_id_t clk);
static hal_clk_status_t sunxi_clk_is_enabled(hal_clk_id_t clk);
static hal_clk_status_t sunxi_clk_round_rate(hal_clk_id_t clk, u32 rate, u32 *prate);
static hal_clk_status_t sunxi_clk_recalc_rate(hal_clk_id_t clk, u32 *rate);
static hal_clk_status_t sunxi_clk_get_rate(hal_clk_id_t clk, u32 *rate);
static hal_clk_status_t sunxi_clk_set_rate(hal_clk_id_t clk, u32 rate);

static inline uint64_t read_cntpct(void)
{
    u64 val;
    asm volatile("mrrc p15, 0, %Q0, %R0, c14" : "=r"(val));
    return val;
}

static inline uint32_t read_cntfrq(void)
{
    u32 frq;
    asm volatile("mrc p15, 0, %0, c14, c0, 0" : "=r"(frq));
    return frq;
}

void clk_udelay(u32 us)
{
    u64 start, target;

    start = read_cntpct();
    target = read_cntfrq() / 1000000ULL * us;
    while (read_cntpct() - start <= target) ;
}


clk_core_pt clk_get_core(hal_clk_id_t clk)
{
    clk_core_pt pclk = NULL;
    u32 i;

    switch (HAL_CLK_GET_TYPE(clk))
    {
        /*      */
        case HAL_CLK_PERIPH:
            for (i = 0;  sunxi_clk_periph_arry[i] != NULL;  i++)
            {
                pclk = (clk_core_pt)sunxi_clk_periph_arry[i];
                if (pclk->clk == clk)
                {
                    break;
                }
            }
            break;
        /*      */
        case HAL_CLK_FACTOR:
            for (i = 0;  sunxi_clk_factor_arry[i] != NULL;  i++)
            {
                pclk = (clk_core_pt)sunxi_clk_factor_arry[i];
                if (pclk->clk == clk)
                {
                    break;
                }
            }
            break;
        /*      */
        case HAL_CLK_FIXED_SRC:
            for (i = 0;  sunxi_clk_fixed_src_arry[i] != NULL;  i++)
            {
                pclk = (clk_core_pt)sunxi_clk_fixed_src_arry[i];
                if (pclk->clk == clk)
                {
                    break;
                }
            }
            break;
        /*      */
        case HAL_CLK_FIXED_FACTOR:
            for (i = 0;  sunxi_clk_fixed_factor_arry[i] != NULL;  i++)
            {
                pclk = (clk_core_pt)sunxi_clk_fixed_factor_arry[i];
                if (pclk->clk == clk)
                {
                    break;
                }
            }
            break;
        /*      */
        default:
            break;
    }

    return pclk;
}

hal_clk_status_t sunxi_clk_set_parent(hal_clk_id_t clk,  hal_clk_id_t parent_clk)
{
    u32 i = 0, cnt = 0, parent_rate = 0;
    u8 index = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;
    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return ret;
    }
    switch (pclk->clk_type)
    {
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            if (periph_clk->clk_core.current_parent == parent_clk)
            {
                return HAL_CLK_STATUS_OK;
            }
            for (i = 0; i < periph_clk->parent_arry_size; i++)
            {
                if (periph_clk->parent_arry[i] != parent_clk)
                {
                    continue;
                }
                ret = sunxi_clk_periph_set_parent(periph_clk, i);
                break;
            }
            if (ret == HAL_CLK_STATUS_OK)
            {
                periph_clk->clk_core.current_parent = parent_clk;
                periph_clk->clk_core.current_parent_type = HAL_CLK_GET_TYPE(parent_clk);
                ret = sunxi_clk_recalc_rate(parent_clk, &parent_rate);
                if (ret == HAL_CLK_STATUS_OK)
                {
                    periph_clk->clk_core.parent_rate = parent_rate;
                }
                else
                {
                    periph_clk->clk_core.parent_rate = 0;
                }
            }
            break;
        /*      */
        case HAL_CLK_FIXED_SRC:
        case HAL_CLK_FIXED_FACTOR:
        case HAL_CLK_FACTOR:
            ret = HAL_CLK_STATUS_OK;
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROR_CLK_SET_RATE_REFUSED;
            break;
    }

    CCMU_TRACE();
    return ret;
}


hal_clk_status_t sunxi_clk_get_parent(hal_clk_id_t clk,  hal_clk_id_t *parent_clk)
{
    u32 i;
    u8 index = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;
    hal_clk_id_t parent;
    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return ret;
    }

    switch (pclk->clk_type)
    {
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            ret = sunxi_clk_periph_get_parent(periph_clk,  &index);
            if (ret != HAL_CLK_STATUS_OK)
            {
                break;
            }
            if (index >= periph_clk->parent_arry_size)
            {
                ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
                break;
            }
            parent = periph_clk->parent_arry[index];
            if (periph_clk->clk_core.current_parent == parent)
            {
                break;
            }
            periph_clk->clk_core.current_parent = parent;
            periph_clk->clk_core.current_parent_type = HAL_CLK_GET_TYPE(parent);
            (*parent_clk) = parent;
            break;
        /*      */
        case HAL_CLK_FIXED_SRC:
        case HAL_CLK_FIXED_FACTOR:
        case HAL_CLK_FACTOR:
            pclk = clk_get_core(clk);
            (*parent_clk) = pclk->current_parent;
            ret = HAL_CLK_STATUS_OK;
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
            break;
    }

    CCMU_TRACE();
    return ret;
}


hal_clk_status_t sunxi_clk_disable(hal_clk_id_t clk)
{
    u32 i;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;
    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;
    clk_factor_pt factor_clk = NULL;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return ret;
    }

    switch (pclk->clk_type)
    {
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            ret =  sunxi_clk_periph_disable(periph_clk);
            if (ret == HAL_CLK_STATUS_DISABLED)
            {
                periph_clk->clk_core.clk_enbale = HAL_CLK_STATUS_DISABLED;
            }
            return HAL_CLK_STATUS_OK;
            break;
        /*      */
        case HAL_CLK_FACTOR:
            factor_clk = (clk_factor_pt)pclk;
            ret =  sunxi_clk_fators_disable(factor_clk);
            if (ret  == HAL_CLK_STATUS_DISABLED)
            {
                factor_clk->clk_core.clk_enbale = HAL_CLK_STATUS_DISABLED;
            }
            return HAL_CLK_STATUS_OK;
            break;
        /*      */
        case HAL_CLK_FIXED_FACTOR:
            ret = HAL_CLK_STATUS_ERROR_CLK_FACTOR_REFUSED;
            break;
        /*      */
        case HAL_CLK_FIXED_SRC:
            ret = HAL_CLK_STATUS_ERROR_CLK_FACTOR_REFUSED;
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
            break;
    }

    CCMU_TRACE();
    return ret;
}


hal_clk_status_t sunxi_clk_enabled(hal_clk_id_t clk)
{
    u32 i;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;
    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;
    clk_factor_pt factor_clk = NULL;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return ret;
    }

    switch (pclk->clk_type)
    {
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            ret =  sunxi_clk_periph_enable(periph_clk);
            if (ret == HAL_CLK_STATUS_ENABLED)
            {
                periph_clk->clk_core.clk_enbale = HAL_CLK_STATUS_ENABLED;
            }
            break;
        /*      */
        case HAL_CLK_FACTOR:
            factor_clk = (clk_factor_pt)pclk;
            ret =  sunxi_clk_fators_enable(factor_clk);
            if (ret == HAL_CLK_STATUS_ENABLED)
            {
                factor_clk->clk_core.clk_enbale = HAL_CLK_STATUS_ENABLED;
            }
            break;

        /*      */
        case HAL_CLK_FIXED_SRC:
        case HAL_CLK_FIXED_FACTOR:
            return pclk->clk_enbale;
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
            break;
    }

    CCMU_TRACE();
    return ret;
}

hal_clk_status_t sunxi_clk_is_enabled(hal_clk_id_t clk)
{
    u32 i;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;

    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;
    clk_factor_pt factor_clk = NULL;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return ret;
    }

    switch (pclk->clk_type)
    {
        case HAL_CLK_FIXED_SRC:
        case HAL_CLK_FIXED_FACTOR:
            return HAL_CLK_STATUS_ENABLED;
            break;
        /*      */
        case HAL_CLK_FACTOR:
            factor_clk = (clk_factor_pt)pclk;
            return sunxi_clk_fators_is_enabled(factor_clk);

            break;
        /*      */
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            return sunxi_clk_periph_is_enabled(periph_clk);
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
            break;
    }

    CCMU_TRACE();
    return ret;
}

hal_clk_status_t sunxi_clk_round_rate(hal_clk_id_t clk, u32 rate, u32 *prate)
{
    u32 i, parent_rate = 0, round_rate = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;

    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;
    clk_factor_pt factor_clk = NULL;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return ret;
    }

    switch (pclk->clk_type)
    {
        /*      */
        case HAL_CLK_FIXED_SRC:
        case HAL_CLK_FIXED_FACTOR:
            (*prate) = pclk->clk_rate;
            ret = HAL_CLK_STATUS_OK;
            break;
        /*      */
        case HAL_CLK_FACTOR:
            factor_clk = (clk_factor_pt)pclk;
            round_rate = sunxi_clk_factors_round_rate(factor_clk, rate);
            if (round_rate == 0)
            {
                ret = HAL_CLK_STATUS_ERROR_CLK_ROUND_FAILED;
                break;
            }
            *prate = round_rate;
            ret = HAL_CLK_STATUS_OK;
            break;
        /*      */
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            parent_rate = periph_clk->clk_core.parent_rate;
            round_rate = sunxi_clk_periph_round_rate(periph_clk, rate, parent_rate);
            if (round_rate == 0)
            {
                ret = HAL_CLK_STATUS_ERROR_CLK_ROUND_FAILED;
                break;
            }
            *prate = round_rate;
            ret = HAL_CLK_STATUS_OK;
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
            return ret;
            break;
    }

    CCMU_TRACE();
    return ret;
}

hal_clk_status_t sunxi_clk_recalc_rate(hal_clk_id_t clk, u32 *rate)
{
    u32 i, current_rate = 0;
    u8 index = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    hal_clk_id_t parent;
    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;
    clk_factor_pt factor_clk = NULL;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
    }

    switch (pclk->clk_type)
    {
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            ret = sunxi_clk_periph_recalc_rate(periph_clk, &current_rate);
            if (ret != HAL_CLK_STATUS_OK)
            {
                ret = HAL_CLK_STATUS_DISABLED;
                break;
            }
            (*rate) = current_rate;
            break;

        case HAL_CLK_FACTOR:
            factor_clk = (clk_factor_pt)pclk;
            ret = sunxi_clk_factors_recalc_rate(factor_clk, &current_rate);
            if (ret != HAL_CLK_STATUS_OK)
            {
                ret = HAL_CLK_STATUS_DISABLED;
                break;
            }
            (*rate) = current_rate;
            break;

        /*      */
        case HAL_CLK_FIXED_SRC:
        case HAL_CLK_FIXED_FACTOR:
            (*rate) = pclk->clk_rate;
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
            break;
    }

    return ret;
}

hal_clk_status_t sunxi_clk_get_rate(hal_clk_id_t clk, u32 *rate)
{
    u32 i;
    clk_core_pt pclk = NULL;
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;
    }
    (*rate) = pclk->clk_rate;

    return HAL_CLK_STATUS_OK;
}


hal_clk_status_t sunxi_clk_set_rate(hal_clk_id_t clk, u32 rate)
{
    u32 i, parent_rate;
    clk_core_pt pclk = NULL;
    clk_periph_pt periph_clk = NULL;
    clk_factor_pt factor_clk = NULL;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;

    CCMU_TRACE();

    pclk = clk_get_core(clk);
    if (pclk == NULL)
    {
        return ret;
    }

    switch (HAL_CLK_GET_TYPE(clk))
    {
        /*      */
        case HAL_CLK_PERIPH:
            periph_clk = (clk_periph_pt)pclk;
            if (periph_clk->clk_core.clk_enbale  == HAL_CLK_STATUS_ENABLED)
            {
                return HAL_CLK_STATUS_ERROR_CLK_NEED_DISABLED;
            }
            if (periph_clk->clk_core.clk_rate == rate)
            {
                return HAL_CLK_STATUS_OK;
            }
            parent_rate = periph_clk->clk_core.parent_rate;
            ret =  sunxi_clk_periph_set_rate(periph_clk, rate);
            if (ret == HAL_CLK_STATUS_OK)
            {
                periph_clk->clk_core.clk_rate = rate;
            }
            break;
        /*      */
        case HAL_CLK_FACTOR:
            factor_clk = (clk_factor_pt)pclk;
            ret = sunxi_clk_factors_set_rate(factor_clk, rate);
            if (ret == HAL_CLK_STATUS_OK)
            {
                factor_clk->clk_core.clk_rate = rate;
            }
            break;
        /*      */
        case HAL_CLK_FIXED_SRC:
        case HAL_CLK_FIXED_FACTOR:
            ret = HAL_CLK_STATUS_ERROR_CLK_SET_RATE_REFUSED;
            break;
        /*      */
        default:
            ret = HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
            break;
    }

    CCMU_TRACE();
    return ret;
}


hal_clk_status_t sunxi_fixed_factor_clk_init(void)
{
    u32 i = 0, parent_rate = 0;
    clk_core_pt pclk = NULL;
    clk_core_pt parent_clk_core = NULL;
    clk_fixed_factor_pt fixed_factor = NULL;
    hal_clk_status_t ret = HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;

    CCMU_TRACE();
    for (i = 0; sunxi_clk_fixed_factor_arry[i] != NULL; i++)
    {
        fixed_factor = sunxi_clk_fixed_factor_arry[i];
        parent_clk_core = clk_get_core(fixed_factor->clk_core.current_parent);
        if (parent_clk_core == NULL)
        {
            return ret;
        }
        if (parent_clk_core->clk_enbale == HAL_CLK_STATUS_DISABLED)
        {
            return HAL_CLK_STATUS_ERROR_CLK_PARENT_DISABLED;
        }

        parent_rate = parent_clk_core->clk_rate;
        fixed_factor->clk_core.clk_enbale = HAL_CLK_STATUS_ENABLED;
        fixed_factor->clk_core.parent_rate = parent_rate;
        fixed_factor->clk_core.clk_rate = (parent_rate * fixed_factor->clk_mult) / fixed_factor->clk_div;

    }

    ret =  HAL_CLK_STATUS_OK;

    CCMU_TRACE();
    return ret;
}


hal_clk_status_t sunxi_periph_bus_clk_init(void)
{
    hal_clk_status_t ret;
    clk_base_pt clk_init;
    clk_periph_pt pclk;
    hal_clk_id_t parent_clk;
    u32 i = 0, parent_rate = 0, round_rate = 0, check_rate = 0;

    CCMU_TRACE();
    for (i = 0; sunxi_periph_clk_init_arry[i] != NULL; i++)
    {
        parent_clk = HAL_CLK_UNINITIALIZED ;
        clk_init = sunxi_periph_clk_init_arry[i];
        pclk = (clk_periph_pt)clk_get_core(clk_init->clk);
        if (pclk == NULL)
        {
            return HAL_CLK_STATUS_ERROR_CLK_NOT_FOUND;
        }
        CCMU_DBG("Clk-id %d init start.................\n", clk_init->clk);
        /* check and set clk parent select regs*/
        ret = sunxi_clk_get_parent(clk_init->clk,  &parent_clk);
        if (ret != HAL_CLK_STATUS_OK)
        {
            break;
        }
        if (clk_init->parent != parent_clk)
        {
            CCMU_DBG("set Parent-id %d \n", parent_clk);
            ret = sunxi_clk_set_parent(clk_init->clk,  clk_init->parent);
            if (ret != HAL_CLK_STATUS_OK)
            {
                break;
            }
        }

        /* check and get round clk*/
        ret =  sunxi_clk_get_rate(clk_init->parent, &parent_rate);
        if (ret != HAL_CLK_STATUS_OK)
        {
            break;
        }
        pclk->clk_core.current_parent = clk_init->parent;
        pclk->clk_core.parent_rate = parent_rate;
        ret = sunxi_clk_round_rate(clk_init->clk, clk_init->clk_rate,  &round_rate);
        if (ret  != HAL_CLK_STATUS_OK)
        {
            break;
        }
        CCMU_DBG("get round rate %dHZ\n", round_rate);
        /* check and disbale clk status*/
        ret = sunxi_clk_is_enabled(clk_init->clk);
        if (ret == HAL_CLK_STATUS_ENABLED)
        {
            ret = sunxi_clk_disable(clk_init->clk);
            if (ret != HAL_CLK_STATUS_OK)
            {
                break;
            }
        }
        CCMU_DBG("set new rate %dHZ\n", round_rate);
        /* set clk rate*/
        ret = sunxi_clk_set_rate(clk_init->clk, round_rate);
        if (ret != HAL_CLK_STATUS_OK)
        {
            break;
        }
        /* enable clk status*/
        ret = sunxi_clk_enabled(clk_init->clk);
        if (ret != HAL_CLK_STATUS_ENABLED)
        {
            break;
        }
        ret = sunxi_clk_recalc_rate(clk_init->clk, &check_rate);
        if (ret != HAL_CLK_STATUS_OK)
        {
            break;
        }
        CCMU_DBG("Clk-id %d cached rate %dHZ recalc new rate %dHZ, parent-id %d  parent rate %dHZ \n", clk_init->clk, pclk->clk_core.clk_rate, check_rate,
                 pclk->clk_core.current_parent, pclk->clk_core.parent_rate);
        CCMU_DBG("Clk-id %d init final .................\n", clk_init->clk);
    }

    CCMU_DBG("ret %d \n", ret);
    return ret;
}

hal_clk_status_t sunxi_factor_clk_init(void)
{
    u32 i;
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    hal_clk_status_t (*func)(void) = NULL;

    for (i = 0; sunxi_clk_factor_init[i] != NULL; i++)
    {
        func = sunxi_clk_factor_init[i];
        ret = func();
        if (ret != HAL_CLK_STATUS_OK)
        {
            break;
        }
    }

    return ret;
}


hal_clk_status_t clk_set_parent(hal_clk_id_t clk, hal_clk_id_t parent_clk)
{
    return sunxi_clk_set_parent(clk, parent_clk);
}


hal_clk_id_t clk_get_parent(hal_clk_id_t clk)
{
    hal_clk_id_t parent_clk = HAL_CLK_UNINITIALIZED ;
    hal_clk_status_t ret;

    ret =  sunxi_clk_get_parent(clk, &parent_clk);
    if (ret == HAL_CLK_STATUS_OK)
    {
        return parent_clk;
    }
    else
    {
        return HAL_CLK_UNINITIALIZED;
    }
}

hal_clk_status_t clk_disable_unprepare(hal_clk_id_t clk)
{
    return sunxi_clk_disable(clk);
}

hal_clk_status_t clk_prepare_enable(hal_clk_id_t clk)
{
    return sunxi_clk_enabled(clk);
}

hal_clk_status_t clk_is_enabled(hal_clk_id_t clk)
{
    return sunxi_clk_is_enabled(clk);
}

hal_clk_status_t clk_round_rate(hal_clk_id_t clk, u32 rate, u32 *prate)
{
    return sunxi_clk_round_rate(clk, rate, prate);
}

hal_clk_status_t clk_recalc_rate(hal_clk_id_t clk, u32 *p_rate)
{
    return sunxi_clk_recalc_rate(clk, p_rate);
}

hal_clk_status_t clk_set_rate(hal_clk_id_t clk, u32 rate)
{
    return sunxi_clk_set_rate(clk, rate);
}


hal_clk_status_t clk_get_rate(hal_clk_id_t clk, u32 *rate)
{
    return sunxi_clk_get_rate(clk, rate);
}

hal_clk_id_t clk_get(hal_clk_type_t type, hal_clk_id_t id)
{
    return id;
}

hal_clk_status_t clk_put(hal_clk_id_t id)
{
    return HAL_CLK_STATUS_OK;
}

hal_clk_status_t clk_init(void)
{
    hal_clk_status_t ret;

    ret = sunxi_factor_clk_init();
    /*the parent clk of some fixed-factor clk maybe factor-pll clk,
        so factor-pll clk init before fixed-factor clk*/
    ret = sunxi_fixed_factor_clk_init();
    ret = sunxi_periph_bus_clk_init();

    return ret;
}
