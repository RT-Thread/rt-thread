/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-11     Lyons        first version
 * 2021-06-24     RiceChen     refactor
 */

#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#include <board.h>
#include "drv_pin.h"
#include "drv_common.h"

#include "fsl_iomuxc.h"
#include "fsl_clock.h"
#include "fsl_elcdif.h"

#define LCD_GPIO_MAX               29
#define LCD_MUX_BASE                0x020E0104U
#define LCD_CONFIG_BASE             0x020E0390U

#define LCD_WIDTH                   BSP_LCD_WIDTH
#define LCD_HEIGHT                  BSP_LCD_HEIGHT
#define LCD_VSW                     BSP_LCD_VSW
#define LCD_VBP                     BSP_LCD_VBP
#define LCD_VFP                     BSP_LCD_VFP
#define LCD_HSW                     BSP_LCD_HSW
#define LCD_HBP                     BSP_LCD_HBP
#define LCD_HFP                     BSP_LCD_HFP
#define LCD_PLL_DIV                 BSP_LCD_PLL_DIV

#define LCD_BITS_PER_PIXEL          32
#define LCD_BUF_SIZE                (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)

#define IMX6ULL_LCD_BL_PIN          GET_PIN(1, 8)

struct fb_fix_screen_info
{
    rt_uint32_t shamem_start;
    rt_uint32_t shamem_len;
};

struct lcd_info
{
    struct rt_device_graphic_info graphic;
    struct fb_fix_screen_info screen;
};

struct imx6ull_lcd_config
{
    LCDIF_Type *ELCDIF;
    char *name;

    rt_uint32_t apd_clk_name;
    rt_uint32_t pix_clk_name;

    rt_uint32_t lcd_mux_base;
    rt_uint32_t lcd_cfg_base;
};

struct imx6ull_lcd_bus
{
    struct rt_device parent;
    struct rt_device_graphic_info info;

    struct imx6ull_lcd_config *config;

    rt_uint8_t *fb_phy;
    rt_uint8_t *fb_virt;
};

#ifdef BSP_USING_LCD
#define LCD_BUS_CONFIG                             \
    {                                               \
        .ELCDIF        = LCDIF,                     \
        .name         = "lcd",                     \
        .apd_clk_name = kCLOCK_Lcd,                 \
        .pix_clk_name = kCLOCK_Lcdif1,              \
        .lcd_mux_base = LCD_MUX_BASE,               \
        .lcd_cfg_base = LCD_CONFIG_BASE,            \
    }
#endif /* BSP_USING_LCD */


#endif
