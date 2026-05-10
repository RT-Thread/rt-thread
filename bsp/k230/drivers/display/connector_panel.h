#ifndef _CONNECTOR_PANEL_H_
#define _CONNECTOR_PANEL_H_

#include "k_connector_comm.h"
#include "k_vo_comm.h"

#include "connector_bus.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VO_PIXEL_CLOCK_HZ       594000000UL
#define PANEL_BG_COLOR_BLACK    0x00000000
#define PANEL_BG_COLOR_WHITE    0x00FFFFFF

struct panel_desc;

struct panel_drv {
    const char* connector_name;
    const struct panel_desc** panel_variants;
    const struct panel_desc*  active_panel;
};

struct panel_gpio_config {
    k_s32  reset_pin;
    k_u32  reset_delay_ms;
    k_u32  backlight_delay_ms;
    k_s32  backlight_pin;
    k_bool reset_active_low;
    k_bool backlight_active_low;
};

struct panel_dsi_config {
    k_vo_dsi_lane_num   lanes;
    k_u32               cmd_mode;
    k_vo_dsi_video_mode video_mode;
    k_u8                vc_id;
    k_u8                lp_cmd_speed_mhz;
};

struct panel_ops {
    int  (*reset)(const struct panel_desc* desc);
    int  (*init)(const struct panel_desc* desc);
    int  (*power_off)(const struct panel_desc* desc);
    k_u32 (*read_chip_id)(const struct panel_desc* desc);
};

struct panel_desc {
    const char*         name;
    k_u32               connector_type;
    enum panel_bus_type bus_type;

    k_vo_timing timing;
    k_u32       bg_color;

    struct panel_gpio_config gpio;

    union {
        struct panel_dsi_config dsi;
    } bus;

    const struct panel_bus_ops* bus_ops;
    const struct panel_ops*     ops;
};

k_u32 panel_correct_pclk(k_u32 pclk);
int   panel_calculate_fps(const k_vo_timing* timing);
int   panel_generic_reset(const struct panel_desc* desc);
int   panel_generic_backlight(const struct panel_desc* desc, k_u32 mode, k_u32 duty);
k_s32 panel_generic_power_on(struct panel_desc* desc);
k_s32 panel_generic_power_off(const struct panel_desc* desc);

#ifdef __cplusplus
}
#endif

#endif /* _CONNECTOR_PANEL_H_ */
