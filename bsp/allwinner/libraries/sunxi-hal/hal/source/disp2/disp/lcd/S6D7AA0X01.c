/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "S6D7AA0X01.h"

static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

#define panel_reset(val) sunxi_lcd_gpio_set_value(sel, 1, val)
#define power_en(val)  sunxi_lcd_gpio_set_value(sel, 0, val)

static void LCD_cfg_panel_info(struct panel_extend_para *info)
{
    u32 i = 0, j = 0;
    u32 items;
    u8 lcd_gamma_tbl[][2] = {
        /* {input value, corrected value} */
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
        u32 num = lcd_gamma_tbl[i + 1][0] - lcd_gamma_tbl[i][0];

        for (j = 0; j < num; j++) {
            u32 value = 0;

            value =
                lcd_gamma_tbl[i][1] +
                ((lcd_gamma_tbl[i + 1][1] -
                  lcd_gamma_tbl[i][1]) * j) / num;
            info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] =
                (value << 16) + (value << 8) + value;
        }
    }
    info->lcd_gamma_tbl[255] =
        (lcd_gamma_tbl[items - 1][1] << 16) +
        (lcd_gamma_tbl[items - 1][1] << 8) + lcd_gamma_tbl[items - 1][1];

    memcpy(info->lcd_cmap_tbl, lcd_cmap_tbl, sizeof(lcd_cmap_tbl));

}

static s32 LCD_open_flow(u32 sel)
{
    /* open lcd power, and delay 50ms */
    LCD_OPEN_FUNC(sel, LCD_power_on, 50);
    /* open lcd power, than delay 200ms */
    LCD_OPEN_FUNC(sel, LCD_panel_init, 100);
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
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 200);
    /* close lcd power, and delay 500ms */
    LCD_CLOSE_FUNC(sel, LCD_power_off, 50);

    return 0;
}

static void LCD_power_on(u32 sel)
{
    /* config lcd_power pin to open lcd power */
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_delay_ms(5);
    /* config lcd_power pin to open lcd power1 */
    sunxi_lcd_power_enable(sel, 1);
    sunxi_lcd_delay_ms(5);
    /* config lcd_power pin to open lcd power2 */
    sunxi_lcd_power_enable(sel, 2);
    sunxi_lcd_delay_ms(5);
    power_en(1);
    sunxi_lcd_delay_ms(20);
    panel_reset(1);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_pin_cfg(sel, 1);
    sunxi_lcd_pwm_enable(sel);
}

static void LCD_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    power_en(0);
    sunxi_lcd_delay_ms(20);
    panel_reset(0);
    sunxi_lcd_delay_ms(5);
    /* config lcd_power pin to close lcd power2 */
    sunxi_lcd_power_disable(sel, 2);
    sunxi_lcd_delay_ms(5);
    /* config lcd_power pin to close lcd power1 */
    sunxi_lcd_power_disable(sel, 1);
    sunxi_lcd_delay_ms(5);
    /* config lcd_power pin to close lcd power */
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

static void LCD_panel_init(u32 sel)
{
    panel_reset(1);
    sunxi_lcd_delay_ms(20);
    panel_reset(0);
    sunxi_lcd_delay_ms(30);
    panel_reset(1);
    sunxi_lcd_delay_ms(100);

    /* Page0 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE0, 0x00);

    /* --- PASSWORD  ----// */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE1, 0x93);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE2, 0x65);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE3, 0xF8);

    /* --- Sequence Ctrl  ----// */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x70, 0x10); /* DC0,DC1 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x71, 0x13); /* DC2,DC3 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x72, 0x06); /* DC7 */

    /* --- Page1  ----// */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE0, 0x01);

    /* Set VCOM */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x00, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x01, 0xA0);
    /* Set VCOM_Reverse */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x03, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x04, 0xA0);

    /* Set Gamma Power, VGMP,VGMN,VGSP,VGSN */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x17, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x18, 0xB1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x19, 0x01); /* 0x00 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1A, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1B, 0xB1);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1C, 0x01); /* 0x00 */

    /* Set Gate Power */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1F, 0x3E); /* VGH_R  = 15V */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x20, 0x2D); /* VGL_R  = -12V */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x21, 0x2D); /* VGL_R2 = -12V */
    /* PA[6]=0, PA[5]=0, PA[4]=0, PA[0]=0 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x22, 0x0E);

    /* SETPANEL */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x37, 0x19); /* SS=1,BGR=1 */

    /* SET RGBCYC */
    /* JDT=101 zigzag inversion */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x38, 0x05);
    /* RGB_N_EQ1, modify 20140806 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x39, 0x08);
    /* RGB_N_EQ2, modify 20140806 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3A, 0x12);
    /* SET EQ3 for TE_H */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3C, 0x78);
    /* SET CHGEN_OFF, modify 20140806 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3E, 0x80);
    /* SET CHGEN_OFF2, modify 20140806 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x3F, 0x80);

    /* Set TCON */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x40, 0x06); /* RSO=800 RGB */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x41, 0xA0); /* LN=640->1280 line */

    /* --- power voltage  ----// */
    /* DCDCM=0001, JD PWR_IC */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x55, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x56, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x57, 0x69);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x58, 0x0A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x59, 0x0A); /* VCL = -2.9V */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5A, 0x28); /* VGH = 19V */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5B, 0x19); /* VGL = -11V */

    /* --- Gamma  ----// */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5D, 0x7C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5E, 0x60);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5F, 0x50);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x60, 0x43);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x61, 0x3f);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x62, 0x30);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x63, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x64, 0x1e);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x65, 0x37);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x66, 0x35);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x67, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x68, 0x52);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x69, 0x3f);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6A, 0x44);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6B, 0x35);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6C, 0x2f);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6D, 0x21);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6E, 0x10);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x70, 0x7C);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x71, 0x60);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x72, 0x50);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x73, 0x43);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x74, 0x3f);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x75, 0x30);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x76, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x77, 0x1e);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x78, 0x37);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x79, 0x35);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7A, 0x34);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7B, 0x52);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7C, 0x3f);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7D, 0x44);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7E, 0x35);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7F, 0x2f);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x80, 0x21);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x81, 0x10);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x82, 0x00);

    /* Page2, for GIP */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE0, 0x02);

    /* GIP_L Pin mapping */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x00, 0x47);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x01, 0x47);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x02, 0x45);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x03, 0x45);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x04, 0x4B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x05, 0x4B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x06, 0x49);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x07, 0x49);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x08, 0x41);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x09, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0A, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0B, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0C, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0D, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0E, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0F, 0x43);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x10, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x11, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x12, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x13, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x14, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x15, 0x1F);

    /* GIP_R Pin mapping */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x16, 0x46);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x17, 0x46);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x18, 0x44);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x19, 0x44);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1A, 0x4A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1B, 0x4A);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1C, 0x48);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1D, 0x48);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1E, 0x40);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x1F, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x20, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x21, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x22, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x23, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x24, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x25, 0x42);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x26, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x27, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x28, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x29, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2A, 0x1F);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2B, 0x1F);

    /* GIP Timing */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x58, 0x40); /* 0x10 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x59, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5A, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5B, 0x30);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5C, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5D, 0x30);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5E, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x5F, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x60, 0x00); /* 0x30 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x61, 0x01);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x62, 0x02);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x63, 0x03); /* 0x14 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x64, 0x6B); /* 0x6A */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x65, 0x00); /* 0x05 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x66, 0x00); /* 0x12 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x67, 0x73);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x68, 0x05);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x69, 0x06); /* 0x14 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6A, 0x6b); /* 0x6A */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6B, 0x08); /* 0x09 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6D, 0x04);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6E, 0x04);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x6F, 0x88);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x70, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x71, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x72, 0x06);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x73, 0x7B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x74, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x75, 0x07); /* 0x3C */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x76, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x77, 0x5D); /* 0x0D */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x78, 0x17); /* 0x2C */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x79, 0x1F); /* 0x00 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7A, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7B, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7C, 0x00);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7D, 0x03);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x7E, 0x7B);

    /* Page1 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE0, 0x01);
#if 1
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x0E, 0x01); /* LEDON output VCSW2 */
#endif
    /* sunxi_lcd_dsi_dcs_write_1para(sel,0x4a,0x35); add by lidf eng mode */

    /* Page3 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE0, 0x03);
    /* From 2E to 2F, LED_VOL */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x98, 0x2F);

    /* Page4 ESD check */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE0, 0x04);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2B, 0x2B);
    sunxi_lcd_dsi_dcs_write_1para(sel, 0x2E, 0X44);

    /* Page0 */
    sunxi_lcd_dsi_dcs_write_1para(sel, 0xE0, 0x00);

    /* SLP OUT */
    /* SSD_Number(0x01); */
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x11);   /* SLPOUT */
    /* Delayms(120); */
    sunxi_lcd_delay_ms(120);

    /* DISP ON */
    /* SSD_Number(0x01); */
    sunxi_lcd_dsi_dcs_write_0para(sel, 0x29);   /* DSPON */
    /* Delayms(5); */
    sunxi_lcd_delay_ms(5);

    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(200);
}

static void LCD_panel_exit(u32 sel)
{
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_SET_DISPLAY_OFF);
    sunxi_lcd_delay_ms(20);
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_ENTER_SLEEP_MODE);
    sunxi_lcd_delay_ms(120);
}

/* sel: 0:lcd0; 1:lcd1 */
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel S6D7AA0X01_panel = {
    /* panel driver name, must mach the lcd_drv_name in sys_config.fex */
    .name = "S6D7AA0X01",
    .func = {
         .cfg_panel_info = LCD_cfg_panel_info,
         .cfg_open_flow = LCD_open_flow,
         .cfg_close_flow = LCD_close_flow,
         .lcd_user_defined_func = LCD_user_defined_func,
         }
    ,
};
