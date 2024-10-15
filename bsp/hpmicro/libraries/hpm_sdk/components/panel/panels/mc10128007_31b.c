/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_panel.h"
#include "hpm_pixelmux_drv.h"
#include "hpm_mipi_dsi_drv.h"
#include "hpm_mipi_dsi_phy_drv.h"
#include <stdio.h>

typedef struct mipi_cmd_list {
    uint16_t len;
    uint8_t cmd[4];
} mipi_cmd_list_t;

static const mipi_cmd_list_t mipi_panel_cmd[] = {
    {4, {0xFF, 0x98, 0x81, 0x03}},
    {2, {0x01, 0x00}},
    {2, {0x02, 0x00}},
    {2, {0x03, 0x55}},
    {2, {0x04, 0x55}},
    {2, {0x05, 0x03}},
    {2, {0x06, 0x06}},
    {2, {0x07, 0x00}},
    {2, {0x08, 0x07}},
    {2, {0x09, 0x00}},
    {2, {0x0A, 0x00}},
    {2, {0x0B, 0x00}},
    {2, {0x0C, 0x00}},
    {2, {0x0D, 0x00}},
    {2, {0x0E, 0x00}},
    {2, {0x0F, 0x00}},
    {2, {0x10, 0x00}},
    {2, {0x11, 0x00}},
    {2, {0x12, 0x00}},
    {2, {0x13, 0x00}},
    {2, {0x14, 0x00}},
    {2, {0x15, 0x00}},
    {2, {0x16, 0x00}},
    {2, {0x17, 0x00}},
    {2, {0x18, 0x00}},
    {2, {0x19, 0x00}},
    {2, {0x1A, 0x00}},
    {2, {0x1B, 0x00}},
    {2, {0x1C, 0x00}},
    {2, {0x1D, 0x00}},
    {2, {0x1E, 0xC0}},
    {2, {0x1F, 0x80}},
    {2, {0x20, 0x04}},
    {2, {0x21, 0x03}},
    {2, {0x22, 0x00}},
    {2, {0x23, 0x00}},
    {2, {0x24, 0x00}},
    {2, {0x25, 0x00}},
    {2, {0x26, 0x00}},
    {2, {0x27, 0x00}},
    {2, {0x28, 0x33}},
    {2, {0x29, 0x33}},
    {2, {0x2A, 0x00}},
    {2, {0x2B, 0x00}},
    {2, {0x2C, 0x00}},
    {2, {0x2D, 0x00}},
    {2, {0x2E, 0x00}},
    {2, {0x2F, 0x00}},
    {2, {0x30, 0x00}},
    {2, {0x31, 0x00}},
    {2, {0x32, 0x00}},
    {2, {0x33, 0x00}},
    {2, {0x34, 0x04}},
    {2, {0x35, 0x00}},
    {2, {0x36, 0x00}},
    {2, {0x37, 0x00}},
    {2, {0x38, 0x3C}},
    {2, {0x39, 0x00}},
    {2, {0x3A, 0x00}},
    {2, {0x3B, 0x00}},
    {2, {0x3C, 0x00}},
    {2, {0x3D, 0x00}},
    {2, {0x3E, 0x00}},
    {2, {0x3F, 0x00}},
    {2, {0x40, 0x00}},
    {2, {0x41, 0x00}},
    {2, {0x42, 0x00}},
    {2, {0x43, 0x00}},
    {2, {0x44, 0x00}},
    {2, {0x50, 0x00}},
    {2, {0x51, 0x11}},
    {2, {0x52, 0x44}},
    {2, {0x53, 0x55}},
    {2, {0x54, 0x88}},
    {2, {0x55, 0xAB}},
    {2, {0x56, 0x00}},
    {2, {0x57, 0x11}},
    {2, {0x58, 0x22}},
    {2, {0x59, 0x33}},
    {2, {0x5A, 0x44}},
    {2, {0x5B, 0x55}},
    {2, {0x5C, 0x66}},
    {2, {0x5D, 0x77}},
    {2, {0x5E, 0x00}},
    {2, {0x5F, 0x02}},
    {2, {0x60, 0x02}},
    {2, {0x61, 0x0A}},
    {2, {0x62, 0x09}},
    {2, {0x63, 0x08}},
    {2, {0x64, 0x13}},
    {2, {0x65, 0x12}},
    {2, {0x66, 0x11}},
    {2, {0x67, 0x10}},
    {2, {0x68, 0x0F}},
    {2, {0x69, 0x0E}},
    {2, {0x6A, 0x0D}},
    {2, {0x6B, 0x0C}},
    {2, {0x6C, 0x06}},
    {2, {0x6D, 0x07}},
    {2, {0x6E, 0x02}},
    {2, {0x6F, 0x02}},
    {2, {0x70, 0x02}},
    {2, {0x71, 0x02}},
    {2, {0x72, 0x02}},
    {2, {0x73, 0x02}},
    {2, {0x74, 0x02}},
    {2, {0x75, 0x02}},
    {2, {0x76, 0x02}},
    {2, {0x77, 0x0A}},
    {2, {0x78, 0x06}},
    {2, {0x79, 0x07}},
    {2, {0x7A, 0x10}},
    {2, {0x7B, 0x11}},
    {2, {0x7C, 0x12}},
    {2, {0x7D, 0x13}},
    {2, {0x7E, 0x0C}},
    {2, {0x7F, 0x0D}},
    {2, {0x80, 0x0E}},
    {2, {0x81, 0x0F}},
    {2, {0x82, 0x09}},
    {2, {0x83, 0x08}},
    {2, {0x84, 0x02}},
    {2, {0x85, 0x02}},
    {2, {0x86, 0x02}},
    {2, {0x87, 0x02}},
    {2, {0x88, 0x02}},
    {2, {0x89, 0x02}},
    {2, {0x8A, 0x02}},
    {4, {0xFF, 0x98, 0x81, 0x04}},
    {2, {0x6E, 0x2A}},
    {2, {0x6F, 0x37}},
    {2, {0x3A, 0x24}},
    {2, {0x8D, 0x19}},
    {2, {0x87, 0xBA}},
    {2, {0xB2, 0xD1}},
    {2, {0x88, 0x0B}},
    {2, {0x38, 0x01}},
    {2, {0x39, 0x00}},
    {2, {0xB5, 0x02}},
    {2, {0x31, 0x25}},
    {2, {0x3B, 0x98}},
    {4, {0xFF, 0x98, 0x81, 0x01}},
    {2, {0x22, 0x0A}},
    {2, {0x31, 0x0C}},
    {2, {0x53, 0x40}},
    {2, {0x55, 0x45}},
    {2, {0x50, 0xB7}},
    {2, {0x51, 0xB2}},
    {2, {0x60, 0x07}},
    {2, {0xA0, 0x22}},
    {2, {0xA1, 0x3F}},
    {2, {0xA2, 0x4E}},
    {2, {0xA3, 0x17}},
    {2, {0xA4, 0x1A}},
    {2, {0xA5, 0x2D}},
    {2, {0xA6, 0x21}},
    {2, {0xA7, 0x22}},
    {2, {0xA8, 0xC4}},
    {2, {0xA9, 0x1B}},
    {2, {0xAA, 0x25}},
    {2, {0xAB, 0xA7}},
    {2, {0xAC, 0x1A}},
    {2, {0xAD, 0x19}},
    {2, {0xAE, 0x4B}},
    {2, {0xAF, 0x1F}},
    {2, {0xB0, 0x2A}},
    {2, {0xB1, 0x59}},
    {2, {0xB2, 0x64}},
    {2, {0xB3, 0x3F}},
    {2, {0xC0, 0x22}},
    {2, {0xC1, 0x48}},
    {2, {0xC2, 0x59}},
    {2, {0xC3, 0x15}},
    {2, {0xC4, 0x15}},
    {2, {0xC5, 0x28}},
    {2, {0xC6, 0x1C}},
    {2, {0xC7, 0x1E}},
    {2, {0xC8, 0xC4}},
    {2, {0xC9, 0x1C}},
    {2, {0xCA, 0x2B}},
    {2, {0xCB, 0xA3}},
    {2, {0xCC, 0x1F}},
    {2, {0xCD, 0x1E}},
    {2, {0xCE, 0x52}},
    {2, {0xCF, 0x24}},
    {2, {0xD0, 0x2A}},
    {2, {0xD1, 0x58}},
    {2, {0xD2, 0x68}},
    {2, {0xD3, 0x3F}},
    {4, {0xFF, 0x98, 0x81, 0x00}},
    {1, {0x11}},
    {1, {0x29}},
};

static void mipi_panel_init_cmd_send(hpm_panel_t *panel)
{
    int ret;
    uint8_t page_cmd[4] = {0xFF, 0x98, 0x81, 0x01};
    uint8_t panel_id[2] = {0x98, 0x81};
    uint8_t rdata;
    MIPI_DSI_Type *mipi_host = panel->hw_if.video.mipi.mipi_host_base;

    mipi_dsi_dcs_write_buffer(mipi_host, 0, page_cmd, 4);

    for (int i = 0; i < 2; i++) {
        mipi_dsi_set_maximum_return_packet_size(mipi_host, 0, 1);
        ret = mipi_dsi_dcs_read(mipi_host, 0, i, &rdata, 1);
        if (ret <= 0 || rdata != panel_id[i]) {
            printf("read id[%d]: 0x%02X -- failed\n", i, rdata);
            while (1) {
            }
        } else {
            printf("read id[%d]: 0x%02X -- ok\n", i, rdata);
        }
        hpm_panel_delay_ms(10);
    }

    int mipi_cmd_num = sizeof(mipi_panel_cmd) / sizeof(mipi_panel_cmd[0]);
    for (int i = 0; i < mipi_cmd_num; i++) {
        ret = mipi_dsi_dcs_write_buffer(mipi_host, 0, mipi_panel_cmd[i].cmd, mipi_panel_cmd[i].len);
        if (ret <= 0)
            printf("mipi_cmd[%d].cmd: 0x%02X -- failed\n", i, mipi_panel_cmd[i].cmd[0]);
    }

    hpm_panel_delay_ms(10);
}

static void mipi_panel_host_init(hpm_panel_t *panel)
{
    MIPI_DSI_Type *mipi_host = panel->hw_if.video.mipi.mipi_host_base;
    const hpm_panel_timing_t *timing = &panel->timing;
    mipi_dsi_config_t mipi_cfg;
    mipi_dsi_get_defconfig_on_video(&mipi_cfg);

    mipi_cfg.channel = 0;
    mipi_cfg.lanes = 4;
    mipi_cfg.video_para.pixel_clock_khz = panel->hw_if.lcdc_pixel_clk_khz;
    mipi_cfg.video_para.hactive = timing->hactive;
    mipi_cfg.video_para.hsync_len = timing->hsync_len;
    mipi_cfg.video_para.hback_porch = timing->hback_porch;
    mipi_cfg.video_para.hfront_porch = timing->hfront_porch;
    mipi_cfg.video_para.vsync_len = timing->vsync_len;
    mipi_cfg.video_para.vactive = timing->vactive;
    mipi_cfg.video_para.vback_porch = timing->vback_porch;
    mipi_cfg.video_para.vfront_porch = timing->vfront_porch;

    mipi_dsi_init(mipi_host, &mipi_cfg);
}

static void mipi_panel_phy_init(hpm_panel_t *panel)
{
    MIPI_DSI_Type *mipi_host = panel->hw_if.video.mipi.mipi_host_base;
    MIPI_DSI_PHY_Type *mipi_phy = panel->hw_if.video.mipi.mipi_phy_base;

    mipi_dsi_phy_config_t mipi_phy_cfg = {
        .lanes = 4,
        .lane_mbps = 500
    };
    mipi_dsi_phy_powerdown(mipi_host);
    mipi_dsi_phy_init(mipi_phy, &mipi_phy_cfg);
    mipi_dsi_phy_poweron(mipi_host);
}

static void reset(hpm_panel_t *panel)
{
    if (!panel->hw_if.set_reset_pin_level)
        return;

    panel->hw_if.set_reset_pin_level(0);
    hpm_panel_delay_ms(20);

    panel->hw_if.set_reset_pin_level(1);
    hpm_panel_delay_ms(15);
}

static void init(hpm_panel_t *panel)
{
    if (panel->hw_if.set_video_router)
        panel->hw_if.set_video_router();

    mipi_panel_host_init(panel);
    mipi_panel_phy_init(panel);
    mipi_panel_init_cmd_send(panel);
}

static void power_on(hpm_panel_t *panel)
{
    MIPI_DSI_Type *mipi_host = panel->hw_if.video.mipi.mipi_host_base;

    if (panel->state.power_state != HPM_PANEL_STATE_POWER_ON) {
        mipi_dsi_video_mode_hs_transfer_enable(mipi_host);

        if (panel->hw_if.set_backlight) {
            if (panel->state.backlight_percent == 0)
                panel->state.backlight_percent = 100;
            panel->hw_if.set_backlight(panel->state.backlight_percent);
        }
        panel->state.power_state = HPM_PANEL_STATE_POWER_ON;
    }
}

static void power_off(hpm_panel_t *panel)
{
    MIPI_DSI_Type *mipi_host = panel->hw_if.video.mipi.mipi_host_base;

    if (panel->state.power_state != HPM_PANEL_STATE_POWER_OFF) {
        if (panel->hw_if.set_backlight)
            panel->hw_if.set_backlight(0);
        mipi_dsi_video_mode_hs_transfer_disable(mipi_host);
        panel->state.power_state = HPM_PANEL_STATE_POWER_OFF;
    }
}

hpm_panel_t panel_mc10128007_31b = {
    .name = "mc10128007_31b",
    .if_type = HPM_PANEL_IF_TYPE_MIPI,
    .timing = {
        .pixel_clock_khz = 60000,
        .hactive = 800,
        .hfront_porch = 52,
        .hback_porch = 48,
        .hsync_len = 8,

        .vactive = 1280,
        .vfront_porch = 15,
        .vback_porch = 16,
        .vsync_len = 6,
    },
    .funcs = {
        .reset = reset,
        .init = init,
        .power_on = power_on,
        .power_off = power_off,
    },
};

