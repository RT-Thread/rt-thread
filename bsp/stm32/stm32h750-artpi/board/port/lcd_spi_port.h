/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-10     zylx         first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

/* rt-thread 3.5 inch screen, 320 * 480 */
#define LCD_HOR_SCREEN
#define LCD_FULL_COLOR      BLACK

#ifndef LCD_FULL_COLOR
#define LCD_FULL_COLOR      WHITE
#endif

#ifndef LCD_HOR_SCREEN
#define LCD_WIDTH           320
#define LCD_HEIGHT          480
#else
#define LCD_WIDTH           480
#define LCD_HEIGHT          320
#endif
#define LCD_BITS_PER_PIXEL  24
#define LCD_BYTES_PER_PIXEL  (LCD_BITS_PER_PIXEL / 8)
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BYTES_PER_PIXEL)
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB888

#define LCD_BACKLIGHT_USING_GPIO
#define LCD_BL_PIN          GET_PIN(C, 6)
#define LCD_RES_PIN         GET_PIN(A, 3)
/* rt-thread 3.5 inch screen, 320 * 480 */

#endif /* __LCD_PORT_H__ */
