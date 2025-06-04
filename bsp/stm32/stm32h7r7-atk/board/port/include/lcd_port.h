/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-08     zylx         first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

struct drv_lcd_device
{
    struct rt_device parent;
    struct rt_device_graphic_info lcd_info;

    struct rt_semaphore lcd_lock;

    /* 0:front_buf is being used 1: back_buf is being used*/
    rt_uint8_t cur_buf;
    rt_uint8_t *front_buf;
    rt_uint8_t *back_buf;
};

#if defined(BSP_USING_OLED_454_MIPI)
    /* RT-Thread AMOLED 1.44 inch screen, 454 * 454 bridged by SSD2828 RGB to mipi IC */
    #define LCD_WIDTH           454
    #define LCD_HEIGHT          454
    #define LCD_BITS_PER_PIXEL  16
    #define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
    #define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565   //RTGRAPHIC_PIXEL_FORMAT_RGB888

    #define LCD_HSYNC_WIDTH     20
    #define LCD_VSYNC_HEIGHT    4
    #define LCD_HBP             40
    #define LCD_VBP             12
    #define LCD_HFP             20
    #define LCD_VFP             20

    #define LCD_BACKLIGHT_USING_GPIO
    #define LCD_BL_GPIO_NUM     GET_PIN(G, 15)

#elif defined(BSP_USING_LCD_360_REDUCED)
    /* RT-Thread produced or atk 4.3 inch screen, 360 * 360 reduced on 800 * 480 */
    #define LCD_WIDTH           360//800//480//800
    #define LCD_HEIGHT          360//480//800//480
    #define LCD_BITS_PER_PIXEL  16//24
    #define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
    #define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565   //RTGRAPHIC_PIXEL_FORMAT_RGB888

    #define LCD_HSYNC_WIDTH     1
    #define LCD_VSYNC_HEIGHT    1
    #define LCD_HBP             6//88
    #define LCD_VBP             6//32
    #define LCD_HFP             480//40+440
    #define LCD_VFP             133//13+120

    #define LCD_BACKLIGHT_USING_GPIO
    #define LCD_BL_GPIO_NUM     GET_PIN(G, 15)

#elif defined(BSP_USING_LCD_454_REDUCED)
    /* RT-Thread produced or atk 4.3 inch screen, 454 * 454 reduced on 800 * 480 */
    #define LCD_WIDTH           454
    #define LCD_HEIGHT          454
    #define LCD_BITS_PER_PIXEL  16
    #define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
    #define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565   //RTGRAPHIC_PIXEL_FORMAT_RGB888

    #define LCD_HSYNC_WIDTH     1
    #define LCD_VSYNC_HEIGHT    1
    #define LCD_HBP             6
    #define LCD_VBP             6
    #define LCD_HFP             (480 - 94)
    #define LCD_VFP             (133 - 26)

    #define LCD_BACKLIGHT_USING_GPIO
    #define LCD_BL_GPIO_NUM     GET_PIN(G, 15)

#else
    //BSP_USING_LCD_800_RGB
    /* RT-Thread produced or atk 4.3 inch screen, 800 * 480 , PixClock 33Mhz */
    #define LCD_WIDTH           800 //480
    #define LCD_HEIGHT          480 //272
    #define LCD_BITS_PER_PIXEL  16
    #define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
    #define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565

    // applied to ATK-4384 LCD screen
    #define LCD_HSYNC_WIDTH     48
    #define LCD_VSYNC_HEIGHT    3
    #define LCD_HBP             88
    #define LCD_VBP             32
    #define LCD_HFP             40
    #define LCD_VFP             13

    #define LCD_BACKLIGHT_USING_GPIO
    #define LCD_BL_GPIO_NUM     GET_PIN(G, 15)      //LCD Backlight set PG15 High to Enable.

#endif

#endif /* __LCD_PORT_H__ */
