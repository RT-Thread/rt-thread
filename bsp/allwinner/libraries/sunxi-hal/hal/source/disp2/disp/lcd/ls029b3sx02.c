/* drivers/video/sunxi/disp2/disp/lcd/ls029b3sx02.c
 *
 * Copyright (c) 2017 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * ls029b3sx02 panel driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#include "ls029b3sx02.h"

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
    /* set func to lcdp->openflow.func
     * set delay time to lcdp->openflow.delay*/
    LCD_OPEN_FUNC(sel, lcd_power_on, 10);
    LCD_OPEN_FUNC(sel, lcd_panel_init, 200);
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
    /*[VDDI]-->[AVDD+]-->[AVDD]-->[rst h]
     * -->[rst l]-->[rst h]*/
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_power_enable(sel, 1);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_power_enable(sel, 2);
    sunxi_lcd_delay_ms(10);
    sunxi_lcd_pin_cfg(sel, 1);
    sunxi_lcd_delay_ms(50);
    sunxi_lcd_gpio_set_value(sel, 1, 1);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(10);
    panel_reset(sel, 0);
    sunxi_lcd_delay_ms(10);
    panel_reset(sel, 1);
    sunxi_lcd_delay_ms(20);
}

static void lcd_power_off(u32 sel)
{
    /*[AVEE-]-->[AVDD+]-->[rst l]-->[VDDI]*/
    sunxi_lcd_pin_cfg(sel, 0);
    sunxi_lcd_delay_ms(20);
    sunxi_lcd_power_disable(sel, 2);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_disable(sel, 1);
    sunxi_lcd_delay_ms(5);
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
    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(100);
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_EXIT_SLEEP_MODE);
    sunxi_lcd_delay_ms(200);
    sunxi_lcd_tcon_enable(sel); /*tcon and dsi enable,start send data*/
    sunxi_lcd_delay_ms(400); /*FIXME modify this value*/
    sunxi_lcd_dsi_mode_switch(sel, 1, 1); /*close dsi,enable cmd mode*/
    sunxi_lcd_delay_ms(100);
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_SET_DISPLAY_ON);
    sunxi_lcd_delay_ms(200);
    sunxi_lcd_dsi_mode_switch(sel, 0, 1); /*enable video mode*/
    return;
}

static void lcd_panel_exit(u32 sel)
{
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_SET_DISPLAY_OFF);
    sunxi_lcd_delay_ms(50);
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_ENTER_SLEEP_MODE);
    sunxi_lcd_delay_ms(80);
    return;
}

/*sel: 0:lcd0; 1:lcd1*/
static s32 lcd_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

/*
static s32 LCD_set_bright(u32 sel, u32 bright)
{
    return 0;
}
*/

struct __lcd_panel ls029b3sx02_panel = {
    /* panel driver name, must mach the name of lcd_drv_name
     * in sys_config.fex */
    .name = "ls029b3sx02",
    .func = {
        .cfg_panel_info = lcd_cfg_panel_info,
        .cfg_open_flow = lcd_open_flow,
        .cfg_close_flow = lcd_close_flow,
         .lcd_user_defined_func = lcd_user_defined_func,
        /* .set_bright = LCD_set_bright,*/
    },
};
