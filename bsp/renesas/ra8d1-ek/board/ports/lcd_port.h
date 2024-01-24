/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2018-07-28     liu2guang      the first version for STM32F469NI-Discovery.
 */

#ifndef __DRV_LCD_H_
#define __DRV_LCD_H_

#include <rtthread.h>
#include <rtdevice.h>

typedef enum
{
    ROTATION_ZERO = 0,
    ROTATION_090 = 90,
    ROTATION_180 = 180,
    ROTATION_270 = 270,
} bsp_rotation;

#define LCD_WIDTH           DISPLAY_HSIZE_INPUT0
#define LCD_HEIGHT          DISPLAY_VSIZE_INPUT0
#define LCD_BITS_PER_PIXEL  DISPLAY_BITS_PER_PIXEL_INPUT1
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565
#define LCD_BUF_SIZE        (LCD_WIDTH * LCD_HEIGHT * LCD_BITS_PER_PIXEL / 8)

#define LCD_XSTRIDE_PHYS          (((DISPLAY_BUFFER_STRIDE_PIXELS_INPUT0 * LCD_BITS_PER_PIXEL + 0x1FF) & 0xFFFFFE00) / LCD_BITS_PER_PIXEL)
#define LCD_NUM_FRAMEBUFFERS    (2)

#define LCD_BL_PIN  BSP_IO_PORT_04_PIN_04

#endif
