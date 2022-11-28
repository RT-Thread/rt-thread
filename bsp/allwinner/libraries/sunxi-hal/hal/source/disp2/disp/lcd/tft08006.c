/* drivers/video/sunxi/disp2/disp/lcd/tft08006.c
 *
 * Copyright (c) 2017 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * tft08006 panel driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 &lcd0 {
    lcd_used            = <1>;

    lcd_driver_name     = "tft08006";
    lcd_backlight       = <50>;
    lcd_if              = <4>;

    lcd_x               = <800>;
    lcd_y               = <1280>;
    lcd_width           = <52>;
    lcd_height          = <52>;
    lcd_dclk_freq       = <68>;

    lcd_pwm_used        = <1>;
    lcd_pwm_ch          = <2>;
    lcd_pwm_freq        = <50000>;
    lcd_pwm_pol         = <1>;
    lcd_pwm_max_limit   = <255>;

    lcd_hbp             = <40>;
    lcd_ht              = <860>;
    lcd_hspw            = <20>;
    lcd_vbp             = <24>;
    lcd_vt              = <1330>;
    lcd_vspw            = <4>;

    lcd_dsi_if          = <0>;
    lcd_dsi_lane        = <4>;
    lcd_lvds_if         = <0>;
    lcd_lvds_colordepth = <0>;
    lcd_lvds_mode       = <0>;
    lcd_frm             = <0>;
    lcd_hv_clk_phase    = <0>;
    lcd_hv_sync_polarity= <0>;
    lcd_gamma_en        = <0>;
    lcd_bright_curve_en = <0>;
    lcd_cmap_en         = <0>;
    lcd_fsync_en        = <0>;
    lcd_fsync_act_time  = <1000>;
    lcd_fsync_dis_time  = <1000>;
    lcd_fsync_pol       = <0>;

    deu_mode            = <0>;
    lcdgamma4iep        = <22>;
    smart_color         = <90>;

    lcd_gpio_0 =  <&pio PG 13 GPIO_ACTIVE_HIGH>;
    pinctrl-0 = <&dsi4lane_pins_a>;
    pinctrl-1 = <&dsi4lane_pins_b>;
};
*/
#include "tft08006.h"

static void lcd_power_on(u32 sel);
static void lcd_power_off(u32 sel);
static void lcd_bl_open(u32 sel);
static void lcd_bl_close(u32 sel);

static void lcd_panel_init(u32 sel);
static void lcd_panel_exit(u32 sel);

#define panel_reset(sel, val) sunxi_lcd_gpio_set_value(sel, 0, val)

static void lcd_cfg_panel_info(struct panel_extend_para *info)
{
    u32 i = 0, j = 0;
    u32 items;
    u8 lcd_gamma_tbl[][2] = {
        {0, 0},
        {15, 15},
        {30, 30},
        {45, 45},
        {60, 60},
        {75, 75},
        {90, 90},
        {105, 105},
        {120, 120},
        {135, 135},
        {150, 150},
        {165, 165},
        {180, 180},
        {195, 195},
        {210, 210},
        {225, 225},
        {240, 240},
        {255, 255},
    };

    u32 lcd_cmap_tbl[2][3][4] = {
        {
            {LCD_CMAP_G0, LCD_CMAP_B1, LCD_CMAP_G2, LCD_CMAP_B3},
            {LCD_CMAP_B0, LCD_CMAP_R1, LCD_CMAP_B2, LCD_CMAP_R3},
            {LCD_CMAP_R0, LCD_CMAP_G1, LCD_CMAP_R2, LCD_CMAP_G3},
        },
        {
            {LCD_CMAP_B3, LCD_CMAP_G2, LCD_CMAP_B1, LCD_CMAP_G0},
            {LCD_CMAP_R3, LCD_CMAP_B2, LCD_CMAP_R1, LCD_CMAP_B0},
            {LCD_CMAP_G3, LCD_CMAP_R2, LCD_CMAP_G1, LCD_CMAP_R0},
        },
    };

    items = sizeof(lcd_gamma_tbl) / 2;
    for (i = 0; i < items - 1; i++) {
        u32 num = lcd_gamma_tbl[i + 1][0] - lcd_gamma_tbl[i][0];

        for (j = 0; j < num; j++) {
            u32 value = 0;

            value = lcd_gamma_tbl[i][1] +
                ((lcd_gamma_tbl[i + 1][1] - lcd_gamma_tbl[i][1])
                 * j) / num;
            info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] =
                (value << 16)
                + (value << 8) + value;
        }
    }
    info->lcd_gamma_tbl[255] = (lcd_gamma_tbl[items - 1][1] << 16) +
                   (lcd_gamma_tbl[items - 1][1] << 8)
                   + lcd_gamma_tbl[items - 1][1];

    memcpy(info->lcd_cmap_tbl, lcd_cmap_tbl, sizeof(lcd_cmap_tbl));

}

static s32 lcd_open_flow(u32 sel)
{
    LCD_OPEN_FUNC(sel, lcd_power_on, 10);
    LCD_OPEN_FUNC(sel, lcd_panel_init, 10);
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 50);
    LCD_OPEN_FUNC(sel, lcd_bl_open, 0);

    return 0;
}

static s32 lcd_close_flow(u32 sel)
{
    LCD_CLOSE_FUNC(sel, lcd_bl_close, 0);
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);
    LCD_CLOSE_FUNC(sel, lcd_panel_exit, 200);
    LCD_CLOSE_FUNC(sel, lcd_power_off, 500);

    return 0;
}

static void lcd_power_on(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 1);
    sunxi_lcd_delay_ms(50);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(5);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(10);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(120);

}

static void lcd_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    sunxi_lcd_delay_ms(20);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(5);
}

static void lcd_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
}

static void lcd_bl_close(u32 sel)
{
    sunxi_lcd_pwm_disable(sel);
}

#define REGFLAG_DELAY 0XFC
#define REGFLAG_END_OF_TABLE 0xFD /* END OF REGISTERS MARKER */

struct LCM_setting_table {
    u8 cmd;
    u32 count;
    u8 para_list[32];
};

static struct LCM_setting_table lcm_tft08006_setting[] = {
#if 0
    {0xFF, 3, {0x98, 0x81, 0x03} },
    {0x01, 1, {0x00} },
    {0x02, 1, {0x00} },
    {0x03, 1, {0x53} },
    {0x04, 1, {0x53} },
    {0x05, 1, {0x13} },
    {0x06, 1, {0x04} },
    {0x07, 1, {0x02} },
    {0x08, 1, {0x02} },
    {0x09, 1, {0x00} },
    {0x0a, 1, {0x00} },
    {0x0b, 1, {0x00} },
    {0x0c, 1, {0x00} },
    {0x0d, 1, {0x00} },
    {0x0e, 1, {0x00} },
    {0x0f, 1, {0x00} },
    {0x10, 1, {0x00} },
    {0x11, 1, {0x00} },
    {0x12, 1, {0x00} },
    {0x13, 1, {0x00} },
    {0x14, 1, {0x00} },
    {0x15, 1, {0x00} },
    {0x16, 1, {0x00} },
    {0x17, 1, {0x00} },
    {0x18, 1, {0x00} },
    {0x19, 1, {0x00} },
    {0x1a, 1, {0x00} },
    {0x1b, 1, {0x00} },
    {0x1c, 1, {0x00} },
    {0x1d, 1, {0x00} },
    {0x1e, 1, {0xc0} },
    {0x1f, 1, {0x80} },
    {0x20, 1, {0x02} },
    {0x21, 1, {0x09} },
    {0x22, 1, {0x00} },
    {0x23, 1, {0x00} },
    {0x24, 1, {0x00} },
    {0x25, 1, {0x00} },
    {0x26, 1, {0x00} },
    {0x27, 1, {0x00} },
    {0x28, 1, {0x55} },
    {0x29, 1, {0x03} },
    {0x2a, 1, {0x00} },
    {0x2b, 1, {0x00} },
    {0x2c, 1, {0x00} },
    {0x2d, 1, {0x00} },
    {0x2e, 1, {0x00} },
    {0x2f, 1, {0x00} },
    {0x30, 1, {0x00} },
    {0x31, 1, {0x00} },
    {0x32, 1, {0x00} },
    {0x33, 1, {0x00} },
    {0x34, 1, {0x00} },
    {0x35, 1, {0x00} },
    {0x36, 1, {0x00} },
    {0x37, 1, {0x00} },
    {0x38, 1, {0x3C} },
    {0x39, 1, {0x00} },
    {0x3a, 1, {0x00} },
    {0x3b, 1, {0x00} },
    {0x3c, 1, {0x00} },
    {0x3d, 1, {0x00} },
    {0x3e, 1, {0x00} },
    {0x3f, 1, {0x00} },
    {0x40, 1, {0x00} },
    {0x41, 1, {0x00} },
    {0x42, 1, {0x00} },
    {0x43, 1, {0x00} },
    {0x44, 1, {0x00} },
    {0x50, 1, {0x01} },
    {0x51, 1, {0x23} },
    {0x52, 1, {0x45} },
    {0x53, 1, {0x67} },
    {0x54, 1, {0x89} },
    {0x55, 1, {0xab} },
    {0x56, 1, {0x01} },
    {0x57, 1, {0x23} },
    {0x58, 1, {0x45} },
    {0x59, 1, {0x67} },
    {0x5a, 1, {0x89} },
    {0x5b, 1, {0xab} },
    {0x5c, 1, {0xcd} },
    {0x5d, 1, {0xef} },
    {0x5e, 1, {0x01} },
    {0x5f, 1, {0x08} },
    {0x60, 1, {0x02} },
    {0x61, 1, {0x02} },
    {0x62, 1, {0x0A} },
    {0x63, 1, {0x15} },
    {0x64, 1, {0x14} },
    {0x65, 1, {0x02} },
    {0x66, 1, {0x11} },
    {0x67, 1, {0x10} },
    {0x68, 1, {0x02} },
    {0x69, 1, {0x0F} },
    {0x6a, 1, {0x0E} },
    {0x6b, 1, {0x02} },
    {0x6c, 1, {0x0D} },
    {0x6d, 1, {0x0C} },
    {0x6e, 1, {0x06} },
    {0x6f, 1, {0x02} },
    {0x70, 1, {0x02} },
    {0x71, 1, {0x02} },
    {0x72, 1, {0x02} },
    {0x73, 1, {0x02} },
    {0x74, 1, {0x02} },
    {0x75, 1, {0x06} },
    {0x76, 1, {0x02} },
    {0x77, 1, {0x02} },
    {0x78, 1, {0x0A} },
    {0x79, 1, {0x15} },
    {0x7a, 1, {0x14} },
    {0x7b, 1, {0x02} },
    {0x7c, 1, {0x10} },
    {0x7d, 1, {0x11} },
    {0x7e, 1, {0x02} },
    {0x7f, 1, {0x0C} },
    {0x80, 1, {0x0D} },
    {0x81, 1, {0x02} },
    {0x82, 1, {0x0E} },
    {0x83, 1, {0x0F} },
    {0x84, 1, {0x08} },
    {0x85, 1, {0x02} },
    {0x86, 1, {0x02} },
    {0x87, 1, {0x02} },
    {0x88, 1, {0x02} },
    {0x89, 1, {0x02} },
    {0x8A, 1, {0x02} },

    {0xFF, 3, {0x98, 0x81, 0x04} },
    {0x6C, 1, {0x15} },
    {0x6E, 1, {0x30} },
    {0x6F, 1, {0x37} },   //3VSP    3VSN
    {0x8D, 1, {0x1F} },
    {0x87, 1, {0xBA} },
    {0x26, 1, {0x76} },
    {0xB2, 1, {0xD1} },
    {0xB5, 1, {0x07} },
    {0x35, 1, {0x17} },
    {0x33, 1, {0x14} },
    {0x31, 1, {0x75} },
    {0x3A, 1, {0x85} },
    {0x3B, 1, {0x98} },
    {0x38, 1, {0x01} },
    {0x39, 1, {0x00} },
    {0x7A, 1, {0x10} },

    {0xFF, 3, {0x98, 0x81, 0x01} },
    {0x22, 1, {0x0A} },
    {0x31, 1, {0x00} },
    {0x50, 1, {0xCF} },     //5.2V
    {0x51, 1, {0xCA} },     //-5.2V
    {0x53, 1, {0x45} },     //45   41
    {0x55, 1, {0x48} },
    {0x60, 1, {0x28} },
    {0x2E, 1, {0xC8} },
    {0x34, 1, {0x01} },

    //{0x56, 1, {0x00} },

    {0xA0, 1, {0x00} },     //VP255 Gamma P
    {0xA1, 1, {0x08} },               //VP251
    {0xA2, 1, {0x18} },               //VP247
    {0xA3, 1, {0x15} },              //VP243
    {0xA4, 1, {0x19} },               //VP239
    {0xA5, 1, {0x2D} },               //VP231
    {0xA6, 1, {0x21} },               //VP219
    {0xA7, 1, {0x23} },               //VP203
    {0xA8, 1, {0x74} },               //VP175
    {0xA9, 1, {0x1C} },               //VP144
    {0xAA, 1, {0x26} },               //VP111
    {0xAB, 1, {0x64} },               //VP80
    {0xAC, 1, {0x1A} },               //VP52
    {0xAD, 1, {0x1C} },               //VP36
    {0xAE, 1, {0x50} },               //VP24
    {0xAF, 1, {0x25} },               //VP16
    {0xB0, 1, {0x2A} },               //VP12
    {0xB1, 1, {0x4C} },              //VP8
    {0xB2, 1, {0x5D} },               //VP4
    {0xB3, 1, {0x23} },               //VP0

    {0xC0, 1, {0x00} }, //VN255 GAMMA N
    {0xC1, 1, {0x1B} },              //VN251
    {0xC2, 1, {0x27} },              //VN247
    {0xC3, 1, {0x13} },              //VN243
    {0xC4, 1, {0x16} },              //VN239
    {0xC5, 1, {0x28} },              //VN231
    {0xC6, 1, {0x1E} },              //VN219
    {0xC7, 1, {0x20} },              //VN203
    {0xC8, 1, {0x7D} },              //VN175
    {0xC9, 1, {0x19} },              //VN144
    {0xCA, 1, {0x27} },              //VN111
    {0xCB, 1, {0x65} },              //VN80
    {0xCC, 1, {0x1D} },              //VN52
    {0xCD, 1, {0x1D} },              //VN36
    {0xCE, 1, {0x52} },              //VN24
    {0xCF, 1, {0x26} },              //VN16
    {0xD0, 1, {0x2C} },              //VN12
    {0xD1, 1, {0x4E} },              //VN8
    {0xD2, 1, {0x59} },              //VN4
    {0xD3, 1, {0x23} },              //VN0

    //{0xFF, 3, {0x98, 0x81, 0x04} },
    //{0x2F, 1, {0x01} },

    {0xFF, 3, {0x98, 0x81, 0x00} },
    {0x35, 1, {0x00} },
#endif

    {0x11, 0, {} },
    {REGFLAG_DELAY, REGFLAG_DELAY, {120} },

    {0x29, 0, {} },
    {REGFLAG_DELAY, REGFLAG_DELAY, {120} },

    {REGFLAG_END_OF_TABLE, REGFLAG_END_OF_TABLE, {} }
};

static void lcd_panel_init(u32 sel)
{
    __u32 i;
    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(100);
    for (i = 0;; i++) {
        if (lcm_tft08006_setting[i].count == REGFLAG_END_OF_TABLE)
            break;
        else if (lcm_tft08006_setting[i].count == REGFLAG_DELAY) {
            sunxi_lcd_delay_ms(lcm_tft08006_setting[i].para_list[0]);
        } else {
            dsi_gen_wr(sel, lcm_tft08006_setting[i].cmd,
                   lcm_tft08006_setting[i].para_list,
                   lcm_tft08006_setting[i].count);
        }
        /* break; */
    }
}

static void lcd_panel_exit(u32 sel)
{
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x10);
    sunxi_lcd_delay_ms(80);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x28);
    sunxi_lcd_delay_ms(50);
}

/*sel: 0:lcd0; 1:lcd1*/
static s32 lcd_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel tft08006_panel = {
    /* panel driver name, must mach the name of
     * lcd_drv_name in sys_config.fex
     */
    .name = "tft08006",
    .func = {
        .cfg_panel_info = lcd_cfg_panel_info,
        .cfg_open_flow = lcd_open_flow,
        .cfg_close_flow = lcd_close_flow,
        .lcd_user_defined_func = lcd_user_defined_func,
    },
};
