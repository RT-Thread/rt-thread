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
 *[lcd0]
 *lcd_used            = 1
 *
 *lcd_driver_name     = "wtl096601g03"
 *
 *lcd_bl_0_percent    = 0
 *lcd_bl_40_percent   = 23
 *lcd_bl_100_percent  = 100
 *lcd_backlight       = 150
 *
 *lcd_if              = 4
 *lcd_x               = 320
 *lcd_y               = 1280
 *lcd_width           = 5
 *lcd_height          = 5
 *lcd_dclk_freq       = 33
 *
 *lcd_pwm_used        = 1
 *lcd_pwm_ch          = 8
 *lcd_pwm_freq        = 50000
 *lcd_pwm_pol         = 1
 *lcd_pwm_max_limit   = 255
 *
 *lcd_hbp             = 50
 *lcd_ht              = 420
 *lcd_hspw            = 30
 *lcd_vbp             = 30
 *lcd_vt              = 1340
 *lcd_vspw            = 20
 *
 *lcd_dsi_if          = 0
 *lcd_dsi_lane        = 4
 *lcd_dsi_format      = 0
 *lcd_dsi_te          = 0
 *lcd_dsi_eotp        = 0
 *
 *lcd_frm             = 0
 *lcd_io_phase        = 0x0000
 *lcd_hv_clk_phase    = 0
 *lcd_hv_sync_polarity= 0
 *lcd_gamma_en        = 0
 *lcd_bright_curve_en = 0
 *lcd_cmap_en         = 0
 *
 *lcdgamma4iep        = 22
 *
 *;lcd_bl_en           = port:PD09<1><0><default><1>
 *lcd_power            = "vcc-lcd"
 *lcd_pin_power        = "vcc18-dsi"
 *lcd_pin_power1        = "vcc-pd"
 *
 *;reset
 *lcd_gpio_0          = port:PD09<1><0><default><1>
*/
#include "wtl096601g03.h"

static void lcd_power_on(u32 sel);
static void lcd_power_off(u32 sel);
static void lcd_bl_open(u32 sel);
static void lcd_bl_close(u32 sel);

static void lcd_panel_init(u32 sel);
static void lcd_panel_exit(u32 sel);

#define panel_reset(sel, val) sunxi_lcd_gpio_set_value(sel, 0, val)

//#define GAMMA2_0
//#define GAMMA2_2
//gamma 0.73
unsigned char gammaTable[256] = {
 0x02, 0x05, 0x08, 0x0b, 0x0d, 0x0f, 0x11, 0x13,
 0x15, 0x17, 0x19, 0x1a, 0x1c, 0x1e, 0x1f, 0x21,
 0x23, 0x24, 0x26, 0x27, 0x29, 0x2a, 0x2b, 0x2d,
 0x2e, 0x30, 0x31, 0x32, 0x34, 0x35, 0x36, 0x38,
 0x39, 0x3a, 0x3b, 0x3d, 0x3e, 0x3f, 0x40, 0x42,
 0x43, 0x44, 0x45, 0x46, 0x48, 0x49, 0x4a, 0x4b,
 0x4c, 0x4d, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54,
 0x55, 0x56, 0x57, 0x59, 0x5a, 0x5b, 0x5c, 0x5d,
 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65,
 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d,
 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d,
 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 0x83, 0x84,
 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c,
 0x8d, 0x8e, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93,
 0x94, 0x95, 0x96, 0x96, 0x97, 0x98, 0x99, 0x9a,
 0x9b, 0x9c, 0x9d, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1,
 0xa2, 0xa3, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
 0xa9, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xae,
 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb3, 0xb4, 0xb5,
 0xb6, 0xb7, 0xb8, 0xb8, 0xb9, 0xba, 0xbb, 0xbc,
 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc0, 0xc1, 0xc2,
 0xc3, 0xc4, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc8,
 0xc9, 0xca, 0xcb, 0xcc, 0xcc, 0xcd, 0xce, 0xcf,
 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd3, 0xd4, 0xd5,
 0xd6, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xda, 0xdb,
 0xdc, 0xdd, 0xdd, 0xde, 0xdf, 0xe0, 0xe0, 0xe1,
 0xe2, 0xe3, 0xe3, 0xe4, 0xe5, 0xe6, 0xe6, 0xe7,
 0xe8, 0xe9, 0xe9, 0xea, 0xeb, 0xec, 0xec, 0xed,
 0xee, 0xef, 0xef, 0xf0, 0xf1, 0xf2, 0xf2, 0xf3,
 0xf4, 0xf4, 0xf5, 0xf6, 0xf7, 0xf7, 0xf8, 0xf9,
 0xfa, 0xfa, 0xfb, 0xfc, 0xfc, 0xfd, 0xfe, 0xff,
};

static void lcd_cfg_panel_info(struct panel_extend_para *info)
{
    u32 i = 0;
    u32 g = 0, value = 0;

    for (i = 0; i < 256; i++) {

        g = gammaTable[i] & 0xff;
        value = 0xff000000 | (g << 16) | (g << 8) | g;

        info->lcd_gamma_tbl[i] = value;
    }
    info->lcd_gamma_en = 1;

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

    /* reset lcd by gpio */
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(100);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(100);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(120);
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

static void lcd_panel_init(u32 sel)
{
    u32 i = 0;

    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(10);

    /* init code for lcd */
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x11);
    sunxi_lcd_delay_ms(100);
    #if 0
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB0, 0x5A); //4T

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x89, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x91, 0x17);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2C, 0x28);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0x00, 0xF1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x01, 0x18);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x02, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x03, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x04, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x05, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x06, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x07, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x08, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x09, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0A, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0B, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0D, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0E, 0x24);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0F, 0x1C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x10, 0xC9);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x11, 0x60);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x12, 0x70);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x13, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x14, 0xE7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x15, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x16, 0x3D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x17, 0x0E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x18, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x19, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1A, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1B, 0xFC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1C, 0x0B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1D, 0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1E, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1F, 0x04);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x20, 0x0C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x21, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x22, 0x04);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x23, 0x81);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x24, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x25, 0x10);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x26, 0x9B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2D, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2E, 0x84);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2F, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x30, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x31, 0x08);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x32, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x33, 0x1C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x34, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x35, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x36, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x37, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x38, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x39, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3A, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3B, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3D, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3E, 0x0F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3F, 0x8C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x40, 0x2A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x41, 0xFC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x42, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x43, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x44, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x45, 0xE8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x46, 0x16);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x47, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x48, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x49, 0x88);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4A, 0x08);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4B, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4C, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4D, 0xD0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4E, 0x13);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4F, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x50, 0x0A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x51, 0x53);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x52, 0x26);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x53, 0x22);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x54, 0x09);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x55, 0x22);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x56, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x57, 0x1C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x58, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x59, 0x3F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5A, 0x28);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5B, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5C, 0xCC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5D, 0x21);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5E, 0x84);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5F, 0x84);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x60, 0x8E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x61, 0x89);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x62, 0xF0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x63, 0xB9);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x64, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x65, 0x96);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x66, 0x0A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x67, 0x62);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x68, 0x90);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x69, 0x12);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6A, 0x42);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6B, 0x48);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6C, 0xE8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6D, 0x98);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6E, 0x08);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x9F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x70, 0x6B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x71, 0x6C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x72, 0xA9);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x73, 0x20);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x74, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x75, 0x29);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x76, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x77, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x78, 0x0F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x79, 0xE0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7A, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7B, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7C, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7D, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7E, 0x4F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7F, 0xFE);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x02);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0x00, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x01, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x02, 0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x03, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x04, 0x54);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x05, 0x38);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x06, 0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x07, 0x0A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x08, 0xC0);//40
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x09, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0A, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0B, 0x14);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0C, 0xE6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0D, 0x0D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0F, 0x08);//00
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x10, 0xF9);//Gamma
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x11, 0xCC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x12, 0x96);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x13, 0x36);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x14, 0x53);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x15, 0x42);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x16, 0xCA);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x17, 0xEE);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x18, 0xF1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x19, 0xF1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1A, 0x76);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1B, 0x0E);//Gamma
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1C, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1D, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1E, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1F, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x20, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x21, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x22, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x23, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x24, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x25, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x26, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x27, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x28, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x29, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2A, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2B, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2C, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2D, 0x07);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x33, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x35, 0x7E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x36, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x38, 0x7E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3A, 0x80);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3B, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3D, 0x2A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3E, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3F, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x40, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x41, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x42, 0xA8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x43, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x44, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x45, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x46, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x47, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x48, 0x9B);//8B
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x49, 0xD2);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4A, 0x81);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4B, 0x02);//42
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4C, 0x15);//16
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4D, 0xC0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4E, 0x0F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4F, 0x61);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x50, 0x78);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x51, 0x7A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x52, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x53, 0x99);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x54, 0xA2);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x55, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x56, 0x14);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x57, 0xB8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x58, 0xDC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x59, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5A, 0x1E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5B, 0x8F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5C, 0xC7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5D, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5E, 0xF1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5F, 0x78);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x60, 0x3C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x61, 0x36);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x62, 0x1E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x63, 0x1B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x64, 0x8F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x65, 0xC7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x66, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x67, 0x31);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x68, 0x0C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x69, 0x89);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6A, 0x30);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6B, 0x8C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6C, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6D, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6E, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x70, 0xC7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x71, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x72, 0x31);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x73, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x74, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x75, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x76, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x77, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x78, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x79, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7A, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7B, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7C, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7D, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7E, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7F, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0B, 0x00);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2C, 0x2C);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x89, 0x03);
    #endif

    #if 0
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB0, 0x5A);//4T

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x89, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x91, 0x17);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2C, 0x28);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0x00, 0xF1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x01, 0x18);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x02, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x03, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x04, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x05, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x06, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x07, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x08, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x09, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0A, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0B, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0D, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0E, 0x24);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0F, 0x1C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x10, 0xC9);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x11, 0x60);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x12, 0x70);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x13, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x14, 0xE7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x15, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x16, 0x3D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x17, 0x0E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x18, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x19, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1A, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1B, 0xFC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1C, 0x0B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1D, 0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1E, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1F, 0x04);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x20, 0x0C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x21, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x22, 0x04);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x23, 0x81);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x24, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x25, 0x10);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x26, 0x9B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2D, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2E, 0x84);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2F, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x30, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x31, 0x08);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x32, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x33, 0x1C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x34, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x35, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x36, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x37, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x38, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x39, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3A, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3B, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3D, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3E, 0x0F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3F, 0x8C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x40, 0x2A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x41, 0xFC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x42, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x43, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x44, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x45, 0xE8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x46, 0x16);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x47, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x48, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x49, 0x88);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4A, 0x08);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4B, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4C, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4D, 0xD0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4E, 0x13);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4F, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x50, 0x0A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x51, 0x53);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x52, 0x26);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x53, 0x22);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x54, 0x09);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x55, 0x22);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x56, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x57, 0x1C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x58, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x59, 0x3F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5A, 0x28);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5B, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5C, 0xCC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5D, 0x21);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5E, 0x84);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5F, 0x84);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x60, 0x8E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x61, 0x89);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x62, 0xF0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x63, 0xB9);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x64, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x65, 0x96);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x66, 0x0A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x67, 0x62);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x68, 0x90);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x69, 0x12);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6A, 0x42);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6B, 0x48);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6C, 0xE8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6D, 0x98);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6E, 0x08);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x9F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x70, 0x6B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x71, 0x6C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x72, 0xA9);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x73, 0x20);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x74, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x75, 0x29);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x76, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x77, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x78, 0x0F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x79, 0xE0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7A, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7B, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7C, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7D, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7E, 0x4F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7F, 0xFE);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x02);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0x00, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x01, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x02, 0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x03, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x04, 0x54);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x05, 0x38);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x06, 0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x07, 0x0A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x08, 0xC0);//40
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x09, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0A, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0B, 0x14);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0C, 0xE6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0D, 0x0D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0F, 0x08);//00
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x10, 0xB9);//Gamma
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x11, 0x4D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x12, 0x47);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x13, 0xC7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x14, 0x73);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x15, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x16, 0x1C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x17, 0xF7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x18, 0xFD);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x19, 0xFB);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1A, 0x78);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1B, 0x0E);//Gamma
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1C, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1D, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1E, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1F, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x20, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x21, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x22, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x23, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x24, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x25, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x26, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x27, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x28, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x29, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2A, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2B, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2C, 0xFF);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2D, 0x07);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x33, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x35, 0x7E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x36, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x38, 0x7E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3A, 0x80);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3B, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3D, 0x2A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3E, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3F, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x40, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x41, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x42, 0xA8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x43, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x44, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x45, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x46, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x47, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x48, 0x9B);//8B
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x49, 0xD2);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4A, 0x81);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4B, 0x02);//42
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4C, 0x15);//16
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4D, 0xC0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4E, 0x0F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x4F, 0x61);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x50, 0x78);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x51, 0x7A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x52, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x53, 0x99);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x54, 0xA2);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x55, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x56, 0x14);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x57, 0xB8);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x58, 0xDC);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x59, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5A, 0x1E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5B, 0x8F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5C, 0xC7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5D, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5E, 0xF1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5F, 0x78);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x60, 0x3C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x61, 0x36);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x62, 0x1E);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x63, 0x1B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x64, 0x8F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x65, 0xC7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x66, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x67, 0x31);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x68, 0x0C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x69, 0x89);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6A, 0x30);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6B, 0x8C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6C, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6D, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6E, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x8D);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x70, 0xC7);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x71, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x72, 0x31);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x73, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x74, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x75, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x76, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x77, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x78, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x79, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7A, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7B, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7C, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7D, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7E, 0xC6);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7F, 0xE3);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0B, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2C, 0x2C);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB1, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x89, 0x03);
    #endif
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x29);

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

struct __lcd_panel wtl096601g03_panel = {
    /* panel driver name, must mach the name of
     * lcd_drv_name in sys_config.fex
     */
    .name = "wtl096601g03",
    .func = {
        .cfg_panel_info = lcd_cfg_panel_info,
            .cfg_open_flow = lcd_open_flow,
            .cfg_close_flow = lcd_close_flow,
            .lcd_user_defined_func = lcd_user_defined_func,
    },
};
