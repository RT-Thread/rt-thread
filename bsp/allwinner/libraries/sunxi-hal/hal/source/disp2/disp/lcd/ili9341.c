/*
 * drivers/video/fbdev/sunxi/disp2/disp/lcd/ili9341/ili9341.c
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

[lcd0]
lcd_used            = 1

lcd_driver_name     = "ili9341"
lcd_x               = 240
lcd_y               = 320
lcd_width           = 108
lcd_height          = 64
lcd_dclk_freq       = 60

lcd_pwm_used        = 0
lcd_pwm_ch          = 0
lcd_pwm_freq        = 50000
lcd_pwm_pol         = 1
lcd_pwm_max_limit   = 255

lcd_hbp             = 20
;10 + 20 + 10 + 240*3 = 760  real set 1000
lcd_ht              = 1000
lcd_hspw            = 10
lcd_vbp             = 5
lcd_vt              = 340
lcd_vspw            = 2

lcd_frm             = 0
lcd_if              = 0
lcd_hv_if   = 8
lcd_hv_clk_phase    = 0
lcd_hv_sync_polarity   = 0
lcd_hv_srgb_seq     = 0

lcd_io_phase        = 0x0000
lcd_gamma_en        = 0
lcd_bright_curve_en = 1
lcd_cmap_en         = 0


lcd_rb_swap = 0

deu_mode            = 0
lcdgamma4iep        = 22
smart_color         = 90

lcd_bl_en           = port:PB07<1><0><default><1>
lcd_power           = "axp233_dc1sw"

;reset
lcd_gpio_0          = port:PB06<1><0><default><1>
;cs
lcd_gpio_1          = port:PD22<1><0><default><0>
;sda
lcd_gpio_2          = port:PH08<1><0><default><0>
;sck
lcd_gpio_3          = port:PH07<1><0><default><0>


lcdd3                = port:PD01<2><0><2><default>
lcdd4                = port:PD02<2><0><2><default>
lcdd5                = port:PD03<2><0><2><default>
lcdd6                = port:PD04<2><0><2><default>
lcdd7                = port:PD05<2><0><2><default>
lcdd10               = port:PD06<2><0><2><default>
lcdd11               = port:PD07<2><0><2><default>
lcdd12               = port:PD08<2><0><2><default>

lcdclk              = port:PD18<2><0><3><default>
lcdde               = port:PD19<2><0><3><default>
lcdhsync            = port:PD20<2><0><3><default>
lcdvsync            = port:PD21<2><0><3><default>
[lcd0_suspend]
lcdd3                = port:PD01<7><0><2><default>
lcdd4                = port:PD02<7><0><2><default>
lcdd5                = port:PD03<7><0><2><default>
lcdd6                = port:PD04<7><0><2><default>
lcdd7                = port:PD05<7><0><2><default>
lcdd10               = port:PD06<7><0><2><default>
lcdd11               = port:PD07<7><0><2><default>
lcdd12               = port:PD08<7><0><2><default>

lcdclk              = port:PD18<7><0><3><default>
lcdde               = port:PD19<7><0><3><default>
lcdhsync            = port:PD20<7><0><3><default>
lcdvsync            = port:PD21<7><0><3><default>
 *
 */
#include "ili9341.h"

#define CPU_TRI_MODE

#define ili9341c_spi_scl_1 sunxi_lcd_gpio_set_value(0, 3, 1)
#define ili9341c_spi_scl_0 sunxi_lcd_gpio_set_value(0, 3, 0)
#define ili9341c_spi_sdi_1 sunxi_lcd_gpio_set_value(0, 2, 1)
#define ili9341c_spi_sdi_0 sunxi_lcd_gpio_set_value(0, 2, 0)
#define ili9341c_spi_cs_1 sunxi_lcd_gpio_set_value(0, 1, 1)
#define ili9341c_spi_cs_0 sunxi_lcd_gpio_set_value(0, 1, 0)

#define ili9341c_spi_reset_1 sunxi_lcd_gpio_set_value(0, 0, 1)
#define ili9341c_spi_reset_0 sunxi_lcd_gpio_set_value(0, 0, 0)

static void lcd_panel_ili9341_init(struct disp_panel_para *info);

static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

extern s32 tcon0_cpu_set_tri_mode(u32 sel);

void write_tcon_register(int offset, int value)
{
    volatile int *tcon_reg = (int *)(0xf1c0c000 + offset);
    int reg = 0;

    reg = *((volatile int *)tcon_reg);
    reg |= value;
    *((volatile int *)tcon_reg) = reg;
}

static void lcd_cfg_panel_info(struct panel_extend_para *info)
{
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
}

static s32 lcd_open_flow(u32 sel)
{
    LCD_OPEN_FUNC(sel, LCD_power_on, 40);
#ifdef CPU_TRI_MODE
    LCD_OPEN_FUNC(sel, LCD_panel_init, 50);
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 50);
#else
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 50);
    LCD_OPEN_FUNC(sel, LCD_panel_init, 50);
#endif
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);

    return 0;
}

static s32 lcd_close_flow(u32 sel)
{
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 50);
#ifdef CPU_TRI_MODE
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 10);
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 10);
#else
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 10);
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 10);
#endif
    LCD_CLOSE_FUNC(sel, LCD_power_off, 10);

    return 0;
}

static void LCD_power_on(u32 sel)
{
    /*config lcd_power pin to open lcd power0*/
    sunxi_lcd_power_enable(sel, 0);
    /*pwr_en, active low*/
    sunxi_lcd_gpio_set_value(sel, 3, 0);
    sunxi_lcd_pin_cfg(sel, 1);
}

static void LCD_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    /*pwr_en, active low*/
    sunxi_lcd_gpio_set_value(sel, 3, 1);
    /*config lcd_power pin to close lcd power0*/
    sunxi_lcd_power_disable(sel, 0);
}

static void LCD_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
    /*config lcd_bl_en pin to open lcd backlight*/
    sunxi_lcd_backlight_enable(sel);
}

static void LCD_bl_close(u32 sel)
{
    /*config lcd_bl_en pin to close lcd backlight*/
    sunxi_lcd_backlight_disable(sel);
    sunxi_lcd_pwm_disable(sel);
}

static void LCD_WRITE_DATA(u32 value)
{
    u32 i;
    ili9341c_spi_cs_0;
    ili9341c_spi_sdi_1;
    ili9341c_spi_scl_0;
    sunxi_lcd_delay_us(10);
    ili9341c_spi_scl_1;
    for (i = 0; i < 8; i++) {
        sunxi_lcd_delay_us(10);
        if (value & 0x80)
            ili9341c_spi_sdi_1;
        else
            ili9341c_spi_sdi_0;
        value <<= 1;
        sunxi_lcd_delay_us(10);
        ili9341c_spi_scl_0;
        ili9341c_spi_scl_1;
    }
    sunxi_lcd_delay_us(10);
    ili9341c_spi_cs_1;
}

static void LCD_WRITE_COMMAND(u32 value)
{
    u32 i;
    ili9341c_spi_cs_0;
    ili9341c_spi_sdi_0;
    ili9341c_spi_scl_0;
    sunxi_lcd_delay_us(10);
    ili9341c_spi_scl_1;
    for (i = 0; i < 8; i++) {
        sunxi_lcd_delay_us(10);
        if (value & 0x80)
            ili9341c_spi_sdi_1;
        else
            ili9341c_spi_sdi_0;
        ili9341c_spi_scl_0;
        sunxi_lcd_delay_us(10);
        ili9341c_spi_scl_1;
        value <<= 1;
    }
    sunxi_lcd_delay_us(10);
    ili9341c_spi_cs_1;
}

static void LCD_panel_init(u32 sel)
{
    struct disp_panel_para *info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL | __GFP_ZERO);

    bsp_disp_get_panel_info(sel, info);
    lcd_panel_ili9341_init(info);
    disp_sys_free(info);
    return;
}

static void LCD_panel_exit(u32 sel)
{
    struct disp_panel_para *info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL | __GFP_ZERO);

    LCD_WRITE_COMMAND(0x28);
    LCD_WRITE_COMMAND(0x10);
    sunxi_lcd_delay_ms(300);
    bsp_disp_get_panel_info(sel, info);
    disp_sys_free(info);
    return;
}

static void lcd_panel_ili9341_init(struct disp_panel_para *info)
{
    //************* Start Initial Sequence **********//
    //************* Reset LCD Driver ****************//
    ili9341c_spi_reset_1;
    sunxi_lcd_delay_ms(1);
    ili9341c_spi_reset_0;
    /*Delay 10ms  This delay time is necessary*/
    sunxi_lcd_delay_ms(10);
    ili9341c_spi_reset_1;
    /*Delay 120 ms*/
    sunxi_lcd_delay_ms(120);
    /************** Start Initial Sequence ***********/
    /*Pixel Format Set*/
    LCD_WRITE_COMMAND(0x3A);
    LCD_WRITE_DATA(0x55);
    LCD_WRITE_COMMAND(0xF6);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_DATA(0x33);
    LCD_WRITE_COMMAND(0xB5);
    LCD_WRITE_DATA(0x04);
    LCD_WRITE_DATA(0x04);
    LCD_WRITE_DATA(0x0A);
    LCD_WRITE_DATA(0x14);
    LCD_WRITE_COMMAND(0x35);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_COMMAND(0xCF);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0xEA);
    LCD_WRITE_DATA(0xF0);
    LCD_WRITE_COMMAND(0xED);
    LCD_WRITE_DATA(0x64);
    LCD_WRITE_DATA(0x03);
    LCD_WRITE_DATA(0x12);
    LCD_WRITE_DATA(0x81);
    LCD_WRITE_COMMAND(0xE8);
    LCD_WRITE_DATA(0x85);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x78);
    LCD_WRITE_COMMAND(0xCB);
    LCD_WRITE_DATA(0x39);
    LCD_WRITE_DATA(0x2C);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x33);
    LCD_WRITE_DATA(0x06);
    LCD_WRITE_COMMAND(0xF7);
    LCD_WRITE_DATA(0x20);
    LCD_WRITE_COMMAND(0xEA);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    /*VRH[5:0]*/
    LCD_WRITE_COMMAND(0xC0);
    LCD_WRITE_DATA(0x21);
    LCD_WRITE_COMMAND(0xC1);
    LCD_WRITE_DATA(0x10);
    LCD_WRITE_COMMAND(0xC5);
    LCD_WRITE_DATA(0x31);
    LCD_WRITE_DATA(0x3C);
    LCD_WRITE_COMMAND(0x36);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_COMMAND(0xB0);
    /*E0,E9£¬D3£¬40*/
    LCD_WRITE_DATA(0xE9);
    LCD_WRITE_COMMAND(0xB1);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x13);
    LCD_WRITE_COMMAND(0xB6);
    LCD_WRITE_DATA(0x0A);
    LCD_WRITE_DATA(0xA2);
    LCD_WRITE_COMMAND(0xF2);
    LCD_WRITE_DATA(0x02);
    LCD_WRITE_COMMAND(0xF6);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_DATA(0x30);
    LCD_WRITE_DATA(0x07);
    LCD_WRITE_COMMAND(0x26);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_COMMAND(0xE0);
    LCD_WRITE_DATA(0x0F);
    LCD_WRITE_DATA(0x30);
    LCD_WRITE_DATA(0x24);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_DATA(0x07);
    LCD_WRITE_DATA(0x03);
    LCD_WRITE_DATA(0x51);
    LCD_WRITE_DATA(0x50);
    LCD_WRITE_DATA(0x45);
    LCD_WRITE_DATA(0x0a);
    LCD_WRITE_DATA(0x15);
    LCD_WRITE_DATA(0x04);
    LCD_WRITE_DATA(0x10);
    LCD_WRITE_DATA(0x40);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_COMMAND(0xE1);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x15);
    LCD_WRITE_DATA(0x0a);
    LCD_WRITE_DATA(0x12);
    LCD_WRITE_DATA(0x07);
    LCD_WRITE_DATA(0x13);
    LCD_WRITE_DATA(0x21);
    LCD_WRITE_DATA(0x22);
    LCD_WRITE_DATA(0x38);
    LCD_WRITE_DATA(0x32);
    LCD_WRITE_DATA(0x06);
    LCD_WRITE_DATA(0x03);
    LCD_WRITE_DATA(0x20);
    LCD_WRITE_DATA(0x2c);
    LCD_WRITE_DATA(0x34);
    LCD_WRITE_COMMAND(0x36);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_COMMAND(0x11);
    sunxi_lcd_delay_ms(120);
    LCD_WRITE_COMMAND(0x29);
    /*Display on*/
    LCD_WRITE_COMMAND(0x2C);
}

void lcd_reflush(void)
{
    /************** Start Initial Sequence ***********/
    /************** Reset LCD Driver *****************/
    ili9341c_spi_reset_1;
    sunxi_lcd_delay_ms(1);
    ili9341c_spi_reset_0;
    /*Delay 10ms  This delay time is necessary*/
    sunxi_lcd_delay_ms(10);
    ili9341c_spi_reset_1;
    /*Delay 120 ms*/
    sunxi_lcd_delay_ms(120);
    /************** Start Initial Sequence ***********/
    /*Pixel Format Set*/
    LCD_WRITE_COMMAND(0x3A);
    LCD_WRITE_DATA(0x55);
    LCD_WRITE_COMMAND(0xF6);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_DATA(0x33);
    LCD_WRITE_COMMAND(0xB5);
    LCD_WRITE_DATA(0x04);
    LCD_WRITE_DATA(0x04);
    LCD_WRITE_DATA(0x0A);
    LCD_WRITE_DATA(0x14);
    LCD_WRITE_COMMAND(0x35);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_COMMAND(0xCF);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0xEA);
    LCD_WRITE_DATA(0xF0);
    LCD_WRITE_COMMAND(0xED);
    LCD_WRITE_DATA(0x64);
    LCD_WRITE_DATA(0x03);
    LCD_WRITE_DATA(0x12);
    LCD_WRITE_DATA(0x81);
    LCD_WRITE_COMMAND(0xE8);
    LCD_WRITE_DATA(0x85);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x78);
    LCD_WRITE_COMMAND(0xCB);
    LCD_WRITE_DATA(0x39);
    LCD_WRITE_DATA(0x2C);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x33);
    LCD_WRITE_DATA(0x06);
    LCD_WRITE_COMMAND(0xF7);
    LCD_WRITE_DATA(0x20);
    LCD_WRITE_COMMAND(0xEA);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    /*VRH[5:0]*/
    LCD_WRITE_COMMAND(0xC0);
    LCD_WRITE_DATA(0x21);
    LCD_WRITE_COMMAND(0xC1);
    LCD_WRITE_DATA(0x10);
    LCD_WRITE_COMMAND(0xC5);
    LCD_WRITE_DATA(0x4F);
    LCD_WRITE_DATA(0x38);
    LCD_WRITE_COMMAND(0x36);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_COMMAND(0xB0);
    LCD_WRITE_DATA(0xE9);
    LCD_WRITE_COMMAND(0xB1);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x13);
    LCD_WRITE_COMMAND(0xB6);
    LCD_WRITE_DATA(0x0A);
    LCD_WRITE_DATA(0xA2);
    LCD_WRITE_COMMAND(0xF2);
    LCD_WRITE_DATA(0x02);
    LCD_WRITE_COMMAND(0xF6);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_DATA(0x30);
    LCD_WRITE_DATA(0x07);
    LCD_WRITE_COMMAND(0x26);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_COMMAND(0xE0);
    LCD_WRITE_DATA(0x0F);
    LCD_WRITE_DATA(0x30);
    LCD_WRITE_DATA(0x24);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_DATA(0x07);
    LCD_WRITE_DATA(0x03);
    LCD_WRITE_DATA(0x51);
    LCD_WRITE_DATA(0x50);
    LCD_WRITE_DATA(0x45);
    LCD_WRITE_DATA(0x0a);
    LCD_WRITE_DATA(0x15);
    LCD_WRITE_DATA(0x04);
    LCD_WRITE_DATA(0x10);
    LCD_WRITE_DATA(0x40);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_COMMAND(0xE1);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x15);
    LCD_WRITE_DATA(0x0a);
    LCD_WRITE_DATA(0x12);
    LCD_WRITE_DATA(0x07);
    LCD_WRITE_DATA(0x13);
    LCD_WRITE_DATA(0x21);
    LCD_WRITE_DATA(0x22);
    LCD_WRITE_DATA(0x38);
    LCD_WRITE_DATA(0x32);
    LCD_WRITE_DATA(0x06);
    LCD_WRITE_DATA(0x03);
    LCD_WRITE_DATA(0x20);
    LCD_WRITE_DATA(0x2c);
    LCD_WRITE_DATA(0x34);
    LCD_WRITE_COMMAND(0x36);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_COMMAND(0x11);
    sunxi_lcd_delay_ms(120);
    LCD_WRITE_COMMAND(0x29);
    /*Display on*/
    LCD_WRITE_COMMAND(0x2C);
}

static s32 lcd_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel ili9341_panel = {
    /* panel driver name, must mach the name of lcd_drv_name in sys_config.fex
       */
    .name = "ili9341",
    .func = {
        .cfg_panel_info = lcd_cfg_panel_info,
        .cfg_open_flow = lcd_open_flow,
        .cfg_close_flow = lcd_close_flow,
        .lcd_user_defined_func = lcd_user_defined_func,
        },
};
