/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_DISPLAY_OUTPUT_H__
#define __SUNXI_DISPLAY_OUTPUT_H__

#include <rtthread.h>

struct rt_device;

struct sunxi_fb_timing
{
    rt_uint32_t pixelclock;
    rt_uint32_t hactive;
    rt_uint32_t hfront_porch;
    rt_uint32_t hback_porch;
    rt_uint32_t hsync_len;
    rt_uint32_t vactive;
    rt_uint32_t vfront_porch;
    rt_uint32_t vback_porch;
    rt_uint32_t vsync_len;
    rt_uint32_t htotal;
    rt_uint32_t vtotal;
    rt_bool_t hsync_active;
    rt_bool_t vsync_active;
    rt_bool_t pixelclk_active;
};

enum sunxi_display_output_type
{
    SUNXI_DISPLAY_OUTPUT_RGB,
    SUNXI_DISPLAY_OUTPUT_LVDS,
    SUNXI_DISPLAY_OUTPUT_DSI,
};

struct sunxi_display_output
{
    enum sunxi_display_output_type type;
    void *tcon;
    void *top;
    void *dsi;
    void *dphy;
    const rt_uint8_t *panel_init_sequence;
    rt_size_t panel_init_sequence_len;
    rt_base_t panel_enable_pin;
    rt_base_t panel_reset_pin;
    rt_uint8_t panel_enable_active;
    rt_uint8_t panel_reset_active;
    rt_uint32_t panel_power_off_delay_ms;
    rt_uint32_t panel_prepare_delay_ms;
    rt_uint32_t panel_reset_delay_ms;
    rt_uint32_t panel_init_delay_ms;
    rt_bool_t panel_prepared;
    rt_uint8_t dsi_lanes;
    rt_uint32_t lvds_polarity;
    rt_bool_t lvds_8bit;
    rt_bool_t lvds_jeida;
};

rt_err_t sunxi_display_output_parse(struct rt_device *dev,
        struct sunxi_display_output *output);
rt_err_t sunxi_display_output_prepare(struct sunxi_display_output *output,
        const struct sunxi_fb_timing *timing);
rt_err_t sunxi_display_output_panel_init(struct sunxi_display_output *output);
void sunxi_display_output_enable(struct sunxi_display_output *output);
void sunxi_display_output_disable(struct sunxi_display_output *output);

#endif /* __SUNXI_DISPLAY_OUTPUT_H__ */
