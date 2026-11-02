/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "ccu_ddn.h"
#include "ccu_ddr.h"
#include "ccu_mix.h"
#include "ccu_dpll.h"
#include "ccu_pll.h"

#include <k1-cru.h>
#include <dt-bindings/clock/k1x.h>

struct k1x_clk
{
    struct rt_clk_node parent;

    union
    {
        struct
        {
            void *mpmu_base;
            void *apmu_base;
            void *apbc_base;
            void *apbs_base;
            void *ciu_base;
            void *dciu_base;
            void *ddrc_base;
            void *apbc2_base;
            void *rcpu_base;
            void *rcpu2_base;
            void *audpmu_base;
            void *audio_ctrl_base;
        };
        void *mmio[CRU_BASE_TYPE_MAX];
    };
};

static const struct ccu_pll_rate_tbl pll2_rate_tbl[] =
{
    PLL_RATE(3000000000UL, 0x66, 0xdd, 0x50, 0x00, 0x3f, 0xe00000),
    PLL_RATE(3200000000UL, 0x67, 0xdd, 0x50, 0x00, 0x43, 0xeaaaab),
    PLL_RATE(2457600000UL, 0x64, 0xdd, 0x50, 0x00, 0x33, 0x0ccccd),
    PLL_RATE(2800000000UL, 0x66, 0xdd, 0x50, 0x00, 0x3a, 0x155555),
};

static const struct ccu_pll_rate_tbl pll3_rate_tbl[] =
{
    PLL_RATE(1600000000UL, 0x61, 0xcd, 0x50, 0x00, 0x43, 0xeaaaab),
    PLL_RATE(1800000000UL, 0x61, 0xcd, 0x50, 0x00, 0x4b, 0x000000),
    PLL_RATE(2000000000UL, 0x62, 0xdd, 0x50, 0x00, 0x2a, 0xeaaaab),
    PLL_RATE(3000000000UL, 0x66, 0xdd, 0x50, 0x00, 0x3f, 0xe00000),
    PLL_RATE(3200000000UL, 0x67, 0xdd, 0x50, 0x00, 0x43, 0xeaaaab),
    PLL_RATE(2457600000UL, 0x64, 0xdd, 0x50, 0x00, 0x33, 0x0ccccd),
};

static SPACEMIT_CCU_PLL(pll2, "pll2", &pll2_rate_tbl, RT_ARRAY_SIZE(pll2_rate_tbl),
        CRU_BASE_TYPE_APBS, APB_SPARE7_REG, APB_SPARE8_REG, APB_SPARE9_REG,
        MPMU_POSR, POSR_PLL2_LOCK, 1, RT_CLK_F_IGNORE_UNUSED);

static SPACEMIT_CCU_PLL(pll3, "pll3", &pll3_rate_tbl, RT_ARRAY_SIZE(pll3_rate_tbl),
        CRU_BASE_TYPE_APBS, APB_SPARE10_REG, APB_SPARE11_REG, APB_SPARE12_REG,
        MPMU_POSR, POSR_PLL3_LOCK, 1, RT_CLK_F_IGNORE_UNUSED);

/* PLL1 */
static SPACEMIT_CCU_GATE_FACTOR(pll1_d2, "pll1_d2", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(1), RT_BIT(1), 0x0, 2, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d3, "pll1_d3", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(2), RT_BIT(2), 0x0, 3, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d4, "pll1_d4", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(3), RT_BIT(3), 0x0, 4, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d5, "pll1_d5", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(4), RT_BIT(4), 0x0, 5, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d6, "pll1_d6", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(5), RT_BIT(5), 0x0, 6, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d7, "pll1_d7", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(6), RT_BIT(6), 0x0, 7, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d8, "pll1_d8", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(7), RT_BIT(7), 0x0, 8, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d11_223p4, "pll1_d11_223p4", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(15), RT_BIT(15), 0x0, 11, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d13_189, "pll1_d13_189", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(16), RT_BIT(16), 0x0, 13, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d23_106p8, "pll1_d23_106p8", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(20), RT_BIT(20), 0x0, 23, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d64_38p4, "pll1_d64_38p4", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(0), RT_BIT(0), 0x0, 64, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_aud_245p7, "pll1_aud_245p7", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(10), RT_BIT(10), 0x0, 10, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_aud_24p5, "pll1_aud_24p5", "pll1_2457p6_vco",
        CRU_BASE_TYPE_APBS, APB_SPARE2_REG, RT_BIT(11), RT_BIT(11), 0x0, 100, 1, RT_CLK_F_IGNORE_UNUSED);

/* PLL2 */
static SPACEMIT_CCU_GATE_FACTOR(pll2_d1, "pll2_d1", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(0), RT_BIT(0), 0x0, 1, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll2_d2, "pll2_d2", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(1), RT_BIT(1), 0x0, 2, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll2_d3, "pll2_d3", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(2), RT_BIT(2), 0x0, 3, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll2_d4, "pll2_d4", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(3), RT_BIT(3), 0x0, 4, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll2_d5, "pll2_d5", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(4), RT_BIT(4), 0x0, 5, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll2_d6, "pll2_d6", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(5), RT_BIT(5), 0x0, 6, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll2_d7, "pll2_d7", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(6), RT_BIT(6), 0x0, 7, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll2_d8, "pll2_d8", "pll2",
        CRU_BASE_TYPE_APBS, APB_SPARE8_REG, RT_BIT(7), RT_BIT(7), 0x0, 8, 1, RT_CLK_F_IGNORE_UNUSED);

/* PLL3 */
static SPACEMIT_CCU_GATE_FACTOR(pll3_d1, "pll3_d1", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(0), RT_BIT(0), 0x0, 1, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll3_d2, "pll3_d2", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(1), RT_BIT(1), 0x0, 2, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll3_d3, "pll3_d3", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(2), RT_BIT(2), 0x0, 3, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll3_d4, "pll3_d4", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(3), RT_BIT(3), 0x0, 4, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll3_d5, "pll3_d5", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(4), RT_BIT(4), 0x0, 5, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll3_d6, "pll3_d6", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(5), RT_BIT(5), 0x0, 6, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll3_d7, "pll3_d7", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(6), RT_BIT(6), 0x0, 7, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll3_d8, "pll3_d8", "pll3",
        CRU_BASE_TYPE_APBS, APB_SPARE11_REG, RT_BIT(7), RT_BIT(7), 0x0, 8, 1, RT_CLK_F_IGNORE_UNUSED);

/* PLL3_DIV */
static SPACEMIT_CCU_FACTOR(pll3_80, "pll3_80", "pll3_d8", 5, 1);
static SPACEMIT_CCU_FACTOR(pll3_40, "pll3_40", "pll3_d8", 10, 1);
static SPACEMIT_CCU_FACTOR(pll3_20, "pll3_20", "pll3_d8", 20, 1);

/* PLL1_D8 */
static SPACEMIT_CCU_GATE(pll1_d8_307p2, "pll1_d8_307p2", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(13), RT_BIT(13), 0x0, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_FACTOR(pll1_d32_76p8, "pll1_d32_76p8", "pll1_d8_307p2", 4, 1);
static SPACEMIT_CCU_FACTOR(pll1_d40_61p44, "pll1_d40_61p44", "pll1_d8_307p2", 5, 1);
static SPACEMIT_CCU_FACTOR(pll1_d16_153p6, "pll1_d16_153p6", "pll1_d8", 2, 1);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d24_102p4, "pll1_d24_102p4", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(12), RT_BIT(12), 0x0, 3, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d48_51p2, "pll1_d48_51p2", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(7), RT_BIT(7), 0x0, 6, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d48_51p2_ap, "pll1_d48_51p2_ap", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(11), RT_BIT(11), 0x0, 6, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_m3d128_57p6, "pll1_m3d128_57p6", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(8), RT_BIT(8), 0x0, 16, 3, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d96_25p6, "pll1_d96_25p6", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(4), RT_BIT(4), 0x0, 12, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d192_12p8, "pll1_d192_12p8", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(3), RT_BIT(3), 0x0, 24, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d192_12p8_wdt, "pll1_d192_12p8_wdt", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(19), RT_BIT(19), 0x0, 24, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d384_6p4, "pll1_d384_6p4", "pll1_d8",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(2), RT_BIT(2), 0x0, 48, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_FACTOR(pll1_d768_3p2, "pll1_d768_3p2", "pll1_d384_6p4", 2, 1);
static SPACEMIT_CCU_FACTOR(pll1_d1536_1p6, "pll1_d1536_1p6", "pll1_d384_6p4", 4, 1);
static SPACEMIT_CCU_FACTOR(pll1_d3072_0p8, "pll1_d3072_0p8", "pll1_d384_6p4", 8, 1);
/* PLL1_D7 */
static SPACEMIT_CCU_FACTOR(pll1_d7_351p08, "pll1_d7_351p08", "pll1_d7", 1, 1);
/* PLL1_D6 */
static SPACEMIT_CCU_GATE(pll1_d6_409p6, "pll1_d6_409p6", "pll1_d6",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(0), RT_BIT(0), 0x0, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d12_204p8, "pll1_d12_204p8", "pll1_d6",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(5), RT_BIT(5), 0x0, 2, 1, RT_CLK_F_IGNORE_UNUSED);
/* PLL1_D5 */
static SPACEMIT_CCU_GATE(pll1_d5_491p52, "pll1_d5_491p52", "pll1_d5",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(21), RT_BIT(21), 0x0, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d10_245p76, "pll1_d10_245p76", "pll1_d5",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(18), RT_BIT(18), 0x0, 2, 1, RT_CLK_F_IGNORE_UNUSED);
/* PLL1_D4 */
static SPACEMIT_CCU_GATE(pll1_d4_614p4, "pll1_d4_614p4", "pll1_d4",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(15), RT_BIT(15), 0x0, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d52_47p26, "pll1_d52_47p26", "pll1_d4",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(10), RT_BIT(10), 0x0, 13, 1, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_GATE_FACTOR(pll1_d78_31p5, "pll1_d78_31p5", "pll1_d4",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(6), RT_BIT(6), 0x0, 39, 2, RT_CLK_F_IGNORE_UNUSED);
/* PLL1_D3 */
static SPACEMIT_CCU_GATE(pll1_d3_819p2, "pll1_d3_819p2", "pll1_d3",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(14), RT_BIT(14), 0x0, RT_CLK_F_IGNORE_UNUSED);
/* PLL1_D2 */
static SPACEMIT_CCU_GATE(pll1_d2_1228p8, "pll1_d2_1228p8", "pll1_d2",
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(16), RT_BIT(16), 0x0, RT_CLK_F_IGNORE_UNUSED);

/* DPLL */
static const struct ccu_dpll_rate_tbl dpll1_rate_tbl[] =
{
    DPLL_RATE(2400000000UL, 0x00, 0x00, 0x20, 0x2a, 0x32, 0x64, 0xdd, 0x50), /* 5000 ppm */
    DPLL_RATE(2400000000UL, 0x00, 0x3b, 0x20, 0x2a, 0x32, 0x64, 0xdd, 0x50), /* 5000 ppm + pre-setting */
};

static const struct ccu_dpll_rate_tbl dpll2_rate_tbl[] =
{
    DPLL_RATE(3200000000UL, 0x55, 0x55, 0x3d, 0x2a, 0x43, 0x67, 0xdd, 0x50), /* 5000ppm */
};

static SPACEMIT_CCU_DPLL(dpll1, "dpll1", &dpll1_rate_tbl, RT_ARRAY_SIZE(dpll1_rate_tbl),
        CRU_BASE_TYPE_APMU, APMU_DPLL1_CLK_CTRL1, APMU_DPLL1_CLK_CTRL2, 0, RT_CLK_F_IGNORE_UNUSED);

static SPACEMIT_CCU_DPLL(dpll2, "dpll2", &dpll2_rate_tbl, RT_ARRAY_SIZE(dpll2_rate_tbl),
        CRU_BASE_TYPE_APMU, APMU_DPLL2_CLK_CTRL1, APMU_DPLL2_CLK_CTRL2, 0, RT_CLK_F_IGNORE_UNUSED);

static const char *const dfc_lvl_parents[] =
{
    "dpll2", "dpll1"
};

static SPACEMIT_CCU_DIV_MUX(dfc_lvl0, "dfc_lvl0", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL0, 14, 2, 8, 1, 0);
static SPACEMIT_CCU_DIV_MUX(dfc_lvl1, "dfc_lvl1", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL1, 14, 2, 8, 1, 0);
static SPACEMIT_CCU_DIV_MUX(dfc_lvl2, "dfc_lvl2", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL2, 14, 2, 8, 1, 0);
static SPACEMIT_CCU_DIV_MUX(dfc_lvl3, "dfc_lvl3", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL3, 14, 2, 8, 1, 0);
static SPACEMIT_CCU_DIV_MUX(dfc_lvl4, "dfc_lvl4", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL4, 14, 2, 8, 1, 0);
static SPACEMIT_CCU_DIV_MUX(dfc_lvl5, "dfc_lvl5", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL5, 14, 2, 8, 1, 0);
static SPACEMIT_CCU_DIV_MUX(dfc_lvl6, "dfc_lvl6", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL6, 14, 2, 8, 1, 0);
static SPACEMIT_CCU_DIV_MUX(dfc_lvl7, "dfc_lvl7", dfc_lvl_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_LEVEL7, 14, 2, 8, 1, 0);
static const char *const ddr_clk_parents[] =
{
    "dfc_lvl0", "dfc_lvl1", "dfc_lvl2", "dfc_lvl3", "dfc_lvl4", "dfc_lvl5", "dfc_lvl6", "dfc_lvl7"
};
static SPACEMIT_CCU_DDR_FC(ddr, "ddr", ddr_clk_parents,
        CRU_BASE_TYPE_APMU, APMU_DFC_AP, RT_BIT(0), 1, 3, 0);

/* MPMU */
static const struct ccu_ddn_info uart_ddn_mask_info =
{
    .factor = 2,
    .num_mask = 0x1fff,
    .den_mask = 0x1fff,
    .num_shift = 16,
    .den_shift = 0,
};
static struct ccu_ddn_tbl slow_uart1_tbl[] =
{
    { .num = 125, .den = 24 },      /* rate = parent_rate * 24/125/2) */
};
static struct ccu_ddn_tbl slow_uart2_tbl[] =
{
    { .num = 6144, .den = 960 },    /* rate = parent_rate * 960/6144/2) */
};

static SPACEMIT_CCU_GATE_NO_PARENT(slow_uart, "slow_uart", RT_NULL,
        CRU_BASE_TYPE_MPMU, MPMU_ACGR, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DDN(slow_uart1_14p74, "slow_uart1_14p74", "pll1_d16_153p6",
        &uart_ddn_mask_info, &slow_uart1_tbl, RT_ARRAY_SIZE(slow_uart1_tbl),
        CRU_BASE_TYPE_MPMU, MPMU_SUCCR, RT_CLK_F_IGNORE_UNUSED);
static SPACEMIT_CCU_DDN(slow_uart2_48, "slow_uart2_48", "pll1_d4_614p4",
        &uart_ddn_mask_info, &slow_uart2_tbl, RT_ARRAY_SIZE(slow_uart2_tbl),
        CRU_BASE_TYPE_MPMU, MPMU_SUCCR_1, RT_CLK_F_IGNORE_UNUSED);

/* rate = parent_rate * den / num / 2) */
static struct ccu_ddn_info mn_ddn_mask_info =
{
    .factor = 2,
    .num_mask = 0x1fff,
    .den_mask = 0x1fff,
    .num_shift = 16,
    .den_shift = 0,
};

/* parent_rate = 614400000Hz */
static struct ccu_ddn_tbl mn_tbl[] =
{
    { .num = 6144, .den = 120 * 2 },
    { .num = 6144, .den = 200 * 2 },
    { .num = 6144, .den = 240 * 2 },
    { .num = 6144, .den = 250 * 2 },
    { .num = 6144, .den = 260 * 2 },
    { .num = 6144, .den = 270 * 2 },
    { .num = 6144, .den = 300 * 2 },
    { .num = 6144, .den = 480 * 2 },
};

static const char *const mn_parent_names[] =
{
    "vctcxo_24", "pll1_d4_614p4"
};

static SPACEMIT_CCU_MUX_GATE(mn_src_clk, "mn_src_clk", mn_parent_names,
        CRU_BASE_TYPE_MPMU, MPMU_PM_MN, 1, 1, RT_BIT(0), RT_BIT(0), 0x0, 0);

static SPACEMIT_CCU_DDN(mn_clk, "mn_clk", "mn_src_clk",
        &mn_ddn_mask_info, &mn_tbl, RT_ARRAY_SIZE(mn_tbl), CRU_BASE_TYPE_MPMU, MPMU_PM_MN_GPCR, 0);

/* parent_rate = 600000000Hz */
static struct ccu_ddn_tbl mn2_tbl[] =
{
    {.num = 6000, .den = 120 * 2},
    {.num = 6000, .den = 200 * 2},
    {.num = 6000, .den = 240 * 2},
    {.num = 6000, .den = 250 * 2},
    {.num = 6000, .den = 260 * 2},
    {.num = 6000, .den = 270 * 2},
    {.num = 6000, .den = 300 * 2},
    {.num = 6000, .den = 480 * 2},
};

static const char *const mn2_parent_names[] =
{
    "vctcxo_24", "pll2_d5"
};

static SPACEMIT_CCU_MUX_GATE(mn2_src_clk, "mn2_src_clk", mn2_parent_names,
        CRU_BASE_TYPE_MPMU, MPMU_PM_MN, 5, 1, RT_BIT(4), RT_BIT(4), 0x0, 0);

static SPACEMIT_CCU_DDN(mn2_clk, "mn2_clk", "mn2_src_clk",
        &mn_ddn_mask_info, &mn2_tbl, RT_ARRAY_SIZE(mn2_tbl), CRU_BASE_TYPE_MPMU, MPMU_PM_MN_GPCR2, 0);

/* APBC */
static const char *const uart_parent_names[] =
{
    "pll1_m3d128_57p6", "slow_uart1_14p74", "slow_uart2_48"
};
static SPACEMIT_CCU_MUX_GATE(uart1_clk, "uart1_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART1_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart2_clk, "uart2_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART2_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart3_clk, "uart3_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART3_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart4_clk, "uart4_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART4_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart5_clk, "uart5_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART5_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart6_clk, "uart6_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART6_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart7_clk, "uart7_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART7_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart8_clk, "uart8_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART8_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(uart9_clk, "uart9_clk", uart_parent_names,
        CRU_BASE_TYPE_APBC, APBC_UART9_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE(gpio_clk, "gpio_clk", "vctcxo_24",
        CRU_BASE_TYPE_APBC, APBC_GPIO_CLK_RST, 0x3, 0x3, 0x0, 0);
static const char *pwm_parent_names[] =
{
    "pll1_d192_12p8", "clk_32k"
};
static SPACEMIT_CCU_MUX_GATE(pwm0_clk, "pwm0_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM0_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm1_clk, "pwm1_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM1_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm2_clk, "pwm2_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM2_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm3_clk, "pwm3_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM3_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm4_clk, "pwm4_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM4_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm5_clk, "pwm5_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM5_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm6_clk, "pwm6_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM6_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm7_clk, "pwm7_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM7_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm8_clk, "pwm8_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM8_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm9_clk, "pwm9_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM9_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm10_clk, "pwm10_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM10_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm11_clk, "pwm11_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM11_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm12_clk, "pwm12_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM12_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm13_clk, "pwm13_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM13_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm14_clk, "pwm14_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM14_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm15_clk, "pwm15_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM15_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm16_clk, "pwm16_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM16_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm17_clk, "pwm17_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM17_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm18_clk, "pwm18_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM18_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(pwm19_clk, "pwm19_clk", pwm_parent_names,
        CRU_BASE_TYPE_APBC, APBC_PWM19_CLK_RST, 4, 3, 0x2, 0x2, 0x0, 0);
static const char *ssp_parent_names[] =
{
    "pll1_d384_6p4", "pll1_d192_12p8", "pll1_d96_25p6", "pll1_d48_51p2",
    "pll1_d768_3p2", "pll1_d1536_1p6", "pll1_d3072_0p8", "vctcxo_1"
};
static SPACEMIT_CCU_MUX_GATE(ssp3_clk, "ssp3_clk", ssp_parent_names,
        CRU_BASE_TYPE_APBC, APBC_SSP3_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE(rtc_clk, "rtc_clk", "clk_32k",
        CRU_BASE_TYPE_APBC, APBC_RTC_CLK_RST, 0x83, 0x83, 0x0, 0);
static const char *twsi_parent_names[] =
{
    "pll1_d78_31p5", "pll1_d48_51p2", "pll1_d40_61p44"
};
static SPACEMIT_CCU_MUX_GATE(twsi0_clk, "twsi0_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI0_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(twsi1_clk, "twsi1_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI1_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(twsi2_clk, "twsi2_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI2_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(twsi4_clk, "twsi4_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI4_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(twsi5_clk, "twsi5_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI5_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(twsi6_clk, "twsi6_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI6_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(twsi7_clk, "twsi7_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI7_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(twsi8_clk, "twsi8_clk", twsi_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TWSI8_CLK_RST, 4, 3, 0x7, 0x3, 0x4, 0);
static const char *timer_parent_names[] =
{
    "pll1_d192_12p8", "clk_32k", "pll1_d384_6p4", "vctcxo_3", "vctcxo_1"
};
static SPACEMIT_CCU_MUX_GATE(timers1_clk, "timers1_clk", timer_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TIMERS1_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(timers2_clk, "timers2_clk", timer_parent_names,
        CRU_BASE_TYPE_APBC, APBC_TIMERS2_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE(aib_clk, "aib_clk", "vctcxo_24",
        CRU_BASE_TYPE_APBC, APBC_AIB_CLK_RST, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(onewire_clk, "onewire_clk", RT_NULL,
        CRU_BASE_TYPE_APBC, APBC_ONEWIRE_CLK_RST, 0x3, 0x3, 0x0, 0);

static SPACEMIT_CCU_GATE_FACTOR(i2s_sysclk, "i2s_sysclk", "pll1_d8_307p2",
        CRU_BASE_TYPE_MPMU, MPMU_ISCCR, RT_BIT(31), RT_BIT(31), 0x0, 200, 1, 0);
static SPACEMIT_CCU_GATE_FACTOR(i2s_bclk, "i2s_bclk", "i2s_sysclk",
        CRU_BASE_TYPE_MPMU, MPMU_ISCCR, RT_BIT(29), RT_BIT(29), 0x0, 1, 1, 0);
static const char *sspa_parent_names[] =
{
    "pll1_d384_6p4", "pll1_d192_12p8", "pll1_d96_25p6",
    "pll1_d48_51p2", "pll1_d768_3p2", "pll1_d1536_1p6", "pll1_d3072_0p8", "i2s_bclk"
};
static SPACEMIT_CCU_MUX_GATE(sspa0_clk, "sspa0_clk", sspa_parent_names,
        CRU_BASE_TYPE_APBC, APBC_SSPA0_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_MUX_GATE(sspa1_clk, "sspa1_clk", sspa_parent_names,
        CRU_BASE_TYPE_APBC, APBC_SSPA1_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(dro_clk, "dro_clk", RT_NULL,
        CRU_BASE_TYPE_APBC, APBC_DRO_CLK_RST, 0x1, 0x1, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(ir_clk, "ir_clk", RT_NULL,
        CRU_BASE_TYPE_APBC, APBC_IR_CLK_RST, 0x1, 0x1, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(tsen_clk, "tsen_clk", RT_NULL,
        CRU_BASE_TYPE_APBC, APBC_TSEN_CLK_RST, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(ipc_ap2aud_clk, "ipc_ap2aud_clk", RT_NULL,
        CRU_BASE_TYPE_APBC, APBC_IPC_AP2AUD_CLK_RST, 0x3, 0x3, 0x0, 0);
static const char *can_parent_names[] =
{
    "pll3_20", "pll3_40", "pll3_80"
};
static SPACEMIT_CCU_MUX_GATE(can0_clk, "can0_clk", can_parent_names,
        CRU_BASE_TYPE_APBC, APBC_CAN0_CLK_RST, 4, 3, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(can0_bus_clk, "can0_bus_clk", RT_NULL,
        CRU_BASE_TYPE_APBC, APBC_CAN0_CLK_RST, RT_BIT(0), RT_BIT(0), 0x0, 0);

/* MPMU */
static SPACEMIT_CCU_GATE(wdt_clk, "wdt_clk", "pll1_d96_25p6",
        CRU_BASE_TYPE_MPMU, MPMU_WDTPCR, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(ripc_clk, "ripc_clk", RT_NULL,
        CRU_BASE_TYPE_MPMU, MPMU_RIPCCR, 0x3, 0x3, 0x0, 0);

/* APMU */
static const char *const jpg_parent_names[] =
{
    "pll1_d4_614p4", "pll1_d6_409p6", "pll1_d5_491p52", "pll1_d3_819p2",
    "pll1_d2_1228p8", "pll2_d4", "pll2_d3"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(jpg_clk, "jpg_clk", jpg_parent_names,
        CRU_BASE_TYPE_APMU, APMU_JPG_CLK_RES_CTRL,
        5, 3, RT_BIT(15), 2, 3, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(jpg_4kafbc_clk, "jpg_4kafbc_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_JPG_CLK_RES_CTRL, RT_BIT(16), RT_BIT(16), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(jpg_2kafbc_clk, "jpg_2kafbc_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_JPG_CLK_RES_CTRL, RT_BIT(17), RT_BIT(17), 0x0, 0);
static const char *const ccic2phy_parent_names[] =
{
    "pll1_d24_102p4", "pll1_d48_51p2_ap"
};
static SPACEMIT_CCU_MUX_GATE(ccic2phy_clk, "ccic2phy_clk", ccic2phy_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CSI_CCIC2_CLK_RES_CTRL, 7, 1, RT_BIT(5), RT_BIT(5), 0x0, 0);
static const char *const ccic3phy_parent_names[] =
{
    "pll1_d24_102p4", "pll1_d48_51p2_ap"
};
static SPACEMIT_CCU_MUX_GATE(ccic3phy_clk, "ccic3phy_clk", ccic3phy_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CSI_CCIC2_CLK_RES_CTRL, 31, 1, RT_BIT(30), RT_BIT(30), 0x0, 0);
static const char *const csi_parent_names[] =
{
    "pll1_d5_491p52", "pll1_d6_409p6", "pll1_d4_614p4", "pll1_d3_819p2",
    "pll2_d2", "pll2_d3", "pll2_d4", "pll1_d2_1228p8"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(csi_clk, "csi_clk", csi_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CSI_CCIC2_CLK_RES_CTRL,
        20, 3, RT_BIT(15), 16, 3, RT_BIT(4), RT_BIT(4), 0x0, 0);
static const char *const camm_parent_names[] =
{
    "pll1_d8_307p2", "pll2_d5", "pll1_d6_409p6", "vctcxo_24"
};
static SPACEMIT_CCU_DIV_MUX_GATE(camm0_clk, "camm0_clk", camm_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CSI_CCIC2_CLK_RES_CTRL,
        23, 4, 8, 2, RT_BIT(28), RT_BIT(28), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(camm1_clk, "camm1_clk", camm_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CSI_CCIC2_CLK_RES_CTRL,
        23, 4, 8, 2, RT_BIT(6), RT_BIT(6), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(camm2_clk, "camm2_clk", camm_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CSI_CCIC2_CLK_RES_CTRL,
        23, 4, 8, 2, RT_BIT(3), RT_BIT(3), 0x0, 0);
static const char *const isp_cpp_parent_names[] =
{
    "pll1_d8_307p2", "pll1_d6_409p6"
};
static SPACEMIT_CCU_DIV_MUX_GATE(isp_cpp_clk, "isp_cpp_clk", isp_cpp_parent_names,
        CRU_BASE_TYPE_APMU, APMU_ISP_CLK_RES_CTRL,
        24, 2, 26, 1, RT_BIT(28), RT_BIT(28), 0x0, 0);
static const char *const isp_bus_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d5_491p52", "pll1_d8_307p2", "pll1_d10_245p76"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(isp_bus_clk, "isp_bus_clk", isp_bus_parent_names,
        CRU_BASE_TYPE_APMU, APMU_ISP_CLK_RES_CTRL,
        18, 3, RT_BIT(23), 21, 2, RT_BIT(17), RT_BIT(17), 0x0, 0);
static const char *const isp_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d5_491p52", "pll1_d4_614p4", "pll1_d8_307p2"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(isp_clk, "isp_clk", isp_parent_names,
        CRU_BASE_TYPE_APMU, APMU_ISP_CLK_RES_CTRL,
        4, 3, RT_BIT(7), 8, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static const char *const dpumclk_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d5_491p52", "pll1_d4_614p4", "pll1_d8_307p2"
};
static SPACEMIT_CCU_DIV2_FC_MUX_GATE(dpu_mclk, "dpu_mclk", dpumclk_parent_names,
        CRU_BASE_TYPE_APMU, APMU_LCD_CLK_RES_CTRL1, APMU_LCD_CLK_RES_CTRL2,
        1, 4, RT_BIT(29), 5, 3, RT_BIT(0), RT_BIT(0), 0x0, 0);
static const char *const dpuesc_parent_names[] =
{
    "pll1_d48_51p2_ap", "pll1_d52_47p26", "pll1_d96_25p6", "pll1_d32_76p8"
};
static SPACEMIT_CCU_MUX_GATE(dpu_esc_clk, "dpu_esc_clk", dpuesc_parent_names,
        CRU_BASE_TYPE_APMU, APMU_LCD_CLK_RES_CTRL1, 0, 2, RT_BIT(2), RT_BIT(2), 0x0, 0);
static const char *const dpubit_parent_names[] =
{
    "pll1_d3_819p2", "pll2_d2", "pll2_d3",
    "pll1_d2_1228p8", "pll2_d4", "pll2_d5", "pll2_d8", "pll2_d8"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(dpu_bit_clk, "dpu_bit_clk", dpubit_parent_names,
        CRU_BASE_TYPE_APMU, APMU_LCD_CLK_RES_CTRL1,
        17, 3, RT_BIT(31), 20, 3, RT_BIT(16), RT_BIT(16), 0x0, 0);
static const char *const dpupx_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d5_491p52", "pll1_d4_614p4", "pll1_d8_307p2", "pll2_d7", "pll2_d8"
};
static SPACEMIT_CCU_DIV2_FC_MUX_GATE(dpu_pxclk, "dpu_pxclk", dpupx_parent_names,
        CRU_BASE_TYPE_APMU, APMU_LCD_CLK_RES_CTRL1, APMU_LCD_CLK_RES_CTRL2,
        17, 4, RT_BIT(30), 21, 3, RT_BIT(16), RT_BIT(16), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(dpu_hclk, "dpu_hclk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_LCD_CLK_RES_CTRL1, RT_BIT(5), RT_BIT(5), 0x0, 0);
static const char *const dpu_spi_parent_names[] =
{
    "pll1_d8_307p2", "pll1_d6_409p6", "pll1_d10_245p76", "pll1_d11_223p4",
    "pll1_d13_189", "pll1_d23_106p8", "pll2_d3", "pll2_d5"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(dpu_spi_clk, "dpu_spi_clk", dpu_spi_parent_names,
        CRU_BASE_TYPE_APMU, APMU_LCD_SPI_CLK_RES_CTRL,
        8, 3, RT_BIT(7), 12, 3, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(dpu_spi_hbus_clk, "dpu_spi_hbus_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_LCD_SPI_CLK_RES_CTRL, RT_BIT(3), RT_BIT(3), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(dpu_spi_bus_clk, "dpu_spi_bus_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_LCD_SPI_CLK_RES_CTRL, RT_BIT(5), RT_BIT(5), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(dpu_spi_aclk, "dpu_spi_aclk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_LCD_SPI_CLK_RES_CTRL, RT_BIT(6), RT_BIT(6), 0x0, 0);
static const char *const v2d_parent_names[] =
{
    "pll1_d5_491p52", "pll1_d6_409p6", "pll1_d8_307p2", "pll1_d4_614p4",
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(v2d_clk, "v2d_clk", v2d_parent_names,
        CRU_BASE_TYPE_APMU, APMU_LCD_CLK_RES_CTRL1,
        9, 3, RT_BIT(28), 12, 2, RT_BIT(8), RT_BIT(8), 0x0, 0);
static const char *const ccic_4x_parent_names[] =
{
    "pll1_d5_491p52", "pll1_d6_409p6", "pll1_d4_614p4", "pll1_d3_819p2",
    "pll2_d2", "pll2_d3", "pll2_d4", "pll1_d2_1228p8"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(ccic_4x_clk, "ccic_4x_clk", ccic_4x_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CCIC_CLK_RES_CTRL,
        18, 3, RT_BIT(15), 23, 2, RT_BIT(4), RT_BIT(4), 0x0, 0);
static const char *const ccic1phy_parent_names[] =
{
    "pll1_d24_102p4", "pll1_d48_51p2_ap"
};
static SPACEMIT_CCU_MUX_GATE(ccic1phy_clk, "ccic1phy_clk", ccic1phy_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CCIC_CLK_RES_CTRL, 7, 1, RT_BIT(5), RT_BIT(5), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(sdh_axi_aclk, "sdh_axi_aclk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_SDH0_CLK_RES_CTRL, RT_BIT(3), RT_BIT(3), 0x0, 0);
static const char *const sdh01_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d4_614p4", "pll2_d8", "pll2_d5",
    "pll1_d11_223p4", "pll1_d13_189", "pll1_d23_106p8"
};

static SPACEMIT_CCU_DIV_FC_MUX_GATE(sdh0_clk, "sdh0_clk", sdh01_parent_names,
        CRU_BASE_TYPE_APMU, APMU_SDH0_CLK_RES_CTRL,
        8, 3, RT_BIT(11), 5, 3, RT_BIT(4), RT_BIT(4), 0x0, 0);
static SPACEMIT_CCU_DIV_FC_MUX_GATE(sdh1_clk, "sdh1_clk", sdh01_parent_names,
        CRU_BASE_TYPE_APMU, APMU_SDH1_CLK_RES_CTRL,
        8, 3, RT_BIT(11), 5, 3, RT_BIT(4), RT_BIT(4), 0x0, 0);
static const char *const sdh2_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d4_614p4", "pll2_d8", "pll1_d3_819p2",
    "pll1_d11_223p4", "pll1_d13_189", "pll1_d23_106p8"
};

static SPACEMIT_CCU_DIV_FC_MUX_GATE(sdh2_clk, "sdh2_clk", sdh2_parent_names,
        CRU_BASE_TYPE_APMU, APMU_SDH2_CLK_RES_CTRL,
        8, 3, RT_BIT(11), 5, 3, RT_BIT(4), RT_BIT(4), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(usb_axi_clk, "usb_axi_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_USB_CLK_RES_CTRL, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(usb_p1_aclk, "usb_p1_aclk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_USB_CLK_RES_CTRL, RT_BIT(5), RT_BIT(5), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(usb30_clk, "usb30_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_USB_CLK_RES_CTRL, RT_BIT(8), RT_BIT(8), 0x0, 0);
static const char *const qspi_parent_names[] =
{
    "pll1_d6_409p6", "pll2_d8", "pll1_d8_307p2", "pll1_d10_245p76",
    "pll1_d11_223p4", "pll1_d23_106p8", "pll1_d5_491p52", "pll1_d13_189"
};
static SPACEMIT_CCU_DIV_MUX_GATE(qspi_clk, "qspi_clk", qspi_parent_names,
        CRU_BASE_TYPE_APMU, APMU_QSPI_CLK_RES_CTRL,
        9, 3, 6, 3, RT_BIT(4), RT_BIT(4), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(qspi_bus_clk, "qspi_bus_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_QSPI_CLK_RES_CTRL, RT_BIT(3), RT_BIT(3), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(dma_clk, "dma_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_DMA_CLK_RES_CTRL, RT_BIT(3), RT_BIT(3), 0x0, 0);
static const char *const aes_parent_names[] =
{
    "pll1_d12_204p8", "pll1_d24_102p4"
};
static SPACEMIT_CCU_MUX_GATE(aes_clk, "aes_clk", aes_parent_names,
        CRU_BASE_TYPE_APMU, APMU_AES_CLK_RES_CTRL, 6, 1, RT_BIT(5), RT_BIT(5), 0x0, 0);
static const char *const vpu_parent_names[] =
{
    "pll1_d4_614p4", "pll1_d5_491p52", "pll1_d3_819p2", "pll1_d6_409p6",
    "pll3_d6", "pll2_d3", "pll2_d4", "pll2_d5"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(vpu_clk, "vpu_clk", vpu_parent_names,
        CRU_BASE_TYPE_APMU, APMU_VPU_CLK_RES_CTRL,
        13, 3, RT_BIT(21), 10, 3, RT_BIT(3), RT_BIT(3), 0x0, 0);
static const char *const gpu_parent_names[] =
{
    "pll1_d4_614p4", "pll1_d5_491p52", "pll1_d3_819p2", "pll1_d6_409p6",
    "pll3_d6", "pll2_d3", "pll2_d4", "pll2_d5"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(gpu_clk, "gpu_clk", gpu_parent_names,
        CRU_BASE_TYPE_APMU, APMU_GPU_CLK_RES_CTRL,
        12, 3, RT_BIT(15), 18, 3, RT_BIT(4), RT_BIT(4), 0x0, 0);
static const char *const emmc_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d4_614p4", "pll1_d52_47p26", "pll1_d3_819p2"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(emmc_clk, "emmc_clk", emmc_parent_names,
        CRU_BASE_TYPE_APMU, APMU_PMUA_EM_CLK_RES_CTRL,
        8, 3, RT_BIT(11), 6, 2, 0x18, 0x18, 0x0, 0);
static SPACEMIT_CCU_DIV_GATE(emmc_x_clk, "emmc_x_clk", "pll1_d2_1228p8",
        CRU_BASE_TYPE_APMU, APMU_PMUA_EM_CLK_RES_CTRL,
        12, 3, RT_BIT(15), RT_BIT(15), 0x0, 0);
static const char *const audio_parent_names[] =
{
    "pll1_aud_245p7", "pll1_d8_307p2", "pll1_d6_409p6"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(audio_clk, "audio_clk", audio_parent_names,
        CRU_BASE_TYPE_APMU, APMU_AUDIO_CLK_RES_CTRL,
        4, 3, RT_BIT(15), 7, 3, RT_BIT(12), RT_BIT(12), 0x0, 0);
static const char *const hdmi_parent_names[] =
{
    "pll1_d6_409p6", "pll1_d5_491p52", "pll1_d4_614p4", "pll1_d8_307p2"
};
static SPACEMIT_CCU_DIV_FC_MUX_GATE(hdmi_mclk, "hdmi_mclk", hdmi_parent_names,
        CRU_BASE_TYPE_APMU, APMU_HDMI_CLK_RES_CTRL,
        1, 4, RT_BIT(29), 5, 3, RT_BIT(0), RT_BIT(0), 0x0, 0);
static const char *const cci550_parent_names[] =
{
    "pll1_d5_491p52", "pll1_d4_614p4", "pll1_d3_819p2", "pll2_d3"
};
static SPACEMIT_CCU_DIV_FC_MUX(cci550_clk, "cci550_clk", cci550_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CCI550_CLK_CTRL, 8, 3, RT_BIT(12), 0, 2, 0);
static const char *const pmua_aclk_parent_names[] =
{
    "pll1_d10_245p76", "pll1_d8_307p2"
};
static SPACEMIT_CCU_DIV_FC_MUX(pmua_aclk, "pmua_aclk", pmua_aclk_parent_names,
        CRU_BASE_TYPE_APMU, APMU_ACLK_CLK_CTRL, 1, 2, RT_BIT(4), 0, 1, 0);
static const char *const cpu_c0_hi_parent_names[] =
{
    "pll3_d2", "pll3_d1"
};
static SPACEMIT_CCU_MUX(cpu_c0_hi_clk, "cpu_c0_hi_clk", cpu_c0_hi_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CPU_C0_CLK_CTRL, 13, 1, 0);
static const char *const cpu_c0_parent_names[] =
{
    "pll1_d4_614p4", "pll1_d3_819p2", "pll1_d6_409p6",
    "pll1_d5_491p52", "pll1_d2_1228p8", "pll3_d3", "pll2_d3", "cpu_c0_hi_clk"
};
static SPACEMIT_CCU_MUX_FC(cpu_c0_core_clk, "cpu_c0_core_clk", cpu_c0_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CPU_C0_CLK_CTRL, RT_BIT(12), 0, 3, 0);
static SPACEMIT_CCU_DIV(cpu_c0_ace_clk, "cpu_c0_ace_clk", "cpu_c0_core_clk",
        CRU_BASE_TYPE_APMU, APMU_CPU_C0_CLK_CTRL, 6, 3, 0);
static SPACEMIT_CCU_DIV(cpu_c0_tcm_clk, "cpu_c0_tcm_clk", "cpu_c0_core_clk",
        CRU_BASE_TYPE_APMU, APMU_CPU_C0_CLK_CTRL, 9, 3, 0);
static const char *const cpu_c1_hi_parent_names[] =
{
    "pll3_d2", "pll3_d1"
};
static SPACEMIT_CCU_MUX(cpu_c1_hi_clk, "cpu_c1_hi_clk", cpu_c1_hi_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CPU_C1_CLK_CTRL, 13, 1, 0);
static const char *const cpu_c1_parent_names[] =
{
    "pll1_d4_614p4", "pll1_d3_819p2", "pll1_d6_409p6",
    "pll1_d5_491p52", "pll1_d2_1228p8", "pll3_d3", "pll2_d3", "cpu_c1_hi_clk"
};
static SPACEMIT_CCU_MUX_FC(cpu_c1_pclk, "cpu_c1_pclk", cpu_c1_parent_names,
        CRU_BASE_TYPE_APMU, APMU_CPU_C1_CLK_CTRL, RT_BIT(12), 0, 3, 0);
static SPACEMIT_CCU_DIV(cpu_c1_ace_clk, "cpu_c1_ace_clk", "cpu_c1_pclk",
        CRU_BASE_TYPE_APMU, APMU_CPU_C1_CLK_CTRL, 6, 3, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(pcie0_clk, "pcie0_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_PCIE_CLK_RES_CTRL_0, 0x7, 0x7, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(pcie1_clk, "pcie1_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_PCIE_CLK_RES_CTRL_1, 0x7, 0x7, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(pcie2_clk, "pcie2_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_PCIE_CLK_RES_CTRL_2, 0x7, 0x7, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(emac0_bus_clk, "emac0_bus_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_EMAC0_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0x0, 0);
static SPACEMIT_CCU_GATE(emac0_ptp_clk, "emac0_ptp_clk", "pll2_d6",
        CRU_BASE_TYPE_APMU, APMU_EMAC0_CLK_RES_CTRL, RT_BIT(15), RT_BIT(15), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(emac1_bus_clk, "emac1_bus_clk", RT_NULL,
        CRU_BASE_TYPE_APMU, APMU_EMAC1_CLK_RES_CTRL, RT_BIT(0), RT_BIT(0), 0x0, 0);
static SPACEMIT_CCU_GATE(emac1_ptp_clk, "emac1_ptp_clk", "pll2_d6",
        CRU_BASE_TYPE_APMU, APMU_EMAC1_CLK_RES_CTRL, RT_BIT(15), RT_BIT(15), 0x0, 0);

/* APBC2 */
static const char *const uart1_sec_parent_names[] =
{
    "pll1_m3d128_57p6", "slow_uart1_14p74", "slow_uart2_48"
};
static SPACEMIT_CCU_MUX_GATE(uart1_sec_clk, "uart1_sec_clk", uart1_sec_parent_names,
        CRU_BASE_TYPE_APBC2, APBC2_UART1_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);

static const char *ssp2_sec_parent_names[] =
{
    "pll1_d384_6p4", "pll1_d192_12p8", "pll1_d96_25p6",
    "pll1_d48_51p2", "pll1_d768_3p2", "pll1_d1536_1p6", "pll1_d3072_0p8"
};
static SPACEMIT_CCU_MUX_GATE(ssp2_sec_clk, "ssp2_sec_clk", ssp2_sec_parent_names,
        CRU_BASE_TYPE_APBC2, APBC2_SSP2_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static const char *twsi3_sec_parent_names[] =
{
    "pll1_d78_31p5", "pll1_d48_51p2", "pll1_d40_61p44"
};
static SPACEMIT_CCU_MUX_GATE(twsi3_sec_clk, "twsi3_sec_clk", twsi3_sec_parent_names,
        CRU_BASE_TYPE_APBC2, APBC2_TWSI3_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE(rtc_sec_clk, "rtc_sec_clk", "clk_32k",
        CRU_BASE_TYPE_APBC2, APBC2_RTC_CLK_RST, 0x83, 0x83, 0x0, 0);
static const char *timer_sec_parent_names[] =
{
    "pll1_d192_12p8", "clk_32k", "pll1_d384_6p4", "vctcxo_3", "vctcxo_1"
};
static SPACEMIT_CCU_MUX_GATE(timers0_sec_clk, "timers0_sec_clk", timer_sec_parent_names,
        CRU_BASE_TYPE_APBC2, APBC2_TIMERS0_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static const char *kpc_sec_parent_names[] =
{
    "pll1_d192_12p8", "clk_32k", "pll1_d384_6p4", "vctcxo_3", "vctcxo_1"
};
static SPACEMIT_CCU_MUX_GATE(kpc_sec_clk, "kpc_sec_clk", kpc_sec_parent_names,
        CRU_BASE_TYPE_APBC2, APBC2_KPC_CLK_RST, 4, 3, 0x3, 0x3, 0x0, 0);
static SPACEMIT_CCU_GATE(gpio_sec_clk, "gpio_sec_clk", "vctcxo_24",
        CRU_BASE_TYPE_APBC2, APBC2_GPIO_CLK_RST, 0x3, 0x3, 0x0, 0);

static const char *const apb_parent_names[] =
{
    "pll1_d96_25p6", "pll1_d48_51p2", "pll1_d96_25p6", "pll1_d24_102p4"
};
static SPACEMIT_CCU_MUX(apb_clk, "apb_clk", apb_parent_names,
        CRU_BASE_TYPE_MPMU, MPMU_APBCSCR, 0, 2, 0);
/* RCPU */
static const char *rhdmi_audio_parent_names[] =
{
    "pll1_aud_24p5", "pll1_aud_245p7"
};
static SPACEMIT_CCU_DIV_MUX_GATE(rhdmi_audio_clk, "rhdmi_audio_clk", rhdmi_audio_parent_names,
        CRU_BASE_TYPE_RCPU, RCPU_HDMI_CLK_RST, 4, 11, 16, 2, 0x6, 0x6, 0x0, 0);

static const char *rcan_parent_names[] =
{
    "pll3_20", "pll3_40", "pll3_80"
};
static SPACEMIT_CCU_DIV_MUX_GATE(rcan_clk, "rcan_clk", rcan_parent_names,
        CRU_BASE_TYPE_RCPU, RCPU_CAN_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(rcan_bus_clk, "rcan_bus_clk", RT_NULL,
        CRU_BASE_TYPE_RCPU, RCPU_CAN_CLK_RST, RT_BIT(2), RT_BIT(2), 0x0, 0);
/* RCPU2 */
static const char *rpwm_parent_names[] =
{
    "pll1_aud_245p7", "pll1_aud_24p5"
};
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm0_clk, "rpwm0_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM0_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm1_clk, "rpwm1_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM1_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm2_clk, "rpwm2_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM2_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm3_clk, "rpwm3_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM3_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm4_clk, "rpwm4_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM4_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm5_clk, "rpwm5_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM5_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm6_clk, "rpwm6_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM6_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm7_clk, "rpwm7_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM7_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm8_clk, "rpwm8_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM8_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);
static SPACEMIT_CCU_DIV_MUX_GATE(rpwm9_clk, "rpwm9_clk", rpwm_parent_names,
        CRU_BASE_TYPE_RCPU2, RCPU2_PWM9_CLK_RST, 8, 11, 4, 2, RT_BIT(1), RT_BIT(1), 0x0, 0);

static const char *ri2c_parent_names[] =
{
    "pll1_d40_61p44", "pll1_d96_25p6", "pll1_d192_12p8", "vctcxo_3"
};
static SPACEMIT_CCU_DIV_MUX_GATE(ri2c0_clk, "ri2c0_clk", ri2c_parent_names,
        CRU_BASE_TYPE_RCPU, RCPU_I2C0_CLK_RST, 8, 11, 4, 2, 0x6, 0x6, 0x0, 0);

static const char *rssp0_parent_names[] =
{
    "pll1_d40_61p44", "pll1_d96_25p6", "pll1_d192_12p8", "vctcxo_3"
};
static SPACEMIT_CCU_DIV_MUX_GATE(rssp0_clk, "rssp0_clk", rssp0_parent_names,
        CRU_BASE_TYPE_RCPU, RCPU_SSP0_CLK_RST, 8, 11, 4, 2, 0x6, 0x6, 0x0, 0);
static SPACEMIT_CCU_GATE_NO_PARENT(rir_clk, "rir_clk", RT_NULL,
        CRU_BASE_TYPE_RCPU, RCPU_IR_CLK_RST, RT_BIT(2), RT_BIT(2), 0x0, 0);
static const char *ruart0_parent_names[] =
{
    "pll1_aud_24p5", "pll1_aud_245p7", "vctcxo_24", "vctcxo_3"
};
static SPACEMIT_CCU_DIV_MUX_GATE(ruart0_clk, "ruart0_clk", ruart0_parent_names,
        CRU_BASE_TYPE_RCPU, RCPU_UART0_CLK_RST, 8, 11, 4, 2, 0x6, 0x6, 0x0, 0);
static const char *ruart1_parent_names[] =
{
    "pll1_aud_24p5", "pll1_aud_245p7", "vctcxo_24", "vctcxo_3"
};
static SPACEMIT_CCU_DIV_MUX_GATE(ruart1_clk, "ruart1_clk", ruart1_parent_names,
        CRU_BASE_TYPE_RCPU, RCPU_UART1_CLK_RST, 8, 11, 4, 2, 0x6, 0x6, 0x0, 0);

static SPACEMIT_CCU_DIV_FLAG(audio_apb_clk, "audio_apb_clk", "audio_clk",
        CRU_BASE_TYPE_AUDPMU, AUDPMU_AUDIO_BUS_CLK_CTRL,
        4, 3, CLK_DIVIDER_POWER_OF_TWO | CLK_DIVIDER_ALLOW_ZERO, 0);

static SPACEMIT_CCU_DIV_FLAG(audio_axi_clk, "audio_axi_clk", "audio_clk",
        CRU_BASE_TYPE_AUDPMU, AUDPMU_AUDIO_BUS_CLK_CTRL,
        0, 2, CLK_DIVIDER_POWER_OF_TWO | CLK_DIVIDER_ALLOW_ZERO, 0);

static const rt_uint32_t bootup_enable_clk_table[] =
{
    CLK_PLL1_307P2,
    CLK_PLL1_409P6,
    CLK_PLL1_491,
    CLK_PLL1_614,
    CLK_PLL1_819,
    CLK_PLL1_1228,
    CLK_PLL1_245P76,
    CLK_PLL1_51P2,
    CLK_PLL1_51P2_AP,
    CLK_PLL1_25P6,
    CLK_PLL3_D1,
    CLK_PLL3_D2,
    CLK_PLL3_D3,
    CLK_PLL2_D3,
    CLK_APB,
    CLK_PMUA_ACLK,
    CLK_DMA,
};

static const rt_ubase_t bootup_set_rate_clk_table[] =
{
    CLK_PM_MN_SRC, 614400000,
    CLK_PM_MN2_SRC, 600000000,
};

static struct rt_clk_cell *spacemit_k1x_ccu_cell[] =
{
    [CLK_PLL2]              = &pll2.common.cell,
    [CLK_PLL3]              = &pll3.common.cell,
    [CLK_PLL1_D2]           = &pll1_d2.common.cell,
    [CLK_PLL1_D3]           = &pll1_d3.common.cell,
    [CLK_PLL1_D4]           = &pll1_d4.common.cell,
    [CLK_PLL1_D5]           = &pll1_d5.common.cell,
    [CLK_PLL1_D6]           = &pll1_d6.common.cell,
    [CLK_PLL1_D7]           = &pll1_d7.common.cell,
    [CLK_PLL1_D8]           = &pll1_d8.common.cell,
    [CLK_PLL1_D11]          = &pll1_d11_223p4.common.cell,
    [CLK_PLL1_D13]          = &pll1_d13_189.common.cell,
    [CLK_PLL1_D23]          = &pll1_d23_106p8.common.cell,
    [CLK_PLL1_D64]          = &pll1_d64_38p4.common.cell,
    [CLK_PLL1_D10_AUD]      = &pll1_aud_245p7.common.cell,
    [CLK_PLL1_D100_AUD]     = &pll1_aud_24p5.common.cell,
    [CLK_PLL2_D1]           = &pll2_d1.common.cell,
    [CLK_PLL2_D2]           = &pll2_d2.common.cell,
    [CLK_PLL2_D3]           = &pll2_d3.common.cell,
    [CLK_PLL2_D4]           = &pll2_d4.common.cell,
    [CLK_PLL2_D5]           = &pll2_d5.common.cell,
    [CLK_PLL2_D6]           = &pll2_d6.common.cell,
    [CLK_PLL2_D7]           = &pll2_d7.common.cell,
    [CLK_PLL2_D8]           = &pll2_d8.common.cell,
    [CLK_PLL3_D1]           = &pll3_d1.common.cell,
    [CLK_PLL3_D2]           = &pll3_d2.common.cell,
    [CLK_PLL3_D3]           = &pll3_d3.common.cell,
    [CLK_PLL3_D4]           = &pll3_d4.common.cell,
    [CLK_PLL3_D5]           = &pll3_d5.common.cell,
    [CLK_PLL3_D6]           = &pll3_d6.common.cell,
    [CLK_PLL3_D7]           = &pll3_d7.common.cell,
    [CLK_PLL3_D8]           = &pll3_d8.common.cell,
    [CLK_PLL3_80]           = &pll3_80.common.cell,
    [CLK_PLL3_40]           = &pll3_40.common.cell,
    [CLK_PLL3_20]           = &pll3_20.common.cell,
    [CLK_PLL1_307P2]        = &pll1_d8_307p2.common.cell,
    [CLK_PLL1_76P8]         = &pll1_d32_76p8.common.cell,
    [CLK_PLL1_61P44]        = &pll1_d40_61p44.common.cell,
    [CLK_PLL1_153P6]        = &pll1_d16_153p6.common.cell,
    [CLK_PLL1_102P4]        = &pll1_d24_102p4.common.cell,
    [CLK_PLL1_51P2]         = &pll1_d48_51p2.common.cell,
    [CLK_PLL1_51P2_AP]      = &pll1_d48_51p2_ap.common.cell,
    [CLK_PLL1_57P6]         = &pll1_m3d128_57p6.common.cell,
    [CLK_PLL1_25P6]         = &pll1_d96_25p6.common.cell,
    [CLK_PLL1_12P8]         = &pll1_d192_12p8.common.cell,
    [CLK_PLL1_12P8_WDT]     = &pll1_d192_12p8_wdt.common.cell,
    [CLK_PLL1_6P4]          = &pll1_d384_6p4.common.cell,
    [CLK_PLL1_3P2]          = &pll1_d768_3p2.common.cell,
    [CLK_PLL1_1P6]          = &pll1_d1536_1p6.common.cell,
    [CLK_PLL1_0P8]          = &pll1_d3072_0p8.common.cell,
    [CLK_PLL1_351]          = &pll1_d7_351p08.common.cell,
    [CLK_PLL1_409P6]        = &pll1_d6_409p6.common.cell,
    [CLK_PLL1_204P8]        = &pll1_d12_204p8.common.cell,
    [CLK_PLL1_491]          = &pll1_d5_491p52.common.cell,
    [CLK_PLL1_245P76]       = &pll1_d10_245p76.common.cell,
    [CLK_PLL1_614]          = &pll1_d4_614p4.common.cell,
    [CLK_PLL1_47P26]        = &pll1_d52_47p26.common.cell,
    [CLK_PLL1_31P5]         = &pll1_d78_31p5.common.cell,
    [CLK_PLL1_819]          = &pll1_d3_819p2.common.cell,
    [CLK_PLL1_1228]         = &pll1_d2_1228p8.common.cell,
    [CLK_SLOW_UART1]        = &slow_uart1_14p74.common.cell,
    [CLK_SLOW_UART2]        = &slow_uart2_48.common.cell,
    [CLK_UART1]             = &uart1_clk.common.cell,
    [CLK_UART2]             = &uart2_clk.common.cell,
    [CLK_UART3]             = &uart3_clk.common.cell,
    [CLK_UART4]             = &uart4_clk.common.cell,
    [CLK_UART5]             = &uart5_clk.common.cell,
    [CLK_UART6]             = &uart6_clk.common.cell,
    [CLK_UART7]             = &uart7_clk.common.cell,
    [CLK_UART8]             = &uart8_clk.common.cell,
    [CLK_UART9]             = &uart9_clk.common.cell,
    [CLK_GPIO]              = &gpio_clk.common.cell,
    [CLK_PWM0]              = &pwm0_clk.common.cell,
    [CLK_PWM1]              = &pwm1_clk.common.cell,
    [CLK_PWM2]              = &pwm2_clk.common.cell,
    [CLK_PWM3]              = &pwm3_clk.common.cell,
    [CLK_PWM4]              = &pwm4_clk.common.cell,
    [CLK_PWM5]              = &pwm5_clk.common.cell,
    [CLK_PWM6]              = &pwm6_clk.common.cell,
    [CLK_PWM7]              = &pwm7_clk.common.cell,
    [CLK_PWM8]              = &pwm8_clk.common.cell,
    [CLK_PWM9]              = &pwm9_clk.common.cell,
    [CLK_PWM10]             = &pwm10_clk.common.cell,
    [CLK_PWM11]             = &pwm11_clk.common.cell,
    [CLK_PWM12]             = &pwm12_clk.common.cell,
    [CLK_PWM13]             = &pwm13_clk.common.cell,
    [CLK_PWM14]             = &pwm14_clk.common.cell,
    [CLK_PWM15]             = &pwm15_clk.common.cell,
    [CLK_PWM16]             = &pwm16_clk.common.cell,
    [CLK_PWM17]             = &pwm17_clk.common.cell,
    [CLK_PWM18]             = &pwm18_clk.common.cell,
    [CLK_PWM19]             = &pwm19_clk.common.cell,
    [CLK_SSP3]              = &ssp3_clk.common.cell,
    [CLK_RTC]               = &rtc_clk.common.cell,
    [CLK_TWSI0]             = &twsi0_clk.common.cell,
    [CLK_TWSI1]             = &twsi1_clk.common.cell,
    [CLK_TWSI2]             = &twsi2_clk.common.cell,
    [CLK_TWSI4]             = &twsi4_clk.common.cell,
    [CLK_TWSI5]             = &twsi5_clk.common.cell,
    [CLK_TWSI6]             = &twsi6_clk.common.cell,
    [CLK_TWSI7]             = &twsi7_clk.common.cell,
    [CLK_TWSI8]             = &twsi8_clk.common.cell,
    [CLK_TIMERS1]           = &timers1_clk.common.cell,
    [CLK_TIMERS2]           = &timers2_clk.common.cell,
    [CLK_AIB]               = &aib_clk.common.cell,
    [CLK_ONEWIRE]           = &onewire_clk.common.cell,
    [CLK_SSPA0]             = &sspa0_clk.common.cell,
    [CLK_SSPA1]             = &sspa1_clk.common.cell,
    [CLK_DRO]               = &dro_clk.common.cell,
    [CLK_IR]                = &ir_clk.common.cell,
    [CLK_TSEN]              = &tsen_clk.common.cell,
    [CLK_IPC_AP2AUD]        = &ipc_ap2aud_clk.common.cell,
    [CLK_CAN0]              = &can0_clk.common.cell,
    [CLK_CAN0_BUS]          = &can0_bus_clk.common.cell,
    [CLK_WDT]               = &wdt_clk.common.cell,
    [CLK_RIPC]              = &ripc_clk.common.cell,
    [CLK_JPG]               = &jpg_clk.common.cell,
    [CLK_JPF_4KAFBC]        = &jpg_4kafbc_clk.common.cell,
    [CLK_JPF_2KAFBC]        = &jpg_2kafbc_clk.common.cell,
    [CLK_CCIC2PHY]          = &ccic2phy_clk.common.cell,
    [CLK_CCIC3PHY]          = &ccic3phy_clk.common.cell,
    [CLK_CSI]               = &csi_clk.common.cell,
    [CLK_CAMM0]             = &camm0_clk.common.cell,
    [CLK_CAMM1]             = &camm1_clk.common.cell,
    [CLK_CAMM2]             = &camm2_clk.common.cell,
    [CLK_ISP_CPP]           = &isp_cpp_clk.common.cell,
    [CLK_ISP_BUS]           = &isp_bus_clk.common.cell,
    [CLK_ISP]               = &isp_clk.common.cell,
    [CLK_DPU_MCLK]          = &dpu_mclk.common.cell,
    [CLK_DPU_ESC]           = &dpu_esc_clk.common.cell,
    [CLK_DPU_BIT]           = &dpu_bit_clk.common.cell,
    [CLK_DPU_PXCLK]         = &dpu_pxclk.common.cell,
    [CLK_DPU_HCLK]          = &dpu_hclk.common.cell,
    [CLK_DPU_SPI]           = &dpu_spi_clk.common.cell,
    [CLK_DPU_SPI_HBUS]      = &dpu_spi_hbus_clk.common.cell,
    [CLK_DPU_SPIBUS]        = &dpu_spi_bus_clk.common.cell,
    [CLK_SPU_SPI_ACLK]      = &dpu_spi_aclk.common.cell,
    [CLK_V2D]               = &v2d_clk.common.cell,
    [CLK_CCIC_4X]           = &ccic_4x_clk.common.cell,
    [CLK_CCIC1PHY]          = &ccic1phy_clk.common.cell,
    [CLK_SDH_AXI]           = &sdh_axi_aclk.common.cell,
    [CLK_SDH0]              = &sdh0_clk.common.cell,
    [CLK_SDH1]              = &sdh1_clk.common.cell,
    [CLK_SDH2]              = &sdh2_clk.common.cell,
    [CLK_USB_P1]            = &usb_p1_aclk.common.cell,
    [CLK_USB_AXI]           = &usb_axi_clk.common.cell,
    [CLK_USB30]             = &usb30_clk.common.cell,
    [CLK_QSPI]              = &qspi_clk.common.cell,
    [CLK_QSPI_BUS]          = &qspi_bus_clk.common.cell,
    [CLK_DMA]               = &dma_clk.common.cell,
    [CLK_AES]               = &aes_clk.common.cell,
    [CLK_VPU]               = &vpu_clk.common.cell,
    [CLK_GPU]               = &gpu_clk.common.cell,
    [CLK_EMMC]              = &emmc_clk.common.cell,
    [CLK_EMMC_X]            = &emmc_x_clk.common.cell,
    [CLK_AUDIO]             = &audio_clk.common.cell,
    [CLK_HDMI]              = &hdmi_mclk.common.cell,
    [CLK_CCI550]            = &cci550_clk.common.cell,
    [CLK_PMUA_ACLK]         = &pmua_aclk.common.cell,
    [CLK_CPU_C0_HI]         = &cpu_c0_hi_clk.common.cell,
    [CLK_CPU_C0_CORE]       = &cpu_c0_core_clk.common.cell,
    [CLK_CPU_C0_ACE]        = &cpu_c0_ace_clk.common.cell,
    [CLK_CPU_C0_TCM]        = &cpu_c0_tcm_clk.common.cell,
    [CLK_CPU_C1_HI]         = &cpu_c1_hi_clk.common.cell,
    [CLK_CPU_C1_CORE]       = &cpu_c1_pclk.common.cell,
    [CLK_CPU_C1_ACE]        = &cpu_c1_ace_clk.common.cell,
    [CLK_PCIE0]             = &pcie0_clk.common.cell,
    [CLK_PCIE1]             = &pcie1_clk.common.cell,
    [CLK_PCIE2]             = &pcie2_clk.common.cell,
    [CLK_EMAC0_BUS]         = &emac0_bus_clk.common.cell,
    [CLK_EMAC0_PTP]         = &emac0_ptp_clk.common.cell,
    [CLK_EMAC1_BUS]         = &emac1_bus_clk.common.cell,
    [CLK_EMAC1_PTP]         = &emac1_ptp_clk.common.cell,
    [CLK_SEC_UART1]         = &uart1_sec_clk.common.cell,
    [CLK_SEC_SSP2]          = &ssp2_sec_clk.common.cell,
    [CLK_SEC_TWSI3]         = &twsi3_sec_clk.common.cell,
    [CLK_SEC_RTC]           = &rtc_sec_clk.common.cell,
    [CLK_SEC_TIMERS0]       = &timers0_sec_clk.common.cell,
    [CLK_SEC_KPC]           = &kpc_sec_clk.common.cell,
    [CLK_SEC_GPIO]          = &gpio_sec_clk.common.cell,
    [CLK_APB]               = &apb_clk.common.cell,
    [CLK_SLOW_UART]         = &slow_uart.common.cell,
    [CLK_I2S_SYSCLK]        = &i2s_sysclk.common.cell,
    [CLK_I2S_BCLK]          = &i2s_bclk.common.cell,
    [CLK_RCPU_HDMIAUDIO]    = &rhdmi_audio_clk.common.cell,
    [CLK_RCPU_CAN]          = &rcan_clk.common.cell,
    [CLK_RCPU_CAN_BUS]      = &rcan_bus_clk.common.cell,
    [CLK_RCPU_I2C0]         = &ri2c0_clk.common.cell,
    [CLK_RCPU_SSP0]         = &rssp0_clk.common.cell,
    [CLK_RCPU_IR]           = &rir_clk.common.cell,
    [CLK_RCPU_UART0]        = &ruart0_clk.common.cell,
    [CLK_RCPU_UART1]        = &ruart1_clk.common.cell,
    [CLK_DPLL1]             = &dpll1.common.cell,
    [CLK_DPLL2]             = &dpll2.common.cell,
    [CLK_DFC_LVL0]          = &dfc_lvl0.common.cell,
    [CLK_DFC_LVL1]          = &dfc_lvl1.common.cell,
    [CLK_DFC_LVL2]          = &dfc_lvl2.common.cell,
    [CLK_DFC_LVL3]          = &dfc_lvl3.common.cell,
    [CLK_DFC_LVL4]          = &dfc_lvl4.common.cell,
    [CLK_DFC_LVL5]          = &dfc_lvl5.common.cell,
    [CLK_DFC_LVL6]          = &dfc_lvl6.common.cell,
    [CLK_DFC_LVL7]          = &dfc_lvl7.common.cell,
    [CLK_DDR]               = &ddr.common.cell,
    [CLK_RCPU2_PWM0]        = &rpwm0_clk.common.cell,
    [CLK_RCPU2_PWM1]        = &rpwm1_clk.common.cell,
    [CLK_RCPU2_PWM2]        = &rpwm2_clk.common.cell,
    [CLK_RCPU2_PWM3]        = &rpwm3_clk.common.cell,
    [CLK_RCPU2_PWM4]        = &rpwm4_clk.common.cell,
    [CLK_RCPU2_PWM5]        = &rpwm5_clk.common.cell,
    [CLK_RCPU2_PWM6]        = &rpwm6_clk.common.cell,
    [CLK_RCPU2_PWM7]        = &rpwm7_clk.common.cell,
    [CLK_RCPU2_PWM8]        = &rpwm8_clk.common.cell,
    [CLK_RCPU2_PWM9]        = &rpwm9_clk.common.cell,
    [CLK_AUDIO_APB]         = &audio_apb_clk.common.cell,
    [CLK_AUDIO_AXI]         = &audio_axi_clk.common.cell,
    [CLK_PM_MN_SRC]         = &mn_src_clk.common.cell,
    [CLK_PM_MN]             = &mn_clk.common.cell,
    [CLK_PM_MN2_SRC]        = &mn2_src_clk.common.cell,
    [CLK_PM_MN2]            = &mn2_clk.common.cell,
};

static rt_err_t spacemit_k1x_ccu_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    int reg_count;
    struct ccu_common *common;
    struct rt_clk *clk;
    struct rt_clk_cell *cell;
    struct rt_device *dev = &pdev->parent;
    struct k1x_clk *kclk = rt_calloc(1, sizeof(*kclk));

    if (!kclk)
    {
        return -RT_ENOMEM;
    }

    reg_count = rt_dm_dev_get_address_count(dev);

    for (int i = 0; i < reg_count; ++i)
    {
        kclk->mmio[i] = rt_dm_dev_iomap(dev, i);

        if (!kclk->mmio[i])
        {
            err = -RT_EIO;
            goto _fail;
        }
    }

    for (int i = 0; i < RT_ARRAY_SIZE(spacemit_k1x_ccu_cell); ++i)
    {
        if (!(cell = spacemit_k1x_ccu_cell[i]))
        {
            continue;
        }

        common = cell_to_ccu_common(cell);

        common->lock = &k1_cru_lock;

        if (common->base_type < reg_count)
        {
            common->base = kclk->mmio[common->base_type];
        }
        else
        {
            common->base = kclk->apbc_base;
        }

        if (common->is_pll)
        {
            struct ccu_pll *pll = rt_container_of(common, struct ccu_pll, common);

            pll->pll.lock_base = kclk->mpmu_base;
        }
    }

    kclk->parent.dev = dev;
    kclk->parent.cells = spacemit_k1x_ccu_cell;
    kclk->parent.cells_nr = RT_ARRAY_SIZE(spacemit_k1x_ccu_cell);

    if ((err = rt_clk_register(&kclk->parent)))
    {
        goto _fail;
    }

    /* Enable some clocks */
    for (int i = 0; i < RT_ARRAY_SIZE(bootup_enable_clk_table); ++i)
    {
        cell = spacemit_k1x_ccu_cell[bootup_enable_clk_table[i]];

        if (cell && (clk = rt_clk_cell_get_clk(cell, RT_NULL)))
        {
            rt_clk_prepare_enable(clk);
        }
    }

    /* Init some clocks' rate */
    for (int i = 0; i < RT_ARRAY_SIZE(bootup_set_rate_clk_table); ++i)
    {
        cell = spacemit_k1x_ccu_cell[bootup_set_rate_clk_table[i++]];

        if (cell && (clk = rt_clk_cell_get_clk(cell, RT_NULL)))
        {
            rt_clk_set_rate(clk, bootup_set_rate_clk_table[i]);
        }
    }

    return RT_EOK;

_fail:
    for (int i = 0; i < CRU_BASE_TYPE_AUDC; ++i)
    {
        if (kclk->mmio[i])
        {
            rt_iounmap(kclk->mmio[i]);
        }
    }

    rt_free(kclk);

    return err;
}

static const struct rt_ofw_node_id spacemit_k1x_ccu_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-clock" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_k1x_ccu_driver =
{
    .name = "clk-spacemit-k1x",
    .ids = spacemit_k1x_ccu_ofw_ids,

    .probe = spacemit_k1x_ccu_probe,
};

static int spacemit_k1x_ccu_register(void)
{
    rt_platform_driver_register(&spacemit_k1x_ccu_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_k1x_ccu_register);
