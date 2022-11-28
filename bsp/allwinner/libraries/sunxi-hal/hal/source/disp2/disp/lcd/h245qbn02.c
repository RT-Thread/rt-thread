/* drivers/video/sunxi/disp2/disp/lcd/he0801a068.c
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

 * lcd_driver_name     = "h245qbn02"
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
#include "h245qbn02.h"

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

    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(10);
    /*3.3v*/
    sunxi_lcd_power_enable(sel, 0);

    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(300);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(20);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_power_enable(sel, 1);
}

static void lcd_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    sunxi_lcd_delay_ms(20);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_disable(sel, 1);
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

static void lcd_panel_init(u32 sel)
{
    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(200);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0x2a, 0x00, 0x00, 0x00, 0xef);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0x2b, 0x00, 0x00, 0x01, 0xaf);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x11);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x36, 0xd0);
    sunxi_lcd_delay_ms(120);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x2c);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x29);
    /*sunxi_lcd_dsi_dcs_write_2para(sel, 0xbd, 0x11, 0x00);*/
    /*sunxi_lcd_dsi_dcs_write_2para(sel, 0xbc, 0x00, 0x94);*/
    /*sunxi_lcd_dsi_dcs_write_2para(sel, 0xbe, 0xd0, 0x02);*/
}

static void lcd_panel_exit(u32 sel)
{
    u8 para[20] = {0x0b, 0x00, 0x00, 0x00, 0x21, 0x4f, 0x01,
               0x0e, 0x2a, 0x66, 0x05, 0x2a, 0x00, 0x05};
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x28);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xf1, 0x5a, 0x5a);
    dsi_dcs_wr(sel, 0xf4, para, 14);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xf1, 0xa5, 0xa5);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x10);
    sunxi_lcd_delay_ms(120);
}

/*sel: 0:lcd0; 1:lcd1*/
static s32 lcd_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

static int lcd_set_esd_info(struct disp_lcd_esd_info *p_info)
{
    if (!p_info)
        return -1;
    p_info->level = 1;
    p_info->freq = 60;
    p_info->esd_check_func_pos = 1;
    return 0;
}


/**
 * @name       :lcd_esd_check
 * @brief      :check if panel is ok
 * @param[IN]  :sel:index of dsi
 * @param[OUT] :none
 * @return     :0 if ok, else not ok
 */
static s32 lcd_esd_check(u32 sel)
{
    tcon_reset(sel);
    return 0;
}

/**
 * @name       :lcd_reset_panel
 * @brief      :reset panel step
 * @param[IN]  :sel:index of dsi
 * @param[OUT] :none
 * @return     :0
 */
static s32 lcd_reset_panel(u32 sel)
{
    /*reset tcon*/
    return 0;
}

struct __lcd_panel h245qbn02_panel = {
    /* panel driver name, must mach the name of
     * lcd_drv_name in sys_config.fex
     */
    .name = "h245qbn02",
    .func = {
        .cfg_panel_info = lcd_cfg_panel_info,
        .cfg_open_flow = lcd_open_flow,
        .cfg_close_flow = lcd_close_flow,
        .lcd_user_defined_func = lcd_user_defined_func,
        .esd_check = lcd_esd_check,
        .reset_panel = lcd_reset_panel,
        .set_esd_info = lcd_set_esd_info,
    },
};
