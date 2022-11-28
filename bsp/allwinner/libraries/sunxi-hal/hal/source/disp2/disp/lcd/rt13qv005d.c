/*
 * drivers/video/fbdev/sunxi/disp2/disp/lcd/rt13qv005d.c
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
[lcd0]
lcd_used            = 1
lcd_driver_name     = "rt13qv005d"
lcd_if              = 1
lcd_x               = 240
lcd_y               = 240
lcd_width           = 26
lcd_height          = 29
lcd_dclk_freq       = 16
lcd_pwm_used        = 1
lcd_pwm_ch          = 8
lcd_pwm_freq        = 50000
lcd_pwm_pol         = 1
lcd_pwm_max_limit   = 255
lcd_hbp             = 20
lcd_ht              = 288
lcd_hspw            = 10
lcd_vbp             = 8
lcd_vt              = 256
lcd_vspw            = 4
lcd_frm             = 1
lcd_hv_clk_phase    = 0
lcd_hv_sync_polarity = 0
lcd_gamma_en        = 0
lcd_bright_curve_en = 1
lcd_cmap_en         = 0
lcd_cpu_mode        = 1
lcd_cpu_te          = 1
lcd_cpu_if          = 12
lcd_hv_if           = 0
lcd_hv_srgb_seq     = 0
lcd_rb_swap         = 0

lcdgamma4iep        = 22

lcd_power           = "vcc-lcd"
lcd_pin_power       = "vcc-pd"

;reset pin
lcd_gpio_0          = port:PD09<1><0><2><1>
;cs pin
lcd_gpio_1          = port:PD10<1><0><2><0>

lcdd3               = port:PD1<2><0><2><default>
lcdd4               = port:PD2<2><0><2><default>
lcdd5               = port:PD3<2><0><2><default>
lcdd6               = port:PD4<2><0><2><default>
lcdd7               = port:PD5<2><0><2><default>
lcdd10              = port:PD6<2><0><2><default>
lcdd11              = port:PD7<2><0><2><default>
lcdd12              = port:PD8<2><0><2><default>
lcdclk              = port:PD18<2><0><3><default>
lcdde               = port:PD19<2><0><3><default>
lcdhsync            = port:PD20<2><0><3><default>
lcdvsync            = port:PD21<2><0><3><default>
[lcd0_suspend]
lcdd3               = port:PD1<7><0><2><default>
lcdd4               = port:PD2<7><0><2><default>
lcdd5               = port:PD3<7><0><2><default>
lcdd6               = port:PD4<7><0><2><default>
lcdd7               = port:PD5<7><0><2><default>
lcdd10              = port:PD6<7><0><2><default>
lcdd11              = port:PD7<7><0><2><default>
lcdd12              = port:PD8<7><0><2><default>
lcdclk              = port:PD18<7><0><3><default>
lcdde               = port:PD19<7><0><3><default>
lcdhsync            = port:PD20<7><0><3><default>
lcdvsync            = port:PD21<7><0><3><default>
 */
#include "rt13qv005d.h"

#define TCON_DEBUG (0)

static void lcd_panel_st7789v_init(u32 sel, struct disp_panel_para *info);
static void lcd_cpu_panel_fr(__u32 sel, __u32 w, __u32 h, __u32 x, __u32 y);
static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

static void LCD_cfg_panel_info(struct panel_extend_para *info)
{
#if 0
    u32 i = 0, j = 0;
    u32 items;
    u8 lcd_gamma_tbl[][2] = {
        //{input value, corrected value}
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
#endif
}

static s32 LCD_open_flow(u32 sel)
{
    LCD_OPEN_FUNC(sel, LCD_power_on, 120);
    LCD_OPEN_FUNC(sel, LCD_panel_init, 100);
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 50);
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 20);
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 10);
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 50);
    LCD_CLOSE_FUNC(sel, LCD_power_off, 0);

    return 0;
}

static void LCD_power_on(u32 sel)
{
    /*config lcd_power pin to open lcd power0 */
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_pin_cfg(sel, 1);

    /*lcd_rst, active hight */
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_gpio_set_value(sel, 1, 1);
    sunxi_lcd_gpio_set_value(sel, 0, 0);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_gpio_set_value(sel, 0, 1);
}

static void LCD_power_off(u32 sel)
{
    /*lcd_cs, active low */
    sunxi_lcd_gpio_set_value(sel, 1, 1);
    sunxi_lcd_delay_ms(10);
    /*lcd_rst, active hight */
    sunxi_lcd_gpio_set_value(sel, 0, 0);
    sunxi_lcd_delay_ms(10);

    sunxi_lcd_pin_cfg(sel, 0);
    /*config lcd_power pin to close lcd power0 */
    sunxi_lcd_power_disable(sel, 0);
}

static void LCD_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
    /*config lcd_bl_en pin to open lcd backlight */
    sunxi_lcd_backlight_enable(sel);
}

static void LCD_bl_close(u32 sel)
{
    /*config lcd_bl_en pin to close lcd backlight */
    sunxi_lcd_backlight_disable(sel);
    sunxi_lcd_pwm_disable(sel);
}

/*static int bootup_flag = 0;*/
static void LCD_panel_init(u32 sel)
{
    struct disp_panel_para *info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL);

    bsp_disp_get_panel_info(sel, info);
    lcd_panel_st7789v_init(sel, info);

    if (LCD_CPU_AUTO_MODE == info->lcd_cpu_mode)
        sunxi_lcd_cpu_set_auto_mode(sel);
    /*else */
    /*  tcon0_cpu_set_tri_mode(sel); */

    disp_sys_free(info);
    return;
}

static void LCD_panel_exit(u32 sel)
{
    sunxi_lcd_cpu_write_index(0, 0x28);
    sunxi_lcd_cpu_write_index(0, 0x10);
}

static void lcd_dbi_wr_dcs(__u32 sel, __u8 cmd, __u8 *para, __u32 para_num)
{
    __u8 index = cmd;
    __u8 *data_p = para;
    __u16 i;
    sunxi_lcd_cpu_write_index(sel, index);
    for (i = 0; i < para_num; i++) {
        sunxi_lcd_cpu_write_data(sel, *(data_p++));
    }
}

static void lcd_cpu_panel_fr(__u32 sel, __u32 w, __u32 h, __u32 x, __u32 y)
{
    __u8 para[4];
    __u32 para_num;
    para[0] = (x >> 8) & 0xff;
    para[1] = (x >> 0) & 0xff;
    para[2] = ((x + w - 1) >> 8) & 0xff;
    para[3] = ((x + w - 1) >> 0) & 0xff;
    para_num = 4;
    lcd_dbi_wr_dcs(sel, DSI_DCS_SET_COLUMN_ADDRESS, para, para_num);

    para[0] = (y >> 8) & 0xff;
    para[1] = (y >> 0) & 0xff;
    para[2] = ((y + h - 1) >> 8) & 0xff;
    para[3] = ((y + h - 1) >> 0) & 0xff;
    para_num = 4;
    lcd_dbi_wr_dcs(sel, DSI_DCS_SET_PAGE_ADDRESS, para, para_num);
}

static void lcd_panel_st7789v_init(u32 sel, struct disp_panel_para *info)
{

    /*lcd_cs, active low */
    sunxi_lcd_gpio_set_value(sel, 1, 0);
    sunxi_lcd_delay_ms(10);


    sunxi_lcd_cpu_write_index(0, 0x11);
    sunxi_lcd_delay_ms(120);

    /* Memory Data Access Control */
    sunxi_lcd_cpu_write_index(0, 0x36);
    sunxi_lcd_cpu_write_data(0, 0x00); /* 0x20 */

    sunxi_lcd_cpu_write_index(0, 0x3A);
    /* 06 ---->262K(RGB666);05---->65K(RGB565) */
    sunxi_lcd_cpu_write_data(0, 0x06);

    sunxi_lcd_cpu_write_index(0, 0xB2);
    sunxi_lcd_cpu_write_data(0, 0x0C);
    sunxi_lcd_cpu_write_data(0, 0x0C);
    sunxi_lcd_cpu_write_data(0, 0x00);
    sunxi_lcd_cpu_write_data(0, 0x33);
    sunxi_lcd_cpu_write_data(0, 0x33);

    sunxi_lcd_cpu_write_index(0, 0xB7);
    sunxi_lcd_cpu_write_data(0, 0x75);

    sunxi_lcd_cpu_write_index(0, 0xBB);
    /* 0x20);//0x3C);//0x0E);//0x20);  //vcom    0x20 */
    sunxi_lcd_cpu_write_data(0, 0x3D);

    sunxi_lcd_cpu_write_index(0, 0xC2);
    sunxi_lcd_cpu_write_data(0, 0x01);
    /* VRH--->值越大越暗，反之越白 */
    sunxi_lcd_cpu_write_index(0, 0xC3);
    /* 0x0b);//0x0b);   0x0B 0x06 */
    sunxi_lcd_cpu_write_data(0, 0x19);

    sunxi_lcd_cpu_write_index(0, 0xC4);
    sunxi_lcd_cpu_write_data(0, 0x20);

    sunxi_lcd_cpu_write_index(0, 0xC6);
    /* frame */
    sunxi_lcd_cpu_write_data(0, 0x0F);

    sunxi_lcd_cpu_write_index(0, 0xD0);
    sunxi_lcd_cpu_write_data(0, 0xA4);
    sunxi_lcd_cpu_write_data(0, 0xA1);

    sunxi_lcd_cpu_write_index(0, 0xD6);
    sunxi_lcd_cpu_write_data(0, 0xA1);

    /*[> gamma <]*/
    sunxi_lcd_cpu_write_index(0, 0xE0);
    sunxi_lcd_cpu_write_data(0, 0x70);
    sunxi_lcd_cpu_write_data(0, 0x04);
    sunxi_lcd_cpu_write_data(0, 0x08);
    sunxi_lcd_cpu_write_data(0, 0x09);
    sunxi_lcd_cpu_write_data(0, 0x09);
    sunxi_lcd_cpu_write_data(0, 0x05);
    sunxi_lcd_cpu_write_data(0, 0x2a);
    sunxi_lcd_cpu_write_data(0, 0x33);
    sunxi_lcd_cpu_write_data(0, 0x41);
    sunxi_lcd_cpu_write_data(0, 0x07);
    sunxi_lcd_cpu_write_data(0, 0x13);
    sunxi_lcd_cpu_write_data(0, 0x13);
    sunxi_lcd_cpu_write_data(0, 0x29);
    sunxi_lcd_cpu_write_data(0, 0x2f);

    sunxi_lcd_cpu_write_index(0, 0xE1); /* gamma */
    sunxi_lcd_cpu_write_data(0, 0x70);
    sunxi_lcd_cpu_write_data(0, 0x03);
    sunxi_lcd_cpu_write_data(0, 0x09);
    sunxi_lcd_cpu_write_data(0, 0x0A);
    sunxi_lcd_cpu_write_data(0, 0x09);
    sunxi_lcd_cpu_write_data(0, 0x06);
    sunxi_lcd_cpu_write_data(0, 0x2B);
    sunxi_lcd_cpu_write_data(0, 0x34);
    sunxi_lcd_cpu_write_data(0, 0x41);
    sunxi_lcd_cpu_write_data(0, 0x07);
    sunxi_lcd_cpu_write_data(0, 0x12);
    sunxi_lcd_cpu_write_data(0, 0x14);
    sunxi_lcd_cpu_write_data(0, 0x28);
    sunxi_lcd_cpu_write_data(0, 0x2E);
    /*inversion on */
    sunxi_lcd_cpu_write_index(0, 0x21);
    /*te on*/
    sunxi_lcd_cpu_write_index(0, 0x35);
    sunxi_lcd_cpu_write_data(0, 0x00);

    sunxi_lcd_cpu_write_index(0, 0x29); /* Display on */

    lcd_cpu_panel_fr(0, info->lcd_x, info->lcd_y, 0, 0);

    sunxi_lcd_cpu_write_index(0, 0x2C); /* start memory write */

}

/* sel: 0:lcd0; 1:lcd1 */
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

/* panel driver name, must mach the name of lcd_drv_name in sys_config.fex */
struct __lcd_panel rt13qv005d_panel = {
    .name = "rt13qv005d",
    .func = {
        .cfg_panel_info = LCD_cfg_panel_info,
        .cfg_open_flow = LCD_open_flow,
        .cfg_close_flow = LCD_close_flow,
        .lcd_user_defined_func = LCD_user_defined_func,
    },
};
