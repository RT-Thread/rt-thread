/*
 * drivers/video/fbdev/sunxi/disp2/disp/lcd/st7789v/st7789v.c
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
[lcd0]
lcd_used            = 1

lcd_driver_name     = "st7789v"
lcd_x               = 240
lcd_y               = 320
lcd_width           = 108
lcd_height          = 64
lcd_dclk_freq       = 19

lcd_pwm_used        = 1
lcd_pwm_ch          = 8
lcd_pwm_freq        = 50000
lcd_pwm_pol         = 0
lcd_pwm_max_limit   = 255

lcd_hbp             = 120
;10 + 20 + 10 + 240*3 = 760  real set 1000
lcd_ht              = 850
lcd_hspw            = 2
lcd_vbp             = 13
lcd_vt              = 373
lcd_vspw            = 2

lcd_frm             = 1
lcd_if              = 0
lcd_hv_if           = 8
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

;lcd_bl_en           = port:PB03<1><0><default><1>
lcd_power           = "vcc-lcd"
lcd_pin_power           = "vcc-pd"

;reset
lcd_gpio_0          = port:PD09<1><0><default><1>
;cs
lcd_gpio_1          = port:PD10<1><0><default><0>
;sda
lcd_gpio_2          = port:PD13<1><0><default><0>
;sck
lcd_gpio_3          = port:PD12<1><0><default><0>


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
 */
#include "st7789v.h"

#define spi_scl_1 sunxi_lcd_gpio_set_value(0, 3, 1)
#define spi_scl_0 sunxi_lcd_gpio_set_value(0, 3, 0)
#define spi_sdi_1 sunxi_lcd_gpio_set_value(0, 2, 1)
#define spi_sdi_0 sunxi_lcd_gpio_set_value(0, 2, 0)
#define spi_cs_1 sunxi_lcd_gpio_set_value(0, 1, 1)
#define spi_cs_0 sunxi_lcd_gpio_set_value(0, 1, 0)

static void lcd_panel_st7789v_init(void);
static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

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
    LCD_OPEN_FUNC(sel, LCD_power_on, 200);
    /* open lcd power, than delay 200ms */
    LCD_OPEN_FUNC(sel, LCD_panel_init, 200);
    /* open lcd controller, and delay 100ms */
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 150);
    /* open lcd backlight, and delay 0ms */
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    /* close lcd backlight, and delay 0ms */
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 50);
    /* close lcd controller, and delay 0ms */
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 10);
    /* open lcd power, than delay 200ms */
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 10);
    /* close lcd power, and delay 500ms */
    LCD_CLOSE_FUNC(sel, LCD_power_off, 10);

    return 0;
}

static void LCD_power_on(u32 sel)
{
    /* config lcd_power pin to open lcd power0 */
    sunxi_lcd_power_enable(sel, 0);
    /* pwr_en, active low */
    sunxi_lcd_gpio_set_value(sel, 3, 0);
    sunxi_lcd_pin_cfg(sel, 1);
}

static void LCD_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    /* pwr_en, active low */
    sunxi_lcd_gpio_set_value(sel, 3, 1);
    /* config lcd_power pin to close lcd power0 */
    sunxi_lcd_power_disable(sel, 0);
}

static void LCD_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
    /* config lcd_bl_en pin to open lcd backlight */
    sunxi_lcd_backlight_enable(sel);
}

static void LCD_bl_close(u32 sel)
{
    /* config lcd_bl_en pin to close lcd backlight */
    sunxi_lcd_backlight_disable(sel);
    sunxi_lcd_pwm_disable(sel);
}

static void st7789v_spi_write_cmd(u8 value)
{
    int i;

    spi_cs_0;
    spi_scl_0;

    spi_sdi_0;
    spi_scl_1;
    spi_scl_0;

    for (i = 0; i < 8; i++) {
        if (value & 0x80)
            spi_sdi_1;
        else
            spi_sdi_0;
        value <<= 1;

        spi_scl_1;
        spi_scl_0;
    }
    spi_cs_1;
}

static void st7789v_spi_write_data(u8 value)
{
    int i;

    spi_cs_0;
    spi_scl_0;

    spi_sdi_1;
    spi_scl_1;
    spi_scl_0;

    for (i = 0; i < 8; i++) {
        if (value & 0x80)
            spi_sdi_1;
        else
            spi_sdi_0;
        value <<= 1;

        spi_scl_1;
        spi_scl_0;
    }
    spi_cs_1;
}

static void LCD_panel_init(u32 sel)
{
    struct disp_panel_para *info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL | __GFP_ZERO);
    bsp_disp_get_panel_info(sel, info);
    lcd_panel_st7789v_init();
    disp_sys_free(info);
    return;
}

static void LCD_panel_exit(u32 sel)
{
    struct disp_panel_para *info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL | __GFP_ZERO);
    st7789v_spi_write_cmd(0x28);
    st7789v_spi_write_cmd(0x10);
    sunxi_lcd_delay_ms(300);
    bsp_disp_get_panel_info(sel, info);
    disp_sys_free(info);
    return;
}

static void lcd_panel_st7789v_init(void)
{
    /* VCI=3.3V */
    /************* Reset LCD Driver ****************/
    spi_cs_0;
    sunxi_lcd_gpio_set_value(0, 0, 1);
    sunxi_lcd_delay_ms(50);
    sunxi_lcd_gpio_set_value(0, 0, 0);
    /* Delay 10ms, This delay time is necessary */
    sunxi_lcd_delay_ms(100);
    sunxi_lcd_gpio_set_value(0, 0, 1);
    /* Delay 120 ms */
    sunxi_lcd_delay_ms(150);

    st7789v_spi_write_cmd(0x01);
    sunxi_lcd_delay_ms(50);
    st7789v_spi_write_cmd(0x11);
    sunxi_lcd_delay_ms(120);

    st7789v_spi_write_cmd(0x36);
    st7789v_spi_write_data(0xd4);
    st7789v_spi_write_cmd(0x3a);
    st7789v_spi_write_data(0x06);
    st7789v_spi_write_cmd(0x20);

    st7789v_spi_write_cmd(0xb0);
    st7789v_spi_write_data(0x11);
    st7789v_spi_write_data(0xe4);

    st7789v_spi_write_cmd(0xb1);
    st7789v_spi_write_data(0xc0);
    st7789v_spi_write_data(0x02);
    st7789v_spi_write_data(0x04);

    st7789v_spi_write_cmd(0xb7);
    st7789v_spi_write_data(0x35);
    st7789v_spi_write_cmd(0xbb);
    st7789v_spi_write_data(0x20);
    st7789v_spi_write_cmd(0xC0);
    st7789v_spi_write_data(0x21);

    st7789v_spi_write_cmd(0xC2);
    /* VDV and VRH Command Enable */
    st7789v_spi_write_data(0x01);

    st7789v_spi_write_cmd(0xC3);
    st7789v_spi_write_data(0x0b);

    st7789v_spi_write_cmd(0xC4);
    st7789v_spi_write_data(0x20);

    st7789v_spi_write_cmd(0xc6);
    st7789v_spi_write_data(0x0f);

    st7789v_spi_write_cmd(0xd0);
    st7789v_spi_write_data(0xa4);
    st7789v_spi_write_data(0xa1);

    st7789v_spi_write_cmd(0xE0);
    st7789v_spi_write_data(0x0D);
    st7789v_spi_write_data(0x10);
    st7789v_spi_write_data(0x13);
    st7789v_spi_write_data(0x08);
    st7789v_spi_write_data(0x07);
    st7789v_spi_write_data(0x04);
    st7789v_spi_write_data(0x2C);
    st7789v_spi_write_data(0x33);
    st7789v_spi_write_data(0x42);
    st7789v_spi_write_data(0x29);
    st7789v_spi_write_data(0x17);
    st7789v_spi_write_data(0x18);
    st7789v_spi_write_data(0x24);
    st7789v_spi_write_data(0x28);

    st7789v_spi_write_cmd(0xE1);
    st7789v_spi_write_data(0x0D);
    st7789v_spi_write_data(0x10);
    st7789v_spi_write_data(0x12);
    st7789v_spi_write_data(0x08);
    st7789v_spi_write_data(0x07);
    st7789v_spi_write_data(0x03);
    st7789v_spi_write_data(0x2B);
    st7789v_spi_write_data(0x32);
    st7789v_spi_write_data(0x40);
    st7789v_spi_write_data(0x28);
    st7789v_spi_write_data(0x17);
    st7789v_spi_write_data(0x16);
    st7789v_spi_write_data(0x26);
    st7789v_spi_write_data(0x28);

    st7789v_spi_write_cmd(0x2a);
    st7789v_spi_write_data(0x00);
    st7789v_spi_write_data(0x00);
    st7789v_spi_write_data(0x00);
    st7789v_spi_write_data(0xef);

    st7789v_spi_write_cmd(0x2b);
    st7789v_spi_write_data(0x00);
    st7789v_spi_write_data(0x00);
    st7789v_spi_write_data(0x01);
    st7789v_spi_write_data(0x3f);

    /* Exit Sleep */
    st7789v_spi_write_cmd(0x21);
    sunxi_lcd_delay_ms(100);
    st7789v_spi_write_cmd(0x11);
    sunxi_lcd_delay_ms(50);
    st7789v_spi_write_cmd(0x29);
    sunxi_lcd_delay_ms(50);
}

/* sel: 0:lcd0; 1:lcd1 */
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel st7789v_panel = {
    /* panel driver name, must mach the name of lcd_drv_name in sys_config.fex
       */
    .name = "st7789v",
    .func = {
        .cfg_panel_info = LCD_cfg_panel_info,
        .cfg_open_flow = LCD_open_flow,
        .cfg_close_flow = LCD_close_flow,
        .lcd_user_defined_func = LCD_user_defined_func,
        },
};
