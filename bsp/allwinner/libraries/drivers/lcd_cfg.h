#ifndef _LCD_CFG_H_
#define _LCD_CFG_H_

#include <stdint.h>

#define COORD_Y_REVERSE    (1<<0)
#define COORD_X_REVERSE    (1<<1)
#define COORD_XY_EXCHANGE  (1<<2)


#define DEFAULT_LCD_CONFIG {\
    type: "rgb",\
    width:480,\
    height:272,\
    bits_pixel:18,\
    timing:\
    {\
        pixel_clock_hz:10000000,\
        h_front_porch:8,\
        h_back_porch:43,\
        h_sync_len:4,\
        v_front_porch:8,\
        v_back_porch:12,\
        v_sync_len:4,\
        h_sync_active:0,\
        v_sync_active:0,\
        den_active:1,\
        clk_active:1\
    },\
    swap_flag:0,\
    ctp_flag:0,\
    bl_mode:1,\
    bl_gpio_pin:GPIOB(6),\
    bl_gpio_level:1,\
    bl_pwm_name: "pwm",\
    bl_pwm_hz:1000,\
    bl_pwm_pol:0,\
    bl_pwm_val:60,\
    bl_pin:GPIOG(13),\
    bl_level:1,\
    pwr_pin:GPIOG(15),\
    pwr_level:1,\
    lane:4\
}

struct panel_timing
{
    int pixel_clock_hz;
    int h_front_porch;
    int h_back_porch;
    int h_sync_len;
    int v_front_porch;
    int v_back_porch;
    int v_sync_len;
    int h_sync_active;
    int v_sync_active;
    int den_active;
    int clk_active;
};
typedef struct panel_timing *panel_timing_t;

struct lcd_cfg_panel_info
{
    rt_int8_t type[8];
    int width;
    int height;
    int bits_pixel;
    struct panel_timing timing;
    int swap_flag;
    int ctp_flag;

    int bl_mode;
    int bl_gpio_pin;
    int bl_gpio_level;
    rt_int8_t bl_pwm_name[8];
    int bl_pwm_hz;
    int bl_pwm_pol;
    int bl_pwm_val;
    int bl_pin;
    int bl_level;
    int pwr_pin;
    int pwr_level;
    int lane;

};

const struct lcd_cfg_panel_info* load_lcd_config_from_xml(void);

#endif
