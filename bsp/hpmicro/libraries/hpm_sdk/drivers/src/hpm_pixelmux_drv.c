/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_pixelmux_drv.h"

void pixelmux_rgb_data_source_enable(pixelmux_rgb_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_RGB_SEL_MASK) |
                        PIXELMUX_PIXMUX_RGB_EN_MASK | PIXELMUX_PIXMUX_RGB_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_rgb_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_RGB_SEL_MASK;
}

void pixelmux_gwc1_data_source_enable(pixelmux_gwc1_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_GWC1_SEL_MASK) |
                        PIXELMUX_PIXMUX_GWC1_EN_MASK | PIXELMUX_PIXMUX_GWC1_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_gwc1_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_GWC1_EN_MASK;
}

void pixelmux_gwc0_data_source_enable(pixelmux_gwc0_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_GWC0_SEL_MASK) |
                        PIXELMUX_PIXMUX_GWC0_EN_MASK | PIXELMUX_PIXMUX_GWC0_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_gwc0_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_GWC0_EN_MASK;
}

void pixelmux_lvb_di1_data_source_enable(pixelmux_lvb_di1_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_LVB_DI1_SEL_MASK) |
                        PIXELMUX_PIXMUX_LVB_DI1_EN_MASK | PIXELMUX_PIXMUX_LVB_DI1_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_lvb_di1_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_LVB_DI1_EN_MASK;
}

void pixelmux_lvb_di0_data_source_enable(pixelmux_lvb_di0_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_LVB_DI0_SEL_MASK) |
                        PIXELMUX_PIXMUX_LVB_DI0_EN_MASK | PIXELMUX_PIXMUX_LVB_DI0_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_lvb_di0_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_LVB_DI0_EN_MASK;
}

void pixelmux_mipi_dsi1_data_source_enable(pixelmux_mipi_dsi1_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_DSI1_SEL_MASK) |
                        PIXELMUX_PIXMUX_DSI1_EN_MASK | PIXELMUX_PIXMUX_DSI1_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_mipi_dsi1_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_DSI1_EN_MASK;
}

void pixelmux_mipi_dsi0_data_source_enable(pixelmux_mipi_dsi0_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_DSI0_SEL_MASK) |
                        PIXELMUX_PIXMUX_DSI0_EN_MASK | PIXELMUX_PIXMUX_DSI0_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_mipi_dsi0_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_DSI0_EN_MASK;
}

void pixelmux_mipi_dsi1_set_data_type(pixelmux_mipi_dsi_data_type_t type)
{

    HPM_PIXEL_MUX->DSI_SETTING[1] = PIXELMUX_DSI_SETTING_DSI_DATA_ENABLE_SET(0x01u<<type) |
                                    PIXELMUX_DSI_SETTING_DSI_DATA_TYPE_SET(type);
}

void pixelmux_mipi_dsi0_set_data_type(pixelmux_mipi_dsi_data_type_t type)
{

    HPM_PIXEL_MUX->DSI_SETTING[0] = PIXELMUX_DSI_SETTING_DSI_DATA_ENABLE_SET(0x01u<<type) |
                                    PIXELMUX_DSI_SETTING_DSI_DATA_TYPE_SET(type);
}

void pixelmux_cam1_data_source_enable(pixelmux_cam1_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_CAM1_SEL_MASK) |
                        PIXELMUX_PIXMUX_CAM1_EN_MASK | PIXELMUX_PIXMUX_CAM1_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_cam1_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_CAM1_EN_MASK;
}

void pixelmux_cam0_data_source_enable(pixelmux_cam0_select_t src)
{
    uint32_t reg_val = (HPM_PIXEL_MUX->PIXMUX & ~PIXELMUX_PIXMUX_CAM0_SEL_MASK) |
                        PIXELMUX_PIXMUX_CAM0_EN_MASK | PIXELMUX_PIXMUX_CAM0_SEL_SET(src);
    HPM_PIXEL_MUX->PIXMUX = reg_val;
}

void pixelmux_cam0_data_source_disable(void)
{
    HPM_PIXEL_MUX->PIXMUX &= ~PIXELMUX_PIXMUX_CAM0_EN_MASK;
}

hpm_stat_t pixelmux_lvds_phy_calc_pll_cfg(uint32_t pixel_freq_hz, bool is_split, lvds_phy_clk_param_t *param)
{
    uint32_t hsclk_freq_hz;
    uint32_t data_rate_div4;
    uint64_t fvco_freq_hz;
    uint32_t fvco_fraction_freq_hz;
    uint32_t lvds_rpck = is_split ? pixel_freq_hz / 2 : pixel_freq_hz;
    uint32_t lane_data_rate_hz = lvds_rpck * 7;
    uint32_t rate_lvds;
    uint32_t pfd_freq_hz;
    uint32_t pll_div_integer; /*pll_div[14:10]*/
    uint32_t pll_div_fraction; /*pll_div[9:0]*/
    int refclk_div;

    if (lvds_rpck / 16 > PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MAX ||
        lvds_rpck < PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MIN) {
        return status_invalid_argument;
    }

    if (lane_data_rate_hz < PIXELMUX_LVDS_TX_PHY_VCO_FREQ_MIN / (8 * 4) ||
        lane_data_rate_hz > PIXELMUX_LVDS_TX_PHY_DATA_LANE_FREQ_MAX) {
        return status_invalid_argument;
    }

    data_rate_div4 = 1;
    if (lane_data_rate_hz > PIXELMUX_LVDS_TX_PHY_VCO_FREQ_MAX / 4) {
        data_rate_div4 = 0;
    }

    hsclk_freq_hz = data_rate_div4 ? lane_data_rate_hz * 4 : lane_data_rate_hz;
    rate_lvds = 0;
    fvco_freq_hz = 0;
    while (rate_lvds <= 3) {
        fvco_freq_hz = (uint64_t)hsclk_freq_hz * (1<<rate_lvds);
        if (fvco_freq_hz >= PIXELMUX_LVDS_TX_PHY_VCO_FREQ_MIN) {
            break;
        }
        rate_lvds++;
    }

    if (rate_lvds > 3 || fvco_freq_hz > PIXELMUX_LVDS_TX_PHY_VCO_FREQ_MAX) {
        return status_invalid_argument;
    }

    refclk_div = 15;
    pfd_freq_hz = 0;
    while (refclk_div >= 0) {
        pfd_freq_hz = lvds_rpck / (refclk_div + 1);
        if (pfd_freq_hz >= PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MIN) {
            break;
        }
        refclk_div--;
    }

    if (refclk_div < 0 || pfd_freq_hz < PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MIN) {
        return status_invalid_argument;
    }

    while (refclk_div >= 0 && pfd_freq_hz < PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MAX) {
        pfd_freq_hz = lvds_rpck / (refclk_div + 1);
        if (fvco_freq_hz / 8 / pfd_freq_hz <= 23) {
            break;
        }
        refclk_div--;
    }

    if (refclk_div < 0 || pfd_freq_hz > PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MAX ||
        (fvco_freq_hz / 8 / pfd_freq_hz) > 23 || (fvco_freq_hz / 8 / pfd_freq_hz) < 6) {
        return status_invalid_argument;
    }

    pll_div_integer = fvco_freq_hz / 8 / pfd_freq_hz;
    fvco_fraction_freq_hz = fvco_freq_hz - pfd_freq_hz * pll_div_integer * 8;
    pll_div_fraction = (fvco_fraction_freq_hz * 1024) / 8 / pfd_freq_hz;

    param->reg.rate_lvds = rate_lvds;
    param->reg.data_rate_div4 = data_rate_div4;
    param->reg.refclk_div = refclk_div;
    param->reg.pll_div = pll_div_integer<<10 | pll_div_fraction;
    param->fvco_freq_hz = fvco_freq_hz;
    param->pfd_freq_hz = pfd_freq_hz;
    param->lane_data_rate_hz = lane_data_rate_hz;
    param->hsclk_freq_hz = hsclk_freq_hz;

    return status_success;
}

void pixelmux_config_tx_phy0_mode(pixelmux_tx_phy_mode_t mode)
{
    HPM_PIXEL_MUX->GPR_WR_D2 = (HPM_PIXEL_MUX->GPR_WR_D2 &
                                ~PIXELMUX_GPR_WR_D2_TX_PHY0_PHY_MODE_MASK) |
                                PIXELMUX_GPR_WR_D2_TX_PHY0_PHY_MODE_SET(mode);
}

void pixelmux_config_tx_phy1_mode(pixelmux_tx_phy_mode_t mode)
{
    HPM_PIXEL_MUX->GPR_WR_D5 = (HPM_PIXEL_MUX->GPR_WR_D5 &
                                ~PIXELMUX_GPR_WR_D5_TX_PHY1_PHY_MODE_MASK) |
                                PIXELMUX_GPR_WR_D5_TX_PHY1_PHY_MODE_SET(mode);
}

void pixelmux_config_lvds_tx_phy0_clk(const lvds_phy_clk_reg_t *clk_reg)
{
    HPM_PIXEL_MUX->GPR_WR_D2 = (HPM_PIXEL_MUX->GPR_WR_D2 &
                                ~(PIXELMUX_GPR_WR_D2_TX_PHY0_PORT_PLL_RDY_SEL_MASK |
                                PIXELMUX_GPR_WR_D2_TX_PHY0_RATE_LVDS_MASK |
                                PIXELMUX_GPR_WR_D2_TX_PHY0_PLL_DIV_MASK |
                                PIXELMUX_GPR_WR_D2_TX_PHY0_REFCLK_DIV_MASK)) |
                                PIXELMUX_GPR_WR_D2_TX_PHY0_RATE_LVDS_SET(clk_reg->rate_lvds) |
                                PIXELMUX_GPR_WR_D2_TX_PHY0_REFCLK_DIV_SET(clk_reg->refclk_div) |
                                PIXELMUX_GPR_WR_D2_TX_PHY0_PLL_DIV_SET(clk_reg->pll_div);

    /*
     * lvds_rpck/refclk control signal
     *  0: normal
     *  1: inverter
     */
    HPM_PIXEL_MUX->GPR_WR_D3 &= ~(0x01ul<<29);

    /*
     * ckphy_ctl[2:0]:CLK_PHY divide ratio select, must be 010:div7
     * ckphy_ctl[8]:div4 enable signal
     */
    HPM_PIXEL_MUX->GPR_WR_D4 = (HPM_PIXEL_MUX->GPR_WR_D4 & ~PIXELMUX_GPR_WR_D4_TX_PHY0_CKPHY_CTL_MASK) |
                                PIXELMUX_GPR_WR_D4_TX_PHY0_CKPHY_CTL_SET((clk_reg->data_rate_div4 & 0x01)<<8 | 0x02);
}

void pixelmux_config_lvds_tx_phy1_clk(const lvds_phy_clk_reg_t *clk_reg)
{
    HPM_PIXEL_MUX->GPR_WR_D5 = (HPM_PIXEL_MUX->GPR_WR_D5 &
                                ~(PIXELMUX_GPR_WR_D5_TX_PHY1_PORT_PLL_RDY_SEL_MASK |
                                PIXELMUX_GPR_WR_D5_TX_PHY1_RATE_LVDS_MASK |
                                PIXELMUX_GPR_WR_D5_TX_PHY1_PLL_DIV_MASK |
                                PIXELMUX_GPR_WR_D5_TX_PHY1_REFCLK_DIV_MASK)) |
                                PIXELMUX_GPR_WR_D5_TX_PHY1_RATE_LVDS_SET(clk_reg->rate_lvds) |
                                PIXELMUX_GPR_WR_D5_TX_PHY1_REFCLK_DIV_SET(clk_reg->refclk_div) |
                                PIXELMUX_GPR_WR_D5_TX_PHY1_PLL_DIV_SET(clk_reg->pll_div);
    /*
     * lvds_rpck/refclk control signal
     *  0: normal
     *  1: inverter
     */
    HPM_PIXEL_MUX->GPR_WR_D6 &= ~(0x01ul<<29);

    /*
     * ckphy_ctl[2:0]:CLK_PHY divide ratio select, must be 010:div7
     * ckphy_ctl[8]:div4 enable signal
     */
    HPM_PIXEL_MUX->GPR_WR_D7 = (HPM_PIXEL_MUX->GPR_WR_D7 & ~PIXELMUX_GPR_WR_D7_TX_PHY1_CKPHY_CTL_MASK) |
                                PIXELMUX_GPR_WR_D7_TX_PHY1_CKPHY_CTL_SET((clk_reg->data_rate_div4 & 0x01)<<8 | 0x02);
}

void pixelmux_config_rx_phy0_mode(pixelmux_rx_phy_mode_t mode)
{
    HPM_PIXEL_MUX->GPR_WR_D8 = (HPM_PIXEL_MUX->GPR_WR_D8 &
                                ~PIXELMUX_GPR_WR_D8_RX_PHY0_PHY_MODE_MASK) |
                                PIXELMUX_GPR_WR_D8_RX_PHY0_PHY_MODE_SET(mode);
}

void pixelmux_config_rx_phy1_mode(pixelmux_rx_phy_mode_t mode)
{
    HPM_PIXEL_MUX->GPR_WR_D9 = (HPM_PIXEL_MUX->GPR_WR_D9 &
                                ~PIXELMUX_GPR_WR_D9_RX_PHY1_PHY_MODE_MASK) |
                                PIXELMUX_GPR_WR_D9_RX_PHY1_PHY_MODE_SET(mode);
}