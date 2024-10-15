/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_panel.h"

static void reset(hpm_panel_t *panel)
{
    if (!panel->hw_if.set_reset_pin_level)
        return;

    panel->hw_if.set_reset_pin_level(0);
    hpm_panel_delay_ms(20);

    panel->hw_if.set_reset_pin_level(1);
    hpm_panel_delay_ms(20);
}

static void init(hpm_panel_t *panel)
{
    if (panel->hw_if.set_video_router)
        panel->hw_if.set_video_router();
}

static void power_on(hpm_panel_t *panel)
{
    if (panel->state.power_state != HPM_PANEL_STATE_POWER_ON &&
        panel->hw_if.set_backlight) {
        if (panel->state.backlight_percent == 0)
            panel->state.backlight_percent = 100;

        panel->hw_if.set_backlight(panel->state.backlight_percent);
        panel->state.power_state = HPM_PANEL_STATE_POWER_ON;
    }
}

static void power_off(hpm_panel_t *panel)
{
    if (panel->state.power_state != HPM_PANEL_STATE_POWER_OFF &&
        panel->hw_if.set_backlight) {

        panel->hw_if.set_backlight(0);
        panel->state.power_state = HPM_PANEL_STATE_POWER_OFF;
    }
}

hpm_panel_t panel_tm070rdh13 = {
    .name = "tm070rdh13",
    .if_type = HPM_PANEL_IF_TYPE_RGB,
    .timing = {
        .pixel_clock_khz = 60000,
        .hactive = 800,
        .hfront_porch = 50,
        .hback_porch = 36,
        .hsync_len = 10,
        .hsync_pol = 1,

        .vactive = 480,
        .vfront_porch = 10,
        .vback_porch = 20,
        .vsync_len = 3,
        .vsync_pol = 1,
    },
    .funcs = {
        .reset = reset,
        .init = init,
        .power_on = power_on,
        .power_off = power_off,
    },
};

