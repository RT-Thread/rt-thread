/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-26     lik         first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

#include "board.h"

/* atk 4.3 inch screen, 480 * 272 */
#define LCD_WIDTH 480
#define LCD_HEIGHT 272
#define LCD_BITS_PER_PIXEL 16
#define LCD_BUF_SIZE (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
#define LCD_PIXEL_FORMAT RTGRAPHIC_PIXEL_FORMAT_RGB565

#define LCD_CLK_DIV 15
#define LCD_HSYNC_WIDTH 5
#define LCD_VSYNC_WIDTH 5
#define LCD_HBP 40
#define LCD_VBP 8
#define LCD_HFP 5
#define LCD_VFP 8

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_GPIO GET_PIN(D, 9)
#define LCD_DISP_GPIO GET_PIN(D, 1)

#endif /* __LCD_PORT_H__ */
