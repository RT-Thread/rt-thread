/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */


#ifndef __DISP_LCD_H__
#define __DISP_LCD_H__

#include "disp_private.h"

#define LCD_GPIO_NUM 8
#define LCD_POWER_NUM 4
#define LCD_POWER_STR_LEN 32
#define LCD_GPIO_REGU_NUM 3
#define LCD_GPIO_SCL (LCD_GPIO_NUM-2)
#define LCD_GPIO_SDA (LCD_GPIO_NUM-1)

struct disp_lcd_cfg {
    bool lcd_used;

    bool lcd_bl_en_used;
    struct disp_gpio_set_t lcd_bl_en;
    int lcd_bl_gpio_hdl;
    char lcd_bl_en_power[LCD_POWER_STR_LEN];

    u32 lcd_power_used[LCD_POWER_NUM];
    struct disp_power_t lcd_power[LCD_POWER_NUM];

    /* 0: invalid, 1: gpio, 2: regulator */
    u32 lcd_fix_power_used[LCD_POWER_NUM];
    struct disp_power_t lcd_fix_power[LCD_POWER_NUM];

    bool lcd_gpio_used[LCD_GPIO_NUM];
    struct disp_gpio_set_t lcd_gpio[LCD_GPIO_NUM];
    int gpio_hdl[LCD_GPIO_NUM];
    struct disp_power_t lcd_gpio_power[LCD_GPIO_REGU_NUM];

    struct disp_power_t lcd_pin_power[LCD_GPIO_REGU_NUM];

    u32 backlight_bright;
    /*
     * IEP-drc backlight dimming rate:
     * 0 -256 (256: no dimming; 0: the most dimming)
     */
    u32 backlight_dimming;
    u32 backlight_curve_adjust[101];

    u32 lcd_bright;
    u32 lcd_contrast;
    u32 lcd_saturation;
    u32 lcd_hue;
};

s32 disp_init_lcd(struct disp_bsp_init_para *para);
s32 disp_lcd_set_bright(struct disp_device *lcd, u32 bright);
s32 disp_lcd_get_bright(struct disp_device *lcd);
s32 disp_lcd_gpio_init(struct disp_device *lcd);
s32 disp_lcd_gpio_exit(struct disp_device *lcd);
s32 disp_lcd_gpio_set_direction(struct disp_device *lcd, u32 io_index,
                u32 direction);
s32 disp_lcd_gpio_get_value(struct disp_device *lcd, u32 io_index);
s32 disp_lcd_gpio_set_value(struct disp_device *lcd, u32 io_index, u32 data);
s32 disp_lcd_is_enabled(struct disp_device *lcd);
#if defined(SUPPORT_EINK) && defined(CONFIG_EINK_PANEL_USED)
extern int display_finish_flag;
#endif

#endif
