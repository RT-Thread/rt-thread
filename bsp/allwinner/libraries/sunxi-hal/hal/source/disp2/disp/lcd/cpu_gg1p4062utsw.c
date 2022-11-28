/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "cpu_gg1p4062utsw.h"

#define gg1p4062utsw_rs(v) sunxi_lcd_gpio_set_value(0, 0, v)
#define gg1p4062utsw_cs(v) sunxi_lcd_gpio_set_value(0, 1, v)

#define lcd_cpu_wr_index_16b sunxi_lcd_cpu_write_index
#define lcd_cpu_wr_data_16b sunxi_lcd_cpu_write_data

static void lcd_power_on(u32 sel);
static void lcd_power_off(u32 sel);
static void lcd_bl_open(u32 sel);
static void lcd_bl_close(u32 sel);

static void lcd_panel_init(u32 sel);
static void lcd_panel_exit(u32 sel);

static void gg1p4062utsw_init(__u32 sel);
static void lcd_cfg_panel_info(struct panel_extend_para *info)
{
    u32 i = 0, j = 0;
    u32 items;
    u8 lcd_gamma_tbl[][2] = {
        /*{input value, corrected value} */
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

            value = lcd_gamma_tbl[i][1] + ((lcd_gamma_tbl[i + 1][1]
                            -
                            lcd_gamma_tbl[i][1]) *
                               j) / num;
            info->lcd_gamma_tbl[lcd_gamma_tbl[i][0] + j] =
                (value << 16) + (value << 8) + value;
        }
    }
    info->lcd_gamma_tbl[255] = (lcd_gamma_tbl[items - 1][1] << 16)
        + (lcd_gamma_tbl[items - 1][1] << 8) + lcd_gamma_tbl[items - 1][1];

    memcpy(info->lcd_cmap_tbl, lcd_cmap_tbl, sizeof(lcd_cmap_tbl));

}

static s32 lcd_open_flow(u32 sel)
{
    /* open lcd power, and delay 50ms */
    LCD_OPEN_FUNC(sel, lcd_power_on, 30);
    /* open lcd power, than delay 200ms */
    LCD_OPEN_FUNC(sel, lcd_panel_init, 50);
    /* open lcd controller, and delay 100ms */
    LCD_OPEN_FUNC(sel, sunxi_lcd_tcon_enable, 100);
    /* open lcd backlight, and delay 0ms */
    LCD_OPEN_FUNC(sel, lcd_bl_open, 0);

    return 0;
}

static s32 lcd_close_flow(u32 sel)
{
    /* close lcd backlight, and delay 0ms */
    LCD_CLOSE_FUNC(sel, lcd_bl_close, 0);
    /* close lcd controller, and delay 0ms */
    LCD_CLOSE_FUNC(sel, sunxi_lcd_tcon_disable, 0);
    /* open lcd power, than delay 200ms */
    LCD_CLOSE_FUNC(sel, lcd_panel_exit, 200);
    /* close lcd power, and delay 500ms */
    LCD_CLOSE_FUNC(sel, lcd_power_off, 500);

    return 0;
}

static void lcd_power_on(u32 sel)
{
    /* enable lcd power0 */
    sunxi_lcd_power_enable(sel, 0);
    /* enable lcd pin output */
    sunxi_lcd_pin_cfg(sel, 1);
}

static void lcd_power_off(u32 sel)
{
    /* disable lcd pin output */
    sunxi_lcd_pin_cfg(sel, 0);
    /* disable lcd power0 */
    sunxi_lcd_power_disable(sel, 0);
}

static void lcd_bl_open(u32 sel)
{
    sunxi_lcd_pwm_enable(sel);
    /* config lcd_bl_en pin to open lcd backlight */
    sunxi_lcd_backlight_enable(sel);
}

static void lcd_bl_close(u32 sel)
{
    /* config lcd_bl_en pin to close lcd backlight */
    sunxi_lcd_backlight_disable(sel);
    sunxi_lcd_pwm_disable(sel);
}

static void lcd_panel_init(u32 sel)
{
    gg1p4062utsw_init(sel);
}

static void lcd_panel_exit(u32 sel)
{
}

static s32 lcd_user_defined_func(u32 sel, u32 para1, u32 para2, u32 para3)
{
    return 0;
}

void lcd_dbi_wr_dcs(__u32 sel, __u8 cmd, __u8 *para, __u32 para_num)
{
    __u8 index = cmd;
    __u8 *data_p = para;
    __u16 i;

    lcd_cpu_wr_index_16b(sel, index);
    for (i = 0; i < para_num; i++)
        lcd_cpu_wr_data_16b(sel, *(data_p++));
}

void lcd_cpu_panel_fr(__u32 sel, __u32 w, __u32 h, __u32 x, __u32 y)
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

    para_num = 0;
    lcd_dbi_wr_dcs(sel, DSI_DCS_WRITE_MEMORY_START, para, para_num);
}

static void gg1p4062utsw_init(__u32 sel)
{
    struct disp_panel_para *panel_info =
        kmalloc(sizeof(struct disp_panel_para),
            GFP_KERNEL | __GFP_ZERO);

    if (panel_info == NULL) {
        __wrn("kmalloc for panel_info(%zu bytes) fail!",
              sizeof(struct disp_panel_para));
        return;
    }
    bsp_disp_get_panel_info(sel, panel_info);
    gg1p4062utsw_cs(0);
    gg1p4062utsw_rs(1);
    sunxi_lcd_delay_ms(50);
    gg1p4062utsw_rs(0);
    sunxi_lcd_delay_ms(50);
    gg1p4062utsw_rs(1);

    sunxi_lcd_delay_ms(100);
    lcd_cpu_wr_index_16b(sel, 0x11);
    lcd_cpu_wr_index_16b(sel, 0x20);
    lcd_cpu_wr_index_16b(sel, 0x38);
    lcd_cpu_wr_index_16b(sel, 0x13);
    sunxi_lcd_delay_ms(50);
    lcd_cpu_wr_index_16b(sel, 0x3A);
    lcd_cpu_wr_data_16b(sel, 0x05);
    lcd_cpu_wr_index_16b(sel, 0xC0);
    lcd_cpu_wr_data_16b(sel, 0x03);
    sunxi_lcd_delay_ms(50);
    lcd_cpu_wr_index_16b(sel, 0xC5);
    lcd_cpu_wr_data_16b(sel, 0xC0);
    sunxi_lcd_delay_ms(50);
    lcd_cpu_wr_index_16b(sel, 0xC6);
    lcd_cpu_wr_data_16b(sel, 0x07);
    lcd_cpu_wr_index_16b(sel, 0xE0);
    lcd_cpu_wr_data_16b(sel, 0x10);
    lcd_cpu_wr_data_16b(sel, 0x11);
    lcd_cpu_wr_data_16b(sel, 0x11);
    lcd_cpu_wr_data_16b(sel, 0x11);
    lcd_cpu_wr_data_16b(sel, 0x11);
    lcd_cpu_wr_data_16b(sel, 0x11);
    lcd_cpu_wr_data_16b(sel, 0x01);
    lcd_cpu_wr_index_16b(sel, 0x29);
    lcd_cpu_wr_index_16b(sel, 0x2a);
    lcd_cpu_wr_data_16b(sel, 0x00);
    lcd_cpu_wr_data_16b(sel, 0x00);
    lcd_cpu_wr_data_16b(sel, 0x00);
    lcd_cpu_wr_data_16b(sel, 0x7f);
    lcd_cpu_wr_index_16b(sel, 0x2b);
    lcd_cpu_wr_data_16b(sel, 0x00);
    lcd_cpu_wr_data_16b(sel, 0x00);
    lcd_cpu_wr_data_16b(sel, 0x00);
    lcd_cpu_wr_data_16b(sel, 0x9f);

    lcd_cpu_panel_fr(sel, panel_info->lcd_x, panel_info->lcd_y, 0, 0);

    if (panel_info->lcd_cpu_mode == LCD_CPU_AUTO_MODE)
        sunxi_lcd_cpu_set_auto_mode(sel);

    disp_sys_free(panel_info);
}

struct __lcd_panel gg1p4062utsw_panel = {
    /*
     * panel driver name, must mach the name
     * of lcd_drv_name in sys_config.fex
     */
    .name = "gg1p4062utsw",
    .func = {
         .cfg_panel_info = lcd_cfg_panel_info,
         .cfg_open_flow = lcd_open_flow,
         .cfg_close_flow = lcd_close_flow,
         .lcd_user_defined_func = lcd_user_defined_func,
         }
    ,
};
