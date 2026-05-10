/* Adapted from atk_k230d connector_panel_common.c for RT-Thread BSP */

#include <rtthread.h>
#include <rtdevice.h>

#include "connector_bus_dsi.h"
#include "connector_panel.h"

extern void kd_vo_reset(void);
extern void kd_vo_wrap_init(void);
extern void kd_vo_set_config_mix(void);
extern void kd_vo_set_frame_intr(k_bool status);
extern void kd_vo_set_timing(const k_vo_timing* timing);
extern void kd_vo_set_pixclk(k_u32 div);
extern void kd_vo_set_background(k_u32 rgb888);
extern void kd_vo_enable(void);

static inline k_u32 panel_calc_pixclk_div(k_u32 pclk_khz)
{
    return (pclk_khz == 0) ? 0 : (VO_PIXEL_CLOCK_HZ / (pclk_khz * 1000)) - 1;
}

static k_s32 panel_vo_init(const struct panel_desc* desc)
{
    kd_vo_wrap_init();
    kd_vo_set_config_mix();
    kd_vo_set_frame_intr(K_TRUE);
    kd_vo_set_timing(&desc->timing);
    kd_vo_set_background(desc->bg_color);
    kd_vo_enable();
    return 0;
}

k_u32 panel_correct_pclk(k_u32 pclk_hz)
{
    k_u32 ratio;

    if (pclk_hz == 0)
        return 0;

    ratio = (VO_PIXEL_CLOCK_HZ + pclk_hz / 2) / pclk_hz;
    if (ratio == 0)
        ratio = 1;

    return VO_PIXEL_CLOCK_HZ / ratio;
}

int panel_calculate_fps(const k_vo_timing* timing)
{
    k_u32 htotal, vtotal;

    if (!timing)
        return 0;

    htotal = timing->hactive + timing->hsync_len + timing->hback_porch + timing->hfront_porch;
    vtotal = timing->vactive + timing->vsync_len + timing->vback_porch + timing->vfront_porch;

    if (htotal == 0 || vtotal == 0)
        return 0;

    return (timing->pclk_khz * 1000) / htotal / vtotal;
}

int panel_generic_reset(const struct panel_desc* desc)
{
    k_s32  reset_pin;
    k_u32  reset_delay_ms;
    k_bool reset_active_low;
    int    inactive_level, active_level;

    if (!desc)
        return -1;

    reset_pin = desc->gpio.reset_pin;
    if (reset_pin < 0)
        return 0;

    reset_delay_ms   = desc->gpio.reset_delay_ms;
    reset_active_low = desc->gpio.reset_active_low;

    if (reset_active_low) {
        active_level   = PIN_LOW;
        inactive_level = PIN_HIGH;
    } else {
        active_level   = PIN_HIGH;
        inactive_level = PIN_LOW;
    }

    rt_pin_mode(reset_pin, PIN_MODE_OUTPUT);

    rt_pin_write(reset_pin, inactive_level);
    rt_thread_mdelay(3);

    rt_pin_write(reset_pin, active_level);
    rt_thread_mdelay(7);

    rt_pin_write(reset_pin, inactive_level);
    rt_thread_mdelay(reset_delay_ms);

    return 0;
}

static int panel_generic_backlight_over_gpio(const struct panel_desc* desc, k_u32 mode, k_u32 duty)
{
    k_s32  backlight_pin;
    k_u32  backlight_delay_ms;
    k_bool backlight_active_low;
    int    target_level;
    int    on;

    if (!desc)
        return -1;

    backlight_pin = desc->gpio.backlight_pin;
    if (backlight_pin < 0)
        return -1;

    if (mode == 0)
        on = 0;
    else if (mode == 1)
        on = 1;
    else
        on = duty / 128;

    backlight_delay_ms   = desc->gpio.backlight_delay_ms;
    backlight_active_low = desc->gpio.backlight_active_low;

    if (backlight_active_low)
        target_level = on ? PIN_LOW : PIN_HIGH;
    else
        target_level = on ? PIN_HIGH : PIN_LOW;

    rt_pin_mode(backlight_pin, PIN_MODE_OUTPUT);
    rt_pin_write(backlight_pin, target_level);

    if (backlight_delay_ms > 0)
        rt_thread_mdelay(backlight_delay_ms);

    return 0;
}

int panel_generic_backlight(const struct panel_desc* desc, k_u32 mode, k_u32 duty)
{
    if (!desc)
        return -1;

    return panel_generic_backlight_over_gpio(desc, mode, duty);
}

k_s32 panel_generic_power_on(struct panel_desc* desc)
{
    k_s32 ret;
    k_u32 pixclk_div;
    int   fps;

    if (!desc)
        return -1;

    kd_vo_reset();

    if (!desc->bus_ops) {
        rt_kprintf("panel_generic_power_on: missing bus_ops\n");
        return -1;
    }

    if (desc->ops && desc->ops->reset) {
        ret = desc->ops->reset(desc);
        if (ret != 0) {
            rt_kprintf("panel_generic_power_on: ops->reset failed: %d\n", ret);
            return ret;
        }
    }

    if (desc->bus_type == PANEL_BUS_DSI) {
        desc->timing.pclk_khz = dsi_correct_pclk(desc->timing.pclk_khz * 1000, desc->bus.dsi.lanes) / 1000;
    } else {
        desc->timing.pclk_khz = panel_correct_pclk(desc->timing.pclk_khz * 1000) / 1000;
    }

    fps = panel_calculate_fps(&desc->timing);
    rt_kprintf("panel %s, pixelclock %u khz, resolution %dx%d@%d\n",
               desc->name, desc->timing.pclk_khz, desc->timing.hactive, desc->timing.vactive, fps);

    pixclk_div = panel_calc_pixclk_div(desc->timing.pclk_khz);
    if (pixclk_div != 0)
        kd_vo_set_pixclk(pixclk_div);

    if (desc->bus_ops->init) {
        ret = desc->bus_ops->init(desc);
        if (ret != 0) {
            rt_kprintf("panel_generic_power_on: bus_ops->init failed: %d\n", ret);
            return ret;
        }
    }

    if (!desc->ops || !desc->ops->init) {
        rt_kprintf("panel_generic_power_on: panel missing mandatory ops->init\n");
        return -1;
    }

    ret = desc->ops->init(desc);
    if (ret != 0) {
        rt_kprintf("panel_generic_power_on: ops->init failed: %d\n", ret);
        return ret;
    }

    if (desc->bus_ops->enable) {
        ret = desc->bus_ops->enable(desc);
        if (ret != 0) {
            rt_kprintf("panel_generic_power_on: bus_ops->enable failed: %d\n", ret);
            return ret;
        }
    }

    ret = panel_vo_init(desc);
    if (ret != 0) {
        rt_kprintf("panel_generic_power_on: panel_vo_init failed: %d\n", ret);
        return ret;
    }

    return 0;
}

k_s32 panel_generic_power_off(const struct panel_desc* desc)
{
    k_s32 first_err = 0;
    k_s32 ret;

    if (!desc)
        return -1;

    panel_generic_backlight(desc, 0, 0);

    if (desc->ops && desc->ops->power_off) {
        ret = desc->ops->power_off(desc);
        if (ret != 0) {
            rt_kprintf("panel_generic_power_off: ops->power_off failed: %d\n", ret);
            first_err = ret;
        }
    }

    if (desc->bus_ops && desc->bus_ops->disable) {
        ret = desc->bus_ops->disable(desc);
        if (ret != 0) {
            rt_kprintf("panel_generic_power_off: bus_ops->disable failed: %d\n", ret);
            if (!first_err)
                first_err = ret;
        }
    }

    return first_err;
}
