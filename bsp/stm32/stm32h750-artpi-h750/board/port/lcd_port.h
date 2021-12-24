/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-08     zylx         first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

/* atk 4.3 inch screen, 800 * 480 */


#define LCD_WIDTH           800
#define LCD_HEIGHT          480
#define LCD_BITS_PER_PIXEL  16
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565

#define LCD_HSYNC_WIDTH     1
#define LCD_VSYNC_HEIGHT    1
#define LCD_HBP             40
#define LCD_VBP             32
#define LCD_HFP             48
#define LCD_VFP             13

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_GPIO_NUM     GET_PIN(D, 4)
#define LCD_DISP_GPIO_NUM   GET_PIN(B, 5)
/* atk 4.3 inch screen, 800 * 480 */

#endif /* __LCD_PORT_H__ */
