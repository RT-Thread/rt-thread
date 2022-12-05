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

#include <hal_clk.h>

void hal_clock_init(void)
{
    CCMU_TRACE();
    clk_init();
}

hal_clk_t hal_clock_get(hal_clk_type_t type, hal_clk_id_t id)
{
    CCMU_TRACE();
    return clk_get(type, id);
}

hal_clk_status_t hal_clock_put(hal_clk_t clk)
{
    CCMU_TRACE();
    return clk_put(clk);
}

hal_clk_status_t hal_clk_set_parent(hal_clk_t clk, hal_clk_t parent)
{
    CCMU_TRACE();
    return clk_set_parent(clk, parent);
}

hal_clk_t hal_clk_get_parent(hal_clk_t clk)
{
    CCMU_TRACE();
    return clk_get_parent(clk);
}

u32 hal_clk_recalc_rate(hal_clk_t clk)
{
    u32 rate = 0;

    CCMU_TRACE();
    clk_recalc_rate(clk, &rate);

    return rate;
}

u32 hal_clk_round_rate(hal_clk_t clk, u32 rate)
{
    u32 round_rate = 0;

    CCMU_TRACE();
    clk_round_rate(clk, rate, &round_rate);

    return round_rate;
}

u32  hal_clk_get_rate(hal_clk_t clk)
{
    u32 rate;

    CCMU_TRACE();
    clk_get_rate(clk, &rate);

    return rate;
}

hal_clk_status_t hal_clk_set_rate(hal_clk_t clk, u32 rate)
{
    hal_clk_status_t ret;

    CCMU_TRACE();
    ret = clk_set_rate(clk, rate);

    return ret;
}

hal_clk_status_t hal_clock_is_enabled(hal_clk_t clk)
{
    CCMU_TRACE();
    return clk_is_enabled(clk);
}

hal_clk_status_t hal_clock_enable(hal_clk_t clk)
{
    hal_clk_status_t ret;

    CCMU_TRACE();
    ret  =  clk_prepare_enable(clk);

    return ret;
}


hal_clk_status_t hal_clock_disable(hal_clk_t clk)
{
    hal_clk_status_t ret;

    CCMU_TRACE();
    ret  =  clk_disable_unprepare(clk);

    return ret;
}
