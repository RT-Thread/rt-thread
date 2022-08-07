/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-19     ZYH          first version
 */

#ifndef __DRV_IO_CONFIG_H__
#define __DRV_IO_CONFIG_H__

#include <rtconfig.h>

enum HS_GPIO_CONFIG
{
#ifdef BSP_USING_LCD
    LCD_DC_PIN = 0,     /* LCD DC PIN */
#if BSP_LCD_RST_PIN >= 0
    LCD_RST_PIN,
#endif
#if BSP_LCD_BACKLIGHT_PIN >= 0
    LCD_BACKLIGHT_PIN,
#endif
#endif
#ifdef BSP_SPI1_USING_SS0
    SPI1_CS0_PIN,
#endif
#ifdef BSP_SPI1_USING_SS1
    SPI1_CS1_PIN,
#endif
#ifdef BSP_SPI1_USING_SS2
    SPI1_CS2_PIN,
#endif
#ifdef BSP_SPI1_USING_SS3
    SPI1_CS3_PIN,
#endif

#ifdef BSP_USING_BRIDGE
    SPI2_INT_PIN,
    SPI2_READY_PIN,
#endif
    GPIO_ALLOC_START /* index of gpio driver start */
};

extern int io_config_init(void);

#endif
