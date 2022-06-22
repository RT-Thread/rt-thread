/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-08     zylx         first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

/* armfly 5 inch screen, 800 * 480 */
#define LCD_WIDTH           800
#define LCD_HEIGHT          480
#define LCD_BITS_PER_PIXEL  16
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565

#define LCD_HSYNC_WIDTH     96
#define LCD_VSYNC_HEIGHT    2
#define LCD_HBP             10
#define LCD_VBP             10
#define LCD_HFP             10
#define LCD_VFP             10

#define LCD_BACKLIGHT_USING_PWM
#define LCD_PWM_DEV_NAME    "pwm2"
#define LCD_PWM_DEV_CHANNEL 1
/* armfly 5 inch screen, 800 * 480 */

#endif /* __LCD_PORT_H__ */
