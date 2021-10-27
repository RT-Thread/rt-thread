/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-14    spaceman   first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

/* TK043F1508 RM68120 5 inch screen, 800 * 480 */
#define LCD_WIDTH           800
#define LCD_HEIGHT          480
#define LCD_BITS_PER_PIXEL  32
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565

#define LCD_HSYNC_WIDTH     96
#define LCD_VSYNC_HEIGHT    2
#define LCD_HBP             10
#define LCD_VBP             10
#define LCD_HFP             10
#define LCD_VFP             10

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_GPIO_NUM -1
#define LCD_DISP_GPIO_NUM -1

/* TK043F1508 RM68120 5 inch screen, 800 * 480 */

#endif /* __LCD_PORT_H__ */
