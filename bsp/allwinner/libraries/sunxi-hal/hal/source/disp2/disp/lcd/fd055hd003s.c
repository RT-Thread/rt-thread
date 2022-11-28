/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
[lcd0]
lcd_used            = 1

lcd_driver_name     = "fd005hd003s"
lcd_bl_0_percent    = 0
lcd_bl_40_percent   = 23
lcd_bl_100_percent  = 100
lcd_backlight       = 100

lcd_if              = 4
lcd_x               = 720
lcd_y               = 1280
lcd_width           = 52
lcd_height          = 52
lcd_dclk_freq       = 66

lcd_pwm_used        = 1
lcd_pwm_ch          = 0
lcd_pwm_freq        = 50000
lcd_pwm_pol         = 1
lcd_pwm_max_limit   = 255

lcd_hbp             = 65
lcd_ht              = 900
lcd_hspw            = 30
lcd_vbp             = 12
lcd_vt              = 1350
lcd_vspw            = 4

lcd_dsi_if          = 0
lcd_dsi_lane        = 4
lcd_dsi_format      = 0
lcd_dsi_te          = 0
lcd_dsi_eotp        = 0

lcd_frm             = 0
lcd_io_phase        = 0x0000
lcd_hv_clk_phase    = 0
lcd_hv_sync_polarity= 0
lcd_gamma_en        = 0
lcd_bright_curve_en = 0
lcd_cmap_en         = 0

lcdgamma4iep        = 22

lcd_bl_en           = port:PB07<1><0><default><1>
lcd_power           = "axp233_dc1sw"

lcd_gpio_0          = port:PB06<1><0><default><1>
 */

#include "fd055hd003s.h"

static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

#define SSD_CMD(a) sunxi_lcd_dsi_dcs_write_0para(sel, a)
#define SSD_Single(a, b) sunxi_lcd_dsi_dcs_write_1para(sel, a, b)
#define panel_reset(sel, val) sunxi_lcd_gpio_set_value(sel, 0, val)
#define Delayms sunxi_lcd_delay_ms

static void fd005hd003s_init(__u32 sel, __u32 mode, __u32 lane, __u32 format)
{
    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(10);

    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(5);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(10);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(120);

    SSD_Single(0xE0, 0x00);
    SSD_Single(0xE1, 0x93);
    SSD_Single(0xE2, 0x65);
    SSD_Single(0xE3, 0xF8);

    SSD_Single(0xE0, 0x01);
    SSD_Single(0x00, 0x00);
    SSD_Single(0x01, 0x48);
    SSD_Single(0x03, 0x00);
    SSD_Single(0x04, 0x66);
    SSD_Single(0x17, 0x00);
    SSD_Single(0x18, 0xBF);
    SSD_Single(0x19, 0x03);
    SSD_Single(0x1A, 0x00);
    SSD_Single(0x1B, 0xBF);
    SSD_Single(0x1C, 0x03);
    SSD_Single(0x1F, 0x79);
    SSD_Single(0x20, 0x2D);
    SSD_Single(0x21, 0x2D);
    SSD_Single(0x22, 0x4F);
    SSD_Single(0x26, 0xF1);
    SSD_Single(0x37, 0x09);
    SSD_Single(0x38, 0x04);
    SSD_Single(0x39, 0x0C);
    SSD_Single(0x3A, 0x18);
    SSD_Single(0x3C, 0x78);
    SSD_Single(0x40, 0x04);
    SSD_Single(0x41, 0xA0);
    SSD_Single(0x55, 0x01);
    SSD_Single(0x56, 0x01);
    SSD_Single(0x57, 0x6D);
    SSD_Single(0x58, 0x0A);
    SSD_Single(0x59, 0x1A);
    SSD_Single(0x5A, 0x65);
    SSD_Single(0x5B, 0x14);
    SSD_Single(0x5C, 0x15);
    SSD_Single(0x5D, 0x70);
    SSD_Single(0x5E, 0x58);
    SSD_Single(0x5F, 0x48);
    SSD_Single(0x60, 0x3B);
    SSD_Single(0x61, 0x35);
    SSD_Single(0x62, 0x25);
    SSD_Single(0x63, 0x29);
    SSD_Single(0x64, 0x13);
    SSD_Single(0x65, 0x2C);
    SSD_Single(0x66, 0x2C);
    SSD_Single(0x67, 0x2C);
    SSD_Single(0x68, 0x4B);
    SSD_Single(0x69, 0x3B);
    SSD_Single(0x6A, 0x43);
    SSD_Single(0x6B, 0x35);
    SSD_Single(0x6C, 0x2F);
    SSD_Single(0x6D, 0x25);
    SSD_Single(0x6E, 0x13);
    SSD_Single(0x6F, 0x02);
    SSD_Single(0x70, 0x70);
    SSD_Single(0x71, 0x58);
    SSD_Single(0x72, 0x48);
    SSD_Single(0x73, 0x3B);
    SSD_Single(0x74, 0x35);
    SSD_Single(0x75, 0x25);
    SSD_Single(0x76, 0x29);
    SSD_Single(0x77, 0x13);
    SSD_Single(0x78, 0x2C);
    SSD_Single(0x79, 0x2C);
    SSD_Single(0x7A, 0x2C);
    SSD_Single(0x7B, 0x4B);
    SSD_Single(0x7C, 0x3B);
    SSD_Single(0x7D, 0x43);
    SSD_Single(0x7E, 0x35);
    SSD_Single(0x7F, 0x2F);
    SSD_Single(0x80, 0x25);
    SSD_Single(0x81, 0x13);
    SSD_Single(0x82, 0x02);
    SSD_Single(0xE0, 0x02);
    SSD_Single(0x00, 0x13);
    SSD_Single(0x01, 0x11);
    SSD_Single(0x02, 0x0B);
    SSD_Single(0x03, 0x09);
    SSD_Single(0x04, 0x07);
    SSD_Single(0x05, 0x05);
    SSD_Single(0x06, 0x1F);
    SSD_Single(0x07, 0x1F);
    SSD_Single(0x08, 0x1F);
    SSD_Single(0x09, 0x1F);
    SSD_Single(0x0A, 0x1F);
    SSD_Single(0x0B, 0x1F);
    SSD_Single(0x0C, 0x1F);
    SSD_Single(0x0D, 0x1F);
    SSD_Single(0x0E, 0x1F);
    SSD_Single(0x0F, 0x1F);
    SSD_Single(0x10, 0x1F);
    SSD_Single(0x11, 0x1F);
    SSD_Single(0x12, 0x01);
    SSD_Single(0x13, 0x03);
    SSD_Single(0x14, 0x1F);
    SSD_Single(0x15, 0x1F);
    SSD_Single(0x16, 0x12);
    SSD_Single(0x17, 0x10);
    SSD_Single(0x18, 0x0A);
    SSD_Single(0x19, 0x08);
    SSD_Single(0x1A, 0x06);
    SSD_Single(0x1B, 0x04);
    SSD_Single(0x1C, 0x1F);
    SSD_Single(0x1D, 0x1F);
    SSD_Single(0x1E, 0x1F);
    SSD_Single(0x1F, 0x1F);
    SSD_Single(0x20, 0x1F);
    SSD_Single(0x21, 0x1F);
    SSD_Single(0x22, 0x1F);
    SSD_Single(0x23, 0x1F);
    SSD_Single(0x24, 0x1F);
    SSD_Single(0x25, 0x1F);
    SSD_Single(0x26, 0x1F);
    SSD_Single(0x27, 0x1F);
    SSD_Single(0x28, 0x00);
    SSD_Single(0x29, 0x02);
    SSD_Single(0x2A, 0x1F);
    SSD_Single(0x2B, 0x1F);
    SSD_Single(0x2C, 0x00);
    SSD_Single(0x2D, 0x02);
    SSD_Single(0x2E, 0x08);
    SSD_Single(0x2F, 0x0A);
    SSD_Single(0x30, 0x04);
    SSD_Single(0x31, 0x06);
    SSD_Single(0x32, 0x1F);
    SSD_Single(0x33, 0x1F);
    SSD_Single(0x34, 0x1F);
    SSD_Single(0x35, 0x1F);
    SSD_Single(0x36, 0x1F);
    SSD_Single(0x37, 0x1F);
    SSD_Single(0x38, 0x1F);
    SSD_Single(0x39, 0x1F);
    SSD_Single(0x3A, 0x1F);
    SSD_Single(0x3B, 0x1F);
    SSD_Single(0x3C, 0x1F);
    SSD_Single(0x3D, 0x1F);
    SSD_Single(0x3E, 0x12);
    SSD_Single(0x3F, 0x10);
    SSD_Single(0x40, 0x1F);
    SSD_Single(0x41, 0x1F);
    SSD_Single(0x42, 0x01);
    SSD_Single(0x43, 0x03);
    SSD_Single(0x44, 0x09);
    SSD_Single(0x45, 0x0B);
    SSD_Single(0x46, 0x05);
    SSD_Single(0x47, 0x07);
    SSD_Single(0x48, 0x1F);
    SSD_Single(0x49, 0x1F);
    SSD_Single(0x4A, 0x1F);
    SSD_Single(0x4B, 0x1F);
    SSD_Single(0x4C, 0x1F);
    SSD_Single(0x4D, 0x1F);
    SSD_Single(0x4E, 0x1F);
    SSD_Single(0x4F, 0x1F);
    SSD_Single(0x50, 0x1F);
    SSD_Single(0x51, 0x1F);
    SSD_Single(0x52, 0x1F);
    SSD_Single(0x53, 0x1F);
    SSD_Single(0x54, 0x13);
    SSD_Single(0x55, 0x11);
    SSD_Single(0x56, 0x1F);
    SSD_Single(0x57, 0x1F);
    SSD_Single(0x58, 0x40);
    SSD_Single(0x59, 0x00);
    SSD_Single(0x5A, 0x00);
    SSD_Single(0x5B, 0x30);
    SSD_Single(0x5C, 0x09);
    SSD_Single(0x5D, 0x30);
    SSD_Single(0x5E, 0x01);
    SSD_Single(0x5F, 0x02);
    SSD_Single(0x60, 0x30);
    SSD_Single(0x61, 0x01);
    SSD_Single(0x62, 0x02);
    SSD_Single(0x63, 0x03);
    SSD_Single(0x64, 0x64);
    SSD_Single(0x65, 0x75);
    SSD_Single(0x66, 0x0D);
    SSD_Single(0x67, 0x72);
    SSD_Single(0x68, 0x0C);
    SSD_Single(0x69, 0x10);
    SSD_Single(0x6A, 0x64);
    SSD_Single(0x6B, 0x08);
    SSD_Single(0x6C, 0x00);
    SSD_Single(0x6D, 0x00);
    SSD_Single(0x6E, 0x00);
    SSD_Single(0x6F, 0x00);
    SSD_Single(0x70, 0x00);
    SSD_Single(0x71, 0x00);
    SSD_Single(0x72, 0x06);
    SSD_Single(0x73, 0x86);
    SSD_Single(0x74, 0x00);
    SSD_Single(0x75, 0x07);
    SSD_Single(0x76, 0x00);
    SSD_Single(0x77, 0x5D);
    SSD_Single(0x78, 0x19);
    SSD_Single(0x79, 0x00);
    SSD_Single(0x7A, 0x05);
    SSD_Single(0x7B, 0x05);
    SSD_Single(0x7C, 0x00);
    SSD_Single(0x7D, 0x03);
    SSD_Single(0x7E, 0x86);
    SSD_Single(0xE0, 0x04);
    SSD_Single(0x09, 0x10);
    SSD_Single(0x2B, 0x2B);
    SSD_Single(0x2E, 0x44);
    SSD_Single(0x2D, 0x03);
    SSD_Single(0xE0, 0x00);
    SSD_Single(0xE6, 0x02);
    SSD_Single(0xE7, 0x02);
    SSD_Single(0x80, 0x03);
    SSD_CMD(0x11);
    Delayms(120);
    SSD_CMD(0x29);
    Delayms(5);
    SSD_Single(0x35, 0x00);
}

static void LCD_cfg_panel_info(struct panel_extend_para *info)
{
    u32 i = 0, j = 0;
    u32 items;
    u8 lcd_gamma_tbl[][2] = {
        /* {input value, corrected value} */
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

static s32 LCD_open_flow(u32 sel)
{
    /* open lcd power, and delay 50ms */
    LCD_OPEN_FUNC(sel, LCD_power_on, 10);
    /* open lcd power, than delay 200ms */
    LCD_OPEN_FUNC(sel, LCD_panel_init, 10);
    /* open lcd controller, and delay 100ms */
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 50);
    /* open lcd backlight, and delay 0ms */
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    /* close lcd backlight, and delay 0ms */
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 0);
    /* close lcd controller, and delay 0ms */
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);
    /* open lcd power, than delay 200ms */
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 10);
    /* close lcd power, and delay 500ms */
    LCD_CLOSE_FUNC(sel, LCD_power_off, 100);

    return 0;
}

static void LCD_power_on(u32 sel)
{
    /* config lcd_power pin to open lcd power */
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_pin_cfg(sel, 1);
    sunxi_lcd_delay_ms(10);
}

static void LCD_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    /* config lcd_power pin to open lcd power */
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_disable(sel, 0);
    sunxi_lcd_delay_ms(5);
}

static void LCD_bl_open(u32 sel)
{
    /* config lcd_bl_en pin to open lcd backlight */
    sunxi_lcd_backlight_enable(sel);
    sunxi_lcd_pwm_enable(sel);
}

static void LCD_bl_close(u32 sel)
{
    /* config lcd_bl_en pin to close lcd backlight */
    sunxi_lcd_backlight_disable(sel);
}

static void LCD_panel_init(u32 sel)
{
    fd005hd003s_init(sel, 0, 0, 0);
}

static void LCD_panel_exit(u32 sel)
{
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_SET_DISPLAY_OFF);
    sunxi_lcd_delay_ms(50);
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_ENTER_SLEEP_MODE);
    sunxi_lcd_delay_ms(20);
}

/* sel: 0:lcd0; 1:lcd1 */
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel fd055hd003s_panel = {
    /* panel driver name, must mach the lcd_drv_name in sys_config.fex */
    .name = "fd005hd003s",
    .func = {
         .cfg_panel_info = LCD_cfg_panel_info,
         .cfg_open_flow = LCD_open_flow,
         .cfg_close_flow = LCD_close_flow,
         .lcd_user_defined_func = LCD_user_defined_func,
         }
    ,
};
