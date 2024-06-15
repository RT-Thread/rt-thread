/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mipi_dsi_phy_drv.h"

typedef struct mipi_phy_clk_reg {
    uint32_t rate; /*!< rate[2:0] */
    uint32_t pll_div; /*!< pll_div[14:0] */
} mipi_phy_clk_reg_t;

#define MIPI_DSI_PHY_RATE_MAX 4
#define MIPI_DSI_PHY_REFCLK_FREQ_MHZ 24UL
#define MIPI_DSI_PHY_VCO_FREQ_MAX 4000UL
#define MIPI_DSI_PHY_PHY_VCO_FREQ_MIN 1600UL

hpm_stat_t mipi_pll_get_cfg(uint32_t lane_mbps, mipi_phy_clk_reg_t *reg)
{
    uint32_t fvco_freq_mhz = lane_mbps;
    uint32_t fvco_fraction_freq_mhz;
    uint32_t rate = 0;
    uint32_t pll_div_integer; /*pll_div[14:10]*/
    uint32_t pll_div_fraction; /*pll_div[9:0]*/

    while (fvco_freq_mhz < MIPI_DSI_PHY_PHY_VCO_FREQ_MIN) {
        rate++;
        fvco_freq_mhz = lane_mbps * (1<<rate);
    }

    if (rate > 4) {
        return status_invalid_argument;
    }

    pll_div_integer = fvco_freq_mhz / 8 / MIPI_DSI_PHY_REFCLK_FREQ_MHZ;
    fvco_fraction_freq_mhz = fvco_freq_mhz - (pll_div_integer * 8 * MIPI_DSI_PHY_REFCLK_FREQ_MHZ);
    pll_div_fraction = (fvco_fraction_freq_mhz * 1024 + (8 * MIPI_DSI_PHY_REFCLK_FREQ_MHZ) / 2) /\
                         (8 * MIPI_DSI_PHY_REFCLK_FREQ_MHZ);

    reg->rate = rate;
    reg->pll_div = pll_div_integer<<10 | pll_div_fraction;

    return status_success;
}

static bool mipi_dsi_phy_pll_init(MIPI_DSI_PHY_Type *ptr, uint32_t lane_mbps)
{
    hpm_stat_t state;
    mipi_phy_clk_reg_t reg;
    state = mipi_pll_get_cfg(lane_mbps, &reg);
    if (state == status_invalid_argument)
        return false;


    ptr->PLL_CTRL_PARA0 = (HPM_MIPI_DSI_PHY0->PLL_CTRL_PARA0 &\
                            ~(MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_MASK |
                                MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_MASK |
                                MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_MASK)) |
                                MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_SET(reg.rate) |
                                MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_SET(0) |
                                MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_SET(reg.pll_div);
    return true;
}

void mipi_dsi_phy_init(MIPI_DSI_PHY_Type *ptr, mipi_dsi_phy_config_t *cfg)
{
    uint32_t byteclk_period_ps = 1000000u / (cfg->lane_mbps / 8);
    uint32_t ui_ps = 1000000u / cfg->lane_mbps;

    ptr->TEST_PARA0 |= 1u<<3;
    mipi_dsi_phy_pll_init(ptr, cfg->lane_mbps);
    ptr->MISC_PARA = (ptr->MISC_PARA & ~(MIPI_DSI_PHY_MISC_PARA_LANE_NUM_MASK)) |
                        MIPI_DSI_PHY_MISC_PARA_LANE_NUM_SET(cfg->lanes - 1);

    uint32_t tlpx_ps = 50 * 1000; /* min: 50ns */
    ptr->COMMON_PARA0 = HPM_DIV_ROUND_UP(tlpx_ps, byteclk_period_ps) - 1;

    uint32_t tclk_prepare_ps = (38 + 95) * 1000 / 2; /* min: 38ns, max: 95ns */
    uint32_t tclk_zero_ps = 300 * 1000 - tclk_prepare_ps; /* min: 300ns */
    uint32_t tclk_pre_ps = 8* ui_ps; /* min: 8 * UI */
    uint32_t t_clk_post_ps = 60 * 1000 + 52 * ui_ps; /* min: 60ns + 52 * UI */
    uint32_t t_clk_trail_ps = 60 * 1000; /* min: 60ns */
    uint32_t t_hs_exit_ps = 100 * 1000; /* min: 100ns */

    ptr->CLANE_PARA2 = MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_SET(HPM_DIV_ROUND_UP(tclk_prepare_ps, byteclk_period_ps) - 1) |
            MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_SET(HPM_DIV_ROUND_UP(tclk_zero_ps, byteclk_period_ps) - 1) |
            MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_SET(HPM_DIV_ROUND_UP(tclk_pre_ps, byteclk_period_ps) - 1);

    ptr->CLANE_PARA3 = MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_SET(HPM_DIV_ROUND_UP(t_clk_post_ps, byteclk_period_ps) - 1) |
            MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_SET(HPM_DIV_ROUND_UP(t_clk_trail_ps, byteclk_period_ps) - 1);


    uint32_t dlane0_para2;
    uint32_t ths_prepare_ps = (40 + 85) / 2 * 1000 + (4 + 6) / 2 * ui_ps; /* min: 40ns + 4 * UI, max: 85ns + 6 * UI */
    uint32_t ths_zero_ps = 145 * 1000 + 10 * ui_ps - ths_prepare_ps; /* min: 145ns + 10 * UI */
    uint32_t ths_trail_ps0 = 8 * ui_ps;
    uint32_t ths_trail_ps1 = 60 * 1000 * 4 * ui_ps;
    uint32_t ths_trail_ps = ths_trail_ps0 > ths_trail_ps1 ? ths_trail_ps0 : ths_trail_ps1;

    dlane0_para2 = MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_SET(HPM_DIV_ROUND_UP(ths_prepare_ps, byteclk_period_ps) - 1) |
                    MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_SET(HPM_DIV_ROUND_UP(ths_zero_ps, byteclk_period_ps) - 1) |
                    MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_SET(HPM_DIV_ROUND_UP(ths_trail_ps, byteclk_period_ps) - 1) |
                    MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_SET(HPM_DIV_ROUND_UP(t_hs_exit_ps, byteclk_period_ps) - 1);

    ptr->DLANE0_PARA2 = dlane0_para2;
    ptr->DLANE1_PARA2 = dlane0_para2;
    ptr->DLANE2_PARA2 = dlane0_para2;
    ptr->DLANE3_PARA2 = dlane0_para2;

    uint32_t ta_go_ps = 4 * tlpx_ps; /* 4 * Tlpx */
    uint32_t ta_sure_ps = tlpx_ps; /* min: Tlpx, max: 2 * Tlpx */
    uint32_t ta_get_ps = 5 * tlpx_ps; /* 4 * Tlpx */

    ptr->DLANE0_PARA4 = MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_SET(HPM_DIV_ROUND_UP(ta_go_ps, byteclk_period_ps) - 1) |
                            MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_SET(HPM_DIV_ROUND_UP(ta_sure_ps, byteclk_period_ps) - 1) |
                            MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_SET(HPM_DIV_ROUND_UP(ta_get_ps, byteclk_period_ps) - 1);

}