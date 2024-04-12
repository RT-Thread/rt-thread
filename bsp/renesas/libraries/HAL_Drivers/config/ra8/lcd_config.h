/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-01     Rbb666       the first version
 */
#ifndef __LCD_CONFIG_H_
#define __LCD_CONFIG_H_

typedef enum
{
    ROTATION_ZERO = 0,
    ROTATION_090 = 90,
    ROTATION_180 = 180,
    ROTATION_270 = 270,
} bsp_rotation;

#define LCD_WIDTH               DISPLAY_HSIZE_INPUT0
#define LCD_HEIGHT              DISPLAY_VSIZE_INPUT0
#define LCD_BITS_PER_PIXEL      DISPLAY_BITS_PER_PIXEL_INPUT1
#define LCD_PIXEL_FORMAT        RTGRAPHIC_PIXEL_FORMAT_RGB565
#define LCD_BUF_SIZE            (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)

#define LCD_NUM_FRAMEBUFFERS    (2)
#define ENABLE_DOUBLE_BUFFER    (1)

#define LCD_BL_PIN              BSP_IO_PORT_10_PIN_11
#define LCD_RST_PIN         	BSP_IO_PORT_11_PIN_04

#endif
