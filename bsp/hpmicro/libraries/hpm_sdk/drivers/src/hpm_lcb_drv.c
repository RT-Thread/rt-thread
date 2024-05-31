/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_lcb_drv.h"

void lcb_get_default_config(lcb_config_t *cfg)
{
    cfg->mode = lcb_mode_display;
    cfg->rxclk_sel = lcb_rxclk_sel_phy0;
    cfg->display.data_width = lcb_display_mode_data_width_24bit;
    cfg->display.map = lcb_display_mode_mapping_vesa;
}

void lcb_init(LCB_Type *ptr, lcb_config_t *cfg)
{
    uint32_t reg_val;

    if (cfg->mode == lcb_mode_display)
        reg_val = (ptr->CTRL & ~(LCB_CTRL_LVDS_RXCK_SEL_MASK |
                    LCB_CTRL_MODE_MASK |
                    LCB_CTRL_DATA_WIDTH_MASK |
                    LCB_CTRL_BIT_MAPPING_MASK)) |
                    LCB_CTRL_MODE_SET(cfg->mode) |
                    LCB_CTRL_LVDS_RXCK_SEL_SET(cfg->rxclk_sel) |
                    LCB_CTRL_DATA_WIDTH_SET(cfg->display.data_width) |
                    LCB_CTRL_BIT_MAPPING_SET(cfg->display.map);
    else
        reg_val = (ptr->CTRL & ~(LCB_CTRL_LVDS_RXCK_SEL_MASK |
                    LCB_CTRL_MODE_MASK |
                    LCB_CTRL_CAM_LINK_WIDTH_MASK)) |
                    LCB_CTRL_MODE_SET(cfg->mode) |
                    LCB_CTRL_LVDS_RXCK_SEL_SET(cfg->rxclk_sel) |
                    LCB_CTRL_CAM_LINK_WIDTH_SET(cfg->cam_link.data_width);

    ptr->CTRL = reg_val;
}

void lcb_get_phy_clk_lane_default_config(lcb_lvds_phy_clk_lane_config_t *cfg)
{
    cfg->rterm = lcb_lvds_phy_rterm_100_ohm;
    cfg->min_adj = lcb_lvds_phy_dll_delay_adj_min_freq_70_110mhz;
    cfg->dll_tuning_int = 0x1FFU;
}

void lcb_get_phy_data_lane_default_config(lcb_lvds_phy_data_lane_config_t *cfg)
{
    cfg->rterm = lcb_lvds_phy_rterm_100_ohm;
    cfg->dline_adj = 0x41;
}

void lcb_lvds_phy0_data_lane_config(LCB_Type *ptr, lcb_lvds_phy_data_lane_config_t *cfg, lcb_lvds_phy_data_lane_id_t lane_id)
{
    ptr->PHY_D_CTRL[lane_id] = (ptr->PHY_D_CTRL[lane_id] & ~(LCB_PHY_D_CTRL_RX_RTERM_MASK)) |
                                LCB_PHY_D_CTRL_RX_RTERM_SET(cfg->rterm);

    if (lane_id == lcb_lvds_phy_data_lane_id_0)
        ptr->PHY_ADJ_CTRL[0] = (ptr->PHY_ADJ_CTRL[0] & ~(LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_MASK)) |
                                LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_SET(cfg->dline_adj);
    else if (lane_id == lcb_lvds_phy_data_lane_id_1)
        ptr->PHY_ADJ_CTRL[0] = (ptr->PHY_ADJ_CTRL[0] & ~(LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_MASK)) |
                                LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_SET(cfg->dline_adj);
}

void lcb_lvds_phy0_clk_lane_config(LCB_Type *ptr, lcb_lvds_phy_clk_lane_config_t *cfg)
{
    ptr->PHY_CK_CTRL[0] = (ptr->PHY_CK_CTRL[0] & ~(LCB_PHY_CK_CTRL_RX_RTERM_MASK | 0x0001)) |
                            LCB_PHY_CK_CTRL_RX_RTERM_SET(cfg->rterm) |
                            (uint32_t)cfg->min_adj;

    ptr->PHY_ADJ_CTRL[0] = (ptr->PHY_ADJ_CTRL[0] & ~(LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_MASK)) |
                            LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_SET(cfg->dll_tuning_int);
}

void lcb_lvds_phy1_data_lane_config(LCB_Type *ptr, lcb_lvds_phy_data_lane_config_t *cfg, lcb_lvds_phy_data_lane_id_t lane_id)
{
    ptr->PHY_D_CTRL[lane_id + 2] = (ptr->PHY_D_CTRL[lane_id + 2] & ~(LCB_PHY_D_CTRL_RX_RTERM_MASK)) |
                                LCB_PHY_D_CTRL_RX_RTERM_SET(cfg->rterm);

    if (lane_id == lcb_lvds_phy_data_lane_id_0)
        ptr->PHY_ADJ_CTRL[1] = (ptr->PHY_ADJ_CTRL[1] & ~(LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_MASK)) |
                                LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_SET(cfg->dline_adj);
    else if (lane_id == lcb_lvds_phy_data_lane_id_1)
        ptr->PHY_ADJ_CTRL[1] = (ptr->PHY_ADJ_CTRL[1] & ~(LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_MASK)) |
                                LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_SET(cfg->dline_adj);
}

void lcb_lvds_phy1_clk_lane_config(LCB_Type *ptr, lcb_lvds_phy_clk_lane_config_t *cfg)
{
    ptr->PHY_CK_CTRL[1] = (ptr->PHY_CK_CTRL[1] & ~(LCB_PHY_CK_CTRL_RX_RTERM_MASK | 0x0001)) |
                            LCB_PHY_CK_CTRL_RX_RTERM_SET(cfg->rterm) |
                            (uint32_t)cfg->min_adj;

    ptr->PHY_ADJ_CTRL[1] = (ptr->PHY_ADJ_CTRL[1] & ~(LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_MASK)) |
                            LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_SET(cfg->dll_tuning_int);
}

void lcb_lvds_phy0_poweron(LCB_Type *ptr)
{
    ptr->PHY_POW_CTRL[0] &= ~(LCB_PHY_POW_CTRL_IDDQ_EN_MASK |
                                LCB_PHY_POW_CTRL_RXCK_PD_MASK |
                                LCB_PHY_POW_CTRL_RX1_PD_MASK |
                                LCB_PHY_POW_CTRL_RX0_PD_MASK);
}

void lcb_lvds_phy1_poweron(LCB_Type *ptr)
{
    ptr->PHY_POW_CTRL[1] &= ~(LCB_PHY_POW_CTRL_IDDQ_EN_MASK |
                                LCB_PHY_POW_CTRL_RXCK_PD_MASK |
                                LCB_PHY_POW_CTRL_RX1_PD_MASK |
                                LCB_PHY_POW_CTRL_RX0_PD_MASK);
}

void lcb_lvds_phy0_powerdown(LCB_Type *ptr)
{
    ptr->PHY_POW_CTRL[0] |= (LCB_PHY_POW_CTRL_IDDQ_EN_MASK |
                                LCB_PHY_POW_CTRL_RXCK_PD_MASK |
                                LCB_PHY_POW_CTRL_RX1_PD_MASK |
                                LCB_PHY_POW_CTRL_RX0_PD_MASK);
}

void lcb_lvds_phy1_powerdown(LCB_Type *ptr)
{
    ptr->PHY_POW_CTRL[1] |= (LCB_PHY_POW_CTRL_IDDQ_EN_MASK |
                                LCB_PHY_POW_CTRL_RXCK_PD_MASK |
                                LCB_PHY_POW_CTRL_RX1_PD_MASK |
                                LCB_PHY_POW_CTRL_RX0_PD_MASK);
}