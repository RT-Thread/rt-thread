// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 huangzhenwei@allwinnertech.com
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

#include "ccu-sun8iw20.h"
#include <hal_clk.h>
#include <hal_reset.h>

/* ccu_des_start */
/*
 * The CPU PLL is actually NP clock, with P being /1, /2 or /4. However
 * P should only be used for output frequencies lower than 288 MHz.
 *
 * For now we can just model it as a multiplier clock, and force P to /1.
 *
 * The M factor is present in the register's description, but not in the
 * frequency formula, and it's documented as "M is only used for backdoor
 * testing", so it's not modelled and then force to 0.
 */
#define SUN8IW20_PLL_CPUX_REG       0x000
static struct ccu_mult pll_cpux_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .mult       = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .common     = {
        .reg        = 0x000,
        .hw.init    = CLK_HW_INIT("pll-cpux", "dcxo24M",
                                  &ccu_mult_ops,
                                  CLK_SET_RATE_UNGATE),
    },
};

/* Some PLLs are input * N / div1 / P. Model them as NKMP with no K */
#define SUN8IW20_PLL_DDR0_REG       0x010
static struct ccu_nkmp pll_ddr0_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .n      = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .m      = _SUNXI_CCU_DIV(1, 1), /* input divider */
    .p      = _SUNXI_CCU_DIV(0, 1), /* output divider */
    .common     = {
        .reg        = 0x010,
        .hw.init    = CLK_HW_INIT("pll-ddr0", "dcxo24M",
                                  &ccu_nkmp_ops,
                                  CLK_SET_RATE_UNGATE |
                                  CLK_IS_CRITICAL),
    },
};

#define SUN8IW20_PLL_PERIPH0_REG    0x020
static struct ccu_nm pll_periph0_parent_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .n      = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .m      = _SUNXI_CCU_DIV(1, 1), /* input divider */
    .common     = {
        .reg        = 0x020,
        .hw.init    = CLK_HW_INIT("pll-periph0-parent", "dcxo24M",
                                  &ccu_nm_ops,
                                  CLK_SET_RATE_UNGATE),
    },
};

static SUNXI_CCU_M(pll_periph0_2x_clk, "pll-periph0-2x",
                   "pll-periph0-parent", 0x020, 16, 3, 0);

static SUNXI_CCU_M(pll_periph0_800m_clk, "pll-periph0-800m",
                   "pll-periph0-parent", 0x020, 20, 3, 0);

/*
 * For Video PLLs, the output divider is described as "used for testing"
 * in the user manual. So it's not modelled and forced to 0.
 */
#define SUN8IW20_PLL_VIDEO0_REG 0x040
static struct ccu_nm pll_video0_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .n      = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .m      = _SUNXI_CCU_DIV(1, 1), /* input divider */
    .fixed_post_div = 4,
    .min_rate   = 288000000,
    .max_rate   = 2400000000UL,
    .common     = {
        .reg        = 0x040,
        .features   = CCU_FEATURE_FIXED_POSTDIV,
        .hw.init    = CLK_HW_INIT("pll-video0", "dcxo24M",
                                  &ccu_nm_ops,
                                  CLK_SET_RATE_UNGATE),
    },
};

#define SUN8IW20_PLL_VIDEO1_REG 0x048
static struct ccu_nm pll_video1_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .n      = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .m      = _SUNXI_CCU_DIV(1, 1), /* input divider */
    .fixed_post_div = 4,
    .min_rate   = 288000000,
    .max_rate   = 2400000000UL,
    .common     = {
        .reg        = 0x048,
        .features   = CCU_FEATURE_FIXED_POSTDIV,
        .hw.init    = CLK_HW_INIT("pll-video1", "dcxo24M",
                                  &ccu_nm_ops,
                                  CLK_SET_RATE_UNGATE),
    },
};

#define SUN8IW20_PLL_VE_REG     0x058
static struct ccu_nkmp pll_ve_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .n      = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .m      = _SUNXI_CCU_DIV(1, 1), /* input divider */
    .p      = _SUNXI_CCU_DIV(0, 1), /* output divider */
    .common     = {
        .reg        = 0x058,
        .hw.init    = CLK_HW_INIT("pll-ve", "dcxo24M",
                                  &ccu_nkmp_ops,
                                  CLK_SET_RATE_UNGATE),
    },
};

/*
 * The Audio PLL has m0, m1 dividers in addition to the usual N, M
 * factors. Since we only need 4 frequencies from this PLL: 22.5792 MHz,
 * 24.576 MHz, 90.3168MHz and 98.304MHz ignore them for now.
 * Enforce the default for them, which is d1 = 0, d2 = 1.
 */
#define SUN8IW20_PLL_AUDIO0_REG     0x078
static struct ccu_sdm_setting pll_audio0_sdm_table[] =
{
    { .rate = 45158400, .pattern = 0xc001bcd3, .m = 18, .n = 33 },
    { .rate = 49152000, .pattern = 0xc001eb85, .m = 20, .n = 40 },
    { .rate = 180633600, .pattern = 0xc001288d, .m = 3, .n = 22 },
    { .rate = 196608000, .pattern = 0xc001eb85, .m = 5, .n = 40 },
};

static struct ccu_nm pll_audio0_4x_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .n      = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .m      = _SUNXI_CCU_DIV(16, 6),
    .fixed_post_div = 2,
    .sdm        = _SUNXI_CCU_SDM(pll_audio0_sdm_table, BIT(24),
                                 0x178, BIT(31)),
    .common     = {
        .reg        = 0x078,
        .features   = CCU_FEATURE_FIXED_POSTDIV |
        CCU_FEATURE_SIGMA_DELTA_MOD,
        .hw.init    = CLK_HW_INIT("pll-audio0-4x", "dcxo24M",
                                  &ccu_nm_ops,
                                  CLK_SET_RATE_UNGATE),
    },
};

/*
 *  * PLL_AUDIO1 don't need Fractional-N. The output is usually 614.4M for audio
 *   * The codec-adc or dac should be divided by themself to output the 24.576M
 *
 */
#define SUN8IW20_PLL_AUDIO1_REG     0x080
static struct ccu_nm pll_audio1_clk =
{
    .enable     = BIT(27),
    .lock       = BIT(28),
    .n      = _SUNXI_CCU_MULT_MIN(8, 8, 12),
    .m      = _SUNXI_CCU_DIV(1, 1),
    /*.sdm      = _SUNXI_CCU_SDM(pll_audio1_sdm_table, BIT(24),
                     0x178, BIT(31)),*/
    .common     = {
        .reg        = 0x080,
        .features   = CCU_FEATURE_SIGMA_DELTA_MOD,
        .hw.init    = CLK_HW_INIT("pll-audio1", "dcxo24M",
                                  &ccu_nm_ops,
                                  CLK_SET_RATE_UNGATE),
    },
};
static SUNXI_CCU_M(pll_audio1_div2_clk, "pll-audio1-div2", "pll-audio1", 0x080, 16, 3, 0);
static SUNXI_CCU_M(pll_audio1_div5_clk, "pll-audio1-div5", "pll-audio1", 0x080, 20, 3, 0);

static struct clk_div_table pll_cpux_div_table[] =
{
    { .val = 0, .div = 1 },
    { .val = 1, .div = 2 },
    { .val = 2, .div = 4 },
    { /* Sentinel */ },
};

static SUNXI_CCU_DIV_TABLE(pll_cpux_div, "pll-cpux-div",
                           "pll-cpux", 0x500, 16, 2,
                           pll_cpux_div_table, 0);

static const char *const cpux_parents[] = { "dcxo24M", "osc32k",
                                            "iosc", "pll-cpux-div",
                                            "pll-periph0", "pll-periph0-2x",
                                            "pll-periph0-800M"
                                          };

static SUNXI_CCU_MUX(cpux_clk, "cpux", cpux_parents,
                     0x500, 24, 3, CLK_SET_RATE_PARENT | CLK_IS_CRITICAL);

static SUNXI_CCU_M(axi_clk, "axi", "cpux", 0x500, 0, 2, 0);

static SUNXI_CCU_M(apb_clk, "apb", "cpux", 0x500, 8, 2, 0);

static const char *const psi_ahb_parents[] = { "dcxo24M", "osc32k",
                                               "iosc", "pll-periph0"
                                             };
static SUNXI_CCU_MP_WITH_MUX(psi_ahb_clk, "psi-ahb",
                             psi_ahb_parents,
                             0x510,
                             0, 2,  /* M */
                             8, 2,  /* P */
                             24, 2, /* mux */
                             0);

static const char *const apb0_apb1_parents[] = { "dcxo24M", "osc32k",
                                                 "psi-ahb", "pll-periph0"
                                               };
static SUNXI_CCU_MP_WITH_MUX(apb0_clk, "apb0", apb0_apb1_parents, 0x520,
                             0, 5,  /* M */
                             8, 2,  /* P */
                             24, 2, /* mux */
                             0);

static SUNXI_CCU_MP_WITH_MUX(apb1_clk, "apb1", apb0_apb1_parents, 0x524,
                             0, 5,  /* M */
                             8, 2,  /* P */
                             24, 2, /* mux */
                             0);

static const char *const de_di_g2d_parents[] = { "pll-periph0-2x", "pll-video0-4x",
                                                 "pll-video1-4x", "pll-audio1-div2"
                                               };
static SUNXI_CCU_M_WITH_MUX_GATE(de0_clk, "de0", de_di_g2d_parents, 0x600,
                                 0, 5,      /* M */
                                 24, 3,     /* mux */
                                 BIT(31),   /* gate */
                                 CLK_SET_RATE_PARENT);

static SUNXI_CCU_GATE(bus_de0_clk, "bus-de0", "psi-ahb",
                      0x60c, BIT(0), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(di_clk, "di", de_di_g2d_parents, 0x620,
                                 0, 5,      /* M */
                                 24, 3,     /* mux */
                                 BIT(31),   /* gate */
                                 CLK_SET_RATE_PARENT);

static SUNXI_CCU_GATE(bus_di_clk, "bus-di", "psi-ahb",
                      0x62c, BIT(0), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(g2d_clk, "g2d",
                                 de_di_g2d_parents,
                                 0x630,
                                 0, 5,      /* M */
                                 24, 3,     /* mux */
                                 BIT(31),   /* gate */
                                 0);

static SUNXI_CCU_GATE(bus_g2d_clk, "bus-g2d", "psi-ahb",
                      0x63c, BIT(0), 0);

static const char *const ce_parents[] = { "dcxo24M", "pll-periph0-2x",
                                          "pll-periph0"
                                        };
static SUNXI_CCU_MP_WITH_MUX_GATE(ce_clk, "ce", ce_parents, 0x680,
                                  0, 4,     /* M */
                                  8, 2,     /* P */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_ce_clk, "bus-ce", "psi-ahb",
                      0x68c, BIT(0), 0);

static const char *const ve_parents[] = { "pll-ve", "pll-periph0-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(ve_clk, "ve", ve_parents, 0x690,
                                 0, 5,      /* M */
                                 24, 1,     /* mux */
                                 BIT(31),   /* gate */
                                 CLK_SET_RATE_PARENT);

static SUNXI_CCU_GATE(bus_ve_clk, "bus-ve", "psi-ahb",
                      0x69c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_dma_clk, "bus-dma", "psi-ahb",
                      0x70c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_msgbox0_clk, "bus-msgbox0", "psi-ahb",
                      0x71c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_msgbox1_clk, "bus-msgbox1", "psi-ahb",
                      0x71c, BIT(1), 0);

static SUNXI_CCU_GATE(bus_msgbox2_clk, "bus-msgbox2", "psi-ahb",
                      0x71c, BIT(2), 0);

static SUNXI_CCU_GATE(bus_spinlock_clk, "bus-spinlock", "psi-ahb",
                      0x72c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_hstimer_clk, "bus-hstimer", "psi-ahb",
                      0x73c, BIT(0), 0);

static SUNXI_CCU_GATE(avs_clk, "avs", "dcxo24M", 0x740, BIT(31), 0);

static SUNXI_CCU_GATE(bus_dbg_clk, "bus-dbg", "psi-ahb",
                      0x78c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_pwm_clk, "bus-pwm", "apb0", 0x7ac, BIT(0), 0);

static SUNXI_CCU_GATE(bus_iommu_clk, "bus-iommu", "apb0", 0x7bc, BIT(0), 0);

static const char *const dram_parents[] = { "pll-ddr0", "pll-audio1-div2",
                                            "pll-periph0-2x", "pll-periph0-800m"
                                          };
static SUNXI_CCU_MP_WITH_MUX_GATE(dram_clk, "dram-clk",
                                  dram_parents, 0x800,
                                  0, 2,         /* M */
                                  8, 2,         /* P */
                                  24, 2,        /* MUX */
                                  BIT(31), 0);

static SUNXI_CCU_GATE(mbus_dma_clk, "mbus-dma", "mbus",
                      0x804, BIT(0), 0);
static SUNXI_CCU_GATE(mbus_ve_clk, "mbus-ve", "mbus",
                      0x804, BIT(1), 0);
static SUNXI_CCU_GATE(mbus_ce_clk, "mbus-ce", "mbus",
                      0x804, BIT(2), 0);
static SUNXI_CCU_GATE(mbus_tvin_clk, "mbus-tvin", "mbus",
                      0x804, BIT(7), 0);
static SUNXI_CCU_GATE(mbus_csi_clk, "mbus-csi", "mbus",
                      0x804, BIT(8), 0);
static SUNXI_CCU_GATE(mbus_g2d_clk, "mbus-g2d", "mbus",
                      0x804, BIT(10), 0);

static SUNXI_CCU_GATE(bus_dram_clk, "bus-dram", "psi-ahb",
                      0x80c, BIT(0), CLK_IS_CRITICAL);

/* don't use postdiv for bsp kernel */
static const char *const mmc0_mmc1_parents[] = { "dcxo24M", "pll-periph0",
                                                 "pll-periph0-2x", "pll-audio1-div2"
                                               };
static SUNXI_CCU_MP_WITH_MUX_GATE(mmc0_clk, "mmc0", mmc0_mmc1_parents, 0x830,
                                  0, 4,     /* M */
                                  8, 2,     /* N->P */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  CLK_SET_RATE_NO_REPARENT);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_clk, "mmc1", mmc0_mmc1_parents, 0x834,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  CLK_SET_RATE_NO_REPARENT);

static const char *const mmc2_parents[] = { "dcxo24M", "pll-periph0",
                                            "pll-periph0-2x", "pll-periph0-800m",
                                            "pll-audio1-div2"
                                          };
static SUNXI_CCU_MP_WITH_MUX_GATE(mmc2_clk, "mmc2", mmc2_parents, 0x838,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  CLK_SET_RATE_NO_REPARENT);

static SUNXI_CCU_GATE(bus_mmc0_clk, "bus-mmc0", "psi-ahb", 0x84c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_mmc1_clk, "bus-mmc1", "psi-ahb", 0x84c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_mmc2_clk, "bus-mmc2", "psi-ahb", 0x84c, BIT(2), 0);

static SUNXI_CCU_GATE(bus_uart0_clk, "bus-uart0", "apb1", 0x90c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_uart1_clk, "bus-uart1", "apb1", 0x90c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_uart2_clk, "bus-uart2", "apb1", 0x90c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_uart3_clk, "bus-uart3", "apb1", 0x90c, BIT(3), 0);
static SUNXI_CCU_GATE(bus_uart4_clk, "bus-uart4", "apb1", 0x90c, BIT(4), 0);
static SUNXI_CCU_GATE(bus_uart5_clk, "bus-uart5", "apb1", 0x90c, BIT(5), 0);

static SUNXI_CCU_GATE(bus_i2c0_clk, "bus-i2c0", "apb1", 0x91c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2c1_clk, "bus-i2c1", "apb1", 0x91c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2c2_clk, "bus-i2c2", "apb1", 0x91c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_i2c3_clk, "bus-i2c3", "apb1", 0x91c, BIT(3), 0);

static SUNXI_CCU_GATE(bus_can0_clk, "bus-can0", "apb1", 0x92c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_can1_clk, "bus-can1", "apb1", 0x92c, BIT(1), 0);

static const char *const spi_parents[] = { "dcxo24M", "pll-periph0",
                                           "pll-periph0-2x", "pll-audio1-div2",
                                           "pll-audio1-div5"
                                         };
static SUNXI_CCU_MP_WITH_MUX_GATE(spi0_clk, "spi0", spi_parents, 0x940,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi1_clk, "spi1", spi_parents, 0x944,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_spi0_clk, "bus-spi0", "psi-ahb", 0x96c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_spi1_clk, "bus-spi1", "psi-ahb", 0x96c, BIT(1), 0);

static SUNXI_CCU_GATE(emac0_25m_clk, "emac0-25m", "pll-periph0", 0x970,
                      BIT(31) | BIT(30), 0);

static SUNXI_CCU_GATE(bus_emac0_clk, "bus-emac0", "psi-ahb", 0x97c, BIT(0), 0);

static const char *const ir_parents[] = { "dcxo24M", "pll-periph0" };
static SUNXI_CCU_MP_WITH_MUX_GATE(ir_tx_clk, "ir-tx", ir_parents, 0x9c0,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_ir_tx_clk, "bus-ir-tx", "apb0", 0x9cc, BIT(0), 0);

static SUNXI_CCU_GATE(bus_gpadc_clk, "bus-gpadc", "apb0", 0x9ec, BIT(0), 0);

static SUNXI_CCU_GATE(bus_ths_clk, "bus-ths", "apb0", 0x9fc, BIT(0), 0);

static const char *const i2s_spdif_tx_parents[] = { "pll-audio0", "pll-audio0-4x",
                                                    "pll-audio1-div2", "pll-audio1-div5"
                                                  };
static SUNXI_CCU_MP_WITH_MUX_GATE(i2s0_clk, "i2s0", i2s_spdif_tx_parents, 0xa10,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(i2s1_clk, "i2s1", i2s_spdif_tx_parents, 0xa14,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(i2s2_clk, "i2s2", i2s_spdif_tx_parents, 0xa18,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static const char *const i2s2_asrc_parents[] = { "pll-audio0-4x", "pll-periph0",
                                                 "pll-audio1-div2", "pll-audio1-div5"
                                               };

static SUNXI_CCU_MP_WITH_MUX_GATE(i2s2_asrc_clk, "i2s2-asrc", i2s2_asrc_parents, 0xa1c,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_i2s0_clk, "bus-i2s0", "apb1", 0xa20, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2s1_clk, "bus-i2s1", "apb1", 0xa20, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2s2_clk, "bus-i2s2", "apb1", 0xa20, BIT(2), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spdif_tx_clk, "spdif-tx", i2s_spdif_tx_parents, 0xa24,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static const char *const spdif_rx_parents[] = { "pll-periph0", "pll-audio1-div2",
                                                "pll-audio1-div5"
                                              };

static SUNXI_CCU_MP_WITH_MUX_GATE(spdif_rx_clk, "spdif-rx", spdif_rx_parents, 0xa28,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_spdif_clk, "bus-spdif", "apb0", 0xa2c, BIT(0), 0);

static const char *const dmic_codec_parents[] = { "pll-audio0", "pll-audio1-div2",
                                                  "pll-audio1-div5"
                                                };

static SUNXI_CCU_MP_WITH_MUX_GATE(dmic_clk, "dmic", dmic_codec_parents, 0xa40,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_dmic_clk, "bus-dmic", "apb0", 0xa4c, BIT(0), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(audio_codec_dac_clk, "audio-codec-dac", dmic_codec_parents, 0xa50,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(audio_codec_adc_clk, "audio-codec-adc", dmic_codec_parents, 0xa54,
                                  0, 5,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_audio_codec_clk, "bus-audio-codec", "apb0", 0xa5c, BIT(0), 0);

/*
 * There are OHCI 12M clock source selection bits for 2 USB 2.0 ports.
 * We will force them to 0 (12M divided from 48M).
 */
#define SUN8IW20_USB0_CLK_REG       0xa70
#define SUN8IW20_USB1_CLK_REG       0xa74

static SUNXI_CCU_GATE(usb_ohci0_clk, "usb-ohci0", "osc12M", 0xa70, BIT(31), 0);

static SUNXI_CCU_GATE(usb_ohci1_clk, "usb-ohci1", "osc12M", 0xa74, BIT(31), 0);

static SUNXI_CCU_GATE(bus_ohci0_clk, "bus-ohci0", "psi-ahb", 0xa8c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_ohci1_clk, "bus-ohci1", "psi-ahb", 0xa8c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_ehci0_clk, "bus-ehci0", "psi-ahb", 0xa8c, BIT(4), 0);
static SUNXI_CCU_GATE(bus_ehci1_clk, "bus-ehci1", "psi-ahb", 0xa8c, BIT(5), 0);
static SUNXI_CCU_GATE(bus_otg_clk, "bus-otg", "psi-ahb", 0xa8c, BIT(8), 0);

static SUNXI_CCU_GATE(bus_lradc_clk, "bus-lradc", "psi-ahb", 0xa9c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_dpss_top0_clk, "bus-dpss-top0", "psi-ahb",
                      0xabc, BIT(0), 0);

static SUNXI_CCU_GATE(hdmi_24m_clk, "hdmi-24m", "dcxo24M", 0xb04, BIT(31), 0);

static const char *const hdmi_cec_parents[] = { "osc32k", "hdmi-cec-32k" };
static SUNXI_CCU_MUX_WITH_GATE(hdmi_cec_clk, "hdmi-cec",
                               hdmi_cec_parents,
                               0xb10,
                               24, 1,           /* mux */
                               BIT(31) | BIT(30),   /* TODO:gate peri*/
                               0);

static SUNXI_CCU_GATE(bus_hdmi_clk, "bus-hdmi", "psi-ahb", 0xb1c, BIT(0), 0);

static const char *const mipi_dsi_parents[] = { "dcxo24M", "pll-periph0",
                                                "pll-video0-2x", "pll-video1-2x",
                                                "pll-audio1-div2"
                                              };
static SUNXI_CCU_M_WITH_MUX_GATE(mipi_dsi_clk, "mipi-dsi",
                                 mipi_dsi_parents,
                                 0xb24,
                                 0, 4,      /* M */
                                 24, 3,     /* mux */
                                 BIT(31),   /* gate */
                                 0);

static SUNXI_CCU_GATE(bus_mipi_dsi_clk, "bus-mipi-dsi", "psi-ahb",
                      0xb4c, BIT(0), 0);

static const char *const hdmi_tcon_tve_parents[] = { "pll-video0", "pll-video0-4x",
                                                     "pll-video1", "pll-video1-4x",
                                                     "pll-periph0-2x", "pll-audio1-div2"
                                                   };
static SUNXI_CCU_MP_WITH_MUX_GATE(tcon_lcd0_clk, "tcon-lcd0",
                                  hdmi_tcon_tve_parents, 0xb60,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_tcon_lcd0_clk, "bus-tcon-lcd0", "psi-ahb",
                      0xb7c, BIT(0), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(tcon_tv_clk, "tcon-tv",
                                  hdmi_tcon_tve_parents, 0xb80,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_tcon_tv_clk, "bus-tcon-tv", "psi-ahb",
                      0xb9c, BIT(0), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(tve_clk, "tve",
                                  hdmi_tcon_tve_parents, 0xbb0,
                                  0, 4,     /* M */
                                  8, 2,     /* N */
                                  24, 3,    /* mux */
                                  BIT(31),  /* gate */
                                  0);

static SUNXI_CCU_GATE(bus_tve_top_clk, "bus-tve-top", "psi-ahb",
                      0xbbc, BIT(0), 0);
static SUNXI_CCU_GATE(bus_tve_clk, "bus-tve", "psi-ahb",
                      0xbbc, BIT(1), 0);

static const char *const tvd_parents[] = { "dcxo24M", "pll-video0",
                                           "pll-video1", "pll-periph0"
                                         };
static SUNXI_CCU_M_WITH_MUX_GATE(tvd_clk, "tvd",
                                 tvd_parents,
                                 0xbc0,
                                 0, 5,      /* M */
                                 24, 3,     /* mux */
                                 BIT(31),   /* gate */
                                 0);

static SUNXI_CCU_GATE(bus_tvd_top_clk, "bus-tvd-top", "psi-ahb",
                      0xbdc, BIT(0), 0);
static SUNXI_CCU_GATE(bus_tvd_clk, "bus-tvd", "psi-ahb",
                      0xbdc, BIT(1), 0);

static const char *const ledc_parents[] = { "dcxo24M", "pll-periph0" };
static SUNXI_CCU_MP_WITH_MUX_GATE(ledc_clk, "ledc",
                                  ledc_parents, 0xbf0,
                                  0, 4,
                                  8, 2,
                                  24, 1,
                                  BIT(31),
                                  0);

static SUNXI_CCU_GATE(bus_ledc_clk, "bus-ledc", "psi-ahb",
                      0xbfc, BIT(0), 0);

static const char *const csi_top_parents[] = { "pll-periph0-2x", "pll-video0-2x",
                                               "pll-video1-2x"
                                             };
static SUNXI_CCU_M_WITH_MUX_GATE(csi_top_clk, "csi-top",
                                 csi_top_parents, 0xc04,
                                 0, 4,      /* M */
                                 24, 3,     /* mux */
                                 BIT(31),   /* gate */
                                 0);

static const char *const csi0_mclk_parents[] = { "dcxo24M", "pll-periph0",
                                                 "pll-video0", "pll-video1",
                                                 "pll-audio-div2", "pll-audio-div5"
                                               };
static SUNXI_CCU_M_WITH_MUX_GATE(csi0_mclk_clk, "csi0-mclk",
                                 csi0_mclk_parents, 0xc08,
                                 0, 5,      /* M */
                                 24, 3,     /* mux */
                                 BIT(31),   /* gate */
                                 0);

static SUNXI_CCU_GATE(bus_csi_clk, "bus-csi", "psi-ahb", 0xc1c, BIT(0), 0);

static const char *const tpadc_parents[] = { "dcxo24M", "pll-audio0" };
static SUNXI_CCU_MUX_WITH_GATE(tpadc_clk, "tpadc",
                               tpadc_parents, 0xc50,
                               24, 3,       /* mux */
                               BIT(31),      /* gate */
                               0);

static SUNXI_CCU_GATE(bus_tpadc_clk, "bus-tpadc", "apb0", 0xc5c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_tzma_clk, "bus-tzma", "apb0", 0xc6c, BIT(0), 0);

static const char *const dsp_parents[] = { "dcxo24M", "osc32k",
                                           "iosc", "pll-periph0-2x"
                                         };
static SUNXI_CCU_M_WITH_MUX_GATE(dsp_clk, "dsp", dsp_parents, 0xc70,
                                 0, 4,
                                 24, 3,
                                 BIT(31), 0);

static SUNXI_CCU_GATE(bus_dsp_cfg_clk, "bus-dsp-cfg", "psi-ahb", 0xc7c, BIT(1), 0);

static const char *const riscv_parents[] = { "dcxo24M", "osc32k",
                                             "iosc", "pll-periph0-800m",
                                             "pll-periph0", "pll-cpux",
                                             "pll-audio1-div2"
                                           };
static SUNXI_CCU_MUX(riscv_clk, "riscv",
                     riscv_parents, 0xd00, 24, 3, 0);

/* The riscv-axi clk needs to be divided by at least 2 */
static struct clk_div_table riscv_axi_table[] =
{
    { .val = 1, .div = 2 },
    { .val = 2, .div = 3 },
    { .val = 3, .div = 4 },
    { /* Sentinel */ },
};
static SUNXI_CCU_DIV_TABLE(riscv_axi_clk, "riscv-axi",
                           "riscv", 0xd00, 8, 2,
                           riscv_axi_table, 0);

static SUNXI_CCU_GATE(bus_riscv_cfg_clk, "bus-riscv-cfg", "psi-ahb",
                      0xd0c, BIT(0), 0);

/* Add the cpu fanout clk */
static SUNXI_CCU_GATE(fanout_24m_clk, "fanout-24m",
                      "dcxo24M", 0xf30, BIT(0), 0);
static SUNXI_CCU_GATE(fanout_12m_clk, "fanout-12m",
                      "osc12M", 0xf30, BIT(1), 0);
static SUNXI_CCU_GATE_WITH_PREDIV(fanout_16m_clk, "fanout-16m",
                                  "pll-periph0-2x", 0xf30,
                                  75,           /* prediv */
                                  BIT(2), 0);
static SUNXI_CCU_GATE_WITH_PREDIV(fanout_25m_clk, "fanout-25m",
                                  "pll-periph0", 0xf30,
                                  24,           /* prediv */
                                  BIT(3), 0);
static SUNXI_CCU_GATE_WITH_PREDIV(fanout_32k_clk, "fanout-32k",
                                  "pll-periph0-2x", 0xf30,
                                  36621,            /* prediv */
                                  BIT(4), 0);

static const char *const fanout_27m_parents[] = { "pll-video0", "pll-video1" };
static SUNXI_CCU_MP_WITH_MUX_GATE_NO_INDEX(fanout_27m_clk, "fanout-27m",
        fanout_27m_parents, 0xf34,
        8, 2,
        0, 5,
        24, 2,
        BIT(31), 0);

static SUNXI_CCU_M_WITH_GATE(fanout_pclk, "fanout-pclk",
                             "apb0", 0xf38, 0, 5, BIT(31), 0);

static const char *const fanout_parents[] = { "fanout-32k", "fanout-12m",
                                              "fanout-16m", "fanout-24m",
                                              "fanout-25m", "fanout-27m",
                                              "fanout-pclk"
                                            };
static SUNXI_CCU_MUX_WITH_GATE(fanout0_out_clk, "fanout0-out-clk",
                               fanout_parents, 0xf3c,
                               0, 3,
                               BIT(21), 0);
static SUNXI_CCU_MUX_WITH_GATE(fanout1_out_clk, "fanout1-out-clk",
                               fanout_parents, 0xf3c,
                               3, 3,
                               BIT(22), 0);
static SUNXI_CCU_MUX_WITH_GATE(fanout2_out_clk, "fanout2-out-clk",
                               fanout_parents, 0xf3c,
                               6, 3,
                               BIT(23), 0);

/* Fixed factor clocks */
static CLK_FIXED_FACTOR_FW_NAME(osc12M_clk, "osc12M", "dcxo24M", 2, 1, 0);

static CLK_FIXED_FACTOR_HW(pll_periph0_clk, "pll-periph0",
                           &pll_periph0_2x_clk.common.hw,
                           2, 1, 0);

/* For AHBS */
static CLK_FIXED_FACTOR_HW(pll_periph0_div3_clk, "pll-periph0-div3",
                           &pll_periph0_2x_clk.common.hw,
                           6, 1, 0);

static CLK_FIXED_FACTOR_HW(hdmi_cec_32k_clk, "hdmi-cec-32k",
                           &pll_periph0_2x_clk.common.hw,
                           36621, 1, 0);

static CLK_FIXED_FACTOR_HW(mbus_clk, "mbus",
                           &pll_ddr0_clk.common.hw,
                           4, 1, 0);

static const struct clk_hw *pll_video0_parents[] =
{
    &pll_video0_clk.common.hw
};
static CLK_FIXED_FACTOR_HWS(pll_video0_4x_clk, "pll-video0-4x",
                            pll_video0_parents,
                            1, 4, CLK_SET_RATE_PARENT);
static CLK_FIXED_FACTOR_HWS(pll_video0_2x_clk, "pll-video0-2x",
                            pll_video0_parents,
                            1, 2, CLK_SET_RATE_PARENT);

static const struct clk_hw *pll_video1_parents[] =
{
    &pll_video1_clk.common.hw
};
static CLK_FIXED_FACTOR_HWS(pll_video1_4x_clk, "pll-video1-4x",
                            pll_video1_parents,
                            1, 4, CLK_SET_RATE_PARENT);
static CLK_FIXED_FACTOR_HWS(pll_video1_2x_clk, "pll-video1-2x",
                            pll_video1_parents,
                            1, 2, CLK_SET_RATE_PARENT);

static const struct clk_hw *pll_audio0_parents[] =
{
    &pll_audio0_4x_clk.common.hw
};
static CLK_FIXED_FACTOR_HWS(pll_audio0_clk, "pll-audio0",
                            pll_audio0_parents,
                            4, 1, CLK_SET_RATE_PARENT);
static CLK_FIXED_FACTOR_HWS(pll_audio0_2x_clk, "pll-audio0-2x",
                            pll_audio0_parents,
                            2, 1, CLK_SET_RATE_PARENT);
/* ccu_des_end */

static struct ccu_common *sun8iw20_ccu_clks[] =
{
    &pll_cpux_clk.common,
    &pll_ddr0_clk.common,
    &pll_periph0_parent_clk.common,
    &pll_periph0_2x_clk.common,
    &pll_periph0_800m_clk.common,
    &pll_video0_clk.common,
    &pll_video1_clk.common,
    &pll_ve_clk.common,
    &pll_audio0_4x_clk.common,
    &pll_audio1_clk.common,
    &pll_audio1_div2_clk.common,
    &pll_audio1_div5_clk.common,
    &pll_cpux_div.common,
    &cpux_clk.common,
    &axi_clk.common,
    &apb_clk.common,
    &psi_ahb_clk.common,
    &apb0_clk.common,
    &apb1_clk.common,
    &de0_clk.common,
    &bus_de0_clk.common,
    &di_clk.common,
    &bus_di_clk.common,
    &g2d_clk.common,
    &bus_g2d_clk.common,
    &ce_clk.common,
    &bus_ce_clk.common,
    &ve_clk.common,
    &bus_ve_clk.common,
    &bus_dma_clk.common,
    &bus_msgbox0_clk.common,
    &bus_msgbox1_clk.common,
    &bus_msgbox2_clk.common,
    &bus_spinlock_clk.common,
    &bus_hstimer_clk.common,
    &avs_clk.common,
    &bus_dbg_clk.common,
    &bus_pwm_clk.common,
    &bus_iommu_clk.common,
    &dram_clk.common,
    &mbus_dma_clk.common,
    &mbus_ve_clk.common,
    &mbus_ce_clk.common,
    &mbus_tvin_clk.common,
    &mbus_csi_clk.common,
    &mbus_g2d_clk.common,
    &bus_dram_clk.common,
    &mmc0_clk.common,
    &mmc1_clk.common,
    &mmc2_clk.common,
    &bus_mmc0_clk.common,
    &bus_mmc1_clk.common,
    &bus_mmc2_clk.common,
    &bus_uart0_clk.common,
    &bus_uart1_clk.common,
    &bus_uart2_clk.common,
    &bus_uart3_clk.common,
    &bus_uart4_clk.common,
    &bus_uart5_clk.common,
    &bus_i2c0_clk.common,
    &bus_i2c1_clk.common,
    &bus_i2c2_clk.common,
    &bus_i2c3_clk.common,
    &bus_can0_clk.common,
    &bus_can1_clk.common,
    &spi0_clk.common,
    &spi1_clk.common,
    &bus_spi0_clk.common,
    &bus_spi1_clk.common,
    &emac0_25m_clk.common,
    &bus_emac0_clk.common,
    &ir_tx_clk.common,
    &bus_ir_tx_clk.common,
    &bus_gpadc_clk.common,
    &bus_ths_clk.common,
    &i2s0_clk.common,
    &i2s1_clk.common,
    &i2s2_clk.common,
    &i2s2_asrc_clk.common,
    &bus_i2s0_clk.common,
    &bus_i2s1_clk.common,
    &bus_i2s2_clk.common,
    &spdif_tx_clk.common,
    &spdif_rx_clk.common,
    &bus_spdif_clk.common,
    &dmic_clk.common,
    &bus_dmic_clk.common,
    &audio_codec_dac_clk.common,
    &audio_codec_adc_clk.common,
    &bus_audio_codec_clk.common,
    &usb_ohci0_clk.common,
    &usb_ohci1_clk.common,
    &bus_ohci0_clk.common,
    &bus_ohci1_clk.common,
    &bus_ehci0_clk.common,
    &bus_ehci1_clk.common,
    &bus_otg_clk.common,
    &bus_lradc_clk.common,
    &bus_dpss_top0_clk.common,
    &hdmi_24m_clk.common,
    &hdmi_cec_clk.common,
    &bus_hdmi_clk.common,
    &mipi_dsi_clk.common,
    &bus_mipi_dsi_clk.common,
    &tcon_lcd0_clk.common,
    &bus_tcon_lcd0_clk.common,
    &tcon_tv_clk.common,
    &bus_tcon_tv_clk.common,
    &tve_clk.common,
    &bus_tve_clk.common,
    &bus_tve_top_clk.common,
    &tvd_clk.common,
    &bus_tvd_clk.common,
    &ledc_clk.common,
    &bus_ledc_clk.common,
    &bus_tvd_top_clk.common,
    &csi_top_clk.common,
    &csi0_mclk_clk.common,
    &bus_csi_clk.common,
    &tpadc_clk.common,
    &bus_tpadc_clk.common,
    &bus_tzma_clk.common,
    &dsp_clk.common,
    &bus_dsp_cfg_clk.common,
    &riscv_clk.common,
    &riscv_axi_clk.common,
    &bus_riscv_cfg_clk.common,
    &fanout_24m_clk.common,
    &fanout_12m_clk.common,
    &fanout_16m_clk.common,
    &fanout_25m_clk.common,
    &fanout_32k_clk.common,
    &fanout_27m_clk.common,
    &fanout_pclk.common,
    &fanout0_out_clk.common,
    &fanout1_out_clk.common,
    &fanout2_out_clk.common,
};

/* ccu_def_start */
static struct clk_hw_onecell_data sun8iw20_hw_clks =
{
    .hws    = {
        [CLK_OSC12M]        = &osc12M_clk.hw,
        [CLK_PLL_CPUX]      = &pll_cpux_clk.common.hw,
        [CLK_PLL_DDR0]      = &pll_ddr0_clk.common.hw,
        [CLK_PLL_PERIPH0_PARENT] = &pll_periph0_parent_clk.common.hw,
        [CLK_PLL_PERIPH0_2X]    = &pll_periph0_2x_clk.common.hw,
        [CLK_PLL_PERIPH0]   = &pll_periph0_clk.hw,
        [CLK_PLL_PERIPH0_800M]  = &pll_periph0_800m_clk.common.hw,
        [CLK_PLL_PERIPH0_DIV3]  = &pll_periph0_div3_clk.hw,
        [CLK_PLL_VIDEO0]    = &pll_video0_clk.common.hw,
        [CLK_PLL_VIDEO0_2X] = &pll_video0_2x_clk.hw,
        [CLK_PLL_VIDEO0_4X] = &pll_video0_4x_clk.hw,
        [CLK_PLL_VIDEO1]    = &pll_video1_clk.common.hw,
        [CLK_PLL_VIDEO1_2X] = &pll_video1_2x_clk.hw,
        [CLK_PLL_VIDEO1_4X] = &pll_video1_4x_clk.hw,
        [CLK_PLL_VE]        = &pll_ve_clk.common.hw,
        [CLK_PLL_AUDIO0]    = &pll_audio0_clk.hw,
        [CLK_PLL_AUDIO0_2X] = &pll_audio0_2x_clk.hw,
        [CLK_PLL_AUDIO0_4X] = &pll_audio0_4x_clk.common.hw,
        [CLK_PLL_AUDIO1]    = &pll_audio1_clk.common.hw,
        [CLK_PLL_AUDIO1_DIV2]   = &pll_audio1_div2_clk.common.hw,
        [CLK_PLL_AUDIO1_DIV5]   = &pll_audio1_div5_clk.common.hw,
        [CLK_PLL_CPUX_DIV]  = &pll_cpux_div.common.hw,
        [CLK_CPUX]      = &cpux_clk.common.hw,
        [CLK_AXI]       = &axi_clk.common.hw,
        [CLK_APB]       = &apb_clk.common.hw,
        [CLK_PSI_AHB]       = &psi_ahb_clk.common.hw,
        [CLK_APB0]      = &apb0_clk.common.hw,
        [CLK_APB1]      = &apb1_clk.common.hw,
        [CLK_MBUS]      = &mbus_clk.hw,
        [CLK_DE0]       = &de0_clk.common.hw,
        [CLK_BUS_DE0]       = &bus_de0_clk.common.hw,
        [CLK_DI]        = &di_clk.common.hw,
        [CLK_BUS_DI]        = &bus_di_clk.common.hw,
        [CLK_G2D]       = &g2d_clk.common.hw,
        [CLK_BUS_G2D]       = &bus_g2d_clk.common.hw,
        [CLK_CE]        = &ce_clk.common.hw,
        [CLK_BUS_CE]        = &bus_ce_clk.common.hw,
        [CLK_VE]        = &ve_clk.common.hw,
        [CLK_BUS_VE]        = &bus_ve_clk.common.hw,
        [CLK_BUS_DMA]       = &bus_dma_clk.common.hw,
        [CLK_BUS_MSGBOX0]   = &bus_msgbox0_clk.common.hw,
        [CLK_BUS_MSGBOX1]   = &bus_msgbox1_clk.common.hw,
        [CLK_BUS_MSGBOX2]   = &bus_msgbox2_clk.common.hw,
        [CLK_BUS_SPINLOCK]  = &bus_spinlock_clk.common.hw,
        [CLK_BUS_HSTIMER]   = &bus_hstimer_clk.common.hw,
        [CLK_AVS]       = &avs_clk.common.hw,
        [CLK_BUS_DBG]       = &bus_dbg_clk.common.hw,
        [CLK_BUS_PWM]       = &bus_pwm_clk.common.hw,
        [CLK_BUS_IOMMU]     = &bus_iommu_clk.common.hw,
        [CLK_DRAM]      = &dram_clk.common.hw,
        [CLK_MBUS_DMA]      = &mbus_dma_clk.common.hw,
        [CLK_MBUS_VE]       = &mbus_ve_clk.common.hw,
        [CLK_MBUS_CE]       = &mbus_ce_clk.common.hw,
        [CLK_MBUS_TVIN]     = &mbus_tvin_clk.common.hw,
        [CLK_MBUS_CSI]      = &mbus_csi_clk.common.hw,
        [CLK_MBUS_G2D]      = &mbus_g2d_clk.common.hw,
        [CLK_BUS_DRAM]      = &bus_dram_clk.common.hw,
        [CLK_MMC0]      = &mmc0_clk.common.hw,
        [CLK_MMC1]      = &mmc1_clk.common.hw,
        [CLK_MMC2]      = &mmc2_clk.common.hw,
        [CLK_BUS_MMC0]      = &bus_mmc0_clk.common.hw,
        [CLK_BUS_MMC1]      = &bus_mmc1_clk.common.hw,
        [CLK_BUS_MMC2]      = &bus_mmc2_clk.common.hw,
        [CLK_BUS_UART0]     = &bus_uart0_clk.common.hw,
        [CLK_BUS_UART1]     = &bus_uart1_clk.common.hw,
        [CLK_BUS_UART2]     = &bus_uart2_clk.common.hw,
        [CLK_BUS_UART3]     = &bus_uart3_clk.common.hw,
        [CLK_BUS_UART4]     = &bus_uart4_clk.common.hw,
        [CLK_BUS_UART5]     = &bus_uart5_clk.common.hw,
        [CLK_BUS_I2C0]      = &bus_i2c0_clk.common.hw,
        [CLK_BUS_I2C1]      = &bus_i2c1_clk.common.hw,
        [CLK_BUS_I2C2]      = &bus_i2c2_clk.common.hw,
        [CLK_BUS_I2C3]      = &bus_i2c3_clk.common.hw,
        [CLK_BUS_CAN0]      = &bus_can0_clk.common.hw,
        [CLK_BUS_CAN1]      = &bus_can1_clk.common.hw,
        [CLK_SPI0]      = &spi0_clk.common.hw,
        [CLK_SPI1]      = &spi1_clk.common.hw,
        [CLK_BUS_SPI0]      = &bus_spi0_clk.common.hw,
        [CLK_BUS_SPI1]      = &bus_spi1_clk.common.hw,
        [CLK_EMAC0_25M]     = &emac0_25m_clk.common.hw,
        [CLK_BUS_EMAC0]     = &bus_emac0_clk.common.hw,
        [CLK_IR_TX]     = &ir_tx_clk.common.hw,
        [CLK_BUS_IR_TX]     = &bus_ir_tx_clk.common.hw,
        [CLK_BUS_GPADC]     = &bus_gpadc_clk.common.hw,
        [CLK_BUS_THS]       = &bus_ths_clk.common.hw,
        [CLK_I2S0]      = &i2s0_clk.common.hw,
        [CLK_I2S1]      = &i2s1_clk.common.hw,
        [CLK_I2S2]      = &i2s2_clk.common.hw,
        [CLK_I2S2_ASRC]     = &i2s2_asrc_clk.common.hw,
        [CLK_BUS_I2S0]      = &bus_i2s0_clk.common.hw,
        [CLK_BUS_I2S1]      = &bus_i2s1_clk.common.hw,
        [CLK_BUS_I2S2]      = &bus_i2s2_clk.common.hw,
        [CLK_SPDIF_TX]      = &spdif_tx_clk.common.hw,
        [CLK_SPDIF_RX]      = &spdif_rx_clk.common.hw,
        [CLK_BUS_SPDIF]     = &bus_spdif_clk.common.hw,
        [CLK_DMIC]      = &dmic_clk.common.hw,
        [CLK_BUS_DMIC]      = &bus_dmic_clk.common.hw,
        [CLK_AUDIO_DAC]     = &audio_codec_dac_clk.common.hw,
        [CLK_AUDIO_ADC]     = &audio_codec_adc_clk.common.hw,
        [CLK_BUS_AUDIO_CODEC]   = &bus_audio_codec_clk.common.hw,
        [CLK_USB_OHCI0]     = &usb_ohci0_clk.common.hw,
        [CLK_USB_OHCI1]     = &usb_ohci1_clk.common.hw,
        [CLK_BUS_OHCI0]     = &bus_ohci0_clk.common.hw,
        [CLK_BUS_OHCI1]     = &bus_ohci1_clk.common.hw,
        [CLK_BUS_EHCI0]     = &bus_ehci0_clk.common.hw,
        [CLK_BUS_EHCI1]     = &bus_ehci1_clk.common.hw,
        [CLK_BUS_OTG]       = &bus_otg_clk.common.hw,
        [CLK_BUS_LRADC]     = &bus_lradc_clk.common.hw,
        [CLK_BUS_DPSS_TOP0] = &bus_dpss_top0_clk.common.hw,
        [CLK_HDMI_24M]      = &hdmi_24m_clk.common.hw,
        [CLK_HDMI_CEC]      = &hdmi_cec_clk.common.hw,
        [CLK_HDMI_CEC_32K]  = &hdmi_cec_32k_clk.hw,
        [CLK_BUS_HDMI]      = &bus_hdmi_clk.common.hw,
        [CLK_MIPI_DSI]      = &mipi_dsi_clk.common.hw,
        [CLK_BUS_MIPI_DSI]  = &bus_mipi_dsi_clk.common.hw,
        [CLK_TCON_LCD0]     = &tcon_lcd0_clk.common.hw,
        [CLK_BUS_TCON_LCD0] = &bus_tcon_lcd0_clk.common.hw,
        [CLK_TCON_TV]       = &tcon_tv_clk.common.hw,
        [CLK_BUS_TCON_TV]   = &bus_tcon_tv_clk.common.hw,
        [CLK_TVE]       = &tve_clk.common.hw,
        [CLK_BUS_TVE]       = &bus_tve_clk.common.hw,
        [CLK_BUS_TVE_TOP]   = &bus_tve_top_clk.common.hw,
        [CLK_TVD]       = &tvd_clk.common.hw,
        [CLK_BUS_TVD]       = &bus_tvd_clk.common.hw,
        [CLK_BUS_TVD_TOP]   = &bus_tvd_top_clk.common.hw,
        [CLK_LEDC]      = &ledc_clk.common.hw,
        [CLK_BUS_LEDC]      = &bus_ledc_clk.common.hw,
        [CLK_CSI_TOP]       = &csi_top_clk.common.hw,
        [CLK_CSI0_MCLK]     = &csi0_mclk_clk.common.hw,
        [CLK_BUS_CSI]       = &bus_csi_clk.common.hw,
        [CLK_TPADC]     = &tpadc_clk.common.hw,
        [CLK_BUS_TPADC]     = &bus_tpadc_clk.common.hw,
        [CLK_BUS_TZMA]      = &bus_tzma_clk.common.hw,
        [CLK_DSP]       = &dsp_clk.common.hw,
        [CLK_BUS_DSP_CFG]   = &bus_dsp_cfg_clk.common.hw,
        [CLK_RISCV]     = &riscv_clk.common.hw,
        [CLK_RISCV_AXI]     = &riscv_axi_clk.common.hw,
        [CLK_BUS_RISCV_CFG] = &bus_riscv_cfg_clk.common.hw,
        [CLK_FANOUT_24M]    = &fanout_24m_clk.common.hw,
        [CLK_FANOUT_12M]    = &fanout_12m_clk.common.hw,
        [CLK_FANOUT_16M]    = &fanout_16m_clk.common.hw,
        [CLK_FANOUT_25M]    = &fanout_25m_clk.common.hw,
        [CLK_FANOUT_32K]    = &fanout_32k_clk.common.hw,
        [CLK_FANOUT_27M]    = &fanout_27m_clk.common.hw,
        [CLK_FANOUT_PCLK]   = &fanout_pclk.common.hw,
        [CLK_FANOUT0_OUT]   = &fanout0_out_clk.common.hw,
        [CLK_FANOUT1_OUT]   = &fanout1_out_clk.common.hw,
        [CLK_FANOUT2_OUT]   = &fanout2_out_clk.common.hw,
    },
    .num = CLK_NUMBER,
};
/* ccu_def_end */

/* rst_def_start */
static struct ccu_reset_map sun8iw20_ccu_resets[] =
{
    [RST_MBUS]      = { 0x540, BIT(30) },

    [RST_BUS_DE0]       = { 0x60c, BIT(16) },
    [RST_BUS_DI]        = { 0x62c, BIT(16) },
    [RST_BUS_G2D]       = { 0x63c, BIT(16) },
    [RST_BUS_CE]        = { 0x68c, BIT(16) },
    [RST_BUS_VE]        = { 0x69c, BIT(16) },
    [RST_BUS_DMA]       = { 0x70c, BIT(16) },
    [RST_BUS_MSGBOX0]   = { 0x71c, BIT(16) },
    [RST_BUS_MSGBOX1]   = { 0x71c, BIT(17) },
    [RST_BUS_MSGBOX2]   = { 0x71c, BIT(18) },
    [RST_BUS_SPINLOCK]  = { 0x72c, BIT(16) },
    [RST_BUS_HSTIMER]   = { 0x73c, BIT(16) },
    [RST_BUS_DBG]       = { 0x78c, BIT(16) },
    [RST_BUS_PWM]       = { 0x7ac, BIT(16) },
    [RST_BUS_DRAM]      = { 0x80c, BIT(16) },
    [RST_BUS_MMC0]      = { 0x84c, BIT(16) },
    [RST_BUS_MMC1]      = { 0x84c, BIT(17) },
    [RST_BUS_MMC2]      = { 0x84c, BIT(18) },
    [RST_BUS_UART0]     = { 0x90c, BIT(16) },
    [RST_BUS_UART1]     = { 0x90c, BIT(17) },
    [RST_BUS_UART2]     = { 0x90c, BIT(18) },
    [RST_BUS_UART3]     = { 0x90c, BIT(19) },
    [RST_BUS_UART4]     = { 0x90c, BIT(20) },
    [RST_BUS_UART5]     = { 0x90c, BIT(21) },
    [RST_BUS_I2C0]      = { 0x91c, BIT(16) },
    [RST_BUS_I2C1]      = { 0x91c, BIT(17) },
    [RST_BUS_I2C2]      = { 0x91c, BIT(18) },
    [RST_BUS_I2C3]      = { 0x91c, BIT(19) },
    [RST_BUS_CAN0]      = { 0x92c, BIT(16) },
    [RST_BUS_CAN1]      = { 0x92c, BIT(17) },
    [RST_BUS_SPI0]      = { 0x96c, BIT(16) },
    [RST_BUS_SPI1]      = { 0x96c, BIT(17) },
    [RST_BUS_EMAC0]     = { 0x97c, BIT(16) },
    [RST_BUS_IR_TX]     = { 0x9cc, BIT(16) },
    [RST_BUS_GPADC]     = { 0x9ec, BIT(16) },
    [RST_BUS_THS]       = { 0x9fc, BIT(16) },
    [RST_BUS_I2S0]      = { 0xa20, BIT(16) },
    [RST_BUS_I2S1]      = { 0xa20, BIT(17) },
    [RST_BUS_I2S2]      = { 0xa20, BIT(18) },
    [RST_BUS_SPDIF]     = { 0xa2c, BIT(16) },
    [RST_BUS_DMIC]      = { 0xa4c, BIT(16) },
    [RST_BUS_AUDIO_CODEC]   = { 0xa5c, BIT(16) },

    [RST_USB_PHY0]      = { 0xa70, BIT(30) },
    [RST_USB_PHY1]      = { 0xa74, BIT(30) },

    [RST_BUS_OHCI0]     = { 0xa8c, BIT(16) },
    [RST_BUS_OHCI1]     = { 0xa8c, BIT(17) },
    [RST_BUS_EHCI0]     = { 0xa8c, BIT(20) },
    [RST_BUS_EHCI1]     = { 0xa8c, BIT(21) },
    [RST_BUS_OTG]       = { 0xa8c, BIT(24) },

    [RST_BUS_LRADC]     = { 0xa9c, BIT(16) },
    [RST_BUS_DPSS_TOP0] = { 0xabc, BIT(16) },
    [RST_BUS_HDMI_SUB]  = { 0xb1c, BIT(17) },
    [RST_BUS_HDMI_MAIN] = { 0xb1c, BIT(16) },
    [RST_BUS_MIPI_DSI]  = { 0xb4c, BIT(16) },
    [RST_BUS_TCON_LCD0] = { 0xb7c, BIT(16) },
    [RST_BUS_TCON_TV]   = { 0xb9c, BIT(16) },
    [RST_BUS_LVDS0]     = { 0xbac, BIT(16) },
    [RST_BUS_TVE]       = { 0xbbc, BIT(17) },
    [RST_BUS_TVE_TOP]   = { 0xbbc, BIT(16) },
    [RST_BUS_TVD]       = { 0xbdc, BIT(17) },
    [RST_BUS_TVD_TOP]   = { 0xbdc, BIT(16) },
    [RST_BUS_LEDC]      = { 0xbfc, BIT(16) },
    [RST_BUS_CSI]       = { 0xc1c, BIT(16) },
    [RST_BUS_TPADC]     = { 0xc5c, BIT(16) },
    [RST_BUS_DSP]       = { 0xc7c, BIT(16) },
    [RST_BUS_DSP_CFG]   = { 0xc7c, BIT(17) },
    [RST_BUS_DSP_DBG]   = { 0xc7c, BIT(18) },
    [RST_BUS_RISCV_CFG] = { 0xd0c, BIT(16) },
    /* TODO: RST_RISCV_SOFT */
};
/* rst_def_end */

static const struct sunxi_ccu_desc sun8iw20_ccu_desc =
{
    .ccu_clks   = sun8iw20_ccu_clks,
    .num_ccu_clks   = ARRAY_SIZE(sun8iw20_ccu_clks),

    .hw_clks    = &sun8iw20_hw_clks,
    .clk_type   = HAL_SUNXI_CCU,

    .resets     = sun8iw20_ccu_resets,
    .reset_type = HAL_SUNXI_RESET,
    .num_resets = ARRAY_SIZE(sun8iw20_ccu_resets),
};

static const u32 pll_regs[] =
{
    SUN8IW20_PLL_CPUX_REG,
    SUN8IW20_PLL_DDR0_REG,
    SUN8IW20_PLL_PERIPH0_REG,
    SUN8IW20_PLL_VIDEO0_REG,
    SUN8IW20_PLL_VIDEO1_REG,
    SUN8IW20_PLL_VE_REG,
    SUN8IW20_PLL_AUDIO0_REG,
    SUN8IW20_PLL_AUDIO1_REG,
};

static const u32 pll_video_regs[] =
{
    SUN8IW20_PLL_VIDEO0_REG,
    SUN8IW20_PLL_VIDEO1_REG,
};

static const u32 usb2_clk_regs[] =
{
    SUN8IW20_USB0_CLK_REG,
    SUN8IW20_USB1_CLK_REG,
};

int sunxi_ccu_init(void)
{
    unsigned long reg = (unsigned long)SUNXI_CCU_BASE;
    u32 val;
    int i;

    /* Enable the lock bits on all Plls */
    for (i = 0; i < ARRAY_SIZE(pll_regs); i++)
    {
        val = readl(reg + pll_regs[i]);
        val |= BIT(29);
        writel(val, reg + pll_regs[i]);
    }

    /*
     * Force the output divider of video PLLs to 0.
     *
     * See the comment before pll-video0 definition for the reason.
     */
    for (i = 0; i < ARRAY_SIZE(pll_video_regs); i++)
    {
        val = readl(reg + pll_video_regs[i]);
        val &= ~BIT(0);
        writel(val, reg + pll_video_regs[i]);
    }

    /* Enforce m1 = 0, m0 = 1 for Audio0 PLL */
    val = readl(reg + SUN8IW20_PLL_AUDIO0_REG);
    val &= ~BIT(1);
    val |= BIT(0);

    writel(val, reg + SUN8IW20_PLL_AUDIO0_REG);

    /* TODO: config PLL_AUDIO1 here */

    /*
     * Force OHCI 12M clock sources to 00 (12MHz divided from 48MHz)
     *
     * This clock mux is still mysterious, and the code just enforces
     * it to have a valid clock parent.
     */
    for (i = 0; i < ARRAY_SIZE(usb2_clk_regs); i++)
    {
        val = readl(reg + usb2_clk_regs[i]);
        val &= ~GENMASK(25, 24);
        writel(val, reg + usb2_clk_regs[i]);
    }

    return ccu_common_init(reg, &sun8iw20_ccu_desc);
}
