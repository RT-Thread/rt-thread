/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-24     spaceman          the first version
 */

#ifndef __LCD_PORT_H__
#define __LCD_PORT_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

//LCD
#define LCD_HEIGHT          (240U)
#define LCD_WIDTH           (240U)
#define LCD_BITS_PER_PIXEL  (16)
#define LCD_PIXEL_FORMAT    (RTGRAPHIC_PIXEL_FORMAT_RGB565)
#define LCD_BUF_SIZE        (LCD_WIDTH*LCD_HEIGHT*LCD_BITS_PER_PIXEL/8)
//BACKLIGHT
#define LCD_BACKLIGHT_PIN   (GET_PIN(D, 15))
//CMD/DATA
#define LCD_CMD_DATA_PIN    (GET_PIN(E, 15))
//SPI
#define LCD_SPI_BUS_NAME    "spi4"
#define LCD_SPI_DEV_NAME    "spi40"
#define LCD_SPI_DEV_CS_PIN  (GET_PIN(E, 11))
#define LCD_SPI_MAX_SPEED   (60 * 1000 *1000)    /* 60M */

#ifdef __cplusplus
}
#endif

#endif /* __LCD_PORT_H__ */

