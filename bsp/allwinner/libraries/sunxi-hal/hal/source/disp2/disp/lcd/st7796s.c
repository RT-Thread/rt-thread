/* drivers/video/sunxi/disp2/disp/lcd/ST7796S.c
 *
 * Copyright (c) 2017 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * he0801a-068 panel driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * [lcd0]
 * lcd_used            = 1

 * lcd_driver_name     = "st7796s"
 * lcd_bl_0_percent    = 0
 * lcd_bl_40_percent   = 23
 * lcd_bl_100_percent  = 100
 * lcd_backlight       = 100

 * lcd_if              = 4
 * lcd_x               = 240
 * lcd_y               = 432
 * lcd_width           = 52
 * lcd_height          = 52
 * lcd_dclk_freq       = 18

 * lcd_pwm_used        = 1
 * lcd_pwm_ch          = 0
 * lcd_pwm_freq        = 50000
 * lcd_pwm_pol         = 1
 * lcd_pwm_max_limit   = 255

 * lcd_hbp             = 96
 * lcd_ht              = 480
 * lcd_hspw            = 2
 * lcd_vbp             = 21
 * lcd_vt              = 514
 * lcd_vspw            = 2

 * lcd_dsi_if          = 1
 * lcd_dsi_lane        = 1
 * lcd_dsi_format      = 0
 * lcd_dsi_te          = 1
 * lcd_dsi_eotp        = 0

 * lcd_frm             = 0
 * lcd_io_phase        = 0x0000
 * lcd_hv_clk_phase    = 0
 * lcd_hv_sync_polarity= 0
 * lcd_gamma_en        = 0
 * lcd_bright_curve_en = 0
 * lcd_cmap_en         = 0

 * lcdgamma4iep        = 22

 * lcd_bl_en           = port:PB03<1><0><default><1>
 * lcd_power           = "axp233_dc1sw"
 * lcd_power1           = "axp233_eldo1"

 * lcd_gpio_0          = port:PB02<1><0><default><0>
 * lcd_vsync          = port:PD21<2><0><3><default>
*/
#include "st7796s.h"

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
        {0, 0},     {15, 15},   {30, 30},   {45, 45},   {60, 60},
        {75, 75},   {90, 90},   {105, 105}, {120, 120}, {135, 135},
        {150, 150}, {165, 165}, {180, 180}, {195, 195}, {210, 210},
        {225, 225}, {240, 240}, {255, 255},
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

            value =
                lcd_gamma_tbl[i][1] +
                ((lcd_gamma_tbl[i + 1][1] - lcd_gamma_tbl[i][1]) *
                 j) /
                num;
            info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] =
                (value << 16) + (value << 8) + value;
        }
    }
    info->lcd_gamma_tbl[255] = (lcd_gamma_tbl[items - 1][1] << 16) +
                   (lcd_gamma_tbl[items - 1][1] << 8) +
                   lcd_gamma_tbl[items - 1][1];

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
    LCD_CLOSE_FUNC(sel, lcd_panel_exit, 200);
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);
    LCD_CLOSE_FUNC(sel, lcd_power_off, 500);

    return 0;
}

static void lcd_power_on(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 1);
    sunxi_lcd_power_enable(sel, 0);
    // sunxi_lcd_power_enable(sel, 1);
    sunxi_lcd_delay_ms(10);

    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(50);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(50);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(50);
}

static void lcd_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    sunxi_lcd_delay_ms(20);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_disable(sel, 0);
}

static void lcd_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
    sunxi_lcd_backlight_enable(sel);
}

static void lcd_bl_close(u32 sel)
{
    sunxi_lcd_backlight_disable(sel);
    sunxi_lcd_pwm_disable(sel);
}

#define REGFLAG_DELAY         0XFF
#define REGFLAG_END_OF_TABLE  0xFE   /* END OF REGISTERS MARKER */

struct LCM_setting_table {
    u8 cmd;
    u32 count;
    u8 para_list[15];
};


static struct LCM_setting_table lcm_initialization_setting[] = {
    {0x11, 1, {0x00} },
    {REGFLAG_DELAY, 50, {} },
    {0x36, 1, {0x48} },
    {0x35, 1, {0x00} },/*te on*/
    {0x3a, 1, {0x77} },/*24bit/pixel*/
    {0xf0, 1, {0xc3} },
    {0xf0, 1, {0x96} },
    {0xb4, 1, {0x01} },
    {0xb6, 3, {0xa0, 0x02, 0x3b} },
    {0xc1, 1, {0x1d} },
    {0xc2, 1, {0xa7} },
    {0xc5, 1, {0x23} },
    {REGFLAG_DELAY, 1, {} },
    {0xe8, 8, {0x40, 0x8a, 0x00, 0x00, 0x29, 0x19, 0xa5, 0x33} },
    {0xe0, 14, { 0xf0, 0x03, 0x0a, 0x12, 0x15,
               0x1d, 0x42, 0x44, 0x50, 0x28, 0x16, 0x15,
               0x20, 0x21} },
    {0xe1, 14, { 0xf0, 0x03, 0x0a, 0x12, 0x15,
               0x1c, 0x42, 0x44, 0x52, 0x28, 0x16, 0x15,
               0x20, 0x23} },
    {REGFLAG_DELAY, 1, {} },
    {0xf0, 1, {0x3c} },
    {0xf0, 1, {0x69} },
    {0x29, 1, {0x00} }, /* DSPON */
    {REGFLAG_DELAY, 1, {} },
    {REGFLAG_END_OF_TABLE, 0x00, {} }
};

static void lcd_panel_init(u32 sel)
{
    u32 i = 0;

    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(100);

    for (i = 0;; i++) {
        if (lcm_initialization_setting[i].cmd == REGFLAG_END_OF_TABLE)
            break;
        else if (lcm_initialization_setting[i].cmd == REGFLAG_DELAY)
            sunxi_lcd_delay_ms(lcm_initialization_setting[i].count);
        else {
            dsi_dcs_wr(0, lcm_initialization_setting[i].cmd,
                   lcm_initialization_setting[i].para_list,
                   lcm_initialization_setting[i].count);
        }
    }
}

static void lcd_panel_exit(u32 sel)
{
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x28);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x10);
    sunxi_lcd_delay_ms(10);
}

/*sel: 0:lcd0; 1:lcd1*/
static s32 lcd_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel st7796s_panel = {
    /* panel driver name, must mach the name of
     * lcd_drv_name in sys_config.fex
     */
    .name = "st7796s",
    .func = {
        .cfg_panel_info = lcd_cfg_panel_info,
            .cfg_open_flow = lcd_open_flow,
            .cfg_close_flow = lcd_close_flow,
            .lcd_user_defined_func = lcd_user_defined_func,
    },
};
