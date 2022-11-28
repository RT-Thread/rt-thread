/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "tm_dsi_panel.h"
#include "panels.h"

extern s32 bsp_disp_get_panel_info(u32 screen_id,
        struct disp_panel_para *info);
static void LCD_power_on(u32 sel);
static void LCD_power_off(u32 sel);
static void LCD_bl_open(u32 sel);
static void LCD_bl_close(u32 sel);

static void LCD_panel_init(u32 sel);
static void LCD_panel_exit(u32 sel);

static u8 const mipi_dcs_pixel_format[4] = {0x77, 0x66, 0x66, 0x55};
#define panel_reset(val) sunxi_lcd_gpio_set_value(sel, 1, val)
#define power_en(val) sunxi_lcd_gpio_set_value(sel, 0, val)

static void LCD_cfg_panel_info(struct panel_extend_para *info)
{
    u32 i = 0, j = 0;
    u32 items;
    u8 lcd_gamma_tbl[][2] = {
        /*{input value, corrected value} */
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
    LCD_OPEN_FUNC(sel, LCD_power_on,
              100); /* open lcd power, and delay 50ms */
    LCD_OPEN_FUNC(sel, LCD_panel_init,
              200); /* open lcd power, than delay 200ms */
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable,
              50); /* open lcd controller, and delay 100ms */
    LCD_OPEN_FUNC(sel, LCD_bl_open,
              0); /* open lcd backlight, and delay 0ms */

    return 0;
}

static s32 LCD_close_flow(u32 sel)
{
    LCD_CLOSE_FUNC(sel, LCD_bl_close,
               200); /* close lcd backlight, and delay 0ms */
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable,
               20); /* close lcd controller, and delay 0ms */
    LCD_CLOSE_FUNC(sel, LCD_panel_exit,
               10); /* open lcd power, than delay 200ms */
    LCD_CLOSE_FUNC(sel, LCD_power_off,
               500); /* close lcd power, and delay 500ms */

    return 0;
}

static void LCD_power_on(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 1);
    sunxi_lcd_power_enable(sel, 0);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_enable(sel, 1);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_enable(sel, 2);
    sunxi_lcd_delay_ms(5);
    power_en(1);
    sunxi_lcd_delay_ms(20);
    panel_reset(0);
    sunxi_lcd_delay_ms(10);
    panel_reset(1);
}

static void LCD_power_off(u32 sel)
{
    sunxi_lcd_pin_cfg(sel, 0);
    power_en(0);
    sunxi_lcd_delay_ms(20);
    panel_reset(0);
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_disable(
        sel, 2); /* config lcd_power pin to close lcd power2 */
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_disable(
        sel, 1); /* config lcd_power pin to close lcd power1 */
    sunxi_lcd_delay_ms(5);
    sunxi_lcd_power_disable(
        sel, 0); /* config lcd_power pin to close lcd power */
}

static void LCD_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
    sunxi_lcd_delay_ms(50);
    sunxi_lcd_backlight_enable(
        sel); /* config lcd_bl_en pin to open lcd backlight */
}

static void LCD_bl_close(u32 sel)
{
    sunxi_lcd_backlight_disable(
        sel); /* config lcd_bl_en pin to close lcd backlight */
    sunxi_lcd_delay_ms(20);
    sunxi_lcd_pwm_disable(sel);
}

#define REGFLAG_DELAY 0XFE
#define REGFLAG_END_OF_TABLE 0xFF /* END OF REGISTERS MARKER */

struct LCM_setting_table {
    u8 cmd;
    u32 count;
    u8 para_list[64];
};

/*add panel initialization code*/
static struct LCM_setting_table LCM_TM040YVZG31_setting[] = {
    {0xB9, 3, {0xFF, 0x83, 0x69} },
    /*Set Power*/
    {0xB1, 19, {0x01, 0x00, 0x34, 0x0A,
                 0x00, 0x11, 0x11, 0x2F, 0x37,
                 0x3F, 0x3F, 0x07, 0x3A, 0x01,
                 0xE6, 0xE6, 0xE6, 0xE6, 0xE6} },
    /* set display,0x2B DSI video mode
     * 0x20 DSI command mod
     */
    {0xB2, 15, {0x00, 0x2B, 0x03, 0x03,
                 0x70, 0x00, 0xFF, 0x00, 0x00,
                 0x00, 0x00, 0x03, 0x03, 0x00,
                 0x01} },
    /*set display 480*800
     *0x00 column inversion, 0x01 1-dot inversion
     *0x02 2-dot inversion, 0x3 zig-zag inversion
     */
    {0xB4, 5, {0x00, 0x18, 0x70, 0x00, 0x00} },
    /*Set VCOM*/
    {0xB6, 2, {0x4a, 0x4a} },
    /*set enable chopper function*/
    {0x36, 1, {0x00} },
    /*set GIP*/
    {0xD5, 26, {0x00, 0x00, 0x03, 0x37,
                0x01, 0x02, 0x00, 0x70, 0x11,
                0x13, 0x00, 0x00, 0x60, 0x24,
                0x71, 0x35, 0x00, 0x00, 0x60,
                0x24, 0x71, 0x35, 0x07, 0x0F,
                0x00, 0x04 } },
    /*R Gamma*/
    {0xE0, 34, {0x04, 0x1F, 0x25, 0x2B,
                0X3E, 0x35, 0x34, 0x4A, 0x08,
                0x0E, 0x0F, 0x14, 0x16, 0x14,
                0x15, 0x14, 0x1F, 0x04, 0x1F,
                0x25, 0x2B, 0x3E, 0x35, 0x34,
                0x4A, 0x08, 0x0E, 0x0F, 0x14,
                0x16, 0x14, 0x15, 0x14, 0x1F} },
    {0xCC, 1, {0x02 } },
    {0x3A, 1, {0x77 } },
     /*set mipi, 0x11 two lanes, 0x10 one lane*/
    {0xBA, 13, {0x00, 0xA0, 0xC6, 0x00,
                0x0A, 0x00, 0x10, 0x30, 0x6F,
                0x02, 0x11, 0x18, 0x40} },
    /*sleep exit*/
    {0x11, 0, {0x00 } },
    {REGFLAG_DELAY, REGFLAG_DELAY, {120} },
    /*display on*/
    {0x29, 0, {0x00 } },
    {REGFLAG_DELAY, REGFLAG_DELAY, {10} },
    {REGFLAG_END_OF_TABLE, REGFLAG_END_OF_TABLE, {} }
};

static void LCD_panel_init(u32 sel)
{
    __u32 i;
    char model_name[25];

    disp_sys_script_get_item("lcd0", "lcd_model_name",
        (int *)model_name, 25);
    sunxi_lcd_dsi_clk_enable(sel);
    sunxi_lcd_delay_ms(20);

    for (i = 0;; i++) {
        if (LCM_TM040YVZG31_setting[i].count == REGFLAG_END_OF_TABLE)
            break;
        else if (LCM_TM040YVZG31_setting[i].count == REGFLAG_DELAY)
            sunxi_lcd_delay_ms(
                LCM_TM040YVZG31_setting[i].para_list[0]);
#ifdef SUPPORT_DSI
        else
            dsi_dcs_wr(sel, LCM_TM040YVZG31_setting[i].cmd,
                   LCM_TM040YVZG31_setting[i].para_list,
                   LCM_TM040YVZG31_setting[i].count);
#endif
    }
}

static void LCD_panel_exit(u32 sel)
{
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_SET_DISPLAY_OFF);
    sunxi_lcd_delay_ms(20);
    sunxi_lcd_dsi_dcs_write_0para(sel, DSI_DCS_ENTER_SLEEP_MODE);
    sunxi_lcd_delay_ms(80);
}

/* sel: 0:lcd0; 1:lcd1 */
static s32 LCD_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

/* sel: 0:lcd0; 1:lcd1 */
/*static s32 LCD_set_bright(u32 sel, u32 bright)*/
/*{*/
    /*sunxi_lcd_dsi_dcs_write_1para(sel,0x51,bright);*/
    /*return 0;*/
/*}*/

struct __lcd_panel tm_dsi_panel = {
    /* panel driver name, must mach the name of
     * lcd_drv_name in sys_config.fex
    */
    .name = "tm_dsi_panel",
    .func = {
    .cfg_panel_info = LCD_cfg_panel_info,
    .cfg_open_flow = LCD_open_flow,
    .cfg_close_flow = LCD_close_flow,
    .lcd_user_defined_func = LCD_user_defined_func,
    /*.set_bright = LCD_set_bright, */
    },
};
