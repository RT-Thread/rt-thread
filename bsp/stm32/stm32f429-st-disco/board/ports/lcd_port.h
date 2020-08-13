/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-08     bernard      The first version for STM32F429 DISCO
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

/* 240 * 320 */
#define LCD_WIDTH           240
#define LCD_HEIGHT          320
#define LCD_BITS_PER_PIXEL  16
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565

#define LCD_HSYNC_WIDTH     10
#define LCD_VSYNC_HEIGHT    2
#define LCD_HBP             20
#define LCD_VBP             2
#define LCD_HFP             10
#define LCD_VFP             5

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_GPIO_NUM     GET_PIN(D, 7)
#define LCD_DISP_GPIO_NUM   GET_PIN(D, 4)

#endif /* __LCD_PORT_H__ */
