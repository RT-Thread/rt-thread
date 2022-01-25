/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-02-17     jinsheng    first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

/* 4.3 inch screen, 480 * 272 */
#define LCD_WIDTH           480
#define LCD_HEIGHT          272
#define LCD_BITS_PER_PIXEL  16
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565

#define LCD_HSYNC_WIDTH     41
#define LCD_VSYNC_HEIGHT    10
#define LCD_HBP             13
#define LCD_VBP             2
#define LCD_HFP             32
#define LCD_VFP             2

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_GPIO_NUM     GET_PIN(K, 3)
#define LCD_DISP_GPIO_NUM   GET_PIN(I, 12)

#endif /* __LCD_PORT_H__ */
