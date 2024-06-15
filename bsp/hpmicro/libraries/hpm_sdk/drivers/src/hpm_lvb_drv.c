/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_lvb_drv.h"

void lvb_get_default_config(lvb_config_t *cfg)
{
    cfg->split_ch_is_reverse = false;
    cfg->split_ch_data_is_unaligned = false;
    cfg->split_hswhbp_width_is_even = true;
    cfg->split_mode_en = false;
    cfg->di0_vsync_polarity = lvb_di_vsync_polarity_active_high;
    cfg->di1_vsync_polarity = lvb_di_vsync_polarity_active_high;
    cfg->txclk_shift = lvb_txclk_shift_1100011;
}

void lvb_init(LVB_Type *ptr, lvb_config_t *cfg)
{
    ptr->CTRL = (ptr->CTRL & ~(LVB_CTRL_SPLIT_CH_REVERSE_MASK |
                        LVB_CTRL_SPLIT_CH_MODE_MASK |
                        LVB_CTRL_SPLIT_HSWHBP_WIDTH_MASK |
                        LVB_CTRL_SPLIT_MODE_EN_MASK |
                        LVB_CTRL_DI1_VSYNC_POLARITY_MASK |
                        LVB_CTRL_DI0_VSYNC_POLARITY_MASK |
                        LVB_CTRL_LVDS_TXCLK_SHIFT_MASK)) |
                        LVB_CTRL_SPLIT_CH_REVERSE_SET(cfg->split_ch_is_reverse) |
                        LVB_CTRL_SPLIT_CH_MODE_SET(cfg->split_ch_data_is_unaligned) |
                        LVB_CTRL_SPLIT_HSWHBP_WIDTH_SET(cfg->split_hswhbp_width_is_even) |
                        LVB_CTRL_SPLIT_MODE_EN_SET(cfg->split_mode_en) |
                        LVB_CTRL_DI1_VSYNC_POLARITY_SET(cfg->di1_vsync_polarity) |
                        LVB_CTRL_DI0_VSYNC_POLARITY_SET(cfg->di0_vsync_polarity) |
                        LVB_CTRL_LVDS_TXCLK_SHIFT_SET(cfg->txclk_shift);
}

void lvb_get_ch_default_config(lvb_ch_config_t *ch_cfg)
{
    ch_cfg->data_src = lvb_ch_data_source_di0;
    ch_cfg->map = lvb_ch_mapping_vesa;
}

void lvb_ch_config(LVB_Type *ptr, lvb_ch_num_t ch_num, lvb_ch_config_t *ch_cfg)
{
    uint32_t reg_val;

    if (ch_num == lvb_ch_num_0) {
        reg_val = (ptr->CTRL & ~(LVB_CTRL_CH0_BIT_MAPPING_MASK | LVB_CTRL_CH0_SEL_MASK)) |
                LVB_CTRL_CH0_BIT_MAPPING_SET(ch_cfg->map) |
                LVB_CTRL_CH0_SEL_SET(ch_cfg->data_src);
    } else {
        reg_val = (ptr->CTRL & ~(LVB_CTRL_CH1_BIT_MAPPING_MASK | LVB_CTRL_CH1_SEL_MASK)) |
                LVB_CTRL_CH1_BIT_MAPPING_SET(ch_cfg->map) |
                LVB_CTRL_CH1_SEL_SET(ch_cfg->data_src);
    }

    ptr->CTRL = reg_val;
}

void lvb_ch_enable(LVB_Type *ptr, lvb_ch_num_t ch_num)
{
    if (ch_num == lvb_ch_num_0) {
        ptr->CTRL |= LVB_CTRL_CH0_EN_MASK;
    } else {
        ptr->CTRL |= LVB_CTRL_CH1_EN_MASK;
    }
}

void lvb_ch_disable(LVB_Type *ptr, lvb_ch_num_t ch_num)
{
    if (ch_num == lvb_ch_num_0) {
        ptr->CTRL &= ~LVB_CTRL_CH0_EN_MASK;
    } else {
        ptr->CTRL &= ~LVB_CTRL_CH1_EN_MASK;
    }
}

void lvb_lvds_phy_lane_get_default_config(lvb_lvds_phy_lane_config_t *cfg)
{
    cfg->tx_idle = false;
    cfg->rterm_enable = true;
    cfg->phase_sel = lvb_lvds_lane_phase_sel_4_16_ui;
    cfg->amp = lvb_lvds_lane_amp_300_mv;
    cfg->vcom = lvb_lvds_lane_vcom_1_2_v;
    cfg->fvco_div4 = true;
}

void lvb_lvds_phy_lane_init(LVB_Type *ptr, lvb_lvds_lane_idx_t tx_index, lvb_lvds_phy_lane_config_t *cfg)
{
    ptr->TX_PHY[tx_index].CTL0 = (ptr->TX_PHY[tx_index].CTL0 & ~(LVB_TX_PHY_CTL0_TX_IDLE_MASK |
                                    LVB_TX_PHY_CTL0_TX_RTERM_EN_MASK |
                                    LVB_TX_PHY_CTL0_TX_BUS_WIDTH_MASK |
                                    LVB_TX_PHY_CTL0_TX_PHASE_SEL_MASK |
                                    LVB_TX_PHY_CTL0_TX_VCOM_MASK |
                                    LVB_TX_PHY_CTL0_TX_AMP_MASK)) |
                                    (cfg->tx_idle ? LVB_TX_PHY_CTL0_TX_IDLE_MASK : 0) |
                                    (cfg->rterm_enable ? LVB_TX_PHY_CTL0_TX_RTERM_EN_MASK : 0) |
                                    LVB_TX_PHY_CTL0_TX_BUS_WIDTH_SET(2) | /* only 7bit */
                                    LVB_TX_PHY_CTL0_TX_PHASE_SEL_SET(cfg->phase_sel) |
                                    LVB_TX_PHY_CTL0_TX_VCOM_SET(cfg->vcom) |
                                    LVB_TX_PHY_CTL0_TX_AMP_SET(cfg->amp);

    if (cfg->fvco_div4) {
        ptr->TX_PHY[tx_index].CTL0 |= (1ul<<7);
    } else {
        ptr->TX_PHY[tx_index].CTL0 &= ~(1ul<<7);
    }
}

void lvb_lvds_phy0_poweron(LVB_Type *ptr)
{
    ptr->PHY_POW_CTRL[0] = (ptr->PHY_POW_CTRL[0] & ~(LVB_PHY_POW_CTRL_TXCK_PD_MASK |
                            LVB_PHY_POW_CTRL_TX3_PD_MASK | LVB_PHY_POW_CTRL_TX2_PD_MASK |
                            LVB_PHY_POW_CTRL_TX1_PD_MASK | LVB_PHY_POW_CTRL_TX0_PD_MASK)) |
                            LVB_PHY_POW_CTRL_PWON_PLL_MASK;
}

void lvb_lvds_phy1_poweron(LVB_Type *ptr)
{
    ptr->PHY_POW_CTRL[1] = (ptr->PHY_POW_CTRL[1] & ~(LVB_PHY_POW_CTRL_TXCK_PD_MASK |
                            LVB_PHY_POW_CTRL_TX3_PD_MASK | LVB_PHY_POW_CTRL_TX2_PD_MASK |
                            LVB_PHY_POW_CTRL_TX1_PD_MASK | LVB_PHY_POW_CTRL_TX0_PD_MASK)) |
                            LVB_PHY_POW_CTRL_PWON_PLL_MASK;
}

void lvb_lvds_phy0_powerdown(LVB_Type *ptr)
{
    ptr->PHY_POW_CTRL[0] = (ptr->PHY_POW_CTRL[0] & ~LVB_PHY_POW_CTRL_PWON_PLL_MASK) |
                            LVB_PHY_POW_CTRL_TXCK_PD_MASK | LVB_PHY_POW_CTRL_TX3_PD_MASK |
                            LVB_PHY_POW_CTRL_TX2_PD_MASK | LVB_PHY_POW_CTRL_TX1_PD_MASK |
                            LVB_PHY_POW_CTRL_TX0_PD_MASK;
}

void lvb_lvds_phy1_powerdown(LVB_Type *ptr)
{
    ptr->PHY_POW_CTRL[1] = (ptr->PHY_POW_CTRL[1] & ~LVB_PHY_POW_CTRL_PWON_PLL_MASK) |
                            LVB_PHY_POW_CTRL_TXCK_PD_MASK | LVB_PHY_POW_CTRL_TX3_PD_MASK |
                            LVB_PHY_POW_CTRL_TX2_PD_MASK | LVB_PHY_POW_CTRL_TX1_PD_MASK |
                            LVB_PHY_POW_CTRL_TX0_PD_MASK;
}