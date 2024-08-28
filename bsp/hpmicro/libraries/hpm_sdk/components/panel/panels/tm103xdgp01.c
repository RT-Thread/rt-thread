/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_panel.h"
#include "hpm_pixelmux_drv.h"
#include "hpm_lvb_drv.h"

static void lvds_panel_lvb_init(hpm_panel_t *panel)
{
    LVB_Type *lvb_base = panel->hw_if.video.lvds.lvb_base;
    lvb_config_t lvb_config;
    lvb_get_default_config(&lvb_config);

    lvb_config.split_mode_en = true;
    lvb_config.txclk_shift = lvb_txclk_shift_1100011;
    lvb_init(lvb_base, &lvb_config);

    lvb_ch_config_t lvb_ch_cfg;
    lvb_ch_cfg.map = lvb_ch_mapping_vesa;

    if (panel->hw_if.video.lvds.channel_di_index == 0)
        lvb_ch_cfg.data_src = lvb_ch_data_source_di0;
    else
        lvb_ch_cfg.data_src = lvb_ch_data_source_di1;

    lvb_ch_config(lvb_base, lvb_ch_num_0, &lvb_ch_cfg);
    lvb_ch_config(lvb_base, lvb_ch_num_1, &lvb_ch_cfg);

    lvb_ch_enable(lvb_base, lvb_ch_num_0);
    lvb_ch_enable(lvb_base, lvb_ch_num_1);
}

static void lvds_panel_phy_init(hpm_panel_t *panel)
{
    LVB_Type *lvb_base = panel->hw_if.video.lvds.lvb_base;
    lvds_phy_clk_param_t param;
    uint32_t pixel_clk = panel->hw_if.lcdc_pixel_clk_khz * 1000;
    pixelmux_lvds_phy_calc_pll_cfg(pixel_clk, true, &param);
    pixelmux_config_lvds_tx_phy0_clk(&param.reg);
    pixelmux_config_lvds_tx_phy1_clk(&param.reg);

    lvb_lvds_phy_lane_config_t lvds_lane_cfg;
    lvb_lvds_phy_lane_get_default_config(&lvds_lane_cfg);
    lvds_lane_cfg.fvco_div4 = param.reg.data_rate_div4;
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds0_tx0, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds0_tx1, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds0_tx2, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds0_tx3, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds0_txck, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds1_tx0, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds1_tx1, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds1_tx2, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds1_tx3, &lvds_lane_cfg);
    lvb_lvds_phy_lane_init(lvb_base, lvb_lvds_lane_idx_lvds1_txck, &lvds_lane_cfg);

    lvb_lvds_phy0_poweron(lvb_base);
    lvb_lvds_phy1_poweron(lvb_base);

    while (lvb_lvds_phy_split_pll_is_lock(lvb_base) == false) {
    }
}

static void reset(hpm_panel_t *panel)
{
    if (!panel->hw_if.set_reset_pin_level)
        return;

    panel->hw_if.set_reset_pin_level(0);
    hpm_panel_delay_us(2000);

    panel->hw_if.set_reset_pin_level(1);
    hpm_panel_delay_us(2000);
}

static void init(hpm_panel_t *panel)
{
    if (panel->hw_if.set_video_router)
        panel->hw_if.set_video_router();

    lvds_panel_lvb_init(panel);
    lvds_panel_phy_init(panel);
}

hpm_panel_t panel_tm103xdgp01 = {
    .name = "tm103xdgp01",
    .if_type = HPM_PANEL_IF_TYPE_LVDS_SPLIT,
    .timing = {
        .pixel_clock_khz = 45000,
        .hactive = 1920,
        .hfront_porch = 32,
        .hback_porch = 32,
        .hsync_len = 64,

        .vactive = 720,
        .vfront_porch = 2,
        .vback_porch = 2,
        .vsync_len = 4,
    },
    .funcs = {
        .reset = reset,
        .init = init,
    },
};

