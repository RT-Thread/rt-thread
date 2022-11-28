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
*/
#include "he0801a068.h"

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
        u32 num = lcd_gamma_tbl[i+1][0] - lcd_gamma_tbl[i][0];

        for (j = 0; j < num; j++) {
            u32 value = 0;

            value = lcd_gamma_tbl[i][1] +
                ((lcd_gamma_tbl[i+1][1] - lcd_gamma_tbl[i][1])
                * j) / num;
            info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] =
                            (value<<16)
                            + (value<<8) + value;
        }
    }
    info->lcd_gamma_tbl[255] = (lcd_gamma_tbl[items-1][1]<<16) +
                    (lcd_gamma_tbl[items-1][1]<<8)
                    + lcd_gamma_tbl[items-1][1];

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
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_power_enable(sel, 1);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_pin_cfg(sel, 1);
    sunxi_lcd_delay_ms(50);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(100);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(100);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(100);

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
    sunxi_lcd_delay_ms(10);
    /*========== Internal setting ==========*/
    sunxi_lcd_dsi_dcs_write_4para(sel, 0xFF, 0xAA, 0x55, 0xA5, 0x80);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0x6F, 0x11, 0x00);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xF7, 0x20, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xF7, 0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x19);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xF7, 0x12);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xF4, 0x03);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x08);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xFA, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x11);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xF3, 0x01);
    /*========== page0 relative ==========*/
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xC8, 0x80);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB1, 0x6C, 0x07);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB6, 0x08);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB8, 0x08);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBB, 0x74, 0x44);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBC, 0x00, 0x00);

    sunxi_lcd_dsi_dcs_write_5para(sel, 0xBD, 0x02, 0xB0, 0x0C, 0x0A, 0x00);

    /*========== page1 relative ==========*/
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB0, 0x05, 0x05);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB1, 0x05, 0x05);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBC, 0x90, 0x01);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBD, 0x90, 0x01);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xCA, 0x00);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xC0, 0x04);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xBE, 0x29);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB3, 0x37, 0x37);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB4, 0x19, 0x19);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB9, 0x44, 0x44);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBA, 0x24, 0x24);
    /*========== page2 relative ==========*/
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x02);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xEE, 0x01);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0xEF, 0x09, 0x06, 0x15, 0x18);

    sunxi_lcd_dsi_dcs_write_6para(sel, 0xB0, 0x00, 0x00, 0x00, 0x25, 0x00,
                      0x43);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x06);
    sunxi_lcd_dsi_dcs_write_6para(sel, 0xB0, 0x00, 0x54, 0x00, 0x68, 0x00,
                      0xA0);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x0C);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0xB0, 0x00, 0xC0, 0x01, 0x00);
    sunxi_lcd_dsi_dcs_write_6para(sel, 0xB1, 0x01, 0x30, 0x01, 0x78, 0x01,
                      0xAE);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x06);
    sunxi_lcd_dsi_dcs_write_6para(sel, 0xB1, 0x02, 0x08, 0x02, 0x52, 0x02,
                      0x54);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x0C);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0xB1, 0x02, 0x99, 0x02, 0xF0);
    sunxi_lcd_dsi_dcs_write_6para(sel, 0xB2, 0x03, 0x20, 0x03, 0x56, 0x03,
                      0x76);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x06);
    sunxi_lcd_dsi_dcs_write_6para(sel, 0xB2, 0x03, 0x93, 0x03, 0xA4, 0x03,
                      0xB9);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x0C);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0xB2, 0x03, 0xC9, 0x03, 0xE3);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0xB3, 0x03, 0xFC, 0x03, 0xFF);

    /*========== GOA relative ==========*/
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x06);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB0, 0x00, 0x10);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB1, 0x12, 0x14);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB2, 0x16, 0x18);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB3, 0x1A, 0x29);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB4, 0x2A, 0x08);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB5, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB6, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB7, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB8, 0x31, 0x0A);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB9, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBA, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBB, 0x0B, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBC, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBD, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBE, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xBF, 0x09, 0x2A);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC0, 0x29, 0x1B);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC1, 0x19, 0x17);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC2, 0x15, 0x13);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC3, 0x11, 0x01);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xE5, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC4, 0x09, 0x1B);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC5, 0x19, 0x17);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC6, 0x15, 0x13);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC7, 0x11, 0x29);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC8, 0x2A, 0x01);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC9, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xCA, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xCB, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xCC, 0x31, 0x0B);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xCD, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xCE, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xCF, 0x0A, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD0, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD1, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD2, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD3, 0x00, 0x2A);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD4, 0x29, 0x10);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD5, 0x12, 0x14);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD6, 0x16, 0x18);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xD7, 0x1A, 0x08);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xE6, 0x31, 0x31);
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xD8, 0x00, 0x00, 0x00, 0x54, 0x00);
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xD9, 0x00, 0x15, 0x00, 0x00, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE7, 0x00);
    /*PAGE3 :*/
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x03);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB0, 0x20, 0x00);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB1, 0x20, 0x00);
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xB2, 0x05, 0x00, 0x00, 0x00, 0x00);

    sunxi_lcd_dsi_dcs_write_5para(sel, 0xB6, 0x05, 0x00, 0x00, 0x00, 0x00);
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xB7, 0x05, 0x00, 0x00, 0x00, 0x00);

    sunxi_lcd_dsi_dcs_write_5para(sel, 0xBA, 0x57, 0x00, 0x00, 0x00, 0x00);
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xBB, 0x57, 0x00, 0x00, 0x00, 0x00);

    sunxi_lcd_dsi_dcs_write_4para(sel, 0xC0, 0x00, 0x00, 0x00, 0x00);
    sunxi_lcd_dsi_dcs_write_4para(sel, 0xC1, 0x00, 0x00, 0x00, 0x00);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xC4, 0x60);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xC5, 0x40);
    /*PAGE5 :*/
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x05);
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xBD, 0x03, 0x01, 0x03, 0x03, 0x03);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB0, 0x17, 0x06);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB1, 0x17, 0x06);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB2, 0x17, 0x06);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB3, 0x17, 0x06);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB4, 0x17, 0x06);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xB5, 0x17, 0x06);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB8, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xB9, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xBA, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xBB, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xBC, 0x00);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xC0, 0x07);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xC4, 0x80);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xC5, 0xA4);

    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC8, 0x05, 0x30);
    sunxi_lcd_dsi_dcs_write_2para(sel, 0xC9, 0x01, 0x31);

    sunxi_lcd_dsi_dcs_write_3para(sel, 0xCC, 0x00, 0x00, 0x3C);
    sunxi_lcd_dsi_dcs_write_3para(sel, 0xCD, 0x00, 0x00, 0x3C);

    sunxi_lcd_dsi_dcs_write_5para(sel, 0xD1, 0x00, 0x04, 0xFD, 0x07, 0x10);
    sunxi_lcd_dsi_dcs_write_5para(sel, 0xD2, 0x00, 0x05, 0x02, 0x07, 0x10);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE5, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE6, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE7, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE8, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE9, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xEA, 0x06);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0xED, 0x30);

    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x11);
    /*reload setting*/
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xF3, 0x01);

    sunxi_lcd_dsi_dcs_write_0para(sel, 0x35);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x11);
    sunxi_lcd_delay_ms(80);
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x29);
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

struct __lcd_panel he0801a068_panel = {
    /* panel driver name, must mach the name of
     * lcd_drv_name in sys_config.fex
     */
    .name = "he0801a068",
    .func = {
        .cfg_panel_info = lcd_cfg_panel_info,
            .cfg_open_flow = lcd_open_flow,
            .cfg_close_flow = lcd_close_flow,
            .lcd_user_defined_func = lcd_user_defined_func,
    },
};
