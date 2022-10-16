/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-07     NU-LL        first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

#include <rtthread.h>
#include "lcd.h"
#include "st7735.h"

#ifdef __cplusplus
extern "C" {
#endif

//LCD
#define LCD_HEIGHT          (80U)
#define LCD_WIDTH           (160U)
#define LCD_BITS_PER_PIXEL  (16)
#define LCD_PIXEL_FORMAT    (RTGRAPHIC_PIXEL_FORMAT_RGB565)
#define LCD_BUF_SIZE        (LCD_WIDTH*LCD_HEIGHT*LCD_BITS_PER_PIXEL/8)
//PWM
#define LCD_PWM_DEV_NAME    "pwm1"
#define LCD_PWM_DEV_CHANNEL (2)
//SPI
#define LCD_SPI_BUS_NAME    "spi4"
#define LCD_SPI_DEV_NAME    "spi40"
#define LCD_SPI_DEV_CS_GPIO (RT_NULL)
#define LCD_SPI_DEV_CS_PIN  (RT_NULL)

#ifdef __cplusplus
}
#endif

#endif

