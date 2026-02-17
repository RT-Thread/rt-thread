/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-composite.h"
#include "clk-rk-cpu.h"
#include "clk-rk-divider.h"
#include "clk-rk-factor.h"
#include "clk-rk-fraction-divider.h"
#include "clk-rk-gate.h"
#include "clk-rk.h"
#include "clk-rk-half-divider.h"
#include "clk-rk-mmc-phase.h"
#include "clk-rk-muxgrf.h"
#include "clk-rk-mux.h"
#include "clk-rk-pll.h"

#define DBG_TAG "clk.rk3568"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dt-bindings/clock/rk3568-cru.h>

#define RK3568_PLL_CON(x)               ((x) * 0x4)
#define RK3568_MODE_CON0                0xc0
#define RK3568_MISC_CON0                0xc4
#define RK3568_MISC_CON1                0xc8
#define RK3568_MISC_CON2                0xcc
#define RK3568_GLB_CNT_TH               0xd0
#define RK3568_GLB_SRST_FST             0xd4
#define RK3568_GLB_SRST_SND             0xd8
#define RK3568_GLB_RST_CON              0xdc
#define RK3568_GLB_RST_ST               0xe0
#define RK3568_CLKSEL_CON(x)            ((x) * 0x4 + 0x100)
#define RK3568_CLKGATE_CON(x)           ((x) * 0x4 + 0x300)
#define RK3568_SOFTRST_CON(x)           ((x) * 0x4 + 0x400)
#define RK3568_SDMMC0_CON0              0x580
#define RK3568_SDMMC0_CON1              0x584
#define RK3568_SDMMC1_CON0              0x588
#define RK3568_SDMMC1_CON1              0x58c
#define RK3568_SDMMC2_CON0              0x590
#define RK3568_SDMMC2_CON1              0x594
#define RK3568_EMMC_CON0                0x598
#define RK3568_EMMC_CON1                0x59c

#define RK3568_PMU_PLL_CON(x)           ((x) * 0x4)
#define RK3568_PMU_MODE_CON0            0x80
#define RK3568_PMU_CLKSEL_CON(x)        ((x) * 0x4 + 0x100)
#define RK3568_PMU_CLKGATE_CON(x)       ((x) * 0x4 + 0x180)
#define RK3568_PMU_SOFTRST_CON(x)       ((x) * 0x4 + 0x200)

#define RK3568_GRF_SOC_CON1             0x504
#define RK3568_GRF_SOC_CON2             0x508
#define RK3568_GRF_SOC_STATUS0          0x580
#define RK3568_PMU_GRF_SOC_CON0         0x100

#define RK3568_FRAC_MAX_PRATE           1000000000
#define RK3568_SPDIF_FRAC_MAX_PRATE     600000000
#define RK3568_UART_FRAC_MAX_PRATE      600000000
#define RK3568_DCLK_PARENT_MAX_PRATE    600000000

#define RK3568_DIV_ATCLK_CORE_MASK      0x1f
#define RK3568_DIV_ATCLK_CORE_SHIFT     0
#define RK3568_DIV_GICCLK_CORE_MASK     0x1f
#define RK3568_DIV_GICCLK_CORE_SHIFT    8
#define RK3568_DIV_PCLK_CORE_MASK       0x1f
#define RK3568_DIV_PCLK_CORE_SHIFT      0
#define RK3568_DIV_PERIPHCLK_CORE_MASK  0x1f
#define RK3568_DIV_PERIPHCLK_CORE_SHIFT 8
#define RK3568_DIV_ACLK_CORE_MASK       0x1f
#define RK3568_DIV_ACLK_CORE_SHIFT      8

#define RK3568_DIV_SCLK_CORE_MASK       0xf
#define RK3568_DIV_SCLK_CORE_SHIFT      0
#define RK3568_MUX_SCLK_CORE_MASK       0x3
#define RK3568_MUX_SCLK_CORE_SHIFT      8
#define RK3568_MUX_SCLK_CORE_NPLL_MASK  0x1
#define RK3568_MUX_SCLK_CORE_NPLL_SHIFT 15
#define RK3568_MUX_CLK_CORE_APLL_MASK   0x1
#define RK3568_MUX_CLK_CORE_APLL_SHIFT  7
#define RK3568_MUX_CLK_PVTPLL_MASK      0x1
#define RK3568_MUX_CLK_PVTPLL_SHIFT     15

struct clk_rk3568_cru
{
    struct rt_clk_node clk_parent;
    struct rt_reset_controller rstc_parent;

    struct rockchip_clk_provider provider;
};

static struct rockchip_pll_rate_table rk3568_pll_rates[] =
{
    /* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
    RK3036_PLL_RATE(2208000000, 1, 92, 1, 1, 1, 0),
    RK3036_PLL_RATE(2184000000, 1, 91, 1, 1, 1, 0),
    RK3036_PLL_RATE(2160000000, 1, 90, 1, 1, 1, 0),
    RK3036_PLL_RATE(2088000000, 1, 87, 1, 1, 1, 0),
    RK3036_PLL_RATE(2064000000, 1, 86, 1, 1, 1, 0),
    RK3036_PLL_RATE(2040000000, 1, 85, 1, 1, 1, 0),
    RK3036_PLL_RATE(2016000000, 1, 84, 1, 1, 1, 0),
    RK3036_PLL_RATE(1992000000, 1, 83, 1, 1, 1, 0),
    RK3036_PLL_RATE(1920000000, 1, 80, 1, 1, 1, 0),
    RK3036_PLL_RATE(1896000000, 1, 79, 1, 1, 1, 0),
    RK3036_PLL_RATE(1800000000, 1, 75, 1, 1, 1, 0),
    RK3036_PLL_RATE(1704000000, 1, 71, 1, 1, 1, 0),
    RK3036_PLL_RATE(1608000000, 1, 67, 1, 1, 1, 0),
    RK3036_PLL_RATE(1600000000, 3, 200, 1, 1, 1, 0),
    RK3036_PLL_RATE(1584000000, 1, 132, 2, 1, 1, 0),
    RK3036_PLL_RATE(1560000000, 1, 130, 2, 1, 1, 0),
    RK3036_PLL_RATE(1536000000, 1, 128, 2, 1, 1, 0),
    RK3036_PLL_RATE(1512000000, 1, 126, 2, 1, 1, 0),
    RK3036_PLL_RATE(1488000000, 1, 124, 2, 1, 1, 0),
    RK3036_PLL_RATE(1464000000, 1, 122, 2, 1, 1, 0),
    RK3036_PLL_RATE(1440000000, 1, 120, 2, 1, 1, 0),
    RK3036_PLL_RATE(1416000000, 1, 118, 2, 1, 1, 0),
    RK3036_PLL_RATE(1400000000, 3, 350, 2, 1, 1, 0),
    RK3036_PLL_RATE(1392000000, 1, 116, 2, 1, 1, 0),
    RK3036_PLL_RATE(1368000000, 1, 114, 2, 1, 1, 0),
    RK3036_PLL_RATE(1344000000, 1, 112, 2, 1, 1, 0),
    RK3036_PLL_RATE(1320000000, 1, 110, 2, 1, 1, 0),
    RK3036_PLL_RATE(1296000000, 1, 108, 2, 1, 1, 0),
    RK3036_PLL_RATE(1272000000, 1, 106, 2, 1, 1, 0),
    RK3036_PLL_RATE(1248000000, 1, 104, 2, 1, 1, 0),
    RK3036_PLL_RATE(1200000000, 1, 100, 2, 1, 1, 0),
    RK3036_PLL_RATE(1188000000, 1, 99, 2, 1, 1, 0),
    RK3036_PLL_RATE(1104000000, 1, 92, 2, 1, 1, 0),
    RK3036_PLL_RATE(1100000000, 3, 275, 2, 1, 1, 0),
    RK3036_PLL_RATE(1008000000, 1, 84, 2, 1, 1, 0),
    RK3036_PLL_RATE(1000000000, 3, 250, 2, 1, 1, 0),
    RK3036_PLL_RATE(912000000, 1, 76, 2, 1, 1, 0),
    RK3036_PLL_RATE(816000000, 1, 68, 2, 1, 1, 0),
    RK3036_PLL_RATE(800000000, 3, 200, 2, 1, 1, 0),
    RK3036_PLL_RATE(700000000, 3, 350, 4, 1, 1, 0),
    RK3036_PLL_RATE(696000000, 1, 116, 4, 1, 1, 0),
    RK3036_PLL_RATE(600000000, 1, 100, 4, 1, 1, 0),
    RK3036_PLL_RATE(594000000, 1, 99, 4, 1, 1, 0),
    RK3036_PLL_RATE(500000000, 1, 125, 6, 1, 1, 0),
    RK3036_PLL_RATE(408000000, 1, 68, 2, 2, 1, 0),
    RK3036_PLL_RATE(312000000, 1, 78, 6, 1, 1, 0),
    RK3036_PLL_RATE(297000000, 1, 99, 4, 2, 1, 0),
    RK3036_PLL_RATE(292500000, 1, 195, 4, 4, 1, 0),
    RK3036_PLL_RATE(241500000, 1, 161, 4, 4, 1, 0),
    RK3036_PLL_RATE(216000000, 1, 72, 4, 2, 1, 0),
    RK3036_PLL_RATE(200000000, 1, 100, 3, 4, 1, 0),
    RK3036_PLL_RATE(148500000, 1, 99, 4, 4, 1, 0),
    RK3036_PLL_RATE(135000000, 1, 45, 4, 2, 1, 0),
    RK3036_PLL_RATE(119000000, 3, 119, 4, 2, 1, 0),
    RK3036_PLL_RATE(108000000, 1, 45, 5, 2, 1, 0),
    RK3036_PLL_RATE(101000000, 1, 101, 6, 4, 1, 0),
    RK3036_PLL_RATE(100000000, 1, 150, 6, 6, 1, 0),
    RK3036_PLL_RATE(96000000, 1, 96, 6, 4, 1, 0),
    RK3036_PLL_RATE(78750000, 4, 315, 6, 4, 1, 0),
    RK3036_PLL_RATE(74250000, 2, 99, 4, 4, 1, 0),
    { /* sentinel */ },
};

#define RK3568_CLKSEL1(_sclk_core)                                      \
{                                                                       \
    .reg = RK3568_CLKSEL_CON(2),                                        \
    .val = HIWORD_UPDATE(_sclk_core, RK3568_MUX_SCLK_CORE_NPLL_MASK,    \
            RK3568_MUX_SCLK_CORE_NPLL_SHIFT) |                          \
           HIWORD_UPDATE(_sclk_core, RK3568_MUX_SCLK_CORE_MASK,         \
            RK3568_MUX_SCLK_CORE_SHIFT) |                               \
           HIWORD_UPDATE(1, RK3568_DIV_SCLK_CORE_MASK,                  \
            RK3568_DIV_SCLK_CORE_SHIFT),                                \
}

#define RK3568_CLKSEL2(_aclk_core)                                      \
{                                                                       \
    .reg = RK3568_CLKSEL_CON(5),                                        \
    .val = HIWORD_UPDATE(_aclk_core, RK3568_DIV_ACLK_CORE_MASK,         \
            RK3568_DIV_ACLK_CORE_SHIFT),                                \
}

#define RK3568_CLKSEL3(_atclk_core, _gic_core)                          \
{                                                                       \
    .reg = RK3568_CLKSEL_CON(3),                                        \
    .val = HIWORD_UPDATE(_atclk_core, RK3568_DIV_ATCLK_CORE_MASK,       \
            RK3568_DIV_ATCLK_CORE_SHIFT) |                              \
           HIWORD_UPDATE(_gic_core, RK3568_DIV_GICCLK_CORE_MASK,        \
            RK3568_DIV_GICCLK_CORE_SHIFT),                              \
}

#define RK3568_CLKSEL4(_pclk_core, _periph_core)                        \
{                                                                       \
    .reg = RK3568_CLKSEL_CON(4),                                        \
    .val = HIWORD_UPDATE(_pclk_core, RK3568_DIV_PCLK_CORE_MASK,         \
            RK3568_DIV_PCLK_CORE_SHIFT) |                               \
           HIWORD_UPDATE(_periph_core, RK3568_DIV_PERIPHCLK_CORE_MASK,  \
            RK3568_DIV_PERIPHCLK_CORE_SHIFT),                           \
}

#define RK3568_CPUCLK_RATE(_prate, _sclk, _acore, _atcore, _gicclk, _pclk, _periph) \
{                                           \
    .prate = _prate##U,                     \
    .divs =                                 \
    {                                       \
        RK3568_CLKSEL1(_sclk),              \
        RK3568_CLKSEL2(_acore),             \
        RK3568_CLKSEL3(_atcore, _gicclk),   \
        RK3568_CLKSEL4(_pclk, _periph),     \
    },                                      \
}

static struct rockchip_cpu_clk_rate_table rk3568_cpu_clk_rates[] =
{
    RK3568_CPUCLK_RATE(1800000000, 0, 1, 7, 7, 7, 7),
    RK3568_CPUCLK_RATE(1704000000, 0, 1, 7, 7, 7, 7),
    RK3568_CPUCLK_RATE(1608000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1584000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1560000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1536000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1512000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1488000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1464000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1440000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1416000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1392000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1368000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1344000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1320000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1296000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1272000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1248000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1224000000, 0, 1, 5, 5, 5, 5),
    RK3568_CPUCLK_RATE(1200000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(1104000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(1008000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(912000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(816000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(696000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(600000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(408000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(312000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(216000000, 0, 1, 3, 3, 3, 3),
    RK3568_CPUCLK_RATE(96000000, 0, 1, 3, 3, 3, 3),
};

static const struct rockchip_cpu_clk_reg_data rk3568_cpu_clk_data =
{
    .core_reg[0] = RK3568_CLKSEL_CON(0),
    .div_core_shift[0] = 0,
    .div_core_mask[0] = 0x1f,
    .core_reg[1] = RK3568_CLKSEL_CON(0),
    .div_core_shift[1] = 8,
    .div_core_mask[1] = 0x1f,
    .core_reg[2] = RK3568_CLKSEL_CON(1),
    .div_core_shift[2] = 0,
    .div_core_mask[2] = 0x1f,
    .core_reg[3] = RK3568_CLKSEL_CON(1),
    .div_core_shift[3] = 8,
    .div_core_mask[3] = 0x1f,
    .num_cores = 4,
    .mux_core_alt = 1,
    .mux_core_main = 0,
    .mux_core_shift = 6,
    .mux_core_mask = 0x1,
};

PNAME(mux_pll_p)                            = "xin24m";
PNAMES(mux_usb480m_p)                       = { "xin24m", "usb480m_phy", "clk_rtc_32k" };
PNAMES(clk_i2s0_8ch_tx_p)                   = { "clk_i2s0_8ch_tx_src", "clk_i2s0_8ch_tx_frac", "i2s0_mclkin", "xin_osc0_half" };
PNAMES(clk_i2s0_8ch_rx_p)                   = { "clk_i2s0_8ch_rx_src", "clk_i2s0_8ch_rx_frac", "i2s0_mclkin", "xin_osc0_half" };
PNAMES(clk_i2s1_8ch_tx_p)                   = { "clk_i2s1_8ch_tx_src", "clk_i2s1_8ch_tx_frac", "i2s1_mclkin", "xin_osc0_half" };
PNAMES(clk_i2s1_8ch_rx_p)                   = { "clk_i2s1_8ch_rx_src", "clk_i2s1_8ch_rx_frac", "i2s1_mclkin", "xin_osc0_half" };
PNAMES(clk_i2s2_2ch_p)                      = { "clk_i2s2_2ch_src", "clk_i2s2_2ch_frac", "i2s2_mclkin", "xin_osc0_half "};
PNAMES(clk_i2s3_2ch_tx_p)                   = { "clk_i2s3_2ch_tx_src", "clk_i2s3_2ch_tx_frac", "i2s3_mclkin", "xin_osc0_half" };
PNAMES(clk_i2s3_2ch_rx_p)                   = { "clk_i2s3_2ch_rx_src", "clk_i2s3_2ch_rx_frac", "i2s3_mclkin", "xin_osc0_half" };
PNAMES(mclk_spdif_8ch_p)                    = { "mclk_spdif_8ch_src", "mclk_spdif_8ch_frac" };
PNAMES(sclk_audpwm_p)                       = { "sclk_audpwm_src", "sclk_audpwm_frac" };
PNAMES(sclk_uart1_p)                        = { "clk_uart1_src", "clk_uart1_frac", "xin24m" };
PNAMES(sclk_uart2_p)                        = { "clk_uart2_src", "clk_uart2_frac", "xin24m" };
PNAMES(sclk_uart3_p)                        = { "clk_uart3_src", "clk_uart3_frac", "xin24m" };
PNAMES(sclk_uart4_p)                        = { "clk_uart4_src", "clk_uart4_frac", "xin24m" };
PNAMES(sclk_uart5_p)                        = { "clk_uart5_src", "clk_uart5_frac", "xin24m" };
PNAMES(sclk_uart6_p)                        = { "clk_uart6_src", "clk_uart6_frac", "xin24m" };
PNAMES(sclk_uart7_p)                        = { "clk_uart7_src", "clk_uart7_frac", "xin24m" };
PNAMES(sclk_uart8_p)                        = { "clk_uart8_src", "clk_uart8_frac", "xin24m" };
PNAMES(sclk_uart9_p)                        = { "clk_uart9_src", "clk_uart9_frac", "xin24m" };
PNAMES(sclk_uart0_p)                        = { "sclk_uart0_div", "sclk_uart0_frac", "xin24m" };
PNAMES(clk_rtc32k_pmu_p)                    = { "clk_32k_pvtm", "xin32k", "clk_rtc32k_frac" };
PNAMES(mpll_gpll_cpll_npll_p)               = { "mpll", "gpll", "cpll", "npll" };
PNAMES(gpll_cpll_npll_p)                    = { "gpll", "cpll", "npll" };
PNAMES(npll_gpll_p)                         = { "npll", "gpll" };
PNAMES(cpll_gpll_p)                         = { "cpll", "gpll" };
PNAMES(gpll_cpll_p)                         = { "gpll", "cpll" };
PNAMES(gpll_cpll_npll_vpll_p)               = { "gpll", "cpll", "npll", "vpll" };
PNAMES(apll_gpll_npll_p)                    = { "apll", "gpll", "npll" };
PNAMES(sclk_core_pre_p)                     = { "sclk_core_src", "npll" };
PNAMES(gpll150_gpll100_gpll75_xin24m_p)     = { "gpll_150m", "gpll_100m", "gpll_75m", "xin24m" };
PNAMES(clk_gpu_pre_mux_p)                   = { "clk_gpu_src", "gpu_pvtpll_out" };
PNAMES(clk_npu_pre_ndft_p)                  = { "clk_npu_src", "clk_npu_np5"};
PNAMES(clk_npu_p)                           = { "clk_npu_pre_ndft", "npu_pvtpll_out" };
PNAMES(dpll_gpll_cpll_p)                    = { "dpll", "gpll", "cpll" };
PNAMES(clk_ddr1x_p)                         = { "clk_ddrphy1x_src", "dpll" };
PNAMES(gpll200_gpll150_gpll100_xin24m_p)    = { "gpll_200m", "gpll_150m", "gpll_100m", "xin24m" };
PNAMES(gpll100_gpll75_gpll50_p)             = { "gpll_100m", "gpll_75m", "cpll_50m" };
PNAMES(i2s0_mclkout_tx_p)                   = { "mclk_i2s0_8ch_tx", "xin_osc0_half" };
PNAMES(i2s0_mclkout_rx_p)                   = { "mclk_i2s0_8ch_rx", "xin_osc0_half" };
PNAMES(i2s1_mclkout_tx_p)                   = { "mclk_i2s1_8ch_tx", "xin_osc0_half" };
PNAMES(i2s1_mclkout_rx_p)                   = { "mclk_i2s1_8ch_rx", "xin_osc0_half" };
PNAMES(i2s2_mclkout_p)                      = { "mclk_i2s2_2ch", "xin_osc0_half" };
PNAMES(i2s3_mclkout_tx_p)                   = { "mclk_i2s3_2ch_tx", "xin_osc0_half" };
PNAMES(i2s3_mclkout_rx_p)                   = { "mclk_i2s3_2ch_rx", "xin_osc0_half" };
PNAMES(mclk_pdm_p)                          = { "gpll_300m", "cpll_250m", "gpll_200m", "gpll_100m" };
PNAMES(clk_i2c_p)                           = { "gpll_200m", "gpll_100m", "xin24m", "cpll_100m" };
PNAMES(gpll200_gpll150_gpll100_p)           = { "gpll_200m", "gpll_150m", "gpll_100m" };
PNAMES(gpll300_gpll200_gpll100_p)           = { "gpll_300m", "gpll_200m", "gpll_100m" };
PNAMES(clk_nandc_p)                         = { "gpll_200m", "gpll_150m", "cpll_100m", "xin24m" };
PNAMES(sclk_sfc_p)                          = { "xin24m", "cpll_50m", "gpll_75m", "gpll_100m", "cpll_125m", "gpll_150m" };
PNAMES(gpll200_gpll150_cpll125_p)           = { "gpll_200m", "gpll_150m", "cpll_125m" };
PNAMES(cclk_emmc_p)                         = { "xin24m", "gpll_200m", "gpll_150m", "cpll_100m", "cpll_50m", "clk_osc0_div_375k" };
PNAMES(aclk_pipe_p)                         = { "gpll_400m", "gpll_300m", "gpll_200m", "xin24m" };
PNAMES(gpll200_cpll125_p)                   = { "gpll_200m", "cpll_125m" };
PNAMES(gpll300_gpll200_gpll100_xin24m_p)    = { "gpll_300m", "gpll_200m", "gpll_100m", "xin24m" };
PNAMES(clk_sdmmc_p)                         = { "xin24m", "gpll_400m", "gpll_300m", "cpll_100m", "cpll_50m", "clk_osc0_div_750k" };
PNAMES(cpll125_cpll50_cpll25_xin24m_p)      = { "cpll_125m", "cpll_50m", "cpll_25m", "xin24m" };
PNAMES(clk_gmac_ptp_p)                      = { "cpll_62p5", "gpll_100m", "cpll_50m", "xin24m" };
PNAMES(cpll333_gpll300_gpll200_p)           = { "cpll_333m", "gpll_300m", "gpll_200m" };
PNAMES(cpll_gpll_hpll_p)                    = { "cpll", "gpll", "hpll" };
PNAMES(gpll_usb480m_xin24m_p)               = { "gpll", "usb480m", "xin24m", "xin24m" };
PNAMES(gpll300_cpll250_gpll100_xin24m_p)    = { "gpll_300m", "cpll_250m", "gpll_100m", "xin24m" };
PNAMES(cpll_gpll_hpll_vpll_p)               = { "cpll", "gpll", "hpll", "vpll" };
PNAMES(hpll_vpll_gpll_cpll_p)               = { "hpll", "vpll", "gpll", "cpll" };
PNAMES(gpll400_cpll333_gpll200_p)           = { "gpll_400m", "cpll_333m", "gpll_200m" };
PNAMES(gpll100_gpll75_cpll50_xin24m_p)      = { "gpll_100m", "gpll_75m", "cpll_50m", "xin24m" };
PNAMES(xin24m_gpll100_cpll100_p)            = { "xin24m", "gpll_100m", "cpll_100m" };
PNAMES(gpll_cpll_usb480m_p)                 = { "gpll", "cpll", "usb480m" };
PNAMES(gpll100_xin24m_cpll100_p)            = { "gpll_100m", "xin24m", "cpll_100m" };
PNAMES(gpll200_xin24m_cpll100_p)            = { "gpll_200m", "xin24m", "cpll_100m" };
PNAMES(xin24m_32k_p)                        = { "xin24m", "clk_rtc_32k" };
PNAMES(cpll500_gpll400_gpll300_xin24m_p)    = { "cpll_500m", "gpll_400m", "gpll_300m", "xin24m" };
PNAMES(gpll400_gpll300_gpll200_xin24m_p)    = { "gpll_400m", "gpll_300m", "gpll_200m", "xin24m" };
PNAMES(xin24m_cpll100_p)                    = { "xin24m", "cpll_100m" };
PNAMES(ppll_usb480m_cpll_gpll_p)            = { "ppll", "usb480m", "cpll", "gpll"};
PNAMES(clk_usbphy0_ref_p)                   = { "clk_ref24m", "xin_osc0_usbphy0_g" };
PNAMES(clk_usbphy1_ref_p)                   = { "clk_ref24m", "xin_osc0_usbphy1_g" };
PNAMES(clk_mipidsiphy0_ref_p)               = { "clk_ref24m", "xin_osc0_mipidsiphy0_g" };
PNAMES(clk_mipidsiphy1_ref_p)               = { "clk_ref24m", "xin_osc0_mipidsiphy1_g" };
PNAMES(clk_wifi_p)                          = { "clk_wifi_osc0", "clk_wifi_div" };
PNAMES(clk_pciephy0_ref_p)                  = { "clk_pciephy0_osc0", "clk_pciephy0_div" };
PNAMES(clk_pciephy1_ref_p)                  = { "clk_pciephy1_osc0", "clk_pciephy1_div" };
PNAMES(clk_pciephy2_ref_p)                  = { "clk_pciephy2_osc0", "clk_pciephy2_div" };
PNAMES(mux_gmac0_p)                         = { "clk_mac0_2top", "gmac0_clkin" };
PNAMES(mux_gmac0_rgmii_speed_p)             = { "clk_gmac0", "clk_gmac0", "clk_gmac0_tx_div50", "clk_gmac0_tx_div5" };
PNAMES(mux_gmac0_rmii_speed_p)              = { "clk_gmac0_rx_div20", "clk_gmac0_rx_div2" };
PNAMES(mux_gmac0_rx_tx_p)                   = { "clk_gmac0_rgmii_speed", "clk_gmac0_rmii_speed", "clk_gmac0_xpcs_mii" };
PNAMES(mux_gmac1_p)                         = { "clk_mac1_2top", "gmac1_clkin" };
PNAMES(mux_gmac1_rgmii_speed_p)             = { "clk_gmac1", "clk_gmac1", "clk_gmac1_tx_div50", "clk_gmac1_tx_div5" };
PNAMES(mux_gmac1_rmii_speed_p)              = { "clk_gmac1_rx_div20", "clk_gmac1_rx_div2" };
PNAMES(mux_gmac1_rx_tx_p)                   = { "clk_gmac1_rgmii_speed", "clk_gmac1_rmii_speed", "clk_gmac1_xpcs_mii" };
PNAMES(clk_hdmi_ref_p)                      = { "hpll", "hpll_ph0" };
PNAMES(clk_pdpmu_p)                         = { "ppll", "gpll" };
PNAMES(clk_mac_2top_p)                      = { "cpll_125m", "cpll_50m", "cpll_25m", "ppll" };
PNAMES(clk_pwm0_p)                          = { "xin24m", "clk_pdpmu" };
PNAMES(aclk_rkvdec_pre_p)                   = { "gpll", "cpll" };
PNAMES(clk_rkvdec_core_p)                   = { "gpll", "cpll" };
PNAMES(clk_32k_ioe_p)                       = { "clk_rtc_32k", "xin32k" };
PNAMES(i2s1_mclkout_p)                      = { "i2s1_mclkout_rx", "i2s1_mclkout_tx" };
PNAMES(i2s3_mclkout_p)                      = { "i2s3_mclkout_rx", "i2s3_mclkout_tx" };
PNAMES(i2s1_mclk_rx_ioe_p)                  = { "i2s1_mclkin_rx", "i2s1_mclkout_rx" };
PNAMES(i2s1_mclk_tx_ioe_p)                  = { "i2s1_mclkin_tx", "i2s1_mclkout_tx" };
PNAMES(i2s2_mclk_ioe_p)                     = { "i2s2_mclkin", "i2s2_mclkout" };
PNAMES(i2s3_mclk_ioe_p)                     = { "i2s3_mclkin", "i2s3_mclkout" };

#define MFLAGS CLK_MUX_HIWORD_MASK
#define DFLAGS CLK_DIVIDER_HIWORD_MASK
#define GFLAGS (CLK_GATE_HIWORD_MASK | CLK_GATE_SET_TO_DISABLE)

static struct rockchip_pll_clk_cell rk3568_pmu_pll_ppll =
    PLL_RAW(pll_type_rk3328, PLL_PPLL, "ppll", mux_pll_p, 1, 0, RK3568_PMU_PLL_CON(0), RK3568_PMU_MODE_CON0,
            0, 4, RK3568_GRF_SOC_STATUS0, 0, rk3568_pll_rates);
static struct rockchip_pll_clk_cell rk3568_pmu_pll_hpll =
    PLL_RAW(pll_type_rk3328, PLL_HPLL, "hpll", mux_pll_p, 1, 0, RK3568_PMU_PLL_CON(16), RK3568_PMU_MODE_CON0,
            2, 7, RK3568_GRF_SOC_STATUS0, 0, rk3568_pll_rates);

static struct rockchip_pll_clk_cell rk3568_pll_apll =
    PLL_RAW(pll_type_rk3328, PLL_APLL, "apll", mux_pll_p, 1, 0, RK3568_PLL_CON(0), RK3568_MODE_CON0,
            0, 0, RK3568_GRF_SOC_STATUS0, 0, rk3568_pll_rates);
static struct rockchip_pll_clk_cell rk3568_pll_dpll =
    PLL_RAW(pll_type_rk3328, PLL_DPLL, "dpll", mux_pll_p, 1, 0, RK3568_PLL_CON(8), RK3568_MODE_CON0,
            2, 1, RK3568_GRF_SOC_STATUS0, 0, RT_NULL);
static struct rockchip_pll_clk_cell rk3568_pll_cpll =
    PLL_RAW(pll_type_rk3328, PLL_CPLL, "cpll", mux_pll_p, 1, 0, RK3568_PLL_CON(24), RK3568_MODE_CON0,
            4, 2, RK3568_GRF_SOC_STATUS0, 0, rk3568_pll_rates);
static struct rockchip_pll_clk_cell rk3568_pll_gpll =
    PLL_RAW(pll_type_rk3328, PLL_GPLL, "gpll", mux_pll_p, 1, 0, RK3568_PLL_CON(16), RK3568_MODE_CON0,
            6, 3, RK3568_GRF_SOC_STATUS0, 0, rk3568_pll_rates);
static struct rockchip_pll_clk_cell rk3568_pll_npll =
    PLL_RAW(pll_type_rk3328, PLL_NPLL, "npll", mux_pll_p, 1, RT_CLK_F_IS_CRITICAL, RK3568_PLL_CON(32), RK3568_MODE_CON0,
            10, 5, RK3568_GRF_SOC_STATUS0, 0, rk3568_pll_rates);
static struct rockchip_pll_clk_cell rk3568_pll_vpll =
    PLL_RAW(pll_type_rk3328, PLL_VPLL, "vpll", mux_pll_p, 1, 0, RK3568_PLL_CON(40), RK3568_MODE_CON0,
            12, 6, RK3568_GRF_SOC_STATUS0, 0, rk3568_pll_rates);

static struct rockchip_clk_cell rk3568_i2s0_8ch_tx_fracmux =
    MUX_RAW(CLK_I2S0_8CH_TX, "clk_i2s0_8ch_tx", clk_i2s0_8ch_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(11), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_i2s0_8ch_rx_fracmux =
    MUX_RAW(CLK_I2S0_8CH_RX, "clk_i2s0_8ch_rx", clk_i2s0_8ch_rx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(13), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_i2s1_8ch_tx_fracmux =
    MUX_RAW(CLK_I2S1_8CH_TX, "clk_i2s1_8ch_tx", clk_i2s1_8ch_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(15), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_i2s1_8ch_rx_fracmux =
    MUX_RAW(CLK_I2S1_8CH_RX, "clk_i2s1_8ch_rx", clk_i2s1_8ch_rx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(17), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_i2s2_2ch_fracmux =
    MUX_RAW(CLK_I2S2_2CH, "clk_i2s2_2ch", clk_i2s2_2ch_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(19), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_i2s3_2ch_tx_fracmux =
    MUX_RAW(CLK_I2S3_2CH_TX, "clk_i2s3_2ch_tx", clk_i2s3_2ch_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(21), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_i2s3_2ch_rx_fracmux =
    MUX_RAW(CLK_I2S3_2CH_RX, "clk_i2s3_2ch_rx", clk_i2s3_2ch_rx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(83), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_spdif_8ch_fracmux =
    MUX_RAW(MCLK_SPDIF_8CH, "mclk_spdif_8ch", mclk_spdif_8ch_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(23), 15, 1, MFLAGS);

static struct rockchip_clk_cell rk3568_audpwm_fracmux =
    MUX_RAW(SCLK_AUDPWM, "sclk_audpwm", sclk_audpwm_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(25), 15, 1, MFLAGS);

static struct rockchip_clk_cell rk3568_uart1_fracmux =
    MUX_RAW(0, "sclk_uart1_mux", sclk_uart1_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(52), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart2_fracmux =
    MUX_RAW(0, "sclk_uart2_mux", sclk_uart2_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(54), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart3_fracmux =
    MUX_RAW(0, "sclk_uart3_mux", sclk_uart3_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(56), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart4_fracmux =
    MUX_RAW(0, "sclk_uart4_mux", sclk_uart4_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(58), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart5_fracmux =
    MUX_RAW(0, "sclk_uart5_mux", sclk_uart5_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(60), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart6_fracmux =
    MUX_RAW(0, "sclk_uart6_mux", sclk_uart6_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(62), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart7_fracmux =
    MUX_RAW(0, "sclk_uart7_mux", sclk_uart7_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(64), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart8_fracmux =
    MUX_RAW(0, "sclk_uart8_mux", sclk_uart8_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(66), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart9_fracmux =
    MUX_RAW(0, "sclk_uart9_mux", sclk_uart9_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(68), 12, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_uart0_fracmux =
    MUX_RAW(0, "sclk_uart0_mux", sclk_uart0_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_PMU_CLKSEL_CON(4), 10, 2, MFLAGS);

static struct rockchip_clk_cell rk3568_rtc32k_pmu_fracmux =
    MUX_RAW(CLK_RTC_32K, "clk_rtc_32k", clk_rtc32k_pmu_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_PMU_CLKSEL_CON(0), 6, 2, MFLAGS);

static struct rt_clk_cell *rk3568_clk_pmu_cells[] =
{
    [PLL_PPLL] = &rk3568_pmu_pll_ppll.rk_cell.cell,
    [PLL_HPLL] = &rk3568_pmu_pll_hpll.rk_cell.cell,
    [XIN_OSC0_DIV] = COMPOSITE_NOMUX(XIN_OSC0_DIV, "xin_osc0_div", "xin24m", RT_CLK_F_IGNORE_UNUSED,
            RK3568_PMU_CLKSEL_CON(0), 0, 5, DFLAGS,
            RK3568_PMU_CLKGATE_CON(0), 0, GFLAGS),
    [CLK_RTC_32K] = &rk3568_rtc32k_pmu_fracmux.cell,
    [CLK_PMU] = GATE(CLK_PMU, "clk_pmu", "xin24m", RT_CLK_F_IS_CRITICAL, RK3568_PMU_CLKGATE_CON(0), 7, GFLAGS),
    [CLK_I2C0] = COMPOSITE_NOMUX(CLK_I2C0, "clk_i2c0", "clk_pdpmu", 0,
            RK3568_PMU_CLKSEL_CON(3), 0, 7, DFLAGS,
            RK3568_PMU_CLKGATE_CON(1), 1, GFLAGS),
    [CLK_RTC32K_FRAC] = COMPOSITE_FRACMUX(CLK_RTC32K_FRAC, "clk_rtc32k_frac", "xin24m", RT_CLK_F_IGNORE_UNUSED,
            RK3568_PMU_CLKSEL_CON(1), 0,
            RK3568_PMU_CLKGATE_CON(0), 1, GFLAGS,
            &rk3568_rtc32k_pmu_fracmux),
    [CLK_UART0_DIV] = COMPOSITE(CLK_UART0_DIV, "sclk_uart0_div", ppll_usb480m_cpll_gpll_p, 0,
            RK3568_PMU_CLKSEL_CON(4), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_PMU_CLKGATE_CON(1), 3, GFLAGS),
    [CLK_UART0_FRAC] = COMPOSITE_FRACMUX(CLK_UART0_FRAC, "sclk_uart0_frac", "sclk_uart0_div", RT_CLK_F_SET_RATE_PARENT,
            RK3568_PMU_CLKSEL_CON(5), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_PMU_CLKGATE_CON(1), 4, GFLAGS,
            &rk3568_uart0_fracmux),
    [SCLK_UART0] = GATE(SCLK_UART0, "sclk_uart0", "sclk_uart0_mux", 0, RK3568_PMU_CLKGATE_CON(1), 5, GFLAGS),
    [DBCLK_GPIO0] = COMPOSITE_NODIV(DBCLK_GPIO0, "dbclk_gpio0", xin24m_32k_p, 0,
            RK3568_PMU_CLKSEL_CON(6), 15, 1, MFLAGS,
            RK3568_PMU_CLKGATE_CON(1), 10, GFLAGS),
    [CLK_PWM0] = COMPOSITE(CLK_PWM0, "clk_pwm0", clk_pwm0_p, 0,
            RK3568_PMU_CLKSEL_CON(6), 7, 1, MFLAGS, 0, 7, DFLAGS,
            RK3568_PMU_CLKGATE_CON(1), 7, GFLAGS),
    [CLK_CAPTURE_PWM0_NDFT] = GATE(CLK_CAPTURE_PWM0_NDFT, "clk_capture_pwm0_ndft", "xin24m", 0, RK3568_PMU_CLKGATE_CON(1), 8, GFLAGS),
    [CLK_PMUPVTM] = GATE(CLK_PMUPVTM, "clk_pmupvtm", "xin24m", 0, RK3568_PMU_CLKGATE_CON(1), 12, GFLAGS),
    [CLK_CORE_PMUPVTM] = GATE(CLK_CORE_PMUPVTM, "clk_core_pmupvtm", "xin24m", 0, RK3568_PMU_CLKGATE_CON(1), 13, GFLAGS),
    [CLK_REF24M] = COMPOSITE_NOMUX(CLK_REF24M, "clk_ref24m", "clk_pdpmu", 0,
            RK3568_PMU_CLKSEL_CON(7), 0, 6, DFLAGS,
            RK3568_PMU_CLKGATE_CON(2), 0, GFLAGS),
    [XIN_OSC0_USBPHY0_G] = GATE(XIN_OSC0_USBPHY0_G, "xin_osc0_usbphy0_g", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 1, GFLAGS),
    [CLK_USBPHY0_REF] = MUX(CLK_USBPHY0_REF, "clk_usbphy0_ref", clk_usbphy0_ref_p, 0,
            RK3568_PMU_CLKSEL_CON(8), 0, 1, MFLAGS),
    [XIN_OSC0_USBPHY1_G] = GATE(XIN_OSC0_USBPHY1_G, "xin_osc0_usbphy1_g", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 2, GFLAGS),
    [CLK_USBPHY1_REF] = MUX(CLK_USBPHY1_REF, "clk_usbphy1_ref", clk_usbphy1_ref_p, 0,
            RK3568_PMU_CLKSEL_CON(8), 1, 1, MFLAGS),
    [XIN_OSC0_MIPIDSIPHY0_G] = GATE(XIN_OSC0_MIPIDSIPHY0_G, "xin_osc0_mipidsiphy0_g", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 3, GFLAGS),
    [CLK_MIPIDSIPHY0_REF] = MUX(CLK_MIPIDSIPHY0_REF, "clk_mipidsiphy0_ref", clk_mipidsiphy0_ref_p, 0,
            RK3568_PMU_CLKSEL_CON(8), 2, 1, MFLAGS),
    [XIN_OSC0_MIPIDSIPHY1_G] = GATE(XIN_OSC0_MIPIDSIPHY1_G, "xin_osc0_mipidsiphy1_g", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 4, GFLAGS),
    [CLK_MIPIDSIPHY1_REF] = MUX(CLK_MIPIDSIPHY1_REF, "clk_mipidsiphy1_ref", clk_mipidsiphy1_ref_p, 0,
            RK3568_PMU_CLKSEL_CON(8), 3, 1, MFLAGS),
    [CLK_WIFI_DIV] = COMPOSITE_NOMUX(CLK_WIFI_DIV, "clk_wifi_div", "clk_pdpmu", 0,
            RK3568_PMU_CLKSEL_CON(8), 8, 6, DFLAGS,
            RK3568_PMU_CLKGATE_CON(2), 5, GFLAGS),
    [CLK_WIFI_OSC0] = GATE(CLK_WIFI_OSC0, "clk_wifi_osc0", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 6, GFLAGS),
    [CLK_WIFI] = MUX(CLK_WIFI, "clk_wifi", clk_wifi_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_PMU_CLKSEL_CON(8), 15, 1, MFLAGS),
    [CLK_PCIEPHY0_DIV] = COMPOSITE_NOMUX(CLK_PCIEPHY0_DIV, "clk_pciephy0_div", "ppll_ph0", 0,
            RK3568_PMU_CLKSEL_CON(9), 0, 3, DFLAGS,
            RK3568_PMU_CLKGATE_CON(2), 7, GFLAGS),
    [CLK_PCIEPHY0_OSC0] = GATE(CLK_PCIEPHY0_OSC0, "clk_pciephy0_osc0", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 8, GFLAGS),
    [CLK_PCIEPHY0_REF] = MUX(CLK_PCIEPHY0_REF, "clk_pciephy0_ref", clk_pciephy0_ref_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_PMU_CLKSEL_CON(9), 3, 1, MFLAGS),
    [CLK_PCIEPHY1_DIV] = COMPOSITE_NOMUX(CLK_PCIEPHY1_DIV, "clk_pciephy1_div", "ppll_ph0", 0,
            RK3568_PMU_CLKSEL_CON(9), 4, 3, DFLAGS,
            RK3568_PMU_CLKGATE_CON(2), 9, GFLAGS),
    [CLK_PCIEPHY1_OSC0] = GATE(CLK_PCIEPHY1_OSC0, "clk_pciephy1_osc0", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 10, GFLAGS),
    [CLK_PCIEPHY1_REF] = MUX(CLK_PCIEPHY1_REF, "clk_pciephy1_ref", clk_pciephy1_ref_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_PMU_CLKSEL_CON(9), 7, 1, MFLAGS),
    [CLK_PCIEPHY2_DIV] = COMPOSITE_NOMUX(CLK_PCIEPHY2_DIV, "clk_pciephy2_div", "ppll_ph0", 0,
            RK3568_PMU_CLKSEL_CON(9), 8, 3, DFLAGS,
            RK3568_PMU_CLKGATE_CON(2), 11, GFLAGS),
    [CLK_PCIEPHY2_OSC0] = GATE(CLK_PCIEPHY2_OSC0, "clk_pciephy2_osc0", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 12, GFLAGS),
    [CLK_PCIEPHY2_REF] = MUX(CLK_PCIEPHY2_REF, "clk_pciephy2_ref", clk_pciephy2_ref_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_PMU_CLKSEL_CON(9), 11, 1, MFLAGS),
    [CLK_PCIE30PHY_REF_M] = GATE(CLK_PCIE30PHY_REF_M, "clk_pcie30phy_ref_m", "ppll_ph0", 0, RK3568_PMU_CLKGATE_CON(2), 13, GFLAGS),
    [CLK_PCIE30PHY_REF_N] = GATE(CLK_PCIE30PHY_REF_N, "clk_pcie30phy_ref_n", "ppll_ph180", 0, RK3568_PMU_CLKGATE_CON(2), 14, GFLAGS),
    [CLK_HDMI_REF] = MUX(CLK_HDMI_REF, "clk_hdmi_ref", clk_hdmi_ref_p, 0,
            RK3568_PMU_CLKSEL_CON(8), 7, 1, MFLAGS),
    [XIN_OSC0_EDPPHY_G] = GATE(XIN_OSC0_EDPPHY_G, "xin_osc0_edpphy_g", "xin24m", 0, RK3568_PMU_CLKGATE_CON(2), 15, GFLAGS),
    [PCLK_PDPMU] = COMPOSITE_NOMUX(PCLK_PDPMU, "pclk_pdpmu", "clk_pdpmu", RT_CLK_F_IS_CRITICAL,
            RK3568_PMU_CLKSEL_CON(2), 0, 5, DFLAGS,
            RK3568_PMU_CLKGATE_CON(0), 2, GFLAGS),
    [PCLK_PMU] = GATE(PCLK_PMU, "pclk_pmu", "pclk_pdpmu", RT_CLK_F_IS_CRITICAL, RK3568_PMU_CLKGATE_CON(0), 6, GFLAGS),
    [PCLK_UART0] = GATE(PCLK_UART0, "pclk_uart0", "pclk_pdpmu", 0, RK3568_PMU_CLKGATE_CON(1), 2, GFLAGS),
    [PCLK_I2C0] = GATE(PCLK_I2C0, "pclk_i2c0", "pclk_pdpmu", 0, RK3568_PMU_CLKGATE_CON(1), 0, GFLAGS),
    [PCLK_GPIO0] = GATE(PCLK_GPIO0, "pclk_gpio0", "pclk_pdpmu", 0, RK3568_PMU_CLKGATE_CON(1), 9, GFLAGS),
    [PCLK_PMUPVTM] = GATE(PCLK_PMUPVTM, "pclk_pmupvtm", "pclk_pdpmu", 0, RK3568_PMU_CLKGATE_CON(1), 11, GFLAGS),
    [PCLK_PWM0] = GATE(PCLK_PWM0, "pclk_pwm0", "pclk_pdpmu", 0, RK3568_PMU_CLKGATE_CON(1), 6, GFLAGS),
    [CLK_PDPMU] = MUX(CLK_PDPMU, "clk_pdpmu", clk_pdpmu_p, 0,
            RK3568_PMU_CLKSEL_CON(2), 15, 1, MFLAGS),
    [SCLK_32K_IOE] = MUXPMUGRF(SCLK_32K_IOE, "clk_32k_ioe", clk_32k_ioe_p, 0,
            RK3568_PMU_GRF_SOC_CON0, 0, 1, MFLAGS),

    &rk3568_uart0_fracmux.cell,

    FACTOR(0, "ppll_ph0", "ppll", 0, 1, 2),
    FACTOR(0, "ppll_ph180", "ppll", 0, 1, 2),
    FACTOR(0, "hpll_ph0", "hpll", 0, 1, 2),
};

static struct rt_clk_cell *rk3568_clk_cells[] =
{
    [PLL_APLL] = &rk3568_pll_apll.rk_cell.cell,
    [PLL_DPLL] = &rk3568_pll_dpll.rk_cell.cell,
    [PLL_CPLL] = &rk3568_pll_cpll.rk_cell.cell,
    [PLL_GPLL] = &rk3568_pll_gpll.rk_cell.cell,
    [PLL_VPLL] = &rk3568_pll_npll.rk_cell.cell,
    [PLL_NPLL] = &rk3568_pll_vpll.rk_cell.cell,
    [CPLL_333M] = COMPOSITE_NOMUX(CPLL_333M, "cpll_333m", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(79), 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 8, GFLAGS),
    [ARMCLK] = CPU(ARMCLK, "armclk", &rk3568_pll_apll.rk_cell, &rk3568_pll_gpll.rk_cell,
            rk3568_cpu_clk_rates, RT_ARRAY_SIZE(rk3568_cpu_clk_rates), &rk3568_cpu_clk_data),
    [USB480M] = MUX(USB480M, "usb480m", mux_usb480m_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_MODE_CON0, 14, 2, MFLAGS),
    [ACLK_CORE_NIU2BUS] = COMPOSITE_NODIV(ACLK_CORE_NIU2BUS, "aclk_core_niu2bus", gpll150_gpll100_gpll75_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(5), 14, 2, MFLAGS,
            RK3568_CLKGATE_CON(1), 2, GFLAGS),
    [CLK_CORE_PVTM] = GATE(CLK_CORE_PVTM, "clk_core_pvtm", "xin24m", 0, RK3568_CLKGATE_CON(1), 10, GFLAGS),
    [CLK_CORE_PVTM_CORE] = GATE(CLK_CORE_PVTM_CORE, "clk_core_pvtm_core", "armclk", 0, RK3568_CLKGATE_CON(1), 11, GFLAGS),
    [CLK_CORE_PVTPLL] = GATE(CLK_CORE_PVTPLL, "clk_core_pvtpll", "armclk", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(1), 12, GFLAGS),
    [CLK_GPU_SRC] = COMPOSITE(CLK_GPU_SRC, "clk_gpu_src", mpll_gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(6), 6, 2, MFLAGS | CLK_MUX_READ_ONLY, 0, 4, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(2), 0, GFLAGS),
    [CLK_GPU_PRE_MUX] = MUX(CLK_GPU_PRE_MUX, "clk_gpu_pre_mux", clk_gpu_pre_mux_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(6), 11, 1, MFLAGS | CLK_MUX_READ_ONLY),
    [ACLK_GPU_PRE] = DIV(ACLK_GPU_PRE, "aclk_gpu_pre", "clk_gpu_pre_mux", 0,
            RK3568_CLKSEL_CON(6), 8, 2, DFLAGS),
    [PCLK_GPU_PRE] = DIV(PCLK_GPU_PRE, "pclk_gpu_pre", "clk_gpu_pre_mux", 0,
            RK3568_CLKSEL_CON(6), 12, 4, DFLAGS),
    [CLK_GPU] = GATE(CLK_GPU, "clk_gpu", "clk_gpu_pre_mux", 0, RK3568_CLKGATE_CON(2), 3, GFLAGS),
    [PCLK_GPU_PVTM] = GATE(PCLK_GPU_PVTM, "pclk_gpu_pvtm", "pclk_gpu_pre", 0, RK3568_CLKGATE_CON(2), 6, GFLAGS),
    [CLK_GPU_PVTM] =  GATE(CLK_GPU_PVTM, "clk_gpu_pvtm", "xin24m", 0, RK3568_CLKGATE_CON(2), 7, GFLAGS),
    [CLK_GPU_PVTM_CORE] = GATE(CLK_GPU_PVTM_CORE, "clk_gpu_pvtm_core", "clk_gpu_src", 0, RK3568_CLKGATE_CON(2), 8, GFLAGS),
    [CLK_GPU_PVTPLL] = GATE(CLK_GPU_PVTPLL, "clk_gpu_pvtpll", "clk_gpu_src", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(2), 9, GFLAGS),
    [CLK_NPU_SRC] = COMPOSITE(CLK_NPU_SRC, "clk_npu_src", npll_gpll_p, 0,
            RK3568_CLKSEL_CON(7), 6, 1, MFLAGS, 0, 4, DFLAGS,
            RK3568_CLKGATE_CON(3), 0, GFLAGS),
    [CLK_NPU_PRE_NDFT] = MUX(CLK_NPU_PRE_NDFT, "clk_npu_pre_ndft", clk_npu_pre_ndft_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(7), 8, 1, MFLAGS),
    [CLK_NPU] = MUX(CLK_NPU, "clk_npu", clk_npu_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(7), 15, 1, MFLAGS),
    [CLK_NPU_NP5] = COMPOSITE_HALFDIV(CLK_NPU_NP5, "clk_npu_np5", npll_gpll_p, 0,
            RK3568_CLKSEL_CON(7), 7, 1, MFLAGS, 4, 2, DFLAGS,
            RK3568_CLKGATE_CON(3), 1, GFLAGS),
    [HCLK_NPU_PRE] = COMPOSITE_NOMUX(HCLK_NPU_PRE, "hclk_npu_pre", "clk_npu", 0,
            RK3568_CLKSEL_CON(8), 0, 4, DFLAGS,
            RK3568_CLKGATE_CON(3), 2, GFLAGS),
    [PCLK_NPU_PRE] = COMPOSITE_NOMUX(PCLK_NPU_PRE, "pclk_npu_pre", "clk_npu", 0,
            RK3568_CLKSEL_CON(8), 4, 4, DFLAGS,
            RK3568_CLKGATE_CON(3), 3, GFLAGS),
    [ACLK_NPU_PRE] = GATE(ACLK_NPU_PRE, "aclk_npu_pre", "clk_npu", 0, RK3568_CLKGATE_CON(3), 4, GFLAGS),
    [ACLK_NPU] = GATE(ACLK_NPU, "aclk_npu", "aclk_npu_pre", 0, RK3568_CLKGATE_CON(3), 7, GFLAGS),
    [HCLK_NPU] = GATE(HCLK_NPU, "hclk_npu", "hclk_npu_pre", 0, RK3568_CLKGATE_CON(3), 8, GFLAGS),
    [PCLK_NPU_PVTM] = GATE(PCLK_NPU_PVTM, "pclk_npu_pvtm", "pclk_npu_pre", 0, RK3568_CLKGATE_CON(3), 9, GFLAGS),
    [CLK_NPU_PVTM] = GATE(CLK_NPU_PVTM, "clk_npu_pvtm", "xin24m", 0, RK3568_CLKGATE_CON(3), 10, GFLAGS),
    [CLK_NPU_PVTM_CORE] = GATE(CLK_NPU_PVTM_CORE, "clk_npu_pvtm_core", "clk_npu_pre_ndft", 0, RK3568_CLKGATE_CON(3), 11, GFLAGS),
    [CLK_NPU_PVTPLL] = GATE(CLK_NPU_PVTPLL, "clk_npu_pvtpll", "clk_npu_pre_ndft", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(3), 12, GFLAGS),
    [CLK_DDRPHY1X_SRC] = COMPOSITE(CLK_DDRPHY1X_SRC, "clk_ddrphy1x_src", dpll_gpll_cpll_p, RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(9), 6, 2, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(4), 0, GFLAGS),
    [CLK_DDR1X] = MUXGRF(CLK_DDR1X, "clk_ddr1x", clk_ddr1x_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(9), 15, 1, MFLAGS),
    [CLK_MSCH] = COMPOSITE_NOMUX(CLK_MSCH, "clk_msch", "clk_ddr1x", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(10), 0, 2, DFLAGS,
            RK3568_CLKGATE_CON(4), 2, GFLAGS),
    [CLK24_DDRMON] = GATE(CLK24_DDRMON, "clk24_ddrmon", "xin24m", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(4), 15, GFLAGS),
    [ACLK_GIC_AUDIO] = COMPOSITE_NODIV(ACLK_GIC_AUDIO, "aclk_gic_audio", gpll200_gpll150_gpll100_xin24m_p, RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(10), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(5), 0, GFLAGS),
    [HCLK_GIC_AUDIO] = COMPOSITE_NODIV(HCLK_GIC_AUDIO, "hclk_gic_audio", gpll150_gpll100_gpll75_xin24m_p, RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(10), 10, 2, MFLAGS,
            RK3568_CLKGATE_CON(5), 1, GFLAGS),
    [HCLK_SDMMC_BUFFER] = GATE(HCLK_SDMMC_BUFFER, "hclk_sdmmc_buffer", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(5), 8, GFLAGS),
    [DCLK_SDMMC_BUFFER] = COMPOSITE_NODIV(DCLK_SDMMC_BUFFER, "dclk_sdmmc_buffer", gpll100_gpll75_gpll50_p, 0,
            RK3568_CLKSEL_CON(10), 12, 2, MFLAGS,
            RK3568_CLKGATE_CON(5), 9, GFLAGS),
    [ACLK_GIC600] = GATE(ACLK_GIC600, "aclk_gic600", "aclk_gic_audio", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(5), 4, GFLAGS),
    [ACLK_SPINLOCK] = GATE(ACLK_SPINLOCK, "aclk_spinlock", "aclk_gic_audio", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(5), 7, GFLAGS),
    [HCLK_I2S0_8CH] = GATE(HCLK_I2S0_8CH, "hclk_i2s0_8ch", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(5), 10, GFLAGS),
    [HCLK_I2S1_8CH] = GATE(HCLK_I2S1_8CH, "hclk_i2s1_8ch", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(5), 11, GFLAGS),
    [HCLK_I2S2_2CH] = GATE(HCLK_I2S2_2CH, "hclk_i2s2_2ch", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(5), 12, GFLAGS),
    [HCLK_I2S3_2CH] = GATE(HCLK_I2S3_2CH, "hclk_i2s3_2ch", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(5), 13, GFLAGS),
    [CLK_I2S0_8CH_TX_SRC] = COMPOSITE(CLK_I2S0_8CH_TX_SRC, "clk_i2s0_8ch_tx_src", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(11), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(6), 0, GFLAGS),
    [CLK_I2S0_8CH_TX_FRAC] = COMPOSITE_FRACMUX(CLK_I2S0_8CH_TX_FRAC, "clk_i2s0_8ch_tx_frac", "clk_i2s0_8ch_tx_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(12), 0,
            RK3568_CLKGATE_CON(6), 1, GFLAGS,
            &rk3568_i2s0_8ch_tx_fracmux),
    [MCLK_I2S0_8CH_TX] = GATE(MCLK_I2S0_8CH_TX, "mclk_i2s0_8ch_tx", "clk_i2s0_8ch_tx", 0, RK3568_CLKGATE_CON(6), 2, GFLAGS),
    [I2S0_MCLKOUT_TX] = COMPOSITE_NODIV(I2S0_MCLKOUT_TX, "i2s0_mclkout_tx", i2s0_mclkout_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(11), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(6), 3, GFLAGS),
    [CLK_I2S0_8CH_RX_SRC] = COMPOSITE(CLK_I2S0_8CH_RX_SRC, "clk_i2s0_8ch_rx_src", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(13), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(6), 4, GFLAGS),
    [CLK_I2S0_8CH_RX_FRAC] = COMPOSITE_FRACMUX(CLK_I2S0_8CH_RX_FRAC, "clk_i2s0_8ch_rx_frac", "clk_i2s0_8ch_rx_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(14), 0,
            RK3568_CLKGATE_CON(6), 5, GFLAGS,
            &rk3568_i2s0_8ch_rx_fracmux),
    [MCLK_I2S0_8CH_RX] = GATE(MCLK_I2S0_8CH_RX, "mclk_i2s0_8ch_rx", "clk_i2s0_8ch_rx", 0, RK3568_CLKGATE_CON(6), 6, GFLAGS),
    [I2S0_MCLKOUT_RX] = COMPOSITE_NODIV(I2S0_MCLKOUT_RX, "i2s0_mclkout_rx", i2s0_mclkout_rx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(13), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(6), 7, GFLAGS),
    [CLK_I2S1_8CH_TX_SRC] = COMPOSITE(CLK_I2S1_8CH_TX_SRC, "clk_i2s1_8ch_tx_src", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(15), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(6), 8, GFLAGS),
    [CLK_I2S1_8CH_TX_FRAC] = COMPOSITE_FRACMUX(CLK_I2S1_8CH_TX_FRAC, "clk_i2s1_8ch_tx_frac", "clk_i2s1_8ch_tx_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(16), 0,
            RK3568_CLKGATE_CON(6), 9, GFLAGS,
            &rk3568_i2s1_8ch_tx_fracmux),
    [MCLK_I2S1_8CH_TX] = GATE(MCLK_I2S1_8CH_TX, "mclk_i2s1_8ch_tx", "clk_i2s1_8ch_tx", 0, RK3568_CLKGATE_CON(6), 10, GFLAGS),
    [I2S1_MCLKOUT_TX] = COMPOSITE_NODIV(I2S1_MCLKOUT_TX, "i2s1_mclkout_tx", i2s1_mclkout_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(15), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(6), 11, GFLAGS),
    [CLK_I2S1_8CH_RX_SRC] = COMPOSITE(CLK_I2S1_8CH_RX_SRC, "clk_i2s1_8ch_rx_src", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(17), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(6), 12, GFLAGS),
    [CLK_I2S1_8CH_RX_FRAC] = COMPOSITE_FRACMUX(CLK_I2S1_8CH_RX_FRAC, "clk_i2s1_8ch_rx_frac", "clk_i2s1_8ch_rx_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(18), 0,
            RK3568_CLKGATE_CON(6), 13, GFLAGS,
            &rk3568_i2s1_8ch_rx_fracmux),
    [MCLK_I2S1_8CH_RX] = GATE(MCLK_I2S1_8CH_RX, "mclk_i2s1_8ch_rx", "clk_i2s1_8ch_rx", 0, RK3568_CLKGATE_CON(6), 14, GFLAGS),
    [I2S1_MCLKOUT_RX] = COMPOSITE_NODIV(I2S1_MCLKOUT_RX, "i2s1_mclkout_rx", i2s1_mclkout_rx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(17), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(6), 15, GFLAGS),
    [CLK_I2S2_2CH_SRC] = COMPOSITE(CLK_I2S2_2CH_SRC, "clk_i2s2_2ch_src", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(19), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(7), 0, GFLAGS),
    [CLK_I2S2_2CH_FRAC] = COMPOSITE_FRACMUX(CLK_I2S2_2CH_FRAC, "clk_i2s2_2ch_frac", "clk_i2s2_2ch_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(20), 0,
            RK3568_CLKGATE_CON(7), 1, GFLAGS,
            &rk3568_i2s2_2ch_fracmux),
    [MCLK_I2S2_2CH] = GATE(MCLK_I2S2_2CH, "mclk_i2s2_2ch", "clk_i2s2_2ch", 0, RK3568_CLKGATE_CON(7), 2, GFLAGS),
    [I2S2_MCLKOUT] = COMPOSITE_NODIV(I2S2_MCLKOUT, "i2s2_mclkout", i2s2_mclkout_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(19), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(7), 3, GFLAGS),
    [CLK_I2S3_2CH_TX_SRC] = COMPOSITE(CLK_I2S3_2CH_TX_SRC, "clk_i2s3_2ch_tx_src", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(21), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(7), 4, GFLAGS),
    [CLK_I2S3_2CH_TX_FRAC] = COMPOSITE_FRACMUX(CLK_I2S3_2CH_TX_FRAC, "clk_i2s3_2ch_tx_frac", "clk_i2s3_2ch_tx_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(22), 0,
            RK3568_CLKGATE_CON(7), 5, GFLAGS,
            &rk3568_i2s3_2ch_tx_fracmux),
    [MCLK_I2S3_2CH_TX] = GATE(MCLK_I2S3_2CH_TX, "mclk_i2s3_2ch_tx", "clk_i2s3_2ch_tx", 0, RK3568_CLKGATE_CON(7), 6, GFLAGS),
    [I2S3_MCLKOUT_TX] = COMPOSITE_NODIV(I2S3_MCLKOUT_TX, "i2s3_mclkout_tx", i2s3_mclkout_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(21), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(7), 7, GFLAGS),
    [CLK_I2S3_2CH_RX_SRC] = COMPOSITE(CLK_I2S3_2CH_RX_SRC, "clk_i2s3_2ch_rx_src", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(83), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(7), 8, GFLAGS),
    [CLK_I2S3_2CH_RX_FRAC] = COMPOSITE_FRACMUX(CLK_I2S3_2CH_RX_FRAC, "clk_i2s3_2ch_rx_frac", "clk_i2s3_2ch_rx_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(84), 0,
            RK3568_CLKGATE_CON(7), 9, GFLAGS,
            &rk3568_i2s3_2ch_rx_fracmux),
    [MCLK_I2S3_2CH_RX] = GATE(MCLK_I2S3_2CH_RX, "mclk_i2s3_2ch_rx", "clk_i2s3_2ch_rx", 0, RK3568_CLKGATE_CON(7), 10, GFLAGS),
    [I2S3_MCLKOUT_RX] = COMPOSITE_NODIV(I2S3_MCLKOUT_RX, "i2s3_mclkout_rx", i2s3_mclkout_rx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(83), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(7), 11, GFLAGS),
    [HCLK_PDM] = GATE(HCLK_PDM, "hclk_pdm", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(5), 14, GFLAGS),
    [MCLK_PDM] = COMPOSITE_NODIV(MCLK_PDM, "mclk_pdm", mclk_pdm_p, 0,
            RK3568_CLKSEL_CON(23), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(5), 15, GFLAGS),
    [HCLK_VAD] = GATE(HCLK_VAD, "hclk_vad", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(7), 12, GFLAGS),
    [HCLK_SPDIF_8CH] = GATE(HCLK_SPDIF_8CH, "hclk_spdif_8ch", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(7), 13, GFLAGS),
    [MCLK_SPDIF_8CH_SRC] = COMPOSITE(MCLK_SPDIF_8CH_SRC, "mclk_spdif_8ch_src", cpll_gpll_p, 0,
            RK3568_CLKSEL_CON(23), 14, 1, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(7), 14, GFLAGS),
    [MCLK_SPDIF_8CH_FRAC] = COMPOSITE_FRACMUX(MCLK_SPDIF_8CH_FRAC, "mclk_spdif_8ch_frac", "mclk_spdif_8ch_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(24), 0,
            RK3568_CLKGATE_CON(7), 15, GFLAGS,
            &rk3568_spdif_8ch_fracmux),
    [MCLK_SPDIF_8CH] = &rk3568_spdif_8ch_fracmux.cell,
    [HCLK_AUDPWM] = GATE(HCLK_AUDPWM, "hclk_audpwm", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(8), 0, GFLAGS),
    [SCLK_AUDPWM_SRC] = COMPOSITE(SCLK_AUDPWM_SRC, "sclk_audpwm_src", gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(25), 14, 1, MFLAGS, 0, 6, DFLAGS,
            RK3568_CLKGATE_CON(8), 1, GFLAGS),
    [SCLK_AUDPWM_FRAC] = COMPOSITE_FRACMUX(SCLK_AUDPWM_FRAC, "sclk_audpwm_frac", "sclk_audpwm_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(26), 0,
            RK3568_CLKGATE_CON(8), 2, GFLAGS,
            &rk3568_audpwm_fracmux),
    [SCLK_AUDPWM] = &rk3568_audpwm_fracmux.cell,
    [HCLK_ACDCDIG] = GATE(HCLK_ACDCDIG, "hclk_acdcdig", "hclk_gic_audio", 0, RK3568_CLKGATE_CON(8), 3, GFLAGS),
    [CLK_ACDCDIG_I2C] = COMPOSITE_NODIV(CLK_ACDCDIG_I2C, "clk_acdcdig_i2c", clk_i2c_p, 0,
            RK3568_CLKSEL_CON(23), 10, 2, MFLAGS,
            RK3568_CLKGATE_CON(8), 4, GFLAGS),
    [CLK_ACDCDIG_DAC] = GATE(CLK_ACDCDIG_DAC, "clk_acdcdig_dac", "mclk_i2s3_2ch_tx", 0, RK3568_CLKGATE_CON(8), 5, GFLAGS),
    [CLK_ACDCDIG_ADC] = GATE(CLK_ACDCDIG_ADC, "clk_acdcdig_adc", "mclk_i2s3_2ch_rx", 0, RK3568_CLKGATE_CON(8), 6, GFLAGS),
    [ACLK_SECURE_FLASH] = COMPOSITE_NODIV(ACLK_SECURE_FLASH, "aclk_secure_flash", gpll200_gpll150_gpll100_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(27), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(8), 7, GFLAGS),
    [HCLK_SECURE_FLASH] = COMPOSITE_NODIV(HCLK_SECURE_FLASH, "hclk_secure_flash", gpll150_gpll100_gpll75_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(27), 2, 2, MFLAGS,
            RK3568_CLKGATE_CON(8), 8, GFLAGS),
    [ACLK_CRYPTO_NS] = GATE(ACLK_CRYPTO_NS, "aclk_crypto_ns", "aclk_secure_flash", 0, RK3568_CLKGATE_CON(8), 11, GFLAGS),
    [HCLK_CRYPTO_NS] = GATE(HCLK_CRYPTO_NS, "hclk_crypto_ns", "hclk_secure_flash", 0, RK3568_CLKGATE_CON(8), 12, GFLAGS),
    [CLK_CRYPTO_NS_CORE] = COMPOSITE_NODIV(CLK_CRYPTO_NS_CORE, "clk_crypto_ns_core", gpll200_gpll150_gpll100_p, 0,
            RK3568_CLKSEL_CON(27), 4, 2, MFLAGS,
            RK3568_CLKGATE_CON(8), 13, GFLAGS),
    [CLK_CRYPTO_NS_PKA] = COMPOSITE_NODIV(CLK_CRYPTO_NS_PKA, "clk_crypto_ns_pka", gpll300_gpll200_gpll100_p, 0,
            RK3568_CLKSEL_CON(27), 6, 2, MFLAGS,
            RK3568_CLKGATE_CON(8), 14, GFLAGS),
    [CLK_CRYPTO_NS_RNG] = GATE(CLK_CRYPTO_NS_RNG, "clk_crypto_ns_rng", "hclk_secure_flash", 0, RK3568_CLKGATE_CON(8), 15, GFLAGS),
    [HCLK_TRNG_NS] =GATE(HCLK_TRNG_NS, "hclk_trng_ns", "hclk_secure_flash", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(9), 10, GFLAGS),
    [CLK_TRNG_NS] = GATE(CLK_TRNG_NS, "clk_trng_ns", "hclk_secure_flash", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(9), 11, GFLAGS),
    [PCLK_OTPC_NS] = GATE(PCLK_OTPC_NS, "pclk_otpc_ns", "hclk_secure_flash", 0, RK3568_CLKGATE_CON(26), 9, GFLAGS),
    [CLK_OTPC_NS_SBPI] = GATE(CLK_OTPC_NS_SBPI, "clk_otpc_ns_sbpi", "xin24m", 0, RK3568_CLKGATE_CON(26), 10, GFLAGS),
    [CLK_OTPC_NS_USR] = GATE(CLK_OTPC_NS_USR, "clk_otpc_ns_usr", "xin_osc0_half", 0, RK3568_CLKGATE_CON(26), 11, GFLAGS),
    [HCLK_NANDC] = GATE(HCLK_NANDC, "hclk_nandc", "hclk_secure_flash", 0, RK3568_CLKGATE_CON(9), 0, GFLAGS),
    [NCLK_NANDC] = COMPOSITE_NODIV(NCLK_NANDC, "nclk_nandc", clk_nandc_p, 0,
            RK3568_CLKSEL_CON(28), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(9), 1, GFLAGS),

    [HCLK_SFC] = GATE(HCLK_SFC, "hclk_sfc", "hclk_secure_flash", 0, RK3568_CLKGATE_CON(9), 2, GFLAGS),
    [HCLK_SFC_XIP] = GATE(HCLK_SFC_XIP, "hclk_sfc_xip", "hclk_secure_flash", 0, RK3568_CLKGATE_CON(9), 3, GFLAGS),
    [SCLK_SFC] = COMPOSITE_NODIV(SCLK_SFC, "sclk_sfc", sclk_sfc_p, 0,
            RK3568_CLKSEL_CON(28), 4, 3, MFLAGS,
            RK3568_CLKGATE_CON(9), 4, GFLAGS),
    [ACLK_EMMC] = GATE(ACLK_EMMC, "aclk_emmc", "aclk_secure_flash", 0, RK3568_CLKGATE_CON(9), 5, GFLAGS),
    [HCLK_EMMC] = GATE(HCLK_EMMC, "hclk_emmc", "hclk_secure_flash", 0, RK3568_CLKGATE_CON(9), 6, GFLAGS),
    [BCLK_EMMC] = COMPOSITE_NODIV(BCLK_EMMC, "bclk_emmc", gpll200_gpll150_cpll125_p, 0,
            RK3568_CLKSEL_CON(28), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(9), 7, GFLAGS),
    [CCLK_EMMC] = COMPOSITE_NODIV(CCLK_EMMC, "cclk_emmc", cclk_emmc_p, 0,
            RK3568_CLKSEL_CON(28), 12, 3, MFLAGS,
            RK3568_CLKGATE_CON(9), 8, GFLAGS),
    [TCLK_EMMC] =GATE(TCLK_EMMC, "tclk_emmc", "xin24m", 0, RK3568_CLKGATE_CON(9), 9, GFLAGS),
    [ACLK_PIPE] = COMPOSITE_NODIV(ACLK_PIPE, "aclk_pipe", aclk_pipe_p, 0,
            RK3568_CLKSEL_CON(29), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(10), 0, GFLAGS),
    [PCLK_PIPE] = COMPOSITE_NOMUX(PCLK_PIPE, "pclk_pipe", "aclk_pipe", 0,
            RK3568_CLKSEL_CON(29), 4, 4, DFLAGS,
            RK3568_CLKGATE_CON(10), 1, GFLAGS),
    [ACLK_PCIE20_MST] = GATE(ACLK_PCIE20_MST, "aclk_pcie20_mst", "aclk_pipe", 0, RK3568_CLKGATE_CON(12), 0, GFLAGS),
    [ACLK_PCIE20_SLV] = GATE(ACLK_PCIE20_SLV, "aclk_pcie20_slv", "aclk_pipe", 0, RK3568_CLKGATE_CON(12), 1, GFLAGS),
    [ACLK_PCIE20_DBI] = GATE(ACLK_PCIE20_DBI, "aclk_pcie20_dbi", "aclk_pipe", 0, RK3568_CLKGATE_CON(12), 2, GFLAGS),
    [PCLK_PCIE20] = GATE(PCLK_PCIE20, "pclk_pcie20", "pclk_pipe", 0, RK3568_CLKGATE_CON(12), 3, GFLAGS),
    [CLK_PCIE20_AUX_NDFT] = GATE(CLK_PCIE20_AUX_NDFT, "clk_pcie20_aux_ndft", "xin24m", 0, RK3568_CLKGATE_CON(12), 4, GFLAGS),
    [ACLK_PCIE30X1_MST] = GATE(ACLK_PCIE30X1_MST, "aclk_pcie30x1_mst", "aclk_pipe", 0, RK3568_CLKGATE_CON(12), 8, GFLAGS),
    [ACLK_PCIE30X1_SLV] = GATE(ACLK_PCIE30X1_SLV, "aclk_pcie30x1_slv", "aclk_pipe", 0, RK3568_CLKGATE_CON(12), 9, GFLAGS),
    [ACLK_PCIE30X1_DBI] = GATE(ACLK_PCIE30X1_DBI, "aclk_pcie30x1_dbi", "aclk_pipe", 0, RK3568_CLKGATE_CON(12), 10, GFLAGS),
    [PCLK_PCIE30X1] = GATE(PCLK_PCIE30X1, "pclk_pcie30x1", "pclk_pipe", 0, RK3568_CLKGATE_CON(12), 11, GFLAGS),
    [CLK_PCIE30X1_AUX_NDFT] = GATE(CLK_PCIE30X1_AUX_NDFT, "clk_pcie30x1_aux_ndft", "xin24m", 0, RK3568_CLKGATE_CON(12), 12, GFLAGS),
    [ACLK_PCIE30X2_MST] = GATE(ACLK_PCIE30X2_MST, "aclk_pcie30x2_mst", "aclk_pipe", 0, RK3568_CLKGATE_CON(13), 0, GFLAGS),
    [ACLK_PCIE30X2_SLV] = GATE(ACLK_PCIE30X2_SLV, "aclk_pcie30x2_slv", "aclk_pipe", 0, RK3568_CLKGATE_CON(13), 1, GFLAGS),
    [ACLK_PCIE30X2_DBI] = GATE(ACLK_PCIE30X2_DBI, "aclk_pcie30x2_dbi", "aclk_pipe", 0, RK3568_CLKGATE_CON(13), 2, GFLAGS),
    [PCLK_PCIE30X2] = GATE(PCLK_PCIE30X2, "pclk_pcie30x2", "pclk_pipe", 0, RK3568_CLKGATE_CON(13), 3, GFLAGS),
    [CLK_PCIE30X2_AUX_NDFT] = GATE(CLK_PCIE30X2_AUX_NDFT, "clk_pcie30x2_aux_ndft", "xin24m", 0, RK3568_CLKGATE_CON(13), 4, GFLAGS),
    [ACLK_SATA0] = GATE(ACLK_SATA0, "aclk_sata0", "aclk_pipe", 0, RK3568_CLKGATE_CON(11), 0, GFLAGS),
    [CLK_SATA0_PMALIVE] = GATE(CLK_SATA0_PMALIVE, "clk_sata0_pmalive", "gpll_20m", 0, RK3568_CLKGATE_CON(11), 1, GFLAGS),
    [CLK_SATA0_RXOOB] = GATE(CLK_SATA0_RXOOB, "clk_sata0_rxoob", "cpll_50m", 0, RK3568_CLKGATE_CON(11), 2, GFLAGS),
    [ACLK_SATA1] = GATE(ACLK_SATA1, "aclk_sata1", "aclk_pipe", 0, RK3568_CLKGATE_CON(11), 4, GFLAGS),
    [CLK_SATA1_PMALIVE] = GATE(CLK_SATA1_PMALIVE, "clk_sata1_pmalive", "gpll_20m", 0, RK3568_CLKGATE_CON(11), 5, GFLAGS),
    [CLK_SATA1_RXOOB] = GATE(CLK_SATA1_RXOOB, "clk_sata1_rxoob", "cpll_50m", 0, RK3568_CLKGATE_CON(11), 6, GFLAGS),
    [ACLK_SATA2] = GATE(ACLK_SATA2, "aclk_sata2", "aclk_pipe", 0, RK3568_CLKGATE_CON(11), 8, GFLAGS),
    [CLK_SATA2_PMALIVE] = GATE(CLK_SATA2_PMALIVE, "clk_sata2_pmalive", "gpll_20m", 0, RK3568_CLKGATE_CON(11), 9, GFLAGS),
    [CLK_SATA2_RXOOB] = GATE(CLK_SATA2_RXOOB, "clk_sata2_rxoob", "cpll_50m", 0, RK3568_CLKGATE_CON(11), 10, GFLAGS),
    [ACLK_USB3OTG0] = GATE(ACLK_USB3OTG0, "aclk_usb3otg0", "aclk_pipe", 0, RK3568_CLKGATE_CON(10), 8, GFLAGS),
    [CLK_USB3OTG0_REF] = GATE(CLK_USB3OTG0_REF, "clk_usb3otg0_ref", "xin24m", 0, RK3568_CLKGATE_CON(10), 9, GFLAGS),
    [CLK_USB3OTG0_SUSPEND] = COMPOSITE_NODIV(CLK_USB3OTG0_SUSPEND, "clk_usb3otg0_suspend", xin24m_32k_p, 0,
            RK3568_CLKSEL_CON(29), 8, 1, MFLAGS,
            RK3568_CLKGATE_CON(10), 10, GFLAGS),
    [ACLK_USB3OTG1] = GATE(ACLK_USB3OTG1, "aclk_usb3otg1", "aclk_pipe", 0, RK3568_CLKGATE_CON(10), 12, GFLAGS),
    [CLK_USB3OTG1_REF] = GATE(CLK_USB3OTG1_REF, "clk_usb3otg1_ref", "xin24m", 0, RK3568_CLKGATE_CON(10), 13, GFLAGS),
    [CLK_USB3OTG1_SUSPEND] = COMPOSITE_NODIV(CLK_USB3OTG1_SUSPEND, "clk_usb3otg1_suspend", xin24m_32k_p, 0,
            RK3568_CLKSEL_CON(29), 9, 1, MFLAGS,
            RK3568_CLKGATE_CON(10), 14, GFLAGS),
    [CLK_XPCS_EEE] = COMPOSITE_NODIV(CLK_XPCS_EEE, "clk_xpcs_eee", gpll200_cpll125_p, 0,
            RK3568_CLKSEL_CON(29), 13, 1, MFLAGS,
            RK3568_CLKGATE_CON(10), 4, GFLAGS),
    [PCLK_XPCS] = GATE(PCLK_XPCS, "pclk_xpcs", "pclk_pipe", 0, RK3568_CLKGATE_CON(13), 6, GFLAGS),
    [ACLK_PHP] = COMPOSITE_NODIV(ACLK_PHP, "aclk_php", gpll300_gpll200_gpll100_xin24m_p, 0,
            RK3568_CLKSEL_CON(30), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(14), 8, GFLAGS),
    [HCLK_PHP] = COMPOSITE_NODIV(HCLK_PHP, "hclk_php", gpll150_gpll100_gpll75_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(30), 2, 2, MFLAGS,
            RK3568_CLKGATE_CON(14), 9, GFLAGS),
    [PCLK_PHP] = COMPOSITE_NOMUX(PCLK_PHP, "pclk_php", "aclk_php", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(30), 4, 4, DFLAGS,
            RK3568_CLKGATE_CON(14), 10, GFLAGS),
    [HCLK_SDMMC0] = GATE(HCLK_SDMMC0, "hclk_sdmmc0", "hclk_php", 0, RK3568_CLKGATE_CON(15), 0, GFLAGS),
    [CLK_SDMMC0] = COMPOSITE_NODIV(CLK_SDMMC0, "clk_sdmmc0", clk_sdmmc_p, 0,
            RK3568_CLKSEL_CON(30), 8, 3, MFLAGS,
            RK3568_CLKGATE_CON(15), 1, GFLAGS),
    [HCLK_SDMMC1] = GATE(HCLK_SDMMC1, "hclk_sdmmc1", "hclk_php", 0, RK3568_CLKGATE_CON(15), 2, GFLAGS),
    [CLK_SDMMC1] = COMPOSITE_NODIV(CLK_SDMMC1, "clk_sdmmc1", clk_sdmmc_p, 0,
            RK3568_CLKSEL_CON(30), 12, 3, MFLAGS,
            RK3568_CLKGATE_CON(15), 3, GFLAGS),
    [ACLK_GMAC0] = GATE(ACLK_GMAC0, "aclk_gmac0", "aclk_php", 0, RK3568_CLKGATE_CON(15), 5, GFLAGS),
    [PCLK_GMAC0] = GATE(PCLK_GMAC0, "pclk_gmac0", "pclk_php", 0, RK3568_CLKGATE_CON(15), 6, GFLAGS),
    [CLK_MAC0_2TOP] = COMPOSITE_NODIV(CLK_MAC0_2TOP, "clk_mac0_2top", clk_mac_2top_p, 0,
            RK3568_CLKSEL_CON(31), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(15), 7, GFLAGS),
    [CLK_MAC0_OUT] = COMPOSITE_NODIV(CLK_MAC0_OUT, "clk_mac0_out", cpll125_cpll50_cpll25_xin24m_p, 0,
            RK3568_CLKSEL_CON(31), 14, 2, MFLAGS,
            RK3568_CLKGATE_CON(15), 8, GFLAGS),
    [CLK_MAC0_REFOUT] = GATE(CLK_MAC0_REFOUT, "clk_mac0_refout", "clk_mac0_2top", 0, RK3568_CLKGATE_CON(15), 12, GFLAGS),
    [CLK_GMAC0_PTP_REF] = COMPOSITE_NODIV(CLK_GMAC0_PTP_REF, "clk_gmac0_ptp_ref", clk_gmac_ptp_p, 0,
            RK3568_CLKSEL_CON(31), 12, 2, MFLAGS,
            RK3568_CLKGATE_CON(15), 4, GFLAGS),
    [ACLK_USB] = COMPOSITE_NODIV(ACLK_USB, "aclk_usb", gpll300_gpll200_gpll100_xin24m_p, 0,
            RK3568_CLKSEL_CON(32), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(16), 0, GFLAGS),
    [HCLK_USB] = COMPOSITE_NODIV(HCLK_USB, "hclk_usb", gpll150_gpll100_gpll75_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(32), 2, 2, MFLAGS,
            RK3568_CLKGATE_CON(16), 1, GFLAGS),
    [PCLK_USB] = COMPOSITE_NOMUX(PCLK_USB, "pclk_usb", "aclk_usb", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(32), 4, 4, DFLAGS,
            RK3568_CLKGATE_CON(16), 2, GFLAGS),
    [HCLK_USB2HOST0] = GATE(HCLK_USB2HOST0, "hclk_usb2host0", "hclk_usb", 0, RK3568_CLKGATE_CON(16), 12, GFLAGS),
    [HCLK_USB2HOST0_ARB] = GATE(HCLK_USB2HOST0_ARB, "hclk_usb2host0_arb", "hclk_usb", 0, RK3568_CLKGATE_CON(16), 13, GFLAGS),
    [HCLK_USB2HOST1] = GATE(HCLK_USB2HOST1, "hclk_usb2host1", "hclk_usb", 0, RK3568_CLKGATE_CON(16), 14, GFLAGS),
    [HCLK_USB2HOST1_ARB] = GATE(HCLK_USB2HOST1_ARB, "hclk_usb2host1_arb", "hclk_usb", 0, RK3568_CLKGATE_CON(16), 15, GFLAGS),
    [HCLK_SDMMC2] = GATE(HCLK_SDMMC2, "hclk_sdmmc2", "hclk_usb", 0, RK3568_CLKGATE_CON(17), 0, GFLAGS),
    [CLK_SDMMC2] = COMPOSITE_NODIV(CLK_SDMMC2, "clk_sdmmc2", clk_sdmmc_p, 0,
            RK3568_CLKSEL_CON(32), 8, 3, MFLAGS,
            RK3568_CLKGATE_CON(17), 1, GFLAGS),
    [ACLK_GMAC1] = GATE(ACLK_GMAC1, "aclk_gmac1", "aclk_usb", 0, RK3568_CLKGATE_CON(17), 3, GFLAGS),
    [PCLK_GMAC1] = GATE(PCLK_GMAC1, "pclk_gmac1", "pclk_usb", 0, RK3568_CLKGATE_CON(17), 4, GFLAGS),
    [CLK_MAC1_2TOP] = COMPOSITE_NODIV(CLK_MAC1_2TOP, "clk_mac1_2top", clk_mac_2top_p, 0,
            RK3568_CLKSEL_CON(33), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(17), 5, GFLAGS),
    [CLK_MAC1_OUT] = COMPOSITE_NODIV(CLK_MAC1_OUT, "clk_mac1_out", cpll125_cpll50_cpll25_xin24m_p, 0,
            RK3568_CLKSEL_CON(33), 14, 2, MFLAGS,
            RK3568_CLKGATE_CON(17), 6, GFLAGS),
    [CLK_MAC1_REFOUT] = GATE(CLK_MAC1_REFOUT, "clk_mac1_refout", "clk_mac1_2top", 0, RK3568_CLKGATE_CON(17), 10, GFLAGS),
    [CLK_GMAC1_PTP_REF] = COMPOSITE_NODIV(CLK_GMAC1_PTP_REF, "clk_gmac1_ptp_ref", clk_gmac_ptp_p, 0,
            RK3568_CLKSEL_CON(33), 12, 2, MFLAGS,
            RK3568_CLKGATE_CON(17), 2, GFLAGS),
    [ACLK_PERIMID] = COMPOSITE_NODIV(ACLK_PERIMID, "aclk_perimid", gpll300_gpll200_gpll100_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(10), 4, 2, MFLAGS,
            RK3568_CLKGATE_CON(14), 0, GFLAGS),
    [HCLK_PERIMID] = COMPOSITE_NODIV(HCLK_PERIMID, "hclk_perimid", gpll150_gpll100_gpll75_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(10), 6, 2, MFLAGS,
            RK3568_CLKGATE_CON(14), 1, GFLAGS),
    [ACLK_VI] = COMPOSITE_NODIV(ACLK_VI, "aclk_vi", gpll400_gpll300_gpll200_xin24m_p, 0,
            RK3568_CLKSEL_CON(34), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(18), 0, GFLAGS),
    [HCLK_VI] = COMPOSITE_NOMUX(HCLK_VI, "hclk_vi", "aclk_vi", 0,
            RK3568_CLKSEL_CON(34), 4, 4, DFLAGS,
            RK3568_CLKGATE_CON(18), 1, GFLAGS),
    [PCLK_VI] = COMPOSITE_NOMUX(PCLK_VI, "pclk_vi", "aclk_vi", 0,
            RK3568_CLKSEL_CON(34), 8, 4, DFLAGS,
            RK3568_CLKGATE_CON(18), 2, GFLAGS),
    [ACLK_VICAP] = GATE(ACLK_VICAP, "aclk_vicap", "aclk_vi", 0, RK3568_CLKGATE_CON(18), 9, GFLAGS),
    [HCLK_VICAP] = GATE(HCLK_VICAP, "hclk_vicap", "hclk_vi", 0, RK3568_CLKGATE_CON(18), 10, GFLAGS),
    [DCLK_VICAP] = COMPOSITE_NODIV(DCLK_VICAP, "dclk_vicap", cpll333_gpll300_gpll200_p, 0,
            RK3568_CLKSEL_CON(34), 14, 2, MFLAGS,
            RK3568_CLKGATE_CON(18), 11, GFLAGS),
    [ICLK_VICAP_G] = GATE(ICLK_VICAP_G, "iclk_vicap_g", "iclk_vicap", 0, RK3568_CLKGATE_CON(18), 13, GFLAGS),
    [ACLK_ISP] = GATE(ACLK_ISP, "aclk_isp", "aclk_vi", 0, RK3568_CLKGATE_CON(19), 0, GFLAGS),
    [HCLK_ISP] = GATE(HCLK_ISP, "hclk_isp", "hclk_vi", 0, RK3568_CLKGATE_CON(19), 1, GFLAGS),
    [CLK_ISP] = COMPOSITE(CLK_ISP, "clk_isp", cpll_gpll_hpll_p, 0,
            RK3568_CLKSEL_CON(35), 6, 2, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(19), 2, GFLAGS),
    [PCLK_CSI2HOST1] =GATE(PCLK_CSI2HOST1, "pclk_csi2host1", "pclk_vi", 0, RK3568_CLKGATE_CON(19), 4, GFLAGS),
    [CLK_CIF_OUT] = COMPOSITE(CLK_CIF_OUT, "clk_cif_out", gpll_usb480m_xin24m_p, 0,
            RK3568_CLKSEL_CON(35), 14, 2, MFLAGS, 8, 6, DFLAGS,
            RK3568_CLKGATE_CON(19), 8, GFLAGS),
    [CLK_CAM0_OUT] = COMPOSITE(CLK_CAM0_OUT, "clk_cam0_out", gpll_usb480m_xin24m_p, 0,
            RK3568_CLKSEL_CON(36), 6, 2, MFLAGS, 0, 6, DFLAGS,
            RK3568_CLKGATE_CON(19), 9, GFLAGS),
    [CLK_CAM1_OUT] = COMPOSITE(CLK_CAM1_OUT, "clk_cam1_out", gpll_usb480m_xin24m_p, 0,
            RK3568_CLKSEL_CON(36), 14, 2, MFLAGS, 8, 6, DFLAGS,
            RK3568_CLKGATE_CON(19), 10, GFLAGS),
    [ACLK_VO] = COMPOSITE_NODIV(ACLK_VO, "aclk_vo", gpll300_cpll250_gpll100_xin24m_p, 0,
            RK3568_CLKSEL_CON(37), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(20), 0, GFLAGS),
    [HCLK_VO] = COMPOSITE_NOMUX(HCLK_VO, "hclk_vo", "aclk_vo", 0,
            RK3568_CLKSEL_CON(37), 8, 4, DFLAGS,
            RK3568_CLKGATE_CON(20), 1, GFLAGS),
    [PCLK_VO] = COMPOSITE_NOMUX(PCLK_VO, "pclk_vo", "aclk_vo", 0,
            RK3568_CLKSEL_CON(37), 12, 4, DFLAGS,
            RK3568_CLKGATE_CON(20), 2, GFLAGS),
    [ACLK_VOP_PRE] = COMPOSITE(ACLK_VOP_PRE, "aclk_vop_pre", cpll_gpll_hpll_vpll_p, 0,
            RK3568_CLKSEL_CON(38), 6, 2, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(20), 6, GFLAGS),
    [ACLK_VOP] = GATE(ACLK_VOP, "aclk_vop", "aclk_vop_pre", 0, RK3568_CLKGATE_CON(20), 8, GFLAGS),
    [HCLK_VOP] = GATE(HCLK_VOP, "hclk_vop", "hclk_vo", 0, RK3568_CLKGATE_CON(20), 9, GFLAGS),
    [DCLK_VOP0] = COMPOSITE(DCLK_VOP0, "dclk_vop0", hpll_vpll_gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(39), 10, 2, MFLAGS, 0, 8, DFLAGS,
            RK3568_CLKGATE_CON(20), 10, GFLAGS),
    [DCLK_VOP1] = COMPOSITE(DCLK_VOP1, "dclk_vop1", hpll_vpll_gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(40), 10, 2, MFLAGS, 0, 8, DFLAGS,
            RK3568_CLKGATE_CON(20), 11, GFLAGS),
    [DCLK_VOP2] = COMPOSITE(DCLK_VOP2, "dclk_vop2", hpll_vpll_gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(41), 10, 2, MFLAGS, 0, 8, DFLAGS,
            RK3568_CLKGATE_CON(20), 12, GFLAGS),
    [CLK_VOP_PWM] = GATE(CLK_VOP_PWM, "clk_vop_pwm", "xin24m", 0, RK3568_CLKGATE_CON(20), 13, GFLAGS),
    [ACLK_HDCP] = GATE(ACLK_HDCP, "aclk_hdcp", "aclk_vo", 0, RK3568_CLKGATE_CON(21), 0, GFLAGS),
    [HCLK_HDCP] = GATE(HCLK_HDCP, "hclk_hdcp", "hclk_vo", 0, RK3568_CLKGATE_CON(21), 1, GFLAGS),
    [PCLK_HDCP] = GATE(PCLK_HDCP, "pclk_hdcp", "pclk_vo", 0, RK3568_CLKGATE_CON(21), 2, GFLAGS),
    [PCLK_HDMI_HOST] = GATE(PCLK_HDMI_HOST, "pclk_hdmi_host", "pclk_vo", 0, RK3568_CLKGATE_CON(21), 3, GFLAGS),
    [CLK_HDMI_SFR] = GATE(CLK_HDMI_SFR, "clk_hdmi_sfr", "xin24m", 0, RK3568_CLKGATE_CON(21), 4, GFLAGS),
    [PCLK_DSITX_0] = GATE(PCLK_DSITX_0, "pclk_dsitx_0", "pclk_vo", 0, RK3568_CLKGATE_CON(21), 6, GFLAGS),
    [PCLK_DSITX_1] = GATE(PCLK_DSITX_1, "pclk_dsitx_1", "pclk_vo", 0, RK3568_CLKGATE_CON(21), 7, GFLAGS),
    [PCLK_EDP_CTRL] = GATE(PCLK_EDP_CTRL, "pclk_edp_ctrl", "pclk_vo", 0, RK3568_CLKGATE_CON(21), 8, GFLAGS),
    [CLK_EDP_200M] = COMPOSITE_NODIV(CLK_EDP_200M, "clk_edp_200m", gpll200_gpll150_cpll125_p, 0,
            RK3568_CLKSEL_CON(38), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(21), 9, GFLAGS),
    [ACLK_VPU_PRE] = COMPOSITE(ACLK_VPU_PRE, "aclk_vpu_pre", gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(42), 7, 1, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(22), 0, GFLAGS),
    [HCLK_VPU_PRE] =COMPOSITE_NOMUX(HCLK_VPU_PRE, "hclk_vpu_pre", "aclk_vpu_pre", 0,
            RK3568_CLKSEL_CON(42), 8, 4, DFLAGS,
            RK3568_CLKGATE_CON(22), 1, GFLAGS),
    [ACLK_VPU] = GATE(ACLK_VPU, "aclk_vpu", "aclk_vpu_pre", 0, RK3568_CLKGATE_CON(22), 4, GFLAGS),
    [HCLK_VPU] = GATE(HCLK_VPU, "hclk_vpu", "hclk_vpu_pre", 0, RK3568_CLKGATE_CON(22), 5, GFLAGS),
    [ACLK_RGA_PRE] = COMPOSITE_NODIV(ACLK_RGA_PRE, "aclk_rga_pre", gpll300_cpll250_gpll100_xin24m_p, 0,
            RK3568_CLKSEL_CON(43), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(23), 0, GFLAGS),
    [HCLK_RGA_PRE] = COMPOSITE_NOMUX(HCLK_RGA_PRE, "hclk_rga_pre", "aclk_rga_pre", 0,
            RK3568_CLKSEL_CON(43), 8, 4, DFLAGS,
            RK3568_CLKGATE_CON(23), 1, GFLAGS),
    [PCLK_RGA_PRE] = COMPOSITE_NOMUX(PCLK_RGA_PRE, "pclk_rga_pre", "aclk_rga_pre", 0,
            RK3568_CLKSEL_CON(43), 12, 4, DFLAGS,
            RK3568_CLKGATE_CON(22), 12, GFLAGS),
    [ACLK_RGA] = GATE(ACLK_RGA, "aclk_rga", "aclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 4, GFLAGS),
    [HCLK_RGA] = GATE(HCLK_RGA, "hclk_rga", "hclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 5, GFLAGS),
    [CLK_RGA_CORE] = COMPOSITE_NODIV(CLK_RGA_CORE, "clk_rga_core", gpll300_gpll200_gpll100_p, 0,
            RK3568_CLKSEL_CON(43), 2, 2, MFLAGS,
            RK3568_CLKGATE_CON(23), 6, GFLAGS),
    [ACLK_IEP] = GATE(ACLK_IEP, "aclk_iep", "aclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 7, GFLAGS),
    [HCLK_IEP] = GATE(HCLK_IEP, "hclk_iep", "hclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 8, GFLAGS),
    [CLK_IEP_CORE] = COMPOSITE_NODIV(CLK_IEP_CORE, "clk_iep_core", gpll300_gpll200_gpll100_p, 0,
            RK3568_CLKSEL_CON(43), 4, 2, MFLAGS,
            RK3568_CLKGATE_CON(23), 9, GFLAGS),
    [HCLK_EBC] = GATE(HCLK_EBC, "hclk_ebc", "hclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 10, GFLAGS),
    [DCLK_EBC] = COMPOSITE_NODIV(DCLK_EBC, "dclk_ebc", gpll400_cpll333_gpll200_p, 0,
            RK3568_CLKSEL_CON(43), 6, 2, MFLAGS,
            RK3568_CLKGATE_CON(23), 11, GFLAGS),
    [ACLK_JDEC] = GATE(ACLK_JDEC, "aclk_jdec", "aclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 12, GFLAGS),
    [HCLK_JDEC] = GATE(HCLK_JDEC, "hclk_jdec", "hclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 13, GFLAGS),
    [ACLK_JENC] = GATE(ACLK_JENC, "aclk_jenc", "aclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 14, GFLAGS),
    [HCLK_JENC] = GATE(HCLK_JENC, "hclk_jenc", "hclk_rga_pre", 0, RK3568_CLKGATE_CON(23), 15, GFLAGS),
    [PCLK_EINK] = GATE(PCLK_EINK, "pclk_eink", "pclk_rga_pre", 0, RK3568_CLKGATE_CON(22), 14, GFLAGS),
    [HCLK_EINK] = GATE(HCLK_EINK, "hclk_eink", "hclk_rga_pre", 0, RK3568_CLKGATE_CON(22), 15, GFLAGS),
    [ACLK_RKVENC_PRE] = COMPOSITE(ACLK_RKVENC_PRE, "aclk_rkvenc_pre", gpll_cpll_npll_p, 0,
            RK3568_CLKSEL_CON(44), 6, 2, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(24), 0, GFLAGS),
    [HCLK_RKVENC_PRE] = COMPOSITE_NOMUX(HCLK_RKVENC_PRE, "hclk_rkvenc_pre", "aclk_rkvenc_pre", 0,
            RK3568_CLKSEL_CON(44), 8, 4, DFLAGS,
            RK3568_CLKGATE_CON(24), 1, GFLAGS),
    [ACLK_RKVENC] = GATE(ACLK_RKVENC, "aclk_rkvenc", "aclk_rkvenc_pre", 0, RK3568_CLKGATE_CON(24), 6, GFLAGS),
    [HCLK_RKVENC] = GATE(HCLK_RKVENC, "hclk_rkvenc", "hclk_rkvenc_pre", 0, RK3568_CLKGATE_CON(24), 7, GFLAGS),
    [CLK_RKVENC_CORE] = COMPOSITE(CLK_RKVENC_CORE, "clk_rkvenc_core", gpll_cpll_npll_vpll_p, 0,
            RK3568_CLKSEL_CON(45), 14, 2, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(24), 8, GFLAGS),
    [ACLK_RKVDEC_PRE] = COMPOSITE(ACLK_RKVDEC_PRE, "aclk_rkvdec_pre", aclk_rkvdec_pre_p, 0,
            RK3568_CLKSEL_CON(47), 7, 1, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(25), 0, GFLAGS),
    [HCLK_RKVDEC_PRE] = COMPOSITE_NOMUX(HCLK_RKVDEC_PRE, "hclk_rkvdec_pre", "aclk_rkvdec_pre", 0,
            RK3568_CLKSEL_CON(47), 8, 4, DFLAGS,
            RK3568_CLKGATE_CON(25), 1, GFLAGS),
    [ACLK_RKVDEC] = GATE(ACLK_RKVDEC, "aclk_rkvdec", "aclk_rkvdec_pre", 0, RK3568_CLKGATE_CON(25), 4, GFLAGS),
    [HCLK_RKVDEC] = GATE(HCLK_RKVDEC, "hclk_rkvdec", "hclk_rkvdec_pre", 0, RK3568_CLKGATE_CON(25), 5, GFLAGS),
    [CLK_RKVDEC_CA] = COMPOSITE(CLK_RKVDEC_CA, "clk_rkvdec_ca", gpll_cpll_npll_vpll_p, 0,
            RK3568_CLKSEL_CON(48), 6, 2, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(25), 6, GFLAGS),
    [CLK_RKVDEC_CORE] = COMPOSITE(CLK_RKVDEC_CORE, "clk_rkvdec_core", clk_rkvdec_core_p, 0,
            RK3568_CLKSEL_CON(49), 14, 2, MFLAGS, 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(25), 7, GFLAGS),
    [CLK_RKVDEC_HEVC_CA] = COMPOSITE(CLK_RKVDEC_HEVC_CA, "clk_rkvdec_hevc_ca", gpll_cpll_npll_vpll_p, 0,
            RK3568_CLKSEL_CON(49), 6, 2, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(25), 8, GFLAGS),
    [ACLK_BUS] = COMPOSITE_NODIV(ACLK_BUS, "aclk_bus", gpll200_gpll150_gpll100_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(50), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(26), 0, GFLAGS),
    [PCLK_BUS] = COMPOSITE_NODIV(PCLK_BUS, "pclk_bus", gpll100_gpll75_cpll50_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(50), 4, 2, MFLAGS,
            RK3568_CLKGATE_CON(26), 1, GFLAGS),
    [PCLK_TSADC] = GATE(PCLK_TSADC, "pclk_tsadc", "pclk_bus", 0, RK3568_CLKGATE_CON(26), 4, GFLAGS),
    [CLK_TSADC_TSEN] = COMPOSITE(CLK_TSADC_TSEN, "clk_tsadc_tsen", xin24m_gpll100_cpll100_p, 0,
            RK3568_CLKSEL_CON(51), 4, 2, MFLAGS, 0, 3, DFLAGS,
            RK3568_CLKGATE_CON(26), 5, GFLAGS),
    [CLK_TSADC] = COMPOSITE_NOMUX(CLK_TSADC, "clk_tsadc", "clk_tsadc_tsen", 0,
            RK3568_CLKSEL_CON(51), 8, 7, DFLAGS,
            RK3568_CLKGATE_CON(26), 6, GFLAGS),
    [PCLK_SARADC] = GATE(PCLK_SARADC, "pclk_saradc", "pclk_bus", 0, RK3568_CLKGATE_CON(26), 7, GFLAGS),
    [CLK_SARADC] = GATE(CLK_SARADC, "clk_saradc", "xin24m", 0, RK3568_CLKGATE_CON(26), 8, GFLAGS),
    [PCLK_SCR] = GATE(PCLK_SCR, "pclk_scr", "pclk_bus", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(26), 12, GFLAGS),
    [PCLK_WDT_NS] = GATE(PCLK_WDT_NS, "pclk_wdt_ns", "pclk_bus", 0, RK3568_CLKGATE_CON(26), 13, GFLAGS),
    [TCLK_WDT_NS] = GATE(TCLK_WDT_NS, "tclk_wdt_ns", "xin24m", 0, RK3568_CLKGATE_CON(26), 14, GFLAGS),
    [ACLK_MCU] = GATE(ACLK_MCU, "aclk_mcu", "aclk_bus", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(32), 13, GFLAGS),
    [PCLK_INTMUX] = GATE(PCLK_INTMUX, "pclk_intmux", "pclk_bus", RT_CLK_F_IGNORE_UNUSED, RK3568_CLKGATE_CON(32), 14, GFLAGS),
    [PCLK_MAILBOX] = GATE(PCLK_MAILBOX, "pclk_mailbox", "pclk_bus", 0, RK3568_CLKGATE_CON(32), 15, GFLAGS),
    [PCLK_UART1] = GATE(PCLK_UART1, "pclk_uart1", "pclk_bus", 0, RK3568_CLKGATE_CON(27), 12, GFLAGS),
    [CLK_UART1_SRC] = COMPOSITE(CLK_UART1_SRC, "clk_uart1_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(52), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(27), 13, GFLAGS),
    [CLK_UART1_FRAC] = COMPOSITE_FRACMUX(CLK_UART1_FRAC, "clk_uart1_frac", "clk_uart1_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(53), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(27), 14, GFLAGS,
            &rk3568_uart1_fracmux),
    [SCLK_UART1] = GATE(SCLK_UART1, "sclk_uart1", "sclk_uart1_mux", 0, RK3568_CLKGATE_CON(27), 15, GFLAGS),
    [PCLK_UART2] = GATE(PCLK_UART2, "pclk_uart2", "pclk_bus", 0, RK3568_CLKGATE_CON(28), 0, GFLAGS),
    [CLK_UART2_SRC] = COMPOSITE(CLK_UART2_SRC, "clk_uart2_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(54), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(28), 1, GFLAGS),
    [CLK_UART2_FRAC] = COMPOSITE_FRACMUX(CLK_UART2_FRAC, "clk_uart2_frac", "clk_uart2_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(55), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(28), 2, GFLAGS,
            &rk3568_uart2_fracmux),
    [SCLK_UART2] = GATE(SCLK_UART2, "sclk_uart2", "sclk_uart2_mux", 0, RK3568_CLKGATE_CON(28), 3, GFLAGS),
    [PCLK_UART3] = GATE(PCLK_UART3, "pclk_uart3", "pclk_bus", 0, RK3568_CLKGATE_CON(28), 4, GFLAGS),
    [CLK_UART3_SRC] = COMPOSITE(CLK_UART3_SRC, "clk_uart3_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(56), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(28), 5, GFLAGS),
    [CLK_UART3_FRAC] = COMPOSITE_FRACMUX(CLK_UART3_FRAC, "clk_uart3_frac", "clk_uart3_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(57), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(28), 6, GFLAGS,
            &rk3568_uart3_fracmux),
    [SCLK_UART3] = GATE(SCLK_UART3, "sclk_uart3", "sclk_uart3_mux", 0, RK3568_CLKGATE_CON(28), 7, GFLAGS),
    [PCLK_UART4] = GATE(PCLK_UART4, "pclk_uart4", "pclk_bus", 0, RK3568_CLKGATE_CON(28), 8, GFLAGS),
    [CLK_UART4_SRC] = COMPOSITE(CLK_UART4_SRC, "clk_uart4_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(58), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(28), 9, GFLAGS),
    [CLK_UART4_FRAC] = COMPOSITE_FRACMUX(CLK_UART4_FRAC, "clk_uart4_frac", "clk_uart4_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(59), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(28), 10, GFLAGS,
            &rk3568_uart4_fracmux),
    [SCLK_UART4] = GATE(SCLK_UART4, "sclk_uart4", "sclk_uart4_mux", 0, RK3568_CLKGATE_CON(28), 11, GFLAGS),
    [PCLK_UART5] = GATE(PCLK_UART5, "pclk_uart5", "pclk_bus", 0, RK3568_CLKGATE_CON(28), 12, GFLAGS),
    [CLK_UART5_SRC] = COMPOSITE(CLK_UART5_SRC, "clk_uart5_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(60), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(28), 13, GFLAGS),
    [CLK_UART5_FRAC] = COMPOSITE_FRACMUX(CLK_UART5_FRAC, "clk_uart5_frac", "clk_uart5_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(61), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(28), 14, GFLAGS,
            &rk3568_uart5_fracmux),
    [SCLK_UART5] = GATE(SCLK_UART5, "sclk_uart5", "sclk_uart5_mux", 0, RK3568_CLKGATE_CON(28), 15, GFLAGS),
    [PCLK_UART6] =GATE(PCLK_UART6, "pclk_uart6", "pclk_bus", 0, RK3568_CLKGATE_CON(29), 0, GFLAGS),
    [CLK_UART6_SRC] = COMPOSITE(CLK_UART6_SRC, "clk_uart6_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(62), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(29), 1, GFLAGS),
    [CLK_UART6_FRAC] = COMPOSITE_FRACMUX(CLK_UART6_FRAC, "clk_uart6_frac", "clk_uart6_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(63), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(29), 2, GFLAGS,
            &rk3568_uart6_fracmux),
    [SCLK_UART6] = GATE(SCLK_UART6, "sclk_uart6", "sclk_uart6_mux", 0, RK3568_CLKGATE_CON(29), 3, GFLAGS),
    [PCLK_UART7] = GATE(PCLK_UART7, "pclk_uart7", "pclk_bus", 0, RK3568_CLKGATE_CON(29), 4, GFLAGS),
    [CLK_UART7_SRC] = COMPOSITE(CLK_UART7_SRC, "clk_uart7_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(64), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(29), 5, GFLAGS),
    [CLK_UART7_FRAC] = COMPOSITE_FRACMUX(CLK_UART7_FRAC, "clk_uart7_frac", "clk_uart7_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(65), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(29), 6, GFLAGS,
            &rk3568_uart7_fracmux),
    [SCLK_UART7] = GATE(SCLK_UART7, "sclk_uart7", "sclk_uart7_mux", 0, RK3568_CLKGATE_CON(29), 7, GFLAGS),
    [PCLK_UART8] = GATE(PCLK_UART8, "pclk_uart8", "pclk_bus", 0, RK3568_CLKGATE_CON(29), 8, GFLAGS),
    [CLK_UART8_SRC] = COMPOSITE(CLK_UART8_SRC, "clk_uart8_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(66), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(29), 9, GFLAGS),
    [CLK_UART8_FRAC] = COMPOSITE_FRACMUX(CLK_UART8_FRAC, "clk_uart8_frac", "clk_uart8_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(67), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(29), 10, GFLAGS,
            &rk3568_uart8_fracmux),
    [SCLK_UART8] = GATE(SCLK_UART8, "sclk_uart8", "sclk_uart8_mux", 0, RK3568_CLKGATE_CON(29), 11, GFLAGS),
    [PCLK_UART9] =GATE(PCLK_UART9, "pclk_uart9", "pclk_bus", 0, RK3568_CLKGATE_CON(29), 12, GFLAGS),
    [CLK_UART9_SRC] =COMPOSITE(CLK_UART9_SRC, "clk_uart9_src", gpll_cpll_usb480m_p, 0,
            RK3568_CLKSEL_CON(68), 8, 2, MFLAGS, 0, 7, DFLAGS,
            RK3568_CLKGATE_CON(29), 13, GFLAGS),
    [CLK_UART9_FRAC] =COMPOSITE_FRACMUX(CLK_UART9_FRAC, "clk_uart9_frac", "clk_uart9_src", RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(69), CLK_FRAC_DIVIDER_NO_LIMIT,
            RK3568_CLKGATE_CON(29), 14, GFLAGS,
            &rk3568_uart9_fracmux),
    [SCLK_UART9] =GATE(SCLK_UART9, "sclk_uart9", "sclk_uart9_mux", 0, RK3568_CLKGATE_CON(29), 15, GFLAGS),
    [PCLK_CAN0] =GATE(PCLK_CAN0, "pclk_can0", "pclk_bus", 0, RK3568_CLKGATE_CON(27), 5, GFLAGS),
    [CLK_CAN0] =COMPOSITE(CLK_CAN0, "clk_can0", gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(70), 7, 1, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(27), 6, GFLAGS),
    [PCLK_CAN1] = GATE(PCLK_CAN1, "pclk_can1", "pclk_bus", 0, RK3568_CLKGATE_CON(27), 7, GFLAGS),
    [CLK_CAN1] = COMPOSITE(CLK_CAN1, "clk_can1", gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(70), 15, 1, MFLAGS, 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(27), 8, GFLAGS),
    [PCLK_CAN2] = GATE(PCLK_CAN2, "pclk_can2", "pclk_bus", 0, RK3568_CLKGATE_CON(27), 9, GFLAGS),
    [CLK_CAN2] = COMPOSITE(CLK_CAN2, "clk_can2", gpll_cpll_p, 0,
            RK3568_CLKSEL_CON(71), 7, 1, MFLAGS, 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(27), 10, GFLAGS),
    [CLK_I2C] = COMPOSITE_NODIV(CLK_I2C, "clk_i2c", clk_i2c_p, 0,
            RK3568_CLKSEL_CON(71), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(32), 10, GFLAGS),
    [PCLK_I2C1] = GATE(PCLK_I2C1, "pclk_i2c1", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 0, GFLAGS),
    [CLK_I2C1] = GATE(CLK_I2C1, "clk_i2c1", "clk_i2c", 0, RK3568_CLKGATE_CON(30), 1, GFLAGS),
    [PCLK_I2C2] = GATE(PCLK_I2C2, "pclk_i2c2", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 2, GFLAGS),
    [CLK_I2C2] = GATE(CLK_I2C2, "clk_i2c2", "clk_i2c", 0, RK3568_CLKGATE_CON(30), 3, GFLAGS),
    [PCLK_I2C3] = GATE(PCLK_I2C3, "pclk_i2c3", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 4, GFLAGS),
    [CLK_I2C3] = GATE(CLK_I2C3, "clk_i2c3", "clk_i2c", 0, RK3568_CLKGATE_CON(30), 5, GFLAGS),
    [PCLK_I2C4] = GATE(PCLK_I2C4, "pclk_i2c4", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 6, GFLAGS),
    [CLK_I2C4] = GATE(CLK_I2C4, "clk_i2c4", "clk_i2c", 0, RK3568_CLKGATE_CON(30), 7, GFLAGS),
    [PCLK_I2C5] = GATE(PCLK_I2C5, "pclk_i2c5", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 8, GFLAGS),
    [CLK_I2C5] = GATE(CLK_I2C5, "clk_i2c5", "clk_i2c", 0, RK3568_CLKGATE_CON(30), 9, GFLAGS),
    [PCLK_SPI0] = GATE(PCLK_SPI0, "pclk_spi0", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 10, GFLAGS),
    [CLK_SPI0] = COMPOSITE_NODIV(CLK_SPI0, "clk_spi0", gpll200_xin24m_cpll100_p, 0,
            RK3568_CLKSEL_CON(72), 0, 1, MFLAGS,
            RK3568_CLKGATE_CON(30), 11, GFLAGS),
    [PCLK_SPI1] = GATE(PCLK_SPI1, "pclk_spi1", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 12, GFLAGS),
    [CLK_SPI1] = COMPOSITE_NODIV(CLK_SPI1, "clk_spi1", gpll200_xin24m_cpll100_p, 0,
            RK3568_CLKSEL_CON(72), 2, 1, MFLAGS,
            RK3568_CLKGATE_CON(30), 13, GFLAGS),
    [PCLK_SPI2] = GATE(PCLK_SPI2, "pclk_spi2", "pclk_bus", 0, RK3568_CLKGATE_CON(30), 14, GFLAGS),
    [CLK_SPI2] = COMPOSITE_NODIV(CLK_SPI2, "clk_spi2", gpll200_xin24m_cpll100_p, 0,
            RK3568_CLKSEL_CON(72), 4, 1, MFLAGS,
            RK3568_CLKGATE_CON(30), 15, GFLAGS),
    [PCLK_SPI3] = GATE(PCLK_SPI3, "pclk_spi3", "pclk_bus", 0, RK3568_CLKGATE_CON(31), 0, GFLAGS),
    [CLK_SPI3] = COMPOSITE_NODIV(CLK_SPI3, "clk_spi3", gpll200_xin24m_cpll100_p, 0,
            RK3568_CLKSEL_CON(72), 6, 1, MFLAGS, RK3568_CLKGATE_CON(31), 1, GFLAGS),
    [PCLK_PWM1] = GATE(PCLK_PWM1, "pclk_pwm1", "pclk_bus", 0, RK3568_CLKGATE_CON(31), 10, GFLAGS),
    [CLK_PWM1] = COMPOSITE_NODIV(CLK_PWM1, "clk_pwm1", gpll100_xin24m_cpll100_p, 0,
            RK3568_CLKSEL_CON(72), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(31), 11, GFLAGS),
    [CLK_PWM1_CAPTURE] = GATE(CLK_PWM1_CAPTURE, "clk_pwm1_capture", "xin24m", 0, RK3568_CLKGATE_CON(31), 12, GFLAGS),
    [PCLK_PWM2] = GATE(PCLK_PWM2, "pclk_pwm2", "pclk_bus", 0, RK3568_CLKGATE_CON(31), 13, GFLAGS),
    [CLK_PWM2] = COMPOSITE_NODIV(CLK_PWM2, "clk_pwm2", gpll100_xin24m_cpll100_p, 0,
            RK3568_CLKSEL_CON(72), 10, 2, MFLAGS,
            RK3568_CLKGATE_CON(31), 14, GFLAGS),
    [CLK_PWM2_CAPTURE] = GATE(CLK_PWM2_CAPTURE, "clk_pwm2_capture", "xin24m", 0, RK3568_CLKGATE_CON(31), 15, GFLAGS),
    [PCLK_PWM3] = GATE(PCLK_PWM3, "pclk_pwm3", "pclk_bus", 0, RK3568_CLKGATE_CON(32), 0, GFLAGS),
    [CLK_PWM3] = COMPOSITE_NODIV(CLK_PWM3, "clk_pwm3", gpll100_xin24m_cpll100_p, 0,
            RK3568_CLKSEL_CON(72), 12, 2, MFLAGS,
            RK3568_CLKGATE_CON(32), 1, GFLAGS),
    [CLK_PWM3_CAPTURE] = GATE(CLK_PWM3_CAPTURE, "clk_pwm3_capture", "xin24m", 0, RK3568_CLKGATE_CON(32), 2, GFLAGS),
    [DBCLK_GPIO] = COMPOSITE_NODIV(DBCLK_GPIO, "dbclk_gpio", xin24m_32k_p, 0,
            RK3568_CLKSEL_CON(72), 14, 1, MFLAGS,
            RK3568_CLKGATE_CON(32), 11, GFLAGS),
    [PCLK_GPIO1] = GATE(PCLK_GPIO1, "pclk_gpio1", "pclk_bus", 0, RK3568_CLKGATE_CON(31), 2, GFLAGS),
    [DBCLK_GPIO1] = GATE(DBCLK_GPIO1, "dbclk_gpio1", "dbclk_gpio", 0, RK3568_CLKGATE_CON(31), 3, GFLAGS),
    [PCLK_GPIO2] = GATE(PCLK_GPIO2, "pclk_gpio2", "pclk_bus", 0, RK3568_CLKGATE_CON(31), 4, GFLAGS),
    [DBCLK_GPIO2] = GATE(DBCLK_GPIO2, "dbclk_gpio2", "dbclk_gpio", 0, RK3568_CLKGATE_CON(31), 5, GFLAGS),
    [PCLK_GPIO3] = GATE(PCLK_GPIO3, "pclk_gpio3", "pclk_bus", 0, RK3568_CLKGATE_CON(31), 6, GFLAGS),
    [DBCLK_GPIO3] = GATE(DBCLK_GPIO3, "dbclk_gpio3", "dbclk_gpio", 0, RK3568_CLKGATE_CON(31), 7, GFLAGS),
    [PCLK_GPIO4] = GATE(PCLK_GPIO4, "pclk_gpio4", "pclk_bus", 0, RK3568_CLKGATE_CON(31), 8, GFLAGS),
    [DBCLK_GPIO4] = GATE(DBCLK_GPIO4, "dbclk_gpio4", "dbclk_gpio", 0, RK3568_CLKGATE_CON(31), 9, GFLAGS),
    [PCLK_TIMER] = GATE(PCLK_TIMER, "pclk_timer", "pclk_bus", 0, RK3568_CLKGATE_CON(32), 3, GFLAGS),
    [CLK_TIMER0] = GATE(CLK_TIMER0, "clk_timer0", "xin24m", 0, RK3568_CLKGATE_CON(32), 4, GFLAGS),
    [CLK_TIMER1] = GATE(CLK_TIMER1, "clk_timer1", "xin24m", 0, RK3568_CLKGATE_CON(32), 5, GFLAGS),
    [CLK_TIMER2] = GATE(CLK_TIMER2, "clk_timer2", "xin24m", 0, RK3568_CLKGATE_CON(32), 6, GFLAGS),
    [CLK_TIMER3] = GATE(CLK_TIMER3, "clk_timer3", "xin24m", 0, RK3568_CLKGATE_CON(32), 7, GFLAGS),
    [CLK_TIMER4] = GATE(CLK_TIMER4, "clk_timer4", "xin24m", 0, RK3568_CLKGATE_CON(32), 8, GFLAGS),
    [CLK_TIMER5] = GATE(CLK_TIMER5, "clk_timer5", "xin24m", 0, RK3568_CLKGATE_CON(32), 9, GFLAGS),
    [ACLK_TOP_HIGH] = COMPOSITE_NODIV(ACLK_TOP_HIGH, "aclk_top_high", cpll500_gpll400_gpll300_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(73), 0, 2, MFLAGS,
            RK3568_CLKGATE_CON(33), 0, GFLAGS),
    [ACLK_TOP_LOW] = COMPOSITE_NODIV(ACLK_TOP_LOW, "aclk_top_low", gpll400_gpll300_gpll200_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(73), 4, 2, MFLAGS,
            RK3568_CLKGATE_CON(33), 1, GFLAGS),
    [HCLK_TOP] = COMPOSITE_NODIV(HCLK_TOP, "hclk_top", gpll150_gpll100_gpll75_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(73), 8, 2, MFLAGS,
            RK3568_CLKGATE_CON(33), 2, GFLAGS),
    [PCLK_TOP] = COMPOSITE_NODIV(PCLK_TOP, "pclk_top", gpll100_gpll75_cpll50_xin24m_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(73), 12, 2, MFLAGS,
            RK3568_CLKGATE_CON(33), 3, GFLAGS),
    [PCLK_PCIE30PHY] = GATE(PCLK_PCIE30PHY, "pclk_pcie30phy", "pclk_top", 0, RK3568_CLKGATE_CON(33), 8, GFLAGS),
    [CLK_OPTC_ARB] = COMPOSITE_NODIV(CLK_OPTC_ARB, "clk_optc_arb", xin24m_cpll100_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(73), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(33), 9, GFLAGS),
    [PCLK_MIPICSIPHY] = GATE(PCLK_MIPICSIPHY, "pclk_mipicsiphy", "pclk_top", 0, RK3568_CLKGATE_CON(33), 13, GFLAGS),
    [PCLK_MIPIDSIPHY0] = GATE(PCLK_MIPIDSIPHY0, "pclk_mipidsiphy0", "pclk_top", 0, RK3568_CLKGATE_CON(33), 14, GFLAGS),
    [PCLK_MIPIDSIPHY1] = GATE(PCLK_MIPIDSIPHY1, "pclk_mipidsiphy1", "pclk_top", 0, RK3568_CLKGATE_CON(33), 15, GFLAGS),
    [PCLK_PIPEPHY0] = GATE(PCLK_PIPEPHY0, "pclk_pipephy0", "pclk_top", 0, RK3568_CLKGATE_CON(34), 4, GFLAGS),
    [PCLK_PIPEPHY1] = GATE(PCLK_PIPEPHY1, "pclk_pipephy1", "pclk_top", 0, RK3568_CLKGATE_CON(34), 5, GFLAGS),
    [PCLK_PIPEPHY2] = GATE(PCLK_PIPEPHY2, "pclk_pipephy2", "pclk_top", 0, RK3568_CLKGATE_CON(34), 6, GFLAGS),
    [PCLK_CPU_BOOST] = GATE(PCLK_CPU_BOOST, "pclk_cpu_boost", "pclk_top", 0, RK3568_CLKGATE_CON(34), 11, GFLAGS),
    [CLK_CPU_BOOST] = GATE(CLK_CPU_BOOST, "clk_cpu_boost", "xin24m", 0, RK3568_CLKGATE_CON(34), 12, GFLAGS),
    [PCLK_OTPPHY] = GATE(PCLK_OTPPHY, "pclk_otpphy", "pclk_top", 0, RK3568_CLKGATE_CON(34), 13, GFLAGS),
    [SCLK_GMAC0] = MUX(SCLK_GMAC0, "clk_gmac0", mux_gmac0_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(31), 2, 1, MFLAGS),
    [SCLK_GMAC0_RGMII_SPEED] = MUX(SCLK_GMAC0_RGMII_SPEED, "clk_gmac0_rgmii_speed", mux_gmac0_rgmii_speed_p, 0,
            RK3568_CLKSEL_CON(31), 4, 2, MFLAGS),
    [SCLK_GMAC0_RMII_SPEED] = MUX(SCLK_GMAC0_RMII_SPEED, "clk_gmac0_rmii_speed", mux_gmac0_rmii_speed_p, 0,
            RK3568_CLKSEL_CON(31), 3, 1, MFLAGS),
    [SCLK_GMAC0_RX_TX] = MUX(SCLK_GMAC0_RX_TX, "clk_gmac0_rx_tx", mux_gmac0_rx_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(31), 0, 2, MFLAGS),
    [SCLK_GMAC1] = MUX(SCLK_GMAC1, "clk_gmac1", mux_gmac1_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(33), 2, 1, MFLAGS),
    [SCLK_GMAC1_RGMII_SPEED] = MUX(SCLK_GMAC1_RGMII_SPEED, "clk_gmac1_rgmii_speed", mux_gmac1_rgmii_speed_p, 0,
            RK3568_CLKSEL_CON(33), 4, 2, MFLAGS),
    [SCLK_GMAC1_RMII_SPEED] = MUX(SCLK_GMAC1_RMII_SPEED, "clk_gmac1_rmii_speed", mux_gmac1_rmii_speed_p, 0,
            RK3568_CLKSEL_CON(33), 3, 1, MFLAGS),
    [SCLK_GMAC1_RX_TX] = MUX(SCLK_GMAC1_RX_TX, "clk_gmac1_rx_tx", mux_gmac1_rx_tx_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_CLKSEL_CON(33), 0, 2, MFLAGS),
    [SCLK_SDMMC0_DRV] = MMC(SCLK_SDMMC0_DRV, "sdmmc0_drv", "clk_sdmmc0", RK3568_SDMMC0_CON0, 1),
    [SCLK_SDMMC0_SAMPLE] = MMC(SCLK_SDMMC0_SAMPLE, "sdmmc0_sample", "clk_sdmmc0", RK3568_SDMMC0_CON1, 1),
    [SCLK_SDMMC1_DRV] = MMC(SCLK_SDMMC1_DRV, "sdmmc1_drv", "clk_sdmmc1", RK3568_SDMMC1_CON0, 1),
    [SCLK_SDMMC1_SAMPLE] = MMC(SCLK_SDMMC1_SAMPLE, "sdmmc1_sample", "clk_sdmmc1", RK3568_SDMMC1_CON1, 1),
    [SCLK_SDMMC2_DRV] = MMC(SCLK_SDMMC2_DRV, "sdmmc2_drv", "clk_sdmmc2", RK3568_SDMMC2_CON0, 1),
    [SCLK_SDMMC2_SAMPLE] = MMC(SCLK_SDMMC2_SAMPLE, "sdmmc2_sample", "clk_sdmmc2", RK3568_SDMMC2_CON1, 1),
    [SCLK_EMMC_DRV] = MMC(SCLK_EMMC_DRV, "emmc_drv", "cclk_emmc", RK3568_EMMC_CON0, 1),
    [SCLK_EMMC_SAMPLE] = MMC(SCLK_EMMC_SAMPLE, "emmc_sample", "cclk_emmc", RK3568_EMMC_CON1, 1),
    [PCLK_EDPPHY_GRF] = GATE(PCLK_EDPPHY_GRF, "pclk_edpphy_grf", "pclk_top", 0, RK3568_CLKGATE_CON(34), 14, GFLAGS),
    [CLK_HDMI_CEC] = GATE(CLK_HDMI_CEC, "clk_hdmi_cec", "clk_rtc_32k", 0, RK3568_CLKGATE_CON(21), 5, GFLAGS),
    [CLK_I2S0_8CH_TX] = &rk3568_i2s0_8ch_tx_fracmux.cell,
    [CLK_I2S0_8CH_RX] = &rk3568_i2s0_8ch_rx_fracmux.cell,
    [CLK_I2S1_8CH_TX] = &rk3568_i2s1_8ch_tx_fracmux.cell,
    [CLK_I2S1_8CH_RX] = &rk3568_i2s1_8ch_rx_fracmux.cell,
    [CLK_I2S2_2CH] = &rk3568_i2s2_2ch_fracmux.cell,
    [CLK_I2S3_2CH_TX] = &rk3568_i2s3_2ch_tx_fracmux.cell,
    [CLK_I2S3_2CH_RX] = &rk3568_i2s3_2ch_rx_fracmux.cell,
    [CPLL_500M] = COMPOSITE_NOMUX(CPLL_500M, "cpll_500m", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(78), 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 7, GFLAGS),
    [CPLL_250M] = COMPOSITE_NOMUX(CPLL_250M, "cpll_250m", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(79), 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 9, GFLAGS),
    [CPLL_125M] = COMPOSITE_NOMUX(CPLL_125M, "cpll_125m", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(80), 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 10, GFLAGS),
    [CPLL_62P5M] = COMPOSITE_NOMUX(CPLL_62P5M, "cpll_62p5", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(80), 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 12, GFLAGS),
    [CPLL_50M] = COMPOSITE_NOMUX(CPLL_50M, "cpll_50m", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(81), 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 13, GFLAGS),
    [CPLL_25M] = COMPOSITE_NOMUX(CPLL_25M, "cpll_25m", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(81), 8, 6, DFLAGS,
            RK3568_CLKGATE_CON(35), 14, GFLAGS),
    [CPLL_100M] = COMPOSITE_NOMUX(CPLL_100M, "cpll_100m", "cpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(82), 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 11, GFLAGS),
    [I2S1_MCLKOUT] = MUXGRF(I2S1_MCLKOUT, "i2s1_mclkout", i2s1_mclkout_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_GRF_SOC_CON1, 5, 1, MFLAGS),
    [I2S3_MCLKOUT] = MUXGRF(I2S3_MCLKOUT, "i2s3_mclkout", i2s3_mclkout_p, RT_CLK_F_SET_RATE_PARENT,
            RK3568_GRF_SOC_CON2, 15, 1, MFLAGS),
    [I2S1_MCLK_RX_IOE] = MUXGRF(I2S1_MCLK_RX_IOE, "i2s1_mclk_rx_ioe", i2s1_mclk_rx_ioe_p, 0,
            RK3568_GRF_SOC_CON2, 0, 1, MFLAGS),
    [I2S1_MCLK_TX_IOE] = MUXGRF(I2S1_MCLK_TX_IOE, "i2s1_mclk_tx_ioe", i2s1_mclk_tx_ioe_p, 0,
            RK3568_GRF_SOC_CON2, 1, 1, MFLAGS),
    [I2S2_MCLK_IOE] = MUXGRF(I2S2_MCLK_IOE, "i2s2_mclk_ioe", i2s2_mclk_ioe_p, 0,
            RK3568_GRF_SOC_CON2, 2, 1, MFLAGS),
    [I2S3_MCLK_IOE] = MUXGRF(I2S3_MCLK_IOE, "i2s3_mclk_ioe", i2s3_mclk_ioe_p, 0,
            RK3568_GRF_SOC_CON2, 3, 1, MFLAGS),
    [PCLK_CORE_PVTM] = GATE(PCLK_CORE_PVTM, "pclk_core_pvtm", "pclk_core_pre", 0, RK3568_CLKGATE_CON(1), 9, GFLAGS),

    &rk3568_uart1_fracmux.cell,
    &rk3568_uart2_fracmux.cell,
    &rk3568_uart3_fracmux.cell,
    &rk3568_uart4_fracmux.cell,
    &rk3568_uart5_fracmux.cell,
    &rk3568_uart6_fracmux.cell,
    &rk3568_uart7_fracmux.cell,
    &rk3568_uart8_fracmux.cell,
    &rk3568_uart9_fracmux.cell,

    COMPOSITE_NOMUX(0, "gpll_400m", "gpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(75), 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 0, GFLAGS),
    COMPOSITE_NOMUX(0, "gpll_300m", "gpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(75), 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 1, GFLAGS),
    COMPOSITE_NOMUX(0, "gpll_200m", "gpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(76), 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 2, GFLAGS),
    COMPOSITE_NOMUX(0, "gpll_150m", "gpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(76), 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 3, GFLAGS),
    COMPOSITE_NOMUX(0, "gpll_100m", "gpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(77), 0, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 4, GFLAGS),
    COMPOSITE_NOMUX(0, "gpll_75m", "gpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(77), 8, 5, DFLAGS,
            RK3568_CLKGATE_CON(35), 5, GFLAGS),
    COMPOSITE_NOMUX(0, "gpll_20m", "gpll", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(78), 0, 6, DFLAGS,
            RK3568_CLKGATE_CON(35), 6, GFLAGS),
    COMPOSITE_NOMUX(0, "clk_osc0_div_750k", "xin24m", RT_CLK_F_IGNORE_UNUSED,
            RK3568_CLKSEL_CON(82), 8, 6, DFLAGS,
            RK3568_CLKGATE_CON(35), 15, GFLAGS),
    FACTOR(0, "clk_osc0_div_375k", "clk_osc0_div_750k", 0, 1, 2),
    FACTOR(0, "xin_osc0_half", "xin24m", 0, 1, 2),
    COMPOSITE(0, "sclk_core_src", apll_gpll_npll_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(2), 8, 2, MFLAGS, 0, 4, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(0), 5, GFLAGS),
    COMPOSITE_NODIV(0, "sclk_core", sclk_core_pre_p, RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(2), 15, 1, MFLAGS,
            RK3568_CLKGATE_CON(0), 7, GFLAGS),
    COMPOSITE_NOMUX(0, "atclk_core", "armclk", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(3), 0, 5, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(0), 8, GFLAGS),
    COMPOSITE_NOMUX(0, "gicclk_core", "armclk", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(3), 8, 5, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(0), 9, GFLAGS),
    COMPOSITE_NOMUX(0, "pclk_core_pre", "armclk", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(4), 0, 5, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(0), 10, GFLAGS),
    COMPOSITE_NOMUX(0, "periphclk_core_pre", "armclk", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(4), 8, 5, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(0), 11, GFLAGS),
    COMPOSITE_NOMUX(0, "tsclk_core", "periphclk_core_pre", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(5), 0, 4, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(0), 14, GFLAGS),
    COMPOSITE_NOMUX(0, "cntclk_core", "periphclk_core_pre", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(5), 4, 4, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(0), 15, GFLAGS),
    COMPOSITE_NOMUX(0, "aclk_core", "sclk_core", RT_CLK_F_IS_CRITICAL,
            RK3568_CLKSEL_CON(5), 8, 5, DFLAGS | CLK_DIVIDER_READ_ONLY,
            RK3568_CLKGATE_CON(1), 0, GFLAGS),
    FACTOR(0, "clk_gmac0_tx_div5", "clk_gmac0", 0, 1, 5),
    FACTOR(0, "clk_gmac0_tx_div50", "clk_gmac0", 0, 1, 50),
    FACTOR(0, "clk_gmac0_rx_div2", "clk_gmac0", 0, 1, 2),
    FACTOR(0, "clk_gmac0_rx_div20", "clk_gmac0", 0, 1, 20),
    FACTOR(0, "clk_gmac1_tx_div5", "clk_gmac1", 0, 1, 5),
    FACTOR(0, "clk_gmac1_tx_div50", "clk_gmac1", 0, 1, 50),
    FACTOR(0, "clk_gmac1_rx_div2", "clk_gmac1", 0, 1, 2),
    FACTOR(0, "clk_gmac1_rx_div20", "clk_gmac1", 0, 1, 20),
};

static rt_err_t clk_rk3568_cru_init(struct clk_rk3568_cru *cru)
{
    cru->clk_parent.cells = rk3568_clk_cells;
    cru->clk_parent.cells_nr = RT_ARRAY_SIZE(rk3568_clk_cells);

    return RT_EOK;
}

static rt_err_t clk_rk3568_pmucru_init(struct clk_rk3568_cru *cru)
{
    cru->clk_parent.cells = rk3568_clk_pmu_cells;
    cru->clk_parent.cells_nr = RT_ARRAY_SIZE(rk3568_clk_pmu_cells);

    return RT_EOK;
}

static rt_err_t clk_rk3568_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct clk_rk3568_cru *cru = rt_calloc(1, sizeof(*cru));
    rt_err_t (*init)(struct clk_rk3568_cru *cru) = (void *)pdev->id->data;

    if (!cru)
    {
        return -RT_ENOMEM;
    }

    cru->provider.reg_base = rt_dm_dev_iomap(dev, 0);

    if (!cru->provider.reg_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    cru->provider.grf = rt_syscon_find_by_ofw_phandle(dev->ofw_node, "rockchip,grf");
    cru->provider.pmugrf = rt_syscon_find_by_ofw_phandle(dev->ofw_node, "rockchip,pmugrf");

    cru->clk_parent.dev = dev;

    if ((err = init(cru)))
    {
        goto _fail;
    }

    rockchip_clk_init(&cru->provider, cru->clk_parent.cells, cru->clk_parent.cells_nr);

    if ((err = rt_clk_register(&cru->clk_parent)))
    {
        goto _fail;
    }

    rockchip_clk_setup(&cru->provider, cru->clk_parent.cells, cru->clk_parent.cells_nr);

    if ((err = rockchip_register_softrst(&cru->rstc_parent, dev->ofw_node, RT_NULL,
        cru->provider.reg_base + RK3568_SOFTRST_CON(0), ROCKCHIP_SOFTRST_HIWORD_MASK)))
    {
        goto _clk_unregister;
    }

    rockchip_register_restart_notifier(&cru->provider, RK3568_GLB_SRST_FST, RT_NULL);

    return RT_EOK;

_clk_unregister:
    rt_clk_unregister(&cru->clk_parent);

_fail:
    if (cru->provider.reg_base)
    {
        rt_iounmap(cru->provider.reg_base);
    }

    rt_free(cru);

    return err;
}

static const struct rt_ofw_node_id clk_rk3568_ofw_ids[] =
{
    { .compatible = "rockchip,rk3568-cru", .data = (void *)clk_rk3568_cru_init },
    { .compatible = "rockchip,rk3568-pmucru", .data = (void *)clk_rk3568_pmucru_init },
    { /* sentinel */ }
};

static struct rt_platform_driver clk_rk3568_driver =
{
    .name = "clk-rk3568",
    .ids = clk_rk3568_ofw_ids,

    .probe = clk_rk3568_probe,
};

static int clk_rk3568_register(void)
{
    rt_platform_driver_register(&clk_rk3568_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(clk_rk3568_register);
