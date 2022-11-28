// SPDX-License-Identifier: GPL-2.0-only
/*
 * sunxi RTC ccu driver
 *
 * Copyright (c) 2020, DaLv <lvda@allwinnertech.com>
 */

#include "ccu.h"
#include "ccu_common.h"
#include "ccu_reset.h"
#include "ccu_div.h"
#include "ccu_gate.h"
#include "ccu_mp.h"
#include "ccu_mult.h"
#include "ccu_nk.h"
#include "ccu_nkm.h"
#include "ccu_nkmp.h"
#include "ccu_nm.h"
#include "ccu_phase.h"

#include "ccu-sun8iw20-rtc.h"

/*
 * iosc clk:
 */
static SUNXI_CCU_GATE(iosc_clk, "iosc", "rc-16m", 0x160, BIT(0), 0);

static SUNXI_CCU_GATE_WITH_KEY(ext32k_gate_clk, "ext32k-gate",
                               "ext-32k", 0x0,
                               KEY_FIELD_MAGIC_NUM_RTC,
                               BIT(4), 0);

static CLK_FIXED_FACTOR(iosc_div32k_clk, "iosc-div32k", "iosc", 500, 1, 0);

/*
 * osc32k clk(losc)
 */
static const char *const osc32k_parents[] = { "iosc-div32k", "ext32k-gate" };
static SUNXI_CCU_MUX_WITH_GATE_KEY(osc32k_clk, "osc32k", osc32k_parents,
                                   0x0, 0, 1,
                                   KEY_FIELD_MAGIC_NUM_RTC, 0, 0);

static SUNXI_CCU_GATE_WITH_FIXED_RATE(dcxo24M_div32k_clk, "dcxo24M-div32k",
                                      "dcxo24M", 0x60,
                                      32768, BIT(16));
/*
 * rtc-1k clock
 */
static const char *const rtc32k_clk_parents[] = { "osc32k", "dcxo24M-div32k"};
static SUNXI_CCU_MUX_WITH_GATE_KEY(rtc32k_clk, "rtc32k", rtc32k_clk_parents,
                                   0x0, 1, 1,
                                   KEY_FIELD_MAGIC_NUM_RTC, 0, 0);
static CLK_FIXED_FACTOR(rtc_1k_clk, "rtc-1k", "rtc32k", 32, 1, 0);

/* rtc-32k-fanout: only for debug */
static const char *const rtc_32k_fanout_clk_parents[] = { "osc32k", "ext32k-gate",
                                                          "dcxo24M-div32k"
                                                        };
static SUNXI_CCU_MUX_WITH_GATE(rtc_32k_fanout_clk, "rtc-32k-fanout",
                               rtc_32k_fanout_clk_parents, 0x60, 1,
                               2, BIT(0), 0);

/* TODO: should add the div func */
static SUNXI_CCU_GATE(rtc_spi_clk, "rtc-spi", "r-ahb", 0x310, BIT(31), 0);

static struct ccu_common *sun8iw20_rtc_ccu_clks[] =
{
    &iosc_clk.common,
    &ext32k_gate_clk.common,
    &osc32k_clk.common,
    &dcxo24M_div32k_clk.common,
    &rtc32k_clk.common,
    &rtc_32k_fanout_clk.common,
    &rtc_spi_clk.common,
};

static struct clk_hw_onecell_data sun8iw20_rtc_ccu_hw_clks =
{
    .hws    = {
        [CLK_IOSC]          = &iosc_clk.common.hw,
        [CLK_EXT32K_GATE]       = &ext32k_gate_clk.common.hw,
        [CLK_IOSC_DIV32K]       = &iosc_div32k_clk.hw,
        [CLK_OSC32K]            = &osc32k_clk.common.hw,
        [CLK_DCXO24M_DIV32K]        = &dcxo24M_div32k_clk.common.hw,
        [CLK_RTC32K]            = &rtc32k_clk.common.hw,
        [CLK_RTC_1K]            = &rtc_1k_clk.hw,
        [CLK_RTC_32K_FANOUT]        = &rtc_32k_fanout_clk.common.hw,
        [CLK_RTC_SPI]           = &rtc_spi_clk.common.hw,
    },
    .num    = CLK_RTC_NUMBER,
};

static const struct sunxi_ccu_desc sun8iw20_rtc_ccu_desc =
{
    .ccu_clks   = sun8iw20_rtc_ccu_clks,
    .num_ccu_clks   = ARRAY_SIZE(sun8iw20_rtc_ccu_clks),

    .hw_clks    = &sun8iw20_rtc_ccu_hw_clks,
    .clk_type   = HAL_SUNXI_RTC_CCU,
};

static void clock_source_init(unsigned long base)
{
    /* (1) enable DCXO */
    /* by default, DCXO_EN = 1. We don't have to do this... */
    set_reg(base + XO_CTRL_REG, 0x1, 1, 1);

    /* (2) enable auto switch function */
    /*
     * In some cases, we boot with auto switch function disabled, and try to
     * enable the auto switch function by rebooting.
     * But the rtc default value does not change unless vcc-rtc is loss.
     * So we should not rely on the default value of reg.
     * BIT(14): LOSC auto switch 32k clk source sel enable. 1: enable
     * BIT(15): LOSC auto switch function disable. 1: disable
     */
    set_reg_key(base + LOSC_CTRL_REG,
                KEY_FIELD_MAGIC_NUM_RTC >> 16, 16, 16,
                0x1, 2, 14);

    /* (3) set the parent of osc32k-sys to ext-osc32k */
    set_reg_key(base + LOSC_CTRL_REG,
                KEY_FIELD_MAGIC_NUM_RTC >> 16, 16, 16,
                0x1, 1, 0);

    /* (4) set the parent of osc32k-out to osc32k-sys */
    /* by default, LOSC_OUT_SRC_SEL = 0x0. We don't have to do this... */
    set_reg(base + LOSC_OUT_GATING_REG,
            0x0, 2, 1);
}

int sunxi_rtc_ccu_init(void)
{
    unsigned long reg = (unsigned long)SUNXI_RTC_CCU_REG;

    clock_source_init(reg);

    return ccu_common_init(reg, &sun8iw20_rtc_ccu_desc);
}
