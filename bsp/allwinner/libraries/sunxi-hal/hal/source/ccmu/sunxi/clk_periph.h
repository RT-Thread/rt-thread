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

#ifndef __CLK_PERIPH_H__
#define __CLK_PERIPH_H__

#include "clk.h"

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define SUNXI_CLK_PERIPH_CONFIG(name, _mux_reg, _mux_shift, _mux_width,  \
                                _div_reg, _div_mshift, _div_mwidth, _div_nshift, _div_nwidth,   \
                                _gate_flags, _enable_reg, _reset_reg, _bus_gate_reg, _drm_gate_reg, \
                                _enable_shift, _reset_shift, _bus_gate_shift, _dram_gate_shift,  _com_gate, _com_gate_off) \
struct sunxi_clk_periph sunxi_clk_periph_config_##name = {      \
    .mux = {                                                \
                                                            .reg = (volatile uint32_t   *)_mux_reg,             \
                                                            .shift = _mux_shift,                                \
                                                            .width = _mux_width,                                \
           },                                                      \
           .divider = {                                            \
                                                                   .reg = (volatile uint32_t   *)_div_reg,                   \
                                                                   .mshift = _div_mshift,                              \
                                                                   .mwidth = _div_mwidth,                              \
                                                                   .nshift = _div_nshift,                              \
                                                                   .nwidth = _div_nwidth,                              \
                      },                                                      \
                      .gate = {                                               \
                                                                              .flags = _gate_flags,                               \
                                                                              .enable = (volatile uint32_t   *)_enable_reg,             \
                                                                              .reset = (volatile uint32_t   *)_reset_reg,               \
                                                                              .bus = (volatile uint32_t   *)_bus_gate_reg,              \
                                                                              .dram = (volatile uint32_t   *)_drm_gate_reg,             \
                                                                              .enb_shift = _enable_shift,                         \
                                                                              .rst_shift = _reset_shift,                          \
                                                                              .bus_shift = _bus_gate_shift,                       \
                                                                              .ddr_shift = _dram_gate_shift,                      \
                              },                                                      \
                              .com_gate = _com_gate,                                  \
                                          .com_gate_off = _com_gate_off,                          \
}

#define SUNXI_CLK_PERIPH(_name, _clk,  _parent_arry) \
    clk_periph_t sunxi_clk_periph_##_name  = {  \
                                                .clk_core = {   \
                                                                .clk = _clk,    \
                                                                .clk_type = HAL_CLK_PERIPH, \
                                                                .current_parent = HAL_CLK_UNINITIALIZED,    \
                                                                .current_parent_type = 0, \
                                                                .clk_rate = 0,     \
                                                                .parent_rate = 0,      \
                                                                .clk_enbale = HAL_CLK_STATUS_DISABLED,   \
                                                            },  \
                                                .parent_arry = _parent_arry,    \
                                                .parent_arry_size = ARRAY_SIZE(_parent_arry), \
                                                .config = &sunxi_clk_periph_config_##_name,     \
                                             }

#define SUNXI_PERIPH_INIT(_name, _clk, _parent_clk, _clk_rate) \
    clk_base_t sunxi_periph_clk_init_##_name = {    \
                                                    .clk = _clk,    \
                                                    .parent = _parent_clk,  \
                                                    .clk_rate = _clk_rate,  \
                                               }


/**
 * struct sunxi_clk_periph_gate - peripheral gate clock
 *
 * @flags:      hardware-specific flags
 * @enable:     enable register
 * @reset:      reset register
 * @bus:        bus gating resiter
 * @dram:       dram gating register
 * @enb_shift:  enable gate bit shift
 * @rst_shift:  reset gate bit shift
 * @bus_shift:  bus gate bit shift
 * @ddr_shift:  dram gate bit shift
 *
 * Flags:
 * SUNXI_PERIPH_NO_GATE - this flag indicates that module gate is not allowed for this module.
 * SUNXI_PERIPH_NO_RESET - This flag indicates that reset is not allowed for this module.
 * SUNXI_PERIPH_NO_BUS_GATE - This flag indicates that bus gate is not allowed for this module.
 * SUNXI_PERIPH_NO_DDR_GATE - This flag indicates that dram gate is not allowed for this module.
 */
struct sunxi_clk_periph_gate
{
    u32             flags;
    volatile uint32_t   *enable;
    volatile uint32_t   *reset;
    volatile uint32_t   *bus;
    volatile uint32_t   *dram;
    u8              enb_shift;
    u8              rst_shift;
    u8              bus_shift;
    u8              ddr_shift;
};

/**
 * struct sunxi_clk_periph_div - periph divider clock
 *
 * @reg:        register containing divider
 * @mshift:     shift to the divider-m bit field, div = (m+1)
 * @mwidth:     width of the divider-m bit field
 * @nshift:     shift to the divider-n bit field, div = (1<<n)
 * @nwidth:     width of the divider-n bit field
 * @lock:       register lock
 *
 * Flags:
 */
struct sunxi_clk_periph_div
{
    volatile uint32_t   *reg;
    u8              mshift;
    u8              mwidth;
    u8              nshift;
    u8              nwidth;
    //spinlock_t      *lock;
};


/**
 * struct sunxi_clk_periph_mux - multiplexer clock
 *
 * @reg:        register controlling multiplexer
 * @shift:      shift to multiplexer bit field
 * @width:      width of mutliplexer bit field
 * @lock:       register lock
 *
 * Clock with multiple selectable parents.  Implements .get_parent, .set_parent
 * and .recalc_rate
 *
 */
struct sunxi_clk_periph_mux
{
    volatile uint32_t   *reg;
    u8              shift;
    u8              width;
    //spinlock_t      *lock;
};

struct sunxi_clk_comgate
{
    const u8        *name;
    u16             val;
    u16             mask;
    u8              share;
    u8              res;
};

#define BUS_GATE_SHARE  0x01
#define RST_GATE_SHARE  0x02
#define MBUS_GATE_SHARE 0x04
#define MOD_GATE_SHARE  0x08

#define IS_SHARE_BUS_GATE(x)  (x->com_gate?((x->com_gate->share & BUS_GATE_SHARE)?1:0):0)
#define IS_SHARE_RST_GATE(x)  (x->com_gate?((x->com_gate->share & RST_GATE_SHARE)?1:0):0)
#define IS_SHARE_MBUS_GATE(x) (x->com_gate?((x->com_gate->share & MBUS_GATE_SHARE)?1:0):0)
#define IS_SHARE_MOD_GATE(x)  (x->com_gate?((x->com_gate->share & MOD_GATE_SHARE)?1:0):0)

/**
 * struct sunxi-clk-periph - peripheral clock
 *
 * @hw:         handle between common and hardware-specific interfaces
 * @flags:      flags used across common struct clk, please take refference of the clk-provider.h
 * @lock:       lock for protecting the periph clock operations
 * @mux:        mux clock
 * @gate:       gate clock
 * @divider:    divider clock
 * @com_gate:       the shared clock
 * @com_gate_off:   bit shift to mark the flag in the com_gate
 * @priv_clkops:    divider clock ops
 * @priv_regops:    gate clock ops
 */
struct sunxi_clk_periph
{
    //struct clk_hw                   hw;
    //unsigned long                   flags;
    //spinlock_t                      *lock;

    struct sunxi_clk_periph_mux     mux;
    struct sunxi_clk_periph_gate    gate;
    struct sunxi_clk_periph_div     divider;
    struct sunxi_clk_comgate       *com_gate;
    u8                              com_gate_off;
    //struct clk_ops                 *priv_clkops;
    //struct sunxi_reg_ops           *priv_regops;
};


hal_clk_status_t sunxi_clk_periph_get_parent(clk_periph_pt clk, u8 *parent_index);
hal_clk_status_t sunxi_clk_periph_set_parent(clk_periph_pt clk, u8 index);
hal_clk_status_t sunxi_clk_periph_enable(clk_periph_pt clk);
hal_clk_status_t sunxi_clk_periph_is_enabled(clk_periph_pt clk);
hal_clk_status_t sunxi_clk_periph_disable(clk_periph_pt clk);
hal_clk_status_t sunxi_clk_periph_recalc_rate(clk_periph_pt clk, u32 *rate);
u32 sunxi_clk_periph_round_rate(clk_periph_pt clk, u32 rate, u32 prate);
hal_clk_status_t sunxi_clk_periph_set_rate(clk_periph_pt clk, u32 rate);


#endif /* __MACH_SUNXI_CLK_PERIPH_H */
