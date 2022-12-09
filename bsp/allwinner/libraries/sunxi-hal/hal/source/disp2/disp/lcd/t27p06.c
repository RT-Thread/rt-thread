/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "t27p06.h"

#define t27p06_spi_scl_1    sunxi_lcd_gpio_set_value(0, 2, 1)
#define t27p06_spi_scl_0    sunxi_lcd_gpio_set_value(0, 2, 0)
#define t27p06_spi_sdi_1    sunxi_lcd_gpio_set_value(0, 1, 1)
#define t27p06_spi_sdi_0    sunxi_lcd_gpio_set_value(0, 1, 0)
#define t27p06_spi_cs_1 sunxi_lcd_gpio_set_value(0, 0, 1)
#define t27p06_spi_cs_0 sunxi_lcd_gpio_set_value(0, 0, 0)

static void t27p06_spi_wr(u32 value);
static void lcd_panel_t27p06_init(void);
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
    LCD_OPEN_FUNC(sel, LCD_power_on, 0);
    /* open lcd power, than delay 200ms */
    LCD_OPEN_FUNC(sel, LCD_panel_init, 10);
    /* open lcd controller, and delay 100ms */
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 300);
    /* open lcd backlight, and delay 0ms */
    LCD_OPEN_FUNC(sel, LCD_bl_open, 0);

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    /* close lcd backlight, and delay 0ms */
    LCD_CLOSE_FUNC(sel, LCD_bl_close, 300);
    /* close lcd controller, and delay 0ms */
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 10);
    /* open lcd power, than delay 200ms */
    LCD_CLOSE_FUNC(sel, LCD_panel_exit, 10);
    /* close lcd power, and delay 500ms */
    LCD_CLOSE_FUNC(sel, LCD_power_off, 500);

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

static void LCD_panel_init(u32 sel)
{
    struct disp_panel_para *info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL | __GFP_ZERO);

    bsp_disp_get_panel_info(sel, info);
    lcd_panel_t27p06_init();
    disp_sys_free(info);
}

static void LCD_panel_exit(u32 sel)
{
    struct disp_panel_para *info =
        kmalloc(sizeof(struct disp_panel_para), GFP_KERNEL | __GFP_ZERO);

    bsp_disp_get_panel_info(sel, info);
    disp_sys_free(info);
}

static void t27p06_spi_wr(u32 value)
{
    u32 i;

    t27p06_spi_cs_1;
    t27p06_spi_sdi_1;
    t27p06_spi_scl_1;
    sunxi_lcd_delay_us(10);
    t27p06_spi_cs_0;
    sunxi_lcd_delay_us(10);
    for (i = 0; i < 16; i++) {
        sunxi_lcd_delay_us(10);
        t27p06_spi_scl_0;
        if (value & 0x8000)
            t27p06_spi_sdi_1;
        else
            t27p06_spi_sdi_0;
        value <<= 1;
        sunxi_lcd_delay_us(10);
        t27p06_spi_scl_1;
    }
    sunxi_lcd_delay_us(10);
    t27p06_spi_sdi_1;
    t27p06_spi_cs_1;
}
static void lcd_panel_t27p06_init(void)
{
    t27p06_spi_wr(0x055f);
    sunxi_lcd_delay_ms(5);
    t27p06_spi_wr(0x051f);  /* reset */
    sunxi_lcd_delay_ms(10);
    t27p06_spi_wr(0x055f);
    sunxi_lcd_delay_ms(50);
    t27p06_spi_wr(0x2b01);  /* exit standby mode */
    t27p06_spi_wr(0x0009);  /* vcomac */
    t27p06_spi_wr(0x019f);  /* vcomdc */
/* t27p06_spi_wr(0x040b);//8-bit rgb interface */
    t27p06_spi_wr(0x040c);  /* 8-bit rgb interface */
    t27p06_spi_wr(0x1604);  /* default gamma setting  2.2 */
}

/* sel: 0:lcd0; 1:lcd1 */
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

struct __lcd_panel t27p06_panel = {
    /* panel driver name, must mach the lcd_drv_name in sys_config.fex */
    .name = "t27p06",
    .func = {
         .cfg_panel_info = LCD_cfg_panel_info,
         .cfg_open_flow = LCD_open_flow,
         .cfg_close_flow = LCD_close_flow,
         .lcd_user_defined_func = LCD_user_defined_func,
         }
    ,
};
