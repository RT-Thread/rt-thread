/*
 * drivers/video/fbdev/sunxi/disp2/disp/lcd/s2003t46/s2003t46g.c
 *
 * Copyright (c) 2007-2018 Allwinnertech Co., Ltd.
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
 *
lcd_used            = <1>;

lcd_driver_name     = "st7789v_cpu";

lcd_backlight       = <150>;

lcd_if              = <1>;
lcd_x               = <240>;
lcd_y               = <320>;
lcd_width           = <108>;
lcd_height          = <64>;
lcd_dclk_freq       = <18>;

lcd_pwm_used        = <1>;
lcd_pwm_ch          = <8>;
lcd_pwm_freq        = <50000>;
lcd_pwm_pol         = <1>;
lcd_pwm_max_limit   = <255>;

lcd_hbp             = <60>;
lcd_ht              = <298>;
lcd_hspw            = <30>;
lcd_vbp             = <340>;
lcd_vt              = <336>;
lcd_vspw            = <2>;

lcd_frm             = <1>;
lcd_io_phase        = <0x0000>;
lcd_hv_clk_phase    = <0>;
lcd_hv_sync_polarity= <0>;
lcd_hv_data_polarity = <1>;
lcd_gamma_en        = <0>;
lcd_bright_curve_en = <0>;
lcd_cmap_en         = <0>;

lcdgamma4iep        = <22>;
lcd_cpu_mode        = <1>;
lcd_cpu_te          = <1>;
lcd_cpu_if      = <12>;
lcd_hv_if           = <0>;
lcd_hv_srgb_seq     = <0>;
lcd_rb_swap         = <0>;

lcd_gpio_0 = <&pio PE 16 1 0 3 0>;
lcd_gpio_1 = <&pio PE 17 1 0 3 0>;

pinctrl-0 = <&rgb8_pins_a>;
pinctrl-1 = <&rgb8_pins_b>;

 */

#include "st7789v_cpu.h"

#define CPU_TRI_MODE

#define DBG_INFO(format, args...) (printk("[ST7789V LCD INFO] LINE:%04d-->%s:"format, __LINE__, __func__, ##args))
#define DBG_ERR(format, args...) (printk("[ST7789V LCD ERR] LINE:%04d-->%s:"format, __LINE__, __func__, ##args))
#define panel_reset(val) sunxi_lcd_gpio_set_value(sel, 0, val)
#define lcd_cs(val)  sunxi_lcd_gpio_set_value(sel, 1, val)

static void lcd_panel_st7789v_init(u32 sel, struct disp_panel_para *info);
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
#ifdef CPU_TRI_MODE
    LCD_OPEN_FUNC(sel, LCD_panel_init, 100);
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 50);
#else
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 100);
    LCD_OPEN_FUNC(sel, LCD_panel_init, 50);
#endif
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 20);
#ifdef CPU_TRI_MODE
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 10);
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 50);
#else
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 10);
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 10);
#endif
    LCD_CLOSE_FUNC(sel, LCD_power_off, 0);

    return 0;
}

static void LCD_power_on(u32 sel)
{
    /*config lcd_power pin to open lcd power0 */
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_pin_cfg(sel, 1);

}

static void LCD_power_off(u32 sel)
{
    /*lcd_cs, active low */
    lcd_cs(1);
    sunxi_lcd_delay_ms(10);
    /*lcd_rst, active hight */
    panel_reset(1);
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

    DBG_INFO("\n");
    bsp_disp_get_panel_info(sel, info);
    lcd_panel_st7789v_init(sel, info);

    disp_sys_free(info);
    return;
}

static void LCD_panel_exit(u32 sel)
{
    sunxi_lcd_cpu_write_index(0, 0x28);
    sunxi_lcd_cpu_write_index(0, 0x10);
}


static void lcd_panel_st7789v_init(u32 sel, struct disp_panel_para *info)
{
    DBG_INFO("\n");
    /*lcd_cs, active low */
    lcd_cs(0);
    sunxi_lcd_delay_ms(10);
    panel_reset(1);
    sunxi_lcd_delay_ms(20);
    panel_reset(0);
    sunxi_lcd_delay_ms(20);
    panel_reset(1);
    sunxi_lcd_delay_ms(20);
    sunxi_lcd_cpu_write_index(0, 0x11);
    sunxi_lcd_delay_ms(120);
    sunxi_lcd_cpu_write_index(0, 0x36);
    sunxi_lcd_cpu_write_data(0, 0x00);
    sunxi_lcd_cpu_write_index(0, 0x3a);
    sunxi_lcd_cpu_write_data(0, 0x06);
    sunxi_lcd_cpu_write_index(0, 0x21);
    sunxi_lcd_cpu_write_index(0, 0xb2);
    sunxi_lcd_cpu_write_data(0, 0x05);
    sunxi_lcd_cpu_write_data(0, 0x05);
    sunxi_lcd_cpu_write_data(0, 0x00);
    sunxi_lcd_cpu_write_data(0, 0x33);
    sunxi_lcd_cpu_write_data(0, 0x33);
    sunxi_lcd_cpu_write_index(0, 0xb7);
    sunxi_lcd_cpu_write_data(0, 0x35);
    /*ST7789V Power setting */
    sunxi_lcd_cpu_write_index(0, 0xb8);
    sunxi_lcd_cpu_write_data(0, 0x2f);
    sunxi_lcd_cpu_write_data(0, 0x2b);
    sunxi_lcd_cpu_write_data(0, 0x2f);
    sunxi_lcd_cpu_write_index(0, 0xbb);
    sunxi_lcd_cpu_write_data(0, 0x20);
    sunxi_lcd_cpu_write_index(0, 0xc0);
    sunxi_lcd_cpu_write_data(0, 0x2c);
    sunxi_lcd_cpu_write_index(0, 0xc2);
    sunxi_lcd_cpu_write_data(0, 0x01);
    sunxi_lcd_cpu_write_index(0, 0xc3);
    sunxi_lcd_cpu_write_data(0, 0x0b);
    sunxi_lcd_cpu_write_index(0, 0xc4);
    sunxi_lcd_cpu_write_data(0, 0x20);
    sunxi_lcd_cpu_write_index(0, 0xc6);
    sunxi_lcd_cpu_write_data(0, 0x11);
    sunxi_lcd_cpu_write_index(0, 0xd0);
    sunxi_lcd_cpu_write_data(0, 0xa4);
    sunxi_lcd_cpu_write_data(0, 0xa1);
    sunxi_lcd_cpu_write_index(0, 0xe8);
    sunxi_lcd_cpu_write_data(0, 0x03);
    sunxi_lcd_cpu_write_index(0, 0xe9);
    sunxi_lcd_cpu_write_data(0, 0x0d);
    sunxi_lcd_cpu_write_data(0, 0x12);
    sunxi_lcd_cpu_write_data(0, 0x00);
    /*ST7789V gamma setting */
    sunxi_lcd_cpu_write_index(0, 0xe0);
    sunxi_lcd_cpu_write_data(0, 0xd0);
    sunxi_lcd_cpu_write_data(0, 0x06);
    sunxi_lcd_cpu_write_data(0, 0x0b);
    sunxi_lcd_cpu_write_data(0, 0x0a);
    sunxi_lcd_cpu_write_data(0, 0x09);
    sunxi_lcd_cpu_write_data(0, 0x05);
    sunxi_lcd_cpu_write_data(0, 0x2e);
    sunxi_lcd_cpu_write_data(0, 0x43);
    sunxi_lcd_cpu_write_data(0, 0x44);
    sunxi_lcd_cpu_write_data(0, 0x09);
    sunxi_lcd_cpu_write_data(0, 0x16);
    sunxi_lcd_cpu_write_data(0, 0x15);
    sunxi_lcd_cpu_write_data(0, 0x23);
    sunxi_lcd_cpu_write_data(0, 0x27);
    sunxi_lcd_cpu_write_index(0, 0xe1);
    sunxi_lcd_cpu_write_data(0, 0xd0);
    sunxi_lcd_cpu_write_data(0, 0x06);
    sunxi_lcd_cpu_write_data(0, 0x0b);
    sunxi_lcd_cpu_write_data(0, 0x09);
    sunxi_lcd_cpu_write_data(0, 0x08);
    sunxi_lcd_cpu_write_data(0, 0x06);
    sunxi_lcd_cpu_write_data(0, 0x2e);
    sunxi_lcd_cpu_write_data(0, 0x44);
    sunxi_lcd_cpu_write_data(0, 0x44);
    sunxi_lcd_cpu_write_data(0, 0x3a);
    sunxi_lcd_cpu_write_data(0, 0x15);
    sunxi_lcd_cpu_write_data(0, 0x15);
    sunxi_lcd_cpu_write_data(0, 0x23);
    sunxi_lcd_cpu_write_data(0, 0x26);

#if defined(CPU_TRI_MODE)
    /* enable te, mode 0 */

    sunxi_lcd_cpu_write_index(0, 0x35);
    sunxi_lcd_cpu_write_data(0, 0x00);

    sunxi_lcd_cpu_write_index(0, 0x44);
    sunxi_lcd_cpu_write_data(0, 0x00);
    sunxi_lcd_cpu_write_data(0, 0x80);
#endif
    sunxi_lcd_cpu_write_index(0, 0x29);
    sunxi_lcd_cpu_write_index(0, 0x2c);

}


/* panel driver name, must mach the name of lcd_drv_name in sys_config.fex */
struct __lcd_panel st7789v_cpu_panel = {
    .name = "st7789v_cpu",
    .func = {
        .cfg_panel_info = LCD_cfg_panel_info,
        .cfg_open_flow = LCD_open_flow,
        .cfg_close_flow = LCD_close_flow,
    },
};
