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

#ifndef __CLK_FACTORS_H__
#define __CLK_FACTORS_H__

#include "clk.h"

struct sunxi_clk_factor_freq
{
    u32 factor;
    u32 freq;
};

#define FACTOR_ALL(nv, ns, nw, kv, ks, kw, mv, ms, mw, \
                   pv, ps, pw, d1v, d1s, d1w, d2v, d2s, d2w) \
((((nv & ((1 << nw) - 1)) << ns) | \
  ((kv & ((1 << kw) - 1)) << ks) | \
  ((mv & ((1 << mw) - 1)) << ms) | \
  ((pv & ((1 << pw) - 1)) << ps) | \
  ((d1v & ((1 << d1w) - 1)) << d1s) | \
  ((d2v & ((1 << d2w) - 1)) << d2s)))

#define F_N8X8_P16x2(nv, pv)      (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, pv, 16, 2, 0, 0, 0, 0, 0, 0))
#define F_N8X8_D1V1X1_D2V0X1(nv, d1v, d2v) (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, d1v, 1, 1, d2v, 0, 1))
#define F_N8X8_D1V1X1(nv, d1v)             (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, d1v, 1, 1, 0, 0, 0))
#define F_N8X8_D1V4X2_D2V0X2(nv, d1v, d2v) (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, d1v, 4, 2, d2v, 0, 2))
#define F_N8X8_P16X6_D1V1X1_D2V0X1(nv, pv, d1v, d2v) (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, pv, 16, 6, d1v, 1, 1, d2v, 0, 1))

#define PLLCPU(n, p, freq)          {F_N8X8_P16x2(n, p), freq}
#define PLLDDR(n, d1, d2, freq)     {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLPERIPH0(n, d1, d2, freq)  {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLPERIPH1(n, d1, d2, freq)  {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLVIDEO0(n, d1, freq)       {F_N8X8_D1V1X1(n, d1), freq}
#define PLLAUDIO(n, p, d1, d2, freq) {F_N8X8_P16X6_D1V1X1_D2V0X1(n, p, d1, d2), freq}

#define SUNXI_CLK_FACTORS_CONFIG(name, _nshift, _nwidth, _kshift, _kwidth, \
                                 _mshift, _mwidth, _pshift, _pwidth, _d1shift, _d1width, \
                                 _d2shift, _d2width, _frac, _outshift, _modeshift, \
                                 _enshift, _sdmshift, _sdmwidth, _sdmpat, _sdmval, \
                                 _mux_inshift, _out_enshift)                        \
struct sunxi_clk_factors_config sunxi_clk_factor_config_##name = { \
    .nshift = _nshift,  \
              .nwidth = _nwidth,  \
                        .kshift = _kshift,  \
                                  .kwidth = _kwidth,  \
                                            .mshift = _mshift,  \
                                                    .mwidth = _mwidth,  \
                                                            .pshift = _pshift,  \
                                                                    .pwidth = _pwidth,  \
                                                                            .d1shift = _d1shift,    \
                                                                                    .d1width = _d1width,    \
                                                                                            .d2shift = _d2shift,    \
                                                                                                    .d2width = _d2width,    \
                                                                                                            .frac = _frac,  \
                                                                                                                    .outshift = _outshift,  \
                                                                                                                            .modeshift = _modeshift,     \
                                                                                                                                    .enshift = _enshift,    \
                                                                                                                                            .sdmshift = _sdmshift,    \
                                                                                                                                                    .sdmwidth = _sdmwidth,    \
                                                                                                                                                            .sdmpat  = _sdmpat,    \
                                                                                                                                                                    .sdmval  = _sdmval,    \
                                                                                                                                                                            .updshift = 0,         \
                                                                                                                                                                                    .mux_inshift = _mux_inshift, \
                                                                                                                                                                                            .out_enshift = _out_enshift, \
}

#define SUNXI_CLK_FACTORS_INIT(_name, _reg, _lock_reg, _lock_bit, _pll_lock_ctrl_reg, _lock_en_bit )   \
    struct factor_init_data sunxi_clk_factor_init_##_name = {    \
        .reg =_reg,     \
              .lock_reg = _lock_reg,  \
                          .pll_lock_ctrl_reg = _pll_lock_ctrl_reg,    \
                                               .lock_bit = _lock_bit,  \
                                                       .lock_en_bit = _lock_en_bit,    \
                                                               .lock_mode = PLL_LOCK_NEW_MODE, \
                                                                       .config = &sunxi_clk_factor_config_##_name,     \
                                                                               .get_factors = &get_factors_##_name,    \
                                                                                       .calc_rate = &calc_rate_##_name,    \
    }

#define SUNXI_CLK_FACTOR(_name, _clk, _current_parent, _current_parent_type, _clk_rate,  _parent_rate ) \
    clk_factor_t sunxi_clk_factor_##_name  = {  \
                                                .clk_core = {   \
                                                                .clk = _clk,    \
                                                                .clk_type = HAL_CLK_FACTOR, \
                                                                .current_parent = _current_parent,  \
                                                                .current_parent_type = _current_parent_type, \
                                                                .clk_rate = _clk_rate,      \
                                                                .parent_rate = _parent_rate,        \
                                                                .clk_enbale = HAL_CLK_STATUS_DISABLED,   \
                                                            },  \
                                                .factor_data = &sunxi_clk_factor_init_##_name,   \
                                             }


/*no-change-from-linux*/
typedef enum pll_lock_mode
{
    PLL_LOCK_NEW_MODE = 0x0,
    PLL_LOCK_OLD_MODE,
    PLL_LOCK_NONE_MODE,
    PLL_LOCK_MODE_MAX,
} pll_lock_mode_e;

/**
 * struct clk_factors_value - factor value
 *
 * @factorn:    factor-n value
 * @factork:    factor-k value
 * @factorm:    factor-m value
 * @factorp:    factor-p value
 * @factord1:   factor-d1 value
 * @factord2:   factor-d2 value
 * @frac_mode:  fraction mode value
 * @frac_freq:  fraction frequnecy value
 */

/*no-change-from-linux*/
struct clk_factors_value
{
    u16 factorn;
    u16 factork;

    u16 factorm;
    u16 factorp;

    u16 factord1;
    u16 factord2;

    u16 frac_mode;
    u16 frac_freq;
};


/**
 * struct sunxi_clk_factors_config - factor config
 *
 * @nshift:     shift to factor-n bit field
 * @nwidth:     width of factor-n bit field
 * @kshift:     shift to factor-k bit field
 * @kwidth:     width of factor-k bit field
 * @mshift:     shift to factor-m bit field
 * @mwidth:     width of factor-m bit field
 * @pshift:     shift to factor-p bit field
 * @pwidth:     width of factor-p bit field
 * @d1shift:    shift to factor-d1 bit field
 * @d1width:    width of factor-d1 bit field
 * @d2shift:    shift to factor-d2 bit field
 * @d2width:    width of factor-d2 bit field
 * @frac:       flag of fraction
 * @outshift:   shift to frequency select bit field
 * @modeshift:  shift to fraction/integer mode select
 * @enshift:    shift to factor enable bit field
 * @lockshift:  shift to factor lock status bit filed
 * @sdmshift:   shift to factor sdm enable bit filed
 * @sdmwidth    shift to factor sdm width bit filed
 * @sdmpat      sdmpat reg address offset
 * @sdmval      sdm default value
 * @updshift    shift to update bit (especial for ddr/ddr0/ddr1)
 * @delay       for flat factors delay.
 * @mux_inshift shift to multiplexer(multiple 24M source clocks) bit field
 * @out_enshift shift to enable pll clock output bit field
 */
/*no-change-from-linux*/
struct sunxi_clk_factors_config
{
    u8 nshift;
    u8 nwidth;
    u8 kshift;
    u8 kwidth;

    u8 mshift;
    u8 mwidth;
    u8 pshift;
    u8 pwidth;

    u8 d1shift;
    u8 d1width;
    u8 d2shift;
    u8 d2width;

    u8 frac;
    u8 outshift;
    u8 modeshift;
    u8 enshift;

    u8 lockshift;
    u8 sdmshift;
    u8 sdmwidth;

    volatile uint32_t *sdmpat;
    u32 sdmval;

    u32 updshift;
    u32 delay;

    u32 mux_inshift;
    u32 out_enshift;
};

/**
 * struct factor_init_data - factor init data
 *
 * @name:       name of the clock
 * @parent_name:name of the parent
 * @num_parents:counter of the parents
 * @flags:      factor optimal configurations
 * @reg:        register address for the factor
 * @lock_reg:   register address for check if the pll has locked
 * @lock_bit:   bit offset of the lock_reg, to check if the the pll has locked
 * @pll_lock_ctrl_reg: pll lock control register, this function is first used on
 *              the sun50i, to enable the function of pll hardlock
 * @lock_en_bit:bit offset of the pll_lock_ctrl_reg, to enable the function
 * @config:     configuration of the factor
 * @get_factors:function for get factors parameter under a given frequency
 * @calc_rate:  function for calculate the factor frequency
 * @priv_ops:   private operations hook for the special factor
 * @priv_regops:register operation hook for read/write the register
 *
 */
struct factor_init_data
{
    //const char          *name;
    //const char          **parent_names;
    //int                 num_parents;
    //unsigned long       flags;
    volatile uint32_t   *reg;
    volatile uint32_t   *lock_reg;
    volatile uint32_t   *pll_lock_ctrl_reg;
    u8 lock_bit;
    u8 lock_en_bit;
    pll_lock_mode_e     lock_mode;
    struct sunxi_clk_factors_config *config;
    int (*get_factors)(u32 rate, u32 parent_rate, struct clk_factors_value *factor);
    int (*calc_rate)(u32 parent_rate, struct clk_factors_value *factor);

    //struct clk_ops *priv_ops;
    //struct sunxi_reg_ops *priv_regops;
};

hal_clk_status_t sunxi_clk_fators_enable(clk_factor_pt clk);
hal_clk_status_t sunxi_clk_fators_disable(clk_factor_pt clk);
hal_clk_status_t sunxi_clk_fators_is_enabled(clk_factor_pt clk);
hal_clk_status_t sunxi_clk_factors_recalc_rate(clk_factor_pt clk, u32 *rate);
hal_clk_status_t sunxi_clk_factors_set_rate(clk_factor_pt clk, u32 rate);
u32 sunxi_clk_factors_round_rate(clk_factor_pt clk, u32 rate);
int sunxi_clk_com_ftr_sr(struct sunxi_clk_factors_config *f_config,
                         struct clk_factors_value *factor,
                         struct sunxi_clk_factor_freq table[],
                         unsigned long index, unsigned long tbl_count);

#endif
